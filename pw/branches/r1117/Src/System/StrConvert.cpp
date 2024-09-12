#include "stdafx.h"

#include "StrConvert.h"
#include <stdarg.h>

#include <System/ported/cwfn.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NStr
{


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ToWString
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<int>( const int& value, wchar_t *pBuffer, const int bufferLen )
{
  return NStr::SWPrintf(pBuffer, bufferLen, L"%d", value );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<unsigned int>( const unsigned int& value, wchar_t *pBuffer, const int bufferLen )
{
	return NStr::SWPrintf( pBuffer, bufferLen, L"%d", value );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<float>( const float& value, wchar_t *pBuffer, const int bufferLen )
{
	return NStr::SWPrintf( pBuffer, bufferLen, L"%.3f", value );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<char const *>( char const* const& value, wchar_t *pBuffer, const int bufferLen )
{
	int length;

  length = NStr::ConvertToWString( value, pBuffer, bufferLen);
	
	// add "..." in case of short buffer
	#ifdef WIN32
	if ( length == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER && bufferLen >= 4 )
	#else
	if ( length == 0 && bufferLen >= 4 )
	#endif
	{
		pBuffer[bufferLen-3] = '.';
		pBuffer[bufferLen-2] = '.';
		pBuffer[bufferLen-1] = '.';
		pBuffer[bufferLen-0] = 0;
		return bufferLen;
	}

	pBuffer[length] = 0;
	return length;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<wchar_t const*>( wchar_t const* const& value, wchar_t *pBuffer, const int bufferLen )
{
	const int valueLen = wcslen( value );
	const bool needEllipsis = valueLen > bufferLen && bufferLen > 4;
	const int resultLen = valueLen > bufferLen ? bufferLen : valueLen;
	//const int copyLen = needEllipsis ? bufferLen - 4 : resultLen;
	
	//if ( copyLen > 0 )
	NStr::WCopy(value, pBuffer, bufferLen);
	
	pBuffer[resultLen] = 0;
	if ( needEllipsis )
	{
		pBuffer[resultLen-3] = '.';
		pBuffer[resultLen-2] = '.';
		pBuffer[resultLen-1] = '.';
	}
	return resultLen;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<CVec2>( const CVec2& value, wchar_t *pBuffer, const int bufferLen )
{
  return NStr::SWPrintf(pBuffer, bufferLen, L"%.3f x %.3f", value.x, value.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<CVec3>( const CVec3& value, wchar_t *pBuffer, const int bufferLen )
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"%.3f x %.3f x %.3f", value.x, value.y, value.z );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<CVec4>( const CVec4& value, wchar_t *pBuffer, const int bufferLen )
{
	return NStr::SWPrintf( pBuffer, bufferLen, L"%.3f x %.3f x %.3f x %.3f", value.x, value.y, value.z, value.w );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<CQuat>( const CQuat& value, wchar_t *pBuffer, const int bufferLen )
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"%.3f x %.3f x %.3f @ %.3f", value.x, value.y, value.z, value.w );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<bool>( const bool& value, wchar_t *pBuffer, const int bufferLen )
{
	if ( value )
	{
	  NStr::WCopy(L"true", pBuffer, bufferLen);
		return 4;
	}
	else
	{
    NStr::WCopy(L"false", pBuffer, bufferLen);
		return 5;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert: value -> char *
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char staticBuff[256] = "";

template <>
const char * Convert < bool > ( const bool & value )
{
  strcpy_s ( staticBuff, value ? "true" : "false" );
  return staticBuff;
}

template <>
const char * Convert < int > ( const int & value )
{
  _ultoa_s ( (unsigned long) value, staticBuff, 10 );
  return staticBuff;
}

template <>
const char * Convert < float > ( const float & value )
{
  NStr::Printf( staticBuff, sizeof( staticBuff ), "%g", value );
  return staticBuff;
}

template <>
const char * Convert < double > ( const double & value )
{
  NStr::Printf( staticBuff, sizeof( staticBuff ), "%g", (float)value );
	return staticBuff;
}

template <>
const char * Convert < CTPoint < int > > ( const CTPoint < int > & value )
{
  NStr::Printf( staticBuff, sizeof( staticBuff ), "%i x %i", value.x, value.y );
  return staticBuff;
}

template <>
const char * Convert < CTRect < int > > ( const CTRect < int > & value )
{
  NStr::Printf( staticBuff, sizeof( staticBuff ), "%i x %i x %i x %i", value.x1, value.y1, value.x2, value.y2 );
  return staticBuff;
}

template <>
const char * Convert < CVec2 > ( const CVec2 & value )
{
  NStr::Printf( staticBuff, sizeof( staticBuff ), "%g x %g", value.x, value.y );
  return staticBuff;
}

template <>
const char * Convert < CVec3 > ( const CVec3 & value )
{
  NStr::Printf( staticBuff, sizeof( staticBuff ), "%g x %g x %g", value.x, value.y, value.z );
  return staticBuff;
}

template <>
const char * Convert < CVec4 > ( const CVec4 & value )
{
  NStr::Printf( staticBuff, sizeof( staticBuff ), "%g x %g x %g x %g", value.x, value.y, value.z, value.w );
  return staticBuff;
}

template <>
const char * Convert < CQuat > ( const CQuat & value )
{
  float angle;
  CVec3 axis;
  value.DecompAngleAxis ( &angle, &axis );
  NStr::Printf( staticBuff, sizeof( staticBuff ), "%g x %g x %g x %g", angle, axis.x, axis.y, axis.z );
  return staticBuff;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert: char * -> type
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename VECTOR, int DIM >
VECTOR ParseVector (const char * str, const VECTOR & empty = VECTOR() )
{
  const char seps[] = " \t";
  const char numberSymbols[] = "0123456789+-.e", commaSymbols[] = "x";
  const char comma[] = "x";

  VECTOR result;

  int index = 0;
  bool needComma = false;
  for(const char * p = str; *p; )
  {
    size_t wordBegin = strspn( p, seps );
    p += wordBegin;

    size_t length = strspn( p, needComma ? commaSymbols : numberSymbols );
    if(!length)
      break;

    const size_t BUFF_SZ = 64;
    char word[ BUFF_SZ ] = "";
    length = Min ( length, BUFF_SZ - 1 );
    memcpy ( word, p, length * sizeof(char) );
    word [ length ] = 0;
    p += length;

    if( needComma )
    {
      if( strcmp( word, comma ) != 0 )
        return empty;
      needComma = false;
    }
    else
    {
      result [ index ] = Convert < T > ( word );
      ++index;
      needComma = (index < DIM);
    }
  }

  if( index == DIM && !needComma)
    return result;
  else
    return empty;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
bool Convert < bool > ( const char * str )
{
  if( NStr::ICmp( str, "true" ) == 0 )
    return true;
  else if( NStr::ICmp( str, "false" ) == 0 )
    return false;
  return NStr::ToInt( str ) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
int Convert < int > ( const char * str )
{
  return NStr::ToInt( str );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
float Convert < float > ( const char * str )
{
  return NStr::ToFloat( str );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
double Convert < double > ( const char * str )
{
  return NStr::ToDouble( str );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
CTPoint < int > Convert( const char * str )
{
  return ParseVector < int, CTPoint < int >, 2 > ( str, CTPoint < int > ( 0, 0 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
CTRect < int > Convert( const char * str )
{
  return ParseVector < int, CTRect < int >, 4 > ( str, CTRect < int > ( 0, 0, 0, 0 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
CVec2 Convert < CVec2 > ( const char * str )
{
  return ParseVector <float, CVec2, 2 > ( str, CVec2 ( 0, 0 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
CVec3 Convert < CVec3 > ( const char * str )
{
  return ParseVector <float, CVec3, 3 > ( str, CVec3 ( 0, 0, 0 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
CVec4 Convert < CVec4 > ( const char * str )
{
  return ParseVector < float, CVec4, 4 > ( str, CVec4 ( 0, 0, 0, 0 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
CQuat Convert < CQuat > ( const char * str )
{
  CVec4 tmp = ParseVector < float, CVec4, 4 > ( str, CVec4 ( 0, 0, 0, 0 ) );
  return CQuat( tmp[0], tmp[1], tmp[2], tmp[3], true );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
wstring Convert < wstring > ( const char * str )
{
  return NStr::ToUnicode(str);
}

} //namespace NStr
