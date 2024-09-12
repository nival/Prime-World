#pragma once

namespace NDb
{
  struct AdvMapObject;
}

namespace NWorld
{
  class TileMap;

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void MarkObject(TileMap *pTileMap, NDb::AdvMapObject const& desc, vector<SVector> & tilesToFill, CTRect<int> *pTileRect = 0);

}