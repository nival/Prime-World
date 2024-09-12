#include "stdafx.h"
#include "SafeTextFormatEx.h"
#include "System/InlineProfiler.h"
#include "ThreadLocal.h"


#ifdef _DEBUG
//Comment out next line to run the test in debug
//#define SAFE_FMT_ENABLE_ASSERTS
//Intentionally disabled - could not resolve all problems in codebase
#endif

#ifdef SAFE_FMT_ENABLE_ASSERTS
#define SAFE_FMT_WARN( reason ) assert( false && (reason) )
#else
#define SAFE_FMT_WARN( reason ) (reason)
#endif



namespace text
{

static const char * ParseFlags( const char * p, SFormatSpecs & specs )
{
  while ( true )
  {
    switch ( *p )
    {
      default:
        return p;

      case ' ':
        specs.flags |= EFlags::Blank;
        break;
      case '-':
        specs.flags |= EFlags::Minus;
        break;
      case '+':
        specs.flags |= EFlags::Plus;
        break;
      case '0':
        specs.flags |= EFlags::Zero;
        break;
      case '#':
        specs.flags |= EFlags::Sharp;
        break;
    }
    ++p;
  }
}




static const char * ParseIntOrAsterisk( const char * p, bool & valuePresent, int & value, size_t & argIndex, const IArg * const * args, size_t argsCount )
{
  valuePresent = false;
  value = 0;

  if ( *p == '*' )
  {
    if ( argIndex >= argsCount ) {
      SAFE_FMT_WARN( "Not enough arguments for asterisk(*) format" );
      return 0;
    }

    const IArg * arg = args[argIndex++];

    if ( !arg->AsInt( value ) ) {
      SAFE_FMT_WARN( "Wrong argument type for asterisk(*) format" );
      return 0;
    }

    valuePresent = true;
    ++p;
  }
  else if ( isdigit( *p ) )
  {
    while ( true )
    {
      if ( !isdigit( *p ) )
        break;
      int digit = ( *p - '0' );
      value = 10 * value + digit;
      ++p;
    }
    valuePresent = true;
  }

  return p;
}



static const char * ParseWidth( const char * p, SFormatSpecs & specs, size_t & argIndex, const IArg * const * args, size_t argsCount )
{
  bool widthPresent = false;
  int width = 0;
  const char * result = ParseIntOrAsterisk( p, widthPresent, width, argIndex, args, argsCount );
  if ( !result )
    return 0;

  if ( widthPresent ) {
    specs.width = width;
    specs.flags |= EFlags::Has_Width;
  }
  return result;
}



static const char * ParsePrecision( const char * p, SFormatSpecs & specs, size_t & argIndex, const IArg * const * args, size_t argsCount )
{
  if ( *p != '.' )
    return p;
  ++p;

  bool precPresent = false;
  int prec = 0;
  const char * result = ParseIntOrAsterisk( p, precPresent, prec, argIndex, args, argsCount );
  if ( !result )
    return 0;

  if ( precPresent ) {
    specs.precision = prec;
    specs.flags |= EFlags::Has_Precision;
  }
  return result;
}



static const char * ParseSize( const char * p )
{
  while ( true )
  {
    if ( !strcmp( p, "ll" ) )
      p += 2;
    else if ( !strcmp( p, "I32" ) )
      p += 3;
    else if ( !strcmp( p, "I64" ) )
      p += 3;
    else
    {
      switch ( *p )
      {
        default:
          return p;

        case 'l':
        case 'L':
        case 'h':
        case 'w':
        case 'I':
          ++p;
          break;
      }
    }
  }
}



static const char * ParseType( const char * p, SFormatSpecs & specs )
{
  switch ( *p )
  {
    default:
      SAFE_FMT_WARN( "Wrong argument type char" );
      return 0;

    case 'c':
    case 'C':
    case 'd':
    case 'i':
    case 'o':
    case 'u':
    case 'f':
    case 'a': //Treated as f
    case 'A': //Treated as f
    case 'p':
    case 's':
    case 'S':
      break;

    case 'e':
    case 'E':
      specs.flags |= ( *p == 'e' ) ? EFlags::Exp : EFlags::EXP;
      break;

    case 'g':
    case 'G':
      specs.flags |= ( *p == 'g' ) ? EFlags::FloatG : EFlags::FLOATG;
      break;

    case 'x':
    case 'X':
      specs.flags |= ( *p == 'x' ) ? EFlags::Hex : EFlags::HEX;
      break;

    //Unsupported
    case 'n':
      SAFE_FMT_WARN( "Unsupported" );
      return 0;
  }

  return p + 1;
}



static const char * ParseArg( IBuffer * buffer, const char * fmt, size_t & argIndex, const IArg * const * args, size_t argsCount )
{
  SFormatSpecs specs;

  const char * widthStart = ParseFlags( fmt, specs );
  if ( !widthStart )
    return fmt; //Error

  const char * precStart = ParseWidth( widthStart, specs, argIndex, args, argsCount );
  if ( !precStart )
    return widthStart; //Error

  const char * sizeStart = ParsePrecision( precStart, specs, argIndex, args, argsCount );
  if ( !sizeStart )
    return precStart; //Error

  const char * typeStart = ParseSize( sizeStart ); //It cannot fail

  const char * end = ParseType( typeStart, specs );
  if ( !end )
    return typeStart; //Error

  if ( argIndex >= argsCount ) {
    SAFE_FMT_WARN( "Too few arguments" );
    buffer->WriteZ( "<arg>" );
    return end; //Error
  }

  const IArg * arg = args[argIndex++];
  arg->Format( buffer, specs );

  return end;
}



size_t FormatArray( IBuffer * buffer, const char * fmt, const IArg * const * args, size_t argsCount )
{
  size_t argIndex = 0;
  const char * p = fmt;

  while ( *p )
  {
    //Plain text
    size_t spLeft = buffer->SpaceLeft();
    if ( !spLeft )
      break;

    const char * perc = p;
    while ( ( spLeft > 0 ) && *perc && ( *perc != '%' ) ) {
      ++perc;
      --spLeft;
    }

    buffer->Write( p, perc - p );
    p = perc;

    if ( *p == '%' )
    {
      ++p;
      if ( *p == '%' ) {
        buffer->Write( '%', 1 );
        ++p;
      }
      else
      {
        p = ParseArg( buffer, p, argIndex, args, argsCount );
      }
    }
  }

  if ( argIndex != argsCount )
    SAFE_FMT_WARN( "Too many arguments (or buffer overflow)" );

  return buffer->Finish();
}









char * BasicArg::SafeAppend( char * buff, const char * buffEnd, const char * src )
{
  if ( !buff || ( buff + 1 >= buffEnd ) )
    return 0;

  size_t buffSz = buffEnd - buff;

  size_t L = strlen( src );
  if ( L >= buffSz )
    return 0;

  memcpy( buff, src, L + 1 );
  return buff + L;
}



char * BasicArg::SafeAppend( char * buff, const char * buffEnd, char c )
{
  if ( !buff || ( buff + 1 >= buffEnd ) )
    return 0;

  buff[0] = c;
  buff[1] = 0;
  return buff + 1;
}



char * BasicArg::FormatFormat( char * fmt, size_t fmtBufffSize, const SFormatSpecs & specs )
{
  char buf[40];

  const char * end = fmt + fmtBufffSize;
  char * p = fmt;
  p = SafeAppend( p, end, '%' );

  if ( specs.flags & EFlags::Sharp )
    p = SafeAppend( p, end, '#' );

  if ( ( specs.flags & EFlags::Minus ) )
    p = SafeAppend( p, end, '-' );

  if ( specs.flags & EFlags::Plus )
    p = SafeAppend( p, end, '+' );
  else if ( specs.flags & EFlags::Blank )
    p = SafeAppend( p, end, ' ' );

  if ( ( specs.flags & EFlags::Zero ) && !( specs.flags & EFlags::Has_Precision ) )
    p = SafeAppend( p, end, '0' );

  if ( specs.flags & EFlags::Has_Width ) {
#if defined( NV_WIN_PLATFORM )
    _itoa( Clamp( specs.width, -256, +256 ), buf, 10 );
#elif defined( NV_LINUX_PLATFORM )
    snprintf( buf, sizeof( buf ), "%d", Clamp( specs.width, -256, +256 ) );
#endif
    p = SafeAppend( p, end, buf );
  }

  if ( specs.flags & EFlags::Has_Precision ) {
    p = SafeAppend( p, end, '.' );
#if defined( NV_WIN_PLATFORM )
    _itoa( Clamp( specs.precision, -256, +256 ), buf, 10 );
#elif defined( NV_LINUX_PLATFORM )
    snprintf( buf, sizeof( buf ), "%d", Clamp( specs.precision, -256, +256 ) );
#endif
    p = SafeAppend( p, end, buf );
  }

  return p;
}



inline size_t StringLength( const char * str ) { return strlen( str ); }
inline size_t StringLength( const wchar_t * str ) { return wcslen( str ); }
inline void WriteBuffer( IBuffer * buf, const char * str, size_t len ) { buf->Write( str, len ); }

inline void WriteBuffer( IBuffer * buf, const wchar_t * str, size_t len ) {
  const static size_t BUF_SZ = 4; //MB_CUR_MAX is NOT a constant in VS
  if ( MB_CUR_MAX > BUF_SZ )
    return;

  size_t L = Min( buf->SpaceLeft(), len );
  for ( const wchar_t *p = str; L > 0; ++p, --L ) {
    char mb[BUF_SZ];
    int mbc = wctomb( mb, *p );
    char c = ( mbc == 1 ) ? mb[0] : '?';
    buf->Write( c, 1 );
  }
}


template <typename TChar>
inline void FormatString( IBuffer * buffer, const TChar * str, const SFormatSpecs & specs )
{
  if ( !str ) {
    buffer->WriteZ( "<nullstr>" );
    return;
  }

  int len = StringLength( str );
  if ( specs.flags & EFlags::Has_Precision )
    len = Min( len, specs.precision );

  int leftAlign = ( specs.flags & EFlags::Minus ) ? true : false;

  if ( leftAlign )
    WriteBuffer( buffer, str, len );

  int padding = 0;
  if ( specs.flags & EFlags::Has_Width )
    if ( specs.width > len )
      padding = specs.width - len;

  if ( padding ) {
    char c = ( ( specs.flags & EFlags::Zero ) && !( specs.flags & EFlags::Minus ) ) ? '0' : ' ';
    buffer->Write( c, padding );
  }

  if ( !leftAlign )
    WriteBuffer( buffer, str, len );
}



void BasicArg::FormatString( IBuffer * buffer, const char * str, const SFormatSpecs & specs )
{
  text::FormatString( buffer, str, specs );
}


void BasicArg::FormatString( IBuffer * buffer, const wchar_t * str, const SFormatSpecs & specs )
{
  text::FormatString( buffer, str, specs );
}


struct ThreadBuf {
  char bytes[THREAD_BUFF_SZ];
};

char (&GetThreadBuffer())[THREAD_BUFF_SZ]
{
  static ThreadLocal<ThreadBuf> buf;
  return buf.GetValue().bytes;
}

} //namespace text
