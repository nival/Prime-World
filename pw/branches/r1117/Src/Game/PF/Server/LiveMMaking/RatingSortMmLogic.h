#ifndef RATINGSORTMMLOGIC_H_INCLUDED
#define RATINGSORTMMLOGIC_H_INCLUDED

#include "ProdMmLogicBase.h"
#include "RatingSortMmJob.h"
#include "RatingSortMmStat.h"
#include "System/RandomGenerator.h"
#include <map>
#include <set>
#include <vector>
#include <list>


namespace NDb
{
  struct MMakingScale;
}


namespace mmaking
{

typedef vector<TGeoIndex> TGeoindexVector;
class RatingSortWorker;

class RatingSortMmLogic : public ProdLogicBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( RatingSortMmLogic, ProdLogicBase );

public:
  RatingSortMmLogic( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix );
  ~RatingSortMmLogic();

  void EnableSimulationMode( bool enable ) { m_simulationMode = enable; }

private:
  struct PresampleKey;
  struct SampleContext;

  typedef std::set<PresampleKey>                TPresample;
  typedef std::vector<StrongMT<RatingSortJob>>  Jobs;
  typedef std::vector<RatingSortBasePoint>      BasePoints;
  typedef std::list<RatingSortBasePoint>        BasePointsList;

  size_t                      m_workersNumber;

  bool                        m_simulationMode;

  BasePoints                  m_basePoints;
  size_t                      m_nextBasePointIdx;

  timer::Time                 m_proPlayerModeEndTime, m_proPlayerModeStartTime;

  StrongMT<RatingSortWorker>  m_worker;

  StrongMT<RatingSortStatistics> m_statistics;

  NRandom::RandomGenerator    m_random;

  unsigned                    m_debugGameId;

  virtual void RunIteration( int mostPopularRevision, volatile bool & isRunning );
  virtual void OnSmartDump();

  void SetupBasePoints( unsigned threadNumber );
  void ShuffleBasePoints( BasePointsList & dest, BasePointsList & src, unsigned historyLength );
  StrongMT<RatingSortJob> CookDataForAJob( const RatingSortBasePoint & basePoint, int mostPopularRevision );
  RatingSortBasePoint GetNextBasePoint();
  void CheckForProPlayers( int mostPopularRevision );
  bool CookData( Jobs & jobs, int mostPopularRevision );
  void DoTheJob( Jobs & jobs, volatile bool & isRunning );
  void SortJobResults( Jobs & jobs );
  void ProcessResults( Jobs & jobs );
  bool IsRequestsInUse( RatingSortJob * job ) const;
  void MarkRequestsInUse( RatingSortJob * job );
  void MarkRequestsInUse( RatingSortFSAlgorithm::Sample & sample );
  void CreateGameFromJob( RatingSortJob * job );
  void DumpJobSample( RatingSortJob * job, unsigned debugGameId );

  bool FilterPresampleByRating( float & squareDiff, const RatingSortBasePoint & basePoint, MmRequest * req, float timeFactor, SampleContext & sampleCtx );
  bool FilterPresampleByForce( float & squareDiff, const RatingSortBasePoint & basePoint, MmRequest * req, float timeFactor, SampleContext & sampleCtx );
  bool FilterPresampleByPartySize( const RatingSortBasePoint & basePoint, MmRequest * req, timer::Time waitTime );
  bool FilterPresampleByPveFaction( const RatingSortBasePoint & basePoint, MmRequest * req );
  void PresampleByBasePoints( TPresample & presample, SampleContext & ctx, const RatingSortBasePoint & basePoint, int mostPopularRevision, MmRequest * _ignoreReq );
  void PresampleLongWait( TPresample & presample, SampleContext & ctx, const RatingSortBasePoint & basePoint, int mostPopularRevision );
  void PresampleNewbies( TPresample & presample, SampleContext & ctx, const RatingSortBasePoint & basePoint, int mostPopularRevision );
  void PresampleFullParties( TPresample & presample, SampleContext & sampleCtx, const RatingSortBasePoint & basePoint, int mostPopularRevision );
  void UpdateSampleContext( SampleContext & ctx, MmRequest * req, timer::Time waitTime );

  bool SampleSample( RatingSortFSAlgorithm::Sample & sample, const TPresample & presample, const RatingSortBasePoint & basePoint, lobby::ETeam::Enum manvrsFaction, SampleContext & sampleCtx );
  StrongMT<RatingSortJob> CheckFullPartyPvpGames( const TPresample & presample, const RatingSortBasePoint & basePoint, SampleContext & sampleCtx );
  StrongMT<RatingSortJob> CheckFullPartyPveGames( const TPresample & presample, const RatingSortBasePoint & basePoint, SampleContext & sampleCtx );
  void OutputGame( RatingSortDraft & draft, EBasket::Enum basket, lobby::ETeam::Enum manoeuvresFaction, ERatingSortBpType::Enum basePointType );
  void DbgReportRejectedGame( RatingSortJob * job, const char * reason );
};

} //namespace mmaking

#endif //RATINGSORTMMLOGIC_H_INCLUDED
