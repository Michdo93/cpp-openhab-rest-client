#include "openhab/API.h"
namespace openhab {

static Headers json_h() { return {{"Content-Type","application/json"},{"Accept","application/json"}}; }
static Headers plain_h(){ return {{"Content-Type","text/plain"}}; }
static Headers acc_j()  { return {{"Accept","application/json"}}; }

json Rules::getRules(const std::string& prefix, const std::string& tags,
                     bool summary, bool staticOnly) {
    Params p;
    if (!prefix.empty()) p["prefix"] = prefix;
    if (!tags.empty())   p["tags"]   = tags;
    p["summary"] = summary ? "true":"false";
    p["staticDataOnly"] = staticOnly ? "true":"false";
    return c_.get("/rules", acc_j(), p).toJson();
}
json Rules::createRule(const json& data) { return c_.post("/rules", json_h(), data.dump()).toJson(); }
json Rules::getRule(const std::string& uid) { return c_.get("/rules/"+uid).toJson(); }
json Rules::updateRule(const std::string& uid, const json& data) {
    return c_.put("/rules/"+uid, json_h(), data.dump()).toJson(); }
json Rules::deleteRule(const std::string& uid) { return c_.del("/rules/"+uid).toJson(); }
json Rules::getModule(const std::string& uid, const std::string& cat, const std::string& mid) {
    return c_.get("/rules/"+uid+"/"+cat+"/"+mid).toJson(); }
json Rules::getModuleConfig(const std::string& uid, const std::string& cat, const std::string& mid) {
    return c_.get("/rules/"+uid+"/"+cat+"/"+mid+"/config").toJson(); }
json Rules::getModuleConfigParam(const std::string& uid, const std::string& cat,
                                  const std::string& mid, const std::string& param) {
    return c_.get("/rules/"+uid+"/"+cat+"/"+mid+"/config/"+param).toJson(); }
json Rules::setModuleConfigParam(const std::string& uid, const std::string& cat,
                                  const std::string& mid, const std::string& param,
                                  const std::string& value) {
    return c_.put("/rules/"+uid+"/"+cat+"/"+mid+"/config/"+param, plain_h(), value).toJson(); }
json Rules::getActions(const std::string& uid)       { return c_.get("/rules/"+uid+"/actions").toJson(); }
json Rules::getConditions(const std::string& uid)    { return c_.get("/rules/"+uid+"/conditions").toJson(); }
json Rules::getTriggers(const std::string& uid)      { return c_.get("/rules/"+uid+"/triggers").toJson(); }
json Rules::getConfiguration(const std::string& uid) { return c_.get("/rules/"+uid+"/config").toJson(); }
json Rules::updateConfiguration(const std::string& uid, const json& cfg) {
    return c_.put("/rules/"+uid+"/config", json_h(), cfg.dump()).toJson(); }
json Rules::setRuleState(const std::string& uid, bool enable) {
    return c_.post("/rules/"+uid+"/enable", plain_h(), enable?"true":"false").toJson(); }
json Rules::enable(const std::string& uid)  { return setRuleState(uid, true); }
json Rules::disable(const std::string& uid) { return setRuleState(uid, false); }
json Rules::runNow(const std::string& uid, const json& ctx) {
    if (ctx.is_null()) return c_.post("/rules/"+uid+"/runnow").toJson();
    return c_.post("/rules/"+uid+"/runnow", json_h(), ctx.dump()).toJson(); }
json Rules::simulateSchedule(const std::string& from, const std::string& until) {
    return c_.get("/rules/schedule/simulations", {}, {{"from",from},{"until",until}}).toJson(); }

} // namespace openhab
