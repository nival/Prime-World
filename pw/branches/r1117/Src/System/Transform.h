#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
////////////////////////////////////////////////////////////////////////////////////////////////////
class CTransformStack;
////////////////////////////////////////////////////////////////////////////////////////////////////
SFBTransform MakeTransform( const CVec3 &ptPos );
SFBTransform MakeTransform( const CVec3 &ptPos, int nRotation );
SFBTransform MakeTransform( const CVec3 &ptPos, const CVec3 &ptScale );
void MakeMatrix( SHMatrix *pRes, float fpTangazh, float fpRiskanie, float fKren, const CVec3 &pos );
void MakeMatrix( SHMatrix *pRes, const CVec3 &ptPos, const CVec3 &ptDir );
void MakeMatrix( SFBTransform *pRes, float fpTangazh, float fpRiskanie, float fKren, const CVec3 &pos );
void MakeMatrix( SFBTransform *pRes, const CVec3 &size, const CVec3 &move, float fAngle = 0 );
void MakeMatrix( SFBTransform *pRes, const CVec3 &size, const CVec3 &move, const CQuat &rot );
bool InvertMatrix( SHMatrix *pRes, const SHMatrix &m );
void TransformYupToZup( SHMatrix *pMatrix );
void MakeProjectiveRay( CVec3 *pDir, CVec3 *pOrig, const SHMatrix &camera, const CVec2 &screenRect, const CVec2 &cursorPos, float fFovX = 90 );
void MakeProjectiveRay( CVec3 *pRes, CVec3 *pOrig, const CTransformStack &ts, const CVec2 &vScreenRect, const CVec2 &cursorPos );
bool TestRayInFrustrum( const CVec3 &ptPos, const SHMatrix &camera, const CVec2 &screenRect, float fFovY = 90, CVec2 *pRes = 0 );
bool TestRayInFrustrum( const CVec3 &ptPos, const CTransformStack &ts, const CVec2 &screenRect, CVec2 *pRes = 0, float *pZ = 0, float *pfMinDistance = 0, float *pfMaxDistance = 0 );
float CalcRadius2( const SBound &b, const SHMatrix &fwd );
void TransformBound( SBound *pRes, const SBound &src, const SHMatrix &fwd );
// original screen is (0,0) - (1,1), (0,0) - upper left corner
void MakeClipTS( CTransformStack *pRes, const CTransformStack &ts, const CVec2 &vOrigin, const CVec2 &vSize );
////////////////////////////////////////////////////////////////////////////////////////////////////
template< int nMaxNumMatrices, class TElement>
class CBaseMatrixStack
{
protected:
	TElement matrices[nMaxNumMatrices];
	int nCurrentMatrix;
public :
	CBaseMatrixStack() : nCurrentMatrix( -1 ) {}
	//
	bool IsEmpty() const { return nCurrentMatrix == -1; }
	void Clear() { nCurrentMatrix = -1; }
	void Pop( int nAmount = 1 ) { ASSERT( nCurrentMatrix >= nAmount - 1 ); nCurrentMatrix -= nAmount; }
	const TElement& Get() const { return matrices[nCurrentMatrix]; }
	void Init( const TElement &matrix ) { matrices[nCurrentMatrix = 0] = matrix; }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
// matrix stack 4x3
// template parameter == max stack size, second parameter - is stack 4x4
template <int nMaxNumMatrices>
class CMatrixStack43: public CBaseMatrixStack<nMaxNumMatrices, SHMatrix>
{
public :
	CMatrixStack43() { for ( int i = 0; i < nMaxNumMatrices; i++ ) Identity( this -> matrices + i ); }
	void Push43( const SHMatrix &matrix );
	void Push33( const SHMatrix &matrix );
	void Push( const CVec3 &pos );
	void Push( const CQuat &rot );
	void Push( const CVec3 &pos, const CQuat &rot );
	void PushScale( float x, float y, float z );
	void PushScale( float val );
};
////////////////////////////////////////////////////////////////////////////////////////////////////
// matrix stack 4x4 FBTransforms
template <int nMaxNumMatrices>
class CFBMatrixStack: public CBaseMatrixStack<nMaxNumMatrices, SFBTransform>
{
protected:
	void SetToFirst() { ASSERT( this -> nCurrentMatrix >= 0 ); this -> nCurrentMatrix = 0; }
public :
	CFBMatrixStack() {}
	//
	void Init( const SHMatrix &matrix ) { this -> nCurrentMatrix = 0; this -> matrices[0].forward = matrix; InvertMatrix( &( this -> matrices[0].backward ), matrix ); }
	void Init() { this -> nCurrentMatrix = 0; Identity( &(this -> matrices[0].forward) ); Identity( &( this -> matrices[0].backward ) ); }
	//
	void Push44( const SHMatrix &matrix );
	void Push43( const SHMatrix &matrix );
	void Push33( const SHMatrix &matrix );
	void Push33Orthonormal( const SHMatrix &matrix );
	void Push33( const SHMatrix &matrix, const SHMatrix &invMatrix );
	void Push( const CVec3 &pos );
	void Push( const CQuat &rot );
	void Push( const CVec3 &pos, const CQuat &rot );
	void PushScale( float x, float y, float z );
	void PushScale( float val );
};
////////////////////////////////////////////////////////////////////////////////////////////////////
class CTransformStack : public CFBMatrixStack<8>
{
	typedef int TFlags;
	CVec4 viewFrustrum[32];
	int nClipPlanes;
	int nClipFlags[32];
	int nClipFlagsPtr;
	//
	void PrepareClipPlanes();
	bool CheckSphere( const CVec4 &ptCenter, float fRadius, bool *pRes );
	bool CheckParallelepiped( const CVec3 &ptCenter, const CVec3 &ptXAxis, const CVec3 &ptYAxis, const CVec3 &ptZAxis );
public:
	CTransformStack() : nClipFlagsPtr(0), nClipPlanes(0) {}
	void SetCamera( const SHMatrix& pos );
	// aspect = ysize/xsize
	// vShift это смещение из расчета того, что несмещенный экран простирается от [-1,1]
	void MakeProjective( float fAspect, float fFovX = 90, float fZMin = 0.1f, float fZMax = 100, const CVec2 &vShift = CVec2( 0, 0 ) );
	void MakeProjective( const CVec2 &screenRect, float fFovX = 90, float fZMin = 0.1f, float fZMax = 100, const CVec2 &vShift = CVec2( 0, 0 ) );
	void MakeParallel( float fWidth, float fHeight, float fZMin = 0.1f, float fZMax = 1000.0f );
	void MakeDirect( const CVec2 &screenRect );
	void Make( const SHMatrix &projection );
	// make clean transform stack 
	void Make() { Init(); ASSERT( nClipPlanes == 0 ); }
	void AddClipPlane( const CVec4 &v );
	bool IsIn( const SSphere &s );
	bool IsIn( const SBound &s );
	bool IsIn( const SSphere &s, const CVec3 &ptXAxis, const CVec3 &ptYAxis, const CVec3 &ptZAxis );
	bool PushClipHint( const SSphere &s );
	bool PushClipHint( const SBound &s );
	void PopClipHint();
	bool IsFullGet() const { return nClipFlags[ nClipFlagsPtr ] == 0; }
	const SFBTransform& GetProjection() const { return matrices[0]; }
	bool GetCoverRect( CTRect<float> *pRes, const CVec3 &ptCenter, float fRadius );
};
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// some inlined functions
////////////////////////////////////////////////////////////////////////////////////////////////////
// a&b 43
inline void Multiply43( SHMatrix *p, const SHMatrix &a, const SHMatrix &b )
{
	p->_11 = a._11*b._11 + a._12*b._21 + a._13*b._31;
	p->_12 = a._11*b._12 + a._12*b._22 + a._13*b._32;
	p->_13 = a._11*b._13 + a._12*b._23 + a._13*b._33;
	p->_14 = a._11*b._14 + a._12*b._24 + a._13*b._34 + a._14;

	p->_21 = a._21*b._11 + a._22*b._21 + a._23*b._31;
	p->_22 = a._21*b._12 + a._22*b._22 + a._23*b._32;
	p->_23 = a._21*b._13 + a._22*b._23 + a._23*b._33;
	p->_24 = a._21*b._14 + a._22*b._24 + a._23*b._34 + a._24;

	p->_31 = a._31*b._11 + a._32*b._21 + a._33*b._31;
	p->_32 = a._31*b._12 + a._32*b._22 + a._33*b._32;
	p->_33 = a._31*b._13 + a._32*b._23 + a._33*b._33;
	p->_34 = a._31*b._14 + a._32*b._24 + a._33*b._34 + a._34;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// b 3x3 a 4x3
inline void Multiply33( SHMatrix *p, const SHMatrix &a, const SHMatrix &b )
{
	p->_11 = a._11*b._11 + a._12*b._21 + a._13*b._31;
	p->_12 = a._11*b._12 + a._12*b._22 + a._13*b._32;
	p->_13 = a._11*b._13 + a._12*b._23 + a._13*b._33;
	p->_14 = a._14;

	p->_21 = a._21*b._11 + a._22*b._21 + a._23*b._31;
	p->_22 = a._21*b._12 + a._22*b._22 + a._23*b._32;
	p->_23 = a._21*b._13 + a._22*b._23 + a._23*b._33;
	p->_24 = a._24;

	p->_31 = a._31*b._11 + a._32*b._21 + a._33*b._31;
	p->_32 = a._31*b._12 + a._32*b._22 + a._33*b._32;
	p->_33 = a._31*b._13 + a._32*b._23 + a._33*b._33;
	p->_34 = a._34;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// b 4x3 a 4x4
inline void MultiplyF43( SHMatrix *p, const SHMatrix &a, const SHMatrix &b )
{
	p->_11 = a._11*b._11 + a._12*b._21 + a._13*b._31;
	p->_12 = a._11*b._12 + a._12*b._22 + a._13*b._32;
	p->_13 = a._11*b._13 + a._12*b._23 + a._13*b._33;
	p->_14 = a._11*b._14 + a._12*b._24 + a._13*b._34 + a._14;

	p->_21 = a._21*b._11 + a._22*b._21 + a._23*b._31;
	p->_22 = a._21*b._12 + a._22*b._22 + a._23*b._32;
	p->_23 = a._21*b._13 + a._22*b._23 + a._23*b._33;
	p->_24 = a._21*b._14 + a._22*b._24 + a._23*b._34 + a._24;

	p->_31 = a._31*b._11 + a._32*b._21 + a._33*b._31;
	p->_32 = a._31*b._12 + a._32*b._22 + a._33*b._32;
	p->_33 = a._31*b._13 + a._32*b._23 + a._33*b._33;
	p->_34 = a._31*b._14 + a._32*b._24 + a._33*b._34 + a._34;

	p->_41 = a._41*b._11 + a._42*b._21 + a._43*b._31;
	p->_42 = a._41*b._12 + a._42*b._22 + a._43*b._32;
	p->_43 = a._41*b._13 + a._42*b._23 + a._43*b._33;
	p->_44 = a._41*b._14 + a._42*b._24 + a._43*b._34 + a._44;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// b 3x3 a 4x4
inline void MultiplyF33( SHMatrix *p, const SHMatrix &a, const SHMatrix &b )
{
	p->_11 = a._11*b._11 + a._12*b._21 + a._13*b._31;
	p->_12 = a._11*b._12 + a._12*b._22 + a._13*b._32;
	p->_13 = a._11*b._13 + a._12*b._23 + a._13*b._33;
	p->_14 = a._14;

	p->_21 = a._21*b._11 + a._22*b._21 + a._23*b._31;
	p->_22 = a._21*b._12 + a._22*b._22 + a._23*b._32;
	p->_23 = a._21*b._13 + a._22*b._23 + a._23*b._33;
	p->_24 = a._24;

	p->_31 = a._31*b._11 + a._32*b._21 + a._33*b._31;
	p->_32 = a._31*b._12 + a._32*b._22 + a._33*b._32;
	p->_33 = a._31*b._13 + a._32*b._23 + a._33*b._33;
	p->_34 = a._34;

	p->_41 = a._41*b._11 + a._42*b._21 + a._43*b._31;
	p->_42 = a._41*b._12 + a._42*b._22 + a._43*b._32;
	p->_43 = a._41*b._13 + a._42*b._23 + a._43*b._33;
	p->_44 = a._44;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// a 4x4
inline void MultiplyFScale( SHMatrix *p, const SHMatrix &a, float x, float y, float z )
{
	p->_11 = a._11*x;
	p->_12 = a._12*y;
	p->_13 = a._13*z;
	p->_14 = a._14;

	p->_21 = a._21*x;
	p->_22 = a._22*y;
	p->_23 = a._23*z;
	p->_24 = a._24;

	p->_31 = a._31*x;
	p->_32 = a._32*y;
	p->_33 = a._33*z;
	p->_34 = a._34;

	p->_41 = a._41*x;
	p->_42 = a._42*y;
	p->_43 = a._43*z;
	p->_44 = a._44;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// b 3x3 a 4x4
inline void MultiplyF33Inv( SHMatrix *p, const SHMatrix &a, const SHMatrix &b )
{
	p->_11 = a._11*b._11 + a._12*b._12 + a._13*b._13;
	p->_12 = a._11*b._21 + a._12*b._22 + a._13*b._23;
	p->_13 = a._11*b._31 + a._12*b._32 + a._13*b._33;
	p->_14 = a._14;

	p->_21 = a._21*b._11 + a._22*b._12 + a._23*b._13;
	p->_22 = a._21*b._21 + a._22*b._22 + a._23*b._23;
	p->_23 = a._21*b._31 + a._22*b._32 + a._23*b._33;
	p->_24 = a._24;

	p->_31 = a._31*b._11 + a._32*b._12 + a._33*b._13;
	p->_32 = a._31*b._21 + a._32*b._22 + a._33*b._23;
	p->_33 = a._31*b._31 + a._32*b._32 + a._33*b._33;
	p->_34 = a._34;

	p->_41 = a._41*b._11 + a._42*b._12 + a._43*b._13;
	p->_42 = a._41*b._21 + a._42*b._22 + a._43*b._23;
	p->_43 = a._41*b._31 + a._42*b._32 + a._43*b._33;
	p->_44 = a._44;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void MultiplyTranslate( SHMatrix *p, const SHMatrix &a, const CVec3 &b )
{
	p->_11 = a._11;
	p->_12 = a._12;
	p->_13 = a._13;
	p->_14 = a._11*b.x + a._12*b.y + a._13*b.z + a._14;

	p->_21 = a._21;
	p->_22 = a._22;
	p->_23 = a._23;
	p->_24 = a._21*b.x + a._22*b.y + a._23*b.z + a._24;

	p->_31 = a._31;
	p->_32 = a._32;
	p->_33 = a._33;
	p->_34 = a._31*b.x + a._32*b.y + a._33*b.z + a._34;

	p->_41 = a._41; 
	p->_42 = a._42; 
	p->_43 = a._43; 
	p->_44 = a._41*b.x + a._42*b.y + a._43*b.z + a._44;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void MultiplyInvTranslate( SHMatrix *p, const SHMatrix &a, const CVec3 &b )
{
	p->_11 = a._11 - b.x * a._14;
	p->_12 = a._12 - b.y * a._14;
	p->_13 = a._13 - b.z * a._14;
	p->_14 = a._14;

	p->_21 = a._21 - b.x * a._24;
	p->_22 = a._22 - b.y * a._24;
	p->_23 = a._23 - b.z * a._24;
	p->_24 = a._24;

	p->_31 = a._31 - b.x * a._34;
	p->_32 = a._32 - b.y * a._34;
	p->_33 = a._33 - b.z * a._34;
	p->_34 = a._34;

	p->_41 = a._41 - b.x * a._14;
	p->_42 = a._42 - b.y * a._14;
	p->_43 = a._43 - b.z * a._14;
	p->_44 = a._44;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void MultiplyTranslate43( SHMatrix *p, const SHMatrix &a, const CVec3 &b )
{
	p->_11 = a._11;
	p->_12 = a._12;
	p->_13 = a._13;
	p->_14 = a._11*b.x + a._12*b.y + a._13*b.z + a._14;

	p->_21 = a._21;
	p->_22 = a._22;
	p->_23 = a._23;
	p->_24 = a._21*b.x + a._22*b.y + a._23*b.z + a._24;

	p->_31 = a._31;
	p->_32 = a._32;
	p->_33 = a._33;
	p->_34 = a._31*b.x + a._32*b.y + a._33*b.z + a._34;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// CMatrixStack43
////////////////////////////////////////////////////////////////////////////////////////////////////
template <int nMaxNumMatrices>
inline void CMatrixStack43<nMaxNumMatrices>::Push43( const SHMatrix &matrix ) 
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	Multiply43( &( this -> matrices[this -> nCurrentMatrix + 1] ), this -> matrices[this -> nCurrentMatrix], matrix );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CMatrixStack43<nMaxNumMatrices>::Push33( const SHMatrix &matrix ) 
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	Multiply33( &( this -> matrices[this -> nCurrentMatrix + 1] ), this -> matrices[this -> nCurrentMatrix], matrix );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CMatrixStack43<nMaxNumMatrices>::Push( const CVec3 &pos ) 
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	MultiplyTranslate43( &( this -> matrices[this -> nCurrentMatrix + 1] ), this -> matrices[this -> nCurrentMatrix], pos );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CMatrixStack43<nMaxNumMatrices>::Push( const CQuat &rot )
{
	SHMatrix matrix;
	rot.DecompEulerMatrix( &matrix );
	Push33( matrix );
}
template <int nMaxNumMatrices>
inline void CMatrixStack43<nMaxNumMatrices>::Push( const CVec3 &pos, const CQuat &rot )
{
	SHMatrix matrix;
	rot.DecompEulerMatrix( &matrix );
	matrix._14 = pos.x; matrix._24 = pos.y; matrix._34 = pos.z;
	Push43( matrix );
}
template <int nMaxNumMatrices>
inline void CMatrixStack43<nMaxNumMatrices>::PushScale( float x, float y, float z )
{
	SHMatrix matrix;
	Zero( matrix );
	matrix._11 = x; matrix._22 = y; matrix._33 = z;
	Push33( matrix );
}
template <int nMaxNumMatrices>
inline void CMatrixStack43<nMaxNumMatrices>::PushScale( float val ) 
{
	PushScale( val, val, val ); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// CFBMatrixStack
////////////////////////////////////////////////////////////////////////////////////////////////////
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::Push44( const SHMatrix &matrix ) 
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	Multiply( &( this -> matrices[this -> nCurrentMatrix + 1].forward ), this -> matrices[this -> nCurrentMatrix].forward, matrix );
	InvertMatrix( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix + 1].forward );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::Push43( const SHMatrix &matrix ) 
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	MultiplyF43( &( this -> matrices[this -> nCurrentMatrix + 1].forward ), this -> matrices[this -> nCurrentMatrix].forward, matrix );
	InvertMatrix( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix + 1].forward );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::Push33( const SHMatrix &matrix ) 
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	MultiplyF33( &( this -> matrices[this -> nCurrentMatrix + 1].forward ), this -> matrices[this -> nCurrentMatrix].forward, matrix );
	InvertMatrix( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix + 1].forward );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::Push33Orthonormal( const SHMatrix &matrix ) 
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	MultiplyF33( &( this -> matrices[this -> nCurrentMatrix + 1].forward ), this -> matrices[this -> nCurrentMatrix].forward, matrix );
	InvertMatrix( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix + 1].forward );
	//MultiplyF33Inv( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix].backward, matrix );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::Push33( const SHMatrix &matrix, const SHMatrix &invMatrix ) 
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	MultiplyF33( &( this -> matrices[this -> nCurrentMatrix + 1].forward ), this -> matrices[this -> nCurrentMatrix].forward, matrix );
	InvertMatrix( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix + 1].forward );
	//MultiplyF33( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix].backward, invMatrix );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::Push( const CVec3 &pos ) 
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	MultiplyTranslate( &( this -> matrices[this -> nCurrentMatrix + 1].forward ), this -> matrices[this -> nCurrentMatrix].forward, pos );
	InvertMatrix( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix + 1].forward );
	//MultiplyInvTranslate( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix].backward, pos );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::Push( const CQuat &rot )
{
	SHMatrix matrix;
	rot.DecompEulerMatrix( &matrix );
	Push33Orthonormal( matrix );
}
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::Push( const CVec3 &pos, const CQuat &rot )
{
	SHMatrix matrix;
	rot.DecompEulerMatrix( &matrix );
	Push( pos );
	Push33Orthonormal( matrix );
}
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::PushScale( float x, float y, float z )
{
	ASSERT( this -> nCurrentMatrix >= 0 );
	MultiplyFScale( &( this -> matrices[ this -> nCurrentMatrix + 1].forward ), this -> matrices[this -> nCurrentMatrix].forward, x, y, z );
	InvertMatrix( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix + 1].forward );
	//MultiplyFScale( &( this -> matrices[this -> nCurrentMatrix + 1].backward ), this -> matrices[this -> nCurrentMatrix].backward, 1/x, 1/y, 1/z );
	this -> nCurrentMatrix++;
}
template <int nMaxNumMatrices>
inline void CFBMatrixStack<nMaxNumMatrices>::PushScale( float val ) 
{
	PushScale( val, val, val ); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
