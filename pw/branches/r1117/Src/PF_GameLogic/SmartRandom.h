#pragma once

namespace NRandom
{
  class RandomGenerator;
}

namespace NWorld
{

class PFLogicObject;

class SmartRandomGenerator
{
  struct RollState
  {
    RollState() : failReps(0), successReps(0) {}
    ZDATA
    int failReps;
    int successReps;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&failReps); f.Add(3,&successReps); return 0; }
  };

  struct RandomState
  {
    ZDATA
    vector<float> probs;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&probs); return 0; }
  };

  struct StateKey
  {
    StateKey() : key(0), first(0), second(0) {}
    StateKey( const int key, const PFLogicObject* pFirst, const PFLogicObject* pSecond );

    // Note: this operator is not used by map algorithms
    bool operator==( StateKey const& other ) const
    {
      return key == other.key && first == other.first && second == other.second;
    }

    bool operator<( StateKey const& other ) const;

    ZDATA
    ConstPtr<PFLogicObject> pFirst;
    ConstPtr<PFLogicObject> pSecond;
    int first;
    int second;
    int key;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&pFirst); f.Add(3,&pSecond); f.Add(4,&first); f.Add(5,&second); f.Add(6,&key); return 0; }
  };

  typedef map<StateKey,RollState> TRollStates;
  typedef map<StateKey,RandomState> TRandomStates;

  NRandom::RandomGenerator* pRandomGen;

  ZDATA
  TRollStates rollStates;
  TRandomStates randomStates;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&rollStates); f.Add(3,&randomStates); return 0; }

  bool Roll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond, int key );
  int Random( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond, int key );
  void Cleanup();
  void Init( NRandom::RandomGenerator* pRG );
};


}