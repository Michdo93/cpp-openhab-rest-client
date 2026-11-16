// Generated from Services.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Services_getServices(OpenHABClient& C, py::V v_language);
static py::V Services_getService(OpenHABClient& C, py::V v_serviceID, py::V v_language);
static py::V Services_getServiceConfig(OpenHABClient& C, py::V v_serviceID);
static py::V Services_updateServiceConfig(OpenHABClient& C, py::V v_serviceID, py::V v_configData, py::V v_language);
static py::V Services_deleteServiceConfig(OpenHABClient& C, py::V v_serviceID);
static py::V Services_getServiceContexts(OpenHABClient& C, py::V v_serviceID, py::V v_language);

static py::V Services_getServices(OpenHABClient& C, py::V v_language) {
    (void)C;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::s("/services"), v_headers, py::V(), py::V());
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

json Services::getServices(const std::optional<std::string>& language) {
    return py::finish([&] { return Services_getServices(*client_, py::arg(language)); });
}

json Services::getServices(const GetServicesArgs& a) {
    return getServices(a.language);
}

static py::V Services_getService(OpenHABClient& C, py::V v_serviceID, py::V v_language) {
    (void)C;
    (void)v_serviceID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/services/"), v_serviceID}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
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
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Services::getService(const std::string& serviceID, const std::optional<std::string>& language) {
    return py::finish([&] { return Services_getService(*client_, py::arg(serviceID), py::arg(language)); });
}

json Services::getService(const std::string& serviceID, const GetServiceArgs& a) {
    return getService(serviceID, a.language);
}

static py::V Services_getServiceConfig(OpenHABClient& C, py::V v_serviceID) {
    (void)C;
    (void)v_serviceID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/services/"), v_serviceID, py::s("/config")}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(500)))) {
            return py::dict({{"error", py::s("Configuration can not be read due to internal error.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(500)))) {
        return py::dict({{"error", py::s("Configuration can not be read due to internal error.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Services::getServiceConfig(const std::string& serviceID) {
    return py::finish([&] { return Services_getServiceConfig(*client_, py::arg(serviceID)); });
}

static py::V Services_updateServiceConfig(OpenHABClient& C, py::V v_serviceID, py::V v_configData, py::V v_language) {
    (void)C;
    (void)v_serviceID;
    (void)v_configData;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "put", py::cat({py::s("/services/"), v_serviceID, py::s("/config")}), v_headers, py::dumps(v_configData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(500)))) {
            return py::dict({{"error", py::s("Configuration can not be updated due to internal error.")}});
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
        return py::dict({{"message", py::s("OK, no old configuration.")}});
    } else if (py::eq(v_status_code, py::V(json(500)))) {
        return py::dict({{"error", py::s("Configuration can not be updated due to internal error.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Services::updateServiceConfig(const std::string& serviceID, const json& configData, const std::optional<std::string>& language) {
    return py::finish([&] { return Services_updateServiceConfig(*client_, py::arg(serviceID), py::arg(configData), py::arg(language)); });
}

json Services::updateServiceConfig(const std::string& serviceID, const json& configData, const UpdateServiceConfigArgs& a) {
    return updateServiceConfig(serviceID, configData, a.language);
}

static py::V Services_deleteServiceConfig(OpenHABClient& C, py::V v_serviceID) {
    (void)C;
    (void)v_serviceID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/services/"), v_serviceID, py::s("/config")}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(500)))) {
            return py::dict({{"error", py::s("Configuration can not be updated due to internal error.")}});
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
        return py::dict({{"message", py::s("OK, no old configuration.")}});
    } else if (py::eq(v_status_code, py::V(json(500)))) {
        return py::dict({{"error", py::s("Configuration can not be updated due to internal error.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Services::deleteServiceConfig(const std::string& serviceID) {
    return py::finish([&] { return Services_deleteServiceConfig(*client_, py::arg(serviceID)); });
}

static py::V Services_getServiceContexts(OpenHABClient& C, py::V v_serviceID, py::V v_language) {
    (void)C;
    (void)v_serviceID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/services/"), v_serviceID, py::s("/contexts")}), v_headers, py::V(), py::V());
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

json Services::getServiceContexts(const std::string& serviceID, const std::optional<std::string>& language) {
    return py::finish([&] { return Services_getServiceContexts(*client_, py::arg(serviceID), py::arg(language)); });
}

json Services::getServiceContexts(const std::string& serviceID, const GetServiceContextsArgs& a) {
    return getServiceContexts(serviceID, a.language);
}

}  // namespace openhab
