#include "stdafx.h"

#include "CollisionMap.h"
#include "CollisionHull.h"
#include "CollisionVolumeNode.h"
#include "Octree.h"
#include "RenderableScene.h"
#include "Scene.h"
#include "../System/BoundCalcer.h"
#include "../Render/StaticMesh.h"

namespace 
{
	bool g_bDrawCollision = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TSwap>
static void Sort( T* elements, const int size, TSwap swap )
{
	for( int i = 0; i < size - 1; ++i )
	{
		for( int j = i + 1; j < size; ++j )
		{
			if ( elements[i] > elements[j] )
				swap( &elements[i], &elements[j] );
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
void CollisionMap::Initialize( int floorsCount, const CVec3& _floorBase, float _floorSize )
{
  floorBase = _floorBase; 
  floorSize = _floorSize; 

  floors.clear();
	floors.resize( floorsCount );
	SetActiveFloor( 0 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CollisionMap::SetActiveFloor( int floor )
{
	NI_VERIFY( floor >= 0 && floor < floors.size(), NStr::StrFmt( "Floor index %d is out of bounds 0 .. %d", floor, floors.size() ), return false );
	activeFloor = floor;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CollisionVolumeNode* CollisionMap::GetNode( const SBound& bounds, const int floor )
{
	if ( !IsValid( floors[floor] ) )
	{
		floors[floor] = new CollisionVolumeNode();
		floors[floor]->SetSize( floorBase, floorSize );
	}

	return floors[floor]->GetNode( bounds.s.ptCenter, bounds.s.fRadius );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CollisionHull* CollisionMap::CreateHull( SceneObject* pSceneObject, const int pieceId, CollisionGeometry* pGeometry, const Matrix43& place, const int floor )
{
	CollisionHull* pCollisionHull = new CollisionHull( pSceneObject, pieceId, this );
	pCollisionHull->SetGeometry( pGeometry );
	pCollisionHull->SetPosition( place, floor );
	return pCollisionHull;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CollisionMap::RemoveHull( CollisionHull* pHull )
{
  if(pHull)
  {
   	pHull->RemoveFromNodes();
  	return true;
  }
  return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CollisionMap::Trace( IntersectionFloat *pIntersections, const int intersectionsSize, const CRay& ray, const bool onlyEnters, float fNear )
{
  if ( !IsValid( floors[GetActiveFloor()] ) )
    return 0;

  tracer.Initialize( ray, onlyEnters, fNear );

  struct HullTracer
  {
    GeometryTracer* pTracer;
    IntersectionFloat *pIntersections;
    int count;
    int intersectionsSize;

    HullTracer( GeometryTracer* _pTracer, IntersectionFloat *_pIntersections, const int _intersectionsSize ) :
    pTracer( _pTracer ),
      pIntersections( _pIntersections ),
      count( 0 ),
      intersectionsSize( _intersectionsSize )
    {}

    const bool Test( CollisionVolumeNode* pNode ) const
    {
      SBound bounds;
      pNode->GetBound( &bounds );
      return pTracer->TestSphere( bounds.s.ptCenter, bounds.s.fRadius );
    }

    void Visit( CollisionHull* pHull )
    {
      if (!pHull->IsEnabled())
        return;

      if ( pTracer->TestSphere( pHull->GetBounds().s.ptCenter, pHull->GetBounds().s.fRadius ) )
      {
        float enter, exit;
        if ( pTracer->TestGeometry( pHull->GetGeometry(), pHull->GetPosition(), &enter, &exit ) && count < intersectionsSize )
        {
          pIntersections[count].pHull = pHull;
          pIntersections[count].enter = enter;
          pIntersections[count].exit = exit;
          pIntersections[count].sortIndex = count;
          ++count;
        }
      }
    }
  };

  HullTracer hullTracer( &tracer, pIntersections, intersectionsSize );
  floors[GetActiveFloor()]->VisitHulls( &hullTracer );
  Sort( pIntersections, hullTracer.count, IntersectionFloatSort() );

  if ( hullTracer.count == 1 && pIntersections[0].pHull->GetPieceId() == 1 )
  {
    pIntersections[0].pHull = 0;
    return 0;
  }

  return hullTracer.count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CollisionMap::Trace( Intersection *pIntersections, const int intersectionsSize, const CRay& ray, const bool onlyEnters, float fNear )
{
	if ( !IsValid( floors[GetActiveFloor()] ) )
		return 0;

  floatIntersections.resize( intersectionsSize );

  int count = Trace( &floatIntersections[0], intersectionsSize, ray, onlyEnters, fNear );

	for( int i = 0; i < count; ++i )
	{
		const int index = floatIntersections[i].sortIndex;

		if ( index < intersectionsSize )
		{
			pIntersections[index].pHull = floatIntersections[i].pHull;
			pIntersections[index].enter = ray.Get( floatIntersections[i].enter );
			pIntersections[index].exit = ray.Get( floatIntersections[i].exit );
		}
	}

	return count;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CollisionMap::TraceRect( CollisionHull* pHull, const SHMatrix& viewAndProj, float fNear, int w, int h, CTRect<float> *pRect )
{
	NI_VERIFY( pRect, "No rect to fill", return false );

	if ( !IsValid( pHull ) || !IsValid( floors[GetActiveFloor()] ) )
		return false;

	CRay tmpRay( CVec3(0,0,0), CVec3(1,1,1) ); // just some temporary ray
	tracer.Initialize( tmpRay, true, fNear );
	return tracer.CalcGeometryRect( pHull->GetGeometry(), pHull->GetPosition(), viewAndProj, w, h, pRect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionMap::DebugRender( Render::IDebugRender* debugRender )
{
	if ( !IsValid( floors[GetActiveFloor()] ) || ( !g_bDrawCollision ) )
		return;

	struct HullRender
	{
    Render::IDebugRender* debugRender;

		const bool Test( CollisionVolumeNode* pNode ) const { return true; }

		void Visit( CollisionHull* pHull )
		{
			if (pHull->IsEnabled())
				pHull->DebugRender( debugRender );
		}
	};

	HullRender hullRender;
  hullRender.debugRender = debugRender;
	floors[GetActiveFloor()]->VisitHulls( &hullRender );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NScene
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( NScene::CollisionVolumeNode );
//BASIC_REGISTER_CLASS( NScene::CollisionHull );
BASIC_REGISTER_CLASS( NScene::CollisionMap );

REGISTER_DEV_VAR( "show_collision", g_bDrawCollision, STORAGE_NONE );
