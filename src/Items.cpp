#include "openhab/API.h"
namespace openhab {

static Headers json_h()  { return {{"Content-Type","application/json"},{"Accept","application/json"}}; }
static Headers plain_h() { return {{"Content-Type","text/plain"}}; }
static Headers acc_j()   { return {{"Accept","application/json"}}; }

json Items::getItems(const std::string& type, const std::string& tags,
                     const std::string& metadata, bool recursive,
                     const std::string& fields, bool staticOnly,
                     const std::string& language) {
    Headers h = acc_j();
    if (!language.empty()) h["Accept-Language"] = language;
    Params p;
    if (!type.empty())     p["type"]         = type;
    if (!tags.empty())     p["tags"]          = tags;
    if (!metadata.empty()) p["metadata"]      = metadata;
    p["recursive"]    = recursive  ? "true" : "false";
    p["staticDataOnly"] = staticOnly ? "true" : "false";
    if (!fields.empty())   p["fields"]        = fields;
    return c_.get("/items", h, p).toJson();
}

json Items::addOrUpdateItems(const json& items) {
    return c_.put("/items", json_h(), items.dump()).toJson();
}

json Items::getItem(const std::string& name, const std::string& metadata,
                    bool recursive, const std::string& lang) {
    Headers h = acc_j();
    if (!lang.empty()) h["Accept-Language"] = lang;
    return c_.get("/items/"+name, h,
        {{"metadata", metadata},{"recursive", recursive ? "true":"false"}}).toJson();
}

json Items::addOrUpdateItem(const std::string& name, const json& data,
                             const std::string& lang) {
    Headers h = json_h();
    if (!lang.empty()) h["Accept-Language"] = lang;
    return c_.put("/items/"+name, h, data.dump()).toJson();
}

json Items::sendCommand(const std::string& name, const std::string& cmd) {
    return c_.post("/items/"+name, plain_h(), cmd).toJson();
}

json Items::postUpdate(const std::string& name, const std::string& state) {
    return updateItemState(name, state);
}

json Items::deleteItem(const std::string& name) {
    return c_.del("/items/"+name).toJson();
}

json Items::addGroupMember(const std::string& name, const std::string& member) {
    return c_.put("/items/"+name+"/members/"+member).toJson();
}

json Items::removeGroupMember(const std::string& name, const std::string& member) {
    return c_.del("/items/"+name+"/members/"+member).toJson();
}

json Items::addMetadata(const std::string& name, const std::string& ns,
                         const json& metadata) {
    return c_.put("/items/"+name+"/metadata/"+ns,
        {{"Content-Type","application/json"}}, metadata.dump()).toJson();
}

json Items::removeMetadata(const std::string& name, const std::string& ns) {
    return c_.del("/items/"+name+"/metadata/"+ns).toJson();
}

json Items::getMetadataNamespaces(const std::string& name, const std::string& lang) {
    Headers h = acc_j();
    if (!lang.empty()) h["Accept-Language"] = lang;
    return c_.get("/items/"+name+"/metadata/namespaces", h).toJson();
}

json Items::getSemanticItem(const std::string& name, const std::string& semClass,
                             const std::string& lang) {
    Headers h = acc_j();
    if (!lang.empty()) h["Accept-Language"] = lang;
    return c_.get("/items/"+name+"/semantic/"+semClass, h).toJson();
}

json Items::getItemState(const std::string& name) {
    return c_.get("/items/"+name+"/state", {{"Accept","text/plain"}}).toJson();
}

json Items::updateItemState(const std::string& name, const std::string& state,
                             const std::string& lang) {
    Headers h = plain_h();
    if (!lang.empty()) h["Accept-Language"] = lang;
    return c_.put("/items/"+name+"/state", h, state).toJson();
}

json Items::addTag(const std::string& name, const std::string& tag) {
    return c_.put("/items/"+name+"/tags/"+tag).toJson();
}

json Items::removeTag(const std::string& name, const std::string& tag) {
    return c_.del("/items/"+name+"/tags/"+tag).toJson();
}

json Items::purgeOrphanedMetadata() {
    return c_.post("/items/metadata/purge").toJson();
}

} // namespace openhab
