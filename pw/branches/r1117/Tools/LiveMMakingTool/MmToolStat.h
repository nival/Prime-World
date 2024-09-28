#ifndef MMTOOLSTAT_H_INCLUDED
#define MMTOOLSTAT_H_INCLUDED


#include "DataHistogram.h"
#include "Server/LiveMMaking/GameEstimFunction.h"
#include "MMakingLogParser.h"
#include "MmData.h"
#include <list>
#include <map>
#include <set>
#include "Server/LobbySocial/SocialLobbyMMStatisticsEx.h"

namespace Json
{
  class Value;
};
/*
namespace socialLobby
{
  class Config;
};*/

namespace mm_test
{



struct SStatRequestData : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( SStatRequestData, BaseObjectST );

  Timestamp ts;
  mmaking::TRequestUId reqId;
  mmaking::SRequestCommonData cmn;
  timer::Time wait;
  vector<mmaking::SRequestMember> members;

  SStatRequestData( const Timestamp & _t, mmaking::TRequestUId _reqid, const mmaking::SRequestCommonData & _cmn, timer::Time _wait, const vector<mmaking::SRequestMember> & _members ) :
  ts( _t ), reqId( _reqid ), cmn( _cmn ), wait( _wait ),
  members( _members )
  {}
};



struct StatisticsSettings
{
  int     imgWidth, imgHeight;
  float   timeStep;
  float   waitLimit;

  StatisticsSettings() :
  imgWidth( 1400 ), imgHeight( 800 ),
  timeStep( 0.5f ),
  waitLimit( 3600.0 )
  {}
};



struct SPerGameHistograms
{
  //Per game
  nutils::EasyVector<double>      stdWaitScale;
  Strong<nutils::DataHistogram>   estimFun;
  Strong<nutils::DataHistogram>   ratingSpan;
  Strong<nutils::DataHistogram>   ratingPatternDelta;
  Strong<nutils::DataHistogram>   ratingTeamAvgDelta;
  Strong<nutils::DataHistogram>   forceSpan;
  Strong<nutils::DataHistogram>   avgForceDelta;
  Strong<nutils::DataHistogram>   waitTimeAvg;
  Strong<nutils::DataHistogram>   wait[2];
  Strong<nutils::DataHistogram>   waitSerge[2];
  Strong<nutils::DataHistogram2D> waitByPartySize[2];
  std::map<string, Strong<nutils::DataHistogram>> waitByHero[2]; //by team; by hero
  Strong<nutils::DataHistogram>   removedWait[2]; //Per removed request
  Strong<nutils::DataHistogram>   removedWaitNoManoeuvres[2]; //Per removed request
  Strong<nutils::DataHistogram>   wins;
  Strong<nutils::DataHistogram>   winsSpan;

  SPerGameHistograms() :
  stdWaitScale( 0, 30, 60, 120, 180, 240, 300, 600, 900, 1200, 1800, 3600, 10800 ),
  estimFun( new nutils::DataHistogram( nutils::EasyVector<double>( 0.0, 0.1, 0.2, 0.3, 0.5, 0.75, 1.0, 2.0, 5.0, 10.0 ) ) ),
  ratingSpan( new nutils::DataHistogram( nutils::EasyVector<double>( 0, 50, 100, 200, 300, 400, 500, 1000, 2000, 3000 ) ) ),
  ratingTeamAvgDelta( new nutils::DataHistogram( nutils::EasyVector<double>( 0, 50, 100, 200, 300, 400, 500, 1000, 2000, 3000 ) ) ),
  ratingPatternDelta( new nutils::DataHistogram( 50 ) ),
  forceSpan( new nutils::DataHistogram( nutils::EasyVector<double>( 0, 2, 5, 10, 15, 20, 30, 50, 100 ) ) ),
  avgForceDelta( new nutils::DataHistogram( 3 ) ),
  wins( new nutils::DataHistogram( 10, 2 ) ),
  winsSpan( new nutils::DataHistogram( 10, 2 ) )
  {
    waitTimeAvg = new nutils::DataHistogram( stdWaitScale );

    for ( int i = 0; i < 2; ++ i )
    {
      wait[i]                     = new nutils::DataHistogram( stdWaitScale );
      waitSerge[i]                = new nutils::DataHistogram( nutils::EasyVector<double>( 0, 120, 240, 300, 600, 900, 3600, 10800 ) );
      removedWait[i]              = new nutils::DataHistogram( stdWaitScale );
      removedWaitNoManoeuvres[i]  = new nutils::DataHistogram( stdWaitScale );
      waitByPartySize[i]          = new nutils::DataHistogram2D( nutils::EasyVector<double>( 0.5, 1.5, 2.5, 3.5, 4.5, 5.5 ), stdWaitScale );
    }
  }
};



struct DataAccumulator
{
  float   sum, avg, minVal, maxVal;
  int     count;

  DataAccumulator() :
  sum(0), avg(0), minVal(0), maxVal(0), count(0) {}

  void Add( float v ) {
    sum += v;
    minVal = count ? Min( minVal, v ) : v;
    maxVal = count ? Max( maxVal, v ) : v;
    ++count;
    avg = sum / count;
  }
};


class WaitTimeByRating : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( WaitTimeByRating, BaseObjectST );

public:
  WaitTimeByRating( int _r0, int _r1, int _step ) :
  minR( _r0 ), maxR( _r1 ), step( _step )
  {
    int delta = maxR - minR;
    int sz = delta / step;
    sz = Max( sz, 1 );
    data.resize( sz );
  }

  void Add( int r, float wait );
  void Write( const char * filename );

private:
  std::vector<DataAccumulator>  data;
  int                           minR, maxR, step;
};



class GameLogEntry : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( GameLogEntry, BaseObjectST );

public:
  GameLogEntry( const Timestamp & _ts, const mmaking::SGame & _data ) :
  ts( _ts ),
  data( _data )
  {}

  const Timestamp & Ts() const { return ts; }
  const mmaking::SGame & Data() const { return data; }

private:
  Timestamp       ts;
  mmaking::SGame  data;
};



class IStatisticsEnumerator
{
public:
  virtual void EnumRequest( const SStatRequestData * data ) = 0;
};


class Statistics : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Statistics, BaseObjectST );

public:
  Statistics( MmData * _mmData, const StatisticsSettings & _statSett );

  const StatisticsSettings & Settings() const { return settings; }

  void ProcessAddRequest( const Timestamp & ts, mmaking::TRequestUId reqId, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members, timer::Time wait );
  void ProcessRemoveRequest( const Timestamp & ts, mmaking::TRequestUId reqId, bool timedOut );
  void ProcessGame( const Timestamp & ts, const mmaking::SGame & game );

  void RecoverGameForce( mmaking::SGame & recovered, const mmaking::SGame & game ) const;

  void EnumActiveRequests( IStatisticsEnumerator * callback ) const;

  void Postprocess();
  void Output() const;

private:
  Strong<socialLobby::Config> socialLobbyconfig;
  map< int, map< int, map<int, list<timer::Time>>> >   lastGameWaitTimesByMode;
  map< int, map< int, map<int, timer::Time>>>         lastGameGatheredByMode;

  typedef list<int> TIntList;

  typedef std::map<string, int> THeroUsage;
  typedef std::list<Strong<SStatRequestData>> TRequestsLog;
  typedef std::set<mmaking::TUserId> TMmIdSet;
  typedef std::map<mmaking::TRequestUId, Strong<SStatRequestData>> TActiveRequests;
  typedef std::map<mmaking::TUserId, Strong<SStatRequestData>> TActiveRequestsByMmId;

  struct ReportItem {
    nutils::DataHistogram::SInfo  info;
    string                        id;
    string                        section;
    string                        descr;
    ReportItem( const nutils::DataHistogram::SInfo & _info, const string & _id, const string & _section, const string & _descr ) :
    info( _info ), id( _id ), section( _section ), descr( _descr )
    {}
  };

  typedef std::list<ReportItem> TReport;

  struct ReqFilterItem : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( ReqFilterItem, BaseObjectST );
    Timestamp                   ts;
    Timestamp                   lastActivity;
    mmaking::TRequestUId        reqId;
    mmaking::SRequestMember     data;
    mmaking::SRequestCommonData cmn;
    bool                        cancelled;
    ReqFilterItem( const Timestamp & _ts, mmaking::TRequestUId _reqId, const mmaking::SRequestMember & _data, const mmaking::SRequestCommonData & _cmn ) :
    ts( _ts ), lastActivity( _ts ), reqId( _reqId ), data( _data ), cmn( _cmn ), cancelled( false ) {}
  };

  typedef std::map<mmaking::TUserId, Strong<ReqFilterItem>> TRequestFilterById;
  typedef std::list<Strong<ReqFilterItem>> TFilteredRequests;
  typedef std::set<string> TLocationIndexTable;
  typedef std::list<Strong<GameLogEntry>> TGamesLog;
  
  Strong<MmData>                mmData;
  const StatisticsSettings      settings;
  StrongMT<mmaking::IHeroesTable> heroes;

  int                           totalGames;
  unsigned                      totalMembers[2];
  unsigned                      totalLadies[2];

  Timestamp                     minimalTimestamp;
  TRequestsLog                  requestsLogRaw;
  TActiveRequests               activeRequestsByReqId;
  TActiveRequestsByMmId         activeRequestsByMmId;
  std::list<mmaking::TRequestUId> removedLog;
  TMmIdSet                      uniqueUserIds[2];
  TMmIdSet                      uniqueLadies[2];
  THeroUsage                    usedHeroes[2];
  THeroUsage                    heroIds;

  timer::Time                   avgWait[2];
  timer::Time                   avgRemovedWait[2];
  unsigned                      totalGameMembers[2];
  unsigned                      totalRemoved[2];
  unsigned long long            avgTeamRating[2];

  unsigned                      mixedNoobGames;

  TRequestFilterById            requestsFilter;
  TFilteredRequests             filteredRequestsLog;
  unsigned                      filteredOutRequestsNumber;

  struct SAvgForceDeltaByForce {
    Strong<nutils::DataHistogram>   histo;
    float                           force0, force1;
    SAvgForceDeltaByForce( float f0, float f1 ) :
    histo( new nutils::DataHistogram( 5 ) ),
    force0( f0 ), force1( f1 ) {}
  };

  typedef std::list<SAvgForceDeltaByForce> AvgForceDeltaByForce;

  Strong<nutils::DataHistogram>   heroRatingHisto[2];
  Strong<nutils::DataHistogram>   heroRatingCanceledHisto[2];
  Strong<nutils::DataHistogram>   playerRatingHisto[2];
  Strong<nutils::DataHistogram>   playerRatingCanceledHisto[2];
  Strong<nutils::DataHistogram>   forceHisto[2];
  Strong<nutils::DataHistogram2D> heroRatingByHourHisto;
  Strong<nutils::DataHistogram2D> ratingSpanByHeroRating;
  Strong<nutils::DataHistogram>   timeoutRatingHisto;

  SPerGameHistograms              totalHistograms;
  std::map<int, SPerGameHistograms> rankedHistograms;

  Strong<nutils::DataHistogram>   avgForceDelta;
  AvgForceDeltaByForce            avgForceDeltaByForce;

  struct RatingForce {
    int     rating;
    float   force;
    RatingForce( int r, float f ) : rating( r ), force( f ) {}
  };

  typedef std::list<RatingForce> RatingForceData;

  RatingForceData               ratingForceData;

  typedef std::map<mmaking::SHeroClassEfficiency, int> HeroClassEfficiencyTeamData;
  typedef std::list<mmaking::SHeroClassEfficiency> HeroClassLog;

  HeroClassEfficiencyTeamData heroClassEfficiencyTeamData;
  HeroClassLog  heroClassLog;

  struct EnemyForceRelationItem {
    float   mine;
    float   enemyAvg;
    float   enemyMin;
    float   enemyMax;
    EnemyForceRelationItem() : mine( 0 ), enemyAvg( 0 ), enemyMin( 0 ), enemyMax( 0 ) {}
    EnemyForceRelationItem( float _mine, float _avg, float _min, float _max ) :
    mine( _mine ), enemyAvg( _avg ), enemyMin( _min ), enemyMax( _max ) {}
  };
  typedef std::vector<EnemyForceRelationItem> EnemyForceRelation;

  EnemyForceRelation enemyForceRelation;

  Strong<WaitTimeByRating>  waitTimeByRating;

  TGamesLog                 gamesLog;

  void UpdateGameHistograms( SPerGameHistograms & histos, const mmaking::SGame & game, const mmaking::SGameEstimDetails & details );
  SPerGameHistograms & GetThatHistos( int rank );
  SPerGameHistograms & GetThatHistosByRating( int rating, mmaking::EBasket::Enum basket );
  void OutputBasketHistos( const SPerGameHistograms & histos, const string & rangeTitle, TReport & report ) const;
  void ReportHistogram( const nutils::DataHistogram * histo, const string & id, const string & reportSection, const string & descr, int precision, TReport & report ) const;
  void OutputHistogram( const nutils::DataHistogram * histo, const string & id, const string & reportSection, const string & subfolder, const string & descr, int precision, TReport & report ) const;
  static void WriteReport( const TReport & report );
  void WriteRatingForce() const;
  void WriteHeroClassStats() const;
  void WriteHeroClassesTeam() const;
  void WriteForceRelations() const;
  void CheckForMinTimestamp( const Timestamp & ts );
  static void BuildLocationTable( TLocationIndexTable & locTable, const mmaking::SGeoInfo & geo );
  static void WriteLocationsHeaderToFile( FILE * f, const TLocationIndexTable & locTable );
  static void WriteLocationsToFile( FILE * f, const TLocationIndexTable & locTable, const mmaking::SGeoInfo & geo );

  struct ECsvFields {
    enum Enum {
      GameId = 2,
      Canceled = 4,
      Wait = 8,
    };
  };
  struct SCsvFields {
    unsigned                fields;
    mmaking::TRequestUId    reqId;
    unsigned                partySize;
    timer::Time             wait;
    bool                    canceled;
    int                     gameId;
    mmaking::EDebugGameType::Enum dbgGameType;
    SCsvFields() : fields(0), reqId( 0 ), wait( 0 ), canceled( false ), gameId( 0 ), dbgGameType( mmaking::EDebugGameType::Normal ) {}
  };
  void WriteRequestCsvHeader( FILE * f, unsigned fields, const TLocationIndexTable & locTable ) const;
  void WriteRequestToCsv( FILE * f, const SCsvFields & fields, const Timestamp & ts, const mmaking::SRequestCommonData & cmn, const mmaking::SRequestMember & data, const TLocationIndexTable & locTable ) const;
  void WriteRequestsLog() const;
  void WriteFilteredRequestsLog() const;
  void WriteGamesLog() const;

  void RegisterHeroId( const string & heroid );
  void CountHeroUsage( lobby::ETeam::Enum team, const string & heroid );
  int FindHeroId( const string & heroid ) const;
  static string HeroUsageToString( const THeroUsage & usage );

  void EvalForceDeltas( const mmaking::SGame & game );
  void CollectForceRelations( const mmaking::SGame & game );

  void AddActiveRequest( SStatRequestData * data );
  void RemoveActiveRequest( SStatRequestData * data );
  Strong<SStatRequestData> FindActRequestByReqId( mmaking::TRequestUId reqId );
  Strong<SStatRequestData> FindActRequestByMmId( mmaking::TUserId mmId );

  void FilterRequestsOnAdd( SStatRequestData * data );
  void FilterRequestsOnCancel( const Timestamp & ts, SStatRequestData * data );
  void FilterRequestsOnGame( const Timestamp & ts, SStatRequestData * data );
};

} //namespace mm_test

namespace mmaking {

bool operator < ( const SHeroClassEfficiency & l, const SHeroClassEfficiency & r );
bool operator == ( const SHeroClassEfficiency & l, const SHeroClassEfficiency & r );

} //namespace mmaking
#endif //MMTOOLSTAT_H_INCLUDED
