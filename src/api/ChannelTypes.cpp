// Generated from ChannelTypes.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V ChannelTypes_getChannelTypes(OpenHABClient& C, py::V v_prefixes, py::V v_language);
static py::V ChannelTypes_getChannelType(OpenHABClient& C, py::V v_channelTypeUID, py::V v_language);
static py::V ChannelTypes_getLinkableItemTypes(OpenHABClient& C, py::V v_channelTypeUID);

static py::V ChannelTypes_getChannelTypes(OpenHABClient& C, py::V v_prefixes, py::V v_language) {
    (void)C;
    (void)v_prefixes;
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
    if (py::truthy(v_prefixes)) {
        py::set(v_params, py::s("prefixes"), v_prefixes);
    }
    try {
        v_response = py::http(C, "get", py::s("/channel-types"), v_headers, py::V(), v_params);
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

json ChannelTypes::getChannelTypes(const std::optional<std::string>& prefixes, const std::optional<std::string>& language) {
    return py::finish([&] { return ChannelTypes_getChannelTypes(*client_, py::arg(prefixes), py::arg(language)); });
}

json ChannelTypes::getChannelTypes(const GetChannelTypesArgs& a) {
    return getChannelTypes(a.prefixes, a.language);
}

static py::V ChannelTypes_getChannelType(OpenHABClient& C, py::V v_channelTypeUID, py::V v_language) {
    (void)C;
    (void)v_channelTypeUID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/channel-types/"), v_channelTypeUID}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Channel type with provided channelTypeUID does not exist.")}});
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
        return py::dict({{"error", py::s("Channel type with provided channelTypeUID does not exist.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json ChannelTypes::getChannelType(const std::string& channelTypeUID, const std::optional<std::string>& language) {
    return py::finish([&] { return ChannelTypes_getChannelType(*client_, py::arg(channelTypeUID), py::arg(language)); });
}

json ChannelTypes::getChannelType(const std::string& channelTypeUID, const GetChannelTypeArgs& a) {
    return getChannelType(channelTypeUID, a.language);
}

static py::V ChannelTypes_getLinkableItemTypes(OpenHABClient& C, py::V v_channelTypeUID) {
    (void)C;
    (void)v_channelTypeUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/channel-types/"), v_channelTypeUID, py::s("/linkableItemTypes")}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(204)))) {
            return py::dict({{"error", py::s("No content: channel type has no linkable items or is no trigger channel.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Given channel type UID not found.")}});
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
        return py::dict({{"error", py::s("Given channel type UID not found.")}});
    } else if (py::eq(v_status_code, py::V(json(204)))) {
        return py::dict({{"error", py::s("No content: channel type has no linkable items or is no trigger channel.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json ChannelTypes::getLinkableItemTypes(const std::string& channelTypeUID) {
    return py::finish([&] { return ChannelTypes_getLinkableItemTypes(*client_, py::arg(channelTypeUID)); });
}

}  // namespace openhab
