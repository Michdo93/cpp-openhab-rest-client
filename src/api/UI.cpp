// Generated from UI.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V UI_getUIComponents(OpenHABClient& C, py::V v_namespace, py::V v_summary);
static py::V UI_addUIComponent(OpenHABClient& C, py::V v_namespace, py::V v_componentData);
static py::V UI_getUIComponent(OpenHABClient& C, py::V v_namespace, py::V v_componentUID);
static py::V UI_updateUIComponent(OpenHABClient& C, py::V v_namespace, py::V v_componentUID, py::V v_componentData);
static py::V UI_deleteUIComponent(OpenHABClient& C, py::V v_namespace, py::V v_componentUID);
static py::V UI_getUITiles(OpenHABClient& C);

static py::V UI_getUIComponents(OpenHABClient& C, py::V v_namespace, py::V v_summary) {
    (void)C;
    (void)v_namespace;
    (void)v_summary;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/ui/components/"), v_namespace}), py::dict({{"Accept", py::s("application/json")}}), py::V(), (py::truthy(v_summary) ? py::V(py::dict({{"summary", v_summary}})) : py::V(py::dict())));
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

json UI::getUIComponents(const std::string& namespace_, bool summary) {
    return py::finish([&] { return UI_getUIComponents(*client_, py::arg(namespace_), py::arg(summary)); });
}

json UI::getUIComponents(const std::string& namespace_, const GetUIComponentsArgs& a) {
    return getUIComponents(namespace_, a.summary);
}

static py::V UI_addUIComponent(OpenHABClient& C, py::V v_namespace, py::V v_componentData) {
    (void)C;
    (void)v_namespace;
    (void)v_componentData;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::cat({py::s("/ui/components/"), v_namespace}), py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("application/json")}}), py::dumps(v_componentData), py::V());
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

json UI::addUIComponent(const std::string& namespace_, const json& componentData) {
    return py::finish([&] { return UI_addUIComponent(*client_, py::arg(namespace_), py::arg(componentData)); });
}

static py::V UI_getUIComponent(OpenHABClient& C, py::V v_namespace, py::V v_componentUID) {
    (void)C;
    (void)v_namespace;
    (void)v_componentUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/ui/components/"), v_namespace, py::s("/"), v_componentUID}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Component not found.")}});
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
        return py::dict({{"error", py::s("Component not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json UI::getUIComponent(const std::string& namespace_, const std::string& componentUID) {
    return py::finish([&] { return UI_getUIComponent(*client_, py::arg(namespace_), py::arg(componentUID)); });
}

static py::V UI_updateUIComponent(OpenHABClient& C, py::V v_namespace, py::V v_componentUID, py::V v_componentData) {
    (void)C;
    (void)v_namespace;
    (void)v_componentUID;
    (void)v_componentData;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/ui/components/"), v_namespace, py::s("/"), v_componentUID}), py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("application/json")}}), py::dumps(v_componentData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Component not found.")}});
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
        return py::dict({{"error", py::s("Component not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json UI::updateUIComponent(const std::string& namespace_, const std::string& componentUID, const json& componentData) {
    return py::finish([&] { return UI_updateUIComponent(*client_, py::arg(namespace_), py::arg(componentUID), py::arg(componentData)); });
}

static py::V UI_deleteUIComponent(OpenHABClient& C, py::V v_namespace, py::V v_componentUID) {
    (void)C;
    (void)v_namespace;
    (void)v_componentUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/ui/components/"), v_namespace, py::s("/"), v_componentUID}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Component not found.")}});
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
        return py::dict({{"error", py::s("Component not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json UI::deleteUIComponent(const std::string& namespace_, const std::string& componentUID) {
    return py::finish([&] { return UI_deleteUIComponent(*client_, py::arg(namespace_), py::arg(componentUID)); });
}

static py::V UI_getUITiles(OpenHABClient& C) {
    (void)C;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/ui/tiles"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json UI::getUITiles() {
    return py::finish([&] { return UI_getUITiles(*client_); });
}

}  // namespace openhab
