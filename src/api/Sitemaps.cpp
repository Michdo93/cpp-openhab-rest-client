// Generated from Sitemaps.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static EventStream Sitemaps_openEventStream(OpenHABClient& C, py::V v_path, py::V v_params, py::V v_errors);
static py::V Sitemaps_getSitemaps(OpenHABClient& C);
static py::V Sitemaps_getSitemap(OpenHABClient& C, py::V v_sitemapName, py::V v_type, py::V v_jsonCallback, py::V v_includeHidden, py::V v_language);
static py::V Sitemaps_getSitemapPage(OpenHABClient& C, py::V v_sitemapName, py::V v_pageID, py::V v_subscriptionID, py::V v_includeHidden, py::V v_language);
static py::V Sitemaps_getFullSitemap(OpenHABClient& C, py::V v_sitemapName, py::V v_subscriptionID, py::V v_includeHidden, py::V v_language);
static EventStream Sitemaps_getSitemapEvents(OpenHABClient& C, py::V v_subscriptionID, py::V v_sitemapName, py::V v_pageID);
static EventStream Sitemaps_getFullSitemapEvents(OpenHABClient& C, py::V v_subscriptionID, py::V v_sitemapName);
static py::V Sitemaps_subscribeToSitemapEvents(OpenHABClient& C);

static EventStream Sitemaps_openEventStream(OpenHABClient& C, py::V v_path, py::V v_params, py::V v_errors) {
    (void)C;
    (void)v_path;
    (void)v_params;
    (void)v_errors;
    py::V v_statusCode;
    try {
        return py::sse(C, v_path, py::V(), v_params);
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_statusCode = py::excStatus(e_err);
        if (py::contains(v_errors, v_statusCode)) {
            return py::asStream(py::dict({{"error", py::get(v_errors, v_statusCode)}}));
        }
        return py::asStream(py::dict({{"error", py::cat({py::s("HTTP error "), v_statusCode, py::s(": "), py::excStr(e_err)})}}));
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::asStream(py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}}));
    }
}

static py::V Sitemaps_getSitemaps(OpenHABClient& C) {
    (void)C;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/sitemaps"), py::dict({{"Accept", py::s("application/json")}}), py::V(), py::V());
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

json Sitemaps::getSitemaps() {
    return py::finish([&] { return Sitemaps_getSitemaps(*client_); });
}

static py::V Sitemaps_getSitemap(OpenHABClient& C, py::V v_sitemapName, py::V v_type, py::V v_jsonCallback, py::V v_includeHidden, py::V v_language) {
    (void)C;
    (void)v_sitemapName;
    (void)v_type;
    (void)v_jsonCallback;
    (void)v_includeHidden;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    if (py::truthy(v_includeHidden)) {
        v_includeHidden = py::s("true");
    } else {
        v_includeHidden = py::s("false");
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/sitemaps/"), v_sitemapName}), (py::truthy(v_language) ? py::V(py::dict({{"Accept-Language", v_language}})) : py::V(py::dict())), py::V(), py::dict({{"type", v_type}, {"jsoncallback", v_jsonCallback}, {"includeHidden", v_includeHidden}}));
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

json Sitemaps::getSitemap(const std::string& sitemapName, const std::optional<std::string>& type, const std::optional<std::string>& jsonCallback, bool includeHidden, const std::optional<std::string>& language) {
    return py::finish([&] { return Sitemaps_getSitemap(*client_, py::arg(sitemapName), py::arg(type), py::arg(jsonCallback), py::arg(includeHidden), py::arg(language)); });
}

json Sitemaps::getSitemap(const std::string& sitemapName, const GetSitemapArgs& a) {
    return getSitemap(sitemapName, a.type, a.jsonCallback, a.includeHidden, a.language);
}

static py::V Sitemaps_getSitemapPage(OpenHABClient& C, py::V v_sitemapName, py::V v_pageID, py::V v_subscriptionID, py::V v_includeHidden, py::V v_language) {
    (void)C;
    (void)v_sitemapName;
    (void)v_pageID;
    (void)v_subscriptionID;
    (void)v_includeHidden;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    if (py::truthy(v_includeHidden)) {
        v_includeHidden = py::s("true");
    } else {
        v_includeHidden = py::s("false");
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/sitemaps/"), v_sitemapName, py::s("/"), v_pageID}), (py::truthy(v_language) ? py::V(py::dict({{"Accept-Language", v_language}})) : py::V(py::dict())), py::V(), py::dict({{"subscriptionid", v_subscriptionID}, {"includeHidden", v_includeHidden}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Invalid subscription id has been provided.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Sitemap with requested name does not exist or page does not exist, or page refers to a non-linkable widget.")}});
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
        return py::dict({{"error", py::s("Sitemap with requested name does not exist or page does not exist, or page refers to a non-linkable widget.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Invalid subscription id has been provided.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Sitemaps::getSitemapPage(const std::string& sitemapName, const std::string& pageID, const std::optional<std::string>& subscriptionID, bool includeHidden, const std::optional<std::string>& language) {
    return py::finish([&] { return Sitemaps_getSitemapPage(*client_, py::arg(sitemapName), py::arg(pageID), py::arg(subscriptionID), py::arg(includeHidden), py::arg(language)); });
}

json Sitemaps::getSitemapPage(const std::string& sitemapName, const std::string& pageID, const GetSitemapPageArgs& a) {
    return getSitemapPage(sitemapName, pageID, a.subscriptionID, a.includeHidden, a.language);
}

static py::V Sitemaps_getFullSitemap(OpenHABClient& C, py::V v_sitemapName, py::V v_subscriptionID, py::V v_includeHidden, py::V v_language) {
    (void)C;
    (void)v_sitemapName;
    (void)v_subscriptionID;
    (void)v_includeHidden;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    if (py::truthy(v_includeHidden)) {
        v_includeHidden = py::s("true");
    } else {
        v_includeHidden = py::s("false");
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/sitemaps/"), v_sitemapName, py::s("/*")}), (py::truthy(v_language) ? py::V(py::dict({{"Accept-Language", v_language}})) : py::V(py::dict())), py::V(), py::dict({{"subscriptionid", v_subscriptionID}, {"includeHidden", v_includeHidden}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Invalid subscription id has been provided.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Sitemap with requested name does not exist.")}});
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
        return py::dict({{"error", py::s("Sitemap with requested name does not exist.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Invalid subscription id has been provided.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Sitemaps::getFullSitemap(const std::string& sitemapName, const std::optional<std::string>& subscriptionID, bool includeHidden, const std::optional<std::string>& language) {
    return py::finish([&] { return Sitemaps_getFullSitemap(*client_, py::arg(sitemapName), py::arg(subscriptionID), py::arg(includeHidden), py::arg(language)); });
}

json Sitemaps::getFullSitemap(const std::string& sitemapName, const GetFullSitemapArgs& a) {
    return getFullSitemap(sitemapName, a.subscriptionID, a.includeHidden, a.language);
}

static EventStream Sitemaps_getSitemapEvents(OpenHABClient& C, py::V v_subscriptionID, py::V v_sitemapName, py::V v_pageID) {
    (void)C;
    (void)v_subscriptionID;
    (void)v_sitemapName;
    (void)v_pageID;
    return Sitemaps_openEventStream(C, py::cat({py::s("/rest/sitemaps/events/"), v_subscriptionID}), py::dict({{"sitemap", v_sitemapName}, {"pageid", v_pageID}}), py::dict({{"400", py::s("Missing sitemap or page parameter, or page not linked successfully to the subscription.")}, {"404", py::s("Subscription not found.")}}));
}

EventStream Sitemaps::getSitemapEvents(const std::string& subscriptionID, const std::optional<std::string>& sitemapName, const std::optional<std::string>& pageID) {
    return py::finishStream([&] { return Sitemaps_getSitemapEvents(*client_, py::arg(subscriptionID), py::arg(sitemapName), py::arg(pageID)); });
}

EventStream Sitemaps::getSitemapEvents(const std::string& subscriptionID, const GetSitemapEventsArgs& a) {
    return getSitemapEvents(subscriptionID, a.sitemapName, a.pageID);
}

static EventStream Sitemaps_getFullSitemapEvents(OpenHABClient& C, py::V v_subscriptionID, py::V v_sitemapName) {
    (void)C;
    (void)v_subscriptionID;
    (void)v_sitemapName;
    return Sitemaps_openEventStream(C, py::cat({py::s("/rest/sitemaps/events/"), v_subscriptionID, py::s("/*")}), py::dict({{"sitemap", v_sitemapName}}), py::dict({{"400", py::s("Missing sitemap parameter, or sitemap not linked successfully to the subscription.")}, {"404", py::s("Subscription not found.")}}));
}

EventStream Sitemaps::getFullSitemapEvents(const std::string& subscriptionID, const std::optional<std::string>& sitemapName) {
    return py::finishStream([&] { return Sitemaps_getFullSitemapEvents(*client_, py::arg(subscriptionID), py::arg(sitemapName)); });
}

EventStream Sitemaps::getFullSitemapEvents(const std::string& subscriptionID, const GetFullSitemapEventsArgs& a) {
    return getFullSitemapEvents(subscriptionID, a.sitemapName);
}

static py::V Sitemaps_subscribeToSitemapEvents(OpenHABClient& C) {
    (void)C;
    py::V v_headers;
    py::V v_location;
    py::V v_response;
    py::V v_status_code;
    py::V v_value;
    try {
        v_response = py::http(C, "post", py::s("/sitemaps/events/subscribe"), py::V(), py::V(), py::V());
        v_location = py::V();
        if (py::isdict(v_response)) {
            v_location = py::getOr(v_response, py::s("location"));
            if (!py::truthy(v_location)) {
                v_headers = [&]() -> py::V { py::V t_ = py::getOr([&]() -> py::V { py::V t_ = py::getOr(v_response, py::s("context")); return py::truthy(t_) ? t_ : py::dict(); }(), py::s("headers")); return py::truthy(t_) ? t_ : py::dict(); }();
                v_value = py::getOr(v_headers, py::s("Location"));
                v_location = (py::truthy([&]() -> py::V { py::V t_ = py::V(json(py::islist(v_value))); return py::truthy(t_) ? v_value : t_; }()) ? py::V(py::get(v_value, py::V(json(0)))) : py::V(v_value));
            }
        }
        if (py::truthy(v_location)) {
            return py::dict({{"message", py::s("Subscription created.")}, {"location", v_location}, {"subscriptionID", py::get(py::split(py::rstrip(v_location, py::s("/")), py::s("/")), py::V(json(-1)))}});
        }
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(503)))) {
            return py::dict({{"error", py::s("Subscriptions limit reached.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(201)))) {
        return py::dict({{"message", py::s("Subscription created.")}});
    } else if (py::eq(v_status_code, py::V(json(503)))) {
        return py::dict({{"error", py::s("Subscriptions limit reached.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Sitemaps::subscribeToSitemapEvents() {
    return py::finish([&] { return Sitemaps_subscribeToSitemapEvents(*client_); });
}

}  // namespace openhab
