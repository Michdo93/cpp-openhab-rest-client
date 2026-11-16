// Generated from Addons.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Addons_getAddons(OpenHABClient& C, py::V v_serviceID, py::V v_language);
static py::V Addons_getAddon(OpenHABClient& C, py::V v_addonID, py::V v_serviceID, py::V v_language);
static py::V Addons_getAddonConfig(OpenHABClient& C, py::V v_addonID, py::V v_serviceID);
static py::V Addons_updateAddonConfig(OpenHABClient& C, py::V v_addonID, py::V v_configData, py::V v_serviceID);
static py::V Addons_installAddon(OpenHABClient& C, py::V v_addonID, py::V v_serviceID);
static py::V Addons_uninstallAddon(OpenHABClient& C, py::V v_addonID, py::V v_serviceID);
static py::V Addons_getAddonServices(OpenHABClient& C, py::V v_language);
static py::V Addons_getAddonSuggestions(OpenHABClient& C, py::V v_language);
static py::V Addons_getAddonTypes(OpenHABClient& C, py::V v_serviceID, py::V v_language);
static py::V Addons_installAddonFromUrl(OpenHABClient& C, py::V v_url);

static py::V Addons_getAddons(OpenHABClient& C, py::V v_serviceID, py::V v_language) {
    (void)C;
    (void)v_serviceID;
    (void)v_language;
    py::V v_headers;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_params = (py::truthy(v_serviceID) ? py::V(py::dict({{"serviceId", v_serviceID}})) : py::V(py::dict()));
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::s("/addons"), v_headers, py::V(), v_params);
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Service not found.")}});
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
        return py::dict({{"error", py::s("Service not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Addons::getAddons(const std::optional<std::string>& serviceID, const std::optional<std::string>& language) {
    return py::finish([&] { return Addons_getAddons(*client_, py::arg(serviceID), py::arg(language)); });
}

json Addons::getAddons(const GetAddonsArgs& a) {
    return getAddons(a.serviceID, a.language);
}

static py::V Addons_getAddon(OpenHABClient& C, py::V v_addonID, py::V v_serviceID, py::V v_language) {
    (void)C;
    (void)v_addonID;
    (void)v_serviceID;
    (void)v_language;
    py::V v_headers;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_params = (py::truthy(v_serviceID) ? py::V(py::dict({{"serviceId", v_serviceID}})) : py::V(py::dict()));
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/addons/"), v_addonID}), v_headers, py::V(), v_params);
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

json Addons::getAddon(const std::string& addonID, const std::optional<std::string>& serviceID, const std::optional<std::string>& language) {
    return py::finish([&] { return Addons_getAddon(*client_, py::arg(addonID), py::arg(serviceID), py::arg(language)); });
}

json Addons::getAddon(const std::string& addonID, const GetAddonArgs& a) {
    return getAddon(addonID, a.serviceID, a.language);
}

static py::V Addons_getAddonConfig(OpenHABClient& C, py::V v_addonID, py::V v_serviceID) {
    (void)C;
    (void)v_addonID;
    (void)v_serviceID;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_params = (py::truthy(v_serviceID) ? py::V(py::dict({{"serviceId", v_serviceID}})) : py::V(py::dict()));
    try {
        v_response = py::http(C, "get", py::cat({py::s("/addons/"), v_addonID, py::s("/config")}), py::dict({{"Accept", py::s("application/json")}}), py::V(), v_params);
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
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Add-on does not exist.")}});
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
        return py::dict({{"error", py::s("Add-on does not exist.")}});
    } else if (py::eq(v_status_code, py::V(json(500)))) {
        return py::dict({{"error", py::s("Configuration can not be read due to internal error.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Addons::getAddonConfig(const std::string& addonID, const std::optional<std::string>& serviceID) {
    return py::finish([&] { return Addons_getAddonConfig(*client_, py::arg(addonID), py::arg(serviceID)); });
}

json Addons::getAddonConfig(const std::string& addonID, const GetAddonConfigArgs& a) {
    return getAddonConfig(addonID, a.serviceID);
}

static py::V Addons_updateAddonConfig(OpenHABClient& C, py::V v_addonID, py::V v_configData, py::V v_serviceID) {
    (void)C;
    (void)v_addonID;
    (void)v_configData;
    (void)v_serviceID;
    py::V v_data;
    py::V v_response;
    py::V v_status_code;
    v_data = py::copy(v_configData);
    try {
        v_response = py::http(C, "put", py::cat({py::s("/addons/"), v_addonID, py::s("/config")}), py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("application/json")}}), py::dumps(v_data), py::dict({{"serviceId", v_serviceID}}));
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
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Add-on does not exist.")}});
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
        return py::dict({{"error", py::s("Add-on does not exist.")}});
    } else if (py::eq(v_status_code, py::V(json(500)))) {
        return py::dict({{"error", py::s("Configuration can not be updated due to internal error.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Addons::updateAddonConfig(const std::string& addonID, const json& configData, const std::optional<std::string>& serviceID) {
    return py::finish([&] { return Addons_updateAddonConfig(*client_, py::arg(addonID), py::arg(configData), py::arg(serviceID)); });
}

json Addons::updateAddonConfig(const std::string& addonID, const json& configData, const UpdateAddonConfigArgs& a) {
    return updateAddonConfig(addonID, configData, a.serviceID);
}

static py::V Addons_installAddon(OpenHABClient& C, py::V v_addonID, py::V v_serviceID) {
    (void)C;
    (void)v_addonID;
    (void)v_serviceID;
    py::V v_data;
    py::V v_response;
    py::V v_status_code;
    v_data = (py::truthy(v_serviceID) ? py::V(py::dict({{"serviceId", v_serviceID}})) : py::V(py::dict()));
    try {
        v_response = py::http(C, "post", py::cat({py::s("/addons/"), v_addonID, py::s("/install")}), py::V(), py::V(), v_data);
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

json Addons::installAddon(const std::string& addonID, const std::optional<std::string>& serviceID) {
    return py::finish([&] { return Addons_installAddon(*client_, py::arg(addonID), py::arg(serviceID)); });
}

json Addons::installAddon(const std::string& addonID, const InstallAddonArgs& a) {
    return installAddon(addonID, a.serviceID);
}

static py::V Addons_uninstallAddon(OpenHABClient& C, py::V v_addonID, py::V v_serviceID) {
    (void)C;
    (void)v_addonID;
    (void)v_serviceID;
    py::V v_data;
    py::V v_response;
    py::V v_status_code;
    v_data = (py::truthy(v_serviceID) ? py::V(py::dict({{"serviceId", v_serviceID}})) : py::V(py::dict()));
    try {
        v_response = py::http(C, "post", py::cat({py::s("/addons/"), v_addonID, py::s("/uninstall")}), py::V(), py::V(), v_data);
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

json Addons::uninstallAddon(const std::string& addonID, const std::optional<std::string>& serviceID) {
    return py::finish([&] { return Addons_uninstallAddon(*client_, py::arg(addonID), py::arg(serviceID)); });
}

json Addons::uninstallAddon(const std::string& addonID, const UninstallAddonArgs& a) {
    return uninstallAddon(addonID, a.serviceID);
}

static py::V Addons_getAddonServices(OpenHABClient& C, py::V v_language) {
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
        v_response = py::http(C, "get", py::s("/addons/services"), v_headers, py::V(), py::V());
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

json Addons::getAddonServices(const std::optional<std::string>& language) {
    return py::finish([&] { return Addons_getAddonServices(*client_, py::arg(language)); });
}

json Addons::getAddonServices(const GetAddonServicesArgs& a) {
    return getAddonServices(a.language);
}

static py::V Addons_getAddonSuggestions(OpenHABClient& C, py::V v_language) {
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
        v_response = py::http(C, "get", py::s("/addons/suggestions"), v_headers, py::V(), py::V());
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

json Addons::getAddonSuggestions(const std::optional<std::string>& language) {
    return py::finish([&] { return Addons_getAddonSuggestions(*client_, py::arg(language)); });
}

json Addons::getAddonSuggestions(const GetAddonSuggestionsArgs& a) {
    return getAddonSuggestions(a.language);
}

static py::V Addons_getAddonTypes(OpenHABClient& C, py::V v_serviceID, py::V v_language) {
    (void)C;
    (void)v_serviceID;
    (void)v_language;
    py::V v_headers;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_params = (py::truthy(v_serviceID) ? py::V(py::dict({{"serviceId", v_serviceID}})) : py::V(py::dict()));
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::s("/addons/types"), v_headers, py::V(), v_params);
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Service not found.")}});
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
        return py::dict({{"error", py::s("Service not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Addons::getAddonTypes(const std::optional<std::string>& serviceID, const std::optional<std::string>& language) {
    return py::finish([&] { return Addons_getAddonTypes(*client_, py::arg(serviceID), py::arg(language)); });
}

json Addons::getAddonTypes(const GetAddonTypesArgs& a) {
    return getAddonTypes(a.serviceID, a.language);
}

static py::V Addons_installAddonFromUrl(OpenHABClient& C, py::V v_url) {
    (void)C;
    (void)v_url;
    py::V v_encoded_url;
    py::V v_endpoint;
    py::V v_response;
    py::V v_status_code;
    v_encoded_url = py::quote(v_url, "");
    v_endpoint = py::cat({py::s("/addons/url/"), v_encoded_url, py::s("/install")});
    try {
        v_response = py::http(C, "post", v_endpoint, py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("The given URL is malformed or not valid.")}});
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
        return py::dict({{"error", py::s("The given URL is malformed or not valid.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Addons::installAddonFromUrl(const std::string& url) {
    return py::finish([&] { return Addons_installAddonFromUrl(*client_, py::arg(url)); });
}

}  // namespace openhab
