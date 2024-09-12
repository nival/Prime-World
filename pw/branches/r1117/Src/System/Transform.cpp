#include "stdafx.h"
#include "Transform.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
SFBTransform MakeTransform( const CVec3 &ptPos )
{
	CFBMatrixStack<4> mStack;
	mStack.Init();
	mStack.Push( ptPos );
	return mStack.Get();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
SFBTransform MakeTransform( const CVec3 &ptPos, int nRotation )
{
	CQuat quat( ToRadian( (float)nRotation ), CVec3( 0, 0, 1 ) );
	SHMatrix rotMatrix;
	CFBMatrixStack<4> mStack;
	mStack.Init();
	mStack.Push( ptPos );
	quat.DecompEulerMatrix( &rotMatrix );
	mStack.Push33( rotMatrix );
	return mStack.Get();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
SFBTransform MakeTransform( const CVec3 &ptPos, const CVec3 &ptScale )
{
	CFBMatrixStack<4> mStack;
	mStack.Init();
	mStack.Push( ptPos );
	mStack.PushScale( ptScale.x, ptScale.y, ptScale.z );
	return mStack.Get();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeMatrix( SFBTransform *pRes, const CVec3 &size, const CVec3 &move, float fAngle )
{
	CFBMatrixStack<4> m;
	m.Init();
	CQuat rot;
	rot.FromAngleAxis( fAngle, CVec3(0,0,1) );
	m.Push( move, rot );
	m.PushScale( size.x, size.y, size.z );
	//SFBTransform t = m.Get();
	//SHMatrix mTest = t.forward * t.backward;
	*pRes = m.Get();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeMatrix( SFBTransform *pRes, const CVec3 &size, const CVec3 &move, const CQuat &rot )
{
	CFBMatrixStack<4> m;
	m.Init();
	m.Push( move, rot );
	m.PushScale( size.x, size.y, size.z );
	*pRes = m.Get();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeMatrix( SHMatrix *pRes, float fpTangazh, float fpRiskanie, float fKren, const CVec3 &pos )
{
	SHMatrix &res = *pRes;
	CQuat q, qt, qr, qk;
	qt.FromAngleAxis( fpTangazh, CVec3(1,0,0) );
	qr.FromAngleAxis( fpRiskanie, CVec3(0,0,1) );
	qk.FromAngleAxis( fKren, CVec3(0,1,0) );
	q = qr * qt * qk;
	Identity( &res );
	q.DecompEulerMatrix( &res );
	res._14 = pos.x;
	res._24 = pos.y;
	res._34 = pos.z;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeMatrix( SFBTransform *pRes, float fpTangazh, float fpRiskanie, float fKren, const CVec3 &pos )
{
	MakeMatrix( &pRes->forward, fpTangazh, fpRiskanie, fKren, pos );
	InvertMatrix( &pRes->backward, pRes->forward );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeMatrix( SHMatrix *pRes, const CVec3 &ptPos, const CVec3 &ptDir )
{
	float fpTang = atan2( ptDir.z, sqrt( sqr( ptDir.x ) + sqr( ptDir.y ) ) );
	float fpRisk = atan2( ptDir.y, ptDir.x ) - FP_PI2;
	MakeMatrix( pRes, fpTang, fpRisk, 0, ptPos );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool InvertMatrix( SHMatrix *pRes, const SHMatrix &m )
{
	bool bRes = true;
	const float m3344 = m._33 * m._44 - m._43 * m._34;
	const float m2344 = m._23 * m._44 - m._43 * m._24;
	const float m2334 = m._23 * m._34 - m._33 * m._24;
	const float m3244 = m._32 * m._44 - m._42 * m._34;
	const float m2244 = m._22 * m._44 - m._42 * m._24;
	const float m2234 = m._22 * m._34 - m._32 * m._24;
	const float m3243 = m._32 * m._43 - m._42 * m._33;
	const float m2243 = m._22 * m._43 - m._42 * m._23;
	const float m2233 = m._22 * m._33 - m._32 * m._23;
	const float m1344 = m._13 * m._44 - m._43 * m._14;
	const float m1334 = m._13 * m._34 - m._33 * m._14;
	const float m1244 = m._12 * m._44 - m._42 * m._14;
	const float m1234 = m._12 * m._34 - m._32 * m._14;
	const float m1243 = m._12 * m._43 - m._42 * m._13;
	const float m1233 = m._12 * m._33 - m._32 * m._13;
	const float m1324 = m._13 * m._24 - m._23 * m._14;
	const float m1224 = m._12 * m._24 - m._22 * m._14;
	const float m1223 = m._12 * m._23 - m._22 * m._13;
	// Adjoint Matrix
	pRes->_11 =	m._22 * m3344 - m._32 * m2344 + m._42 * m2334;
	pRes->_21 = -m._21 * m3344 + m._31 * m2344 - m._41 * m2334;
	pRes->_31 =	m._21 * m3244 - m._31 * m2244 + m._41 * m2234;
	pRes->_41 = -m._21 * m3243 + m._31 * m2243 - m._41 * m2233;
	
	pRes->_12 = -m._12 * m3344 + m._32 * m1344 - m._42 * m1334;
	pRes->_22 =	m._11 * m3344 - m._31 * m1344 + m._41 * m1334;
	pRes->_32 = -m._11 * m3244 + m._31 * m1244 - m._41 * m1234;
	pRes->_42 =	m._11 * m3243 - m._31 * m1243 + m._41 * m1233;
	
	pRes->_13 =	m._12 * m2344 - m._22 * m1344 + m._42 * m1324;
	pRes->_23 = -m._11 * m2344 + m._21 * m1344 - m._41 * m1324;
	pRes->_33 =	m._11 * m2244 - m._21 * m1244 + m._41 * m1224;
	pRes->_43 = -m._11 * m2243 + m._21 * m1243 - m._41 * m1223;
	
	pRes->_14 = -m._12 * m2334 + m._22 * m1334 - m._32 * m1324;
	pRes->_24 =	m._11 * m2334 - m._21 * m1334 + m._31 * m1324;
	pRes->_34 = -m._11 * m2234 + m._21 * m1234 - m._31 * m1224;
	pRes->_44 =	m._11 * m2233 - m._21 * m1233 + m._31 * m1223;
	// Division by determinant
	float fDet = m._11*pRes->_11 + m._21*pRes->_12 + m._31*pRes->_13 + m._41*pRes->_14;
	if ( fDet == 0 )
	{
		ASSERT( 0 );
		bRes = false; // singular matrix found !
	}
	else
		fDet = 1.0f / fDet;
	pRes->_11 *= fDet;	pRes->_21 *= fDet;	pRes->_31 *= fDet;	pRes->_41 *= fDet;
	pRes->_12 *= fDet;	pRes->_22 *= fDet;	pRes->_32 *= fDet;	pRes->_42 *= fDet;
	pRes->_13 *= fDet;	pRes->_23 *= fDet;	pRes->_33 *= fDet;	pRes->_43 *= fDet;
	pRes->_14 *= fDet;	pRes->_24 *= fDet;	pRes->_34 *= fDet;	pRes->_44 *= fDet;
	
	return bRes;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void TransformYupToZup( SHMatrix *pMatrix )
{
	SHMatrix basisZup(
		1, 0,	0, 0,
		0, 0, -1, 0,
		0, 1,	0, 0,
		0, 0,	0, 1 );
	SHMatrix inverseBasisZup(
		1,	0, 0, 0,
		0,	0, 1, 0,
		0, -1, 0, 0,
		0,	0, 0, 1 );

	SHMatrix temp = basisZup * (*pMatrix);
	(*pMatrix) = temp * inverseBasisZup;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeProjectiveRay( CVec3 *pRes, CVec3 *pOrig, const SHMatrix &camera, const CVec2 &screenRect, const CVec2 &cursorPos, float fFovX )
{
	float fDepth = screenRect.x * 0.5f / tan( ToRadian(fFovX) * 0.5f );
	CVec3 direction( cursorPos.x - screenRect.x / 2, fDepth, -cursorPos.y + screenRect.y / 2 );
	if ( fabs2( direction ) < 1e-8f )
		direction = CVec3( 0,1,0 );
	else
		Normalize( &direction );
	camera.RotateVector( pRes, direction );
	*pOrig = camera.GetTranslation();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeProjectiveRay( CVec3 *pRes, CVec3 *pOrig, const CTransformStack &ts, const CVec2 &vScreenRect, const CVec2 &cursorPos )
{
	SHMatrix sCamera = ts.Get().backward * ts.GetProjection().forward;
	SHMatrix sBackProjection = ts.GetProjection().backward;

	CVec4 vScreenSpace( cursorPos.x * 2 / vScreenRect.x - 1, -cursorPos.y * 2 / vScreenRect.y + 1, 1, 1 ), vResScreen;
	sBackProjection.RotateHVector( &vResScreen, vScreenSpace );
	float fW1 = 1 / vResScreen.w;
	sCamera.RotateVector( pRes, CVec3( vResScreen.x * fW1, vResScreen.y * fW1, vResScreen.z * fW1 ) );
	*pOrig = sCamera.GetTranslation();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool TestRayInFrustrum( const CVec3 &ptPos, const SHMatrix &camera, const CVec2 &screenRect, float fFovY, CVec2 *pRes )
{
	SHMatrix cam1;
	InvertMatrix( &cam1, camera );
	CVec3 vRes;
	cam1.RotateHVector( &vRes, ptPos );
	if ( vRes.y < 0.001f )
		return false;
	vRes.x /= vRes.y;
	vRes.z /= vRes.y;
	float fDepth = screenRect.y * 0.5f / tan( ToRadian(fFovY) * 0.5f );

	if ( pRes != 0 )
	{
		pRes->x = vRes.x * fDepth + screenRect.x / 2;
		pRes->y = - vRes.z * fDepth + screenRect.y / 2;
	}

	if ( fabs( vRes.x * fDepth ) > screenRect.x / 2 )
		return false;
	if ( fabs( vRes.z * fDepth ) > screenRect.y / 2 )
		return false;
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool TestRayInFrustrum( const CVec3 &ptPos, const CTransformStack &ts, const CVec2 &screenRect, CVec2 *pRes, float *pZ, float *pfMinDistance, float *pfMaxDistance )
{
	CVec4 vRes;
	ts.Get().forward.RotateHVector( &vRes, ptPos );
	vRes.x /= fabs( vRes.w );
	vRes.y /= fabs( vRes.w );
	if ( pZ != 0)
	{
		vRes.z /= fabs( vRes.w );
		*pZ = vRes.z;
	}
	if ( pRes != 0 )
	{
		pRes->x = vRes.x * screenRect.x / 2 + screenRect.x / 2;
		pRes->y = -vRes.y * screenRect.y / 2 + screenRect.y / 2;
	}

	if ( fabs( vRes.x ) > 1 )
		return false;
	if ( fabs( vRes.y ) > 1 )
		return false;
	if ( pfMaxDistance && vRes.z > *pfMaxDistance )
		return false;
	if ( pfMinDistance && vRes.z < *pfMinDistance )
		return false;

	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// take bounding box and calc enclosing sphere, this function does not place limitations
// on fwd structure besides fwd should not include projection
float CalcRadius2( const SBound &b, const SHMatrix &fwd )
{
	ASSERT( b.ptHalfBox.x >= 0 );
	ASSERT( b.ptHalfBox.y >= 0 );
	ASSERT( b.ptHalfBox.z >= 0 );
	float fSign;
	CVec3 ptRes = fwd.GetXAxis3() * b.ptHalfBox.x;
	fSign = fwd.GetXAxis3() * fwd.GetYAxis3() < 0 ? -1 : 1;
	ptRes += fwd.GetYAxis3() * (b.ptHalfBox.y * fSign);
	fSign = ptRes * fwd.GetZAxis3() < 0 ? -1 : 1;
	ptRes += fwd.GetZAxis3() * (b.ptHalfBox.z * fSign);
	return fabs2( ptRes );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void TransformBound( SBound *pRes, const SBound &src, const SHMatrix &fwd )
{
	CVec3 ptCenter;
	fwd.RotateHVector( &ptCenter, src.s.ptCenter );
	float fR = sqrt( CalcRadius2( src, fwd ) );
	pRes->SphereInit( ptCenter, fR );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// CTransformStack
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTransformStack::SetCamera( const SHMatrix& pos )
{
	SetToFirst();
	SHMatrix res, axisSwitch;
	Identity( &axisSwitch );
	axisSwitch._22 = 0;
	axisSwitch._23 = 1;
	axisSwitch._32 = 1;
	axisSwitch._33 = 0;
	Push43( axisSwitch );
	res.HomogeneousInverse( pos );
	Push43( res );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static void ScaleClipVertex( CVec4 *pRes, const CVec4 &vClip, const SHMatrix &m )
{
	CVec4 leng;
	m.RotateHVector( &leng, vClip );
	leng.w = 0;
	*pRes = vClip * ( 1 / fabs( leng ) );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTransformStack::PrepareClipPlanes()
{
	SHMatrix m;
	Transpose( &m, Get().forward );
	ScaleClipVertex( viewFrustrum + 0, CVec4( 1,0,0,1), m );
	ScaleClipVertex( viewFrustrum + 1, CVec4(-1,0,0,1), m );
	ScaleClipVertex( viewFrustrum + 2, CVec4(0, 1,0,1), m );
	ScaleClipVertex( viewFrustrum + 3, CVec4(0,-1,0,1), m );
	ScaleClipVertex( viewFrustrum + 4, CVec4(0,0,-1,1), m );
	ScaleClipVertex( viewFrustrum + 5, CVec4(0,0, 1,0), m );
	nClipPlanes = 6;
	nClipFlags[0] = ( 1 << nClipPlanes ) - 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTransformStack::AddClipPlane( const CVec4 &v )
{
	ASSERT( nClipPlanes < ARRAY_SIZE(viewFrustrum) );
	viewFrustrum[ nClipPlanes++ ] = v;
	nClipFlags[0] = ( 1 << nClipPlanes ) - 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTransformStack::MakeProjective( float fAspect, float fFov, float fZMin, float fZMax, const CVec2 &vShift )
{
	float h, w, Q;
	float far_plane = fZMax;
	float near_plane = fZMin;

	// fFov as 	fFovX
	float fFovY = ToRadian( fFov );
	float fFovX = 2 * atan( tan(fFovY*0.5f) / fAspect );

	w = (float)1/tan(fFovX*0.5);	// 1/tan(x) == cot(x)
	h = (float)1/tan(fFovY*0.5);	 // 1/tan(x) == cot(x)
	
	// fFov as diagonal fov
	//float fTan05Fov = tanf( ToRadian( fFov ) * 0.5f );
	//float fA2 = fAspect * fAspect;
	//w = sqrt( 1.0f + fA2 ) / fTan05Fov;
	//h = sqrt( 1.0f + 1.0f / fA2 ) / fTan05Fov;

	Q = far_plane/(far_plane - near_plane);
 
	SHMatrix ret;
#if defined( NV_WIN_PLATFORM )
	ZeroMemory(&ret, sizeof(ret));
#elif defined( NV_LINUX_PLATFORM )
  memset( &ret, 0, sizeof( ret ) );
#endif
	ret._11 = w;
	ret._22 = h;
	ret._33 = Q;
	ret._34 = -Q*near_plane;
	ret._43 = 1;
	
	//ret.GetX() += vShift.x * ret.GetW();
	CVec4 xa = vShift.x * ret.GetW();
	ret._11 += xa.x; 
	ret._12 += xa.y; 
  ret._13 += xa.z; 
  ret._14 += xa.w; 
	
	//ret.GetY() += vShift.y * ret.GetW();
  CVec4 ya = vShift.y * ret.GetW();
  ret._21 += ya.x; 
  ret._22 += ya.y; 
  ret._23 += ya.z; 
  ret._24 += ya.w; 
	
	
	Init( ret );

	PrepareClipPlanes();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTransformStack::MakeProjective( const CVec2 &screenRect, float fFov, float fZMin, float fZMax, const CVec2 &vShift ) 
{ 
	if ( screenRect.y == 0 || screenRect.x == 0 )
		MakeProjective( 1, fFov, fZMin, fZMax, vShift );
	else
		MakeProjective( screenRect.y / screenRect.x, fFov, fZMin, fZMax, vShift ); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTransformStack::MakeParallel( float fWidth, float fHeight, float fZMin, float fZMax )
{
	SHMatrix ret;
#if defined( NV_WIN_PLATFORM )
	ZeroMemory(&ret, sizeof(ret));
#elif defined( NV_LINUX_PLATFORM )
  memset( &ret, 0, sizeof( ret ) );
#endif
	ret._11 = 2 / fWidth;
	ret._22 = 2 / fHeight;
	ret._33 = 1 / ( fZMax - fZMin );
	ret._34 = -fZMin * ret._33;
	ret._44 = 1;
	Init( ret );

	PrepareClipPlanes();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTransformStack::MakeDirect( const CVec2 &screenRect )
{
	float fWidth = screenRect.x;
	float fHeight = screenRect.y;
	float far_plane = 1000.0f;
	float near_plane = 0.1f;
	fWidth = Max( fWidth, 1.0f );
	fHeight = Max( fHeight, 1.0f );
	SHMatrix ret;
#if defined( NV_WIN_PLATFORM )
	ZeroMemory(&ret, sizeof(ret));
#elif defined( NV_LINUX_PLATFORM )
  memset( &ret, 0, sizeof( ret ) );
#endif
	ret._11 = 2 / fWidth;
	ret._14 = -1;
	ret._22 = -2 / fHeight;
	ret._24 = 1;
	ret._33 = 1 / ( far_plane - near_plane );
	ret._34 = -near_plane * ret._33;
	ret._44 = 1;
	Init( ret );

	PrepareClipPlanes();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTransformStack::Make( const SHMatrix &projection )
{
	Init( projection );
	PrepareClipPlanes();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline float Dot( const CVec4 &a, const CVec4 &b ) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
inline float Dot( const CVec3 &a, const CVec4 &b ) { return a.x * b.x + a.y * b.y + a.z * b.z + b.w; }
////////////////////////////////////////////////////////////////////////////////////////////////////
// more precise approach to this is would be to find extremum of (center.x + R * sin(alpha)) / (center.w + R * cos(alpha))
// this problem reduces to extremum of (a + sin(alpha)) / (b + cos(alpha)), its approximate solution is CalcLeftRight
static void CalcLeftRight( float *pf1, float *pf2, float a, float b )
{
	float f1 = a - 1;
	if ( f1 < 0 )
		*pf1 = f1 / ( b - 1 );
	else
		*pf1 = f1 / ( b + 1 );
	float f2 = a + 1;
	if ( f2 < 0 )
		*pf2 = f2 / ( b + 1 );
	else
		*pf2 = f2 / ( b - 1 );
	ASSERT( *pf2 > *pf1 );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static float CalcScale( const CVec4 &vTrans )
{
	return sqrt( sqr(vTrans.x) + sqr(vTrans.y) + sqr(vTrans.z) );
}
bool CTransformStack::GetCoverRect( CTRect<float> *pRes, const CVec3 &_ptCenter, float fRadius )
{
	CVec4 ptCenter;
	const SHMatrix &m = Get().forward;
	m.RotateHVector( &ptCenter, _ptCenter );
	TFlags nFlags = nClipFlags[ nClipFlagsPtr ], nTest = 1;
	for ( int i = 0; i < nClipPlanes; i++, nTest <<= 1 )
	{
		if ( ( nFlags & nTest ) == 0 )
			continue;
		float fTest = Dot( ptCenter, viewFrustrum[i] );
		if ( fTest < -fRadius )
			return false;
	}
	if ( ptCenter.w <= 0 || fRadius == 0 )
	{
		pRes->x1 = -1; pRes->x2 = 1;
		pRes->y1 = -1; pRes->y2 = 1;
		return true;
	}

	float fSX = CalcScale( m.GetX() );
	float fSY = CalcScale( m.GetY() );
	float fSW = CalcScale( m.GetW() );

	float fR1 = 1 / fRadius;
	float fB = ptCenter.w / fSW * fR1;
	if ( fB <= 1 )
	{
		pRes->x1 = -1; pRes->x2 = 1;
		pRes->y1 = -1; pRes->y2 = 1;
		return true;
	}

	float fX = ptCenter.x / fSX * fR1;
	CalcLeftRight( &pRes->x1, &pRes->x2, fX, fB );
	pRes->x1 *= fSX / fSW;
	pRes->x2 *= fSX / fSW;

	float fY = ptCenter.y / fSY * fR1;
	CalcLeftRight( &pRes->y1, &pRes->y2, fY, fB );
	pRes->y1 *= fSY / fSW;
	pRes->y2 *= fSY / fSW;
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTransformStack::PushClipHint( const SSphere &s )
{
	CVec4 ptCenter;
	float fRadius = s.fRadius;
	Get().forward.RotateHVector( &ptCenter, s.ptCenter );
	TFlags nFlags = nClipFlags[ nClipFlagsPtr ], nTest = 1;
	for ( int i = 0; i < nClipPlanes; i++, nTest <<= 1 )
	{
		if ( ( nFlags & nTest ) == 0 )
			continue;
		float fTest = Dot( ptCenter, viewFrustrum[i] );
		if ( fTest < -fRadius )
			return false;
		if ( fTest > fRadius )
			nFlags &= ~nTest;
	}
	nClipFlags[ ++nClipFlagsPtr ] = nFlags;
	ASSERT( nClipFlagsPtr < ARRAY_SIZE(nClipFlags) );
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTransformStack::PushClipHint( const SBound &bv )
{
	float fRadius = bv.s.fRadius;
	CVec4 ptCenter;
	Get().forward.RotateHVector( &ptCenter, bv.s.ptCenter );
	TFlags nFlags = nClipFlags[ nClipFlagsPtr ], nTest = 1;
	bool bDoubt = false;
	for ( int i = 0; i < nClipPlanes; i++, nTest <<= 1 )
	{
		if ( ( nFlags & nTest ) == 0 )
			continue;
		float fTest = Dot( ptCenter, viewFrustrum[i] );
		if ( fTest < -fRadius )
			return false;
		bDoubt |= fTest < 0;
		if ( fTest > fRadius )
			nFlags &= ~nTest;
	}
	nClipFlags[ ++nClipFlagsPtr ] = nFlags;
	ASSERT( nClipFlagsPtr < ARRAY_SIZE(nClipFlags) );
	if ( !bDoubt )
		return true;
	if ( CheckParallelepiped( 
		bv.s.ptCenter, 
		CVec3( bv.ptHalfBox.x, 0, 0 ), 
		CVec3( 0, bv.ptHalfBox.y, 0 ), 
		CVec3( 0, 0, bv.ptHalfBox.z ) ) )
		return true;
	--nClipFlagsPtr;
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTransformStack::PopClipHint()
{
	ASSERT( nClipFlagsPtr > 0 );
	--nClipFlagsPtr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTransformStack::IsIn( const SSphere &s )
{
	TFlags nFlags = nClipFlags[ nClipFlagsPtr ], nTest = 1;
	if ( nFlags == 0 )
		return true;
	CVec4 ptCenter;
	Get().forward.RotateHVector( &ptCenter, s.ptCenter );
	for ( int i = 0; i < nClipPlanes; i++, nTest <<= 1 )
	{
		if ( ( nFlags & nTest ) == 0 )
			continue;
		float fTest = Dot( ptCenter, viewFrustrum[i] );
		if ( fTest < -s.fRadius )
			return false;
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// return true - exact result is known, result is stored to *pRes, returns false when in doubt
bool CTransformStack::CheckSphere( const CVec4 &ptCenter, float fRadius, bool *pRes )
{
	bool bIn = true;
	TFlags nFlags = nClipFlags[ nClipFlagsPtr ], nTest = 1;
	for ( int i = 0; i < nClipPlanes; i++, nTest <<= 1 )
	{
		if ( ( nFlags & nTest ) == 0 )
			continue;
		float fDot = Dot( ptCenter, viewFrustrum[i] );
		// trivial reject, sphere is behind plane
		if ( fDot < -fRadius )
		{
			*pRes = false;
			return true;
		}
		if ( fDot < 0 )
			bIn = false;
	}
	// trivial accept, center in frustrum
	if ( bIn )
	{
		*pRes = true;
		return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static CVec3 ptPolygon[128];
static int nUnusedVertex;
struct SClipPolygon
{
	int n[128];
	int nSize;
	SClipPolygon() : nSize(0) {}
	void push_back( int _n ) { ASSERT( nSize < 128 ); n[nSize++] = _n; }
	int size() const { return nSize; }
	int& operator[]( int i ) { ASSERT( i >= 0 && i < nSize ); return n[i]; }
	int operator[]( int i ) const { ASSERT( i >= 0 && i < nSize ); return n[i]; }
	void resize( int n ) { nSize = n; }
	bool empty() const { return nSize == 0; }
};
static bool ClipPolygon( const SClipPolygon &pts, const CVec4 &plane, SClipPolygon *pRes )
{
	float fRes[128];
	for ( int i = 0; i < pts.size(); ++i )
		fRes[i] = Dot( ptPolygon[ pts[i] ], plane );
	pRes->resize(0);
	/*bool bRes = false;
	*pRes = pts;
	for ( int i = 0; i < pts.size(); ++i ) if ( fRes[i] > 0 ) bRes = true;
	return bRes;*/
	float fPrev = fRes[ pts.size() - 1 ];
	const CVec3 *pPrev = &ptPolygon[ pts[ pts.size() - 1 ] ];
	for ( int i = 0; i < pts.size(); ++i )
	{
		if ( fRes[i] > 0 )
		{
			if ( fPrev <= 0 )
			{
				pRes->push_back( nUnusedVertex );
				ptPolygon[nUnusedVertex++] = ( ptPolygon[ pts[i] ] * fPrev - *pPrev * fRes[i] ) / ( fPrev - fRes[i] );
			}
			pRes->push_back( pts[i] );
		}
		else
		{
			if ( fPrev > 0 )
			{
				pRes->push_back( nUnusedVertex );
				ptPolygon[nUnusedVertex++] = ( ptPolygon[ pts[i] ] * fPrev - *pPrev * fRes[i] ) / ( fPrev - fRes[i] );
			}
		}
		fPrev = fRes[i];
		pPrev = &ptPolygon[ pts[i] ];
	}
	return !pRes->empty();
}
static int nPolygonIndices[6][4] = 
{
	{3,2,1,0},
	{4,5,6,7},
	{0,1,5,4},
	{1,2,6,5},
	{2,3,7,6},
	{3,0,4,7},
};
////////////////////////////////////////////////////////////////////////////////////////////////////
// could have been much more efficient - look box/box intersection info
bool CTransformStack::CheckParallelepiped( const CVec3 &ptCenter, const CVec3 &ptXAxis, const CVec3 &ptYAxis, const CVec3 &ptZAxis )
{
	// project 8 points & test them against frustrum
	ptPolygon[0] = ptCenter - ptXAxis - ptYAxis - ptZAxis;
	ptPolygon[1] = ptCenter + ptXAxis - ptYAxis - ptZAxis;
	ptPolygon[2] = ptCenter + ptXAxis + ptYAxis - ptZAxis;
	ptPolygon[3] = ptCenter - ptXAxis + ptYAxis - ptZAxis;
	ptPolygon[4] = ptCenter - ptXAxis - ptYAxis + ptZAxis;
	ptPolygon[5] = ptCenter + ptXAxis - ptYAxis + ptZAxis;
	ptPolygon[6] = ptCenter + ptXAxis + ptYAxis + ptZAxis;
	ptPolygon[7] = ptCenter - ptXAxis + ptYAxis + ptZAxis;
	CVec4 vInside4;
	CVec3 vInside;
	Get().backward.RotateHVector( &vInside4, CVec4( 0, 0, 1, 2 ) );
	vInside.x = vInside4.x / vInside4.w;
	vInside.y = vInside4.y / vInside4.w;
	vInside.z = vInside4.z / vInside4.w;
	nUnusedVertex = 8;
	bool bHasFront = false;
	for ( int i = 0; i < 6; ++i )
	{
		SClipPolygon poly, rPoly, *pSrc, *pDst;
		poly.push_back( nPolygonIndices[i][0] );
		poly.push_back( nPolygonIndices[i][1] );
		poly.push_back( nPolygonIndices[i][2] );
		poly.push_back( nPolygonIndices[i][3] );
		const CVec3 &a = ptPolygon[ nPolygonIndices[i][0] ];
		const CVec3 &b = ptPolygon[ nPolygonIndices[i][1] ];
		const CVec3 &c = ptPolygon[ nPolygonIndices[i][2] ];
		// test polygon side
		CVec3 vNormal( (c - b) ^ (a - b) );
		float fFront = vNormal * (b - vInside);
		if ( fFront >= 0 )
			continue;
		bHasFront = true;
		// clip it with each plane
		pSrc = &poly;
		pDst = &rPoly;
		TFlags nFlags = nClipFlags[ nClipFlagsPtr ], nTest = 1;
		for ( int k = 0; k < nClipPlanes; k++, nTest <<= 1 )
		{
			if ( ( nFlags & nTest ) == 0 )
				continue;
			CVec4 vClipPlane;
			Get().forward.RotateHVectorTransposed( &vClipPlane, viewFrustrum[k] );
			if ( !ClipPolygon( *pSrc, vClipPlane, pDst ) )
				goto NextPolygon;
			swap( pSrc, pDst );
		}
		return true; // intersects
NextPolygon: ;
	}
	if ( !bHasFront )
		return true; // lies inside
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTransformStack::IsIn( const SBound &s )
{
	if ( IsFullGet() )
		return true;
	CVec4 ptCenter;
	Get().forward.RotateHVector( &ptCenter, s.s.ptCenter );
	bool bRes;
	if ( CheckSphere( ptCenter, s.s.fRadius, &bRes ) )
		return bRes;
	return CheckParallelepiped( 
		s.s.ptCenter, 
		CVec3( s.ptHalfBox.x, 0, 0 ), 
		CVec3( 0, s.ptHalfBox.y, 0 ), 
		CVec3( 0, 0, s.ptHalfBox.z ) );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTransformStack::IsIn( const SSphere &s, const CVec3 &_ptXAxis, 
	const CVec3 &_ptYAxis, const CVec3 &_ptZAxis )
{
	if ( IsFullGet() )
		return true;
	CVec4 ptCenter;
	Get().forward.RotateHVector( &ptCenter, s.ptCenter );
	bool bRes;
	if ( CheckSphere( ptCenter, s.fRadius, &bRes ) )
		return bRes;
	return CheckParallelepiped( 
		s.ptCenter, 
		_ptXAxis, 
		_ptYAxis, 
		_ptZAxis );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeClipTS( CTransformStack *pRes, const CTransformStack &ts, const CVec2 &vOrigin, const CVec2 &vSize )
{
	const SFBTransform &projection = ts.GetProjection();
	SHMatrix m = projection.forward;
	
	//m.x = m.x * (1.0f / vSize.x) + m.w * ( ( 1 - 2 * vOrigin.x - vSize.x ) / vSize.x );
	CVec4 nx = m.GetX() * (1.0f / vSize.x) + m.GetW() * ( ( 1 - 2 * vOrigin.x - vSize.x ) / vSize.x );
	m._11 = nx.x;
  m._12 = nx.y;
  m._13 = nx.z;
  m._14 = nx.w;
	
	//m.y = m.y * (1.0f / vSize.y) + m.w * ( (-1 + 2 * vOrigin.y + vSize.y ) / vSize.y );
	CVec4 ny = m.GetY() * (1.0f / vSize.y) + m.GetW() * ( (-1 + 2 * vOrigin.y + vSize.y ) / vSize.y );
	m._21 = ny.x;
  m._22 = ny.y;
  m._23 = ny.z;
  m._24 = ny.w;
	
	pRes->Make( m );
	pRes->Push43( projection.backward * ts.Get().forward );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
