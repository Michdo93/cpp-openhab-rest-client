// Generated from Tags.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Tags_getTags(OpenHABClient& C, py::V v_language);
static py::V Tags_createTag(OpenHABClient& C, py::V v_tagData, py::V v_language);
static py::V Tags_getTag(OpenHABClient& C, py::V v_tagID, py::V v_language);
static py::V Tags_updateTag(OpenHABClient& C, py::V v_tagID, py::V v_tagData, py::V v_language);
static py::V Tags_deleteTag(OpenHABClient& C, py::V v_tagID, py::V v_language);

static py::V Tags_getTags(OpenHABClient& C, py::V v_language) {
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
        v_response = py::http(C, "get", py::s("/tags"), v_headers, py::V(), py::V());
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

json Tags::getTags(const std::optional<std::string>& language) {
    return py::finish([&] { return Tags_getTags(*client_, py::arg(language)); });
}

json Tags::getTags(const GetTagsArgs& a) {
    return getTags(a.language);
}

static py::V Tags_createTag(OpenHABClient& C, py::V v_tagData, py::V v_language) {
    (void)C;
    (void)v_tagData;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("*/*")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "post", py::s("/tags"), v_headers, py::dumps(v_tagData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("The tag identifier is invalid or the tag label is missing.")}});
        } else if (py::eq(v_status_code, py::V(json(409)))) {
            return py::dict({{"error", py::s("A tag with the same identifier already exists.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(201)))) {
        return py::dict({{"message", py::s("Created")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("The tag identifier is invalid or the tag label is missing.")}});
    } else if (py::eq(v_status_code, py::V(json(409)))) {
        return py::dict({{"error", py::s("A tag with the same identifier already exists.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Tags::createTag(const json& tagData, const std::optional<std::string>& language) {
    return py::finish([&] { return Tags_createTag(*client_, py::arg(tagData), py::arg(language)); });
}

json Tags::createTag(const json& tagData, const CreateTagArgs& a) {
    return createTag(tagData, a.language);
}

static py::V Tags_getTag(OpenHABClient& C, py::V v_tagID, py::V v_language) {
    (void)C;
    (void)v_tagID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/tags/"), v_tagID}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Semantic tag not found.")}});
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
        return py::dict({{"error", py::s("Semantic tag not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Tags::getTag(const std::string& tagID, const std::optional<std::string>& language) {
    return py::finish([&] { return Tags_getTag(*client_, py::arg(tagID), py::arg(language)); });
}

json Tags::getTag(const std::string& tagID, const GetTagArgs& a) {
    return getTag(tagID, a.language);
}

static py::V Tags_updateTag(OpenHABClient& C, py::V v_tagID, py::V v_tagData, py::V v_language) {
    (void)C;
    (void)v_tagID;
    (void)v_tagData;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("*/*")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "put", py::cat({py::s("/tags/"), v_tagID}), v_headers, py::dumps(v_tagData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Semantic tag not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Semantic tag not found.")}});
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
        return py::dict({{"error", py::s("Semantic tag not found.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Semantic tag not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Tags::updateTag(const std::string& tagID, const json& tagData, const std::optional<std::string>& language) {
    return py::finish([&] { return Tags_updateTag(*client_, py::arg(tagID), py::arg(tagData), py::arg(language)); });
}

json Tags::updateTag(const std::string& tagID, const json& tagData, const UpdateTagArgs& a) {
    return updateTag(tagID, tagData, a.language);
}

static py::V Tags_deleteTag(OpenHABClient& C, py::V v_tagID, py::V v_language) {
    (void)C;
    (void)v_tagID;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/tags/"), v_tagID}), (py::truthy(v_language) ? py::V(py::dict({{"Accept-Language", v_language}})) : py::V(py::dict())), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Semantic tag not removable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Semantic tag not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK, was deleted.")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Semantic tag not found.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Semantic tag not removable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Tags::deleteTag(const std::string& tagID, const std::optional<std::string>& language) {
    return py::finish([&] { return Tags_deleteTag(*client_, py::arg(tagID), py::arg(language)); });
}

json Tags::deleteTag(const std::string& tagID, const DeleteTagArgs& a) {
    return deleteTag(tagID, a.language);
}

}  // namespace openhab
