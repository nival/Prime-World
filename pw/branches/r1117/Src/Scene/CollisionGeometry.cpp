#include "stdafx.h"

#include "CollisionGeometry.h"
#include "../System/BoundCalcer.h"
#include "../System/BinChunkSerializer.h"
#include "../Render/StaticMesh.h"
#include "../Render/locktype.h"
#include "../Render/vertexelementtype.h"
#include "../Render/vertexformatdescriptor.h"
#include "../Render/vertexelementdescriptor.h"
#include "../Render/vertexstreamdescriptor.h"
#include "../Render/renderprimitivetype.h"
#include "../Render/debugrenderer.h"

static bool ComparePoints( const CVec3& point1, const CVec3& point2 )
{
	if ( point1.x > point2.x )
		return false;
	else if ( point1.x == point2.x )
	{
		if ( point1.y > point2.y ) 
			return false;
		else if ( point1.y == point2.y && point1.z > point2.z )
			return false;
	}

	return true;
}

namespace NScene
{

void CollisionGeometry::Clear()
{
	points.clear();
	edges.clear();
	triangles.clear();
}

WORD CollisionGeometry::AddEdge( const WORD start, const WORD finish )
{
	for ( int i = 0; i < edges.size(); ++i )
	{
		if ( edges[i].start == start && edges[i].finish == finish )
			return i;
		if ( edges[i].start == finish && edges[i].finish == start )
			return i | BACKWARD_EDGE_MASK;
	}

	WORD result = edges.size();
	Edge& edge = edges.push_back();

	if ( ComparePoints( points[start], points[finish] ) )
	{
		edge.start = start;
		edge.finish = finish;
	}
	else
	{
		edge.start = finish;
		edge.finish = start;
		result |= BACKWARD_EDGE_MASK;
	}

	return result;
}

void CollisionGeometry::Create( const vector<CVec3> &_points, const vector<CollisionGeometry::Triangle> &_triangles )
{
	points = _points;
	edges.clear();
	triangles.clear();

	for ( vector<Triangle>::const_iterator it = _triangles.begin(); it != _triangles.end(); ++it )
	{
		if ( it->edge1 == it->edge2 || it->edge1 == it->edge3 || it->edge2 == it->edge3 )
			continue;
		
		triangles.push_back( Triangle( AddEdge( it->edge1, it->edge2 ), AddEdge( it->edge2, it->edge3 ), AddEdge( it->edge3, it->edge1 ) ) );
	}
}

void CollisionGeometry::GetBounds( SBound* pBounds ) const
{
	BoundCalcer calcer;
	for ( vector<CVec3>::const_iterator it = points.begin(); it != points.end(); ++it )
		calcer.Add( *it );

	calcer.Make( pBounds );
}

void CollisionGeometry::GetTransformedBounds( SBound* pBounds, const Matrix43& position ) const
{
	BoundCalcer calcer;
	CVec3 temp;
	for ( vector<CVec3>::const_iterator it = points.begin(); it != points.end(); ++it )
	{
		temp = Transform( *it, position );
		calcer.Add( temp );
	}

	calcer.Make( pBounds );

}

void CollisionGeometry::DebugDraw( const Matrix43& position, Render::IDebugRender* debugRender ) const
{
	for ( vector<Edge>::const_iterator it = edges.begin(); it != edges.end(); ++it )
	{
		CVec3 p1 = Transform( points[it->start], position );
		CVec3 p2 = Transform( points[it->finish], position );
		debugRender->DrawLine3D(p1, p2, Render::Color((unsigned long)0xFF00FF00), Render::Color((unsigned long)0xFF00FF00), false);
	}
}

CollisionGeometryManager& CollisionGeometry::GetCollisionManager()
{
  static CollisionGeometryManager manager;
  return manager;
}
} // namespace NScene
BASIC_REGISTER_CLASS( NScene::CollisionGeometry );