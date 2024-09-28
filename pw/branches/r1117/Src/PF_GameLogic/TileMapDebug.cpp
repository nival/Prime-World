#include "stdafx.h"

#include "PFWorld.h"
#include "TileMap.h"
#include "../Terrain/Terrain.h"
#include "../Scene/RenderableScene.h"

namespace 
{
const Render::Color layerColors[] =
{
  Render::Color(   0,   0,   0 ),    // 0000   
  Render::Color( 255,   0,   0 ),    // 0001   
  Render::Color(   0, 255,   0 ),    // 0010   
  Render::Color( 255, 255,   0 ),    // 0011   
  Render::Color(   0,   0, 255 ),    // 0100   
  Render::Color( 255,   0, 255 ),    // 0101   
  Render::Color(   0, 255, 255 ),    // 0110   
  Render::Color( 255, 255, 255 ),    // 0111   
  Render::Color(   0, 128,   0 ),    // 1000   
  Render::Color( 255, 255,   0 ),    // 1001   
  Render::Color( 255, 255,   0 ),    // 1010   
  Render::Color( 255, 255,   0 ),    // 1011   
  Render::Color(   0, 255, 255 ),    // 1100   
  Render::Color( 255, 255, 255 ),    // 1101   
  Render::Color(   0, 255, 255 ),    // 1110   
  Render::Color( 255, 255, 255 ),    // 1111   
};

int g_showTiles = 0;

void UpdateMinMaxTile( const NWorld::TileMap* tileMap, const CVec2& point, SVector& min, SVector& max )
{
  const SVector tile = tileMap->GetTile( point );
  min.x = Min( min.x, tile.x );
  min.y = Min( min.y, tile.y );
  max.x = Max( max.x, tile.x );
  max.y = Max( max.y, tile.y );
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NGameX
{
// NOTE: here we using knowledge of internal TileMap organization;
// is TileMap layout will be changed, this code should be also modified

void DrawMapDebug( NWorld::PFWorld* pWorld )
{
  if ( g_showTiles == 0 )
    return;

  // other g_showTiles values are treated as bitmask
  const NScene::IScene* scene = pWorld->GetScene();
  if ( !scene )
    return;

  const FrustumIntersection& fi = scene->GetRenderScene()->GetCameraFrustumIntersection();
  const NWorld::TileMap* tileMap = pWorld->GetTileMap();

  SVector min, max;
  min = max = tileMap->GetTile( fi.points[0] );
  UpdateMinMaxTile( tileMap, fi.points[1], min, max );
  UpdateMinMaxTile( tileMap, fi.points[2], min, max );
  UpdateMinMaxTile( tileMap, fi.points[3], min, max );
  min.x = Max( 0, min.x );
  min.y = Max( 0, min.y );
  max.x = Min( tileMap->GetSizeX() - 1, max.x );
  max.y = Min( tileMap->GetSizeY() - 1, max.y );

  const float pointSize = tileMap->GetTileSize() * 0.25f;
  const Terrain::TerrainHeightManager& heights = scene->GetTerrain()->GetHeightManager();

  for ( int x = min.x; x <= max.x; x++ )
  {
    for ( int y = min.y; y < max.y; y++ )
    {
      int result = 0;
      int mode = 1;
      for( int i = 0; i < 4; ++i, mode <<= 1 )
      {
        if ( !tileMap->CanUnitGoDebug( x, y, mode, g_showTiles ) )
          result |= mode;
      }

      if ( result == 0 )
        continue;

      CVec3 point;
      point.Set( tileMap->GetPointByTile( x, y ) );
      point.z = heights.GetHeightFast( point.x, point.y );
      Render::DebugRenderer::DrawPoint3D( point, pointSize, layerColors[result], false );
    }
  }
}

} // namespace

REGISTER_DEV_VAR( "show_tiles",   g_showTiles,   STORAGE_NONE );
