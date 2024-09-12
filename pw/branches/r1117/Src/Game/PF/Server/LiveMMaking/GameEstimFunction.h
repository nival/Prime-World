#ifndef MMGAMEESTIMFUNCTION_H_INCLUDED
#define MMGAMEESTIMFUNCTION_H_INCLUDED

#include "MMakingRequest.h"
#include "Db/DBServer.auto.h"

namespace mmaking
{

struct SGameEstimDetails
{
  bool    valid;
  float   sumValue;
  float   maxValue;

  //separate functions terms, without wait-time-scaling
  float   sexTerm;
  float   genderPairsDeltaTerm;
  float   heroesTerm;
  float   ratingSpanTerm;
  float   ratingPatternDeltaTerm;
  float   ratingTeamAvgDeltaTerm;
  float   forceSpanTerm;
  float   heroClassesOptimumTerm;
  float   heroClassesDifferTerm;
  //float   loseStreakCorrectionTerm;

  //source values
  int     genderPairsDelta;
  int     teamRating[2]; //средний рейтинг команд
  int     avgForce; //PVE only, single team
  int     ratingSpan; //–азброс (макс - мин) рейтингов игроков в игре
  int     ratingPatternDelta;
  int     ratingTeamAvgDelta; // –азброс среднего рейтинга команд
  int     forceSpan;
  //int     loseStreakCorrectionLevel;
  int     waitTimeAvg;
  int     waitTimeMin, waitTimeMax;

  SGameEstimDetails() :
  valid( true ),
  sumValue( 0 ), maxValue( 0 ),
  sexTerm( 0 ), genderPairsDeltaTerm( 0 ), heroesTerm( 0 ),
  ratingSpanTerm( 0 ), ratingPatternDeltaTerm( 0 ), ratingTeamAvgDeltaTerm( 0 ),
  forceSpanTerm( 0 ),
  heroClassesOptimumTerm( 0 ), heroClassesDifferTerm( 0 ),
  //loseStreakCorrectionTerm( 0 ),
  genderPairsDelta( 0 ),
  ratingSpan( 0 ), ratingPatternDelta( 0 ), ratingTeamAvgDelta( 0 ),
  forceSpan( 0 ),
  //loseStreakCorrectionLevel( 0 ),
  waitTimeAvg( 0 ), waitTimeMin( 0 ), waitTimeMax( 0 )
  {
    teamRating[0] = teamRating[1] = 0;
  }
};



class GameEstimFun : public NonCopyable
{
public:
  GameEstimFun( int teamSize, const NDb::MapMMakingSettings * sett, EBasket::Enum basket, lobby::ETeam::Enum manoeuvresFaction, bool pveMode );

  void Reset();

  void Count( lobby::ETeam::Enum team, lobby::ESex::Enum sex, THeroShortId heroId, EBasket::Enum basket, int rating, int force, const SHeroClassEfficiency & heroEff, int waitTimeSec, int loseStreak, bool mandatory );
  void Uncount( lobby::ETeam::Enum team, lobby::ESex::Enum sex, THeroShortId heroId, EBasket::Enum basket, int rating, int force, const SHeroClassEfficiency & heroEff, int waitTimeSec, int loseStreak, bool mandatory );

  void Get( SGameEstimDetails & details, int minMandatoryRequests ) const;

  const SHeroClassEfficiency (&ClassEfficiencies() const)[2] { return _classEfficiencies; }

private:
  const int _teamSize;
  const int _necessaryLadiesCount;
  NDb::Ptr<NDb::MapMMakingSettings> _sett;
  const EBasket::Enum _basket;
  const lobby::ETeam::Enum _manoeuvresFaction;
  const bool    _pveMode;
  const float   _maxLadiesDelta;
  const float   _maxGenderPairs;
  const int     _minNoobNumber;
  SHeroClassEfficiency _optimalClassEffMin, _optimalClassEffMax;

  template <class TValue>
  struct TRecord {
    int       count;
    TValue    value;
    TRecord() : count( 0 ), value( 0 ) {}
    explicit TRecord( TValue val ) : count( 1 ), value( val ) {}
  };

  typedef vector<TRecord<THeroShortId>>  Heroes;
  typedef vector<int>  IntVec;

  int           _totals[2];
  int           _females[2];
  int           _males[2];
  Heroes        _heroes[2];
  IntVec        _rating[2];
  IntVec        _force;
  IntVec        _loseStreak[2];
  mutable IntVec _sortBuffer[2];
  IntVec        _waitTime;
  int           _totalRating[2];
  int           _totalForce; //PVE only, single team
  SHeroClassEfficiency _classEfficiencies[2];
  int           _noobNumbers[2];
  int           _leaverNumbers[2];
  int           _mandatoryRequests;

  void CalculateBasicFactors( SGameEstimDetails & details ) const;
  void CalculateRating( SGameEstimDetails & details ) const;
  void CalculateForce( SGameEstimDetails & details ) const;
  void CalculateHeroClasses( SGameEstimDetails & details ) const;
  void CalculateWaitTime( SGameEstimDetails & details ) const;
  bool CheckNoobsConditions( const SGameEstimDetails & details ) const;
  void Finalize( SGameEstimDetails & details ) const;
};

} //namespace mmaking

#endif //MMGAMEESTIMFUNCTION_H_INCLUDED
