#include "stdafx.h"
#include "SocialLobbyGame.h"
#include "SocialLobbyUserContext.h"
#include "SocialLobbyParty.h"
#include "SocialLobbyCtrl.h"
#include "SocialLobbyConfig.h"
#include "SocialLobbyGuildFightCalc.h"
#include "ISocialLobbyPvxSvc.h"
#include "SocialLobbyLog.h"
#include "SocialLobbyStatistics.h"
#include "Db/DBServer.auto.h"
#include "Server/Statistic/StatisticsServerTypes.h"
#include "Server/Roll/RatingCalc.h"
#include <map>
#include "System/InlineProfiler.h"
#include "System/Crc32Checksum.h"
#include "Server/TourneyCfg/TourneyCfg.h"


namespace socialLobby
{

Game::Game( Config * _cfg, lobby::TSocialGameId _id, const mmaking::SGame & _data, const NDb::AdvMapDescription * _map, const NDb::RollSettings * _rollSett, bool _customGame, timer::Time _now, IGameStatistics * _statistics, IControl * _control ) :
config( _cfg ),
id( _id ), strId( lobby::FmtSocGameId( _id ) ),
creationTime( _now ),
customGame( _customGame ),
control( _control ),
state( EGameState::Accepting ),
now( _now ),
data( _data ),
map( _map ),
rollSett( _rollSett ),
totalPlayers( 0 ), acceptedCount( 0 ),
preGameLobbyStartTime( 0 ),
hadPreGameLobby( false ),
statistics( _statistics )
{
  for ( int i = 0; i < data.humans.size(); ++i )
    totalPlayers += data.humans[i].members.size();

  parties.reserve( data.humans.size() );
}



void Game::Clear()
{
  ChangeState( EGameState::Cleared );

  parties.clear();
  acceptedCount = 0;
  totalPlayers = 0;
  data = mmaking::SGame(); 
}



void Game::Poll( timer::Time _now )
{
  now = _now;

  switch ( state )
  {
    case EGameState::Accepting:
      if ( now > creationTime + config->acceptTimeout )
      {
        SOCLOBBY_LOG_MSG( "Waiting game %s is timed out, rolling it back...", StrId() );
        AcceptTimedOut();
        RollBackGameRequests( 0 ); //Game will be cleared
      }
      return;

    case EGameState::PreGameLobby:
      if ( now > preGameLobbyStartTime + config->guardLobbyTimeout )
      {
        SOCLOBBY_LOG_MSG( "Pre game lobby timed out, rolling it back. game=%s, timeout=%.0f", StrId(), config->guardLobbyTimeout );
        PreGameLobbyTimedOut();
        RollBackGameRequests( 0 );
      }
      return;

    case EGameState::PvX:
      if ( now > creationTime + config->backupTimeoutLong * 60.0f )
      {
        SOCLOBBY_LOG_ERR( "ACTIVE game %s is timed out (%.0fm), removing it...", strId, config->backupTimeoutLong );
        RemoveAllRequests();
        Clear();
      }
      else if ( !pvxService.Valid() )
      {
        SOCLOBBY_LOG_ERR( "Active game lost connection to PVX, removing it. game=%s", strId );
        RemoveAllRequests();
        Clear();
      }
      return;

    default:
    case EGameState::Cleared:
      return;
  }
}



void Game::AddParty( Party * _party )
{
  if ( parties.size() >= data.humans.size() )
    SOCLOBBY_LOG_WRN( "Game %s overflow", StrId() );

  parties.push_back( _party );
}



bool Game::FindMemberByPvx( Strong<UserContext> & _ctx, Strong<Party> & _party, TUserIdPvX _pvxUserId )
{
  for ( int pi = 0; pi < parties.size(); ++pi )
    if ( Party * party = parties[pi] )
      for ( int mi = 0; mi < party->Size(); ++mi )
        if ( UserContext * ctx = party->Member( mi ) )
          if ( ctx->Data().userIdPvx == _pvxUserId ) {
            _ctx = ctx;
            _party = party;
            return true;
          }

  _ctx = 0;
  _party = 0;
  return false;
}



void Game::AcceptGame( UserContext * _ctx )
{
  NI_ASSERT( state == EGameState::Accepting, "" );

  bool gameChanged = false;
  if ( _ctx->Status() == ERequestStatus::WaitingAccept )
  {
    _ctx->ChangeStatus( ERequestStatus::Accepted );
    gameChanged = true;
  }

  int accepted = 0, notAccepted = 0;
  int officerNumber = 0;
  bool isMemberCheck = false;

  for ( int pi = 0; pi < parties.size(); ++pi )
    if ( Party * party = parties[pi] )
    {
      int maxRating = 0;
      for ( int mi = 0; mi < party->Size(); ++mi )
        if ( UserContext * member = party->Member( mi ) )
        {
          if ( _ctx == member )
            isMemberCheck = true;
          if ( member->Status() == ERequestStatus::Accepted )
            ++accepted;
          else
            ++notAccepted;

          if ( member->Data().basket != mmaking::EBasket::Newbie )
            maxRating = Max( maxRating, member->Data().heroRating );

          if ( gameChanged )
            member->Modify();
        }
      if ( maxRating >= config->officerLobbyRating )
        officerNumber += party->Size();
    }
  NI_ASSERT( isMemberCheck, "" );

  SOCLOBBY_LOG_MSG( "User %s accepted game %s: %d + %d / %d, lifetime %.1f", _ctx->FmtId(), StrId(), accepted, notAccepted, totalPlayers, now - creationTime );

  acceptedCount = accepted;
  if ( acceptedCount >= totalPlayers )
  {
    SOCLOBBY_LOG_MSG( "Game %s completely accepted", StrId() );
    const bool pvp = ( data.mapType == NDb::MAPTYPE_PVP ) || ( data.mapType == NDb::MAPTYPE_CTE );
    const bool coop = ( data.mapType == NDb::MAPTYPE_COOPERATIVE );
    const bool noobGame = ( data.basket == mmaking::EBasket::Newbie );

    bool preGameLobby = false;
    if ( pvp )
      preGameLobby = ( officerNumber > 0 ) && !noobGame;
    if ( coop )
      preGameLobby = ( parties.size() > 1 );
    if ( customGame )
      preGameLobby = false;

    if ( tourney::Enabled() || (map && map->mapSettings && map->mapSettings->fullPartyOnly))
      preGameLobby = false;

    if ( preGameLobby )
      StartPreGameLobby();
    else
      ToPvx();
    return;
  }
  else if ( !notAccepted )
  {
    SOCLOBBY_LOG_MSG( "game %s partially cancelled, rolling back those who accepted", StrId() );
    RollBackGameRequests( 0 );
  }
}



void Game::GuardReady( UserContext * _ctx )
{
  if ( state != EGameState::PreGameLobby ) {
    SOCLOBBY_LOG_ERR( "User %s trying to accept already playing game", _ctx->FmtId() );
    return;
  }

  bool changed = false;

  if ( !_ctx->PreGameLobbyReadiness() )
  {
    _ctx->SetPreGameLobbyReadiness( true );
    changed = true;
  }

  int ready = 0;
  bool isMemberCheck = false;

  for ( int pi = 0; pi < parties.size(); ++pi )
    if ( Party * party = parties[pi] )
      for ( int mi = 0; mi < party->Size(); ++mi )
        if ( UserContext * member = party->Member( mi ) )
        {
          if ( _ctx == member )
            isMemberCheck = true;
          if ( member->PreGameLobbyReadiness() )
            ++ready;

          if ( changed )
            member->Modify();
        }
  NI_ASSERT( isMemberCheck, "" );

  SOCLOBBY_LOG_MSG( "User %s is ready in pre game lobby %s: %d / %d, time %.1f", _ctx->FmtId(), StrId(), ready, totalPlayers, now - preGameLobbyStartTime );

  if ( ready >= totalPlayers )
  {
    SOCLOBBY_LOG_MSG( "Pre game lobby %s is ready", StrId() );
    ToPvx();
    return;
  }
}



inline void MeasurePlayerData( const PvxGameDetails & data )
{
#if 0 //DO_COMMIT
  CObj<Stream> stream = new MemoryStream(16384);
  CObj<IBinSaver> saver = CreateChunklessSaver( stream, 0, false );

  PvxGameDetails & nonConstData = const_cast<PvxGameDetails & >( data );
  nonConstData & *saver;

  int sz = stream->GetPosition();
  DebugTrace( "Player data size: %d", sz );
#endif
}



void Game::ToPvx()
{
  StrongMT<IControl> lockedControl = control.Lock();
  NI_VERIFY( lockedControl, "", return );

  LogGame( true, 0 );

  ChangeState( EGameState::PvXReady );

  PvxGameDetails pvxDetails;
  if ( !SetupGameForPvx( pvxDetails ) )
  {
    RollBackGameRequests( 0 );
    return;
  }

  string location = lockedControl->DetermineClusterForGame( data );
  if ( !location.empty() )
  {
    Strong<IPvxSvcWrapper> pvx = lockedControl->AllocatePvxSvc( location.c_str(), (unsigned)totalPlayers );
    if ( pvx )
    {
      MeasurePlayerData( pvxDetails );

      pvxService = pvx;
      pvx->Remote()->NewGame( id, data, pvxDetails, lockedControl->GetPvxAcknowledge() );
      SOCLOBBY_LOG_MSG( "Game %s pushed to lobby. location=%s, svcid=%s", StrId(), location, pvx->SvcId().c_str() );
      return;
    }
  }

  //fail case
  SOCLOBBY_LOG_CRI( "PVX service is not available! Game %s disbanded. location=%s", StrId(), location );

  RemoveAllRequests();
  Clear();
}



void Game::RemoveUser( UserContext * _ctxToKill )
{
  //TODO: Destroy game when first request is removed
  if ( state == EGameState::Accepting )
  {
    const bool modify = ( _ctxToKill->StatusIs() | ERequestStatus::WaitingAccept | ERequestStatus::Accepted );

    int accepted = 0, notAccepted = 0;

    for ( int pi = 0; pi < parties.size(); ++pi )
      if ( Party * party = parties[pi] )
      {
        for ( int mi = 0; mi < party->Size(); ++mi )
          if ( UserContext * ctx = party->Member( mi ) )
          {
            if ( ctx == _ctxToKill )
              party->ResetMember( mi );
            else
            {
              if ( ctx->Status() == ERequestStatus::Accepted )
                ++accepted;
              else
                ++notAccepted;

              if ( modify )
                ctx->Modify();
            }
          }
      }

    acceptedCount = accepted;

    if ( !notAccepted )
    {
      SOCLOBBY_LOG_MSG( "game %s cancelled", StrId() );
      LogGame( false, _ctxToKill );
      RollBackGameRequests( _ctxToKill );
    }
  }
  else if ( ( state == EGameState::PreGameLobby ) || ( state == EGameState::PvXReady ) )
  {
    SOCLOBBY_LOG_MSG( "game %s cancelled", StrId() );
    LogGame( false, _ctxToKill );
    RollBackGameRequests( _ctxToKill );
  }

  _ctxToKill->SetGame( 0 );
}



void Game::AcceptTimedOut()
{
  NI_PROFILE_FUNCTION;

  LogGame( false, 0 );

  for ( int pi = 0; pi < parties.size(); ++pi )
    if ( Party * party = parties[pi] )
      for ( int mi = 0; mi < party->Size(); ++mi )
        if ( UserContext * ctx = party->Member( mi ) )
        {
          if ( ctx->Status() == ERequestStatus::WaitingAccept )
          {
            ctx->ChangeStatus( ERequestStatus::AcceptTimedOut );
            ctx->SetGame( 0 );
            party->ResetMember( mi );
          }
          else
            if ( ctx->Status() != ERequestStatus::Accepted )
              SOCLOBBY_LOG_ERR( "Wrong request status %d", (int)ctx->Status() );
        }
}



void Game::PreGameLobbyTimedOut()
{
  NI_PROFILE_FUNCTION;

  LogGame( false, 0 );

  for ( int pi = 0; pi < parties.size(); ++pi )
    if ( Party * party = parties[pi] )
      for ( int mi = 0; mi < party->Size(); ++mi )
        if ( UserContext * ctx = party->Member( mi ) )
        {
          if ( ctx->Status() != ERequestStatus::PreGameLobby )
            SOCLOBBY_LOG_ERR( "Wrong request status. Should be in pre game lobby. uid=%s, status=%d", ctx->FmtId(), (int)ctx->Status() );

          if ( !ctx->PreGameLobbyReadiness() )
          {
            ctx->ChangeStatus( ERequestStatus::AcceptTimedOut );
            ctx->SetGame( 0 );
            party->ResetMember( mi );
          }
        }
}



inline const mmaking::SGameParty * FindPartyData( const mmaking::SGame & _data, mmaking::TRequestUId _reqId )
{
  for ( int i = 0; i < _data.humans.size(); ++i )
    if ( _data.humans[i].requestUId == _reqId )
      return &_data.humans[i];
  return 0;
}



inline const lobby::ETeam::Enum FindPlayerFaction( const mmaking::SGame & _data, mmaking::TUserId _uid )
{
  for ( int pi = 0; pi < _data.humans.size(); ++pi )
      for ( int mi = 0; mi < _data.humans[pi].members.size(); ++mi )
        if ( _data.humans[pi].members[mi].mmId == _uid )
          return _data.humans[pi].common.team;

  return lobby::ETeam::None;
}



void Game::RollBackGameRequests( UserContext * _exceptThis )
{
  NI_PROFILE_FUNCTION;

  timer::Time addWaitTime = now - creationTime;
  addWaitTime = 0; //NUM_TASK That's not needed now

  for ( int pi = 0; pi < parties.size(); ++pi )
    if ( Party * party = parties[pi] )
    {
      bool partyRolledBack = false;

      if ( !_exceptThis || !party->HasMember( _exceptThis ) )
        if ( const mmaking::SGameParty * partyData = FindPartyData( data, party->MmReqId() ) )
          partyRolledBack = party->PutRequestInLine( 0, partyData->waitTime + addWaitTime, true );

      if ( !partyRolledBack )
        SOCLOBBY_LOG_MSG( "Can not roll back party, setting party members in state %d. pty_id=%d", (int)ERequestStatus::PartyCameApart, party->Id() );

      for ( int mi = 0; mi < party->Size(); ++mi )
        if ( UserContext * ctx = party->Member( mi ) )
        {
          ctx->SetGame( 0 );
          ctx->SetPreGameLobbyReadiness( false );

          if ( !partyRolledBack )
            if ( ctx->Status() != ERequestStatus::AcceptTimedOut )
              ctx->ChangeStatus( ERequestStatus::PartyCameApart );
        }
    }

  Clear();
}



bool Game::SetupGameForPvx( PvxGameDetails & _pvxDetails )
{
  NI_PROFILE_FUNCTION;

  if ( data.mapType == NDb::MAPTYPE_NONE ) {
    //Game was cleared after acception; Most likely, it was cancelled by one of its participants (after accept)
    SOCLOBBY_LOG_MSG( "Could not output game %s (it was cleared?)", StrId() );
    return false;
  }

  _pvxDetails = PvxGameDetails();

  GuildFightCalculator guildFightCalc( data );

  for ( int pi = 0; pi < parties.size(); ++pi )
  {
    Party * party = parties[pi];
    if ( !party ) {
      SOCLOBBY_LOG_ERR( "Dead party whilst popping up game %s. Rolling it back...", StrId() );
      return false;
    }

    for ( int mi = 0; mi < party->Size(); ++mi )
    {
      UserContext * ctx = party->Member( mi );
      if ( !ctx )
        continue;

      if ( !( ctx->StatusIs() | ERequestStatus::Accepted | ERequestStatus::PreGameLobby ) ) {
        SOCLOBBY_LOG_ERR( "Wrong request %s status %d whilst popping up game %s. Rolling it back...", ctx->FmtId(), (int)ctx->Status(), StrId() );
        return false;
      }

      _pvxDetails.playerDetails.push_back();
      PlayerDetails & details = _pvxDetails.playerDetails.back();

      details.pvxUserId = ctx->Data().userIdPvx;
      details.uid = ctx->Data().uid;
      details.gameData = ctx->PlayerDetails();
      details.nick = ctx->Data().nickname;
      details.login = ctx->Data().login;

      details.gameData.partyId = ( party->PlayersNumber() > 1 ) ? ( pi + 1 ) : 0;

      guildFightCalc.Add( ctx->Data().userIdPvx, ctx->PlayerDetails().guildData.id );

    }
  }

  if ( _pvxDetails.playerDetails.size() != totalPlayers ) {
    SOCLOBBY_LOG_ERR( "Incomplete game %s. Rolling it back...", StrId() );
    return false;
  }

  _pvxDetails.preGameLobby = hadPreGameLobby;
  _pvxDetails.customGame = customGame;
  
  // map->minimalGuildFightTeam = -1, всегда не гильдийский 
  // map->minimalGuildFightTeam = 0,  всегда гильдийский 

  // по задаче https://SITE/browse/NUM_TASK
  // отключаем (в данных) старую логику определения гильдийского боя, а так же все награды для гильдии насыпаем всем, у кого есть билет в кланвый ивент (GuildWarEventPass) в баффах
  guildFightCalc.PrepareGuildData(_pvxDetails.guildData);
  if ( map->minimalGuildFightTeam != -1 && guildFightCalc.IsGuildFight( map->minimalGuildFightTeam) )
    _pvxDetails.sessiontype = lobby::ETypeOfSession::SESSIONTYPE_GUILDBATTLE;
  else 
    _pvxDetails.sessiontype= lobby::ETypeOfSession::SESSIONTYPE_USUALBATTLE;

  if ( !AddRatingDeltasToPvxInfo( _pvxDetails ) )
    WarningTrace( "Rating delta calculation failed. game_id=%d", StrId() );

  NI_ASSERT( state == EGameState::PvXReady, "" );
  ChangeState( EGameState::PvX );
  acceptedCount = 0;

  for ( int i = 0; i < parties.size(); ++i )
    parties[i]->ChangeAllMembersStatus( ERequestStatus::PreparingPvX );

  return true;
}



bool Game::AddRatingDeltasToPvxInfo( PvxGameDetails & _pvxDetails )
{
  const bool pvp = ( data.mapType == NDb::MAPTYPE_PVP ) || ( data.mapType == NDb::MAPTYPE_CTE );
  if ( !pvp )
    return true;
  
  roll::RatingDeltaCalculator calculator1( rollSett, map );
  roll::RatingDeltaCalculator calculator2( rollSett, map );

  for ( int i = 0; i < _pvxDetails.playerDetails.size(); ++i )
  {
    const PlayerDetails & detls = _pvxDetails.playerDetails[i];

    lobby::ETeam::Enum faction = FindPlayerFaction( data, detls.pvxUserId );
    NI_VERIFY( faction != lobby::ETeam::None, "", return false );

    calculator1.AddPlayer( faction, detls.uid, detls.gameData.heroRating, detls.gameData.partyId );
    calculator2.AddPlayer( faction, detls.uid, detls.gameData.heroRating, detls.gameData.partyId );
  }

  if ( !calculator1.Calculate( lobby::ETeam::Team1 ) )
    return false;
  if ( !calculator2.Calculate( lobby::ETeam::Team2 ) )
    return false;

  for ( int i = 0; i < _pvxDetails.playerDetails.size(); ++i )
  {
    PlayerDetails & detls = _pvxDetails.playerDetails[i];

    lobby::ETeam::Enum faction = FindPlayerFaction( data, detls.pvxUserId );
    NI_VERIFY( faction != lobby::ETeam::None, "", return false );

    float delta1 = 0, delta2 = 0;
    calculator1.GetDelta( detls.uid, delta1, true );
    calculator2.GetDelta( detls.uid, delta2, true );

    detls.gameData.ratingDeltaPrediction.onVictory  = ( faction == lobby::ETeam::Team1 ) ? delta1 : delta2;
    detls.gameData.ratingDeltaPrediction.onDefeat   = ( faction == lobby::ETeam::Team1 ) ? delta2 : delta1;
  }

  return true;
}



void Game::OutputPing( SMatchmakingStatus & _ping, TUserIdPvX _pvxid )
{
  NI_PROFILE_FUNCTION;
  _ping.gameId = id;
  _ping.requestsAccepted = acceptedCount;
  _ping.totalPlayers = totalPlayers;

  _ping.gameBasket = data.basket;

  _ping.preGameLobbyInfo.preGameLobby = hadPreGameLobby;

  if ( _ping.progress == ERequestStatus::PreGameLobby )
  {
    lobby::ETeam::Enum we = FindPlayerFaction( data, _pvxid );

    for ( int i = 0; i < data.humans.size(); ++i )
      for ( int mi = 0; mi < data.humans[i].members.size(); ++mi )
      {
        const mmaking::SRequestMember & m = data.humans[i].members[mi];
        Strong<UserContext> ctx;
        Strong<Party> party;
        if ( FindMemberByPvx( ctx, party, m.mmId ) ) {
          const bool ready = ctx->PreGameLobbyReadiness();
          if ( data.humans[i].common.team == we )
            _ping.preGameLobbyInfo.allies.push_back( SAllyStatus( ctx->Data().uid, ready ) );
          else
            if ( ready )
              _ping.preGameLobbyInfo.foesReady += 1;
        }
      }
  }

  PingDebugInfo( _ping );
}



bool Game::CanBeASpectator() const
{
  int counter = 0;
  for ( TWeakRequestSet::const_iterator it = spectators.begin(); it != spectators.end(); ++it )
    if ( *it )
      ++counter;

  if ( counter >= config->maxSpectators )
    return false;

  return true;
}



void Game::AddSpectator( UserContext * _spect )
{
  spectators.insert( _spect );
}



void Game::StartPreGameLobby()
{
  SOCLOBBY_LOG_MSG( "Starting pre game lobby. game=%s", StrId() );

  ChangeState( EGameState::PreGameLobby );
  acceptedCount = 0;

  hadPreGameLobby = true;

  preGameLobbyStartTime = now;

  for ( int i = 0; i < parties.size(); ++i )
    parties[i]->ChangeAllMembersStatus( ERequestStatus::PreGameLobby );
}



void Game::LogGame( bool success, UserContext * cancelledCtx )
{
  if ( data.mapType == NDb::MAPTYPE_NONE )
    return;

  SOCLOBBY_LOG_MSG( "Logging game %s", StrId() );

  StatisticService::RPC::MMakingGame statData;

  statData.status = success ? StatisticService::ELobbyGameStatus::Launched : StatisticService::ELobbyGameStatus::Dismissed;
  statData.persistentId = id;
  statData.basket = data.basket;
  statData.members.reserve( totalPlayers );
  statData.map = NStr::ToUnicode( data.mapId );
  
  

  for ( int pi = 0; pi < data.humans.size(); ++pi ) {
    const mmaking::SGameParty & pty = data.humans[pi];
    for ( int mi = 0; mi < pty.members.size(); ++mi ) {
      const mmaking::SRequestMember & memb = pty.members[mi];

      statData.members.push_back( StatisticService::RPC::MMakingMember() );
      StatisticService::RPC::MMakingMember & statMemb = statData.members.back();

      statMemb.userid     = memb.mmId;
      statMemb.faction    = pty.common.team;
      statMemb.original_faction = memb.original_team;
      statMemb.sex        = memb.sex;
      statMemb.heroid     = Crc32Checksum().AddString( memb.heroId.c_str() ).Get();
      statMemb.heroRating = memb.heroRating;
      statMemb.playerRating = memb.playerRating;
      statMemb.guardRating = memb.guardRating;
      statMemb.force      = memb.force;
      statMemb.partyId    = ( pty.members.size() > 1 ) ? ( pi + 1 ) : 0;
      statMemb.loseStreak = memb.loseStreak;
      statMemb.waitTime   = pty.waitTime;
      statMemb.fameLevel  = memb.fameLevel;
      statMemb.basket     = memb.basket;

      if ( cancelledCtx && ( memb.mmId == cancelledCtx->Data().userIdPvx ) ) {
        statMemb.lobbyReaction = StatisticService::ELobbyReaction::Cancel;
        continue;
      }

      Strong<UserContext> ctx;
      Strong<Party> party;
      if ( !FindMemberByPvx( ctx, party, memb.mmId ) ) {
        statMemb.lobbyReaction = StatisticService::ELobbyReaction::Cancel;
        continue;
      }

      ERequestStatus::Enum st = ctx->Status();
      if ( st == ERequestStatus::Accepted )
        statMemb.lobbyReaction = StatisticService::ELobbyReaction::Accept;
      else if ( st == ERequestStatus::PreGameLobby ) {
        if ( ctx->PreGameLobbyReadiness() )
        {
          statMemb.lobbyReaction = StatisticService::ELobbyReaction::PreGameLobbyReady;
          statMemb.lobbyReactionTime = ctx->PreGameLobbyReadyTime() - preGameLobbyStartTime;
        }
        else
          statMemb.lobbyReaction = StatisticService::ELobbyReaction::PreGameLobbyNotReady;
      }
      else if ( ( st == ERequestStatus::WaitingAccept ) || ( st == ERequestStatus::AcceptTimedOut ) )
        statMemb.lobbyReaction = StatisticService::ELobbyReaction::Slowpoke;
      else
        SOCLOBBY_LOG_WRN( "Wrong user context %s status %d while writing statistics for game %s", ctx->FmtId(), (int)ctx->Status(), StrId() );
    }
  }
  SOCLOBBY_LOG_MSG( "Send LogMMakingGame statistics ( status: %d, persistentId: %s, basket: %d, members: %d, map: %s ) ", 
      statData.status, 
      StrId(), 
      statData.basket,
      statData.members.size(),
      statData.map);

  statistics->LogMMakingGame( statData );
}



void Game::PingDebugInfo( SMatchmakingStatus & _ping )
{
  if ( !config->debugInfoOnPing )
    return;

  NI_PROFILE_HEAVY_FUNCTION;

  _ping.debugInfo.reserve( 256 );
  _ping.debugInfo = NI_STRFMT( "Game %s: ", StrId() );
  bool first = true;
  for ( int pi = 0; pi < parties.size(); ++pi )
  {
    Party * p = parties[pi];
    if ( !p ) {
      _ping.debugInfo += "<Entire party missing>";
      continue;
    }

    if ( p->Id() ) {
      _ping.debugInfo += NI_STRFMT( "Party p%d: ( ", p->Id() );
      first = true;
    }

    for ( int mi = 0; mi < p->Size(); ++mi ) {
      if ( UserContext * ctx = p->Member( mi ) )
        _ping.debugInfo += NI_STRFMT( "%su%d/%s/%d", first ? "" : ", ", ctx->Data().uid, ctx->Data().login, (int)ctx->Status() );
      else
        _ping.debugInfo += NI_STRFMT( "%s<leaver>", first ? "" : ", " );
      first = false;
    }

    if ( p->Id() )
      _ping.debugInfo += ")";
  }
}



void Game::RemoveAllRequests()
{
  for ( int pi = 0; pi < parties.size(); ++pi )
    if ( Party * party = parties[pi] )
      party->RemoveAllRequests( false );

  //parties and partiesByMmReq will be cleansed on their poll
}

} //namespace socialLobby
