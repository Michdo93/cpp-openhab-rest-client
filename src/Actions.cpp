#include "openhab/API.h"
#include <sstream>
namespace openhab {

static Headers json_h() { return {{"Content-Type","application/json"},{"Accept","application/json"}}; }
static Headers plain_h(){ return {{"Content-Type","text/plain"}}; }
static Headers acc_j()  { return {{"Accept","application/json"}}; }

// ── Actions ───────────────────────────────────────────────────────────────────
json Actions::getActions(const std::string& uid, const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.get("/actions/"+uid, h).toJson(); }
json Actions::executeAction(const std::string& uid, const std::string& actionUID,
                            const json& inputs, const std::string& lang) {
    Headers h = json_h(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.post("/actions/"+uid+"/"+actionUID, h, inputs.dump()).toJson(); }

// ── Addons ────────────────────────────────────────────────────────────────────
json Addons::getAddons(const std::string& svc, const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    Params p; if (!svc.empty()) p["serviceId"]=svc;
    return c_.get("/addons", h, p).toJson(); }
json Addons::getAddon(const std::string& id, const std::string& svc, const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    Params p; if (!svc.empty()) p["serviceId"]=svc;
    return c_.get("/addons/"+id, h, p).toJson(); }
json Addons::getAddonConfig(const std::string& id, const std::string& svc) {
    Params p; if (!svc.empty()) p["serviceId"]=svc;
    return c_.get("/addons/"+id+"/config", {}, p).toJson(); }
json Addons::updateAddonConfig(const std::string& id, const json& cfg, const std::string& svc) {
    Params p; if (!svc.empty()) p["serviceId"]=svc;
    return c_.put("/addons/"+id+"/config", {{"Content-Type","application/json"}}, cfg.dump(), p).toJson(); }
json Addons::installAddon(const std::string& id, const std::string& svc) {
    Params p; if (!svc.empty()) p["serviceId"]=svc;
    return c_.post("/addons/"+id+"/install", {}, "", p).toJson(); }
json Addons::uninstallAddon(const std::string& id, const std::string& svc) {
    Params p; if (!svc.empty()) p["serviceId"]=svc;
    return c_.post("/addons/"+id+"/uninstall", {}, "", p).toJson(); }
json Addons::getAddonServices(const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.get("/addons/services", h).toJson(); }
json Addons::getAddonSuggestions(const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    return c_.get("/addons/suggestions", h).toJson(); }
json Addons::getAddonTypes(const std::string& svc, const std::string& lang) {
    Headers h = acc_j(); if (!lang.empty()) h["Accept-Language"]=lang;
    Params p; if (!svc.empty()) p["serviceId"]=svc;
    return c_.get("/addons/types", h, p).toJson(); }
json Addons::installAddonFromUrl(const std::string& url) {
    return c_.post("/addons/url", plain_h(), url).toJson(); }

// ── Audio ─────────────────────────────────────────────────────────────────────
json Audio::getDefaultSink(const std::string& lang)   { Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang; return c_.get("/audio/defaultsink",h).toJson(); }
json Audio::getDefaultSource(const std::string& lang) { Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang; return c_.get("/audio/defaultsource",h).toJson(); }
json Audio::getSinks(const std::string& lang)         { Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang; return c_.get("/audio/sinks",h).toJson(); }
json Audio::getSources(const std::string& lang)       { Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang; return c_.get("/audio/sources",h).toJson(); }

// ── Auth ──────────────────────────────────────────────────────────────────────
json Auth::getAPITokens()                     { return c_.get("/auth/apitokens").toJson(); }
json Auth::revokeAPIToken(const std::string& n){ return c_.del("/auth/apitokens/"+n).toJson(); }
json Auth::logout(const std::string& rt, const std::string& sid) {
    return c_.del("/auth/logout",{},""  ,{{"refreshToken",rt},{"sessionId",sid}}).toJson(); }
json Auth::getSessions() { return c_.get("/auth/sessions").toJson(); }
json Auth::getToken(const std::string& gt, const std::string& code,
                    const std::string& ruri, const std::string& cid,
                    const std::string& rt,   const std::string& cv) {
    std::string body;
    auto add = [&](const std::string& k, const std::string& v) {
        if (v.empty()) return;
        if (!body.empty()) body += "&";
        body += k + "=" + v;
    };
    add("grant_type",   gt); add("code",         code);
    add("redirect_uri", ruri); add("client_id",  cid);
    add("refresh_token",rt);   add("code_verifier",cv);
    return c_.post("/auth/token",{{"Content-Type","application/x-www-form-urlencoded"}},body).toJson(); }

// ── ChannelTypes ──────────────────────────────────────────────────────────────
json ChannelTypes::getChannelTypes(const std::string& pre, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    Params p; if(!pre.empty())p["prefixes"]=pre;
    return c_.get("/channel-types",h,p).toJson(); }
json ChannelTypes::getChannelType(const std::string& uid, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/channel-types/"+uid,h).toJson(); }
json ChannelTypes::getLinkableItemTypes(const std::string& uid) {
    return c_.get("/channel-types/"+uid+"/linkableItemTypes").toJson(); }

// ── ConfigDescriptions ────────────────────────────────────────────────────────
json ConfigDescriptions::getConfigDescriptions(const std::string& scheme, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    Params p; if(!scheme.empty())p["scheme"]=scheme;
    return c_.get("/config-descriptions",h,p).toJson(); }
json ConfigDescriptions::getConfigDescription(const std::string& uri, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/config-descriptions/"+uri,h).toJson(); }

// ── Discovery ─────────────────────────────────────────────────────────────────
json Discovery::getDiscoveryBindings() { return c_.get("/discovery").toJson(); }
json Discovery::getBindingInfo(const std::string& id, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/bindings/"+id,h).toJson(); }
json Discovery::startBindingScan(const std::string& id, const std::string& input) {
    return c_.post("/discovery/bindings/"+id+"/scan",{},input).toJson(); }

// ── Iconsets ──────────────────────────────────────────────────────────────────
json Iconsets::getIconsets(const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/iconsets",h).toJson(); }

// ── Inbox ─────────────────────────────────────────────────────────────────────
json Inbox::getDiscoveredThings(bool includeIgnored) {
    return c_.get("/inbox",{},{{"includeIgnored",includeIgnored?"true":"false"}}).toJson(); }
json Inbox::removeDiscoveryResult(const std::string& uid) { return c_.del("/inbox/"+uid).toJson(); }
json Inbox::approveDiscoveryResult(const std::string& uid, const std::string& label,
                                    const std::string& newId, const std::string& lang) {
    Headers h=plain_h(); if(!lang.empty())h["Accept-Language"]=lang;
    Params p; if(!newId.empty())p["newThingId"]=newId;
    return c_.post("/inbox/"+uid+"/approve",h,label,p).toJson(); }
json Inbox::ignoreDiscoveryResult(const std::string& uid)   { return c_.post("/inbox/"+uid+"/ignore").toJson(); }
json Inbox::unignoreDiscoveryResult(const std::string& uid) { return c_.post("/inbox/"+uid+"/unignore").toJson(); }

// ── Links ─────────────────────────────────────────────────────────────────────
json Links::getLinks(const std::string& ch, const std::string& item) {
    Params p; if(!ch.empty())p["channelUID"]=ch; if(!item.empty())p["itemName"]=item;
    return c_.get("/links",{},p).toJson(); }
json Links::getLink(const std::string& item, const std::string& ch) {
    return c_.get("/links/"+item+"/"+ch).toJson(); }
json Links::linkItemToChannel(const std::string& item, const std::string& ch, const json& cfg) {
    return c_.put("/links/"+item+"/"+ch,{{"Content-Type","application/json"}},cfg.dump()).toJson(); }
json Links::unlinkItemFromChannel(const std::string& item, const std::string& ch) {
    return c_.del("/links/"+item+"/"+ch).toJson(); }
json Links::deleteAllLinks(const std::string& obj)  { return c_.del("/links/"+obj).toJson(); }
json Links::getOrphanLinks()                        { return c_.get("/links/orphan").toJson(); }
json Links::purgeUnusedLinks()                      { return c_.post("/links/purge").toJson(); }

// ── Logging ───────────────────────────────────────────────────────────────────
json Logging::getLoggers()                        { return c_.get("/loggers").toJson(); }
json Logging::getLogger(const std::string& n)     { return c_.get("/loggers/"+n).toJson(); }
json Logging::modifyOrAddLogger(const std::string& n, const std::string& lvl) {
    json body = {{"level", lvl}};
    return c_.put("/loggers/"+n,{{"Content-Type","application/json"}},body.dump()).toJson(); }
json Logging::removeLogger(const std::string& n)  { return c_.del("/loggers/"+n).toJson(); }

// ── ModuleTypes ───────────────────────────────────────────────────────────────
json ModuleTypes::getModuleTypes(const std::string& tags, const std::string& tf,
                                  const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    Params p; if(!tags.empty())p["tags"]=tags; if(!tf.empty())p["type"]=tf;
    return c_.get("/module-types",h,p).toJson(); }
json ModuleTypes::getModuleType(const std::string& uid, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/module-types/"+uid,h).toJson(); }

// ── Persistence ───────────────────────────────────────────────────────────────
json Persistence::getServices(const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/persistence",h).toJson(); }
json Persistence::getServiceConfiguration(const std::string& id) { return c_.get("/persistence/"+id).toJson(); }
json Persistence::setServiceConfiguration(const std::string& id, const json& cfg) {
    return c_.put("/persistence/"+id,{{"Content-Type","application/json"}},cfg.dump()).toJson(); }
json Persistence::deleteServiceConfiguration(const std::string& id) { return c_.del("/persistence/"+id).toJson(); }
json Persistence::getItemsFromService(const std::string& svc) {
    Params p; if(!svc.empty())p["serviceId"]=svc;
    return c_.get("/persistence/items",{},p).toJson(); }
json Persistence::getItemPersistenceData(const std::string& item, const std::string& svc,
                                          const std::string& st, const std::string& et,
                                          int page, int pl, bool boundary, bool itemState) {
    Params p{{"serviceId",svc},{"page",std::to_string(page)},{"pagelength",std::to_string(pl)},
             {"boundary",boundary?"true":"false"},{"itemState",itemState?"true":"false"}};
    if(!st.empty())p["starttime"]=st; if(!et.empty())p["endtime"]=et;
    return c_.get("/persistence/items/"+item,{},p).toJson(); }
json Persistence::storeItemData(const std::string& item, const std::string& time,
                                 const std::string& state, const std::string& svc) {
    Params p{{"time",time}}; if(!svc.empty())p["serviceId"]=svc;
    return c_.put("/persistence/items/"+item,plain_h(),state,p).toJson(); }
json Persistence::deleteItemData(const std::string& item, const std::string& st,
                                  const std::string& et, const std::string& svc) {
    return c_.del("/persistence/items/"+item,{},""
        ,{{"serviceId",svc},{"starttime",st},{"endtime",et}}).toJson(); }

// ── ProfileTypes ──────────────────────────────────────────────────────────────
json ProfileTypes::getProfileTypes(const std::string& ch, const std::string& it,
                                    const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    Params p; if(!ch.empty())p["channelTypeUID"]=ch; if(!it.empty())p["itemType"]=it;
    return c_.get("/profile-types",h,p).toJson(); }

// ── Services ──────────────────────────────────────────────────────────────────
json Services::getServices(const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/services",h).toJson(); }
json Services::getService(const std::string& id, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/services/"+id,h).toJson(); }
json Services::getServiceConfig(const std::string& id)  { return c_.get("/services/"+id+"/config").toJson(); }
json Services::updateServiceConfig(const std::string& id, const json& cfg, const std::string& lang) {
    Headers h={{"Content-Type","application/json"}}; if(!lang.empty())h["Accept-Language"]=lang;
    return c_.put("/services/"+id+"/config",h,cfg.dump()).toJson(); }
json Services::deleteServiceConfig(const std::string& id) { return c_.del("/services/"+id+"/config").toJson(); }
json Services::getServiceContexts(const std::string& id, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/services/"+id+"/contexts",h).toJson(); }

// ── Sitemaps ──────────────────────────────────────────────────────────────────
json Sitemaps::getSitemaps() { return c_.get("/sitemaps").toJson(); }
json Sitemaps::getSitemap(const std::string& name, const std::string& type,
                           bool hidden, const std::string& lang) {
    Headers h; if(!lang.empty())h["Accept-Language"]=lang;
    Params p; if(!type.empty())p["type"]=type; p["includeHidden"]=hidden?"true":"false";
    return c_.get("/sitemaps/"+name,h,p).toJson(); }
json Sitemaps::getSitemapPage(const std::string& name, const std::string& pageId,
                               const std::string& subId, bool hidden, const std::string& lang) {
    Headers h; if(!lang.empty())h["Accept-Language"]=lang;
    Params p; if(!subId.empty())p["subscriptionid"]=subId; p["includeHidden"]=hidden?"true":"false";
    return c_.get("/sitemaps/"+name+"/"+pageId,h,p).toJson(); }
SSEConnection Sitemaps::getSitemapEvents(const std::string& subId,
                                          const std::string& sn, const std::string& pid) {
    std::string url = c_.baseUrl()+"/rest/sitemaps/events/"+subId;
    if(!sn.empty())  url += "?sitemap="+sn;
    if(!pid.empty()) url += (sn.empty()?"?":"&") + std::string("pageid="+pid);
    return c_.sse(url); }
json Sitemaps::subscribeToSitemapEvents() { return c_.post("/sitemaps/events/subscribe").toJson(); }

// ── Systeminfo ────────────────────────────────────────────────────────────────
json Systeminfo::getSystemInfo() { return c_.get("/systeminfo").toJson(); }
json Systeminfo::getUoMInfo()    { return c_.get("/systeminfo/uom").toJson(); }

// ── Tags ──────────────────────────────────────────────────────────────────────
json Tags::getTags(const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/tags",h).toJson(); }
json Tags::createTag(const json& data, const std::string& lang) {
    Headers h={{"Content-Type","application/json"}}; if(!lang.empty())h["Accept-Language"]=lang;
    return c_.post("/tags",h,data.dump()).toJson(); }
json Tags::getTag(const std::string& id, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/tags/"+id,h).toJson(); }
json Tags::updateTag(const std::string& id, const json& data, const std::string& lang) {
    Headers h={{"Content-Type","application/json"}}; if(!lang.empty())h["Accept-Language"]=lang;
    return c_.put("/tags/"+id,h,data.dump()).toJson(); }
json Tags::deleteTag(const std::string& id, const std::string& lang) {
    Headers h; if(!lang.empty())h["Accept-Language"]=lang;
    return c_.del("/tags/"+id,h).toJson(); }

// ── Templates ─────────────────────────────────────────────────────────────────
json Templates::getTemplates(const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/templates",h).toJson(); }
json Templates::getTemplate(const std::string& uid, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/templates/"+uid,h).toJson(); }

// ── ThingTypes ────────────────────────────────────────────────────────────────
json ThingTypes::getThingTypes(const std::string& bindingId, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    Params p; if(!bindingId.empty())p["bindingId"]=bindingId;
    return c_.get("/thing-types",h,p).toJson(); }
json ThingTypes::getThingType(const std::string& uid, const std::string& lang) {
    Headers h=acc_j(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/thing-types/"+uid,h).toJson(); }

// ── Transformations ───────────────────────────────────────────────────────────
json Transformations::getTransformations()                  { return c_.get("/transformations").toJson(); }
json Transformations::getTransformation(const std::string& uid) { return c_.get("/transformations/"+uid).toJson(); }
json Transformations::updateTransformation(const std::string& uid, const json& data) {
    return c_.put("/transformations/"+uid,{{"Content-Type","application/json"}},data.dump()).toJson(); }
json Transformations::deleteTransformation(const std::string& uid) { return c_.del("/transformations/"+uid).toJson(); }
json Transformations::getTransformationServices()           { return c_.get("/transformations/services").toJson(); }

// ── UI ────────────────────────────────────────────────────────────────────────
json UI::getUIComponents(const std::string& ns, bool summary) {
    return c_.get("/ui/components/"+ns,{},{{"summary",summary?"true":"false"}}).toJson(); }
json UI::addUIComponent(const std::string& ns, const json& data) {
    return c_.post("/ui/components/"+ns,{{"Content-Type","application/json"}},data.dump()).toJson(); }
json UI::getUIComponent(const std::string& ns, const std::string& uid) {
    return c_.get("/ui/components/"+ns+"/"+uid).toJson(); }
json UI::updateUIComponent(const std::string& ns, const std::string& uid, const json& data) {
    return c_.put("/ui/components/"+ns+"/"+uid,{{"Content-Type","application/json"}},data.dump()).toJson(); }
json UI::deleteUIComponent(const std::string& ns, const std::string& uid) {
    return c_.del("/ui/components/"+ns+"/"+uid).toJson(); }
json UI::getUITiles() { return c_.get("/ui/tiles").toJson(); }

// ── UUID ──────────────────────────────────────────────────────────────────────
json UUID::getUUID() { return c_.get("/uuid").toJson(); }

// ── Voice ─────────────────────────────────────────────────────────────────────
json Voice::getDefaultVoice() { return c_.get("/voice/defaultvoice").toJson(); }
json Voice::startDialog(const std::string& sid, const std::string& ks,
                        const std::string& stt, const std::string& tts,
                        const std::string& v,   const std::string& hli,
                        const std::string& sink,const std::string& kw,
                        const std::string& li) {
    Params p{{"sourceId",sid}};
    if(!ks.empty())   p["ksId"]          = ks;
    if(!stt.empty())  p["sttId"]         = stt;
    if(!tts.empty())  p["ttsId"]         = tts;
    if(!v.empty())    p["voiceId"]       = v;
    if(!hli.empty())  p["hliIds"]        = hli;
    if(!sink.empty()) p["sinkId"]        = sink;
    if(!kw.empty())   p["keyword"]       = kw;
    if(!li.empty())   p["listeningItem"] = li;
    return c_.post("/voice/dialog/start",{},""  ,p).toJson(); }
json Voice::stopDialog(const std::string& sid) {
    return c_.post("/voice/dialog/stop",{},{},{{"sourceId",sid}}).toJson(); }
json Voice::getInterpreters(const std::string& lang) {
    Headers h; if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/voice/interpreters",h).toJson(); }
json Voice::interpretText(const std::string& text, const std::string& lang) {
    Headers h=plain_h(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.post("/voice/interpreters",h,text).toJson(); }
json Voice::getInterpreter(const std::string& id, const std::string& lang) {
    Headers h; if(!lang.empty())h["Accept-Language"]=lang;
    return c_.get("/voice/interpreters/"+id,h).toJson(); }
json Voice::interpretTextBatch(const std::string& text, const std::string& ids,
                                const std::string& lang) {
    Headers h=plain_h(); if(!lang.empty())h["Accept-Language"]=lang;
    return c_.post("/voice/interpreters/"+ids,h,text).toJson(); }
json Voice::listenAndAnswer(const std::string& sid, const std::string& stt,
                             const std::string& tts, const std::string& v,
                             const std::string& hli, const std::string& sink,
                             const std::string& li) {
    Params p{{"sourceId",sid},{"sttId",stt},{"ttsId",tts},{"voiceId",v}};
    if(!hli.empty())  p["hliIds"]        = hli;
    if(!sink.empty()) p["sinkId"]        = sink;
    if(!li.empty())   p["listeningItem"] = li;
    return c_.post("/voice/listenandanswer",{},""  ,p).toJson(); }
json Voice::sayText(const std::string& text, const std::string& vid,
                    const std::string& sink, const std::string& vol) {
    return c_.post("/voice/say",{},""  ,
        {{"text",text},{"voiceId",vid},{"sinkId",sink},{"volume",vol}}).toJson(); }
json Voice::getVoices() { return c_.get("/voice/voices").toJson(); }

} // namespace openhab
