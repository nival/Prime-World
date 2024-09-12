#include "stdafx.h"
#include "TerrainGrid.h"
#include "RenderableScene.h"
#include "GeometryBuilders.h"

namespace NScene
{

TerrainGrid::TerrainGrid( IScene *_pScene, const HeightsController* controller, int _size, float _step, float _accur )
: pScene( _pScene )
,	step( _step )
,	size( _size )
, pHeightController( controller )
, accur( _accur )
, cycle( 0 )
, pStaticMesh_free( 0 )
, pStaticMesh_blocked( 0 )
, version( -1 )
{
}

TerrainGrid::~TerrainGrid()
{
	delete pStaticMesh_free;
	delete pStaticMesh_blocked;
}

void TerrainGrid::Render()
{
	/* BVS. Something strange. Should be refactored
	if ( pHeightController->GetVersion() != version && cycle >= 3 )
	{
		float z = 0.f;
		if ( pHeightController->GetHeight( 0, 0, 0, &z, 0 ) )
		{
			vector<CVec3> points;
			vector<CollisionGeometry::Triangle> triangles;
			int curPIdx = 0;

			delete pStaticMesh_free;
			delete pStaticMesh_blocked;

			for ( int x = 0; x < size; x++ )
			{
				for ( int y = 0; y < size; y++ )
				{
					z = GetHeight(x, y);
					vector<CVec3> pnts;
					vector<CollisionGeometry::Triangle> tris;
					CollisionGeometry* geom = CreatePyramid( CVec3(x*step,y*step,0.f), CVec3(step-0.5f,step-0.5f,z+0.1f), 1.0f, false, pnts, tris );
					delete geom;
					for ( int pIdx = 0; pIdx < pnts.size(); pIdx++ )
					{
						points.push_back( pnts[pIdx] );
					}
					for ( int tIdx = 0; tIdx < tris.size(); tIdx++ )
					{
						CollisionGeometry::Triangle toadd = tris[tIdx];
						toadd.edge1 += curPIdx;
						toadd.edge2 += curPIdx;
						toadd.edge3 += curPIdx;
						triangles.push_back( toadd );
					}
					curPIdx += pnts.size();
				}
			}
	
			CollisionGeometry geom( points, triangles );
			pStaticMesh_free = geom.CreateModel( Render::Color( 10, 128, 216, 128 ) );

			version = pHeightController->GetVersion();
			cycle++;
		}
	}

	else
	{
		if ( pStaticMesh_free )
		{
			pStaticMesh_free->SetWorldMatrix( IDENTITY_MATRIX );
//			pScene->PushRenderComponent( ActorInfo( pStaticMesh_free ) );
		}
		if ( pStaticMesh_blocked )
		{
			pStaticMesh_blocked->SetWorldMatrix( IDENTITY_MATRIX );
//			pScene->PushRenderComponent( ActorInfo( pStaticMesh_blocked ) );
		}
		cycle++;
 	}
	*/
}

float TerrainGrid::GetHeight( int x, int y )
{
	float maxZ = 0.f;
	float z = 0.f;
	for ( float i = -step; i < step; i += accur )
	{
		for ( float j = -step; j < step; j += accur )
		{
			if ( pHeightController->GetHeight( x*step+i, y*step+j, 0, &z, 0 ) )
			{
				maxZ = z > maxZ ? z : maxZ;
			}
		}
	}
	return maxZ;
}

}
