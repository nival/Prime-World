#include "TestCollector.h"
#include "Exceptions.h"
#include "SymAccess.h"
#include "LogListener.h"
#include "XmlListener.h"
#include <eh.h>
#include "../CxxTest/ValueTraits.h"
#include "../CxxTest/TestSuite.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static NHelpers::SCallStackEntry entries[64];
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int CollectCallStack( struct _EXCEPTION_POINTERS *pExPtrs )
{
	NHelpers::CollectCallStack( entries, 64, pExPtrs );
	return EXCEPTION_EXECUTE_HANDLER;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace CxxTest
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CTestCollector::CTestCollector()
{
	globalFixtures.initialize();
	suiteDescriptions.initialize();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestCollector::activateAllTests()
{
	for ( SuiteDescription *sd = suiteDescriptions.firstSuiteDescription(); sd != 0; sd = sd->next() )
	{
		sd->activateAllTests();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTestCollector::leaveOnly( const char *szSuiteName, const char *szTestName )
{
	bool bResult = false;
	for ( SuiteDescription *sd = suiteDescriptions.firstSuiteDescription(); sd != 0; sd = sd->next() )
	{
		if ( !stringsEqual( sd->suiteName(), szSuiteName ) )
			sd->setActive( false );
		else
		{
			sd->setActive( true );
			if ( szTestName != 0 )
				bResult = sd->leaveOnly( szTestName );
			else
			{
				sd->activateAllTests();
				bResult = true;
			}
		}
	}

	return bResult;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned CTestCollector::numTotalTests() const
{
	unsigned nResult = 0;
	for ( const SuiteDescription *sd = suiteDescriptions.firstSuiteDescription(); sd != 0; sd = sd->next() )
		nResult += sd->numTests();

	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTestCollector::setUp()
{
	for ( GlobalFixture *gf = globalFixtures.firstGlobalFixture(); gf != 0; gf = gf->nextGlobalFixture() )
	{
		__try
		{
			if ( !gf->setUpWorld() )
				return false;
		}
		__except( CollectCallStack( GetExceptionInformation() ) )
		{
			TestTracker::tracker().failedTest( entries[0].szFile.c_str(), entries[0].nLine, NHelpers::ExceptionCodeToString( GetExceptionCode() ) );
			return false;
		}
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTestCollector::tearDown()
{
	bool ok = true;
	for ( GlobalFixture *gf = globalFixtures.lastGlobalFixture(); gf != 0; gf = gf->prevGlobalFixture() )
	{
		__try
		{
			ok &= gf->tearDownWorld();
		}
		__except( CollectCallStack( GetExceptionInformation() ) )
		{
			TestTracker::tracker().failedTest( entries[0].szFile.c_str(), entries[0].nLine, NHelpers::ExceptionCodeToString( GetExceptionCode() ) );
			ok = false;
		}
	}
	return ok;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestCollector::clear()
{
	for ( GlobalFixture *gf = globalFixtures.firstGlobalFixture(); gf != 0; )
	{
		GlobalFixture *pTemp = gf;
		gf = gf->nextGlobalFixture();
		delete pTemp;
	}

	for ( SuiteDescription *sd = suiteDescriptions.firstSuiteDescription(); sd != 0; )
	{
		SuiteDescription *pTemp = sd;
		sd = sd->next();
		delete pTemp;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestCollector::runTest( TestDescription &td )
{
	TestTracker::tracker().enterTest( td );
	if ( td.setUp() )
	{
		__try
		{
			td.run();
		}
		__except( CollectCallStack( GetExceptionInformation() ) )
		{
			TestTracker::tracker().failedTest( entries[0].szFile.c_str(), entries[0].nLine, NHelpers::ExceptionCodeToString( GetExceptionCode() ) );
		}
		td.tearDown();
	}
	
	TestTracker::tracker().leaveTest( td );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestCollector::runSuite( SuiteDescription &sd )
{
	TestTracker::tracker().enterSuite( sd );
	if ( sd.setUp() )
	{
		for ( TestDescription *td = sd.firstTest(); td != 0; td = td->next() )
		{
			if ( td->active() )
				runTest( *td );
		}
		sd.tearDown();
	}
	
	TestTracker::tracker().leaveSuite( sd );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestCollector::runWorld()
{
	TestTracker::tracker().enterWorld( *this );
	if ( setUp() )
	{
		for ( SuiteDescription *sd = suiteDescriptions.firstSuiteDescription(); sd != 0; sd = sd->next() )
		{
			if ( sd->active() )
				runSuite( *sd );
		}
		tearDown();
	}
	
	TestTracker::tracker().leaveWorld( *this );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestCollector::run( const char* szFileName, const char *szWorldName )
{
	CxxTest::TestListener* pListener = 0;
	if ( szFileName == 0 || szFileName[0] == 0 )
		pListener = new CLogListener();
	else
		pListener = new CXmlListener( szFileName, szWorldName );

	TestTracker::tracker().setListener( pListener );
	runWorld();
	TestTracker::tracker().setListener( 0 );

	delete pListener;
	clear();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}