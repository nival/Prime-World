#include "stdafx.h"
#include "StrUtils.h"

#include <System/ported/cwfn.h>

namespace NStr {

void Copy(char *dest, const char *src, size_t  sizeOut)
{
  // Input check
  NI_ASSERT((NULL != dest) && (NULL != src), "Empty input str");
  NI_ASSERT(sizeOut > 0, "Output size should be more 0");

  // Length of input string
  unsigned int nLenIn = strlen(src);
  NI_ASSERT(sizeOut > nLenIn, "Not suff.space");

  // Safe memory copy
  if(sizeOut > 0)
  {
    int  nNumCharsToCopy = std::min< size_t >( sizeOut - 1, nLenIn );
    memcpy(dest, src, nNumCharsToCopy * sizeof(char));
    dest[nNumCharsToCopy] = '\0';
  }
}

void CopyN(char *dest, const char *src, size_t sizeOut, size_t numBytes)
{
  // Input check
  NI_ASSERT((NULL != dest) && (NULL != src), "Empty input str");
  NI_ASSERT(sizeOut > 0, "Output size should be more 0");
  NI_ASSERT(numBytes < sizeOut, "Number of bytes to copy should be less than output size");

  // Length of input string
  unsigned int nLenIn = strlen(src);
  NI_ASSERT(nLenIn >= numBytes, "Not suff.space");

  // Safe memory copy
  if((sizeOut > 0) && (nLenIn >= numBytes))
  {
    int nNumCharsToCopy = std::min< size_t >( sizeOut - 1, numBytes );
    memcpy(dest, src, nNumCharsToCopy * sizeof(char));
    dest[nNumCharsToCopy] = '\0';
  }
}

int   Cmp(const char *sStr1, const char *sStr2, unsigned int /*numCharsToCompare*/)
{
  int r = strcmp( sStr1, sStr2);
  return r;
}

int   NCmp(const char *sStr1, const char *sStr2, unsigned int numCharsToCompare)
{
  int r = strncmp( sStr1, sStr2, numCharsToCompare);
  return r;
}

int   ICmp(const char *sStr1, const char *sStr2, unsigned int /*numCharsToCompare*/)
{
  int r = strcasecmp( sStr1, sStr2 );
  return r;
}

int   Len(const char *src)
{
  int r = strlen(src);
  if ( src == NULL )
  {
    r = 0;
  }
  return r;
}


void Cat(char *sOut, const char *sIn, size_t sizeOut)
{
  // Input check
  NI_ASSERT((NULL != sOut) && (NULL != sIn), "NULL input");
  NI_ASSERT(sizeOut > 0, "0 output length");

  // Length of input string
  unsigned int nLenIn  = strlen(sIn);
  unsigned int nLenOut = strlen(sOut);
  nLenIn = nLenIn;
  NI_ASSERT(sizeOut > nLenIn + nLenOut, "Too small dest buf");

  // Invalid finish
  if(sizeOut <= nLenOut)
    return;

  Copy(sOut + nLenOut, sIn, sizeOut - nLenOut);
}

int VPrintf(char *sOut, size_t sizeOut, const char *sFormat, va_list vlArgs)
{
  // Input check
  NI_ASSERT((NULL != sOut) && (NULL != sFormat), "Empty args");
  NI_ASSERT(sizeOut > 0, "Bad size");
  
  int nNumWrittenChars = -1;

  // Safe write to string
  if(sizeOut > 0)
  {
    nNumWrittenChars = std::vsnprintf( sOut, sizeOut - 1, sFormat, vlArgs );
    // vsnprintf

    // Check if _vsnprintf write correctly
    //seASSERT(-1 != nNumWrittenChars);
    //seASSERT((nNumWrittenChars > 0) && (seUInt32(nNumWrittenChars) < sizeOut)); // Just in case

    // Finish string in any case
    sOut[(-1 != nNumWrittenChars) ? nNumWrittenChars : (sizeOut - 1)] = '\0';
  }
  
  return nNumWrittenChars;
}

int Printf(char *sOut, size_t sizeOut, const char *sFormat, ...)
{
  va_list vlArgs;
  va_start(vlArgs, sFormat);
  int nNumWrittenChars = VPrintf(sOut, sizeOut, sFormat, vlArgs);
  va_end(vlArgs);
  return nNumWrittenChars;
}

void GenerateUUID( char *dest, size_t sizeOut )
{
	assert( NULL != dest );

	GUID guid;
	CoCreateGuid( &guid );
	GUID2String( guid, dest );
}

void SysLog( const char *logString )
{
	OutputDebugString( logString );
}

void ItoA(int i, char *buf, size_t buf_len)
{
  ( void ) snprintf( buf, buf_len, "%d", i );
}

int WCmp( const wchar_t *str1, const wchar_t *str2 )
{
	return _wcsicmp( str1, str2);
}

int WNCmp(const wchar_t *str1, const wchar_t *str2, int maxCount)
{
	return _wcsnicmp( str1, str2, maxCount);
}

int WCopy(const wchar_t *src, wchar_t *dest, int destMax)
{
	return wcscpy_s( dest, destMax, src );
}

int   ConvertToWString( const char *src, wchar_t *dest, int DestMax)
{
  int i;

  for (i = 0; src[i] && i < DestMax; i++)
  {
    dest[i] = (wchar_t)src[i];
  }
  dest[i] = 0;
  NI_ASSERT( src[i] == 0, "Too small dest buffer" );
  return i;
}

int   SWPrintf(wchar_t *dest, size_t destMaxlen, const wchar_t *format, ...)
{
  int ret;
  
  va_list vlArgs;
  va_start(vlArgs, format);
  ret = vswprintf( dest, destMaxlen, format, vlArgs );
  // swprintf
  va_end(vlArgs);           
  return ret;
}

void WVPrintf(wchar_t *dest, size_t destMax, const wchar_t *format, va_list vlArgs)
{
	vswprintf( dest, destMax, format, vlArgs );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * FindFirst( const char *sStr, const char *sSubStr )
{
  return (char*)strstr( sStr, sSubStr );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * FindFirstI( const char *sStr, const char *sSubStr )
{
	return const_cast< char * >( strcasestr( sStr, sSubStr ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wchar_t * FindFirst( const wchar_t *sStr, const wchar_t *sSubStr )
{
	return (wchar_t*)wcsstr( sStr, sSubStr );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wchar_t * FindFirstI( const wchar_t *sStr, const wchar_t *sSubStr )
{
	return const_cast< wchar_t * >( wcsstr( sStr, sSubStr ) ); // TODO: Need to use correct function to compare
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * FindFirstChar( const char *sStr, char ch )
{
  return (char*)strchr( sStr, ch );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * FindLastChar( const char *sStr, char ch )
{
  return (char*)strrchr( sStr, ch );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
};  // name space



