#ifndef SOCIALCONNECTION_H_B249AEE3_6DAF
#define SOCIALCONNECTION_H_B249AEE3_6DAF

#include "System/JobThread.h"
#include "ISocialConnection.h"

namespace NGameX
{

namespace Http
{
  struct HttpRequest;
}

namespace SocialBootstrap
{
  class Session;
}

class SocialConnection : public BaseObjectST, public ISocialConnection
{
  NI_DECLARE_REFCOUNT_CLASS_2( SocialConnection, BaseObjectST, ISocialConnection );

  int rid;

  const nstl::string serverName;
  const nstl::string uid;
  const nstl::string serverKey;
  const nstl::string serverSecret;
  
  int x, y, width, height;
  bool needCrop;

  nstl::vector<StrongMT<threading::JobThread>> sendRequestJobs;

  void GenerateRequest(Http::HttpRequest& request);
  void SendRequest(const Http::HttpRequest& request, const nstl::string& data = nstl::string());
  void parseAuids(const nstl::vector<__int64>& auids, std::string& res );

public:
  explicit SocialConnection(const SocialBootstrap::Session& ss);
  SocialConnection( const char* _serverName, const char* _uid, const char* _serverKey, const char* _serverSecret );
  ~SocialConnection();

  virtual bool AddFriend( __int64 auid );
  virtual bool CreateComplaint( __int64 toauid, int category, const nstl::wstring& text, const nstl::wstring& _logs, int kills, int deaths, int assists, 
                                       int points, int prime, int leave, int distance, int afks );
  virtual bool ChoosePartyAgain(const nstl::vector<__int64>& auids, const unsigned __int64 sessionId, const unsigned __int64 timeLeft, const bool agreed);
  virtual bool SendTeam(__int64 auid, const nstl::vector<__int64>& team_auids);
  virtual void Step();
  virtual void Share();
  virtual void Share( int _x, int _y, int _width, int _height );

  virtual void OnProtectionError();
};

class DummySocialConnection : public SocialConnection
{
  NI_DECLARE_REFCOUNT_CLASS_1( DummySocialConnection, SocialConnection );

public:
  DummySocialConnection() : SocialConnection("", "", "", "") {}

  virtual bool AddFriend( __int64 auid ) { return true; }
  virtual bool CreateComplaint( __int64 toauid, int category, const nstl::wstring& text, const nstl::wstring& _logs, int kills, int deaths, int assists, 
                                       int points, int prime, int leave, int distance, int afks ) { return true; }
  virtual bool ChoosePartyAgain(const nstl::vector<__int64>&, const unsigned __int64, const unsigned __int64, const bool) { return true; }
  virtual bool SendTeam(__int64 auid, const nstl::vector<__int64>& team_auids){return true;};

  virtual void OnProtectionError() {}
};

}

#endif //#define SOCIALCONNECTION_H_B249AEE3_6DAF
