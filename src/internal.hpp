// Internal declarations shared by the source files of the library.
#pragma once

#include "openhab/OpenHABClient.hpp"

#include <curl/curl.h>

#include <stdexcept>
#include <string>

namespace openhab {

struct OpenHABClient::Impl {
    std::string url;  // without trailing slash
    std::string username, password, token;
    double timeout = OpenHABClient::DEFAULT_TIMEOUT;
    bool verify = true;
    bool isCloud = false;
    bool isLoggedIn = false;
    std::string lastError;
};

namespace detail {

/** HTTP error (status >= 400) – Python: requests.exceptions.HTTPError. */
struct RequestException : std::runtime_error {
    int status;
    RequestException(const std::string& msg, int s) : std::runtime_error(msg), status(s) {}
};
struct HTTPError : RequestException {
    HTTPError(const std::string& msg, int s) : RequestException(msg, s) {}
};

/** Result of one request: value, and whether it is a StatusResponse (empty body). */
struct Reply {
    json value;
    bool isStatus = false;
};

void curlInitOnce();
std::string quote(const std::string& s, const std::string& safe);
std::string buildUrl(const OpenHABClient::Impl& c, const std::string& resourcePath);
/** "a=b&c=d" from a params object (None dropped, booleans lower case, lists repeated). */
std::string queryString(const json& params);
void applyAuth(CURL* h, const OpenHABClient::Impl& c);
curl_slist* authHeader(curl_slist* l, const OpenHABClient::Impl& c);
std::string httpErrorText(int status, const std::string& reason, const std::string& url,
                          const std::string& body);
/** Executes a request; throws HTTPError / RequestException like the Python client. */
Reply request(OpenHABClient::Impl& c, const std::string& verb, const std::string& path,
              const json& headers, const json& data, const json& params);
/** Opens a stream (Python: client.executeSSE); the stream carries errors. */
EventStream openStream(OpenHABClient::Impl& c, const std::string& path, const json& headers,
                       const json& params);
/** Python repr()/str() of a value (str for the top level). */
std::string pyStr(const json& v, bool top = true);

}  // namespace detail
}  // namespace openhab
