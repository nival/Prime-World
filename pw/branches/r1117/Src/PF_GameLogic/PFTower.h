#pragma once

#include "PFWorld.h"
#include "PFBaseUnit.h"
#include "PFWorldObjectBase.h"
#include "PFBuildings.h"
#include "PFBattleBuilding.h"

namespace NCore { class WorldCommandQueue; }

namespace NGameX 
{ 
  class PFTower; 
}

namespace NWorld
{

class PFTower : public PFBattleBuilding
{
	WORLD_OBJECT_METHODS_WITH_CLIENT(0x2C5BE303, PFTower, NGameX::PFTower)

public:
	explicit PFTower(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);  
  ~PFTower();

	virtual void Reset();

protected:
  explicit PFTower() { type = NDb::UNITTYPE_TOWER; }
  
  virtual bool  Step(float dtInSeconds);
  virtual float OnDamage(const DamageDesc &desc);
  virtual void  OnScream( const CPtr<PFBaseUnit> pTarget, ScreamTarget::ScreamType st );
  virtual void  OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc);
    
  virtual void  OnTargetAssigned();
  virtual void  OnTargetDropped();
  
  ZDATA_(PFBattleBuilding);
  float            screamCooldown;
	NDb::Ptr<NDb::Tower> pDesc;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBattleBuilding*)this); f.Add(2,&screamCooldown); f.Add(3,&pDesc); return 0; }
};

class PFControllableTower : public PFTower
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x2C6C1341, PFControllableTower, NGameX::PFTower)

  explicit PFControllableTower() { type = NDb::UNITTYPE_TOWER; }
  ZDATA_(PFTower)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFTower*)this); return 0; }

  explicit PFControllableTower(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);  
protected:

  virtual bool  Step(float dtInSeconds);
  virtual float OnDamage(const DamageDesc &desc);
  virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc = 0);
  virtual void  OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget );
  virtual void  OnScream( const CPtr<PFBaseUnit> pTarget, ScreamTarget::ScreamType st );
};

class PFFountain : public PFBuilding
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0xF61A401, PFFountain, NGameX::PFBuilding)

public:
  explicit PFFountain() { type = NDb::UNITTYPE_BUILDING; }
  explicit PFFountain(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);

	virtual void Reset();

protected:
  virtual void OnDestroyContents();
  virtual void OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget );

  ZDATA_(PFBuilding)
	NDb::Ptr<NDb::Fountain> pDesc;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBuilding*)this); f.Add(2,&pDesc); return 0; }
};

}
