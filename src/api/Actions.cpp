// Generated from Actions.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Actions_getActions(OpenHABClient& C, py::V v_thingUID, py::V v_language);
static py::V Actions_executeAction(OpenHABClient& C, py::V v_thingUID, py::V v_actionUID, py::V v_actionInputs, py::V v_language);

static py::V Actions_getActions(OpenHABClient& C, py::V v_thingUID, py::V v_language) {
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
        v_response = py::http(C, "get", py::cat({py::s("/actions/"), v_thingUID}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(204)))) {
            return py::dict({{"error", py::s("No actions found.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::cat({py::s("Thing not found: "), v_thingUID})}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(204)))) {
        return py::dict({{"error", py::s("No actions found.")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::cat({py::s("Thing not found: "), v_thingUID})}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Actions::getActions(const std::string& thingUID, const std::optional<std::string>& language) {
    return py::finish([&] { return Actions_getActions(*client_, py::arg(thingUID), py::arg(language)); });
}

json Actions::getActions(const std::string& thingUID, const GetActionsArgs& a) {
    return getActions(thingUID, a.language);
}

static py::V Actions_executeAction(OpenHABClient& C, py::V v_thingUID, py::V v_actionUID, py::V v_actionInputs, py::V v_language) {
    (void)C;
    (void)v_thingUID;
    (void)v_actionUID;
    (void)v_actionInputs;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "post", py::cat({py::s("/actions/"), v_thingUID, py::s("/"), v_actionUID}), v_headers, py::dumps(v_actionInputs), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Action not found.")}});
        } else if (py::eq(v_status_code, py::V(json(500)))) {
            return py::dict({{"error", py::s("Creation of action handler or execution failed.")}});
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
        return py::dict({{"error", py::s("Action not found.")}});
    } else if (py::eq(v_status_code, py::V(json(500)))) {
        return py::dict({{"error", py::s("Creation of action handler or execution failed.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Actions::executeAction(const std::string& thingUID, const std::string& actionUID, const json& actionInputs, const std::optional<std::string>& language) {
    return py::finish([&] { return Actions_executeAction(*client_, py::arg(thingUID), py::arg(actionUID), py::arg(actionInputs), py::arg(language)); });
}

json Actions::executeAction(const std::string& thingUID, const std::string& actionUID, const json& actionInputs, const ExecuteActionArgs& a) {
    return executeAction(thingUID, actionUID, actionInputs, a.language);
}

}  // namespace openhab
