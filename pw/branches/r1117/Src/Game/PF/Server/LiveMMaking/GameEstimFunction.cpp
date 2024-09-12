#include "stdafx.h"
#include "GameEstimFunction.h"
#include "System/InlineProfiler.h"

namespace mmaking
{

GameEstimFun::GameEstimFun( int teamSize, const NDb::MapMMakingSettings * sett, EBasket::Enum basket, lobby::ETeam::Enum manoeuvresFaction, bool pveMode ) :
_teamSize( teamSize ), _necessaryLadiesCount( sett->necessaryLadiesCount ),
_sett( sett ),
_basket( basket ),
_manoeuvresFaction( manoeuvresFaction ),
_pveMode( pveMode ),
_maxLadiesDelta( Max( sett->necessaryLadiesCount, abs( teamSize - sett->necessaryLadiesCount ) ) ),
_maxGenderPairs( teamSize / 2 ),
_minNoobNumber( sett->minimalNoobsPercentage * teamSize / 100 )
{
  Reset();

  NI_ASSERT( HeroClassesNumber == ( NDb::KnownEnum<NDb::MMakingHeroClassEnum>::sizeOf - 1 ), "" );
}



void GameEstimFun::Reset()
{
  NI_PROFILE_HEAVY_FUNCTION;

  for ( int i = 0; i < 2; ++i ) {
    _totals[i] = 0;
    _females[i] = 0;
    _males[i] = 0;
    _heroes[i].clear();
    _heroes[i].reserve( _teamSize );
    _rating[i].clear();
    _rating[i].reserve( _teamSize );
    _loseStreak[i].clear();
    _loseStreak[i].reserve( _teamSize );
    _sortBuffer[i].clear();
    _sortBuffer[i].reserve( _teamSize );
    _totalRating[i] = 0;
    _noobNumbers[i] = 0;

    for ( int j = 0; j < HeroClassesNumber; ++j )
      _classEfficiencies[i].classes[j] = 0;
  }

  _force.clear();
  _force.reserve( _teamSize );
  _totalForce = 0;

  _waitTime.clear();
  _waitTime.reserve( _teamSize * 2 );

  NI_VERIFY( _sett->optimalClasses.size() == HeroClassesNumber + 1, "", return );
  for ( int i = 0; i < HeroClassesNumber; ++i ) {
    _optimalClassEffMin.classes[i] = (int)( _sett->optimalClasses[i + 1].minEfficiency * 100.0f + 0.5f );
    _optimalClassEffMax.classes[i] = (int)( _sett->optimalClasses[i + 1].maxEfficiency * 100.0f + 0.5f );
  }

  _mandatoryRequests = 0;
}



template <class TRec, class TValue>
void AddToLinearSet( vector<TRec> & linset, TValue val ) {
  for ( vector<TRec>::iterator i = linset.begin(); i != linset.end(); ++i )
    if ( i->value == val ) {
      ++i->count;
      return;
    }
  linset.push_back( TRec( val ) );
}



template <class TRec, class TValue>
bool RemoveFromLinearSet( vector<TRec> & linset, TValue val ) {
  for ( vector<TRec>::iterator i = linset.begin(); i != linset.end(); ++i )
    if ( i->count && i->value == val ) {
      --(i->count);
      if ( !i->count ) {
        if ( ( i + 1 ) != linset.end() )
          *i = linset.back();
        linset.pop_back();
      }
      return true;
    }
  return false;
}


void GameEstimFun::Count( lobby::ETeam::Enum team, lobby::ESex::Enum sex, THeroShortId heroId, EBasket::Enum basket, int rating, int force, const SHeroClassEfficiency & heroEff, int waitTimeSec, int loseStreak, bool mandatory )
{
  //NI_PROFILE_HEAVY_FUNCTION;

  int tidx = lobby::ETeam::Index( team );

  ++_totals[tidx];

  if ( sex == lobby::ESex::Male )
    ++_males[tidx];
  else if ( sex == lobby::ESex::Female )
    ++_females[tidx];

  AddToLinearSet( _heroes[tidx], heroId );

  if ( _basket == EBasket::Normal || _basket == EBasket::Leaver )
    _loseStreak[tidx].push_back( loseStreak );

  if ( _basket != EBasket::Newbie )
  {
    _rating[tidx].push_back( rating );
    _totalRating[tidx] += rating;
  }

  if ( _pveMode )
  {
    _force.push_back( force );
    _totalForce += force;
  }

  _classEfficiencies[tidx].Add( heroEff );

  _waitTime.push_back( waitTimeSec );

  if ( basket == EBasket::Newbie )
    ++_noobNumbers[tidx];

  if ( basket == EBasket::Leaver )
    ++_leaverNumbers[tidx];

  if ( mandatory )
    ++_mandatoryRequests;
}


inline void SafePopValue( vector<int> & vec, int checkValue ) {
#ifdef _DEBUG
  NI_VERIFY( !vec.empty(), "", return );
  NI_ASSERT( vec.back() == checkValue, "" );
#endif //_DEBUG
  vec.pop_back();
}


void GameEstimFun::Uncount( lobby::ETeam::Enum team, lobby::ESex::Enum sex, THeroShortId heroId, EBasket::Enum basket, int rating, int force, const SHeroClassEfficiency & heroEff, int waitTimeSec, int loseStreak, bool mandatory )
{
  //NI_PROFILE_HEAVY_FUNCTION;

  int tidx = lobby::ETeam::Index( team );

  --_totals[tidx];

  if ( sex == lobby::ESex::Male )
    --_males[tidx];
  else if ( sex == lobby::ESex::Female )
    --_females[tidx];

  RemoveFromLinearSet( _heroes[tidx], heroId );

  if ( _basket == EBasket::Normal || _basket == EBasket::Leaver)
    SafePopValue( _loseStreak[tidx], loseStreak );

  if ( _basket != EBasket::Newbie )
  {
    SafePopValue( _rating[tidx], rating );
    _totalRating[tidx] -= rating;
  }

  if ( _pveMode )
  {
    SafePopValue( _force, force );
    _totalForce -= force;
  }

  _classEfficiencies[tidx].Sub( heroEff );

  SafePopValue( _waitTime, waitTimeSec );

  if ( basket == EBasket::Newbie )
    --_noobNumbers[tidx];

  if ( basket == EBasket::Leaver )
    --_leaverNumbers[tidx];


  if ( mandatory )
    --_mandatoryRequests;
}



inline void GetMinMax( int & minVal, int & maxVal, const vector<int> & arr )
{
  for ( vector<int>::const_iterator i = arr.begin(); i != arr.end(); ++i )
  {
    const int r = *i;
    if ( ( minVal < 0 ) || ( r < minVal ) )
      minVal = r;
    if ( ( maxVal < 0 ) || ( r > maxVal ) )
      maxVal = r;
  }
}



inline void GetMinMax( int & minv, int & maxv, const vector<int> arr[2] )
{
  int minvals[2] = { -1, -1 }, maxvals[2] = { -1, -1 };

  for ( int tidx = 0; tidx < 2; ++tidx )
    GetMinMax( minvals[tidx], maxvals[tidx], arr[tidx] );

  minv = Min( minvals[0], minvals[1] );
  maxv = Max( maxvals[0], maxvals[1] );
}



inline int GetSortedDifference( const vector<int> ratings[2], vector<int> buffer[2] )
{
  NI_ASSERT( ratings[0].size() == ratings[1].size(), "" );

  for ( int tidx = 0; tidx < 2; ++tidx ) {
    const vector<int> & R = ratings[tidx];
    vector<int> & B = buffer[tidx];
    //FIXME: Do insertion sort here
    B = R;
    for ( vector<int>::iterator i = B.begin(); i < B.end(); ++i )
      for ( vector<int>::iterator j = i + 1; j < B.end(); ++j )
        if ( *i > *j )
          swap( *i, *j );
  }

  int sum = 0;
  for ( int i = 0; i < buffer[0].size(); ++i ) {
    int delta = abs( buffer[1][i] - buffer[0][i] );
    sum += delta;
  }

  return sum / buffer[0].size();
}



void GameEstimFun::Get( SGameEstimDetails & details, int minMandatoryRequests ) const
{
  //NI_PROFILE_HEAVY_FUNCTION;

  if ( _pveMode )
    NI_VERIFY( ( _totals[0] + _totals[1] ) == _teamSize, "", return )
  else
    NI_VERIFY( ( _totals[0] == _teamSize ) && ( _totals[1] == _teamSize ), "", return );

  CalculateBasicFactors( details );
  CalculateRating( details );
  CalculateForce( details );
  CalculateHeroClasses( details );
  CalculateWaitTime( details );

  if ( !CheckNoobsConditions( details ) )
    details.valid = false;

  if ( _mandatoryRequests < minMandatoryRequests )
    details.valid = false;

  Finalize( details );
}



void GameEstimFun::CalculateBasicFactors( SGameEstimDetails & details ) const
{
  const float maxHeroesDelta = _teamSize - 1;

  //Look in NUM_TASK for the formulaes
  for ( int ti = 0; ti < 2; ++ti )
    if ( _totals[ti] )
    {
      details.sexTerm += _sett->estimFunctionWeights.ladiesNumber * fabs( _necessaryLadiesCount - (float)_females[ti] ) / (float)_maxLadiesDelta;
      details.heroesTerm += _sett->estimFunctionWeights.heroes * fabs( _teamSize - (float)_heroes[ti].size() ) / (float)maxHeroesDelta;
    }

  if ( !_pveMode )
  {
    details.sexTerm *= 0.5f;
    details.heroesTerm *= 0.5f;

    int _genderPairs[2] = { 0, 0 };
    for ( int ti = 0; ti < 2; ++ti )
      _genderPairs[ti] = Min( _females[ti], _males[ti] );

    details.genderPairsDelta = abs( _genderPairs[0] - _genderPairs[1] );
    details.genderPairsDeltaTerm = _sett->estimFunctionWeights.genderPairs * details.genderPairsDelta / _maxGenderPairs;
  }
}



void GameEstimFun::CalculateRating( SGameEstimDetails & details ) const
{
  if ( ( _basket == EBasket::Newbie ) || _pveMode )
    return;

  details.teamRating[0] = _totalRating[0] / _teamSize;
  details.teamRating[1] = _totalRating[1] / _teamSize;
  float avgTeamRating = 0.5f * ( details.teamRating[0] + details.teamRating[1] );

  int ratingMin = -1, ratingMax = -1;
  GetMinMax( ratingMin, ratingMax, _rating );

  details.ratingSpan = ratingMax - ratingMin;
  details.ratingSpanTerm = _sett->estimFunctionWeights.ratingSpan * details.ratingSpan / avgTeamRating;

  details.ratingPatternDelta = GetSortedDifference( _rating, _sortBuffer );
  details.ratingPatternDeltaTerm = _sett->estimFunctionWeights.ratingPatternDelta * details.ratingPatternDelta / avgTeamRating;

  details.ratingTeamAvgDelta = abs( details.teamRating[0] - details.teamRating[1] );
  details.ratingTeamAvgDeltaTerm = _sett->estimFunctionWeights.ratingTeamAvgDelta * details.ratingTeamAvgDelta / avgTeamRating;
}



void GameEstimFun::CalculateForce( SGameEstimDetails & details ) const
{
  if ( !_pveMode )
    return;

  details.avgForce = _totalForce / ( _teamSize * 2 );

  int forceMin = -1, forceMax = -1;
  GetMinMax( forceMin, forceMax, _force );

  details.forceSpan = forceMax - forceMin;
  details.forceSpanTerm = _sett->estimFunctionWeights.forceSpan * details.forceSpan / details.avgForce;
}



void GameEstimFun::CalculateHeroClasses( SGameEstimDetails & details ) const
{
  if ( !_pveMode && _sett->estimFunctionWeights.heroClassesDifference )
  {
    int deltaSum = 0;
    for ( int i = 0; i < HeroClassesNumber; ++i )
      deltaSum += abs( _classEfficiencies[0].classes[i] - _classEfficiencies[1].classes[i] );
    details.heroClassesDifferTerm = _sett->estimFunctionWeights.heroClassesDifference * deltaSum * 1e-2f / _teamSize;
  }

  if ( _sett->estimFunctionWeights.heroClassesOptimum )
  {
    int optimumDiffer = 0;
    for ( int j = 0; j < 2; ++j )
    {
      if ( !_totals[j] )
        continue;

      const int (&classes)[HeroClassesNumber] = _classEfficiencies[j].classes;

      for ( int i = 0; i < HeroClassesNumber; ++i )
      {
        const int minEff = _optimalClassEffMin.classes[i];
        const int maxEff = _optimalClassEffMax.classes[i];

        const int eff = classes[i];
        if ( eff < minEff )
          optimumDiffer += minEff - eff;
        else if ( eff > maxEff )
          optimumDiffer += eff - maxEff;
      }
    }

    if ( !_pveMode )
      optimumDiffer *= 0.5f;

    details.heroClassesOptimumTerm = _sett->estimFunctionWeights.heroClassesOptimum * optimumDiffer * 1e-2f / _teamSize;
  }
}



void GameEstimFun::CalculateWaitTime( SGameEstimDetails & details ) const
{
  int totalWait = 0;
  int minWait = INT_MAX, maxWait = 0;
  for ( IntVec::const_iterator i = _waitTime.begin(); i != _waitTime.end(); ++i ) {
    const int w = *i;
    totalWait += w;
    if ( w < minWait )
      minWait = w;
    if ( w > maxWait )
      maxWait = w;
  }
  details.waitTimeAvg = totalWait / ( _waitTime.size() );
  details.waitTimeMin = minWait;
  details.waitTimeMax = maxWait;

  details.waitTimeAvg = ( details.waitTimeAvg + maxWait ) / 2; //Special tweak
}



bool GameEstimFun::CheckNoobsConditions( const SGameEstimDetails & details ) const
{
  if ( _basket != EBasket::Newbie )
    return true;
  if ( _pveMode )
    return true;

  if ( ( _noobNumbers[0] >= _teamSize ) && ( _noobNumbers[1] >= _teamSize ) )
    return true; //all ok, pure noob game

  if ( details.waitTimeMin < _sett->noobsTimeout )
    return false;

  if ( ( _noobNumbers[0] < _minNoobNumber ) || ( _noobNumbers[1] < _minNoobNumber ) )
    return false;

  return true;
}



inline void UpdateSumAndMax( float & sumValue, float & maxValue, float value )
{
  sumValue += value;
  if ( value > maxValue )
    maxValue = value;
}



void GameEstimFun::Finalize( SGameEstimDetails & details ) const
{
  details.sumValue = 0;

  //sex and heroes terms
  details.sumValue += details.sexTerm;
  details.maxValue = details.sexTerm;

  UpdateSumAndMax( details.sumValue, details.maxValue, details.genderPairsDeltaTerm );
  UpdateSumAndMax( details.sumValue, details.maxValue, details.heroesTerm );
  UpdateSumAndMax( details.sumValue, details.maxValue, details.heroClassesOptimumTerm );
  UpdateSumAndMax( details.sumValue, details.maxValue, details.heroClassesDifferTerm );

  //Rating and force terms
  float ratingForceSum = 0, ratingForceMax = 0;

  //if ( _basket == EBasket::Normal )
  //  UpdateSumAndMax( ratingForceSum, ratingForceMax, details.loseStreakCorrectionTerm );

  if ( ( _basket != EBasket::Newbie ) && !_pveMode )
  {
    UpdateSumAndMax( ratingForceSum, ratingForceMax, details.ratingSpanTerm );
    UpdateSumAndMax( ratingForceSum, ratingForceMax, details.ratingPatternDeltaTerm );
    UpdateSumAndMax( ratingForceSum, ratingForceMax, details.ratingTeamAvgDeltaTerm );
  }

  if ( _pveMode )
    UpdateSumAndMax( ratingForceSum, ratingForceMax, details.forceSpanTerm );

  details.sumValue += ratingForceSum;
  if ( ratingForceMax > details.maxValue )
    details.maxValue = ratingForceMax;

  //FIXME: pre-calculate this in ctor
  const float funDecreaseFactor = ( _manoeuvresFaction == lobby::ETeam::None ) ? _sett->estimFunDecreaseFactor : _sett->estimFunManoeuvresDecreaseFactor;

  if ( details.waitTimeMin < _sett->lowWaitTimeThreshold ) {
    const float t = ( _sett->lowWaitTimeThreshold - details.waitTimeMin ) / (float)_sett->lowWaitTimeThreshold;
    const float k = Lerp( 1.0f, _sett->lowWaitTimeFactor, t );
    details.sumValue *= k;
    details.maxValue *= k;
  }
  else if ( details.waitTimeAvg > _sett->estimFunDecreaseTimeEnd ) {
    details.sumValue *= funDecreaseFactor;
    details.maxValue *= funDecreaseFactor;
  }
  else if ( details.waitTimeAvg > _sett->estimFunDecreaseTimeBegin ) {
    const float deltaTime = _sett->estimFunDecreaseTimeEnd - _sett->estimFunDecreaseTimeBegin;
    const float t = ( details.waitTimeAvg - _sett->estimFunDecreaseTimeBegin ) / deltaTime;
    const float k = Lerp( 1.0f, funDecreaseFactor, t );
    details.sumValue *= k;
    details.maxValue *= k;
  }
}

} //namespace mmaking
