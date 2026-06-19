#include "openhab/API.h"
namespace openhab {

static Headers json_h()  { return {{"Content-Type","application/json"},{"Accept","application/json"}}; }
static Headers plain_h() { return {{"Content-Type","text/plain"}}; }
static Headers acc_j()   { return {{"Accept","application/json"}}; }

json Things::getThings(bool summary, bool staticOnly, const std::string& lang) {
    Headers h = acc_j();
    if (!lang.empty()) h["Accept-Language"] = lang;
    return c_.get("/things", h, {{"summary", summary?"true":"false"},
        {"staticDataOnly", staticOnly?"true":"false"}}).toJson();
}
json Things::createThing(const json& data, const std::string& lang) {
    Headers h = json_h(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.post("/things", h, data.dump()).toJson();
}
json Things::getThing(const std::string& uid, const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.get("/things/"+uid, h).toJson();
}
json Things::updateThing(const std::string& uid, const json& data, const std::string& lang) {
    Headers h = json_h(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.put("/things/"+uid, h, data.dump()).toJson();
}
json Things::deleteThing(const std::string& uid, bool force, const std::string& lang) {
    Headers h; if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.del("/things/"+uid, h, "", {{"force", force?"true":"false"}}).toJson();
}
json Things::updateThingConfiguration(const std::string& uid, const json& cfg, const std::string& lang) {
    Headers h = json_h(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.put("/things/"+uid+"/config", h, cfg.dump()).toJson();
}
json Things::getThingConfigStatus(const std::string& uid, const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.get("/things/"+uid+"/config/status", h).toJson();
}
json Things::setThingStatus(const std::string& uid, bool enabled, const std::string& lang) {
    Headers h = plain_h(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.put("/things/"+uid+"/enable", h, enabled?"true":"false").toJson();
}
json Things::enableThing(const std::string& uid)  { return setThingStatus(uid, true); }
json Things::disableThing(const std::string& uid) { return setThingStatus(uid, false); }
json Things::updateThingFirmware(const std::string& uid, const std::string& ver, const std::string& lang) {
    Headers h; h["Content-Type"]="application/json"; if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.put("/things/"+uid+"/firmware/"+ver, h).toJson();
}
json Things::getThingFirmwareStatus(const std::string& uid, const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.get("/things/"+uid+"/firmware/status", h).toJson();
}
json Things::getThingFirmwares(const std::string& uid, const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.get("/things/"+uid+"/firmwares", h).toJson();
}
json Things::getThingStatus(const std::string& uid, const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.get("/things/"+uid+"/status", h).toJson();
}

} // namespace openhab
