// Generated from Events.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static EventStream Events_getEvents(OpenHABClient& C, py::V v_topics);
static EventStream Events_initiateStateTracker(OpenHABClient& C);
static py::V Events_updateSSEConnectionItems(OpenHABClient& C, py::V v_connectionID, py::V v_items);

static EventStream Events_getEvents(OpenHABClient& C, py::V v_topics) {
    (void)C;
    (void)v_topics;
    return py::openStream(C, v_topics, py::V(), py::V(), py::dict({{"400", py::s("Topic is empty or contains invalid characters.")}}));
}

EventStream Events::getEvents(const std::optional<std::string>& topics) {
    return py::finishStream([&] { return Events_getEvents(*client_, py::arg(topics)); });
}

EventStream Events::getEvents(const GetEventsArgs& a) {
    return getEvents(a.topics);
}

static EventStream Events_initiateStateTracker(OpenHABClient& C) {
    (void)C;
    return py::openStream(C, py::V(), py::s("/rest/events/states"), py::dict({{"Accept", py::s("*/*")}}), py::V());
}

EventStream Events::initiateStateTracker() {
    return py::finishStream([&] { return Events_initiateStateTracker(*client_); });
}

static py::V Events_updateSSEConnectionItems(OpenHABClient& C, py::V v_connectionID, py::V v_items) {
    (void)C;
    (void)v_connectionID;
    (void)v_items;
    py::V v_response;
    py::V v_statusCode;
    try {
        v_response = py::http(C, "post", py::cat({py::s("/events/states/"), v_connectionID}), py::dict({{"Content-Type", py::s("application/json")}}), py::dumps(v_items), py::V());
        if (py::isstatus(v_response)) {
            v_statusCode = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_statusCode = py::excStatus(e_err);
        if (py::eq(v_statusCode, py::V(json(404)))) {
            return py::dict({{"error", py::s("Unknown connectionID.")}});
        }
        return py::dict({{"error", py::cat({py::s("HTTP error "), v_statusCode, py::s(": "), py::excStr(e_err)})}});
    } catch (const py::RequestException& e_err) {
        (void)e_err;
        return py::dict({{"error", py::cat({py::s("Request error: "), py::excStr(e_err)})}});
    }
    if (py::eq(v_statusCode, py::V(json(200)))) {
        return py::dict({{"message", py::s("OK")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_statusCode})}});
}

json Events::updateSSEConnectionItems(const std::string& connectionID, const json& items) {
    return py::finish([&] { return Events_updateSSEConnectionItems(*client_, py::arg(connectionID), py::arg(items)); });
}

static EventStream ItemEvents_ItemEvent(OpenHABClient& C);
static EventStream ItemEvents_ItemAddedEvent(OpenHABClient& C, py::V v_itemName);
static EventStream ItemEvents_ItemRemovedEvent(OpenHABClient& C, py::V v_itemName);
static EventStream ItemEvents_ItemUpdatedEvent(OpenHABClient& C, py::V v_itemName);
static EventStream ItemEvents_ItemCommandEvent(OpenHABClient& C, py::V v_itemName);
static EventStream ItemEvents_ItemStateEvent(OpenHABClient& C, py::V v_itemName);
static EventStream ItemEvents_ItemStatePredictedEvent(OpenHABClient& C, py::V v_itemName);
static EventStream ItemEvents_ItemStateChangedEvent(OpenHABClient& C, py::V v_itemName);
static EventStream ItemEvents_GroupItemStateChangedEvent(OpenHABClient& C, py::V v_itemName, py::V v_memberName);

static EventStream ItemEvents_ItemEvent(OpenHABClient& C) {
    (void)C;
    return py::openStream(C, py::s("openhab/items/*"), py::V(), py::V(), py::V());
}

EventStream ItemEvents::ItemEvent() {
    return py::finishStream([&] { return ItemEvents_ItemEvent(*client_); });
}

static EventStream ItemEvents_ItemAddedEvent(OpenHABClient& C, py::V v_itemName) {
    (void)C;
    (void)v_itemName;
    return py::openStream(C, py::cat({py::s("openhab/items/"), v_itemName, py::s("/added")}), py::V(), py::V(), py::V());
}

EventStream ItemEvents::ItemAddedEvent(const std::string& itemName) {
    return py::finishStream([&] { return ItemEvents_ItemAddedEvent(*client_, py::arg(itemName)); });
}

EventStream ItemEvents::ItemAddedEvent(const ItemAddedEventArgs& a) {
    return ItemAddedEvent(a.itemName);
}

static EventStream ItemEvents_ItemRemovedEvent(OpenHABClient& C, py::V v_itemName) {
    (void)C;
    (void)v_itemName;
    return py::openStream(C, py::cat({py::s("openhab/items/"), v_itemName, py::s("/removed")}), py::V(), py::V(), py::V());
}

EventStream ItemEvents::ItemRemovedEvent(const std::string& itemName) {
    return py::finishStream([&] { return ItemEvents_ItemRemovedEvent(*client_, py::arg(itemName)); });
}

EventStream ItemEvents::ItemRemovedEvent(const ItemRemovedEventArgs& a) {
    return ItemRemovedEvent(a.itemName);
}

static EventStream ItemEvents_ItemUpdatedEvent(OpenHABClient& C, py::V v_itemName) {
    (void)C;
    (void)v_itemName;
    return py::openStream(C, py::cat({py::s("openhab/items/"), v_itemName, py::s("/updated")}), py::V(), py::V(), py::V());
}

EventStream ItemEvents::ItemUpdatedEvent(const std::string& itemName) {
    return py::finishStream([&] { return ItemEvents_ItemUpdatedEvent(*client_, py::arg(itemName)); });
}

EventStream ItemEvents::ItemUpdatedEvent(const ItemUpdatedEventArgs& a) {
    return ItemUpdatedEvent(a.itemName);
}

static EventStream ItemEvents_ItemCommandEvent(OpenHABClient& C, py::V v_itemName) {
    (void)C;
    (void)v_itemName;
    return py::openStream(C, py::cat({py::s("openhab/items/"), v_itemName, py::s("/command")}), py::V(), py::V(), py::V());
}

EventStream ItemEvents::ItemCommandEvent(const std::string& itemName) {
    return py::finishStream([&] { return ItemEvents_ItemCommandEvent(*client_, py::arg(itemName)); });
}

EventStream ItemEvents::ItemCommandEvent(const ItemCommandEventArgs& a) {
    return ItemCommandEvent(a.itemName);
}

static EventStream ItemEvents_ItemStateEvent(OpenHABClient& C, py::V v_itemName) {
    (void)C;
    (void)v_itemName;
    return py::openStream(C, py::cat({py::s("openhab/items/"), v_itemName, py::s("/state")}), py::V(), py::V(), py::V());
}

EventStream ItemEvents::ItemStateEvent(const std::string& itemName) {
    return py::finishStream([&] { return ItemEvents_ItemStateEvent(*client_, py::arg(itemName)); });
}

EventStream ItemEvents::ItemStateEvent(const ItemStateEventArgs& a) {
    return ItemStateEvent(a.itemName);
}

static EventStream ItemEvents_ItemStatePredictedEvent(OpenHABClient& C, py::V v_itemName) {
    (void)C;
    (void)v_itemName;
    return py::openStream(C, py::cat({py::s("openhab/items/"), v_itemName, py::s("/statepredicted")}), py::V(), py::V(), py::V());
}

EventStream ItemEvents::ItemStatePredictedEvent(const std::string& itemName) {
    return py::finishStream([&] { return ItemEvents_ItemStatePredictedEvent(*client_, py::arg(itemName)); });
}

EventStream ItemEvents::ItemStatePredictedEvent(const ItemStatePredictedEventArgs& a) {
    return ItemStatePredictedEvent(a.itemName);
}

static EventStream ItemEvents_ItemStateChangedEvent(OpenHABClient& C, py::V v_itemName) {
    (void)C;
    (void)v_itemName;
    return py::openStream(C, py::cat({py::s("openhab/items/"), v_itemName, py::s("/statechanged")}), py::V(), py::V(), py::V());
}

EventStream ItemEvents::ItemStateChangedEvent(const std::string& itemName) {
    return py::finishStream([&] { return ItemEvents_ItemStateChangedEvent(*client_, py::arg(itemName)); });
}

EventStream ItemEvents::ItemStateChangedEvent(const ItemStateChangedEventArgs& a) {
    return ItemStateChangedEvent(a.itemName);
}

static EventStream ItemEvents_GroupItemStateChangedEvent(OpenHABClient& C, py::V v_itemName, py::V v_memberName) {
    (void)C;
    (void)v_itemName;
    (void)v_memberName;
    return py::openStream(C, py::cat({py::s("openhab/items/"), v_itemName, py::s("/"), v_memberName, py::s("/statechanged")}), py::V(), py::V(), py::V());
}

EventStream ItemEvents::GroupItemStateChangedEvent(const std::string& itemName, const std::string& memberName) {
    return py::finishStream([&] { return ItemEvents_GroupItemStateChangedEvent(*client_, py::arg(itemName), py::arg(memberName)); });
}

EventStream ItemEvents::GroupItemStateChangedEvent(const GroupItemStateChangedEventArgs& a) {
    return GroupItemStateChangedEvent(a.itemName, a.memberName);
}

static EventStream ThingEvents_ThingAddedEvent(OpenHABClient& C, py::V v_thingUID);
static EventStream ThingEvents_ThingRemovedEvent(OpenHABClient& C, py::V v_thingUID);
static EventStream ThingEvents_ThingUpdatedEvent(OpenHABClient& C, py::V v_thingUID);
static EventStream ThingEvents_ThingStatusInfoEvent(OpenHABClient& C, py::V v_thingUID);
static EventStream ThingEvents_ThingStatusInfoChangedEvent(OpenHABClient& C, py::V v_thingUID);

static EventStream ThingEvents_ThingAddedEvent(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return py::openStream(C, py::cat({py::s("openhab/things/"), v_thingUID, py::s("/added")}), py::V(), py::V(), py::V());
}

EventStream ThingEvents::ThingAddedEvent(const std::string& thingUID) {
    return py::finishStream([&] { return ThingEvents_ThingAddedEvent(*client_, py::arg(thingUID)); });
}

EventStream ThingEvents::ThingAddedEvent(const ThingAddedEventArgs& a) {
    return ThingAddedEvent(a.thingUID);
}

static EventStream ThingEvents_ThingRemovedEvent(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return py::openStream(C, py::cat({py::s("openhab/things/"), v_thingUID, py::s("/removed")}), py::V(), py::V(), py::V());
}

EventStream ThingEvents::ThingRemovedEvent(const std::string& thingUID) {
    return py::finishStream([&] { return ThingEvents_ThingRemovedEvent(*client_, py::arg(thingUID)); });
}

EventStream ThingEvents::ThingRemovedEvent(const ThingRemovedEventArgs& a) {
    return ThingRemovedEvent(a.thingUID);
}

static EventStream ThingEvents_ThingUpdatedEvent(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return py::openStream(C, py::cat({py::s("openhab/things/"), v_thingUID, py::s("/updated")}), py::V(), py::V(), py::V());
}

EventStream ThingEvents::ThingUpdatedEvent(const std::string& thingUID) {
    return py::finishStream([&] { return ThingEvents_ThingUpdatedEvent(*client_, py::arg(thingUID)); });
}

EventStream ThingEvents::ThingUpdatedEvent(const ThingUpdatedEventArgs& a) {
    return ThingUpdatedEvent(a.thingUID);
}

static EventStream ThingEvents_ThingStatusInfoEvent(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return py::openStream(C, py::cat({py::s("openhab/things/"), v_thingUID, py::s("/status")}), py::V(), py::V(), py::V());
}

EventStream ThingEvents::ThingStatusInfoEvent(const std::string& thingUID) {
    return py::finishStream([&] { return ThingEvents_ThingStatusInfoEvent(*client_, py::arg(thingUID)); });
}

EventStream ThingEvents::ThingStatusInfoEvent(const ThingStatusInfoEventArgs& a) {
    return ThingStatusInfoEvent(a.thingUID);
}

static EventStream ThingEvents_ThingStatusInfoChangedEvent(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return py::openStream(C, py::cat({py::s("openhab/things/"), v_thingUID, py::s("/statuschanged")}), py::V(), py::V(), py::V());
}

EventStream ThingEvents::ThingStatusInfoChangedEvent(const std::string& thingUID) {
    return py::finishStream([&] { return ThingEvents_ThingStatusInfoChangedEvent(*client_, py::arg(thingUID)); });
}

EventStream ThingEvents::ThingStatusInfoChangedEvent(const ThingStatusInfoChangedEventArgs& a) {
    return ThingStatusInfoChangedEvent(a.thingUID);
}

static EventStream InboxEvents_InboxAddedEvent(OpenHABClient& C, py::V v_thingUID);
static EventStream InboxEvents_InboxRemovedEvent(OpenHABClient& C, py::V v_thingUID);
static EventStream InboxEvents_InboxUpdatedEvent(OpenHABClient& C, py::V v_thingUID);

static EventStream InboxEvents_InboxAddedEvent(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return py::openStream(C, py::cat({py::s("openhab/inbox/"), v_thingUID, py::s("/added")}), py::V(), py::V(), py::V());
}

EventStream InboxEvents::InboxAddedEvent(const std::string& thingUID) {
    return py::finishStream([&] { return InboxEvents_InboxAddedEvent(*client_, py::arg(thingUID)); });
}

EventStream InboxEvents::InboxAddedEvent(const InboxAddedEventArgs& a) {
    return InboxAddedEvent(a.thingUID);
}

static EventStream InboxEvents_InboxRemovedEvent(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return py::openStream(C, py::cat({py::s("openhab/inbox/"), v_thingUID, py::s("/removed")}), py::V(), py::V(), py::V());
}

EventStream InboxEvents::InboxRemovedEvent(const std::string& thingUID) {
    return py::finishStream([&] { return InboxEvents_InboxRemovedEvent(*client_, py::arg(thingUID)); });
}

EventStream InboxEvents::InboxRemovedEvent(const InboxRemovedEventArgs& a) {
    return InboxRemovedEvent(a.thingUID);
}

static EventStream InboxEvents_InboxUpdatedEvent(OpenHABClient& C, py::V v_thingUID) {
    (void)C;
    (void)v_thingUID;
    return py::openStream(C, py::cat({py::s("openhab/inbox/"), v_thingUID, py::s("/updated")}), py::V(), py::V(), py::V());
}

EventStream InboxEvents::InboxUpdatedEvent(const std::string& thingUID) {
    return py::finishStream([&] { return InboxEvents_InboxUpdatedEvent(*client_, py::arg(thingUID)); });
}

EventStream InboxEvents::InboxUpdatedEvent(const InboxUpdatedEventArgs& a) {
    return InboxUpdatedEvent(a.thingUID);
}

static EventStream LinkEvents_ItemChannelLinkAddedEvent(OpenHABClient& C, py::V v_itemName, py::V v_channelUID);
static EventStream LinkEvents_ItemChannelLinkRemovedEvent(OpenHABClient& C, py::V v_itemName, py::V v_channelUID);

static EventStream LinkEvents_ItemChannelLinkAddedEvent(OpenHABClient& C, py::V v_itemName, py::V v_channelUID) {
    (void)C;
    (void)v_itemName;
    (void)v_channelUID;
    return py::openStream(C, py::cat({py::s("openhab/links/"), v_itemName, py::s("-"), v_channelUID, py::s("/added")}), py::V(), py::V(), py::V());
}

EventStream LinkEvents::ItemChannelLinkAddedEvent(const std::string& itemName, const std::string& channelUID) {
    return py::finishStream([&] { return LinkEvents_ItemChannelLinkAddedEvent(*client_, py::arg(itemName), py::arg(channelUID)); });
}

EventStream LinkEvents::ItemChannelLinkAddedEvent(const ItemChannelLinkAddedEventArgs& a) {
    return ItemChannelLinkAddedEvent(a.itemName, a.channelUID);
}

static EventStream LinkEvents_ItemChannelLinkRemovedEvent(OpenHABClient& C, py::V v_itemName, py::V v_channelUID) {
    (void)C;
    (void)v_itemName;
    (void)v_channelUID;
    return py::openStream(C, py::cat({py::s("openhab/links/"), v_itemName, py::s("-"), v_channelUID, py::s("/removed")}), py::V(), py::V(), py::V());
}

EventStream LinkEvents::ItemChannelLinkRemovedEvent(const std::string& itemName, const std::string& channelUID) {
    return py::finishStream([&] { return LinkEvents_ItemChannelLinkRemovedEvent(*client_, py::arg(itemName), py::arg(channelUID)); });
}

EventStream LinkEvents::ItemChannelLinkRemovedEvent(const ItemChannelLinkRemovedEventArgs& a) {
    return ItemChannelLinkRemovedEvent(a.itemName, a.channelUID);
}

static EventStream ChannelEvents_ChannelDescriptionChangedEvent(OpenHABClient& C, py::V v_channelUID);
static EventStream ChannelEvents_ChannelTriggeredEvent(OpenHABClient& C, py::V v_channelUID);

static EventStream ChannelEvents_ChannelDescriptionChangedEvent(OpenHABClient& C, py::V v_channelUID) {
    (void)C;
    (void)v_channelUID;
    return py::openStream(C, py::cat({py::s("openhab/channels/"), v_channelUID, py::s("/descriptionchanged")}), py::V(), py::V(), py::V());
}

EventStream ChannelEvents::ChannelDescriptionChangedEvent(const std::string& channelUID) {
    return py::finishStream([&] { return ChannelEvents_ChannelDescriptionChangedEvent(*client_, py::arg(channelUID)); });
}

EventStream ChannelEvents::ChannelDescriptionChangedEvent(const ChannelDescriptionChangedEventArgs& a) {
    return ChannelDescriptionChangedEvent(a.channelUID);
}

static EventStream ChannelEvents_ChannelTriggeredEvent(OpenHABClient& C, py::V v_channelUID) {
    (void)C;
    (void)v_channelUID;
    return py::openStream(C, py::cat({py::s("openhab/channels/"), v_channelUID, py::s("/triggered")}), py::V(), py::V(), py::V());
}

EventStream ChannelEvents::ChannelTriggeredEvent(const std::string& channelUID) {
    return py::finishStream([&] { return ChannelEvents_ChannelTriggeredEvent(*client_, py::arg(channelUID)); });
}

EventStream ChannelEvents::ChannelTriggeredEvent(const ChannelTriggeredEventArgs& a) {
    return ChannelTriggeredEvent(a.channelUID);
}

}  // namespace openhab
