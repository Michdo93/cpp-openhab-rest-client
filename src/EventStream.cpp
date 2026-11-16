// Server-Sent Events – the C++ counterpart of Client.executeSSE and SSE.py.
//
// The stream is read with the curl multi interface: nextLine()/nextEvent() pump the
// connection until a complete line has arrived or the time is up. No thread is
// needed, and interrupt() wakes up a waiting call at once.
#include "internal.hpp"

#include <chrono>
#include <csignal>
#include <cstring>

namespace openhab {

static long long nowMs() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

struct EventStream::Impl {
    CURLM* multi = nullptr;
    CURL* easy = nullptr;
    curl_slist* headers = nullptr;
    std::string in;            // received, not yet returned bytes
    size_t pos = 0;            // start of the next line in "in"
    bool headersDone = false;  // status line and headers received
    int status = 0;            // HTTP status
    std::string reason;
    bool running = false;      // transfer still active
    volatile std::sig_atomic_t interrupted = 0;
    bool failed = false;
    std::string error;
    int errorStatus = 0;
    std::string url;

    ~Impl() {
        if (multi) {
            curl_multi_remove_handle(multi, easy);
            curl_multi_cleanup(multi);
        }
        if (easy) curl_easy_cleanup(easy);
        curl_slist_free_all(headers);
    }

    void fail(const std::string& msg, int st) {
        if (!failed) error = msg;
        failed = true;
        errorStatus = st;
        running = false;
    }

    // Pumps the transfer for at most waitMs; returns false if the transfer has ended.
    bool pump(int waitMs) {
        if (!multi || !running) return false;
        int still = 0, numfds = 0;
        curl_multi_poll(multi, nullptr, 0, waitMs, &numfds);
        curl_multi_perform(multi, &still);
        if (!still) {
            running = false;
            CURLMsg* m;
            int q;
            while ((m = curl_multi_info_read(multi, &q)) != nullptr) {
                if (m->msg == CURLMSG_DONE && m->data.result != CURLE_OK && !interrupted &&
                    status < 400)
                    fail(curl_easy_strerror(m->data.result), 0);
            }
        }
        return running;
    }

    static size_t onBody(char* p, size_t s, size_t n, void* u) {
        static_cast<Impl*>(u)->in.append(p, s * n);
        return s * n;
    }

    static size_t onHeader(char* line, size_t s, size_t n, void* u) {
        auto* x = static_cast<Impl*>(u);
        size_t len = s * n;
        if (len > 5 && std::strncmp(line, "HTTP/", 5) == 0) {
            x->headersDone = false;
            x->reason.clear();
            std::string l(line, len);
            while (!l.empty() && (l.back() == '\r' || l.back() == '\n')) l.pop_back();
            size_t a = l.find(' ');
            if (a != std::string::npos) {
                x->status = std::atoi(l.c_str() + a + 1);
                size_t b = l.find(' ', a + 1);
                if (b != std::string::npos) x->reason = l.substr(b + 1);
            }
        } else if (len <= 2 && (line[0] == '\r' || line[0] == '\n')) {
            x->headersDone = true;  // empty line ends the headers
        }
        return len;
    }
};

namespace detail {

EventStream openStream(OpenHABClient::Impl& c, const std::string& path, const json& headers,
                       const json& params) {
    curlInitOnce();
    auto x = std::make_unique<EventStream::Impl>();
    x->url = buildUrl(c, path);
    std::string q = queryString(params);
    if (!q.empty()) x->url += (x->url.find('?') != std::string::npos ? "&" : "?") + q;

    // identity: a compressed stream would be flushed late
    x->headers = curl_slist_append(nullptr, "Accept: text/event-stream");
    x->headers = curl_slist_append(x->headers, "Cache-Control: no-cache");
    x->headers = authHeader(x->headers, c);
    if (headers.is_object())
        for (auto it = headers.begin(); it != headers.end(); ++it)
            if (it.value().is_string())
                x->headers = curl_slist_append(
                    x->headers, (it.key() + ": " + it.value().get<std::string>()).c_str());
    x->easy = curl_easy_init();
    curl_easy_setopt(x->easy, CURLOPT_URL, x->url.c_str());
    curl_easy_setopt(x->easy, CURLOPT_HTTPHEADER, x->headers);
    curl_easy_setopt(x->easy, CURLOPT_WRITEFUNCTION, EventStream::Impl::onBody);
    curl_easy_setopt(x->easy, CURLOPT_WRITEDATA, x.get());
    curl_easy_setopt(x->easy, CURLOPT_HEADERFUNCTION, EventStream::Impl::onHeader);
    curl_easy_setopt(x->easy, CURLOPT_HEADERDATA, x.get());
    curl_easy_setopt(x->easy, CURLOPT_CONNECTTIMEOUT_MS,
                     static_cast<long>(OpenHABClient::SSE_CONNECT_TIMEOUT * 1000));
    curl_easy_setopt(x->easy, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(x->easy, CURLOPT_TCP_KEEPALIVE, 1L);
    applyAuth(x->easy, c);
    x->multi = curl_multi_init();
    curl_multi_add_handle(x->multi, x->easy);
    x->running = true;

    // Like requests: wait for the response headers (there is no read timeout –
    // openHAB sends the headers of sitemap streams only with the first event).
    while (x->running && !x->headersDone && !x->interrupted) x->pump(200);
    if (x->status >= 400) {
        // read the error body, then report it like _raiseForStatus
        long long end = nowMs() + static_cast<long long>(c.timeout * 1000);
        while (x->running && nowMs() < end) x->pump(100);
        x->fail(httpErrorText(x->status, x->reason, x->url, x->in), x->status);
    } else if (!x->headersDone && !x->failed && !x->interrupted) {
        x->fail("connection closed before the response headers", 0);
    }
    return EventStream(std::move(x));
}

}  // namespace detail

EventStream::EventStream() = default;
EventStream::EventStream(std::unique_ptr<Impl> impl) : impl_(std::move(impl)) {}
EventStream::~EventStream() = default;
EventStream::EventStream(EventStream&&) noexcept = default;
EventStream& EventStream::operator=(EventStream&&) noexcept = default;

EventStream EventStream::failed(const std::string& message, int status) {
    auto x = std::make_unique<Impl>();
    x->fail(message.empty() ? "error" : message, status);
    return EventStream(std::move(x));
}

std::optional<std::string> EventStream::nextLine(int timeoutMs) {
    Impl* x = impl_.get();
    if (!x) return std::nullopt;
    long long end = timeoutMs < 0 ? -1 : nowMs() + timeoutMs;
    for (;;) {
        size_t nl = x->in.find('\n', x->pos);
        if (nl != std::string::npos) {
            std::string line = x->in.substr(x->pos, nl - x->pos);
            if (!line.empty() && line.back() == '\r') line.pop_back();
            x->pos = nl + 1;
            if (x->pos > 65536) {  // compact the buffer
                x->in.erase(0, x->pos);
                x->pos = 0;
            }
            return line;
        }
        if (x->interrupted) return std::nullopt;
        if (!x->running) {
            if (x->pos < x->in.size()) {  // last line without newline
                std::string line = x->in.substr(x->pos);
                x->pos = x->in.size();
                return line;
            }
            return std::nullopt;
        }
        long long left = end < 0 ? 200 : end - nowMs();
        if (left <= 0) return std::nullopt;
        x->pump(static_cast<int>(left > 200 ? 200 : left));
    }
}

std::optional<json> EventStream::parseData(const std::string& line) {
    if (line.compare(0, 5, "data:") != 0) return std::nullopt;
    json ev = json::parse(line.substr(5), nullptr, false);
    if (ev.is_discarded()) return std::nullopt;
    if (ev.is_object() && ev.contains("payload") && ev["payload"].is_string()) {
        json p = json::parse(ev["payload"].get<std::string>(), nullptr, false);
        if (!p.is_discarded()) ev["payload"] = std::move(p);
    }
    return ev;
}

std::optional<json> EventStream::nextEvent(int timeoutMs, bool includeAlive) {
    long long end = timeoutMs < 0 ? -1 : nowMs() + timeoutMs;
    for (;;) {
        int left = end < 0 ? -1 : static_cast<int>(end - nowMs());
        if (end >= 0 && left < 0) left = 0;
        auto line = nextLine(left);
        if (!line) return std::nullopt;
        auto ev = parseData(*line);
        if (!ev) continue;
        if ((ev->is_object() && ev->contains("topic")) || includeAlive) return ev;
    }
}

bool EventStream::isOpen() const {
    const Impl* x = impl_.get();
    return x && !x->failed && !x->interrupted && (x->running || x->pos < x->in.size());
}

bool EventStream::isError() const { return !impl_ || impl_->failed; }

std::string EventStream::error() const {
    if (!impl_) return "no stream";
    return impl_->failed ? impl_->error : std::string();
}

int EventStream::errorStatus() const { return impl_ ? impl_->errorStatus : 0; }

json EventStream::errorResult() const {
    if (!isError()) return nullptr;
    return json{{"error", error()}};
}

void EventStream::interrupt() noexcept {
    Impl* x = impl_.get();
    if (!x) return;
    x->interrupted = 1;
    if (x->multi) curl_multi_wakeup(x->multi);
}

void EventStream::close() { impl_.reset(); }

EventStream::iterator& EventStream::iterator::operator++() {
    if (!s_) return *this;
    auto e = s_->nextEvent(-1);
    if (e) cur_ = std::move(*e);
    else s_ = nullptr;
    return *this;
}

}  // namespace openhab
