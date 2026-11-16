// Unit tests with a small local HTTP server – no openHAB needed.
// POSIX only (Linux, macOS); on Windows the test reports "skipped".
#include <openhab/openhab.hpp>

#include <cstdio>
#include <iostream>
#include <string>

#ifdef _WIN32
int main() { std::puts("unit tests need POSIX sockets – skipped"); return 0; }
#else

#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <cstring>
#include <mutex>
#include <thread>
#include <vector>

using openhab::json;

static int failures = 0, checks = 0;
#define CHECK(cond, what)                                                          \
    do {                                                                           \
        checks++;                                                                  \
        if (!(cond)) {                                                             \
            failures++;                                                            \
            std::cout << "FAIL " << __FILE__ << ":" << __LINE__ << ": " << what << "\n"; \
        }                                                                          \
    } while (0)

// ── a tiny HTTP server ────────────────────────────────────────────────────────
struct Reply {
    std::string response;              // complete raw response
    std::vector<std::string> chunks;   // for streams: sent one after the other
    int chunkDelayMs = 0;
    int keepOpenMs = 0;                // keep the connection open after the chunks
};

static std::mutex mtx;
static Reply current;
static std::string lastRequest;
static int port, listenFd;

static void sleepMs(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

static void server() {
    for (;;) {
        int fd = accept(listenFd, nullptr, nullptr);
        if (fd < 0) return;
        std::string req;
        char buf[4096];
        for (;;) {
            ssize_t k = recv(fd, buf, sizeof buf, 0);
            if (k <= 0) break;
            req.append(buf, static_cast<size_t>(k));
            size_t end = req.find("\r\n\r\n");
            if (end == std::string::npos) continue;
            const char* cl = strcasestr(req.c_str(), "content-length:");
            size_t want = cl ? static_cast<size_t>(std::atoi(cl + 15)) : 0;
            if (req.size() >= end + 4 + want) break;
        }
        Reply r;
        {
            std::lock_guard<std::mutex> l(mtx);
            lastRequest = req;
            r = current;
        }
        if (!r.response.empty()) send(fd, r.response.data(), r.response.size(), MSG_NOSIGNAL);
        for (size_t i = 0; i < r.chunks.size(); i++) {
            if (i) sleepMs(r.chunkDelayMs);
            send(fd, r.chunks[i].data(), r.chunks[i].size(), MSG_NOSIGNAL);
        }
        if (r.keepOpenMs) sleepMs(r.keepOpenMs);
        close(fd);
    }
}

static void startServer() {
    sockaddr_in a{};
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    int one = 1;
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);
    bind(listenFd, reinterpret_cast<sockaddr*>(&a), sizeof a);
    socklen_t len = sizeof a;
    getsockname(listenFd, reinterpret_cast<sockaddr*>(&a), &len);
    port = ntohs(a.sin_port);
    listen(listenFd, 8);
    std::thread(server).detach();
}

static void respond(const std::string& raw) {
    std::lock_guard<std::mutex> l(mtx);
    current = Reply{};
    current.response = raw;
}

static bool has(const std::string& text) {
    std::lock_guard<std::mutex> l(mtx);
    return lastRequest.find(text) != std::string::npos;
}
static std::string req() {
    std::lock_guard<std::mutex> l(mtx);
    return lastRequest.substr(0, 300);
}

static long long nowMs() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

static const char* OK200 = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";

// ── tests ─────────────────────────────────────────────────────────────────────

static void testRequests(openhab::OpenHABClient& c) {
    openhab::Items items(c);
    respond(OK200);
    json r = items.sendCommand("Wohnzimmer_Licht", "ON");
    CHECK(r == json({{"message", "OK"}}), "sendCommand result " << r);
    CHECK(has("POST /rest/items/Wohnzimmer_Licht HTTP/1.1"), "request line: " << req());
    CHECK(has("Authorization: Bearer oh.test.123"), "token header missing");
    CHECK(has("Content-Type: text/plain"), "content type of a command");
    CHECK(has("\r\n\r\nON"), "command body");

    respond("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 27\r\n"
            "Connection: close\r\n\r\n[{\"name\":\"A\",\"state\":\"ON\"}]");
    openhab::Items::GetItemsArgs a;
    a.tags = "Light";
    a.fields = "name,state";
    r = items.getItems(a);
    CHECK(r.is_array() && openhab::str(r, "0.state") == "ON", "getItems " << r);
    CHECK(has("GET /rest/items?tags=Light&metadata=.%2A&recursive=false&fields=name%2Cstate"
              "&staticDataOnly=false HTTP/1.1"), "query: " << req());

    // positional optional arguments give the same request
    respond("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 2\r\n"
            "Connection: close\r\n\r\n[]");
    r = items.getItems(std::nullopt, "Light", ".*", false, "name,state");
    CHECK(has("GET /rest/items?tags=Light&metadata=.%2A&recursive=false&fields=name%2Cstate"
              "&staticDataOnly=false HTTP/1.1"), "positional: " << req());

    respond("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 8\r\n"
            "Connection: close\r\n\r\n21.5 \xc2\xb0" "C");
    r = items.getItemState("Temp");
    CHECK(r.is_string() && r.get<std::string>() == "21.5 \xc2\xb0" "C", "state " << r);

    // "#" in a channel UID must not start a URL fragment
    respond(OK200);
    r = openhab::Links(c).unlinkItemFromChannel("Licht", "astro:sun:home:rise#start");
    CHECK(has("DELETE /rest/links/Licht/astro%3Asun%3Ahome%3Arise%23start"), "link url: " << req());

    // dict bodies are sent as JSON
    respond(OK200);
    r = items.addOrUpdateItem("X", json{{"type", "Switch"}, {"name", "X"}});
    CHECK(has("PUT /rest/items/X") && has("Content-Type: application/json") &&
              has("{\"type\":\"Switch\",\"name\":\"X\"}"),
          "addOrUpdateItem: " << req());

    // persistence: the state goes into the query, not into the body
    respond(OK200);
    r = openhab::Persistence(c).storeItemData("T", "2026-11-06T10:00:00.000Z", "19.5", "inmemory");
    CHECK(has("PUT /rest/persistence/items/T?serviceId=inmemory&time=2026-11-06T10%3A00%3A00.000Z"
              "&state=19.5 "),
          "storeItemData: " << req());

    // low-level request
    respond("HTTP/1.1 201 Created\r\nLocation: /rest/x\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
    r = c.post("/x", nullptr, "text");
    CHECK(r == json({{"status", 201}, {"location", "/rest/x"}}), "status response " << r);
}

static void testErrors(openhab::OpenHABClient& c) {
    respond("HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\nContent-Length: 62\r\n"
            "Connection: close\r\n\r\n{\"error\":{\"message\":\"Item X does not exist!\",\"http-code\":404}}");
    json r = openhab::Items(c).getItem("X");
    CHECK(openhab::isError(r) && openhab::errorMessage(r) == "Item not found.", "404 " << r);

    respond("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 4\r\nConnection: close\r\n\r\nboom");
    r = openhab::UUID(c).getUUID();
    std::string e = openhab::errorMessage(r);
    CHECK(e.find("HTTP error 500: 500 Server Error: Internal Server Error for url: ") == 0 &&
              e.find("(boom)") != std::string::npos,
          "500 " << r);

    openhab::ClientOptions o;
    o.timeout = 2;
    openhab::OpenHABClient dead("http://127.0.0.1:1", o);
    CHECK(!dead.isLoggedIn() && !dead.lastError().empty(), "login check");
    r = openhab::Items(dead).getItems();
    CHECK(openhab::errorMessage(r).rfind("Request error: ", 0) == 0, "unreachable " << r);
}

static void testJson() {
    json v = json::parse(R"({"payload":{"value":"ON","n":"21.5 °C"},"list":[1,{"a":"b"}]})");
    CHECK(openhab::str(v, "payload.value") == "ON", "path");
    CHECK(openhab::num(v, "payload.n") == 21.5, "number from string");
    CHECK(openhab::str(v, "list.1.a") == "b", "array index");
    CHECK(!openhab::at(v, "list.-1.a").is_null(), "negative index");
    CHECK(openhab::at(v, "nope.x").is_null(), "missing part");
    CHECK(!openhab::isError(v), "not an error");

    auto e = openhab::EventStream::parseData(
        R"(data: {"topic":"openhab/items/A/statechanged","payload":"{\"value\":\"OFF\"}","type":"ItemStateChangedEvent"})");
    CHECK(e && openhab::str(*e, "payload.value") == "OFF", "parseSSEData");
    CHECK(!openhab::EventStream::parseData("event: message"), "non-data line");
}

static const char* SSE_HEAD =
    "HTTP/1.1 200 OK\r\nContent-Type: text/event-stream\r\nConnection: close\r\n\r\n";

static void testSse(openhab::OpenHABClient& c) {
    {
        std::lock_guard<std::mutex> l(mtx);
        current = Reply{};
        current.chunks = {std::string(SSE_HEAD) + "event: message\ndata: {\"type\":\"ALIVE\",\"interval\":10}\n\n",
                          // an event split in the middle of a line
                          "event: message\ndata: {\"topic\":\"openhab/items/A/statechanged\",\"pay",
                          "load\":\"{\\\"value\\\":\\\"ON\\\"}\",\"type\":\"ItemStateChangedEvent\"}\n\n"};
        current.chunkDelayMs = 150;
        current.keepOpenMs = 3000;
    }
    openhab::EventStream s = openhab::ItemEvents(c).ItemStateChangedEvent("A");
    CHECK(!s.isError(), "stream error " << s.error());
    CHECK(has("GET /rest/events?topics=openhab%2Fitems%2FA%2Fstatechanged") &&
              has("Accept: text/event-stream"),
          "stream request: " << req());
    auto ev = s.nextEvent(2000);
    CHECK(ev && openhab::str(*ev, "payload.value") == "ON", "event");
    long long t0 = nowMs();
    ev = s.nextEvent(300);
    CHECK(!ev && nowMs() - t0 < 900 && s.isOpen(), "timeout");
    std::thread t([&] { sleepMs(300); s.interrupt(); });
    t0 = nowMs();
    ev = s.nextEvent(-1);
    CHECK(!ev && nowMs() - t0 < 1500 && !s.isOpen(), "interrupt took " << nowMs() - t0 << " ms");
    t.join();
    s.close();

    // ALIVE only on request; range-for over the events
    {
        std::lock_guard<std::mutex> l(mtx);
        current = Reply{};
        current.chunks = {std::string(SSE_HEAD) + "data: {\"type\":\"ALIVE\",\"interval\":10}\n\n" +
                          "data: {\"topic\":\"t/1\",\"payload\":\"1\"}\n\n" +
                          "data: {\"topic\":\"t/2\",\"payload\":\"2\"}\n\n"};
    }
    s = openhab::Events(c).getEvents();
    ev = s.nextEvent(2000, true);
    CHECK(ev && openhab::str(*ev, "type") == "ALIVE", "alive");
    int n = 0;
    for (const json& e : s) n += e["payload"].get<int>();
    CHECK(n == 3, "range-for sum " << n);

    // HTTP error of a stream: message of the Python library
    respond("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
    s = openhab::Events(c).getEvents("bad topic");
    CHECK(s.isError() && s.error() == "Topic is empty or contains invalid characters.",
          "stream error: " << s.error());
    CHECK(!s.nextEvent(100), "no events from a failed stream");
    CHECK(s.errorResult() == json({{"error", "Topic is empty or contains invalid characters."}}),
          "errorResult");
}

int main() {
    startServer();
    std::string url = "http://127.0.0.1:" + std::to_string(port) + "/";
    respond(OK200);
    openhab::OpenHABClient c(url, std::nullopt, std::nullopt, "oh.test.123", 5);
    CHECK(c.isLoggedIn(), "login");
    CHECK(has("GET /rest/ HTTP/1.1"), "login request: " << req());
    CHECK(c.url() + "/" == url, "trailing slash removed");

    openhab::OpenHABClient basic(url, "user", "pass");
    CHECK(has("Authorization: Basic dXNlcjpwYXNz"), "basic auth");

    testRequests(c);
    testErrors(c);
    testJson();
    testSse(c);
    std::cout << checks << " checks, " << failures << " failed\n";
    return failures ? 1 : 0;
}
#endif
