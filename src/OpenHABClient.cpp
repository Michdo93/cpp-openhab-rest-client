// HTTP client – the C++ counterpart of python-openhab-rest-client/openhab/Client.py.
#include "internal.hpp"

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <mutex>

namespace openhab {
namespace detail {

void curlInitOnce() {
    static std::once_flag once;
    std::call_once(once, [] { curl_global_init(CURL_GLOBAL_DEFAULT); });
}

static bool startsWith(const std::string& s, const char* p) { return s.rfind(p, 0) == 0; }

static bool ieqPrefix(const char* s, size_t n, const char* p) {
    size_t k = std::strlen(p);
    if (n < k) return false;
    for (size_t i = 0; i < k; i++)
        if (std::tolower(static_cast<unsigned char>(s[i])) != std::tolower(static_cast<unsigned char>(p[i])))
            return false;
    return true;
}

std::string quote(const std::string& s, const std::string& safe) {
    static const char hex[] = "0123456789ABCDEF";
    std::string out;
    for (unsigned char ch : s) {
        if (std::isalnum(ch) || std::strchr("_.-~", ch) ||
            (ch < 128 && ch && safe.find(static_cast<char>(ch)) != std::string::npos)) {
            out += static_cast<char>(ch);
        } else {
            out += '%';
            out += hex[ch >> 4];
            out += hex[ch & 15];
        }
    }
    return out;
}

std::string buildUrl(const OpenHABClient::Impl& c, const std::string& resourcePath) {
    if (startsWith(resourcePath, "http://") || startsWith(resourcePath, "https://"))
        return resourcePath;
    std::string p = resourcePath;
    if (p.empty() || p[0] != '/') p = "/" + p;
    std::string out = c.url;
    if (!(p == "/rest" || startsWith(p, "/rest/") || startsWith(p, "/rest?"))) out += "/rest";
    // "#" is valid inside openHAB UIDs but would start a URL fragment
    size_t q = p.find('?');
    for (size_t i = 0; i < p.size() && (q == std::string::npos || i < q); i++)
        out += p[i] == '#' ? std::string("%23") : std::string(1, p[i]);
    if (q != std::string::npos) out += p.substr(q);
    return out;
}

static void addParam(std::string& b, const std::string& key, const json& v) {
    std::string text;
    if (v.is_null()) return;
    if (v.is_boolean()) text = v.get<bool>() ? "true" : "false";
    else if (v.is_number_integer()) text = std::to_string(v.get<long long>());
    else if (v.is_number()) text = v.dump();
    else if (v.is_string()) text = v.get<std::string>();
    else return;
    if (!b.empty()) b += '&';
    b += quote(key, "") + "=" + quote(text, "");
}

std::string queryString(const json& params) {
    std::string b;
    if (!params.is_object()) return b;
    for (auto it = params.begin(); it != params.end(); ++it) {
        if (it.value().is_array())
            for (const auto& e : it.value()) addParam(b, it.key(), e);
        else
            addParam(b, it.key(), it.value());
    }
    return b;
}

static std::string withQuery(std::string base, const json& params) {
    std::string q = queryString(params);
    if (q.empty()) return base;
    return base + (base.find('?') != std::string::npos ? "&" : "?") + q;
}

void applyAuth(CURL* h, const OpenHABClient::Impl& c) {
    if (!c.verify) {
        curl_easy_setopt(h, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(h, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    if (c.token.empty() && !c.username.empty() && !c.password.empty()) {
        curl_easy_setopt(h, CURLOPT_HTTPAUTH, static_cast<long>(CURLAUTH_BASIC));
        curl_easy_setopt(h, CURLOPT_USERNAME, c.username.c_str());
        curl_easy_setopt(h, CURLOPT_PASSWORD, c.password.c_str());
    }
    static const std::string agent = std::string("cpp-openhab-rest-client/") + VERSION;
    curl_easy_setopt(h, CURLOPT_USERAGENT, agent.c_str());
    curl_easy_setopt(h, CURLOPT_NOSIGNAL, 1L);
}

curl_slist* authHeader(curl_slist* l, const OpenHABClient::Impl& c) {
    if (!c.token.empty()) l = curl_slist_append(l, ("Authorization: Bearer " + c.token).c_str());
    return l;
}

static std::string trim(const std::string& s) {
    size_t a = 0, b = s.size();
    while (a < b && std::isspace(static_cast<unsigned char>(s[a]))) a++;
    while (b > a && std::isspace(static_cast<unsigned char>(s[b - 1]))) b--;
    return s.substr(a, b - a);
}

std::string httpErrorText(int status, const std::string& reason, const std::string& url,
                          const std::string& body) {
    std::string message;
    json j = json::parse(body, nullptr, false);
    if (!j.is_discarded()) {
        if (j.is_object() && j.contains("error")) {
            const json& e = j["error"];
            if (e.is_object()) message = e.value("message", "");
            else if (e.is_string()) message = e.get<std::string>();
        }
    } else {
        message = trim(body).substr(0, 200);
        message = trim(message);
    }
    std::string text = std::to_string(status) + (status < 500 ? " Client Error: " : " Server Error: ") +
                       reason + " for url: " + url;
    if (!message.empty()) text += " (" + message + ")";
    return text;
}

namespace {
struct ReplyBuf {
    std::string body, reason, contentType, location;
};

size_t bodyCb(char* p, size_t s, size_t n, void* u) {
    static_cast<ReplyBuf*>(u)->body.append(p, s * n);
    return s * n;
}

std::string headerValue(const char* line, size_t n) {
    const char* v = static_cast<const char*>(std::memchr(line, ':', n));
    if (!v) return "";
    return trim(std::string(v + 1, line + n));
}

size_t headerCb(char* line, size_t s, size_t n, void* u) {
    auto* r = static_cast<ReplyBuf*>(u);
    size_t len = s * n;
    if (len > 5 && std::strncmp(line, "HTTP/", 5) == 0) {
        // status line: HTTP/1.1 404 Not Found – a new response starts (redirects)
        r->contentType.clear();
        r->location.clear();
        r->reason.clear();
        std::string l = trim(std::string(line, len));
        size_t a = l.find(' ');
        size_t b = a == std::string::npos ? a : l.find(' ', a + 1);
        if (b != std::string::npos) r->reason = l.substr(b + 1);
    } else if (ieqPrefix(line, len, "content-type:")) {
        r->contentType = headerValue(line, len);
    } else if (ieqPrefix(line, len, "location:")) {
        r->location = headerValue(line, len);
    }
    return len;
}

size_t discardCb(char*, size_t s, size_t n, void*) { return s * n; }
}  // namespace

Reply request(OpenHABClient::Impl& c, const std::string& verb, const std::string& path,
              const json& headers, const json& data, const json& params) {
    curlInitOnce();
    std::string url = withQuery(buildUrl(c, path.empty() ? "/" : path), params);

    // body: strings as they are, everything else as JSON
    bool hasBody = !data.is_null();
    std::string body;
    bool bodyIsJson = false;
    if (hasBody) {
        if (data.is_string()) {
            body = data.get<std::string>();
            size_t i = body.find_first_not_of(" \t\r\n");
            bodyIsJson = i != std::string::npos && (body[i] == '{' || body[i] == '[');
        } else {
            body = data.dump();
            bodyIsJson = true;
        }
    }

    curl_slist* hl = authHeader(nullptr, c);
    bool hasCt = false;
    if (headers.is_object()) {
        for (auto it = headers.begin(); it != headers.end(); ++it) {
            if (!it.value().is_string()) continue;
            std::string k = it.key();
            if (k.size() == 12 && ieqPrefix(k.c_str(), k.size(), "content-type")) hasCt = true;
            hl = curl_slist_append(hl, (k + ": " + it.value().get<std::string>()).c_str());
        }
    }
    if (!body.empty() && !hasCt)
        hl = curl_slist_append(hl, bodyIsJson ? "Content-Type: application/json"
                                              : "Content-Type: text/plain");
    if (!hasCt && body.empty()) hl = curl_slist_append(hl, "Content-Type:");
    hl = curl_slist_append(hl, "Expect:");

    ReplyBuf r;
    char err[CURL_ERROR_SIZE] = "";
    CURL* h = curl_easy_init();
    curl_easy_setopt(h, CURLOPT_URL, url.c_str());
    curl_easy_setopt(h, CURLOPT_HTTPHEADER, hl);
    curl_easy_setopt(h, CURLOPT_WRITEFUNCTION, bodyCb);
    curl_easy_setopt(h, CURLOPT_WRITEDATA, &r);
    curl_easy_setopt(h, CURLOPT_HEADERFUNCTION, headerCb);
    curl_easy_setopt(h, CURLOPT_HEADERDATA, &r);
    curl_easy_setopt(h, CURLOPT_ERRORBUFFER, err);
    curl_easy_setopt(h, CURLOPT_TIMEOUT_MS, static_cast<long>(c.timeout * 1000));
    curl_easy_setopt(h, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(h, CURLOPT_ACCEPT_ENCODING, "");
    applyAuth(h, c);
    if (verb == "post") curl_easy_setopt(h, CURLOPT_POST, 1L);
    else if (verb == "put") curl_easy_setopt(h, CURLOPT_CUSTOMREQUEST, "PUT");
    else if (verb == "delete") curl_easy_setopt(h, CURLOPT_CUSTOMREQUEST, "DELETE");
    if (verb != "get") {
        curl_easy_setopt(h, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(h, CURLOPT_POSTFIELDSIZE, static_cast<long>(body.size()));
    }
    CURLcode rc = curl_easy_perform(h);
    long status = 0;
    char* eff = nullptr;
    curl_easy_getinfo(h, CURLINFO_RESPONSE_CODE, &status);
    curl_easy_getinfo(h, CURLINFO_EFFECTIVE_URL, &eff);
    std::string effUrl = eff ? eff : url;
    curl_easy_cleanup(h);
    curl_slist_free_all(hl);

    if (rc != CURLE_OK) throw RequestException(err[0] ? err : curl_easy_strerror(rc), 0);
    if (status >= 400)
        throw HTTPError(httpErrorText(static_cast<int>(status), r.reason, effUrl, r.body),
                        static_cast<int>(status));
    Reply out;
    if (trim(r.body).empty()) {
        out.value = json{{"status", status}};
        if (!r.location.empty()) out.value["location"] = r.location;
        out.isStatus = true;
        return out;
    }
    if (r.contentType.find("json") != std::string::npos) {
        out.value = json::parse(r.body, nullptr, false);
        if (!out.value.is_discarded()) return out;
    }
    out.value = r.body;
    return out;
}

static std::string reprNum(const json& v) {
    // nlohmann prints floats like Python's repr (shortest round trip, "21.0")
    return v.dump();
}

std::string pyStr(const json& v, bool top) {
    if (v.is_null()) return "None";
    if (v.is_boolean()) return v.get<bool>() ? "True" : "False";
    if (v.is_number()) return reprNum(v);
    if (v.is_string()) return top ? v.get<std::string>() : "'" + v.get<std::string>() + "'";
    bool obj = v.is_object();
    std::string b = obj ? "{" : "[";
    bool first = true;
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (!first) b += ", ";
        first = false;
        if (obj) b += "'" + it.key() + "': ";
        b += pyStr(it.value(), false);
    }
    return b + (obj ? "}" : "]");
}

}  // namespace detail

// ── OpenHABClient ─────────────────────────────────────────────────────────────

OpenHABClient::OpenHABClient(const std::string& url, const std::optional<std::string>& username,
                             const std::optional<std::string>& password,
                             const std::optional<std::string>& token, double timeout, bool verify)
    : impl_(std::make_unique<Impl>()) {
    detail::curlInitOnce();
    impl_->url = url;
    while (!impl_->url.empty() && impl_->url.back() == '/') impl_->url.pop_back();
    impl_->username = username.value_or("");
    impl_->password = password.value_or("");
    impl_->token = token.value_or("");
    impl_->timeout = timeout > 0 ? timeout : DEFAULT_TIMEOUT;
    impl_->verify = verify;
    login();
}

OpenHABClient::OpenHABClient(const std::string& url, const ClientOptions& o)
    : OpenHABClient(url, o.username, o.password, o.token, o.timeout, o.verify) {}

OpenHABClient::~OpenHABClient() = default;
OpenHABClient::OpenHABClient(OpenHABClient&&) noexcept = default;
OpenHABClient& OpenHABClient::operator=(OpenHABClient&&) noexcept = default;

bool OpenHABClient::login() {
    Impl& c = *impl_;
    c.isCloud = c.url == "https://myopenhab.org" || c.url == "https://home.myopenhab.org";
    c.isLoggedIn = false;
    c.lastError.clear();
    std::string url = c.url + "/rest/";
    CURL* h = curl_easy_init();
    curl_slist* hd = detail::authHeader(nullptr, c);
    char err[CURL_ERROR_SIZE] = "";
    curl_easy_setopt(h, CURLOPT_URL, url.c_str());
    curl_easy_setopt(h, CURLOPT_HTTPHEADER, hd);
    curl_easy_setopt(h, CURLOPT_WRITEFUNCTION, detail::discardCb);
    curl_easy_setopt(h, CURLOPT_TIMEOUT_MS, static_cast<long>(c.timeout * 1000));
    curl_easy_setopt(h, CURLOPT_ERRORBUFFER, err);
    curl_easy_setopt(h, CURLOPT_FOLLOWLOCATION, 1L);
    detail::applyAuth(h, c);
    CURLcode rc = curl_easy_perform(h);
    long status = 0;
    curl_easy_getinfo(h, CURLINFO_RESPONSE_CODE, &status);
    if (rc != CURLE_OK)
        c.lastError = std::string("Connection error occurred: ") + (err[0] ? err : curl_easy_strerror(rc));
    else if (status >= 400)
        c.lastError = "HTTP error occurred: " + std::to_string(status) + " for url: " + url;
    else
        c.isLoggedIn = true;
    curl_slist_free_all(hd);
    curl_easy_cleanup(h);
    return c.isLoggedIn;
}

bool OpenHABClient::isLoggedIn() const { return impl_->isLoggedIn; }
bool OpenHABClient::isCloud() const { return impl_->isCloud; }
const std::string& OpenHABClient::url() const { return impl_->url; }
const std::string& OpenHABClient::lastError() const { return impl_->lastError; }
double OpenHABClient::timeout() const { return impl_->timeout; }

static json lowLevel(OpenHABClient::Impl& c, const char* verb, const std::string& endpoint,
                     const json& headers, const json& data, const json& params) {
    try {
        return detail::request(c, verb, endpoint, headers, data, params).value;
    } catch (const detail::HTTPError& e) {
        return json{{"error", "HTTP error " + std::to_string(e.status) + ": " + e.what()}};
    } catch (const detail::RequestException& e) {
        return json{{"error", std::string("Request error: ") + e.what()}};
    }
}

json OpenHABClient::get(const std::string& e, const json& h, const json& p) {
    return lowLevel(*impl_, "get", e, h, nullptr, p);
}
json OpenHABClient::post(const std::string& e, const json& h, const json& d, const json& p) {
    return lowLevel(*impl_, "post", e, h, d, p);
}
json OpenHABClient::put(const std::string& e, const json& h, const json& d, const json& p) {
    return lowLevel(*impl_, "put", e, h, d, p);
}
json OpenHABClient::del(const std::string& e, const json& h, const json& d, const json& p) {
    return lowLevel(*impl_, "delete", e, h, d, p);
}

EventStream OpenHABClient::executeSSE(const std::string& url, const json& headers,
                                      const json& params) {
    return detail::openStream(*impl_, url, headers, params);
}

// ── Results ───────────────────────────────────────────────────────────────────

bool isError(const json& r) { return r.is_object() && r.contains("error"); }

std::string errorMessage(const json& r) {
    if (!isError(r)) return "";
    const json& e = r["error"];
    if (e.is_string()) return e.get<std::string>();
    if (e.is_object() && e.contains("message") && e["message"].is_string())
        return e["message"].get<std::string>();
    return "error";
}

json at(const json& v, const std::string& path) {
    const json* cur = &v;
    size_t pos = 0;
    while (pos <= path.size() && !path.empty()) {
        size_t dot = path.find('.', pos);
        std::string part = path.substr(pos, dot == std::string::npos ? std::string::npos : dot - pos);
        if (cur->is_array()) {
            char* end = nullptr;
            long i = std::strtol(part.c_str(), &end, 10);
            if (part.empty() || *end) return nullptr;
            if (i < 0) i += static_cast<long>(cur->size());
            if (i < 0 || static_cast<size_t>(i) >= cur->size()) return nullptr;
            cur = &(*cur)[static_cast<size_t>(i)];
        } else if (cur->is_object()) {
            auto it = cur->find(part);
            if (it == cur->end()) return nullptr;
            cur = &*it;
        } else {
            return nullptr;
        }
        if (dot == std::string::npos) break;
        pos = dot + 1;
    }
    return *cur;
}

std::string str(const json& v, const std::string& path, const std::string& fallback) {
    json x = at(v, path);
    return x.is_string() ? x.get<std::string>() : fallback;
}

double num(const json& v, const std::string& path, double fallback) {
    json x = at(v, path);
    if (x.is_number()) return x.get<double>();
    if (x.is_string()) {
        const std::string s = x.get<std::string>();
        char* end = nullptr;
        double d = std::strtod(s.c_str(), &end);
        if (end != s.c_str()) return d;
    }
    return fallback;
}

}  // namespace openhab
