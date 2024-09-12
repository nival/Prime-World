#ifndef __CWFN_H_INCLUDED__925380__
#define __CWFN_H_INCLUDED__925380__

#include "System/ported/types.h"
#include "System/DefaultTypes.h"

#if defined( NV_LINUX_PLATFORM )

  #include "nstring.h"
	#include <cstdio>
	#include <cstdlib>
	#include <algorithm>
  #include <string>
	#include <assert.h>
	#include <syslog.h>

	inline void OutputDebugString( char const * lpOutputString )
	{
		syslog( LOG_USER | LOG_DEBUG, "%s", lpOutputString );
	}

	#define _vsnprintf_s vsnprintf
	#define _vsnwprintf_s vswprintf
	#define _strnicmp strncasecmp
	#define _snprintf_s std::snprintf

	inline UINT GetACP()
	{
		// В Linux кодовую страницу пока не используем, а используем текущую локаль для конвертации
		return 0;
	}

	inline int _wtoi( wchar_t const * str )
	{
		char buffer[ 12 ];
		return wcstombs( buffer, str, sizeof( buffer ) ) == 0 ? 0 : atoi( buffer );
	}

	inline char * strrev( char *str )
	{
		if ( str )
			std::reverse( str, str + strlen( str ) );

		return str;
	}

	inline errno_t _ultoa_s( unsigned long value, char *str, size_t size_of_str, int radix )
	{
		assert( NULL != str );
		assert( 0 < size_of_str );
		assert( 2 <= radix && radix >= 16 ); // in windows version of ultoa radix can be 36 as a maximum value

		static const char digits[] = "0123456789ABCDEF";

		char *current = str;
		char *str_end = str + size_of_str;

		if ( 0 == value && size_of_str )
			*current++ = '0';
		else {

			while ( current != str_end ) {

				*current++ = digits[ value % radix ];

				if ( 0 == ( value /= radix ) )
					break;

			}

			std::reverse( str, current );

		}

		if ( current != str_end )
			*current = '\0';

		return 0;
	}

	template< size_t size > inline errno_t _ultoa_s( unsigned long value, char (&str)[ size ], int radix )
	{
		return _ultoa_s( value, str, size, radix );
	}

	inline __int64 _atoi64( const char *str )
	{
		return strtol( str, NULL, 10 );
	}

	enum { CP_ACP = 0 };

	static __int64 _wcstoi64( const wchar_t *nptr, wchar_t **endptr, int base )
	{
		char buffer[ 24 ];
		char *end = NULL;
		__int64 result = wcstombs( buffer, nptr, sizeof( buffer ) ) == 0 ? 0 : strtol( buffer, &end, base );

		if ( endptr )
			*endptr = const_cast< wchar_t * >( nptr + ( end - &buffer[ 0 ] ) );

		return result;
	}

	static nival::uint64_t _wcstoui64( const wchar_t *nptr, wchar_t **endptr, int base  )
	{
		char buffer[ 24 ];
		char *end = NULL;
		__int64 result = wcstombs( buffer, nptr, sizeof( buffer ) ) == 0 ? 0 : strtoul( buffer, &end, base );

		if ( endptr )
			*endptr = const_cast< wchar_t * >( nptr + ( end - &buffer[ 0 ] ) );

		return result;
	}

	inline int WideCharToMultiByte(
		UINT CodePage,
		DWORD dwFlags,
		LPCWSTR lpWideCharStr,
		int cchWideChar,
		LPSTR lpMultiByteStr,
		int cbMultiByte,
		LPCSTR lpDefaultChar,
		LPBOOL lpUsedDefaultChar
	)
	{
		return wcstombs( lpMultiByteStr, lpWideCharStr, cbMultiByte );
	}

	inline int MultiByteToWideChar(
		UINT CodePage,
		DWORD dwFlags,
		LPCSTR lpMultiByteStr,
		int cbMultiByte,
		LPWSTR lpWideCharStr,
		int cchWideChar
	)
	{
		return mbstowcs( lpWideCharStr, lpMultiByteStr, cchWideChar );
	}

	template< size_t size > inline errno_t strcpy_s( char ( &strDestination )[ size ], const char *strSource )
	{
		strncpy( strDestination, strSource, size );
		return 0;
	}

	inline errno_t strcpy_s( char *strDestination, size_t numberOfElements, const char *strSource )
	{
		strncpy( strDestination, strSource, numberOfElements );
		return 0;
	}

	inline int _stricmp( const char *string1, const char *string2 )
	{
		return strcasecmp( string1, string2 );
	}

	inline errno_t wcscpy_s( wchar_t *destination, size_t number_of_elements, const wchar_t *source )
	{
		wcsncpy( destination, source, number_of_elements );
		return 0;
	}

	inline int _wcsicmp( wchar_t const *string1, wchar_t const *string2 )
	{
		return wcscasecmp( string1, string2 );
	}

	inline int _wcsnicmp( wchar_t const *string1, wchar_t const *string2, size_t count )
	{
		return wcsncasecmp( string1, string2, count );
	}

	inline int _vsnprintf_s( char *buffer, size_t sizeOfBuffer, size_t count, const char *format, va_list argptr )
	{
		return std::vsnprintf( buffer, sizeOfBuffer, format, argptr );
	}

	inline BOOL PathCanonicalizeA( LPSTR lpszDst, LPCSTR lpszSrc )
	{
		// В Linux есть похожий аналог этой функции, но он выполняет работу не с самим строками, а с реальной файловой системой, так как сам путь может содежать ссылки внутри себя, а их без обращений к файловой системе не развернуть.
		//assert( false );
		//return realpath( lpszSrc, lpszDst ) ? TRUE : FALSE;
    size_t ind = 0;
    const nstl::string src( lpszSrc );
    nstl::string dst;
    while ( ind != std::string::npos )
    {
      size_t next = src.find( '/', ind + 1 );
      if ( next == std::string::npos )
      {
        const int diff = src.length() - ind;
        if ( diff > 1 )
        {
          if ( src[ ind + 1 ] == '.' )
          {
            if ( diff == 2 ) { ;; }
            else if ( ( diff == 3 ) && ( src[ ind + 2 ] == '.' ) )
            {
              size_t last = dst.rfind( '/' );
              if ( last == std::string::npos ) { last = 0; }
              dst.erase( last );
            }
            else { dst.append( src.substr( ind ) ); }
          }
          else { dst.append( src.substr( ind ) ); }
        }
        else { dst.append( src.substr( ind ) ); }
      }
      else
      {
        const int diff = next - ind;
        if ( diff > 1 )
        {
          if ( src[ ind + 1 ] == '.' )
          {
            if ( diff == 2 ) { ;; }
            else if ( ( diff == 3 ) && ( src[ ind + 2 ] == '.' ) )
            {
              size_t last = dst.rfind( '/' );
              if ( last == std::string::npos ) { last = 0; }
              dst.erase( last );
            }
            else { dst.append( src.substr( ind, diff ) ); }
          }
          else { dst.append( src.substr( ind, diff ) ); }
        }
      }
      ind = next;
    }
    strcpy( lpszDst, dst.c_str() );
    return TRUE;
	}
  
  inline bool operator==( const GUID & g1, const GUID & g2 )
  {
    return ( g1.Data1 == g2.Data1 )
        && ( g1.Data2 == g2.Data2 )
        && ( g1.Data3 == g2.Data3 )
        && ( g1.Data4[ 0 ] == g2.Data4[ 0 ] )
        && ( g1.Data4[ 1 ] == g2.Data4[ 1 ] )
        && ( g1.Data4[ 2 ] == g2.Data4[ 2 ] )
        && ( g1.Data4[ 3 ] == g2.Data4[ 3 ] )
        && ( g1.Data4[ 4 ] == g2.Data4[ 4 ] )
        && ( g1.Data4[ 5 ] == g2.Data4[ 5 ] )
        && ( g1.Data4[ 6 ] == g2.Data4[ 6 ] )
        && ( g1.Data4[ 7 ] == g2.Data4[ 7 ] );
  }
  
  inline bool operator!=( const GUID & g1, const GUID & g2 )
  {
    return !( g1 == g2 );
  }
  
  inline bool IsEqualGUID( const GUID & rguid1, const GUID & rguid2 )
  {
    return rguid1 == rguid2;
  }

	static HRESULT CoCreateGuid( GUID *pguid )
	{
		assert( NULL != pguid );

		// Using a simple case to generate the guid
		pguid->Data1 = DWORD( rand() & 0xFFFF ) << 16 | WORD( rand() & 0xFFFF );
		pguid->Data2 = WORD( rand() & 0xFFFF );
		pguid->Data3 = WORD( rand() & 0xFFFF );
		* reinterpret_cast< WORD * >( &pguid->Data4[ 0 ] ) = WORD( rand() & 0xFFFF );
		* reinterpret_cast< WORD * >( &pguid->Data4[ 2 ] ) = WORD( rand() & 0xFFFF );
		* reinterpret_cast< WORD * >( &pguid->Data4[ 4 ] ) = WORD( rand() & 0xFFFF );
		* reinterpret_cast< WORD * >( &pguid->Data4[ 6 ] ) = WORD( rand() & 0xFFFF );

		return 0;
	}

	inline void GUID2String( GUID const &guid, char *string_guid )
	{
		std::sprintf( string_guid, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
			guid.Data1,
			guid.Data2,
			guid.Data3,
			guid.Data4[ 0 ],
			guid.Data4[ 1 ],
			guid.Data4[ 2 ],
			guid.Data4[ 3 ],
			guid.Data4[ 4 ],
			guid.Data4[ 5 ],
			guid.Data4[ 6 ],
			guid.Data4[ 7 ]
		);
	}
  
  inline HRESULT UuidCreate( GUID * guid )
  {
    return CoCreateGuid( guid );
  }
  
  inline void UuidToString( GUID const * guid, byte ** string_guid )
  {
    GUID2String( *guid, (char*)(*string_guid) );
  }
  
  inline void RpcStringFree( byte ** )
  {
  }

	inline errno_t fopen_s( FILE **pFile, const char *filename, const char *mode )
	{
		assert( NULL != pFile );

		*pFile = fopen( filename, mode ); // Need to parse mode and create the new linux mode

		return pFile ? 0 : 1;
	}

	inline errno_t gmtime_s( struct tm *_tm, const time_t *time )
	{
		return gmtime_r( time, _tm ) ? 0 : 1;
	}

#endif // defined( NV_LINUX_PLATFORM )
#endif // __CWFN_H_INCLUDED__925380__

