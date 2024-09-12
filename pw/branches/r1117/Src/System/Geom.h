#ifndef _GEOM_H_
#define _GEOM_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <float.h>
#include "MathTools.h"

#ifndef WIN32
  #include <stdlib.h>
#endif

#include "./../../Data/GameLogic/Vec2_Base.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack( push, 4 )

#ifdef WIN32
  #pragma warning( push )
  #pragma warning( disable: 4201 ) // warning C4201: nonstandard extension used : nameless struct/union
#endif
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** different vector classes: 2D, 3D and 4D vectors with all necessary functions
// **
// **
// **
// ************************************************************************************************************************ //

const CVec2 VNULL2 = CVec2( 0, 0 );
const CVec2 V2_AXIS_X = CVec2( 1, 0 );
const CVec2 V2_AXIS_Y = CVec2( 0, 1 );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void CVec2::Maximize( const CVec2 &v ) { x = Max( x, v.x ); y = Max( y, v.y ); }

inline void CVec2::Minimize( const CVec2 &v ) { x = Min( x, v.x ); y = Min( y, v.y ); }

inline bool CVec2::IsFinite() const 
{ 
    return ni_math::isFiniteNumber(x) != 0 && ni_math::isFiniteNumber(y) != 0; 
}
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const float Cross( const CVec2 &a, const CVec2 &b )
{
	return a.x*b.y - a.y*b.x;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool operator==( const CVec2 &v1, const CVec2 &v2 ) { return ( (v1.x == v2.x) && (v1.y == v2.y) ); }
inline bool operator!=( const CVec2 &v1, const CVec2 &v2 ) { return ( (v1.x != v2.x) || (v1.y != v2.y) ); }
inline const CVec2 operator-( const CVec2 &a) { return CVec2(-a.x, -a.y); }
inline const CVec2 operator+( const CVec2 &a, const CVec2 &b ) { return CVec2( a.x + b.x, a.y + b.y ); }
inline const CVec2 operator-( const CVec2 &a, const CVec2 &b ) { return CVec2( a.x - b.x, a.y - b.y ); }
inline float operator*( const CVec2 &a, const CVec2 &b ) { return ( a.x*b.x + a.y*b.y ); }
inline const CVec2 operator*( const CVec2 &a, const float b ) { return CVec2( a.x*b, a.y*b ); }
inline const CVec2 operator*( const float a, const CVec2 &b ) { return CVec2( b.x*a, b.y*a ); }
inline const CVec2 operator/( const CVec2 &a, const float b ) { float b1 = 1.0f/b; return CVec2( a.x*b1, a.y*b1 ); }
inline float fabs2( const CVec2 &a ) { return fabs2( a.x, a.y ); }
inline float fabs( const CVec2 &a ) { return fabs( a.x, a.y ); }
inline bool Normalize( CVec2 *pVec ) { return Normalize(pVec->x, pVec->y); }
inline const CVec2 operator^( const CVec2 &a, const CVec2 &b ) { CVec2 vRes( a ); vRes ^= b; return vRes; }
inline const CVec2 CProduct( const CVec2 &a, const CVec2 &b ) { CVec2 vRes( a ); vRes.CProduct( b ); return vRes; }

struct D3DXVECTOR3;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3D vector
class CVec3
{
public:
	union
	{
		struct { float x, y, z; };
		struct { float r, g, b; };					// for color components
		struct { float u, v, q; };					// for texture coord
		float m[3];
	};
public:
  CVec3() {	}
	CVec3( const float _x, const float _y, const float _z ) : x( _x ), y( _y ), z( _z ) {	}
  CVec3( const float *_coords ) : x( _coords[0] ), y( _coords[1] ), z( _coords[2] ) {	}
	//CVec3( const float _x, const float _y, const float _z = 0.0f ) : x( _x ), y( _y ), z( _z ) {	}
	CVec3( const CVec2 &v2, const float _z ) : x( v2.x ), y( v2.y ), z( _z ) {	}
	// cross-vector assignment
	//CVec3& operator=( const CVec2 &v ) { x = v.x; y = v.y; z = 0.0f; return *this; }
	// setup
	void Set( const float _x, const float _y, const float _z ) { x = _x; y = _y; z = _z; }
	void Set( const CVec2 &v ) { x = v.x; y = v.y; }
	// "cast"
	const CVec2& AsVec2D() const { return *reinterpret_cast<const CVec2*>(this); }
  CVec2& AsVec2D() { return reinterpret_cast<CVec2&>(*this); }
	// indexed access
	float& operator[]( int i ) { return m[i]; };
	const float& operator[]( int i ) const { return m[i]; }
	// comparison
	bool operator==( const CVec3 &v ) const { return ( (v.x == x) && (v.y == y) && (v.z == z) ); }
	bool operator!=( const CVec3 &v ) const { return ( (v.x != x) || (v.y != y) || (v.z != z) ); }
	// internal data non-math modification
	__forceinline void Maximize( const CVec3 &v ) { x = Max( x, v.x ); y = Max( y, v.y ); z = Max( z, v.z ); }
	__forceinline void Minimize( const CVec3 &v ) { x = Min( x, v.x ); y = Min( y, v.y ); z = Min( z, v.z ); }
  //
  void Negate( const CVec3 &v ) { x = -v.x; y = -v.y; z = -v.z; } // this = -v
	void Negate() { x = -x; y = -y; z = -z; }		 // this = -this
	float Length() const { return sqrt(x*x+y*y+z*z); }		 
	float LengthSqr() const { return x*x+y*y+z*z; }
  void Add( const CVec3 &v1, const CVec3 &v2 ) { x = v1.x + v2.x; y = v1.y + v2.y; z = v1.z + v2.z; } // this = v1 + v2
	void Sub( const CVec3 &v1, const CVec3 &v2 ) { x = v1.x - v2.x; y = v1.y - v2.y; z = v1.z - v2.z; } // this = v1 - v2
  void Mul( const CVec3 &v1, const CVec3 &v2 ) { x = v1.x * v2.x; y = v1.y * v2.y; z = v1.z * v2.z; } // this = v1 - v2
  void Div( const CVec3 &v1, const CVec3 &v2 ) { x = v1.x / v2.x; y = v1.y / v2.y; z = v1.z / v2.z; } // this = v1 - v2
	void Displace( const CVec3 &v1, const CVec3 &v2, const float t ) { x = v1.x + t*v2.x; y = v1.y + t*v2.y; z = v1.z + t*v2.z; } //	this = v1 + t*v2
	void Displace( const CVec3 &v, const float t ) { x += t*v.x; y += t*v.y; z += t*v.z; } //	this += t*v;
	void Lerp( const float t, const CVec3 &v1, const CVec3 &v2 ) { x = t*v2.x + (1 - t)*v1.x; y = t*v2.y + (1 - t)*v1.y; z = t*v2.z + (1 - t)*v1.z; } //this = (1 - t)*v1 + t*v2
	void Interpolate( const CVec3 &v1, const CVec3 &v2, const float t ) { Lerp(t, v1, v2); }
	float Dot( const CVec3 &v ) const { return x*v.x + y*v.y + z*v.z; }
	// mathematical operations
	CVec3& operator+=( const CVec3 &v ) { x += v.x; y += v.y; z += v.z; return *this; }
	CVec3& operator-=( const CVec3 &v ) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	CVec3& operator*=( const float d ) { x *= d; y *= d; z *= d; return *this; }
	CVec3& operator/=( const float d ) { float d1 = 1.0f / d; x *= d1; y *= d1; z *= d1; return *this; }
  // check it
  bool IsFinite() const 
  { 
      return ni_math::isFiniteNumber(x) != 0 && ni_math::isFiniteNumber(y) != 0 && ni_math::isFiniteNumber(z) != 0; 
  }
  operator D3DXVECTOR3& () { return reinterpret_cast<D3DXVECTOR3&>(*this); }
  operator const D3DXVECTOR3& () const { return reinterpret_cast<const D3DXVECTOR3&>(*this); }

  static const CVec3& Zero() { static const CVec3 zero(0,0,0); return zero; }
  static const CVec3& Huge() { const float huge = 1.e16f; static const CVec3 vHuge(huge,huge,huge); return vHuge; }
  
  float X() const { return x; }
  float Y() const { return y; }
  float Z() const { return z; }
};

__forceinline D3DXVECTOR3* AsD3D(CVec3* _src)             { return (D3DXVECTOR3*)(_src); }
__forceinline const D3DXVECTOR3* AsD3D(const CVec3* _src) { return (D3DXVECTOR3*)(_src); }

__forceinline D3DXVECTOR3* AsD3D(vector<CVec3>& _src) { return &static_cast<D3DXVECTOR3&>(_src[0]); }
__forceinline const D3DXVECTOR3* AsD3D(const vector<const CVec3>& _src) { return &static_cast<const D3DXVECTOR3&>(_src[0]); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CVec3 VNULL3 = CVec3( 0, 0, 0 );
const CVec3 V3_AXIS_X = CVec3( 1, 0, 0 );
const CVec3 V3_AXIS_Y = CVec3( 0, 1, 0 );
const CVec3 V3_AXIS_Z = CVec3( 0, 0, 1 );
const CVec3 INITIALDIR3 = CVec3( 0, -1, 0 );
const CVec2 INITIALDIR2 = CVec2( 0, -1 );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SVec3Hash
{
	int operator()( const CVec3 &a ) const { const int *p = (const int*)&a; return p[0] ^ p[1] ^ p[2]; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const CVec3 Cross( const CVec3 &a, const CVec3 &b )
{
  return CVec3( a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const CVec3 operator-( const CVec3 &a) { return CVec3(-a.x, -a.y, -a.z); }
inline const CVec3 operator+( const CVec3 &a, const CVec3 &b ) { return CVec3( a.x + b.x, a.y + b.y, a.z + b.z ); }
inline const CVec3 operator-( const CVec3 &a, const CVec3 &b ) { return CVec3( a.x - b.x, a.y - b.y, a.z - b.z ); }
inline float operator*( const CVec3 &a, const CVec3 &b ) { return ( a.x*b.x + a.y*b.y + a.z*b.z ); }
inline const CVec3 operator*( const CVec3 &a, const float b ) { return CVec3( a.x*b, a.y*b, a.z*b ); }
inline const CVec3 operator*( const float a, const CVec3 &b ) { return CVec3( b.x*a, b.y*a, b.z*a ); }
inline const CVec3 operator/( const CVec3 &a, const float b ) { float b1 = 1.0f/b; return CVec3( a.x*b1, a.y*b1, a.z*b1 ); }
inline const CVec3 operator^( const CVec3 &a, const CVec3 &b ) { return CVec3( a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y ); }
inline float fabs2( const CVec3 &a ) { return fabs2( a.x, a.y, a.z ); }
inline float fabs( const CVec3 &a ) { return fabs( a.x, a.y, a.z ); }
inline bool Normalize( CVec3 *pVec ) { return Normalize(pVec->x, pVec->y, pVec->z); }

inline unsigned char floatToByte( const float fNumber ) { return (unsigned char)( fNumber * 127.0f ); }
inline float byteToFloat( const unsigned char cNumber ) { return float( char( cNumber ) ) / 127.0f; }
inline unsigned long Vec3ToDWORD( const CVec3 &v ) { return (unsigned long)( floatToByte( v.x ) ) | ( (unsigned long)( floatToByte( v.y ) ) << 8 ) | ( (unsigned long)( floatToByte( v.z ) ) << 16 ); }
inline const CVec3 DWORDToVec3( unsigned long dwVector ) { return CVec3( byteToFloat( dwVector & 0xff ), byteToFloat( (dwVector >> 8) & 0xff ), byteToFloat( (dwVector >> 16) & 0xff ) ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 4D vector
class CVec4
{
public:
	union
	{
		struct { float x, y, z, w;  };
		struct { float r, g, b, a;  };				// for color components
		struct { float u, v, q, ww; };				// for texture coord
		float m[4];
	};
public:
  CVec4() {	}
	CVec4( const float _x, const float _y, const float _z, const float _w ) : x( _x ), y( _y ), z( _z ), w( _w ) {	}
	//CVec4( const float _x, const float _y, const float _z = 0.0f, const float _w = 0.0f ) : x( _x ), y( _y ), z( _z ), w( _w ) {	}
  CVec4( const CVec2 &_v1, const CVec2 &_v2 ) : x( _v1.x ), y( _v1.y ), z( _v2.x ), w( _v2.y ) {	}
	CVec4( const CVec2 &v2, const float _z, const float _w ) : x( v2.x ), y( v2.y ), z( _z ), w( _w ) {	}
	CVec4( const CVec3 &v3, const float _w ) : x( v3.x ), y( v3.y ), z( v3.z ), w( _w ) {	}
	// setup
	void Set( const float _x, const float _y, const float _z, const float _w ) { x = _x; y = _y; z = _z; w = _w; }
	void Set( const CVec3 &v, const float _w ) { x = v.x, y = v.y; z = v.z; w = _w; }
	void Set( const class CQuat &q );
  // "cast"
  const CVec3& AsVec3D() const { return *reinterpret_cast<const CVec3*>(this); }
  CVec3& AsVec3D() { return reinterpret_cast<CVec3&>(*this); }
	// indexed access
	float& operator[]( int i ) { return m[i]; };
	const float& operator[]( int i ) const { return m[i]; }
	// comparison
	bool operator==( const CVec4 &v ) const { return ( (v.x == x) && (v.y == y) && (v.z == z) && (v.w == w) ); }
	bool operator!=( const CVec4 &v ) const { return ( (v.x != x) || (v.y != y) || (v.z != z) || (v.w != w) ); }
	// internal data non-math modification
	void Maximize( const CVec4 &v ) { x = Max( x, v.x ); y = Max( y, v.y ); z = Max( z, v.z ); w = Max( w, v.w ); }
	void Minimize( const CVec4 &v ) { x = Min( x, v.x ); y = Min( y, v.y ); z = Min( z, v.z ); w = Min( w, v.w ); }
	//
	void Negate( const CVec4 &v ) { x = -v.x; y = -v.y; z = -v.z; w = -v.w; } // this = -v
	void Negate() { x = -x; y = -y; z = -z; w = -w; }		 // this = -this
	void Add( const CVec4 &v1, const CVec4 &v2 ) { x = v1.x + v2.x; y = v1.y + v2.y; z = v1.z + v2.z; w = v1.w + v2.w; } // this = v1 + v2
	void Sub( const CVec4 &v1, const CVec4 &v2 ) { x = v1.x - v2.x; y = v1.y - v2.y; z = v1.z - v2.z; w = v1.w - v2.w; } // this = v1 - v2
	void Displace( const CVec4 &v1, const CVec4 &v2, const float t ) { x = v1.x + t*v2.x; y = v1.y + t*v2.y; z = v1.z + t*v2.z; w = v1.w + t*v2.w; } //	this = v1 + t*v2
	void Displace( const CVec4 &v, const float t ) { x += t*v.x; y += t*v.y; z += t*v.z; w += t*v.w; } //	this += t*v;
	void Lerp( const float t, const CVec4 &v1, const CVec4 &v2 ) { x = t*v2.x + (1 - t)*v1.x; y = t*v2.y + (1 - t)*v1.y; z = t*v2.z + (1 - t)*v1.z; w = t*v2.w + (1 - t)*v1.w; } //this = (1 - t)*v1 + t*v2
	void Interpolate( const CVec4 &v1, const CVec4 &v2, const float t ) { Lerp(t, v1, v2); }
	float Dot( const CVec4 &v ) const { return x*v.x + y*v.y + z*v.z + w*v.w; }
  // check it
  bool IsFinite() const 
  { 
      return ni_math::isFiniteNumber(x) != 0 && ni_math::isFiniteNumber(y) != 0 &&
             ni_math::isFiniteNumber(z) != 0 && ni_math::isFiniteNumber(w) != 0; 
  }
  
	// mathematical operations
	CVec4& operator+=( const CVec4 &v ) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	CVec4& operator-=( const CVec4 &v ) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	CVec4& operator*=( const float d ) { x *= d; y *= d; z *= d; w *= d; return *this; }
	CVec4& operator/=( const float d ) { float d1 = 1.0f / d; x *= d1; y *= d1; z *= d1; w *= d1; return *this; }
};
const CVec4 VNULL4 = CVec4( 0, 0, 0, 0 );
const CVec4 V4_AXIS_X = CVec4( 1, 0, 0, 0 );
const CVec4 V4_AXIS_Y = CVec4( 0, 1, 0, 0 );
const CVec4 V4_AXIS_Z = CVec4( 0, 0, 1, 0 );
const CVec4 V4_AXIS_W = CVec4( 0, 0, 0, 1 );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const CVec4 operator-( const CVec4 &a) { return CVec4(-a.x, -a.y, -a.z, -a.w); }
inline const CVec4 operator+( const CVec4 &a, const CVec4 &b ) { return CVec4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w ); }
inline const CVec4 operator-( const CVec4 &a, const CVec4 &b ) { return CVec4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w ); }
inline float operator*( const CVec4 &a, const CVec4 &b ) { return ( a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w ); }
inline const CVec4 operator*( const CVec4 &a, const float b ) { return CVec4( a.x*b, a.y*b, a.z*b, a.w*b ); }
inline const CVec4 operator*( const float a, const CVec4 &b ) { return CVec4( b.x*a, b.y*a, b.z*a, b.w*a ); }
inline const CVec4 operator/( const CVec4 &a, const float b ) { float b1 = 1.0f/b; return CVec4( a.x*b1, a.y*b1, a.z*b1, a.w*b1 ); }
inline float fabs2( const CVec4 &a ) { return fabs2( a.x, a.y, a.z, a.w ); }
inline float fabs( const CVec4 &a ) { return fabs( a.x, a.y, a.z, a.w ); }
inline bool Normalize( CVec4 *pVec ) { return Normalize(pVec->x, pVec->y, pVec->z, pVec->w); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CVecPolar
{
public:	
	float fLat, fLong;

	CVecPolar() { }
	CVecPolar( const float _fLat, const float _fLong ) : fLat( _fLat ), fLong( _fLong ) { }

	CVecPolar& operator+=( const CVecPolar &v ) { fLat += v.fLat; fLong += v.fLong; return *this; }
	CVecPolar& operator-=( const CVecPolar &v ) { fLat -= v.fLat; fLong -= v.fLong; return *this; }
};
inline const CVecPolar operator+( const CVecPolar &v1, const CVecPolar &v2 ) { return CVecPolar( v1.fLat + v2.fLat, v1.fLong + v2.fLong ); }
inline const CVecPolar operator-( const CVecPolar &v1, const CVecPolar &v2 ) { return CVecPolar( v1.fLat - v2.fLat, v1.fLong - v2.fLong ); }
const CVecPolar VNULLPOLAR = CVecPolar( 0.0f, 0.0f );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** 2D line, segment, circle and some useful functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SVector
{
	int x, y;
	//
  SVector() : x( 0 ), y( 0 ) {	}
	SVector( const int _x, const int _y ) : x( _x ), y( _y ) {	}
	SVector( const SVector &vec ) : x( vec.x ), y( vec.y ) {	}
	SVector( const CVec2 &vec ) : x( (int)vec.x ), y( (int)vec.y ) {	}

	const CVec2 ToCVec2() const { return CVec2( x, y ); }
	const CVec2 Norm() const 
	{ 
		if ( float revR = sqrt( float(x*x + y*y) ) )
		{
			revR = 1 / revR;
			return CVec2( float(x)*revR, float(y)*revR ); 
		}
		else
			return VNULL2;
	}
	//
	void TurnLeft()	 { swap( x, y ); x = -x; }
	void TurnRight() { swap( x, y ); y = -y; }

	void TurnLeftUntilAxis()
	{
		const short int signX = Sign( x );
		const short int signY = Sign( y );
		/*	
		if ( signX >= 0 && signY == -1 ) 	{ x = 1;	y = 0; return; }
		if ( signX == 1 && signY >= 0 )		{ x = 0;	y = 1; return; }
		if ( signX <= 0 && signY == 1 )		{ x = -1; y = 0; return; }
		if ( signX == -1 && signY <= 0 )	{ x = 0;	y = -1; return; }
		*/
		if ( signX != 0 && signX * signY >= 0 )
			x = 0, y = signX;
		else
			x = -signY, y = 0;
	}

	void TurnLeftUntil45()
	{
		const short int signX = Sign( x );
		const short int signY = Sign( y );

		if ( signX != 0 && signX * signY >= 0 )
		{
			if ( abs(x) > abs(y) )
				x = signX;
			else
				x = 0;
			y = signX;
		}
		else
		{
			if ( abs(y) > abs(x) )
				y = signY;
			else
				y = 0;

			x = -signY;
		}
	}

	void TurnLeftUntil90()
	{
		const int oldX = x;
		x = -y;
		y = oldX;
	}

	void TurnLeftUntil135()
	{
		x = -x;
		y = -y;
		TurnRightUntil45();
	}

	void TurnRightUntilAxis()
	{
		const short int signX = Sign( x );
		const short int signY = Sign( y );
		/*	
		if ( signX >=0 && signY == 1 )		{ x = 1;	y = 0; return; }
		if ( signX == -1 && signY >= 0 )	{ x = 0;	y = 1; return; }
		if ( signX <= 0 && signY == -1 )	{ x = -1; y = 0; return; }
		if ( signX == 1 && signY <= 0 )		{ x = 0;	y = -1; return; }
		*/
		if ( signX != 0 && signX * signY <= 0 ) 
			x = 0, y = -signX;
		else
			y = 0, x = signY;
	}

	void TurnRightUntil45()
	{
		const short int signX = Sign( x );
		const short int signY = Sign( y );

		if ( signX != 0 && signX * signY <= 0 ) 
		{
			if ( abs(x) > abs(y) )
				x = signX;
			else
				x = 0;
			y = -signX;
		}
		else
		{
			if ( abs(y) > abs(x) )
				y = signY;
			else
				y = 0;
			x = signY;
		}
	}

	void TurnRightUntil90()
	{
		const int oldX = x;
		x = y;
		y = -oldX;
	}

	void TurnRightUntil135()
	{
		x = -x;
		y = -y;
		TurnLeftUntil45();
	}

	const bool operator!=( const SVector &vec ) const { return x != vec.x || y != vec.y; }
	const bool operator==( const SVector &vec )	const { return x == vec.x && y == vec.y; }
	const SVector operator-( const SVector &vec ) const { return SVector( x-vec.x, y-vec.y ); }
	const SVector operator+( const SVector &vec ) const { return SVector( x+vec.x, y+vec.y ); }
	SVector& operator+=( const SVector &vec ) { x += vec.x; y += vec.y; return *this; }
	SVector& operator-=( const SVector &vec ) { x -= vec.x; y -= vec.y; return *this; }
	const int operator*( const SVector &vec ) const { return x*vec.x + y*vec.y; }
	SVector& operator*=( const int n ) { x *= n; y *= n; return *this; }
	// деление нацело
	SVector& operator/=( const int n ) { const float coeff = 1.0f / float(n); x *= (int)coeff; y *= (int)coeff; return *this; }
};
inline const SVector operator*( const SVector &a, const int b ) { return SVector( a.x*b, a.y*b ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const int fabs2( const SVector &vect )
{
	return ( vect.x * vect.x + vect.y * vect.y );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const float fabs( const SVector &vect )
{
	return fabs( vect.x, vect.y );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLine2
{
	// to ensure 4-bytes alignment without crap (multilayer sync fix)
	union
	{
		bool bNormalized;
		int dummy;
	};
public:
	float a, b, c;
//
  CLine2() : a( 0 ), b( 0 ), c( 0 ) { }
	CLine2( const float _a, const float _b, const float _c ) : dummy(0), a(_a), b(_b), c(_c) { }
	CLine2( const CVec2 &p1, const CVec2 &p2 ) : dummy(0), a( p2.y - p1.y ), b( p1.x - p2.x ), c( p2.x*p1.y - p1.x*p2.y ) {	}

	// расстояние до точки со знаком
	float DistToPoint( const CVec2 &point );
	// проекция точки на прямую
	void ProjectPoint( const CVec2 &point, CVec2 *result );
	// знак - в какой полуплоскости отн. прямой лежит точка
	const int GetSign( const CVec2 &point ) const { return Sign( (int)(a * point.x + b * point.y + c) ) ; }
  // перпендикуляр к прямой, проходящий через заданную точку
  CLine2* GetPerpendicularByPoint( const CVec2& point ) const { return new CLine2( b, -a, a*point.y - b*point.x ); }

	// нормализация линии
	void Normalize()
	{
		if ( !bNormalized )
		{
			const float fCoeff = 1.0f / fabs( a, b );
			a *= fCoeff;
			b *= fCoeff;
			c *= fCoeff;

			bNormalized = true;
		}
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSegment
{
public:
	//{ don't change order
	CVec2 p1, p2;
	CVec2 dir;
	//}
	//
	CSegment() { }
	CSegment( const CVec2 &_p1, const CVec2 &_p2 ) 
		: p1( _p1 ), p2( _p2 ), dir( p2 - p1 ) {	}
	CSegment( const float x1, const float y1, const float x2, const float y2 )
		: p1( x1, y1 ), p2( x2, y2 ), dir( p2 - p1 ) { }
	// расстояние от точки до отрезка
	const float GetDistToPoint( const CVec2 &point ) const;
	// дать точку на отрезке, ближайшую к заданной
	void GetClosestPoint( const CVec2 &point, CVec2 *result ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCircle
{
public:
	CVec2 center;
	float r;
	//
  CCircle() : r( 0 ) { }
	CCircle( const CVec2 &_center, const float _r ) 
		: center( _center ), r( _r ) {	}
	//
	const CVec2& GetCenter() const { return center; }
	bool IsIntersected( const CCircle &circle ) const
	{
		const float fDist2 = fabs2( circle.center - center );
		return fDist2 < sqr(r + circle.r);
	}
  bool IsInside( const CVec2 &pt ) const { return fabs2(pt - center) <= sqr(r); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// по касательному вектору (единичной длины), точке касания и радиусу
inline void GetCirclesByTangent( const CVec2 &tang, const CVec2 &p, const float r, CCircle *c1, CCircle *c2 );

inline int QuadraticEquation( double c2, double halfC1, double c0, double& x1, double& x2 );

//Пересекаем прямую с окружностью. Возвращаем кол-во точек пересечения.
inline int GetLineCircleIntersection( const CLine2& _line, const CCircle& _circle, CVec2& p1, CVec2& p2 );

// найти точки касания для касательной, проведённой из данной точки к окружности
inline bool FindTangentPoints( const CVec2 &p, const CCircle &c, CVec2 *p1, CVec2 *p2 );

// ориентированная ( против часовой - положительна ) площадь треугольника, помноженная на два
inline float TriangleArea2( const CVec2 &p1, const CVec2 &p2, const CVec2 &p3 );

inline float IsPointInsideTriangle( const CVec2 &p1, const CVec2 &p2, const CVec2 &p3, const CVec2 &p );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** plane in 3D space
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 plane in 3D space
	  		pt2
		   /
	  pt0
		   \
			  pt1
*/			
			
struct SPlane
{
public:
		CVec4 vec4;
public:
	SPlane() {	}
	SPlane( const CVec3 &n, const float d ) :  vec4(n.x, n.y, n.z, d) {	}
	SPlane( const CVec4 &v ) : vec4( v ) {	}
	SPlane( const SPlane &plane ) : vec4( plane.vec4 ) {	}
	// setup functions
	bool Set( const CVec3 &pt0, const CVec3 &pt1, const CVec3 &pt2, bool bNormalize );
	void Set( const CVec3 &pt0, const CVec3 &pt1, const CVec3 &pt2 );
	void Set( const CVec3 &vNormale, const float fDist ) { vec4.x = vNormale.x; vec4.y = vNormale.y; vec4.z = vNormale.z; vec4.ww = fDist; }
	// recalc 'd' coeff for a plane with the point 'pt'
	//void RecalcDist( const CVec3 &pt ) { d = -( n * pt ); }
	// distance functions
	float GetDistanceToPoint( const CVec3 &pt ) const 
	{ 
	  CVec3 n(vec4.x, vec4.y, vec4.z);
	  return ( n*pt + vec4.ww ); 
	}
	/*
	bool IsPointOnPlane( const CVec3 &pt ) const { return n*pt == -d; }
	bool IsPointOverPlane( const CVec3 &pt ) const { return n*pt > -d; }
	bool IsPointUnderPlane( const CVec3 &pt ) const { return n*pt < -d; }
	// протестировать, не лежит ли точка под плоскостью. вернуть 0x80000000 если это так или 0 в противном случае
	unsigned long CheckPointUnderPlane( const CVec3 &pt ) const;
	*/
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** homogeneous matrix (4x4) for any type of transformation
// **
// **	|x'|		|xx xy xz xw|		|x|				|x'|		|_11 _12 _13 _14|		|x|				|x'|		|x.x x.y x.z x.w|		|x|
// **	|y'|	=	|yx yy yz yw|	*	|y|				|y'|	=	|_21 _22 _23 _24|	*	|y|				|y'|	=	|y.x y.y y.z y.w|	*	|y|
// **	|z'|		|zx zy zz zw|		|z|				|z'|		|_31 _32 _33 _34|		|z|				|z'|		|z.x z.y z.z z.w|		|z|
// **	|w'|		|wx wy wz ww|		|w|				|w'|		|_41 _42 _43 _44|		|w|				|w'|		|w.x w.y w.z w.w|		|w|
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MVec3
{
  float x, y, z;
};

struct MVec4
{
  float x, y, z, w;
};

struct SHMatrix
{
public :
	union
	{
		float m[4][4];
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		struct
		{
			float xx, xy, xz, xw;
			float yx, yy, yz, yw;
			float zx, zy, zz, zw;
			float wx, wy, wz, ww;
		};
	};
public :
	float GetNormEstimate()
	{
		float fRes = 0.0f;
		for( int i = 0; i < 16; ++i )
		{
			fRes += m[0][i] * m[0][i];
		}		
		return fRes;
	}
	SHMatrix() { }
	SHMatrix( float __11, float __12, float __13, float __14,
						float __21, float __22, float __23, float __24,
						float __31, float __32, float __33, float __34,
						float __41, float __42, float __43, float __44 )
						: _11(__11), _12(__12), _13(__13), _14(__14),
							_21(__21), _22(__22), _23(__23), _24(__24),
							_31(__31), _32(__32), _33(__33), _34(__34),
							_41(__41), _42(__42), _43(__43), _44(__44) {	}
	//SHMatrix( float _m[4][4] ) { memcpy( &(m[0][0]), &(_m[0][0]), 16*sizeof(float) ); }
	//SHMatrix( float *_m ) { memcpy( &(m[0][0]), &(_m[0]), 16*sizeof(float) ); }
	SHMatrix( const CVec3 &vPos ) { Set( vPos ); }
	SHMatrix( const class CQuat &quat ) { Set( quat ); }
	SHMatrix( const CVec3 &vPos, const class CQuat &quat ) { Set( vPos, quat ); }
	//
	void Set( const CVec3 &vPos );
	void Set( const class CQuat &quat );
	void Set( const CVec3 &vPos, const class CQuat &quat );
	void Set( float __11, float __12, float __13, float __14,
						float __21, float __22, float __23, float __24,
						float __31, float __32, float __33, float __34,
						float __41, float __42, float __43, float __44 );
	// axis access
	
  const CVec4& GetX() const { return *reinterpret_cast<const CVec4*>(&_11); }
  const CVec4& GetY() const { return *reinterpret_cast<const CVec4*>(&_21); }
  const CVec4& GetZ() const { return *reinterpret_cast<const CVec4*>(&_31); }
  const CVec4& GetW() const { return *reinterpret_cast<const CVec4*>(&_41); }
	
	const CVec3& GetXAxis3() const { return *reinterpret_cast<const CVec3*>(&_11); }
	const CVec3& GetYAxis3() const { return *reinterpret_cast<const CVec3*>(&_21); }
	const CVec3& GetZAxis3() const { return *reinterpret_cast<const CVec3*>(&_31); }
	const CVec3 GetTrans3() const { return CVec3( _14, _24, _34 ); }
	const CVec4 GetTrans4() const { return CVec4( _14, _24, _34, _44 ); }
	// matrix-vector multiplication
	void Transform( CVec3 *pRes, const CVec3 &v ) const { RotateVector(pRes, v); }
	void TransformHomogeneous( CVec3 *pRes, const CVec3 &v ) const { RotateHVector(pRes, v); }
	void RotateVector( CVec3 *pRes, const CVec3 &v ) const;
	void RotateHVector( CVec3 *pRes, const CVec3 &v ) const;
	void RotateHVector( CVec4 *pRes, const CVec3 &v ) const;
	void RotateHVector( CVec4 *pRes, const CVec4 &v ) const;
	void RotateHVectorTransposed( CVec4 *pRes, const CVec4 &v ) const;
	void RotateVectorTransposed( CVec3 *pResult, const CVec3 &v ) const;
	void RotateHDirection( CVec4 *pResult, const CVec3 &pt ) const;
	bool HomogeneousInverse( const SHMatrix &m );
	const CVec3 GetTranslation() const { return CVec3( _14, _24, _34 ); }
};
inline bool operator==( const SHMatrix &a, const SHMatrix &b ) { return memcmp( &a, &b, sizeof(a) ) == 0; }
inline bool operator!=( const SHMatrix &a, const SHMatrix &b ) { return !(a == b); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// прямое и обратное преобразование вместе
struct SFBTransform
{
	SHMatrix forward, backward;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** quaternion
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//__declspec(align(16))
class CQuat
{
	// for use in the internal functions
	// to avoid ambiguity with angle-axis constructor
	CQuat( float fX, float fY, float fZ, float fW, int, int ) : x( fX ), y( fY ), z( fZ ), w( fW ) {	}

public:
	union
	{
		struct { float i, j, k, s; };
		struct { float x, y, z, w; };
	};
	CQuat( float fAngle, float fAxisX, float fAxisY, float fAxisZ, const bool bNormalizeAxis = false );
	CQuat( float fAngle, const CVec3 &vAxis, const bool bNormalizeAxis = false );
  CQuat( const CVec3 &vDir, const bool bNormalizeDir = false );
	CQuat( float yaw, float pitch, float roll );
	CQuat( const CVec4 &quat ) { x = quat.x; y = quat.y; z = quat.z; w = quat.w; }
  CQuat() : x( 0 ), y( 0 ), z( 0 ), w( 0 ) {}
	// composition
  void FromAngleAxis( float fAngle, const CVec3 &vAxis, const bool bNormalizeAxis = false );
  void FromAngleAxis( float fAngle, float fAxisX, float fAxisY, float fAxisZ, const bool bNormalizeAxis = false );
  void FromDirection( const CVec3 &vDir, const bool bNormalizeAxis = false );
	void FromEulerMatrix( const SHMatrix &m );
	void FromEulerAngles( float yaw, float pitch, float roll );
	void FromComponents( float _x, float _y, float _z, float _w ) { x = _x; y = _y; z = _z; w = _w; }
	void FromComponents( const CVec4 &vec4 ) { x = vec4.x; y = vec4.y; z =  vec4.z; w = vec4.w; }
	// decomposition
	void DecompAngleAxis( float *pfAngle, CVec3 *pvAxis ) const;
	void DecompAngleAxis( float *pfAngle, float *pfAxisX, float *pfAxisY, float *pfAxisZ ) const;
	void DecompEulerMatrix( SHMatrix *pMatrix ) const;
	void DecompEulerAngles( float *pfYaw, float *pfPitch, float *pfRoll ) const;
	void DecompEulerAnglesLof( float *pfYaw, float *pfPitch, float *pfRoll, float e ) const;
	void DecompReversedEulerMatrix( SHMatrix *pMatrix ) const;
	float	GetYaw() const;
	float	GetPitch() const;
	float	GetRoll() const;

  const CVec3 GetDirection() const { return Rotate( CVec3( 0.0f, 1.0f, 0.0f ) ); }

	// internal data non-math modification
	bool Normalize() { return ::Normalize(x, y, z, w); }
	void Maximize( const CQuat &v ) { x = Max( x, v.x ); y = Max( y, v.y ); z = Max( z, v.z ); w = Max( w, v.w ); }
	void Minimize( const CQuat &v ) { x = Min( x, v.x ); y = Min( y, v.y ); z = Min( z, v.z ); w = Min( w, v.w ); }
	//
	void Negate( const CQuat &q ) { x = -q.x; y = -q.y; z = -q.z; w = -q.w; } // this = -v
	void Negate() { x = -x; y = -y; z = -z; w = -w; }		 // this = -this
	bool Inverse( const CQuat &q );
	bool Inverse();
	void UnitInverse( const CQuat &q ) { x = -q.x; y = -q.y; z = -q.z; w = q.w; }
	void UnitInverse() { x = -x; y = -y; z = -z; }
	void UnitInverseX() { x = -x; }
	void UnitInverseY() { y = -y; }
	void UnitInverseZ() { z = -z; }
	//
	void Deriv( const CQuat &q, const CVec3 &v );
  
  void FromToRotation( const CVec3& from, const CVec3& to );
  void RotateToDirection( const CVec3& dir ) { FromToRotation( GetDirection(), dir ); }
  
  // some neccessary operators
  friend const CQuat operator*( const CQuat &a, const CQuat &b );
	friend const CQuat operator/( const CQuat &a, const CQuat &b );
	CQuat& operator*=( const CQuat &quat );
	CQuat& operator/=( const CQuat &quat );
	const CQuat operator+( const CQuat &q ) const { return CQuat( x + q.x, y + q.y, z + q.z, w + q.w, 0, 0 ); }
	const CQuat operator-() const { return CQuat( -x, -y, -z, -w, 0, 0 ); }				// unary minus
	float Dot( const CQuat &quat ) const { return x*quat.x + y*quat.y + z*quat.z + w*quat.w; }
	//
	void MinimizeRotationAngle() { if ( w < 0 ) { x = -x; y = -y; z = -z; w = -w; } }
	// mathematical functions
	const CQuat Exp() const;
	const CQuat Log() const;
	// interpolation
	// Spherical Linear intERPolation from 'p' to 'q' with coeff 'factor'
	void Slerp( const float factor, const CQuat &p, const CQuat &q );
	void Interpolate( const CQuat &p, const CQuat &q, const float t ) { Slerp(t, p, q); }
	// rotate vector via quaternion itself
	const CVec3 Rotate( const CVec3 &r ) const;
	void Rotate( CVec3 *pRes, const CVec3 &vec ) const;
	// rotate vectors 'X = (1, 0, 0)', 'Y = (0, 1, 0)' and 'Z = (0, 0, 1)' via quaternion
	const CVec3 GetXAxis() const;
	const CVec3 GetYAxis() const;
	const CVec3 GetZAxis() const;
	void GetXAxis( CVec3 *pResult ) const;
	void GetYAxis( CVec3 *pResult ) const;
	void GetZAxis( CVec3 *pResult ) const;
  // check it
  bool IsFinite() const 
  { 
      return ni_math::isFiniteNumber(x) != 0 && ni_math::isFiniteNumber(y) != 0 &&
             ni_math::isFiniteNumber(z) != 0 && ni_math::isFiniteNumber(w) != 0; 
  }
	//
	friend float fabs2( const CQuat &q ) { return fabs2( q.x, q.y, q.z, q.w ); }
	friend float fabs( const CQuat &q ) { return static_cast<float>( sqrt( fabs2(q) ) ); }
	
	const CVec4& GetInternalVector() const { return *reinterpret_cast<const CVec4*>(&x); }
};
const CQuat QNULL = CQuat( 0, 1, 0, 0 );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** POINT template
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TYPE>
class CTPoint
{
public:
  typedef CTPoint<TYPE> TPoint;
  union
  {
    struct { TYPE x, y; };
    struct { TYPE u, v; };
    struct { TYPE s, t; };
    struct { TYPE a, b; };
    struct { TYPE min, max; };
  };
  //
  CTPoint() { x = y = 0;	}
  CTPoint( TYPE _x, TYPE _y ) : x( _x ), y( _y ) {}

  template <typename TAnother>
  CTPoint( const CTPoint<TAnother> & pt ) : x( (TYPE)pt.x ), y( (TYPE)pt.y ) {}
  //
  TYPE & operator [] ( int i ) { return i ? y : x; }
  const TYPE & operator [] ( int i ) const { return i ? y : x; }
  //
  bool operator==( const TPoint &v ) const { return ( (v.x == x) && (v.y == y) ); }
  bool operator!=( const TPoint &v ) const { return ( (v.x != x) || (v.y != y) ); }
  // mathematical operations
  TPoint& operator+=( const TPoint &v ) { x += v.x; y += v.y; return *this; }
  TPoint& operator-=( const TPoint &v ) { x -= v.x; y -= v.y; return *this; }
  TPoint& operator*=( const TYPE d ) { x *= d; y *= d; return *this; }
  //
  void Set( const TYPE _x, const TYPE _y ) { x = _x; y = _y; }

  template <typename TAnother>
  void Set( const CTPoint<TAnother> & pt ) { x = (TYPE)pt.x; y = (TYPE)pt.y; }
};
template<class T>
inline float fabs( const CTPoint<T> &pt ) { return fabs( pt.x, pt.y ); }
template<class T>
inline float fabs2( const CTPoint<T> &pt ) { return fabs2( pt.x, pt.y ); }
template<class T>
inline const CTPoint<T> operator-( const CTPoint<T> &a) { return CTPoint<T>(-a.x, -a.y); }
template<class T>
inline const CTPoint<T> operator+( const CTPoint<T> &a, const CTPoint<T> &b ) { return CTPoint<T>( a.x + b.x, a.y + b.y ); }
template<class T>
inline const CTPoint<T> operator-( const CTPoint<T> &a, const CTPoint<T> &b ) { return CTPoint<T>( a.x - b.x, a.y - b.y ); }
template<class T>
inline const CTPoint<T> operator*( const CTPoint<T> &a, const float b ) { return CTPoint<T>( a.x*b, a.y*b ); }
template<class T>
inline const CTPoint<T> operator*( const T a, const CTPoint<T> &b ) { return CTPoint<T>( b.x*a, b.y*a ); }
template<class T>
inline const CTPoint<T> operator*( const CTPoint<T> &b, const T a ) { return CTPoint<T>( b.x*a, b.y*a ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** RECT template
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TYPE>
class CTRect
{
public:
	typedef CTRect<TYPE> TRect;
	typedef CTPoint<TYPE> TPoint;
	union																 // left (minimal) x
	{
		struct { TYPE left, top, right, bottom; };
		struct { TYPE x1, y1, x2, y2; };
		struct { TYPE minx, miny, maxx, maxy; };
	};
	//
	CTRect() { x1 = y1 = x2 = y2 = 0; }
	CTRect( const TYPE _minx, const TYPE _miny, const TYPE _maxx, const TYPE _maxy ) 
		: minx( _minx ), miny( _miny ), maxx( _maxx ), maxy( _maxy ) {	}
	CTRect( const TPoint &vLT, const TPoint &vRB ) 
		: minx( vLT.x ), miny( vLT.y ), maxx( vRB.x ), maxy( vRB.y ) {	}
	CTRect( const CVec2 &vLT, const CVec2 &vRB ) 
		: minx( vLT.x ), miny( vLT.y ), maxx( vRB.x ), maxy( vRB.y ) {	}
	template <class T1>
		explicit CTRect( const CTRect<T1> &rect ) // smirnov [2009/7/15]: implicit conversions lead to hard-to-find bugs
			: x1( rect.x1 ), y1( rect.y1 ), x2( rect.x2 ), y2( rect.y2 ) {	}
	CTRect( const TRect &rect ) 
		: x1( rect.x1 ), y1( rect.y1 ), x2( rect.x2 ), y2( rect.y2 ) {	}
	// assignment
	template <class T1>
		const TRect& operator=( const CTRect<T1> &rect ) { x1 = rect.x1; y1 = rect.y1; x2 = rect.x2; y2 = rect.y2; return *this; }
	const TRect& operator=( const TRect &rect ) { x1 = rect.x1; y1 = rect.y1; x2 = rect.x2; y2 = rect.y2; return *this; }
	void Set( const TYPE _x1, const TYPE _y1, const TYPE _x2, const TYPE _y2 ) { x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2; }
	void Set( const CVec2 &vLT, const CVec2 &vRB ) { minx = vLT.x; miny = vLT.y; maxx = vRB.x; maxy = vRB.y; }
	void Set( const TPoint &vLT, const TPoint &vRB ) { minx = vLT.x; miny = vLT.y; maxx = vRB.x; maxy = vRB.y; }
	void Set( const TRect &rect ) { x1 = rect.x1; y1 = rect.y1; x2 = rect.x2; y2 = rect.y2; }
	void SetEmpty() { minx = miny = maxx = maxy = 0; }
	void SetRect( const TYPE _x1, const TYPE _y1, const TYPE _x2, const TYPE _y2 ) { Set(_x1, _y1, _x2, _y2); }
	void SetRect( const CVec2 &vLT, const CVec2 &vRB ) { Set(vLT, vRB); }
	void SetRect( const TPoint &vLT, const TPoint &vRB ) { Set(vLT, vRB); }
	void SetRect( const TRect &rect ) { Set(rect); }
	void SetRectEmpty() { SetEmpty(); }
  //
  TYPE & operator [] ( int i ) { return const_cast < TYPE & > ( ( static_cast < const TRect * > ( this ) ) -> operator [] (i) ); }
  const TYPE & operator [] ( int i ) const {
    switch(i) {
      case 0: return x1;
      case 1: return y1;
      case 2: return x2;
      case 3: default: return y2; }
  }
	// operators
	void operator*=( float fScale ) { x1 *= fScale; y1 *= fScale; x2 *= fScale; y2 *= fScale; }
	// sizes access
	const TYPE Width() const { return ( maxx - minx ); }
	const TYPE Height() const { return ( maxy - miny ); }
	const TYPE GetSizeX() const { return Width(); }
	const TYPE GetSizeY() const { return Height(); }
	const TPoint GetSize() const { return TPoint( Width(), Height() ); }
	const TYPE GetArea() const { return Width() * Height(); }
	// corners access
	const TPoint GetLeftTop() const { return TPoint( minx, miny ); }
	const TPoint GetRightTop() const { return TPoint( maxx, miny ); }
	const TPoint GetLeftBottom() const { return TPoint( minx, maxy ); }
	const TPoint GetRightBottom() const { return TPoint( maxx, maxy ); }
	const TPoint GetCenter() const { return TPoint( (minx + maxx) / TYPE(2), (miny + maxy) / TYPE(2) ); }
	// checks
	bool operator==( const TRect &rc ) const { return (x1 == rc.x1) && (y1 == rc.y1) && (x2 == rc.x2) && (y2 == rc.y2); }
	bool operator!=( const TRect &rc ) const { return (x1 != rc.x1) || (y1 != rc.y1) || (x2 != rc.x2) || (y2 != rc.y2); }
	bool IsEmpty() const { return ( (minx >= maxx) || (miny >= maxy) ); }
	bool IsInside( const CVec2 &pt ) const { return (pt.x >= minx) && (pt.x <= maxx) && (pt.y >= miny) && (pt.y <= maxy); }
	bool IsInside( const TPoint &pt ) const { return (pt.x >= minx) && (pt.x <= maxx) && (pt.y >= miny) && (pt.y <= maxy); }
	bool IsInside( const TYPE &x, const TYPE &y ) const { return (x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy); }
	bool IsInside( const TRect &rect ) const { return (rect.minx >= minx) && (rect.maxx <= maxx) && (rect.miny >= miny) && (rect.maxy <= maxy); }
	bool IsIntersect( const TRect &rc ) const { return ( Max(minx, rc.minx) < Min(maxx, rc.maxx) ) && ( Max(miny, rc.miny) < Min(maxy, rc.maxy) ); }
	bool IsIntersectEdges( const TRect &rc ) const { return ( Max(minx, rc.minx) <= Min(maxx, rc.maxx) ) && ( Max(miny, rc.miny) <= Min(maxy, rc.maxy) ); }
	// intersection, union, etc
	void Intersect( const TRect &rect )
	{
		minx = Max( minx, rect.minx ); maxx = Min( maxx, rect.maxx );
		miny = Max( miny, rect.miny ); maxy = Min( maxy, rect.maxy );
	}
	TRect &Union( const TRect &rect )
	{
		if ( IsEmpty() )
			*this = rect;
		else if ( !rect.IsEmpty() )
		{
			minx = Min( minx, rect.minx ); maxx = Max( maxx, rect.maxx );
			miny = Min( miny, rect.miny ); maxy = Max( maxy, rect.maxy );
		}
		return *this;
	}
  void Add( const CVec2 &pt )
  {
    minx = Min( minx, pt.x ); maxx = Max( maxx, pt.x );
    miny = Min( miny, pt.y ); maxy = Max( maxy, pt.y );
  }
	// inflation / deflation
	void Inflate( const TYPE halfX, const TYPE halfY ) { x1 -= halfX; y1 -= halfY; x2 += halfX; y2 += halfY; }
	void Deflate( const TYPE halfX, const TYPE halfY ) { x1 += halfX; y1 += halfY; x2 -= halfX; y2 -= halfY; }
	// moving
	// move to point
	void MoveTo( const TYPE x, const TYPE y ) { x2 += x - x1; y2 += y - y1; x1 = x; y1 = y; }
	void MoveTo( const TPoint &pt ) { MoveTo(pt.x, pt.y); }
	void MoveTo( const CVec2 &pt ) { MoveTo(pt.x, pt.y); }
	// move to dist
	void Move( const TYPE dx, const TYPE dy ) { x1 += dx; y1 += dy; x2 += dx; y2 += dy; }
	void Move( const TPoint &pt ) { Move(pt.x, pt.y); }
	void Move( const CVec2 &pt ) { Move(pt.x, pt.y); }
	// normalization
	void Normalize() { Set( Min( minx, maxx ), Min( miny, maxy ), Max( minx, maxx ), Max( miny, maxy ) ); }

	// BEWARE of floating-point precision!
	bool IsSame( const TRect &rect ) { return x1 == rect.x1 && x2 == rect.x2 && y1 == rect.y1 && y2 == rect.y2; }
	bool HasSameSize( const TRect &rect ) { return GetSizeX() == rect.GetSizeX() && GetSizeY() == rect.GetSizeY(); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CTRect<int> noCrop(0,0,0,0);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// triangle
struct STriangle
{
	unsigned short i1, i2, i3;
	//
	STriangle() {}
	STriangle( unsigned short _i1, unsigned short _i2, unsigned short _i3 ): i1(_i1), i2(_i2), i3(_i3) {}
	//
	void Set( const unsigned short _i1, const unsigned short _i2, const unsigned short _i3 ) { i1 = _i1; i2 = _i2; i3 = _i3; }
};
// ориентированная ( против часовой - положительна ) площадь треугольника, помноженная на два
inline float TriangleAAA( const CVec2 &p1, const CVec2 &p2, const CVec2 &p3 )
{
	return p1.x * ( p2.y - p3.y ) + p2.x * ( p3.y - p1.y ) + p3.x * ( p1.y - p2.y );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SEdge
{
	unsigned short wStart, wFinish;
	//
	SEdge() {}
	SEdge( unsigned short _wS, unsigned short _wF ): wStart(_wS), wFinish(_wF) {}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRay
{ 
public:
	CVec3 ptOrigin, ptDir;
	//
	CRay(){}
	CRay(const CVec3 &_ptOrigin, const CVec3 &_ptDir) : ptOrigin(_ptOrigin), ptDir(_ptDir) {}
	CVec3 Get( float fT ) const { return ptOrigin + ptDir * fT; }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
struct SSphere
{
	CVec3 ptCenter;
	float fRadius;

	SSphere() {}
	SSphere( const CVec3 &_ptCenter, float _fRadius ): ptCenter(_ptCenter), fRadius(_fRadius) {}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SMassSphere
{
	CVec3 ptCenter;
	float fRadius;
	float fMass;

	SMassSphere() {}
	SMassSphere( const CVec3 &_ptCenter, float _fRadius, float _fMass ):
		ptCenter(_ptCenter), fRadius(_fRadius), fMass(_fMass) {}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SBound
{
	SSphere s;
	CVec3 ptHalfBox;

	SBound() : ptHalfBox( 0.f, 0.f, 0.f ) {}
	
	void BoxInit( const CVec3 &ptMin, const CVec3 &ptMax )
	{
		ptHalfBox = ( ptMax - ptMin ) * 0.5f;
		s.ptCenter = ( ptMax + ptMin ) * 0.5f;
		s.fRadius = fabs( ptHalfBox );
	}
	void BoxExInit( const CVec3 &_ptCenter, const CVec3 &_ptHalfBox )
	{
		s.ptCenter = _ptCenter;
		s.fRadius = fabs( _ptHalfBox );
		ptHalfBox = _ptHalfBox;
	}
	void SphereInit( const CVec3 &_ptCenter, float fRadius )
	{
		s.ptCenter = _ptCenter;
		s.fRadius = fRadius;
		ptHalfBox = CVec3( fRadius, fRadius, fRadius );
	}
	void Extend( float fAxisHalfSize )
	{
		ptHalfBox.x += fAxisHalfSize; ptHalfBox.y += fAxisHalfSize; ptHalfBox.z += fAxisHalfSize;
		s.fRadius = fabs( ptHalfBox );
	}
	void Grow( const SBound& toadd )
	{
		if ( fabs( ptHalfBox ) > 0.0001f )
		{
			CVec3 ptMax =  s.ptCenter + ptHalfBox;
			ptMax.Maximize( toadd.s.ptCenter + toadd.ptHalfBox );

			CVec3 ptMin =  s.ptCenter - ptHalfBox;
			ptMin.Minimize( toadd.s.ptCenter - toadd.ptHalfBox );

			ptHalfBox = ( ptMax - ptMin ) * 0.5f;
			s.ptCenter = ( ptMax + ptMin ) * 0.5f;
			s.fRadius = fabs( ptHalfBox );
		}
		else
		{
			s = toadd.s;
			ptHalfBox = toadd.ptHalfBox;
		}
	}
	bool IsInside( const CVec3 &v )
	{
		CVec3 vTest( s.ptCenter - v );
		if ( fabs2( vTest ) > fabs2( s.fRadius ) )
			return false;
		return fabs( vTest.x ) <= ptHalfBox.x && fabs( vTest.y ) < ptHalfBox.y && fabs( vTest.z ) < ptHalfBox.z;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool DoesIntersect( const SBound &a, const SBound &b )
{
	CVec3 ptDif = a.s.ptCenter - b.s.ptCenter;
	if ( fabs2(ptDif) > fabs2( a.s.fRadius + b.s.fRadius ) )
		return false;
	if ( 
		fabs(ptDif.x) > a.ptHalfBox.x + b.ptHalfBox.x || 
		fabs(ptDif.y) > a.ptHalfBox.y + b.ptHalfBox.y || 
		fabs(ptDif.z) > a.ptHalfBox.z + b.ptHalfBox.z )
		return false;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** plane realization
/*

   **			pt2
   **		 /
   **	pt0
   **		\
   **			pt1
*/   
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
inline bool SPlane::Set( const CVec3 &pt0, const CVec3 &pt1, const CVec3 &pt2, bool bNormalize )
{
	CVec3 v1( pt1.x - pt0.x, pt1.y - pt0.y, pt1.z - pt0.z ), v2( pt2.x - pt0.x, pt2.y - pt0.y, pt2.z - pt0.z );
	if ( bNormalize && ( !Normalize(&v1) || !Normalize(&v2) ) )
		return false;
	// calc normale
	n = v1 ^ v2;
	if ( bNormalize && !Normalize(&n) )
		return false;
	// calc distance coeff
	d = -( pt0 * n );
	//
	return true;
}
inline void SPlane::Set( const CVec3 &pt0, const CVec3 &pt1, const CVec3 &pt2 )
{
	CVec3 v1( pt1.x - pt0.x, pt1.y - pt0.y, pt1.z - pt0.z ), v2( pt2.x - pt0.x, pt2.y - pt0.y, pt2.z - pt0.z );
	// calc normale
	n = v1 ^ v2;
	// calc distance coeff
	d = -( pt0 * n );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// протестировать, не лежит ли точка под плоскостью.
// вернуть 0x80000000 если это так или 0 в противном случае
inline unsigned long SPlane::CheckPointUnderPlane( const CVec3 &pt ) const
{
	float fDist = n*pt + d;
	return ( FP_BITS(fDist) & 0x80000000 );
}


*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** matrix realization
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Identity( SHMatrix *pRes )
{
	MemSetDWord( reinterpret_cast<unsigned long*>(pRes), 0, 16 );
	pRes->_11 = pRes->_22 = pRes->_33 = pRes->_44 = 1.0f;
}
//#pragma optimize( "aw", off )
// allow &m == p
inline void Transpose( SHMatrix *p, const SHMatrix &m )
{
	p->Set( m._11, m._21, m._31, m._41,
		m._12, m._22, m._32, m._42,
		m._13, m._23, m._33, m._43,
		m._14, m._24, m._34, m._44 );
}
//#pragma optimize( "", on )
inline void SHMatrix::Set( const CVec3 &vPos )
{
	// zero everything
	MemSetDWord( reinterpret_cast<unsigned long*>(this), 0, 16 );
	// identity
	_11 = _22 = _33 = _44 = 1.0f;
	// write position to last column
	_14 = vPos.x; _24 = vPos.y; _34 = vPos.z;
}
inline void SHMatrix::Set( const CQuat &quat )
{
	// decomp quaternion to 3x3 minor
	quat.DecompEulerMatrix( this );
	// reset other components to default
	_14 = _24 = _34 = _41 = _42 = _43 = 0;
	_44 = 1;
}
inline void SHMatrix::Set( const CVec3 &vPos, const CQuat &quat )
{
	// decomp quaternion to 3x3 minor
	quat.DecompEulerMatrix( this );
	// write position to last column
	_14 = vPos.x; _24 = vPos.y; _34 = vPos.z;
	// reset other components to default
	_41 = _42 = _43 = 0;
	_44 = 1;
}
inline void SHMatrix::Set( float __11, float __12, float __13, float __14,
													 float __21, float __22, float __23, float __24,
													 float __31, float __32, float __33, float __34,
													 float __41, float __42, float __43, float __44 )
{
	_11 = __11; _12 = __12; _13 = __13; _14 = __14;
	_21 = __21; _22 = __22; _23 = __23; _24 = __24;
	_31 = __31; _32 = __32; _33 = __33; _34 = __34;
	_41 = __41; _42 = __42; _43 = __43; _44 = __44;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Multiply( SHMatrix *p, const SHMatrix &a, const SHMatrix &b )
{
	p->_11 = a._11*b._11 + a._12*b._21 + a._13*b._31 + a._14*b._41;
	p->_12 = a._11*b._12 + a._12*b._22 + a._13*b._32 + a._14*b._42;
	p->_13 = a._11*b._13 + a._12*b._23 + a._13*b._33 + a._14*b._43;
	p->_14 = a._11*b._14 + a._12*b._24 + a._13*b._34 + a._14*b._44;

	p->_21 = a._21*b._11 + a._22*b._21 + a._23*b._31 + a._24*b._41;
	p->_22 = a._21*b._12 + a._22*b._22 + a._23*b._32 + a._24*b._42;
	p->_23 = a._21*b._13 + a._22*b._23 + a._23*b._33 + a._24*b._43;
	p->_24 = a._21*b._14 + a._22*b._24 + a._23*b._34 + a._24*b._44;

	p->_31 = a._31*b._11 + a._32*b._21 + a._33*b._31 + a._34*b._41;
	p->_32 = a._31*b._12 + a._32*b._22 + a._33*b._32 + a._34*b._42;
	p->_33 = a._31*b._13 + a._32*b._23 + a._33*b._33 + a._34*b._43;
	p->_34 = a._31*b._14 + a._32*b._24 + a._33*b._34 + a._34*b._44;

	p->_41 = a._41*b._11 + a._42*b._21 + a._43*b._31 + a._44*b._41;
	p->_42 = a._41*b._12 + a._42*b._22 + a._43*b._32 + a._44*b._42;
	p->_43 = a._41*b._13 + a._42*b._23 + a._43*b._33 + a._44*b._43;
	p->_44 = a._41*b._14 + a._42*b._24 + a._43*b._34 + a._44*b._44;
}
inline void MultiplyScale( SHMatrix *p, const SHMatrix &a, const float fX, const float fY, const float fZ )
{
	p->_11 = a._11*fX;
	p->_12 = a._12*fY;
	p->_13 = a._13*fZ;
	p->_14 = a._14;

	p->_21 = a._21*fX;
	p->_22 = a._22*fY;
	p->_23 = a._23*fZ;
	p->_24 = a._24;

	p->_31 = a._31*fX;
	p->_32 = a._32*fY;
	p->_33 = a._33*fZ;
	p->_34 = a._34;

	p->_41 = a._41*fX;
	p->_42 = a._42*fY;
	p->_43 = a._43*fZ;
	p->_44 = a._44;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const SHMatrix operator*( const SHMatrix &a, const SHMatrix &b )
{
	SHMatrix ret;
	Multiply( &ret, a, b );
	return ret;
}
inline SFBTransform operator*( const SFBTransform &a, const SFBTransform &b ) 
{ 
	SFBTransform res;
	res.forward = a.forward * b.forward;
	res.backward = b.backward * a.backward;
	return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#pragma optimize( "aw", off )
inline void SHMatrix::RotateVector( CVec3 *pResult, const CVec3 &pt ) const
{
	const float x = _11*pt.x + _12*pt.y + _13*pt.z;
	const float y = _21*pt.x + _22*pt.y + _23*pt.z;
	const float z = _31*pt.x + _32*pt.y + _33*pt.z;
	pResult->Set( x, y, z );
}
inline void SHMatrix::RotateVectorTransposed( CVec3 *pResult, const CVec3 &pt ) const
{
	const float x = pt.x, y = pt.y, z = pt.z;
	pResult->x = _11*x + _21*y + _31*z;
	pResult->y = _12*x + _22*y + _32*z;
	pResult->z = _13*x + _23*y + _33*z;
}
inline void SHMatrix::RotateHDirection( CVec4 *pResult, const CVec3 &pt ) const
{
	const float x = pt.x, y = pt.y, z = pt.z;
	pResult->x = _11*x + _12*y + _13*z;
	pResult->y = _21*x + _22*y + _23*z;
	pResult->z = _31*x + _32*y + _33*z;
	pResult->w = _41*x + _42*y + _43*z;
}
inline void SHMatrix::RotateHVector( CVec3 *pResult, const CVec3 &pt ) const
{
	const float x = _11*pt.x + _12*pt.y + _13*pt.z + _14;
	const float y = _21*pt.x + _22*pt.y + _23*pt.z + _24;
	const float z = _31*pt.x + _32*pt.y + _33*pt.z + _34;
	pResult->Set( x, y, z );
}
inline void SHMatrix::RotateHVector( CVec4 *pResult, const CVec3 &pt ) const
{
	const float x = _11*pt.x + _12*pt.y + _13*pt.z + _14;
	const float y = _21*pt.x + _22*pt.y + _23*pt.z + _24;
	const float z = _31*pt.x + _32*pt.y + _33*pt.z + _34;
	const float w = _41*pt.x + _42*pt.y + _43*pt.z + _44;
	pResult->Set( x, y, z, w );
}
inline void SHMatrix::RotateHVector( CVec4 *pResult, const CVec4 &pt ) const
{
	const float x = _11*pt.x + _12*pt.y + _13*pt.z + _14*pt.w;
	const float y = _21*pt.x + _22*pt.y + _23*pt.z + _24*pt.w;
	const float z = _31*pt.x + _32*pt.y + _33*pt.z + _34*pt.w;
	const float w = _41*pt.x + _42*pt.y + _43*pt.z + _44*pt.w;
	pResult->Set( x, y, z, w );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void SHMatrix::RotateHVectorTransposed( CVec4 *pResult, const CVec4 &pt ) const
{
	const float x = _11*pt.x + _21*pt.y + _31*pt.z + _41*pt.w;
	const float y = _12*pt.x + _22*pt.y + _32*pt.z + _42*pt.w;
	const float z = _13*pt.x + _23*pt.y + _33*pt.z + _43*pt.w;
	const float w = _14*pt.x + _24*pt.y + _34*pt.z + _44*pt.w;
	pResult->Set( x, y, z, w );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool SHMatrix::HomogeneousInverse( const SHMatrix &m )
{
	float det =	m._11*(m._22*m._33 - m._23*m._32) + m._21*(m._13*m._32 - m._12*m._33) + m._31*(m._12*m._23 - m._13*m._22);
	if ( det == 0 )
		return false;											 // singular matrix found !
	det = 1.0f/det;
	// calculate reverse rotation
	_11 = ( m._22*m._33 - m._23*m._32 ) * det;
	_12 = ( m._13*m._32 - m._12*m._33 ) * det;
	_13 = ( m._12*m._23 - m._13*m._22 ) * det;
	_14 = -( m._14*_11 + m._24*_12 + m._34*_13 );
	//
	_21 = ( m._23*m._31 - m._21*m._33 ) * det;
	_22 = ( m._11*m._33 - m._13*m._31 ) * det;
	_23 = ( m._13*m._21 - m._11*m._23 ) * det;
	_24 = -( m._14*_21 + m._24*_22 + m._34*_23 );
	//
	_31 = ( m._21*m._32 - m._22*m._31 ) * det;
	_32 = ( m._12*m._31 - m._11*m._32 ) * det;
	_33 = ( m._11*m._22 - m._12*m._21 ) * det;
	_34 = -( m._14*_31 + m._24*_32 + m._34*_33 );
	//
	_41 = _42 = _43 = 0.0f;
	_44 = 1.0f;
	//
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void SetLookAtZ( SHMatrix *pRes, CVec3 const& from, CVec3 const& to)
{
	pRes->Set(from);
	CVec3 zaxis = to - from;
	if (Normalize(&zaxis))
	{
		CVec3 xaxis = V3_AXIS_Z ^ zaxis;
		if (Normalize(&xaxis))
		{
			CVec3 yaxis = zaxis ^ xaxis;
			pRes->_11 = xaxis.x;
			pRes->_21 = xaxis.y;
			pRes->_31 = xaxis.z;
			pRes->_12 = yaxis.x;
			pRes->_22 = yaxis.y;
			pRes->_32 = yaxis.z;
			pRes->_13 = zaxis.x;
			pRes->_23 = zaxis.y;
			pRes->_33 = zaxis.z;
		}
		else if (zaxis.z < 0.0f)
		{
			// flipped upside down
			pRes->_11 = -1.0f;
			pRes->_33 = -1.0f;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// invert matrix 4x4 in cost of 18 + 16*3 + 4 + 16 = 86 multiplications
inline bool Invert( SHMatrix *pRes, const SHMatrix &m )
{
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
		return false;												// singular matrix found !
	fDet = 1.0f / fDet;
	pRes->_11 *= fDet;	pRes->_21 *= fDet;	pRes->_31 *= fDet;	pRes->_41 *= fDet;
	pRes->_12 *= fDet;	pRes->_22 *= fDet;	pRes->_32 *= fDet;	pRes->_42 *= fDet;
	pRes->_13 *= fDet;	pRes->_23 *= fDet;	pRes->_33 *= fDet;	pRes->_43 *= fDet;
	pRes->_14 *= fDet;	pRes->_24 *= fDet;	pRes->_34 *= fDet;	pRes->_44 *= fDet;

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// determinant
inline float Det( float _11 ) { return _11; }
inline float Det( float _11, float _12, float _21, float _22 ) { return _11*_22 - _12*_21; }

inline float Det( float _11, float _12, float _13,
									float _21, float _22, float _23,
									float _31, float _32, float _33 )
{
	return _11*( _22*_33 - _32*_23 ) -
				 _21*( _12*_33 - _32*_13 ) +
				 _31*( _12*_23 - _22*_13 );
}

inline float Det( float _11, float _12, float _13, float _14,
									float _21, float _22, float _23, float _24,
									float _31, float _32, float _33, float _34,
									float _41, float _42, float _43, float _44 )
{
	const float M3344 = _33*_44 - _43*_34;
	const float M2344 = _23*_44 - _43*_24;
	const float M2334 = _23*_34 - _33*_24;
	const float M1344 = _13*_44 - _43*_14;
	const float M1334 = _13*_34 - _33*_14;
	const float M1324 = _13*_24 - _23*_14;

	return _11 * ( _22*M3344 - _32*M2344 + _42*M2334 ) -
				 _21 * ( _12*M3344 - _32*M1344 + _42*M1334 ) +
				 _31 * ( _12*M2344 - _22*M1344 + _42*M1324 ) -
				 _41 * ( _12*M2334 - _22*M1334 + _32*M1324 );
}
inline float Det( const SHMatrix &m )
{
	return Det( m._11, m._12, m._13, m._14,
							m._21, m._22, m._23, m._24,
							m._31, m._32, m._33, m._34,
							m._41, m._42, m._43, m._44 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** quaternion realization
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float FP_QUAT_EPSILON = 1e-04f;	// cutoff for sin(angle) near zero
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// create quaternion from rotation axis and angle
inline void CQuat::FromAngleAxis( float fAngle, const CVec3 &vAxis, const bool bNormalizeAxis )
{
	//NI_ASSERT( bNormalizeAxis || fabs( fabs( vAxis ) - 1 ) < FP_QUAT_EPSILON, "not normalized quat" );

	fAngle *= 0.5f;
	const float fSinAlpha = bNormalizeAxis ? sin( fAngle ) / fabs( vAxis ) : sin( fAngle );
	x = vAxis.x * fSinAlpha;
	y = vAxis.y * fSinAlpha;
	z = vAxis.z * fSinAlpha;
	w = cos( fAngle );
}
inline void CQuat::FromAngleAxis( float fAngle, float fAxisX, float fAxisY, float fAxisZ, const bool bNormalizeAxis )
{
	//NI_ASSERT( bNormalizeAxis || fabs( fabs( fAxisX, fAxisY, fAxisZ ) - 1 ) < FP_QUAT_EPSILON, "not normalized quat" );
	
	fAngle *= 0.5f;
	const float fSinAlpha = bNormalizeAxis ? sin( fAngle ) / fabs( fAxisX, fAxisY, fAxisZ ) : sin( fAngle );
	x = fAxisX * fSinAlpha;
	y = fAxisY * fSinAlpha;
	z = fAxisZ * fSinAlpha;
	w = cos( fAngle );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// create quaternion from direction vector
inline void CQuat::FromDirection( const CVec3 &vDir, const bool bNormalizeDir )
{
  *this = QNULL;
  CVec3 v = bNormalizeDir ? vDir / fabs( vDir ) : vDir;
  RotateToDirection( v );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// create quaternion from Euler matrix
inline void CQuat::FromEulerMatrix( const SHMatrix &m )
{
	// first compute squared magnitudes of quaternion components - at least one
	// will be greater than 0 since quaternion is unit magnitude
	float qs2 = 0.25f * (m.xx + m.yy + m.zz + 1);
	float qx2 = qs2 - 0.5f * (m.yy + m.zz);
	float qy2 = qs2 - 0.5f * (m.zz + m.xx);
	float qz2 = qs2 - 0.5f * (m.xx + m.yy);
	// find maximum magnitude component
	int n = (qs2 > qx2 ) ?
												((qs2 > qy2) ? ((qs2 > qz2) ? 0 : 3) : ((qy2 > qz2) ? 2 : 3)) :
												((qx2 > qy2) ? ((qx2 > qz2) ? 1 : 3) : ((qy2 > qz2) ? 2 : 3));
	// compute signed quaternion components using numerically stable method
	float tmp;
	switch ( n )
	{
		case 0:
			w = static_cast<float>( sqrt( qs2 ) );
			tmp = 0.25f / w;
			x = ( m.zy - m.yz ) * tmp;
			y = ( m.xz - m.zx ) * tmp;
			z = ( m.yx - m.xy ) * tmp;
			break;
		case 1:
			x = static_cast<float>( sqrt( qx2 ) );
			tmp = 0.25f / x;
			w = ( m.zy - m.yz ) * tmp;
			y = ( m.xy + m.yx ) * tmp;
			z = ( m.xz + m.zx ) * tmp;
			break;
		case 2:
			y = static_cast<float>( sqrt( qy2 ) );
			tmp = 0.25f / y;
			w = ( m.xz - m.zx ) * tmp;
			z = ( m.yz + m.zy ) * tmp;
			x = ( m.yx + m.xy ) * tmp;
			break;
		case 3:
			z = static_cast<float>( sqrt( qz2 ) );
			tmp = 0.25f / z;
			w = ( m.yx - m.xy ) * tmp;
			x = ( m.zx + m.xz ) * tmp;
			y = ( m.zy + m.yz ) * tmp;
			break;
	}
	// for consistency, force positive scalar component [ (s; v) = (-s; -v) ]
	MinimizeRotationAngle();
	// normalize
	::Normalize( x, y, z, w );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	converts 3 euler angles (in radians) to a quaternion
//	Assumes roll is rotation about X, pitch is rotation about Y, yaw is about Z.
//	Assumes order of yaw, pitch, roll applied as follows:
//						p' = roll( pitch( yaw(p) ) )
inline void CQuat::FromEulerAngles( float yaw, float pitch, float roll )
{
	const float fHalfYaw = yaw * 0.5f;
	const float fHalfPitch = pitch * 0.5f;
	const float fHalfRoll = roll * 0.5f;

	const float fCosYaw = cos( fHalfYaw );
	const float fSinYaw = sin( fHalfYaw );
	const float fCosPitch = cos( fHalfPitch );
	const float fSinPitch = sin( fHalfPitch );
	const float fCosRoll = cos( fHalfRoll );
	const float fSinRoll = sin( fHalfRoll );

	x = fSinRoll*fCosPitch*fCosYaw - fCosRoll*fSinPitch*fSinYaw;
	y = fCosRoll*fSinPitch*fCosYaw + fSinRoll*fCosPitch*fSinYaw;
	z = fCosRoll*fCosPitch*fSinYaw - fSinRoll*fSinPitch*fCosYaw;
	w = fCosRoll*fCosPitch*fCosYaw + fSinRoll*fSinPitch*fSinYaw;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline CQuat::CQuat( float yaw, float pitch, float roll )
{
	FromEulerAngles( yaw, pitch, roll );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CQuat::CQuat( float fAngle, float fAxisX, float fAxisY, float fAxisZ, const bool bNormalizeAxis )
{
	FromAngleAxis( fAngle, fAxisX, fAxisY, fAxisZ, bNormalizeAxis );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CQuat::CQuat( float fAngle, const CVec3 &vAxis, const bool bNormalizeAxis )
{
	FromAngleAxis( fAngle, vAxis, bNormalizeAxis );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CQuat::CQuat( const CVec3 &vDir, const bool bNormalizeDir )
{
  FromDirection( vDir, bNormalizeDir );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void CQuat::Deriv( const CQuat &q, const CVec3 &v )
{
	x = 0.5f * (	q.w*v.x - q.z*v.y + q.y*v.z );
	y = 0.5f * (	q.z*v.x + q.w*v.y - q.x*v.z );
	z = 0.5f * ( -q.y*v.x + q.x*v.y + q.w*v.z );
	w = 0.5f * ( -q.x*v.x - q.y*v.y - q.z*v.z );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// rotations
inline const CVec3 CQuat::GetXAxis() const
{
	return CVec3( w*w - (x*x + y*y + z*z) + 2.0f*x*x, (z*w + x*y)*2.0f, (-y*w + x*z)*2.0f );
}
inline const CVec3 CQuat::GetYAxis() const
{
	return CVec3( (-z*w + y*x)*2.0f, w*w - (x*x + y*y + z*z) + 2.0f*y*y, (x*w + y*z)*2.0f );
}
inline const CVec3 CQuat::GetZAxis() const
{
	return CVec3( (y*w + z*x)*2.0f, (-x*w + z*y)*2.0f, w*w - (x*x + y*y + z*z) + 2.0f*z*z );
}
inline void CQuat::GetXAxis( CVec3 *pRes ) const
{
	pRes->x = w*w - (x*x + y*y + z*z) + 2.0f*x*x;
	pRes->y = (z*w + x*y)*2.0f;
	pRes->z = (-y*w + x*z)*2.0f;
}
inline void CQuat::GetYAxis( CVec3 *pRes ) const
{
	pRes->x = (-z*w + y*x)*2.0f;
	pRes->y = w*w - (x*x + y*y + z*z) + 2.0f*y*y;
	pRes->z = (x*w + y*z)*2.0f;
}
inline void CQuat::GetZAxis( CVec3 *pRes ) const
{
	pRes->x = (y*w + z*x)*2.0f;
	pRes->y = (-x*w + z*y)*2.0f;
	pRes->z = w*w - (x*x + y*y + z*z) + 2.0f*z*z;
}
inline const CVec3 CQuat::Rotate( const CVec3 &r ) const
{
	const CVec3 L( x, y, z );
	return ( r*(w*w - L*L) + (2.0f*w)*(L^r) + (2.0f*(L*r))*L );
}
inline void CQuat::Rotate( CVec3 *pRes, const CVec3 &vec ) const
{
	const CVec3 L( x, y, z );
	*pRes = ( vec*(w*w - L*L) + (2.0f*w)*(L^vec) + (2.0f*(L*vec))*L );
}
inline void CQuat::FromToRotation( const CVec3& from, const CVec3& to )
{
  CVec3 relativeAxis = Cross( from , to );
  CQuat relativeQuat;
  relativeQuat.x = relativeAxis.x;
  relativeQuat.y = relativeAxis.y;
  relativeQuat.z = relativeAxis.z;
  relativeQuat.w = from.Length() * to.Length() + from.Dot( to );
  relativeQuat.Normalize();
  (*this) *= relativeQuat;
  Normalize();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const CQuat operator*( const CQuat &a, const CQuat &b )
{
	return CQuat( a.w*b.x + b.w*a.x + (a.y*b.z - a.z*b.y),
								a.w*b.y + b.w*a.y + (a.z*b.x - a.x*b.z),
								a.w*b.z + b.w*a.z + (a.x*b.y - a.y*b.x),
								a.w*b.w - (a.x*b.x + a.y*b.y + a.z*b.z), 0, 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// divide quaternion 'A' on quaternion 'B'
// stage 1: reverse axis for 'B' ( q1 = reversed 'B' )
// stage 2: return 'q1' * 'A'
inline const CQuat operator/( const CQuat &a, const CQuat &b )
{
	CQuat q1;
	q1.UnitInverse( b );
	return q1 * a;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// quaternion's multiplication with assignment (this = a*this)
inline CQuat& CQuat::operator*=( const CQuat &a )
{
	float xtmp = a.w*x + w*a.x + (a.y*z - a.z*y);
	float ytmp = a.w*y + w*a.y + (a.z*x - a.x*z);
	float ztmp = a.w*z + w*a.z + (a.x*y - a.y*x);
	float wtmp = a.w*w - ( a.x*x + a.y*y + a.z*z );
	x = xtmp; y = ytmp; z = ztmp; w = wtmp;

	return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// divide 'this' quaternion on the 'q'
// stage 1: reverse axis for 'q' ( q1 = reversed 'q' )
// stage 2: 'this' = 'q1' * 'this'
inline CQuat& CQuat::operator/=( const CQuat &q )
{
	CQuat q1;
	q1.UnitInverse( q );
	(*this) *= q1;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// inverse quaternion
inline bool CQuat::Inverse( const CQuat &q )
{
	float norm = fabs2( q.x, q.y, q.z, q.w );
	if ( norm > FP_EPSILON2 )
	{
		norm = 1.0f / static_cast<float>( sqrt( norm ) );
		x = -q.x * norm;
		y = -q.y * norm;
		z = -q.z * norm;
		w =	q.w * norm;
		return true;
	}
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// inverse quaternion
inline bool CQuat::Inverse()
{
	float norm = fabs2( x, y, z, w );
	if ( norm > FP_EPSILON2 )
	{
		norm = 1.0f / static_cast<float>( sqrt( norm ) );
		x *= -norm;
		y *= -norm;
		z *= -norm;
		w *=	norm;
		return true;
	}
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// decomposing quaternion to axis and angle
inline void CQuat::DecompAngleAxis( float *pfAngle, CVec3 *pvAxis ) const
{
	// The quaternion representing the rotation is
	//	 q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
	float len = fabs2( x, y, z );
	if ( len > 1e-8f )
	{
		*pfAngle = 2.0f * acos( w );
		len = 1.0f / float( sqrt(len) );
		pvAxis->x = x * len;
		pvAxis->y = y * len;
		pvAxis->z = z * len;
	}
	else
	{
		// angle is 0 (mod 2*pi), so any axis will do
		*pfAngle = 0.0f;
		pvAxis->x = 1.0f;
		pvAxis->y = 0.0f;
		pvAxis->z = 0.0f;
	}
}
inline void CQuat::DecompAngleAxis( float *pfAngle, float *pfAxisX, float *pfAxisY, float *pfAxisZ ) const
{
	// The quaternion representing the rotation is
	//	 q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
	float len = x*x + y*y + z*z;
	if ( len > 1e-8f )
	{
		*pfAngle = 2.0f * acos( w );
		len = 1.0f / float( sqrt(len) );
		*pfAxisX = x * len;
		*pfAxisY = y * len;
		*pfAxisZ = z * len;
	}
	else
	{
		// angle is 0 (mod 2*pi), so any axis will do
		*pfAngle = 0.0f;
		*pfAxisX = 1.0f;
		*pfAxisY = 0.0f;
		*pfAxisZ = 0.0f;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// decompose quaternion to Euler matrix
inline void CQuat::DecompEulerMatrix( SHMatrix *pRes ) const
{
	const float tx	= x + x;
	const float ty	= y + y;
	const float tz	= z + z;
	const float twx = tx*w;
	const float twy = ty*w;
	const float twz = tz*w;
	const float txx = tx*x;
	const float txy = ty*x;
	const float txz = tz*x;
	const float tyy = ty*y;
	const float tyz = tz*y;
	const float tzz = tz*z;

	pRes->_11 = 1.0f - (tyy + tzz);
	pRes->_12 = txy - twz;
	pRes->_13 = txz + twy;

	pRes->_21 = txy + twz;
	pRes->_22 = 1.0f - (txx + tzz);
	pRes->_23 = tyz - twx;

	pRes->_31 = txz - twy;
	pRes->_32 = tyz + twx;
	pRes->_33 = 1.0f - (txx + tyy);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// decompose quaternion to reversed Euler matrix (reverse transform)
inline void CQuat::DecompReversedEulerMatrix( SHMatrix *pRes ) const
{
	const float tx	= -( x + x );
	const float ty	= -( y + y );
	const float tz	= -( z + z );
	const float twx =	tx*w;
	const float twy =	ty*w;
	const float twz =	tz*w;
	const float txx = -tx*x;
	const float txy = -ty*x;
	const float txz = -tz*x;
	const float tyy = -ty*y;
	const float tyz = -tz*y;
	const float tzz = -tz*z;

	pRes->_11 = 1.0f - (tyy + tzz);
	pRes->_12 = txy - twz;
	pRes->_13 = txz + twy;

	pRes->_21 = txy + twz;
	pRes->_22 = 1.0f - (txx + tzz);
	pRes->_23 = tyz - twx;

	pRes->_31 = txz - twy;
	pRes->_32 = tyz + twx;
	pRes->_33 = 1.0f - (txx + tyy);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calculate exponent of the quaternion
inline const CQuat CQuat::Exp() const
{
	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).	If sin(A) is near zero,
	// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.
	const double angle = fabs( x, y, z );
	const double sn = sin( angle );
	CQuat result;

	result.w = float( cos(angle) );

	if ( fabs(sn) >= FP_QUAT_EPSILON )
	{
		const float coeff = float( sn / angle );
		result.x = coeff * x;
		result.y = coeff * y;
		result.z = coeff * z;
	}
	else
	{
		result.x = x;
		result.y = y;
		result.z = z;
	}

	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calculates natural logarithm of the quaternion
inline const CQuat CQuat::Log() const
{
	// If q = cos(A) + sin(A)*(x*i + y*j + z*k) where (x,y,z) is unit length, then
	// log(q) = A*(x*i + y*j + z*k).	If sin(A) is near zero, use log(q) =
	// sin(A)*(x*i + y*j + z*k) since sin(A)/A has limit 1.
	if ( fabs(w) < 1.0f )
	{
		const double angle = acos( w );
		const double sn = sin( angle );
		if ( fabs(sn) >= FP_QUAT_EPSILON )
		{
			const float coeff = float( angle / sn );
			return CQuat( coeff*x, coeff*y, coeff*z, 0, 0, 0 );
		}
	}

	return CQuat( x, y, z, 0, 0, 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Spherical Linear intERPolation between two quaternions (SLERP) (from 'p' to 'q' with coeff 'factor')
inline void CQuat::Slerp( float factor, const CQuat &p1, const CQuat &q1 )
{
  if ( factor < 0.0f )
  {
    factor = 0.0f; 
  }
  else if ( factor > 1.0f )
  {
    factor = 1.0f;
  }

	float scale0, scale1;
	//CQuat q1( q );
	// use the dot product to get the cosine of the angle between the quaternions
	const float rawcosom = p1.Dot(q1);
	// calculate coefficients
	if ( (1.0 - fabs(rawcosom)) > 0.1f )
	{
		const float omega = acos( rawcosom );
		const float sinom = 1.f/sin( omega ) ;
		scale0 = sin((1.f - factor) * omega) * sinom ;
		scale1 = sin(factor * omega) * sinom ;
	}
	else																	// "p" and "q" quaternions are very close. so we can do a linear interpolation
	{
		scale0 = 1.0f - factor;
		scale1 = factor;
	}

	scale1 = rawcosom >=0.f ? scale1 : -scale1;
	// calculate final values
	x = scale0*p1.x + scale1*q1.x;
	y = scale0*p1.y + scale1*q1.y;
	z = scale0*p1.z + scale1*q1.z;
	w = scale0*p1.w + scale1*q1.w;

  Normalize();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shortest arc between two vectors.
inline CQuat ShortestArc(const CVec3& from, const CVec3& to )
{
	CVec3 c = from ^ to;
	CQuat result;
	result.FromComponents( c.x, c.y, c.z, from * to );
	result.Normalize();
	result.w += 1.0f;      // reducing angle to halfangle
	if( result.w <= 0.00001 ) // angle close to PI
	{
		if( ( from.z * from.z ) > ( from.x * from.x ) )
		{
			result.FromComponents( 0, from.z, - from.y, result.w ); //from*vector3(1,0,0)
		}
		else
		{
			result.FromComponents( from.y, - from.x, 0, result.w ); //from*vector3(0,0,1) 
		}
	}
	result.Normalize();
	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** 2D line, circle and some useful functions realization
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline int QuadraticEquation( double c2, double halfC1, double c0, double& x1, double& x2 )
{
  if ( c2 == 0.0 )
  {
    if ( halfC1 == 0.0 )
    {
      return 0;
    }
    x1 = - c0 / ( 2 * halfC1 );
    return 1;
  }

  const double halfD = halfC1*halfC1 - c2*c0;

  if ( halfD < 0.0 )
  {
    return 0;
  }

  if ( halfD == 0.0 )
  {
    x1 = - halfC1 / c2;
    return 1;
  }

  double k = -halfC1 - sqrt( halfD );
  if ( halfC1 < 0.0f )
  {
    k = -halfC1 + sqrt( halfD );
  }

  x1 = k / c2;
  x2 = c0 / k;

  return 2;
}

inline int GetLineCircleIntersection( const CLine2& _line, const CCircle& _circle, CVec2& p1, CVec2& p2 )
{
  NI_VERIFY( ( ( _line.a != 0.0f ) || ( _line.b != 0.0f ) ), NStr::StrFmt( "Incorrect line parameters ( line equation: \"%.2f = 0\" )!", _line.c ), return 0 );
  NI_VERIFY( _circle.r > 0.0f, NStr::StrFmt( "Incorrect circle parameters ( r = %.2f )!", _circle.r ), return 0 );

  const CVec2 delta = _circle.center;
  const CVec2 zero( 0.0f, 0.0f );
  const float r = _circle.r;

  CLine2 line = _line;
  line.c += line.a * delta.x + line.b * delta.y;

  // Now we intersect circle with center in (0,0) with correct parallel line

  CLine2 lineNormalized = line;
  const float dist = fabs( lineNormalized.DistToPoint( zero ) );
  if ( dist > r )
  {
    return 0;
  }
  if ( fabs( dist - r ) <= EPS_VALUE  )
  {
    lineNormalized.ProjectPoint( zero, &p1 );
    p1 += delta;
    return 1;
  }

  bool forY = true;
  if ( fabs( line.a ) > fabs( line.b ) )
  {
    forY = false;
  }

  if ( forY )
  {
    line.a /= line.b;
    line.c /= line.b;
    line.b = 1.0f;
  }
  else
  {
    line.b /= line.a;
    line.c /= line.a;
    line.a = 1.0f;
  }

  if ( line.b == 0 )
  {
    const float x = -line.c / line.a;
    p1.x = p2.x = x;

    const float k = sqrt( fabs2( r ) - fabs2( x ) );
    p1.y = k;
    p2.y = -k;
  }
  else
  {
    if ( forY )
    {
      const double a = -line.a;
      const double b = -line.c;

      // y = a*x + b
      // x^2 + ( a*x + b )^2 = r^2

      const double c2     = a*a + 1.0f;
      const double halfC1 = a*b;
      const double c0     = fabs2( b ) + - fabs2( r );
      // c2*x^2 + 2*halfC1*x + c0 = 0

      double x1, x2;
      const int rootCount = QuadraticEquation( c2, halfC1, c0, x1, x2 );

      NI_VERIFY( rootCount == 2,
        NStr::StrFmt( "Line-circle intersection calculation failed: quadratic equation ( %.2f*x^2 + %.2f*x + %.2f = 0 ) should have 2 roots!",
          c2, 2*halfC1, c0 ), return 0 );

      p1.x = static_cast<float>( x1 );
      p2.x = static_cast<float>( x2 );

      p1.y = a*p1.x + b;
      p2.y = a*p2.x + b;
    }
    else
    {
      const double a = -line.b;
      const double b = -line.c;

      // x = a*y + b
      // y^2 + ( a*y + b )^2 = r^2

      const double c2     = a*a + 1.0f;
      const double halfC1 = a*b;
      const double c0     = fabs2( b ) - fabs2( r );
      // c2*y^2 + 2*halfC1*y + c0 = 0

      double y1, y2;
      const int rootCount = QuadraticEquation( c2, halfC1, c0, y1, y2 );

      NI_VERIFY( rootCount == 2,
        NStr::StrFmt( "Line-circle intersection calculation failed: quadratic equation ( %.2f*y^2 + %.2f*y + %.2f = 0 ) should have 2 roots!",
          c2, 2*halfC1, c0 ), return 0 );

      p1.y = static_cast<float>( y1 );
      p2.y = static_cast<float>( y2 );

      p1.x = a*p1.y + b;
      p2.x = a*p2.y + b;
    }
  }

  p1 += delta;
  p2 += delta;
  return 2;
}

inline void GetCirclesByTangent( const CVec2 &tang, const CVec2 &p, const float r, CCircle *c1, CCircle *c2 )
{
	const CVec2 v( -tang.y, tang.x );

	c1->r = r;
	c1->center = p + v * r;

	c2->r = r;
	c2->center = p - v * r;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool FindTangentPoints( const CVec2 &p, const CCircle &c, CVec2 *p1, CVec2 *p2 )
{
	const CVec2 v = c.center - p;
	const float hyp2 = fabs2( v );
	const float r2 = fabs2( c.r );

	if ( hyp2 < r2 )
		return false;

	if ( hyp2 == r2 )
	{
		*p1 = p;
		*p2 = p;
	}
	else
	{
		const float leg2 = hyp2 - r2;
		const float cossin = float( sqrt( leg2 ) ) * c.r / hyp2;
		const float cos2 = leg2 / hyp2;

		p1->x = v.x * cos2 - v.y * cossin + p.x;
		p1->y = v.x * cossin + v.y * cos2 + p.y;

		p2->x = p1->x + 2 * v.y * cossin;
		p2->y = p1->y - 2 * v.x * cossin;
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*															CLine2															*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void CLine2::ProjectPoint( const CVec2 &point, CVec2 *result )
{
	float fK;
	if ( bNormalized )
		fK = a * point.x + b * point.y + c;
	else
		fK = ( a * point.x + b * point.y + c ) / fabs2( a, b );

	result->x = point.x - fK * a;
	result->y = point.y - fK * b;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CLine2::DistToPoint( const CVec2 &point )
{
	Normalize();
	return ( a * point.x + b * point.y + c );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool IsParallel( const CLine2& l1, const CLine2& l2 )
{
	const float eps = 0.00001f;
  const float temp = (l1.a * l2.b - l2.a * l1.b);
	return fabs( temp ) <= eps;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool IntersectLines( CVec2* pResult, const CLine2& l1, const CLine2& l2 )
{
	if ( IsParallel( l1, l2 ) )
		return false;

	CVec2& p = *pResult;

	p.x = ( l2.b * l1.c - l1.b * l2.c ) / ( l2.a * l1.b - l1.a * l2.b );
	p.y = ( l1.b != 0 ? ( - l1.c - l1.a * p.x ) / l1.b : ( - l2.c - l2.a * p.x ) / l2.b );

	if ( l1.b != 0 )
	{
		p.y = -( l1.c + l1.a * p.x ) / l1.b;
	}
	else
	{
		p.y = -( l2.c + l2.a * p.x ) / l2.b;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float TriangleArea2( const CVec2 &p1, const CVec2 &p2, const CVec2 &p3 )
{
	return p1.x * ( p2.y - p3.y ) + p2.x * ( p3.y - p1.y ) + p3.x * ( p1.y - p2.y );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float IsPointInsideTriangle( const CVec2 &p1, const CVec2 &p2, const CVec2 &p3, const CVec2 &p )
{
	const int nSign1 = Sign( (int)TriangleArea2( p, p1, p2 ) );
	const int nSign2 = Sign( (int)TriangleArea2( p, p2, p3 ) );
	const int nSign3 = Sign( (int)TriangleArea2( p, p3, p1 ) );
	const int nSign	 = Sign( (int)TriangleArea2( p1, p2, p3 ) );

	if ( nSign != 0 )
		return nSign * nSign1 >= 0 && nSign * nSign2 >= 0 && nSign * nSign3 >= 0;
	// singular triangle
	else
	{
		if ( nSign1 == 0 && nSign2 == 0 && nSign3 == 0 )
		{
			return CSegment( p1, p2 ).GetDistToPoint( p ) < 1e-6 || 
						 CSegment( p1, p3 ).GetDistToPoint( p ) < 1e-6;
		}
		else
			return false;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*														CSegment															*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const float CSegment::GetDistToPoint( const CVec2 &point ) const
{
	if ( ( point - p1 ) * dir <= 0 )
		return fabs( point - p1 );
	else if ( ( point - p2 ) * dir >= 0 )
		return fabs( point - p2 );
	else
		return fabs( TriangleArea2( p1, p2, point ) ) / fabs( p2 - p1 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void CSegment::GetClosestPoint( const CVec2 &point, CVec2 *result ) const
{
	if ( ( point - p1 ) * dir <= 0 )
		*result = p1;
	else if ( ( point - p2 ) * dir >= 0 )
		*result = p2;
	else
		CLine2( p1, p2 ).ProjectPoint( point, result );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void MakeMatrix( SHMatrix *pMatrix, const CVec3 &pos, const CQuat &rot )
{
	pMatrix->Set( pos, rot );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void MakeMatrix( SHMatrix *pMatrix, const CVec3 &pos, const CQuat &rot, const CVec3 &scale )
{
	rot.DecompEulerMatrix( pMatrix );
	pMatrix->_11 *= scale.x;
	pMatrix->_21 *= scale.x;
	pMatrix->_31 *= scale.x;
	pMatrix->_12 *= scale.y;
	pMatrix->_22 *= scale.y;
	pMatrix->_32 *= scale.y;
	pMatrix->_13 *= scale.z;
	pMatrix->_23 *= scale.z;
	pMatrix->_33 *= scale.z;
	pMatrix->_14 = pos.x;
	pMatrix->_24 = pos.y;
	pMatrix->_34 = pos.z;
	pMatrix->_41 = pMatrix->_42 = pMatrix->_43 = 0.0f;
	pMatrix->_44 = 1.0f;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const unsigned short GetDirectionByVector( const CVec2 &vec );
const unsigned short GetDirectionByVector( float x, float y );
const CVec2 GetVectorByDirection( const unsigned short dir );
const unsigned short GetZDirectionBy3DVector( const float x, const float y, const float z );
const unsigned short GetZDirectionBy3DVector( const CVec2 &vec, const float z );
// угол между между вектором и OXY
const unsigned short GetZAngle( const float x, const float y, float z );
// угол между между вектором и OXY
const unsigned short GetZAngle( const CVec2 &vec, const float z );
const unsigned short GetZAngle( const CVec3 &vPoint );
const unsigned short DirsDifference( const unsigned short dir1, const unsigned short dir2 );
const int DifferenceSign( const unsigned short dir1, const unsigned short dir2 );
// в угле от startAngleDir до finishAngleDir против часовой
bool IsInTheAngle( const unsigned short dir, const unsigned short startAngleDir, const unsigned short finishAngleDir );
// dir в минимальном угле мжду dir1 и dir2
bool IsInTheMinAngle( const unsigned short dir, const unsigned short dir1, const unsigned short dir2 );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsAlmostZero( const CVec2 &vec )
{
	const static float eps = 0.0001f;
	return ( fabs( vec.x ) < eps	&& fabs( vec.y ) < eps );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsAlmostZero( const CVec3 &vec )
{
	const static float eps = 0.0001f;
	return ( fabs( vec.x ) < eps && fabs( vec.y ) < eps && fabs( vec.z ) < eps );
}
inline bool IsAlmostZero( const float x, const float y )
{
	const static float eps = 0.0001f;
	return ( fabs( x ) < eps	&& fabs( y ) < eps );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*															SRect																*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum ESide
{
	SIDE_FRONT		= 0,
	SIDE_LEFT			= 1,
	SIDE_BACK			= 2,
	SIDE_RIGHT		= 3,
	SIDE_TOP			= 4,
	SIDE_BOTTOM		= 5,
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRect
{
	CVec2 v1, v2, v3, v4;
	CVec2 dir, dirPerp, center;
	float lengthAhead, lengthBack, width;

	bool IsIntersectProject( const CVec2 &v1, const CVec2 &v2, const CVec2 &v3, const CVec2 &v4, const CVec2 &dir, const float min, const float max ) const;

	//public:
	void InitRect( const CVec2 &_v1, const CVec2 &_v2, const CVec2 &_v3, const CVec2 &_v4 );
	// задаётся половина реальной длины и ширины (как бы радиусы)
	void InitRect( const CVec2 &center, const CVec2 &dir, const float length, const float width );
	// задаются длины вперёд и назад, половина ширины
	void InitRect( const CVec2 &center, const CVec2 &dir, const float lengthAhead, const float lengthBack, const float width );

	bool IsIntersected( const SRect &rect ) const;
	bool IsIntersected( const CSegment &segment ) const;

	// границы прямоугольника не принадлежат ему
	bool IsPointInside( const CVec2 &point ) const;
	bool IsIntersectCircle( const CVec2 &circleCenter, const float r ) const;
	bool IsIntersectCircle( const CCircle &circle ) const { return IsIntersectCircle( circle.center, circle.r ); }
	bool IsIntersectTriangle( const CVec2 &v1, const CVec2 &v2, const CVec2 &v3 ) const;

	const int GetSide( const unsigned short dirFromRectCenter ) const;
	const int GetSide( const CVec2 &point ) const;

	void Compress( const float fFactor );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float fabs( const SRect rect1, const SRect rect2 );
// угол, под которым rect виден из точки point
const unsigned short GetVisibleAngle( const CVec2 &point, const SRect rect );
// точка пересечения луча из точки vPoint по направлению vDir (можно не нормировать) с прямоугольником rect
// возвращает false, если не пересекается
const bool GetRectBeamIntersection( CVec2 *pvResult, const CVec2 &vPoint, const CVec2 &vDir, const SRect &rect );
// вернуть нормализованное значение вектора
inline const CVec2 Norm( const CVec2 &v )
{
	return ( v == VNULL2 ) ? VNULL2 : v/fabs(v);
}
// получить углы, необходимые для поворота этой нормали относительно осей X (phi) и Y (theta) 
// для совпадения её с осью Z
inline void GetAngles( const CVec3 &vNormal, float *pfPhi, float *pfTheta )
{
	// phi - поворот в плоскости ZY относительно оси X
	// cos( phi ) = Z*N(x=0) = (0, 0, 1) * (0, Ny, Nz) / sqrt( Ny**2 + Nz**2 );
	{
		const float fLen2 = fabs2( vNormal.y, vNormal.z );
		*pfPhi = fLen2 < 1e-8f ? 0 : vNormal.z / sqrt( fLen2 );
		*pfPhi = -Sign( vNormal.y ) * acos( Clamp(*pfPhi, -1.0f, 1.0f) );
	}
	// theta - поворот в плоскости ZX относительно оси Y
	// cos( theta ) = Z*N(y=0) = Nz / fabs( Nx, Nz )
	{
		const float fLen2 = fabs2( vNormal.x, vNormal.z );
		*pfTheta = fLen2 < 1e-8f ? 0 : vNormal.z / sqrt( fLen2 );
		*pfTheta = Sign( vNormal.x ) * acos( Clamp(*pfTheta, -1.0f, 1.0f) );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void MakeOrientation( CQuat *pQuat, const CVec3 &vNormal )
{
	float fPhi, fTheta;										// theta and phi angles
	GetAngles( vNormal, &fPhi, &fTheta );

	CQuat q1( fPhi, V3_AXIS_X );
	CQuat q2( fTheta, V3_AXIS_Y );
	q1.MinimizeRotationAngle();
	q2.MinimizeRotationAngle();
	(*pQuat) *=	q1 * q2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline int mDistance( const SVector &vec1, const SVector &vec2 )
{
	return Max( abs( vec1.x-vec2.x ), abs( vec1.y-vec2.y ) );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// "Forward" axis
inline CVec3 GetEulerXAxis( float fYaw, float fPitch, float fRoll )
{
	CVec3 ptRes;
	CQuat q;
	q.FromEulerAngles( fYaw, fPitch, fRoll );
	q.GetXAxis( &ptRes );
	return ptRes;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// "Side" or "Strafe" axis
inline CVec3 GetEulerYAxis( float fYaw, float fPitch, float fRoll )
{
	CVec3 ptRes;
	CQuat q;
	q.FromEulerAngles( fYaw, fPitch, fRoll );
	q.GetYAxis( &ptRes );
	return ptRes;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// "Up" axis
inline CVec3 GetEulerZAxis( float fYaw, float fPitch, float fRoll )
{
	CVec3 ptRes;
	CQuat q;
	q.FromEulerAngles( fYaw, fPitch, fRoll );
	q.GetZAxis( &ptRes );
	return ptRes;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 GetOffsetPointAlongPath( vector<CVec2> const& path, int nearestPoint, float offset );
CVec2 GetNearestPathPoint( vector<CVec2> const& path, CVec2 const& pos, int& nearestPathPoint, float& distFormPathPoint );
CVec2 GetNearestPathPoint( vector<CVec2> const& path, CVec2 const& pos );
CVec2 GetNearestPathPoint( vector<CVec2> const& path, CVec2 const& pos, int& nearestPathPoint);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace nstl
{
template<> struct hash<SVector>
{
	int operator()( const SVector &v ) const { return v.x << 16 | v.y; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<> struct hash<CVec2>
{
	int operator()( const CVec2 &v ) const { return ( ( (int)v.x )<<16 ) | ( (int)v.y ); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#ifdef WIN32
  #pragma warning( pop )
#endif  


#pragma pack( pop )


//Здеся были какие-то операторы вывода векторов в NLogg::StreamBuffer. Но PW собирается и без них.
//Если что, эти самые операторы вынесены в отдельный ашник GeomStreamers.h

#endif //_GEOM_H_
