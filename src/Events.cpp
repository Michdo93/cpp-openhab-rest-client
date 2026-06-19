#include "openhab/API.h"
namespace openhab {

// ── Events ────────────────────────────────────────────────────────────────────
SSEConnection Events::getEvents(const std::string& topics) {
    std::string url = c_.baseUrl() + "/rest/events";
    if (!topics.empty()) url += "?topics=" + topics;
    return c_.sse(url);
}
SSEConnection Events::initiateStateTracker() {
    return c_.sse(c_.baseUrl() + "/rest/events/states");
}
json Events::updateSSEConnectionItems(const std::string& connId, const json& items) {
    return c_.post("/events/states/"+connId,
        {{"Content-Type","application/json"}}, items.dump()).toJson();
}

// ── ItemEvents ────────────────────────────────────────────────────────────────
static SSEConnection itemSse(OpenHABClient& c, const std::string& topic) {
    return c.sse(c.baseUrl() + "/rest/events?topics=" + topic);
}
SSEConnection ItemEvents::ItemEvent()                                           { return itemSse(c_, "openhab/items"); }
SSEConnection ItemEvents::ItemAddedEvent(const std::string& n)                  { return itemSse(c_, "openhab/items/"+n+"/added"); }
SSEConnection ItemEvents::ItemRemovedEvent(const std::string& n)                { return itemSse(c_, "openhab/items/"+n+"/removed"); }
SSEConnection ItemEvents::ItemUpdatedEvent(const std::string& n)                { return itemSse(c_, "openhab/items/"+n+"/updated"); }
SSEConnection ItemEvents::ItemCommandEvent(const std::string& n)                { return itemSse(c_, "openhab/items/"+n+"/command"); }
SSEConnection ItemEvents::ItemStateEvent(const std::string& n)                  { return itemSse(c_, "openhab/items/"+n+"/state"); }
SSEConnection ItemEvents::ItemStatePredictedEvent(const std::string& n)         { return itemSse(c_, "openhab/items/"+n+"/statepredicted"); }
SSEConnection ItemEvents::ItemStateChangedEvent(const std::string& n)           { return itemSse(c_, "openhab/items/"+n+"/statechanged"); }
SSEConnection ItemEvents::GroupItemStateChangedEvent(const std::string& i,
                                                     const std::string& m)      { return itemSse(c_, "openhab/items/"+i+"/"+m+"/statechanged"); }

// ── ThingEvents ───────────────────────────────────────────────────────────────
static SSEConnection thingSse(OpenHABClient& c, const std::string& topic) {
    return c.sse(c.baseUrl() + "/rest/events?topics=" + topic);
}
SSEConnection ThingEvents::ThingAddedEvent(const std::string& u)             { return thingSse(c_, "openhab/things/"+u+"/added"); }
SSEConnection ThingEvents::ThingRemovedEvent(const std::string& u)           { return thingSse(c_, "openhab/things/"+u+"/removed"); }
SSEConnection ThingEvents::ThingUpdatedEvent(const std::string& u)           { return thingSse(c_, "openhab/things/"+u+"/updated"); }
SSEConnection ThingEvents::ThingStatusInfoEvent(const std::string& u)        { return thingSse(c_, "openhab/things/"+u+"/status"); }
SSEConnection ThingEvents::ThingStatusInfoChangedEvent(const std::string& u) { return thingSse(c_, "openhab/things/"+u+"/statuschanged"); }

// ── InboxEvents ───────────────────────────────────────────────────────────────
SSEConnection InboxEvents::InboxAddedEvent(const std::string& u)   { return c_.sse(c_.baseUrl()+"/rest/events?topics=openhab/inbox/"+u+"/added"); }
SSEConnection InboxEvents::InboxRemovedEvent(const std::string& u) { return c_.sse(c_.baseUrl()+"/rest/events?topics=openhab/inbox/"+u+"/removed"); }
SSEConnection InboxEvents::InboxUpdatedEvent(const std::string& u) { return c_.sse(c_.baseUrl()+"/rest/events?topics=openhab/inbox/"+u+"/updated"); }

// ── LinkEvents ────────────────────────────────────────────────────────────────
SSEConnection LinkEvents::ItemChannelLinkAddedEvent(const std::string& i, const std::string& ch) {
    return c_.sse(c_.baseUrl()+"/rest/events?topics=openhab/links/"+i+"-"+ch+"/added"); }
SSEConnection LinkEvents::ItemChannelLinkRemovedEvent(const std::string& i, const std::string& ch) {
    return c_.sse(c_.baseUrl()+"/rest/events?topics=openhab/links/"+i+"-"+ch+"/removed"); }

// ── ChannelEvents ─────────────────────────────────────────────────────────────
SSEConnection ChannelEvents::ChannelDescriptionChangedEvent(const std::string& u) {
    return c_.sse(c_.baseUrl()+"/rest/events?topics=openhab/channels/"+u+"/descriptionchanged"); }
SSEConnection ChannelEvents::ChannelTriggeredEvent(const std::string& u) {
    return c_.sse(c_.baseUrl()+"/rest/events?topics=openhab/channels/"+u+"/triggered"); }

} // namespace openhab
