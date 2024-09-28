//!Component('StrUtils')
#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "StrProc.h"

class StrUtilsTest : public CxxTest::TestSuite
{
public:
  void test_url_encode_plain()
  {
    string encoded;
    NStr::UrlEncode( encoded, "Plain_text.0-9~", true, false );
    TS_ASSERT_EQUALS( encoded, "Plain_text.0-9~" );
  }

  void test_url_encode_space_perc()
  {
    string encoded;
    NStr::UrlEncode( encoded, "A B", false, false );
    TS_ASSERT_EQUALS( encoded, "A%20B" );
  }

  void test_url_encode_space_form()
  {
    string encoded;
    NStr::UrlEncode( encoded, "A B", true, false );
    TS_ASSERT_EQUALS( encoded, "A+B" );
  }

  void test_url_encode_soft()
  {
    string encoded;
    NStr::UrlEncode( encoded, "({\"soft_rules.are-cool*!\"})", true, true );
    TS_ASSERT_EQUALS( encoded, "({\"soft_rules.are-cool*!\"})" );
  }

  void test_url_encode_hard()
  {
    string encoded;
    NStr::UrlEncode( encoded, "({\"soft_rules.are-cool*!\"})", true, false );
    TS_ASSERT_EQUALS( encoded, "%28%7B%22soft_rules.are-cool%2A%21%22%7D%29" );
  }

  void test_decode_plain()
  {
    string decoded;
    NStr::UrlDecode( decoded, "Plain_text.0-9~", true );
    TS_ASSERT_EQUALS( decoded, "Plain_text.0-9~" );
  }


  void test_decode_space1()
  {
    string decoded;
    NStr::UrlDecode( decoded, "A%20B+", false );
    TS_ASSERT_EQUALS( decoded, "A B+" );
  }

  void test_decode_space2()
  {
    string decoded;
    NStr::UrlDecode( decoded, "A%20B+", true );
    TS_ASSERT_EQUALS( decoded, "A B " );
  }

  void test_decode()
  {
    string decoded;
    NStr::UrlDecode( decoded, "%28%7B%22soft_rules.are-cool%2A%21%22%7D%29", true );
    TS_ASSERT_EQUALS( decoded, "({\"soft_rules.are-cool*!\"})" );
  }
};
