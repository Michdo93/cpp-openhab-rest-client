# cpp-openhab-rest-client

A C++17 client for the openHAB REST API – for services, Qt applications, robotics (ROS 2),
embedded Linux and every program where C++ is the language of choice.

It is part of a family of libraries with **the same classes, methods, parameters and
results** in every language: [Python](https://github.com/Michdo93/python-openhab-rest-client)
(the reference), [JavaScript](https://github.com/Michdo93/js-openhab-rest-client),
[Node.js](https://github.com/Michdo93/nodejs-openhab-rest-client),
[Java](https://github.com/Michdo93/java-openhab-rest-client),
[Android/Kotlin](https://github.com/Michdo93/android-openhab-rest-client),
[C](https://github.com/Michdo93/c-openhab-rest-client),
[C#](https://github.com/Michdo93/csharp-openhab-rest-client) and C++.
Tests for openHAB installations: [cpp-openhab-test-suite](https://github.com/Michdo93/cpp-openhab-test-suite).

```cpp
#include <openhab/openhab.hpp>
#include <cstdlib>
#include <iostream>

int main() {
    const char* token = std::getenv("OPENHAB_TOKEN");   // never pass a null char* to std::string
    openhab::OpenHABClient client("http://127.0.0.1:8080", std::nullopt, std::nullopt,
                                  token ? token : "");
    openhab::Items items(client);

    openhab::json r = items.sendCommand("Wohnzimmer_Licht", "ON");
    if (openhab::isError(r)) std::cerr << openhab::errorMessage(r) << "\n";

    openhab::Items::GetItemsArgs args;
    args.tags = "Light";
    args.fields = "name,state";
    for (const auto& item : items.getItems(args))
        std::cout << item["name"] << " = " << item["state"] << "\n";

    auto stream = openhab::ItemEvents(client).ItemStateChangedEvent("Wohnzimmer_Licht");
    while (auto e = stream.nextEvent(10000))            // wait at most 10 s
        std::cout << openhab::str(*e, "payload.value") << "\n";
}
```

## What is new in 2.0.0

Version 2.0.0 is a rewrite (details: [BUGS-1.0.0.md](BUGS-1.0.0.md)). The REST classes are
generated from python-openhab-rest-client (`tools/py2cpp.py`), statement by statement – same
endpoints, headers, query parameters, error messages and results. A differential test with 79
calls against openHAB 5 gives identical results for Python and C++.

- all 33 classes and 178 methods (1.0.0 declared 171, but implemented only 5 classes – the
  others ended in linker errors)
- Python parameter order and defaults; optional parameters also as argument struct
  (C++20: `items.getItems({.tags = "Light"})`)
- results as `openhab::json` (`nlohmann::ordered_json`, keys in the order openHAB sends them);
  errors as `{"error": "..."}`, empty successes as `{"message": "OK"}` – nothing is thrown
- event streams (`openhab::EventStream`) with time limit, range-for, interrupt from another
  thread or a signal handler; HTTP errors of streams are reported, TLS is verified
- names and UIDs in paths are encoded (`#` in channel and action UIDs), timeout and TLS options,
  thread-safe requests
- new names that do not collide with c-openhab-rest-client: `<openhab/openhab.hpp>`,
  `libopenhab_rest_client_cpp`, `find_package(OpenHABRestClientCpp)`, target
  `openhab::rest_client_cpp`

## Requirements

- C++17 compiler: GCC 8+, Clang 7+, MSVC 2019+ or MinGW-w64
- CMake 3.16+
- [libcurl](https://curl.se/libcurl/) and [nlohmann/json](https://github.com/nlohmann/json) 3.2+
  (nlohmann/json is downloaded automatically if it is not installed)

| System | Packages |
|---|---|
| Debian, Ubuntu, Raspberry Pi OS | `sudo apt install build-essential cmake libcurl4-openssl-dev nlohmann-json3-dev` |
| Fedora | `sudo dnf install gcc-c++ cmake libcurl-devel json-devel` |
| macOS (Homebrew) | `brew install cmake curl nlohmann-json` |
| Windows (vcpkg) | `vcpkg install curl nlohmann-json` |
| Windows (MSYS2 MinGW) | `pacman -S mingw-w64-x86_64-{gcc,cmake,curl,nlohmann-json}` |

## Using the library

### CMake FetchContent (recommended)

```cmake
cmake_minimum_required(VERSION 3.16)
project(myapp CXX)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(cpp_openhab_rest_client
  GIT_REPOSITORY https://github.com/Michdo93/cpp-openhab-rest-client.git
  GIT_TAG 2.0.0)
FetchContent_MakeAvailable(cpp_openhab_rest_client)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE openhab::rest_client_cpp)
```

### Installed library

```bash
git clone https://github.com/Michdo93/cpp-openhab-rest-client.git
cmake -S cpp-openhab-rest-client -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j2
sudo cmake --install build
```

```cmake
find_package(OpenHABRestClientCpp 2 REQUIRED)
target_link_libraries(myapp PRIVATE openhab::rest_client_cpp)  # or openhab::rest_client_cpp_shared
```

or without CMake: `g++ -std=c++17 main.cpp $(pkg-config --cflags --libs openhab_rest_client_cpp)`.

## Concepts

### Client

```cpp
openhab::OpenHABClient c("http://127.0.0.1:8080", std::nullopt, std::nullopt, token);
openhab::OpenHABClient cloud("https://myopenhab.org", "me@example.com", password);

openhab::ClientOptions o;          // C++20: openhab::OpenHABClient c(url, {.token = token, .timeout = 30});
o.token = token;
o.timeout = 30;                    // seconds (default 10)
o.verify = false;                  // self-signed certificate
openhab::OpenHABClient slow(url, o);

c.isLoggedIn();                    // was openHAB reachable? (Python: isLoggedIn)
c.lastError();                     // why not
```

A client may be used from several threads at the same time. The REST classes keep a
reference to it: `openhab::Items items(c);`.

### Methods and arguments

The classes and methods have the names of the Python library (`openhab::Items::getItems`,
`openhab::ThingTypes::getThingType`). Required parameters come first, the optional ones keep the
Python order and defaults (`None` → `std::nullopt`, dictionaries and lists → `openhab::json`).
Every method with optional parameters also takes an argument struct:

```cpp
items.getItem("Wohnzimmer_Licht");
items.getItem("Wohnzimmer_Licht", "semantics", false);           // positional

openhab::Items::GetItemArgs a;                                    // C++17
a.metadata = "semantics";
a.recursive = false;
items.getItem("Wohnzimmer_Licht", a);

items.getItem("Wohnzimmer_Licht", {.metadata = "semantics", .recursive = false});   // C++20
```

### Results

Every REST method returns an `openhab::json` (`nlohmann::ordered_json`):

| Response | Result |
|---|---|
| JSON | object or array |
| text (e.g. an item state) | string: `r.get<std::string>()` |
| empty success | `{"message": "OK"}` (or the status object, where Python returns it) |
| error | `{"error": "Item not found."}` – test with `openhab::isError(r)`, read with `openhab::errorMessage(r)` |

Helpers: `openhab::at(v, "payload.value")`, `openhab::str(v, "0.name")`,
`openhab::num(v, "state", 0.0)` (also for states such as `"21.5 °C"`).

### Event streams (Server-Sent Events)

```cpp
openhab::EventStream s = openhab::ItemEvents(c).ItemStateChangedEvent("Wohnzimmer_Licht");
if (s.isError()) std::cerr << s.error() << "\n";
while (s.isOpen()) {
    auto e = s.nextEvent(1000);                  // wait at most 1 s
    if (!e) continue;                            // timeout: do other work
    std::cout << openhab::str(*e, "payload.value") << "\n";
}
for (const openhab::json& e : s) { ... }        // until the stream ends
```

`s.interrupt()` (from another thread or a signal handler) ends a waiting call at once;
`nextLine()` returns the raw lines, `EventStream::parseData()` decodes a `data:` line,
`nextEvent(timeout, true)` also returns the ALIVE messages.

### Low-level requests

`c.get/post/put/del("/items", headers, data, params)` reach any endpoint; `c.executeSSE(path)`
opens any event stream.

## Development

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j2
ctest --test-dir build --output-on-failure      # unit tests with a local HTTP server, C++20 test
OPENHAB_URL=http://127.0.0.1:8080 OPENHAB_TOKEN=oh.xxx ctest --test-dir build   # + integration

# regenerate the REST classes from python-openhab-rest-client
python3 tools/py2cpp.py ../python-openhab-rest-client/openhab .
```

## Methods

### Actions

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getActions` | thingUID | language | `json` |
| `executeAction` | thingUID, actionUID, actionInputs | language | `json` |

### Addons

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getAddons` |  | serviceID, language | `json` |
| `getAddon` | addonID | serviceID, language | `json` |
| `getAddonConfig` | addonID | serviceID | `json` |
| `updateAddonConfig` | addonID, configData | serviceID | `json` |
| `installAddon` | addonID | serviceID | `json` |
| `uninstallAddon` | addonID | serviceID | `json` |
| `getAddonServices` |  | language | `json` |
| `getAddonSuggestions` |  | language | `json` |
| `getAddonTypes` |  | serviceID, language | `json` |
| `installAddonFromUrl` | url |  | `json` |

### Audio

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getDefaultSink` |  | language | `json` |
| `getDefaultSource` |  | language | `json` |
| `getSinks` |  | language | `json` |
| `getSources` |  | language | `json` |

### Auth

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getAPITokens` |  |  | `json` |
| `revokeAPIToken` | tokenName |  | `json` |
| `logout` | refreshToken, sessionID |  | `json` |
| `getSessions` |  |  | `json` |
| `getToken` |  | useCookie, grantType, code, redirectURI, clientID, refreshToken, codeVerifier | `json` |

### ChannelEvents

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `ChannelDescriptionChangedEvent` |  | channelUID | `EventStream` |
| `ChannelTriggeredEvent` |  | channelUID | `EventStream` |

### ChannelTypes

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getChannelTypes` |  | prefixes, language | `json` |
| `getChannelType` | channelTypeUID | language | `json` |
| `getLinkableItemTypes` | channelTypeUID |  | `json` |

### ConfigDescriptions

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getConfigDescriptions` |  | scheme, language | `json` |
| `getConfigDescription` | uri | language | `json` |

### Discovery

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getDiscoveryBindings` |  |  | `json` |
| `getBindingInfo` | bindingID | language | `json` |
| `startBindingScan` | bindingID | input | `json` |

### Events

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getEvents` |  | topics | `EventStream` |
| `initiateStateTracker` |  |  | `EventStream` |
| `updateSSEConnectionItems` | connectionID, items |  | `json` |

### Iconsets

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getIconsets` |  | language | `json` |

### Inbox

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getDiscoveredThings` |  | includeIgnored | `json` |
| `removeDiscoveryResult` | thingUID |  | `json` |
| `approveDiscoveryResult` | thingUID, thingLabel | newThingID, language | `json` |
| `ignoreDiscoveryResult` | thingUID |  | `json` |
| `unignoreDiscoveryResult` | thingUID |  | `json` |

### InboxEvents

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `InboxAddedEvent` |  | thingUID | `EventStream` |
| `InboxRemovedEvent` |  | thingUID | `EventStream` |
| `InboxUpdatedEvent` |  | thingUID | `EventStream` |

### ItemEvents

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `ItemEvent` |  |  | `EventStream` |
| `ItemAddedEvent` |  | itemName | `EventStream` |
| `ItemRemovedEvent` |  | itemName | `EventStream` |
| `ItemUpdatedEvent` |  | itemName | `EventStream` |
| `ItemCommandEvent` |  | itemName | `EventStream` |
| `ItemStateEvent` |  | itemName | `EventStream` |
| `ItemStatePredictedEvent` |  | itemName | `EventStream` |
| `ItemStateChangedEvent` |  | itemName | `EventStream` |
| `GroupItemStateChangedEvent` |  | itemName, memberName | `EventStream` |

### Items

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getItems` |  | type, tags, metadata, recursive, fields, staticDataOnly, language, parents | `json` |
| `addOrUpdateItems` | items |  | `json` |
| `getItem` | itemName | metadata, recursive, language, parents | `json` |
| `addOrUpdateItem` | itemName, itemData | language | `json` |
| `sendCommand` | itemName, command | source | `json` |
| `postUpdate` | itemName, state | source | `json` |
| `deleteItem` | itemName |  | `json` |
| `addGroupMember` | itemName, memberItemName |  | `json` |
| `removeGroupMember` | itemName, memberItemName |  | `json` |
| `addMetadata` | itemName, namespace_, metadata |  | `json` |
| `removeMetadata` | itemName, namespace_ |  | `json` |
| `getMetadataNamespaces` | itemName | language | `json` |
| `getSemanticItem` | itemName, semanticClass | language | `json` |
| `getItemState` | itemName |  | `json` |
| `updateItemState` | itemName, state | language, source | `json` |
| `addTag` | itemName, tag |  | `json` |
| `removeTag` | itemName, tag |  | `json` |
| `purgeOrphanedMetadata` |  |  | `json` |

### LinkEvents

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `ItemChannelLinkAddedEvent` |  | itemName, channelUID | `EventStream` |
| `ItemChannelLinkRemovedEvent` |  | itemName, channelUID | `EventStream` |

### Links

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getLinks` |  | channelUID, itemName | `json` |
| `getLink` | itemName, channelUID |  | `json` |
| `linkItemToChannel` | itemName, channelUID, configuration |  | `json` |
| `unlinkItemFromChannel` | itemName, channelUID |  | `json` |
| `deleteAllLinks` | object |  | `json` |
| `getOrphanLinks` |  |  | `json` |
| `purgeUnusedLinks` |  |  | `json` |

### Logging

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getLoggers` |  |  | `json` |
| `getLogger` | loggerName |  | `json` |
| `modifyOrAddLogger` | loggerName, level |  | `json` |
| `removeLogger` | loggerName |  | `json` |

### ModuleTypes

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getModuleTypes` |  | tags, typeFilter, language | `json` |
| `getModuleType` | moduleTypeUID | language | `json` |

### Persistence

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getServices` |  | language | `json` |
| `getServiceConfiguration` | serviceID |  | `json` |
| `setServiceConfiguration` | serviceID, config |  | `json` |
| `deleteServiceConfiguration` | serviceID |  | `json` |
| `getItemsFromService` |  | serviceID, itemName | `json` |
| `getItemPersistenceData` | itemName | serviceID, startTime, endTime, page, pageLength, boundary, itemState, displayState, language | `json` |
| `storeItemData` | itemName, time, state | serviceID | `json` |
| `deleteItemData` | itemName, startTime, endTime, serviceID |  | `json` |

### ProfileTypes

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getProfileTypes` |  | channelTypeUID, itemType, language | `json` |

### Rules

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getRules` |  | prefix, tags, summary, staticDataOnly | `json` |
| `createRule` | ruleData |  | `json` |
| `getRule` | ruleUID |  | `json` |
| `updateRule` | ruleUID, ruleData |  | `json` |
| `deleteRule` | ruleUID |  | `json` |
| `getModule` | ruleUID, moduleCategory, moduleID |  | `json` |
| `getModuleConfig` | ruleUID, moduleCategory, moduleID |  | `json` |
| `getModuleConfigParam` | ruleUID, moduleCategory, moduleID, param |  | `json` |
| `setModuleConfigParam` | ruleUID, moduleCategory, moduleID, param, value |  | `json` |
| `getActions` | ruleUID |  | `json` |
| `getConditions` | ruleUID |  | `json` |
| `getConfiguration` | ruleUID |  | `json` |
| `updateConfiguration` | ruleUID, configData |  | `json` |
| `setRuleState` | ruleUID, enable |  | `json` |
| `enable` | ruleUID |  | `json` |
| `disable` | ruleUID |  | `json` |
| `runNow` | ruleUID | contextData | `json` |
| `getTriggers` | ruleUID |  | `json` |
| `simulateSchedule` | fromTime, untilTime |  | `json` |

### Services

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getServices` |  | language | `json` |
| `getService` | serviceID | language | `json` |
| `getServiceConfig` | serviceID |  | `json` |
| `updateServiceConfig` | serviceID, configData | language | `json` |
| `deleteServiceConfig` | serviceID |  | `json` |
| `getServiceContexts` | serviceID | language | `json` |

### Sitemaps

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getSitemaps` |  |  | `json` |
| `getSitemap` | sitemapName | type, jsonCallback, includeHidden, language | `json` |
| `getSitemapPage` | sitemapName, pageID | subscriptionID, includeHidden, language | `json` |
| `getFullSitemap` | sitemapName | subscriptionID, includeHidden, language | `json` |
| `getSitemapEvents` | subscriptionID | sitemapName, pageID | `EventStream` |
| `getFullSitemapEvents` | subscriptionID | sitemapName | `EventStream` |
| `subscribeToSitemapEvents` |  |  | `json` |

### Systeminfo

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getSystemInfo` |  |  | `json` |
| `getUoMInfo` |  |  | `json` |

### Tags

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getTags` |  | language | `json` |
| `createTag` | tagData | language | `json` |
| `getTag` | tagID | language | `json` |
| `updateTag` | tagID, tagData | language | `json` |
| `deleteTag` | tagID | language | `json` |

### Templates

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getTemplates` |  | language | `json` |
| `getTemplate` | templateUID | language | `json` |

### ThingEvents

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `ThingAddedEvent` |  | thingUID | `EventStream` |
| `ThingRemovedEvent` |  | thingUID | `EventStream` |
| `ThingUpdatedEvent` |  | thingUID | `EventStream` |
| `ThingStatusInfoEvent` |  | thingUID | `EventStream` |
| `ThingStatusInfoChangedEvent` |  | thingUID | `EventStream` |

### Things

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getThings` |  | summary, staticDataOnly, language | `json` |
| `createThing` | thingData | language | `json` |
| `getThing` | thingUID | language | `json` |
| `updateThing` | thingUID, thingData | language | `json` |
| `deleteThing` | thingUID | force, language | `json` |
| `updateThingConfiguration` | thingUID, configurationData | language | `json` |
| `getThingConfigStatus` | thingUID | language | `json` |
| `setThingStatus` | thingUID, enabled | language | `json` |
| `enableThing` | thingUID |  | `json` |
| `disableThing` | thingUID |  | `json` |
| `updateThingFirmware` | thingUID, firmwareVersion | language | `json` |
| `getThingFirmwareStatus` | thingUID | language | `json` |
| `getThingFirmwares` | thingUID | language | `json` |
| `getThingStatus` | thingUID | language | `json` |

### ThingTypes

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getThingTypes` |  | bindingID, language | `json` |
| `getThingType` | thingTypeUID | language | `json` |

### Transformations

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getTransformations` |  |  | `json` |
| `getTransformation` | transformationUID |  | `json` |
| `updateTransformation` | transformationUID, transformationData |  | `json` |
| `deleteTransformation` | transformationUID |  | `json` |
| `getTransformationServices` |  |  | `json` |

### UI

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getUIComponents` | namespace_ | summary | `json` |
| `addUIComponent` | namespace_, componentData |  | `json` |
| `getUIComponent` | namespace_, componentUID |  | `json` |
| `updateUIComponent` | namespace_, componentUID, componentData |  | `json` |
| `deleteUIComponent` | namespace_, componentUID |  | `json` |
| `getUITiles` |  |  | `json` |

### UUID

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getUUID` |  |  | `json` |

### Voice

| Method | Parameters | Optional (defaults as in Python) | Returns |
|---|---|---|---|
| `getDefaultVoice` |  | language | `json` |
| `startDialog` | sourceID | ksID, sttID, ttsID, voiceID, hliIDs, sinkID, keyword, listeningItem, language | `json` |
| `stopDialog` | sourceID |  | `json` |
| `getInterpreters` |  | language | `json` |
| `interpretText` | text | language | `json` |
| `getInterpreter` | interpreterID | language | `json` |
| `interpretTextBatch` | text, IDs | language | `json` |
| `listenAndAnswer` | sourceID, sttID, ttsID, voiceID, hliIDs, sinkID, listeningItem | language | `json` |
| `sayText` | text, voiceID, sinkID | volume | `json` |
| `getVoices` |  | language | `json` |

