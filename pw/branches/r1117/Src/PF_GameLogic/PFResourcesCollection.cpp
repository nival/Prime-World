/************************************************************************/
/* клиентская имплементация класса PFResources                          */
/************************************************************************/
#include "stdafx.h"
#include "PFResourcesCollectionClient.h"


namespace NWorld
{
  void PFResourcesCollection::CollectConsumables()
  {
    DebugTrace("[ResourceCollection] collect consumables");
    CollectResources( "Items\\", "*.ARCT.xdb", consumables, hashedConsumables );
  }
};

BASIC_REGISTER_CLASS( NWorld::PFResourcesCollection );

