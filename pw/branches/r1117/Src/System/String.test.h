//!Component('NSTL')
#include "stdafx.h"
#include "cxxtest/TestSuite.h"

class StringFunctest : public CxxTest::TestSuite
{
public:
  void testCopyAndEqual()
  {
    nstl::string strl16 = "ttt";
    nstl::string strl162("ttt");
    nstl::string strl163 = strl162;

    TS_ASSERT_EQUALS(strl16, strl162);
    TS_ASSERT_EQUALS(strl163, strl162);

    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string str162("qwertyuiopasdfg");
    nstl::string str163 = str162;

    TS_ASSERT_EQUALS(str16, str162);
    TS_ASSERT_EQUALS(str163, str162);

    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";
    nstl::string strg162("qwertyuiopasdfghjklzxcvbnm");
    nstl::string strg163 = strg162;

    TS_ASSERT_EQUALS(strg16, strg162);
    TS_ASSERT_EQUALS(strg163, strg162);
  }

  void testSizeResizeCapacityAt()
  {
    nstl::string strl16 = "ttt";
    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";

    TS_ASSERT_EQUALS( strl16.size(), 3 );
    TS_ASSERT_EQUALS( str16.size(), 15 );
    TS_ASSERT_EQUALS( strg16.size(), 26 );

    TS_ASSERT_EQUALS( strl16[1], 't' );
    TS_ASSERT_EQUALS( str16[14], 'g' );
    TS_ASSERT_EQUALS( strg16[23], 'b' );

    strl16.resize(1);
    str16.resize(1);
    strg16.resize(1);

    TS_ASSERT_EQUALS( strl16.size(), 1 );
    TS_ASSERT_EQUALS( str16.size(), 1 );
    TS_ASSERT_EQUALS( strg16.size(), 1 );

    TS_ASSERT_EQUALS( strl16[0], 't' );
    TS_ASSERT_EQUALS( str16[0], 'q' );
    TS_ASSERT_EQUALS( strg16[0], 'q' );

    TS_ASSERT_EQUALS( strl16.capacity(), 15 );
    TS_ASSERT_EQUALS( str16.capacity(), 15 );
    TS_ASSERT_EQUALS( strg16.capacity(), 26 );

    strl16.reserve( 8 );
    str16.reserve( 17 );
    strg16.reserve( 33 );

    TS_ASSERT_EQUALS( strl16.capacity(), 15 );
    TS_ASSERT_EQUALS( str16.capacity(), 17 );
    TS_ASSERT_EQUALS( strg16.capacity(), 33 );
  }

  void testAppend()
  {
    nstl::string strl16 = "ttt";
    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";

    strl16 += 'a';
    str16 += 'a';
    strg16 += 'a';

    TS_ASSERT_EQUALS( strl16[3], 'a' );
    TS_ASSERT_EQUALS( str16[15], 'a' );
    TS_ASSERT_EQUALS( strg16[26], 'a' );

    strl16 += "qwerty";
    str16 += "qwerty";
    strg16 += "qwerty";

    TS_ASSERT_EQUALS( strl16[5], 'w' );
    TS_ASSERT_EQUALS( str16[17], 'w' );
    TS_ASSERT_EQUALS( strg16[28], 'w' );

    nstl::string temp = "temp";

    strl16 += temp;
    str16 += temp;
    strg16 += temp;

    TS_ASSERT_EQUALS( strl16[11], 'e' );
    TS_ASSERT_EQUALS( str16[23], 'e' );
    TS_ASSERT_EQUALS( strg16[34], 'e' );
  }

  void testInsert()
  {
    nstl::string strl16 = "ttt";
    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";

    const char* ch_g = "g";

    strl16.insert( 2, ch_g );
    str16.insert( 2, ch_g );
    strg16.insert( 2, ch_g );

    TS_ASSERT_EQUALS( strl16[2], 'g' );
    TS_ASSERT_EQUALS( str16[2], 'g' );
    TS_ASSERT_EQUALS( strg16[2], 'g' );

    strl16.insert( strl16.begin()+1, 'm' );
    str16.insert( str16.begin()+1, 'm' );
    strg16.insert( strg16.begin()+1, 'm' );

    TS_ASSERT_EQUALS( strl16[1], 'm' );
    TS_ASSERT_EQUALS( str16[1], 'm' );
    TS_ASSERT_EQUALS( strg16[1], 'm' );
  }

  void testErase()
  {
    nstl::string strl16 = "ttt";
    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";

    strl16.erase( 1, 2 );
    str16.erase( 1, 2 );
    strg16.erase( 1, 2 );

    TS_ASSERT_EQUALS( strl16, nstl::string("t") );
    TS_ASSERT_EQUALS( str16, nstl::string("qrtyuiopasdfg") );
    TS_ASSERT_EQUALS( strg16, nstl::string("qrtyuiopasdfghjklzxcvbnm") );
  }

  void testReplace()
  {
    nstl::string strl16 = "ttt";
    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";
    
    char temp[4] = "omg";

    strl16.replace( 1, 2, temp );
    str16.replace( 1, 2, temp );
    strg16.replace( 1, 2, temp );

    TS_ASSERT_EQUALS( strl16, nstl::string("tomg") );
    TS_ASSERT_EQUALS( str16, nstl::string("qomgrtyuiopasdfg") );
    TS_ASSERT_EQUALS( strg16, nstl::string("qomgrtyuiopasdfghjklzxcvbnm") );
  }

  void testSwap()
  {
    nstl::string strl16 = "ttt";
    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";

    strl16.swap( str16 );
    str16.swap( strg16 );
    
    TS_ASSERT_EQUALS( strl16, nstl::string("qwertyuiopasdfg") );
    TS_ASSERT_EQUALS( str16, nstl::string("qwertyuiopasdfghjklzxcvbnm") );
    TS_ASSERT_EQUALS( strg16, nstl::string("ttt") );
  }

  void testCStr()
  {
    nstl::string strl16 = "ttt";
    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";

    TS_ASSERT_EQUALS( strcmp( strl16.c_str(), "ttt"), 0 );
    TS_ASSERT_EQUALS( strcmp( str16.c_str(), "qwertyuiopasdfg"), 0 );
    TS_ASSERT_EQUALS( strcmp( strg16.c_str(), "qwertyuiopasdfghjklzxcvbnm"), 0 );
  }

  void testFind()
  {
    nstl::string strl16 = "ttt";
    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";

    TS_ASSERT_EQUALS( strl16.find( 't', 1 ), 1 );
    TS_ASSERT_EQUALS( str16.find( 't', 2 ), 4 );
    TS_ASSERT_EQUALS( strg16.find( 't', 2 ), 4 );

    TS_ASSERT_EQUALS( strl16.find_last_of( 'n', nstl::string::npos ), nstl::string::npos );
    TS_ASSERT_EQUALS( str16.find_last_of( 'n', nstl::string::npos ), nstl::string::npos );
    TS_ASSERT_EQUALS( strg16.find_last_of( 'n', nstl::string::npos ), 24 );
  }

  void testSubStrAndCompare()
  {
    nstl::string strl16 = "ttt";
    nstl::string str16 = "qwertyuiopasdfg";
    nstl::string strg16 = "qwertyuiopasdfghjklzxcvbnm";

    nstl::string ss1 = strl16.substr( 1, 1 );
    nstl::string ss2 = str16.substr( 6, 2 );
    nstl::string ss3 = strg16.substr( 6, 2 );

    nstl::string ssc1 = "t";
    nstl::string ssc2 = "ui";
    nstl::string ssc3 = "ui";

    TS_ASSERT_EQUALS( ss1.compare( ssc1 ), 0 );
    TS_ASSERT_EQUALS( ss2.compare( ssc2 ), 0 );
    TS_ASSERT_EQUALS( ss3.compare( ssc3 ), 0 );
  }

  void test_swap_for_short_string()
  {
    string dest;
    {
      string * src = new string( "Red fox" );
      dest.swap( *src );

      //HACK to ensure 'src' memory cleanup
      src->~string();
      memset( src, 0, sizeof( string ) );
      //delete (void*)src;
      delete src;
    }
    TS_ASSERT_EQUALS( dest, "Red fox" );
  }
};


