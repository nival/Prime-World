#define _WIN32_WINNT 0x0502
#include "DllTestCollector.h"
#include <windows.h>
#include <vector>
#include <string>
using namespace std;
#include "ExportsCollector.h"
#include "LibraryGuard.h"
#include "../CxxTest/CxxTest.h"
#include "Log.h"
#include "ErrorFormatter.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef BOOL (*TSetDllDirectory)( LPCTSTR lpPathName );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace CxxTest
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CDllTestCollector::SetAdditionalDir( const char *szAdditionalDir )
{
	::SetDllDirectory( szAdditionalDir );
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CDllTestCollector::collect( GlobalFixtureList &globalFixtures, SuiteDescriptionList &suiteDescriptions )
{
	vector<string> functions;
	if ( !NExports::CollectFunctionsNames( &functions, szDllFile ) )
		return false;

	vector<string> suites;
	vector<string> fixtures;
	for ( vector<string>::const_iterator it = functions.begin(); it != functions.end(); ++it )
	{
		if ( it->find( CXX_REGISTER_GLOBAL_FIXTURE_FUNCTION ) == 0 )
			fixtures.push_back( *it );
		if ( it->find( CXX_REGISTER_TEST_SUITE_FUNCTION ) == 0 )
			suites.push_back( *it );
	}

	if ( suites.empty() )
	{
		log( LEVEL_CRITICAL ) << "No test suites found in library \"" << szDllFile << "\"" << endl;
		return false;
	}

	char currentDir[MAX_PATH];
	GetCurrentDirectory( MAX_PATH, currentDir );
	if ( !library.Create( szDllFile ) )
	{
		log( LEVEL_CRITICAL ) << "Cannot load library \"" << szDllFile << "\". " << NHelpers::GetLastError() << endl;
		return false;
	}

	for ( vector<string>::const_iterator it = fixtures.begin(); it != fixtures.end(); ++it )
	{
		TCxxRegisterGlobalFixtureFunc regFunc = (TCxxRegisterGlobalFixtureFunc)library.GetProcAddress( it->c_str() );
		if ( regFunc == 0 )
		{
			log( LEVEL_CRITICAL ) << "Invalid registration function \"" << it->c_str() << "\" in file \"" << szDllFile << "\"" << endl;
			return false;
		}
		(regFunc)( globalFixtures );
	}

	for ( vector<string>::const_iterator it = suites.begin(); it != suites.end(); ++it )
	{
		TCxxRegisterTestSuiteFunc regFunc = (TCxxRegisterTestSuiteFunc)library.GetProcAddress( it->c_str() );
		if ( regFunc == 0 )
		{
			log( LEVEL_CRITICAL ) << "Invalid registration function \"" << it->c_str() << "\" in file \"" << szDllFile << "\"" << endl;
			return false;
		}
		(regFunc)( globalFixtures, suiteDescriptions );
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDllTestCollector::clear()
{
	CTestCollector::clear();
	library.Clear();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CDllTestCollector::setUp()
{
	TCxxSetupTestListener setupTestListenerFunc = (TCxxSetupTestListener)library.GetProcAddress( CXX_SETUP_TEST_LISTENER_FUNCTION );
	if ( setupTestListenerFunc == 0 )
	{
		log( LEVEL_CRITICAL ) << "Cannot find function \"" << CXX_SETUP_TEST_LISTENER_FUNCTION << "\" in file \"" << szDllFile << "\"" << endl;
		return false;
	}

	TestTracker &tracker = TestTracker::tracker();
	(setupTestListenerFunc)( &tracker );

	return CTestCollector::setUp();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CDllTestCollector::tearDown()
{
	bool bResult = CTestCollector::tearDown();

	TCxxSetupTestListener setupTestListenerFunc = (TCxxSetupTestListener)library.GetProcAddress( CXX_SETUP_TEST_LISTENER_FUNCTION );
	if ( setupTestListenerFunc == 0 )
	{
		log( LEVEL_CRITICAL ) << "Cannot find function \"" << CXX_SETUP_TEST_LISTENER_FUNCTION << "\" in file \"" << szDllFile << "\"" << endl;
		return false;
	}

	(setupTestListenerFunc)( 0 );
	return bResult;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}