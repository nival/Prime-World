#pragma once

#include "PFApplicator.h"

namespace NWorld
{

class PFApplSummon;
class PFBaseSummonedUnit;
class PFSummonedUnitBehaviour;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFSummonBehaviourDataBase : public CObjectBase
  {
  WORLD_OBJECT_METHODS(0xF730CC0, PFSummonBehaviourDataBase);
  ZDATA
  ZNOPARENT(CObjectBase)
  CPtr<PFApplSummon> pAppl;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&pAppl); return 0; }

  PFSummonBehaviourDataBase(NDb::SummonBehaviourBase const& dbDesc) {};
  void Initialize(CPtr<PFApplSummon> pAppl_) { pAppl = pAppl_; } 
  virtual PFSummonedUnitBehaviour* CreateBehaviour(CPtr<PFBaseSummonedUnit> const& pSummonedUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourData, float lifeTime, int behaviourFlags) { return CreateDummyBehaviour(pSummonedUnit, pMaster, pBehaviourData, lifeTime, behaviourFlags); };
  virtual NDb::EUnitType GetSummonedUnitType() const { return NDb::UNITTYPE_DUMMYUNIT; }
  
  static PFSummonedUnitBehaviour* CreateDummyBehaviour(CPtr<PFBaseSummonedUnit> const& pSummonedUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase, float lifeTime, int behaviourFlags);

protected:
  PFSummonBehaviourDataBase() {} // for CPtr/CObj support only!
  CPtr<PFApplSummon> const& GetApplicator() const { return pAppl; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFSummonBehaviourDataCommon : public PFSummonBehaviourDataBase
{
  WORLD_OBJECT_METHODS(0xF730CC1, PFSummonBehaviourDataCommon);
public:
  PFSummonBehaviourDataCommon(NDb::SummonBehaviourCommon const& dbDesc) : PFSummonBehaviourDataBase(dbDesc), dbDesc(&dbDesc) {}
  virtual PFSummonedUnitBehaviour* CreateBehaviour(CPtr<PFBaseSummonedUnit> const& pSummonedUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase, float lifeTime, int behaviourFlags);
  virtual NDb::EUnitType GetSummonedUnitType() const;

protected:
  PFSummonBehaviourDataCommon() {} // for CPtr/CObj support only!

  ZDATA_(PFSummonBehaviourDataBase)
  ZNOCRC
  NDb::Ptr<NDb::SummonBehaviourCommon> dbDesc;
  ZNOCRCEND
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFSummonBehaviourDataBase*)this);  if(!f.IsChecksum()){ f.Add(2,&dbDesc);  } return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplSummon: public DBLinker<PFBaseApplicator, NDb::SummonApplicator>
{
  WORLD_OBJECT_METHODS(0xF730B00, PFApplSummon)
  PFApplSummon() {} // for CPtr/CObj support only!

  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplSummon(PFApplCreatePars const &cp) : Base(cp)
  {
    // fatal
    //NI_ASSERT(GetDB().creepTerrainNeutral, "Missing creep for summon applicator, please specify some");
  }

  virtual bool Start();
  virtual bool Step(float dtInSeconds) { return true; }

  virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
  virtual int GetAcceptableUnitTypeFlags() const { return NDb::SPELLTARGET_HEROMALE | NDb::SPELLTARGET_SUMMON |
    NDb::SPELLTARGET_CREEP | NDb::SPELLTARGET_SIEGECREEP | NDb::SPELLTARGET_ALLNEUTRALS | NDb::SPELLTARGET_FACTIONCHAMPION; }

  unsigned int GetFlags() const { return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplCloneHero: public DBLinker<PFBaseApplicator, NDb::CloneHeroApplicator>
{
	WORLD_OBJECT_METHODS(0x9E7243C0, PFApplCloneHero);
protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFApplCloneHero(PFApplCreatePars const &cp) : Base(cp) {}
	PFApplCloneHero() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
	virtual bool Start();
	virtual bool Step(float dtInSeconds)
	{
		NI_ALWAYS_ASSERT("Must not get here");
		return true;
	}

	virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
	virtual int GetAcceptableUnitTypeFlags() const { return NDb::SPELLTARGET_HEROMALE | NDb::SPELLTARGET_HEROFEMALE; }
};

}

