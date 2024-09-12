#include "stdafx.h"
#include "LoginContext.h"
#ifdef NV_WIN_PLATFORM
#include <comutil.h>
#endif
#include "LoginCompatibleClientVersion.h"

NI_DEFINE_REFCOUNT(Login::SLoginContext);

namespace Login
{

unsigned int g_LoginRequestTimeoutSeconds = 60; // столько секунд login context может находиться в одной стадии (напр. ждать ответа на RPC-запрос)
REGISTER_VAR( "login_stage_timeout_seconds", g_LoginRequestTimeoutSeconds, STORAGE_NONE );

// UGLY: quick & dirty механизм подсчета вызовов
volatile LONG g_loginContextCtorCount = 0;
volatile LONG g_loginContextDtorCount = 0;


const char* SLoginContext::StageNames[] = {
  #define EnUm( x ) #x // для .h -- значение, для .cpp -- строчное представление
      EnUm( STAGE_NEW ),
      EnUm( _TIME_LOGIN_CHECK_START ),
      EnUm( STAGE_ASYNC_LOGIN_WAIT ),
      EnUm( _TIME_ASYNC_LOGIN_DONE ),
      EnUm( _TIME_ADD_USER_START ),
      EnUm( STAGE_ADD_USER_WAIT ),
      EnUm( _TIME_ALLOCATE_RELAY_USER_START ),
      EnUm( STAGE_ALLOCATE_RELAY_USER_WAIT ),
      EnUm( _TIME_ALLOCATE_RELAY_USER_READY ),
      EnUm( STAGE_RELAY_CLIENT_ALLOCATION_WAIT ),
      EnUm( _RELAY_CLIENT_ALLOCATION_CONFIRMED ),
      EnUm( _TIME_REMOVE_USER_START ),
      EnUm( STAGE_REMOVE_USER_WAIT ),
      EnUm( _TIME_FAIL ), // обломались (ошибка или таймаут)
      EnUm( _TIME_SUCCESS ), // закончили с логином; после ответа клиенту прибьем
      EnUm( _TIME_REPLY_SENT ),
  //--
  #undef EnUm
};



SLoginContext::SLoginContext( Network::IConnection* conn_ )
  : connection( conn_ )
  , stage( STAGE_NEW )
  , isLoginChecked( false )
  , rcUserEnvPrep(UserManager::Result::FAIL)
  , gameid(Cluster::INVALID_GAME_ID)
{// будем слегка тестировать новые strong/weak
  nival::interlocked_increment( g_loginContextCtorCount );
#if defined( NV_WIN_PLATFORM )
  ZeroMemory( stageTimes, sizeof(stageTimes) );
#elif defined( NV_LINUX_PLATFORM )
  memset( stageTimes, 0, sizeof(stageTimes) );
#endif
}



SLoginContext::~SLoginContext()
{// будем слегка тестировать новые strong/weak
  nival::interlocked_increment( g_loginContextDtorCount );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SLoginContext::DumpCtorCounters()
{
  LOG_D(LOGIN_CHNL) << "SLoginContext (ctors=" << g_loginContextCtorCount << " dtors=" << g_loginContextDtorCount << ")";
}



void SLoginContext::SetStage(const TStage stage_) 
{ 
  stage = stage_; 
  timeLastRequest = NHPTimer::GetScalarTime(); 
  stageTimes[stage] = timeLastRequest;
}



bool SLoginContext::IsTimeout(const Timestamp now_) 
{ 
  return (g_LoginRequestTimeoutSeconds ? timeLastRequest + g_LoginRequestTimeoutSeconds < now_ : false); 
}



void SLoginContext::DumpStageTimes()
{
  char buf[1024];
  char* dest = buf;
  Timestamp lastValid = 0;
  for ( int stage=0; stage<TOTAL_STAGE_COUNT; stage++ )
  {
    if ( stageTimes[stage] )
    {
      Timestamp delta = lastValid ? stageTimes[stage]-lastValid : 0;
      lastValid = stageTimes[stage];
#if defined( NV_WIN_PLATFORM )
      int numWritten = sprintf_s( dest, 1024+buf-dest, "\n %s : %.3f (%.5f)", StageNames[stage], lastValid, delta );
#elif defined( NV_LINUX_PLATFORM )
      int numWritten = snprintf( dest, 1024+buf-dest, "\n %s : %.3f (%.5f)", StageNames[stage], lastValid, delta );
#endif
      if ( numWritten >= 0 )
        dest += numWritten;
    }
  }

  LOG_D(LOGIN_CHNL) << "Stage times: login=" << request.login << ", id=" << response.userId 
    << ", total login time=" << (lastValid - stageTimes[STAGE_NEW]) << buf;
}



void SLoginContext::onFindUserSession(UserManager::UserSessionInfo _usershadow)
{
  response.userId = _usershadow.userid_;
  response.sessionPath = _usershadow.sessionPath_;
  SetStage(SLoginContext::STAGE_RECONNECT_CHECK_FINISH);
}



void SLoginContext::OnPrepareUserEnvReturn(UserManager::Result::Enum _result, Cluster::TUserId _userid, rpc::CallStatus _status)
{
  LOG_M(LOGIN_CHNL).Trace("%s(rc=%d u=%d rpcsts=%d)", __FUNCTION__, (int)_result, _userid, (int)_status);

  if (_status != rpc::CallSuccessful)
  {
    LOG_E(LOGIN_CHNL).Trace("%s: rpc call timeout/disconnect(rpcsts=%d userid=%d)", 
      __FUNCTION__, (int)_status, _userid);

    SetStage(STAGE_PREPARE_USER_ENVIRONMENT_COMPLETED);
    rcUserEnvPrep = UserManager::Result::FAIL;
    return;
  }

  rcUserEnvPrep = _result;
  SetStage(STAGE_PREPARE_USER_ENVIRONMENT_RETURN);
}



void SLoginContext::OnPrepareUserEnv(int _result, Cluster::TUserId _userid, UserManager::RelayInfo const & _relayInfo, UserManager::PartialReconnectInfo const & _partialReconnectInfo)
{
  LOG_M(LOGIN_CHNL).Trace("%s(rc=%d u=%d relay=%s relayaddr=%s secondaryrelay=%s secondaryaddr=%s partialReconnectSupport=%d partialReconnectRetries=%d partialReconnectTimeout=%d)",
    __FUNCTION__, (int)_result, _userid, _relayInfo.primary_.c_str(), _relayInfo.primaryAddr_.c_str(), _relayInfo.secondary_.c_str(), _relayInfo.secondaryAddr_.c_str(), 
    _partialReconnectInfo.supported_, _partialReconnectInfo.retries_, _partialReconnectInfo.retryTimeout_);

  rcUserEnvPrep = (UserManager::Result::Enum)_result;

  if (UserManager::Result::SUCCESS == _result)
  {
    relay = _relayInfo.primary_;
    relayAddr = _relayInfo.primaryAddr_;
    secondaryRelay = _relayInfo.secondary_;
    secondaryRelayAddr = _relayInfo.secondaryAddr_;

    response.partialReconnectSupport = _partialReconnectInfo.supported_;
    response.partialReconnectRetries = _partialReconnectInfo.retries_;
    response.partialReconnectRetryTimeout = _partialReconnectInfo.retryTimeout_;
  }

  SetStage(STAGE_PREPARE_USER_ENVIRONMENT_COMPLETED);
}

} // namespace Login
