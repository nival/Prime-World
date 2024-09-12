#pragma once

#include "Server/LiveMMaking/MMakingLog.h"
#include "Db/DBServer.auto.h"
#include "Server/LiveMMaking/HeroesTable.h"
#include "MmToolSource.h"
#include "MmToolExpect.h"
#include "MmToolStat.h"
#include "MmToolCounter.h"
#include "Server/LiveMMaking/LiveMMakingConfigVars.h"
#include "Server/LiveMMaking/RatingSortMmLogic.h"
#include "Server/LiveMMaking/RankMatchmaking.h"
#include "Server/LiveMMaking/SimpleMMaking.h"
#include "Server/TourneyCfg/TourneyCfg.h"

namespace mm_test
{

class ScriptPlayer : public BaseObjectST, public simple_parser::Parser
{
  NI_DECLARE_REFCOUNT_CLASS_1( ScriptPlayer, BaseObjectST );

public:
  explicit ScriptPlayer( MmData * _mmData, const StatisticsSettings & statSett, bool mockMm ) :
  mmData( _mmData ),
  timescale( 1.0 ), timelimit( 0 ),
  unexpectedGames( 0 ),
  playbackTime( 0 ),
  lastRealtimePoll( 0 ),
  lastTitleUpdate( 0 )
  {
    const string mapId = mmData->map->GetDBID().GetFormatted();

    if ( mockMm || mmData->map->matchmakingSettings->mock )
    {
      StrongMT<mmaking::StubMMaking> logic = new mmaking::StubMMaking( mmData->db, mmaking::CreateConfigFromStatics(), mmData->heroes, mmData->teamSize, mmData->map->mapType, mapId.c_str(), "testmm" );
      if (mmData->map->matchmakingSettings->isTournamentMap)
        logic->EnableAlgoStartRotation( false );
      context.logic = logic;
    }
    else if ( mmData->db->useRanking )
    {
      StrongMT<mmaking::RankMMakingLogic> logic = 
        new mmaking::RankMMakingLogic( mmData->db, mmaking::CreateConfigFromStatics(), mmData->heroes, mmData->teamSize, mmData->map->mapType, "TestMap", "testmm" );
      logic->LaunchParallelThread();
      context.logic = logic;
    }
    else
    {
      StrongMT<mmaking::RatingSortMmLogic> logic = 
        new mmaking::RatingSortMmLogic( mmData->db, mmaking::CreateConfigFromStatics(), mmData->heroes, mmData->teamSize, mmData->map->mapType, mapId.c_str(), "testmm" );
      logic->EnableSimulationMode( true );
      logic->LaunchParallelThread();
      context.logic = logic;
    }

    context.callback = new MmCallback;

    statistics = new Statistics( mmData, statSett );
  }


  bool Parse( simple_parser::Context & _ctx )
  {
    sources.clear();
    activeSources.clear();
    timescale = 1.0;
    timelimit = 0.0;
    playbackTime = 0;
    lastRealtimePoll = 0;

    timer::Time timeOffset = 0;

    while ( true )
    {
      _ctx.ptr = SkipSpaces( _ctx.ptr );
      if ( !*_ctx.ptr )
        return true;

      string key;
      if ( !ForceWord( key, _ctx ) )
        return false;

      if ( key == "skip" )
      {
        timer::Time t = 0;
        if ( !ForceValue( t, _ctx ) )
          return false;
        NI_VERIFY( t >= 0, "Negative time shift", t = 0 );
        timeOffset += t;
      }
      else if ( key == "add" )
      {
        Strong<Source> src = new Source( timeOffset );
        if ( !src->Parse( _ctx ) )
          return false;
        sources.push_back( src );
      }
      else if ( key == "timescale" )
      {
        if ( !ForceValue( timescale, _ctx ) )
          return false;
      }
      else if ( key == "timelimit" )
      {
        if ( !ForceValue( timelimit, _ctx ) )
          return false;
      }
      else if ( key == "recycle_cooldown" )
      {
        if ( !recycleCooldown.Parse( _ctx ) )
          return false;
      }
      else if ( key == "expect" )
      {
        Strong<Expectation> exp = new Expectation;
        if ( !exp->Parse( _ctx ) )
          return false;
        expectations.push_back( exp );
      }

      if ( !ForceSymbol( _ctx, ";" ) )
        return false;
    }
  }


  void StartPlayback( timer::Time _realtime )
  {
    MessageTrace( "%d sources read, starting playback...", sources.size() );
    MessageTrace( "Timescale %.2fx", timescale );
    MessageTrace( "Timelimit %.0f seconds", timelimit );

    activeSources.clear();
    playbackTime = 0;
    lastRealtimePoll = _realtime;

    counter = new MmTestCounter( playbackTime );
  }


  bool PollPlayback( timer::Time _realtime )
  {
    timer::Time delta = _realtime - lastRealtimePoll;
    NI_VERIFY( delta >= 0, "", delta = 0; );
    lastRealtimePoll = _realtime;

    playbackTime += delta * timescale;

    //TODO: Emulate requests removal AND rollback

    context.logic->SetTime( playbackTime );

    PollSources();
    PollNewGames();
    PollRecycledRequests();

    counter->Poll( playbackTime );

    UpdateTitle();

    if ( timelimit )
      if ( playbackTime > timelimit )
        return false;

    unsigned team1 = 0, team2 = 0;
    context.logic->GetLineStatistics( team1, team2 );

    return HasSmthToPlayback() || team1 || team2 || !requestsOnCooldown.empty();
  }


  bool TestPassedOk()
  {
    if ( unexpectedGames )
      return false;
    for ( TExpectations::iterator it = expectations.begin(); it != expectations.end(); ++it )
      if ( !(*it)->Clean() )
        return false;
    return true;
  }


  Statistics * Stat() { return statistics; }
  const Statistics * Stat() const { return statistics; }


  ~ScriptPlayer() 
  {
    if (IsValid(context.logic))
    {
      mmaking::IMMakingLogic* logic = context.logic.Get();
      mmaking::IParallelThreadHolder* pHolder = dynamic_cast<mmaking::IParallelThreadHolder*>(logic);
      pHolder->StopParallelThread();

      context.logic = NULL;
    }
  }

private:
  bool HasSmthToPlayback()
  {
    return !activeSources.empty() || !sources.empty();
  }


  void PollSources()
  {
    if ( !HasSmthToPlayback() )
      return;

    while ( !sources.empty() )
    {
      Strong<Source> src = *sources.begin();
      if ( playbackTime < src->StartTime() )
        break;

      if ( src->Play( playbackTime, context ) )
        activeSources.push_back( src );

      sources.erase( sources.begin() );
    }

    for ( TSources::iterator it = activeSources.begin(); it != activeSources.end(); )
    {
      Strong<Source> src = *it;

      const bool result = src->Poll( playbackTime, context );
      if ( !result )
        it = activeSources.erase( it );
      else
        ++it;
    }

    if ( !HasSmthToPlayback() )
      MessageTrace( "Playback finished." );
  }



  void PollNewGames()
  {
    mmaking::SGame game;
    while( context.logic->PopGame( game ) )
    {
      statistics->ProcessGame( Timestamp( playbackTime ), game );
      counter->CountGame();

      CheckExpectations( game );

      if ( recycleCooldown.valuesSet )
        RecycleGameRequests( game, context.random.NextF( recycleCooldown.from, recycleCooldown.to ) );
    }
  }



  void RecycleGameRequests( const mmaking::SGame & _game, timer::Time _cooldown )
  {
    for ( int i = 0; i < _game.humans.size(); ++i )
    {
      const mmaking::SGameParty & party = _game.humans[i];

      TRequestMap::iterator it = context.requestsInMmaking.find( party.requestUId );
      NI_VERIFY( it != context.requestsInMmaking.end(), NI_STRFMT( "Request with id %d is LOST", party.requestUId ), continue );

      Strong<StoredRequest> req = it->second;

      context.requestsInMmaking.erase( it );

      req->recycleMoment = playbackTime + _cooldown;
      requestsOnCooldown.push_back( req );
    }
  }


  void PollRecycledRequests()
  {
    for ( TRequestList::iterator it = requestsOnCooldown.begin(); it != requestsOnCooldown.end(); )
    {
      StoredRequest * req = *it;
      if ( req->recycleMoment > playbackTime )
      {
        ++it;
        continue;
      }

      mmaking::TRequestUId reqId = context.nextReqUId++;
      statistics->ProcessAddRequest( Timestamp( playbackTime ), reqId, req->common, req->members, 0 );
      context.logic->AddGroupRequest( reqId, req->common, req->members, 0.0, context.callback );

      Strong<StoredRequest> & slot = context.requestsInMmaking[reqId];
      NI_ASSERT( !slot, "" );
      slot = req;

      it = requestsOnCooldown.erase( it );
    }
  }



  void CheckExpectations( const mmaking::SGame & _game )
  {
    for ( TExpectations::iterator it = expectations.begin(); it != expectations.end(); ++it )
    {
      Strong<Expectation> exp = *it;

      if ( exp->Clean() )
        continue;

      if ( ( playbackTime <= exp->TimeRange().from ) || ( playbackTime >= exp->TimeRange().to ) )
        continue;

      int hits = 0, total = 0;
      for ( int pi = 0; pi < _game.humans.size(); ++pi )
      {
        const mmaking::SGameParty & _party = _game.humans[pi];
        int tidx = lobby::ETeam::Index( _party.common.team );
        total += _party.members.size();

        for ( int mi = 0; mi < _party.members.size(); ++mi )
          if ( exp->Sides()[tidx].find( _party.members[mi].mmId ) != exp->Sides()[tidx].end() )
            ++hits;
      }

      if ( hits < total )
        continue;

      exp->Clear();
      MessageTrace( "Expected game cleared!" );
      return;
    }

    ++unexpectedGames;
    ErrorTrace( "Game not expected!" );
  }


  void UpdateTitle()
  {
    timer::Time t = timer::Now();
    if ( t < lastTitleUpdate + 1.0 )
      return;
    lastTitleUpdate = t;

    int hh = (int)( playbackTime / 3600.0 ), mm = (int)( ( playbackTime - hh * 3600.0 ) / 60.0 ), ss = (int)( ( playbackTime - -hh * 3600 - mm * 60.0 ) );

    unsigned team1 = 0, team2 = 0;
    context.logic->GetLineStatistics( team1, team2 );

    SetConsoleTitle( NI_STRFMT( "MMaking %02d:%02d:%02d: %d SrcInln, %d SrcAct, %u+%u MmLine, %d CD, %d Games, %.1f GPS", hh, mm, ss,
                                      sources.size(),
                                      activeSources.size(),
                                      team1, team2,
                                      requestsOnCooldown.size(),
                                      counter->TotalGames(),
                                      counter->AverageGamesPerSec() ) );
  }


  //Types
  typedef list<Strong<Source>>  TSources;
  typedef list<Strong<Expectation>> TExpectations;

  TSources      sources;
  TExpectations expectations;
  int           unexpectedGames;

  //Data
  timer::Time   timescale;
  timer::Time   timelimit;
  simple_parser::ValuesRange<timer::Time>  recycleCooldown;

  timer::Time   playbackTime;
  timer::Time   lastRealtimePoll;
  TSources      activeSources;

  Context       context;
  TRequestList  requestsOnCooldown;

  Strong<MmData> mmData;

  timer::Time   lastTitleUpdate;

  Strong<Statistics> statistics;
  Strong<MmTestCounter> counter;
};

} //namespace mm_test
