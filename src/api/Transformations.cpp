// Generated from Transformations.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Transformations_getTransformations(OpenHABClient& C);
static py::V Transformations_getTransformation(OpenHABClient& C, py::V v_transformationUID);
static py::V Transformations_updateTransformation(OpenHABClient& C, py::V v_transformationUID, py::V v_transformationData);
static py::V Transformations_deleteTransformation(OpenHABClient& C, py::V v_transformationUID);
static py::V Transformations_getTransformationServices(OpenHABClient& C);

static py::V Transformations_getTransformations(OpenHABClient& C) {
    (void)C;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/transformations"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json Transformations::getTransformations() {
    return py::finish([&] { return Transformations_getTransformations(*client_); });
}

static py::V Transformations_getTransformation(OpenHABClient& C, py::V v_transformationUID) {
    (void)C;
    (void)v_transformationUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::cat({py::s("/transformations/"), v_transformationUID}), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json Transformations::getTransformation(const std::string& transformationUID) {
    return py::finish([&] { return Transformations_getTransformation(*client_, py::arg(transformationUID)); });
}

static py::V Transformations_updateTransformation(OpenHABClient& C, py::V v_transformationUID, py::V v_transformationData) {
    (void)C;
    (void)v_transformationUID;
    (void)v_transformationData;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/transformations/"), v_transformationUID}), py::dict({{"Content-Type", py::s("application/json")}}), py::dumps(v_transformationData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Bad Request (content missing or invalid)")}});
        } else if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Transformation not editable.")}});
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
        return py::dict({{"error", py::s("Bad Request (content missing or invalid)")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Transformation not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Transformations::updateTransformation(const std::string& transformationUID, const json& transformationData) {
    return py::finish([&] { return Transformations_updateTransformation(*client_, py::arg(transformationUID), py::arg(transformationData)); });
}

static py::V Transformations_deleteTransformation(OpenHABClient& C, py::V v_transformationUID) {
    (void)C;
    (void)v_transformationUID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/transformations/"), v_transformationUID}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Transformation not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("UID not found.")}});
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
        return py::dict({{"error", py::s("UID not found.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Transformation not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Transformations::deleteTransformation(const std::string& transformationUID) {
    return py::finish([&] { return Transformations_deleteTransformation(*client_, py::arg(transformationUID)); });
}

static py::V Transformations_getTransformationServices(OpenHABClient& C) {
    (void)C;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/transformations/services"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json Transformations::getTransformationServices() {
    return py::finish([&] { return Transformations_getTransformationServices(*client_); });
}

}  // namespace openhab
