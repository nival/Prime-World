#ifndef __FAST_MATH_H__
#define __FAST_MATH_H__
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMath
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fast trigonometry section
// sinus & cosinus
float Sin( float fAlpha );
__forceinline float Cos( const float fAlpha ) { return Sin( fAlpha + FP_PI2 ); }

// result depends on current FPU rounding state, don't use in AI, can lead to async
float FastSin( float fAlpha );	
__forceinline float FastCos( const float fAlpha ) { return FastSin( fAlpha + FP_PI2 ); }

// arc sinus & arc cosinus
float ASin( float fSin );
__forceinline float ACos( const float fCos ) { return FP_PI2 - ASin( fCos ); }

// result depends on current FPU rounding state, don't use in AI, can lead to async
float FastASin( float fSin );
__forceinline float FastACos( const float fCos ) { return FP_PI2 - FastASin( fCos ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fast SQRT
float Sqrt( float fVal );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void NormalizeFast( float *pfX, float *pfY )
{
	const float fRcprLen = 1.0f / Sqrt( fabs2(*pfX, *pfY) );
	*pfX *= fRcprLen;
	*pfY *= fRcprLen;
}
inline void NormalizeFast( float *pfX, float *pfY, float *pfZ )
{
	const float fRcprLen = 1.0f / Sqrt( fabs2(*pfX, *pfY, *pfZ) );
	*pfX *= fRcprLen;
	*pfY *= fRcprLen;
	*pfZ *= fRcprLen;
}
inline void NormalizeFast( float *pfX, float *pfY, float *pfZ, float *pfW )
{
	const float fRcprLen = 1.0f / Sqrt( fabs2(*pfX, *pfY, *pfZ, *pfW) );
	*pfX *= fRcprLen;
	*pfY *= fRcprLen;
	*pfZ *= fRcprLen;
	*pfW *= fRcprLen;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#pragma optimize( "aw", off )
inline void NormalizeFast( CVec2 *pRes, const CVec2 &v )
{
	const float fRcprLen = 1.0f / Sqrt( fabs2(v) );
	pRes->x = v.x * fRcprLen;
	pRes->y = v.y * fRcprLen;
}
inline void NormalizeFast( CVec3 *pRes, const CVec3 &v )
{
	const float fRcprLen = 1.0f / Sqrt( fabs2(v) );
	pRes->x = v.x * fRcprLen;
	pRes->y = v.y * fRcprLen;
	pRes->z = v.z * fRcprLen;
}
inline void NormalizeFast( CVec4 *pRes, const CVec4 &v )
{
	const float fRcprLen = 1.0f / Sqrt( fabs2(v) );
	pRes->x = v.x * fRcprLen;
	pRes->y = v.y * fRcprLen;
	pRes->z = v.z * fRcprLen;
	pRes->w = v.w * fRcprLen;
}
#ifdef WIN32
  #pragma optimize( "", on )
#endif  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float GetAngle( float fCos, float fSin )
{
	NI_VERIFY( fabs ( fCos * fCos + fSin * fSin - 1 ) < 0.001f, "Vector normalization required", return 0 );

	fCos = Clamp( fCos, -1.0f, 1.0f );
	fSin = Clamp( fSin, -1.0f, 1.0f );

	const float fAngle = acos( fCos );
	return fSin >= 0 ? fAngle : FP_2PI - fAngle;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float GetAngle( const CVec2 &vDir ) { return GetAngle( vDir.x, vDir.y ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float GetAngle( const CVec2 &v1, const CVec2 &v2 )
{
	NI_ASSERT( ( fabs2( v1 ) - 1.0f ) < FP_EPSILON, "Vector normalization required" );
	NI_ASSERT( ( fabs2( v2 ) - 1.0f ) < FP_EPSILON, "Vector normalization required" );

	const float fAngle = NMath::ACos( v1*v2 );
	const float fSin = v1.x*v2.y - v2.x*v1.y;
	return fSin >= 0.0f ? fAngle : FP_2PI - fAngle;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __FAST_MATH_H__
