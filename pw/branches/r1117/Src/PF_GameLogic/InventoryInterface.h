#pragma once

namespace NDb
{
  struct Consumable;
};


namespace NWorld
{

class PFConsumable;


_interface IInventory : public IObjectBase
{
   virtual int GetSlotCount() const = 0;
   virtual const PFConsumable * GetConsumable( int slot ) const = 0;
   virtual bool CanAddItem( const NDb::Consumable * dbItem, int quantity ) const = 0;
   virtual bool CanUseConsumables() const = 0;
};

}
