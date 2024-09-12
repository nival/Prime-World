#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "SimpleParser.h"


namespace ETestEnum
{
  enum Enum
  {
    One, Another, OneMore, Last
  };
}


namespace ETestColors
{
  enum Enum
  {
    Red, Green, Blue
  };
}


namespace simple_parser
{

bool ParseSingleValue( ETestEnum::Enum & _val, const char * _text )
{
  if ( !_stricmp( _text, "one" ) )
    _val = ETestEnum::One;
  else if ( !_stricmp( _text, "another" ) )
    _val = ETestEnum::Another;
  else if ( !_stricmp( _text, "onemore" ) )
    _val = ETestEnum::OneMore;
  else if ( !_stricmp( _text, "last" ) )
    _val = ETestEnum::Last;
  else
    return false;

  return true;
}


bool ParseSingleValue( ETestColors::Enum & _val, const char * _text )
{
  if ( !_stricmp( _text, "red" ) )
    _val = ETestColors::Red;
  else if ( !_stricmp( _text, "green" ) )
    _val = ETestColors::Green;
  else if ( !_stricmp( _text, "blue" ) )
    _val = ETestColors::Blue;
  else
    return false;

  return true;
}

} //namespace simple_parser


template<class T>
std::set<T> & operator << ( std::set<T> & _set, const T & _v )
{
  _set.insert( _v );
  return _set;
}

struct SimpleParserTest : public CxxTest::TestSuite
{
  void test_set_int()
  {
    simple_parser::ValuesSet<int> vset;

    simple_parser::Context ctx( "{4, 33 , 55   ,100}" );
    TS_ASSERT( vset.Parse( ctx ) );

    std::set<int> ref;
    ref << 4 << 33 << 55 << 100;
    TS_ASSERT( ref == vset );
  }


  void test_set_int_simple()
  {
    simple_parser::ValuesSet<int> vset;

    simple_parser::Context ctx( "10" );
    TS_ASSERT( vset.Parse( ctx ) );

    std::set<int> ref;
    ref << 10;
    TS_ASSERT( ref == vset );
  }


  void test_set_int_empty()
  {
    simple_parser::ValuesSet<int> vset;
    simple_parser::Context ctx( "{}" );
    TS_ASSERT( vset.Parse( ctx ) );
    TS_ASSERT( vset.empty() );
  }


  void test_set_int_error_empty()
  {
    simple_parser::ValuesSet<int> vset;
    simple_parser::Context ctx( "" );
    TS_ASSERT( !vset.Parse( ctx ) );
    TS_ASSERT( ctx.errorPtr );
    TS_ASSERT_EQUALS( *ctx.errorPtr, 0 );
  }


  void test_set_int_error_no_closing()
  {
    simple_parser::ValuesSet<int> vset;
    const char * srcPtr = "{10 , ";
    simple_parser::Context ctx( srcPtr );
    TS_ASSERT( !vset.Parse( ctx ) );
    TS_ASSERT( ctx.errorPtr );
    TS_ASSERT( ( ctx.errorPtr - srcPtr ) >= 4 );
  }


  void test_set_int_error_wrong_separator()
  {
    simple_parser::ValuesSet<int> vset;
    const char * srcPtr = "{1 * 2}";
    simple_parser::Context ctx( srcPtr );
    TS_ASSERT( !vset.Parse( ctx ) );
    TS_ASSERT( ctx.errorPtr );
    TS_ASSERT( ctx.errorPtr - srcPtr >= 2 );
  }


  void test_set_int_error_no_separator()
  {
    simple_parser::ValuesSet<int> vset;
    const char * srcPtr = "{1 2}";
    simple_parser::Context ctx( srcPtr );
    TS_ASSERT( !vset.Parse( ctx ) );
    TS_ASSERT( ctx.errorPtr );
    TS_ASSERT( ctx.errorPtr - srcPtr >= 2 );
  }


  void test_enum_set()
  {
    simple_parser::Context ctx( "{ one, another ,last }" );
    simple_parser::ValuesSet<ETestEnum::Enum> vset;
    TS_ASSERT( vset.Parse( ctx ) );

    std::set<ETestEnum::Enum> ref;
    ref << ETestEnum::One << ETestEnum::Another << ETestEnum::Last;
    TS_ASSERT( ref == vset );
  }


  void test_enum_set_unknown()
  {
    simple_parser::Context ctx( "{ red, green,xxx }" );
    simple_parser::ValuesSet<ETestColors::Enum> vset;
    TS_ASSERT( !vset.Parse( ctx ) );
    TS_ASSERT( ctx.errorPtr );
    TS_ASSERT( !strncmp( ctx.errorPtr, "xxx", 3 ) );
  }


  void test_int_range()
  {
    simple_parser::ValuesRange<int> vrng;
    simple_parser::Context ctx( "[5, 10]" );
    TS_ASSERT( vrng.Parse( ctx ) );
    TS_ASSERT_EQUALS( vrng.valuesSet, 2 );
    TS_ASSERT_EQUALS( vrng.from, 5 );
    TS_ASSERT_EQUALS( vrng.to, 10 );
  }


  void test_int_range_point()
  {
    simple_parser::ValuesRange<int> vrng;
    simple_parser::Context ctx( "8" );
    TS_ASSERT( vrng.Parse( ctx ) );
    TS_ASSERT_EQUALS( vrng.valuesSet, 1 );
    TS_ASSERT_EQUALS( vrng.from, 8 );
    TS_ASSERT_EQUALS( vrng.to, 8 );
  }


  void test_int_range_error()
  {
    simple_parser::ValuesRange<int> vrng;
    simple_parser::Context ctx( "[8]" );
    TS_ASSERT( !vrng.Parse( ctx ) );
    TS_ASSERT( ctx.errorPtr );
    TS_ASSERT( !strncmp( ctx.errorPtr, "]", 1 ) );
  }


  void test_int_range_error_separator()
  {
    simple_parser::ValuesRange<int> vrng;
    simple_parser::Context ctx( "[8*10]" );
    TS_ASSERT( !vrng.Parse( ctx ) );
    TS_ASSERT( ctx.errorPtr );
    TS_ASSERT( !strncmp( ctx.errorPtr, "*10", 3 ) );
  }


  void test_float_range()
  {
    simple_parser::ValuesRange<float> vrng;
    simple_parser::Context ctx( "[ 3.14, 6.28 ]" );
    TS_ASSERT( vrng.Parse( ctx ) );
    TS_ASSERT_DELTA( vrng.from, 3.14f, 1e-3f );
    TS_ASSERT_DELTA( vrng.to, 6.28f, 1e-3f );
  }


  void test_double_range()
  {
    simple_parser::ValuesRange<double> vrng;
    simple_parser::Context ctx( "[ 1.5, 100.500 ]" );
    TS_ASSERT( vrng.Parse( ctx ) );
    TS_ASSERT_DELTA( vrng.from, 1.5, 1e-6 );
    TS_ASSERT_DELTA( vrng.to, 100.500, 1e-6 );
  }


  void test_string_vector()
  {
    simple_parser::ValuesVector<string> vec;
    simple_parser::Context ctx( "{ one, two, three }" );
    TS_ASSERT( vec.Parse( ctx ) );
    TS_ASSERT_EQUALS( vec.size(), 3 );
    TS_ASSERT_EQUALS( vec[0], "one" );
    TS_ASSERT_EQUALS( vec[1], "two" );
    TS_ASSERT_EQUALS( vec[2], "three" );
  }


  void test_string_vector_simple()
  {
    simple_parser::ValuesVector<string> vec;
    simple_parser::Context ctx( " oneword " );
    TS_ASSERT( vec.Parse( ctx ) );
    TS_ASSERT_EQUALS( vec.size(), 1 );
    TS_ASSERT_EQUALS( vec[0], "oneword" );
  }
};
