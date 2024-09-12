#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "System/config.h"
#include <math.h>
#include "System/ported/types.h"
#include "System/nvector.h"

#ifdef X64BUILD
#ifdef WIN32
#undef WIN32
#define WIN32UNDEFED
#endif
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// square root of the 2 and 3
#define SQRT_2      1.41421356237309504880
#define SQRT_3      1.73205080756887729353
#define FP_SQRT_2   1.41421356f
#define FP_SQRT_3   1.73205081f
// different constants with 'pi'
#define PI                  3.14159265358979323846
#define FP_PI               3.14159265f
#define FP_2PI          6.28318531f
#define FP_4PI          12.56637061f
#define FP_8PI          25.13274123f
#define FP_PI2          1.57079633f
#define FP_PI4          0.78539816f
#define FP_PI8          0.39269908f
#define FP_3PI2         4.71238898f
#define FP_INV_PI       0.31830989f
#define FP_EPSILON  1e-12f
#define FP_EPSILON2 1e-24f

#define FP_MAX_VALUE 3.402823466e+38f
#define FP_MIN_VALUE 1.175494351e-38f

#define EPS_VALUE 1.192092896e-7f
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** some FP tricks
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// access float as DWORD
#define FP_BITS( fp ) ( *(unsigned long*)(&(fp)) )
#define FP_BITS_CONST( fp ) ( *(const unsigned long*)(&(fp)) )
// floating pt 1.0
#define FP_ONE_BITS 0x3F800000
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** pack/unpack
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// побитовое приведение типа
template <class TYPE_OUT, class TYPE_IN>
inline TYPE_OUT bit_cast( const TYPE_IN &val )
{
    return *reinterpret_cast<const TYPE_OUT*>( &val );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// трюки с битами
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Return the next power of 2 higher than the input
// If the input is already a power of 2, the output will be the same as the input.
// Got this from Brian Sharp's sweng mailing list.
inline unsigned long int GetNextPow2(unsigned long int n)
{
    n -= 1;

    n |= n >> 16;
    n |= n >> 8;
    n |= n >> 4;
    n |= n >> 2;
    n |= n >> 1;

    return n + 1;
}

inline unsigned long int GetNextPow2( int n ) { return GetNextPow2( (unsigned long int)(n) ); }

// получить старший включенный бит
inline int GetMSB( unsigned long n )
{
    int k = 0;
    if ( n & 0xFFFF0000 ) k = 16, n >>= 16;
    if ( n & 0x0000FF00 ) k += 8, n >>= 8;
    if ( n & 0x000000F0 ) k += 4, n >>= 4;
    if ( n & 0x0000000C ) k += 2, n >>= 2;
    if ( n & 0x00000002 ) k += 1;
    return k;
}
inline int GetMSB( long n ) { return GetMSB( (unsigned long)(n) ); }
inline int GetMSB( unsigned short n )
{
    int k = 0;
    if ( n & 0xFF00 ) k = 8, n >>= 8;
    if ( n & 0x00F0 ) k += 4, n >>= 4;
    if ( n & 0x000C ) k += 2, n >>= 2;
    if ( n & 0x0002 ) k += 1;
    return k;
}
inline int GetMSB( short n ) { return GetMSB( (unsigned short)(n) ); }
inline int GetMSB( unsigned char n )
{
    int k = 0;
    if ( n & 0xF0 ) k   = 4, n >>= 4;
    if ( n & 0x0C ) k += 2, n >>= 2;
    if ( n & 0x02 ) k += 1;
    return k;
}
inline int GetMSB( char n ) { return GetMSB( (unsigned char)(n) ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// получить младший включенный бит
inline int GetLSB( unsigned long n )
{
    int k = 0;
    if ( (n & 0x0000FFFF) == 0 ) k = 16, n >>= 16;
    if ( (n & 0x000000FF) == 0 ) k += 8, n >>= 8;
    if ( (n & 0x0000000F) == 0 ) k += 4, n >>= 4;
    if ( (n & 0x00000003) == 0 ) k += 2, n >>= 2;
    if ( (n & 0x00000001) == 0 ) k += 1;
    return k;
}
inline int GetLSB( int n ) { return GetLSB( (unsigned long)(n) ); }
inline int GetLSB( unsigned short n )
{
    int k = 0;
    if ( (n & 0x00FF) == 0 ) k  = 8, n >>= 8;
    if ( (n & 0x000F) == 0 ) k += 4, n >>= 4;
    if ( (n & 0x0003) == 0 ) k += 2, n >>= 2;
    if ( (n & 0x0001) == 0 ) k += 1;
    return k;
}
inline int GetLSB( short n ) { return GetLSB( (unsigned short)(n) ); }
inline int GetLSB( unsigned char n )
{
    int k = 0;
    if ( (n & 0x0F) == 0 ) k    = 4, n >>= 4;
    if ( (n & 0x03) == 0 ) k += 2, n >>= 2;
    if ( (n & 0x01) == 0 ) k += 1;
    return k;
}
inline int GetLSB( char n ) { return GetLSB( (unsigned char)(n) ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// подсчёт колличества ненулевых бит в числе
// 0x49249249ul // = 0100_1001_0010_0100_1001_0010_0100_1001
// 0x381c0e07ul // = 0011_1000_0001_1100_0000_1110_0000_0111
inline int GetNumBits( unsigned long v )
{
    v = (v & 0x49249249ul) + ((v >> 1) & 0x49249249ul) + ((v >> 2) & 0x49249249ul);
    v = ((v + (v >> 3)) & 0x381c0e07ul) + ((v >> 6) & 0x381c0e07ul);
    return int( (v + (v >> 9) + (v >> 18) + (v >> 27)) & 0x3f );
}
inline int GetNumBits( int v ) { return GetNumBits( (unsigned long)(v) ); }
inline int GetNumBits( unsigned char v )
{
    v = (v & 0x55) + ((v >> 1) & 0x55);
    v = (v & 0x33) + ((v >> 2) & 0x33);
    return int( (v & 0x0f) + ((v >> 4) & 0x0f) );
}
inline int GetNumBits( char v ) { return GetNumBits( (unsigned char)(v) ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// работа со знаком числа
// ************************************************************************************************************************ //
// signum function
template <class TYPE>
inline TYPE Sign( const TYPE x )
{
    if ( x < 0 )
        return -1;
    else if ( x > 0 )
        return +1;
    else
        return 0;
}

#ifdef WIN32

// calculates sign for integer variable, returns -1, 0, 1. template specialization
//#pragma warning( disable: 4035 ) // compiler can and does produce wrong code in this case with optimisations turned on
template <>
inline int Sign<int>( const int nVal )
{
    int nRes;
    _asm
    {
        xor ecx, ecx
        mov eax, nVal
        test eax, 0x7FFFFFFF
        setne cl
        sar eax, 31
        or eax, ecx
        mov nRes, eax
    }
    return nRes;
}
template <>
inline short int Sign<short int>( const short int nVal )
{
    short int nRes;
    _asm
    {
        xor ecx,ecx
        mov ax, nVal
        test ax, 0x7FFF
        setne cl
        sar ax, 15
        or ax, cx
        mov nRes, ax
    }
    return nRes;
}

#else


#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// radian <=> degree conversion functions
// ************************************************************************************************************************ //
inline float ToRadian( const float angle )
{
    return float( angle * (FP_PI/180.0f) );
}
inline float ToDegree( const float angle )
{
    return float( angle * (180.0f/FP_PI) );
}
inline float NormalizeAngleInDegree( const float angle )
{
    float fResult = fmod( double(angle), 360.0 );
    if ( fResult < 0 )
        fResult += 360.f;
    return fResult;
}
inline int NormalizeAngleInDegree( const int angle )
{
    return angle % 360;
}
inline float SignumNormalizeAngleInDegree( const float angle )
{
    return float( fmod( angle + 180*Sign(angle),    360 ) - 180 * Sign( angle ) );
}
inline float NormalizeAngleInRadian( const float angle )
{
    return float( fmod( double(angle), 2.0*PI ) + ( double(angle) < 0 ? 2.0*PI : 0 ) );
}
inline float SignumNormalizeAngleInRadian( const float angle )
{
    return float( fmod( double(angle) + PI, 2.0*PI ) + (double(angle) < -PI ? PI : -PI ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// обнуление памяти по типу переменной
// ************************************************************************************************************************ //
template <class TYPE>
inline void Zero( TYPE &val )
{
    memset( &val, 0, sizeof(val) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// обнуление участка памяти, состоящего из DWORD'ов
// ************************************************************************************************************************ //
inline void MemSetDWord( unsigned long* lpData, const unsigned long value, const int nCount )
{
  #ifdef WIN32
    _asm
    {
        mov ecx, nCount
        mov edi, lpData
        mov eax, value
        rep stosd
    }
    #else
      unsigned long *dest = lpData;
      for (int i = nCount; i > 0; i--)
      {
        *dest = value; dest++;
      }
      
    #endif
}



// ************************************************************************************************************************ //
// ** float-to-int преобразование с текущим состоянием процессора
// ************************************************************************************************************************ //
// very fast float-to-int conversion. WARNING: uses current FPU rounding state (!)
__forceinline int Float2Int( const float fVal )
{
    int nRet;
    #ifdef WIN32
      __asm fld dword ptr fVal
      __asm fistp nRet
  #else
    nRet = (int)(ceilf(fVal));
  #endif      
    return nRet;
}


__forceinline void Float2Int( int *pInt, float fVal ) 
{
  #ifdef WIN32
      __asm fld fVal
      __asm mov edx, pInt
      __asm fistp dword ptr [edx];
  #else
    *(pInt) = (int)(ceilf(fVal));
  #endif      
}



__forceinline int Round (const float fVal)
{
  if (fVal >= 0.0f)
    return ((int)(fVal + 0.5f));
  else
    return ((int)(fVal - 0.5f));
};



// min/max functions
template <class TYPE>
inline const TYPE& Min( const TYPE& val1, const TYPE& val2 )
{
    return (val1 < val2 ? val1 : val2);
}


template <class TYPE>
inline const TYPE& Max( const TYPE& val1, const TYPE& val2 )
{
    return (val1 > val2 ? val1 : val2);
}



// clamp - обрезать число с двух сторон (min/max)
template <class TYPE>
inline const TYPE Clamp( const TYPE tVal, const TYPE tMin, const TYPE tMax )
{
    return Max( tMin, Min(tVal, tMax) );
}
inline const float ClampFast( const float fVal, const float fMin, const float fMax )
{
    union { float f; int hex; };
    f = fVal - fMin;
    hex &= ~hex>>31;
    f += fMin - fMax;
    hex &= hex>>31;
    f += fMax;

    return f;
}
inline const int ClampFast( const int nVal, const int nMin, const int nMax )
{
    int hex = nVal - nMin;
    hex &= ~hex>>31;
    hex += nMin - nMax;
    hex &= hex>>31;
    hex += nMax;

    return hex;
}


template <class T>
inline T Lerp( T x0, T x1, T t )
{
  return x0 * ( T(1.0) - t ) + x1 * t;
}



// получение модуля от разных величин

inline float fabs2( const float x, const float y, const float z, const float w )
{
    return ( x*x + y*y + z*z + w*w );
}
inline float fabs( const float x, const float y, const float z, const float w )
{
    return static_cast<float>( sqrt( fabs2(x, y, z, w) ) );
}
inline float fabs2( const float x, const float y, const float z )
{
    return ( x*x + y*y + z*z );
}
inline float fabs( const float x, const float y, const float z )
{
    return static_cast<float>( sqrt( fabs2(x, y, z) ) );
}
inline float fabs2( const float x, const float y )
{
    return ( x*x + y*y );
}
inline float fabs( const float x, const float y )
{
    return static_cast<float>( sqrt( fabs2(x, y) ) );
}
inline float fabs2( const float x )
{
    return x*x;
}
inline float sqr( const float x ) { return x * x; }



template <class TYPE> 
inline bool Normalize( TYPE &x, TYPE &y )
{
    TYPE u = fabs2( x, y );
    if ( fabs(u - TYPE(1)) < FP_EPSILON )
        return true;                                                // already normalized
    if ( u < FP_EPSILON2 )
        return false;                                            // can't normalize
    u = static_cast<TYPE>( TYPE(1) / sqrt( u ) );
    x *= u;
    y *= u;
    return true;
}
template <class TYPE> 
inline bool Normalize( TYPE &x, TYPE &y, TYPE &z )
{
    TYPE u = fabs2( x, y, z );
    if ( fabs(u - TYPE(1)) < FP_EPSILON )
        return true;                                                // already normalized
    if ( u < FP_EPSILON2 )
        return false;                                            // can't normalize
    u = static_cast<TYPE>( TYPE(1) / sqrt( u ) );
    x *= u;
    y *= u;
    z *= u;
    return true;
}
template <class TYPE> 
inline bool Normalize( TYPE &x, TYPE &y, TYPE &z, TYPE &w )
{
    TYPE u = fabs2( x, y, z, w );
    if ( fabs(u - TYPE(1)) < FP_EPSILON )
        return true;                                                // already normalized
    if ( u < FP_EPSILON2 )
        return false;                                            // can't normalize
    u = static_cast<TYPE>( TYPE(1) / sqrt( u ) );   
    x *= u;
    y *= u;
    z *= u;
    w *= u;
    return true;
}

template <typename T>
inline T Ceil2PowerOf2(T v)
{
  --v;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  return ++v;
}

template<class TYPE>
inline TYPE Align(const TYPE ptr, int alignment)
{
    return (TYPE) (((unsigned)ptr + alignment - 1) & ~(alignment - 1));
}

namespace ni_math {

template<class T>
inline int QuadraticEquation( T & x0, T & x1, T a, T b, T c, T eps )
{
  T d = sqr( b ) - T(4) * a * c;
  if ( d < -eps )
    return 0;
  if ( d < eps ) {
    x0 = x1 = b / ( T(-2) * a );
    return 1;
  }
  
  T xd = sqrt( d );
  x0 = ( -b - xd ) / ( T(2) * a );
  x1 = ( -b + xd ) / ( T(2) * a );
  if ( x0 > x1 )
    swap( x0, x1 );
  return 2;
}


bool CreateLogarithmScale( nstl::vector<double> & points, double scaleMin, double scaleMax, double stepLo, double stepHi );

template< typename T >
bool isFiniteNumber( T t )
{
  return
#if defined( NV_WIN_PLATFORM )
    ( _finite( t ) != 0 );
#elif defined( NV_LINUX_PLATFORM )
    ( finite( t ) );
#endif
}

} //namespace ni_math

#ifdef WIN32UNDEFED
#define WIN32
#endif