// Integration tests against a real openHAB (OPENHAB_URL, OPENHAB_TOKEN).
// Without these variables the test is skipped (exit code 77).
// It creates and deletes the item CppTest_Switch; everything else is only read.
#include <openhab/openhab.hpp>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

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

int main() {
    const char* url = std::getenv("OPENHAB_URL");
    const char* token = std::getenv("OPENHAB_TOKEN");
    if (!url || !*url || !token || !*token) {
        std::cout << "OPENHAB_URL/OPENHAB_TOKEN not set – skipped\n";
        return 77;
    }
    openhab::OpenHABClient c(url, std::nullopt, std::nullopt, std::string(token));
    CHECK(c.isLoggedIn(), "login: " << c.lastError());

    json r = openhab::Systeminfo(c).getSystemInfo();
    CHECK(!openhab::str(r, "systemInfo.osName").empty(), "systeminfo " << r);

    // create (a freshly started openHAB may need a moment for the item registry)
    openhab::Items items(c);
    json item = {{"type", "Switch"}, {"name", "CppTest_Switch"}, {"label", "C++-Test"},
                 {"tags", {"Switch"}}};
    for (int i = 0; i < 30; i++) {
        r = items.addOrUpdateItem("CppTest_Switch", item);
        if (!openhab::isError(r)) break;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    CHECK(!openhab::isError(r), "create " << r);

    // command, state, events
    items.postUpdate("CppTest_Switch", "OFF");
    openhab::EventStream s = openhab::ItemEvents(c).ItemStateChangedEvent("CppTest_Switch");
    CHECK(!s.isError(), "stream " << s.error());
    r = items.sendCommand("CppTest_Switch", "ON");
    CHECK(r == json({{"message", "OK"}}), "command " << r);
    auto ev = s.nextEvent(5000);
    CHECK(ev && openhab::str(*ev, "payload.value") == "ON", "event " << (ev ? *ev : json()));
    s.close();

    r = items.getItemState("CppTest_Switch");
    CHECK(r == "ON", "state " << r);

    r = items.sendCommand("CppTest_Switch", "HALB");
    CHECK(openhab::isError(r), "invalid command " << r);

    openhab::Items::GetItemsArgs a;
    a.tags = "Switch";
    a.fields = "name";
    r = items.getItems(a);
    bool found = false;
    for (const json& e : r) found |= openhab::str(e, "name") == "CppTest_Switch";
    CHECK(found, "getItems with tag");

    r = items.deleteItem("CppTest_Switch");
    CHECK(r == json({{"message", "OK"}}), "delete " << r);
    r = items.getItem("CppTest_Switch");
    CHECK(openhab::errorMessage(r) == "Item not found.", "gone " << r);

    // stream without events: ALIVE messages keep it open (long run: OPENHAB_LONG_SSE=seconds)
    int seconds = std::getenv("OPENHAB_LONG_SSE") ? std::atoi(std::getenv("OPENHAB_LONG_SSE")) : 12;
    s = openhab::ItemEvents(c).ItemStateChangedEvent("Gibts_nicht_Item");
    int alive = 0;
    for (int i = 0; i < seconds; i++)
        if (s.nextEvent(1000, true)) alive++;
    CHECK(s.isOpen() && alive >= 1, "stream alive after " << seconds << " s (" << alive << " ALIVE)");

    std::cout << checks << " checks, " << failures << " failed\n";
    return failures ? 1 : 0;
}
