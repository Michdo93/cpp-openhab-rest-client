/*
 * cpp-openhab-rest-client – client, results and Server-Sent Events.
 *
 * Every REST method of this library (API.hpp) returns an nlohmann::ordered_json value,
 * exactly like python-openhab-rest-client:
 *   - JSON responses as object or array,
 *   - text responses (e.g. an item state) as string,
 *   - errors as object {"error": "..."} and empty successes as {"message": "OK"}.
 * Methods that open an event stream return an openhab::EventStream.
 */
#pragma once

#include <nlohmann/json.hpp>

#include <atomic>
#include <cstddef>
#include <iterator>
#include <memory>
#include <optional>
#include <string>

// ── Export macros ─────────────────────────────────────────────────────────────
#if defined(_WIN32) || defined(__CYGWIN__)
#  ifdef OPENHAB_BUILDING_DLL
#    define OPENHAB_API __declspec(dllexport)
#  elif defined(OPENHAB_STATIC)
#    define OPENHAB_API
#  else
#    define OPENHAB_API __declspec(dllimport)
#  endif
#else
#  if defined(OPENHAB_BUILDING_DLL) && defined(__GNUC__) && __GNUC__ >= 4
#    define OPENHAB_API __attribute__((visibility("default")))
#  else
#    define OPENHAB_API
#  endif
#endif

namespace openhab {

// ordered_json keeps the order of the keys – like Python dicts and like openHAB sends them
using json = nlohmann::ordered_json;

inline constexpr const char* VERSION = "2.0.0";

class EventStream;

/** Optional arguments of the client (C++20: OpenHABClient c(url, {.token = t});). */
struct ClientOptions {
    std::optional<std::string> username;  ///< Basic Authentication (also myopenHAB)
    std::optional<std::string> password;
    std::optional<std::string> token;     ///< API token (Bearer) – takes precedence
    double timeout = 10.0;                ///< seconds for normal requests
    bool verify = true;                   ///< TLS certificate check
};

/**
 * Connection to openHAB – the counterpart of python-openhab-rest-client's OpenHABClient.
 *
 *   openhab::OpenHABClient client("http://127.0.0.1:8080", std::nullopt, std::nullopt, token);
 *   openhab::OpenHABClient client("http://127.0.0.1:8080", options);   // ClientOptions
 *
 * The constructor checks whether openHAB is reachable (isLoggedIn()). The client is
 * thread-safe: every request uses its own connection.
 */
class OPENHAB_API OpenHABClient {
public:
    static constexpr double DEFAULT_TIMEOUT = 10.0;
    static constexpr double SSE_CONNECT_TIMEOUT = 10.0;

    explicit OpenHABClient(const std::string& url,
                           const std::optional<std::string>& username = std::nullopt,
                           const std::optional<std::string>& password = std::nullopt,
                           const std::optional<std::string>& token = std::nullopt,
                           double timeout = DEFAULT_TIMEOUT, bool verify = true);
    OpenHABClient(const std::string& url, const ClientOptions& options);
    ~OpenHABClient();

    OpenHABClient(const OpenHABClient&) = delete;
    OpenHABClient& operator=(const OpenHABClient&) = delete;
    OpenHABClient(OpenHABClient&&) noexcept;
    OpenHABClient& operator=(OpenHABClient&&) noexcept;

    /** Repeats the reachability check of the constructor; returns isLoggedIn(). */
    bool login();
    /** true if openHAB was reachable and accepted the credentials. */
    bool isLoggedIn() const;
    /** true for myopenHAB. */
    bool isCloud() const;
    /** Base URL without trailing slash. */
    const std::string& url() const;
    /** Why the last login failed (empty if it worked). */
    const std::string& lastError() const;
    /** Timeout for normal requests in seconds. */
    double timeout() const;

    // ── Low-level requests (Python: client.get/post/put/delete) ──────────────
    // endpoint: "/items", "/rest/items" or a full URL. headers and params are JSON
    // objects (null = none); data is sent as text if it is a string, otherwise as JSON.
    // Returns the decoded JSON, the text as string, {"status": 200[, "location": ...]}
    // for empty bodies, or {"error": "..."} for HTTP and connection errors.
    json get(const std::string& endpoint, const json& headers = nullptr,
             const json& params = nullptr);
    json post(const std::string& endpoint, const json& headers = nullptr,
              const json& data = nullptr, const json& params = nullptr);
    json put(const std::string& endpoint, const json& headers = nullptr,
             const json& data = nullptr, const json& params = nullptr);
    json del(const std::string& endpoint, const json& headers = nullptr,
             const json& data = nullptr, const json& params = nullptr);

    /** Opens an event stream (Python: client.executeSSE). Check stream.isError(). */
    EventStream executeSSE(const std::string& url, const json& headers = nullptr,
                           const json& params = nullptr);

    struct Impl;
    Impl& impl() { return *impl_; }

private:
    std::unique_ptr<Impl> impl_;
};

// ── Results ───────────────────────────────────────────────────────────────────

/** true if result is an error object {"error": ...}. */
OPENHAB_API bool isError(const json& result);

/** The error message of an error object, otherwise an empty string. */
OPENHAB_API std::string errorMessage(const json& result);

/**
 * Walks a path through objects and arrays: "payload.value", "0.label", "members.2.name".
 * Returns nullptr (json null) if a part is missing.
 */
OPENHAB_API json at(const json& value, const std::string& path);

/** String at path, or fallback if it is missing or not a string. */
OPENHAB_API std::string str(const json& value, const std::string& path,
                            const std::string& fallback = "");

/** Number at path (numbers and numeric strings such as "21.5 °C"), or fallback. */
OPENHAB_API double num(const json& value, const std::string& path, double fallback = 0.0);

// ── Server-Sent Events ────────────────────────────────────────────────────────

/**
 * An open event stream – returned by the *Events classes and Events::getEvents().
 *
 *   auto stream = openhab::ItemEvents(client).ItemStateChangedEvent("Wohnzimmer_Licht");
 *   while (auto e = stream.nextEvent(5000)) std::cout << (*e)["payload"] << "\n";
 *   for (const json& e : stream) { ... }            // until the stream ends
 *
 * Move-only. interrupt() may be called from another thread or a signal handler.
 */
class OPENHAB_API EventStream {
public:
    struct Impl;

    EventStream();
    explicit EventStream(std::unique_ptr<Impl> impl);
    ~EventStream();
    EventStream(EventStream&&) noexcept;
    EventStream& operator=(EventStream&&) noexcept;
    EventStream(const EventStream&) = delete;
    EventStream& operator=(const EventStream&) = delete;

    /** A stream that only carries an error message. */
    static EventStream failed(const std::string& message, int status = 0);

    /**
     * Next event with decoded payload – Python: next(iterSSEEvents(stream)).
     * Waits at most timeoutMs milliseconds (-1 = no limit). Returns std::nullopt on
     * timeout, at the end of the stream, after interrupt() and on errors – isOpen()
     * tells whether more can come. ALIVE messages only with includeAlive = true.
     */
    std::optional<json> nextEvent(int timeoutMs = -1, bool includeAlive = false);

    /** Next raw line (Python: iterSSELines). */
    std::optional<std::string> nextLine(int timeoutMs = -1);

    /** Decodes one "data:" line (Python: parseSSEData); nullopt for other lines. */
    static std::optional<json> parseData(const std::string& line);

    /** true while the stream is connected and not interrupted. */
    bool isOpen() const;
    /** true if the stream could not be opened (or failed later). */
    bool isError() const;
    /** Error message (empty if there is none). */
    std::string error() const;
    /** HTTP status of the error (0 if it was no HTTP error). */
    int errorStatus() const;
    /** The error as result object {"error": ...}, or null. */
    json errorResult() const;

    /** Wakes up a waiting nextEvent()/nextLine() and ends the stream. Thread- and signal-safe. */
    void interrupt() noexcept;
    /** Closes the connection (the destructor does that, too). */
    void close();

    /** Input iterator over the events (no time limit, ALIVE skipped). */
    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = json;
        using difference_type = std::ptrdiff_t;
        using pointer = const json*;
        using reference = const json&;
        iterator() = default;
        explicit iterator(EventStream* s) : s_(s) { ++*this; }
        reference operator*() const { return cur_; }
        pointer operator->() const { return &cur_; }
        iterator& operator++();
        bool operator==(const iterator& o) const { return s_ == o.s_; }
        bool operator!=(const iterator& o) const { return s_ != o.s_; }

    private:
        EventStream* s_ = nullptr;
        json cur_;
    };
    iterator begin() { return iterator(this); }
    iterator end() { return iterator(); }

private:
    std::unique_ptr<Impl> impl_;
};

}  // namespace openhab
