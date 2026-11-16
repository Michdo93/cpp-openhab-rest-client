// Links against the installed library; no openHAB needed.
#include <openhab/openhab.hpp>

#include <iostream>

int main() {
    openhab::OpenHABClient client("http://127.0.0.1:1", openhab::ClientOptions{});
    openhab::json r = openhab::Items(client).getItemState("Test");
    std::cout << "isLoggedIn=" << client.isLoggedIn() << " error=" << openhab::isError(r)
              << "\n";
    return !client.isLoggedIn() && openhab::isError(r) ? 0 : 1;
}
