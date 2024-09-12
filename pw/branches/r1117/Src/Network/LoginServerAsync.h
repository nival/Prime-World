#pragma once
#include "LoginServerBase.h"

#include "RPC/RPC.h" 
#include "RPC/LocalEntityFactory.h" 
#include "RPC/GateKeeper.h"
#include "Coordinator/LoginServerNaming.h"
#include "RPC/IfaceRequester.h"
#include "UserManager/UserManagerSvc/RUserManagerIface.auto.h"
#include "SessionKeyRegisterIface.h"

namespace Login
{

struct SSessionContext: public BaseObjectMT
{// matchmaker выдает пары (sessionKey, sessionPath) для запуска клиентов, уже прошедших matchmaking
  NI_DECLARE_REFCOUNT_CLASS_1( SSessionContext, BaseObjectMT );

  SSessionContext( const char * path_, const char* zz_login_, int zz_uid_, Cluster::TGameId _gameid, bool useOnce_ )
    : sessionPath(path_), zz_login(zz_login_), zz_uid(zz_uid_), gameid_(_gameid), timestamp(NHPTimer::GetScalarTime()), useOnce(useOnce_) { }
   
  Transport::TServiceId sessionPath; // куда клиенту дальше ломиться со своим sessionKey (lobby? hybrid? имя, по которому наверное делаем RequestNode)
  nstl::string zz_login; 
  int zz_uid;
  Cluster::TGameId gameid_;
  Timestamp timestamp; // так, для контроля когда выдано (может, понадобится таймаут прилепить)
  bool useOnce;
};



// [sessionKey] -> sessionPath, для запуска клиентов, уже прошедших matchmaking
typedef nstl::map<nstl::string,StrongMT<SSessionContext> > TSessionContextMap; 




class LoginServerAsync : public LoginServerBase, public ISessionKeyRegister
{
  NI_DECLARE_REFCOUNT_CLASS_2( LoginServerAsync, LoginServerBase, ISessionKeyRegister );

public:
  RPC_ID();

  // async processor version (server):
  LoginServerAsync( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  ~LoginServerAsync();

  virtual void Poll( timer::Time _now );

  static bool onCmdAddSessionKey(const char *name, vector<wstring> const & params);

protected:
  //ISessionKeyRegister
  void AddSessionKey( nstl::string const & _sessionKey, Transport::TServiceId const & _sessionPath, nstl::string const & _login, Cluster::TUserId _userid, Cluster::TGameId _gameid, IAddSessionKeyCallback * _pcb );

  virtual bool ProcessNewContext( SLoginContext * context );

private:
  IAsyncLoginProcessor * asyncProcessor;

  threading::Mutex mutexContexts;
  TLoginContexts contexts; // набор заявок на логин (пока там вектор, для асинк. операций может быть удобнее map[clientId]); по этому списку итерируем контексты в Step()

  threading::Mutex mutexContextMap;
  TLoginContextMap contextMap; // вторичная мапа [userId]->context: контексты, которые уже прошли AddUser, добавляем сюда, для легкости нотификаций

  threading::Mutex mutexSessionMap;
  TSessionContextMap sessionMap; // [sessionKey] -> sessionPath, для запуска клиентов, уже прошедших matchmaking
  ESessionLoginMode sessionLogin; // проверять ли sessionKey, и насколько сурово

  int debug_stepCount;

  StrongMT<rpc::IfaceRequester<UserManager::RIUserManager> > userMngrIface_;

  static TSessionContextMap predefinedSessionMap; //  для данных поступающих от команды login_add_session_key
  
  static ESessionLoginMode ParseLoginMode( const Transport::TServiceOptions & _options );
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Login
