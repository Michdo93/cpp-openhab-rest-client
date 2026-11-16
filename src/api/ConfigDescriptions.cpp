// Generated from ConfigDescriptions.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V ConfigDescriptions_getConfigDescriptions(OpenHABClient& C, py::V v_scheme, py::V v_language);
static py::V ConfigDescriptions_getConfigDescription(OpenHABClient& C, py::V v_uri, py::V v_language);

static py::V ConfigDescriptions_getConfigDescriptions(OpenHABClient& C, py::V v_scheme, py::V v_language) {
    (void)C;
    (void)v_scheme;
    (void)v_language;
    py::V v_headers;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    v_params = py::dict();
    if (py::truthy(v_scheme)) {
        py::set(v_params, py::s("scheme"), v_scheme);
    }
    try {
        v_response = py::http(C, "get", py::s("/config-descriptions"), v_headers, py::V(), v_params);
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

json ConfigDescriptions::getConfigDescriptions(const std::optional<std::string>& scheme, const std::optional<std::string>& language) {
    return py::finish([&] { return ConfigDescriptions_getConfigDescriptions(*client_, py::arg(scheme), py::arg(language)); });
}

json ConfigDescriptions::getConfigDescriptions(const GetConfigDescriptionsArgs& a) {
    return getConfigDescriptions(a.scheme, a.language);
}

static py::V ConfigDescriptions_getConfigDescription(OpenHABClient& C, py::V v_uri, py::V v_language) {
    (void)C;
    (void)v_uri;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/config-descriptions/"), v_uri}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Invalid URI syntax.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Not found.")}});
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
        return py::dict({{"error", py::s("Not found.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Invalid URI syntax.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json ConfigDescriptions::getConfigDescription(const std::string& uri, const std::optional<std::string>& language) {
    return py::finish([&] { return ConfigDescriptions_getConfigDescription(*client_, py::arg(uri), py::arg(language)); });
}

json ConfigDescriptions::getConfigDescription(const std::string& uri, const GetConfigDescriptionArgs& a) {
    return getConfigDescription(uri, a.language);
}

}  // namespace openhab
