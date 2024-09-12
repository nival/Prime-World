#include "stdafx.h"
#include "SmartRandom.h"
#include "PFLogicObject.h"


namespace NWorld
{

SmartRandomGenerator::StateKey::StateKey( const int _key, const PFLogicObject* _pFirst, const PFLogicObject* _pSecond )
: key( _key )
, pFirst( _pFirst )
, pSecond( _pSecond )
, first( _pFirst ? _pFirst->GetWOID() : 0 )
, second( _pSecond ? _pSecond->GetWOID() : 0 )
{
}

bool SmartRandomGenerator::StateKey::operator<( StateKey const& other ) const
{
  if ( key < other.key )
    return true;
  if ( key > other.key )
    return false;

  if ( first < other.first )
    return true;
  if ( first > other.first )
    return false;

  if ( second < other.second )
    return true;

  return false;
}

// probability is supposed to be float (not percents)
bool SmartRandomGenerator::Roll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond, const int key )
{
  NI_VERIFY( pFirst && pSecond, "Improper usage of smart random", return false; );

  StateKey stateKey( key, static_cast<PFLogicObject const*>(pFirst), static_cast<PFLogicObject const*>(pSecond) );
  RollState& rs = rollStates[stateKey];

  if ( maxSuccessReps > -1 && rs.successReps == maxSuccessReps )
  {
    rs.successReps = 0;
    rs.failReps = 1;
    return false;
  }

  if ( maxFailReps > -1 && rs.failReps == maxFailReps )
  {
    rs.failReps = 0;
    rs.successReps = 1;
    return true;
  }

  bool res = pRandomGen->Roll( probability * 100.0f ); // input number is percents
  if ( res )
  {
    rs.successReps++;
    rs.failReps = 0;
  }
  else
  {
    rs.failReps++;
    rs.successReps = 0;
  }

  return res;
}

// probDecrement is supposed to be float (not percents)
int SmartRandomGenerator::Random( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond, int key )
{
  NI_VERIFY( outcomesNumber > 1, "Improper usage of smart random", return 0; )
  NI_VERIFY( pFirst && pSecond, "Improper usage of smart random", return 0; )

  const float defaultProb = 1.0f / (float)outcomesNumber;

  StateKey stateKey( key, static_cast<PFLogicObject const*>(pFirst), static_cast<PFLogicObject const*>(pSecond) );
  RandomState& rs = randomStates[stateKey];
  vector<float>& probs = rs.probs;
  if ( probs.empty() )
  {
    probs.resize( outcomesNumber, defaultProb );
  }

  float sum = 0;
  for ( int i = 0; i < probs.size(); ++i )
    sum += probs[i];
  NI_VERIFY( sum > 0, "Distribution is zero!", return -1; )

  float roll = pRandomGen->NextF( 0.0f, sum );

  float cumulative = 0;
  int result = -1;
  for ( int i = 0; i < probs.size(); ++i )
  {
    cumulative += probs[i];
    if ( roll < cumulative )
    {
      result = i;
      break;
    }
  }

  NI_VERIFY( result > -1, "Bad random!", return -1; )

  const float dec = min( probs[result], probDecrement > 0.0f ? probDecrement : defaultProb );
  const float inc = dec / (float)(outcomesNumber - 1);
  for ( int i = 0; i < probs.size(); ++i )
  {
    if ( i == result )
    {
      probs[i] -= dec;
    }
    else
    {
      probs[i] += inc;
    }
  }
 
  return result;
}

// Remove states that contain invalid pointers (dead objects)
void SmartRandomGenerator::Cleanup()
{
  TRollStates::iterator it = rollStates.begin();
  while( it != rollStates.end() )
  {
    TRollStates::iterator next = it;
    ++next;
    if ( !IsValid(it->first.pFirst) || !IsValid(it->first.pSecond) )
      rollStates.erase( it );
    it = next;
  }

  TRandomStates::iterator it2 = randomStates.begin();
  while( it2 != randomStates.end() )
  {
    TRandomStates::iterator next = it2;
    ++next;
    if ( !IsValid(it2->first.pFirst) || !IsValid(it2->first.pSecond) )
      randomStates.erase( it2 );
    it2 = next;
  }
}

void SmartRandomGenerator::Init( NRandom::RandomGenerator* pRG )
{
  pRandomGen = pRG;
}

}