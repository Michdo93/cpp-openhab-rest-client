// Generated from Discovery.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Discovery_getDiscoveryBindings(OpenHABClient& C);
static py::V Discovery_getBindingInfo(OpenHABClient& C, py::V v_bindingID, py::V v_language);
static py::V Discovery_startBindingScan(OpenHABClient& C, py::V v_bindingID, py::V v_input);

static py::V Discovery_getDiscoveryBindings(OpenHABClient& C) {
    (void)C;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/discovery"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json Discovery::getDiscoveryBindings() {
    return py::finish([&] { return Discovery_getDiscoveryBindings(*client_); });
}

static py::V Discovery_getBindingInfo(OpenHABClient& C, py::V v_bindingID, py::V v_language) {
    (void)C;
    (void)v_bindingID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/discovery/bindings/"), v_bindingID, py::s("/info")}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Discovery service not found.")}});
        } else if (!py::eq(v_status_code, py::V(json(200)))) {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return v_response;
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Discovery::getBindingInfo(const std::string& bindingID, const std::optional<std::string>& language) {
    return py::finish([&] { return Discovery_getBindingInfo(*client_, py::arg(bindingID), py::arg(language)); });
}

json Discovery::getBindingInfo(const std::string& bindingID, const GetBindingInfoArgs& a) {
    return getBindingInfo(bindingID, a.language);
}

static py::V Discovery_startBindingScan(OpenHABClient& C, py::V v_bindingID, py::V v_input) {
    (void)C;
    (void)v_bindingID;
    (void)v_input;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_params = py::dict({{"input", v_input}});
    try {
        v_response = py::http(C, "post", py::cat({py::s("/discovery/bindings/"), v_bindingID, py::s("/scan")}), py::dict({{"Accept", py::s("text/plain")}}), py::V(), v_params);
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

json Discovery::startBindingScan(const std::string& bindingID, const std::optional<std::string>& input) {
    return py::finish([&] { return Discovery_startBindingScan(*client_, py::arg(bindingID), py::arg(input)); });
}

json Discovery::startBindingScan(const std::string& bindingID, const StartBindingScanArgs& a) {
    return startBindingScan(bindingID, a.input);
}

}  // namespace openhab
