#include "stdafx.h"
#include "PathMap.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
const int VALUE_SCALE = 10;

const SVector offsets[] =
{
	SVector(-1,  0), SVector( 1, 0), SVector(0, -1), SVector(0, 1),
	SVector(-1, -1), SVector(-1, 1), SVector(1, -1), SVector(1, 1)
};

const int lengths[] =
{
	int(1.0 * VALUE_SCALE), int(1.0 * VALUE_SCALE), int(1.0 * VALUE_SCALE), int(1.0 * VALUE_SCALE),
	int(1.41 * VALUE_SCALE), int(1.41 * VALUE_SCALE), int(1.41 * VALUE_SCALE), int(1.41 * VALUE_SCALE)
};
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PathMap::PathMap( const TileMap* _tileMap, const CVec2& pos, int unitRadius, float distance, bool allowDiagonal ) : tileMap( _tileMap )
{
  offset = ( unitRadius - 1 ) * tileMap->GetTileSize();
  SVector startTile = tileMap->GetTile( pos );

  const int maxLength = ceil( distance / tileMap->GetTileSize() );
  bounds.x1 = Max( startTile.x - maxLength, 0 );
  bounds.y1 = Max( startTile.y - maxLength, 0 );
  bounds.x2 = Min( startTile.x + maxLength, tileMap->GetSizeX() );
  bounds.y2 = Min( startTile.y + maxLength, tileMap->GetSizeY() );
  
  map.SetSizes( bounds.Width(), bounds.Height() );
  map.FillEvery( -1 * VALUE_SCALE );
  BuildPathMap( tileMap, startTile, unitRadius, maxLength, allowDiagonal );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PathMap::GetDistance( const CVec2& pos, float& toWalk, float& remaining ) const
{
  const SVector tile = tileMap->GetTile( pos );
  if ( !IsInside( tile ) )
    return false;

  const int length = GetValue( tile );
  if ( length >= 0 )
  {
    toWalk = length * tileMap->GetTileSize() / VALUE_SCALE;
    remaining = 0;
    return true;
  }

  SVector bestTile;
  int bestDist = INT_MAX;
  for( int d = 1; d <= MAX_UNIT_SIZE; ++d )
  {
    for( int dx = -d; dx <= d; ++dx )
    {
      CheckBestTile( SVector( tile.x + dx, tile.y - d ), bestTile, bestDist );
      CheckBestTile( SVector( tile.x + dx, tile.y + d ), bestTile, bestDist );
    }

    for( int dy = -d + 1; dy < d; ++dy )
    {
      CheckBestTile( SVector( tile.x - d, tile.y + dy ), bestTile, bestDist );
      CheckBestTile( SVector( tile.x + d, tile.y + dy ), bestTile, bestDist );
    }
  }

  if ( bestDist == INT_MAX )
    return false;

  toWalk = bestDist * tileMap->GetTileSize() / VALUE_SCALE;
  remaining = fabs( tileMap->GetPointByTile( bestTile ) - pos ) * tileMap->GetTileSize() / VALUE_SCALE + offset;

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PathMap::CheckBestTile( const SVector& tile, SVector& bestTile, int& bestDist ) const
{
  const int dist = GetValue( tile );
  if ( dist >= 0 && dist < bestDist )
  {
    bestTile = tile;
    bestDist = dist;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PathMap::BuildPathMap( const TileMap* tileMap, const SVector& startTile, int unitRadius, int maxLength, bool allowDiagonal )
{
  const int tileToCheck = allowDiagonal ? 8 : 4;

  SetValue( startTile, 0 );
  
  vector<SVector> queue;
  queue.push_back( startTile );
  
  while ( !queue.empty() )
  {
    SVector tile = queue.back();
    queue.pop_back();

    const int length = GetValue( tile );
    for( int i = 0; i < tileToCheck; ++i )
    {
      const int checkLength = length + lengths[i];
      if ( length > maxLength )
        continue;

      const SVector checkTile = tile + offsets[i];
      if ( !IsInside( tile ) )
        continue;

      if ( !tileMap->CanUnitGo( unitRadius, checkTile ) )
        SetValue( checkTile, -1 * VALUE_SCALE );

      const int tileLength = GetValue( checkTile );
      if ( tileLength < 0 || checkLength < tileLength )
      {
        SetValue( checkTile, checkLength );
        queue.push_back( checkTile );
      }
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NWorld
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
