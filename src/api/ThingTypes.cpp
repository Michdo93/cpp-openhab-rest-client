// Generated from ThingTypes.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V ThingTypes_getThingTypes(OpenHABClient& C, py::V v_bindingID, py::V v_language);
static py::V ThingTypes_getThingType(OpenHABClient& C, py::V v_thingTypeUID, py::V v_language);

static py::V ThingTypes_getThingTypes(OpenHABClient& C, py::V v_bindingID, py::V v_language) {
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
        v_response = py::http(C, "get", py::s("/thing-types"), v_headers, py::V(), (py::truthy(v_bindingID) ? py::V(py::dict({{"bindingId", v_bindingID}})) : py::V(py::dict())));
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

json ThingTypes::getThingTypes(const std::optional<std::string>& bindingID, const std::optional<std::string>& language) {
    return py::finish([&] { return ThingTypes_getThingTypes(*client_, py::arg(bindingID), py::arg(language)); });
}

json ThingTypes::getThingTypes(const GetThingTypesArgs& a) {
    return getThingTypes(a.bindingID, a.language);
}

static py::V ThingTypes_getThingType(OpenHABClient& C, py::V v_thingTypeUID, py::V v_language) {
    (void)C;
    (void)v_thingTypeUID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/thing-types/"), v_thingTypeUID}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("No Content.")}});
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
        return py::dict({{"error", py::s("No Content.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json ThingTypes::getThingType(const std::string& thingTypeUID, const std::optional<std::string>& language) {
    return py::finish([&] { return ThingTypes_getThingType(*client_, py::arg(thingTypeUID), py::arg(language)); });
}

json ThingTypes::getThingType(const std::string& thingTypeUID, const GetThingTypeArgs& a) {
    return getThingType(thingTypeUID, a.language);
}

}  // namespace openhab
