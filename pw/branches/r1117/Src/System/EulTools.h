#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////////
#define GETEULERORDER( i, p, r, f ) ( ( ( ( ( ( i << 1 ) + p ) << 1 ) + r ) << 1 ) + f )
////////////////////////////////////////////////////////////////////////////////////////////////////
enum EEULERDEFS
{
	ED_X = 0,
	ED_Y = 1,
	ED_Z = 2,

	ED_STATICFRAME = 0,
	ED_ROTATEFRAME = 1,

	ED_NOREPEAT = 0,
	ED_REPEAT = 1,

	ED_EVEN = 0,
	ED_ODD = 1,
};
////////////////////////////////////////////////////////////////////////////////////////////////////
enum EEULERORDER
{
	EO_XYZs = GETEULERORDER( ED_X, ED_EVEN, ED_NOREPEAT, ED_STATICFRAME ),
	EO_XYXs = GETEULERORDER( ED_X, ED_EVEN, ED_REPEAT,	 ED_STATICFRAME ),
	EO_XZYs = GETEULERORDER( ED_X, ED_ODD,	ED_NOREPEAT, ED_STATICFRAME ),
	EO_XZXs = GETEULERORDER( ED_X, ED_ODD,	ED_REPEAT,	 ED_STATICFRAME ),
	EO_YZXs = GETEULERORDER( ED_Y, ED_EVEN, ED_NOREPEAT, ED_STATICFRAME ),
	EO_YZYs = GETEULERORDER( ED_Y, ED_EVEN, ED_REPEAT,	 ED_STATICFRAME ),
	EO_YXZs = GETEULERORDER( ED_Y, ED_ODD,	ED_NOREPEAT, ED_STATICFRAME ),
	EO_YXYs = GETEULERORDER( ED_Y, ED_ODD,	ED_REPEAT,	 ED_STATICFRAME ),
	EO_ZXYs = GETEULERORDER( ED_Z, ED_EVEN, ED_NOREPEAT, ED_STATICFRAME ),
	EO_ZXZs = GETEULERORDER( ED_Z, ED_EVEN, ED_REPEAT,	 ED_STATICFRAME ),
	EO_ZYXs = GETEULERORDER( ED_Z, ED_ODD,	ED_NOREPEAT, ED_STATICFRAME ),
	EO_ZYZs = GETEULERORDER( ED_Z, ED_ODD,	ED_REPEAT,	 ED_STATICFRAME ),
	/////
	EO_ZYXr = GETEULERORDER( ED_X, ED_EVEN, ED_NOREPEAT, ED_ROTATEFRAME ),
	EO_XYXr = GETEULERORDER( ED_X, ED_EVEN, ED_REPEAT,	 ED_ROTATEFRAME ),
	EO_YZXr = GETEULERORDER( ED_X, ED_ODD,	ED_NOREPEAT, ED_ROTATEFRAME ),
	EO_XZXr = GETEULERORDER( ED_X, ED_ODD,	ED_REPEAT,	 ED_ROTATEFRAME ),
	EO_XZYr = GETEULERORDER( ED_Y, ED_EVEN, ED_NOREPEAT, ED_ROTATEFRAME ),
	EO_YZYr = GETEULERORDER( ED_Y, ED_EVEN, ED_REPEAT,	 ED_ROTATEFRAME ),
	EO_ZXYr = GETEULERORDER( ED_Y, ED_ODD,	ED_NOREPEAT, ED_ROTATEFRAME ),
	EO_YXYr = GETEULERORDER( ED_Y, ED_ODD,	ED_REPEAT,	 ED_ROTATEFRAME ),
	EO_YXZr = GETEULERORDER( ED_Z, ED_EVEN, ED_NOREPEAT, ED_ROTATEFRAME ),
	EO_ZXZr = GETEULERORDER( ED_Z, ED_EVEN, ED_REPEAT,	 ED_ROTATEFRAME ),
	EO_XYZr = GETEULERORDER( ED_Z, ED_ODD,	ED_NOREPEAT, ED_ROTATEFRAME ),
	EO_ZYZr = GETEULERORDER( ED_Z, ED_ODD,	ED_REPEAT,	 ED_ROTATEFRAME )
};
////////////////////////////////////////////////////////////////////////////////////////////////////
inline unsigned int GetSafe( unsigned int uiOrder ) { static unsigned int aiSafe[] = { 0, 1, 2, 0 }; return( aiSafe[ uiOrder & 0x3 ] ); }
inline unsigned int GetNext( unsigned int uiOrder ) { static unsigned int aiNext[] = { 1, 2, 0, 1 }; return( aiNext[ uiOrder & 0x3 ] ); }
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void GetOrderData( unsigned int uiOrder, int &i, int &j, int &k, int &h, int &n, int &s, int &f )
{
	f = uiOrder & 0x1; uiOrder >>= 1;
	s = uiOrder & 0x1; uiOrder >>= 1;
	n = uiOrder & 0x1; uiOrder >>= 1;
	i = GetSafe( uiOrder & 0x3 );
	j = GetNext( i + n );
	k = GetNext( i + 1 - n );
	h = s ? k : i;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline CVec3 ToEulerAngles( const SHMatrix &kM, unsigned int uiOrder )
{
	int i,j,k,h,n,s,f;
	GetOrderData( uiOrder, i, j, k, h, n, s, f );
	////
	CVec3 kAngles;
	if( s == ED_REPEAT )
	{
		float sy = sqrtf( kM.m[i][j] * kM.m[i][j] + kM.m[i][k] * kM.m[i][k] );
	
		if( sy > FP_EPSILON )
		{
			kAngles.x = atan2f( kM.m[i][j],	kM.m[i][k] );
			kAngles.y = atan2f( sy,				kM.m[i][i] );
			kAngles.z = atan2f( kM.m[j][i], -kM.m[k][i] );
		}
		else
		{
			kAngles.x = atan2f( -kM.m[j][k], kM.m[j][j] );
			kAngles.y = atan2f( sy,				kM.m[i][i] );
			kAngles.z = 0.0f;
		}
	}
	else
	{
		float cy = sqrtf( kM.m[i][i] * kM.m[i][i] + kM.m[j][i] * kM.m[j][i] );
	
		if( cy > FP_EPSILON )
		{
			kAngles.x = atan2f(	kM.m[k][j], kM.m[k][k] );
			kAngles.y = atan2f( -kM.m[k][i], cy			 );
			kAngles.z = atan2f(	kM.m[j][i], kM.m[i][i] );
		}
		else
		{
			kAngles.x = atan2f( -kM.m[j][k], kM.m[j][j] );
			kAngles.y = atan2f( -kM.m[k][i], cy			 );
			kAngles.z = 0.0f;
		}
	}
	////
	if( n == ED_ODD ) { kAngles.x = -kAngles.x; kAngles.y = -kAngles.y; kAngles.z = -kAngles.z; }
	if( f == ED_ROTATEFRAME ) { float t = kAngles.x; kAngles.x = kAngles.z; kAngles.z = t; }
	////
	return kAngles;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline CVec3 ToEulerAngles( const CQuat &sQuat, unsigned int uiOrder )
{
	return ToEulerAngles( SHMatrix( sQuat ), uiOrder );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
