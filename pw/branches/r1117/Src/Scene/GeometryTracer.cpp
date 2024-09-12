#include "stdafx.h"

#include "GeometryTracer.h"
#include "CollisionGeometry.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static float traceSign[] = { 1.f, -1.f };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline static float Dot( const CVec3& a, const CVec4& b ) 
{ 
	return a.x * b.x + a.y * b.y + a.z * b.z + b.w; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline static void TransformPoints( vector<CVec3>* pResult, const vector<CVec3>& points, const CVec4& axis1, const CVec4& axis2, const CVec4& axis3 )
{
	pResult->resize( points.size() );
	for( int i = 0; i < points.size(); ++i )
	{
		const CVec3& src = points[i];
		CVec3& dst = (*pResult)[i];
		dst.x = Dot( src, axis1 );
		dst.y = Dot( src, axis2 );
		if ( fabs2( dst ) < 1e-6 )
			dst.x = -1e-3f; // handle degenerate case via converting it to non degenerate :)
		dst.z = Dot( src, axis3 );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline static float CrossProduct2D( const CVec3 &a, const CVec3 &b )
{
	return a.x * b.y - a.y * b.x;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline static void PrepareEdges( vector<float>* pResult, const vector<NScene::CollisionGeometry::Edge>& edges, const vector<CVec3>& transformed, float nearZ )
{
	pResult->resize( edges.size() );
	for( int i = 0; i < edges.size(); ++i )
	{
		/* TODO: MUSTFIX and uncomment (to prevent picking objects behind camera)
		if ( transformed[edges[i].start].z < nearZ || transformed[edges[i].finish].z < nearZ )
		{
			(*pResult)[i] = 0; // exclude polygons with this edge from testing
			continue;
		}
		*/

		(*pResult)[i] = CrossProduct2D( transformed[edges[i].start], transformed[edges[i].finish] );
		if ( (*pResult)[i] == 0 )
			(*pResult)[i] = 1e-6f; // same as with points, somebody has to win ;)
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline static float GetDistance( const CVec3 &a1, float f1, const CVec3 &a2, float f2, const CVec3& dir )
{
	return ( ( a2 * f1 - a1 * f2 ) / (f1 - f2) ) * dir;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeometryTracer::Initialize( const CRay& ray, const bool _enterOnly, const float _nearZ )
{
	NI_VERIFY( fabs2( ray.ptDir ) > 0, "Invalid direction for ray", return );

	enterOnly = _enterOnly;

	CVec3 _axis1;
	if ( fabs( ray.ptDir.x ) > fabs( ray.ptDir.y ) && fabs( ray.ptDir.x ) > fabs( ray.ptDir.z ) )
		_axis1 = ray.ptDir ^ CVec3(0,1,0); 
	else
		_axis1 = ray.ptDir ^ CVec3(1,0,0); 
	Normalize( &_axis1 );

	CVec3 _axis2 = ray.ptDir ^ _axis1;
	Normalize( &_axis2 );

	origin = ray.ptOrigin;
	dir = ray.ptDir;
	dirNorm = dir;
	Normalize( &dirNorm );

	axis1 = CVec4( _axis1.x, _axis1.y, _axis1.z, -( _axis1 * origin ) );
	axis2 = CVec4( _axis2.x, _axis2.y, _axis2.z, -( _axis2 * origin ) );

	CVec3 _axis3 = dirNorm;
	axis3 = CVec4( _axis3.x, _axis3.y, _axis3.z, -( _axis3 * origin ) );
	nearZ = _nearZ;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GeometryTracer::TestSphere( const CVec3& center, const float radius ) const
{
	CVec3 v = ( center - origin ) ^ dirNorm;
	return fabs( v ) <= radius;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeometryTracer::GetTriangle( TriangleRef* pResult, const CollisionGeometry::Triangle& triangle, const vector<CVec3>& points,
																 const vector<CollisionGeometry::Edge>& edges, const Matrix43& placement ) const
{
	int i1, i2, i3;
	if ( triangle.edge1 & CollisionGeometry::BACKWARD_EDGE_MASK )
	{
		i1 = edges[triangle.edge1 & CollisionGeometry::EDGE_INDEX_MASK].finish; 
		i2 = edges[triangle.edge1 & CollisionGeometry::EDGE_INDEX_MASK].start;
	}
	else
	{
		i1 = edges[triangle.edge1 & CollisionGeometry::EDGE_INDEX_MASK].start; 
		i2 = edges[triangle.edge1 & CollisionGeometry::EDGE_INDEX_MASK].finish;
	}
	if ( triangle.edge2 & CollisionGeometry::BACKWARD_EDGE_MASK )
		i3 = edges[triangle.edge2 & CollisionGeometry::EDGE_INDEX_MASK].start;
	else
		i3 = edges[triangle.edge2 & CollisionGeometry::EDGE_INDEX_MASK].finish;
	
	pResult->point1 = Transform( points[i1], placement );
	pResult->point2 = Transform( points[i2], placement );
	pResult->point3 = Transform( points[i3], placement );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GeometryTracer::CalcTriangleCross( const TriangleRef& triangle ) const
{
	CVec3 triangleNormal = ( triangle.point2 - triangle.point1 )^( triangle.point3 - triangle.point1 );
	Normalize( &triangleNormal );
	const float denominator = ( dir * triangleNormal );
	if ( denominator != 0 )
		return ( ( triangle.point1 - origin ) * triangleNormal ) / denominator;

	// trouble happened, calc distance to triangle in different way
	const CVec3 separate = triangleNormal ^ dir;
	const float f0 = origin * separate;
	const float f1 = triangle.point1 * separate - f0;
	const float f2 = triangle.point2 * separate - f0;
	const float f3 = triangle.point3 * separate - f0;
	float distance = 1e30f;

	if ( f1 * f2 < 0 )
		distance = Min( distance, GetDistance( triangle.point1, f1, triangle.point2, f2, dir ) );
	if ( f2 * f3 < 0 )
		distance = Min( distance, GetDistance( triangle.point2, f2, triangle.point3, f3, dir ) );
	if ( f3 * f1 < 0 )
		distance = Min( distance, GetDistance( triangle.point3, f3, triangle.point1, f1, dir ) );

	NI_VERIFY( distance != 1e30f, "Invalid triangle", return 0.0f );

	distance = ( distance - origin * dir ) / fabs( dir );
	return distance;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline static void ProjectPoints( vector<CVec3>* pResult, const vector<CVec3>& points, const Matrix43& _placement, const SHMatrix& viewAndProj, int w, int h )
{
	pResult->resize( points.size() );

	SHMatrix placement;
	placement._11 = _placement._11;
	placement._12 = _placement._12;
	placement._13 = _placement._13;
	placement._14 = _placement._14;
	placement._21 = _placement._21;
	placement._22 = _placement._22;
	placement._23 = _placement._23;
	placement._24 = _placement._24;
	placement._31 = _placement._31;
	placement._32 = _placement._32;
	placement._33 = _placement._33;
	placement._34 = _placement._34;
	placement._41 = 0;
	placement._42 = 0;
	placement._43 = 0;
	placement._44 = 1;

	SHMatrix transform = viewAndProj * placement;

	for( int i = 0; i < points.size(); ++i )
	{
		CVec4 src;
		transform.RotateHVector( &src, points[i] );
		CVec3& dst = (*pResult)[i];
		dst.x = (( src.x / src.w + 1.0 ) * w) / 2.0;
		dst.y = h - (( src.y / src.w + 1.0 ) * h) / 2.0;
		dst.z = src.z;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GeometryTracer::CalcGeometryRect( const CollisionGeometry* pGeometry, const Matrix43& placement, const SHMatrix& viewAndProj, int w, int h, CTRect<float> *pRect )
{
	NI_VERIFY( pRect, "No rect to fill!", return false );

	pRect->x1 = 0;
	pRect->x2 = 0;
	pRect->y1 = 0;
	pRect->y2 = 0;

	NI_VERIFY( IsValid( pGeometry ), "Invalid hull geometry", return false );

	ProjectPoints( &transformed, pGeometry->GetPoints(), placement, viewAndProj, w,h );
	if ( transformed.empty() )
		return false;

	bool gotPoints = false;
	for ( int i = 0; i < transformed.size(); ++i )
	{
		if ( transformed[i].z < nearZ )
			continue;

		float x = transformed[i].x;
		float y = transformed[i].y;

		if ( !gotPoints )
		{
			gotPoints = true;
			pRect->x1 = pRect->x2 = x;
			pRect->y1 = pRect->y2 = y;
		}
		else
		{
			if ( x < pRect->x1 ) pRect->x1 = x;
			if ( x > pRect->x2 ) pRect->x2 = x;
			if ( y < pRect->y1 ) pRect->y1 = y;
			if ( y > pRect->y2 ) pRect->y2 = y;
		}
	}

	return gotPoints;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GeometryTracer::TestGeometry( const CollisionGeometry* pGeometry, const Matrix43& placement, float *pEnter, float *pExit )
{
	*pEnter = 1e38f;
	*pExit = -1e38f;

	NI_VERIFY( IsValid( pGeometry ), "Invalid hull geometry", return false );

	bool haveEnter = false;
	bool haveExit = false;

	CVec4 _axis1 = TransformTransposed( axis1, placement );
	CVec4 _axis2 = TransformTransposed( axis2, placement );
	CVec4 _axis3 = TransformTransposed( axis3, placement );

	TransformPoints( &transformed, pGeometry->GetPoints(), _axis1, _axis2, _axis3 );
	PrepareEdges( &edges, pGeometry->GetEdges(), transformed, nearZ );

	for ( vector<CollisionGeometry::Triangle>::const_iterator it = pGeometry->GetTriangles().begin(); it != pGeometry->GetTriangles().end(); ++it )
	{
		const float f1 = edges[it->edge1 & 0x7fff] * traceSign[it->edge1>>15];
		const float f2 = edges[it->edge2 & 0x7fff] * traceSign[it->edge2>>15];
		const float f3 = edges[it->edge3 & 0x7fff] * traceSign[it->edge3>>15];

		if ( f1 < 0 && f2 < 0 && f3 < 0 )
		{
			TriangleRef triangle;
			GetTriangle( &triangle, *it, pGeometry->GetPoints(), pGeometry->GetEdges(), placement );
			*pEnter = Min( *pEnter, CalcTriangleCross( triangle ) );
			haveEnter = true;
			if ( enterOnly )
			{
				*pExit = *pEnter;
				continue;
			}
		}
		if ( f1 > 0 && f2 > 0 && f3 > 0 )
		{
			TriangleRef triangle;
			GetTriangle( &triangle, *it, pGeometry->GetPoints(), pGeometry->GetEdges(), placement );
			*pExit = Max( *pExit, CalcTriangleCross( triangle ) );
			haveExit = true;
		}
	}

	if ( !haveEnter && !haveExit )
		return false;
	else if ( !haveEnter )
		*pEnter = *pExit;
	else if ( !haveExit )
		*pExit = *pEnter;

	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NScene
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
