#pragma once

#include "PFWorld.h"
#include "PFCreep.h"

#include "DBUnit.h"

namespace NGameX 
{ 
  class PFClientCreature; 
  class PFClientSummoned;
}

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creep behaviour
class PFSummonedUnitBehaviour : public PFSummonBehaviour
{
	WORLD_OBJECT_METHODS( 0x9E677A82, PFSummonedUnitBehaviour )
protected:
  PFSummonedUnitBehaviour() {}
  PFSummonedUnitBehaviour( PFBaseMovingUnit* pUnit, const CPtr<PFBaseUnit>& pMaster, const NDb::SummonBehaviourBase* pBehaviourData, float lifeTime, int behaviourFlags = BEHAVIOURFLAGS_NONE );

  ZDATA_(PFSummonBehaviour);
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFSummonBehaviour*)this); return 0; }

  static PFSummonedUnitBehaviour* Create(PFBaseMovingUnit *pUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourData, float lifeTime, int behaviourFlags = BEHAVIOURFLAGS_NONE);
  virtual void AcquireBehaviourDefinedSpawnPosition(Target& spawnPosition) const {} // we have not default spawn position defined in behaviour

  virtual void GetKillerAward(CPtr<PFBaseUnit> pKiller, NaftaAward& award);
  virtual int GetSummonTypeInt() const { return -1; }
  virtual void OnUnitDie( CPtr<PFBaseUnit> pKiller ) { UpdateClientColor(); }
  virtual void UpdateClientColor();

  virtual bool IsInDefaultState() const { return pUnit->IsIdle(); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creep behaviour
class PFSummonedUnitAIBehaviour : public PFSummonedUnitBehaviour, public PFBaseUnitEventListener
{
  WORLD_OBJECT_METHODS( 0xF732442, PFSummonedUnitAIBehaviour )
protected:
  PFSummonedUnitAIBehaviour() {}
  PFSummonedUnitAIBehaviour( PFBaseMovingUnit* pUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase,
    NDb::SummonType summonType, float lifeTime, int behaviourFlags = BEHAVIOURFLAGS_NONE );

  ZDATA_(PFSummonedUnitBehaviour);
  ZNOPARENT(PFBaseUnitEventListener)
  NDb::SummonType       summonType;
  bool                  isSuspended;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFSummonedUnitBehaviour*)this); f.Add(2,&summonType); f.Add(3,&isSuspended); return 0; }

  static PFSummonedUnitAIBehaviour* Create(PFBaseMovingUnit* pUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase,
    NDb::SummonType summonType, float lifeTime, int behaviourFlags = BEHAVIOURFLAGS_NONE );

  NDb::SummonType GetSummonType() const { return summonType; }
  virtual int GetSummonTypeInt() const { return int(summonType); }

  virtual bool OnStep(float dtInSeconds);
  virtual void OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget );
  virtual bool CanSelectTarget( PFBaseUnit const* pTarget, bool mustSeeTarget = false ) const;
  virtual void OnStop();
  virtual void Suspend();
  virtual void Resume();
  virtual void OnDamage(PFBaseUnitDamageDesc const & desc);

  virtual void AcquireBehaviourDefinedSpawnPosition(Target& spawnPosition) const;

  virtual CVec2 GetMasterOffset() const;
  virtual CVec2 GetEscortPosition() const { return pMaster->GetPosition().AsVec2D() + GetMasterOffset(); };

  virtual bool IsEssentialSummon() const { return (behaviourFlags & BEHAVIOURFLAGS_ESSENTIALSUMMON) || summonType == NDb::SUMMONTYPE_PRIMARY; }

  // from Event listener
  virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Summoned unit
class PFBaseSummonedUnit : public PFBaseCreep
{
public:
  PFBaseSummonedUnit( CPtr<PFWorld> const& pWorld, NDb::Creature const* creepObj, NDb::EUnitType unitType, CPtr<PFBaseUnit> const& pMaster, Placement const& placement, bool noSummonAnimation = false, bool _attachGlowEffect = false, bool _openWarFog = true );

  // damage/health/energy methods
  virtual float                   OnDamage(const DamageDesc &desc);
  virtual float                   OnBeforeDamage(const DamageDesc &desc);
  void SetAdditionalDamageParam( float _takeModDmg, NDb::ESpellTarget _takeTypeUnit ) { takeModDmg = _takeModDmg; takeTypeUnit = _takeTypeUnit; }

  virtual NDb::EFaction  GetOriginalFaction() const { return IsValid(GetMasterUnit())? GetMasterUnit()->GetOriginalFaction(): GetFaction(); }
  virtual void OnAfterReset();
  virtual void Reset();
  bool GetOpenWarFog() const { return( openWarFog ); }
  virtual bool             SetSkin( const nstl::string& skinId );
  const NDb::CreepSkin*    GetCreepSkin() const { return pCurrentSkin; }
  virtual const NDb::DbResource* GetSkin() const { return pCurrentSkin; }
  virtual const NDb::UnitDeathParameters* GetDeathParams() const;

  virtual void             OpenWarFog() { if( openWarFog ) PFBaseCreep::OpenWarFog(); }
  virtual void             OpenWarFog(NDb::EFaction _faction, float timeout, float radius) { if( openWarFog ) PFBaseCreep::OpenWarFog( _faction, timeout, radius ); }
  virtual void             CloseWarFog(bool immediately = false) { if( openWarFog ) PFBaseCreep::CloseWarFog( immediately ); }
  virtual void             UpdateWarFog() { if( openWarFog ) PFBaseCreep::UpdateWarFog(); }
protected:
  explicit PFBaseSummonedUnit() {}
  
private:
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x2C641300, PFBaseSummonedUnit, NGameX::PFCreep);
  
  NDb::Ptr< NDb::CreepSkin >   pCurrentSkin;

  virtual void             StepWarFog(float dtInSeconds) { if( openWarFog ) PFBaseCreep::StepWarFog( dtInSeconds ); }
  void MakeClientObject(PFBaseMaleHero* pHero, NDb::Creature const* dbSummonedObj, bool noSummonAnimation = true);


  ZDATA_(PFBaseCreep)
  float takeModDmg;
  NDb::ESpellTarget takeTypeUnit;
  bool attachGlowEffect;
  bool openWarFog;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseCreep*)this); f.Add(2,&takeModDmg); f.Add(3,&takeTypeUnit); f.Add(4,&attachGlowEffect); f.Add(5,&openWarFog); return 0; }
};

} //namespace NWorld