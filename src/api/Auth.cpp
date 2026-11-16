// Generated from Auth.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Auth_getAPITokens(OpenHABClient& C);
static py::V Auth_revokeAPIToken(OpenHABClient& C, py::V v_tokenName);
static py::V Auth_logout(OpenHABClient& C, py::V v_refreshToken, py::V v_sessionID);
static py::V Auth_getSessions(OpenHABClient& C);
static py::V Auth_getToken(OpenHABClient& C, py::V v_useCookie, py::V v_grantType, py::V v_code, py::V v_redirectURI, py::V v_clientID, py::V v_refreshToken, py::V v_codeVerifier);

static py::V Auth_getAPITokens(OpenHABClient& C) {
    (void)C;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    try {
        v_response = py::http(C, "get", py::s("/auth/apitokens"), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(401)))) {
            return py::dict({{"error", py::s("User is not authenticated.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("User not found.")}});
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
        return py::dict({{"error", py::s("User not found.")}});
    } else if (py::eq(v_status_code, py::V(json(401)))) {
        return py::dict({{"error", py::s("User is not authenticated.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Auth::getAPITokens() {
    return py::finish([&] { return Auth_getAPITokens(*client_); });
}

static py::V Auth_revokeAPIToken(OpenHABClient& C, py::V v_tokenName) {
    (void)C;
    (void)v_tokenName;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/auth/apitokens/"), v_tokenName}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(401)))) {
            return py::dict({{"error", py::s("User is not authenticated.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("User not found.")}});
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
        return py::dict({{"error", py::s("User not found.")}});
    } else if (py::eq(v_status_code, py::V(json(401)))) {
        return py::dict({{"error", py::s("User is not authenticated.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Auth::revokeAPIToken(const std::string& tokenName) {
    return py::finish([&] { return Auth_revokeAPIToken(*client_, py::arg(tokenName)); });
}

static py::V Auth_logout(OpenHABClient& C, py::V v_refreshToken, py::V v_sessionID) {
    (void)C;
    (void)v_refreshToken;
    (void)v_sessionID;
    py::V v_data;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/x-www-form-urlencoded")}});
    v_data = py::dict({{"refresh_token", v_refreshToken}, {"id", v_sessionID}});
    try {
        v_response = py::http(C, "post", py::s("/auth/logout"), v_headers, v_data, py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(401)))) {
            return py::dict({{"error", py::s("User is not authenticated.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("User not found.")}});
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
        return py::dict({{"error", py::s("User not found.")}});
    } else if (py::eq(v_status_code, py::V(json(401)))) {
        return py::dict({{"error", py::s("User is not authenticated.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Auth::logout(const std::string& refreshToken, const std::string& sessionID) {
    return py::finish([&] { return Auth_logout(*client_, py::arg(refreshToken), py::arg(sessionID)); });
}

static py::V Auth_getSessions(OpenHABClient& C) {
    (void)C;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    try {
        v_response = py::http(C, "get", py::s("/auth/sessions"), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(401)))) {
            return py::dict({{"error", py::s("User is not authenticated.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("User not found.")}});
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
        return py::dict({{"error", py::s("User not found.")}});
    } else if (py::eq(v_status_code, py::V(json(401)))) {
        return py::dict({{"error", py::s("User is not authenticated.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Auth::getSessions() {
    return py::finish([&] { return Auth_getSessions(*client_); });
}

static py::V Auth_getToken(OpenHABClient& C, py::V v_useCookie, py::V v_grantType, py::V v_code, py::V v_redirectURI, py::V v_clientID, py::V v_refreshToken, py::V v_codeVerifier) {
    (void)C;
    (void)v_useCookie;
    (void)v_grantType;
    (void)v_code;
    (void)v_redirectURI;
    (void)v_clientID;
    (void)v_refreshToken;
    (void)v_codeVerifier;
    py::V v_body;
    py::V v_encodedBody;
    py::V v_headers;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/x-www-form-urlencoded")}, {"Accept", py::s("application/json")}});
    v_params = py::dict({{"useCookie", py::lower(py::str(v_useCookie))}});
    v_body = py::dict({{"grant_type", v_grantType}, {"code", v_code}, {"redirect_uri", v_redirectURI}, {"client_id", v_clientID}, {"refresh_token", v_refreshToken}, {"code_verifier", v_codeVerifier}});
    v_body = py::withoutNone(v_body);
    v_encodedBody = py::urlencode(v_body);
    try {
        v_response = py::http(C, "post", py::s("/auth/token"), v_headers, v_encodedBody, v_params);
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Invalid request parameters.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return v_response;
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Invalid request parameters.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Auth::getToken(bool useCookie, const std::optional<std::string>& grantType, const std::optional<std::string>& code, const std::optional<std::string>& redirectURI, const std::optional<std::string>& clientID, const std::optional<std::string>& refreshToken, const std::optional<std::string>& codeVerifier) {
    return py::finish([&] { return Auth_getToken(*client_, py::arg(useCookie), py::arg(grantType), py::arg(code), py::arg(redirectURI), py::arg(clientID), py::arg(refreshToken), py::arg(codeVerifier)); });
}

json Auth::getToken(const GetTokenArgs& a) {
    return getToken(a.useCookie, a.grantType, a.code, a.redirectURI, a.clientID, a.refreshToken, a.codeVerifier);
}

}  // namespace openhab
