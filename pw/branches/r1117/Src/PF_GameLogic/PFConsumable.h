#pragma once

#include "../System/NameMap.h"
#include "PFWorldObjectBase.h"

namespace NDb
{
  struct Consumable;
}

namespace NWorld
{

class PFAbilityData;
class PFConsumableAbilityData;
class PFWorld;
class PFBaseUnit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PFConsumable : public PFWorldObjectBase, public NNameMap::Map
{
  WORLD_OBJECT_METHODS(0xF68CC00, PFConsumable);

  NAMEMAP_DECLARE;
public:
  PFConsumable( CPtr<PFWorld> const& pWorld, CPtr<PFBaseUnit> const& pOwner, NDb::Ptr<NDb::Consumable> const& pDBDesc);
  PFConsumable( CObj<PFConsumableAbilityData> const& pAbilityData, int quantity );
  
  CObj<PFConsumableAbilityData>& GetAbility();
  CObj<PFConsumableAbilityData> const& GetAbility() const;
  NDb::Consumable const* GetDBDesc() const;

  int   GetQuantity() const;
  void  SetQuantity(int quantity);
  void  AddQuantity(int adds);
  int   GetMaxQuantity() const;
  int const &GetMoneyCost() const;

  int GetNaftaCost()  const { return GetMoneyCost(); } // for formulas

  bool  CanBeUsed() const;
  bool  IsSpendable() const;

  void SetActionBarIndex( int idx ) { actionBarIndex = idx; }
  int GetActionBarIndex() const { return actionBarIndex; }

  void SetPet( bool v ) { isPet = v; }
  bool IsPet() const { return isPet; }

private:
  PFConsumable();
  
  mutable int moneyCost; // for namemaps, not need to serialize!
  int actionBarIndex;
  bool isPet;
  
  ZDATA_(PFWorldObjectBase)
  ZNOPARENT(NNameMap::Map)
  CObj<PFConsumableAbilityData> pAbilityData;
	NDb::Ptr<NDb::Consumable> pDBDesc;
  int quantity;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pAbilityData); f.Add(3,&pDBDesc); f.Add(4,&quantity); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CObj<PFConsumableAbilityData> const& PFConsumable::GetAbility() const {
  NI_ASSERT(pAbilityData, "Invalid ability!");
  return pAbilityData;
}
inline CObj<PFConsumableAbilityData>& PFConsumable::GetAbility() {
  NI_ASSERT(pAbilityData, "Invalid ability!");
  return pAbilityData;
}
inline NDb::Consumable const* PFConsumable::GetDBDesc() const{
  return pDBDesc;
}
inline int PFConsumable::GetQuantity() const {
  return quantity;
}
inline void PFConsumable::SetQuantity(int quantity_) {
  quantity = quantity_;
}

}
