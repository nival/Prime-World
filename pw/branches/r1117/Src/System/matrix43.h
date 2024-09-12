#ifndef _MATRIX43_H_
#define _MATRIX43_H_

#include <System/Geom.h>
#include <xmmintrin.h>
#include <System/Decompose.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//__declspec(align(16))
struct Matrix43
{
#ifdef WIN32
  #pragma warning ( disable : 4201 )
#endif
  
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
		};
	};
#ifdef WIN32
  #pragma warning ( default : 4201 )
#endif  

  float GetUniformScale() const
	{
    float s = 
      sqr( _11 ) + sqr( _21 ) + sqr( _31 ) +
      sqr( _12 ) + sqr( _22 ) + sqr( _32 ) +
      sqr( _13 ) + sqr( _23 ) + sqr( _33 );
    return sqrt( s / 3.0f );
	}

	Matrix43 GetInversed() const
	{
		Matrix43 mat;
		const Matrix43& m = *this;

		float det =	m._11*(m._22*m._33 - m._23*m._32) + m._21*(m._13*m._32 - m._12*m._33) + m._31*(m._12*m._23 - m._13*m._22);
		if ( det == 0 ) return Matrix43();											 // singular matrix found !
		det = 1.0f/det;
		// calculate reverse rotation
		mat._11 = ( m._22*m._33 - m._23*m._32 ) * det;
		mat._12 = ( m._13*m._32 - m._12*m._33 ) * det;
		mat._13 = ( m._12*m._23 - m._13*m._22 ) * det;
		mat._14 = -( m._14*mat._11 + m._24*mat._12 + m._34*mat._13 );
		//
		mat._21 = ( m._23*m._31 - m._21*m._33 ) * det;
		mat._22 = ( m._11*m._33 - m._13*m._31 ) * det;
		mat._23 = ( m._13*m._21 - m._11*m._23 ) * det;
		mat._24 = -( m._14*mat._21 + m._24*mat._22 + m._34*mat._23 );
		//
		mat._31 = ( m._21*m._32 - m._22*m._31 ) * det;
		mat._32 = ( m._12*m._31 - m._11*m._32 ) * det;
		mat._33 = ( m._11*m._22 - m._12*m._21 ) * det;
		mat._34 = -( m._14*mat._31 + m._24*mat._32 + m._34*mat._33 );

		return mat;
	}

	///
	Matrix43& operator = ( const Matrix43& other )
	{
#ifdef _DEBUG
		if(&other == this)
			NI_ALWAYS_ASSERT( "this is the same matrix!" );
#endif
		memcpy( this, &other, sizeof(Matrix43) );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	__forceinline Matrix43 operator * ( const Matrix43& b ) const
	{
		Matrix43 res;

		res._11 = _11*b._11 + _12*b._21 + _13*b._31;
		res._12 = _11*b._12 + _12*b._22 + _13*b._32;
		res._13 = _11*b._13 + _12*b._23 + _13*b._33;
		res._14 = _11*b._14 + _12*b._24 + _13*b._34 + _14;

		res._21 = _21*b._11 + _22*b._21 + _23*b._31;
		res._22 = _21*b._12 + _22*b._22 + _23*b._32;
		res._23 = _21*b._13 + _22*b._23 + _23*b._33;
		res._24 = _21*b._14 + _22*b._24 + _23*b._34 + _24;

		res._31 = _31*b._11 + _32*b._21 + _33*b._31;
		res._32 = _31*b._12 + _32*b._22 + _33*b._32;
		res._33 = _31*b._13 + _32*b._23 + _33*b._33;
		res._34 = _31*b._14 + _32*b._24 + _33*b._34 + _34;

		return res;
	}

  __forceinline Matrix43 operator + ( const Matrix43& b ) const
  {
    Matrix43 res;

    res._11 = _11+b._11;
    res._12 = _12+b._12;
    res._13 = _13+b._13;
    res._14 = _14+b._14;

    res._21 = _21+b._21;
    res._22 = _22+b._22;
    res._23 = _23+b._23;
    res._24 = _24+b._24;

    res._31 = _31+b._31;
    res._32 = _32+b._32;
    res._33 = _33+b._33;
    res._34 = _34+b._34;

    return res;
  }

  __forceinline Matrix43 operator / ( float b ) const
  {
    Matrix43 res;

    res._11 = _11/b;
    res._12 = _12/b;
    res._13 = _13/b;
    res._14 = _14/b;

    res._21 = _21/b;
    res._22 = _22/b;
    res._23 = _23/b;
    res._24 = _24/b;

    res._31 = _31/b;
    res._32 = _32/b;
    res._33 = _33/b;
    res._34 = _34/b;

    return res;
  }

	///
	inline void Set( const CQuat& rot, const CVec3& trans, const CVec3& scale )
	{
		Set( rot, trans );

		_11 *= scale.x;
		_12 *= scale.y;
		_13 *= scale.z;
		_21 *= scale.x;
		_22 *= scale.y;
		_23 *= scale.z;
		_31 *= scale.x;
		_32 *= scale.y;
		_33 *= scale.z;
	}

	inline void Set( const CQuat& rot, const CVec3& trans )
	{
		SetRotationFromQuat( rot );
    SetTranslation( trans );
  }

  inline void SetScale( const CVec3& scale )
  {
    _11 = scale.x;
    _22 = scale.y;
    _33 = scale.z;
  }

  inline void SetTranslation( const CVec3& trans )
  {
    _14 = trans.x;
    _24 = trans.y;
    _34 = trans.z;
  }

  inline void Set( const CQuat& rot, const CVec4& trans, const CVec4& scale )
  {
    SetRotationFromQuat( rot );
    SetTranslation( trans.AsVec3D() );

    _11 *= scale.x;
    _12 *= scale.y;
    _13 *= scale.z;
    _21 *= scale.x;
    _22 *= scale.y;
    _23 *= scale.z;
    _31 *= scale.x;
    _32 *= scale.y;
    _33 *= scale.z;
  }

	inline void Set( const CVec4& rot, const CVec4& trans, const CVec4& scale )
	{
    Set( (const CQuat&)rot, trans, scale );
	}

	///
	inline void SetRotationFromQuat( const CQuat&	q )
	{
		const float tx	= q.x + q.x;
		const float ty	= q.y + q.y;
		const float tz	= q.z + q.z;
		const float twx = tx*q.w;
		const float twy = ty*q.w;
		const float twz = tz*q.w;
		const float txx = tx*q.x;
		const float txy = ty*q.x;
		const float txz = tz*q.x;
		const float tyy = ty*q.y;
		const float tyz = tz*q.y;
		const float tzz = tz*q.z;

		_11 = 1.0f - (tyy + tzz);
		_12 = txy - twz;
		_13 = txz + twy;

		_21 = txy + twz;
		_22 = 1.0f - (txx + tzz);
		_23 = tyz - twx;

		_31 = txz - twy;
		_32 = tyz + twx;
		_33 = 1.0f - (txx + tyy);
	}

	///
	void Set( const SHMatrix& matrix )
	{
		memcpy(this, reinterpret_cast< const void* >(&matrix), sizeof(*this) );
	}

	bool operator == ( const SHMatrix& matrix ) const
	{
		return _11 == matrix._11 && _12 == matrix._12 && _13 == matrix._13 && _14 == matrix._14
			&& _21 == matrix._21 && _22 == matrix._22 && _23 == matrix._23 && _24 == matrix._24
			&& _31 == matrix._31 && _32 == matrix._32 && _33 == matrix._33 && _34 == matrix._34;
	}

	bool operator!=( const SHMatrix &matrix ) const { return !(*this == matrix); }

	Matrix43()
	{
	}
	Matrix43( const CQuat& rot, const CVec3& trans )
	{
		Set( rot, trans, CVec3( 1.f, 1.f, 1.f ) );
	}

	Matrix43( const CVec3& trans )
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = trans.x;
		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;
		_24 = trans.y;
		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
		_34 = trans.z;
	}

  bool IsFinite() const
  {
      return 
        ni_math::isFiniteNumber(_11) != 0 && ni_math::isFiniteNumber(_12) != 0 && ni_math::isFiniteNumber(_13) != 0 && ni_math::isFiniteNumber(_14) != 0 &&
        ni_math::isFiniteNumber(_21) != 0 && ni_math::isFiniteNumber(_22) != 0 && ni_math::isFiniteNumber(_23) != 0 && ni_math::isFiniteNumber(_24) != 0 &&
        ni_math::isFiniteNumber(_31) != 0 && ni_math::isFiniteNumber(_32) != 0 && ni_math::isFiniteNumber(_33) != 0 && ni_math::isFiniteNumber(_34) != 0;
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline Matrix43( const CQuat& rot, const CVec3& trans, const CVec3& scale )
	{
		Set( rot, trans, scale );
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Matrix43 IDENTITY_MATRIX = Matrix43( QNULL, VNULL3 );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline bool operator==( const Matrix43& matrix1, const Matrix43& matrix2 )
{
	return memcmp( &matrix1, &matrix2, sizeof( matrix1 ) ) == 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline void Copy( SHMatrix* pRes, const Matrix43& matrix )
{
	memcpy(pRes, reinterpret_cast< const void* >(&matrix), sizeof(Matrix43) );
	pRes->_41 = pRes->_42 = pRes->_43 = 0.f; pRes->_44 = 1.f;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline void Identity( Matrix43* pRes ) 
{
	pRes->_11 = 1.0f;
	pRes->_12 = 0.0f;
	pRes->_13 = 0.0f;
	pRes->_14 = 0.0f;
	pRes->_21 = 0.0f;
	pRes->_22 = 1.0f;
	pRes->_23 = 0.0f;
	pRes->_24 = 0.0f;
	pRes->_31 = 0.0f;
	pRes->_32 = 0.0f;
	pRes->_33 = 1.0f;
	pRes->_34 = 0.0f;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline CVec3 Transform( const CVec3& v, const Matrix43& matrix )
{
	return CVec3(
		v.x * matrix._11 + v.y * matrix._12 + v.z * matrix._13 + matrix._14,
		v.x * matrix._21 + v.y * matrix._22 + v.z * matrix._23 + matrix._24,
		v.x * matrix._31 + v.y * matrix._32 + v.z * matrix._33 + matrix._34
	);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline CVec3 Rotate( const CVec3& v, const Matrix43& matrix )
{
	return CVec3(
		v.x * matrix._11 + v.y * matrix._12 + v.z * matrix._13,
		v.x * matrix._21 + v.y * matrix._22 + v.z * matrix._23,
		v.x * matrix._31 + v.y * matrix._32 + v.z * matrix._33
		);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline CVec4 TransformTransposed( const CVec4& v, const Matrix43& matrix )
{
	return CVec4(
		v.x * matrix._11 + v.y * matrix._21 + v.z * matrix._31,
		v.x * matrix._12 + v.y * matrix._22 + v.z * matrix._32,
		v.x * matrix._13 + v.y * matrix._23 + v.z * matrix._33,
		v.x * matrix._14 + v.y * matrix._24 + v.z * matrix._34 + v.w
	);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline float CalcRadius2( const SBound& b, const Matrix43& matrix )
{
	ASSERT( b.ptHalfBox.x >= 0 );
	ASSERT( b.ptHalfBox.y >= 0 );
	ASSERT( b.ptHalfBox.z >= 0 );
	CVec3 ptRes( matrix._11 * b.ptHalfBox.x, matrix._21 * b.ptHalfBox.x, matrix._31 * b.ptHalfBox.x );
	
	float sign = matrix._11 * matrix._12 + matrix._21 * matrix._22 + matrix._31 * matrix._32 < 0 ? -1 : 1;
	ptRes.x += matrix._12 * b.ptHalfBox.y * sign;
	ptRes.y += matrix._22 * b.ptHalfBox.y * sign;
	ptRes.z += matrix._32 * b.ptHalfBox.y * sign;

	sign = ptRes.x * matrix._13 + ptRes.y * matrix._23 + ptRes.z * matrix._33 < 0 ? -1 : 1;
	ptRes.x += matrix._13 * b.ptHalfBox.z * sign;
	ptRes.y += matrix._23 * b.ptHalfBox.z * sign;
	ptRes.z += matrix._33 * b.ptHalfBox.z * sign;

	return fabs2( ptRes );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Result = Matrix1 * Matrix2
// R = A * B
__forceinline void SEEMatrixMultiply( void* _result, const void* _matrix1, const void* _matrix2 )
{
	//float _11, _12, _13, _14;
	//float _21, _22, _23, _24;
	//float _31, _32, _33, _34;
	const __m128* A = reinterpret_cast<const __m128*>( _matrix1 );
	const __m128* B = reinterpret_cast<const __m128*>( _matrix2 );
	__m128* R = reinterpret_cast<__m128*>( _result );
	__m128 temp0, temp1, temp2;
	const __m128 C4 = {0.f, 0.f, 0.f, 1.f};

	temp0 = _mm_mul_ps( _mm_shuffle_ps( A[0], A[0], _MM_SHUFFLE(0,0,0,0) ), B[0] );
	temp1 = _mm_mul_ps( _mm_shuffle_ps( A[1], A[1], _MM_SHUFFLE(0,0,0,0) ), B[0] );
	temp2 = _mm_mul_ps( _mm_shuffle_ps( A[2], A[2], _MM_SHUFFLE(0,0,0,0) ), B[0] );

	temp0 = _mm_add_ps( _mm_mul_ps( _mm_shuffle_ps( A[0], A[0], _MM_SHUFFLE(1,1,1,1) ), B[1] ), temp0 );
	temp1 = _mm_add_ps( _mm_mul_ps( _mm_shuffle_ps( A[1], A[1], _MM_SHUFFLE(1,1,1,1) ), B[1] ), temp1 );
	temp2 = _mm_add_ps( _mm_mul_ps( _mm_shuffle_ps( A[2], A[2], _MM_SHUFFLE(1,1,1,1) ), B[1] ), temp2 );

	temp0 = _mm_add_ps( _mm_mul_ps( _mm_shuffle_ps( A[0], A[0], _MM_SHUFFLE(2,2,2,2) ), B[2] ), temp0 );
	temp1 = _mm_add_ps( _mm_mul_ps( _mm_shuffle_ps( A[1], A[1], _MM_SHUFFLE(2,2,2,2) ), B[2] ), temp1 );
	temp2 = _mm_add_ps( _mm_mul_ps( _mm_shuffle_ps( A[2], A[2], _MM_SHUFFLE(2,2,2,2) ), B[2] ), temp2 );

	R[0] = _mm_add_ps( _mm_mul_ps( _mm_shuffle_ps( A[0], A[0], _MM_SHUFFLE(3,3,3,3) ), C4 ), temp0 );
	R[1] = _mm_add_ps( _mm_mul_ps( _mm_shuffle_ps( A[1], A[1], _MM_SHUFFLE(3,3,3,3) ), C4 ), temp1 );
	R[2] = _mm_add_ps( _mm_mul_ps( _mm_shuffle_ps( A[2], A[2], _MM_SHUFFLE(3,3,3,3) ), C4 ), temp2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline void ComposeMatrix( Matrix43* matrix, const CVec3& pos, const CVec3& rot, float scale )
{
	CQuat rotation;

	float roll = -rot.x / 180.0f * FP_PI;
	float pitch = -rot.y / 180.0f * FP_PI;
	float yaw = -rot.z / 180.0f * FP_PI;

	float fHalfYaw = yaw * 0.5f;
	float fHalfPitch = pitch * 0.5f;
	float fHalfRoll = roll * 0.5f;

	float fCosYaw = cos( fHalfYaw );
	float fSinYaw = sin( fHalfYaw );
	float fCosPitch = cos( fHalfPitch );
	float fSinPitch = sin( fHalfPitch );
	float fCosRoll = cos( fHalfRoll );
	float fSinRoll = sin( fHalfRoll );

	rotation.x = fSinRoll * fCosPitch * fCosYaw - fCosRoll * fSinPitch * fSinYaw;
	rotation.y = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
	rotation.z = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
	rotation.w = fCosRoll * fCosPitch * fCosYaw + fSinRoll * fSinPitch * fSinYaw;

	matrix->_14 = pos.x;
	matrix->_24 = pos.y;
	matrix->_34 = pos.z;

	float tx = rotation.x + rotation.x;
	float ty = rotation.y + rotation.y;
	float tz = rotation.z + rotation.z;
	float twx = tx * rotation.w;
	float twy = ty * rotation.w;
	float twz = tz * rotation.w;
	float txx = tx * rotation.x;
	float txy = ty * rotation.x;
	float txz = tz * rotation.x;
	float tyy = ty * rotation.y;
	float tyz = tz * rotation.y;
	float tzz = tz * rotation.z;

	matrix->_11 = 1.0f - (tyy + tzz);
	matrix->_21 = txy - twz;
	matrix->_31 = txz + twy;

	matrix->_12 = txy + twz;
	matrix->_22 = 1.0f - (txx + tzz);
	matrix->_32 = tyz - twx;

	matrix->_13 = txz - twy;
	matrix->_23 = tyz + twx;
	matrix->_33 = 1.0f - (txx + tyy);

	matrix->_11 *= scale;
	matrix->_12 *= scale;
	matrix->_13 *= scale;
	matrix->_21 *= scale;
	matrix->_22 *= scale;
	matrix->_23 *= scale;
	matrix->_31 *= scale;
	matrix->_32 *= scale;
	matrix->_33 *= scale;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ComposeMatrix( Matrix43& matrix, const CVec3& pos, const CQuat& rotation, const CVec3& scale )
{
	matrix._14 = pos.x;
	matrix._24 = pos.y;
	matrix._34 = pos.z;

	float tx = rotation.x + rotation.x;
	float ty = rotation.y + rotation.y;
	float tz = rotation.z + rotation.z;
	float twx = -tx * rotation.w;
	float twy = -ty * rotation.w;
	float twz = -tz * rotation.w;
	float txx = tx * rotation.x;
	float txy = ty * rotation.x;
	float txz = tz * rotation.x;
	float tyy = ty * rotation.y;
	float tyz = tz * rotation.y;
	float tzz = tz * rotation.z;

	matrix._11 = 1.0f - (tyy + tzz);
	matrix._21 = txy - twz;
	matrix._31 = txz + twy;

	matrix._12 = txy + twz;
	matrix._22 = 1.0f - (txx + tzz);
	matrix._32 = tyz - twx;

	matrix._13 = txz - twy;
	matrix._23 = tyz + twx;
	matrix._33 = 1.0f - (txx + tyy);

	matrix._11 *= scale.x;
	matrix._12 *= scale.y;
	matrix._13 *= scale.z;
	matrix._21 *= scale.x;
	matrix._22 *= scale.y;
	matrix._23 *= scale.z;
	matrix._31 *= scale.x;
	matrix._32 *= scale.y;
	matrix._33 *= scale.z;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// inline void DecomposeMatrix( const Matrix43& source, CVec3& translation, CQuat& rotation, float& scale )
// {
// 	// extract translation
// 	translation.x = source._14;
// 	translation.y = source._24;
// 	translation.z = source._34;
// 
// 	// extract scale
// 	scale = sqrtf( source._11 * source._11 + source._21 * source._21 + source._31 * source._31 );
// 
// 	// extract rotation
//   float scaledTracePlusOne = 1.0f + (source._11 + source._22 + source._33) / scale;
// 	if ( scaledTracePlusOne > 10e-3f )
// 	{
// 		rotation.w = sqrtf( scaledTracePlusOne ) / 2.0f;
// 		rotation.x = (source._23 / scale - source._32 / scale) / (4.0f * rotation.w);
// 		rotation.y = (source._31 / scale - source._13 / scale) / (4.0f * rotation.w);
// 		rotation.z = (source._12 / scale - source._21 / scale) / (4.0f * rotation.w);
// 	}
// 	else if ( source._11 > source._22 && source._11 > source._33 )
// 	{
// 		rotation.x = sqrtf( 1.0f + source._11 / scale - source._22 / scale - source._33 / scale ) / 2.0f;
// 		rotation.y = (source._21 / scale + source._12 / scale) / (4.0f * rotation.x);
// 		rotation.z = (source._31 / scale + source._13 / scale) / (4.0f * rotation.x);
// 		rotation.w = (source._23 / scale - source._32 / scale) / (4.0f * rotation.x);
// 	}
// 	else if ( source._22 > source._33 )
// 	{
// 		rotation.y = sqrtf( 1.0f + source._22 / scale - source._11 / scale - source._33 / scale ) / 2.0f;
// 		rotation.x = (source._21 / scale + source._12 / scale) / (4.0f * rotation.y);
// 		rotation.z = (source._32 / scale + source._23 / scale) / (4.0f * rotation.y);
// 		rotation.w = (source._31 / scale - source._13 / scale) / (4.0f * rotation.y);
// 	}
// 	else
// 	{
// 		rotation.z = sqrtf( 1.0f + source._33 / scale - source._11 / scale - source._22 / scale ) / 2.0f;
// 		rotation.x = (source._31 / scale + source._13 / scale) / (4.0f * rotation.z);
// 		rotation.y = (source._32 / scale + source._23 / scale) / (4.0f * rotation.z);
// 		rotation.w = (source._12 / scale - source._21 / scale) / (4.0f * rotation.z);
// 	}
// 
// 	// renormalize rotation quaternion
// 	float len = sqrtf( rotation.x * rotation.x + rotation.y * rotation.y + rotation.z * rotation.z + rotation.w * rotation.w );
// 	rotation.x *= -len;
// 	rotation.y *= -len;
// 	rotation.z *= -len;
// 	rotation.w *= len;
// }

inline void DecomposeMatrix( const Matrix43& source, CVec3& translation, CQuat& rotation, CVec3& scale )
{
  SHMatrix shm;
  Copy( &shm, source );
  AffineParts parts;
  HMatrix A;
  memcpy(&A,&shm,sizeof(SHMatrix));
  decomp_affine(A,&parts);
  translation.x = parts.t.x;
  translation.y = parts.t.y;
  translation.z = parts.t.z;
  rotation.x = parts.q.x;
  rotation.y = parts.q.y;
  rotation.z = parts.q.z;
  rotation.w = parts.q.w;
  scale.x = parts.k.x;
  scale.y = parts.k.y;
  scale.z = parts.k.z;
}

struct DoubleMatrix43
{
#ifdef WIN32
#pragma warning ( disable : 4201 )
#endif

  union
  {
    struct
    {
      double _11, _12, _13, _14;
      double _21, _22, _23, _24;
      double _31, _32, _33, _34;
    };
  };
#ifdef WIN32
#pragma warning ( default : 4201 )
#endif

  DoubleMatrix43()
  {
    _11 = 1.0f;
    _12 = 0.0f;
    _13 = 0.0f;
    _14 = 0.0f;
    _21 = 0.0f;
    _22 = 1.0f;
    _23 = 0.0f;
    _24 = 0.0f;
    _31 = 0.0f;
    _32 = 0.0f;
    _33 = 1.0f;
    _34 = 0.0f;
  }

  DoubleMatrix43( const Matrix43& a )
  {
    _11 = a._11;
    _12 = a._12;
    _13 = a._13;
    _14 = a._14;

    _21 = a._21;
    _22 = a._22;
    _23 = a._23;
    _24 = a._24;

    _31 = a._31;
    _32 = a._32;
    _33 = a._33;
    _34 = a._34;
  }

  __forceinline DoubleMatrix43 operator * ( const DoubleMatrix43& b ) const
  {
    DoubleMatrix43 res;

    res._11 = _11*b._11 + _12*b._21 + _13*b._31;
    res._12 = _11*b._12 + _12*b._22 + _13*b._32;
    res._13 = _11*b._13 + _12*b._23 + _13*b._33;
    res._14 = _11*b._14 + _12*b._24 + _13*b._34 + _14;

    res._21 = _21*b._11 + _22*b._21 + _23*b._31;
    res._22 = _21*b._12 + _22*b._22 + _23*b._32;
    res._23 = _21*b._13 + _22*b._23 + _23*b._33;
    res._24 = _21*b._14 + _22*b._24 + _23*b._34 + _24;

    res._31 = _31*b._11 + _32*b._21 + _33*b._31;
    res._32 = _31*b._12 + _32*b._22 + _33*b._32;
    res._33 = _31*b._13 + _32*b._23 + _33*b._33;
    res._34 = _31*b._14 + _32*b._24 + _33*b._34 + _34;

    return res;
  }

  void GetMatrix43( Matrix43* a )
  {
    a->_11 = _11;
    a->_12 = _12;
    a->_13 = _13;
    a->_14 = _14;

    a->_21 = _21;
    a->_22 = _22;
    a->_23 = _23;
    a->_24 = _24;

    a->_31 = _31;
    a->_32 = _32;
    a->_33 = _33;
    a->_34 = _34;
  }

};


inline void DecomposeMatrix( const DoubleMatrix43& source, 
                            double& translationX, double& translationY, double& translationZ,
                            double& rotationX, double& rotationY, double& rotationZ, double& rotationW,
                            double& scale )
{
  // extract translation
  translationX = source._14;
  translationY = source._24;
  translationZ = source._34;

  // extract scale
  scale = sqrt( source._11 * source._11 + source._21 * source._21 + source._31 * source._31 );

  // extract rotation
  double scaledTracePlusOne = 1.0 + (source._11 + source._22 + source._33) / scale;
  if ( scaledTracePlusOne > 10e-6 )
  {
    rotationW = sqrt( scaledTracePlusOne ) / 2.0;
    rotationX = (source._23 / scale - source._32 / scale) / (4.0 * rotationW);
    rotationY = (source._31 / scale - source._13 / scale) / (4.0 * rotationW);
    rotationZ = (source._12 / scale - source._21 / scale) / (4.0 * rotationW);
  }
  else if ( source._11 > source._22 && source._11 > source._33 )
  {
    rotationX = sqrt( 1.0 + source._11 / scale - source._22 / scale - source._33 / scale ) / 2.0;
    rotationY = (source._21 / scale + source._12 / scale) / (4.0 * rotationX);
    rotationZ = (source._31 / scale + source._13 / scale) / (4.0 * rotationX);
    rotationW = (source._23 / scale - source._32 / scale) / (4.0 * rotationX);
  }
  else if ( source._22 > source._33 )
  {
    rotationY = sqrt( 1.0 + source._22 / scale - source._11 / scale - source._33 / scale ) / 2.0;
    rotationX = (source._21 / scale + source._12 / scale) / (4.0 * rotationY);
    rotationZ = (source._32 / scale + source._23 / scale) / (4.0 * rotationY);
    rotationW = (source._31 / scale - source._13 / scale) / (4.0 * rotationY);
  }
  else
  {
    rotationZ = sqrt( 1.0 + source._33 / scale - source._11 / scale - source._22 / scale ) / 2.0;
    rotationX = (source._31 / scale + source._13 / scale) / (4.0 * rotationZ);
    rotationY = (source._32 / scale + source._23 / scale) / (4.0 * rotationZ);
    rotationW = (source._12 / scale - source._21 / scale) / (4.0 * rotationZ);
  }

  // renormalize rotation quaternion
  double len = sqrt( rotationX * rotationX + rotationY * rotationY + rotationZ * rotationZ + rotationW * rotationW );
  rotationX *= -len;
  rotationY *= -len;
  rotationZ *= -len;
  rotationW *= len;
}

#endif	// _MATRIX43_H_

