// Generated from Links.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Links_getLinks(OpenHABClient& C, py::V v_channelUID, py::V v_itemName);
static py::V Links_getLink(OpenHABClient& C, py::V v_itemName, py::V v_channelUID);
static py::V Links_linkItemToChannel(OpenHABClient& C, py::V v_itemName, py::V v_channelUID, py::V v_configuration);
static py::V Links_unlinkItemFromChannel(OpenHABClient& C, py::V v_itemName, py::V v_channelUID);
static py::V Links_deleteAllLinks(OpenHABClient& C, py::V v_object);
static py::V Links_getOrphanLinks(OpenHABClient& C);
static py::V Links_purgeUnusedLinks(OpenHABClient& C);

static py::V Links_getLinks(OpenHABClient& C, py::V v_channelUID, py::V v_itemName) {
    (void)C;
    (void)v_channelUID;
    (void)v_itemName;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_params = py::dict();
    if (py::truthy(v_channelUID)) {
        py::set(v_params, py::s("channelUID"), v_channelUID);
    }
    if (py::truthy(v_itemName)) {
        py::set(v_params, py::s("itemName"), v_itemName);
    }
    try {
        v_response = py::http(C, "get", py::s("/links"), py::dict({{"Accept", py::s("application/json")}}), py::V(), v_params);
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

json Links::getLinks(const std::optional<std::string>& channelUID, const std::optional<std::string>& itemName) {
    return py::finish([&] { return Links_getLinks(*client_, py::arg(channelUID), py::arg(itemName)); });
}

json Links::getLinks(const GetLinksArgs& a) {
    return getLinks(a.channelUID, a.itemName);
}

static py::V Links_getLink(OpenHABClient& C, py::V v_itemName, py::V v_channelUID) {
    (void)C;
    (void)v_itemName;
    (void)v_channelUID;
    py::V v_channelPath;
    py::V v_itemPath;
    py::V v_response;
    py::V v_status_code;
    v_itemPath = py::quote(v_itemName, "");
    v_channelPath = py::quote(v_channelUID, "");
    try {
        v_response = py::http(C, "get", py::cat({py::s("/links/"), v_itemPath, py::s("/"), v_channelPath}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Link not found.")}});
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
        return py::dict({{"error", py::s("Link not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Links::getLink(const std::string& itemName, const std::string& channelUID) {
    return py::finish([&] { return Links_getLink(*client_, py::arg(itemName), py::arg(channelUID)); });
}

static py::V Links_linkItemToChannel(OpenHABClient& C, py::V v_itemName, py::V v_channelUID, py::V v_configuration) {
    (void)C;
    (void)v_itemName;
    (void)v_channelUID;
    (void)v_configuration;
    py::V v_channelPath;
    py::V v_itemPath;
    py::V v_response;
    py::V v_status_code;
    v_itemPath = py::quote(v_itemName, "");
    v_channelPath = py::quote(v_channelUID, "");
    try {
        v_response = py::http(C, "put", py::cat({py::s("/links/"), v_itemPath, py::s("/"), v_channelPath}), py::dict({{"Content-Type", py::s("application/json")}}), py::dumps(py::dict({{"itemName", v_itemName}, {"channelUID", v_channelUID}, {"configuration", v_configuration}})), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Link is not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Content does not match the path.")}});
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
        return py::dict({{"error", py::s("Content does not match the path.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Link is not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Links::linkItemToChannel(const std::string& itemName, const std::string& channelUID, const json& configuration) {
    return py::finish([&] { return Links_linkItemToChannel(*client_, py::arg(itemName), py::arg(channelUID), py::arg(configuration)); });
}

static py::V Links_unlinkItemFromChannel(OpenHABClient& C, py::V v_itemName, py::V v_channelUID) {
    (void)C;
    (void)v_itemName;
    (void)v_channelUID;
    py::V v_channelPath;
    py::V v_itemPath;
    py::V v_response;
    py::V v_status_code;
    v_itemPath = py::quote(v_itemName, "");
    v_channelPath = py::quote(v_channelUID, "");
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/links/"), v_itemPath, py::s("/"), v_channelPath}), py::dict({{"Content-Type", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Link not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Link not found.")}});
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
        return py::dict({{"error", py::s("Link not found.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Link not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Links::unlinkItemFromChannel(const std::string& itemName, const std::string& channelUID) {
    return py::finish([&] { return Links_unlinkItemFromChannel(*client_, py::arg(itemName), py::arg(channelUID)); });
}

static py::V Links_deleteAllLinks(OpenHABClient& C, py::V v_object) {
    (void)C;
    (void)v_object;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/links/"), v_object}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json Links::deleteAllLinks(const std::string& object) {
    return py::finish([&] { return Links_deleteAllLinks(*client_, py::arg(object)); });
}

static py::V Links_getOrphanLinks(OpenHABClient& C) {
    (void)C;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/links/orphans"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json Links::getOrphanLinks() {
    return py::finish([&] { return Links_getOrphanLinks(*client_); });
}

static py::V Links_purgeUnusedLinks(OpenHABClient& C) {
    (void)C;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::s("/links/purge"), py::V(), py::V(), py::V());
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

json Links::purgeUnusedLinks() {
    return py::finish([&] { return Links_purgeUnusedLinks(*client_); });
}

}  // namespace openhab
