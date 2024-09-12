#pragma once

#include <Vendor/JsonCpp/include/json/json.h>

namespace NGameX
{
  namespace SocialBootstrap
  {
    struct LoginParams
    {
      bool queueLogin;

      const char* serverName;
      const char* serverSecret;

      const char* snid;
      const char* snuid;
      const char* sntoken;
      const char* sntoken2;

      const char* version;

      LoginParams();
    };

    class Session
    {
    public:
      explicit Session(const LoginParams& params, bool _loggedIn);
      ~Session();

      bool Login();
      bool Logout();

      const nstl::string& GetServerLoginToken() const { return !serverLoginToken.empty() ? serverLoginToken : sntoken; }
      const nstl::string& GetServerLocation() const { return serverLocation; }
      const nstl::string& GetServerSecret() const { return serverSecret; }
      const nstl::string& GetServerName() const { return serverName; }
      const nstl::string& GetServerKey() const { return serverKey; }
      const nstl::string& GetUID() const { return uid; }
      void SetUID(const nstl::string& _uid) { uid =_uid; }
      void SetServerKey(const nstl::string& _key) { serverKey=_key; }
    private:
      Session();
      Session(const Session&);
      Session& operator=(const Session&);

      bool QueueLogin();
      bool QueuePoll();

      void Update();

      bool HandleLoginResponse(const Json::Value& json);
      bool HandleQueueLoginResponse(const Json::Value& json, const bool isInPollLoop);
      bool HandleLogoutResponse(const Json::Value& json);

      bool CheckQueueLoginShortResponse(const Json::Value& json) const;

      const bool queueLogin;

      const nstl::string host;

      const nstl::string snid;
      const nstl::string snuid;
      const nstl::string sntoken;
      const nstl::string sntoken2;

      const nstl::string version;

      nstl::string serverKey;
      nstl::string serverName;
      nstl::string serverSecret;

      nstl::string serverLocation;
      nstl::string serverLoginToken;

      nstl::string uid;

      bool loggedIn;
    };

    class MatchMaking
    {
    public:
      explicit MatchMaking(const Session& ss);
      ~MatchMaking();

      bool Make(const bool tutorial = true);

      const nstl::string& GetMapId() const { return mapId; }
      const nstl::string& GetSessionId() const { return sessionId; }
    private:
      MatchMaking();
      MatchMaking(const MatchMaking&);
      MatchMaking& operator=(const MatchMaking&);

      bool HandleAddResponse(const Json::Value& json);
      bool HandlePingResponse(const Json::Value& json);

      const Session& ss;

      nstl::string mmid;
      nstl::string mapId;
      nstl::string sessionId;
    };

    struct LaunchData
    {
      nstl::string serverLoginToken;
      nstl::string serverLocation;
      nstl::string serverSecret;
      nstl::string serverName;
      nstl::string serverKey;

      nstl::string uid;

      nstl::string mapId;
      nstl::string sessionId;

      void Update(const Session& ss)
      {
        serverLoginToken = ss.GetServerLoginToken();
        serverLocation = ss.GetServerLocation();
        serverSecret = ss.GetServerSecret();
        serverName = ss.GetServerName();
        serverKey = ss.GetServerKey();

        uid = ss.GetUID();
      }

      void Update(const MatchMaking& smm)
      {
        mapId = smm.GetMapId();
        sessionId = smm.GetSessionId();
      }
    };
  }
}

