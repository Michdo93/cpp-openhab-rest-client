// Generated from Logging.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Logging_getLoggers(OpenHABClient& C);
static py::V Logging_getLogger(OpenHABClient& C, py::V v_loggerName);
static py::V Logging_modifyOrAddLogger(OpenHABClient& C, py::V v_loggerName, py::V v_level);
static py::V Logging_removeLogger(OpenHABClient& C, py::V v_loggerName);

static py::V Logging_getLoggers(OpenHABClient& C) {
    (void)C;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/logging"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json Logging::getLoggers() {
    return py::finish([&] { return Logging_getLoggers(*client_); });
}

static py::V Logging_getLogger(OpenHABClient& C, py::V v_loggerName) {
    (void)C;
    (void)v_loggerName;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/logging/"), v_loggerName}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json Logging::getLogger(const std::string& loggerName) {
    return py::finish([&] { return Logging_getLogger(*client_, py::arg(loggerName)); });
}

static py::V Logging_modifyOrAddLogger(OpenHABClient& C, py::V v_loggerName, py::V v_level) {
    (void)C;
    (void)v_loggerName;
    (void)v_level;
    py::V v_data;
    py::V v_response;
    py::V v_status_code;
    v_data = py::dict({{"loggerName", v_loggerName}, {"level", v_level}});
    try {
        v_response = py::http(C, "put", py::cat({py::s("/logging/"), v_loggerName}), py::dict({{"Content-Type", py::s("application/json")}}), py::dumps(v_data), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Payload is invalid.")}});
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
        return py::dict({{"error", py::s("Payload is invalid.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Logging::modifyOrAddLogger(const std::string& loggerName, const std::string& level) {
    return py::finish([&] { return Logging_modifyOrAddLogger(*client_, py::arg(loggerName), py::arg(level)); });
}

static py::V Logging_removeLogger(OpenHABClient& C, py::V v_loggerName) {
    (void)C;
    (void)v_loggerName;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/logging/"), v_loggerName}), py::V(), py::V(), py::V());
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

json Logging::removeLogger(const std::string& loggerName) {
    return py::finish([&] { return Logging_removeLogger(*client_, py::arg(loggerName)); });
}

}  // namespace openhab
