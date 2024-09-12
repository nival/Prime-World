//!Component("System/Commands")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "Commands.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TestCall
{
public:
  TestCall() : method1Called(false), method2Called(false), method3Called(false) {};
  virtual ~TestCall() {};

  bool Method1( const char *name, const vector<wstring> &args )
  {
    if ( args.size() < 2 )
      return true;
    
    method1Called = ( args[1] == L"testA" );

    return true;
  }

  bool Method2( const char *name, const vector<wstring> &args )
  {
    if ( args.size() < 2 )
      return true;

    method2Called = ( args[1] == L"testB" );

    return true;
  }

  bool Method3( const char *name, const vector<wstring> &args )
  {
    if ( args.size() < 2 )
      return true;

    method3Called = ( args[1] == L"testC" );

    return true;
  }

  bool Method1Called() const { return method1Called; }
  bool Method2Called() const { return method2Called; }
  bool Method3Called() const { return method3Called; }

private:

  bool method1Called;
  bool method2Called;
  bool method3Called;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ContextCommandTest : public CxxTest::TestSuite 
{
public:

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void testContextCommand()
	{
    TestCall testCall;

    NGlobal::RegisterContextCmd( "test_method1", &testCall, &TestCall::Method1 );
    NGlobal::RegisterContextCmd( "test_method2", &testCall, &TestCall::Method2 );
    NGlobal::RegisterContextCmd( "test_method3", &testCall, &TestCall::Method3 );

    TS_ASSERT( NGlobal::IsCommandRegistred( "test_method1" ) );
    TS_ASSERT( NGlobal::IsCommandRegistred( "test_method2" ) );
    TS_ASSERT( NGlobal::IsCommandRegistred( "test_method3" ) );

    NGlobal::RunCommand( L"test_method1 A testA" );
    NGlobal::RunCommand( L"test_method2 A testB" );
    NGlobal::RunCommand( L"test_method3 A testC" );

    TS_ASSERT( testCall.Method1Called() );
    TS_ASSERT( testCall.Method2Called() );
    TS_ASSERT( testCall.Method3Called() );

    NGlobal::UnregisterCmd( "test_method1" );
    NGlobal::UnregisterCmd( "test_method2" );
    NGlobal::UnregisterCmd( "test_method3" );

    TS_ASSERT_EQUALS( NGlobal::IsCommandRegistred( "test_method1" ), false );
    TS_ASSERT_EQUALS( NGlobal::IsCommandRegistred( "test_method2" ), false );
    TS_ASSERT_EQUALS( NGlobal::IsCommandRegistred( "test_method3" ), false );
  }
};
