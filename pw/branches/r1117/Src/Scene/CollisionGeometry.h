#pragma once

#include "CollisionGeometryManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
	struct CollisionGeometry;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
	class StaticMesh;
  _interface IDebugRender;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CollisionGeometry : public CObjectBase
{
	OBJECT_BASIC_METHODS( CollisionGeometry );

public:
	struct Edge
	{
		WORD start, finish;

		Edge() : start( 0 ), finish( 0 ) {}
		Edge( const WORD _start, const WORD _finish ) : start( _start ), finish( _finish ) {}
	};

	struct Triangle
	{
		WORD edge1, edge2, edge3;

		Triangle() : edge1( 0 ), edge2( 0 ), edge3( 0 ) {}
		Triangle( const WORD _edge1, const WORD _edge2, const WORD _edge3 ) : edge1( _edge1 ), edge2( _edge2 ), edge3( _edge3 ) {}
	};

	enum { BACKWARD_EDGE_MASK = 0x8000, EDGE_INDEX_MASK = 0x7FFF, };
private:
  ZDATA
  ZNOPARENT(CObjectBase)
		vector<CVec3> points;
		vector<Edge> edges;
		vector<Triangle> triangles;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(2,&points); f.Add(3,&edges); f.Add(4,&triangles); return 0; }
private:

	WORD AddEdge( const WORD start, const WORD finish );

public:
	CollisionGeometry() {}
	CollisionGeometry( const vector<CVec3> &points, const vector<CollisionGeometry::Triangle> &triangles ) { Create( points, triangles ); }

	void Create( const vector<CVec3> &points, const vector<CollisionGeometry::Triangle> &triangles );
	void Clear();

	const vector<CVec3>& GetPoints() const { return points; }
	const vector<Edge>& GetEdges() const { return edges; }
	const vector<Triangle>& GetTriangles() const { return triangles; }

	void DebugDraw( const Matrix43& position, Render::IDebugRender* debugRender ) const;

	void GetBounds( SBound* pBounds ) const;
	void GetTransformedBounds( SBound* pBounds, const Matrix43& position ) const;

  static CollisionGeometryManager& GetCollisionManager();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NScene