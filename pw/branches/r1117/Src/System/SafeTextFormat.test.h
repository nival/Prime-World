//!Component("System/SafeTextFormat")
//!Component("System/Commands")

#include "stdafx.h"
#include "types.h"
#include "SafeTextFormatBuffers.h"
#include "SafeTextFormatEx.h"
#include "SafeTextFormatNstl.h"
#include "SafeTextFormatStl.h"
#include "cxxtest/TestSuite.h"

#pragma warning( disable : 4996) //This function or variable may be unsafe.


template <size_t N>
bool operator == ( const text::StaticBuffer<N> & buf, const char * str )
{
  return !strcmp( buf.c_str(), str );
}


class TestSafeFormat : public CxxTest::TestSuite
{
public:
  void test_std_sprintf()
  {
    int i = 357;

    {
      char buf[256] = "";
      sprintf( buf, "%d", i );
      TS_ASSERT( !strcmp( buf, "357" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%8d", i );
      TS_ASSERT( !strcmp( buf, "     357" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%8.4d", i );
      TS_ASSERT( !strcmp( buf, "    0357" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%l", i );
      TS_ASSERT( !strcmp( buf, "" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%ld", i );
      TS_ASSERT( !strcmp( buf, "357" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%.5d", i );
      TS_ASSERT( !strcmp( buf, "00357" ) );
    }
    {
      char buf[256] = "";
#if defined( NV_WIN_PLATFORM )
      sprintf( buf, "%llllllld", (long long)i );
#elif defined( NV_LINUX_PLATFORM )
      sprintf( buf, "%lld", (long long)i );
#endif
      TS_ASSERT( !strcmp( buf, "357" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "% + + i", i );
      TS_ASSERT( !strcmp( buf, "+357" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%   i", i );
      TS_ASSERT( !strcmp( buf, " 357" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%*i", 5, i );
      TS_ASSERT( !strcmp( buf, "  357" ) );
    }
    {
      char buf[256] = "";
#if defined( NV_WIN_PLATFORM )
      sprintf( buf, "%llI32lllI64lllli", (__int64)i );
#elif defined( NV_LINUX_PLATFORM )
      sprintf( buf, "%lld", (long long)i );
#endif
      TS_ASSERT( !strcmp( buf, "357" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%#x", i );
      TS_ASSERT( !strcmp( buf, "0x165" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%-+8i", i );
      TS_ASSERT( !strcmp( buf, "+357    " ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%8.3s", "test" );
      TS_ASSERT( !strcmp( buf, "     tes" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%-8.3s", "test" );
      TS_ASSERT( !strcmp( buf, "tes     " ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%2.4s", "testing" );
      TS_ASSERT( !strcmp( buf, "test" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%8.6s", "test" );
      TS_ASSERT( !strcmp( buf, "    test" ) );
    }
    {
      char buf[256] = "";
      sprintf( buf, "%08s", "test" );
#if defined( NV_WIN_PLATFORM )
      TS_ASSERT( !strcmp( buf, "0000test" ) );
#elif defined( NV_LINUX_PLATFORM )
      TS_ASSERT( !strcmp( buf, "    test" ) );
#endif
    }
    {
      char buf[256] = "";
      sprintf( buf, "Char: %c, UChar: %c", (char)'X', (unsigned char)'U' );
      TS_ASSERT( !strcmp( buf, "Char: X, UChar: U" ) );
    }
  }


  void check_16buffer( text::IBuffer & buffer ) {
    TS_ASSERT( buffer.SpaceLeft() == 15 );
    TS_ASSERT( buffer.Write( "1234", 4 ) == 4 );
    TS_ASSERT( buffer.SpaceLeft() == 11 );
    TS_ASSERT( buffer.Write( '!', 1 ) == 1 );
    TS_ASSERT( buffer.SpaceLeft() == 10 );

    TS_ASSERT( buffer.Write( '.', 1 ) == 1 );
    TS_ASSERT( buffer.SpaceLeft() == 9 );
    TS_ASSERT( buffer.Write( 'X', 0 ) == 0 );
    TS_ASSERT( buffer.SpaceLeft() == 9 );
    buffer.Finish();
    TS_ASSERT( !strcmp( buffer.c_str(), "1234!." ) );
  }

  void test_static_buffer_smoke() {
    text::StaticBuffer<16> buffer;
    check_16buffer( buffer );
  }

  void test_external_buffer_smoke() {
    char buf[16];
    text::ExternalBuffer buffer( buf, 16 );
    check_16buffer( buffer );
  }

  void begin_overflow_test( text::StaticBuffer<8> & buf ) {
    TS_ASSERT( buf.SpaceLeft() == 7 );
    TS_ASSERT( buf.Write( "12345", 5 ) == 5 );
    TS_ASSERT( buf.SpaceLeft() == 2 );
  }

  void test_static_buffer_overflow_by_write_char() {
    text::StaticBuffer<8> buf;
    begin_overflow_test( buf );
    TS_ASSERT( buf.Write( 'a', 1 ) == 1 );
    TS_ASSERT( buf.SpaceLeft() == 1 );
    TS_ASSERT( buf.Write( 'b', 1 ) == 1 );
    TS_ASSERT( buf.SpaceLeft() == 0 );
    TS_ASSERT( buf.Write( 'c', 1 ) == 0 );
    TS_ASSERT( buf.SpaceLeft() == 0 );
    buf.Finish();
    TS_ASSERT( memcmp( buf.c_str(), "12345ab", 8 ) == 0 );
  }

  void test_static_buffer_overflow_by_write_str() {
    text::StaticBuffer<8> buf;
    begin_overflow_test( buf );
    TS_ASSERT( buf.Write( "abcdef", 6 ) == 2 );
    TS_ASSERT( buf.SpaceLeft() == 0 );
    buf.Finish();
    TS_ASSERT( memcmp( buf.c_str(), "12345ab", 8 ) == 0 );
  }

  template <class TStlString>
  void check_stl_buffer( text::TStlBuffer<TStlString> & buffer ) {
    TS_ASSERT( buffer.Write( "1234", 4 ) == 4 );
    TS_ASSERT( buffer.Write( '!', 1 ) == 1 );

    TS_ASSERT( buffer.Write( '.', 1 ) == 1 );
    TS_ASSERT( buffer.Write( 'X', 0 ) == 0 );
    buffer.Finish();
    TS_ASSERT( !strcmp( buffer.c_str(), "1234!." ) );
  }

  void test_stl_buffer_nstl() {
    text::NstlBuffer buffer;
    check_stl_buffer( buffer );
  }

  void test_stl_buffer_std() {
    text::StlBuffer buffer;
    check_stl_buffer( buffer );
  }

  void test_format_arr_smoke()
  {
    text::StaticBuffer<16> buffer;

    text::TArg<int> arg1( 100500 );
    text::TArg<int> arg2( 5 );
    text::IArg *args[2] = { &arg1, &arg2 };

    text::FormatArray( &buffer, "abc%x - %d", args, 2 );
    TS_ASSERT_EQUALS( buffer, "abc18894 - 5" );
  }


  void test_empty() {
    text::StaticBuffer<8> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "" );
    TS_ASSERT_EQUALS( B.Length(), 0 );
    TS_ASSERT_EQUALS( B, "" );
  }

  void test_raw_text() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Quick brown fox jumped over the lazy dog" );
    TS_ASSERT_EQUALS( B.Length(), 40 );
    TS_ASSERT_EQUALS( B, "Quick brown fox jumped over the lazy dog" );
  }

  void test_precision_ints() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Integer: %.5d", 128 );
    TS_ASSERT_EQUALS( B, "Integer: 00128" );
  }

  void test_ints() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Integer: %d, Unsigned: %u", -500, 100 );
    TS_ASSERT_EQUALS( B, "Integer: -500, Unsigned: 100" );
  }

  void test_intsX() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Integer: %x, Unsigned: %x", -500, 100 );
    TS_ASSERT_EQUALS( B, "Integer: fffffe0c, Unsigned: 64" );
  }

  void test_longs() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Long: %i, ULong: %i", (long)-500, (long)100 );
    TS_ASSERT_EQUALS( B, "Long: -500, ULong: 100" );
  }

  void test_int32() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Signed: %i", static_cast< nival::int32_t >( -5 ) );
    TS_ASSERT_EQUALS( B, "Signed: -5" );
  }

  void test_chars() {
    text::StaticBuffer<32> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Char: %c, UChar: %c", (char)'X', (unsigned char)'U' );
    TS_ASSERT_EQUALS( B, "Char: X, UChar: 85" );
  }

  void test_int64() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    nival::int64_t i = -1024ll * 1024ll * 1024ll * 34ll;
    nival::uint64_t ui = 1024ull * 1024ull * 1024ull * 17ull;
    fmtr.Trace( "Signed: %i, Unsigned: %i", i, ui );
    TS_ASSERT_EQUALS( B, "Signed: -36507222016, Unsigned: 18253611008" );
  }

  void test_longlongs() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    long long i = -1024ll * 1024ll * 1024ll * 34ll;
    unsigned long long ui = 1024ull * 1024ull * 1024ull * 17ull;
    fmtr.Trace( "Signed: %i, Unsigned: %i", i, ui );
    TS_ASSERT_EQUALS( B, "Signed: -36507222016, Unsigned: 18253611008" );
  }

  void test_longlongsX() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    long long i = -1024ll * 1024ll * 1024ll * 34ll;
    unsigned long long ui = 1024ull * 1024ull * 1024ull * 17ull;
    fmtr.Trace( "Signed: %X, Unsigned: %x", i, ui );
    TS_ASSERT_EQUALS( B, "Signed: FFFFFFF780000000, Unsigned: 440000000" );
  }

  void test_shortints() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Signed: %i, Unsigned: %i", (short)-32768, (unsigned short)65535 );
    TS_ASSERT_EQUALS( B, "Signed: -32768, Unsigned: 65535" );
  }

  void test_shortintsX() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Signed: %x, Unsigned: %#X", (short)-32768, (unsigned short)65535 );
    TS_ASSERT_EQUALS( B, "Signed: 8000, Unsigned: 0XFFFF" );
  }

  void test_floats() {
    text::StaticBuffer<128> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Float: %f, Exp: %e, EXP: %E, g: %g, g2: %g, G: %G", 3.14f, 27.2, 27.2, 25.5, -15.0, -2000000.0 );
#if defined( NV_WIN_PLATFORM )
    TS_ASSERT_EQUALS( B, "Float: 3.140000, Exp: 2.720000e+001, EXP: 2.720000E+001, g: 25.5, g2: -15, G: -2E+006" );
#elif defined( NV_WIN_PLATFORM )
    TS_ASSERT_EQUALS( B, "Float: 3.140000, Exp: 2.720000e+01, EXP: 2.720000E+01, g: 25.5, g2: -15, G: -2E+06" );
#endif
  }

  void test_zstrings() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    const char * s1 = "Abc";
    char s2[] = "def";
    fmtr.Trace( "String: %s%s", s1, s2 );
    TS_ASSERT_EQUALS( B, "String: Abcdef" );
  }

  void test_zstrings_arr() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    char str[] = "Abcdef";
    fmtr.Trace( "String: %s", str );
    TS_ASSERT_EQUALS( B, "String: Abcdef" );
  }

  void test_nstl_string() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    nstl::string str( "NSTL SUXX" );
    fmtr.Trace( "String: %s", str );
    TS_ASSERT_EQUALS( B, "String: NSTL SUXX" );
  }

  void test_nstl_wstring() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    nstl::wstring str( L"NSTL SUXX wide" );
    fmtr.Trace( "String: %s", str );
    TS_ASSERT_EQUALS( B, "String: NSTL SUXX wide" );
  }

  void test_std_string() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    std::string str( "STD STL" );
    fmtr.Trace( "String: %s", str );
    TS_ASSERT_EQUALS( B, "String: STD STL" );
  }

  void test_std_wstring() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    std::wstring str( L"STD STL wide" );
    fmtr.Trace( "String: %s", str );
    TS_ASSERT_EQUALS( B, "String: STD STL wide" );
  }

  void test_string_width() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "String: (%8s)", "text" );
    TS_ASSERT_EQUALS( B, "String: (    text)" );
  }

  void test_string_left_align() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "String: (%-8s)", "text" );
    TS_ASSERT_EQUALS( B, "String: (text    )" );
  }

  void test_string_precision() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "String: (%.4s)", "long text" );
    TS_ASSERT_EQUALS( B, "String: (long)" );
  }

  void test_string_width_and_precision() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "String: (%-8.4s)", "long text" );
    TS_ASSERT_EQUALS( B, "String: (long    )" );
  }

  void test_string_funny_zero_padding() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "String: (%08s)", "zeroes" );
    TS_ASSERT_EQUALS( B, "String: (00zeroes)" );
  }

  void test_wstring() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Wide string: (%s)", L"Vasya pupkin" );
    TS_ASSERT_EQUALS( B, "Wide string: (Vasya pupkin)" );
  }

  void test_booleans() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Is this %i or %i?", true, false );
    TS_ASSERT_EQUALS( B, "Is this true or false?" );
  }

  void test_void_ptr() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Pointer: %i", (void *)0x00100500);
    TS_ASSERT_EQUALS( B, "Pointer: 100500" );
  }

  //void xtest_enum() {
  //  enum EnumType { One, Two, Three };
  //  text::StaticBuffer<32> B;
  //  text::PrintfFormatterBufferPtr fmtr( &B );
  //  EnumType e = Three;
  //  fmtr.Trace( "Enum: %i", e );
  //  TS_ASSERT_EQUALS( B, "Pointer: 2" );
  //}

  void test_arity()
  {
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int0: %d", 11 );
      TS_ASSERT_EQUALS( B, "int0: 11" );
    }
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int1: %d, flt2: %.1f", 11, 22.0f );
      TS_ASSERT_EQUALS( B, "int1: 11, flt2: 22.0" );
    }
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int1: %d, flt2: %.1f, str3: %s", 11, 22.0f, "33" );
      TS_ASSERT_EQUALS( B, "int1: 11, flt2: 22.0, str3: 33" );
    }
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int1: %d, flt2: %.1f, str3: %s, int4: %d", 11, 22.0f, "33", 44 );
      TS_ASSERT_EQUALS( B, "int1: 11, flt2: 22.0, str3: 33, int4: 44" );
    }
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int1: %d, flt2: %.1f, str3: %s, int4: %d, flt5: %.1f", 11, 22.0f, "33", 44, 55.0 );
      TS_ASSERT_EQUALS( B, "int1: 11, flt2: 22.0, str3: 33, int4: 44, flt5: 55.0" );
    }
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int1: %d, flt2: %.1f, str3: %s, int4: %d, flt5: %.1f, int6: %d", 11, 22.0f, "33", 44, 55.0, "66" );
      TS_ASSERT_EQUALS( B, "int1: 11, flt2: 22.0, str3: 33, int4: 44, flt5: 55.0, int6: 66" );
    }
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int1: %d, flt2: %.1f, str3: %s, int4: %d, flt5: %.1f, str6: %s, int7: %d", 11, 22.0f, "33", 44, 55.0, "66", 77 );
      TS_ASSERT_EQUALS( B, "int1: 11, flt2: 22.0, str3: 33, int4: 44, flt5: 55.0, str6: 66, int7: 77" );
    }
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int1: %d, flt2: %.1f, str3: %s, int4: %d, flt5: %.1f, str6: %s, int7: %d, flt8: %.1f", 11, 22.0f, "33", 44, 55.0, "66", 77, 88.0 );
      TS_ASSERT_EQUALS( B, "int1: 11, flt2: 22.0, str3: 33, int4: 44, flt5: 55.0, str6: 66, int7: 77, flt8: 88.0" );
    }
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int1: %d, flt2: %.1f, str3: %s, int4: %d, flt5: %.1f, str6: %s, int7: %d, flt8: %.1f, str9: %s", 11, 22.0f, "33", 44, 55.0, "66", 77, 88.0, "99" );
      TS_ASSERT_EQUALS( B, "int1: 11, flt2: 22.0, str3: 33, int4: 44, flt5: 55.0, str6: 66, int7: 77, flt8: 88.0, str9: 99" );
    }
    {
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "int1: %d, flt2: %.1f, str3: %s, int4: %d, flt5: %.1f, str6: %s, int7: %d, flt8: %.1f, str9: %s, int10: %i", 11, 22.0f, "33", 44, 55.0, "66", 77, 88.0, "99", 101 );
      TS_ASSERT_EQUALS( B, "int1: 11, flt2: 22.0, str3: 33, int4: 44, flt5: 55.0, str6: 66, int7: 77, flt8: 88.0, str9: 99, int10: 101" );
    }
  }

  void test_buffer_overflow()
  {
    { //overflow in plain text
      text::StaticBuffer<16> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "Value padding padding: %i", 100500 );
      TS_ASSERT_EQUALS( B.Length(), 15 );
      TS_ASSERT_EQUALS( B, "Value padding p" );
    }
    { // -overflow in numerical arg
      text::StaticBuffer<19> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "Value padding: %i", 100500 );
      TS_ASSERT_EQUALS( B.Length(), 18 );
      TS_ASSERT_EQUALS( B, "Value padding: 100" );
    }
    { // -overflow in string arg
      text::StaticBuffer<24> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      fmtr.Trace( "Value padding: %s", "0123456789abcdef" );
      TS_ASSERT_EQUALS( B.Length(), 23 );
      TS_ASSERT_EQUALS( B, "Value padding: 01234567" );
    }
  }

  void test_smoke() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Int1: %d, Integer2: %03i", 10, 8 );
    TS_ASSERT_EQUALS( B, "Int1: 10, Integer2: 008" );
  }

  void test_wrong_type() {
    text::StaticBuffer<64> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Value: (%lld)", "gotcha!" );
    TS_ASSERT_EQUALS( B, "Value: (gotcha!)" );
  }

  void test_fmt() {
    TS_ASSERT( !strcmp( NI_STRFMT( "Test text" ), "Test text" ) );
    TS_ASSERT( !strcmp( NI_STRFMT( "Test int: %i, test zero: %i", 3, 0 ), "Test int: 3, test zero: 0" ) );
  }

  void test_nstl_containers() {
    { //vector
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      nstl::vector<int> V; V.push_back( 10 ); V.push_back( 20 );
      fmtr.Trace( "Vector: %i", V );
      TS_ASSERT_EQUALS( B, "Vector: [10, 20]" );
    }
    { //map
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      nstl::map<nstl::string, unsigned> M; M["red"] = 0xff0000; M["green"] = 0x00ff00; M["blue"] = 0x0000ff;
      fmtr.Trace( "Map: %x", M );
      TS_ASSERT_EQUALS( B, "Map: {(blue, ff), (green, ff00), (red, ff0000)}" );
    }
    { //set
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      nstl::set<nstl::string> S; S.insert("one"); S.insert("two"); S.insert("four");
      fmtr.Trace( "Set: %x", S );
      TS_ASSERT_EQUALS( B, "Set: {four, one, two}" );
    }
    { //big vector
      text::StaticBuffer<1024> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      nstl::vector<int> V;
      for ( int i = 0; i < 1000; ++i ) V.push_back(i);
      fmtr.Trace( "Vector: %iend", V );
      TS_ASSERT_EQUALS( B, "Vector: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, ...]end" );
    }
  }


  void test_std_containers() {
    { //vector
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      std::vector<int> V; V.push_back( 10 ); V.push_back( 20 );
      fmtr.Trace( "Vector: %i", V );
      TS_ASSERT_EQUALS( B, "Vector: [10, 20]" );
    }
    { //map
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      std::map<nstl::string, unsigned> M; M["red"] = 0xff0000; M["green"] = 0x00ff00; M["blue"] = 0x0000ff;
      fmtr.Trace( "Map: %x", M );
      TS_ASSERT_EQUALS( B, "Map: {(blue, ff), (green, ff00), (red, ff0000)}" );
    }
    { //set
      text::StaticBuffer<256> B;
      text::PrintfFormatterBufferPtr fmtr( &B );
      std::set<nstl::string> S; S.insert("one"); S.insert("two"); S.insert("four");
      fmtr.Trace( "Set: %x", S );
      TS_ASSERT_EQUALS( B, "Set: {four, one, two}" );
    }
  }
  
  struct TestVal {
    nstl::string name;
    int amount;
    TestVal( const char * _name, int _amount ) : name( _name ), amount( _amount ) {}
    void Format( text::IBuffer * buffer, const text::SFormatSpecs & specs ) const {
      text::PrintfFormatterBufferPtr innerFmtr( buffer );
      innerFmtr.Trace( "(%s: %i)", name, amount ); }
  };

  void test_custom_object() {
    text::StaticBuffer<256> B;
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "from %i, %i to", TestVal( "Cabbage", 100500 ), TestVal( "Apple", 0 ) );
    TS_ASSERT_EQUALS( B, "from (Cabbage: 100500), (Apple: 0) to" );
  }
};
