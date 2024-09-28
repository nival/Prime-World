#include "stdafx.h"
#include "SocialLobbyUserContext.h"
#include "ISocialLobbyUserCtx.h"
#include "ISocialLobbyNotify.h"
#include "ISocialLobbyPvxSvc.h"
#include "SocialLobbyGame.h"
#include "SocialLobbyParty.h"
#include "SocialLobbyConfig.h"
#include "SocialLobbyCtrl.h"
#include "SocialLobbyLog.h"
#include "Server/Statistic/StatisticsServerTypes.h"
#include "System/Crc32Checksum.h"
#include "System/InlineProfiler.h"


namespace socialLobby
{


//Dummy proxy class to keep UserContext inhereted from single threaded BaseObjectST
//And to resove possible circular reference between local UserContext and remote PingContext(HttpGateway)
class UserContext::RpcWrapper : public IUserContext, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RpcWrapper, IUserContext, BaseObjectMT );
public:
  RpcWrapper( UserContext * _ctx ) : ctx( _ctx ) {}

  virtual void AcceptGameSession( const SPlayerData& _playerData ) { if ( ctx ) ctx->AcceptGameSession( _playerData ); }
  virtual void ChangeGuardHero( const SPlayerData& _playerData ) { if ( ctx ) ctx->ChangeGuardHero( _playerData ); }
  virtual void GuardReady() { if ( ctx ) ctx->GuardReady(); }
  virtual void ReconnectToGame() { if ( ctx ) ctx->ReconnectToGame(); }
  virtual void LeaveGame() { if ( ctx ) ctx->LeaveGame(); }
  virtual void CancelRequest() { if ( ctx ) ctx->CancelRequest( ECancelMode::Normal ); }
  virtual void CancelPartyRequest() { if ( ctx ) ctx->CancelRequest( ECancelMode::Party ); }
  virtual void EmergencyCancel() { if ( ctx ) ctx->CancelRequest( ECancelMode::Emergency ); }

private:
  Weak<UserContext> ctx;
};


#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

UserContext::UserContext( Config * _cfg, const SMatchmakingRequest & _data, timer::Time _now, IControl * _control, INotify * _notify ) :
config( _cfg ),
data( _data ),
creationTime( _now ),
control( _control ), notify( _notify ),
rpcWrapper( new RpcWrapper( this ) ),
status( ERequestStatus::Null ),
now( _now ),
preGameLobbyReadiness( false ),
preGameLobbyReadyTime( 0 ),
pvxDropTime( 0 ),
currentStatusExpires( 0 ),
connectionLostExpires( -1.0 ),
modified( false )
{
  dbgFormattedId = NI_STRFMT( "u%lld", data.uid );

  currentStatusExpires = creationTime + 60.0f * config->backupTimeoutShort;

  data.clientRevision = _control->MapClientRevision( data.clientRevision );
}



void UserContext::AcceptGameSession( const SPlayerData & _playerData )
{
  NI_PROFILE_FUNCTION;

  if ( !game ) {
    SOCLOBBY_LOG_MSG( "User %s (state %d) has no game to accept (too late?)", FmtId(), (int)status );
    return;
  }

  if ( !( StatusIs() | ERequestStatus::WaitingAccept | ERequestStatus::Accepted ) ) {
    SOCLOBBY_LOG_ERR( "User context is in wrong for accept (user=%s, state=%d)", FmtId(), (int)status );
    return;
  }

  if ( game->State() != EGameState::Accepting ) {
    SOCLOBBY_LOG_ERR( "Accepting game in wrong state! user=%s, state=%d", FmtId(), (int)game->State() );
    return;
  }

  playerDetails = _playerData.data;

  game->AcceptGame( this );
}



void UserContext::ChangeGuardHero( const SPlayerData & _playerData )
{
  NI_PROFILE_FUNCTION;

  SOCLOBBY_LOG_MSG( "New Player Details. user=%s, hero=%d, prev_hero=%d", FmtId(), _playerData.data.heroId, playerDetails.heroId );

  if ( status != ERequestStatus::PreGameLobby ) {
    SOCLOBBY_LOG_MSG( "User context is in wrong state to change player details (user=%s, state=%d)", FmtId(), (int)status );
    return;
  }

  playerDetails = _playerData.data;
}



void UserContext::GuardReady()
{
  NI_PROFILE_FUNCTION;

  if ( status != ERequestStatus::PreGameLobby ) {
    SOCLOBBY_LOG_MSG( "User context is in wrong state to update guard readiness (user=%s, state=%d)", FmtId(), (int)status );
    return;
  }

  if ( !game ) {
    SOCLOBBY_LOG_ERR( "User has no game to set ready (user=%s, state=%d)", FmtId(), (int)status );
    return;
  }

  game->GuardReady( this );
}



void UserContext::ReconnectToGame()
{
  NI_PROFILE_FUNCTION;

  SOCLOBBY_LOG_MSG( "User %s tries to reconnect...", FmtId() );

  StrongMT<IControl> lockedControl = control.Lock();
  NI_VERIFY( lockedControl, "", return )

  if ( status != ERequestStatus::ClientDropped ) {
    SOCLOBBY_LOG_ERR( "Wrong request %s reconnect state %d", FmtId(), (int)status );
    return;
  }

  if ( !game ) {
    SOCLOBBY_LOG_ERR( "No game to reconnect to (%s)", FmtId() );
    return;
  }

  bool found = false;
  for ( int pi = 0; !found && pi < game->PartiesCount(); ++pi )
    if ( Party * party = game->GetParty( pi ) )
      for ( int mi = 0; !found && mi < party->Size(); ++mi )
        if ( UserContext * tmpCtx = party->Member( mi ) )
          if ( tmpCtx == this )
            found = true;
  if ( !found )
    SOCLOBBY_LOG_ERR( "Game %s do not contain user %s", game->StrId(), FmtId() );

  Strong<IPvxSvcWrapper> pvx = game->PvxService();
  if ( !pvx ) {
    SOCLOBBY_LOG_ERR( "PVX service is not available! User %s cannot reconnect to game %s", FmtId(), game->StrId() );
    return;
  }

  ChangeStatus( ERequestStatus::PreparingPvX );

  pvx->Remote()->NewReconnectingUser( game->Id(), data.userIdPvx, lockedControl->GetPvxAcknowledge() );

  SOCLOBBY_LOG_MSG( "Reconnecting user %s pushed to lobby, game %s", FmtId(), game->StrId() );
}



void UserContext::LeaveGame()
{
  NI_PROFILE_FUNCTION;

  SOCLOBBY_LOG_MSG( "User %s wishes to abandon the game", FmtId() );

  StrongMT<IControl> lockedControl = control.Lock();
  NI_VERIFY( lockedControl, "", return );

  if ( status != ERequestStatus::ClientDropped ) {
    SOCLOBBY_LOG_ERR( "Wrong leaver request %s state %d", FmtId(), (int)status );
    return;
  }

  AbandonGame( now );
}



void UserContext::CancelRequest( ECancelMode::Enum mode )
{
  NI_PROFILE_FUNCTION;

  if ( mode == ECancelMode::Emergency )
    SOCLOBBY_LOG_WRN( "Cancelling request (in emergency mode), id=%s...", FmtId() );
  else
    SOCLOBBY_LOG_MSG( "Cancelling%s request, id=%s...", ( mode == ECancelMode::Party ) ? " party" : "", FmtId() );

  StrongMT<IControl> lockedControl = control.Lock();
  NI_VERIFY( lockedControl, "", return );

  if ( mode == ECancelMode::Party )
    party->RemoveAllRequests( true, this );

  lockedControl->RemoveUserContext( this, true );
}



void UserContext::OverrideNotify( INotify * _notify )
{
  if ( notify->GetStatus() != rpc::Disconnected )
    SOCLOBBY_LOG_WRN( "Overriding active notify (status %d) for context %s", (int)notify->GetStatus(), FmtId() );

  notify = _notify;
  Modify();
}



void UserContext::SetPreGameLobbyReadiness( bool ready )
{
  preGameLobbyReadiness = ready;

  if ( preGameLobbyReadiness )
    preGameLobbyReadyTime = now;
  else
    preGameLobbyReadyTime = 0;
}



void UserContext::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  now = _now;

  if ( now > currentStatusExpires )
  {
    SOCLOBBY_LOG_ERR( "UserContext %s timed out, status=%d", FmtId(), (int)status );

    if ( StrongMT<IControl> lockedControl = control.Lock() )
      lockedControl->RemoveUserContext( this, true );
    return;
  }

  if ( status == ERequestStatus::ClientDropped )
  {
    if ( now > pvxDropTime + config->reconnectTimeout )
      AbandonGame( now );
  }

  if ( notify->GetStatus() != rpc::Connected ) {
    if ( connectionLostExpires < 0 ) {
      connectionLostExpires = now + config->connectionLostTimeout;
      SOCLOBBY_LOG_ERR( "UserContext %s lost connection", FmtId() );
    }
    else
      if ( now > connectionLostExpires ) {
        SOCLOBBY_LOG_ERR( "UserContext %s have lost connection too long ago (%.1f)", FmtId(), config->connectionLostTimeout );
        if ( StrongMT<IControl> lockedControl = control.Lock() )
          lockedControl->RemoveUserContext( this, true );
        return;
      }
  }
  else
    connectionLostExpires = -1.0;

  if ( party->State() == EPartyState::InLine )
    if ( !party->MmLogicIsValid() ) {
      SOCLOBBY_LOG_ERR( "MM logic is not valid. Removing user context. uid=%s, map=%s", FmtId(), party->MapId() );
        if ( StrongMT<IControl> lockedControl = control.Lock() )
          lockedControl->RemoveUserContext( this, false );
        return;
    }

  if ( modified ) {
    OutputPing();
    modified = false;
  }
}



void UserContext::ChangeStatus( ERequestStatus::Enum _newStatus )
{
  if ( _newStatus != status )
    Modify();

  if ( ( _newStatus != ERequestStatus::PreparingPvX ) && ( _newStatus != ERequestStatus::WaitingInPvX ) )
    mixedSessionLogin.clear();

  status = _newStatus;

  StrongMT<IControl> lockedControl = control.Lock();
  NI_VERIFY( lockedControl, "", return );

  if ( StatusIs() | ERequestStatus::InGame | ERequestStatus::InLine | ERequestStatus::WaitingGameFinish | ERequestStatus::ClientDropped )
    currentStatusExpires = now + 60.0f * config->backupTimeoutLong;
  else
    currentStatusExpires = now + 60.0f * config->backupTimeoutShort;
}



void UserContext::AbandonGame( timer::Time _now )
{
  StrongMT<IControl> lockedControl = control.Lock();
  NI_VERIFY( lockedControl, "", return )

  NI_VERIFY( game.Valid(), "", return );

  SOCLOBBY_LOG_MSG( "User %s abandoned game %s", FmtId(), game->StrId() );

  ChangeStatus( ERequestStatus::WaitingGameFinish );
  
  if ( Strong<IPvxSvcWrapper> pvx = game->PvxService() )
    pvx->Remote()->UserLeftTheGameInCastle( game->Id(), data.userIdPvx, lockedControl->GetPvxAcknowledge() );
  else
    SOCLOBBY_LOG_ERR( "PVX service is not available! Cannot notify about user leaving the game. uid=%s, gameid=%s", FmtId(), game->StrId() );
}



void UserContext::PvxPrepared( const string & key )
{
  if ( status != ERequestStatus::PreparingPvX ) {
    SOCLOBBY_LOG_ERR( "Pvx prepared, wrong request %s state %d", FmtId(), (int)status );
    return;
  }

  mixedSessionLogin = key;
  ChangeStatus( ERequestStatus::WaitingInPvX );
}



void UserContext::SetupGameResultForCompletion( lobby::ETeam::Enum _winner, lobby::TSocialGameId _dbgGameId, const mmaking::SGame & _mmData )
{
  gameResults.winner = _winner;

  if ( status == ERequestStatus::WaitingGameFinish )
    gameResults.playerIsLeaver = true;
  else
    gameResults.playerIsLeaver = false;

  //In manoeuvres, 'data.team' can be overriden by MM
  lobby::ETeam::Enum playerTeam = lobby::ETeam::None;
  for ( int ti = 0; ti < _mmData.humans.size(); ++ti ) {
    const mmaking::SGameParty & pty = _mmData.humans[ti];
    for ( int mi = 0; mi < pty.members.size(); ++mi )
      if ( pty.members[mi].mmId == data.userIdPvx ) {
        playerTeam = pty.common.team;
        break;
      }
    if ( playerTeam != lobby::ETeam::None )
      break;
  }

  if ( playerTeam != lobby::ETeam::None )
    gameResults.playerWin = ( playerTeam == _winner );
  else
    SOCLOBBY_LOG_ERR( "Player %s not found in game %s", FmtId(), lobby::FmtSocGameId( _dbgGameId ) );
}



void UserContext::OutputPing()
{
  SMatchmakingStatus ping;

  ping.sessionContextId = data.sessionContextId;
  ping.progress = status;

  if ( status == ERequestStatus::WaitingInPvX )
    ping.pvxSessionKey = mixedSessionLogin;

  if ( game )
    game->OutputPing( ping, data.userIdPvx );

  if ( status == ERequestStatus::GameFinished )
    ping.gameResults = gameResults;

  LogPing( ping );

  notify->UpdateStatus( ping );
}



void UserContext::LogPing( const SMatchmakingStatus & _ping )
{
  NI_PROFILE_HEAVY_FUNCTION;

  if ( config->verbosityLevel == EVerbosity::Silent )
    return;

  SOCLOBBY_LOG_MSG( "Sending ping update for request %s: %d / %d /'%s'", FmtId(), (int)_ping.progress, _ping.requestsAccepted, _ping.pvxSessionKey );
}



void UserContext::SetupCancelledStatistics( StatisticService::RPC::MMakingCanceled & _statData, timer::Time _now, int _partySize )
{
  _statData.map = NStr::ToUnicode( data.map );
  _statData.member.userid         = data.userIdPvx;
  _statData.member.faction        = data.faction;
  _statData.member.sex            = data.zzimaSex;
  _statData.member.heroid         = Crc32Checksum().AddString( data.heroId.c_str() ).Get();
  _statData.member.heroRating     = data.heroRating;
  _statData.member.playerRating   = data.playerRating;
  _statData.member.guardRating    = data.guardRating;
  _statData.member.force          = data.force;
  _statData.member.partyId        = _partySize;
  _statData.member.loseStreak     = CountLoseStreak( data.winLoseHistory );
  _statData.member.waitTime       = _now - creationTime;
  _statData.member.lobbyReaction  = StatisticService::ELobbyReaction::Cancel;
  _statData.member.basket         = data.basket;
}



int UserContext::CountLoseStreak( const string & winLoseHistory )
{
  int count = 0;
  for ( ; count < winLoseHistory.size(); ++count )
    if ( winLoseHistory[count] != '0' )
      return count;

  return count;
}

} //namespace socialLobby
