# cpp-openhab-rest-client 1.0.0 – findings and what 2.0.0 changes

Checked on 16 November 2026 against openHAB 5.2.3 and python-openhab-rest-client 21.4.1
(the reference of the library family).

## Build and API

| Finding | 1.0.0 | 2.0.0 |
|---|---|---|
| Classes without implementation | `API.h` declares 33 classes with 171 methods, `src/` implements only Items, Things, Rules, Events and Actions – every other call ends in a linker error (`undefined reference to openhab::Persistence::…`) | all 33 classes, 178 methods, generated from the Python library (`tools/py2cpp.py`) |
| Parameters | own order and names (`getItems(type, tags, metadata, recursive, fields, staticOnly, language)`, `getItem(name, metadata, recursive, lang)`, …), several Python parameters missing (`parents`, `source`, …) | Python order, names and defaults; optional parameters also as argument struct (`GetItemsArgs`, C++20: `getItems({.tags = "Light"})`) |
| Results | raw `HttpResponse`/`json`, empty successes `{"status": 200}` | same results as Python: JSON, text as string, `{"message": "OK"}`, `{"error": "…"}` with the messages of the Python library |
| Errors | `OpenHABException` thrown for every HTTP error ≥ 400 – a missing item ends the program unless every call is wrapped in try/catch | `{"error": "Item not found."}` etc.; nothing is thrown |
| Responses with `Location` header | returned before the status check – a 4xx with `Location` counts as success | status is checked first |
| Key order | `nlohmann::json` sorts keys (query parameters and bodies differ from Python) | `nlohmann::ordered_json` keeps the order like Python dicts |
| Header/library names | `openhab/openhab.h`, `libopenhab_rest_client`, CMake package `OpenHABRestClient` – the same names as c-openhab-rest-client, both libraries cannot be installed side by side | `openhab/openhab.hpp`, `libopenhab_rest_client_cpp`, `find_package(OpenHABRestClientCpp)`, target `openhab::rest_client_cpp`, pkg-config `openhab_rest_client_cpp` |

## Requests

| Finding | 1.0.0 | 2.0.0 |
|---|---|---|
| Item names, UIDs in paths | not encoded (`"/items/" + name`); `#` in channel and action UIDs starts a URL fragment | encoded like Python (`quote`), `#` → `%23` |
| Topics of event streams | not encoded (`?topics=openhab/items/*/statechanged` with raw `*` and `,`) | encoded |
| Timeout | fixed 10 s | `timeout` argument / `ClientOptions::timeout` like Python |
| Persistence | not implemented (state in the body would be wrong anyway – openHAB expects it in the query) | `storeItemData` sends `state` as query parameter, service ID via `serviceId` |

## Event streams

| Finding | 1.0.0 | 2.0.0 |
|---|---|---|
| TLS | `CURLOPT_SSL_VERIFYPEER = 0` for every stream – certificates are never checked | verification on, `verify = false` only on request |
| HTTP status | not checked – a 401/404 stream silently delivers nothing | stream carries the error (`isError()`, `error()`), messages as in Python (`"Topic is empty or contains invalid characters."`) |
| `ItemEvents::ItemEvent()` | topic `openhab/items` – no event matches | `openhab/items/*` |
| `cancel()` | only takes effect when the next data arrives (up to the next ALIVE message) | `interrupt()` wakes up a waiting call at once, also from another thread or a signal handler |
| Reading | blocking callback only, `data:` lines only with a following space, payload as raw string | `nextEvent(timeoutMs)` with time limit, range-for, payload decoded (JSON in JSON), ALIVE messages on request |

## Differential test

79 calls (items, metadata, tags, groups, links, things, rules, persistence, transformations,
sitemaps, errors) with python-openhab-rest-client 21.4.1 and cpp-openhab-rest-client 2.0.0
against the same openHAB 5.2.3: **0 differences** (time stamps, UUIDs and memory values
normalised). Unit tests (local HTTP server): 39 checks; integration tests: 12 checks; valgrind
without definite leaks.
