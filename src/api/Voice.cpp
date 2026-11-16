// Generated from Voice.py of python-openhab-rest-client by tools/py2cpp.py – do not edit.
#include "../py_rt.hpp"
#include "openhab/API.hpp"

namespace openhab {

static py::V Voice_getDefaultVoice(OpenHABClient& C, py::V v_language);
static py::V Voice_startDialog(OpenHABClient& C, py::V v_sourceID, py::V v_ksID, py::V v_sttID, py::V v_ttsID, py::V v_voiceID, py::V v_hliIDs, py::V v_sinkID, py::V v_keyword, py::V v_listeningItem, py::V v_language);
static py::V Voice_stopDialog(OpenHABClient& C, py::V v_sourceID);
static py::V Voice_getInterpreters(OpenHABClient& C, py::V v_language);
static py::V Voice_interpretText(OpenHABClient& C, py::V v_text, py::V v_language);
static py::V Voice_getInterpreter(OpenHABClient& C, py::V v_interpreterID, py::V v_language);
static py::V Voice_interpretTextBatch(OpenHABClient& C, py::V v_text, py::V v_IDs, py::V v_language);
static py::V Voice_listenAndAnswer(OpenHABClient& C, py::V v_sourceID, py::V v_sttID, py::V v_ttsID, py::V v_voiceID, py::V v_hliIDs, py::V v_sinkID, py::V v_listeningItem, py::V v_language);
static py::V Voice_sayText(OpenHABClient& C, py::V v_text, py::V v_voiceID, py::V v_sinkID, py::V v_volume);
static py::V Voice_getVoices(OpenHABClient& C, py::V v_language);

static py::V Voice_getDefaultVoice(OpenHABClient& C, py::V v_language) {
    (void)C;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/voice/defaultvoice"), py::dict({{"Accept", py::s("application/json")}, {"Accept-Language", v_language}}), py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("No default voice was found.")}});
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
        return py::dict({{"error", py::s("No default voice was found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Voice::getDefaultVoice(const std::optional<std::string>& language) {
    return py::finish([&] { return Voice_getDefaultVoice(*client_, py::arg(language)); });
}

json Voice::getDefaultVoice(const GetDefaultVoiceArgs& a) {
    return getDefaultVoice(a.language);
}

static py::V Voice_startDialog(OpenHABClient& C, py::V v_sourceID, py::V v_ksID, py::V v_sttID, py::V v_ttsID, py::V v_voiceID, py::V v_hliIDs, py::V v_sinkID, py::V v_keyword, py::V v_listeningItem, py::V v_language) {
    (void)C;
    (void)v_sourceID;
    (void)v_ksID;
    (void)v_sttID;
    (void)v_ttsID;
    (void)v_voiceID;
    (void)v_hliIDs;
    (void)v_sinkID;
    (void)v_keyword;
    (void)v_listeningItem;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::s("/voice/dialog/start"), (py::truthy(v_language) ? py::V(py::dict({{"Accept-Language", v_language}})) : py::V(py::dict())), py::V(), py::dict({{"sourceId", v_sourceID}, {"ksId", v_ksID}, {"sttId", v_sttID}, {"ttsId", v_ttsID}, {"voiceId", v_voiceID}, {"hliIds", v_hliIDs}, {"sinkId", v_sinkID}, {"keyword", v_keyword}, {"listeningItem", v_listeningItem}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Services are missing or language is not supported by services or dialog processing is already started for the audio source.")}});
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
        return py::dict({{"error", py::s("Services are missing or language is not supported by services or dialog processing is already started for the audio source.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Voice::startDialog(const std::string& sourceID, const std::optional<std::string>& ksID, const std::optional<std::string>& sttID, const std::optional<std::string>& ttsID, const std::optional<std::string>& voiceID, const std::optional<std::string>& hliIDs, const std::optional<std::string>& sinkID, const std::optional<std::string>& keyword, const std::optional<std::string>& listeningItem, const std::optional<std::string>& language) {
    return py::finish([&] { return Voice_startDialog(*client_, py::arg(sourceID), py::arg(ksID), py::arg(sttID), py::arg(ttsID), py::arg(voiceID), py::arg(hliIDs), py::arg(sinkID), py::arg(keyword), py::arg(listeningItem), py::arg(language)); });
}

json Voice::startDialog(const std::string& sourceID, const StartDialogArgs& a) {
    return startDialog(sourceID, a.ksID, a.sttID, a.ttsID, a.voiceID, a.hliIDs, a.sinkID, a.keyword, a.listeningItem, a.language);
}

static py::V Voice_stopDialog(OpenHABClient& C, py::V v_sourceID) {
    (void)C;
    (void)v_sourceID;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::s("/voice/dialog/stop"), py::V(), py::V(), py::dict({{"sourceId", v_sourceID}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(405)))) {
            return py::dict({{"error", py::s("No dialog processing is started for the audio source.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("No audio source was found.")}});
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
        return py::dict({{"error", py::s("No audio source was found.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("No dialog processing is started for the audio source.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Voice::stopDialog(const std::string& sourceID) {
    return py::finish([&] { return Voice_stopDialog(*client_, py::arg(sourceID)); });
}

static py::V Voice_getInterpreters(OpenHABClient& C, py::V v_language) {
    (void)C;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::s("/voice/interpreters"), v_headers, py::V(), py::V());
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

json Voice::getInterpreters(const std::optional<std::string>& language) {
    return py::finish([&] { return Voice_getInterpreters(*client_, py::arg(language)); });
}

json Voice::getInterpreters(const GetInterpretersArgs& a) {
    return getInterpreters(a.language);
}

static py::V Voice_interpretText(OpenHABClient& C, py::V v_text, py::V v_language) {
    (void)C;
    (void)v_text;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("text/plain")}, {"Accept", py::s("text/plain")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "post", py::s("/voice/interpreters"), v_headers, v_text, py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::cat({py::s("Interpretation exception occurs: "), py::excStr(e_err)})}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("No human language interpreter was found.")}});
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
        return py::dict({{"error", py::s("No human language interpreter was found.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Interpretation exception occurs.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Voice::interpretText(const std::string& text, const std::optional<std::string>& language) {
    return py::finish([&] { return Voice_interpretText(*client_, py::arg(text), py::arg(language)); });
}

json Voice::interpretText(const std::string& text, const InterpretTextArgs& a) {
    return interpretText(text, a.language);
}

static py::V Voice_getInterpreter(OpenHABClient& C, py::V v_interpreterID, py::V v_language) {
    (void)C;
    (void)v_interpreterID;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Accept", py::s("application/json")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "get", py::cat({py::s("/voice/interpreters/"), v_interpreterID}), v_headers, py::V(), py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("Interpreter not found.")}});
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
        return py::dict({{"error", py::s("Interpreter not found.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Voice::getInterpreter(const std::string& interpreterID, const std::optional<std::string>& language) {
    return py::finish([&] { return Voice_getInterpreter(*client_, py::arg(interpreterID), py::arg(language)); });
}

json Voice::getInterpreter(const std::string& interpreterID, const GetInterpreterArgs& a) {
    return getInterpreter(interpreterID, a.language);
}

static py::V Voice_interpretTextBatch(OpenHABClient& C, py::V v_text, py::V v_IDs, py::V v_language) {
    (void)C;
    (void)v_text;
    (void)v_IDs;
    (void)v_language;
    py::V v_headers;
    py::V v_response;
    py::V v_status_code;
    v_headers = py::dict({{"Content-Type", py::s("text/plain")}, {"Accept", py::s("text/plain")}});
    if (py::truthy(v_language)) {
        py::set(v_headers, py::s("Accept-Language"), v_language);
    }
    try {
        v_response = py::http(C, "post", py::cat({py::s("/voice/interpreters/"), py::join(py::s(","), v_IDs)}), v_headers, v_text, py::V());
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::cat({py::s("Interpretation exception occurs: "), py::excStr(e_err)})}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("No human language interpreter was found.")}});
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
        return py::dict({{"error", py::s("No human language interpreter was found.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Interpretation exception occurs.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Voice::interpretTextBatch(const std::string& text, const json& IDs, const std::optional<std::string>& language) {
    return py::finish([&] { return Voice_interpretTextBatch(*client_, py::arg(text), py::arg(IDs), py::arg(language)); });
}

json Voice::interpretTextBatch(const std::string& text, const json& IDs, const InterpretTextBatchArgs& a) {
    return interpretTextBatch(text, IDs, a.language);
}

static py::V Voice_listenAndAnswer(OpenHABClient& C, py::V v_sourceID, py::V v_sttID, py::V v_ttsID, py::V v_voiceID, py::V v_hliIDs, py::V v_sinkID, py::V v_listeningItem, py::V v_language) {
    (void)C;
    (void)v_sourceID;
    (void)v_sttID;
    (void)v_ttsID;
    (void)v_voiceID;
    (void)v_hliIDs;
    (void)v_sinkID;
    (void)v_listeningItem;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::s("/voice/listenandanswer"), (py::truthy(v_language) ? py::V(py::dict({{"Accept-Language", v_language}})) : py::V(py::dict())), py::V(), py::dict({{"sourceId", v_sourceID}, {"sttId", v_sttID}, {"ttsId", v_ttsID}, {"voiceId", v_voiceID}, {"hliIds", (py::truthy(v_hliIDs) ? py::V(py::join(py::s(","), v_hliIDs)) : py::V(py::V()))}, {"sinkId", v_sinkID}, {"listeningItem", v_listeningItem}}));
        if (py::isstatus(v_response)) {
            v_status_code = py::get(v_response, py::s("status"));
        } else {
            return v_response;
        }
    } catch (const py::HTTPError& e_err) {
        (void)e_err;
        v_status_code = py::excStatus(e_err);
        if (py::eq(v_status_code, py::V(json(400)))) {
            return py::dict({{"error", py::s("Services are missing or language is not supported by services or dialog processing is already started for the audio source.")}});
        } else if (py::eq(v_status_code, py::V(json(404)))) {
            return py::dict({{"error", py::s("One of the given ids is wrong.")}});
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
        return py::dict({{"error", py::s("One of the given ids is wrong.")}});
    } else if (py::eq(v_status_code, py::V(json(400)))) {
        return py::dict({{"error", py::s("Services are missing or language is not supported by services or dialog processing is already started for the audio source.")}});
    }
    return py::dict({{"error", py::cat({py::s("Unexpected response: "), v_status_code})}});
}

json Voice::listenAndAnswer(const std::string& sourceID, const std::string& sttID, const std::string& ttsID, const std::string& voiceID, const json& hliIDs, const std::string& sinkID, const std::string& listeningItem, const std::optional<std::string>& language) {
    return py::finish([&] { return Voice_listenAndAnswer(*client_, py::arg(sourceID), py::arg(sttID), py::arg(ttsID), py::arg(voiceID), py::arg(hliIDs), py::arg(sinkID), py::arg(listeningItem), py::arg(language)); });
}

json Voice::listenAndAnswer(const std::string& sourceID, const std::string& sttID, const std::string& ttsID, const std::string& voiceID, const json& hliIDs, const std::string& sinkID, const std::string& listeningItem, const ListenAndAnswerArgs& a) {
    return listenAndAnswer(sourceID, sttID, ttsID, voiceID, hliIDs, sinkID, listeningItem, a.language);
}

static py::V Voice_sayText(OpenHABClient& C, py::V v_text, py::V v_voiceID, py::V v_sinkID, py::V v_volume) {
    (void)C;
    (void)v_text;
    (void)v_voiceID;
    (void)v_sinkID;
    (void)v_volume;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "post", py::s("/voice/say"), py::dict({{"Content-Type", py::s("text/plain")}}), v_text, py::dict({{"voiceid", v_voiceID}, {"sinkid", v_sinkID}, {"volume", v_volume}}));
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

json Voice::sayText(const std::string& text, const std::string& voiceID, const std::string& sinkID, const std::string& volume) {
    return py::finish([&] { return Voice_sayText(*client_, py::arg(text), py::arg(voiceID), py::arg(sinkID), py::arg(volume)); });
}

json Voice::sayText(const std::string& text, const std::string& voiceID, const std::string& sinkID, const SayTextArgs& a) {
    return sayText(text, voiceID, sinkID, a.volume);
}

static py::V Voice_getVoices(OpenHABClient& C, py::V v_language) {
    (void)C;
    (void)v_language;
    py::V v_response;
    py::V v_status_code;
    try {
        v_response = py::http(C, "get", py::s("/voice/voices"), py::dict({{"Accept", py::s("application/json")}, {"Accept-Language", v_language}}), py::V(), py::V());
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

json Voice::getVoices(const std::optional<std::string>& language) {
    return py::finish([&] { return Voice_getVoices(*client_, py::arg(language)); });
}

json Voice::getVoices(const GetVoicesArgs& a) {
    return getVoices(a.language);
}

}  // namespace openhab
