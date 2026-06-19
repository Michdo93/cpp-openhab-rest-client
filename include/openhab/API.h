#pragma once

#include "OpenHABClient.h"
#include <string>
#include <optional>

namespace openhab {

// ── Helper macros for optional string params ──────────────────────────────────
// All optional string params default to "" (empty = not sent)

// ═══════════════════════════════════════════════════════════════════════════════
// Items
// ═══════════════════════════════════════════════════════════════════════════════

class Items {
public:
    explicit Items(OpenHABClient& client) : c_(client) {}

    json getItems(const std::string& type         = "",
                  const std::string& tags         = "",
                  const std::string& metadata     = ".*",
                  bool               recursive    = false,
                  const std::string& fields       = "",
                  bool               staticOnly   = false,
                  const std::string& language     = "");

    json addOrUpdateItems (const json& items);
    json getItem          (const std::string& name, const std::string& metadata = ".*",
                           bool recursive = true, const std::string& lang = "");
    json addOrUpdateItem  (const std::string& name, const json& data,
                           const std::string& lang = "");
    json sendCommand      (const std::string& name, const std::string& command);
    json postUpdate       (const std::string& name, const std::string& state);
    json deleteItem       (const std::string& name);
    json addGroupMember   (const std::string& name, const std::string& member);
    json removeGroupMember(const std::string& name, const std::string& member);
    json addMetadata      (const std::string& name, const std::string& ns,
                           const json& metadata);
    json removeMetadata   (const std::string& name, const std::string& ns);
    json getMetadataNamespaces(const std::string& name, const std::string& lang = "");
    json getSemanticItem  (const std::string& name, const std::string& semClass,
                           const std::string& lang = "");
    json getItemState     (const std::string& name);
    json updateItemState  (const std::string& name, const std::string& state,
                           const std::string& lang = "");
    json addTag           (const std::string& name, const std::string& tag);
    json removeTag        (const std::string& name, const std::string& tag);
    json purgeOrphanedMetadata();

private:
    OpenHABClient& c_;
};

// ═══════════════════════════════════════════════════════════════════════════════
// Things
// ═══════════════════════════════════════════════════════════════════════════════

class Things {
public:
    explicit Things(OpenHABClient& client) : c_(client) {}

    json getThings             (bool summary = false, bool staticOnly = false,
                                const std::string& lang = "");
    json createThing           (const json& data, const std::string& lang = "");
    json getThing              (const std::string& uid, const std::string& lang = "");
    json updateThing           (const std::string& uid, const json& data,
                                const std::string& lang = "");
    json deleteThing           (const std::string& uid, bool force = false,
                                const std::string& lang = "");
    json updateThingConfiguration(const std::string& uid, const json& config,
                                  const std::string& lang = "");
    json getThingConfigStatus  (const std::string& uid, const std::string& lang = "");
    json setThingStatus        (const std::string& uid, bool enabled,
                                const std::string& lang = "");
    json enableThing           (const std::string& uid);
    json disableThing          (const std::string& uid);
    json updateThingFirmware   (const std::string& uid, const std::string& version,
                                const std::string& lang = "");
    json getThingFirmwareStatus(const std::string& uid, const std::string& lang = "");
    json getThingFirmwares     (const std::string& uid, const std::string& lang = "");
    json getThingStatus        (const std::string& uid, const std::string& lang = "");

private:
    OpenHABClient& c_;
};

// ═══════════════════════════════════════════════════════════════════════════════
// Rules
// ═══════════════════════════════════════════════════════════════════════════════

class Rules {
public:
    explicit Rules(OpenHABClient& client) : c_(client) {}

    json getRules          (const std::string& prefix = "", const std::string& tags = "",
                            bool summary = false, bool staticOnly = false);
    json createRule        (const json& data);
    json getRule           (const std::string& uid);
    json updateRule        (const std::string& uid, const json& data);
    json deleteRule        (const std::string& uid);
    json getModule         (const std::string& uid, const std::string& cat,
                            const std::string& mid);
    json getModuleConfig   (const std::string& uid, const std::string& cat,
                            const std::string& mid);
    json getModuleConfigParam(const std::string& uid, const std::string& cat,
                              const std::string& mid, const std::string& param);
    json setModuleConfigParam(const std::string& uid, const std::string& cat,
                              const std::string& mid, const std::string& param,
                              const std::string& value);
    json getActions        (const std::string& uid);
    json getConditions     (const std::string& uid);
    json getTriggers       (const std::string& uid);
    json getConfiguration  (const std::string& uid);
    json updateConfiguration(const std::string& uid, const json& config);
    json setRuleState      (const std::string& uid, bool enable);
    json enable            (const std::string& uid);
    json disable           (const std::string& uid);
    json runNow            (const std::string& uid, const json& context = nullptr);
    json simulateSchedule  (const std::string& from, const std::string& until);

private:
    OpenHABClient& c_;
};

// ═══════════════════════════════════════════════════════════════════════════════
// Events (SSE)
// ═══════════════════════════════════════════════════════════════════════════════

class Events {
public:
    explicit Events(OpenHABClient& client) : c_(client) {}

    SSEConnection getEvents          (const std::string& topics = "");
    SSEConnection initiateStateTracker();
    json          updateSSEConnectionItems(const std::string& connId,
                                           const json& items);
private:
    OpenHABClient& c_;
};

class ItemEvents {
public:
    explicit ItemEvents(OpenHABClient& client) : c_(client) {}

    SSEConnection ItemEvent                    ();
    SSEConnection ItemAddedEvent               (const std::string& name = "*");
    SSEConnection ItemRemovedEvent             (const std::string& name = "*");
    SSEConnection ItemUpdatedEvent             (const std::string& name = "*");
    SSEConnection ItemCommandEvent             (const std::string& name = "*");
    SSEConnection ItemStateEvent               (const std::string& name = "*");
    SSEConnection ItemStatePredictedEvent      (const std::string& name = "*");
    SSEConnection ItemStateChangedEvent        (const std::string& name = "*");
    SSEConnection GroupItemStateChangedEvent   (const std::string& item,
                                                const std::string& member);
private:
    OpenHABClient& c_;
};

class ThingEvents {
public:
    explicit ThingEvents(OpenHABClient& client) : c_(client) {}

    SSEConnection ThingAddedEvent             (const std::string& uid = "*");
    SSEConnection ThingRemovedEvent           (const std::string& uid = "*");
    SSEConnection ThingUpdatedEvent           (const std::string& uid = "*");
    SSEConnection ThingStatusInfoEvent        (const std::string& uid = "*");
    SSEConnection ThingStatusInfoChangedEvent (const std::string& uid = "*");
private:
    OpenHABClient& c_;
};

class InboxEvents {
public:
    explicit InboxEvents(OpenHABClient& client) : c_(client) {}
    SSEConnection InboxAddedEvent  (const std::string& uid = "*");
    SSEConnection InboxRemovedEvent(const std::string& uid = "*");
    SSEConnection InboxUpdatedEvent(const std::string& uid = "*");
private:
    OpenHABClient& c_;
};

class LinkEvents {
public:
    explicit LinkEvents(OpenHABClient& client) : c_(client) {}
    SSEConnection ItemChannelLinkAddedEvent  (const std::string& item = "*",
                                              const std::string& ch   = "*");
    SSEConnection ItemChannelLinkRemovedEvent(const std::string& item = "*",
                                              const std::string& ch   = "*");
private:
    OpenHABClient& c_;
};

class ChannelEvents {
public:
    explicit ChannelEvents(OpenHABClient& client) : c_(client) {}
    SSEConnection ChannelDescriptionChangedEvent(const std::string& uid = "*");
    SSEConnection ChannelTriggeredEvent         (const std::string& uid = "*");
private:
    OpenHABClient& c_;
};

// ═══════════════════════════════════════════════════════════════════════════════
// All remaining API classes
// ═══════════════════════════════════════════════════════════════════════════════

class Actions {
public:
    explicit Actions(OpenHABClient& c) : c_(c) {}
    json getActions   (const std::string& thingUID, const std::string& lang = "");
    json executeAction(const std::string& thingUID, const std::string& actionUID,
                       const json& inputs, const std::string& lang = "");
private: OpenHABClient& c_;
};

class Addons {
public:
    explicit Addons(OpenHABClient& c) : c_(c) {}
    json getAddons          (const std::string& serviceID = "", const std::string& lang = "");
    json getAddon           (const std::string& id, const std::string& serviceID = "",
                             const std::string& lang = "");
    json getAddonConfig     (const std::string& id, const std::string& serviceID = "");
    json updateAddonConfig  (const std::string& id, const json& config,
                             const std::string& serviceID = "");
    json installAddon       (const std::string& id, const std::string& serviceID = "");
    json uninstallAddon     (const std::string& id, const std::string& serviceID = "");
    json getAddonServices   (const std::string& lang = "");
    json getAddonSuggestions(const std::string& lang = "");
    json getAddonTypes      (const std::string& serviceID = "", const std::string& lang = "");
    json installAddonFromUrl(const std::string& url);
private: OpenHABClient& c_;
};

class Audio {
public:
    explicit Audio(OpenHABClient& c) : c_(c) {}
    json getDefaultSink  (const std::string& lang = "");
    json getDefaultSource(const std::string& lang = "");
    json getSinks        (const std::string& lang = "");
    json getSources      (const std::string& lang = "");
private: OpenHABClient& c_;
};

class Auth {
public:
    explicit Auth(OpenHABClient& c) : c_(c) {}
    json getAPITokens ();
    json revokeAPIToken(const std::string& name);
    json logout        (const std::string& refreshToken, const std::string& sessionId);
    json getSessions   ();
    json getToken      (const std::string& grantType    = "",
                        const std::string& code         = "",
                        const std::string& redirectUri  = "",
                        const std::string& clientId     = "",
                        const std::string& refreshToken = "",
                        const std::string& codeVerifier = "");
private: OpenHABClient& c_;
};

class ChannelTypes {
public:
    explicit ChannelTypes(OpenHABClient& c) : c_(c) {}
    json getChannelTypes     (const std::string& prefixes = "", const std::string& lang = "");
    json getChannelType      (const std::string& uid, const std::string& lang = "");
    json getLinkableItemTypes(const std::string& uid);
private: OpenHABClient& c_;
};

class ConfigDescriptions {
public:
    explicit ConfigDescriptions(OpenHABClient& c) : c_(c) {}
    json getConfigDescriptions(const std::string& scheme = "", const std::string& lang = "");
    json getConfigDescription (const std::string& uri, const std::string& lang = "");
private: OpenHABClient& c_;
};

class Discovery {
public:
    explicit Discovery(OpenHABClient& c) : c_(c) {}
    json getDiscoveryBindings();
    json getBindingInfo      (const std::string& bindingId, const std::string& lang = "");
    json startBindingScan    (const std::string& bindingId, const std::string& input = "");
private: OpenHABClient& c_;
};

class Iconsets {
public:
    explicit Iconsets(OpenHABClient& c) : c_(c) {}
    json getIconsets(const std::string& lang = "");
private: OpenHABClient& c_;
};

class Inbox {
public:
    explicit Inbox(OpenHABClient& c) : c_(c) {}
    json getDiscoveredThings   (bool includeIgnored = true);
    json removeDiscoveryResult (const std::string& uid);
    json approveDiscoveryResult(const std::string& uid, const std::string& label,
                                const std::string& newId = "", const std::string& lang = "");
    json ignoreDiscoveryResult  (const std::string& uid);
    json unignoreDiscoveryResult(const std::string& uid);
private: OpenHABClient& c_;
};

class Links {
public:
    explicit Links(OpenHABClient& c) : c_(c) {}
    json getLinks            (const std::string& channelUID = "", const std::string& item = "");
    json getLink             (const std::string& item, const std::string& channelUID);
    json linkItemToChannel   (const std::string& item, const std::string& channelUID,
                              const json& config);
    json unlinkItemFromChannel(const std::string& item, const std::string& channelUID);
    json deleteAllLinks      (const std::string& object);
    json getOrphanLinks      ();
    json purgeUnusedLinks    ();
private: OpenHABClient& c_;
};

class Logging {
public:
    explicit Logging(OpenHABClient& c) : c_(c) {}
    json getLoggers        ();
    json getLogger         (const std::string& name);
    json modifyOrAddLogger (const std::string& name, const std::string& level);
    json removeLogger      (const std::string& name);
private: OpenHABClient& c_;
};

class ModuleTypes {
public:
    explicit ModuleTypes(OpenHABClient& c) : c_(c) {}
    json getModuleTypes(const std::string& tags = "", const std::string& typeFilter = "",
                        const std::string& lang = "");
    json getModuleType (const std::string& uid, const std::string& lang = "");
private: OpenHABClient& c_;
};

class Persistence {
public:
    explicit Persistence(OpenHABClient& c) : c_(c) {}
    json getServices             (const std::string& lang = "");
    json getServiceConfiguration (const std::string& serviceId);
    json setServiceConfiguration (const std::string& serviceId, const json& config);
    json deleteServiceConfiguration(const std::string& serviceId);
    json getItemsFromService     (const std::string& serviceId = "");
    json getItemPersistenceData  (const std::string& item, const std::string& serviceId,
                                  const std::string& startTime = "",
                                  const std::string& endTime   = "",
                                  int page = 1, int pageLength = 50,
                                  bool boundary = false, bool itemState = false);
    json storeItemData           (const std::string& item, const std::string& time,
                                  const std::string& state, const std::string& serviceId = "");
    json deleteItemData          (const std::string& item, const std::string& start,
                                  const std::string& end, const std::string& serviceId);
private: OpenHABClient& c_;
};

class ProfileTypes {
public:
    explicit ProfileTypes(OpenHABClient& c) : c_(c) {}
    json getProfileTypes(const std::string& channelTypeUID = "",
                         const std::string& itemType = "",
                         const std::string& lang = "");
private: OpenHABClient& c_;
};

class Services {
public:
    explicit Services(OpenHABClient& c) : c_(c) {}
    json getServices       (const std::string& lang = "");
    json getService        (const std::string& id, const std::string& lang = "");
    json getServiceConfig  (const std::string& id);
    json updateServiceConfig(const std::string& id, const json& config,
                             const std::string& lang = "");
    json deleteServiceConfig(const std::string& id);
    json getServiceContexts (const std::string& id, const std::string& lang = "");
private: OpenHABClient& c_;
};

class Sitemaps {
public:
    explicit Sitemaps(OpenHABClient& c) : c_(c) {}
    json          getSitemaps           ();
    json          getSitemap            (const std::string& name,
                                         const std::string& type = "",
                                         bool includeHidden = false,
                                         const std::string& lang = "");
    json          getSitemapPage        (const std::string& name,
                                         const std::string& pageId,
                                         const std::string& subId = "",
                                         bool includeHidden = false,
                                         const std::string& lang = "");
    SSEConnection getSitemapEvents      (const std::string& subId,
                                         const std::string& sitemapName = "",
                                         const std::string& pageId = "");
    json          subscribeToSitemapEvents();
private: OpenHABClient& c_;
};

class Systeminfo {
public:
    explicit Systeminfo(OpenHABClient& c) : c_(c) {}
    json getSystemInfo();
    json getUoMInfo   ();
private: OpenHABClient& c_;
};

class Tags {
public:
    explicit Tags(OpenHABClient& c) : c_(c) {}
    json getTags   (const std::string& lang = "");
    json createTag (const json& data, const std::string& lang = "");
    json getTag    (const std::string& id, const std::string& lang = "");
    json updateTag (const std::string& id, const json& data, const std::string& lang = "");
    json deleteTag (const std::string& id, const std::string& lang = "");
private: OpenHABClient& c_;
};

class Templates {
public:
    explicit Templates(OpenHABClient& c) : c_(c) {}
    json getTemplates(const std::string& lang = "");
    json getTemplate (const std::string& uid, const std::string& lang = "");
private: OpenHABClient& c_;
};

class ThingTypes {
public:
    explicit ThingTypes(OpenHABClient& c) : c_(c) {}
    json getThingTypes(const std::string& bindingId = "", const std::string& lang = "");
    json getThingType (const std::string& uid, const std::string& lang = "");
private: OpenHABClient& c_;
};

class Transformations {
public:
    explicit Transformations(OpenHABClient& c) : c_(c) {}
    json getTransformations       ();
    json getTransformation        (const std::string& uid);
    json updateTransformation     (const std::string& uid, const json& data);
    json deleteTransformation     (const std::string& uid);
    json getTransformationServices();
private: OpenHABClient& c_;
};

class UI {
public:
    explicit UI(OpenHABClient& c) : c_(c) {}
    json getUIComponents  (const std::string& ns, bool summary = false);
    json addUIComponent   (const std::string& ns, const json& data);
    json getUIComponent   (const std::string& ns, const std::string& uid);
    json updateUIComponent(const std::string& ns, const std::string& uid, const json& data);
    json deleteUIComponent(const std::string& ns, const std::string& uid);
    json getUITiles       ();
private: OpenHABClient& c_;
};

class UUID {
public:
    explicit UUID(OpenHABClient& c) : c_(c) {}
    json getUUID();
private: OpenHABClient& c_;
};

class Voice {
public:
    explicit Voice(OpenHABClient& c) : c_(c) {}
    json getDefaultVoice    ();
    json startDialog        (const std::string& sourceId,
                             const std::string& ksId    = "",
                             const std::string& sttId   = "",
                             const std::string& ttsId   = "",
                             const std::string& voiceId = "",
                             const std::string& hliIds  = "",
                             const std::string& sinkId  = "",
                             const std::string& keyword = "",
                             const std::string& listeningItem = "");
    json stopDialog         (const std::string& sourceId);
    json getInterpreters    (const std::string& lang = "");
    json interpretText      (const std::string& text, const std::string& lang = "");
    json getInterpreter     (const std::string& id, const std::string& lang = "");
    json interpretTextBatch (const std::string& text, const std::string& ids,
                             const std::string& lang = "");
    json listenAndAnswer    (const std::string& sourceId, const std::string& sttId,
                             const std::string& ttsId, const std::string& voiceId,
                             const std::string& hliIds = "",
                             const std::string& sinkId = "",
                             const std::string& listeningItem = "");
    json sayText            (const std::string& text, const std::string& voiceId,
                             const std::string& sinkId, const std::string& volume = "100");
    json getVoices          ();
private: OpenHABClient& c_;
};

} // namespace openhab
