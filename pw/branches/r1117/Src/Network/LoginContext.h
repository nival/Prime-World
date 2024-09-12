#pragma once
#include "LoginTypes.h"
#include "RPC/RPC.h"
//#include "RPC/P2PNode.h" // ValQueryCB<>
#include <RPC/IfaceRequester.h>
#include "LoginData.h"
#include "System/HPTimer.h"
#include "UserManager/UserManagerSvc/RUserManagerIface.auto.h"

// имена лог-каналов (для всех логин-классов)
#define LOGIN_CHNL "Login" 

namespace Relay
{
  class RIBalancer;
}

namespace Login
{

typedef NHPTimer::FTime Timestamp;


struct SLoginContext : public UserManager::IPrepareUserEnvCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SLoginContext, UserManager::IPrepareUserEnvCallback, BaseObjectMT );

  enum TStage { // STAGE_XXX: состояния, _TIME_XXX: просто замеры времени для stageTimes
    #define EnUm( x ) x // для .h -- значение, для .cpp -- строчное представление
      EnUm( STAGE_RECONNECT_CHECK_START ),
      EnUm( STAGE_RECONNECT_CHECK_IN_PROGRESS ),
      EnUm( STAGE_RECONNECT_CHECK_FINISH ),
      EnUm( STAGE_NEW ),
      EnUm( _TIME_LOGIN_CHECK_START ),
      EnUm( STAGE_ASYNC_LOGIN_WAIT ),
      EnUm( _TIME_ASYNC_LOGIN_DONE ),
      EnUm( _TIME_REPARE_USER_ENVIRONMENT ),
      EnUm( STAGE_PREPARE_USER_ENVIRONMENT_STARTED ),
      EnUm( STAGE_PREPARE_USER_ENVIRONMENT_RETURN ),
      EnUm( STAGE_PREPARE_USER_ENVIRONMENT_IN_PROGRESS ),
      EnUm( STAGE_PREPARE_USER_ENVIRONMENT_COMPLETED ),
      EnUm( _TIME_FAIL ), // обломались (ошибка или таймаут)
      EnUm( _TIME_SUCCESS ), // закончили с логином; после ответа клиенту прибьем
      EnUm( _TIME_REPLY_SENT ),
      //--
      TOTAL_STAGE_COUNT
    #undef EnUm
  };
  static const char* StageNames[];

  TStage                stage;
  volatile bool         isLoginChecked; // для ZZima будет делаться асинхронно, через отдельную очередь заявок
  Timestamp             timeLastRequest; // для таймаутов

  StrongMT<Network::IConnection> connection;
  LoginRequestMessage   request;
  LoginResultMessage    response;
  LoginResultData       resultData;

  Transport::TServiceId relay;
  Network::NetAddress   relayAddr;
  Transport::TServiceId secondaryRelay;
  Network::NetAddress   secondaryRelayAddr;
  string reconnectSessionKey; // reconnect session key
  UserManager::Result::Enum rcUserEnvPrep;
  Cluster::TGameId gameid;

  Timestamp             stageTimes[ TOTAL_STAGE_COUNT ];

  SLoginContext(Network::IConnection* conn_=0); // будем слегка тестировать новые strong/weak, поэтому не inline
  ~SLoginContext(); // будем слегка тестировать новые strong/weak, поэтому не inline

  void SetStage(const TStage stage_);
  bool IsTimeout(const Timestamp now_);

  void DumpStageTimes(); 
  static void DumpCtorCounters(); // DEBUG

  int GetUserId() { return response.userId; }
  string const & sessionKey() const { return request.sessionKey; }

  //  UserManager::FindUserShadow return callback
  void onFindUserSession(UserManager::UserSessionInfo _usershadow);

  //  UserManager::PrepareUserEnv return callback
  void OnPrepareUserEnvReturn(UserManager::Result::Enum _result, Cluster::TUserId _userid, rpc::CallStatus _status);
  //  UserManager::IPrepareUserEnvCallback
  void OnPrepareUserEnv(int _result, Cluster::TUserId _userid, UserManager::RelayInfo const & _relayInfo, UserManager::PartialReconnectInfo const & _partialReconnectInfo);
};

typedef nstl::list<StrongMT<SLoginContext> > TLoginContexts;
typedef nstl::map<int,StrongMT<SLoginContext> > TLoginContextMap; // [userId] -> strong<SLoginContext>, для маппинга нотификаций



enum ESessionLoginMode
{
  SESSION_LOGIN_NONE = 0, // игнорируем sessionKey
  SESSION_LOGIN_CHECK, // проверяем sessionKey, подставляем sessionPath
  SESSION_LOGIN_ONLY // вообще запрещаем коннектиться без валидного sessionKey
};



struct IAsyncLoginProcessor 
{
  virtual void setUserManagerIface( rpc::IfaceRequester<UserManager::RIUserManager> * _userMngrIface ) {};

  // НЕ pure virtual: чтобы не заставлять вносить новые методы там где они пустые (без ZZima и т.п.)
  virtual bool PerformLoginCheck( string const &login, string const &password, Network::IConnection *connection, Login::LoginResultData * result ) { return true; }

  // async
  virtual bool MainStep() { return false; }
  virtual bool ClientStep( StrongMT<SLoginContext> & context ) { return false; }
  virtual unsigned GetAsyncOpCount() { return 0; } // кол-во асинхронных операций, выполненных за текущий степ

  // результат ждем в context->isLoginChecked (bool) и context->result (data)
  virtual void AsyncLoginRequest( string const &login, string const &password, const StrongMT<Login::SLoginContext> & result ) {} 

  // здесь финализируем очередь async-запросов (web/XML/soap..): выкидываем исполненные запросы и т.п.
  virtual void AsyncStep() {} 
};

} // namespace Login
