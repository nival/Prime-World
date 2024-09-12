#ifndef __PLANE_GEOMETRY_H__
#define __PLANE_GEOMETRY_H__

#include "Win32Random.h"


// Приведения типов
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TPoint>
inline const TPoint GetPointType( const CVec2 &vec )
{
	NI_ALWAYS_ASSERT(	"Can convert only to CVec2 and CVec3!" );
}
template <>
inline const CVec2 GetPointType<CVec2>( const CVec2 &vec )
{
	return vec;
}
template <>
inline const CVec3 GetPointType<CVec3>( const CVec2 &vec )
{
	return CVec3( vec.x, vec.y, 0.0f );
}
//
template <class TPoint>
inline const TPoint GetPointType( const CVec3 &vec )
{
	NI_ALWAYS_ASSERT(	"Can convert only to CVec2 and CVec3!" );
}
template <>
inline const CVec2 GetPointType<CVec2>( const CVec3 &vec )
{
	return CVec2( vec.x, vec.y );
}
template <>
inline const CVec3 GetPointType<CVec3>( const CVec3 &vec )
{
	return vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//определитель что разность элементов меньше заданного значения
template <class TElement>
struct SInRangeFunctional
{
	float fRange;
	SInRangeFunctional() : fRange( 0 ) {}
	SInRangeFunctional( float _fRange ) : fRange( _fRange ) {}

	bool operator()( const TElement &rElement1, const TElement &rElement2 ) const
	{
		return fabs2( rElement1 - rElement2 ) <= fRange;
	}
};

// геометрия с плавающей точкой
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EClassifyEdge
{
	CE_UNKNOWN	= 0,
	
	CE_LEFT			= 1,
	CE_RIGHT		= 2,
	CE_BEYONG		= 3,
	CE_BEHIND		= 4,
	CE_BETWEEN	= 5,
	CE_BEGIN		= 6,
	CE_END			= 7,
	
	CE_COUNT		= 8,
};
const extern EClassifyEdge NEGATIVE_CLASSIFY_EDGE[CE_COUNT + 1];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EClassifyPolygon
{
	CP_UNKNOWN	= 0,
	
	CP_INSIDE		= 1,
	CP_OUTSIDE	= 2,
	CP_BOUNDARY	= 3,
	CP_VERTEX		= 4,
	
	CP_COUNT		= 5,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EClassifyIntersection
{
	CI_UNKNOWN				= 0,
	
	CI_COLLINEAR			= 1,
	CI_PARALLEL				= 2,			
	CI_SKEW						= 3,
	CI_SKEW_CROSS			= 4,
	CI_SKEW_NO_CROSS	= 5,	

	CI_COUNT					= 6,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EClassifyRotation
{
	CR_UNKNOWN					= 0,
	
	CR_CLOCKWISE				= 1,
	CR_COUNTERCLOCKWISE	= 2,
	CR_LINE							= 3,

	CR_COUNT						= 4,
};
const extern EClassifyRotation NEGATIVE_CLASSIFY_ROTATION[CR_COUNT + 1];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline EClassifyEdge GetNegativeClassifyEdge( EClassifyEdge classifyEdge )
{
	return NEGATIVE_CLASSIFY_EDGE[static_cast<int>(classifyEdge)];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EClassifyPolygon GetNegativeClassifyPolygon( EClassifyPolygon classifyPolygon );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline EClassifyRotation GetNegativeClassifyRotation( EClassifyRotation classifyRotation )
{
	return NEGATIVE_CLASSIFY_ROTATION[static_cast<int>(classifyRotation)];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline EClassifyEdge GetClassifyNormal()
{
	return CE_LEFT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline EClassifyEdge GetClassifyEdgeInnerSpace( EClassifyRotation classifyRotation )
{
	if ( classifyRotation == CR_CLOCKWISE )
	{
		return CE_RIGHT;
	}
	else if (	classifyRotation == CR_COUNTERCLOCKWISE )
	{
		return CE_LEFT;
	}
	else
	{
		return CE_UNKNOWN;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//																	*CE_LEFT
//
//
//							 CE_BEGIN									CE_END
// -*----------- *===========*============>* ------------*--------			
//	CE_BEHIND								CE_BETWEEN									CE_BEYONG
//
//										 *CE_RIGHT
//
//
template<class TPoint>
EClassifyEdge ClassifyEdge( const TPoint &rvBegin, const TPoint &rvEnd, const TPoint &v )
{
	const TPoint v10 = rvEnd - rvBegin;
	const TPoint v20 = v - rvBegin;
	const float s1020 = v10.x * v20.y - v10.y * v20.x;
	if ( s1020 > 0.0f )
	{
		return CE_LEFT;
	}
	else if ( s1020 < 0.0f )
	{
		return CE_RIGHT;
	}
	else if ( ( ( v10.x * v20.x ) < 0.0f ) || ( ( v10.y * v20.y ) < 0.0f ) )
	{
		return CE_BEHIND;
	}
	else if ( fabs2( v10.x, v10.y ) < fabs2( v20.x, v20.y ) )
	{
		return CE_BEYONG;
	}
	else if ( ( v.x == rvBegin.x ) && ( v.y == rvBegin.y ) )
	{
		return CE_BEGIN;
	}
	else if ( ( v.x == rvEnd.x ) && ( v.y == rvEnd.y ) )
	{
		return CE_END;
	}
	return CE_BETWEEN;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
EClassifyIntersection ClassifyIntersect( const TPoint &rvBegin0, const TPoint &rvEnd0, const TPoint &rvBegin1, const TPoint &rvEnd1, float *pfIntersectionPoint )
{
	TPoint edge1Normal( rvBegin1 );
	edge1Normal.x = ( rvEnd1 - rvBegin1 ).y;
	edge1Normal.y = ( rvBegin1 - rvEnd1 ).x;

	const TPoint vEdge0 = rvEnd0 - rvBegin0;
	const float fDenominator = edge1Normal.x * vEdge0.x + edge1Normal.y * vEdge0.y;
	if ( fDenominator == 0.0f )
	{
		EClassifyEdge classifyEdge = ClassifyEdge( rvBegin1, rvEnd1, rvBegin0 );
		if ( ( classifyEdge == CE_LEFT ) || ( classifyEdge == CE_RIGHT ) )
		{
			return CI_PARALLEL;
		}
		else
		{
			return CI_COLLINEAR;
		}
	}
	else
	{
		if ( pfIntersectionPoint )
		{
			TPoint v = rvBegin0 - rvBegin1;
			( *pfIntersectionPoint ) = ( ( -1.0f ) * ( edge1Normal.x * v.x +	edge1Normal.y * v.y ) ) / fDenominator;
		}
		return CI_SKEW;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
EClassifyIntersection ClassifyCross( const TPoint &rvBegin0, const TPoint &rvEnd0,	const TPoint &rvBegin1, const TPoint &rvEnd1, float *pfIntersectionPoint )
{
	float fInnerIntersectionPoint = 0.0f;
	EClassifyIntersection innerClassifyIntersection = ClassifyIntersect( rvBegin0, rvEnd0,	rvBegin1, rvEnd1, &fInnerIntersectionPoint );
	if ( pfIntersectionPoint )
	{
		( *pfIntersectionPoint ) = fInnerIntersectionPoint;
	}
	if ( innerClassifyIntersection != CI_SKEW )
	{
		return innerClassifyIntersection;
	}
	else
	{
		if ( ( fInnerIntersectionPoint < 0.0f ) || ( fInnerIntersectionPoint > 1.0f ) )
		{
			return CI_SKEW_NO_CROSS;
		}
		else
		{
			float fOuterIntersectionPoint = 0.0f;
			EClassifyIntersection	OuterClassifyIntersection = ClassifyIntersect( rvBegin1, rvEnd1,	rvBegin0, rvEnd0, &fOuterIntersectionPoint );
			if ( ( fOuterIntersectionPoint < 0.0f ) || ( fOuterIntersectionPoint > 1.0f ) )
			{
				return CI_SKEW_NO_CROSS;
			}
			else
			{
				return CI_SKEW_CROSS;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Точка в полигоне или нет
template<class TPolygon, class TPoint>
EClassifyPolygon ClassifyConvexPolygon( const TPolygon &rPolygon, const TPoint &v )
{
	if ( rPolygon.empty() )
	{
		return CP_OUTSIDE;
	}

	typename TPolygon::const_iterator itCurrentPoint0 = rPolygon.begin();
	typename TPolygon::const_iterator itCurrentPoint1 = rPolygon.begin();
	
	++itCurrentPoint1;
	if ( itCurrentPoint1 == rPolygon.end() )
	{
		if ( ( itCurrentPoint0->x == v.x ) && ( itCurrentPoint0->y == v.y ) )
		{
			return CP_VERTEX;
		}
		else
		{
			return CP_OUTSIDE;
		}
	}
	
	EClassifyEdge classifyEdge = CE_UNKNOWN;
	while ( ( classifyEdge != CE_LEFT ) && ( classifyEdge != CE_RIGHT ) )
	{
		classifyEdge = ClassifyEdge( ( *itCurrentPoint0 ), ( *itCurrentPoint1 ), v );
		if ( classifyEdge == CE_BETWEEN )
		{
			return CP_BOUNDARY;
		}
		else if ( ( classifyEdge == CE_BEGIN ) || ( classifyEdge == CE_END ) )
		{
			return CP_VERTEX;
		}

		++itCurrentPoint0;
		if ( itCurrentPoint0 == rPolygon.end() )
		{
			return CP_OUTSIDE;
		}
		++itCurrentPoint1;
		if ( itCurrentPoint1 == rPolygon.end() )
		{
			itCurrentPoint1 = rPolygon.begin();
		}
	}
	
	EClassifyEdge negativeClassifyEdge = GetNegativeClassifyEdge( classifyEdge );
	while ( itCurrentPoint0 != rPolygon.end() )
	{
		classifyEdge = ClassifyEdge( ( *itCurrentPoint0 ), ( *itCurrentPoint1 ), v );
		if ( classifyEdge == negativeClassifyEdge )
		{
			return CP_OUTSIDE;
		}
		++itCurrentPoint0;
		++itCurrentPoint1;
		if ( itCurrentPoint1 == rPolygon.end() )
		{
			itCurrentPoint1 = rPolygon.begin();
		}
	}
	return CP_INSIDE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
EClassifyPolygon ClassifyPolygon( const TPolygon &rPolygon, const TPoint &v )
{
	if ( rPolygon.empty() )
	{
		return CP_OUTSIDE;
	}

	typename TPolygon::const_iterator itCurrentPoint0 = rPolygon.begin();
	typename TPolygon::const_iterator itCurrentPoint1 = rPolygon.begin();

	++itCurrentPoint1;
	if ( itCurrentPoint1 == rPolygon.end() )
	{
		if ( ( itCurrentPoint0->x == v.x ) && ( itCurrentPoint0->y == v.y ) )
		{
			return CP_VERTEX;
		}
		else
		{
			return CP_OUTSIDE;
		}
	}
	
	EClassifyPolygon classifyPolygon = CP_OUTSIDE;
	while ( itCurrentPoint0 != rPolygon.end() )
	{
		EClassifyEdge classifyEdge = ClassifyEdge( ( *itCurrentPoint0 ), ( *itCurrentPoint1 ), v );
		if ( classifyEdge == CE_BETWEEN )
		{
			return CP_BOUNDARY;
		}
		else if ( ( classifyEdge == CE_BEGIN ) || ( classifyEdge == CE_END ) )
		{
			return CP_VERTEX;
		}

		if ( ( itCurrentPoint1->y <= v.y ) && ( v.y < itCurrentPoint0->y ) &&
				 ( ( ( v.x - itCurrentPoint1->x ) * ( itCurrentPoint0->y - itCurrentPoint1->y )	) <
					 ( ( v.y - itCurrentPoint1->y ) * ( itCurrentPoint0->x - itCurrentPoint1->x ) ) ) )
		{
			classifyPolygon = GetNegativeClassifyPolygon( classifyPolygon );
		}
		else if ( ( itCurrentPoint0->y <= v.y ) && ( v.y < itCurrentPoint1->y ) && 
							( ( ( v.x - itCurrentPoint1->x ) * ( itCurrentPoint0->y - itCurrentPoint1->y ) ) >
								( ( v.y - itCurrentPoint1->y ) * ( itCurrentPoint0->x - itCurrentPoint1->x ) ) ) )
		{
			classifyPolygon = GetNegativeClassifyPolygon( classifyPolygon );
		}

		++itCurrentPoint0;
		++itCurrentPoint1;
		if ( itCurrentPoint1 == rPolygon.end() )
		{
			itCurrentPoint1 = rPolygon.begin();
		}
	}
	return classifyPolygon;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
EClassifyPolygon ClassifyPolygon( const TPolygon &rPolygon, const TPolygon &rPolygonCheck )
{
	EClassifyPolygon classifyPolygonInside = CP_INSIDE;	
	EClassifyPolygon classifyPolygonOutside = CP_OUTSIDE;	
	for ( typename TPolygon::const_iterator itPoint = rPolygonCheck.begin(); itPoint != rPolygonCheck.end(); ++itPoint )
	{
		if ( ClassifyPolygon<TPolygon, TPoint>( rPolygon, *itPoint ) != CP_OUTSIDE )
		{
			classifyPolygonOutside = CP_INSIDE;
		}
		else
		{
			classifyPolygonInside = CP_OUTSIDE;
		}
	}
	if ( classifyPolygonInside == classifyPolygonOutside )
	{
		return classifyPolygonInside;
	}
	else
	{
		return CP_UNKNOWN;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Периметр полигона
template<class TPolygon>
float GetPolygonPerimeter( const TPolygon &rPolygon )
{
	//ноль точек
	if ( rPolygon.empty() )
	{
		return 0.0f;
	}

	typename TPolygon::const_iterator itCurrentPoint0 = rPolygon.begin();
	typename TPolygon::const_iterator itCurrentPoint1 = rPolygon.begin();
	++itCurrentPoint1;
	//одна точка
	if ( itCurrentPoint1 == rPolygon.end() )
	{
		return 0.0f;
	}

	float fPerimeter = 0;
	while ( itCurrentPoint0 != rPolygon.end() )
	{
		fPerimeter += fabs( ( *itCurrentPoint1 ) - ( *itCurrentPoint0 ) );

		++itCurrentPoint0;
		++itCurrentPoint1;
		if ( itCurrentPoint1 == rPolygon.end() )
		{
			itCurrentPoint1 = rPolygon.begin();
		}
	}
	return fPerimeter;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Площадь полигона
template<class TPolygon>
float GetSignedPolygonSquare( const TPolygon &rPolygon )
{
	//ноль точек
	if ( rPolygon.empty() )
	{
		return 0.0f;
	}

	typename TPolygon::const_iterator itCurrentPoint0 = rPolygon.begin();
	typename TPolygon::const_iterator itCurrentPoint1 = rPolygon.begin();
	typename TPolygon::const_iterator itCurrentPoint2 = rPolygon.begin();
	++itCurrentPoint1;
	++itCurrentPoint2;
	//одна точка
	if ( itCurrentPoint1 == rPolygon.end() )
	{
		return 0.0f;
	}
	++itCurrentPoint2;
	//две точки
	if ( itCurrentPoint2 == rPolygon.end() )
	{
		return 0.0f;
	}

	float fSquare = 0;
	while ( itCurrentPoint0 != rPolygon.end() )
	{
		fSquare += ( itCurrentPoint1->x * ( itCurrentPoint2->y - itCurrentPoint0->y ) );

		++itCurrentPoint0;
		++itCurrentPoint1;
		++itCurrentPoint2;
		if ( itCurrentPoint1 == rPolygon.end() )
		{
			itCurrentPoint1 = rPolygon.begin();
		}
		if ( itCurrentPoint2 == rPolygon.end() )
		{
			itCurrentPoint2 = rPolygon.begin();
		}
	}
	return ( fSquare / 2.0f );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Центральная точка
template<class TPolygon, class TPoint>
bool GetPolygonMassCenter( const TPolygon &rPolygon, TPoint *pvMassCenter )
{
	//ноль точек
	if ( rPolygon.empty() )
	{
		return false;
	}

	int nPointCount = 1;
	typename TPolygon::const_iterator itPoint = rPolygon.begin();
	( *pvMassCenter ) = ( *itPoint );
	++itPoint;
	for ( ; itPoint != rPolygon.end(); ++itPoint )
	{
		( *pvMassCenter ) += ( *itPoint );
		++nPointCount;
	}
	( *pvMassCenter ) = ( *pvMassCenter ) / nPointCount;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
EClassifyRotation ClassifyRotation( const TPoint &v0, const TPoint &v1, const TPoint &v2 )
{
	const EClassifyEdge classifyEdge = ClassifyEdge( v0, v1, v2 );
	if ( classifyEdge == CE_RIGHT )
	{
		return CR_CLOCKWISE;
	}
	if ( classifyEdge == CE_LEFT )
	{
		return CR_COUNTERCLOCKWISE;
	}
	return CR_LINE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon>
EClassifyRotation ClassifyRotation( const TPolygon &rPolygon )
{
	const float fPolygonSquare = GetSignedPolygonSquare( rPolygon );	
	if ( fPolygonSquare < 0	)
	{
		return CR_CLOCKWISE;
	}
	else if ( fPolygonSquare > 0 )
	{
		return CR_COUNTERCLOCKWISE;
	}
	return CR_LINE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
float GetSignedAngle( const TPoint &rvBegin, const TPoint &rvEnd, const TPoint &v )
{
	const TPoint vBeginV = rvBegin - v;
	const TPoint vEndV = rvEnd - v;
	const float fvBeginVAngle = GetPolarAngle( vBeginV );
	const float fvEndVAngle = GetPolarAngle( vEndV );
	if ( fvBeginVAngle == ( -1.0f ) || ( fvEndVAngle == ( -1.0f ) ) )
	{
		return FP_PI;
	}
	else
	{
		const float fEngle = fvEndVAngle - fvBeginVAngle;
		if ( ( fEngle == FP_PI ) || ( fEngle == ( -FP_PI ) ) )
		{
			return FP_PI;
		}
		else if ( fEngle < ( -FP_PI ) )
		{
			return ( fEngle + FP_2PI ); 
		}
		else if ( fEngle > FP_PI )
		{
			return FP_2PI - fEngle;
		}
		return fEngle;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon>
TPolygon GetPointOnEdge( const TPolygon &rvBegin, const TPolygon &rvEnd, float fPoint )
{
	return ( rvBegin + fPoint * ( rvEnd - rvBegin ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CVec2 CreateFromPolarCoord( float r, float a ) { return CVec2( r * cos( a ), r * sin( a ) ); }
inline CVec3 CreateFromPolarCoord( float r, float a, float fZ ) { return CVec3( r * cos( a ), r * sin( a ), fZ ); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
float GetPolarAngle( const TPoint &v )
{
	if ( ( v.x == 0.0f ) && ( v.y == 0.0f ) )
	{
		return -1.0f;
	}
	else if ( v.x == 0.0f )
	{
		return ( ( v.y > 0.0f ) ? ( FP_PI2 ) : ( FP_PI + FP_PI2 ) );
	}
	else
	{
		float a = atan( v.y / v.x );
		if ( v.x > 0.0f )
		{
			return ( ( v.y >= 0.0f ) ? ( a ) : ( FP_2PI + a ) );
		}
		else
		{
			return ( FP_PI + a );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
float GetPolarLength( const TPoint &v )
{
	return fabs( v.x, v.y );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
TPoint GetNormal( const TPoint &v )
{
	TPoint vNormal = v;
	vNormal.x = -v.y;
	vNormal.y = v.x;
	return vNormal;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
inline void MovePoint( TPoint *pPoint, const TPoint &rvMove ) { ( *pPoint ) += rvMove; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
inline void RotatePoint( TPoint *pPoint, float a )
{ 
	const float fX = pPoint->x;
	const float fSinA = sin( a );
	const float fCosA = cos( a );
	pPoint->x = ( fX * fCosA ) - ( pPoint->y * fSinA );
	pPoint->y = ( fX * fSinA ) + ( pPoint->y * fCosA );
}
template<class TPoint>
inline void RotatePoint( TPoint *pPoint, float a, const TPoint &rCenterPoint ) { TPoint point = ( *pPoint ) - rCenterPoint; RotatePoint( &point, a ); ( *pPoint ) = point + rCenterPoint; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void NormalazeDirection( float *pDirection )
{
	if ( pDirection != 0 )
	{
		while ( ( *pDirection ) > FP_2PI )
		{
			( *pDirection ) = ( *pDirection ) - FP_2PI;
		}
		while ( ( *pDirection ) < 0.0f )
		{
			( *pDirection ) = ( *pDirection ) + FP_2PI;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
void MovePoints( TPolygon *pPolygon, const TPoint &rvMove )
{
	for ( typename TPolygon::iterator itPoint = pPolygon->begin(); itPoint != pPolygon->end(); ++itPoint )
	{
		MovePoint<TPoint>( &( *itPoint ), rvMove );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
void RotatePoints( TPolygon *pPolygon, float a )
{
	const float fSinA = sin( a );
	const float fCosA = cos( a );
	for ( typename TPolygon::iterator itPoint = pPolygon->begin(); itPoint != pPolygon->end(); ++itPoint )
	{
		const float fX = itPoint->x;
		itPoint->x = ( fX * fCosA ) - ( itPoint->y * fSinA );
		itPoint->y = ( fX * fSinA ) + ( itPoint->y * fCosA );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
void RotatePoints( TPolygon *pPolygon, float a, const TPoint &rCenterPoint )
{
	const float fSinA = sin( a );
	const float fCosA = cos( a );
	for ( typename TPolygon::iterator itPoint = pPolygon->begin(); itPoint != pPolygon->end(); ++itPoint )
	{
		TPoint point = ( *itPoint ) - rCenterPoint;
		const float fX = point.x;
		point.x = ( fX * fCosA ) - ( point.y * fSinA );
		point.y = ( fX * fSinA ) + ( point.y * fCosA );
		( *itPoint ) = point + rCenterPoint;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
void RotateEdgeToPI2( TPoint *pvBegin, TPoint *pvEnd )
{
	NI_ASSERT( ( pvBegin != 0 ) && ( pvEnd != 0 ),
						 NStr::StrFmt( "Wrong parameters: pvBegin %x, pvEnd %x\n", pvBegin, pvEnd ) );

	const TPoint m = 0.5f * ( ( *pvBegin ) + ( *pvEnd ) );
	const TPoint v = ( *pvEnd ) - ( *pvBegin );
	TPoint vNormal = GetNormal( v );
	( *pvBegin ) = m - 0.5f * vNormal;
	( *pvEnd ) = m + 0.5f * vNormal;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
void FlipEdgeToPI( TPoint *pvBegin, TPoint *pvEnd )
{
	NI_ASSERT( ( pvBegin != 0 ) && ( pvEnd != 0 ),
						 NStr::StrFmt( "Wrong parameters: pvBegin %x, pvEnd %x\n", pvBegin, pvEnd ) );

	const TPoint vTemp = ( *pvEnd );
	( *pvEnd ) = ( *pvBegin );
	( *pvBegin ) = vTemp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
bool SplitByEdge( const TPolygon &rSourcePolygon, const TPoint &rvBegin, const TPoint &rvEnd, TPolygon *pLeftPolygon, TPolygon *pRightPolygon )
{
	if ( pLeftPolygon )
	{
		pLeftPolygon->clear();
	}
	if( pRightPolygon )
	{
		pRightPolygon->clear();
	}

	if ( rSourcePolygon.empty() )
	{
		return true;
	}

	typename TPolygon::const_iterator itSourcePoint0 = rSourcePolygon.begin();
	typename TPolygon::const_iterator itSourcePoint1 = rSourcePolygon.begin();

	++itSourcePoint1;
	if ( itSourcePoint1 == rSourcePolygon.end() )
	{
		EClassifyEdge classifyEdge = ClassifyEdge( rvBegin, rvEnd, ( *itSourcePoint0 ) );
		if ( classifyEdge != CE_LEFT )
		{
			if ( pRightPolygon )
			{
				pRightPolygon->push_back( ( *itSourcePoint0 ) );
			}
		}
		if ( classifyEdge != CE_RIGHT )
		{
			if ( pLeftPolygon )
			{
				pLeftPolygon->push_back( ( *itSourcePoint0 ) );
			}
		}
		return true;
	}
	
	while ( itSourcePoint0 != rSourcePolygon.end() )
	{
		const EClassifyEdge beginClassifyEdge = ClassifyEdge( rvBegin, rvEnd, ( *itSourcePoint0 ) );
		const EClassifyEdge endClassifyEdge = ClassifyEdge( rvBegin, rvEnd, ( *itSourcePoint1 ) );

		float fIntersectPoint = 0.0f;
		const EClassifyIntersection classifyIntersect = ClassifyIntersect( rvBegin, rvEnd, ( *itSourcePoint0 ), ( *itSourcePoint1 ), &fIntersectPoint );

		TPoint vIntersectionPoint;
		if ( classifyIntersect == CI_SKEW )
		{
			vIntersectionPoint = GetPointOnEdge( rvBegin, rvEnd, fIntersectPoint );
		}

		if ( beginClassifyEdge == CE_RIGHT )
		{
			if ( endClassifyEdge != CE_RIGHT )
			{
				NI_ASSERT( classifyIntersect == CI_SKEW,
									 NStr::StrFmt( "Invalid Intersection: ( %g, %g )--( %g, %g ) with ( %g, %g )--( %g, %g )",
													 rvBegin.x, rvBegin.y, rvEnd.x, rvEnd.y,
													 itSourcePoint0->x, itSourcePoint0->x, itSourcePoint1->x, itSourcePoint1->y ) );
				if ( classifyIntersect != CI_SKEW )
				{
					return false;
				}
				if ( pRightPolygon )
				{
					pRightPolygon->push_back( vIntersectionPoint );
				}
				if ( pLeftPolygon )
				{
					if ( endClassifyEdge == CE_LEFT ) 
					{
						pLeftPolygon->push_back( vIntersectionPoint );
					}
					pLeftPolygon->push_back( *itSourcePoint1 );
				}
			}
			else
			{
				if ( pRightPolygon )
				{
					pRightPolygon->push_back( *itSourcePoint1 );
				}
			}
		}
		else if ( beginClassifyEdge == CE_LEFT )
		{
			if ( endClassifyEdge != CE_LEFT )
			{
				NI_ASSERT( classifyIntersect == CI_SKEW,
									 NStr::StrFmt( "Invalid Intersection: ( %g, %g )--( %g, %g ) with ( %g, %g )--( %g, %g )",
													 rvBegin.x, rvBegin.y, rvEnd.x, rvEnd.y,
													 itSourcePoint0->x, itSourcePoint0->x, itSourcePoint1->x, itSourcePoint1->y ) );
				if ( classifyIntersect != CI_SKEW )
				{
					return false;
				}
				if ( pRightPolygon )
				{
					if ( endClassifyEdge == CE_RIGHT ) 
					{
						pRightPolygon->push_back( vIntersectionPoint );
					}
					pRightPolygon->push_back( *itSourcePoint1 );

				}
				if ( pLeftPolygon )
				{
					pLeftPolygon->push_back( vIntersectionPoint );
				}
			}
			else
			{
				if ( pLeftPolygon )
				{
					pLeftPolygon->push_back( *itSourcePoint1 );
				}
			}
		}
		else
		{
			if ( endClassifyEdge == CE_RIGHT )
			{
				if ( pRightPolygon )
				{
					pRightPolygon->push_back( *itSourcePoint1 );
				}
			}
			else if ( endClassifyEdge == CE_LEFT )
			{
				if ( pLeftPolygon )
				{
					pLeftPolygon->push_back( *itSourcePoint1 );
				}
			}
			else
			{
				if ( pRightPolygon )
				{
					pRightPolygon->push_back( *itSourcePoint1 );
				}
				if ( pLeftPolygon )
				{
					pLeftPolygon->push_back( *itSourcePoint1 );
				}
			}
		}

		++itSourcePoint0;
		++itSourcePoint1;
		if ( itSourcePoint1 == rSourcePolygon.end() )
		{
			itSourcePoint1 = rSourcePolygon.begin();
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
bool CutByPolygonCore( const TPolygon &rPolygon, const TPolygon &rPolygonCore, TPolygon *pCutPolygon )
{
	NI_ASSERT( pCutPolygon != 0, NStr::StrFmt( "CutByPolygonCore() Wrong parameter: pCutPolygon %x\n", pCutPolygon ) );

	if ( rPolygonCore.empty() )
	{
		( *pCutPolygon ) = rPolygon;
		return true;
	}
	typename TPolygon::const_iterator itCurrentPoint0 = rPolygonCore.begin();
	typename TPolygon::const_iterator itCurrentPoint1 = rPolygonCore.begin();
	++itCurrentPoint1;
	if ( itCurrentPoint1 == rPolygonCore.end() )
	{
		( *pCutPolygon ) = rPolygon;
		return true;
	}
	EClassifyRotation classifyRotation = ClassifyRotation( rPolygonCore );
	if ( classifyRotation == CR_LINE )
	{
		( *pCutPolygon ) = rPolygon;
		return true;
	}
	TPolygon polygon0;
	TPolygon polygon1;
	polygon0.insert( polygon0.end(), rPolygon.begin(), rPolygon.end() );

	int nCount = 0;
	while ( itCurrentPoint0 != rPolygonCore.end() )
	{
		TPoint vBegin = ( *itCurrentPoint0 );
		TPoint vEnd = ( *itCurrentPoint1 );
		if ( ( nCount & 0x01 ) > 0 )
		{
			if ( classifyRotation == CR_CLOCKWISE )
			{
				SplitByEdge( polygon1, vBegin, vEnd, static_cast<TPolygon*>( 0 ), &polygon0 );
			}
			else
			{
				SplitByEdge( polygon1, vBegin, vEnd, &polygon0, static_cast<TPolygon*>( 0 ) );
			}
			polygon1.clear();
		}
		else
		{
			if ( classifyRotation == CR_CLOCKWISE )
			{
				SplitByEdge( polygon0, vBegin, vEnd, static_cast<TPolygon*>( 0 ), &polygon1 );
			}
			else
			{
				SplitByEdge( polygon0, vBegin, vEnd, &polygon1, static_cast<TPolygon*>( 0 ) );
			}
			polygon0.clear();
		}
		++nCount;
		
		++itCurrentPoint0;
		++itCurrentPoint1;
		if ( itCurrentPoint1 == rPolygonCore.end() )
		{
			itCurrentPoint1 = rPolygonCore.begin();
		}
	}

	pCutPolygon->clear();
	if ( ( nCount & 0x01 ) > 0 )
	{
		pCutPolygon->insert( pCutPolygon->end(), polygon1.begin(), polygon1.end() );
	}
	else
	{
		pCutPolygon->insert( pCutPolygon->end(), polygon0.begin(), polygon0.end() );
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
bool GetVoronoyPolygon( const TPolygon &rBoundingPolygon, const TPolygon &rPoints, const vector<float> &weights, const TPoint &rPoint, float fWeight, TPolygon *pVoronoyPolygon )
{
	NI_ASSERT( pVoronoyPolygon != 0, NStr::StrFmt( "Wrong parameter: pVoronoyPolygon %x\n", pVoronoyPolygon ) );
	ASSERT( rPoints.size() == weights.size() );

	if ( rBoundingPolygon.empty() )
	{
		return true;
	}

	TPolygon polygon0;
	TPolygon polygon1;
	polygon0.insert( polygon0.end(), rBoundingPolygon.begin(), rBoundingPolygon.end() );

	int nCount = 0;

	for ( int i = 0; i < rPoints.size(); ++i )
	{
		if ( ( rPoints[i].x != rPoint.x ) || ( rPoints[i].y != rPoint.y ) )
		{
			TPoint vBegin = rPoint;
			TPoint vEnd = rPoints[i];
			TPoint vOffset = ( vEnd - vBegin ) *	( fWeight - weights[i] ) / ( fWeight + weights[i] ) / 2.f;
			RotateEdgeToPI2( &vBegin, &vEnd );
			vBegin += vOffset;
			vEnd += vOffset;
			
			if ( ( nCount & 0x01 ) > 0 )
			{
				SplitByEdge( polygon1, vBegin, vEnd, &polygon0, static_cast<TPolygon*>( 0 ) );
				polygon1.clear();
			}
			else
			{
				SplitByEdge( polygon0, vBegin, vEnd, &polygon1, static_cast<TPolygon*>( 0 ) );
				polygon0.clear();
			}
			++nCount;
		}
	}

	pVoronoyPolygon->clear();
	if ( ( nCount & 0x01 ) > 0 )
	{
		pVoronoyPolygon->insert( pVoronoyPolygon->end(), polygon1.begin(), polygon1.end() );
	}
	else
	{
		pVoronoyPolygon->insert( pVoronoyPolygon->end(), polygon0.begin(), polygon0.end() );
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
bool GetVoronoyPolygon( const TPolygon &rBoundingPolygon, const TPolygon &rPoints, const TPoint &rPoint, TPolygon *pVoronoyPolygon )
{
	NI_ASSERT( pVoronoyPolygon != 0, NStr::StrFmt( "Wrong parameter: pVoronoyPolygon %x\n", pVoronoyPolygon ) );

	if ( rBoundingPolygon.empty() )
	{
		return true;
	}

	TPolygon polygon0;
	TPolygon polygon1;
	polygon0.insert( polygon0.end(), rBoundingPolygon.begin(), rBoundingPolygon.end() );

	int nCount = 0;
	
	for ( typename TPolygon::const_iterator itPoint = rBoundingPolygon.begin(); itPoint != rBoundingPolygon.end(); ++itPoint )
	{
		if ( ( itPoint->x != rPoint.x ) || ( itPoint->y != rPoint.y ) )
		{
			TPoint vBegin = rPoint;
			TPoint vEnd = ( *itPoint );
			RotateEdgeToPI2( &vBegin, &vEnd );
			
			if ( ( nCount & 0x01 ) > 0 )
			{
				SplitByEdge( polygon1, vBegin, vEnd, &polygon0, static_cast<TPolygon*>( 0 ) );
				polygon1.clear();
			}
			else
			{
				SplitByEdge( polygon0, vBegin, vEnd, &polygon1, static_cast<TPolygon*>( 0 ) );
				polygon0.clear();
			}
			++nCount;
		}
	}

	for ( typename TPolygon::const_iterator itPoint = rPoints.begin(); itPoint != rPoints.end(); ++itPoint )
	{
		if ( ( itPoint->x != rPoint.x ) || ( itPoint->y != rPoint.y ) )
		{
			TPoint vBegin = rPoint;
			TPoint vEnd = ( *itPoint );
			RotateEdgeToPI2( &vBegin, &vEnd );
			
			if ( ( nCount & 0x01 ) > 0 )
			{
				SplitByEdge( polygon1, vBegin, vEnd, &polygon0, static_cast<TPolygon*>( 0 ) );
				polygon1.clear();
			}
			else
			{
				SplitByEdge( polygon0, vBegin, vEnd, &polygon1, static_cast<TPolygon*>( 0 ) );
				polygon0.clear();
			}
			++nCount;
		}
	}

	pVoronoyPolygon->clear();
	if ( ( nCount & 0x01 ) > 0 )
	{
		pVoronoyPolygon->insert( pVoronoyPolygon->end(), polygon1.begin(), polygon1.end() );
	}
	else
	{
		pVoronoyPolygon->insert( pVoronoyPolygon->end(), polygon0.begin(), polygon0.end() );
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
bool GetVoronoyPolygon( const TPolygon &rBoundingPolygon, const TPoint &rPoint, TPolygon *pVoronoyPolygon )
{
	const TPolygon points;
	return GetVoronoyPolygon( rBoundingPolygon, points, rPoint, pVoronoyPolygon );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Убирание пар точек из вектора расположенных на расстоянии fRange между друг другом
//возвращает число удаленных элементов
template<class TPolygon, class TPoint>
void UniquePolygon( TPolygon *pPolygon, float fRange )
{
	NI_ASSERT( pPolygon != 0, NStr::StrFmt( "Wrong parameter: %x\n", pPolygon ) );
	pPolygon->erase( unique( pPolygon->begin(), pPolygon->end(), SInRangeFunctional<TPoint>( fRange ) ), pPolygon->end() );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPoint>
inline void UpdateBoundingBox( TPoint *pvMin, TPoint *pvMax, const TPoint &rvPoint )
{
	if ( pvMin->x > rvPoint.x )
	{
		pvMin->x = rvPoint.x;
	}
	else if ( pvMax->x < rvPoint.x )
	{
		pvMax->x = rvPoint.x;
	}
	//
	if ( pvMin->y > rvPoint.y )
	{
		pvMin->y = rvPoint.y;
	}
	else if ( pvMax->y < rvPoint.y )
	{
		pvMax->y = rvPoint.y;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Минимальный прямоугольник в корорый входят все точки полигона
template<class TPolygon>
void GetPolygonBoundingBox( const TPolygon &rPolygon, CTRect<float> *pBoundingBox )
{
	NI_ASSERT( pBoundingBox != 0, NStr::StrFmt( "Wrong parameter: %x\n", pBoundingBox ) );

	pBoundingBox->Set( 0.0f, 0.0f, 0.0f, 0.0f );
	//вырожденный случай
	if ( !rPolygon.empty() )
	{
		typename TPolygon::const_iterator itPoint = rPolygon.begin();
		pBoundingBox->Set( itPoint->x, itPoint->y, itPoint->x, itPoint->y );
		for ( ++itPoint; itPoint != rPolygon.end(); ++itPoint )
		{
			if ( pBoundingBox->minx > itPoint->x )
			{
				pBoundingBox->minx = itPoint->x;
			}
			else if ( pBoundingBox->maxx < itPoint->x )
			{
				pBoundingBox->maxx = itPoint->x;
			}
			if ( pBoundingBox->miny > itPoint->y )
			{
				pBoundingBox->miny = itPoint->y;
			}
			else if ( pBoundingBox->maxy < itPoint->y )
			{
				pBoundingBox->maxy = itPoint->y;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon>
inline CTRect<float> GetPolygonBoundingBox( const TPolygon &rPolygon )
{
	CTRect<float> boundingBox( 0.0f, 0.0f, 0.0f, 0.0f );
	GetPolygonBoundingBox( rPolygon, &boundingBox );
	return boundingBox;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// *----|--------------------|----*
//			|
//			|
//	fMinSideDistanceRatio ( 0.0f ... 0.5f )
//	
//	rShiftRatio - пределы относительного отклонения новой точки от отрезка
//
template<class TPoint>
TPoint GetRandomEdgePoint( const TPoint &rvBegin, const TPoint &rvEnd, float fMinSideDistanceRatio, const CTPoint<float> &rShiftRatio, EClassifyEdge classifyEdge )
{
	NI_ASSERT( ( fMinSideDistanceRatio >= 0.0f ) && ( fMinSideDistanceRatio <= 0.5f ), NStr::StrFmt( "Invalid fMinSideDistanceRatio %g [0, 0.5]", fMinSideDistanceRatio ) );
	NI_ASSERT( rShiftRatio.min <= rShiftRatio.max, NStr::StrFmt( "Invalid fShiftRatio %g < %g", rShiftRatio.min, rShiftRatio.max ) );
	
	const TPoint vEdge = rvEnd - rvBegin;
	
	TPoint vNormal = GetNormal( vEdge );
	Normalize( &vNormal );
	
	const float fPoint = NWin32Random::Random( fMinSideDistanceRatio, 1.0f - fMinSideDistanceRatio );
	TPoint vPoint = GetPointOnEdge( rvBegin, rvEnd, fPoint );

	const float fShift = fabs( rvBegin - rvEnd ) * NWin32Random::Random( rShiftRatio.min, rShiftRatio.max );
	if ( classifyEdge == CE_LEFT )
	{
		vPoint += vNormal * fShift;
	}
	else if ( classifyEdge == CE_RIGHT )
	{
		vPoint -= vNormal * fShift;
	}
	
	return vPoint;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
bool RandomizeEdges( const TPolygon &rSourceSequence, int nDepth, float fMinSideDistanceRatio, const CTPoint<float> &rShiftRatio, TPolygon *pRandomizedSequence, float fMinEdgeLength, float fMaxEdgeLength, bool bPolygon )
{
	NI_ASSERT( pRandomizedSequence != 0, NStr::StrFmt( "Wrong parameter: pRandomizedSequence %x\n", pRandomizedSequence ) );

	if ( rSourceSequence.empty() )
	{
		return true;
	}
	else
	{
		typename TPolygon::const_iterator itTestSourcePoint = rSourceSequence.begin();
		++itTestSourcePoint;
		if ( itTestSourcePoint == rSourceSequence.end() )
		{
			return true;
		}
	}

	const float fMinEdgeLength2 = fabs2( fMinEdgeLength );
	const float fMaxEdgeLength2 = fabs2( fMaxEdgeLength );
	CTPoint<float> onLineShiftRatio( 0.0f, 0.0f );
	TPolygon sequence0;
	TPolygon sequence1;
	sequence0.insert( sequence0.end(), rSourceSequence.begin(), rSourceSequence.end() );
	
	int nCount = 0;
	while ( nCount < nDepth )
	{
		bool bNewPointsNotInserted = true;
		if ( ( nCount & 0x01 ) > 0 )
		{
			sequence0.clear();
			typename TPolygon::const_iterator itSourcePoint0 = sequence1.begin();
			typename TPolygon::const_iterator itSourcePoint1 = sequence1.begin();
			++itSourcePoint1;
			EClassifyEdge classifyEdge = ( NWin32Random::Random( 2 ) > 0 ) ? CE_LEFT : CE_RIGHT;
			while ( itSourcePoint0 != sequence1.end() )
			{
				sequence0.push_back( ( *itSourcePoint0 ) );
				const float fEdgeLength2 = fabs2( ( *itSourcePoint1 ) - ( *itSourcePoint0 ) );
				if ( fEdgeLength2 > fMaxEdgeLength2 )
				{
					sequence0.push_back( GetRandomEdgePoint( ( *itSourcePoint0 ), ( *itSourcePoint1 ), fMinSideDistanceRatio, onLineShiftRatio, classifyEdge ) );
					classifyEdge = GetNegativeClassifyEdge( classifyEdge );
					bNewPointsNotInserted = false;
				}
				else if ( fEdgeLength2 > fMinEdgeLength2 )
				{
					sequence0.push_back( GetRandomEdgePoint( ( *itSourcePoint0 ), ( *itSourcePoint1 ), fMinSideDistanceRatio, rShiftRatio, classifyEdge ) );
					classifyEdge = GetNegativeClassifyEdge( classifyEdge );
					bNewPointsNotInserted = false;
				}					
				++itSourcePoint0;
				++itSourcePoint1;
				
				if ( itSourcePoint1 == sequence1.end() )
				{
					if ( bPolygon )
					{
						itSourcePoint1 = sequence1.begin();
					}
					else
					{
						sequence0.push_back( ( *itSourcePoint0 ) );
						break;
					}
				}
			}
		}
		else
		{
			sequence1.clear();
			typename TPolygon::const_iterator itSourcePoint0 = sequence0.begin();
			typename TPolygon::const_iterator itSourcePoint1 = sequence0.begin();
			++itSourcePoint1;
			EClassifyEdge classifyEdge = ( NWin32Random::Random( 2 ) > 0 ) ? CE_LEFT : CE_RIGHT;
			while ( itSourcePoint0 != sequence0.end() )
			{
				sequence1.push_back( ( *itSourcePoint0 ) );
				const float fEdgeLength2 = fabs2( ( *itSourcePoint1 ) - ( *itSourcePoint0 ) );
				if ( fEdgeLength2 > fMaxEdgeLength2 )
				{
					sequence1.push_back( GetRandomEdgePoint( ( *itSourcePoint0 ), ( *itSourcePoint1 ), fMinSideDistanceRatio, onLineShiftRatio, classifyEdge ) );
					classifyEdge = GetNegativeClassifyEdge( classifyEdge );
					bNewPointsNotInserted = false;
				}
				else	if ( fEdgeLength2 > fMinEdgeLength2 )
				{
					sequence1.push_back( GetRandomEdgePoint( ( *itSourcePoint0 ), ( *itSourcePoint1 ), fMinSideDistanceRatio, rShiftRatio, classifyEdge ) );
					classifyEdge = GetNegativeClassifyEdge( classifyEdge );
					bNewPointsNotInserted = false;
				}
				++itSourcePoint0;
				++itSourcePoint1;
				
				if ( itSourcePoint1 == sequence0.end() )
				{
					if ( bPolygon )
					{
						itSourcePoint1 = sequence0.begin();
					}
					else
					{
						sequence1.push_back( ( *itSourcePoint0 ) );
						break;
					}
				}
			}
		}
		++nCount;
		if	( bNewPointsNotInserted )
		{
			break;
		}
	}

	pRandomizedSequence->clear();
	if ( ( nCount & 0x01 ) > 0 )
	{
		pRandomizedSequence->insert( pRandomizedSequence->end(), sequence1.begin(), sequence1.end() );
	}
	else
	{
		pRandomizedSequence->insert( pRandomizedSequence->end(), sequence0.begin(), sequence0.end() );
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TPolygon, class TPoint>
bool EnlargePolygonCore( const TPolygon &rBoundingPolygon, const TPolygon &rPolygon, float fDistance, TPolygon *pEnlargedPolygon )
{
	NI_ASSERT( pEnlargedPolygon != 0, NStr::StrFmt( "Wrong parameter: pEnlargedPolygon %x\n", pEnlargedPolygon ) );

	typename TPolygon::const_iterator itCurrentPoint0 = rPolygon.begin();
	typename TPolygon::const_iterator itCurrentPoint1 = rPolygon.begin();
	++itCurrentPoint1;
	if ( itCurrentPoint1 == rPolygon.end() )
	{
		pEnlargedPolygon->clear();
		return false;
	}
	else
	{
		typename TPolygon::const_iterator itCurrentPoint2 = itCurrentPoint1;
		++itCurrentPoint2;
		if ( itCurrentPoint2 == rPolygon.end() )
		{
			pEnlargedPolygon->clear();
			return false;
		}
	}

	EClassifyRotation classifyRotation = ClassifyRotation( rPolygon );
	if ( classifyRotation == CR_LINE )
	{
		pEnlargedPolygon->clear();
		return false;
	}
	else if ( classifyRotation == CR_COUNTERCLOCKWISE )
	{
		fDistance *= ( -1 );
	}

	TPolygon polygon0;
	TPolygon polygon1;
	polygon0.insert( polygon0.end(), rBoundingPolygon.begin(), rBoundingPolygon.end() );

	int nCount = 0;
	while ( itCurrentPoint0 != rPolygon.end() )
	{
		TPoint vBegin = ( *itCurrentPoint0 );
		TPoint vEnd = ( *itCurrentPoint1 );
		TPoint vNormal = GetNormal( vEnd - vBegin );
		Normalize( &vNormal );

		vBegin += vNormal * fDistance;
		vEnd += vNormal * fDistance;

		if ( ( nCount & 0x01 ) > 0 )
		{
			if ( classifyRotation == CR_CLOCKWISE )
			{
				SplitByEdge( polygon1, vBegin, vEnd, static_cast<TPolygon*>( 0 ), &polygon0 );
			}
			else
			{
				SplitByEdge( polygon1, vBegin, vEnd, &polygon0, static_cast<TPolygon*>( 0 ) );
			}
			polygon1.clear();
		}
		else
		{
			if ( classifyRotation == CR_CLOCKWISE )
			{
				SplitByEdge( polygon0, vBegin, vEnd, static_cast<TPolygon*>( 0 ), &polygon1 );
			}
			else
			{
				SplitByEdge( polygon0, vBegin, vEnd, &polygon1, static_cast<TPolygon*>( 0 ) );
			}
			polygon0.clear();
		}
		++nCount;
		
		++itCurrentPoint0;
		++itCurrentPoint1;
		if ( itCurrentPoint1 == rPolygon.end() )
		{
			itCurrentPoint1 = rPolygon.begin();
		}
	}

	pEnlargedPolygon->clear();
	if ( ( nCount & 0x01 ) > 0 )
	{
		pEnlargedPolygon->insert( pEnlargedPolygon->end(), polygon1.begin(), polygon1.end() );
	}
	else
	{
		pEnlargedPolygon->insert( pEnlargedPolygon->end(), polygon0.begin(), polygon0.end() );
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 0 - на границе
// > 0 - внутри
// < 0 - снарукжи
template<class TPolygon, class TPoint>
float PolygonDistance( const TPolygon &rPolygon, const TPoint &v, bool bPolygon )
{
	//нет точек
	if ( rPolygon.empty() )
	{
		return 0.0;
	}

	typename TPolygon::const_iterator itCurrentPoint0 = rPolygon.begin();
	typename TPolygon::const_iterator itCurrentPoint1 = rPolygon.begin();

	//одна точка
	++itCurrentPoint1;
	if ( itCurrentPoint1 == rPolygon.end() )
	{
		return fabs( v - ( *itCurrentPoint0 ) );
	}
	
	EClassifyPolygon classifyPolygon = ClassifyPolygon( rPolygon, v );
	
	//точка на границе полигона
	if ( ( classifyPolygon == CP_BOUNDARY ) || ( classifyPolygon == CP_VERTEX ) )
	{
		return 0.0f;
	}

	float fDistance = fabs( v	- ( *itCurrentPoint0 ) );
	//определяем минимальное расстояние для стороны и для вертекса стороны
	while ( itCurrentPoint0 != rPolygon.end() )
	{
		//( *itCurrentPoint0 );
		//( *itCurrentPoint1 );

		//расстояние до точки ( *itCurrentPoint0 )
		const float fVertexDistance = fabs( v - ( *itCurrentPoint0 ) );
		if ( fVertexDistance < fDistance )
		{
			fDistance = fVertexDistance;
		}
		
		//скялярные произведения
		const float dotPoduct_v0_10 = ( v - ( *itCurrentPoint0 ) ) * ( ( *itCurrentPoint1 ) - ( *itCurrentPoint0 ) );
		const float dotPoduct_v1_01 = ( v - ( *itCurrentPoint1 ) ) * ( ( *itCurrentPoint0 ) - ( *itCurrentPoint1 ) );
		
		//проекция внутри отрезка
		if ( ( dotPoduct_v0_10 > FP_EPSILON ) && ( dotPoduct_v1_01 > FP_EPSILON ) )
		{
			const float fEdgeDistance = fVertexDistance * sqrt( 1 - fabs2( dotPoduct_v0_10 / ( fVertexDistance * fabs( ( *itCurrentPoint1 ) - ( *itCurrentPoint0 ) ) ) ) );	
			if ( fEdgeDistance < fDistance )
			{
				fDistance = fEdgeDistance;
			}
		}
		
		++itCurrentPoint0;
		++itCurrentPoint1;
		if ( itCurrentPoint1 == rPolygon.end() )
		{
			if ( bPolygon )
			{
				itCurrentPoint1 = rPolygon.begin();
			}
			else
			{
				break;
			}
		}
	}
	return ( fDistance * ( ( classifyPolygon == CP_INSIDE ) ? ( 1.0f ) : ( -1.0f ) ) );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Целочисленная геометрия
//
//bounds.maxy +----------------------------+
//						*****************************|
//						*****************************|
//						*****************************|
//						*****************************|
//						*****************************|
//						*****************************|
//						*****************************|
//						*****************************|
//						*****************************|
//bounds.miny *****************************+
//						bounds.minx									bounds.max
//
// * - точки входящие в bounds
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Работает только для нормальных Bounds ( min < max )
template<class TRect>
inline bool IsValidPoint( const TRect &rBounds, int x, int y )
{
	return ( x >= rBounds.minx ) && ( x < rBounds.maxx ) &&
				 ( y >= rBounds.miny ) && ( y < rBounds.maxy );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Работает только для нормальных Bounds ( min < max )
template<class TRect, class TPoint>
inline bool IsValidPoint( const TRect &rBounds, const TPoint &rPoint )
{
	return IsValidPointForNormalRect( rBounds, rPoint.x, rPoint.y );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Работает для любых Bounds ( min < max ) || ( min > max )
template<class TRect>
inline bool IsValidPointSlow( const TRect &rBounds, const int x, const int y )
{
	bool bXIsValid = true;
	if ( rBounds.minx < rBounds.maxx )
	{
		bXIsValid = ( x >= rBounds.minx ) && ( x < rBounds.maxx );
	}
	else
	{
		bXIsValid = ( x >= rBounds.maxx ) && ( x < rBounds.minx );
	}
	bool bYIsValid = true;
	if ( rBounds.miny < rBounds.maxy )
	{
		bYIsValid = ( y >= rBounds.miny ) && ( y < rBounds.maxy );
	}
	else
	{
		bYIsValid = ( y >= rBounds.maxy ) && ( y < rBounds.miny );
	}

	return ( bXIsValid && bYIsValid );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Работает для любых Bounds ( min < max ) || ( min > max )
template<class TRect, class TPoint>
inline bool IsValidPointSlow( const TRect &rBounds, const TPoint &rPoint )
{
	return IsValidPoint( rBounds, rPoint.x, rPoint.y );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Работает только для нормальных Bounds ( min < max )
//если вернули 0 - произошел сдвиг точки на границу
//если вернули 1 - точка не изменилась
template<class TRect, class TPoint>
inline int ValidatePoint( const TRect &rBounds, TPoint *pPoint )
{
	NI_ASSERT_T( pPoint != 0, NStr::StrFmt( "Wrong parameter: %x\n", pPoint ) );

	int nResult = 1;
	//Определяем границы
	if ( pPoint->x < rBounds.minx )
	{
		pPoint->x = rBounds.minx;
		nResult = 0;
	}
	if ( pPoint->y < rBounds.miny )
	{
		pPoint->y = rBounds.miny;
		nResult = 0;
	}
	if ( pPoint->x > ( rBounds.maxx - 1 ) )
	{
		pPoint->x = ( rBounds.maxx - 1 );
		nResult = 0;
	}
	if ( pPoint->y > ( rBounds.maxy - 1 ) )
	{
		pPoint->y = ( rBounds.maxy - 1 );
		nResult = 0;
	}
	return nResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Работает только для нормальных Bounds ( min < max )
//если вернули -1 - ни одна точка pIndices не попадает в прямоугольник rBounds
//если вернули 0 - произошло отсечение по одной из сторон
//если вернули 1 - pRect не изменялся
template<class TRect>
inline int ValidateRect( const TRect &rBounds, TRect *pRect )
{
	NI_ASSERT( pRect != 0, "Wrong parameter: pRect == 0" );
	//
	pRect->Normalize();
	//
	//Вырожденный случай не рассматриваем
	if ( ( pRect->minx >= rBounds.maxx ) ||
			 ( pRect->miny >= rBounds.maxy ) ||
			 ( pRect->maxx <= rBounds.minx ) ||
			 ( pRect->maxy <= rBounds.miny ) )
	{
		return ( -1 );
	}

	int nResult = 1;
	//Определяем границы
	if ( pRect->minx < rBounds.minx )
	{
		pRect->minx = rBounds.minx;
		nResult = 0;
	}
	if ( pRect->miny < rBounds.miny )
	{
		pRect->miny = rBounds.miny;
		nResult = 0;
	}
	if ( pRect->maxx > rBounds.maxx )
	{
		pRect->maxx = rBounds.maxx;
		nResult = 0;
	}
	if ( pRect->maxy > rBounds.maxy )
	{
		pRect->maxy = rBounds.maxy;
		nResult = 0;
	}
	return nResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//функционал коллекционирующий пары чисел (координаты точек)
template<class TList, class TPoint>
struct StoreTilesFunctional
{
	TList tileList;

	bool operator()( int nXIndex, int nYIndex )
	{ 
		tileList.push_back( TPoint( nXIndex, nYIndex ) );
		return true;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//функционал изменяющий pLockArray на заданное значение
template<class TArray, class TElement>
struct SModifyTilesFunctional
{
	TElement value;
	TArray *pLockArray;

	SModifyTilesFunctional( const TElement &rValue, TArray *_pLockArray )
		: value( rValue ), pLockArray( _pLockArray )
	{
		NI_ASSERT( pLockArray != 0, "Wrong parameter: pLockArray == 0" );
	}
	bool operator()( int nXIndex, int nYIndex )
	{ 
		(*pLockArray)[nYIndex][nXIndex] = value;
		return true;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//функционал определяющий есть ли тайл заданного значения в pLockArray
template<class TArray, class TElement>
struct SCheckTilesFunctional
{
	TElement value;
	const TArray *pLockArray;
	bool isPresent;

	SCheckTilesFunctional( const TElement &rValue, TArray *_pLockArray )
		: value( rValue ), pLockArray( _pLockArray ), isPresent( false )
	{
		NI_ASSERT( pLockArray != 0, "Wrong parameter: pLockArray == 0" );
	}
	bool operator()( int nXIndex, int nYIndex )
	{ 
		if ( (*pLockArray)[nYIndex][nXIndex] == value )
		{
			isPresent = true;
		}
		return ( !isPresent );
	}
};

/**
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//применение функционалов для поля pLockArray, функционалы перечислены выше
//некоторые функционалы могут изменять массив
template<class TYPE>
bool ApplyTilesInObjectsPassability( const CTRect<int> &rRect,										//границы применимости функционалов
																		 const SMapObjectInfo *pMapObjectInfo,				//указатель на массив обьектов
																		 int nMapObjectInfoCount,											//число обьектов
																		 TYPE &rApplyFunctional,											//функционал
																		 bool isIgnoreInvalidIndices = false )				//пропускать обьекты за краями карты
{
	IObjectsDB *pIDB = GetSingleton<IObjectsDB>();
	if ( !pIDB )
	{
		return false;
	}

	for ( int nObjectIndex = 0; nObjectIndex < nMapObjectInfoCount; ++nObjectIndex )
	{
		const SGDBObjectDesc* pGDBObjectDesc = pIDB->GetDesc( pMapObjectInfo[nObjectIndex].szName.c_str() );
		if ( ( pGDBObjectDesc != 0 ) &&
				 ( IsObjectHasPassability( pGDBObjectDesc->eGameType ) ) )
		{
			const SStaticObjectRPGStats* pStaticObjectRPGStats = NGDB::GetRPGStats<SStaticObjectRPGStats>( pMapObjectInfo[nObjectIndex].szName.c_str() );
			const CVec2 &rOrigin = pStaticObjectRPGStats->GetOrigin( pMapObjectInfo[nObjectIndex].nFrameIndex );
			const CArray2D<BYTE> &rPassability = pStaticObjectRPGStats->GetPassability( pMapObjectInfo[nObjectIndex].nFrameIndex );
			CTPoint<int> start( ( pMapObjectInfo[nObjectIndex].vPos.x - rOrigin.x + ( SAIConsts::TILE_SIZE / 2.0 ) ) / SAIConsts::TILE_SIZE,
													( pMapObjectInfo[nObjectIndex].vPos.y - rOrigin.y + ( SAIConsts::TILE_SIZE / 2.0 ) ) / SAIConsts::TILE_SIZE );
			
			CTRect<int> indices( start.x, start.y, start.x + rPassability.GetSizeX(), start.y + rPassability.GetSizeY() );
			int result = ValidateIndices( rRect, &indices );
			//нет ни одного тайла
			if ( result < 0 )
			{
				if ( isIgnoreInvalidIndices )
				{
					//скипаем обьект, переходим к следующему
					continue;
				}
				else
				{
					//возвращаем ошибку
					return false;
				}
			}
			//пассабилити выходит за границы массива
			if ( ( result < 1 ) && !isIgnoreInvalidIndices )
			{
				//возвращаем ошибку
				return false;
			}
			//пробегаем по тайлам
			for ( int nXIndex = indices.minx; nXIndex < indices.maxx; ++nXIndex )
			{
				for ( int nYIndex = indices.miny; nYIndex < indices.maxy; ++nYIndex )
				{
					if ( rPassability[nYIndex - start.y][nXIndex - start.x] != RMGC_UNLOCKED )
					{
						if ( !rApplyFunctional( nXIndex, nYIndex ) )
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

template<class TYPE>
bool ApplyTilesInObjectsPassability( const CTRect<int> &rRect, const SMapObjectInfo &rMapObjectInfo, TYPE &rApplyFunctional, bool isIgnoreInvalidIndices = false )
{
	return ApplyTilesInObjectsPassability( rRect, &rMapObjectInfo, 1, rApplyFunctional, isIgnoreInvalidIndices );
}
/**/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//применение функционалов для для всех точек сетки входящих в полигон, функционалы перечислены выше
template<class Type, class TPolygon, class TPoint>
bool ApplyPointsInPolygon( const CTRect<int> &rRect,					//границы применимости функционалов
													 const TPolygon &rPolygon,					//полигон
													 float fTileSize,										//сторона тайла
													 Type &rApplyFunctional )						//функционал
{
	CTRect<float> boundingBox = GetPolygonBoundingBox( rPolygon );
	CTRect<int> indices( (int)( boundingBox.minx / fTileSize ) - 1,
											 (int)( boundingBox.miny / fTileSize ) - 1,
											 (int)( boundingBox.maxx / fTileSize ) + 1,
											 (int)( boundingBox.maxy / fTileSize ) + 1 );
	if ( ValidateRect( rRect, &indices ) < 0 )
	{
		return false;
	}
	//пробегаем по тайлам
	for ( int nXIndex = indices.minx; nXIndex < indices.maxx; ++nXIndex )
	{
		for ( int nYIndex = indices.miny; nYIndex < indices.maxy; ++nYIndex )
		{
			CVec2 vPoint( ( nXIndex * fTileSize ), ( nYIndex * fTileSize ) );
			TPoint point = GetPointType< TPoint >( vPoint );
			if ( ClassifyPolygon( rPolygon, point ) != CP_OUTSIDE )
			{
				if ( !rApplyFunctional( nXIndex, nYIndex ) )
				{
					return false;
				}
			}
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//применение функционалов для для всех тайлов входящих в полигон, функционалы перечислены выше
template<class Type, class TPolygon, class TPoint>
bool ApplyTilesInPolygon( const CTRect<int> &rRect,						//границы применимости функционалов
													const TPolygon &rPolygon,						//полигон
													float fTileSize,										//сторона тайла
													Type &rApplyFunctional )						//функционал
{
	CTRect<float> boundingBox = GetPolygonBoundingBox( rPolygon );
	CTRect<int> indices( (int)( ( boundingBox.minx + ( fTileSize / 2.0f ) ) / fTileSize ),
											 (int)( ( boundingBox.miny + ( fTileSize / 2.0f ) ) / fTileSize ),
											 (int)( ( boundingBox.maxx + ( fTileSize / 2.0f ) ) / fTileSize ),
											 (int)( ( boundingBox.maxy + ( fTileSize / 2.0f ) ) / fTileSize ) );
	if ( ValidateRect( rRect, &indices ) < 0 )
	{
		return false;
	}
	//пробегаем по тайлам
	for ( int nXIndex = indices.minx; nXIndex < indices.maxx; ++nXIndex )
	{
		for ( int nYIndex = indices.miny; nYIndex < indices.maxy; ++nYIndex )
		{
			CVec2 vTileCenter( ( nXIndex * fTileSize ) + ( fTileSize / 2.0f ),
												 ( nYIndex * fTileSize ) + ( fTileSize / 2.0f ) );
			TPoint tileCenter = GetPointType< TPoint >( vTileCenter );
			if ( ClassifyPolygon( rPolygon, tileCenter ) != CP_OUTSIDE )
			{
				if ( !rApplyFunctional( nXIndex, nYIndex ) )
				{
					return false;
				}
			}
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//применение функционалов для для всех тайлов входящих в прямоуголник (включительно, как у дорог)
template<class Type>
bool ApplyTilesInRange( const CTRect<int> &rRect,	//границы применимости функционалов
												int nMinX,								//границы прямоугольника
												int nMinY,								//
												int nMaxX,								//
												int nMaxY,								//
												Type &rApplyFunctional )	//функционал
{
	CTRect<int> indices( nMinX, nMinY, nMaxX + 1, nMaxY + 1 );
	if ( ValidateRect( rRect, &indices ) < 0 )
	{
		return false;
	}
	//пробегаем по тайлам
	for ( int nXIndex = indices.minx; nXIndex < indices.maxx; ++nXIndex )
	{
		for ( int nYIndex = indices.miny; nYIndex < indices.maxy; ++nYIndex )
		{
			if ( !rApplyFunctional( nXIndex, nYIndex ) )
			{
				return false;
			}
		}
	}
	return true;
}

template<class Type>
bool ApplyTilesInRange( const CTRect<int> &rRect,
												const CTPoint<int> &rMin,
												const CTPoint<int> &rMax,
												Type &rApplyFunctional )
{
	return ApplyTilesInRange( rRect, rMin.x, rMin.y, rMax.x, rMax.y, rApplyFunctional );
}

template<class Type>
bool ApplyTilesInRange( const CTRect<int> &rRect,
												const CTRect<int> &rRange,
												Type &rApplyFunctional )
{
	return ApplyTilesInRange( rRect, rRange.minx, rRange.miny, rRange.maxx, rRange.maxy, rApplyFunctional );
}

//CRAP{оптимизировать колекционирование тайлов в круге
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//в радиусе нет локаных тайлов 
template<class Type>
bool ApplyTilesInCircle( const CTRect<int> &rRect,	//границы применимости функционалов
												 int nXPosition,						//центр круга
												 int nYPosition,						//
												 int nRadius,								//радиус круга
												 Type &rApplyFunctional )		//функционал
{
	CTRect<int> indices( nXPosition - nRadius, nYPosition - nRadius, nXPosition + nRadius + 1, nYPosition + nRadius + 1 );
	if ( ValidateRect( rRect, &indices )	< 0 )
	{
		return false;
	}
	//пробегаем по тайлам
	for ( int nXIndex = indices.minx; nXIndex < indices.maxx; ++nXIndex )
	{
		for ( int nYIndex = indices.miny; nYIndex < indices.maxy; ++nYIndex )
		{
			if ( ( sqr( nXIndex - nXPosition ) + sqr( nYIndex - nYPosition ) ) <= sqr( nRadius ) )
			{
				if ( !rApplyFunctional( nXIndex, nYIndex ) )
				{
					return false;
				}
			}
		}
	}
	return true;
}
//CRAP}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
inline bool ApplyTilesInCircle( const CTRect<int> &rRect,
																const CTPoint<int> &rCenter,
																int nRadius,
																Type &rApplyFunctional )
{
	return ApplyTilesInCircle( rRect, rCenter.x, rCenter.y, nRadius, rApplyFunctional );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // #if !defined(__PLANE_GEOMETRY_H__)
