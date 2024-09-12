#include "stdafx.h"
#include "GatewayPingContext.h"
#include "Server/LobbySocial/RISocialLobby.auto.h"
#include "Server/LobbySocial/RISocialLobbyNotify.auto.h"
#include "System/SafeTextFormatStl.h"
#include "System/InlineProfiler.h"

#include "HttpGatewayLog.inl"


namespace HttpGateway
{

static float s_contextTimeout = 60.0f;
REGISTER_VAR( "http_gateway_ctx_timeout", s_contextTimeout, STORAGE_NONE );

static float s_contextUpdTimeout = 7200.0f;
REGISTER_VAR( "http_gateway_ctx_upd_timeout", s_contextUpdTimeout, STORAGE_NONE );



socialLobby::TUId PingContext::StrToUid( const char * str )
{
  return _atoi64( str );
}



PingContext::PingContext( timer::Time _now, socialLobby::TUId _uid, const char * _sessionId, EContextState::Enum _ctxState, socialLobby::ERequestStatus::Enum _initialStatus ) :
uid( _uid ), uidString( NI_STRFMT( "%lld", _uid ) ),
ctxState( _ctxState ),
creationTime( _now ),
now( _now ),
lastPingTime( _now ),
lastUpdateTime( _now )
{
  data.progress = _initialStatus;
  data.sessionContextId = _sessionId;
}



bool PingContext::ResetRestored( timer::Time _now, const char * _sessionId, EContextState::Enum _ctxState, socialLobby::ERequestStatus::Enum _status )
{
  NI_PROFILE_FUNCTION;

  threading::SpinLockGuard guarg( mutex );

  if ( ( ctxState == EContextState::Condemned ) || ( ctxState == EContextState::Restored ) ) {
    _ChangeState( _ctxState );
    data.progress = _status;
    data.sessionContextId = _sessionId;
    lastPingTime = _now;
    lastUpdateTime = _now;
    creationTime = _now;
    return true;
  }

  return false;
}



EContextState::Enum PingContext::CtxState() const
{
  threading::SpinLockGuard guarg( mutex );
  return ctxState;
}



void PingContext::Condemn()
{
  threading::SpinLockGuard guarg( mutex );
  _Condemn();
}



void PingContext::_Condemn()
{
  _ChangeState( EContextState::Condemned );
  data.progress = socialLobby::ERequestStatus::Null;
  lobbyCtx = 0;
}



std::string PingContext::SessionId()
{
  threading::SpinLockGuard guarg( mutex );

  return data.sessionContextId.c_str();
}



void PingContext::_ChangeState( EContextState::Enum _st )
{
  ctxState = _st;
}



void PingContext::RenewLastAcessTime( timer::Time _now )
{
  threading::SpinLockGuard guarg( mutex );
  lastPingTime = _now;
}



bool PingContext::Poll( timer::Time _now )
{
  threading::SpinLockGuard guarg( mutex );

  now = _now;

  if ( ctxState == EContextState::New || ( ctxState == EContextState::Restored ) )
    if ( now > creationTime + s_contextTimeout ) {
      SVC_LOG_WRN.Trace( "New context timed out: uid=%d", Uid() );
      return false;
    }

  if ( now > lastPingTime + s_contextTimeout )
  {
    const bool active = ( ctxState == EContextState::ApprovedByLobby );

    if ( active )
      SVC_LOG_ERR.Trace( "Active context timed out: uid=%d", Uid() );
    else
      SVC_LOG_WRN.Trace( "Context timed out: uid=%d", Uid() );

    if ( active )
      if ( lobbyCtx ) {
        lobbyCtx->EmergencyCancel();
        lobbyCtx = 0;
      }
    return false;
  }

  if ( now > lastUpdateTime + s_contextUpdTimeout )
  {
    SVC_LOG_ERR.Trace( "Context timed out (no updates): uid=%d", Uid() );

    if ( ctxState == EContextState::ApprovedByLobby )
      if ( lobbyCtx ) {
        lobbyCtx->EmergencyCancel();
        lobbyCtx = 0;
      }
    return false;
  }

  if ( lobbyCtx )
    switch ( lobbyCtx->GetStatus() ) {
      case rpc::Connected:
      case rpc::PartiallyConnected:
      case rpc::Connecting:
        break;
      default:
        SVC_LOG_WRN.Trace( "Context lost connection to lobby: uid=%d", Uid() );
        lobbyCtx = 0;
        return false;
    }

  return true;
}



void PingContext::Open( socialLobby::IUserContext * _ctx )
{
  NI_PROFILE_FUNCTION;

  SVC_LOG_MSG.Trace( "PingContext open uid=%s", uidString.c_str() );

  threading::SpinLockGuard guarg( mutex );

  lobbyCtx = _ctx;

  if ( ( ctxState != EContextState::New ) && ( ctxState != EContextState::Restored ) && ( ctxState != EContextState::Condemned ) )
    SVC_LOG_MSG.Trace( "Wrong http gateway context state=%d, uid=%s", (int)ctxState, uidString.c_str() );

  timer::Time now = timer::Now();
  timer::Time reactTime = now - lastPingTime;
  SVC_LOG_MSG.Trace( "PingContext open uid=%s, reaction time %.2f", uidString.c_str(), reactTime );
  lastPingTime = now;

  _ChangeState( EContextState::ApprovedByLobby );
  data.progress = socialLobby::ERequestStatus::JustAddedToLobby;
}



void PingContext::Failure()
{
  NI_PROFILE_FUNCTION;

  SVC_LOG_MSG.Trace( "PingContext failure uid=%s", uidString.c_str() );

  threading::SpinLockGuard guarg( mutex );

  NI_ASSERT( ctxState == EContextState::New || ctxState == EContextState::Restored, NI_STRFMT( "Wrong http gateway context state=%d, uid=%s", (int)ctxState, uidString.c_str() ) );

  lastPingTime = timer::Now();

  SVC_LOG_WRN.Trace( "Social Lobby rejected request uid=%s", uidString.c_str() );
  _Condemn();
}



void PingContext::UpdateStatus( const socialLobby::SMatchmakingStatus & _status )
{
  NI_PROFILE_FUNCTION;

  SVC_LOG_DBG.Trace( "UpdateStatus uid=%s, progress=%d, requestsAccepted=%d/%d, winner=%d, mmid=%s", uidString, (int)_status.progress,
                                                              _status.requestsAccepted, _status.totalPlayers, (int)_status.gameResults.winner,
                                                              _status.sessionContextId );

  threading::SpinLockGuard guarg( mutex );

  if ( !data.sessionContextId.empty() )
    if ( data.sessionContextId != _status.sessionContextId )
      SVC_LOG_WRN.Trace( "Got wrong mmid for context: uid=%s ('%s' vs '%s')", uidString, data.sessionContextId, _status.sessionContextId );

  //NOTE: Ответ от lobby может прийти ПОСЛЕ УДАЛЕНИЯ запроса по cancel

  if ( ctxState == EContextState::Condemned )
    if ( _status.progress != socialLobby::ERequestStatus::Null ) {
      SVC_LOG_WRN.Trace( "Got non-null status for condemned context: uid=%s, mmid=%s", uidString, data.sessionContextId );
      return;
    }

  //DO NOT update 'lastPingTime' here

  if ( ( ctxState == EContextState::Restored ) || ( ctxState == EContextState::New ) )
    SVC_LOG_WRN.Trace( "Got ping for new/restored context (Requests sequence failed?). uid=%s, progress=%d(%s)", uidString.c_str(), (int)_status.progress, socialLobby::ERequestStatus::ToString( _status.progress ) );

  if ( _status.progress == socialLobby::ERequestStatus::Null ) {
    SVC_LOG_ERR.Trace( "Got Null ping for context: uid=%s, mmid=%s", uidString, data.sessionContextId );
    _Condemn();
  }

  data = _status;

  lastUpdateTime = now;
}



void PingContext::Close()
{
  NI_PROFILE_FUNCTION;

  SVC_LOG_MSG.Trace( "PingContext close uid=%s", uidString.c_str() );

  threading::SpinLockGuard guarg( mutex );

  lastPingTime = timer::Now();

  //FIXME: Actually, this context already should be cancelled..

  _Condemn();
}



inline void FillGameResults( Json::Value & value, const socialLobby::SMatchmakingStatus & data )
{
  if ( data.progress != socialLobby::ERequestStatus::GameFinished )
    return;
  
  value["victoriousFaction"] = (int)(data.gameResults.winner);
  value["playerWin"] = (int)(data.gameResults.playerWin);
  value["playerIsLeaver"] = (int)(data.gameResults.playerIsLeaver);
}



inline void FillPreGameLobbyJson( Json::Value & value, const socialLobby::SMatchmakingStatus & data )
{
  value["guards_game"] = data.preGameLobbyInfo.preGameLobby ? 1 : 0;

  if ( data.progress == socialLobby::ERequestStatus::PreGameLobby )
  {
    Json::Value allies( Json::arrayValue );
    for ( int i = 0; i < data.preGameLobbyInfo.allies.size(); ++i ) {
      Json::Value a;
      a["uid"] = NI_STRFMT( "%lld", data.preGameLobbyInfo.allies[i].uid );
      a["rdy"] = data.preGameLobbyInfo.allies[i].ready ? 1 : 0;
      allies.append( a );
    }
    value["allies"] = allies;
    value["foes_rdy"] = (int)data.preGameLobbyInfo.foesReady;
  }
}



void PingContext::HandlePingRequest( Json::Value & pvxReply )
{
  NI_PROFILE_FUNCTION;

  threading::SpinLockGuard guard( mutex );

  switch ( ctxState )
  {
    case EContextState::Condemned:
      SVC_LOG_MSG.Trace( "ping: Context condemned, uid=%s", uidString );
      break;

    case EContextState::Restored:
      SVC_LOG_MSG.Trace( "ping: Context restoration still in progress, uid=%s", uidString );
      return;

    case EContextState::New:
      SVC_LOG_MSG.Trace( "ping: New context is not opened yet, uid=%s", uidString );
      break;

    default:
    case EContextState::ApprovedByLobby:
      // processed silently
      break;
  }

  if ( ctxState != EContextState::Condemned )
    lastPingTime = timer::Now();

  // -> reply: should be [0, 0, 0, 0, 0] or [<progress>, <session_id_string>, <players_accepted>, <players_total>, <debug_string>]
  Json::Value progress_list( Json::arrayValue );

  progress_list.append( (int)data.progress ); 

  if( !data.pvxSessionKey.empty() )
    progress_list.append( data.pvxSessionKey.c_str() );
  else
    progress_list.append( 0 );

  progress_list.append( data.requestsAccepted ); 
  progress_list.append( data.totalPlayers ); 
  
  if( !data.debugInfo.empty() )
    progress_list.append( data.debugInfo.c_str() );
  else
    progress_list.append( 0 );

  Json::Value gameResults;
  FillGameResults( gameResults, data );
  progress_list.append( gameResults );

  progress_list.append( NI_STRFMT( "%lld", (__int64)data.gameId ) ); 

  progress_list.append( data.sessionContextId.c_str() );

  Json::Value preGameLobbyJson;
  FillPreGameLobbyJson( preGameLobbyJson, data );
  progress_list.append( preGameLobbyJson );

  pvxReply["ping"][uidString] = progress_list;

  SVC_LOG_MSG.Trace( "Ping answer: uid=%s, progress=%d, mmid=%s, gameId=%016llx, pvxKey=%s, winner=%s, isLeaver=%i, playerWin=%i",
    uidString.c_str(), (int)data.progress, data.sessionContextId.c_str(), data.gameId, data.pvxSessionKey.c_str(),
    lobby::ETeam::ToString( data.gameResults.winner ), data.gameResults.playerIsLeaver, data.gameResults.playerWin );
}



void PingContext::HandleLeaveRequest()
{
  if ( lobbyCtx )
    if ( ctxState == EContextState::ApprovedByLobby ) {
      lobbyCtx->LeaveGame();
      return;
    }
  SVC_LOG_WRN.Trace( "leave: Context is not in lobby yet! uid=%d", uid );
}



void PingContext::HandleReconnectRequest()
{
  if ( lobbyCtx )
    if ( ctxState == EContextState::ApprovedByLobby ) {
      lobbyCtx->ReconnectToGame();
      return;
    }
  SVC_LOG_WRN.Trace( "reconnect: Context is not in lobby yet! uid=%d", uid );
}



bool PingContext::HandleAcceptRequest( const socialLobby::SPlayerData & playerData )
{
  if ( lobbyCtx )
    if ( ctxState == EContextState::ApprovedByLobby ) {
      lobbyCtx->AcceptGameSession( playerData );
      return true;
    }
  SVC_LOG_WRN.Trace( "accept: Context is not in lobby yet! uid=%d", uid );
  return false;
}



bool PingContext::HandleHeroChangeRequest( const socialLobby::SPlayerData & playerData )
{
  if ( lobbyCtx )
    if ( ctxState == EContextState::ApprovedByLobby ) {
      lobbyCtx->ChangeGuardHero( playerData );
      return true;
    }
  SVC_LOG_WRN.Trace( "herochange: Context is not in lobby yet! uid=%d", uid );
  return false;
}



bool PingContext::HandleGuardReadyRequest()
{
  if ( lobbyCtx )
    if ( ctxState == EContextState::ApprovedByLobby ) {
      lobbyCtx->GuardReady();
      return true;
    }
  SVC_LOG_WRN.Trace( "ready: Context is not in lobby yet! uid=%d", uid );
  return false;
}



void PingContext::HandleCancelRequest( bool partyCancel )
{
  threading::SpinLockGuard guard( mutex );

  if ( ( ctxState == EContextState::New ) || ( ctxState == EContextState::ApprovedByLobby ) )
  {
    if ( lobbyCtx ) {
      if ( partyCancel )
        lobbyCtx->CancelPartyRequest();
      else
        lobbyCtx->CancelRequest();
    }
  }
  else
    SVC_LOG_WRN.Trace( "cancel: Context is not in lobby yet! uid=%d", uid );

  _Condemn();
}

} // namespace HttpGateway
