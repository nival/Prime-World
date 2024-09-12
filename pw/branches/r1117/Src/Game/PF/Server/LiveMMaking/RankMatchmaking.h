#ifndef RANKMATCHMAKING_H_INCLUDED
#define RANKMATCHMAKING_H_INCLUDED

#include "ProdMmLogicBase.h"
#include <map>
#include <set>
#include <vector>
#include <list>

namespace mmaking
{

struct QueueIteratorCtx;


struct GeolocationConstraints;

typedef vector<TGeoIndex> TGeoindexVector;


class RankMMakingLogic : public ProdLogicBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( RankMMakingLogic, ProdLogicBase );

public:
  RankMMakingLogic( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix );
  ~RankMMakingLogic();
  
  typedef std::map<int, TRequestMap> TRankRequestMap;
  typedef std::map<int, int> TMergedRankLineCountMap;
private:
  class TeamDraft;
  class Factions;
  
  struct ESweepStage
  {
    enum Enum { LowerLimit = 0, UpperLimit, WidenedLimits, EndMarker };
  };

  struct EForceRequestPriority
  {
    enum Enum{ BOTH = -1, TEAM1 = 0, TEAM2, NOBODY} ;
  };


  unsigned    m_totalGames, m_fullPartyGames, m_fullPartyMixedGames, m_donorGames;
  TRankRequestMap m_rrequests;
  TMergedRankLineCountMap m_MergedRankRequestsCount;
  virtual void RunIteration( int mostPopularRevision, volatile bool & isRunning );
  virtual void OnSmartDump();

  void SearchRank( int mostPopularRevision, const RankDescription * targetRank );
  void SearchForGame( int mostPopularRevision, const RankDescription * targetRank, const GeolocationConstraints & geo, bool fullParty, bool isRandomIter);
  bool SearchForFullParty( TeamDraft teams[2], int mostPopularRevision, const RankDescription * targetRank, const GeolocationConstraints & geo, bool isRandomIter);
  void BasicSweep( TeamDraft & team1, TeamDraft & team2, ESweepStage::Enum stage, int mostPopularRevision,  const RankDescription * targetRank, const TGeoindexVector& sidesLocale, TGeoIndex geolocation, bool isRandomIter);
  void SweepForFullParty( TeamDraft & team1, TeamDraft & team2, int mostPopularRevision, const RankDescription * targetRank, const TGeoindexVector& sidesLocale, TGeoIndex geolocation, bool isRandomIter);
  bool CommonRequestCheckList( const MmRequest * req, timer::Time waitTime, const RankDescription * targetRank,timer::Time & waitTimePenalty );
  bool CheckHeroClasses( const TeamDraft & team, ESweepStage::Enum stage, MmRequest * req, timer::Time correctedWaitTime );
  bool CheckHeroClassesLowLimit( const TeamDraft & team );
  bool CheckDonorConditions( TeamDraft teams[2], const GeolocationConstraints & geo );
  bool CheckLeaverBasket( TeamDraft teams[2] );
  bool CheckRequestLeaverTeam( const TeamDraft& team, const MmRequest * req,timer::Time waitTime );
  bool CheckRankDiff(TeamDraft& team1, TeamDraft& team2,MmRequest * req);
  bool CheckRequestSide(  const TeamDraft & team, const MmRequest * req, timer::Time waitTime );
  void OutputGame( const TeamDraft (&teams)[2], EBasket::Enum basket,  bool dbgFullParty, const RankDescription * targetRank, const GeolocationConstraints & dbgGeo );
  void ChangeSide(TeamDraft (&teams)[2]);
  virtual void PickUpNewRequest( MmRequest * newReq, IMMakingLogicCallback * callback );
  virtual bool DeleteRequest( TRequestUId requestId );
  virtual void ClearInUse(const RankDescription * targetRank);
  bool checkForce(const TeamDraft & team1, const TeamDraft & team2, ESweepStage::Enum stage, MmRequest * req, timer::Time waitTime,bool isParty);
  bool checkPR( const TeamDraft & team1, const TeamDraft & team2, ESweepStage::Enum stage, MmRequest * req, timer::Time waitTime);
  int  CheckHeroForce(EForceRequestPriority::Enum priority,  const TeamDraft & team1, const TeamDraft & team2, ESweepStage::Enum stage, MmRequest * req, timer::Time waitTime,bool isParty = false  );
  int  CheckPlayerRating(EForceRequestPriority::Enum priority, const TeamDraft & team1, const TeamDraft & team2, ESweepStage::Enum stage, MmRequest * req, timer::Time waitTime);

  bool CheckRequestGeneral(TeamDraft& team1, TeamDraft& team2, MmRequest * req, const RankDescription * targetRank, float waitTime, unsigned iteratorFlags, const TGeoindexVector& sidesLocales, timer::Time& waitTimePenalty );
  bool CheckRequestForTeam(TeamDraft& team, MmRequest * req, const RankDescription * targetRank, QueueIteratorCtx& itCtx, EBasket::Enum basket, ESweepStage::Enum stage, timer::Time& correctedWaitTime, unsigned iteratorFlags, const TGeoIndex primaryLocale, timer::Time waitTimePenalty  );
  bool CheckFullPartyRequest(TeamDraft& team, MmRequest * req, const RankDescription * targetRank, QueueIteratorCtx& itCtx, EBasket::Enum basket,  timer::Time& correctedWaitTime, unsigned iteratorFlags, const TGeoIndex primaryLocale );

  void ProcessRequestWithForce(TeamDraft& team1, TeamDraft& team2, ESweepStage::Enum stage, int mostPopularRevision, const RankDescription * targetRank, MmRequest * req, EBasket::Enum basket, QueueIteratorCtx& itCtx, unsigned iteratorFlags, const TGeoindexVector& sidesLocale);
  void ProcessRequest(TeamDraft& team1, TeamDraft& team2, ESweepStage::Enum stage, int mostPopularRevision, const RankDescription * targetRank, MmRequest * req, EBasket::Enum basket, QueueIteratorCtx& itCtx, unsigned iteratorFlags, const TGeoindexVector& sidesLocale);
  void ProcessFullPartyRequestWithForce(TeamDraft& team1, TeamDraft& team2,int mostPopularRevision, const RankDescription * targetRank,  MmRequest * req, EBasket::Enum basket, QueueIteratorCtx& itCtx, unsigned iteratorFlags, const TGeoindexVector& sidesLocale);
  void ProcessFullPartyRequest(TeamDraft& team1, TeamDraft& team2,int mostPopularRevision, const RankDescription * targetRank, MmRequest * req, EBasket::Enum basket, QueueIteratorCtx& itCtx, unsigned iteratorFlags, const TGeoindexVector& sidesLocale);
  void AddToTeam(const int flag, TeamDraft& team1, TeamDraft& team2, MmRequest * req, timer::Time& correctedWaitTime);
  bool CheckLocale(MmRequest * req, const TGeoIndex primaryLocale, unsigned iteratorFlags ) const;
  const TGeoIndex GetPrimaryLocale(int flag,  const TGeoindexVector& sidesLocale ) const;
  inline int chooseTeam(EForceRequestPriority::Enum priority,int fTeam1, int fTeam2 );
  };
} //namespace mmaking

#endif //RANKMATCHMAKING_H_INCLUDED
