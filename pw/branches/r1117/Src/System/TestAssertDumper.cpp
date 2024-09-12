#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "TestAssertDumper.h"
#include "DebugTraceDumper.h"

namespace NLogg
{

static StrongMT<NLogg::TestAssertDumper> g_testassertDumper = new NLogg::TestAssertDumper( &GetSystemLog(), "Assert" );
static unsigned failLevelsFilter = 0xffffffff;
static StrongMT<NLogg::CDebugTraceDumper> g_debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );


TestAssertDumper::TestAssertDumper( CLogger *pDefaultLogger, const char *szName )
: CDumper( pDefaultLogger )
{
    AddLevel( NLogg::LEVEL_WARNING );
    AddLevel( NLogg::LEVEL_ERROR );
    AddLevel( NLogg::LEVEL_ASSERT );
    AddLevel( NLogg::LEVEL_CRITICAL );
}



void TestAssertDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  if ( failLevelsFilter & GetLevelMask( entryInfo.level ) )
  {
    nstl::string message( textOnly );
    _TS_FAIL( entryInfo.filename, entryInfo.line, message.c_str() );
  }
}



void FailTestOnAnyError( bool fail )
{
  FailTestOnLogLevel( LEVEL_WARNING,  fail );
  FailTestOnLogLevel( LEVEL_ERROR,    fail );
  FailTestOnLogLevel( LEVEL_ASSERT,   fail );
  FailTestOnLogLevel( LEVEL_CRITICAL, fail );
}



void FailTestOnLogLevel( ELevel level, bool fail )
{
  unsigned mask = GetLevelMask( level );
  if ( fail )
    failLevelsFilter |= mask;
  else
    failLevelsFilter &= ~mask;
}

}
