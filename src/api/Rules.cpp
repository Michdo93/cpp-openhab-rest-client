// Generated from Rules.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Rules_getRules(OpenHABClient& C, py::V v_prefix, py::V v_tags, py::V v_summary, py::V v_staticDataOnly);
static py::V Rules_createRule(OpenHABClient& C, py::V v_ruleData);
static py::V Rules_getRule(OpenHABClient& C, py::V v_ruleUID);
static py::V Rules_updateRule(OpenHABClient& C, py::V v_ruleUID, py::V v_ruleData);
static py::V Rules_deleteRule(OpenHABClient& C, py::V v_ruleUID);
static py::V Rules_getModule(OpenHABClient& C, py::V v_ruleUID, py::V v_moduleCategory, py::V v_moduleID);
static py::V Rules_getModuleConfig(OpenHABClient& C, py::V v_ruleUID, py::V v_moduleCategory, py::V v_moduleID);
static py::V Rules_getModuleConfigParam(OpenHABClient& C, py::V v_ruleUID, py::V v_moduleCategory, py::V v_moduleID, py::V v_param);
static py::V Rules_setModuleConfigParam(OpenHABClient& C, py::V v_ruleUID, py::V v_moduleCategory, py::V v_moduleID, py::V v_param, py::V v_value);
static py::V Rules_getActions(OpenHABClient& C, py::V v_ruleUID);
static py::V Rules_getConditions(OpenHABClient& C, py::V v_ruleUID);
static py::V Rules_getConfiguration(OpenHABClient& C, py::V v_ruleUID);
static py::V Rules_updateConfiguration(OpenHABClient& C, py::V v_ruleUID, py::V v_configData);
static py::V Rules_setRuleState(OpenHABClient& C, py::V v_ruleUID, py::V v_enable);
static py::V Rules_enable(OpenHABClient& C, py::V v_ruleUID);
static py::V Rules_disable(OpenHABClient& C, py::V v_ruleUID);
static py::V Rules_runNow(OpenHABClient& C, py::V v_ruleUID, py::V v_contextData);
static py::V Rules_getTriggers(OpenHABClient& C, py::V v_ruleUID);
static py::V Rules_simulateSchedule(OpenHABClient& C, py::V v_fromTime, py::V v_untilTime);

static py::V Rules_getRules(OpenHABClient& C, py::V v_prefix, py::V v_tags, py::V v_summary, py::V v_staticDataOnly) {
    (void)C;
    (void)v_prefix;
    (void)v_tags;
    (void)v_summary;
    (void)v_staticDataOnly;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/rules"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::dict({{"prefix", v_prefix}, {"tags", v_tags}, {"summary", v_summary}, {"staticDataOnly", v_staticDataOnly}}));
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

json Rules::getRules(const std::optional<std::string>& prefix, const std::optional<std::string>& tags, bool summary, bool staticDataOnly) {
    return py::finish([&] { return Rules_getRules(*client_, py::arg(prefix), py::arg(tags), py::arg(summary), py::arg(staticDataOnly)); });
}

json Rules::getRules(const GetRulesArgs& a) {
    return getRules(a.prefix, a.tags, a.summary, a.staticDataOnly);
}

static py::V Rules_createRule(OpenHABClient& C, py::V v_ruleData) {
    (void)C;
    (void)v_ruleData;
    py::V v_location;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::s("/rules"), py::dict({{"Content-Type", py::s("application/json")}}), py::dumps(v_ruleData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
            v_location = py::getOr(v_response, py::s("location"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Creation refused: Missing required parameter.")}});
        } else if (py::eq(v_status_code, py::V(json(409)))) {
            return py::dict({{"error", py::s("Creation refused: Rule with the same UID already exists.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(201)))) {
        return py::dict({{"message", py::s("Rule successfully created.")}, {"location", (py::truthy(v_location) ? py::V(v_location) : py::V(py::s("No Location headers provided.")))}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Creation refused: Missing required parameter.")}});
    } else if (py::eq(v_status_code, py::V(json(409)))) {
        return py::dict({{"error", py::s("Creation refused: Rule with the same UID already exists.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::createRule(const json& ruleData) {
    return py::finish([&] { return Rules_createRule(*client_, py::arg(ruleData)); });
}

static py::V Rules_getRule(OpenHABClient& C, py::V v_ruleUID) {
    (void)C;
    (void)v_ruleUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/rules/"), v_ruleUID}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule not found.")}});
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
        return py::dict({{"error", py::s("Rule not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::getRule(const std::string& ruleUID) {
    return py::finish([&] { return Rules_getRule(*client_, py::arg(ruleUID)); });
}

static py::V Rules_updateRule(OpenHABClient& C, py::V v_ruleUID, py::V v_ruleData) {
    (void)C;
    (void)v_ruleUID;
    (void)v_ruleData;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/rules/"), v_ruleUID}), py::dict({{"Content-Type", py::s("application/json")}}), py::dumps(v_ruleData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::updateRule(const std::string& ruleUID, const json& ruleData) {
    return py::finish([&] { return Rules_updateRule(*client_, py::arg(ruleUID), py::arg(ruleData)); });
}

static py::V Rules_deleteRule(OpenHABClient& C, py::V v_ruleUID) {
    (void)C;
    (void)v_ruleUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/rules/"), v_ruleUID}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::deleteRule(const std::string& ruleUID) {
    return py::finish([&] { return Rules_deleteRule(*client_, py::arg(ruleUID)); });
}

static py::V Rules_getModule(OpenHABClient& C, py::V v_ruleUID, py::V v_moduleCategory, py::V v_moduleID) {
    (void)C;
    (void)v_ruleUID;
    (void)v_moduleCategory;
    (void)v_moduleID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/rules/"), v_ruleUID, py::s("/"), v_moduleCategory, py::s("/"), v_moduleID}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found or does not have a module with such Category and ID.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found or does not have a module with such Category and ID.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::getModule(const std::string& ruleUID, const std::string& moduleCategory, const std::string& moduleID) {
    return py::finish([&] { return Rules_getModule(*client_, py::arg(ruleUID), py::arg(moduleCategory), py::arg(moduleID)); });
}

static py::V Rules_getModuleConfig(OpenHABClient& C, py::V v_ruleUID, py::V v_moduleCategory, py::V v_moduleID) {
    (void)C;
    (void)v_ruleUID;
    (void)v_moduleCategory;
    (void)v_moduleID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/rules/"), v_ruleUID, py::s("/"), v_moduleCategory, py::s("/"), v_moduleID, py::s("/config")}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found or does not have a module with such Category and ID.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found or does not have a module with such Category and ID.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::getModuleConfig(const std::string& ruleUID, const std::string& moduleCategory, const std::string& moduleID) {
    return py::finish([&] { return Rules_getModuleConfig(*client_, py::arg(ruleUID), py::arg(moduleCategory), py::arg(moduleID)); });
}

static py::V Rules_getModuleConfigParam(OpenHABClient& C, py::V v_ruleUID, py::V v_moduleCategory, py::V v_moduleID, py::V v_param) {
    (void)C;
    (void)v_ruleUID;
    (void)v_moduleCategory;
    (void)v_moduleID;
    (void)v_param;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/rules/"), v_ruleUID, py::s("/"), v_moduleCategory, py::s("/"), v_moduleID, py::s("/config/"), v_param}), py::dict({{"Accept", py::s("text/plain")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found or does not have a module with such Category and ID.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found or does not have a module with such Category and ID.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::getModuleConfigParam(const std::string& ruleUID, const std::string& moduleCategory, const std::string& moduleID, const std::string& param) {
    return py::finish([&] { return Rules_getModuleConfigParam(*client_, py::arg(ruleUID), py::arg(moduleCategory), py::arg(moduleID), py::arg(param)); });
}

static py::V Rules_setModuleConfigParam(OpenHABClient& C, py::V v_ruleUID, py::V v_moduleCategory, py::V v_moduleID, py::V v_param, py::V v_value) {
    (void)C;
    (void)v_ruleUID;
    (void)v_moduleCategory;
    (void)v_moduleID;
    (void)v_param;
    (void)v_value;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/rules/"), v_ruleUID, py::s("/"), v_moduleCategory, py::s("/"), v_moduleID, py::s("/config/"), v_param}), py::dict({{"Content-Type", py::s("text/plain")}}), py::str(v_value), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found or does not have a module with such Category and ID.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found or does not have a module with such Category and ID.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::setModuleConfigParam(const std::string& ruleUID, const std::string& moduleCategory, const std::string& moduleID, const std::string& param, const std::string& value) {
    return py::finish([&] { return Rules_setModuleConfigParam(*client_, py::arg(ruleUID), py::arg(moduleCategory), py::arg(moduleID), py::arg(param), py::arg(value)); });
}

static py::V Rules_getActions(OpenHABClient& C, py::V v_ruleUID) {
    (void)C;
    (void)v_ruleUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/rules/"), v_ruleUID, py::s("/actions")}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::getActions(const std::string& ruleUID) {
    return py::finish([&] { return Rules_getActions(*client_, py::arg(ruleUID)); });
}

static py::V Rules_getConditions(OpenHABClient& C, py::V v_ruleUID) {
    (void)C;
    (void)v_ruleUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/rules/"), v_ruleUID, py::s("/conditions")}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::getConditions(const std::string& ruleUID) {
    return py::finish([&] { return Rules_getConditions(*client_, py::arg(ruleUID)); });
}

static py::V Rules_getConfiguration(OpenHABClient& C, py::V v_ruleUID) {
    (void)C;
    (void)v_ruleUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/rules/"), v_ruleUID, py::s("/config")}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::getConfiguration(const std::string& ruleUID) {
    return py::finish([&] { return Rules_getConfiguration(*client_, py::arg(ruleUID)); });
}

static py::V Rules_updateConfiguration(OpenHABClient& C, py::V v_ruleUID, py::V v_configData) {
    (void)C;
    (void)v_ruleUID;
    (void)v_configData;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/rules/"), v_ruleUID, py::s("/config")}), py::dict({{"Content-Type", py::s("application/json")}}), py::dumps(v_configData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::updateConfiguration(const std::string& ruleUID, const json& configData) {
    return py::finish([&] { return Rules_updateConfiguration(*client_, py::arg(ruleUID), py::arg(configData)); });
}

static py::V Rules_setRuleState(OpenHABClient& C, py::V v_ruleUID, py::V v_enable) {
    (void)C;
    (void)v_ruleUID;
    (void)v_enable;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::cat({py::s("/rules/"), v_ruleUID, py::s("/enable")}), py::dict({{"Content-Type", py::s("text/plain")}}), (py::truthy(v_enable) ? py::V(py::s("true")) : py::V(py::s("false"))), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::setRuleState(const std::string& ruleUID, bool enable) {
    return py::finish([&] { return Rules_setRuleState(*client_, py::arg(ruleUID), py::arg(enable)); });
}

static py::V Rules_enable(OpenHABClient& C, py::V v_ruleUID) {
    (void)C;
    (void)v_ruleUID;
    return Rules_setRuleState(C, v_ruleUID, py::V(json(true)));
}

json Rules::enable(const std::string& ruleUID) {
    return py::finish([&] { return Rules_enable(*client_, py::arg(ruleUID)); });
}

static py::V Rules_disable(OpenHABClient& C, py::V v_ruleUID) {
    (void)C;
    (void)v_ruleUID;
    return Rules_setRuleState(C, v_ruleUID, py::V(json(false)));
}

json Rules::disable(const std::string& ruleUID) {
    return py::finish([&] { return Rules_disable(*client_, py::arg(ruleUID)); });
}

static py::V Rules_runNow(OpenHABClient& C, py::V v_ruleUID, py::V v_contextData) {
    (void)C;
    (void)v_ruleUID;
    (void)v_contextData;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::cat({py::s("/rules/"), v_ruleUID, py::s("/runnow")}), py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("application/json")}}), py::dumps([&]() -> py::V { py::V t_ = v_contextData; return py::truthy(t_) ? t_ : py::dict(); }()), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::runNow(const std::string& ruleUID, const json& contextData) {
    return py::finish([&] { return Rules_runNow(*client_, py::arg(ruleUID), py::arg(contextData)); });
}

json Rules::runNow(const std::string& ruleUID, const RunNowArgs& a) {
    return runNow(ruleUID, a.contextData);
}

static py::V Rules_getTriggers(OpenHABClient& C, py::V v_ruleUID) {
    (void)C;
    (void)v_ruleUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/rules/"), v_ruleUID, py::s("/triggers")}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
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
        return py::dict({{"error", py::s("Rule corresponding to the given UID was not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::getTriggers(const std::string& ruleUID) {
    return py::finish([&] { return Rules_getTriggers(*client_, py::arg(ruleUID)); });
}

static py::V Rules_simulateSchedule(OpenHABClient& C, py::V v_fromTime, py::V v_untilTime) {
    (void)C;
    (void)v_fromTime;
    (void)v_untilTime;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/rules/schedule/simulations"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::dict({{"from", v_fromTime}, {"until", v_untilTime}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("The max. simulation duration of 180 days is exceeded.")}});
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
        return py::dict({{"error", py::s("The max. simulation duration of 180 days is exceeded.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Rules::simulateSchedule(const std::string& fromTime, const std::string& untilTime) {
    return py::finish([&] { return Rules_simulateSchedule(*client_, py::arg(fromTime), py::arg(untilTime)); });
}

}  // namespace openhab
