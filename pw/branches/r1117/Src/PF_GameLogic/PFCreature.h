#pragma once

#include "PFBaseMovingUnit.h"

namespace NGameX { class PFClientCreature; };
namespace NDb { struct AnimSet; enum EAnimStates; }

namespace NWorld
{

class PFCreature : public PFBaseMovingUnit
{  
  WORLD_OBJECT_METHODS_WITH_CLIENT( 0x2C63F440, PFCreature, NGameX::PFClientCreature);
protected:
  PFCreature() {}

  bool Step(float dtInSeconds);
  virtual void Reset();
  virtual void OnAfterReset();
  virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc = 0);

  virtual void RemoveCorpse();
  void PlaceSkeleton(bool playOnUnitDieEffect = true);

  ZDATA_(PFBaseMovingUnit);
  float                     deadUnitLifeTime;           // time offset then corpse would be destroyed
  float                     unitFallUndergroundOffset;  // time offset then skeleton would be placed in place of unit death
  float                     observingTimeOffset;
  float                     forcedAnimationTimeLeft;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnit*)this); f.Add(2,&deadUnitLifeTime); f.Add(3,&unitFallUndergroundOffset); f.Add(4,&observingTimeOffset);  f.Add(5,&forcedAnimationTimeLeft); return 0; }
  PFCreature(PFWorld* pWorld, const CVec3 &pos, const CVec2 & direction, const NDb::Creature &unitDesc);

  int ReplaceAnimSet( NDb::Ptr<NDb::AnimSet> pSet );
  void RollbackAnimSet( int setId );

  virtual bool GetOpenWarFog() const { return( true ); }

  int  ReplaceAnimation( NDb::EAnimStates state, char const* name, char const* marker, bool upper, bool affectAllSets);
  int  ReplaceAnimation( char const* oldName, char const* name, char const* marker, bool upper, bool affectAllSets);
  void RollbackAnimation( NDb::EAnimStates state, int id, bool upper);
  void RollbackAnimation( char const* oldName, int id, bool upper);

  virtual void OnRessurect();
  virtual bool UpdateClientColor();
  
  virtual CObj<IPFState>  InvokeAbility(int id, Target const &target);
	
  virtual void            OnAbilityDispatchStarted(PFAbilityData const* pData) const;

  virtual bool CanObserveNature() const { return !IsDead() || (observingTimeOffset >= 0); }

  void ForceAnimation( const string& anim, int loopCount );
  void StopForcedAnimation( bool checkForcedAnimTime = true );

};

class PFCreatureUseAbilityState : public PFBaseUnitUseAbilityState
{
  WORLD_OBJECT_METHODS(0xF5CC389, PFCreatureUseAbilityState)
public:
	PFCreatureUseAbilityState(CPtr<PFWorld> const& pWorld, CPtr<PFCreature> const& pOwner, int id, Target const &target);
protected:
	virtual void OnEnter();
  virtual int  GetNumSubStates() const;
	PFCreatureUseAbilityState() {}
protected:
	ValueWithModifiers abilityRange;

	ZDATA_(PFBaseUnitUseAbilityState)
  CPtr<PFCreature> pCreature;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseUnitUseAbilityState*)this); f.Add(2,&pCreature); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFCreatureResurrectEvent : public PFBaseUnitEvent
{
public:
	PFCreatureResurrectEvent() : PFBaseUnitEvent(NDb::BASEUNITEVENT_RESURRECT) {}
};

}