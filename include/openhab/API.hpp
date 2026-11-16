// Generated from python-openhab-rest-client by tools/py2cpp.py – do not edit.
#pragma once

#include "OpenHABClient.hpp"

#include <optional>
#include <string>

namespace openhab {

// ── Actions ───────────────────────────────────────────────────────────────────

class OPENHAB_API Actions {
public:
    explicit Actions(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getActions() – the defaults of the Python library. */
    struct GetActionsArgs {
        std::optional<std::string> language;
    };

    /**
     * Get all available actions for provided thing UID.
     *
     * :param thingUID: The UID of the thing for which actions are to be retrieved.
     * :param language: (Optional) Language setting for the Accept-Language headers.
     *
     * :return: A list of actions.
     */
    json getActions(const std::string& thingUID,
                    const std::optional<std::string>& language = std::nullopt);
    /** getActions() with the optional arguments as struct. */
    json getActions(const std::string& thingUID, const GetActionsArgs& a);

    /** Optional arguments of executeAction() – the defaults of the Python library. */
    struct ExecuteActionArgs {
        std::optional<std::string> language;
    };

    /**
     * Executes a thing action.
     *
     * :param thingUID: The UID of the thing on which the action is to be executed.
     * :param actionUID: The UID of the action to be executed.
     * :param actionInputs: The inputs for the action as a dictionary.
     * :param language: (Optional) Language setting for the Accept-Language headers.
     *
     * :return: A response from the server.
     */
    json executeAction(const std::string& thingUID, const std::string& actionUID,
                       const json& actionInputs,
                       const std::optional<std::string>& language = std::nullopt);
    /** executeAction() with the optional arguments as struct. */
    json executeAction(const std::string& thingUID, const std::string& actionUID,
                       const json& actionInputs, const ExecuteActionArgs& a);

private:
    OpenHABClient* client_;
};

// ── Addons ────────────────────────────────────────────────────────────────────

class OPENHAB_API Addons {
public:
    explicit Addons(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getAddons() – the defaults of the Python library. */
    struct GetAddonsArgs {
        std::optional<std::string> serviceID;
        std::optional<std::string> language;
    };

    /**
     * Retrieves a list of all available add-ons.
     *
     * :param serviceID: Optional service ID to filter the results.
     * :param language: Optional language preference for the response.
     *
     * :return: A dictionary containing the add-ons data.
     */
    json getAddons(const std::optional<std::string>& serviceID = std::nullopt,
                   const std::optional<std::string>& language = std::nullopt);
    /** getAddons() with the optional arguments as struct. */
    json getAddons(const GetAddonsArgs& a);

    /** Optional arguments of getAddon() – the defaults of the Python library. */
    struct GetAddonArgs {
        std::optional<std::string> serviceID;
        std::optional<std::string> language;
    };

    /**
     * Retrieves details of a specific add-on by its ID.
     *
     * :param addonID: The unique identifier of the add-on.
     * :param serviceID: Optional service ID to filter the results.
     * :param language: Optional language preference for the response.
     *
     * :return: A dictionary containing details of the specified add-on.
     */
    json getAddon(const std::string& addonID,
                  const std::optional<std::string>& serviceID = std::nullopt,
                  const std::optional<std::string>& language = std::nullopt);
    /** getAddon() with the optional arguments as struct. */
    json getAddon(const std::string& addonID, const GetAddonArgs& a);

    /** Optional arguments of getAddonConfig() – the defaults of the Python library. */
    struct GetAddonConfigArgs {
        std::optional<std::string> serviceID;
    };

    /**
     * Retrieves the configuration of a specific add-on.
     *
     * :param addonID: The unique identifier of the add-on.
     * :param serviceID: Optional service ID to filter the results.
     *
     * :return: A dictionary containing the configuration of the specified add-on.
     */
    json getAddonConfig(const std::string& addonID,
                        const std::optional<std::string>& serviceID = std::nullopt);
    /** getAddonConfig() with the optional arguments as struct. */
    json getAddonConfig(const std::string& addonID, const GetAddonConfigArgs& a);

    /** Optional arguments of updateAddonConfig() – the defaults of the Python library. */
    struct UpdateAddonConfigArgs {
        std::optional<std::string> serviceID;
    };

    /**
     * Updates the configuration of a specific add-on and returns the updated configuration.
     *
     * :param addonID: The unique identifier of the add-on.
     * :param configData: A dictionary containing the new configuration settings.
     * :param serviceID: Optional service ID to specify the target service.
     *
     * :return: A dictionary containing the updated configuration.
     */
    json updateAddonConfig(const std::string& addonID, const json& configData,
                           const std::optional<std::string>& serviceID = std::nullopt);
    /** updateAddonConfig() with the optional arguments as struct. */
    json updateAddonConfig(const std::string& addonID, const json& configData,
                           const UpdateAddonConfigArgs& a);

    /** Optional arguments of installAddon() – the defaults of the Python library. */
    struct InstallAddonArgs {
        std::optional<std::string> serviceID;
    };

    /**
     * Installs an add-on by its ID.
     *
     * :param addonID: The unique identifier of the add-on.
     * :param serviceID: Optional service ID to specify the target service.
     *
     * :return: A dictionary containing the installation status.
     */
    json installAddon(const std::string& addonID,
                      const std::optional<std::string>& serviceID = std::nullopt);
    /** installAddon() with the optional arguments as struct. */
    json installAddon(const std::string& addonID, const InstallAddonArgs& a);

    /** Optional arguments of uninstallAddon() – the defaults of the Python library. */
    struct UninstallAddonArgs {
        std::optional<std::string> serviceID;
    };

    /**
     * Uninstalls an add-on by its ID.
     *
     * :param addonID: The unique identifier of the add-on.
     * :param serviceID: Optional service ID to specify the target service.
     *
     * :return: A dictionary containing the uninstallation status.
     */
    json uninstallAddon(const std::string& addonID,
                        const std::optional<std::string>& serviceID = std::nullopt);
    /** uninstallAddon() with the optional arguments as struct. */
    json uninstallAddon(const std::string& addonID, const UninstallAddonArgs& a);

    /** Optional arguments of getAddonServices() – the defaults of the Python library. */
    struct GetAddonServicesArgs {
        std::optional<std::string> language;
    };

    /**
     * Retrieves a list of all available add-on services.
     *
     * :param language: Optional language preference for the response.
     *
     * :return: A dictionary containing the available add-on services.
     */
    json getAddonServices(const std::optional<std::string>& language = std::nullopt);
    /** getAddonServices() with the optional arguments as struct. */
    json getAddonServices(const GetAddonServicesArgs& a);

    /** Optional arguments of getAddonSuggestions() – the defaults of the Python library. */
    struct GetAddonSuggestionsArgs {
        std::optional<std::string> language;
    };

    /**
     * Retrieves a list of suggested add-ons for installation.
     *
     * :param language: Optional language preference for the response.
     *
     * :return: A dictionary containing suggested add-ons.
     */
    json getAddonSuggestions(const std::optional<std::string>& language = std::nullopt);
    /** getAddonSuggestions() with the optional arguments as struct. */
    json getAddonSuggestions(const GetAddonSuggestionsArgs& a);

    /** Optional arguments of getAddonTypes() – the defaults of the Python library. */
    struct GetAddonTypesArgs {
        std::optional<std::string> serviceID;
        std::optional<std::string> language;
    };

    /**
     * Retrieves a list of all available add-on types.
     *
     * :param language: Optional language preference for the response.
     *
     * :return: A dictionary containing available add-on types.
     */
    json getAddonTypes(const std::optional<std::string>& serviceID = std::nullopt,
                       const std::optional<std::string>& language = std::nullopt);
    /** getAddonTypes() with the optional arguments as struct. */
    json getAddonTypes(const GetAddonTypesArgs& a);

    /**
     * Installs an add-on from a given URL.
     *
     * :param url: The URL of the add-on to install.
     *
     * :return: A dictionary containing the installation status.
     */
    json installAddonFromUrl(const std::string& url);

private:
    OpenHABClient* client_;
};

// ── Audio ─────────────────────────────────────────────────────────────────────

class OPENHAB_API Audio {
public:
    explicit Audio(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getDefaultSink() – the defaults of the Python library. */
    struct GetDefaultSinkArgs {
        std::optional<std::string> language;
    };

    /**
     * Retrieves the default sink if defined, or the first available sink.
     *
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A dictionary containing information about the default sink.
     */
    json getDefaultSink(const std::optional<std::string>& language = std::nullopt);
    /** getDefaultSink() with the optional arguments as struct. */
    json getDefaultSink(const GetDefaultSinkArgs& a);

    /** Optional arguments of getDefaultSource() – the defaults of the Python library. */
    struct GetDefaultSourceArgs {
        std::optional<std::string> language;
    };

    /**
     * Retrieves the default source if defined, or the first available source.
     *
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A dictionary containing information about the default source.
     */
    json getDefaultSource(const std::optional<std::string>& language = std::nullopt);
    /** getDefaultSource() with the optional arguments as struct. */
    json getDefaultSource(const GetDefaultSourceArgs& a);

    /** Optional arguments of getSinks() – the defaults of the Python library. */
    struct GetSinksArgs {
        std::optional<std::string> language;
    };

    /**
     * Retrieves a list of all available sinks.
     *
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A list of available sinks.
     */
    json getSinks(const std::optional<std::string>& language = std::nullopt);
    /** getSinks() with the optional arguments as struct. */
    json getSinks(const GetSinksArgs& a);

    /** Optional arguments of getSources() – the defaults of the Python library. */
    struct GetSourcesArgs {
        std::optional<std::string> language;
    };

    /**
     * Retrieves a list of all available sources.
     *
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A list of available sources.
     */
    json getSources(const std::optional<std::string>& language = std::nullopt);
    /** getSources() with the optional arguments as struct. */
    json getSources(const GetSourcesArgs& a);

private:
    OpenHABClient* client_;
};

// ── Auth ──────────────────────────────────────────────────────────────────────

class OPENHAB_API Auth {
public:
    explicit Auth(OpenHABClient& client) : client_(&client) {}

    /**
     * Retrieve the API tokens associated with the authenticated user.
     *
     * :param language: (Optional) Language setting for the API request.
     *
     * :return: JSON response from the server.
     */
    json getAPITokens();

    /**
     * Revoke a specific API token associated with the authenticated user.
     *
     * :param tokenName: Name of the API token to be revoked.
     * :param language: (Optional) Language setting for the API request.
     *
     * :return: JSON response from the server.
     */
    json revokeAPIToken(const std::string& tokenName);

    /**
     * Terminate the session associated with a refresh token.
     *
     * :param refreshToken: The refresh token used to delete the session.
     * :param id: The user ID associated with the refresh token.
     *
     * :return: JSON response from the server.
     */
    json logout(const std::string& refreshToken, const std::string& sessionID);

    /**
     * Retrieve the sessions associated with the authenticated user.
     *
     * :return: JSON response from the server.
     */
    json getSessions();

    /** Optional arguments of getToken() – the defaults of the Python library. */
    struct GetTokenArgs {
        bool useCookie = false;
        std::optional<std::string> grantType;
        std::optional<std::string> code;
        std::optional<std::string> redirectURI;
        std::optional<std::string> clientID;
        std::optional<std::string> refreshToken;
        std::optional<std::string> codeVerifier;
    };

    /**
     * Obtain access and refresh tokens.
     *
     * :param useCookie: (Optional) Whether to use cookies for the session.
     * :param grantType: (Optional) The type of grant being requested.
     * :param code: (Optional) Authorization code for authentication.
     * :param redirectUri: (Optional) Redirect URI for OAuth authentication.
     * :param clientID: (Optional) Client ID for authentication.
     * :param refreshToken: (Optional) Refresh token for token renewal.
     * :param codeVerifier: (Optional) Code verifier for PKCE authentication.
     *
     * :return: JSON response from the server.
     */
    json getToken(bool useCookie = false,
                  const std::optional<std::string>& grantType = std::nullopt,
                  const std::optional<std::string>& code = std::nullopt,
                  const std::optional<std::string>& redirectURI = std::nullopt,
                  const std::optional<std::string>& clientID = std::nullopt,
                  const std::optional<std::string>& refreshToken = std::nullopt,
                  const std::optional<std::string>& codeVerifier = std::nullopt);
    /** getToken() with the optional arguments as struct. */
    json getToken(const GetTokenArgs& a);

private:
    OpenHABClient* client_;
};

// ── ChannelTypes ──────────────────────────────────────────────────────────────

class OPENHAB_API ChannelTypes {
public:
    explicit ChannelTypes(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getChannelTypes() – the defaults of the Python library. */
    struct GetChannelTypesArgs {
        std::optional<std::string> prefixes;
        std::optional<std::string> language;
    };

    /**
     * Retrieves all available channel types.
     *
     * :param language: Optional headers 'Accept-Language' to specify the preferred language.
     * :param prefixes: Optional query parameter to filter channel types by prefix.
     *
     * :return: A list of channel types.
     */
    json getChannelTypes(const std::optional<std::string>& prefixes = std::nullopt,
                         const std::optional<std::string>& language = std::nullopt);
    /** getChannelTypes() with the optional arguments as struct. */
    json getChannelTypes(const GetChannelTypesArgs& a);

    /** Optional arguments of getChannelType() – the defaults of the Python library. */
    struct GetChannelTypeArgs {
        std::optional<std::string> language;
    };

    /**
     * Retrieves the item types the given trigger channel type UID can be linked to.
     *
     * :param channelTypeUID: The unique UID of the channel type.
     * :param language: Optional headers 'Accept-Language' to specify the preferred language.
     *
     * :return: Details of the specific channel type.
     */
    json getChannelType(const std::string& channelTypeUID,
                        const std::optional<std::string>& language = std::nullopt);
    /** getChannelType() with the optional arguments as struct. */
    json getChannelType(const std::string& channelTypeUID, const GetChannelTypeArgs& a);

    /**
     * Retrieves the item types that can be linked to the specified trigger channel type.
     *
     * :param channelTypeUID: The unique UID of the channel type.
     *
     * :return: A list of item types.
     */
    json getLinkableItemTypes(const std::string& channelTypeUID);

private:
    OpenHABClient* client_;
};

// ── ConfigDescriptions ────────────────────────────────────────────────────────

class OPENHAB_API ConfigDescriptions {
public:
    explicit ConfigDescriptions(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getConfigDescriptions() – the defaults of the Python library. */
    struct GetConfigDescriptionsArgs {
        std::optional<std::string> scheme;
        std::optional<std::string> language;
    };

    /**
     * Retrieves all available config descriptions.
     *
     * :param language: Optional headers 'Accept-Language' to specify the preferred language.
     * :param scheme: Optional query parameter to filter results by a specific scheme.
     *
     * :return: A list of configuration descriptions.
     */
    json getConfigDescriptions(const std::optional<std::string>& scheme = std::nullopt,
                               const std::optional<std::string>& language = std::nullopt);
    /** getConfigDescriptions() with the optional arguments as struct. */
    json getConfigDescriptions(const GetConfigDescriptionsArgs& a);

    /** Optional arguments of getConfigDescription() – the defaults of the Python library. */
    struct GetConfigDescriptionArgs {
        std::optional<std::string> language;
    };

    /**
     * Retrieves a config description by URI.
     *
     * :param uri: The URI of the requested configuration description.
     * :param language: Optional headers 'Accept-Language' to specify the preferred language.
     *
     * :return: Details of the specific configuration description.
     */
    json getConfigDescription(const std::string& uri,
                              const std::optional<std::string>& language = std::nullopt);
    /** getConfigDescription() with the optional arguments as struct. */
    json getConfigDescription(const std::string& uri, const GetConfigDescriptionArgs& a);

private:
    OpenHABClient* client_;
};

// ── Discovery ─────────────────────────────────────────────────────────────────

class OPENHAB_API Discovery {
public:
    explicit Discovery(OpenHABClient& client) : client_(&client) {}

    /**
     * Gets all bindings that support discovery.
     *
     * :return: Eine Liste der Bindings als Strings.
     */
    json getDiscoveryBindings();

    /** Optional arguments of getBindingInfo() – the defaults of the Python library. */
    struct GetBindingInfoArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets information about the discovery services for a binding.
     *
     * :param bindingId: The ID of the binding to get discovery information for.
     * :param language: Optional language parameter for the response (Accept-Language header).
     *
     * :return: Information about the discovery service for the specified binding.
     */
    json getBindingInfo(const std::string& bindingID,
                        const std::optional<std::string>& language = std::nullopt);
    /** getBindingInfo() with the optional arguments as struct. */
    json getBindingInfo(const std::string& bindingID, const GetBindingInfoArgs& a);

    /** Optional arguments of startBindingScan() – the defaults of the Python library. */
    struct StartBindingScanArgs {
        std::optional<std::string> input;
    };

    /**
     * Starts asynchronous discovery process for a binding and returns the timeout in seconds of the discovery operation.
     *
     * :param bindingID: The ID of the binding for which the discovery is to be started.
     * :param input: An input parameter to start the discovery.
     *
     * :return: Timeout duration of the discovery operation in seconds.
     */
    json startBindingScan(const std::string& bindingID,
                          const std::optional<std::string>& input = std::nullopt);
    /** startBindingScan() with the optional arguments as struct. */
    json startBindingScan(const std::string& bindingID, const StartBindingScanArgs& a);

private:
    OpenHABClient* client_;
};

// ── Events ────────────────────────────────────────────────────────────────────

class OPENHAB_API Events {
public:
    explicit Events(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getEvents() – the defaults of the Python library. */
    struct GetEventsArgs {
        std::optional<std::string> topics;
    };

    /**
     * Get all available events, optionally filtered by topic.
     *
     * :param topics: A comma-separated list of topics to filter the events by
     *                (e.g. "openhab/items/ * /statechanged,openhab/things/ * /statuschanged").
     *                The wildcard * also matches slashes.
     *
     * :return: A SSE stream of events (requests.Response) or {"error": ...}.
     */
    EventStream getEvents(const std::optional<std::string>& topics = std::nullopt);
    /** getEvents() with the optional arguments as struct. */
    EventStream getEvents(const GetEventsArgs& a);

    /**
     * Initiates a new item state tracker connection.
     *
     * The first event of the stream carries the connection ID, which is needed for
     * updateSSEConnectionItems().
     *
     * :return: A SSE stream (requests.Response) or {"error": ...}.
     */
    EventStream initiateStateTracker();

    /**
     * Changes the list of items a SSE connection will receive state updates for.
     *
     * :param connectionID: The ID of the existing connection.
     * :param items: A list of item names to subscribe to for state updates.
     *
     * :return: A success message when the update is completed.
     */
    json updateSSEConnectionItems(const std::string& connectionID, const json& items);

private:
    OpenHABClient* client_;
};

// ── ItemEvents ────────────────────────────────────────────────────────────────

class OPENHAB_API ItemEvents {
public:
    explicit ItemEvents(OpenHABClient& client) : client_(&client) {}

    /**
     * Get all item-related events.
     *
     * :return: A SSE stream of item events.
     */
    EventStream ItemEvent();

    /** Optional arguments of ItemAddedEvent() – the defaults of the Python library. */
    struct ItemAddedEventArgs {
        std::string itemName = "*";
    };

    /**
     * Get events for added items.
     *
     * :param itemName: The name of the item (default is "*").
     *
     * :return: A SSE stream of added item events.
     */
    EventStream ItemAddedEvent(const std::string& itemName = "*");
    /** ItemAddedEvent() with the optional arguments as struct. */
    EventStream ItemAddedEvent(const ItemAddedEventArgs& a);

    /** Optional arguments of ItemRemovedEvent() – the defaults of the Python library. */
    struct ItemRemovedEventArgs {
        std::string itemName = "*";
    };

    /**
     * Get events for removed items.
     *
     * :param itemName: The name of the item (default is "*").
     *
     * :return: A SSE stream of removed item events.
     */
    EventStream ItemRemovedEvent(const std::string& itemName = "*");
    /** ItemRemovedEvent() with the optional arguments as struct. */
    EventStream ItemRemovedEvent(const ItemRemovedEventArgs& a);

    /** Optional arguments of ItemUpdatedEvent() – the defaults of the Python library. */
    struct ItemUpdatedEventArgs {
        std::string itemName = "*";
    };

    /**
     * Get events for updated items.
     *
     * :param itemName: The name of the item (default is "*").
     *
     * :return: A SSE stream of updated item events.
     */
    EventStream ItemUpdatedEvent(const std::string& itemName = "*");
    /** ItemUpdatedEvent() with the optional arguments as struct. */
    EventStream ItemUpdatedEvent(const ItemUpdatedEventArgs& a);

    /** Optional arguments of ItemCommandEvent() – the defaults of the Python library. */
    struct ItemCommandEventArgs {
        std::string itemName = "*";
    };

    /**
     * Get events for item commands.
     *
     * :param itemName: The name of the item (default is "*").
     *
     * :return: A SSE stream of item command events.
     */
    EventStream ItemCommandEvent(const std::string& itemName = "*");
    /** ItemCommandEvent() with the optional arguments as struct. */
    EventStream ItemCommandEvent(const ItemCommandEventArgs& a);

    /** Optional arguments of ItemStateEvent() – the defaults of the Python library. */
    struct ItemStateEventArgs {
        std::string itemName = "*";
    };

    /**
     * Get events for item state updates.
     *
     * :param itemName: The name of the item (default is "*").
     *
     * :return: A SSE stream of item state events.
     */
    EventStream ItemStateEvent(const std::string& itemName = "*");
    /** ItemStateEvent() with the optional arguments as struct. */
    EventStream ItemStateEvent(const ItemStateEventArgs& a);

    /** Optional arguments of ItemStatePredictedEvent() – the defaults of the Python library. */
    struct ItemStatePredictedEventArgs {
        std::string itemName = "*";
    };

    /**
     * Get events for predicted item state changes.
     *
     * :param itemName: The name of the item (default is "*").
     *
     * :return: A SSE stream of item state predicted events.
     */
    EventStream ItemStatePredictedEvent(const std::string& itemName = "*");
    /** ItemStatePredictedEvent() with the optional arguments as struct. */
    EventStream ItemStatePredictedEvent(const ItemStatePredictedEventArgs& a);

    /** Optional arguments of ItemStateChangedEvent() – the defaults of the Python library. */
    struct ItemStateChangedEventArgs {
        std::string itemName = "*";
    };

    /**
     * Get events for item state changes.
     *
     * Note: with the default "*", state changes of group items are included as
     * well, because their topic openhab/items/<group>/<member>/statechanged also
     * matches the pattern.
     *
     * :param itemName: The name of the item (default is "*").
     *
     * :return: A SSE stream of item state changed events.
     */
    EventStream ItemStateChangedEvent(const std::string& itemName = "*");
    /** ItemStateChangedEvent() with the optional arguments as struct. */
    EventStream ItemStateChangedEvent(const ItemStateChangedEventArgs& a);

    /** Optional arguments of GroupItemStateChangedEvent() – the defaults of the Python library. */
    struct GroupItemStateChangedEventArgs {
        std::string itemName = "*";
        std::string memberName = "*";
    };

    /**
     * Get events for state changes of group items.
     *
     * :param itemName: The name of the group item (default is "*").
     * :param memberName: The name of the group member that caused the change (default is "*").
     *
     * :return: A SSE stream of group item state changed events.
     */
    EventStream GroupItemStateChangedEvent(const std::string& itemName = "*",
                                           const std::string& memberName = "*");
    /** GroupItemStateChangedEvent() with the optional arguments as struct. */
    EventStream GroupItemStateChangedEvent(const GroupItemStateChangedEventArgs& a);

private:
    OpenHABClient* client_;
};

// ── ThingEvents ───────────────────────────────────────────────────────────────

class OPENHAB_API ThingEvents {
public:
    explicit ThingEvents(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of ThingAddedEvent() – the defaults of the Python library. */
    struct ThingAddedEventArgs {
        std::string thingUID = "*";
    };

    /**
     * Get events for added things.
     *
     * :param thingUID: The UID of the thing (default is "*").
     *
     * :return: A SSE stream of added thing events.
     */
    EventStream ThingAddedEvent(const std::string& thingUID = "*");
    /** ThingAddedEvent() with the optional arguments as struct. */
    EventStream ThingAddedEvent(const ThingAddedEventArgs& a);

    /** Optional arguments of ThingRemovedEvent() – the defaults of the Python library. */
    struct ThingRemovedEventArgs {
        std::string thingUID = "*";
    };

    /**
     * Get events for removed things.
     *
     * :param thingUID: The UID of the thing (default is "*").
     *
     * :return: A SSE stream of removed thing events.
     */
    EventStream ThingRemovedEvent(const std::string& thingUID = "*");
    /** ThingRemovedEvent() with the optional arguments as struct. */
    EventStream ThingRemovedEvent(const ThingRemovedEventArgs& a);

    /** Optional arguments of ThingUpdatedEvent() – the defaults of the Python library. */
    struct ThingUpdatedEventArgs {
        std::string thingUID = "*";
    };

    /**
     * Get events for updated things.
     *
     * :param thingUID: The UID of the thing (default is "*").
     *
     * :return: A SSE stream of updated thing events.
     */
    EventStream ThingUpdatedEvent(const std::string& thingUID = "*");
    /** ThingUpdatedEvent() with the optional arguments as struct. */
    EventStream ThingUpdatedEvent(const ThingUpdatedEventArgs& a);

    /** Optional arguments of ThingStatusInfoEvent() – the defaults of the Python library. */
    struct ThingStatusInfoEventArgs {
        std::string thingUID = "*";
    };

    /**
     * Get events for thing status information.
     *
     * :param thingUID: The UID of the thing (default is "*").
     *
     * :return: A SSE stream of thing status information events.
     */
    EventStream ThingStatusInfoEvent(const std::string& thingUID = "*");
    /** ThingStatusInfoEvent() with the optional arguments as struct. */
    EventStream ThingStatusInfoEvent(const ThingStatusInfoEventArgs& a);

    /** Optional arguments of ThingStatusInfoChangedEvent() – the defaults of the Python library. */
    struct ThingStatusInfoChangedEventArgs {
        std::string thingUID = "*";
    };

    /**
     * Get events for thing status information changes.
     *
     * :param thingUID: The UID of the thing (default is "*").
     *
     * :return: A SSE stream of thing status information changed events.
     */
    EventStream ThingStatusInfoChangedEvent(const std::string& thingUID = "*");
    /** ThingStatusInfoChangedEvent() with the optional arguments as struct. */
    EventStream ThingStatusInfoChangedEvent(const ThingStatusInfoChangedEventArgs& a);

private:
    OpenHABClient* client_;
};

// ── InboxEvents ───────────────────────────────────────────────────────────────

class OPENHAB_API InboxEvents {
public:
    explicit InboxEvents(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of InboxAddedEvent() – the defaults of the Python library. */
    struct InboxAddedEventArgs {
        std::string thingUID = "*";
    };

    /**
     * Get events for added things in the inbox.
     *
     * :param thingUID: The UID of the thing (default is "*").
     *
     * :return: A SSE stream of added inbox events.
     */
    EventStream InboxAddedEvent(const std::string& thingUID = "*");
    /** InboxAddedEvent() with the optional arguments as struct. */
    EventStream InboxAddedEvent(const InboxAddedEventArgs& a);

    /** Optional arguments of InboxRemovedEvent() – the defaults of the Python library. */
    struct InboxRemovedEventArgs {
        std::string thingUID = "*";
    };

    /**
     * Get events for removed things in the inbox.
     *
     * :param thingUID: The UID of the thing (default is "*").
     *
     * :return: A SSE stream of removed inbox events.
     */
    EventStream InboxRemovedEvent(const std::string& thingUID = "*");
    /** InboxRemovedEvent() with the optional arguments as struct. */
    EventStream InboxRemovedEvent(const InboxRemovedEventArgs& a);

    /** Optional arguments of InboxUpdatedEvent() – the defaults of the Python library. */
    struct InboxUpdatedEventArgs {
        std::string thingUID = "*";
    };

    /**
     * Get events for updated things in the inbox.
     *
     * :param thingUID: The UID of the thing (default is "*").
     *
     * :return: A SSE stream of updated inbox events.
     */
    EventStream InboxUpdatedEvent(const std::string& thingUID = "*");
    /** InboxUpdatedEvent() with the optional arguments as struct. */
    EventStream InboxUpdatedEvent(const InboxUpdatedEventArgs& a);

private:
    OpenHABClient* client_;
};

// ── LinkEvents ────────────────────────────────────────────────────────────────

class OPENHAB_API LinkEvents {
public:
    explicit LinkEvents(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of ItemChannelLinkAddedEvent() – the defaults of the Python library. */
    struct ItemChannelLinkAddedEventArgs {
        std::string itemName = "*";
        std::string channelUID = "*";
    };

    /**
     * Get events for added item-channel links.
     *
     * :param itemName: The name of the item (default is "*").
     * :param channelUID: The UID of the channel (default is "*").
     *
     * :return: A SSE stream of added item-channel link events.
     */
    EventStream ItemChannelLinkAddedEvent(const std::string& itemName = "*",
                                          const std::string& channelUID = "*");
    /** ItemChannelLinkAddedEvent() with the optional arguments as struct. */
    EventStream ItemChannelLinkAddedEvent(const ItemChannelLinkAddedEventArgs& a);

    /** Optional arguments of ItemChannelLinkRemovedEvent() – the defaults of the Python library. */
    struct ItemChannelLinkRemovedEventArgs {
        std::string itemName = "*";
        std::string channelUID = "*";
    };

    /**
     * Get events for removed item-channel links.
     *
     * :param itemName: The name of the item (default is "*").
     * :param channelUID: The UID of the channel (default is "*").
     *
     * :return: A SSE stream of removed item-channel link events.
     */
    EventStream ItemChannelLinkRemovedEvent(const std::string& itemName = "*",
                                            const std::string& channelUID = "*");
    /** ItemChannelLinkRemovedEvent() with the optional arguments as struct. */
    EventStream ItemChannelLinkRemovedEvent(const ItemChannelLinkRemovedEventArgs& a);

private:
    OpenHABClient* client_;
};

// ── ChannelEvents ─────────────────────────────────────────────────────────────

class OPENHAB_API ChannelEvents {
public:
    explicit ChannelEvents(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of ChannelDescriptionChangedEvent() – the defaults of the Python library. */
    struct ChannelDescriptionChangedEventArgs {
        std::string channelUID = "*";
    };

    /**
     * Get events for changes in channel descriptions.
     *
     * :param channelUID: The UID of the channel (default is "*").
     *
     * :return: A SSE stream of channel description changed events.
     */
    EventStream ChannelDescriptionChangedEvent(const std::string& channelUID = "*");
    /** ChannelDescriptionChangedEvent() with the optional arguments as struct. */
    EventStream ChannelDescriptionChangedEvent(const ChannelDescriptionChangedEventArgs& a);

    /** Optional arguments of ChannelTriggeredEvent() – the defaults of the Python library. */
    struct ChannelTriggeredEventArgs {
        std::string channelUID = "*";
    };

    /**
     * Get events for triggered channels.
     *
     * :param channelUID: The UID of the channel (default is "*").
     *
     * :return: A SSE stream of channel triggered events.
     */
    EventStream ChannelTriggeredEvent(const std::string& channelUID = "*");
    /** ChannelTriggeredEvent() with the optional arguments as struct. */
    EventStream ChannelTriggeredEvent(const ChannelTriggeredEventArgs& a);

private:
    OpenHABClient* client_;
};

// ── Iconsets ──────────────────────────────────────────────────────────────────

class OPENHAB_API Iconsets {
public:
    explicit Iconsets(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getIconsets() – the defaults of the Python library. */
    struct GetIconsetsArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets all icon sets.
     *
     * :param language: Optional language preference for the response (e.g. 'en', 'de').
     *
     * :return: A list of icon sets with details such as ID, label, description and supported formats.
     */
    json getIconsets(const std::optional<std::string>& language = std::nullopt);
    /** getIconsets() with the optional arguments as struct. */
    json getIconsets(const GetIconsetsArgs& a);

private:
    OpenHABClient* client_;
};

// ── Inbox ─────────────────────────────────────────────────────────────────────

class OPENHAB_API Inbox {
public:
    explicit Inbox(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getDiscoveredThings() – the defaults of the Python library. */
    struct GetDiscoveredThingsArgs {
        bool includeIgnored = true;
    };

    /**
     * Get all discovered things.
     *
     * :param includeIgnored: Whether ignored entries should also be included (default: True).
     *
     * :return: A list of discovered things with details such as UID, flag, label, and properties.
     */
    json getDiscoveredThings(bool includeIgnored = true);
    /** getDiscoveredThings() with the optional arguments as struct. */
    json getDiscoveredThings(const GetDiscoveredThingsArgs& a);

    /**
     * Removes the discovery result from the inbox.
     *
     * :param thingUID: The UID of the discovered thing to be removed.
     *
     * :return: The API response to the delete request.
     */
    json removeDiscoveryResult(const std::string& thingUID);

    /** Optional arguments of approveDiscoveryResult() – the defaults of the Python library. */
    struct ApproveDiscoveryResultArgs {
        std::optional<std::string> newThingID;
        std::optional<std::string> language;
    };

    /**
     * Approves the discovery result by adding the thing to the registry.
     *
     * :param thingUID: The UID of the discovered thing.
     * :param thingLabel: The new name of the thing.
     * :param newThingID: Optional: The new thing ID.
     * :param language: Optional: Language preference for the response.
     *
     * :return: The API response to the approval request.
     */
    json approveDiscoveryResult(const std::string& thingUID, const std::string& thingLabel,
                                const std::optional<std::string>& newThingID = std::nullopt,
                                const std::optional<std::string>& language = std::nullopt);
    /** approveDiscoveryResult() with the optional arguments as struct. */
    json approveDiscoveryResult(const std::string& thingUID, const std::string& thingLabel,
                                const ApproveDiscoveryResultArgs& a);

    /**
     * Flags a discovery result as ignored for further processing.
     *
     * :param thingUID: The UID of the discovered thing.
     *
     * :return: The API response to the ignore request.
     */
    json ignoreDiscoveryResult(const std::string& thingUID);

    /**
     * Removes the ignore flag from a discovery result.
     *
     * :param thingUID: The UID of the discovered thing.
     *
     * :return: The API response to the unignore request.
     */
    json unignoreDiscoveryResult(const std::string& thingUID);

private:
    OpenHABClient* client_;
};

// ── Items ─────────────────────────────────────────────────────────────────────

class OPENHAB_API Items {
public:
    explicit Items(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getItems() – the defaults of the Python library. */
    struct GetItemsArgs {
        std::optional<std::string> type;
        std::optional<std::string> tags;
        std::string metadata = ".*";
        bool recursive = false;
        std::optional<std::string> fields;
        bool staticDataOnly = false;
        std::optional<std::string> language;
        std::optional<bool> parents;
    };

    /**
     * Get all available items.
     *
     * :param type: Optional; Item type filter.
     * :param tags: Optional; Item tag filter.
     * :param metadata: Optional; Metadata selector (default: .*).
     * :param recursive: Optional; Whether to fetch group members recursively (default: False).
     * :param fields: Optional; Limit to specific fields (comma-separated).
     * :param staticDataOnly: Optional; Only returns cached data (default: False).
     * :param language: Optional; Language filter for headers "Accept-Language".
     * :param parents: Optional; Include the parent groups of each item (openHAB 4.1+).
     *
     * :return: A list containing the item data as returned by the API.
     */
    json getItems(const std::optional<std::string>& type = std::nullopt,
                  const std::optional<std::string>& tags = std::nullopt,
                  const std::string& metadata = ".*", bool recursive = false,
                  const std::optional<std::string>& fields = std::nullopt,
                  bool staticDataOnly = false,
                  const std::optional<std::string>& language = std::nullopt,
                  const std::optional<bool>& parents = std::nullopt);
    /** getItems() with the optional arguments as struct. */
    json getItems(const GetItemsArgs& a);

    /**
     * Adds a list of items to the registry or updates the existing items.
     *
     * :param items: A list of item data (Dictionary).
     *
     * :return: A response object or confirmation that the items were successfully added or updated.
     */
    json addOrUpdateItems(const json& items);

    /** Optional arguments of getItem() – the defaults of the Python library. */
    struct GetItemArgs {
        std::string metadata = ".*";
        bool recursive = true;
        std::optional<std::string> language;
        std::optional<bool> parents;
    };

    /**
     * Gets a single item.
     *
     * :param itemName: The name of the item.
     * :param metadata: Optional; Metadata selector (default: .*).
     * :param recursive: Optional; Whether to fetch group members recursively (default: True).
     * :param language: Optional; Language filter for headers "Accept-Language".
     *
     * :return: A dictionary containing the requested item data.
     */
    json getItem(const std::string& itemName, const std::string& metadata = ".*",
                 bool recursive = true, const std::optional<std::string>& language = std::nullopt,
                 const std::optional<bool>& parents = std::nullopt);
    /** getItem() with the optional arguments as struct. */
    json getItem(const std::string& itemName, const GetItemArgs& a);

    /** Optional arguments of addOrUpdateItem() – the defaults of the Python library. */
    struct AddOrUpdateItemArgs {
        std::optional<std::string> language;
    };

    /**
     * Adds a new item to the registry or updates the existing item.
     *
     * :param itemName: The name of the item.
     * :param itemData: The data of the item (Dictionary).
     * :param language: Optional; Language filter for headers "Accept-Language".
     *
     * :return: A response object or confirmation that the item was successfully added or updated.
     */
    json addOrUpdateItem(const std::string& itemName, const json& itemData,
                         const std::optional<std::string>& language = std::nullopt);
    /** addOrUpdateItem() with the optional arguments as struct. */
    json addOrUpdateItem(const std::string& itemName, const json& itemData,
                         const AddOrUpdateItemArgs& a);

    /** Optional arguments of sendCommand() – the defaults of the Python library. */
    struct SendCommandArgs {
        std::optional<std::string> source;
    };

    /**
     * Sends a command to an item.
     *
     * :param itemName: The name of the item.
     * :param command: The command to be sent (e.g., ON, OFF).
     * :param source: Optional; Source of the command, shown in the event (openHAB 4.1+).
     *
     * :return: A response object or confirmation that the command was successfully sent.
     */
    json sendCommand(const std::string& itemName, const std::string& command,
                     const std::optional<std::string>& source = std::nullopt);
    /** sendCommand() with the optional arguments as struct. */
    json sendCommand(const std::string& itemName, const std::string& command,
                     const SendCommandArgs& a);

    /** Optional arguments of postUpdate() – the defaults of the Python library. */
    struct PostUpdateArgs {
        std::optional<std::string> source;
    };

    /**
     * Updates the state of an item.
     *
     * :param itemName: The name of the item.
     * :param state: The state to be signaled for the item.
     *
     * :return: A response object or confirmation that the state was successfully updated.
     */
    json postUpdate(const std::string& itemName, const std::string& state,
                    const std::optional<std::string>& source = std::nullopt);
    /** postUpdate() with the optional arguments as struct. */
    json postUpdate(const std::string& itemName, const std::string& state, const PostUpdateArgs& a);

    /**
     * Removes an item from the registry.
     *
     * :param itemName: The name of the item.
     *
     * :return: A response object or confirmation that the item was successfully deleted.
     */
    json deleteItem(const std::string& itemName);

    /**
     * Adds a new member to a group item.
     *
     * :param itemName: The name of the group item.
     * :param memberItemName: The name of the member item.
     *
     * :return: A response object or confirmation that the group member was successfully added.
     */
    json addGroupMember(const std::string& itemName, const std::string& memberItemName);

    /**
     * Removes an existing member from a group item.
     *
     * :param itemName: The name of the group item.
     * :param memberItemName: The name of the member item.
     *
     * :return: A response object or confirmation that the group member was successfully removed.
     */
    json removeGroupMember(const std::string& itemName, const std::string& memberItemName);

    /**
     * Adds metadata to an item.
     *
     * :param itemName: The name of the item.
     * :param namespace: The namespace of the metadata.
     * :param metadata: A dictionary containing the metadata.
     *
     * :return: A response object or confirmation that the metadata was successfully added.
     */
    json addMetadata(const std::string& itemName, const std::string& namespace_,
                     const json& metadata);

    /**
     * Removes metadata from an item.
     *
     * :param itemName: The name of the item.
     * :param namespace: The namespace of the metadata.
     *
     * :return: A response object or confirmation that the metadata was successfully removed.
     */
    json removeMetadata(const std::string& itemName, const std::string& namespace_);

    /** Optional arguments of getMetadataNamespaces() – the defaults of the Python library. */
    struct GetMetadataNamespacesArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets the namespaces of an item.
     *
     * :param itemName: The name of the item.
     * :param language: Optional; Language filter for headers "Accept-Language".
     *
     * :return: A list of namespaces associated with the item.
     */
    json getMetadataNamespaces(const std::string& itemName,
                               const std::optional<std::string>& language = std::nullopt);
    /** getMetadataNamespaces() with the optional arguments as struct. */
    json getMetadataNamespaces(const std::string& itemName, const GetMetadataNamespacesArgs& a);

    /** Optional arguments of getSemanticItem() – the defaults of the Python library. */
    struct GetSemanticItemArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets the item that defines the requested semantics of an item.
     *
     * :param itemName: The name of the item.
     * :param semanticClass: The requested semantic class.
     * :param language: Optional; Language filter for headers "Accept-Language".
     *
     * :return: A dictionary containing the semantic item data.
     */
    json getSemanticItem(const std::string& itemName, const std::string& semanticClass,
                         const std::optional<std::string>& language = std::nullopt);
    /** getSemanticItem() with the optional arguments as struct. */
    json getSemanticItem(const std::string& itemName, const std::string& semanticClass,
                         const GetSemanticItemArgs& a);

    /**
     * Gets the state of an item.
     *
     * :param itemName: The name of the item.
     *
     * :return: A dictionary containing the current state of the item.
     */
    json getItemState(const std::string& itemName);

    /** Optional arguments of updateItemState() – the defaults of the Python library. */
    struct UpdateItemStateArgs {
        std::optional<std::string> language;
        std::optional<std::string> source;
    };

    /**
     * Updates the state of an item.
     *
     * :param itemName: The name of the item.
     * :param state: The new state of the item.
     * :param language: Optional; Language filter for headers "Accept-Language".
     *
     * :return: A response object or confirmation that the state was successfully updated.
     */
    json updateItemState(const std::string& itemName, const std::string& state,
                         const std::optional<std::string>& language = std::nullopt,
                         const std::optional<std::string>& source = std::nullopt);
    /** updateItemState() with the optional arguments as struct. */
    json updateItemState(const std::string& itemName, const std::string& state,
                         const UpdateItemStateArgs& a);

    /**
     * Adds a tag to an item.
     *
     * :param itemName: The name of the item.
     * :param tag: The tag to be added.
     *
     * :return: A response object or confirmation that the tag was successfully added.
     */
    json addTag(const std::string& itemName, const std::string& tag);

    /**
     * Removes a tag from an item.
     *
     * :param itemName: The name of the item.
     * :param tag: The tag to be removed.
     *
     * :return: A response object or confirmation that the tag was successfully removed.
     */
    json removeTag(const std::string& itemName, const std::string& tag);

    /**
     * Remove unused/orphaned metadata.
     *
     * :return: A response object or confirmation that orphaned metadata was successfully purged.
     */
    json purgeOrphanedMetadata();

private:
    OpenHABClient* client_;
};

// ── Links ─────────────────────────────────────────────────────────────────────

class OPENHAB_API Links {
public:
    explicit Links(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getLinks() – the defaults of the Python library. */
    struct GetLinksArgs {
        std::optional<std::string> channelUID;
        std::optional<std::string> itemName;
    };

    /**
     * Gets all available links.
     *
     * :param channelUID: Optional; Filters by the Channel UID.
     * :param itemName: Optional; Filters by the Item Name.
     *
     * :return: A list of links containing details such as ItemName, ChannelUID, and configuration.
     */
    json getLinks(const std::optional<std::string>& channelUID = std::nullopt,
                  const std::optional<std::string>& itemName = std::nullopt);
    /** getLinks() with the optional arguments as struct. */
    json getLinks(const GetLinksArgs& a);

    /**
     * Retrieves an individual link.
     *
     * :param itemName: The name of the item.
     * :param channelUID: The UID of the channel.
     *
     * :return: The link with details of the item, channel UID, and configuration.
     */
    json getLink(const std::string& itemName, const std::string& channelUID);

    /**
     * Links an item to a channel.
     *
     * :param itemName: The name of the item.
     * :param channelUID: The UID of the channel.
     * :param configuration: The configuration for the link.
     *
     * :return: The API response when the link is successfully created.
     */
    json linkItemToChannel(const std::string& itemName, const std::string& channelUID,
                           const json& configuration);

    /**
     * Unlinks an item from a channel.
     *
     * :param itemName: The name of the item.
     * :param channelUID: The UID of the channel.
     *
     * :return: The API response when the link is successfully removed.
     */
    json unlinkItemFromChannel(const std::string& itemName, const std::string& channelUID);

    /**
     * Delete all links that refer to an item or thing.
     *
     * :param object: The name of the item or the UID of the thing.
     *
     * :return: The API response when all links are successfully deleted.
     */
    json deleteAllLinks(const std::string& object);

    /**
     * Get orphan links between items and broken/non-existent thing channels.
     *
     * :return: A list of orphan links.
     */
    json getOrphanLinks();

    /**
     * Remove unused/orphaned links.
     *
     * :return: The API response when the links are successfully removed.
     */
    json purgeUnusedLinks();

private:
    OpenHABClient* client_;
};

// ── Logging ───────────────────────────────────────────────────────────────────

class OPENHAB_API Logging {
public:
    explicit Logging(OpenHABClient& client) : client_(&client) {}

    /**
     * Get all loggers.
     *
     * :return: A list of loggers with names and levels.
     */
    json getLoggers();

    /**
     * Get a single logger.
     *
     * :param loggerName: The name of the logger.
     *
     * :return: The logger with the specified name and level.
     */
    json getLogger(const std::string& loggerName);

    /**
     * Modify or add a logger.
     *
     * :param loggerName: The name of the logger.
     * :param level: The level of the logger.
     *
     * :return: The API response after modification or addition.
     */
    json modifyOrAddLogger(const std::string& loggerName, const std::string& level);

    /**
     * Remove a single logger.
     *
     * :param loggerName: The name of the logger.
     *
     * :return: The API response after removing the logger.
     */
    json removeLogger(const std::string& loggerName);

private:
    OpenHABClient* client_;
};

// ── ModuleTypes ───────────────────────────────────────────────────────────────

class OPENHAB_API ModuleTypes {
public:
    explicit ModuleTypes(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getModuleTypes() – the defaults of the Python library. */
    struct GetModuleTypesArgs {
        std::optional<std::string> tags;
        std::optional<std::string> typeFilter;
        std::optional<std::string> language;
    };

    /**
     * Get all available module types.
     *
     * :param tags: Optional filter for tags.
     * :param typeFilter: Optional filter for the type (action, condition, trigger).
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A list of module types.
     */
    json getModuleTypes(const std::optional<std::string>& tags = std::nullopt,
                        const std::optional<std::string>& typeFilter = std::nullopt,
                        const std::optional<std::string>& language = std::nullopt);
    /** getModuleTypes() with the optional arguments as struct. */
    json getModuleTypes(const GetModuleTypesArgs& a);

    /** Optional arguments of getModuleType() – the defaults of the Python library. */
    struct GetModuleTypeArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets a module type corresponding to the given UID.
     *
     * :param moduleTypeUID: The UID of the module type.
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A dictionary with the module type information.
     */
    json getModuleType(const std::string& moduleTypeUID,
                       const std::optional<std::string>& language = std::nullopt);
    /** getModuleType() with the optional arguments as struct. */
    json getModuleType(const std::string& moduleTypeUID, const GetModuleTypeArgs& a);

private:
    OpenHABClient* client_;
};

// ── Persistence ───────────────────────────────────────────────────────────────

class OPENHAB_API Persistence {
public:
    explicit Persistence(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getServices() – the defaults of the Python library. */
    struct GetServicesArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets a list of persistence services.
     *
     * :return: A list of persistence services with IDs, labels, and types.
     */
    json getServices(const std::optional<std::string>& language = std::nullopt);
    /** getServices() with the optional arguments as struct. */
    json getServices(const GetServicesArgs& a);

    /**
     * Gets a persistence service configuration.
     *
     * :param serviceID: The ID of the persistence service.
     *
     * :return: The configuration of the service.
     */
    json getServiceConfiguration(const std::string& serviceID);

    /**
     * Sets a persistence service configuration.
     *
     * :param serviceID: The ID of the persistence service.
     * :param config: The configuration data.
     *
     * :return: The response from the API after modification.
     */
    json setServiceConfiguration(const std::string& serviceID, const json& config);

    /**
     * Deletes a persistence service configuration.
     *
     * :param serviceID: The ID of the persistence service.
     *
     * :return: The response from the API after deleting the configuration.
     */
    json deleteServiceConfiguration(const std::string& serviceID);

    /** Optional arguments of getItemsFromService() – the defaults of the Python library. */
    struct GetItemsFromServiceArgs {
        std::optional<std::string> serviceID;
        std::optional<std::string> itemName;
    };

    /**
     * Gets a list of items available via a specific persistence service.
     *
     * :param serviceID: Optional; The ID of the persistence service (default service if omitted).
     * :param itemName: Optional; Only return information for this item.
     *
     * :return: A list of items with their last and earliest timestamps.
     */
    json getItemsFromService(const std::optional<std::string>& serviceID = std::nullopt,
                             const std::optional<std::string>& itemName = std::nullopt);
    /** getItemsFromService() with the optional arguments as struct. */
    json getItemsFromService(const GetItemsFromServiceArgs& a);

    /** Optional arguments of getItemPersistenceData() – the defaults of the Python library. */
    struct GetItemPersistenceDataArgs {
        std::optional<std::string> serviceID;
        std::optional<std::string> startTime;
        std::optional<std::string> endTime;
        std::optional<int> page;
        std::optional<int> pageLength;
        bool boundary = false;
        bool itemState = false;
        std::optional<bool> displayState;
        std::optional<std::string> language;
    };

    /**
     * Gets item persistence data from the persistence service.
     *
     * :param itemName: The name of the item.
     * :param serviceID: Optional; The ID of the persistence service. If omitted, the default service is used.
     * :param startTime: Optional; Start time (ISO 8601, e.g. "2026-10-30T00:00:00.000Z"). Defaults to 1 day before `endTime`.
     * :param endTime: Optional; End time (ISO 8601). Defaults to the current time.
     * :param page: Optional; Page number, starting at 0. Paging is only active if `pageLength` is set as well.
     * :param pageLength: Optional; Number of data points per page. Without it, all data points are returned.
     * :param boundary: Optional; Also return the values just before and after the time range (default: False).
     * :param itemState: Optional; Add the current item state at the end of the series (default: False).
     * :param displayState: Optional; Add a formatted display state to every data point (openHAB 5.0+).
     * :param language: Optional; Value for the "Accept-Language" header.
     *
     * :return: The retrieved data points of the item.
     */
    json getItemPersistenceData(const std::string& itemName,
                                const std::optional<std::string>& serviceID = std::nullopt,
                                const std::optional<std::string>& startTime = std::nullopt,
                                const std::optional<std::string>& endTime = std::nullopt,
                                const std::optional<int>& page = std::nullopt,
                                const std::optional<int>& pageLength = std::nullopt,
                                bool boundary = false, bool itemState = false,
                                const std::optional<bool>& displayState = std::nullopt,
                                const std::optional<std::string>& language = std::nullopt);
    /** getItemPersistenceData() with the optional arguments as struct. */
    json getItemPersistenceData(const std::string& itemName, const GetItemPersistenceDataArgs& a);

    /** Optional arguments of storeItemData() – the defaults of the Python library. */
    struct StoreItemDataArgs {
        std::optional<std::string> serviceID;
    };

    /**
     * Stores item persistence data into the persistence service.
     *
     * :param serviceID: The ID of the persistence service.
     * :param itemName: The name of the item.
     * :param time: The time of the storage.
     * :param state: The state of the item to be stored.
     *
     * :return: The response from the API after storing the data.
     */
    json storeItemData(const std::string& itemName, const std::string& time,
                       const std::string& state,
                       const std::optional<std::string>& serviceID = std::nullopt);
    /** storeItemData() with the optional arguments as struct. */
    json storeItemData(const std::string& itemName, const std::string& time,
                       const std::string& state, const StoreItemDataArgs& a);

    /**
     * Deletes item persistence data from a specific persistence service in a given time range.
     *
     * :param serviceID: The ID of the persistence service.
     * :param itemName: The name of the item.
     * :param startTime: The start time of the data to be deleted.
     * :param endTime: The end time of the data to be deleted.
     *
     * :return: The response from the API after deleting the data.
     */
    json deleteItemData(const std::string& itemName, const std::string& startTime,
                        const std::string& endTime, const std::string& serviceID);

private:
    OpenHABClient* client_;
};

// ── ProfileTypes ──────────────────────────────────────────────────────────────

class OPENHAB_API ProfileTypes {
public:
    explicit ProfileTypes(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getProfileTypes() – the defaults of the Python library. */
    struct GetProfileTypesArgs {
        std::optional<std::string> channelTypeUID;
        std::optional<std::string> itemType;
        std::optional<std::string> language;
    };

    /**
     * Gets all available profile types.
     *
     * :param channelTypeUID: Optional filter for the channel type.
     * :param itemType: Optional filter for the item type.
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A list of profile types.
     */
    json getProfileTypes(const std::optional<std::string>& channelTypeUID = std::nullopt,
                         const std::optional<std::string>& itemType = std::nullopt,
                         const std::optional<std::string>& language = std::nullopt);
    /** getProfileTypes() with the optional arguments as struct. */
    json getProfileTypes(const GetProfileTypesArgs& a);

private:
    OpenHABClient* client_;
};

// ── Rules ─────────────────────────────────────────────────────────────────────

class OPENHAB_API Rules {
public:
    explicit Rules(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getRules() – the defaults of the Python library. */
    struct GetRulesArgs {
        std::optional<std::string> prefix;
        std::optional<std::string> tags;
        bool summary = false;
        bool staticDataOnly = false;
    };

    /**
     * Get available rules, optionally filtered by tags and/or prefix.
     *
     * :param prefix: Optional prefix to filter the results.
     * :param tags: Optional tag array to filter the results.
     * :param summary: If true, only summary fields will be returned.
     * :param staticDataOnly: If true, only static data will be returned.
     *
     * :return: A list of rules (JSON objects).
     */
    json getRules(const std::optional<std::string>& prefix = std::nullopt,
                  const std::optional<std::string>& tags = std::nullopt, bool summary = false,
                  bool staticDataOnly = false);
    /** getRules() with the optional arguments as struct. */
    json getRules(const GetRulesArgs& a);

    /**
     * Creates a rule.
     *
     * :param ruleData: The rule data to be created (as a dictionary).
     *
     * :return: The created rule (JSON).
     */
    json createRule(const json& ruleData);

    /**
     * Gets the rule corresponding to the given UID.
     *
     * :param ruleUID: The UID of the rule to retrieve.
     *
     * :return: The rule object (JSON).
     */
    json getRule(const std::string& ruleUID);

    /**
     * Updates an existing rule corresponding to the given UID.
     *
     * :param ruleUID: The UID of the rule to update.
     * :param ruleData: The new rule data (as a dictionary).
     *
     * :return: The updated rule (JSON).
     */
    json updateRule(const std::string& ruleUID, const json& ruleData);

    /**
     * Removes an existing rule corresponding to the given UID.
     *
     * :param ruleUID: The UID of the rule to delete.
     *
     * :return: The API response (status code).
     */
    json deleteRule(const std::string& ruleUID);

    /**
     * Gets the rule's module corresponding to the given category and ID.
     *
     * :param ruleUID: The UID of the rule.
     * :param moduleCategory: The category of the module.
     * :param moduleID: The ID of the module.
     *
     * :return: The module (JSON).
     */
    json getModule(const std::string& ruleUID, const std::string& moduleCategory,
                   const std::string& moduleID);

    /**
     * Gets the module's configuration.
     *
     * :param ruleUID: The UID of the rule.
     * :param moduleCategory: The category of the module.
     * :param moduleID: The ID of the module.
     *
     * :return: The module configuration (JSON).
     */
    json getModuleConfig(const std::string& ruleUID, const std::string& moduleCategory,
                         const std::string& moduleID);

    /**
     * Gets the module's configuration parameter.
     *
     * :param ruleUID: The UID of the rule.
     * :param moduleCategory: The category of the module.
     * :param moduleID: The ID of the module.
     * :param param: The name of the configuration parameter.
     *
     * :return: The configuration parameter value (JSON).
     */
    json getModuleConfigParam(const std::string& ruleUID, const std::string& moduleCategory,
                              const std::string& moduleID, const std::string& param);

    /**
     * Sets the module's configuration parameter value.
     *
     * :param ruleUID: The UID of the rule.
     * :param moduleCategory: The category of the module.
     * :param moduleID: The ID of the module.
     * :param param: The name of the configuration parameter.
     * :param value: The value to set for the configuration parameter.
     *
     * :return: The API response (status code).
     */
    json setModuleConfigParam(const std::string& ruleUID, const std::string& moduleCategory,
                              const std::string& moduleID, const std::string& param,
                              const std::string& value);

    /**
     * Gets the rule actions.
     *
     * :param ruleUID: The UID of the rule.
     *
     * :return: A list of actions (JSON).
     */
    json getActions(const std::string& ruleUID);

    /**
     * Gets the rule conditions.
     *
     * :param ruleUID: The UID of the rule.
     *
     * :return: A list of conditions (JSON).
     */
    json getConditions(const std::string& ruleUID);

    /**
     * Gets the rule configuration values.
     *
     * :param ruleUID: The UID of the rule.
     *
     * :return: The configuration of the rule (JSON).
     */
    json getConfiguration(const std::string& ruleUID);

    /**
     * Sets the rule configuration values.
     *
     * :param ruleUID: The UID of the rule.
     * :param configData: The new configuration data (as a dictionary).
     *
     * :return: The updated configuration (JSON).
     */
    json updateConfiguration(const std::string& ruleUID, const json& configData);

    /**
     * Sets the rule configuration values. Activates or deactivates the rule.
     *
     * :param ruleUID: The UID of the rule.
     * :param enable: If true, the rule will be activated. If false, the rule will be deactivated.
     *
     * :return: The API response (status code).
     */
    json setRuleState(const std::string& ruleUID, bool enable);

    /**
     */
    json enable(const std::string& ruleUID);

    /**
     */
    json disable(const std::string& ruleUID);

    /** Optional arguments of runNow() – the defaults of the Python library. */
    struct RunNowArgs {
        json contextData;
    };

    /**
     * Executes the rule's actions immediately.
     *
     * :param ruleUID: The UID of the rule.
     * :param contextData: Optional context data for executing the rule.
     *
     * :return: The API response (status code).
     */
    json runNow(const std::string& ruleUID, const json& contextData = nullptr);
    /** runNow() with the optional arguments as struct. */
    json runNow(const std::string& ruleUID, const RunNowArgs& a);

    /**
     * Gets the rule triggers.
     *
     * :param ruleUID: The UID of the rule.
     *
     * :return: A list of triggers (JSON).
     */
    json getTriggers(const std::string& ruleUID);

    /**
     * Simulates the executions of rules filtered by tag 'Schedule' within the given times.
     *
     * :param fromTime: Simulates the executions of rules filtered by tag 'Schedule' within the given times.
     * :param untilTime: Simulates the executions of rules filtered by tag 'Schedule' within the given times.
     *
     * :return: The simulation results (JSON).
     */
    json simulateSchedule(const std::string& fromTime, const std::string& untilTime);

private:
    OpenHABClient* client_;
};

// ── Services ──────────────────────────────────────────────────────────────────

class OPENHAB_API Services {
public:
    explicit Services(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getServices() – the defaults of the Python library. */
    struct GetServicesArgs {
        std::optional<std::string> language;
    };

    /**
     * Get all configurable services.
     *
     * :param language: Optional language setting (as header).
     *
     * :return: A list of services (JSON).
     */
    json getServices(const std::optional<std::string>& language = std::nullopt);
    /** getServices() with the optional arguments as struct. */
    json getServices(const GetServicesArgs& a);

    /** Optional arguments of getService() – the defaults of the Python library. */
    struct GetServiceArgs {
        std::optional<std::string> language;
    };

    /**
     * Get configurable service for the given service ID.
     *
     * :param serviceID: The ID of the service to retrieve.
     * :param language: Optional language setting (as header).
     *
     * :return: The service object (JSON).
     */
    json getService(const std::string& serviceID,
                    const std::optional<std::string>& language = std::nullopt);
    /** getService() with the optional arguments as struct. */
    json getService(const std::string& serviceID, const GetServiceArgs& a);

    /**
     * Get service configuration for the given service ID.
     *
     * :param serviceID: The ID of the service.
     *
     * :return: The configuration of the service (JSON).
     */
    json getServiceConfig(const std::string& serviceID);

    /** Optional arguments of updateServiceConfig() – the defaults of the Python library. */
    struct UpdateServiceConfigArgs {
        std::optional<std::string> language;
    };

    /**
     * Updates a service configuration for the given service ID and returns the old configuration.
     *
     * :param serviceID: The ID of the service.
     * :param configData: The new configuration data (as a dictionary).
     *
     * :return: The old configuration of the service (JSON).
     */
    json updateServiceConfig(const std::string& serviceID, const json& configData,
                             const std::optional<std::string>& language = std::nullopt);
    /** updateServiceConfig() with the optional arguments as struct. */
    json updateServiceConfig(const std::string& serviceID, const json& configData,
                             const UpdateServiceConfigArgs& a);

    /**
     * Deletes a service configuration for the given service ID and returns the old configuration.
     *
     * :param serviceID: The ID of the service.
     *
     * :return: The old configuration of the service (JSON).
     */
    json deleteServiceConfig(const std::string& serviceID);

    /** Optional arguments of getServiceContexts() – the defaults of the Python library. */
    struct GetServiceContextsArgs {
        std::optional<std::string> language;
    };

    /**
     * Get existing multiple context service configurations for the given factory PID.
     *
     * :param serviceID: The ID of the service.
     * :param language: Optional language setting (as header).
     *
     * :return: A list of contexts (JSON).
     */
    json getServiceContexts(const std::string& serviceID,
                            const std::optional<std::string>& language = std::nullopt);
    /** getServiceContexts() with the optional arguments as struct. */
    json getServiceContexts(const std::string& serviceID, const GetServiceContextsArgs& a);

private:
    OpenHABClient* client_;
};

// ── Sitemaps ──────────────────────────────────────────────────────────────────

class OPENHAB_API Sitemaps {
public:
    explicit Sitemaps(OpenHABClient& client) : client_(&client) {}

    /**
     * Get all available sitemaps.
     *
     * :return: A list of sitemaps (JSON).
     */
    json getSitemaps();

    /** Optional arguments of getSitemap() – the defaults of the Python library. */
    struct GetSitemapArgs {
        std::optional<std::string> type;
        std::optional<std::string> jsonCallback;
        bool includeHidden = false;
        std::optional<std::string> language;
    };

    /**
     * Get sitemap by name.
     *
     * :param sitemapName: The name of the sitemap to retrieve.
     * :param type: Optional query parameter for type.
     * :param jsonCallback: Optional query parameter for JSON callback.
     * :param includeHidden: Whether hidden widgets should be included.
     * :param language: Optional language setting (as header).
     *
     * :return: The sitemap object (JSON).
     */
    json getSitemap(const std::string& sitemapName,
                    const std::optional<std::string>& type = std::nullopt,
                    const std::optional<std::string>& jsonCallback = std::nullopt,
                    bool includeHidden = false,
                    const std::optional<std::string>& language = std::nullopt);
    /** getSitemap() with the optional arguments as struct. */
    json getSitemap(const std::string& sitemapName, const GetSitemapArgs& a);

    /** Optional arguments of getSitemapPage() – the defaults of the Python library. */
    struct GetSitemapPageArgs {
        std::optional<std::string> subscriptionID;
        bool includeHidden = false;
        std::optional<std::string> language;
    };

    /**
     * Polls the data for one page of a sitemap.
     *
     * :param sitemapName: The name of the sitemap.
     * :param pageID: The ID of the page.
     * :param subscriptionID: Optional query parameter for the subscription ID.
     * :param includeHidden: Whether hidden widgets should be included.
     * :param language: Optional language setting (as header).
     *
     * :return: The sitemap page (JSON).
     */
    json getSitemapPage(const std::string& sitemapName, const std::string& pageID,
                        const std::optional<std::string>& subscriptionID = std::nullopt,
                        bool includeHidden = false,
                        const std::optional<std::string>& language = std::nullopt);
    /** getSitemapPage() with the optional arguments as struct. */
    json getSitemapPage(const std::string& sitemapName, const std::string& pageID,
                        const GetSitemapPageArgs& a);

    /** Optional arguments of getFullSitemap() – the defaults of the Python library. */
    struct GetFullSitemapArgs {
        std::optional<std::string> subscriptionID;
        bool includeHidden = false;
        std::optional<std::string> language;
    };

    /**
     * Polls the data for a whole sitemap. Not recommended due to potentially high traffic.
     *
     * :param sitemapName: The name of the sitemap.
     * :param subscriptionID: Optional query parameter for the subscription ID.
     * :param includeHidden: Whether hidden widgets should be included.
     * :param language: Optional language setting (as header).
     *
     * :return: The complete sitemap (JSON).
     */
    json getFullSitemap(const std::string& sitemapName,
                        const std::optional<std::string>& subscriptionID = std::nullopt,
                        bool includeHidden = false,
                        const std::optional<std::string>& language = std::nullopt);
    /** getFullSitemap() with the optional arguments as struct. */
    json getFullSitemap(const std::string& sitemapName, const GetFullSitemapArgs& a);

    /** Optional arguments of getSitemapEvents() – the defaults of the Python library. */
    struct GetSitemapEventsArgs {
        std::optional<std::string> sitemapName;
        std::optional<std::string> pageID;
    };

    /**
     * Opens the event stream (SSE) of a sitemap subscription for one page.
     *
     * :param subscriptionID: The ID of the subscription (see subscribeToSitemapEvents()).
     * :param sitemapName: The name of the sitemap.
     * :param pageID: The ID of the page (the sitemap name for the home page).
     *
     * :return: A SSE stream (requests.Response, read it with iterSSEEvents()) or {"error": ...}.
     */
    EventStream getSitemapEvents(const std::string& subscriptionID,
                                 const std::optional<std::string>& sitemapName = std::nullopt,
                                 const std::optional<std::string>& pageID = std::nullopt);
    /** getSitemapEvents() with the optional arguments as struct. */
    EventStream getSitemapEvents(const std::string& subscriptionID, const GetSitemapEventsArgs& a);

    /** Optional arguments of getFullSitemapEvents() – the defaults of the Python library. */
    struct GetFullSitemapEventsArgs {
        std::optional<std::string> sitemapName;
    };

    /**
     * Opens the event stream (SSE) of a sitemap subscription for the whole sitemap.
     * Not recommended due to potentially high traffic.
     *
     * :param subscriptionID: The ID of the subscription.
     * :param sitemapName: The name of the sitemap.
     *
     * :return: A SSE stream (requests.Response) or {"error": ...}.
     */
    EventStream getFullSitemapEvents(const std::string& subscriptionID,
                                     const std::optional<std::string>& sitemapName = std::nullopt);
    /** getFullSitemapEvents() with the optional arguments as struct. */
    EventStream getFullSitemapEvents(const std::string& subscriptionID,
                                     const GetFullSitemapEventsArgs& a);

    /**
     * Creates a sitemap event subscription.
     *
     * :return: The response to the subscription request (JSON).
     */
    json subscribeToSitemapEvents();

private:
    OpenHABClient* client_;
};

// ── Systeminfo ────────────────────────────────────────────────────────────────

class OPENHAB_API Systeminfo {
public:
    explicit Systeminfo(OpenHABClient& client) : client_(&client) {}

    /**
     * Gets information about the system.
     *
     * :return: A Dictionary with system informations.
     */
    json getSystemInfo();

    /**
     * Get all supported dimensions and their system units.
     *
     * :return: A Dictionary with UOM informations.
     */
    json getUoMInfo();

private:
    OpenHABClient* client_;
};

// ── Tags ──────────────────────────────────────────────────────────────────────

class OPENHAB_API Tags {
public:
    explicit Tags(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getTags() – the defaults of the Python library. */
    struct GetTagsArgs {
        std::optional<std::string> language;
    };

    /**
     * Get all available semantic tags.
     *
     * :param language: Optional headers for language setting.
     *
     * :return: A list of semantic tags (JSON).
     */
    json getTags(const std::optional<std::string>& language = std::nullopt);
    /** getTags() with the optional arguments as struct. */
    json getTags(const GetTagsArgs& a);

    /** Optional arguments of createTag() – the defaults of the Python library. */
    struct CreateTagArgs {
        std::optional<std::string> language;
    };

    /**
     * Creates a new semantic tag and adds it to the registry.
     *
     * :param tagData: The data object for the tag to be created.
     * :param language: Optional headers for language setting.
     *
     * :return: The response to the tag creation request (JSON).
     */
    json createTag(const json& tagData, const std::optional<std::string>& language = std::nullopt);
    /** createTag() with the optional arguments as struct. */
    json createTag(const json& tagData, const CreateTagArgs& a);

    /** Optional arguments of getTag() – the defaults of the Python library. */
    struct GetTagArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets a semantic tag and its sub-tags.
     *
     * :param tagID: The ID of the tag to retrieve.
     * :param language: Optional headers for language setting.
     *
     * :return: The tag object and its sub-tags (JSON).
     */
    json getTag(const std::string& tagID,
                const std::optional<std::string>& language = std::nullopt);
    /** getTag() with the optional arguments as struct. */
    json getTag(const std::string& tagID, const GetTagArgs& a);

    /** Optional arguments of updateTag() – the defaults of the Python library. */
    struct UpdateTagArgs {
        std::optional<std::string> language;
    };

    /**
     * Updates a semantic tag.
     *
     * :param tagID: The ID of the tag to be updated.
     * :param tagData: The new tag data.
     * :param language: Optional headers for language setting.
     *
     * :return: The response to the tag update request (JSON).
     */
    json updateTag(const std::string& tagID, const json& tagData,
                   const std::optional<std::string>& language = std::nullopt);
    /** updateTag() with the optional arguments as struct. */
    json updateTag(const std::string& tagID, const json& tagData, const UpdateTagArgs& a);

    /** Optional arguments of deleteTag() – the defaults of the Python library. */
    struct DeleteTagArgs {
        std::optional<std::string> language;
    };

    /**
     * Removes a semantic tag and its sub-tags from the registry.
     *
     * :param tagID: The ID of the tag to be removed.
     * :param language: Optional headers for language setting.
     *
     * :return: The response to the tag deletion request (JSON).
     */
    json deleteTag(const std::string& tagID,
                   const std::optional<std::string>& language = std::nullopt);
    /** deleteTag() with the optional arguments as struct. */
    json deleteTag(const std::string& tagID, const DeleteTagArgs& a);

private:
    OpenHABClient* client_;
};

// ── Templates ─────────────────────────────────────────────────────────────────

class OPENHAB_API Templates {
public:
    explicit Templates(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getTemplates() – the defaults of the Python library. */
    struct GetTemplatesArgs {
        std::optional<std::string> language;
    };

    /**
     * Get all available templates.
     *
     * :param language: (Optional) Language setting for the Accept-Language header.
     * :return: A list of templates.
     */
    json getTemplates(const std::optional<std::string>& language = std::nullopt);
    /** getTemplates() with the optional arguments as struct. */
    json getTemplates(const GetTemplatesArgs& a);

    /** Optional arguments of getTemplate() – the defaults of the Python library. */
    struct GetTemplateArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets a template corresponding to the given UID.
     *
     * :param templateUID: The UID of the template.
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A dictionary with the details of the template.
     */
    json getTemplate(const std::string& templateUID,
                     const std::optional<std::string>& language = std::nullopt);
    /** getTemplate() with the optional arguments as struct. */
    json getTemplate(const std::string& templateUID, const GetTemplateArgs& a);

private:
    OpenHABClient* client_;
};

// ── ThingTypes ────────────────────────────────────────────────────────────────

class OPENHAB_API ThingTypes {
public:
    explicit ThingTypes(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getThingTypes() – the defaults of the Python library. */
    struct GetThingTypesArgs {
        std::optional<std::string> bindingID;
        std::optional<std::string> language;
    };

    /**
     * Gets all available thing types without config description, channels, and properties.
     *
     * :param bindingID: (Optional) Filter by binding ID.
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A list of thing types.
     */
    json getThingTypes(const std::optional<std::string>& bindingID = std::nullopt,
                       const std::optional<std::string>& language = std::nullopt);
    /** getThingTypes() with the optional arguments as struct. */
    json getThingTypes(const GetThingTypesArgs& a);

    /** Optional arguments of getThingType() – the defaults of the Python library. */
    struct GetThingTypeArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets a thing type by UID.
     *
     * :param thingTypeUID: The UID of the thing type.
     * :param language: (Optional) Language setting for the Accept-Language header.
     *
     * :return: A dictionary with the details of the thing type or an empty response with status 204.
     */
    json getThingType(const std::string& thingTypeUID,
                      const std::optional<std::string>& language = std::nullopt);
    /** getThingType() with the optional arguments as struct. */
    json getThingType(const std::string& thingTypeUID, const GetThingTypeArgs& a);

private:
    OpenHABClient* client_;
};

// ── Things ────────────────────────────────────────────────────────────────────

class OPENHAB_API Things {
public:
    explicit Things(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getThings() – the defaults of the Python library. */
    struct GetThingsArgs {
        bool summary = false;
        bool staticDataOnly = false;
        std::optional<std::string> language;
    };

    /**
     * Get all available things.
     *
     * :param summary: If True, returns only the summary fields.
     * :param staticDataOnly: If True, returns a cacheable list.
     * :param language: The preferred language for the response.
     *
     * :return: JSON response with the things.
     */
    json getThings(bool summary = false, bool staticDataOnly = false,
                   const std::optional<std::string>& language = std::nullopt);
    /** getThings() with the optional arguments as struct. */
    json getThings(const GetThingsArgs& a);

    /** Optional arguments of createThing() – the defaults of the Python library. */
    struct CreateThingArgs {
        std::optional<std::string> language;
    };

    /**
     * Creates a new thing and adds it to the registry.
     *
     * :param thingData: The JSON object containing the thing data.
     * :param language: The preferred language for the response.
     *
     * :return: The API response.
     */
    json createThing(const json& thingData,
                     const std::optional<std::string>& language = std::nullopt);
    /** createThing() with the optional arguments as struct. */
    json createThing(const json& thingData, const CreateThingArgs& a);

    /** Optional arguments of getThing() – the defaults of the Python library. */
    struct GetThingArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets a thing by UID.
     *
     * :param thingUID: The UID of the thing.
     * :param language: The preferred language for the response.
     *
     * :return: JSON response with the thing data.
     */
    json getThing(const std::string& thingUID,
                  const std::optional<std::string>& language = std::nullopt);
    /** getThing() with the optional arguments as struct. */
    json getThing(const std::string& thingUID, const GetThingArgs& a);

    /** Optional arguments of updateThing() – the defaults of the Python library. */
    struct UpdateThingArgs {
        std::optional<std::string> language;
    };

    /**
     * Updates a thing.
     *
     * :param thingUID: The UID of the thing.
     * :param thingData: The JSON object containing the updated thing data.
     * :param language: The preferred language for the response.
     *
     * :return: The API response.
     */
    json updateThing(const std::string& thingUID, const json& thingData,
                     const std::optional<std::string>& language = std::nullopt);
    /** updateThing() with the optional arguments as struct. */
    json updateThing(const std::string& thingUID, const json& thingData, const UpdateThingArgs& a);

    /** Optional arguments of deleteThing() – the defaults of the Python library. */
    struct DeleteThingArgs {
        bool force = false;
        std::optional<std::string> language;
    };

    /**
     * Removes a thing from the registry. Set 'force' to __true__ if you want the thing to be removed immediately.
     *
     * :param thingUID: The UID of the thing.
     * :param force: If True, the thing will be immediately removed.
     * :param language: The preferred language for the response.
     *
     * :return: The API response.
     */
    json deleteThing(const std::string& thingUID, bool force = false,
                     const std::optional<std::string>& language = std::nullopt);
    /** deleteThing() with the optional arguments as struct. */
    json deleteThing(const std::string& thingUID, const DeleteThingArgs& a);

    /** Optional arguments of updateThingConfiguration() – the defaults of the Python library. */
    struct UpdateThingConfigurationArgs {
        std::optional<std::string> language;
    };

    /**
     * Updates a thing's configuration.
     *
     * :param thingUID: The UID of the thing.
     * :param configurationData: The configuration data of the thing.
     * :param language: The preferred language for the response.
     *
     * :return: The API response.
     */
    json updateThingConfiguration(const std::string& thingUID, const json& configurationData,
                                  const std::optional<std::string>& language = std::nullopt);
    /** updateThingConfiguration() with the optional arguments as struct. */
    json updateThingConfiguration(const std::string& thingUID, const json& configurationData,
                                  const UpdateThingConfigurationArgs& a);

    /** Optional arguments of getThingConfigStatus() – the defaults of the Python library. */
    struct GetThingConfigStatusArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets the thing's configuration status.
     *
     * :param thingUID: The UID of the thing.
     * :param language: The preferred language for the response.
     *
     * :return: JSON response with the thing's configuration status.
     */
    json getThingConfigStatus(const std::string& thingUID,
                              const std::optional<std::string>& language = std::nullopt);
    /** getThingConfigStatus() with the optional arguments as struct. */
    json getThingConfigStatus(const std::string& thingUID, const GetThingConfigStatusArgs& a);

    /** Optional arguments of setThingStatus() – the defaults of the Python library. */
    struct SetThingStatusArgs {
        std::optional<std::string> language;
    };

    /**
     * Sets the thing's enabled status.
     *
     * :param thingUID: The UID of the thing.
     * :param enabled: If True, the thing will be enabled.
     * :param language: The preferred language for the response.
     *
     * :return: The API response.
     */
    json setThingStatus(const std::string& thingUID, bool enabled,
                        const std::optional<std::string>& language = std::nullopt);
    /** setThingStatus() with the optional arguments as struct. */
    json setThingStatus(const std::string& thingUID, bool enabled, const SetThingStatusArgs& a);

    /**
     */
    json enableThing(const std::string& thingUID);

    /**
     */
    json disableThing(const std::string& thingUID);

    /** Optional arguments of updateThingFirmware() – the defaults of the Python library. */
    struct UpdateThingFirmwareArgs {
        std::optional<std::string> language;
    };

    /**
     * Updates the firmware of a thing.
     *
     * :param thingUID: The UID of the thing.
     * :param firmwareVersion: The firmware version.
     * :param language: The preferred language for the response.
     *
     * :return: The API response.
     */
    json updateThingFirmware(const std::string& thingUID, const std::string& firmwareVersion,
                             const std::optional<std::string>& language = std::nullopt);
    /** updateThingFirmware() with the optional arguments as struct. */
    json updateThingFirmware(const std::string& thingUID, const std::string& firmwareVersion,
                             const UpdateThingFirmwareArgs& a);

    /** Optional arguments of getThingFirmwareStatus() – the defaults of the Python library. */
    struct GetThingFirmwareStatusArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets the thing's firmware status.
     *
     * :param thingUID: The UID of the thing.
     * :param language: The preferred language for the response.
     *
     * :return: JSON response with the firmware status.
     */
    json getThingFirmwareStatus(const std::string& thingUID,
                                const std::optional<std::string>& language = std::nullopt);
    /** getThingFirmwareStatus() with the optional arguments as struct. */
    json getThingFirmwareStatus(const std::string& thingUID, const GetThingFirmwareStatusArgs& a);

    /** Optional arguments of getThingFirmwares() – the defaults of the Python library. */
    struct GetThingFirmwaresArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets all available firmwares for the provided thing UID.
     *
     * :param thingUID: The UID of the thing.
     * :param language: The preferred language for the response.
     *
     * :return: A list of available firmwares.
     */
    json getThingFirmwares(const std::string& thingUID,
                           const std::optional<std::string>& language = std::nullopt);
    /** getThingFirmwares() with the optional arguments as struct. */
    json getThingFirmwares(const std::string& thingUID, const GetThingFirmwaresArgs& a);

    /** Optional arguments of getThingStatus() – the defaults of the Python library. */
    struct GetThingStatusArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets the thing's status.
     *
     * :param thingUID: The UID of the thing.
     * :param language: The preferred language for the response.
     *
     * :return: JSON response with the thing's status.
     */
    json getThingStatus(const std::string& thingUID,
                        const std::optional<std::string>& language = std::nullopt);
    /** getThingStatus() with the optional arguments as struct. */
    json getThingStatus(const std::string& thingUID, const GetThingStatusArgs& a);

private:
    OpenHABClient* client_;
};

// ── Transformations ───────────────────────────────────────────────────────────

class OPENHAB_API Transformations {
public:
    explicit Transformations(OpenHABClient& client) : client_(&client) {}

    /**
     * Get a list of all transformations.
     *
     * :return: A list of transformations (JSON).
     */
    json getTransformations();

    /**
     * Get a single transformation.
     *
     * :param transformationUID: The transformationUID of the transformation to retrieve.
     *
     * :return: The transformation (JSON).
     */
    json getTransformation(const std::string& transformationUID);

    /**
     * Update a single transformation.
     *
     * :param transformationUID: The transformationUID of the transformation to update.
     * :param transformationData: The new data for the transformation.
     *
     * :return: The response to the transformation update request (JSON).
     */
    json updateTransformation(const std::string& transformationUID, const json& transformationData);

    /**
     * Delete a single transformation.
     *
     * :param transformationUID: The transformationUID of the transformation to delete.
     *
     * :return: The response to the transformation update request (JSON) or status/error message.
     */
    json deleteTransformation(const std::string& transformationUID);

    /**
     * Get all transformation services.
     *
     * :return: A list of transformation services (JSON).
     */
    json getTransformationServices();

private:
    OpenHABClient* client_;
};

// ── UI ────────────────────────────────────────────────────────────────────────

class OPENHAB_API UI {
public:
    explicit UI(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getUIComponents() – the defaults of the Python library. */
    struct GetUIComponentsArgs {
        bool summary = false;
    };

    /**
     * Get all registered UI components in the specified namespace.
     *
     * :param namespace: The namespace for which UI components should be retrieved.
     * :param summary: If True, only summary fields will be returned.
     *
     * :return: A list of UI components (JSON).
     */
    json getUIComponents(const std::string& namespace_, bool summary = false);
    /** getUIComponents() with the optional arguments as struct. */
    json getUIComponents(const std::string& namespace_, const GetUIComponentsArgs& a);

    /**
     * Add a UI component in the specified namespace.
     *
     * :param namespace: The namespace where the UI component should be added.
     * :param componentData: The data of the UI component (JSON) to be added.
     *
     * :return: The response to the request (JSON).
     */
    json addUIComponent(const std::string& namespace_, const json& componentData);

    /**
     * Get a specific UI component in the specified namespace.
     *
     * :param namespace: The namespace where the UI component is located.
     * :param componentUID: The UID of the UI component to retrieve.
     *
     * :return: The UI component (JSON).
     */
    json getUIComponent(const std::string& namespace_, const std::string& componentUID);

    /**
     * Update a specific UI component in the specified namespace.
     *
     * :param namespace: The namespace where the UI component should be updated.
     * :param componentUID: The UID of the UI component to update.
     * :param componentData: The new data for the UI component (JSON).
     *
     * :return: The response to the request (JSON).
     */
    json updateUIComponent(const std::string& namespace_, const std::string& componentUID,
                           const json& componentData);

    /**
     * Remove a specific UI component in the specified namespace.
     *
     * :param namespace: The namespace where the UI component should be removed.
     * :param componentUID: The UID of the UI component to delete.
     *
     * :return: The response to the request (JSON).
     */
    json deleteUIComponent(const std::string& namespace_, const std::string& componentUID);

    /**
     * Get all registered UI tiles.
     *
     * :return: A list of UI tiles (JSON).
     */
    json getUITiles();

private:
    OpenHABClient* client_;
};

// ── UUID ──────────────────────────────────────────────────────────────────────

class OPENHAB_API UUID {
public:
    explicit UUID(OpenHABClient& client) : client_(&client) {}

    /**
     * A unified unique id.
     *
     * :return: The UUID as String.
     */
    json getUUID();

private:
    OpenHABClient* client_;
};

// ── Voice ─────────────────────────────────────────────────────────────────────

class OPENHAB_API Voice {
public:
    explicit Voice(OpenHABClient& client) : client_(&client) {}

    /** Optional arguments of getDefaultVoice() – the defaults of the Python library. */
    struct GetDefaultVoiceArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets the default voice.
     *
     * :return: A dictionary with the details of the default voice.
     */
    json getDefaultVoice(const std::optional<std::string>& language = std::nullopt);
    /** getDefaultVoice() with the optional arguments as struct. */
    json getDefaultVoice(const GetDefaultVoiceArgs& a);

    /** Optional arguments of startDialog() – the defaults of the Python library. */
    struct StartDialogArgs {
        std::optional<std::string> ksID;
        std::optional<std::string> sttID;
        std::optional<std::string> ttsID;
        std::optional<std::string> voiceID;
        std::optional<std::string> hliIDs;
        std::optional<std::string> sinkID;
        std::optional<std::string> keyword;
        std::optional<std::string> listeningItem;
        std::optional<std::string> language;
    };

    /**
     * Start dialog processing for a given audio source.
     *
     * :param sourceID: The ID of the audio source.
     * :param ksID: The ID of the keyword spotter (optional).
     * :param sttID: The ID of the speech-to-text system (optional).
     * :param ttsID: The ID of the text-to-speech system (optional).
     * :param voiceID: The ID of the voice (optional).
     * :param hliIDs: A comma-separated list of interpreter IDs (optional).
     * :param sinkID: The ID of the audio output (optional).
     * :param keyword: The keyword used to start the dialog (optional).
     * :param listeningItem: The name of the item to listen to (optional).
     * :param language: The language for the request (optional).
     *
     * :return: The response from the server.
     */
    json startDialog(const std::string& sourceID,
                     const std::optional<std::string>& ksID = std::nullopt,
                     const std::optional<std::string>& sttID = std::nullopt,
                     const std::optional<std::string>& ttsID = std::nullopt,
                     const std::optional<std::string>& voiceID = std::nullopt,
                     const std::optional<std::string>& hliIDs = std::nullopt,
                     const std::optional<std::string>& sinkID = std::nullopt,
                     const std::optional<std::string>& keyword = std::nullopt,
                     const std::optional<std::string>& listeningItem = std::nullopt,
                     const std::optional<std::string>& language = std::nullopt);
    /** startDialog() with the optional arguments as struct. */
    json startDialog(const std::string& sourceID, const StartDialogArgs& a);

    /**
     * Stop dialog processing for a given audio source.
     *
     * :param sourceID: The ID of the audio source.
     * :return: The response from the server.
     */
    json stopDialog(const std::string& sourceID);

    /** Optional arguments of getInterpreters() – the defaults of the Python library. */
    struct GetInterpretersArgs {
        std::optional<std::string> language;
    };

    /**
     * Get the list of all interpreters.
     *
     * :param language: The language for the request (optional).
     *
     * :return: A list of interpreters if successful.
     */
    json getInterpreters(const std::optional<std::string>& language = std::nullopt);
    /** getInterpreters() with the optional arguments as struct. */
    json getInterpreters(const GetInterpretersArgs& a);

    /** Optional arguments of interpretText() – the defaults of the Python library. */
    struct InterpretTextArgs {
        std::optional<std::string> language;
    };

    /**
     * Sends a text to the default human language interpreter.
     *
     * :param text: The text to be interpreted.
     * :param language: The language of the text.
     * :param IDs: A list of interpreter IDs (optional).
     *
     * :return: The response from the server.
     */
    json interpretText(const std::string& text,
                       const std::optional<std::string>& language = std::nullopt);
    /** interpretText() with the optional arguments as struct. */
    json interpretText(const std::string& text, const InterpretTextArgs& a);

    /** Optional arguments of getInterpreter() – the defaults of the Python library. */
    struct GetInterpreterArgs {
        std::optional<std::string> language;
    };

    /**
     * Gets a single interpreter.
     *
     * :param interpreterID: The ID of the interpreter.
     * :param language: The language for the request (optional).
     *
     * :return: The details of the interpreter.
     */
    json getInterpreter(const std::string& interpreterID,
                        const std::optional<std::string>& language = std::nullopt);
    /** getInterpreter() with the optional arguments as struct. */
    json getInterpreter(const std::string& interpreterID, const GetInterpreterArgs& a);

    /** Optional arguments of interpretTextBatch() – the defaults of the Python library. */
    struct InterpretTextBatchArgs {
        std::optional<std::string> language;
    };

    /**
     * Sends a text to a given human language interpreter(s).
     *
     * :param text: The text to be interpreted.
     * :param language: The language of the text.
     * :param IDs: A list of interpreter IDs.
     *
     * :return: The response from the server.
     */
    json interpretTextBatch(const std::string& text, const json& IDs,
                            const std::optional<std::string>& language = std::nullopt);
    /** interpretTextBatch() with the optional arguments as struct. */
    json interpretTextBatch(const std::string& text, const json& IDs,
                            const InterpretTextBatchArgs& a);

    /** Optional arguments of listenAndAnswer() – the defaults of the Python library. */
    struct ListenAndAnswerArgs {
        std::optional<std::string> language;
    };

    /**
     * Executes a simple dialog sequence without keyword spotting for a given audio source.
     *
     * :param sourceID: The ID of the audio source.
     * :param sttID: The ID of the speech-to-text system.
     * :param ttsID: The ID of the text-to-speech system.
     * :param voiceID: The ID of the voice.
     * :param hliIDs: A list of interpreter IDs (optional).
     * :param sinkID: The ID of the audio output (optional).
     * :param listeningItem: The name of the item to listen to (optional).
     * :param language: The language for the request (optional).
     *
     * :return: The response from the server.
     */
    json listenAndAnswer(const std::string& sourceID, const std::string& sttID,
                         const std::string& ttsID, const std::string& voiceID, const json& hliIDs,
                         const std::string& sinkID, const std::string& listeningItem,
                         const std::optional<std::string>& language = std::nullopt);
    /** listenAndAnswer() with the optional arguments as struct. */
    json listenAndAnswer(const std::string& sourceID, const std::string& sttID,
                         const std::string& ttsID, const std::string& voiceID, const json& hliIDs,
                         const std::string& sinkID, const std::string& listeningItem,
                         const ListenAndAnswerArgs& a);

    /** Optional arguments of sayText() – the defaults of the Python library. */
    struct SayTextArgs {
        std::string volume = "100";
    };

    /**
     * Speaks a given text with a given voice through the given audio sink.
     *
     * :param text: The text to be spoken.
     * :param voiceID: The ID of the voice.
     * :param sinkID: The ID of the audio output.
     * :param volume: The volume level (default: 100).
     *
     * :return: The response from the server.
     */
    json sayText(const std::string& text, const std::string& voiceID, const std::string& sinkID,
                 const std::string& volume = "100");
    /** sayText() with the optional arguments as struct. */
    json sayText(const std::string& text, const std::string& voiceID, const std::string& sinkID,
                 const SayTextArgs& a);

    /** Optional arguments of getVoices() – the defaults of the Python library. */
    struct GetVoicesArgs {
        std::optional<std::string> language;
    };

    /**
     * Get the list of all voices.
     *
     * :return: A list of voices if successful.
     */
    json getVoices(const std::optional<std::string>& language = std::nullopt);
    /** getVoices() with the optional arguments as struct. */
    json getVoices(const GetVoicesArgs& a);

private:
    OpenHABClient* client_;
};

}  // namespace openhab
