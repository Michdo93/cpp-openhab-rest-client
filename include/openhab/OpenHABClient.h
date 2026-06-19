#pragma once

#include <string>
#include <map>
#include <functional>
#include <stdexcept>
#include <thread>
#include <atomic>
#include <nlohmann/json.hpp>

namespace openhab {

using json = nlohmann::json;
using Headers = std::map<std::string, std::string>;
using Params  = std::map<std::string, std::string>;

// ── Exception ─────────────────────────────────────────────────────────────────

class OpenHABException : public std::runtime_error {
public:
    explicit OpenHABException(const std::string& msg, int statusCode = -1)
        : std::runtime_error(msg), statusCode_(statusCode) {}
    int statusCode() const noexcept { return statusCode_; }
private:
    int statusCode_;
};

// ── HTTP response ─────────────────────────────────────────────────────────────

struct HttpResponse {
    int         statusCode{0};
    std::string body;
    std::string contentType;
    std::string location;

    bool isJson()  const { return contentType.find("application/json") != std::string::npos; }
    bool isEmpty() const { return body.empty() || body.find_first_not_of(" \t\r\n") == std::string::npos; }

    json toJson() const {
        if (isEmpty()) return json{{"status", statusCode}};
        try { return json::parse(body); }
        catch (...) { return json(body); }
    }
};

// ── SSEConnection ─────────────────────────────────────────────────────────────

/**
 * Wraps an active Server-Sent Events stream.
 * Iterate with the forEach callback or call nextEvent() in a loop.
 *
 *   auto sse = itemEvents.ItemStateChangedEvent("testSwitch");
 *   sse.forEach([](const std::string& data) {
 *       std::cout << data << std::endl;
 *       return true;   // false = stop
 *   });
 */
class SSEConnection {
public:
    explicit SSEConnection(const std::string& url,
                           const std::string& authHeader);
    ~SSEConnection();

    SSEConnection(const SSEConnection&)            = delete;
    SSEConnection& operator=(const SSEConnection&) = delete;
    SSEConnection(SSEConnection&&)                 = default;

    /**
     * Blocking: calls callback for each event payload.
     * Callback receives the raw data string (after "data: ").
     * Return true to continue, false to stop.
     */
    void forEach(std::function<bool(const std::string&)> callback);

    /** Cancel the stream (safe to call from another thread). */
    void cancel();

private:
    std::string url_;
    std::string authHeader_;
    std::atomic<bool> cancelled_{false};

    static size_t writeCallback(char* ptr, size_t size,
                                size_t nmemb, void* userdata);
};

// ── OpenHABClient ─────────────────────────────────────────────────────────────

/**
 * Core HTTP client for the openHAB REST API.
 *
 * Uses libcurl for HTTP and nlohmann/json for JSON parsing.
 * Mirrors python-openhab-rest-client: same class names, same method names.
 *
 *   // Basic Auth
 *   openhab::OpenHABClient client("http://127.0.0.1:8080", "openhab", "habopen");
 *
 *   // Token Auth
 *   openhab::OpenHABClient client("http://127.0.0.1:8080", "", "", "oh.openhab.xxx");
 */
class OpenHABClient {
public:
    OpenHABClient(const std::string& url,
                  const std::string& username = "",
                  const std::string& password = "",
                  const std::string& token    = "");
    ~OpenHABClient() = default;

    // Non-copyable, movable
    OpenHABClient(const OpenHABClient&)            = delete;
    OpenHABClient& operator=(const OpenHABClient&) = delete;
    OpenHABClient(OpenHABClient&&)                 = default;

    // ── Getters ───────────────────────────────────────────────────────────────
    const std::string& baseUrl()    const { return baseUrl_; }
    const std::string& username()   const { return username_; }
    bool               isCloud()    const { return isCloud_; }
    bool               isLoggedIn() const { return isLoggedIn_; }

    // ── HTTP methods ──────────────────────────────────────────────────────────
    HttpResponse get   (const std::string& endpoint,
                        const Headers& headers = {},
                        const Params&  params  = {}) const;

    HttpResponse post  (const std::string& endpoint,
                        const Headers& headers = {},
                        const std::string& body = "",
                        const Params& params    = {}) const;

    HttpResponse put   (const std::string& endpoint,
                        const Headers& headers = {},
                        const std::string& body = "",
                        const Params& params    = {}) const;

    HttpResponse del   (const std::string& endpoint,
                        const Headers& headers = {},
                        const std::string& body = "",
                        const Params& params    = {}) const;

    // ── SSE ───────────────────────────────────────────────────────────────────
    SSEConnection sse(const std::string& url) const;

    // ── Helpers ───────────────────────────────────────────────────────────────
    std::string buildUrl(const std::string& endpoint,
                         const Params& params = {}) const;

    std::string authHeader() const;

private:
    void login();
    HttpResponse execute(const std::string& method,
                         const std::string& endpoint,
                         const Headers& headers,
                         const std::string& body,
                         const Params& params) const;

    std::string baseUrl_;
    std::string username_;
    std::string password_;
    std::string token_;
    bool        isCloud_{false};
    bool        isLoggedIn_{false};
};

} // namespace openhab
