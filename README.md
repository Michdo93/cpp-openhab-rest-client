# cpp-openhab-rest-client

A C++ client for the openHAB REST API. This library enables easy interaction with the openHAB REST API to control smart home devices, retrieve status information, and process events — from any C++ application.

It mirrors the [python-openhab-rest-client](https://github.com/Michdo93/python-openhab-rest-client) library: same class names, same method names, same usage pattern.

**Dependencies:**
- [libcurl](https://curl.se/libcurl/) — HTTP communication
- [nlohmann/json](https://github.com/nlohmann/json) — JSON parsing (auto-downloaded by CMake if not found)

All API methods return `nlohmann::json` objects, so you work with structured data directly — no manual JSON parsing needed.

## Features

Supports the following openHAB REST API endpoints:

- Actions
- Addons
- Audio
- Auth
- ChannelTypes
- ConfigDescriptions
- Discovery
- Events (general + ItemEvents, ThingEvents, InboxEvents, LinkEvents, ChannelEvents)
- Iconsets
- Inbox
- Items
- Links
- Logging
- ModuleTypes
- Persistence
- ProfileTypes
- Rules
- Services
- Sitemaps
- Systeminfo
- Tags
- Templates
- ThingTypes
- Things
- Transformations
- UI
- UUID
- Voice

Server-Sent Events (SSE) are supported via `SSEConnection` using a callback (`forEach`) or cancellable blocking loop.

## Requirements

- **C++17** or later
- **CMake 3.16** or later
- **libcurl** development headers
- **nlohmann/json 3.2.0+** (auto-downloaded if not installed)
- A C++ compiler: GCC 8+, Clang 7+, MSVC 2019+, or MinGW-w64

---

## Building the Library

The library uses CMake and produces both a **shared library** (`libopenhab_rest_client.so` / `.dll`) and a **static library** (`libopenhab_rest_client.a` / `.lib`).

---

### Linux / macOS

#### 1. Install dependencies

**Ubuntu / Debian:**
```bash
sudo apt-get update
sudo apt-get install -y libcurl4-openssl-dev cmake build-essential
```

**Fedora / RHEL / CentOS:**
```bash
sudo dnf install -y libcurl-devel cmake gcc-c++ make
```

**Arch Linux:**
```bash
sudo pacman -S curl cmake base-devel
```

**macOS (Homebrew):**
```bash
brew install curl cmake nlohmann-json
```

#### 2. Clone and build

```bash
git clone https://github.com/Michdo93/cpp-openhab-rest-client.git
cd cpp-openhab-rest-client
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j$(nproc)
```

This produces:
- `build/libopenhab_rest_client.so` (shared) + `build/libopenhab_rest_client.so.1` (versioned symlink)
- `build/libopenhab_rest_client.a` (static)
- `build/openhab_test` (test executable)

#### 3. Install system-wide (optional)

```bash
sudo cmake --install .
# Installs to /usr/local/lib/ and /usr/local/include/openhab/
```

Or to a custom prefix:

```bash
cmake --install . --prefix /opt/openhab-client
```

---

### Windows (MSVC + vcpkg)

#### 1. Install vcpkg dependencies

```powershell
vcpkg install curl nlohmann-json --triplet x64-windows
```

#### 2. Build with CMake

```powershell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release `
    -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_INSTALLATION_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build . --config Release
```

This produces:
- `build/Release/openhab_rest_client.dll`
- `build/Release/openhab_rest_client.lib`
- `build/Release/openhab_test.exe`

#### Visual Studio

1. Open Visual Studio and choose **Open a local folder**.
2. Select the `cpp-openhab-rest-client` directory.
3. Visual Studio detects `CMakeLists.txt` automatically.
4. Set the CMake toolchain file in **Project → CMake Settings** if using vcpkg.
5. Build with **Build → Build All**.

---

### Windows (MinGW-w64 / MSYS2)

```bash
pacman -S mingw-w64-x86_64-curl mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc mingw-w64-x86_64-nlohmann-json
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

---

### Raspberry Pi / ARM / Embedded Linux

Same as Linux — works on all Linux distributions with libcurl:

```bash
sudo apt-get install -y libcurl4-openssl-dev cmake build-essential
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j4
```

Cross-compilation for ARM from x86 host:

```bash
sudo apt-get install -y gcc-aarch64-linux-gnu g++-aarch64-linux-gnu libcurl4-openssl-dev
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-aarch64.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

---

## Adding the Library to Your Project

Once built (or installed), there are several ways to use it.

---

### Option 1: CMake `find_package` (after system install)

After `cmake --install`, use `find_package` in your own `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenHABRestClient REQUIRED)
find_package(CURL REQUIRED)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE openhab_rest_client ${CURL_LIBRARIES})
```

---

### Option 2: CMake `FetchContent` (no pre-install needed)

Automatically download and build as part of your project:

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    openhab_rest_client
    GIT_REPOSITORY https://github.com/Michdo93/cpp-openhab-rest-client.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(openhab_rest_client)

find_package(CURL REQUIRED)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE
    openhab_rest_client_static
    ${CURL_LIBRARIES}
    nlohmann_json::nlohmann_json)
```

---

### Option 3: CMake `add_subdirectory` (local copy)

Clone or copy the library into your project tree:

```bash
git clone https://github.com/Michdo93/cpp-openhab-rest-client.git libs/openhab
```

Then in your `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/openhab)
find_package(CURL REQUIRED)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE
    openhab_rest_client_static
    ${CURL_LIBRARIES}
    nlohmann_json::nlohmann_json)
```

---

### Option 4: Manual compilation (no CMake)

Compile the library sources directly alongside your application:

**Linux / macOS:**
```bash
g++ -std=c++17 -O2 \
    -I/path/to/cpp-openhab-rest-client/include \
    -I/path/to/nlohmann \
    cpp-openhab-rest-client/src/OpenHABClient.cpp \
    cpp-openhab-rest-client/src/Items.cpp \
    cpp-openhab-rest-client/src/Things.cpp \
    cpp-openhab-rest-client/src/Rules.cpp \
    cpp-openhab-rest-client/src/Events.cpp \
    cpp-openhab-rest-client/src/Actions.cpp \
    main.cpp \
    -lcurl -o myapp
```

**Windows (MSVC Developer Command Prompt):**
```cmd
cl /std:c++17 /O2 /EHsc ^
    /I"path\to\include" /I"path\to\nlohmann" ^
    src\OpenHABClient.cpp src\Items.cpp src\Things.cpp ^
    src\Rules.cpp src\Events.cpp src\Actions.cpp ^
    main.cpp ^
    /link curl.lib /out:myapp.exe
```

---

### Option 5: Link against pre-built libraries

If you downloaded or built the shared/static library:

**Linux (shared):**
```bash
g++ -std=c++17 main.cpp \
    -I/usr/local/include \
    -L/usr/local/lib \
    -lopenhab_rest_client -lcurl \
    -Wl,-rpath,/usr/local/lib \
    -o myapp
```

**Linux (static):**
```bash
g++ -std=c++17 main.cpp \
    -I/usr/local/include \
    /usr/local/lib/libopenhab_rest_client.a \
    -lcurl -o myapp
```

**Windows (shared DLL):**
```cmd
cl /std:c++17 main.cpp /I"include" ^
    /link openhab_rest_client.lib curl.lib /out:myapp.exe
```
Copy `openhab_rest_client.dll` next to the executable.

---

## Include

All classes are in the `openhab` namespace. Use the single convenience header:

```cpp
#include <openhab/openhab.h>
```

Or include individual headers:

```cpp
#include <openhab/OpenHABClient.h>   // client + SSEConnection + OpenHABException
#include <openhab/API.h>             // all API classes
```

---

## Usage

### Authentication

```cpp
#include <openhab/openhab.h>
using namespace openhab;

// Basic Authentication
OpenHABClient client("http://127.0.0.1:8080", "openhab", "habopen");

// Token Authentication
OpenHABClient client("http://127.0.0.1:8080", "", "", "oh.openhab.xxxx");

// myopenhab.org Cloud
OpenHABClient client("https://myopenhab.org", "your@email.com", "yourpassword");
```

The constructor calls `login()` automatically. Check connectivity:

```cpp
if (!client.isLoggedIn()) {
    std::cerr << "Connection failed." << std::endl;
    return 1;
}
```

### REST Requests

All API methods return `nlohmann::json`. Throw `OpenHABException` on HTTP errors:

```cpp
#include <openhab/openhab.h>
#include <iostream>
using namespace openhab;

int main() {
    try {
        OpenHABClient client("http://127.0.0.1:8080", "openhab", "habopen");
        Items items(client);

        json allItems = items.getItems();
        std::cout << allItems.dump(2) << std::endl;

        items.sendCommand("MyLightSwitch", "ON");
    }
    catch (const OpenHABException& e) {
        std::cerr << "HTTP " << e.statusCode() << ": " << e.what() << std::endl;
    }
    return 0;
}
```

### Working with JSON responses

All methods return `nlohmann::json`. Access fields directly:

```cpp
json item = items.getItem("MyLightSwitch");
std::string state = item["state"].get<std::string>();
std::string name  = item["name"].get<std::string>();
std::cout << name << " = " << state << std::endl;

// Iterate over a list
json allItems = items.getItems();
for (const auto& it : allItems) {
    std::cout << it["name"].get<std::string>() << std::endl;
}
```

### Server-Sent Events (SSE)

`SSEConnection` is non-copyable and uses a blocking `forEach` callback. Return `true` to continue receiving events, `false` to stop.

```cpp
#include <openhab/openhab.h>
#include <iostream>
using namespace openhab;

int main() {
    OpenHABClient client("http://127.0.0.1:8080", "openhab", "habopen");
    ItemEvents itemEvents(client);

    auto sse = itemEvents.ItemStateChangedEvent("MyLightSwitch");
    sse.forEach([](const std::string& data) -> bool {
        // data = raw JSON payload after "data: "
        json event = json::parse(data);
        std::cout << "Event: " << event.dump() << std::endl;
        return true;  // return false to stop
    });

    return 0;
}
```

#### Stop from another thread

```cpp
auto sse = itemEvents.ItemStateChangedEvent();

// Start SSE in a background thread
std::thread sseThread([&sse]() {
    sse.forEach([](const std::string& data) -> bool {
        std::cout << data << std::endl;
        return true;
    });
});

// Stop after 10 seconds from main thread
std::this_thread::sleep_for(std::chrono::seconds(10));
sse.cancel();
sseThread.join();
```

### Running the test application

Edit the connection settings at the top of `test/test.cpp`, then:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
./openhab_test
```

---

## Full List of Methods

All methods return `nlohmann::json` unless noted. All methods throw `openhab::OpenHABException` on HTTP errors or connection failures. Optional `std::string` parameters default to `""` (empty = not sent to the server).

---

### `openhab::OpenHABClient`

The core HTTP client. All API classes hold a reference to an `OpenHABClient`.

#### Header

```cpp
#include <openhab/OpenHABClient.h>
```

#### Constructor

```cpp
OpenHABClient(const std::string& url,
              const std::string& username = "",
              const std::string& password = "",
              const std::string& token    = "")
```

**Parameters:**
- `url` — Base URL (e.g. `"http://127.0.0.1:8080"`). Trailing slash is stripped.
- `username` — Username for Basic Authentication, or `""`.
- `password` — Password for Basic Authentication, or `""`.
- `token` — Bearer token for Token Authentication, or `""`.

The constructor calls `login()` automatically. Non-copyable, movable.

**Examples:**

```cpp
// Basic Auth
openhab::OpenHABClient client("http://127.0.0.1:8080", "openhab", "habopen");

// Token Auth
openhab::OpenHABClient client("http://127.0.0.1:8080", "", "", "oh.openhab.xxxx");

// Cloud
openhab::OpenHABClient client("https://myopenhab.org", "user@example.com", "pass");
```

#### Getters

| Method | Return type | Description |
|---|---|---|
| `baseUrl()` | `const std::string&` | Base URL without trailing slash |
| `username()` | `const std::string&` | Username (Basic Auth) |
| `isCloud()` | `bool` | `true` when connected to `myopenhab.org` |
| `isLoggedIn()` | `bool` | `true` after a successful `login()` |

#### HTTP Methods

```cpp
HttpResponse get (const std::string& endpoint,
                  const Headers& headers = {},
                  const Params&  params  = {}) const;

HttpResponse post(const std::string& endpoint,
                  const Headers& headers = {},
                  const std::string& body = "",
                  const Params& params = {}) const;

HttpResponse put (const std::string& endpoint,
                  const Headers& headers = {},
                  const std::string& body = "",
                  const Params& params = {}) const;

HttpResponse del (const std::string& endpoint,
                  const Headers& headers = {},
                  const std::string& body = "",
                  const Params& params = {}) const;
```

Note: `del` is used instead of `delete` because `delete` is a C++ keyword.

**Type aliases:**
```cpp
using Headers = std::map<std::string, std::string>;
using Params  = std::map<std::string, std::string>;
```

#### SSE

```cpp
SSEConnection sse(const std::string& url) const;
```

Opens an SSE stream to the given full URL. Returns an `SSEConnection`.

---

### `openhab::OpenHABException`

Thrown by all REST methods on HTTP errors or connection failures.

```cpp
#include <openhab/OpenHABClient.h>
```

Inherits from `std::runtime_error`.

| Method | Return type | Description |
|---|---|---|
| `what()` | `const char*` | Error message |
| `statusCode()` | `int` | HTTP status code, or `-1` if not applicable |

```cpp
try {
    items.getItem("nonExistent");
}
catch (const openhab::OpenHABException& e) {
    std::cerr << "HTTP " << e.statusCode() << ": " << e.what() << std::endl;
}
```

---

### `openhab::HttpResponse`

Returned by the low-level HTTP methods (`get`, `post`, `put`, `del`). The high-level API classes return `json` directly.

| Field/Method | Type | Description |
|---|---|---|
| `statusCode` | `int` | HTTP status code |
| `body` | `std::string` | Response body |
| `contentType` | `std::string` | Content-Type header value |
| `location` | `std::string` | Location header (for redirects) |
| `isJson()` | `bool` | `true` if Content-Type contains `application/json` |
| `isEmpty()` | `bool` | `true` if body is blank |
| `toJson()` | `json` | Parse body as JSON, or return `{"status": N}` if empty |

---

### `openhab::SSEConnection`

Wraps an active SSE HTTP stream. Non-copyable, movable.

```cpp
#include <openhab/OpenHABClient.h>
```

#### Methods

##### `forEach(std::function<bool(const std::string&)> callback)`

Blocks and calls `callback` for each event. The argument is the raw payload after `"data: "`. Return `true` to continue, `false` to stop.

```cpp
auto sse = itemEvents.ItemStateChangedEvent("testSwitch");
sse.forEach([](const std::string& data) -> bool {
    auto event = nlohmann::json::parse(data);
    std::cout << event["type"].get<std::string>() << std::endl;
    return true; // keep receiving
});
```

##### `cancel()`

Stops the stream. Safe to call from another thread.

```cpp
sse.cancel();
```

---

### `openhab::Actions`

Provides methods to retrieve and execute thing actions.

#### Constructor

```cpp
openhab::Actions actions(client);
```

#### Methods

##### `getActions(const std::string& thingUID, const std::string& lang = "")`

Gets all available actions for a thing.

**Parameters:**
- `thingUID` — The UID of the thing.
- `lang` — Optional `Accept-Language` header value.

**Returns:** `json`

##### `executeAction(const std::string& thingUID, const std::string& actionUID, const json& inputs, const std::string& lang = "")`

Executes an action on a thing.

**Parameters:**
- `thingUID` — The UID of the thing.
- `actionUID` — The UID of the action.
- `inputs` — JSON object with input parameters.
- `lang` — Optional language header.

**Returns:** `json`

```cpp
actions.executeAction("myThingUID", "myActionUID",
    {{"param1", "value1"}, {"param2", 42}});
```

---

### `openhab::Addons`

Provides methods to manage openHAB add-ons.

#### Constructor

```cpp
openhab::Addons addons(client);
```

#### Methods

| Method | Description |
|---|---|
| `getAddons(const std::string& serviceID = "", const std::string& lang = "")` | Gets all available add-ons |
| `getAddon(const std::string& id, const std::string& serviceID = "", const std::string& lang = "")` | Gets a specific add-on |
| `getAddonConfig(const std::string& id, const std::string& serviceID = "")` | Gets the add-on configuration |
| `updateAddonConfig(const std::string& id, const json& config, const std::string& serviceID = "")` | Updates the add-on configuration |
| `installAddon(const std::string& id, const std::string& serviceID = "")` | Installs an add-on |
| `uninstallAddon(const std::string& id, const std::string& serviceID = "")` | Uninstalls an add-on |
| `getAddonServices(const std::string& lang = "")` | Gets all add-on services |
| `getAddonSuggestions(const std::string& lang = "")` | Gets suggested add-ons |
| `getAddonTypes(const std::string& serviceID = "", const std::string& lang = "")` | Gets all add-on types |
| `installAddonFromUrl(const std::string& url)` | Installs an add-on from a URL |

---

### `openhab::Audio`

Provides methods to interact with the openHAB audio system.

#### Constructor

```cpp
openhab::Audio audio(client);
```

#### Methods

| Method | Description |
|---|---|
| `getDefaultSink(const std::string& lang = "")` | Gets the default audio sink |
| `getDefaultSource(const std::string& lang = "")` | Gets the default audio source |
| `getSinks(const std::string& lang = "")` | Gets all available sinks |
| `getSources(const std::string& lang = "")` | Gets all available sources |

---

### `openhab::Auth`

Provides methods for authentication token and session management.

#### Constructor

```cpp
openhab::Auth auth(client);
```

#### Methods

| Method | Description |
|---|---|
| `getAPITokens()` | Gets all API tokens for the current user |
| `revokeAPIToken(const std::string& name)` | Revokes an API token by name |
| `logout(const std::string& refreshToken, const std::string& sessionId)` | Terminates a session |
| `getSessions()` | Gets all active sessions |
| `getToken(const std::string& grantType = "", const std::string& code = "", const std::string& redirectUri = "", const std::string& clientId = "", const std::string& refreshToken = "", const std::string& codeVerifier = "")` | Obtains OAuth access and refresh tokens |

---

### `openhab::ChannelTypes`

Provides methods to retrieve channel type information.

#### Constructor

```cpp
openhab::ChannelTypes channelTypes(client);
```

#### Methods

| Method | Description |
|---|---|
| `getChannelTypes(const std::string& prefixes = "", const std::string& lang = "")` | Gets all channel types |
| `getChannelType(const std::string& uid, const std::string& lang = "")` | Gets a specific channel type |
| `getLinkableItemTypes(const std::string& uid)` | Gets item types linkable to a trigger channel type |

---

### `openhab::ConfigDescriptions`

Provides methods to retrieve configuration descriptions.

#### Constructor

```cpp
openhab::ConfigDescriptions configDescriptions(client);
```

#### Methods

| Method | Description |
|---|---|
| `getConfigDescriptions(const std::string& scheme = "", const std::string& lang = "")` | Gets all configuration descriptions |
| `getConfigDescription(const std::string& uri, const std::string& lang = "")` | Gets a specific configuration description |

---

### `openhab::Discovery`

Provides methods to interact with the openHAB discovery service.

#### Constructor

```cpp
openhab::Discovery discovery(client);
```

#### Methods

| Method | Description |
|---|---|
| `getDiscoveryBindings()` | Gets all bindings that support discovery |
| `getBindingInfo(const std::string& bindingId, const std::string& lang = "")` | Gets information about a binding |
| `startBindingScan(const std::string& bindingId, const std::string& input = "")` | Starts a discovery scan |

```cpp
discovery.startBindingScan("zwave");
```

---

### `openhab::Events`

Provides general openHAB event bus access via SSE.

#### Constructor

```cpp
openhab::Events events(client);
```

#### Methods

| Method | Returns | Description |
|---|---|---|
| `getEvents(const std::string& topics = "")` | `SSEConnection` | All events, optionally filtered by topic |
| `initiateStateTracker()` | `SSEConnection` | Initiates a new state tracker SSE connection |
| `updateSSEConnectionItems(const std::string& connId, const json& items)` | `json` | Updates items tracked by a state tracker |

```cpp
auto sse = events.getEvents("openhab/items/*/statechanged");
sse.forEach([](const std::string& data) -> bool {
    std::cout << data << std::endl;
    return true;
});
```

---

### `openhab::ItemEvents`

Provides SSE streams for item-related events. All methods return `SSEConnection`. The optional `name` parameter defaults to `"*"` (all items).

#### Constructor

```cpp
openhab::ItemEvents itemEvents(client);
```

#### Methods

| Method | Description |
|---|---|
| `ItemEvent()` | All item events |
| `ItemAddedEvent(const std::string& name = "*")` | Item added events |
| `ItemRemovedEvent(const std::string& name = "*")` | Item removed events |
| `ItemUpdatedEvent(const std::string& name = "*")` | Item updated events |
| `ItemCommandEvent(const std::string& name = "*")` | Item command events |
| `ItemStateEvent(const std::string& name = "*")` | Item state events |
| `ItemStatePredictedEvent(const std::string& name = "*")` | Item state predicted events |
| `ItemStateChangedEvent(const std::string& name = "*")` | Item state changed events |
| `GroupItemStateChangedEvent(const std::string& item, const std::string& member)` | Group item state changed events for a specific member |

```cpp
auto sse = itemEvents.ItemStateChangedEvent("MyLightSwitch");
sse.forEach([](const std::string& data) -> bool {
    auto event = nlohmann::json::parse(data);
    std::cout << event["type"].get<std::string>() << std::endl;
    return true;
});
```

---

### `openhab::ThingEvents`

Provides SSE streams for thing-related events. All methods return `SSEConnection`. The optional `uid` parameter defaults to `"*"`.

#### Constructor

```cpp
openhab::ThingEvents thingEvents(client);
```

#### Methods

| Method | Description |
|---|---|
| `ThingAddedEvent(const std::string& uid = "*")` | Thing added events |
| `ThingRemovedEvent(const std::string& uid = "*")` | Thing removed events |
| `ThingUpdatedEvent(const std::string& uid = "*")` | Thing updated events |
| `ThingStatusInfoEvent(const std::string& uid = "*")` | Thing status info events |
| `ThingStatusInfoChangedEvent(const std::string& uid = "*")` | Thing status info changed events |

---

### `openhab::InboxEvents`

Provides SSE streams for inbox (discovery) events. All methods return `SSEConnection`. The optional `uid` parameter defaults to `"*"`.

#### Constructor

```cpp
openhab::InboxEvents inboxEvents(client);
```

#### Methods

| Method | Description |
|---|---|
| `InboxAddedEvent(const std::string& uid = "*")` | Inbox added events |
| `InboxRemovedEvent(const std::string& uid = "*")` | Inbox removed events |
| `InboxUpdatedEvent(const std::string& uid = "*")` | Inbox updated events |

---

### `openhab::LinkEvents`

Provides SSE streams for item-channel link events. Both methods return `SSEConnection`.

#### Constructor

```cpp
openhab::LinkEvents linkEvents(client);
```

#### Methods

| Method | Description |
|---|---|
| `ItemChannelLinkAddedEvent(const std::string& item = "*", const std::string& ch = "*")` | Link added events |
| `ItemChannelLinkRemovedEvent(const std::string& item = "*", const std::string& ch = "*")` | Link removed events |

---

### `openhab::ChannelEvents`

Provides SSE streams for channel events. Both methods return `SSEConnection`.

#### Constructor

```cpp
openhab::ChannelEvents channelEvents(client);
```

#### Methods

| Method | Description |
|---|---|
| `ChannelDescriptionChangedEvent(const std::string& uid = "*")` | Channel description changed events |
| `ChannelTriggeredEvent(const std::string& uid = "*")` | Channel triggered events |

---

### `openhab::Iconsets`

#### Constructor

```cpp
openhab::Iconsets iconsets(client);
```

#### Methods

| Method | Description |
|---|---|
| `getIconsets(const std::string& lang = "")` | Gets all available iconsets |

---

### `openhab::Inbox`

Provides methods to manage the openHAB inbox (discovery results).

#### Constructor

```cpp
openhab::Inbox inbox(client);
```

#### Methods

| Method | Description |
|---|---|
| `getDiscoveredThings(bool includeIgnored = true)` | Gets all discovered things |
| `removeDiscoveryResult(const std::string& uid)` | Removes a discovery result |
| `approveDiscoveryResult(const std::string& uid, const std::string& label, const std::string& newId = "", const std::string& lang = "")` | Approves a discovery result and creates the thing |
| `ignoreDiscoveryResult(const std::string& uid)` | Marks a discovery result as ignored |
| `unignoreDiscoveryResult(const std::string& uid)` | Removes the ignore flag |

---

### `openhab::Items`

Provides methods to manage openHAB items.

#### Constructor

```cpp
openhab::Items items(client);
```

#### Methods

##### `getItems(const std::string& type = "", const std::string& tags = "", const std::string& metadata = ".*", bool recursive = false, const std::string& fields = "", bool staticOnly = false, const std::string& language = "")`

Gets all available items with optional filters.

**Parameters:**
- `type` — Item type filter (e.g. `"Switch"`, `"Number"`).
- `tags` — Tag filter.
- `metadata` — Metadata selector (default `".*"`).
- `recursive` — Fetch group members recursively.
- `fields` — Comma-separated list of fields to return.
- `staticOnly` — Return only cached data.
- `language` — Language for the response.

**Returns:** `json`

##### `addOrUpdateItems(const json& items)`

Adds or updates a list of items.

**Returns:** `json`

##### `getItem(const std::string& name, const std::string& metadata = ".*", bool recursive = true, const std::string& lang = "")`

Gets a single item.

**Returns:** `json`

##### `addOrUpdateItem(const std::string& name, const json& data, const std::string& lang = "")`

Adds or updates a single item.

**Returns:** `json`

##### `sendCommand(const std::string& name, const std::string& command)`

Sends a command to an item.

**Returns:** `json`

```cpp
items.sendCommand("MyLightSwitch", "ON");
```

##### `postUpdate(const std::string& name, const std::string& state)`

Updates the state of an item (alias for `updateItemState`).

**Returns:** `json`

##### `deleteItem(const std::string& name)`

Removes an item from the registry.

**Returns:** `json`

##### `addGroupMember(const std::string& name, const std::string& member)`

Adds a member to a group item.

**Returns:** `json`

##### `removeGroupMember(const std::string& name, const std::string& member)`

Removes a member from a group item.

**Returns:** `json`

##### `addMetadata(const std::string& name, const std::string& ns, const json& metadata)`

Adds metadata to an item.

**Returns:** `json`

##### `removeMetadata(const std::string& name, const std::string& ns)`

Removes metadata from an item.

**Returns:** `json`

##### `getMetadataNamespaces(const std::string& name, const std::string& lang = "")`

Gets all metadata namespaces of an item.

**Returns:** `json`

##### `getSemanticItem(const std::string& name, const std::string& semClass, const std::string& lang = "")`

Gets the item that defines the requested semantics.

**Returns:** `json`

##### `getItemState(const std::string& name)`

Gets the current state of an item.

**Returns:** `json` — the state as a plain text string wrapped in JSON.

```cpp
json state = items.getItemState("MyLightSwitch");
std::cout << state.get<std::string>() << std::endl;
```

##### `updateItemState(const std::string& name, const std::string& state, const std::string& lang = "")`

Updates the state of an item.

**Returns:** `json`

##### `addTag(const std::string& name, const std::string& tag)`

Adds a tag to an item.

**Returns:** `json`

##### `removeTag(const std::string& name, const std::string& tag)`

Removes a tag from an item.

**Returns:** `json`

##### `purgeOrphanedMetadata()`

Removes unused/orphaned metadata from all items.

**Returns:** `json`

---

### `openhab::Links`

Provides methods to manage item-channel links.

#### Constructor

```cpp
openhab::Links links(client);
```

#### Methods

| Method | Description |
|---|---|
| `getLinks(const std::string& channelUID = "", const std::string& item = "")` | Gets all links, optionally filtered |
| `getLink(const std::string& item, const std::string& channelUID)` | Gets a specific link |
| `linkItemToChannel(const std::string& item, const std::string& channelUID, const json& config)` | Links an item to a channel |
| `unlinkItemFromChannel(const std::string& item, const std::string& channelUID)` | Unlinks an item from a channel |
| `deleteAllLinks(const std::string& object)` | Deletes all links for an item or thing |
| `getOrphanLinks()` | Gets all orphan links |
| `purgeUnusedLinks()` | Removes all unused/orphaned links |

---

### `openhab::Logging`

Provides methods to manage openHAB loggers.

#### Constructor

```cpp
openhab::Logging logging(client);
```

#### Methods

| Method | Description |
|---|---|
| `getLoggers()` | Gets all loggers and their levels |
| `getLogger(const std::string& name)` | Gets a specific logger |
| `modifyOrAddLogger(const std::string& name, const std::string& level)` | Modifies or adds a logger (`"DEBUG"`, `"INFO"`, `"WARN"`, `"ERROR"`) |
| `removeLogger(const std::string& name)` | Removes a logger |

---

### `openhab::ModuleTypes`

Provides methods to retrieve rule module types.

#### Constructor

```cpp
openhab::ModuleTypes moduleTypes(client);
```

#### Methods

| Method | Description |
|---|---|
| `getModuleTypes(const std::string& tags = "", const std::string& typeFilter = "", const std::string& lang = "")` | Gets all module types |
| `getModuleType(const std::string& uid, const std::string& lang = "")` | Gets a specific module type |

---

### `openhab::Persistence`

Provides methods to interact with openHAB persistence services.

#### Constructor

```cpp
openhab::Persistence persistence(client);
```

#### Methods

| Method | Description |
|---|---|
| `getServices(const std::string& lang = "")` | Gets all persistence services |
| `getServiceConfiguration(const std::string& serviceId)` | Gets a service configuration |
| `setServiceConfiguration(const std::string& serviceId, const json& config)` | Sets a service configuration |
| `deleteServiceConfiguration(const std::string& serviceId)` | Deletes a service configuration |
| `getItemsFromService(const std::string& serviceId = "")` | Gets items available via a service |
| `getItemPersistenceData(const std::string& item, const std::string& serviceId, const std::string& startTime = "", const std::string& endTime = "", int page = 1, int pageLength = 50, bool boundary = false, bool itemState = false)` | Gets item persistence data |
| `storeItemData(const std::string& item, const std::string& time, const std::string& state, const std::string& serviceId = "")` | Stores a data point |
| `deleteItemData(const std::string& item, const std::string& start, const std::string& end, const std::string& serviceId)` | Deletes item data within a time range |

```cpp
json data = persistence.getItemPersistenceData(
    "MyTemperatureSensor", "rrd4j",
    "2024-01-01T00:00:00.000+0000",
    "2024-01-02T00:00:00.000+0000",
    1, 100);
```

---

### `openhab::ProfileTypes`

#### Constructor

```cpp
openhab::ProfileTypes profileTypes(client);
```

#### Methods

| Method | Description |
|---|---|
| `getProfileTypes(const std::string& channelTypeUID = "", const std::string& itemType = "", const std::string& lang = "")` | Gets all available profile types |

---

### `openhab::Rules`

Provides methods to manage openHAB rules.

#### Constructor

```cpp
openhab::Rules rules(client);
```

#### Methods

| Method | Description |
|---|---|
| `getRules(const std::string& prefix = "", const std::string& tags = "", bool summary = false, bool staticOnly = false)` | Gets all rules |
| `createRule(const json& data)` | Creates a new rule |
| `getRule(const std::string& uid)` | Gets a specific rule |
| `updateRule(const std::string& uid, const json& data)` | Updates an existing rule |
| `deleteRule(const std::string& uid)` | Deletes a rule |
| `getModule(const std::string& uid, const std::string& cat, const std::string& mid)` | Gets a specific module |
| `getModuleConfig(const std::string& uid, const std::string& cat, const std::string& mid)` | Gets the module configuration |
| `getModuleConfigParam(const std::string& uid, const std::string& cat, const std::string& mid, const std::string& param)` | Gets a module config parameter |
| `setModuleConfigParam(const std::string& uid, const std::string& cat, const std::string& mid, const std::string& param, const std::string& value)` | Sets a module config parameter |
| `getActions(const std::string& uid)` | Gets all action modules |
| `getConditions(const std::string& uid)` | Gets all condition modules |
| `getTriggers(const std::string& uid)` | Gets all trigger modules |
| `getConfiguration(const std::string& uid)` | Gets the rule configuration |
| `updateConfiguration(const std::string& uid, const json& config)` | Updates the rule configuration |
| `setRuleState(const std::string& uid, bool enable)` | Enables or disables a rule |
| `enable(const std::string& uid)` | Enables a rule |
| `disable(const std::string& uid)` | Disables a rule |
| `runNow(const std::string& uid, const json& context = nullptr)` | Executes a rule immediately |
| `simulateSchedule(const std::string& from, const std::string& until)` | Simulates the rule schedule |

```cpp
rules.enable("my-rule-uid");
rules.runNow("my-rule-uid");
```

---

### `openhab::Services`

Provides methods to manage openHAB configurable services.

#### Constructor

```cpp
openhab::Services services(client);
```

#### Methods

| Method | Description |
|---|---|
| `getServices(const std::string& lang = "")` | Gets all configurable services |
| `getService(const std::string& id, const std::string& lang = "")` | Gets a specific service |
| `getServiceConfig(const std::string& id)` | Gets the service configuration |
| `updateServiceConfig(const std::string& id, const json& config, const std::string& lang = "")` | Updates the service configuration |
| `deleteServiceConfig(const std::string& id)` | Deletes the service configuration |
| `getServiceContexts(const std::string& id, const std::string& lang = "")` | Gets all contexts of a multi-context service |

---

### `openhab::Sitemaps`

Provides methods to interact with openHAB sitemaps.

#### Constructor

```cpp
openhab::Sitemaps sitemaps(client);
```

#### Methods

| Method | Returns | Description |
|---|---|---|
| `getSitemaps()` | `json` | Gets all available sitemaps |
| `getSitemap(const std::string& name, const std::string& type = "", bool includeHidden = false, const std::string& lang = "")` | `json` | Gets a specific sitemap |
| `getSitemapPage(const std::string& name, const std::string& pageId, const std::string& subId = "", bool includeHidden = false, const std::string& lang = "")` | `json` | Gets a sitemap page |
| `getSitemapEvents(const std::string& subId, const std::string& sitemapName = "", const std::string& pageId = "")` | `SSEConnection` | Gets sitemap events as SSE stream |
| `subscribeToSitemapEvents()` | `json` | Creates a sitemap event subscription |

---

### `openhab::Systeminfo`

#### Constructor

```cpp
openhab::Systeminfo systeminfo(client);
```

#### Methods

| Method | Description |
|---|---|
| `getSystemInfo()` | Gets general system information |
| `getUoMInfo()` | Gets units of measurement information |

---

### `openhab::Tags`

Provides methods to manage openHAB semantic tags.

#### Constructor

```cpp
openhab::Tags tags(client);
```

#### Methods

| Method | Description |
|---|---|
| `getTags(const std::string& lang = "")` | Gets all semantic tags |
| `createTag(const json& data, const std::string& lang = "")` | Creates a new tag |
| `getTag(const std::string& id, const std::string& lang = "")` | Gets a specific tag |
| `updateTag(const std::string& id, const json& data, const std::string& lang = "")` | Updates a tag |
| `deleteTag(const std::string& id, const std::string& lang = "")` | Deletes a tag |

---

### `openhab::Templates`

#### Constructor

```cpp
openhab::Templates templates(client);
```

#### Methods

| Method | Description |
|---|---|
| `getTemplates(const std::string& lang = "")` | Gets all available rule templates |
| `getTemplate(const std::string& uid, const std::string& lang = "")` | Gets a specific rule template |

---

### `openhab::ThingTypes`

#### Constructor

```cpp
openhab::ThingTypes thingTypes(client);
```

#### Methods

| Method | Description |
|---|---|
| `getThingTypes(const std::string& bindingId = "", const std::string& lang = "")` | Gets all available thing types |
| `getThingType(const std::string& uid, const std::string& lang = "")` | Gets a specific thing type |

---

### `openhab::Things`

Provides methods to manage openHAB things.

#### Constructor

```cpp
openhab::Things things(client);
```

#### Methods

| Method | Description |
|---|---|
| `getThings(bool summary = false, bool staticOnly = false, const std::string& lang = "")` | Gets all things |
| `createThing(const json& data, const std::string& lang = "")` | Creates a new thing |
| `getThing(const std::string& uid, const std::string& lang = "")` | Gets a specific thing |
| `updateThing(const std::string& uid, const json& data, const std::string& lang = "")` | Updates a thing |
| `deleteThing(const std::string& uid, bool force = false, const std::string& lang = "")` | Deletes a thing |
| `updateThingConfiguration(const std::string& uid, const json& config, const std::string& lang = "")` | Updates the thing configuration |
| `getThingConfigStatus(const std::string& uid, const std::string& lang = "")` | Gets the configuration status |
| `setThingStatus(const std::string& uid, bool enabled, const std::string& lang = "")` | Enables or disables a thing |
| `enableThing(const std::string& uid)` | Enables a thing |
| `disableThing(const std::string& uid)` | Disables a thing |
| `updateThingFirmware(const std::string& uid, const std::string& version, const std::string& lang = "")` | Updates the firmware |
| `getThingFirmwareStatus(const std::string& uid, const std::string& lang = "")` | Gets the firmware status |
| `getThingFirmwares(const std::string& uid, const std::string& lang = "")` | Gets available firmware versions |
| `getThingStatus(const std::string& uid, const std::string& lang = "")` | Gets the thing status |

---

### `openhab::Transformations`

#### Constructor

```cpp
openhab::Transformations transformations(client);
```

#### Methods

| Method | Description |
|---|---|
| `getTransformations()` | Gets all transformations |
| `getTransformation(const std::string& uid)` | Gets a specific transformation |
| `updateTransformation(const std::string& uid, const json& data)` | Updates a transformation |
| `deleteTransformation(const std::string& uid)` | Deletes a transformation |
| `getTransformationServices()` | Gets all transformation services |

---

### `openhab::UI`

Provides methods to manage UI components and tiles.

#### Constructor

```cpp
openhab::UI ui(client);
```

#### Methods

| Method | Description |
|---|---|
| `getUIComponents(const std::string& ns, bool summary = false)` | Gets all UI components in a namespace |
| `addUIComponent(const std::string& ns, const json& data)` | Adds a UI component |
| `getUIComponent(const std::string& ns, const std::string& uid)` | Gets a specific UI component |
| `updateUIComponent(const std::string& ns, const std::string& uid, const json& data)` | Updates a UI component |
| `deleteUIComponent(const std::string& ns, const std::string& uid)` | Deletes a UI component |
| `getUITiles()` | Gets all registered UI tiles |

---

### `openhab::UUID`

#### Constructor

```cpp
openhab::UUID uuid(client);
```

#### Methods

| Method | Description |
|---|---|
| `getUUID()` | Gets the UUID of the openHAB instance |

```cpp
json id = uuid.getUUID();
std::cout << id.get<std::string>() << std::endl;
```

---

### `openhab::Voice`

Provides methods to interact with the openHAB voice system.

#### Constructor

```cpp
openhab::Voice voice(client);
```

#### Methods

| Method | Description |
|---|---|
| `getDefaultVoice()` | Gets the default voice |
| `getVoices()` | Gets all available voices |
| `getInterpreters(const std::string& lang = "")` | Gets all human language interpreters |
| `getInterpreter(const std::string& id, const std::string& lang = "")` | Gets a specific interpreter |
| `interpretText(const std::string& text, const std::string& lang = "")` | Sends text to the default interpreter |
| `interpretTextBatch(const std::string& text, const std::string& ids, const std::string& lang = "")` | Sends text to multiple interpreters (comma-separated IDs) |
| `startDialog(const std::string& sourceId, const std::string& ksId = "", const std::string& sttId = "", const std::string& ttsId = "", const std::string& voiceId = "", const std::string& hliIds = "", const std::string& sinkId = "", const std::string& keyword = "", const std::string& listeningItem = "")` | Starts dialog processing |
| `stopDialog(const std::string& sourceId)` | Stops dialog processing |
| `listenAndAnswer(const std::string& sourceId, const std::string& sttId, const std::string& ttsId, const std::string& voiceId, const std::string& hliIds = "", const std::string& sinkId = "", const std::string& listeningItem = "")` | Single listen-and-answer dialog |
| `sayText(const std::string& text, const std::string& voiceId, const std::string& sinkId, const std::string& volume = "100")` | Speaks text aloud |

```cpp
voice.sayText("Hello from openHAB!", "voicerss:en-us", "javasound:sink:default");

voice.startDialog("javasound:source:microphone",
    "", "googlestt", "googletts", "google:en-US:en-US-Wavenet-A");
```

---

## C++ vs. Python — Key Differences

| Topic | C++ | Python |
|---|---|---|
| Distribution | Source + CMake build | PyPI (`pip install`) |
| Dependency management | CMake / vcpkg / apt / brew | pip |
| Include | `#include <openhab/openhab.h>` | `from openhab import Items` |
| Namespace | `openhab::` or `using namespace openhab;` | module-level import |
| Return type | `nlohmann::json` (structured data) | `dict`, `list`, or `str` |
| JSON access | `item["state"].get<std::string>()` | `item["state"]` |
| Error handling | `openhab::OpenHABException` (inherits `std::runtime_error`) | `requests.exceptions.*` |
| Async | Not built-in — use `std::thread` for SSE | `AsyncOpenHABClient` + `aiohttp` |
| SSE | `SSEConnection::forEach(callback)` + `cancel()` | `response.iter_lines()` |
| Memory | Stack-allocated or RAII — no GC | GC-managed |
| Optional params | Empty string `""` = not sent | `None` / default value |
| HTTP DELETE | `del(...)` (avoids C++ keyword conflict) | `delete(...)` |
| JSON body | `json` object passed directly | Python `dict` |
| Static library | `libopenhab_rest_client.a` | n/a |
| Shared library | `libopenhab_rest_client.so` / `.dll` | n/a |
| Platforms | Linux, macOS, Windows, ARM/Raspberry Pi | Cross-platform |
| Minimum standard | C++17 | Python 3.x |

---

## Contributing

Contributions are welcome! Please create an issue or pull request to suggest changes.

### How to contribute:
1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add your feature description"
   ```
4. Push to the branch:
   ```bash
   git push origin feature/your-feature-name
   ```
5. Open a pull request.

Please ensure your code compiles with C++17, builds cleanly with CMake, and follows the existing style (snake_case method names, `const std::string&` for string parameters, `""` for optional params).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
