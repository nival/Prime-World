#include "stdafx.h"

#include "PFAdvMapObject.h"
#include "TileMap.h"

namespace NWorld
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void MarkObject(TileMap *pTileMap, NDb::AdvMapObject const& desc, vector<SVector> & tilesToFill, CTRect<int> *pTileRect)
  {
    NI_VERIFY(NULL != pTileMap, "Invalid TileMap", return );
    NI_VERIFY( IsValid( desc.gameObject ), "NDb::AdvMapObject without linked NDb::GameObject", return );
    if (!desc.lockMap)
      return;
    const Placement &place = desc.offset.GetPlace();
    float minScale = desc.gameObject->minLockScale;
    if ((place.scale.x < minScale && place.scale.y < minScale) || place.scale.z < minScale)
      return;
  
    pTileMap->FillOccupiedTiles(tilesToFill, desc.gameObject->collision, desc.gameObject->lockMask.tileSize, desc.gameObject->lockMask.mask, place, pTileRect);
  }
}
