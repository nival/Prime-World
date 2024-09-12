#include <stdafx.h>
#include "SocialBootstrap.h"
#include "HttpStuff.h"
#include "System/Math/MD4.h"

#include "System/MainFrame.h"
#include "AdventureScreen.h"

nstl::string s_socialLoginAddress;

REGISTER_VAR("social_login_address", s_socialLoginAddress, STORAGE_GLOBAL);

namespace NGameX
{
namespace SocialBootstrap
{

//////////////////////////////////////////////////////////////////////////

  static inline const char* SafeString(const char* s) { return (!!s ? s : ""); }
  static inline const wchar_t* SafeString(const wchar_t* s) { return (!!s ? s : L""); }

  nstl::string GenerateSecret(const nstl::string& token)
  {
    const byte* const bytes = reinterpret_cast<const byte*>(token.c_str());
    const uint size = static_cast<uint>(token.size());

    return math::GenerateMD5(bytes, size).ToString();
  }

//////////////////////////////////////////////////////////////////////////

  LoginParams::LoginParams()
    : queueLogin(false)
    , serverName(NULL)
    , serverSecret(NULL)
    , snid(NULL)
    , snuid(NULL)
    , sntoken(NULL)
    , sntoken2(NULL)
    , version(NULL)
  {

  }

//////////////////////////////////////////////////////////////////////////

  Session::Session(const LoginParams& params, bool _loggedIn=false )
    : queueLogin(params.queueLogin)
    , host(s_socialLoginAddress)
    , snid(SafeString(params.snid))
    , snuid(SafeString(params.snuid))
    , sntoken(SafeString(params.sntoken))
    , sntoken2(SafeString(params.sntoken2))
    , version(SafeString(params.version))
    , serverKey()
    , serverName(SafeString(params.serverName))
    , serverSecret(SafeString(params.serverSecret))
    , serverLocation()
    , serverLoginToken()
    , uid()
    , loggedIn(_loggedIn)
  {
    Update();

    curl_global_init(CURL_GLOBAL_ALL);
  }

  Session::~Session()
  {
    Logout();
  }

  bool Session::Login()
  {
    using namespace Http;

    NI_VERIFY(!loggedIn, "Already logged in!", return true);

    Update();

    if (queueLogin)
    {
      if (!QueueLogin())
      {
        return false;
      }
    }

    Update();

    {
      HttpRequest request(serverLocation);

      request.AddQueryParam("action", "sn_login");
      request.AddQueryParam("snid", snid);
      request.AddQueryParam("snuid", snuid);
      request.AddQueryParam("sntoken", GetServerLoginToken());
      request.AddQueryParam("ver", version);

      request.Build(serverSecret);

      const StrongMT<RequestSender> rs(SendRequest(request, true));

      if (rs->GetResponseStatus() != ResponseStatus::OK)
      {
        ErrorTrace("sn_login: Request failed!");
        return false;
      }

      if (!HandleLoginResponse(rs->GetResponseJson()))
      {
        ErrorTrace("sn_login: Failed to handle response!");
        return false;
      }
    }

    loggedIn = true;

    return true;
  }

  bool Session::Logout()
  {
    using namespace Http;

    if (!loggedIn)
      return true;

    const bool needLogout = (NMainFrame::GetExitCode() != EXIT_CODE_RETURN_TO_CASTLE);

    if (needLogout)
    {
      HttpRequest request(serverLocation);

      request.AddQueryParam("action", "logout");
      request.AddQueryParam("force", true);

      request.SetUID(uid);
      request.SetKey(serverKey);

      request.Build(serverSecret);

      const StrongMT<RequestSender> rs(SendRequest(request, true));

      if (rs->GetResponseStatus() != ResponseStatus::OK)
      {
        ErrorTrace("logout: Request failed!");
        return false;
      }

      if (!HandleLogoutResponse(rs->GetResponseJson()))
      {
        ErrorTrace("logout: Failed to handle response!");
        return false;
      }

      ::Sleep(1000);

      DevTrace("logout: done");
    }
    else
    {
      DevTrace("logout: intentionally skipped");
    }

    loggedIn = false;

    return true;
  }

  bool Session::QueueLogin()
  {
    using namespace Http;

    NI_VERIFY(queueLogin, "Invalid operation", return true);

    {
      HttpRequest request(serverLocation);

      request.AddQueryParam("action", "qlogin");
      request.AddQueryParam("snuid", snuid);
      request.AddQueryParam("sntoken", sntoken);
      request.AddQueryParam("ver", version);

      request.Build(serverSecret);

      const StrongMT<RequestSender> rs(SendRequest(request, true));

      if (rs->GetResponseStatus() != ResponseStatus::OK)
      {
        ErrorTrace("qlogin: Request failed!");
        return false;
      }

      if (CheckQueueLoginShortResponse(rs->GetResponseJson()))
      {
        return QueuePoll();
      }

      if (!HandleQueueLoginResponse(rs->GetResponseJson(), false))
      {
        ErrorTrace("qlogin: Failed to handle response!");
        return false;
      }
    }

    return true;
  }

  bool Session::QueuePoll()
  {
    using namespace Http;

    NI_VERIFY(queueLogin, "Invalid operation", return true);

    bool ok = false;

    for (int attempt = 0; !ok && attempt < 60; ++attempt)
    {
      ::Sleep(1000);

      HttpRequest request(serverLocation);

      request.AddQueryParam("action", "qpoll");
      request.AddQueryParam("snuid", snuid);
      request.AddQueryParam("sntoken", sntoken);
      request.AddQueryParam("ver", version);

      request.Build(serverSecret);

      const StrongMT<RequestSender> rs(SendRequest(request, true));

      if (rs->GetResponseStatus() != ResponseStatus::OK)
      {
        ErrorTrace("qpoll: Request failed!");
        return false;
      }

      if (!HandleQueueLoginResponse(rs->GetResponseJson(), true))
      {
        continue;
      }

      ok = true;
    }

    if (!ok)
    {
      ErrorTrace("qpoll: Queue login didn't finish in time!");
      return false;
    }

    return true;
  }

  void Session::Update()
  {
    using namespace Http;

    serverLocation = BuildLocation(host, serverName);
  }

  bool Session::HandleLoginResponse(const Json::Value& json)
  {
    const Json::Value& _uid = json["uid"];
    const Json::Value& _serverKey = json["key"];

    if (!_uid || !_serverKey)
    {
      ErrorTrace("sn_login: Malformed response (missing data)");
      return false;
    }

    uid = NStr::StrFmt("%llu", _uid.asUInt64());
    serverKey = _serverKey.asCString();

    return true;
  }

  bool Session::HandleQueueLoginResponse(const Json::Value& json, const bool isInPollLoop)
  {
    const Json::Value& gserver = json["gserver"];
    const Json::Value& token = json["token"];

    if (!gserver || !token)
    {
      if (isInPollLoop)
        DevTrace("qpoll: Still waiting...");
      else
        ErrorTrace("qlogin: Malformed response (missing data)");
      return false;
    }

    serverLoginToken = token.asCString();
    serverName = gserver.asCString();
    serverSecret = GenerateSecret(serverLoginToken);

    return true;
  }

  bool Session::HandleLogoutResponse(const Json::Value& json)
  {
    return true;
  }

  bool Session::CheckQueueLoginShortResponse(const Json::Value& json) const
  {
    const Json::Value& gserver = json["gserver"];
    const Json::Value& token = json["token"];

    return !gserver || !token;
  }

//////////////////////////////////////////////////////////////////////////

  MatchMaking::MatchMaking(const Session& ss)
    : ss(ss)
    , mmid()
    , mapId()
    , sessionId()
  {

  }

  MatchMaking::~MatchMaking()
  {

  }

  bool MatchMaking::Make(const bool tutorial /*= true*/)
  {
    NI_VERIFY(tutorial, "Unexpected parameter value", return false);

    using namespace Http;

    {
      ::Sleep(1000);

      HttpRequest request(ss.GetServerLocation());

      request.AddQueryParam("action", "mm_add");

      if (tutorial)
      {
        request.AddQueryParam("tutorial", 1);
      }
      else
      {
        // TODO: ?
      }

      request.SetUID(ss.GetUID());
      request.SetKey(ss.GetServerKey());

      request.Build(ss.GetServerSecret());

      const StrongMT<RequestSender> rs(SendRequest(request, true));

      if (rs->GetResponseStatus() != ResponseStatus::OK)
      {
        ErrorTrace("mm_add: Request failed!");
        return false;
      }

      if (!HandleAddResponse(rs->GetResponseJson()))
      {
        ErrorTrace("mm_add: Failed to handle response!");
        return false;
      }
    }

    for (int attempt = 0; attempt < 60; ++attempt)
    {
      ::Sleep(1000);

      HttpRequest request(ss.GetServerLocation());

      request.AddQueryParam("action", "mm_ping");
//      request.AddQueryParam("mmid", mmid);

      request.SetUID(ss.GetUID());
      request.SetKey(ss.GetServerKey());

      request.Build(ss.GetServerSecret());

      const StrongMT<RequestSender> rs(SendRequest(request, true));

      if (rs->GetResponseStatus() != ResponseStatus::OK)
      {
        ErrorTrace("mm_ping: Request failed!");
        return false;
      }

      if (!HandlePingResponse(rs->GetResponseJson()))
      {
        ErrorTrace("mm_ping: Failed to handle response!");
        return false;
      }

      if (!sessionId.empty())
        break;
    }

    if (sessionId.empty())
    {
      ErrorTrace("mm_ping: MM didn't finish in time");
      return false;
    }

    return true;
  }

  bool MatchMaking::HandleAddResponse(const Json::Value& json)
  {
    const Json::Value& _mmid = json["mmid"];

    if (!_mmid)
    {
      ErrorTrace("mm_add: Malformed response (missing mmid)");
      return false;
    }

    mmid = _mmid.asCString();

    return true;
  }

  bool MatchMaking::HandlePingResponse(const Json::Value& json)
  {
    const Json::Value& mm = json["mm"];

    if (!mm)
    {
      ErrorTrace("mm_ping: Malformed response (missing mm)");
      return false;
    }

    const Json::Value& _mmid = mm["mmid"];

    if (!_mmid)
    {
      ErrorTrace("mm_ping: Malformed response (missing mm.mmid)");
      return false;
    }

    NI_VERIFY(nstl::string(_mmid.asCString()) == mmid, "Mismatched MM ID!", return false);

    const Json::Value& _mapId = mm["game_type"];
    const Json::Value& _sessionId = mm["session_id"];

    if (!_sessionId)
    {
      return true;
    }

    if (!_mapId)
    {
      ErrorTrace("mm_ping: Malformed response (missing mm.game_type)");
      return false;
    }

    mapId = _mapId.asCString();
    sessionId = _sessionId.asCString();

    return true;
  }

} // namespace TutorialBootstrap
} // namespace NGameX

