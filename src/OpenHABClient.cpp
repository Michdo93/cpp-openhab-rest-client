#include "openhab/OpenHABClient.h"

#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <cstring>
#include <algorithm>

namespace openhab {

// ── CURL write callback ────────────────────────────────────────────────────────

static size_t curlWriteCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* buf = static_cast<std::string*>(userdata);
    buf->append(ptr, size * nmemb);
    return size * nmemb;
}

static size_t curlHeaderCallback(char* buffer, size_t size, size_t nitems, void* userdata) {
    auto* headers = static_cast<std::map<std::string,std::string>*>(userdata);
    std::string line(buffer, size * nitems);
    auto pos = line.find(':');
    if (pos != std::string::npos) {
        std::string key   = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        // trim
        while (!key.empty()   && std::isspace((unsigned char)key.back()))   key.pop_back();
        while (!value.empty() && std::isspace((unsigned char)value.front())) value.erase(value.begin());
        while (!value.empty() && std::isspace((unsigned char)value.back()))  value.pop_back();
        // lowercase key
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        (*headers)[key] = value;
    }
    return size * nitems;
}

// ── URL helpers ────────────────────────────────────────────────────────────────

static std::string urlEncode(CURL* curl, const std::string& s) {
    char* enc = curl_easy_escape(curl, s.c_str(), static_cast<int>(s.size()));
    std::string result(enc ? enc : s);
    if (enc) curl_free(enc);
    return result;
}

// ── OpenHABClient ──────────────────────────────────────────────────────────────

OpenHABClient::OpenHABClient(const std::string& url,
                             const std::string& username,
                             const std::string& password,
                             const std::string& token)
    : baseUrl_(url), username_(username), password_(password), token_(token)
{
    // Strip trailing slash
    while (!baseUrl_.empty() && baseUrl_.back() == '/')
        baseUrl_.pop_back();

    curl_global_init(CURL_GLOBAL_DEFAULT);
    login();
}

void OpenHABClient::login() {
    isCloud_ = (baseUrl_.find("myopenhab.org") != std::string::npos);
    if (isCloud_) {
        // myopenhab.org does not accept Basic Auth on /rest directly.
        // Validation happens on the first real API call.
        isLoggedIn_ = true;
        return;
    }
    try {
        auto resp = get("/rest");
        isLoggedIn_ = (resp.statusCode >= 200 && resp.statusCode < 300);
    } catch (...) {
        isLoggedIn_ = false;
    }
}

std::string OpenHABClient::authHeader() const {
    if (!token_.empty()) {
        return "Bearer " + token_;
    }
    if (!username_.empty() && !password_.empty()) {
        // Base64 encode username:password
        const std::string creds = username_ + ":" + password_;
        // Simple Base64 implementation
        const std::string chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string encoded;
        int val = 0, bits = -6;
        for (unsigned char c : creds) {
            val = (val << 8) + c;
            bits += 8;
            while (bits >= 0) {
                encoded += chars[(val >> bits) & 0x3F];
                bits -= 6;
            }
        }
        if (bits > -6) encoded += chars[((val << 8) >> (bits + 8)) & 0x3F];
        while (encoded.size() % 4) encoded += '=';
        return "Basic " + encoded;
    }
    return "";
}

std::string OpenHABClient::buildUrl(const std::string& endpoint,
                                    const Params& params) const {
    std::string path = endpoint;
    if (path.empty() || path[0] != '/') path = "/" + path;
    if (path.substr(0, 5) != "/rest") path = "/rest" + path;

    std::string url = baseUrl_ + path;

    if (!params.empty()) {
        CURL* curl = curl_easy_init();
        url += "?";
        bool first = true;
        for (const auto& [k, v] : params) {
            if (v.empty()) continue;
            if (!first) url += "&";
            url += urlEncode(curl, k) + "=" + urlEncode(curl, v);
            first = false;
        }
        curl_easy_cleanup(curl);
    }
    return url;
}

HttpResponse OpenHABClient::execute(const std::string& method,
                                    const std::string& endpoint,
                                    const Headers& headers,
                                    const std::string& body,
                                    const Params& params) const {
    CURL* curl = curl_easy_init();
    if (!curl) throw OpenHABException("curl_easy_init failed");

    std::string responseBody;
    std::map<std::string, std::string> responseHeaders;

    curl_easy_setopt(curl, CURLOPT_URL,            buildUrl(endpoint, params).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  curlWriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,      &responseBody);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, curlHeaderCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA,     &responseHeaders);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,        10L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 8L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L); // don't follow — we want Location header
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // allow self-signed certs

    // HTTP method
    if      (method == "POST")   curl_easy_setopt(curl, CURLOPT_POST,          1L);
    else if (method == "PUT")    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    else if (method == "DELETE") curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    // GET is default

    // Request body
    if (!body.empty()) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,    body.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)body.size());
    } else if (method == "POST" || method == "PUT") {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0L);
    }

    // Headers
    struct curl_slist* curlHeaders = nullptr;

    auto auth = authHeader();
    if (!auth.empty()) {
        curlHeaders = curl_slist_append(curlHeaders,
            ("Authorization: " + auth).c_str());
    }

    for (const auto& [k, v] : headers) {
        curlHeaders = curl_slist_append(curlHeaders, (k + ": " + v).c_str());
    }

    if (curlHeaders)
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);

    CURLcode res = curl_easy_perform(curl);

    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

    curl_slist_free_all(curlHeaders);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
        throw OpenHABException(std::string("curl error: ") + curl_easy_strerror(res));

    HttpResponse response;
    response.statusCode  = static_cast<int>(httpCode);
    response.body        = responseBody;
    response.contentType = responseHeaders.count("content-type")
                           ? responseHeaders.at("content-type") : "";
    response.location    = responseHeaders.count("location")
                           ? responseHeaders.at("location") : "";

    if (!response.location.empty()) return response;

    if (response.statusCode >= 400) {
        throw OpenHABException(
            "HTTP " + std::to_string(response.statusCode) + ": " + responseBody,
            response.statusCode);
    }

    return response;
}

HttpResponse OpenHABClient::get(const std::string& ep,
                                const Headers& h, const Params& p) const {
    return execute("GET",    ep, h, "", p);
}
HttpResponse OpenHABClient::post(const std::string& ep,
                                 const Headers& h, const std::string& b,
                                 const Params& p) const {
    return execute("POST",   ep, h, b,  p);
}
HttpResponse OpenHABClient::put(const std::string& ep,
                                const Headers& h, const std::string& b,
                                const Params& p) const {
    return execute("PUT",    ep, h, b,  p);
}
HttpResponse OpenHABClient::del(const std::string& ep,
                                const Headers& h, const std::string& b,
                                const Params& p) const {
    return execute("DELETE", ep, h, b,  p);
}

SSEConnection OpenHABClient::sse(const std::string& url) const {
    return SSEConnection(url, authHeader());
}

// ── SSEConnection ──────────────────────────────────────────────────────────────

struct SSECallbackData {
    std::function<bool(const std::string&)> callback;
    std::string buffer;
    std::atomic<bool>* cancelled;
};

size_t SSEConnection::writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* data = static_cast<SSECallbackData*>(userdata);
    if (data->cancelled->load()) return 0; // abort

    data->buffer.append(ptr, size * nmemb);

    // Process complete lines
    size_t pos;
    while ((pos = data->buffer.find('\n')) != std::string::npos) {
        std::string line = data->buffer.substr(0, pos);
        data->buffer.erase(0, pos + 1);

        // Strip \r
        if (!line.empty() && line.back() == '\r') line.pop_back();

        if (line.substr(0, 6) == "data: ") {
            std::string payload = line.substr(6);
            if (!payload.empty()) {
                bool cont = data->callback(payload);
                if (!cont) {
                    data->cancelled->store(true);
                    return 0; // signal curl to abort
                }
            }
        }
    }
    return size * nmemb;
}

SSEConnection::SSEConnection(const std::string& url,
                             const std::string& authHeader)
    : url_(url), authHeader_(authHeader) {}

SSEConnection::~SSEConnection() {
    cancelled_.store(true);
}

void SSEConnection::cancel() {
    cancelled_.store(true);
}

void SSEConnection::forEach(std::function<bool(const std::string&)> callback) {
    cancelled_.store(false);

    CURL* curl = curl_easy_init();
    if (!curl) throw OpenHABException("curl_easy_init failed for SSE");

    SSECallbackData data;
    data.callback  = std::move(callback);
    data.cancelled = &cancelled_;

    curl_easy_setopt(curl, CURLOPT_URL,           url_.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &data);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,       0L);      // no timeout for SSE
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 8L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Accept: text/event-stream");
    headers = curl_slist_append(headers, "Cache-Control: no-cache");
    if (!authHeader_.empty())
        headers = curl_slist_append(headers, ("Authorization: " + authHeader_).c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_perform(curl); // blocks until stream ends or callback returns false

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}

} // namespace openhab