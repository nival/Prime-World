#include "stdafx.h"

#include "NameMap.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNameMap {


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline bool IsNumeric( wchar_t c, bool excludeZero = false )
{
  return ( c >= (excludeZero ? L'1' : L'0') ) && ( c <= L'9' );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline bool ParseFormat( const wchar_t * format, wchar_t & leading, wchar_t & trailing, int & width, int & digits, bool & forceSign )
{
  const wchar_t * p = format;

  if(!p[0])
    return true;

  //leading symbol
  if(!IsNumeric(*p, true))
  {
    if ( *p == L'+' )
    {
      forceSign = true;
    }
    else
    {
      leading = *p;
    }
    ++p;
  }

  //width
  for( int w = 0; ; ++p )
    if(IsNumeric(*p))
      w = w * 10 + (*p - L'0');
    else if(!*p || *p == L'.')
    {
      width = w;
      break;
    }
    else
      return false;

  if(*p == L'.')
    ++p;

  //trailing symbol
  if(!*p)
    return true;

  if(!IsNumeric(*p, true))
  {
    trailing = *p;
    ++p;
  }

  //decimal digits
  for( int d = 0; ; ++p )
    if(IsNumeric(*p))
      d = d * 10 + (*p - L'0');
    else if(!*p)
    {
      digits = d;
      return true;
    }
    return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int FormatWString( wchar_t * buffer, int size, const wchar_t * source, wchar_t leading, wchar_t trailing, int width, int digits )
{
  int len = (int)wcslen( source );
  if(digits && digits < len)
    len = digits;

  if(!width)
    width = len;

  int padding = ( len < width ) ? ( width - len ) : 0;
  padding = Min( padding, size - 1 );

  for(int i = 0; i < padding; ++i)
    buffer[i] = leading;

  int newLen = width - padding;
  newLen = Min( newLen, size - padding - 1 );
  for(int i = 0; i < newLen; ++i)
    buffer[padding + i] = source[i];

  int total = padding + newLen;
  buffer[total] = 0;
  return total;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static size_t SafeAppend( wchar_t * buffer, size_t size, const wchar_t * text, size_t offset )
{
  if( offset + 1 >= size )
    return offset;

  size_t len = wcslen( text );
  size_t tocopy = len;
  if ( ( offset + len + 1 ) >= size )
    tocopy = size - offset - 1;

  memcpy( buffer + offset, text, tocopy * sizeof(wchar_t) );
  buffer[ offset + tocopy ] = 0;
  return offset + tocopy;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int FormatWStringList( wchar_t * buffer, int size, const wchar_t * separator, const WStringListT & slist )
{
  size_t offs = 0;
  WStringListT::const_iterator it = slist.begin();
  while( true )
  {
    offs = SafeAppend( buffer, size, it->c_str(), offs );
    ++it;
    if( it == slist.end() )
      return offs + 1;
    else
      offs = SafeAppend( buffer, size, separator, offs );
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Использовать с форматом "%#1.*f" 
template< class Iter >
inline Iter skipTrailingZeros( Iter it )
{
  while( *it == '0' ) 
    --it;

  if( *it == '.' )
    --it;

  return it;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ReadonlyVariant::Format( wchar_t * buffer, int size, const wchar_t * format )
{
  if( GetType() == VariantType::WStringList )
  {
    return FormatWStringList( buffer, size, format, GetWStringList() );
  }

  wchar_t leading = L' ', trailing = '0';
  int width = 0, digits = 0;
  bool forceSign = false;

  ParseFormat( format, leading, trailing, width, digits, forceSign );
  
  const int BUF_SZ = 64;

  if( GetType() == VariantType::Bool )
  {
    return swprintf( buffer, size, L"%*s", width, GetBool() ? L"true" : L"false" );
  }
  if( GetType() == VariantType::Int )
  {
    wchar_t fmt[BUF_SZ] = L"";
    width = Min( width, BUF_SZ - 8 );
    //digits = Min( digits, 6 );
    swprintf( fmt, BUF_SZ, L"%%%s%s%ii", (forceSign ? L"+" : L""), (leading == L'0' ? L"0" : L""), width );
    return swprintf( buffer, size, fmt, GetInt() );
  }
  else if ( GetType() == VariantType::Float )
  {
    wchar_t fmt[BUF_SZ] = L"";
    width = Min( width, BUF_SZ - 8 );
    digits = Min( digits, 6 );

    //Параметр %g перестаёт подходить, когда fabs(val) < 0
    //http://codepad.org/Yqg6g8SM
    swprintf( fmt, BUF_SZ, L"%%%s#%s%i.%if", (forceSign ? L"+" : L""), (leading == L'0' ? L"0" : L""), width + 1, digits );
    wchar_t * pLast = buffer + swprintf( buffer, size, fmt, GetFloat() );
     
    if( pLast > buffer )
    {
      pLast = skipTrailingZeros( pLast - 1 ) + 1;
      *pLast = '\0';
    }
    
    return pLast - buffer;
  }
  else if ( GetType() == VariantType::WString )
  {
    digits = Max(digits, 0);
    return FormatWString( buffer, size, GetWString(), leading, trailing, width, digits );
  }
  else if ( GetType() == VariantType::String )
  {
    digits = Max(digits, 0);
    wstring temp = NStr::ToUnicode( GetString() );
    return FormatWString( buffer, size, temp.c_str(), leading, trailing, width, digits );
  }
  else
    if(size > 0)
      buffer[0] = 0;

  return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Variant * Map::GetVariant( const char * name, void* prms, bool readonly )
{
  //we use one inline cycle instead of strlen + strchr
  const char * openBrace = 0, * closingBrace = 0;
  int bracesCount = 0;
  const char * end = name;
  for( ; *end && *end != '.'; ++end)
  {
    if( !bracesCount && *end == '.' )
      break;

    NI_VERIFY( closingBrace == 0, "Text after closing variant argument brace!", return 0 );

    if( *end == '(' )
    {
      NI_VERIFY( end > name, "Name-map or variant name expected, '(' found!", return 0 );
      if( !bracesCount )
        openBrace = end;
      ++bracesCount;
    }
    else if ( *end == ')' )
    {
      NI_VERIFY( bracesCount > 0, "Unexpected ')' in variant argument!", return 0 );
      --bracesCount;
      if( !bracesCount )
        closingBrace = end;
    }
  }

  size_t length = end - name;

  const char * args = 0;
  int argsLength = 0;

  if( openBrace )
  {
    NI_VERIFY( closingBrace, "Incorrect braces balance in variant argument!", return 0 );
    NI_ASSERT( closingBrace > openBrace, "" );
    args = openBrace + 1;
    argsLength = closingBrace - args;
    length = openBrace - name;
  }

  if(!length)
    return 0;

  if(!*end) //eol
  {
    Variant * pVariant = 0;
    if( ResolveName ( name, length, args, argsLength, 0, &pVariant, prms, readonly ) )
      return pVariant;
    return 0;
  }

  //dot found
  Map * pMap = 0;
  if( ResolveName( name, length, args, argsLength, &pMap, 0, prms, readonly ) )
    return pMap->GetVariant ( end + 1, prms, readonly );

  return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Map::ResolveName( const char * name, int length, const char * args, int argsLength, Map ** ppMap, Variant ** ppVariant, void* prms, bool readonly )
{
  if ( ResolveNameByMacro( name, length, args, argsLength, ppMap, ppVariant, prms, readonly ) )
    return true;

  if ( ppMap )
    if(Map * nameMap = ResolveNameMap( name, length, args, argsLength, prms, readonly ))
    {
      *ppMap = nameMap;
      return true;
    }

  if( ppVariant )
    if( Variant * variant = ResolveVariant( name, length, args, argsLength, prms, readonly ) )
    {
      *ppVariant = variant;
      return true;
    }

  return false;
}

} //namespace NNameMap

NI_DEFINE_REFCOUNT( NNameMap::IMap );
