// Runtime for the generated REST classes – see py_rt.hpp.
#include "py_rt.hpp"

#include <cstring>

namespace openhab {
namespace py {

static bool numeric(const json& v, double& d) {
    if (v.is_number()) { d = v.get<double>(); return true; }
    if (v.is_boolean()) { d = v.get<bool>() ? 1 : 0; return true; }
    return false;
}

bool eq(const V& a, const V& b) {
    double x, y;
    if (a.j.is_null() || b.j.is_null()) return a.j.is_null() && b.j.is_null();
    if (numeric(a.j, x) && numeric(b.j, y)) return x == y;
    return a.j == b.j;
}

int cmp(const V& a, const V& b) {
    double x = 0, y = 0;
    numeric(a.j, x);
    numeric(b.j, y);
    return x < y ? -1 : x > y;
}

static std::optional<std::string> keyText(const json& k) {
    if (k.is_string()) return k.get<std::string>();
    if (k.is_number_integer()) return std::to_string(k.get<long long>());
    return std::nullopt;
}

bool contains(const V& c, const V& x) {
    if (c.j.is_object()) {
        auto k = keyText(x.j);
        return k && c.j.contains(*k);
    }
    if (c.j.is_array()) {
        for (const auto& e : c.j)
            if (eq(V(e), x)) return true;
        return false;
    }
    if (c.j.is_string() && x.j.is_string())
        return c.j.get_ref<const std::string&>().find(x.j.get_ref<const std::string&>()) !=
               std::string::npos;
    return false;
}

V str(const V& v) { return V(json(detail::pyStr(v.j, true))); }

V cat(std::initializer_list<V> parts) {
    std::string b;
    for (const V& p : parts) b += detail::pyStr(p.j, true);
    return V(json(b));
}

static std::string text(const V& s) { return s.j.is_string() ? s.j.get<std::string>() : ""; }

V lower(const V& s) {
    std::string t = s.j.is_string() ? s.j.get<std::string>() : detail::pyStr(s.j);
    for (char& ch : t)
        if (ch >= 'A' && ch <= 'Z') ch = static_cast<char>(ch - 'A' + 'a');
    return V(json(t));
}

V strip(const V& s) {
    std::string t = text(s);
    size_t a = t.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return V(json(""));
    size_t b = t.find_last_not_of(" \t\r\n");
    return V(json(t.substr(a, b - a + 1)));
}

V rstrip(const V& s, const V& chars) {
    std::string t = text(s), c = text(chars);
    while (!t.empty() && c.find(t.back()) != std::string::npos) t.pop_back();
    return V(json(t));
}

V split(const V& s, const V& sep) {
    json l = json::array();
    std::string t = text(s), d = text(sep);
    size_t p = 0;
    for (;;) {
        size_t q = d.empty() ? std::string::npos : t.find(d, p);
        l.push_back(t.substr(p, q == std::string::npos ? std::string::npos : q - p));
        if (q == std::string::npos) break;
        p = q + d.size();
    }
    return V(l);
}

V join(const V& sep, const V& items) {
    std::string b, d = text(sep);
    bool first = true;
    if (items.j.is_array())
        for (const auto& e : items.j) {
            if (!first) b += d;
            first = false;
            b += detail::pyStr(e, true);
        }
    return V(json(b));
}

V len(const V& v) {
    if (v.j.is_string()) return V(json(v.j.get_ref<const std::string&>().size()));
    if (v.j.is_array() || v.j.is_object()) return V(json(v.j.size()));
    return V(json(0));
}

V dict() { return V(json::object()); }

V dict(std::initializer_list<std::pair<const char*, V>> items) {
    json d = json::object();
    for (const auto& kv : items) d[kv.first] = kv.second.j;
    return V(d);
}

V list() { return V(json::array()); }

V list(std::initializer_list<V> items) {
    json l = json::array();
    for (const V& v : items) l.push_back(v.j);
    return V(l);
}

V copy(const V& m) { return m.j.is_null() ? V(json::object()) : V(m.j); }

V withoutNone(const V& m) {
    json d = json::object();
    if (m.j.is_object())
        for (auto it = m.j.begin(); it != m.j.end(); ++it)
            if (!it.value().is_null()) d[it.key()] = it.value();
    return V(d);
}

V get(const V& obj, const V& key) {
    if (obj.j.is_object()) {
        auto k = keyText(key.j);
        if (k) {
            auto it = obj.j.find(*k);
            if (it != obj.j.end()) return V(*it);
        }
    } else if (obj.j.is_array() && key.j.is_number_integer()) {
        long long i = key.j.get<long long>();
        if (i < 0) i += static_cast<long long>(obj.j.size());
        if (i >= 0 && static_cast<size_t>(i) < obj.j.size()) return V(obj.j[static_cast<size_t>(i)]);
    }
    return V();
}

V getOr(const V& obj, const V& key, const V& dflt) {
    auto k = keyText(key.j);
    if (obj.j.is_object() && k && obj.j.contains(*k)) return get(obj, key);
    return dflt;
}

void set(V& obj, const V& key, const V& value) {
    if (!obj.j.is_object()) return;
    auto k = keyText(key.j);
    if (k) obj.j[*k] = value.j;
}

V quote(const V& s, const char* safe) {
    std::string t = s.j.is_string() ? s.j.get<std::string>() : detail::pyStr(s.j);
    return V(json(detail::quote(t, safe)));
}

V urlencode(const V& params) { return V(json(detail::queryString(params.j))); }

V dumps(const V& v) {
    // Python's json.dumps puts a space after ":" and "," – openHAB does not care,
    // but the text is the same as in the other libraries of the family.
    return V(json(v.j.dump()));
}

V http(OpenHABClient& c, const char* verb, const V& path, const V& headers, const V& data,
       const V& params) {
    detail::Reply r = detail::request(c.impl(), verb, text(path), headers.j, data.j, params.j);
    return V(std::move(r.value), r.isStatus);
}

EventStream sse(OpenHABClient& c, const V& path, const V& headers, const V& params) {
    EventStream s = detail::openStream(c.impl(), text(path), headers.j, params.j);
    if (s.isError()) {
        int st = s.errorStatus();
        if (st) throw HTTPError(s.error(), st);
        throw RequestException(s.error(), 0);
    }
    return s;
}

EventStream openStream(OpenHABClient& c, const V& topics, const V& path, const V& headers,
                       const V& errors) {
    json params = nullptr;
    if (truthy(topics)) params = json{{"topics", topics.j}};
    std::string p = path.j.is_string() ? path.j.get<std::string>() : "/rest/events";
    EventStream s = detail::openStream(c.impl(), p, headers.j, params);
    if (!s.isError()) return s;
    int status = s.errorStatus();
    std::string key = std::to_string(status);
    std::string msg;
    if (status && errors.j.is_object() && errors.j.contains(key) && errors.j[key].is_string())
        msg = errors.j[key].get<std::string>();
    else if (status)
        msg = "HTTP error " + key + ": " + s.error();
    else
        msg = "Request error: " + s.error();
    return EventStream::failed(msg, status);
}

EventStream asStream(const V& v) {
    std::string e = errorMessage(v.j);
    return EventStream::failed(e.empty() ? "no event stream" : e, 0);
}

json errorObject(const RequestException& e, bool http) {
    if (http) return json{{"error", "HTTP error " + std::to_string(e.status) + ": " + e.what()}};
    return json{{"error", std::string("Request error: ") + e.what()}};
}

}  // namespace py
}  // namespace openhab
