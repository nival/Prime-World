#pragma once

#include "Geom.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct BoundCalcer
{
	CVec3 ptMin, ptMax;
	BoundCalcer(): ptMin( 1e38f, 1e38f, 1e38f ), ptMax( -1e38f, -1e38f, -1e38f ) {}

	__forceinline void Add( const CVec3& p, float fRadius )
	{
		ptMin.Minimize( p - CVec3( fRadius, fRadius, fRadius ) );
		ptMax.Maximize( p + CVec3( fRadius, fRadius, fRadius ) );
	}

	__forceinline void Add( const CVec3& p )
	{
		ptMin.Minimize( p );
		ptMax.Maximize( p );
	}

	__forceinline void Add( const SBound& bv )
	{
		ptMin.Minimize( bv.s.ptCenter - bv.ptHalfBox );
		ptMax.Maximize( bv.s.ptCenter + bv.ptHalfBox );
	}

	const CVec3 &GetMin() const { return ptMin; }
	const CVec3 &GetMax() const { return ptMax; }

	void Make( SBound *pRes ) const
	{
		if ( IsEmpty() )
			pRes->BoxInit( VNULL3, VNULL3 ); 
		else
			pRes->BoxInit( ptMin, ptMax ); 
	}

	bool IsEmpty() const { return ptMin.x > ptMax.x; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
