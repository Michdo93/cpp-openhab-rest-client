// Generated from Inbox.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Inbox_getDiscoveredThings(OpenHABClient& C, py::V v_includeIgnored);
static py::V Inbox_removeDiscoveryResult(OpenHABClient& C, py::V v_thingUID);
static py::V Inbox_approveDiscoveryResult(OpenHABClient& C, py::V v_thingUID, py::V v_thingLabel, py::V v_newThingID, py::V v_language);
static py::V Inbox_ignoreDiscoveryResult(OpenHABClient& C, py::V v_thingUID);
static py::V Inbox_unignoreDiscoveryResult(OpenHABClient& C, py::V v_thingUID);

static py::V Inbox_getDiscoveredThings(OpenHABClient& C, py::V v_includeIgnored) {
    (void)C;
    (void)v_includeIgnored;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/inbox"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::dict({{"includeIgnored", py::lower(py::str(v_includeIgnored))}}));
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

json Inbox::getDiscoveredThings(bool includeIgnored) {
    return py::finish([&] { return Inbox_getDiscoveredThings(*client_, py::arg(includeIgnored)); });
}

json Inbox::getDiscoveredThings(const GetDiscoveredThingsArgs& a) {
    return getDiscoveredThings(a.includeIgnored);
}

static py::V Inbox_removeDiscoveryResult(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/inbox/"), v_thingUID}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Discovery result not found in the inbox.")}});
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
        return py::dict({{"error", py::s("Discovery result not found in the inbox.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Inbox::removeDiscoveryResult(const std::string& thingUID) {
    return py::finish([&] { return Inbox_removeDiscoveryResult(*client_, py::arg(thingUID)); });
}

static py::V Inbox_approveDiscoveryResult(OpenHABClient& C, py::V v_thingUID, py::V v_thingLabel, py::V v_newThingID, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_thingLabel;
    (void)v_newThingID;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::cat({py::s("/inbox/"), v_thingUID, py::s("/approve")}), (py::truthy(v_language) ? py::V(py::dict({{"Accept-Language", v_language}, {"Content-Type", py::s("text/plain")}})) : py::V(py::dict({{"Content-Type", py::s("text/plain")}}))), v_thingLabel, (py::truthy(v_newThingID) ? py::V(py::dict({{"newThingId", v_newThingID}})) : py::V(py::dict())));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Invalid new thing ID.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Thing unable to be approved.")}});
        } else if (py::eq(v_status_code, py::V(json(409)))) {
            return py::dict({{"error", py::s("No binding found that supports this thing.")}});
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
        return py::dict({{"error", py::s("Invalid new thing ID.")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Thing unable to be approved.")}});
    } else if (py::eq(v_status_code, py::V(json(409)))) {
        return py::dict({{"error", py::s("No binding found that supports this thing.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Inbox::approveDiscoveryResult(const std::string& thingUID, const std::string& thingLabel, const std::optional<std::string>& newThingID, const std::optional<std::string>& language) {
    return py::finish([&] { return Inbox_approveDiscoveryResult(*client_, py::arg(thingUID), py::arg(thingLabel), py::arg(newThingID), py::arg(language)); });
}

json Inbox::approveDiscoveryResult(const std::string& thingUID, const std::string& thingLabel, const ApproveDiscoveryResultArgs& a) {
    return approveDiscoveryResult(thingUID, thingLabel, a.newThingID, a.language);
}

static py::V Inbox_ignoreDiscoveryResult(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::cat({py::s("/inbox/"), v_thingUID, py::s("/ignore")}), py::V(), py::V(), py::V());
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

json Inbox::ignoreDiscoveryResult(const std::string& thingUID) {
    return py::finish([&] { return Inbox_ignoreDiscoveryResult(*client_, py::arg(thingUID)); });
}

static py::V Inbox_unignoreDiscoveryResult(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::cat({py::s("/inbox/"), v_thingUID, py::s("/unignore")}), py::V(), py::V(), py::V());
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

json Inbox::unignoreDiscoveryResult(const std::string& thingUID) {
    return py::finish([&] { return Inbox_unignoreDiscoveryResult(*client_, py::arg(thingUID)); });
}

}  // namespace openhab
