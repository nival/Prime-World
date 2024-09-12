#include "MmLogPlayback.h"

#include "MMakingLogParser.h"
#include "Db/DBServer.auto.h"
#include "Server/LiveMMaking/LiveMMakingConfigVars.h"
#include <direct.h>


namespace mm_test
{

LogPlaybackCallback::LogPlaybackCallback( MmData * _mmData, const StatisticsSettings & statSett, const VisualizationSettings & visSett ) :
BasicLogParser( statSett.timeStep, "Playback" ),
mmData( _mmData ),
visualizerNextStep( 0.0 )
{
  stat = new Statistics( mmData, statSett );

  visualizer = new Visualization( mmData, visSett );

  mmCallback = new MmDummyCallback;

  string mapId = mmData->map->GetDBID().GetFormatted();

  if ( mmData->db->useRanking )
  {
    logic = new mmaking::RankMMakingLogic( mmData->db, mmaking::CreateConfigFromStatics(), mmData->heroes, mmData->teamSize, mmData->map->mapType, mapId.c_str(), "testmm" );
  }
  else
  {
    StrongMT<mmaking::RatingSortMmLogic> rsLogic =
      new mmaking::RatingSortMmLogic( mmData->db, mmaking::CreateConfigFromStatics(), mmData->heroes, mmData->teamSize, mmData->map->mapType, mapId.c_str(), "testmm" );
    rsLogic->EnableSimulationMode( true );
    logic = rsLogic;
  }
}



void LogPlaybackCallback::OnAddRequest( const Timestamp & ts, mmaking::TRequestUId reqId, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members, timer::Time wait )
{
  //NI_PROFILE_FUNCTION;

  PlayToTimestamp( ts );

  if ( wait )
    return;

  std::map<string,int> heroCounter;

  vector<mmaking::TUserId> mmids;
  mmids.reserve( members.size() );
  for ( int i = 0; i < members.size(); ++i ) {
    mmids.push_back( members[i].mmId );
    heroCounter[members[i].heroId] += 1;
  }

  //Check for identical-heroes in request; No more than 2 allowed
  for ( std::map<string,int>::const_iterator it = heroCounter.begin(); it != heroCounter.end(); ++it )
    if ( it->second > 2 ) {
      WarningTrace( "Too many identical heroes (%s x %d of %d) in request %d. Skipped!", it->first, it->second, members.size(), reqId );
      return;
    }

  Strong<ReqItem> item = new ReqItem( reqId, mmids, PlaybackTime() );

  {
    TRequests::iterator prevIt = reqById.find( reqId );
    if ( prevIt != reqById.end() ) {
      Strong<ReqItem> prev = prevIt->second;
      WarningTrace( "Add: dup by reqid! reqid=%d, mmids=%i, old_mmids=%i, old_wait: %.1f", 
                                                    reqId, mmids, prev->mmids, PlaybackTime() - prev->t0 );
      reqAliases[reqId] = prev->reqid;
      return;
    }
  }

  for ( int i = 0; i < mmids.size(); ++i ) {
    mmaking::TUserId mmid = mmids[i];
    TRequestsByMmId::iterator prevIt = reqByMmId.find( mmid );
    if ( prevIt != reqByMmId.end() ) {
      Strong<ReqItem> prev = prevIt->second;
      WarningTrace( "Add: dup by mmid! reqid=%d, mmid=%d, mmids=%i, old_reqid=%i, old_mmids=%i, old_wait: %.1f",
                                                    reqId, mmid, mmids, prev->reqid, prev->mmids, PlaybackTime() - prev->t0 );
      reqAliases[reqId] = prev->reqid;
      return;
    }
  }

  reqById[reqId] = item;
  for ( int i = 0; i < mmids.size(); ++i )
    reqByMmId[mmids[i]] = item;

  stat->ProcessAddRequest( ts, reqId, commonData, members, wait );
  logic->AddGroupRequest( reqId, commonData, members, wait, mmCallback );
  visualizer->AddRequestMark( ts, commonData, members );
}



void LogPlaybackCallback::OnRemoveRequest( const Timestamp & ts, mmaking::TRequestUId reqId )
{
  TRequests::iterator it = reqById.find( reqId );

  if ( it == reqById.end() ) {
    WarningTrace( "Remove: not found! reqid=%d", reqId );
    TRequestAliases::iterator aliasIt = reqAliases.find( reqId );
    if ( aliasIt == reqAliases.end() )
      return;
    mmaking::TRequestUId alias = aliasIt->second;
    WarningTrace( "Remove: using alias! reqid=%d, new_reqid=%d", reqId, alias );
    reqAliases.erase( aliasIt );

    OnRemoveRequest( ts, alias ); //HACK: re-enter
    return;
  }

  Strong<ReqItem> item = it->second;
  NI_VERIFY( reqId == item->reqid, "", return );

  stat->ProcessRemoveRequest( ts, reqId, false );
  logic->RemoveRequest( reqId, mmCallback );

  Remove( it );
}



void LogPlaybackCallback::OnGame( const Timestamp & ts, const mmaking::SGame & game )
{
/*
  std::set<Strong<ReqItem>> toRemove;
  for ( int i = 0; i < game.humans.size(); ++i )
  {
    const mmaking::SGameParty & party = game.humans[i];

    for ( int mi = 0; mi < party.members.size(); ++mi )
    {
      mmaking::TUserId mmid = party.members[mi].mmId;
      TRequestsByMmId::iterator it = reqByMmId.find( mmid );
      if ( it != reqByMmId.end() ) {
        Strong<ReqItem> item = it->second;
        toRemove.insert( item );
      }
      else
        WarningTrace( "Game: unknown mmid! reqid=%d, mmid=%d", party.requestUId, mmid );
    }
  }

  for ( std::set<Strong<ReqItem>>::iterator it = toRemove.begin(); it != toRemove.end(); ++it ) {
    Strong<ReqItem> item = *it;
    stat->ProcessRemoveRequest( ts, item->reqid, false );
    logic->RemoveRequest( item->reqid, mmCallback );
    Remove( item );
  }
*/
}



void LogPlaybackCallback::Finish()
{
  const timer::Time overtime = 600.0;
  MessageTrace( "Main data playback finished. Playing overtime (%.0f minutes)...", overtime / 60.0 );

  PlayTo( PlaybackTime() + overtime );

  MessageTrace( "Postprocessing data..." );
  stat->Postprocess();
}



void LogPlaybackCallback::Output()
{
  stat->Output();

  _mkdir( "results" );
  visualizer->DrawBunch( "results/" );
}



void LogPlaybackCallback::Remove( ReqItem * item )
{
  TRequests::iterator it = reqById.find( item->reqid );
  NI_VERIFY( it != reqById.end(), NI_STRFMT( "Unknown request! reqid=%d", item->reqid ), return );
  Remove( it );
}



void LogPlaybackCallback::Remove( TRequests::iterator it )
{
  Strong<ReqItem> item = it->second;

  for ( int i = 0; i < item->mmids.size(); ++i ) {
    mmaking::TUserId mmid = item->mmids[i];
    TRequestsByMmId::iterator itmmid = reqByMmId.find( mmid );
    NI_VERIFY( itmmid != reqByMmId.end(), NI_STRFMT( "Unknown mmid! reqid=%d, mmid=%d", item->reqid, mmid ), continue );
    reqByMmId.erase( itmmid );
  }

  reqById.erase( it );
}



void LogPlaybackCallback::PlaybackPoll()
{
  PollRequests();
  PollLogic();
  PollMainVisualization();
}



void LogPlaybackCallback::PollLogic()
{
  //NI_PROFILE_FUNCTION;

  logic->SetTime( PlaybackTime() );
  logic->TestPoll();

  mmaking::SGame game;
  while ( logic->PopGame( game ) )
  {
    stat->ProcessGame( PlaybackTimestamp(), game );

    visualizer->AddGameMark( PlaybackTimestamp(), game );

    //Cleanup
    std::set<Strong<ReqItem>> toRemove;
    for ( int i = 0; i < game.humans.size(); ++i ) {
      mmaking::TRequestUId reqid = game.humans[i].requestUId;
      TRequests::iterator it = reqById.find( reqid );
      if ( it != reqById.end() )
      {
        Strong<ReqItem> item = it->second;
        toRemove.insert( item );
      }
      else
        WarningTrace( "Game: unknown reqid! reqid=%d", reqid );
    }

    for ( std::set<Strong<ReqItem>>::iterator it = toRemove.begin(); it != toRemove.end(); ++it )
      Remove( *it );
  }
}



void LogPlaybackCallback::PollRequests()
{
  for ( TRequests::iterator it = reqById.begin(); it != reqById.end();  ) {
    Strong<ReqItem> item = it->second;

    if ( PlaybackTime() > item->t0 + stat->Settings().waitLimit )
    {
      stat->ProcessRemoveRequest( PlaybackTimestamp(), item->reqid, true );
      logic->RemoveRequest( item->reqid, mmCallback );

      ++it;
      Remove( item );
    }
    else
      ++it;
  }
}



void LogPlaybackCallback::PollMainVisualization()
{
  if ( PlaybackTime() < visualizerNextStep )
    return;
  
  if ( !visualizerNextStep )
    visualizerNextStep = PlaybackTime();

  visualizerNextStep += visualizer->Sett().step;

  struct SEnumerator : public mmaking::IDbgRequestsEnumerator {
    virtual void EnumRequest( mmaking::MmRequest * req ) {
      int r = req->AvgPlayerRating() /*+ req->PartyRatingCompensation()*/;
      if ( req->Basket() == mmaking::EBasket::Normal || req->Basket() == mmaking::EBasket::Leaver )
        r += req->LoseStreakRatingCompensation() / req->Size();
      tslice->Add( req->CommonData().team, r, req->Size() );
    }
    Strong<Visualization::ITimeslice> tslice;
    SEnumerator( Visualization::ITimeslice * slice ) : tslice( slice ) {}
  };

  SEnumerator E( visualizer->OpenTimeslice( PlaybackTimestamp() ) );
  logic->DebugEnumerateRequests( &E );
  E.tslice->Close();
}

} //namespace mm_test
