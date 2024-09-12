#include "stdafx.h"

#include "../Terrain/Terrain.h"
#include "HeightsController.h"
#include "CollisionHull.h"
#include "GeometryTracer.h"
#include "../System/ChunklessSaver.h"
#include "../Render/debugrenderer.h"
#include "PointSelector.h"
#include "../System/lerp.h"
#include "../System/InlineProfiler.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline static void ResetHeight( float* pHeight )
{
	if ( pHeight )
		*pHeight = 0.0f;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline static void ResetNormal( CVec3* pNormal )
{
	if ( pNormal )
	{
		pNormal->x = 0.0f;
		pNormal->y = 0.0f;
		pNormal->z = 1.0f;
	}
}

namespace
{
  ///< debug var to drawing intersected point
  bool gDrawTerrainPick = false;
  REGISTER_DEV_VAR( "draw_terrain_pick", gDrawTerrainPick, STORAGE_NONE );

  static NDebug::PerformanceDebugVar terrain_Intersect( "Intersect()", "Terrain", 10, 10, true );
  static NDebug::StringDebugVar terrain_Pick("Pick", "Terrain");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TerrainLayerHeight
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TerrainLayerHeight : public HeightsController::ILayerHeights
{
	OBJECT_METHODS( 0x49561C00, TerrainLayerHeight );
	Terrain::Terrain* pTerrain;

	TerrainLayerHeight() : pTerrain( 0 ) { }

public:
	TerrainLayerHeight( Terrain::Terrain* _pTerrain ) : pTerrain( _pTerrain ) { }

	void Update() { }
  #ifndef VISUAL_CUTTED
  	int GetVersion() const { return pTerrain->GetHeightsCounter(); }
  #else  	
    int GetVersion() const { return 0; }
  #endif  	
	bool GetHeight( const float x, const float y, float* pHeight, CVec3* pNormal ) const
	{
	//	ResetNormal( pNormal );
	  #ifndef VISUAL_CUTTED
		return pTerrain->GetHeight( x, y, pHeight, pNormal );
		#else
		  return 0;
		#endif
	}

  void Load(const nstl::string& filename) {}
  void Save(const nstl::string& filename) {}

	void AddObject( CollisionHull* pHull ) { }
	void RemoveObject( CollisionHull* pHull ) { }

  virtual void Clear(int layer) { }

	bool IsTerrainLayer() const { return true; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ObjectsLayerHeight
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SVectorHash
{
	int operator()( const SVector &a ) const { return ( a.x << 12 ) + a.y; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ObjectsLayerHeight : public HeightsController::ILayerHeights
{
	OBJECT_METHODS( 0x49561C40, ObjectsLayerHeight );

	typedef hash_map<SVector, float, SVectorHash> THeightsMap;
	THeightsMap heights;
	float tileSize;

	void TraceCollisionGeometry( CollisionHull * pHull );
public:
	ObjectsLayerHeight() : tileSize(TERRAIN_TILE_SIZE) { }

	void Update() {}
	int GetVersion() const { return 0; }
	bool GetHeight( const float _x, const float _y, float* pHeight, CVec3* pNormal ) const
	{
		ResetNormal( pNormal );

		int x = floor( _x / tileSize );
		int y = floor( _y / tileSize );

		THeightsMap::const_iterator it = heights.find( SVector( x, y ) );
		if ( it != heights.end() )
		{
			*pHeight = it->second;
			return true;
		}

		return false;
	}

	void AddObject( CollisionHull* pHull ) 
	{
		TraceCollisionGeometry( pHull );
	}
	void RemoveObject( CollisionHull* pObject ) {}

  void Load(const nstl::string& filename) 
  {
    CObj<Stream> pStream = RootFileSystem::OpenFile( filename, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    if( !pStream || !pStream->IsOk() )
    {
      return;
    }

    CObj<IBinSaver> pSaver = CreateChunklessSaver( pStream, 0, true );
    heights.clear();
    pSaver->Add(1, &heights);
 
  }
  void Save(const nstl::string& filename) 
  {
    CObj<Stream> pStream = RootFileSystem::OpenFile( filename, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
    NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open object heights layer file for writing %s", filename ), return );

    pStream->SetSize( heights.size() * 32 );
    CObj<IBinSaver> pSaver = CreateChunklessSaver( pStream, 0, false );
    pSaver->Add(1, &heights);
  }

	bool IsTerrainLayer() const { return false; }

  void Clear( int layer ) { heights.clear(); }

  static const float TERRAIN_TILE_SIZE;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float ObjectsLayerHeight::TERRAIN_TILE_SIZE = 1.0f;

static int IntersectTrinagle( const CVec3& orig, const CVec3& dir, 
                       const CVec3& vert0, const CVec3& vert1, const CVec3& vert2, 
                       float* t, float *u, float *v )
{
  static const float EPSILON = 0.001f;

#define CROSS(dest, v1, v2) \
  dest.x = v1.y*v2.z-v1.z*v2.y; \
  dest.y = v1.z*v2.x-v1.x*v2.z; \
  dest.z = v1.x*v2.y-v1.y*v2.x; \

  CVec3 edge1, edge2, tvec, pvec, qvec;
  float det, inv_det;

  edge1 = vert1-vert0;
  edge2 = vert2-vert0;

  CROSS( pvec, dir, edge2 );
  det = edge1.Dot( pvec );

  if ( det > -EPSILON && det < EPSILON )
    return 0;

  inv_det = 1.0f/det;

  tvec = orig-vert0; 
  *u = tvec.Dot(pvec)*inv_det;
  if ( *u < 0.0f || *u > 1.0f )
    return 0;

  CROSS( qvec, tvec, edge1 );
  *v = dir.Dot(qvec)*inv_det;
  if ( *v < 0.0f || *v + *u > 1.0f )
    return 0;

  *t = edge2.Dot(qvec) * inv_det;
#undef CROSS
  return 1;
}

static int SortByZ( const void* _A, const void* _B )
{
  const TriangleRef* a1 = (const TriangleRef*) _A;
  const TriangleRef* a2 = (const TriangleRef*) _B;
  float z1 = a1->point1.z;
  float z2 = a2->point1.z;

  if ( a1->point2.z > z1 )
    z1 = a1->point2.z;
  if ( a2->point2.z > z2 )
    z2 = a2->point2.z;

  if ( a1->point3.z > z1 )
    z1 = a1->point3.z;
  if ( a2->point3.z > z2 )
    z2 = a2->point3.z;

  if ( z1 < z2 ) return -1;
  else if ( z1 == z2 ) return 0;
  return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectsLayerHeight::TraceCollisionGeometry( CollisionHull * pHull )
{
	SBound bounds;
	pHull->GetGeometry()->GetTransformedBounds( &bounds,  pHull->GetPosition() );

	int minx = floor( ( bounds.s.ptCenter.x - bounds.ptHalfBox.x ) / tileSize );
	int miny = floor( ( bounds.s.ptCenter.y - bounds.ptHalfBox.y ) / tileSize );

	int maxx = ceil( ( bounds.s.ptCenter.x + bounds.ptHalfBox.x ) / tileSize );
	int maxy = ceil( ( bounds.s.ptCenter.y + bounds.ptHalfBox.y ) / tileSize );

  nstl::vector<TriangleRef> triangles;
  triangles.resize( pHull->GetGeometry()->GetTriangles().size() );
  GeometryTracer util;
  CVec3 dir( 0.0f, 0.0f, -1.0f );
  for ( int i = 0; i < triangles.size(); i++ )
  {
    util.GetTriangle( &triangles[i], pHull->GetGeometry()->GetTriangles()[i], pHull->GetGeometry()->GetPoints(), 
      pHull->GetGeometry()->GetEdges(), pHull->GetPosition() );
  }

  qsort( &triangles[0], triangles.size(), sizeof(TriangleRef), SortByZ );

  TriangleRef& tricache = triangles[0];

  for ( int x = minx; x <= maxx; ++x )
  {
    for ( int y = miny; y <= maxy; ++y )
    {
      CVec3 origin( x * tileSize, y * tileSize, 100.f );
      float tFactor = 1e38f;
      bool isIntersect = false;

      //try cache
      {
        float t = 0;
        float u = 0;
        float v = 0;

        if ( IntersectTrinagle(origin, dir, tricache.point1, tricache.point2, tricache.point3, &t, &u, &v) )
        {
          tFactor = Min( tFactor, t );
          isIntersect = true;
        }
      }

      //cache mismatch
      if ( !isIntersect )
      {
        for ( int i = 0; i < triangles.size(); i++ )
        {
          float t = 0;
          float u = 0;
          float v = 0;

          if ( triangles[i].point1.x < origin.x && triangles[i].point2.x < origin.x && triangles[i].point3.x < origin.x )
            continue;
          if ( triangles[i].point1.x > origin.x && triangles[i].point2.x > origin.x && triangles[i].point3.x > origin.x )
            continue;
          if ( triangles[i].point1.y < origin.y && triangles[i].point2.y < origin.y && triangles[i].point3.y < origin.y )
            continue;
          if ( triangles[i].point1.y > origin.y && triangles[i].point2.y > origin.y && triangles[i].point3.y > origin.y )
            continue;

          if ( IntersectTrinagle(origin, dir, triangles[i].point1, triangles[i].point2, triangles[i].point3, &t, &u, &v) )
          {
            tFactor = Min( tFactor, t );
            isIntersect = true;
            tricache = triangles[i];
            break;
          }
        }
      }

      if ( isIntersect )
      {
        float height = 100.0f-tFactor;

        heights[ SVector( x, y ) ] = height;

        for ( int dx = -1; dx <= 1; ++dx )
          for ( int dy = -1; dy <= 1; ++dy )
          {
            if ( heights.find( SVector( x + dx, y + dy ) ) == heights.end() )
              heights[ SVector( x + dx, y + dy ) ] = height; 
          }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LayerInfo
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeightsController::LayerInfo::Set( ILayerHeights* _pLayerHeights )
{
	pLayerHeights = _pLayerHeights;
	UpdateVersion();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeightsController::LayerInfo::Reset()
{
	pLayerHeights = 0;
	version = -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HeightsController::LayerInfo::UpdateVersion()
{
	if ( IsValid( pLayerHeights ) && version != pLayerHeights->GetVersion() )
	{
		pLayerHeights->Update();
		version = pLayerHeights->GetVersion();
		return true;
	}

	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HeightsController
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeightsController::Initialize( const int layersCount )
{
	layers.resize( layersCount );
	for( vector<LayerInfo>::iterator it = layers.begin(); it != layers.end(); ++it )
		it->Reset();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeightsController::AddTerrainToLayer( const int layer, Terrain::Terrain* pTerrain )
{
	NI_VERIFY( layer >= 0 && layer < layers.size(), NStr::StrFmt( "Invalid layer index %d. Total layers %d", layer, layers.size() ), return );
	NI_VERIFY( IsValid( pTerrain ), "Invalid terrain", return );
	
  layers[layer].Set( new TerrainLayerHeight( pTerrain ) );
  this->pTerrain = pTerrain;
	++version;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
void HeightsController::AddObjectToLayer( const int layer, CollisionHull* pHull )
{
	NI_VERIFY( layer >= 0 && layer < layers.size(), NStr::StrFmt( "Invalid layer index %d. Total layers %d", layer, layers.size() ), return );
	NI_VERIFY( !IsValid( layers[layer].pLayerHeights ) || !layers[layer].pLayerHeights->IsTerrainLayer(),
		NStr::StrFmt( "Layer %d already has terrain heights manager", layer ), return );

	if ( !IsValid( layers[layer].pLayerHeights ) )
		layers[layer].Set( new ObjectsLayerHeight() );

	layers[layer].pLayerHeights->AddObject( pHull );
	++version;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
void HeightsController::RemoveObject( CollisionHull* pHull )
{
	for( vector<LayerInfo>::iterator it = layers.begin(); it != layers.end(); ++it )
	{
		if ( IsValid( it->pLayerHeights ) )
		{
			it->pLayerHeights->RemoveObject( pHull );
		}
	}
}

bool HeightsController::GetHeight( const float x, const float y, int layer, float* pHeight, CVec3* pNormal ) const
{
  NI_PROFILE_HEAVY_FUNCTION
  
  int _x = floor( x/ObjectsLayerHeight::TERRAIN_TILE_SIZE );
  int _y = floor( y/ObjectsLayerHeight::TERRAIN_TILE_SIZE );

  bool res = _GetHeight( _x, _y, layer, pHeight, pNormal );
  float h1 = *pHeight;
  float h2 = 0.0f;
  float h3 = 0.0f;
  float h4 = 0.0f;
  _GetHeight( _x+1, _y, layer, &h2, 0 );
  _GetHeight( _x, _y+1, layer, &h3, 0 );
  _GetHeight( _x+1, _y+1, layer, &h4, 0 );

  *pHeight = BiLerp( h1, h2, h3, h4, x-_x, y-_y);

  return res;
}

bool HeightsController::GetHeightByTile( const int tileX, const int tileY, int layer, float* pHeight, CVec3* pNormal ) const
{
  Terrain::GridConstants const& params = pTerrain->GetGridConstants();
  return GetHeight( ((float)tileX + 0.5f) * params.metersPerTile, ((float)tileY + 0.5f) * params.metersPerTile, layer, pHeight, pNormal );
}

bool HeightsController::GetHeightsOfSquareArea( int sideInTiles, float x, float y, float& u, float& v, float result[] ) const
{
   NI_VERIFY( sideInTiles > 0, "Area side must be positive!", return false );
 
   const Terrain::GridConstants& params = pTerrain->GetGridConstants();

   int mapSize = Min( params.sizeInTiles.x, params.sizeInTiles.y );
   NI_VERIFY( mapSize > 0, "Map size is 0?!", return false );
   NI_VERIFY( sideInTiles < mapSize, "Given area is larger then a map! Setting sideInTiles to %d!", return false );
 
   int nTileX = x / params.metersPerTile;
   int nTileY = y / params.metersPerTile;
 
   int nBeginTileX = nTileX - ( sideInTiles - 1 ) / 2;
   int nBeginTileY = nTileY - ( sideInTiles - 1 ) / 2;
 
   if ( nBeginTileX < 0 )
   {
     nBeginTileX = 0;
   }
   if ( nBeginTileY < 0 )
   {
     nBeginTileY = 0;
   }
 
   if ( nBeginTileX > params.sizeInTiles.x - sideInTiles )
   {
     nBeginTileX = params.sizeInTiles.x - sideInTiles;
   }
   if ( nBeginTileY > params.sizeInTiles.y - sideInTiles )
   {
     nBeginTileY = params.sizeInTiles.y - sideInTiles;
   }
 
   u = x / params.metersPerTile - nTileX;
   v = y / params.metersPerTile - nTileY;
 
   NI_VERIFY( ( u >= 0 ) && ( u <= 1 ), "Wrong u", return false );
   NI_VERIFY( ( v >= 0 ) && ( v <= 1 ), "Wrong v", return false );
 
   for ( int i = 0; i < sideInTiles + 1; i++ )
   {
     for ( int j = 0; j < sideInTiles + 1; j++ )
     {
       float curX = ( nBeginTileX + j ) * params.metersPerTile;
       float curY = ( nBeginTileY + i ) * params.metersPerTile;
       bool curResult = GetHeight( curX, curY, 1, &result[i * ( sideInTiles + 1 ) + j], 0 );
       NI_VERIFY( curResult, NStr::StrFmt( "Failed to get height in point [%f,%f] )", curX, curY ), return false );
     }
   }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HeightsController::_GetHeight( const float x, const float y, int layer, float* pHeight, CVec3* pNormal ) const
{
	NI_VERIFY( layer >= 0 && layer < layers.size(), NStr::StrFmt( "Invalid layer index %d. Total layers %d", layer, layers.size() ), return false );
	if ( !IsValid( layers[layer].pLayerHeights ) )
	{
    if ( !IsValid( layers[0].pLayerHeights ) )
    {
		  ResetHeight( pHeight );
		  ResetNormal( pNormal );
		  return false;
    }
    else
    {
      layer = 0;
    }
	}

	static float tempHeight;
	static CVec3 tempNormal;

	const bool result = layers[layer].pLayerHeights->GetHeight( x, y, pHeight ? pHeight : &tempHeight, pNormal ? pNormal : &tempNormal );
	if ( !result )
	{
		if ( layer != 0 && !layers[layer].pLayerHeights->IsTerrainLayer() )
			return layers[0].pLayerHeights->GetHeight( x, y, pHeight, pNormal );

		ResetHeight( pHeight );
		ResetNormal( pNormal );
		return false;
	}

  // Add terrain height
//   if ( layer == 1 )
//   {
//     const bool result2 = layers[0].pLayerHeights->GetHeight( x, y, &tempHeight, &tempNormal );
//     if ( result2 )
//     {
//       *pHeight += tempHeight;
//     }
//   }

	return true;	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeightsController::Update()
{
	for( vector<LayerInfo>::iterator it = layers.begin(); it != layers.end(); ++it )
	{
		if ( it->UpdateVersion() )
			++version;
	}
}

int HeightsController::GetVersion() const
{
	return version;
}

void HeightsController::LoadObjectLayer( int layer, const nstl::string& filename )
{
  NI_VERIFY( layer >= 0 && layer < layers.size(), NStr::StrFmt( "Invalid layer index %d. Total layers %d", layer, layers.size() ), return );
  if ( !IsValid( layers[layer].pLayerHeights ) )
    layers[layer].Set( new ObjectsLayerHeight() );

  layers[layer].pLayerHeights->Load(filename);
}

void HeightsController::SaveObjectLayer( int layer, const nstl::string& filename )
{
  NI_VERIFY( layer >= 0 && layer < layers.size(), NStr::StrFmt( "Invalid layer index %d. Total layers %d", layer, layers.size() ), return );
  if ( IsValid( layers[layer].pLayerHeights ) )
    layers[layer].pLayerHeights->Save( filename );
}

void HeightsController::ClearHeightMapLayer( int layer )
{
  NI_VERIFY( layer >= 0 && layer < layers.size(), NStr::StrFmt( "Invalid layer index %d. Total layers %d", layer, layers.size() ), return );
  if ( IsValid( layers[layer].pLayerHeights ) )
    layers[layer].pLayerHeights->Clear( layer );
}

bool HeightsController::Intersect( CVec3* pIntersection, const CRay& ray ) const
{
  NI_VERIFY( pIntersection, "Invalid result storage!", return false; );
  NDebug::PerformanceDebugVarGuard profile(terrain_Intersect, false);

  const CVec3 geometryBasis = VNULL3;

  CVec2 point( ray.ptOrigin.x - geometryBasis.x, ray.ptOrigin.y - geometryBasis.y );
  CVec2 dir( ray.ptDir.x, ray.ptDir.y );
  Normalize( &dir );

  if( gDrawTerrainPick )
  {
    const Render::Color color( 0, 255, 255 );
    Render::DebugRenderer::DrawLine3D( CVec3( point, 0.f ), CVec3( point + dir * 10000.f, 0.f ), color, color, false );
  }

  if( pTerrain->IntersectWithGrid( &point, dir ) )
  {
    if( gDrawTerrainPick )
      Render::DebugRenderer::DrawPoint3D( CVec3( point, 0.f ), 2.f, Render::Color( 0, 255, 255 ), false );

    CVec2 rayPointFirst;
    CVec2 rayPointSecond;
    PointSelector pointSelector( point, dir, pTerrain->GetGridConstants().metersPerTile );

    //@Ivn@TODO: replace this for with while // smirnov [2009/4/3]: 'while' was replaced with 'for' already (preventing infinite loops)
    for (int tryCount = 0; tryCount < 1000; tryCount++)
    {
      // choose next points
      pointSelector( &rayPointFirst, &rayPointSecond );

      float terrainHeight1 = 0.f;
      float terrainHeight2 = 0.f;

      // check bounds of terrain
      if( GetHeight( rayPointFirst.x, rayPointFirst.y, 1, &terrainHeight1, 0 ) && GetHeight( rayPointSecond.x, rayPointSecond.y, 1, &terrainHeight2, 0 ) )
      {
        const float startX = ray.ptOrigin.x - geometryBasis.x;
        const float startY = ray.ptOrigin.y - geometryBasis.y;

        const float t1 = fabs( ray.ptDir.x ) > EPS_VALUE 
          ? ( rayPointFirst.x - startX ) / ray.ptDir.x 
          : ( rayPointFirst.y - startY ) / ray.ptDir.y;
        const float t2 = fabs( ray.ptDir.x ) > EPS_VALUE 
          ? ( rayPointSecond.x - startX ) / ray.ptDir.x 
          : ( rayPointSecond.y - startY ) / ray.ptDir.y;

        const CVec3& p1 = ray.Get( t1 );
        const CVec3& p2 = ray.Get( t2 );

        if( ( p1.z >= terrainHeight1 && p2.z <= terrainHeight2 ) || ( p1.z <= terrainHeight1 && p2.z >= terrainHeight2 ) )
        {
          // different sides
          const CLine2 line1 = fabs( rayPointFirst.x - rayPointSecond.x ) > EPS_VALUE
            ? CLine2( CVec2( rayPointFirst.x, p1.z ), CVec2( rayPointSecond.x, p2.z ) ) 
            : CLine2( CVec2( rayPointFirst.y, p1.z ), CVec2( rayPointSecond.y, p2.z ) );
          const CLine2 line2 = fabs( rayPointFirst.x - rayPointSecond.x ) > EPS_VALUE
            ? CLine2( CVec2( rayPointFirst.x, terrainHeight1 ), CVec2( rayPointSecond.x, terrainHeight2 ) ) 
            : CLine2( CVec2( rayPointFirst.y, terrainHeight1 ), CVec2( rayPointSecond.y, terrainHeight2 ) );

          CVec2 intersection;
          if( !IntersectLines( &intersection, line1, line2 ) )
            continue;

          const float t = ( intersection.y - ray.ptOrigin.z ) / ray.ptDir.z;
          *pIntersection = ray.Get( t );

          if( gDrawTerrainPick )
          {
            Render::DebugRenderer::DrawPoint3D( *pIntersection, 1.f, Render::Color( 255, 0, 0 ), true );
            terrain_Pick.SetValue("{%.1f, %.1f, %.1f}", pIntersection->x, pIntersection->y, pIntersection->z);
          }

          return true;
        }
      }
      else
        break;
    }

    return false;
  }

  const float z = 0.0f - ray.ptOrigin.z;
  if ( fabs( z ) > EPS_VALUE )
    *pIntersection = ray.Get( z / ray.ptDir.z );
  return false;
}
void PlaceOnTerrain(const IHeightsController &controller, CVec3 &pos, int layer)
{
  NI_PROFILE_FUNCTION

	float z = 0.0f;
	controller.GetHeight(pos.x, pos.y, layer, &z, 0);
	pos.z += z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}// namespace NScene
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS_NM( TerrainLayerHeight, NScene );
REGISTER_SAVELOAD_CLASS_NM( ObjectsLayerHeight, NScene );
