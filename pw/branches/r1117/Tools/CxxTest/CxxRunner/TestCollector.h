#pragma once

#include "../CxxTest/Descriptions.h"
#include "../CxxTest/GlobalFixture.h"
#include "TestTracker.h"
#include "LogListener.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace CxxTest
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTestCollector : WorldDescription
{
	GlobalFixtureList globalFixtures;
	SuiteDescriptionList suiteDescriptions;

	const SuiteDescription &suiteDescription( unsigned i ) const { return *(suiteDescriptions.nth( i ) ); }
	SuiteDescription *firstSuite() { return suiteDescriptions.firstSuiteDescription(); }
	const SuiteDescription *firstSuite() const { return suiteDescriptions.firstSuiteDescription(); }

	void runWorld();
	void runSuite( SuiteDescription &sd );
	void runTest( TestDescription &td );
protected:
	virtual bool setUp();
	virtual bool tearDown();

	virtual bool collect( GlobalFixtureList &globalFixtures, SuiteDescriptionList &suiteDescriptions ) { return true; }
	virtual void clear();
public:
	CTestCollector();

	bool initialize() { return collect(  globalFixtures, suiteDescriptions ); }

	void activateAllTests();
	bool leaveOnly( const char *szSuiteName, const char *szTestName );
	void run( const char* szFileName, const char *szWorldName );

	unsigned numSuites() const { return suiteDescriptions.size(); }
  unsigned numTotalTests() const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////