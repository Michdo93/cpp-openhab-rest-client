# openhab-rest-client — C++

C++ client for the openHAB REST API.
Mirrors **python-openhab-rest-client** exactly: same class names, same method names, same usage pattern.

**Abhängigkeiten:** libcurl · nlohmann/json · C++17

---

## Abhängigkeiten installieren

### Ubuntu / Debian
```bash
sudo apt install libcurl4-openssl-dev nlohmann-json3-dev cmake build-essential
```

### macOS (Homebrew)
```bash
brew install curl nlohmann-json cmake
```

### Windows (vcpkg)
```bash
vcpkg install curl nlohmann-json
```

---

## Bauen

```bash
mkdir build && cd build

# Linux/macOS
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j$(nproc)

# Windows (Visual Studio)
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

# Ausgabe:
#   libopenhab_rest_client.so   (Shared Library, Linux)
#   libopenhab_rest_client.a    (Static Library, Linux)
#   openhab_rest_client.dll     (Shared Library, Windows)
#   openhab_rest_client.lib     (Static Library, Windows)
#   openhab_test                (Testanwendung)
```

### Install (systemweit)
```bash
cmake --build . --target install
# Headers → /usr/local/include/openhab/
# Library  → /usr/local/lib/
```

---

## In ein eigenes Projekt einbinden

### Option A — CMake (empfohlen)

**CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.16)
project(MeinProjekt)

find_package(OpenHABRestClient REQUIRED)   # nach system-install
# ODER direkt:
add_subdirectory(extern/openhab-rest-client)

add_executable(meins main.cpp)
target_link_libraries(meins PRIVATE openhab_rest_client_static)
```

### Option B — manuell (g++)
```bash
g++ -std=c++17 -O2 \
    -I/pfad/zu/openhab-rest-client/include \
    main.cpp \
    /pfad/zu/openhab-rest-client/build/libopenhab_rest_client.a \
    -lcurl -o meins
```

### Option C — als git submodule
```bash
git submodule add https://github.com/Michdo93/cpp-openhab-rest-client extern/openhab-rest-client
```
```cmake
add_subdirectory(extern/openhab-rest-client)
target_link_libraries(meins PRIVATE openhab_rest_client_static)
```

---

## Quick Start

```cpp
#include <openhab/openhab.h>
#include <iostream>

int main() {
    // Basic Auth
    openhab::OpenHABClient client("http://127.0.0.1:8080", "openhab", "habopen");

    // Token Auth
    // openhab::OpenHABClient client("http://127.0.0.1:8080", "", "", "oh.openhab.xxx");

    if (!client.isLoggedIn()) {
        std::cerr << "Verbindung fehlgeschlagen\n";
        return 1;
    }

    // Items
    openhab::Items items(client);
    auto allItems = items.getItems();
    std::cout << allItems.dump(2) << "\n";

    items.sendCommand("LivingRoomLight", "ON");

    auto state = items.getItemState("LivingRoomLight");
    std::cout << "State: " << state.dump() << "\n";

    // Things
    openhab::Things things(client);
    auto allThings = things.getThings();

    // Rules
    openhab::Rules rules(client);
    rules.enable("my-rule-uid");
    rules.runNow("my-rule-uid");

    return 0;
}
```

---

## JSON-Verarbeitung

Alle Methoden geben `nlohmann::json` zurück:

```cpp
openhab::Items items(client);
auto result = items.getItems("Switch");   // type-Filter

// Array iterieren
for (auto& item : result) {
    std::cout << item["name"].get<std::string>()
              << " = " << item["state"].get<std::string>() << "\n";
}

// Einzelnes Feld lesen
auto itemData = items.getItem("LivingRoomLight");
std::string name  = itemData["name"];
std::string state = itemData.value("state", "NULL");

// JSON für addOrUpdateItem bauen
nlohmann::json newItem = {
    {"type",       "Switch"},
    {"name",       "MeinSchalter"},
    {"label",      "Mein Schalter"},
    {"groupNames", nlohmann::json::array()},
    {"tags",       nlohmann::json::array()}
};
items.addOrUpdateItem("MeinSchalter", newItem);
```

---

## Server-Sent Events (SSE)

SSE läuft blockierend — für Hintergrund-Threads empfohlen:

```cpp
#include <openhab/openhab.h>
#include <thread>
#include <atomic>

std::atomic<bool> stop{false};

// SSE in separatem Thread
std::thread sseThread([&] {
    openhab::ItemEvents itemEvents(client);
    auto sse = itemEvents.ItemStateChangedEvent("LivingRoomLight");

    sse.forEach([&](const std::string& data) {
        // data = roher JSON-String nach "data: "
        auto json = nlohmann::json::parse(data);
        std::cout << "Event: " << json.dump() << "\n";
        return !stop.load();   // false = Stream stoppen
    });
});

// Nach 30 Sekunden stoppen
std::this_thread::sleep_for(std::chrono::seconds(30));
stop.store(true);
sseThread.join();
```

### Alle SSE-Klassen

```cpp
openhab::ItemEvents    ie(client);
ie.ItemStateChangedEvent("*");         // alle Items
ie.ItemCommandEvent("LivingRoomLight");
ie.ItemAddedEvent();
ie.GroupItemStateChangedEvent("gLights", "*");

openhab::ThingEvents   te(client);
te.ThingStatusInfoChangedEvent("*");

openhab::InboxEvents   inb(client);
inb.InboxAddedEvent();

openhab::LinkEvents    le(client);
le.ItemChannelLinkAddedEvent();

openhab::ChannelEvents ce(client);
ce.ChannelTriggeredEvent("*");

openhab::Events        ev(client);
ev.getEvents("openhab/items,openhab/things");   // mehrere Topics
```

---

## Fehlerbehandlung

```cpp
try {
    openhab::Items items(client);
    auto r = items.getItem("nichtVorhandenes");
} catch (const openhab::OpenHABException& e) {
    std::cerr << "HTTP " << e.statusCode() << ": " << e.what() << "\n";
} catch (const std::exception& e) {
    std::cerr << "Fehler: " << e.what() << "\n";
}
```

---

## Alle Klassen

`OpenHABClient`, `SSEConnection`, `OpenHABException`

API: `Actions`, `Addons`, `Audio`, `Auth`, `ChannelTypes`, `ConfigDescriptions`,
`Discovery`, `Events`, `Iconsets`, `Inbox`, `Items`, `ItemEvents`,
`ThingEvents`, `InboxEvents`, `LinkEvents`, `ChannelEvents`,
`Links`, `Logging`, `ModuleTypes`, `Persistence`, `ProfileTypes`,
`Rules`, `Services`, `Sitemaps`, `Systeminfo`, `Tags`, `Templates`,
`ThingTypes`, `Things`, `Transformations`, `UI`, `UUID`, `Voice`

---

## Testanwendung

```bash
# Konfiguration in test/test.cpp anpassen:
#   const std::string URL      = "http://127.0.0.1:8080";
#   const std::string USERNAME = "openhab";
#   const std::string PASSWORD = "habopen";

./build/openhab_test
```

---

## Plattformen

| Platform | Compiler | Status |
|---|---|---|
| Linux (Ubuntu 22+) | GCC 11+, Clang 14+ | ✅ |
| macOS 12+ | Apple Clang, GCC via Homebrew | ✅ |
| Windows 10/11 | MSVC 2019+, MinGW | ✅ (via vcpkg) |
| Raspberry Pi (ARM) | GCC 11+ | ✅ |

---

## License

MIT
