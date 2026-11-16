// Generated from ProfileTypes.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V ProfileTypes_getProfileTypes(OpenHABClient& C, py::V v_channelTypeUID, py::V v_itemType, py::V v_language);

static py::V ProfileTypes_getProfileTypes(OpenHABClient& C, py::V v_channelTypeUID, py::V v_itemType, py::V v_language) {
    (void)C;
    (void)v_channelTypeUID;
    (void)v_itemType;
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
    if (py::truthy(v_channelTypeUID)) {
        py::set(v_params, py::s("channelTypeUID"), v_channelTypeUID);
    }
    if (py::truthy(v_itemType)) {
        py::set(v_params, py::s("itemType"), v_itemType);
    }
    try {
        v_response = py::http(C, "get", py::s("/profile-types"), v_headers, py::V(), v_params);
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

json ProfileTypes::getProfileTypes(const std::optional<std::string>& channelTypeUID, const std::optional<std::string>& itemType, const std::optional<std::string>& language) {
    return py::finish([&] { return ProfileTypes_getProfileTypes(*client_, py::arg(channelTypeUID), py::arg(itemType), py::arg(language)); });
}

json ProfileTypes::getProfileTypes(const GetProfileTypesArgs& a) {
    return getProfileTypes(a.channelTypeUID, a.itemType, a.language);
}

}  // namespace openhab
