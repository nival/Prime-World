#pragma once

#include "PFWorldObjectBase.h"
#include "PFLogicObject.h"

namespace NWorld
{

class TriggerMarkerHandler : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS( 0xEF94A3C0, TriggerMarkerHandler );
  
private:
  TriggerMarkerHandler() {}

  // Functor
  struct UnitAccumulatorFunctor : public NonCopyable
  {
    int counterUnitFaction[3];
    CVec2         pos;
    float         range;
    NDb::ESpellTarget targetType;

    UnitAccumulatorFunctor( const CVec2 &pos_, float range_, NDb::ESpellTarget _targetType )
    : pos(pos_), range(range_), targetType(_targetType)
    {
      counterUnitFaction[ NDb::FACTION_NEUTRAL ] = 0;
      counterUnitFaction[ NDb::FACTION_FREEZE ] = 0;
      counterUnitFaction[ NDb::FACTION_BURN ] = 0;
    } 

    void operator()( NWorld::PFLogicObject& unit )
    {
      if ( unit.IsInRange( pos, range ) && (targetType & (1L << unit.GetUnitType())) != 0 ) 
        counterUnitFaction[unit.GetFaction()]++;
    }

    int operator [] (int i) { return counterUnitFaction[i]; }
  };

  struct areaState
  {
    int current;
    int previous;
  };

  typedef hash_map< string, vector< areaState > > ActiveStates;

  ZDATA_(PFWorldObjectBase)
  NDb::Ptr<NDb::AdvMapSettings> advMapSettings;
  ActiveStates activeStates;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&advMapSettings); f.Add(3,&activeStates); return 0; }

  TriggerMarkerHandler( PFWorld* pWorld, NDb::AdvMapSettings const * _advMapSettings );

  virtual bool Step(float dt);
 };
} // namespace NWorld
