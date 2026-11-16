// C++20: optional arguments with designated initializers – compile test plus a
// check that the structs carry the defaults of the Python library.
#include <openhab/openhab.hpp>

#include <iostream>

int main() {
    openhab::Items::GetItemsArgs a{.tags = "Light", .fields = "name,state"};
    openhab::Things::GetThingsArgs t{.summary = true};
    openhab::ClientOptions o{.token = "oh.x", .timeout = 2};
    bool ok = a.metadata == ".*" && !a.recursive && a.tags == "Light" && !a.language &&
              t.summary && o.token == "oh.x" && o.verify;
    // only compiled: the calls with designated initializers
    if (false) {
        openhab::OpenHABClient c("http://127.0.0.1:1", {.token = "x", .timeout = 1});
        openhab::Items(c).getItems({.tags = "Light"});
        openhab::Items(c).getItem("X", {.metadata = "semantics"});
    }
    std::cout << (ok ? "ok" : "defaults wrong") << "\n";
    return ok ? 0 : 1;
}
