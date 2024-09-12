#pragma once

#include "PFWorld.h"
#include "PFBaseUnit.h"
#include "PFWorldObjectBase.h"

#include "DBAdvMap.h"
#include "DBConsumable.h"

// Prototype implementation: may be mainbuilding and quarters will be merged into one class later

namespace NGameX 
{ 
	class PFBuilding;
  class PFAnimatedBuilding;
}

namespace NWorld
{

class PFAbilityData;
class PFBaseHero;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBuilding : public PFBaseUnit, public ILogicStatesMapObject
{
	WORLD_OBJECT_METHODS_WITH_CLIENT( 0x2C5BE400, PFBuilding, NGameX::PFBuilding );
public:
  explicit PFBuilding() {}
	explicit PFBuilding(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);
  NDb::ERoute GetRouteId()const { return routeID; }

  bool CanDenyBuilding( CPtr<PFBaseHero>const& pDennier ) const;
  void DenyBuilding( CPtr<PFBaseHero>const& pDennier );
  bool IsDecoration() const {return isDecoration;}

  const vector<SVector> & GetOccupiedTiles() {return occupiedTiles;}
  virtual bool IsInRange( const CVec2& aimerPos, float range ) const;
  virtual float OnHeal(CPtr<PFBaseUnit> pSender, float amount, bool ignoreHealingMods = false );

  virtual void OnAfterReset();
  virtual void Reset();

  virtual void Hide(bool hide);

  const NDb::AdvMapObject& GetAdvMapObjectCopy() const { return dbObjectCopy; }

  void MakeLevelupsForTimeDelta( float dtInSeconds );

  void SetState( const string& newStateName );
protected:
  void Init(NDb::AdvMapObject const& dbObject, NDb::Building const* pDesc, NDb::EUnitType type);
  virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc = 0);
  virtual bool  Step(float dtInSeconds);

  ZDATA_(PFBaseUnit)
  ZNOPARENT(ILogicStatesMapObject)
  NDb::ERoute routeID;
  int   routeLevel;
  bool  isDenying; // !temporary! Do not use it!! (на здании лежит ДоТ пожертвования)
  bool isDecoration;
  ZNOCRC
  ZNOMAPOBJECT
  NDb::AdvMapObject dbObjectCopy; // for marking on tile map
  vector<SVector> occupiedTiles;
  ZNOMAPOBJECTEND
  float levelUpInterval;
  float levelUpTimer;
  ZNOCRCEND
  string stateName;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseUnit*)this); f.Add(2,&routeID); f.Add(3,&routeLevel); f.Add(4,&isDenying); f.Add(5,&isDecoration);  if(!f.IsChecksum()){  if(!IsMapObject()){ f.Add(6,&dbObjectCopy); f.Add(7,&occupiedTiles);  } f.Add(8,&levelUpInterval); f.Add(9,&levelUpTimer);  } f.Add(10,&stateName); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFQuarters : public PFBuilding
{
	WORLD_OBJECT_METHODS_WITH_CLIENT( 0x2C5BE401, PFQuarters, NGameX::PFBuilding );
public:
	explicit PFQuarters() {}
	explicit PFQuarters(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);
	virtual void Reset();
  virtual void OnUnitDie( CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc = 0 );
  ZDATA_(PFBuilding);
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBuilding*)this); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFShop : public PFBuilding
{
  WORLD_OBJECT_METHODS_WITH_CLIENT( 0xF61AC80, PFShop, NGameX::PFBuilding );
public:
  explicit PFShop() {}
  explicit PFShop(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);

  bool IsHeroNear(PFBaseHero const *pMale) const;
	float GetInteractionRadius() const;
  
	NDb::ConsumablesShop const* GetConsumablesShop() const;
  int GetNumConsumables() const;
  NDb::Consumable const* GetConsumableDesc(int item) const;
  bool CanBuyConsumable(PFBaseHero const *pMale, int itemId) const;
	virtual void Reset();
private:
  NDb::Ptr<NDb::Shop> pDesc;
  ZDATA_(PFBuilding)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBuilding*)this); return 0; }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFSimpleBuilding : public PFBuilding
{
  WORLD_OBJECT_METHODS_WITH_CLIENT( 0xF67AC00, PFSimpleBuilding, NGameX::PFBuilding );
public:
  explicit PFSimpleBuilding(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);  
	virtual void Reset();
private:
  explicit PFSimpleBuilding() {}
  ZDATA_(PFBuilding)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBuilding*)this); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFUsableBuilding : public PFBuilding
{
  WORLD_OBJECT_METHODS_WITH_CLIENT( 0xE78B3C82, PFUsableBuilding, NGameX::PFBuilding );
public:
  explicit PFUsableBuilding(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);  
  virtual void Reset();
private:
  explicit PFUsableBuilding() {}
  ZDATA_(PFBuilding)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBuilding*)this); return 0; }
};
}