#pragma once

#include "../System/NameMap.h"

#include "PFPickupable.h"
#include "PFConsumable.h"
#include "PFSimpleObject.h"


namespace NDb
{
  struct Consumable;
}

namespace NGameX
{
  class PFClientChest;
}

namespace NWorld
{

class PFBaseHero;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PFConsumableChest : public PFPickupableObjectBase, public NNameMap::Map
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0xF68CB82, PFConsumableChest, NGameX::PFClientChest);
  NAMEMAP_DECLARE;
public:
  static CObj<PFConsumableChest> Create(PFWorld* pWorld, NDb::Ptr<NDb::Consumable> const& dbConsumable, const CVec2& pos, int quantity, NDb::GameObject const* gameObject = NULL);

  virtual bool CanBePickedUpBy( CPtr<PFBaseHero> const& pPicker ) const ;
  virtual void OnPickedUp( const CPtr<PFBaseHero>& pPicker );
	virtual void Reset();

  NDb::Ptr<NDb::Consumable> const& GetConsumableDesc() const;
private:
  PFConsumableChest(PFWorld* pWorld, NDb::Ptr<NDb::Consumable> const& dbConsumable, int quantity, const NDb::AdvMapObject &_dbObject);
  PFConsumableChest() {} // hack for CObj/CPtr support

  const wstring& GetName() const;
  
  ZDATA_(PFPickupableObjectBase);
  ZNOPARENT(NNameMap::Map)
  NDb::Ptr<NDb::Consumable> consumable;
  int                       quantity;
  ZNOCRC
  NDb::AdvMapObject dbObject;
  ZNOCRCEND
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFPickupableObjectBase*)this); f.Add(2,&consumable); f.Add(3,&quantity);  if(!f.IsChecksum()){ f.Add(4,&dbObject);  } return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline NDb::Ptr<NDb::Consumable> const& PFConsumableChest::GetConsumableDesc() const {
  return consumable;
}

}