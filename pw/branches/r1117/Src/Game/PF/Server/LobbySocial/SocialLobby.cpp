#include "stdafx.h"

#include "SocialLobby.h"
#include "SocialLobbyParty.h"
#include "SocialLobbyUserContext.h"
#include "SocialLobbyGame.h"
#include "ISocialLobbyPvxSvc.h"
#include "ISocialLobbyNotify.h"
#include "SocialLobbyConfig.h"
#include "SocialLobbyRemoteMm.h"
#include "SocialLobbyPvxServices.h"
#include "SocialLobbyMaps.h"
#include "SocialLobbyLog.h"
#include "SocialLobbyClientRevisions.h"
#include "Server/LiveMMaking/HeroesTable.h"
#include "Server/Statistic/StatisticsServerTypes.h"
#include "System/InlineProfiler.h"
#include "Server/LiveMMaking/RankTable.h"
#include "Db/DBServer.auto.h"
#include "SocialLobbyMMStatisticsEx.h"


NI_DEFINE_REFCOUNT( socialLobby::SocialLobby );
NI_DEFINE_REFCOUNT( socialLobby::IPvxAcknowledge );

namespace socialLobby
{

SocialLobby::SocialLobby( Config * _cfg, IGameStatistics * _statistics, IPvxAcknowledge * _pvxAck, IMaps * _maps, const NDb::RollSettings * _rollSett, Transport::IPerfCounters * _perfCounters ) :
config( _cfg ),
nextMmRequestId( 1 ),
maps( _maps ),
rollSett( _rollSett ),
perfCounters( _perfCounters ),
statistics( _statistics ),
pvxAck( _pvxAck ),
now( 0 ),
lastGameGathered( 0 )
{
  mmLogix = new MmLogix( config, maps, this );
  clientRevisions = new ClientRevisions( config->clientRevisionsMerge );
  pvxServices = new PvxServices( config );

  //lastGameWaitTimesByMode[];

  //lastGameGatheredByMode[] = now;
}



void SocialLobby::ProcessConfiguration()
{
  pvxServices->ReloadConfig();
  clientRevisions = new ClientRevisions( config->clientRevisionsMerge );
}



void SocialLobby::UpdateConfigByValue( Config * _cfg )
{
  *(SConfig*)config = *_cfg;

  ProcessConfiguration();
}



void SocialLobby::Poll( timer::Time realTime )
{
  NI_PROFILE_FUNCTION_MEM;

  now = realTime;

  //TODO: Call some of these functions (or all) less often
  PollRequests();
  PollParties();
  PollGames();
  pvxServices->Poll( now );
  mmLogix->Poll( now );
}



const char * SocialLobby::EFindReason::ToString( Enum e )
{
  switch ( e )
  {
    default:              return "unknown";
    case Get:             return "Get";
    case PvxReady:        return "PvxReady";
    case EnteredPvx:      return "EnteredPvx";
    case DroppedFromPvx:  return "DroppedFromPvx";
  }
}



UserContext * SocialLobby::FindContextSafe( TUId _uid, EFindReason::Enum _reason )
{
  NI_PROFILE_HEAVY_FUNCTION;

  TRequestMap::iterator it = requests.find( _uid );
  if ( it == requests.end() ) {
    if ( _reason == EFindReason::Get )
      SOCLOBBY_LOG_MSG( "Unknown request uid u%lld (reason: %s)", _uid, EFindReason::ToString( _reason ) );
    else
      SOCLOBBY_LOG_WRN( "Unknown request uid u%lld (reason: %s)", _uid, EFindReason::ToString( _reason ) );
    return 0;
  }

  Strong<UserContext> ctx = it->second;
  NI_VERIFY( ctx, "", return 0 );
  NI_VERIFY( ctx->Data().uid == _uid, "", return 0 );

  return ctx;
}



UserContext * SocialLobby::FindContextSafePvx( TUserIdPvX _userid, EFindReason::Enum _reason )
{
  NI_PROFILE_HEAVY_FUNCTION;

  TRequestMapPvx::iterator it = requestsForPvx.find( _userid );
  if ( it == requestsForPvx.end() )
  {
    if ( _reason == EFindReason::DroppedFromPvx )
      SOCLOBBY_LOG_MSG( "Unknown request userid pu%d (reason: %s)", _userid, EFindReason::ToString( _reason ) );
    else
      SOCLOBBY_LOG_ERR( "Unknown request userid pu%d (reason: %s)", _userid, EFindReason::ToString( _reason ) );
    return 0;
  }

  Strong<UserContext> ctx = it->second;
  NI_VERIFY( ctx, "", return 0 );
  NI_VERIFY( ctx->Data().userIdPvx == _userid, "", return 0 );

  return ctx;
}



UserContext * SocialLobby::GetContextInLobby( TUId _uid, EFindReason::Enum _reason )
{
  UserContext * ctx = FindContextSafe( _uid, _reason );
  if ( !ctx )
    return 0;

  if ( !ctx->GetGame() ) {
    SOCLOBBY_LOG_ERR( "UserContext %s has no game (reason: %s)", ctx->FmtId(), EFindReason::ToString( _reason ) );
    return 0;
  }

  if ( ctx->GetGame()->State() != EGameState::PvX ) {
    SOCLOBBY_LOG_ERR( "UserContext %s is in wrong game that is not in lobby yet (reason: %s)", ctx->FmtId(), EFindReason::ToString( _reason ) );
    return 0;
  }

  return ctx;
}



UserContext * SocialLobby::GetContextInLobbyPvx( TUserIdPvX _userid, EFindReason::Enum _reason )
{
  UserContext * ctx = FindContextSafePvx( _userid, _reason );
  if ( !ctx )
    return 0;
  
  if ( !ctx->GetGame() ) {
    SOCLOBBY_LOG_ERR( "UserContext %s has no game (reason: %s)", ctx->FmtId(), EFindReason::ToString( _reason ) );
    return 0;
  }

  if ( ctx->GetGame()->State() != EGameState::PvX ) {
    SOCLOBBY_LOG_ERR( "UserContext %s is in wrong game that is not in lobby yet (reason: %s)", ctx->FmtId(), EFindReason::ToString( _reason ) );
    return 0;
  }

  return ctx;
}



bool SocialLobby::PvxInstance( IPvxSvc * _pvx, const string & _clusterId, const Transport::TServiceId & _svcId, const PvxClusterSettings& _settings )
{
  pvxServices->Add( _pvx, _clusterId, _svcId, _settings );
  return true;
}



bool SocialLobby::UpdatePvxSettings( const string& _clusterId, const Transport::TServiceId& _svcId, const PvxClusterSettings& _settings )
{
  pvxServices->UpdateSettings( _clusterId, _svcId, _settings );
  return true;
}



void SocialLobby::PvxInstanceLoadNotify( const string& _clusterId, const Transport::TServiceId & _svcId, unsigned _load )
{
  pvxServices->LoadNotify( _clusterId, _svcId, _load );
}



bool SocialLobby::PvXPreparedForUser( TUserIdPvX _userId, const string & _key )
{
  NI_PROFILE_FUNCTION;

  SOCLOBBY_LOG_MSG( "PvX prepared for user pu%d, key '%s'", _userId, _key );

  UserContext * ctx = GetContextInLobbyPvx( _userId, EFindReason::PvxReady );
  if ( !ctx )
    return false;

  ctx->PvxPrepared( _key );
  return true;
}



bool SocialLobby::UserEnteredPvX( TUserIdPvX _userId )
{
  NI_PROFILE_FUNCTION;

  SOCLOBBY_LOG_MSG( "User pu%d entered PvX", _userId );

  UserContext * ctx = GetContextInLobbyPvx( _userId, EFindReason::EnteredPvx );
  if ( !ctx )
    return false;

  if ( ctx->StatusIs() | ERequestStatus::ClientDropped | ERequestStatus::InGame )
    SOCLOBBY_LOG_MSG( "User %s is fast-reconnecting. Context state is %d", ctx->FmtId(), (int)ctx->Status() );
  else
    if ( ctx->Status() != ERequestStatus::WaitingInPvX ) {
      SOCLOBBY_LOG_ERR( "Wrong request %s state %d", ctx->FmtId(), (int)ctx->Status() );
      return false;
    }

  ctx->ChangeStatus( ERequestStatus::InGame );
  return true;
}



bool SocialLobby::UserDroppedFromPvX( TUserIdPvX _userId, bool _intentional )
{
  NI_PROFILE_FUNCTION;

  SOCLOBBY_LOG_MSG( "User pu%d dropped from PvX%s", _userId, _intentional ? " (leaver)" : "" );

  UserContext * ctx = FindContextSafePvx( _userId, EFindReason::DroppedFromPvx );
  if ( !ctx )
    return false;

  if ( ctx->Status() == ERequestStatus::GameFinished )
    return true; //Do nothing

  if ( !( ctx->StatusIs() | ERequestStatus::WaitingInPvX | ERequestStatus::InGame ) ) {
    SOCLOBBY_LOG_ERR( "Wrong leaver request %s state %d", ctx->FmtId(), (int)ctx->Status() );
    return false;
  }

  Game * game = ctx->GetGame();
  if ( !game || ( game->State() != EGameState::PvX ) ) {
    SOCLOBBY_LOG_ERR( "Wrong leaver request %s game (%s) or game state", ctx->FmtId(), game ? game->StrId() : 0 );
    return false;
  }

  if ( _intentional )
    ctx->AbandonGame( now );
  else
  {
    ctx->ChangeStatus( ERequestStatus::ClientDropped );
    ctx->SetPvxDropTime( now );
  }

  return true;
}



bool SocialLobby::GameFinished( lobby::TSocialGameId _gameId, int /*lobby::ETeam::Enum*/ _winner )
{
  NI_PROFILE_FUNCTION;

  SOCLOBBY_LOG_MSG( "Game %s finished: Faction %d won", lobby::FmtSocGameId( _gameId ), (int)_winner );

  TGames::iterator gameIt = games.find( _gameId );
  if( gameIt == games.end() ) {
    SOCLOBBY_LOG_ERR( "Game %s not found", lobby::FmtSocGameId( _gameId ) );
    return false;
  }

  Strong<Game> game = gameIt->second;
  NI_VERIFY( game, "", return false );
  if ( game->State() != EGameState::PvX ) {
    SOCLOBBY_LOG_ERR( "Game %s should be in lobby yet (status=%d)", game->StrId(), (int)game->State() );
    return false;
  }

  for ( int pi = 0; pi < game->PartiesCount(); ++pi )
    if ( Party * party = game->GetParty( pi ) )
      for ( int mi = 0; mi < party->Size(); ++mi )
        if ( UserContext * ctx = party->Member( mi ) )
        {
          if ( !( ctx->StatusIs() | ERequestStatus::ClientDropped | ERequestStatus::PreparingPvX | ERequestStatus::WaitingInPvX | ERequestStatus::InGame | ERequestStatus::WaitingGameFinish ) )
            SOCLOBBY_LOG_ERR( "Wrong state %d of request %s from game %s", (int)ctx->Status(), ctx->FmtId(), game->StrId() );

          ctx->SetupGameResultForCompletion( (lobby::ETeam::Enum)_winner, game->Id(), game->Data() );

          ctx->SetGame( 0 );
          ctx->ChangeStatus( ERequestStatus::GameFinished );
          ctx->ClearPlayerDetails();
        }

  games.erase( gameIt );

  return true;
}



void SocialLobby::MmLogicSetupResult( const Transport::TServiceId & _svcId, bool _result )
{
  mmLogix->SetupResult( _svcId, _result );
}



void SocialLobby::GameMatchmaked( const mmaking::SGame & _game )
{
  GatherMmStatistics( _game );
  CreateGame( _game );
}



void SocialLobby::GameMatchmakedForReconnect( const mmaking::SReconnectSlot & _slot )
{
  //TODO...
}



void SocialLobby::MmResultAddRequest( mmaking::TRequestUId _requestUId, bool _ok )
{
  if ( _ok )
    return;

  SOCLOBBY_LOG_ERR( "MM AddRequest failed. reqid=%d", _requestUId );

  TPartiesByMmRequest::iterator it = partiesByMmReq.find( _requestUId );
  if ( it != partiesByMmReq.end() )
    if ( Strong<Party> party = it->second )
      if ( party->State() == EPartyState::InLine )
      {
        party->RemoveAllRequests( false );
        return;
      }

  SOCLOBBY_LOG_ERR( "MM AddRequest failed for unknown party or party not in MM. reqid=%d", _requestUId );
}



void SocialLobby::MmResultRemoveRequest( mmaking::TRequestUId _requestUId, bool _ok )
{
  if ( !_ok )
    SOCLOBBY_LOG_ERR( "MM RemoveRequest failed (%d)", _requestUId );
}



void SocialLobby::MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok )
{
  if ( !_ok )
    SOCLOBBY_LOG_ERR( "MM AddReconnectGame failed (%s)", lobby::FmtGameId( _gameId ) );
}



void SocialLobby::MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok )
{
  if ( !_ok )
    SOCLOBBY_LOG_ERR( "MM RemoveReconnectGame failed (%s)", lobby::FmtGameId( _gameId ) );
}



void SocialLobby::MmDebugStatus( const char * _status )
{
  mmDebugStatus = _status ? _status : "";
}



void SocialLobby::RegisterMmLogic( const Transport::TServiceId & _svcId, mmaking::ILiveMMaking * _logic, int _gameModes )
{
  mmLogix->RegisterMmLogic( _svcId, _logic, (mmaking::EServiceGameModes::Enum)_gameModes );
}



void SocialLobby::AddRequest( const SMatchmakingRequest & _reqData, INotify * _callback )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( _callback, "", return );

  SOCLOBBY_LOG_MSG( "Adding request uid=u%i, pvxid=pu%d, mmid=%s, login=%s, nick='%s', map=%s, basket=%d, pty_id=%d, party=%i, party2=%i",
                              _reqData.uid, _reqData.userIdPvx, _reqData.sessionContextId, _reqData.login, _reqData.nickname,
                              _reqData.map, (int)_reqData.basket,
                              _reqData.partyId, _reqData.partyLineup, _reqData.enemyPartyLineup );
  SOCLOBBY_LOG_MSG( "Request data: uid=u%i, faction=%d, original_faction=%d, hero=%s, hrating=%d, grating=%d, prating=%d, force=%.2f, fame=%d",
                              _reqData.uid, (int)_reqData.faction, (int)_reqData.original_faction, _reqData.heroId, _reqData.heroRating, _reqData.guardRating, _reqData.playerRating,
                              _reqData.force, _reqData.fameLevel );
  SOCLOBBY_LOG_MSG( "Request data: uid=u%i, rev=%d, locale=%s, pings=%s",
                              _reqData.uid, _reqData.clientRevision, _reqData.geoInfo.locale, _reqData.geoInfo.FmtPings() );

  Strong<UserContext> ctx = new UserContext( config, _reqData, now, this, _callback );

  if ( !CheckRequestDuplication( ctx ) )
    return;

  Strong<Party> party;
  bool newParty = false;

  if ( _reqData.partyId )
  {
    if ( ( _reqData.partyLineup.size() + _reqData.enemyPartyLineup.size() ) < 2 )
      SOCLOBBY_LOG_WRN( "Party for less then two men. pty_id=%d, %d", _reqData.partyId, _reqData.partyLineup.size() );

    TParties::iterator partyIt = parties.find( _reqData.partyId );
    if ( partyIt != parties.end() )
    {
      if ( partyIt->second.Valid() )
        party = partyIt->second;
      else
        parties.erase( partyIt );
    }
  }

  if ( !party )
  {
    SOCLOBBY_LOG_MSG( "Creating new party. pty_id=%d, pty_size=%d+%d, uid=%s", _reqData.partyId, _reqData.partyLineup.size(), _reqData.enemyPartyLineup.size(), ctx->FmtId() );
    party = new Party( config, now, ctx, this );
    newParty = true;
  }
  else
    if ( !party->Add( ctx ) )
    {
      _callback->Failure();
      return;
    }

  ctx->SetParty( party );

  if ( newParty &&  _reqData.partyId ) {
    const bool inserted = parties.insert( TParties::value_type( _reqData.partyId, party.Get() ) ).second;
    NI_ASSERT( inserted, "" );
  }

  const bool inserted1 = requests.insert( TRequestMap::value_type( _reqData.uid, ctx ) ).second;
  const bool inserted2 = requestsForPvx.insert( TRequestMapPvx::value_type( _reqData.userIdPvx, ctx ) ).second;
  NI_ASSERT( inserted1, "" );
  NI_ASSERT( inserted2, "" );

  ctx->ChangeStatus( ERequestStatus::WaitingPartyMembers );

  if ( party->Completed() )
  {
    if ( party->HasEnemyLineup() )
    {
      if ( CreateCustomGame( party ) )
      {
        _callback->Open( ctx->RpcInterface() );
        return;
      }
      else
      {
        _callback->Failure();
        ctx->CancelPartyRequest();
        return;
      }
    }

    mmaking::TRequestUId mmReqId = nextMmRequestId++;
    SOCLOBBY_LOG_MSG( "Party completed, sending to MM. pty_id=%d, req_id=%d", party->Id(), mmReqId );
    if ( !party->PutRequestInLine( mmReqId, 0, false ) ) {
      _callback->Failure();
      ctx->CancelPartyRequest();
      return;
     }

    Weak<Party> & mmReqSlot = partiesByMmReq[mmReqId];
    if ( mmReqSlot.Valid() )
      SOCLOBBY_LOG_ERR( "Duplicate mm request id. pty_id=%d, req_id=%d", party->Id(), mmReqId );
    mmReqSlot = party;
  }

  _callback->Open( ctx->RpcInterface() );
}



void SocialLobby::Spectate( const SMatchmakingRequestCore & _reqData, TUId _targetUid, NI_LPTR INotify * _callback )
{
  NI_PROFILE_FUNCTION;

  SOCLOBBY_LOG_MSG( "Spectator mode requested. uid=%d, pvxid=%d, target=%d, login=%s, mmid=%s", _reqData.uid, _reqData.userIdPvx, _reqData.targetUid, _reqData.login, _reqData.sessionContextId );
  NI_VERIFY( _callback, "", _callback->Failure(); return );

  Strong<UserContext> target = FindSpectatorTarget( _reqData, _targetUid );
  if ( !target )
  {
    _callback->Failure();
    return;
  }

  Strong<Game> targetGame = target->GetGame();
  Strong<IPvxSvcWrapper> pvx = targetGame->PvxService();
  NI_VERIFY( pvx, "", return );

  SMatchmakingRequest mmReqData;
  reinterpret_cast<SMatchmakingRequestCore &>(mmReqData) = _reqData;

  //let's imitate some target properties
  mmReqData.map = targetGame->Data().mapId;

  Strong<UserContext> ctx = new UserContext( config, mmReqData, now, this, _callback );

  if ( !CheckRequestDuplication( ctx ) )
  {
    _callback->Failure();
    return;
  }

  Strong<Party> party = new Party( config, now, ctx, this );

  ctx->SetParty( party );

  const bool inserted1 = requests.insert( TRequestMap::value_type( _reqData.uid, ctx ) ).second;
  const bool inserted2 = requestsForPvx.insert( TRequestMapPvx::value_type( _reqData.userIdPvx, ctx ) ).second;
  NI_ASSERT( inserted1, "" );
  NI_ASSERT( inserted2, "" );

  ctx->SetGame( targetGame );
  targetGame->AddParty( party );
  targetGame->AddSpectator( ctx );

  ctx->ChangeStatus( ERequestStatus::PreparingPvX );

  pvx->Remote()->NewSpectator( targetGame->Id(), _reqData.userIdPvx, _reqData.login, GetPvxAcknowledge(), _reqData.nickname );
  _callback->Open( ctx->RpcInterface() );

  SOCLOBBY_LOG_MSG( "Spectator created and pushed to PVX. uid=%d, target=%d, game=%s, svcid=%s", _reqData.uid, _reqData.targetUid, targetGame->StrId(), pvx->SvcId().c_str() );
}



void SocialLobby::GetRequest( TUId _uid, INotify * _callback )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( _callback, "", return );

  SOCLOBBY_LOG_MSG( "Requested context u%d...", _uid );

  UserContext * ctx = FindContextSafe( _uid, EFindReason::Get );

  if ( ctx && ( ctx->Status() != ERequestStatus::Null ) )
  {
    SOCLOBBY_LOG_MSG( "Re-opened context %s", ctx->FmtId() );
    ctx->OverrideNotify( _callback );
    _callback->Open( ctx->RpcInterface() );
  }
  else
    _callback->Failure();
}




SServerStatus SocialLobby::GetServerStatus()
{
  SServerStatus st;

  st.acceptTimeout = config->acceptTimeout;
  st.reconnectTimeout = config->reconnectTimeout;

  float totalWait = 0;
  
  for ( list<timer::Time>::iterator it = lastGameWaitTimes.begin(); it != lastGameWaitTimes.end(); ++it )
    totalWait += *it;

  st.averageMmTime = lastGameWaitTimes.size() ? ( totalWait / (timer::Time)lastGameWaitTimes.size() ) : 0;
  st.averageMmTime += ( now - lastGameGathered ) * config->mmWaitTimeFactor;
  st.averageMmTime = Min( st.averageMmTime, config->mmWaitTimeLimit );
  
  st.guardLobbyTimeout = config->guardLobbyTimeout;

  GetServerStatusEx(st);

  st.pvpMmDebugStatus = mmDebugStatus;

  return st;
}

void SocialLobby::GetServerStatusEx( SServerStatus& st)
{
  
  for ( map< int, map< int, map< int, list<timer::Time> > > >::iterator itb = lastGameWaitTimesByMode.begin(); itb != lastGameWaitTimesByMode.end(); ++itb )
  {
    const string basket = GetBasketKey((*itb).first);

    for( map<int, map< int, list<timer::Time> > > ::iterator itm = (*itb).second.begin(); itm != (*itb).second.end(); ++itm )
    {
      int mode = (*itm).first;
      for (map< int, list<timer::Time> >::iterator itr = (*itm).second.begin(); itr != (*itm).second.end(); ++itr )
      {
         st.avgTimesPerMode[basket][mode][(*itr).first] = 0;
         float totalWaitPerMode = 0;
         for (list<timer::Time>::iterator it = (*itr).second.begin(); it != (*itr).second.end(); ++it)
           totalWaitPerMode += (*it);

         st.avgTimesPerMode[basket][mode][(*itr).first] = (*itr).second.size() ? (totalWaitPerMode / (timer::Time)(*itr).second.size() ) : 0;
         st.avgTimesPerMode[basket][mode][(*itr).first] += ( now - lastGameGatheredByMode[(*itb).first][mode][(*itr).first] ) * config->mmWaitTimeFactor;
         st.avgTimesPerMode[basket][mode][(*itr).first] = Min( st.avgTimesPerMode[basket][mode][(*itr).first], config->mmWaitTimeLimit );

         //SOCLOBBY_LOG_DBG("st.avgTimesPerMode[%s][%d][%d] %f", basket.c_str(), mode, (*itr).first, st.avgTimesPerMode[basket][mode][(*itr).first]);
      }
    }
  }
}

RemoteMmLogic * SocialLobby::GetMmLogic( const string & mapId ) const
{
  return mmLogix->GetMmLogic( mapId );
}



Strong<IPvxSvcWrapper> SocialLobby::AllocatePvxSvc( const string & _clusterId, unsigned _loadIncrement )
{
  if ( StrongMT<Transport::IPerfCounters> locked = perfCounters.Lock() )
    locked->AutoPerfCounterRate( "users_inc_soclobby", _loadIncrement );

  return pvxServices->Allocate( _clusterId, _loadIncrement );
}



string SocialLobby::DetermineClusterForGame( const mmaking::SGame & _game ) const
{
  return pvxServices->DetermineClusterForGame( _game );
}



void SocialLobby::RemoveUserContext( UserContext * _ctx, bool _logStatistics )
{
  if ( _logStatistics )
    LogCancelledToStatistics( _ctx );

  RemoveRequest( _ctx, true );
}



int SocialLobby::MapClientRevision( int srcRev )
{
  return clientRevisions->Map( srcRev );
}



bool SocialLobby::CheckRequestDuplication( UserContext * _newCtx )
{
  TRequestMap::iterator reqIt = requests.find( _newCtx->Data().uid );
  if ( reqIt != requests.end() )
  {
    SOCLOBBY_LOG_ERR( "There is active request (status %d) for this uid %s", (int)reqIt->second->Status(), _newCtx->FmtId() );
    _newCtx->GetNotify()->Failure();
    return false;
  }

  TRequestMapPvx::iterator reqPvxIt = requestsForPvx.find( _newCtx->Data().userIdPvx );
  if ( reqPvxIt != requestsForPvx.end() )
  {
    SOCLOBBY_LOG_ERR( "There is active request (status %d) for this pvx userid pu%d", (int)reqPvxIt->second->Status(), _newCtx->Data().userIdPvx );
    _newCtx->GetNotify()->Failure();
    return false;
  }

  return true;
}



void SocialLobby::RemoveRequest( UserContext * _ctx, bool clearGameOfRequest )
{
  NI_ASSERT( _ctx, "" );

  if ( _ctx->GetGame() )
  {
    if ( clearGameOfRequest )
      _ctx->GetGame()->RemoveUser( _ctx );
  }
  else
  {
    if ( _ctx->GetParty()->State() == EPartyState::InLine )
    {
      _ctx->GetParty()->RemoveRequestFromLine();
      _ctx->GetParty()->ChangeAllMembersStatus( ERequestStatus::PartyCameApart );
    }
  }

  if ( _ctx->GetNotify() )
    _ctx->GetNotify()->Close();

  TRequestMap::iterator uidIt = requests.find( _ctx->Data().uid );
  if ( uidIt != requests.end() )
    requests.erase( uidIt );

  TRequestMapPvx::iterator useridIt = requestsForPvx.find( _ctx->Data().userIdPvx );
  if ( useridIt != requestsForPvx.end() )
    requestsForPvx.erase( useridIt );
}



UserContext * SocialLobby::FindSpectatorTarget( const SMatchmakingRequestCore & _reqData, TUId _targetUid )
{
  TRequestMap::iterator targetIt = requests.find( _targetUid );
  if ( targetIt == requests.end() )
  {
    SOCLOBBY_LOG_WRN( "Spectator target not found. uid=u%d, target=u%d", _reqData.uid, _targetUid );
    return 0;
  }

  Strong<UserContext> target = targetIt->second;
  NI_VERIFY( target, "", return 0 );

  if ( !( target->StatusIs() | ERequestStatus::InGame | ERequestStatus::ClientDropped ) )
  {
    SOCLOBBY_LOG_WRN( "Spectator target is in wrong state. uid=%d, target=%d, status=%d", _reqData.uid, _targetUid, (int)target->Status() );
    return 0;
  }

  Strong<Game> game = target->GetGame();
  if ( !game )
  {
    SOCLOBBY_LOG_WRN( "Spectator target has no game. uid=%d, target=%d", _reqData.uid, _targetUid );
    return 0;
  }

  if ( game->State() != EGameState::PvX )
  {
    SOCLOBBY_LOG_WRN( "Spectator target game is in wrong state. uid=%d, target=%d, game=%s, state=%d", _reqData.uid, _targetUid, game->StrId(), (int)game->State() );
    return 0;
  }

  if ( 
    ( game->Data().mapType != NDb::MAPTYPE_PVP ) && 
    ( game->Data().mapType != NDb::MAPTYPE_CTE ) && 
    ( game->Data().mapType != NDb::MAPTYPE_SERIES ) &&
    ( game->Data().mapType != NDb::MAPTYPE_COOPERATIVE ) )
  {
    SOCLOBBY_LOG_WRN( "Wrong spectator target game map type. uid=%d, target=%d, game=%s, game_type=%d", _reqData.uid, _targetUid, game->StrId(), (int)game->Data().mapType );
    return 0;
  }

  if ( !game->PvxService() )
  {
    SOCLOBBY_LOG_ERR( "PVX service of target game is not available! uid=%d, target=%d, game=%s", _reqData.uid, _targetUid, game->StrId() );
    return 0;
  }

  if ( !game->CanBeASpectator() )
  {
    SOCLOBBY_LOG_WRN( "Spectator target game already has a spectator. uid=%d, target=%d", _reqData.uid, _targetUid, (int)target->Status() );
    return 0;
  }

  SOCLOBBY_LOG_DBG( "Found spectator target game. uid=%d, target=%d, game=%s", _reqData.uid, _targetUid, game->StrId() );
  return target;
}



bool SocialLobby::CreateCustomGame( Party * _party )
{
  NDb::Ptr<NDb::AdvMapDescription> map = maps->FindMap( _party->MapId().c_str() );
  if ( !map )
  {
    SOCLOBBY_LOG_ERR( "Unsupported map in custom game. pty_id=%d, map=%s", _party->Id(), _party->MapId() );
    return false;
  }

  mmaking::SGame mmData;
  if ( !_party->SetupCustomGame( mmData, map ) )
    return false;

  Strong<Game> game = new Game( config, persistentIdGenerator.GetNext(), mmData, map, rollSett, true, now, statistics, this );

  bool allIsOk = true;
  for ( int mi = 0; mi < _party->Size(); ++mi )
    if ( UserContext * ctx = _party->Member( mi ) )
    {
      if ( ctx->GetGame() ) {
        SOCLOBBY_LOG_ERR( "Game member is already in game, rolling back new game, uid=%s, game_id=%s", ctx->FmtId(), ctx->GetGame()->StrId() );
        allIsOk = false;
      }
      ctx->ChangeStatus( ERequestStatus::WaitingAccept );
      ctx->SetGame( game );
    }

  game->AddParty( _party );

  if ( !allIsOk )
  {
    game->RollBackGameRequests( 0 );
    return false;
  }

  Strong<Game> & gameSlot = games[game->Id()];

  NI_ASSERT( !gameSlot, "" );
  gameSlot = game;

  SOCLOBBY_LOG_MSG( "Custom game created. game_id=%s, pty_id=%d", game->StrId(), _party->Id() );
  return true;
}



void SocialLobby::CreateGame( const mmaking::SGame & _mmData )
{
  NI_PROFILE_FUNCTION;

  NDb::Ptr<NDb::AdvMapDescription> map = maps->FindMap( _mmData.mapId.c_str() );
  Strong<Game> game = new Game( config, persistentIdGenerator.GetNext(), _mmData, map, rollSett, false, now, statistics, this );

  string dbgIdList;
  dbgIdList.reserve( 128 );

  //First, check that all data structures/states are fine;
  //reset 'InLine' flags in UserContext's and Party's
  bool allIsOk = true;
  for ( int pi = 0; pi < _mmData.humans.size(); ++pi )
  {
    const mmaking::SGameParty & prty = _mmData.humans[pi];

    TPartiesByMmRequest::iterator it = partiesByMmReq.find( prty.requestUId );

    if ( ( it == partiesByMmReq.end() ) || !it->second.Valid() )
    {
      allIsOk = false;
      SOCLOBBY_LOG_ERR( "Party for mm-request %d is missing, rolling back game", prty.requestUId );
      continue;
    }

    if ( pi ) dbgIdList += ", ";

    Party * party = it->second;

    if ( party->PlayersNumber() > 1 ) dbgIdList += "(";

    int alive = 0;
    for ( int mi = 0; mi < party->Size(); ++mi )
      if ( UserContext * ctx = party->Member( mi ) )
      {
        ++alive;

        if ( ctx->GetGame() ) {
          SOCLOBBY_LOG_ERR( "Game member %s is already in game %s, rolling back game", ctx->FmtId(), ctx->GetGame()->StrId() );
          allIsOk = false;
        }

        if ( ctx->Status() != ERequestStatus::InLine ) {
          SOCLOBBY_LOG_ERR( "Game member %s has wrong status %d, rolling back game", ctx->FmtId(), (int)ctx->Status() );
          allIsOk = false;
        }

        bool found = false;
        for ( int mi2 = 0; !found && mi2 < prty.members.size(); ++mi2 )
          if ( prty.members[mi2].mmId == ctx->Data().userIdPvx )
            found = true;
        if ( !found )
          SOCLOBBY_LOG_ERR( "Game member not found in mm-data. uid=%s, pty_id=%d", ctx->FmtId(), party->Id() );

        ctx->ChangeStatus( ERequestStatus::WaitingAccept );
        ctx->SetGame( game );

        dbgIdList += NI_STRFMT( "%su%lld/pu%d", ( alive > 1 ) ? ", " : "", ctx->Data().uid, ctx->Data().userIdPvx );
      }
    if ( alive != prty.members.size() ) {
      SOCLOBBY_LOG_ERR( "Party is incomplete, rolling back game. pty_id=%d, alive=%d, total=%d", party->Id(), alive, prty.members.size() );
      allIsOk = false;
    }

    if ( party->PlayersNumber() > 1 ) dbgIdList += ")";

    party->ResetRequestInLine();
    game->AddParty( party );
  }

  if ( !allIsOk )
  {
    game->RollBackGameRequests( 0 );
    return;
  }

  Strong<Game> & gameSlot = games[game->Id()];

  NI_ASSERT( !gameSlot, "" );
  gameSlot = game;

  SOCLOBBY_LOG_MSG( "Game created. game_id=%s, map=%s, info=%s", game->StrId(), _mmData.mapId, dbgIdList.c_str() );
}



void SocialLobby::MoveGame( TGames & from, TGames & to, lobby::TSocialGameId gameId )
{
  TGames::iterator it = from.find( gameId );
  NI_VERIFY( it != from.end(), "", return );
  Strong<Game> game = it->second;
  NI_VERIFY( game.Valid(), "", return );

  std::pair<TGames::iterator, bool> insertResult =
    to.insert( TGames::value_type( gameId, game ) );
  NI_VERIFY( insertResult.second, "", return );

  from.erase( it );
}



void SocialLobby::PollRequests()
{
  NI_PROFILE_FUNCTION;

  for ( TRequestMap::iterator it = requests.begin(); it != requests.end(); )
  {
    TRequestMap::iterator next = it;
    ++next;

    Strong<UserContext> ctx = it->second;
    ctx->Poll( now );

    it = next;
  }
}



void SocialLobby::PollParties()
{
  for ( TParties::iterator it = parties.begin(); it != parties.end(); )
  {
    Party * party = it->second;
    if ( party && party->Poll( now ) )
      ++it;
    else
      it = parties.erase( it );
  }

  for ( TPartiesByMmRequest::iterator it = partiesByMmReq.begin(); it != partiesByMmReq.end(); )
  {
    if ( !it->second.Valid() )
      it = partiesByMmReq.erase( it );
    else
      ++it;
  }
}



void SocialLobby::PollGames()
{
  NI_PROFILE_FUNCTION;

  for ( TGames::iterator it = games.begin(); it != games.end(); )
  {
    Strong<Game> game = it->second;

    game->Poll( now );

    if ( game->State() == EGameState::Cleared )
    {
      SOCLOBBY_LOG_MSG( "Removing game %s", game->StrId() );
      it = games.erase( it );
    }
    else
      ++it;
  }
}


void SocialLobby::GatherMmStatistics( const mmaking::SGame & _mmData )
{
  GatherMmStatisticsByMode(maps->FindMap( _mmData.mapId.c_str() ),lastGameWaitTimesByMode, lastGameGatheredByMode, config, now, _mmData);

  if ( ( _mmData.mapType != NDb::MAPTYPE_PVP ) && ( _mmData.mapType != NDb::MAPTYPE_CTE ) )
    return;

  timer::Time totalWait = 0;
  int total = 0;

  for ( int pi = 0; pi < _mmData.humans.size(); ++pi ) {
    int sz = _mmData.humans[pi].members.size();
    total += sz;
    totalWait += _mmData.humans[pi].waitTime * sz;
  }
  NI_VERIFY( total, "", return );

  timer::Time avgWait = totalWait / total;

  lastGameWaitTimes.push_back( avgWait );

  while ( lastGameWaitTimes.size() > config->mmWaitTimeLineLength )
    lastGameWaitTimes.pop_front();

  lastGameGathered = now;
}



void SocialLobby::LogCancelledToStatistics( UserContext * _ctx )
{
  Strong<Party> party = _ctx->GetParty();
  NI_VERIFY( party, "", return );

  if ( ( party->State() != EPartyState::InLine ) && ( party->State() != EPartyState::WaitingMembers ) )
    return;

  SOCLOBBY_LOG_MSG( "Logging cancelled request %s", _ctx->FmtId() );

  StatisticService::RPC::MMakingCanceled statData;
  _ctx->SetupCancelledStatistics( statData, now, party->PlayersNumber() );
  statistics->LogMMakingCancelled( statData );
}

} //namespace socialLobby
