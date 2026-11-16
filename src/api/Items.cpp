// Generated from Items.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Items_getItems(OpenHABClient& C, py::V v_type, py::V v_tags, py::V v_metadata, py::V v_recursive, py::V v_fields, py::V v_staticDataOnly, py::V v_language, py::V v_parents);
static py::V Items_addOrUpdateItems(OpenHABClient& C, py::V v_items);
static py::V Items_getItem(OpenHABClient& C, py::V v_itemName, py::V v_metadata, py::V v_recursive, py::V v_language, py::V v_parents);
static py::V Items_addOrUpdateItem(OpenHABClient& C, py::V v_itemName, py::V v_itemData, py::V v_language);
static py::V Items_sendCommand(OpenHABClient& C, py::V v_itemName, py::V v_command, py::V v_source);
static py::V Items_postUpdate(OpenHABClient& C, py::V v_itemName, py::V v_state, py::V v_source);
static py::V Items_deleteItem(OpenHABClient& C, py::V v_itemName);
static py::V Items_addGroupMember(OpenHABClient& C, py::V v_itemName, py::V v_memberItemName);
static py::V Items_removeGroupMember(OpenHABClient& C, py::V v_itemName, py::V v_memberItemName);
static py::V Items_addMetadata(OpenHABClient& C, py::V v_itemName, py::V v_namespace, py::V v_metadata);
static py::V Items_removeMetadata(OpenHABClient& C, py::V v_itemName, py::V v_namespace);
static py::V Items_getMetadataNamespaces(OpenHABClient& C, py::V v_itemName, py::V v_language);
static py::V Items_getSemanticItem(OpenHABClient& C, py::V v_itemName, py::V v_semanticClass, py::V v_language);
static py::V Items_getItemState(OpenHABClient& C, py::V v_itemName);
static py::V Items_updateItemState(OpenHABClient& C, py::V v_itemName, py::V v_state, py::V v_language, py::V v_source);
static py::V Items_addTag(OpenHABClient& C, py::V v_itemName, py::V v_tag);
static py::V Items_removeTag(OpenHABClient& C, py::V v_itemName, py::V v_tag);
static py::V Items_purgeOrphanedMetadata(OpenHABClient& C);

static py::V Items_getItems(OpenHABClient& C, py::V v_type, py::V v_tags, py::V v_metadata, py::V v_recursive, py::V v_fields, py::V v_staticDataOnly, py::V v_language, py::V v_parents) {
    (void)C;
    (void)v_type;
    (void)v_tags;
    (void)v_metadata;
    (void)v_recursive;
    (void)v_fields;
    (void)v_staticDataOnly;
    (void)v_language;
    (void)v_parents;
    py::V v_headers;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    v_params = py::dict({{"type", v_type}, {"tags", v_tags}, {"metadata", v_metadata}, {"recursive", py::lower(py::str(v_recursive))}, {"fields", v_fields}, {"staticDataOnly", py::lower(py::str(v_staticDataOnly))}, {"parents", v_parents}});
    v_params = py::withoutNone(v_params);
    try {
        v_response = py::http(C, "get", py::s("/items"), v_headers, py::V(), v_params);
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

json Items::getItems(const std::optional<std::string>& type, const std::optional<std::string>& tags, const std::string& metadata, bool recursive, const std::optional<std::string>& fields, bool staticDataOnly, const std::optional<std::string>& language, const std::optional<bool>& parents) {
    return py::finish([&] { return Items_getItems(*client_, py::arg(type), py::arg(tags), py::arg(metadata), py::arg(recursive), py::arg(fields), py::arg(staticDataOnly), py::arg(language), py::arg(parents)); });
}

json Items::getItems(const GetItemsArgs& a) {
    return getItems(a.type, a.tags, a.metadata, a.recursive, a.fields, a.staticDataOnly, a.language, a.parents);
}

static py::V Items_addOrUpdateItems(OpenHABClient& C, py::V v_items) {
    (void)C;
    (void)v_items;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::s("/items"), py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("*/*")}}), py::dumps(v_items), py::V());
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

json Items::addOrUpdateItems(const json& items) {
    return py::finish([&] { return Items_addOrUpdateItems(*client_, py::arg(items)); });
}

static py::V Items_getItem(OpenHABClient& C, py::V v_itemName, py::V v_metadata, py::V v_recursive, py::V v_language, py::V v_parents) {
    (void)C;
    (void)v_itemName;
    (void)v_metadata;
    (void)v_recursive;
    (void)v_language;
    (void)v_parents;
    py::V v_headers;
    py::V v_params;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    v_params = py::dict({{"metadata", v_metadata}, {"recursive", py::lower(py::str(v_recursive))}, {"parents", v_parents}});
    try {
        v_response = py::http(C, "get", py::cat({py::s("/items/"), v_itemName}), v_headers, py::V(), v_params);
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
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
        return py::dict({{"error", py::s("Item not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::getItem(const std::string& itemName, const std::string& metadata, bool recursive, const std::optional<std::string>& language, const std::optional<bool>& parents) {
    return py::finish([&] { return Items_getItem(*client_, py::arg(itemName), py::arg(metadata), py::arg(recursive), py::arg(language), py::arg(parents)); });
}

json Items::getItem(const std::string& itemName, const GetItemArgs& a) {
    return getItem(itemName, a.metadata, a.recursive, a.language, a.parents);
}

static py::V Items_addOrUpdateItem(OpenHABClient& C, py::V v_itemName, py::V v_itemData, py::V v_language) {
    (void)C;
    (void)v_itemName;
    (void)v_itemData;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("application/json")}, {"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "put", py::cat({py::s("/items/"), v_itemName}), v_headers, py::dumps(v_itemData), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Payload invalid.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found or name in path invalid.")}});
        } else if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Item not editable.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(201)))) {
        return py::dict({{"message", py::s("Item created.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Payload invalid.")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Item not found or name in path invalid.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Item not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::addOrUpdateItem(const std::string& itemName, const json& itemData, const std::optional<std::string>& language) {
    return py::finish([&] { return Items_addOrUpdateItem(*client_, py::arg(itemName), py::arg(itemData), py::arg(language)); });
}

json Items::addOrUpdateItem(const std::string& itemName, const json& itemData, const AddOrUpdateItemArgs& a) {
    return addOrUpdateItem(itemName, itemData, a.language);
}

static py::V Items_sendCommand(OpenHABClient& C, py::V v_itemName, py::V v_command, py::V v_source) {
    (void)C;
    (void)v_itemName;
    (void)v_command;
    (void)v_source;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::cat({py::s("/items/"), v_itemName}), py::dict({{"Content-Type", py::s("text/plain")}}), py::str(v_command), py::dict({{"source", v_source}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Invalid command for this item.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
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
        return py::dict({{"error", py::s("Item not found.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Invalid command for this item.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::sendCommand(const std::string& itemName, const std::string& command, const std::optional<std::string>& source) {
    return py::finish([&] { return Items_sendCommand(*client_, py::arg(itemName), py::arg(command), py::arg(source)); });
}

json Items::sendCommand(const std::string& itemName, const std::string& command, const SendCommandArgs& a) {
    return sendCommand(itemName, command, a.source);
}

static py::V Items_postUpdate(OpenHABClient& C, py::V v_itemName, py::V v_state, py::V v_source) {
    (void)C;
    (void)v_itemName;
    (void)v_state;
    (void)v_source;
    return Items_updateItemState(C, v_itemName, v_state, py::V(), v_source);
}

json Items::postUpdate(const std::string& itemName, const std::string& state, const std::optional<std::string>& source) {
    return py::finish([&] { return Items_postUpdate(*client_, py::arg(itemName), py::arg(state), py::arg(source)); });
}

json Items::postUpdate(const std::string& itemName, const std::string& state, const PostUpdateArgs& a) {
    return postUpdate(itemName, state, a.source);
}

static py::V Items_deleteItem(OpenHABClient& C, py::V v_itemName) {
    (void)C;
    (void)v_itemName;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/items/"), v_itemName}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found or item is not editable.")}});
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
        return py::dict({{"error", py::s("Item not found or item is not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::deleteItem(const std::string& itemName) {
    return py::finish([&] { return Items_deleteItem(*client_, py::arg(itemName)); });
}

static py::V Items_addGroupMember(OpenHABClient& C, py::V v_itemName, py::V v_memberItemName) {
    (void)C;
    (void)v_itemName;
    (void)v_memberItemName;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/items/"), v_itemName, py::s("/members/"), v_memberItemName}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Member item is not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item or member item not found or item is not of type group item.")}});
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
        return py::dict({{"error", py::s("Item or member item not found or item is not of type group item.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Member item is not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::addGroupMember(const std::string& itemName, const std::string& memberItemName) {
    return py::finish([&] { return Items_addGroupMember(*client_, py::arg(itemName), py::arg(memberItemName)); });
}

static py::V Items_removeGroupMember(OpenHABClient& C, py::V v_itemName, py::V v_memberItemName) {
    (void)C;
    (void)v_itemName;
    (void)v_memberItemName;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/items/"), v_itemName, py::s("/members/"), v_memberItemName}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Member item is not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item or member item not found or item is not of type group item.")}});
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
        return py::dict({{"error", py::s("Item or member item not found or item is not of type group item.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Member item is not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::removeGroupMember(const std::string& itemName, const std::string& memberItemName) {
    return py::finish([&] { return Items_removeGroupMember(*client_, py::arg(itemName), py::arg(memberItemName)); });
}

static py::V Items_addMetadata(OpenHABClient& C, py::V v_itemName, py::V v_namespace, py::V v_metadata) {
    (void)C;
    (void)v_itemName;
    (void)v_namespace;
    (void)v_metadata;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/items/"), v_itemName, py::s("/metadata/"), v_namespace}), py::dict({{"Content-Type", py::s("application/json")}}), py::dumps(v_metadata), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Metadata value empty.")}});
        } else if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Metadata not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    } else if (py::eq(v_status_code, py::V(json(201)))) {
        return py::dict({{"message", py::s("Created.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Metadata value empty.")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Item not found.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Metadata not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::addMetadata(const std::string& itemName, const std::string& namespace_, const json& metadata) {
    return py::finish([&] { return Items_addMetadata(*client_, py::arg(itemName), py::arg(namespace_), py::arg(metadata)); });
}

static py::V Items_removeMetadata(OpenHABClient& C, py::V v_itemName, py::V v_namespace) {
    (void)C;
    (void)v_itemName;
    (void)v_namespace;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/items/"), v_itemName, py::s("/metadata/"), v_namespace}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Meta data not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
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
        return py::dict({{"error", py::s("Item not found.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Meta data not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::removeMetadata(const std::string& itemName, const std::string& namespace_) {
    return py::finish([&] { return Items_removeMetadata(*client_, py::arg(itemName), py::arg(namespace_)); });
}

static py::V Items_getMetadataNamespaces(OpenHABClient& C, py::V v_itemName, py::V v_language) {
    (void)C;
    (void)v_itemName;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/items/"), v_itemName, py::s("/metadata/namespaces")}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
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
        return py::dict({{"error", py::s("Item not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::getMetadataNamespaces(const std::string& itemName, const std::optional<std::string>& language) {
    return py::finish([&] { return Items_getMetadataNamespaces(*client_, py::arg(itemName), py::arg(language)); });
}

json Items::getMetadataNamespaces(const std::string& itemName, const GetMetadataNamespacesArgs& a) {
    return getMetadataNamespaces(itemName, a.language);
}

static py::V Items_getSemanticItem(OpenHABClient& C, py::V v_itemName, py::V v_semanticClass, py::V v_language) {
    (void)C;
    (void)v_itemName;
    (void)v_semanticClass;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/items/"), v_itemName, py::s("/semantic/"), v_semanticClass}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
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
        return py::dict({{"error", py::s("Item not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::getSemanticItem(const std::string& itemName, const std::string& semanticClass, const std::optional<std::string>& language) {
    return py::finish([&] { return Items_getSemanticItem(*client_, py::arg(itemName), py::arg(semanticClass), py::arg(language)); });
}

json Items::getSemanticItem(const std::string& itemName, const std::string& semanticClass, const GetSemanticItemArgs& a) {
    return getSemanticItem(itemName, semanticClass, a.language);
}

static py::V Items_getItemState(OpenHABClient& C, py::V v_itemName) {
    (void)C;
    (void)v_itemName;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("text/plain")}});
    try {
        v_response = py::http(C, "get", py::cat({py::s("/items/"), v_itemName, py::s("/state")}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
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
        return py::dict({{"error", py::s("Item not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::getItemState(const std::string& itemName) {
    return py::finish([&] { return Items_getItemState(*client_, py::arg(itemName)); });
}

static py::V Items_updateItemState(OpenHABClient& C, py::V v_itemName, py::V v_state, py::V v_language, py::V v_source) {
    (void)C;
    (void)v_itemName;
    (void)v_state;
    (void)v_language;
    (void)v_source;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("text/plain")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "put", py::cat({py::s("/items/"), v_itemName, py::s("/state")}), v_headers, py::str(v_state), py::dict({{"source", v_source}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Invalid state for this item.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
        } else {
            return py::dict({{"error", py::cat({py::s("HTTP error "), v_status_code, py::s(": "), py::excStr(e_err)})}});
        }
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_status_code, py::V(json(202)))) {
        return py::dict({{"message", py::s("Accepted.")}});
    } else if (py::eq(v_status_code, py::V(json(404)))) {
        return py::dict({{"error", py::s("Item not found.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Invalid state for this item.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::updateItemState(const std::string& itemName, const std::string& state, const std::optional<std::string>& language, const std::optional<std::string>& source) {
    return py::finish([&] { return Items_updateItemState(*client_, py::arg(itemName), py::arg(state), py::arg(language), py::arg(source)); });
}

json Items::updateItemState(const std::string& itemName, const std::string& state, const UpdateItemStateArgs& a) {
    return updateItemState(itemName, state, a.language, a.source);
}

static py::V Items_addTag(OpenHABClient& C, py::V v_itemName, py::V v_tag) {
    (void)C;
    (void)v_itemName;
    (void)v_tag;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "put", py::cat({py::s("/items/"), v_itemName, py::s("/tags/"), v_tag}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Item not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
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
        return py::dict({{"error", py::s("Item not found.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Item not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::addTag(const std::string& itemName, const std::string& tag) {
    return py::finish([&] { return Items_addTag(*client_, py::arg(itemName), py::arg(tag)); });
}

static py::V Items_removeTag(OpenHABClient& C, py::V v_itemName, py::V v_tag) {
    (void)C;
    (void)v_itemName;
    (void)v_tag;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "delete", py::cat({py::s("/items/"), v_itemName, py::s("/tags/"), v_tag}), py::V(), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("Item not editable.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Item not found.")}});
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
        return py::dict({{"error", py::s("Item not found.")}});
    } else if (py::eq(v_status_code, py::V(json(405)))) {
        return py::dict({{"error", py::s("Item not editable.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Items::removeTag(const std::string& itemName, const std::string& tag) {
    return py::finish([&] { return Items_removeTag(*client_, py::arg(itemName), py::arg(tag)); });
}

static py::V Items_purgeOrphanedMetadata(OpenHABClient& C) {
    (void)C;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::s("/items/metadata/purge"), py::V(), py::V(), py::V());
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

json Items::purgeOrphanedMetadata() {
    return py::finish([&] { return Items_purgeOrphanedMetadata(*client_); });
}

}  // namespace openhab
