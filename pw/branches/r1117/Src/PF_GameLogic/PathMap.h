#pragma once

#include "TileMap.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PathMap
{
public:
	PathMap( const TileMap* tileMap, const CVec2& pos, int unitRadius, float distance, bool allowDiagonal );

	// get distance to the requested point; returns 'false' when destination point is unreachable;
	// 'toWalk' is possible length of path, 'remaining' is a distance from path end point to
	// 'pos' (> 0 when destination is not reachable directly)
	bool GetDistance( const CVec2& pos, float& toWalk, float& remaining ) const;

private:
  ConstPtr<TileMap> tileMap;
  CTRect<int> bounds;
  CArray2D<int> map;
  float offset;

  bool IsInside( const SVector& tile ) const { return bounds.IsInside( tile.x, tile.y ); }
  
  int GetValue( const SVector& tile ) const { return map.Get( tile.x - bounds.x1, tile.y - bounds.y1 ); }
  void SetValue( const SVector& tile, int value ) { map.Set( tile.x - bounds.x1, tile.y - bounds.y1, value ); }

  void CheckBestTile( const SVector& tile, SVector& bestTile, int& bestDist ) const;

  void BuildPathMap( const TileMap* tileMap, const SVector& startTile, int unitRadius, int maxLength, bool allowDiagonal );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NWorld