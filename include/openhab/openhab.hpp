#pragma once

/**
 * cpp-openhab-rest-client 2.0.0 – one include for the whole library.
 *
 *   #include <openhab/openhab.hpp>
 *
 *   openhab::OpenHABClient client("http://127.0.0.1:8080", std::nullopt, std::nullopt, token);
 *   openhab::Items items(client);
 *   openhab::json all = items.getItems();
 *   items.sendCommand("Wohnzimmer_Licht", "ON");
 *
 * Same classes, methods, parameters and results as python-openhab-rest-client.
 */

#include "OpenHABClient.hpp"
#include "API.hpp"
