// Generated from Things.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Things_getThings(OpenHABClient& C, py::V v_summary, py::V v_staticDataOnly, py::V v_language);
static py::V Things_createThing(OpenHABClient& C, py::V v_thingData, py::V v_language);
static py::V Things_getThing(OpenHABClient& C, py::V v_thingUID, py::V v_language);
static py::V Things_updateThing(OpenHABClient& C, py::V v_thingUID, py::V v_thingData, py::V v_language);
static py::V Things_deleteThing(OpenHABClient& C, py::V v_thingUID, py::V v_force, py::V v_language);
static py::V Things_updateThingConfiguration(OpenHABClient& C, py::V v_thingUID, py::V v_configurationData, py::V v_language);
static py::V Things_getThingConfigStatus(OpenHABClient& C, py::V v_thingUID, py::V v_language);
static py::V Things_setThingStatus(OpenHABClient& C, py::V v_thingUID, py::V v_enabled, py::V v_language);
static py::V Things_enableThing(OpenHABClient& C, py::V v_thingUID);
static py::V Things_disableThing(OpenHABClient& C, py::V v_thingUID);
static py::V Things_updateThingFirmware(OpenHABClient& C, py::V v_thingUID, py::V v_firmwareVersion, py::V v_language);
static py::V Things_getThingFirmwareStatus(OpenHABClient& C, py::V v_thingUID, py::V v_language);
static py::V Things_getThingFirmwares(OpenHABClient& C, py::V v_thingUID, py::V v_language);
static py::V Things_getThingStatus(OpenHABClient& C, py::V v_thingUID, py::V v_language);

static py::V Things_getThings(OpenHABClient& C, py::V v_summary, py::V v_staticDataOnly, py::V v_language) {
    (void)C;
    (void)v_summary;
    (void)v_staticDataOnly;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::s("/things"), v_headers, py::V(), py::dict({{"summary", v_summary}, {"staticDataOnly", v_staticDataOnly}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (!py::eq(v_status_code, py::V(json(200)))) {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::getThings(bool summary, bool staticDataOnly, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_getThings(*client_, py::arg(summary), py::arg(staticDataOnly), py::arg(language)); });
}

json Things::getThings(const GetThingsArgs& a) {
    return getThings(a.summary, a.staticDataOnly, a.language);
}

static py::V Things_createThing(OpenHABClient& C, py::V v_thingData, py::V v_language) {
    (void)C;
    (void)v_thingData;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("*/*")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "post", py::s("/things"), v_headers, py::dumps(v_thingData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(409)))) {
            return py::dict({{"error", py::s("A thing with the same uid already exists.")}});
        } else if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("A uid must be provided, if no binding can create a thing of this type.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("A uid must be provided, if no binding can create a thing of this type.")}});
    } else if (py::eq(v_status_code, py::V(json(409)))) {
        return py::dict({{"error", py::s("A thing with the same uid already exists.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::createThing(const json& thingData, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_createThing(*client_, py::arg(thingData), py::arg(language)); });
}

json Things::createThing(const json& thingData, const CreateThingArgs& a) {
    return createThing(thingData, a.language);
}

static py::V Things_getThing(OpenHABClient& C, py::V v_thingUID, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/things/"), v_thingUID}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Thing not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("THing not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::getThing(const std::string& thingUID, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_getThing(*client_, py::arg(thingUID), py::arg(language)); });
}

json Things::getThing(const std::string& thingUID, const GetThingArgs& a) {
    return getThing(thingUID, a.language);
}

static py::V Things_updateThing(OpenHABClient& C, py::V v_thingUID, py::V v_thingData, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_thingData;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("*/*")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "put", py::cat({py::s("/things/"), v_thingUID}), v_headers, py::dumps(v_thingData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(409)))) {
            return py::dict({{"error", py::s("Thing could not be updated as it is not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Thing not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Thing not found.")}});
    } else if (py::eq(v_status_code, py::V(json(409)))) {
        return py::dict({{"error", py::s("Thing could not be updated as it is not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::updateThing(const std::string& thingUID, const json& thingData, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_updateThing(*client_, py::arg(thingUID), py::arg(thingData), py::arg(language)); });
}

json Things::updateThing(const std::string& thingUID, const json& thingData, const UpdateThingArgs& a) {
    return updateThing(thingUID, thingData, a.language);
}

static py::V Things_deleteThing(OpenHABClient& C, py::V v_thingUID, py::V v_force, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_force;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/things/"), v_thingUID}), (py::truthy(v_language) ? py::V(py::dict({{"Accept-Language", v_language}})) : py::V(py::dict())), py::V(), py::dict({{"force", v_force}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(409)))) {
            return py::dict({{"error", py::s("Thing could not be deleted because it's not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Thing not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK, was deleted.")}});
    } else if (py::eq(v_status_code, py::V(json(202)))) {
        return py::dict({{"message", py::s("ACCEPTED for asynchronous deletion.")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Thing not found.")}});
    } else if (py::eq(v_status_code, py::V(json(409)))) {
        return py::dict({{"error", py::s("Thing could not be deleted because it's not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::deleteThing(const std::string& thingUID, bool force, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_deleteThing(*client_, py::arg(thingUID), py::arg(force), py::arg(language)); });
}

json Things::deleteThing(const std::string& thingUID, const DeleteThingArgs& a) {
    return deleteThing(thingUID, a.force, a.language);
}

static py::V Things_updateThingConfiguration(OpenHABClient& C, py::V v_thingUID, py::V v_configurationData, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_configurationData;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("*/*")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "put", py::cat({py::s("/things/"), v_thingUID, py::s("/config")}), v_headers, py::dumps(v_configurationData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Configuration of the thing is not valid.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Thing not found.")}});
        } else if (py::eq(v_status_code, py::V(json(409)))) {
            return py::dict({{"error", py::s("Thing could not be updated as it is not editable.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Configuration of the thing is not valid.")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Thing not found.")}});
    } else if (py::eq(v_status_code, py::V(json(409)))) {
        return py::dict({{"error", py::s("Thing could not be updated as it is not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::updateThingConfiguration(const std::string& thingUID, const json& configurationData, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_updateThingConfiguration(*client_, py::arg(thingUID), py::arg(configurationData), py::arg(language)); });
}

json Things::updateThingConfiguration(const std::string& thingUID, const json& configurationData, const UpdateThingConfigurationArgs& a) {
    return updateThingConfiguration(thingUID, configurationData, a.language);
}

static py::V Things_getThingConfigStatus(OpenHABClient& C, py::V v_thingUID, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/things/"), v_thingUID, py::s("/config/status")}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Thing not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Thing not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::getThingConfigStatus(const std::string& thingUID, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_getThingConfigStatus(*client_, py::arg(thingUID), py::arg(language)); });
}

json Things::getThingConfigStatus(const std::string& thingUID, const GetThingConfigStatusArgs& a) {
    return getThingConfigStatus(thingUID, a.language);
}

static py::V Things_setThingStatus(OpenHABClient& C, py::V v_thingUID, py::V v_enabled, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_enabled;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("text/plain")}, {"Accept", py::s("*/*")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "put", py::cat({py::s("/things/"), v_thingUID, py::s("/enable")}), v_headers, (py::truthy(v_enabled) ? py::V(py::s("true")) : py::V(py::s("false"))), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Thing not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Thing not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::setThingStatus(const std::string& thingUID, bool enabled, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_setThingStatus(*client_, py::arg(thingUID), py::arg(enabled), py::arg(language)); });
}

json Things::setThingStatus(const std::string& thingUID, bool enabled, const SetThingStatusArgs& a) {
    return setThingStatus(thingUID, enabled, a.language);
}

static py::V Things_enableThing(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return Things_setThingStatus(C, v_thingUID, py::V(json(true)), py::V());
}

json Things::enableThing(const std::string& thingUID) {
    return py::finish([&] { return Things_enableThing(*client_, py::arg(thingUID)); });
}

static py::V Things_disableThing(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return Things_setThingStatus(C, v_thingUID, py::V(json(false)), py::V());
}

json Things::disableThing(const std::string& thingUID) {
    return py::finish([&] { return Things_disableThing(*client_, py::arg(thingUID)); });
}

static py::V Things_updateThingFirmware(OpenHABClient& C, py::V v_thingUID, py::V v_firmwareVersion, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_firmwareVersion;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/things/"), v_thingUID, py::s("/firmware/"), v_firmwareVersion}), (py::truthy(v_language) ? py::V(py::dict({{"Accept-Language", v_language}})) : py::V(py::dict())), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Firmware update preconditions not satisfied.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Thing not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Thing not found.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Firmware update preconditions not satisfied.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::updateThingFirmware(const std::string& thingUID, const std::string& firmwareVersion, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_updateThingFirmware(*client_, py::arg(thingUID), py::arg(firmwareVersion), py::arg(language)); });
}

json Things::updateThingFirmware(const std::string& thingUID, const std::string& firmwareVersion, const UpdateThingFirmwareArgs& a) {
    return updateThingFirmware(thingUID, firmwareVersion, a.language);
}

static py::V Things_getThingFirmwareStatus(OpenHABClient& C, py::V v_thingUID, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("*/*")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/things/"), v_thingUID, py::s("/firmware/status")}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (!py::eq(v_status_code, py::V(json(200)))) {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(204)))) {
        return py::dict({{"error", py::s("No firmware status provided by this Thing.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::getThingFirmwareStatus(const std::string& thingUID, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_getThingFirmwareStatus(*client_, py::arg(thingUID), py::arg(language)); });
}

json Things::getThingFirmwareStatus(const std::string& thingUID, const GetThingFirmwareStatusArgs& a) {
    return getThingFirmwareStatus(thingUID, a.language);
}

static py::V Things_getThingFirmwares(OpenHABClient& C, py::V v_thingUID, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/things/"), v_thingUID, py::s("/firmwares")}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (!py::eq(v_status_code, py::V(json(200)))) {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(204)))) {
        return py::dict({{"error", py::s("No firmwares found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::getThingFirmwares(const std::string& thingUID, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_getThingFirmwares(*client_, py::arg(thingUID), py::arg(language)); });
}

json Things::getThingFirmwares(const std::string& thingUID, const GetThingFirmwaresArgs& a) {
    return getThingFirmwares(thingUID, a.language);
}

static py::V Things_getThingStatus(OpenHABClient& C, py::V v_thingUID, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/things/"), v_thingUID, py::s("/status")}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Thing not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Thing not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Things::getThingStatus(const std::string& thingUID, const std::optional<std::string>& language) {
    return py::finish([&] { return Things_getThingStatus(*client_, py::arg(thingUID), py::arg(language)); });
}

json Things::getThingStatus(const std::string& thingUID, const GetThingStatusArgs& a) {
    return getThingStatus(thingUID, a.language);
}

}  // namespace openhab
