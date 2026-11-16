// Runtime for the REST classes that tools/py2cpp.py generates from
// python-openhab-rest-client. Python values become py::V (a JSON value that also
// knows whether it is a StatusResponse); requests throw HTTPError/RequestException
// like requests does, and the generated code catches them where Python does.
#pragma once

#include "internal.hpp"

#include <initializer_list>
#include <optional>
#include <string>
#include <utility>

namespace openhab {
namespace py {

using detail::HTTPError;
using detail::RequestException;

struct V {
    json j;
    bool status = false;  // StatusResponse (empty answer with HTTP status)
    V() = default;
    V(json x) : j(std::move(x)) {}
    V(json x, bool s) : j(std::move(x)), status(s) {}
};

inline V s(const char* t) { return V(json(std::string(t))); }

// ── arguments of the public methods ──────────────────────────────────────────
inline V arg(const std::string& x) { return V(json(x)); }
inline V arg(const std::optional<std::string>& x) { return x ? V(json(*x)) : V(); }
inline V arg(bool x) { return V(json(x)); }
inline V arg(const std::optional<bool>& x) { return x ? V(json(*x)) : V(); }
inline V arg(int x) { return V(json(x)); }
inline V arg(const std::optional<int>& x) { return x ? V(json(*x)) : V(); }
inline V arg(double x) { return V(json(x)); }
inline V arg(const std::optional<double>& x) { return x ? V(json(*x)) : V(); }
inline V arg(const json& x) { return V(x); }

// ── truth and comparison ─────────────────────────────────────────────────────
inline bool isnone(const V& v) { return v.j.is_null(); }

inline bool truthy(const V& v) {
    const json& j = v.j;
    if (j.is_null()) return false;
    if (j.is_boolean()) return j.get<bool>();
    if (j.is_number()) return j.get<double>() != 0;
    if (j.is_string()) return !j.get_ref<const std::string&>().empty();
    if (j.is_array() || j.is_object()) return !j.empty() || v.status;
    return true;
}

bool eq(const V& a, const V& b);
int cmp(const V& a, const V& b);
bool contains(const V& container, const V& x);

// ── strings ──────────────────────────────────────────────────────────────────
V str(const V& v);
V cat(std::initializer_list<V> parts);
V lower(const V& s);
V strip(const V& s);
V rstrip(const V& s, const V& chars);
V split(const V& s, const V& sep);
V join(const V& sep, const V& items);
V len(const V& v);

inline bool isdict(const V& v) { return v.j.is_object() && !v.status; }
inline bool islist(const V& v) { return v.j.is_array(); }
inline bool isstr(const V& v) { return v.j.is_string(); }
inline bool isbool(const V& v) { return v.j.is_boolean(); }
inline bool isstatus(const V& v) { return v.status; }

// ── containers ───────────────────────────────────────────────────────────────
V dict();
V dict(std::initializer_list<std::pair<const char*, V>> items);
V list();
V list(std::initializer_list<V> items);
V copy(const V& m);
V withoutNone(const V& m);
V get(const V& obj, const V& key);
V getOr(const V& obj, const V& key, const V& dflt = V());
void set(V& obj, const V& key, const V& value);

// ── encoding ─────────────────────────────────────────────────────────────────
V quote(const V& s, const char* safe);
V urlencode(const V& params);
V dumps(const V& v);

// ── HTTP and streams ─────────────────────────────────────────────────────────
V http(OpenHABClient& c, const char* verb, const V& path, const V& headers, const V& data,
       const V& params);
EventStream sse(OpenHABClient& c, const V& path, const V& headers, const V& params);
EventStream openStream(OpenHABClient& c, const V& topics, const V& path, const V& headers,
                       const V& errors);
EventStream asStream(const V& v);
inline V excStatus(const RequestException& e) { return V(json(e.status)); }
inline V excStr(const RequestException& e) { return V(json(std::string(e.what()))); }

// ── public results ───────────────────────────────────────────────────────────
json errorObject(const RequestException& e, bool http);

template <class F>
json finish(F&& f) {
    try {
        return f().j;
    } catch (const HTTPError& e) {
        return errorObject(e, true);
    } catch (const RequestException& e) {
        return errorObject(e, false);
    }
}

template <class F>
EventStream finishStream(F&& f) {
    try {
        return f();
    } catch (const HTTPError& e) {
        return EventStream::failed(errorObject(e, true)["error"].get<std::string>(), e.status);
    } catch (const RequestException& e) {
        return EventStream::failed(errorObject(e, false)["error"].get<std::string>(), 0);
    }
}

}  // namespace py
}  // namespace openhab
