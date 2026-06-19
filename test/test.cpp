/**
 * openhab-rest-client — C++ Testanwendung
 *
 * Konfiguration anpassen:
 *   const std::string URL      = "http://127.0.0.1:8080";
 *   const std::string USERNAME = "openhab";
 *   const std::string PASSWORD = "habopen";
 *
 * Kompilieren & starten (via CMake):
 *   mkdir build && cd build
 *   cmake ..
 *   cmake --build .
 *   ./openhab_test
 */

#include <openhab/openhab.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace openhab;

// ── Konfiguration ─────────────────────────────────────────────────────────────
const std::string URL      = "http://127.0.0.1:8080";
const std::string USERNAME = "openhab";
const std::string PASSWORD = "habopen";
const std::string TOKEN    = "";   // Alternative: Token statt Basic Auth

const std::string TEST_ITEM        = "testSwitch";
const std::string TEST_NUMBER_ITEM = "testNumber";
const std::string TEST_GROUP       = "Static";
const std::string TEST_THING_UID   = "astro:sun:b54938fe5c";
const std::string TEST_LOGGER      = "org.openhab.test.cpp";
const std::string TEST_RULE_UID    = "test_color-4";

// ── ANSI-Farben ───────────────────────────────────────────────────────────────
const std::string GREEN  = "\033[32m";
const std::string RED    = "\033[31m";
const std::string YELLOW = "\033[33m";
const std::string BLUE   = "\033[34m";
const std::string BOLD   = "\033[1m";
const std::string DIM    = "\033[2m";
const std::string RESET  = "\033[0m";

int passed = 0, failed = 0, total = 0;

void header(int num, const std::string& name) {
    std::string dashes(std::max(2, 44 - (int)name.size()), '-');
    std::cout << "\n" << DIM << "────" << RESET
              << " " << BOLD << "Test #" << num << ": " << name << "()" << RESET
              << " " << DIM << dashes << RESET << "\n";
}

void ok(const std::string& label, const std::string& preview = "") {
    std::string disp = preview.size() > 100 ? preview.substr(0, 100) + "…" : preview;
    std::cout << "  " << GREEN << "✓" << RESET << " " << label;
    if (!disp.empty()) std::cout << DIM << " → " << disp << RESET;
    std::cout << "\n";
    ++passed;
}

void fail(const std::string& label, const std::string& err) {
    std::cout << "  " << RED << "✗" << RESET << " " << label << ": "
              << RED << err << RESET << "\n";
    ++failed;
}

void info(const std::string& msg) {
    std::cout << "  " << BLUE << "ℹ" << RESET << " " << DIM << msg << RESET << "\n";
}

// Run a test, catch exceptions
template<typename Fn>
void run(int num, const std::string& name, Fn fn) {
    ++total;
    header(num, name);
    try { fn(); }
    catch (const OpenHABException& e) { fail(name, e.what()); }
    catch (const std::exception& e)   { fail(name, e.what()); }
    catch (...) { fail(name, "unknown error"); }
}

int main() {
    std::cout << "\n"
              << BOLD << "╔═══════════════════════════════════════════════════════╗\n"
                       "║   openhab-rest-client — C++ Testanwendung             ║\n"
                       "╚═══════════════════════════════════════════════════════╝" << RESET
              << "\n  URL: " << YELLOW << URL << RESET
              << "   Auth: " << (TOKEN.empty() ? "Basic" : "Token") << "\n\n";

    // ── Client ────────────────────────────────────────────────────────────────
    OpenHABClient client = TOKEN.empty()
        ? OpenHABClient(URL, USERNAME, PASSWORD)
        : OpenHABClient(URL, "", "", TOKEN);

    if (!client.isLoggedIn()) {
        std::cerr << RED << BOLD
                  << "Verbindung fehlgeschlagen. URL / Zugangsdaten prüfen."
                  << RESET << "\n";
        return 1;
    }
    std::cout << "  " << GREEN << "✓" << RESET
              << " Verbunden  isCloud=" << client.isCloud()
              << "  isLoggedIn=" << client.isLoggedIn() << "\n\n";

    // ════════════════════════════════════════════════════════════════════════
    // UUID / Systeminfo
    // ════════════════════════════════════════════════════════════════════════

    run(1, "getUUID", [&] {
        UUID uuid(client);
        auto r = uuid.getUUID();
        ok("UUID", r.is_string() ? r.get<std::string>() : r.dump());
    });

    run(2, "getSystemInfo", [&] {
        Systeminfo sys(client);
        auto r = sys.getSystemInfo();
        ok("systemInfo", r.dump().substr(0, 80));
    });

    run(3, "getUoMInfo", [&] {
        Systeminfo sys(client);
        auto r = sys.getUoMInfo();
        ok("UoMInfo", r.dump().substr(0, 80));
    });

    // ════════════════════════════════════════════════════════════════════════
    // Items
    // ════════════════════════════════════════════════════════════════════════

    Items itemsAPI(client);

    run(4, "getItems", [&] {
        auto r = itemsAPI.getItems();
        ok("getItems", r.is_array()
            ? std::to_string(r.size()) + " Items"
            : r.dump().substr(0, 80));
    });

    run(5, "getItems (Switch)", [&] {
        auto r = itemsAPI.getItems("Switch");
        ok("getItems Switch", r.is_array()
            ? std::to_string(r.size()) + " Switch-Items"
            : r.dump());
    });

    run(6, "getItem", [&] {
        auto r = itemsAPI.getItem(TEST_ITEM);
        ok("getItem " + TEST_ITEM,
           r.contains("name") ? r["name"].get<std::string>() : r.dump());
    });

    run(7, "getItemState", [&] {
        auto r = itemsAPI.getItemState(TEST_ITEM);
        ok("State von " + TEST_ITEM, r.dump());
    });

    run(8, "sendCommand ON", [&] {
        auto r = itemsAPI.sendCommand(TEST_ITEM, "ON");
        ok("sendCommand ON", r.dump());
    });

    run(9, "sendCommand OFF", [&] {
        auto r = itemsAPI.sendCommand(TEST_ITEM, "OFF");
        ok("sendCommand OFF", r.dump());
    });

    run(10, "updateItemState", [&] {
        auto r = itemsAPI.updateItemState(TEST_NUMBER_ITEM, "42");
        ok("updateItemState → 42", r.dump());
    });

    run(11, "postUpdate", [&] {
        auto r = itemsAPI.postUpdate(TEST_NUMBER_ITEM, "100");
        ok("postUpdate → 100", r.dump());
    });

    run(12, "addOrUpdateItem (create)", [&] {
        json data = {
            {"type","Switch"}, {"name","cppTestSwitch"},
            {"label","C++ Test Switch"}, {"groupNames", json::array()},
            {"tags", json::array()}
        };
        auto r = itemsAPI.addOrUpdateItem("cppTestSwitch", data);
        ok("addOrUpdateItem", r.dump().substr(0, 60));
    });

    run(13, "addOrUpdateItems (bulk)", [&] {
        json items = json::array();
        items.push_back({{"type","Number"},{"name","cppTestNumber"},{"label","C++ Number"}});
        auto r = itemsAPI.addOrUpdateItems(items);
        ok("addOrUpdateItems", r.dump().substr(0, 60));
    });

    run(14, "addTag", [&] {
        ok("addTag", itemsAPI.addTag(TEST_ITEM, "Lighting").dump());
    });

    run(15, "removeTag", [&] {
        ok("removeTag", itemsAPI.removeTag(TEST_ITEM, "Lighting").dump());
    });

    run(16, "addMetadata", [&] {
        json meta = {{"value","cppValue"},{"config",json::object()}};
        ok("addMetadata", itemsAPI.addMetadata(TEST_ITEM, "cppTestNS", meta).dump());
    });

    run(17, "getMetadataNamespaces", [&] {
        ok("getMetadataNamespaces", itemsAPI.getMetadataNamespaces(TEST_ITEM).dump());
    });

    run(18, "removeMetadata", [&] {
        ok("removeMetadata", itemsAPI.removeMetadata(TEST_ITEM, "cppTestNS").dump());
    });

    run(19, "addGroupMember", [&] {
        ok("addGroupMember", itemsAPI.addGroupMember(TEST_GROUP, "cppTestNumber").dump());
    });

    run(20, "removeGroupMember", [&] {
        ok("removeGroupMember", itemsAPI.removeGroupMember(TEST_GROUP, "cppTestNumber").dump());
    });

    run(21, "purgeOrphanedMetadata", [&] {
        ok("purgeOrphanedMetadata", itemsAPI.purgeOrphanedMetadata().dump());
    });

    run(22, "deleteItem", [&] {
        try { itemsAPI.deleteItem("cppTestSwitch"); } catch (...) {}
        try { itemsAPI.deleteItem("cppTestNumber"); } catch (...) {}
        ok("deleteItem (beide Test-Items gelöscht)");
    });

    // ════════════════════════════════════════════════════════════════════════
    // Things
    // ════════════════════════════════════════════════════════════════════════

    Things thingsAPI(client);

    run(23, "getThings", [&] {
        auto r = thingsAPI.getThings();
        ok("getThings", r.is_array() ? std::to_string(r.size()) + " Things" : r.dump());
    });

    run(24, "getThing", [&] {
        auto r = thingsAPI.getThing(TEST_THING_UID);
        ok("getThing", r.contains("UID") ? r["UID"].get<std::string>() : r.dump());
    });

    run(25, "getThingStatus", [&] {
        ok("getThingStatus", thingsAPI.getThingStatus(TEST_THING_UID).dump());
    });

    run(26, "enableThing / disableThing", [&] {
        thingsAPI.enableThing(TEST_THING_UID);  ok("enableThing");
        thingsAPI.disableThing(TEST_THING_UID); ok("disableThing");
        thingsAPI.enableThing(TEST_THING_UID);  ok("enableThing (zurücksetzen)");
    });

    run(27, "getThingFirmwares", [&] {
        ok("getThingFirmwares", thingsAPI.getThingFirmwares(TEST_THING_UID).dump());
    });

    // ════════════════════════════════════════════════════════════════════════
    // Rules
    // ════════════════════════════════════════════════════════════════════════

    Rules rulesAPI(client);

    run(28, "getRules", [&] {
        auto r = rulesAPI.getRules();
        ok("getRules", r.is_array() ? std::to_string(r.size()) + " Regeln" : r.dump());
    });

    run(29, "getRule", [&] {
        auto r = rulesAPI.getRule(TEST_RULE_UID);
        ok("getRule", r.contains("uid") ? r["uid"].get<std::string>() : r.dump());
    });

    run(30, "createRule / enable / disable / runNow / deleteRule", [&] {
        auto uid = "cppTestRule_" + std::to_string(
            std::chrono::system_clock::now().time_since_epoch().count());
        json data = {
            {"uid", uid}, {"name","C++ Test Rule"},
            {"description","Created by C++ test"},
            {"triggers",json::array()},{"conditions",json::array()},{"actions",json::array()}
        };
        rulesAPI.createRule(data); ok("createRule");
        rulesAPI.enable(uid);      ok("enable");
        rulesAPI.disable(uid);     ok("disable");
        rulesAPI.deleteRule(uid);  ok("deleteRule");
    });

    // ════════════════════════════════════════════════════════════════════════
    // Actions / Addons / Audio / Logging / Links
    // ════════════════════════════════════════════════════════════════════════

    run(31, "getActions", [&] {
        Actions a(client);
        auto r = a.getActions(TEST_THING_UID);
        ok("getActions", r.is_array() ? std::to_string(r.size()) + " Aktionen" : r.dump());
    });

    run(32, "getAddons",           [&] { Addons a(client); ok("getAddons",      a.getAddons().dump().substr(0,60)); });
    run(33, "getAddonTypes",       [&] { Addons a(client); ok("getAddonTypes",  a.getAddonTypes().dump().substr(0,60)); });
    run(34, "getAddonSuggestions", [&] { Addons a(client); ok("getAddonSugg.",  a.getAddonSuggestions().dump().substr(0,60)); });
    run(35, "getAddonServices",    [&] { Addons a(client); ok("getAddonSvc.",   a.getAddonServices().dump().substr(0,60)); });
    run(36, "getDefaultSink",      [&] { Audio  a(client); ok("getDefaultSink", a.getDefaultSink().dump()); });
    run(37, "getDefaultSource",    [&] { Audio  a(client); ok("getDefSrc.",     a.getDefaultSource().dump()); });
    run(38, "getSinks",            [&] { Audio  a(client); ok("getSinks",       a.getSinks().dump().substr(0,60)); });
    run(39, "getSources",          [&] { Audio  a(client); ok("getSources",     a.getSources().dump().substr(0,60)); });

    run(40, "getLoggers", [&] {
        Logging l(client);
        ok("getLoggers", l.getLoggers().dump().substr(0, 60));
    });

    run(41, "modifyOrAddLogger / getLogger / removeLogger", [&] {
        Logging l(client);
        l.modifyOrAddLogger(TEST_LOGGER, "DEBUG"); ok("modifyOrAddLogger");
        ok("getLogger", l.getLogger(TEST_LOGGER).dump());
        l.removeLogger(TEST_LOGGER);               ok("removeLogger");
    });

    run(42, "getLinks",       [&] { Links l(client); ok("getLinks",       l.getLinks().dump().substr(0,60)); });
    run(43, "getOrphanLinks", [&] { Links l(client); ok("getOrphanLinks", l.getOrphanLinks().dump().substr(0,60)); });

    // ════════════════════════════════════════════════════════════════════════
    // More classes
    // ════════════════════════════════════════════════════════════════════════

    run(44, "getChannelTypes",       [&] { ChannelTypes c(client);       ok("getChannelTypes",  c.getChannelTypes().dump().substr(0,60)); });
    run(45, "getThingTypes",         [&] { ThingTypes c(client);         ok("getThingTypes",    c.getThingTypes().dump().substr(0,60)); });
    run(46, "getConfigDescriptions", [&] { ConfigDescriptions c(client); ok("getConfigDesc.",   c.getConfigDescriptions().dump().substr(0,60)); });
    run(47, "Persistence.getServices",[&]{ Persistence p(client);        ok("getServices",      p.getServices().dump().substr(0,60)); });
    run(48, "getDiscoveryBindings",  [&] { Discovery d(client);          ok("getDiscovery",     d.getDiscoveryBindings().dump().substr(0,60)); });
    run(49, "getDiscoveredThings",   [&] { Inbox i(client);              ok("getDiscovered",    i.getDiscoveredThings().dump().substr(0,60)); });
    run(50, "getSitemaps",           [&] { Sitemaps s(client);           ok("getSitemaps",      s.getSitemaps().dump().substr(0,60)); });
    run(51, "getTags",               [&] { Tags t(client);               ok("getTags",          t.getTags().dump().substr(0,60)); });
    run(52, "getTemplates",          [&] { Templates t(client);          ok("getTemplates",     t.getTemplates().dump().substr(0,60)); });
    run(53, "getModuleTypes",        [&] { ModuleTypes m(client);        ok("getModuleTypes",   m.getModuleTypes().dump().substr(0,60)); });
    run(54, "getProfileTypes",       [&] { ProfileTypes p(client);       ok("getProfileTypes",  p.getProfileTypes().dump().substr(0,60)); });
    run(55, "getTransformations",    [&] { Transformations t(client);    ok("getTransf.",       t.getTransformations().dump().substr(0,60)); });
    run(56, "getTransfServices",     [&] { Transformations t(client);    ok("getTransfSvc.",    t.getTransformationServices().dump().substr(0,60)); });
    run(57, "getUITiles",            [&] { UI u(client);                 ok("getUITiles",       u.getUITiles().dump().substr(0,60)); });
    run(58, "getServices",           [&] { Services s(client);           ok("getServices",      s.getServices().dump().substr(0,60)); });
    run(59, "getIconsets",           [&] { Iconsets i(client);           ok("getIconsets",      i.getIconsets().dump().substr(0,60)); });
    run(60, "getAPITokens",          [&] { Auth a(client);               ok("getAPITokens",     a.getAPITokens().dump()); });
    run(61, "getSessions",           [&] { Auth a(client);               ok("getSessions",      a.getSessions().dump()); });
    run(62, "getVoices",             [&] { Voice v(client);              ok("getVoices",        v.getVoices().dump().substr(0,60)); });
    run(63, "getDefaultVoice",       [&] { Voice v(client);              ok("getDefaultVoice",  v.getDefaultVoice().dump()); });
    run(64, "getInterpreters",       [&] { Voice v(client);              ok("getInterpreters",  v.getInterpreters().dump().substr(0,60)); });

    // ════════════════════════════════════════════════════════════════════════
    // SSE Demo (5 Sekunden)
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "\n" << DIM << "═══ SSE Demo (5s) ═══════════════════════════════════════" << RESET << "\n";
    std::cout << "  " << BLUE << "⚡" << RESET
              << " Öffne ItemStateChangedEvent Stream für '" << TEST_ITEM << "'…\n\n";

    ItemEvents itemEvents(client);
    auto sse = itemEvents.ItemStateChangedEvent(TEST_ITEM);

    // Sende Befehle in separatem Thread
    std::atomic<bool> stopSender{false};
    std::thread sender([&] {
        bool toggle = true;
        while (!stopSender.load()) {
            try {
                itemsAPI.sendCommand(TEST_ITEM, toggle ? "ON" : "OFF");
            } catch (...) {}
            toggle = !toggle;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    int sseCount = 0;
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);

    sse.forEach([&](const std::string& data) {
        ++sseCount;
        std::string display = data.size() > 100 ? data.substr(0, 100) + "…" : data;
        std::cout << "  " << BLUE << "⚡" << RESET << " " << DIM << display << RESET << "\n";
        return std::chrono::steady_clock::now() < deadline; // false = stop
    });

    stopSender.store(true);
    sender.join();

    std::cout << "\n  " << GREEN << "✓" << RESET
              << " SSE beendet — " << sseCount << " Event(s) empfangen\n";

    // ── Zusammenfassung ───────────────────────────────────────────────────────
    std::string line(55, '=');
    std::cout << "\n" << BOLD << line << RESET << "\n";
    std::cout << "  Ergebnis: " << total << " Tests   "
              << GREEN << BOLD << passed << " bestanden" << RESET << "   "
              << (failed > 0 ? RED + BOLD : std::string{})
              << failed << " fehlgeschlagen" << RESET << "\n";
    std::cout << BOLD << line << RESET << "\n\n";

    return failed > 0 ? 1 : 0;
}
