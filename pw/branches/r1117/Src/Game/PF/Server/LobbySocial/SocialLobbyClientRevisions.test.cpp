//!Component("System/Pointers")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "SocialLobbyClientRevisions.h"


struct Test_SocialLobbyClientRevisions : public CxxTest::TestSuite
{
  void test_empty()
  {
    StrongMT<socialLobby::ClientRevisions> test = new socialLobby::ClientRevisions( "" );
    TS_ASSERT_EQUALS( test->Map(1), 1 );
  }


  void test_smoke()
  {
    StrongMT<socialLobby::ClientRevisions> test = new socialLobby::ClientRevisions( "10 20 33" );
    TS_ASSERT_EQUALS( test->Map(1), 1 );
    TS_ASSERT_EQUALS( test->Map(10), 10 );
    TS_ASSERT_EQUALS( test->Map(20), 10 );
    TS_ASSERT_EQUALS( test->Map(33), 10 );
  }
};
