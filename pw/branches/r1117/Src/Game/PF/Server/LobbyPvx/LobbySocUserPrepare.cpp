#include "stdafx.h"
#include "LobbySocUserPrepare.h"
#include <System/Math/MD4.h>
#include "ServerAppBase/ServerCfg.h"
#include "ILoginSvcWrapper.h"
#include "System/SafeTextFormatStl.h"
#include "System/SafeTextFormatNStl.h"
#include "Network/ClusterConfiguration.h"
#include "LobbyLog.h"


namespace lobby
{

ESocUserPreparation::Enum SocUserPrepareItem::Poll( ISessionLoginWrapper * loginSvcAgent, timer::Time now )
{
  switch ( state )
  {
    case ESocUserPreparation::Initial:
      CreateSessionKey( loginSvcAgent );
      state = ESocUserPreparation::WaitingAnswer;
      loginAckTimeout = now + 15.0f;
      break;

    case ESocUserPreparation::WaitingAnswer:
      if ( now >= loginAckTimeout )
      {
        LOBBY_LOG_ERR( "Login ack timed out! pvxuid=%d", data.pvxUid );
        state = ESocUserPreparation::Failed;
      }
      break;

    default:
    case ESocUserPreparation::Done:
      break;
  }

  return state;
}



void SocUserPrepareItem::CreateSessionKey( ISessionLoginWrapper * loginSvcAgent )
{
  NI_PROFILE_HEAVY_FUNCTION;

  math::MD5Generator md5;
  md5.Start();
  md5.AddObject( startTicks );
  md5.AddObject( timer::GetTicks() );
  md5.AddObject( data.pvxUid );
  md5.Update( (const byte *)data.login.c_str(), data.login.size() );
  md5.Stop();

  NI_ASSERT( md5.Get().DIGEST_SIZE == 4, "" );
  tmpPassword = md5.Get().ToString();

  Transport::TServiceId fullsvcid;
  Transport::MakeFullServiceId( HostServer::Cfg::GetSvcPath().c_str(), serviceId, fullsvcid );
  loginSvcAgent->AddSessionKey( tmpPassword, fullsvcid, data.login, data.pvxUid, data.gameId, this );

  LOBBY_LOG_MSG( "Session key sent to login. pvxuid=%d, key=%s, login=%s, gameid=%s, svcid=%s", data.pvxUid, tmpPassword.c_str(), data.login, FmtGameId(data.gameId), fullsvcid.c_str() );
}



void SocUserPrepareItem::OnAddSessionKey( int _rc, const  nstl::string & _loginSvcAddr, Cluster::TUserId _userid )
{
  LOBBY_LOG_MSG( "Got session key ack: rc=%d, pvxuid=%d, loginAddr=%s", _rc, _userid, _loginSvcAddr );
  if ( state != ESocUserPreparation::WaitingAnswer ) {
    LOBBY_LOG_ERR( "Wrong session key prepare state! pvxuid=%d, state=%d", data.pvxUid, (int)state );
    return;
  }

  key.reserve( _loginSvcAddr.size() + data.login.size() + key.size() + 3 );

  const char separator = '/';
  key = _loginSvcAddr;
  key += separator;
  key += data.login;
  key += separator;
  key += tmpPassword;

  state = ESocUserPreparation::Done;
}

} //namespace lobby
