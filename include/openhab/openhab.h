#pragma once

/**
 * openhab-rest-client — C++ Library
 *
 * Single include for all openHAB REST API classes.
 *
 *   #include <openhab/openhab.h>
 *
 *   openhab::OpenHABClient client("http://127.0.0.1:8080", "openhab", "habopen");
 *   openhab::Items items(client);
 *   auto allItems = items.getItems();
 *   items.sendCommand("LivingRoomLight", "ON");
 */

#include "OpenHABClient.h"
#include "API.h"
