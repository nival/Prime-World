#include "StdAfx.h"
#include "CollisionGeometry.h"
#include "GeometryBuilders.h"
#include "../System/Transform.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MemBuilderVertex
{
	CVec3 point;

	MemBuilderVertex() {}
	MemBuilderVertex( const CVec3& _point ) : point( _point ) {}

	bool operator==( const MemBuilderVertex &a ) const 
	{
		return fabs2( point - a.point )	< 1e-6;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MemBuilderVertexHash
{
	int operator()( const MemBuilderVertex& v ) const
	{ 
		float f = v.point.x + v.point.y * 123 + v.point.z * 15352331;
		return *(int*)&f;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct GeometryBuilder
{
	typedef hash_map<MemBuilderVertex, int, MemBuilderVertexHash> CPointsHash;

	vector<CVec3> points;
	vector<NScene::CollisionGeometry::Triangle> triangles;
	
	CPointsHash pointsHash;
	
	WORD GetPointIndex( const CVec3 &point )
	{
		CPointsHash::iterator pos = pointsHash.find( point );
		if ( pos == pointsHash.end() )
		{
			int index = points.size();
			points.push_back( point );
			pointsHash[point] = index;
			return index;
		}

		return pos->second;
	}

	void AddSphereTriangle( const CVec3 &a, const CVec3 &b, const CVec3 &c, int subs )
	{
		if ( subs == 0 )
		{
			WORD w1 = GetPointIndex( a );
			WORD w2 = GetPointIndex( b );
			WORD w3 = GetPointIndex( c );
			triangles.push_back( NScene::CollisionGeometry::Triangle( w1, w2, w3 ) );
		}
		else
		{
			CVec3 ab( a + b );
			CVec3 bc( b + c );
			CVec3 ca( a + c );
			Normalize( &ab );
			Normalize( &bc );
			Normalize( &ca );
			AddSphereTriangle( ab, b, bc, subs - 1 );
			AddSphereTriangle( a, ab, ca, subs - 1 );
			AddSphereTriangle( ca, bc, c, subs - 1 );
			AddSphereTriangle( ab, bc, ca, subs - 1 );
		}
	}

	NScene::CollisionGeometry* CreateGeometry( float radius ) const
	{
		vector<CVec3> shiftedPoints( points.size() );
		for( int i = 0; i < points.size(); ++i )
			shiftedPoints[i] = points[i] * radius;

		return new NScene::CollisionGeometry( shiftedPoints, triangles );
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{

CollisionGeometry* CreatePyramid( const SBound& bound, float topSideSize, bool twoSided, 
																	vector<CVec3>& points, vector<CollisionGeometry::Triangle>& triangles )
{
	CVec3 center = bound.s.ptCenter;
	center.z -= bound.ptHalfBox.z;
	CVec3 size = bound.ptHalfBox * 2.0f;
	return CreatePyramid(center, size, topSideSize, twoSided, points, triangles);
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CollisionGeometry* CreatePyramid( const CVec3& center, const CVec3& size, float topSideSize, bool twoSided
																 , vector<CVec3>& points, vector<CollisionGeometry::Triangle>& triangles )
{
	const float sizeX2 = size.x / 2;
	const float sizeY2 = size.y / 2;
	const float topSizeX2 = sizeX2 * topSideSize;
	const float topSizeY2 = sizeY2 * topSideSize;

	points.clear();
	points.resize( 8 );
	points[0] = CVec3( center.x - sizeX2,			center.y - sizeY2,		center.z );
	points[1] = CVec3( center.x - sizeX2,			center.y + sizeY2,		center.z );
	points[2] = CVec3( center.x + sizeX2,			center.y + sizeY2,		center.z );
	points[3] = CVec3( center.x + sizeX2,			center.y - sizeY2,		center.z );
	points[4] = CVec3( center.x - topSizeX2,	center.y - topSizeY2, center.z + size.z);
	points[5] = CVec3( center.x - topSizeX2,	center.y + topSizeY2, center.z + size.z );
	points[6] = CVec3( center.x + topSizeX2,	center.y + topSizeY2, center.z + size.z );
	points[7] = CVec3( center.x + topSizeX2,	center.y - topSizeY2, center.z + size.z );

	triangles.clear();
	triangles.resize( 12 );
	triangles[0] =  CollisionGeometry::Triangle( 0, 1, 2 );
	triangles[1] =  CollisionGeometry::Triangle( 0, 2, 3 );
	triangles[2] =  CollisionGeometry::Triangle( 3, 6, 7 );
	triangles[3] =  CollisionGeometry::Triangle( 3, 2, 6 );
	triangles[4] =  CollisionGeometry::Triangle( 0, 7, 4 );
	triangles[5] =  CollisionGeometry::Triangle( 0, 3, 7 );
	triangles[6] =  CollisionGeometry::Triangle( 5, 0, 4 );
	triangles[7] =  CollisionGeometry::Triangle( 5, 1, 0 );
	triangles[8] =  CollisionGeometry::Triangle( 6, 1, 5 );
	triangles[9] =  CollisionGeometry::Triangle( 6, 2, 1 );
	triangles[10] = CollisionGeometry::Triangle( 4, 6, 5 );
	triangles[11] = CollisionGeometry::Triangle( 4, 7, 6 );

	if ( twoSided )
	{
		triangles.resize( triangles.size() + 12 );
		for ( int i = 0; i < 12; ++i )
			triangles[12 + i] = CollisionGeometry::Triangle( triangles[i].edge1, triangles[i].edge3, triangles[i].edge2 );
	}

	return new CollisionGeometry( points, triangles );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CollisionGeometry* CreateSphere( float radius, int subs	)
{
	GeometryBuilder builder;
	CVec3 a( 1.000f, 0.000f, -0.707f );
	CVec3 b( 0.000f, -1.000f, 0.707f );
	CVec3 c( 0.000f, 1.000f, 0.707f );
	CVec3 d( -1.000f, 0.000f, -0.707f );
	Normalize( &a );
	Normalize( &b );
	Normalize( &c );
	Normalize( &d );
	builder.AddSphereTriangle( a, c, b, subs );
	builder.AddSphereTriangle( a, b, d, subs );
	builder.AddSphereTriangle( a, d, c, subs );
	builder.AddSphereTriangle( b, c, d, subs );

	return builder.CreateGeometry( radius );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CollisionGeometry* CreateCylinder( float radius, int subs, float height )
{
	vector<CVec3> points;
	vector<CollisionGeometry::Triangle> triangles;
	
	if( height < 0.01f ) // without volume
	{
		points.push_back( CVec3( 0.0f, 0.0f, 0.0f ) );
		for( int i = 0; i < subs; ++i )
		{
			float a = FP_2PI * i / subs + FP_PI / subs;
			points.push_back( CVec3( radius*cos(a), radius*sin(a), 0.0f ) );
		}
		for( int i1 = 0; i1 < subs; ++i1 )
		{
			int i2 = i1+1;
			if( i2 >= subs ) i2 -= subs;
			triangles.push_back( CollisionGeometry::Triangle( 0, i1+1, i2+1 ) );
		}
	}
	else // with volume
	{
		points.push_back( CVec3( 0.0f, 0.0f, 0.0f ) );
		points.push_back( CVec3( 0.0f, 0.0f, height ) );
		for( int i = 0; i < subs; ++i )
		{
			float a = FP_2PI * i / subs + FP_PI / subs;
			points.push_back( CVec3( radius*cos(a), radius*sin(a), 0.0f ) );
		}
		for( int i = 0; i < subs; ++i )
		{
			float a = FP_2PI * i / subs + FP_PI / subs;
			points.push_back( CVec3( radius*cos(a), radius*sin(a), height ) );
		}

		for( int i1 = 0; i1 < subs; ++i1 )
		{
			int i2 = i1+1;
			if( i2 >= subs ) i2 -= subs;
			triangles.push_back( CollisionGeometry::Triangle( 0, i1+2, i2+2 ) );
			triangles.push_back( CollisionGeometry::Triangle( 1, i1+2+subs, i2+2+subs ) );
			triangles.push_back( CollisionGeometry::Triangle( i1+2+subs, i1+2, i2+2 ) );
			triangles.push_back( CollisionGeometry::Triangle( i1+2+subs, i2+2, i2+2+subs ) );
		}
	}

	return new CollisionGeometry( points, triangles );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}