// Generated from Persistence.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Persistence_getServices(OpenHABClient& C, py::V v_language);
static py::V Persistence_getServiceConfiguration(OpenHABClient& C, py::V v_serviceID);
static py::V Persistence_setServiceConfiguration(OpenHABClient& C, py::V v_serviceID, py::V v_config);
static py::V Persistence_deleteServiceConfiguration(OpenHABClient& C, py::V v_serviceID);
static py::V Persistence_getItemsFromService(OpenHABClient& C, py::V v_serviceID, py::V v_itemName);
static py::V Persistence_getItemPersistenceData(OpenHABClient& C, py::V v_itemName, py::V v_serviceID, py::V v_startTime, py::V v_endTime, py::V v_page, py::V v_pageLength, py::V v_boundary, py::V v_itemState, py::V v_displayState, py::V v_language);
static py::V Persistence_storeItemData(OpenHABClient& C, py::V v_itemName, py::V v_time, py::V v_state, py::V v_serviceID);
static py::V Persistence_deleteItemData(OpenHABClient& C, py::V v_itemName, py::V v_startTime, py::V v_endTime, py::V v_serviceID);

static py::V Persistence_getServices(OpenHABClient& C, py::V v_language) {
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
        v_response = py::http(C, "get", py::s("/persistence"), v_headers, py::V(), py::V());
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

json Persistence::getServices(const std::optional<std::string>& language) {
    return py::finish([&] { return Persistence_getServices(*client_, py::arg(language)); });
}

json Persistence::getServices(const GetServicesArgs& a) {
    return getServices(a.language);
}

static py::V Persistence_getServiceConfiguration(OpenHABClient& C, py::V v_serviceID) {
    (void)C;
    (void)v_serviceID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/persistence/"), v_serviceID}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Service configuration not found.")}});
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
        return py::dict({{"error", py::s("Service configuration not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Persistence::getServiceConfiguration(const std::string& serviceID) {
    return py::finish([&] { return Persistence_getServiceConfiguration(*client_, py::arg(serviceID)); });
}

static py::V Persistence_setServiceConfiguration(OpenHABClient& C, py::V v_serviceID, py::V v_config) {
    (void)C;
    (void)v_serviceID;
    (void)v_config;
    py::V v_response;
    py::V v_status_code;
    try {
        py::set(v_config, py::s("serviceId"), v_serviceID);
        v_response = py::http(C, "put", py::cat({py::s("/persistence/"), v_serviceID}), py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("application/json")}}), py::dumps(v_config), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Payload invalid.")}});
        } else if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("PersistenceServiceConfiguration not editable.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(201)))) {
        return py::dict({{"message", py::s("PersistenceServiceConfiguration created.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Payload invalid.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("PersistenceServiceConfiguration not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Persistence::setServiceConfiguration(const std::string& serviceID, const json& config) {
    return py::finish([&] { return Persistence_setServiceConfiguration(*client_, py::arg(serviceID), py::arg(config)); });
}

static py::V Persistence_deleteServiceConfiguration(OpenHABClient& C, py::V v_serviceID) {
    (void)C;
    (void)v_serviceID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/persistence/"), v_serviceID}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Payload invalid.")}});
        } else if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("PersistenceServiceConfiguration not editable.")}});
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
        return py::dict({{"error", py::s("Payload invalid.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("PersistenceServiceConfiguration not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Persistence::deleteServiceConfiguration(const std::string& serviceID) {
    return py::finish([&] { return Persistence_deleteServiceConfiguration(*client_, py::arg(serviceID)); });
}

static py::V Persistence_getItemsFromService(OpenHABClient& C, py::V v_serviceID, py::V v_itemName) {
    (void)C;
    (void)v_serviceID;
    (void)v_itemName;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/persistence/items"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::dict({{"serviceId", v_serviceID}, {"itemName", v_itemName}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Unknown persistence service.")}});
        }
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("The persistence service does not provide item information.")}});
        }
        return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Persistence::getItemsFromService(const std::optional<std::string>& serviceID, const std::optional<std::string>& itemName) {
    return py::finish([&] { return Persistence_getItemsFromService(*client_, py::arg(serviceID), py::arg(itemName)); });
}

json Persistence::getItemsFromService(const GetItemsFromServiceArgs& a) {
    return getItemsFromService(a.serviceID, a.itemName);
}

static py::V Persistence_getItemPersistenceData(OpenHABClient& C, py::V v_itemName, py::V v_serviceID, py::V v_startTime, py::V v_endTime, py::V v_page, py::V v_pageLength, py::V v_boundary, py::V v_itemState, py::V v_displayState, py::V v_language) {
    (void)C;
    (void)v_itemName;
    (void)v_serviceID;
    (void)v_startTime;
    (void)v_endTime;
    (void)v_page;
    (void)v_pageLength;
    (void)v_boundary;
    (void)v_itemState;
    (void)v_displayState;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    if (py::truthy([&]() -> py::V { py::V t_ = py::V(json(!py::isnone(v_pageLength))); return py::truthy(t_) ? py::V(json(py::isnone(v_page))) : t_; }())) {
        v_page = py::V(json(0));
    }
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/persistence/items/"), v_itemName}), v_headers, py::V(), py::dict({{"serviceId", v_serviceID}, {"starttime", v_startTime}, {"endtime", v_endTime}, {"page", v_page}, {"pagelength", v_pageLength}, {"boundary", v_boundary}, {"itemState", v_itemState}, {"displayState", v_displayState}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Unknown Item or persistence service.")}});
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
        return py::dict({{"error", py::s("Unknown Item or persistence service.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Persistence::getItemPersistenceData(const std::string& itemName, const std::optional<std::string>& serviceID, const std::optional<std::string>& startTime, const std::optional<std::string>& endTime, const std::optional<int>& page, const std::optional<int>& pageLength, bool boundary, bool itemState, const std::optional<bool>& displayState, const std::optional<std::string>& language) {
    return py::finish([&] { return Persistence_getItemPersistenceData(*client_, py::arg(itemName), py::arg(serviceID), py::arg(startTime), py::arg(endTime), py::arg(page), py::arg(pageLength), py::arg(boundary), py::arg(itemState), py::arg(displayState), py::arg(language)); });
}

json Persistence::getItemPersistenceData(const std::string& itemName, const GetItemPersistenceDataArgs& a) {
    return getItemPersistenceData(itemName, a.serviceID, a.startTime, a.endTime, a.page, a.pageLength, a.boundary, a.itemState, a.displayState, a.language);
}

static py::V Persistence_storeItemData(OpenHABClient& C, py::V v_itemName, py::V v_time, py::V v_state, py::V v_serviceID) {
    (void)C;
    (void)v_itemName;
    (void)v_time;
    (void)v_state;
    (void)v_serviceID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/persistence/items/"), v_itemName}), py::V(), py::V(), py::dict({{"serviceId", v_serviceID}, {"time", v_time}, {"state", v_state}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Unknown Item or persistence service.")}});
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
        return py::dict({{"error", py::s("Unknown Item or persistence service.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Persistence::storeItemData(const std::string& itemName, const std::string& time, const std::string& state, const std::optional<std::string>& serviceID) {
    return py::finish([&] { return Persistence_storeItemData(*client_, py::arg(itemName), py::arg(time), py::arg(state), py::arg(serviceID)); });
}

json Persistence::storeItemData(const std::string& itemName, const std::string& time, const std::string& state, const StoreItemDataArgs& a) {
    return storeItemData(itemName, time, state, a.serviceID);
}

static py::V Persistence_deleteItemData(OpenHABClient& C, py::V v_itemName, py::V v_startTime, py::V v_endTime, py::V v_serviceID) {
    (void)C;
    (void)v_itemName;
    (void)v_startTime;
    (void)v_endTime;
    (void)v_serviceID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/persistence/items/"), v_itemName}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::dict({{"serviceId", v_serviceID}, {"starttime", v_startTime}, {"endtime", v_endTime}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::cat({py::s("Invalid filter parameters or service not modifiable: "), py::excStr(e_err)})}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Unknown persistence service.")}});
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
        return py::dict({{"error", py::s("Unknown persistence service.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Invalid filter parameters.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Persistence::deleteItemData(const std::string& itemName, const std::string& startTime, const std::string& endTime, const std::string& serviceID) {
    return py::finish([&] { return Persistence_deleteItemData(*client_, py::arg(itemName), py::arg(startTime), py::arg(endTime), py::arg(serviceID)); });
}

}  // namespace openhab
