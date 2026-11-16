// Generated from ModuleTypes.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V ModuleTypes_getModuleTypes(OpenHABClient& C, py::V v_tags, py::V v_typeFilter, py::V v_language);
static py::V ModuleTypes_getModuleType(OpenHABClient& C, py::V v_moduleTypeUID, py::V v_language);

static py::V ModuleTypes_getModuleTypes(OpenHABClient& C, py::V v_tags, py::V v_typeFilter, py::V v_language) {
    (void)C;
    (void)v_tags;
    (void)v_typeFilter;
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
    if (py::truthy(v_tags)) {
        py::set(v_params, py::s("tags"), v_tags);
    }
    if (py::truthy(v_typeFilter)) {
        py::set(v_params, py::s("type"), v_typeFilter);
    }
    try {
        v_response = py::http(C, "get", py::s("/module-types"), v_headers, py::V(), v_params);
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

json ModuleTypes::getModuleTypes(const std::optional<std::string>& tags, const std::optional<std::string>& typeFilter, const std::optional<std::string>& language) {
    return py::finish([&] { return ModuleTypes_getModuleTypes(*client_, py::arg(tags), py::arg(typeFilter), py::arg(language)); });
}

json ModuleTypes::getModuleTypes(const GetModuleTypesArgs& a) {
    return getModuleTypes(a.tags, a.typeFilter, a.language);
}

static py::V ModuleTypes_getModuleType(OpenHABClient& C, py::V v_moduleTypeUID, py::V v_language) {
    (void)C;
    (void)v_moduleTypeUID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/module-types/"), v_moduleTypeUID}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Module Type corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Module Type corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json ModuleTypes::getModuleType(const std::string& moduleTypeUID, const std::optional<std::string>& language) {
    return py::finish([&] { return ModuleTypes_getModuleType(*client_, py::arg(moduleTypeUID), py::arg(language)); });
}

json ModuleTypes::getModuleType(const std::string& moduleTypeUID, const GetModuleTypeArgs& a) {
    return getModuleType(moduleTypeUID, a.language);
}

}  // namespace openhab
