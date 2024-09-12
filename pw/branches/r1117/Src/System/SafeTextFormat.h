#ifndef SYSTEM_SAFEPRINTF_H_INCLUDED
#define SYSTEM_SAFEPRINTF_H_INCLUDED

#pragma warning( disable : 4244 ) //conversion from 'double' to 'float', possible loss of data
#pragma warning( disable : 4996) //This function or variable may be unsafe.

#include "MathTools.h"
#include "noncopyable.h"
#include <stdio.h>


namespace text
{

namespace EFlags
{
  enum Enum {
    Minus           = 1,
    Plus            = 2,
    Zero            = 4,
    Sharp           = 8,
    Blank           = 16,
    Has_Width       = 256,
    Has_Precision   = 512,
    Hex             = 1024,
    HEX             = 2048,
    Exp             = 4096,
    EXP             = 8192,
    FloatG          = 16384,
    FLOATG          = 32768
  };
}



struct SFormatSpecs
{
  int         width;
  int         precision;
  unsigned    flags;

  SFormatSpecs() : width( 0 ), precision( 0 ), flags( 0 ) {}
};



class IBuffer
{
public:
  virtual size_t Length() const = 0;
  virtual size_t SpaceLeft() const = 0;
  virtual size_t Write( char c, size_t count ) = 0;
  virtual size_t Write( const char * bytes, size_t size ) = 0;
  virtual size_t Finish() = 0;
  virtual const char * c_str() const = 0;

  size_t WriteZ( const char * str ) {
    size_t l = strlen( str );
    return Write( str, l ); }
};



class IArg
{
public:
  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const = 0;
  virtual bool AsInt( int & intValue ) const = 0;
};





class BasicArg : public IArg, public NonCopyable
{
protected:
  static char * SafeAppend( char * buff, const char * buffEnd, const char * src );
  static char * SafeAppend( char * buff, const char * buffEnd, char c );
  static char * FormatFormat( char * fmt, size_t fmtBufffSize, const SFormatSpecs & specs );
  static void FormatString( IBuffer * buffer, const char * str, const SFormatSpecs & specs );
  static void FormatString( IBuffer * buffer, const wchar_t * str, const SFormatSpecs & specs );
};



//generic implementation, requires implementation of the next method:
// void Format( text::IBuffer * buffer, const text::SFormatSpecs & specs ) const;
template <class T>
class TArg : public BasicArg
{
public:
  TArg( const T & _v ) : v( _v ) {}

  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const
  {
    v.Format( buffer, specs );
  }

  virtual bool AsInt( int & _intValue ) const { _intValue; return false; }

private:
  const T & v;
};



///// generic numeric arguments /////
template<class T, class TFormatPolicy>
class TNumericArg : public BasicArg, public TFormatPolicy
{
public:
  TNumericArg( const T _v ) : v( _v ) {}

  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const
  {
    char fmt[64];
    const size_t fmtBufSize = sizeof(fmt) / sizeof(char);
    char * fmtEnd = fmt + fmtBufSize;

    char * ptr = FormatFormat( fmt, fmtBufSize, specs );

    ptr = SafeAppend( ptr, fmtEnd, this -> P_Fmt( specs.flags ) );
    if ( !ptr ) {
      buffer->WriteZ( "<arg>" );
      return;
    }
    
    char buf[256];
    int len =
#if defined( NV_WIN_PLATFORM )
      _snprintf( buf, 255, fmt, v );
#elif defined( NV_LINUX_PLATFORM )
      snprintf( buf, 255, fmt, v );
#endif
    buf[len] = 0;
    buffer->WriteZ( buf );
  }

  virtual bool AsInt( int & _intValue ) const { if ( this -> P_CanBeInt ) _intValue = this -> P_ToInt( v ); return this -> P_CanBeInt; }

private:
  const T v;
};




///// int & long /////
struct IntArgPolicy {
  static const char * P_Fmt( unsigned flags ) {
    if ( flags & EFlags::Hex ) return "x";
    if ( flags & EFlags::HEX ) return "X";
    return "d"; }
  static const bool P_CanBeInt = true;
  static int P_ToInt( int v ) { return v; }
};

template<>
struct TArg<int> : public TNumericArg<int, IntArgPolicy> {
  TArg( int _v ) : TNumericArg<int, IntArgPolicy>( _v ) {}
};

template<>
struct TArg<long> : public TNumericArg<int, IntArgPolicy> {
  TArg( long _v ) : TNumericArg<int, IntArgPolicy>( _v ) {}
};

///// unsigned int & long /////
struct UIntArgPolicy {
  static const char * P_Fmt( unsigned flags ) {
    if ( flags & EFlags::Hex ) return "x";
    if ( flags & EFlags::HEX ) return "X";
    return "u"; }
  static const bool P_CanBeInt = true;
  static int P_ToInt( unsigned v ) { return (int)v; }
};

template<>
struct TArg<unsigned> : public TNumericArg<unsigned, UIntArgPolicy> {
  TArg( unsigned _v ) : TNumericArg<unsigned, UIntArgPolicy>( _v ) {}
};

template<>
struct TArg<unsigned long> : public TNumericArg<unsigned, UIntArgPolicy> {
  TArg( unsigned long _v ) : TNumericArg<unsigned, UIntArgPolicy>( _v ) {}
};


///// signed 64-bit integers/////
template<typename T>
struct Signed64ArgPolicy {
  static const char * P_Fmt( unsigned flags ) {
    if ( flags & EFlags::Hex ) return "llx";
    if ( flags & EFlags::HEX ) return "llX";
    return "lld"; }
  static const bool P_CanBeInt = true;
  static int P_ToInt( T v ) { return (int)v; }
};

template<>
struct TArg<long long> : public TNumericArg<long long, Signed64ArgPolicy<long long> > {
  TArg( long long _v ) : TNumericArg<long long, Signed64ArgPolicy<long long> >( _v ) {}
};


///// unsigned 64-bit integers /////
template<typename T>
struct Unsigned64ArgPolicy {
  static const char * P_Fmt( unsigned flags ) {
    if ( flags & EFlags::Hex ) return "llx";
    if ( flags & EFlags::HEX ) return "llX";
    return "llu"; }
  static const bool P_CanBeInt = true;
  static int P_ToInt( T v ) { return (int)v; }
};

template<>
struct TArg<unsigned long long> : public TNumericArg<unsigned long long, Unsigned64ArgPolicy<unsigned long long> > {
  TArg( unsigned long long _v ) : TNumericArg<unsigned long long, Unsigned64ArgPolicy<unsigned long long> >( _v ) {}
};



///// signed 16-bit integers/////
struct ShortIntArgPolicy {
  static const char * P_Fmt( unsigned flags ) {
    if ( flags & EFlags::Hex ) return "hx";
    if ( flags & EFlags::HEX ) return "hX";
    return "hd"; }
  static const bool P_CanBeInt = true;
  static int P_ToInt( short v ) { return (int)v; }
};

template<>
struct TArg<short> : public TNumericArg<short, ShortIntArgPolicy> {
  TArg( short _v ) : TNumericArg<short, ShortIntArgPolicy>( _v ) {}
};


///// unsigned 16-bit integers /////
struct UShortIntArgPolicy {
  static const char * P_Fmt( unsigned flags ) {
    if ( flags & EFlags::Hex ) return "hx";
    if ( flags & EFlags::HEX ) return "hX";
    return "hu"; }
  static const bool P_CanBeInt = true;
  static int P_ToInt( unsigned short v ) { return (int)v; }
};

template<>
struct TArg<unsigned short> : public TNumericArg<unsigned short, UShortIntArgPolicy> {
  TArg( unsigned short _v ) : TNumericArg<unsigned short, UShortIntArgPolicy>( _v ) {}
};



///// char /////
struct CharArgPolicy {
  static const char * P_Fmt( unsigned flags ) { return "c"; }
  static const bool P_CanBeInt = false;
  static int P_ToInt( char v ) { return 0; }
};

template<>
struct TArg<char> : public TNumericArg<char, CharArgPolicy> {
  TArg( char _v ) : TNumericArg<char, CharArgPolicy>( _v ) {}
};



///// unsigned char /////
// NOTE: Non-printf behaviour, print unsigner char as unsigned int
template<>
struct TArg<unsigned char> : public TNumericArg<unsigned, UIntArgPolicy> {
  TArg( unsigned char _v ) : TNumericArg<unsigned, UIntArgPolicy>( (unsigned)_v ) {}
};


///// floats /////
template<class TFloatType>
struct FloatArgPolicy {
  static const char * P_Fmt( unsigned flags ) {
    if ( flags & EFlags::FloatG ) return "g";
    if ( flags & EFlags::FLOATG ) return "G";
    if ( flags & EFlags::Exp ) return "e";
    if ( flags & EFlags::EXP ) return "E";
    return "f"; }
  static const bool P_CanBeInt = false;
  static int P_ToInt( TFloatType v ) { return 0; }
};

template<>
struct TArg<float> : public TNumericArg<float, FloatArgPolicy<float> > {
  TArg( float _v ) : TNumericArg<float, FloatArgPolicy<float> >( _v ) {}
};

template<>
struct TArg<double> : public TNumericArg<double, FloatArgPolicy<double> > {
  TArg( double _v ) : TNumericArg<double, FloatArgPolicy<double> >( _v ) {}
};

template<>
struct TArg<long double> : public TNumericArg<long double, FloatArgPolicy<long double> > {
  TArg( long double _v ) : TNumericArg<long double, FloatArgPolicy<long double> >( _v ) {}
};


///// strings /////
template <class TChar>
class BasicStringArg : public BasicArg
{
public:
  BasicStringArg( const TChar * _s ) : str( _s ) {}

  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const { FormatString( buffer, str, specs ); }
  virtual bool AsInt( int & _intValue ) const { return false; }

private:
  const TChar * str;
};


template<>
struct TArg<const char *> : public BasicStringArg<char> {
  TArg( const char * _v ) : BasicStringArg<char>( _v ) {}
};

template<size_t N>
struct TArg<const char [N]> : public BasicStringArg<char> {
  TArg( const char * _v ) : BasicStringArg<char>( _v ) {}
};

template<>
struct TArg<char *> : public BasicStringArg<char> {
  TArg( const char * _v ) : BasicStringArg<char>( _v ) {}
};

template<size_t N>
struct TArg<char [N]> : public BasicStringArg<char> {
  TArg( const char * _v ) : BasicStringArg<char>( _v ) {}
};

template<>
struct TArg<const wchar_t *> : public BasicStringArg<wchar_t> {
  TArg( const wchar_t * _v ) : BasicStringArg<wchar_t>( _v ) {}
};

template<size_t N>
struct TArg<const wchar_t [N]> : public BasicStringArg<wchar_t> {
  TArg( const wchar_t * _v ) : BasicStringArg<wchar_t>( _v ) {}
};

template<>
struct TArg<wchar_t *> : public BasicStringArg<wchar_t> {
  TArg( const wchar_t * _v ) : BasicStringArg<wchar_t>( _v ) {}
};

template<size_t N>
struct TArg<wchar_t [N]> : public BasicStringArg<wchar_t> {
  TArg( const wchar_t * _v ) : BasicStringArg<wchar_t>( _v ) {}
};

// std::string and nstl::string support is in separate header files //



///// bool /////
template<>
class TArg<bool> : public BasicArg
{
public:
  TArg( bool _v ) : v( _v ) {}

  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const { FormatString( buffer, v ? "true" : "false", specs ); }

  virtual bool AsInt( int & _intValue ) const { return false; }

private:
  const bool v;
};


///// pointers /////
struct PointerPolicy {
  static const char * P_Fmt( unsigned flags ) { return "x"; }
  static const bool P_CanBeInt = false;
  static int P_ToInt( void * v ) { return 0; }
};

template<>
struct TArg<void *> : public TNumericArg<void *, PointerPolicy> {
  TArg( void * _v ) : TNumericArg<void *, PointerPolicy>( _v ) {}
};






///// STL containers /////
template<class TContaner, class TBracesPolicy, class TValueFormatPolicy>
class TContainerArg : public BasicArg, public TBracesPolicy, public TValueFormatPolicy
{
public:
  TContainerArg( const TContaner & c ) : C( c ) {}

  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const
  {
    buffer->WriteZ( TBracesPolicy::P_OpeningBrace() );
    int idx = 0;
    for ( typename TContaner::const_iterator i = C.begin(); i != C.end(); ++i, ++idx ) {
      if ( idx )
        buffer->WriteZ( ", " );
      if ( idx < 16 )
        TValueFormatPolicy::P_FormatArg( buffer, specs, i );
      else {
        buffer->WriteZ( "..." );
        break;
      }
    }
    buffer->WriteZ( TBracesPolicy::P_ClosingBrace() );
  }

  virtual bool AsInt( int & ) const { return false; }

private:
  const TContaner & C;
};


struct ContainerBracesPolicy_Brackets {
  static const char * P_OpeningBrace() { return "["; }
  static const char * P_ClosingBrace() { return "]"; }
};

struct ContainerBracesPolicy_Curly {
  static const char * P_OpeningBrace() { return "{"; }
  static const char * P_ClosingBrace() { return "}"; }
};



template<class TIter, class T>
struct TContainerValuePolicy_Single {
  static void P_FormatArg( IBuffer * buffer, const SFormatSpecs & specs, const TIter & iter ) {
    TArg<T> a( *iter );
    a.Format( buffer, specs );
  }
};

template<class TIter, class TFirst, class TSecond>
struct TContainerValuePolicy_Pair {
  static void P_FormatArg( IBuffer * buffer, const SFormatSpecs & specs, const TIter & iter ) {
    buffer->WriteZ( "(" );
    {
      TArg<TFirst> a( iter->first );
      a.Format( buffer, specs );
    }
    buffer->WriteZ( ", " );
    {
      TArg<TSecond> a( iter->second );
      a.Format( buffer, specs );
    }
    buffer->WriteZ( ")" );
  }
};




size_t FormatArray( IBuffer * buffer, const char * fmt, const IArg * const * args, size_t argsCount );


////// format class /////
template<class TBufferType, class TBufferAccessPolicy>
class PrintfFormatter : public TBufferAccessPolicy
{
public:
  PrintfFormatter()
  {}

  explicit PrintfFormatter( TBufferType _buffer ) :
  TBufferAccessPolicy( _buffer )
  {}

  inline void Trace( const char * fmt ) {
    TBufferType buffer = TBufferType();
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, 0, 0 );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0>
  inline void Trace( const char * fmt, const T0 & a0 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0);
    const IArg * args[] = { &t0 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0, class T1>
  inline void Trace( const char * fmt, const T0 & a0, const T1 & a1 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0); TArg<T1> t1(a1);
    const IArg * args[] = { &t0, &t1 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0, class T1, class T2>
  inline void Trace( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0); TArg<T1> t1(a1); TArg<T2> t2(a2);
    const IArg * args[] = { &t0, &t1, &t2 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0, class T1, class T2, class T3>
  inline void Trace( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0); TArg<T1> t1(a1); TArg<T2> t2(a2); TArg<T3> t3(a3);
    const IArg * args[] = { &t0, &t1, &t2, &t3 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0, class T1, class T2, class T3, class T4>
  inline void Trace( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0); TArg<T1> t1(a1); TArg<T2> t2(a2); TArg<T3> t3(a3); TArg<T4> t4(a4);
    const IArg * args[] = { &t0, &t1, &t2, &t3, &t4 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0, class T1, class T2, class T3, class T4, class T5>
  inline void Trace( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0); TArg<T1> t1(a1); TArg<T2> t2(a2); TArg<T3> t3(a3); TArg<T4> t4(a4); TArg<T5> t5(a5);
    const IArg * args[] = { &t0, &t1, &t2, &t3, &t4, &t5 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0, class T1, class T2, class T3, class T4, class T5, class T6>
  inline void Trace( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5, const T6 & a6 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0); TArg<T1> t1(a1); TArg<T2> t2(a2); TArg<T3> t3(a3); TArg<T4> t4(a4); TArg<T5> t5(a5); TArg<T6> t6(a6);
    const IArg * args[] = { &t0, &t1, &t2, &t3, &t4, &t5, &t6 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
  inline void Trace( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5, const T6 & a6, const T7 & a7 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0); TArg<T1> t1(a1); TArg<T2> t2(a2); TArg<T3> t3(a3); TArg<T4> t4(a4); TArg<T5> t5(a5); TArg<T6> t6(a6); TArg<T7> t7(a7);
    const IArg * args[] = { &t0, &t1, &t2, &t3, &t4, &t5, &t6, &t7 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
  inline void Trace( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5, const T6 & a6, const T7 & a7, const T8 & a8 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0); TArg<T1> t1(a1); TArg<T2> t2(a2); TArg<T3> t3(a3); TArg<T4> t4(a4); TArg<T5> t5(a5); TArg<T6> t6(a6); TArg<T7> t7(a7); TArg<T8> t8(a8);
    const IArg * args[] = { &t0, &t1, &t2, &t3, &t4, &t5, &t6, &t7, &t8 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }

  template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
  inline void Trace( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5, const T6 & a6, const T7 & a7, const T8 & a8, const T9 & a9 ) {
    TBufferType buffer;
    TBufferAccessPolicy::InitFormatBuffer( buffer );
    TArg<T0> t0(a0); TArg<T1> t1(a1); TArg<T2> t2(a2); TArg<T3> t3(a3); TArg<T4> t4(a4); TArg<T5> t5(a5); TArg<T6> t6(a6); TArg<T7> t7(a7); TArg<T8> t8(a8); TArg<T9> t9(a9);
    const IArg * args[] = { &t0, &t1, &t2, &t3, &t4, &t5, &t6, &t7, &t8, &t9 };
    FormatArray( TBufferAccessPolicy::ConvertBufferToPointer( buffer ), fmt, args, sizeof( args ) / sizeof( IArg * ) );
    TBufferAccessPolicy::OnFormatFinished( buffer );
  }
}; //class PrintfFormatter



class PrintfFormatterBufferPtrPolicy
{
protected:
  PrintfFormatterBufferPtrPolicy( text::IBuffer * _ptr ) : bufferPtr( _ptr ) {}
  PrintfFormatterBufferPtrPolicy() : bufferPtr( 0 ) {}
  void SetFormatBuffer( text::IBuffer * _ptr ) { bufferPtr = _ptr; }

  void InitFormatBuffer( text::IBuffer * & _ptr ) { _ptr = bufferPtr; }
  static inline text::IBuffer * ConvertBufferToPointer( text::IBuffer * _ptr ) { return _ptr; }
  void OnFormatFinished( text::IBuffer * _ptr ) {}

private:
  text::IBuffer * bufferPtr;
};



class PrintfFormatterBufferPtr : public PrintfFormatter<text::IBuffer *, PrintfFormatterBufferPtrPolicy>, public NonCopyable
{
public:
  explicit PrintfFormatterBufferPtr( text::IBuffer * _ref ) :
  PrintfFormatter<text::IBuffer *, PrintfFormatterBufferPtrPolicy>( _ref )
  {}

  PrintfFormatterBufferPtr()
  {}
};

} //namespace text

#endif //SYSTEM_SAFEPRINTF_H_INCLUDED
