#pragma once

#include "MmToolLog.h"
#include "MmVisualization.h"
#include <direct.h>


namespace mm_test
{

class LogScanner : public mm_test::BasicLogParser
{
  NI_DECLARE_REFCOUNT_CLASS_1( LogScanner, mm_test::BasicLogParser );

public:
  LogScanner( MmData * _mmData, const StatisticsSettings & statSett, const VisualizationSettings & visSett ) :
  visualizerNextStep( 0.0 ),
  mmData( _mmData )
  {
    stat = new Statistics( mmData, statSett );
    vis = new Visualization( mmData, visSett );
  }

  virtual void OnAddRequest( const Timestamp & ts, mmaking::TRequestUId reqId, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members, timer::Time wait)
  {
    PlayToTimestamp( ts );

    stat->ProcessAddRequest( ts, reqId, commonData, members, wait );
    vis->AddRequestMark( ts, commonData, members );
  }

  virtual void OnRemoveRequest( const Timestamp & ts, mmaking::TRequestUId reqId )
  {
    PlayToTimestamp( ts );

    stat->ProcessRemoveRequest( ts, reqId, false );
  }

  virtual void OnGame( const Timestamp & ts, const mmaking::SGame & game )
  {
    PlayToTimestamp( ts );

    //FIXME: this only needed for logs version 910 and earlier
    //later logs have correct rating values and non-zero force right in the game records
    mmaking::SGame recoveredGame;
    stat->RecoverGameForce( recoveredGame, game );

    stat->ProcessGame( ts, recoveredGame );
    vis->AddGameMark( ts, recoveredGame );
  }

  void Finish()
  {
    stat->Postprocess();
  }

  void Output()
  {
    stat->Output();

    _mkdir( "results" );
    vis->DrawBunch( "results/" );
  }

private:
  Strong<MmData>      mmData;
  Strong<Statistics>      stat;
  Strong<Visualization>   vis;
  timer::Time             visualizerNextStep;

  void PlaybackPoll()
  {
    if ( PlaybackTime() < visualizerNextStep )
      return;
    
    if ( !visualizerNextStep )
      visualizerNextStep = PlaybackTime();

    visualizerNextStep += vis->Sett().step;

    struct SEnumerator : public IStatisticsEnumerator {
      virtual void EnumRequest( const SStatRequestData * data ) {
        int effr = 0;
        for ( int mi = 0; mi < data->members.size(); ++mi ) {
          effr += data->members[mi].playerRating;
          if ( data->members[mi].basket == mmaking::EBasket::Normal )
            effr += mmaking::MmRequest::LoseStreakRatingCompensation( db, data->members[mi].loseStreak );
        }
        effr /= data->members.size();
        //effr += mmaking::MmRequest::PartyRatingCompensation( db, data->members.size() );

        tslice->Add( data->cmn.team, effr, data->members.size() );
      }
      NDb::Ptr<NDb::MapMMakingSettings> db;
      Strong<Visualization::ITimeslice> tslice;
      SEnumerator( const NDb::MapMMakingSettings * _db, Visualization::ITimeslice * slice ) : db( _db ), tslice( slice ) {}
    };

    SEnumerator E( mmData->db, vis->OpenTimeslice( PlaybackTimestamp() ) );
    stat->EnumActiveRequests( &E );
    E.tslice->Close();
  }
};

} //namespace mm_test
