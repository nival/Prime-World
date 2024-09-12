#pragma once

#include "CollisionGeometry.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{

struct TriangleRef
{
  CVec3 point1, point2, point3;
};

class GeometryTracer
{
	bool enterOnly;
	CVec3 origin, dir, dirNorm;
	CVec4 axis1, axis2, axis3;
	float nearZ;

	vector<float> edges;
	vector<CVec3> transformed;

	float CalcTriangleCross( const TriangleRef& triangle ) const;
public:
	void Initialize( const CRay& ray, const bool enterOnly, const float _nearZ );
	
	bool TestSphere( const CVec3& center, const float radius ) const;
	bool TestGeometry( const CollisionGeometry* pGeometry, const Matrix43& placement, float *pEnter, float *pExit );

  void GetTriangle( TriangleRef* pResult, const CollisionGeometry::Triangle& triangle, const vector<CVec3>& points,
    const vector<CollisionGeometry::Edge>& edges, const Matrix43& placement ) const;

	bool CalcGeometryRect( const CollisionGeometry* pGeometry, const Matrix43& placement, const SHMatrix& viewAndProj, int w, int h, CTRect<float> *pRect );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namepsace NScene
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
