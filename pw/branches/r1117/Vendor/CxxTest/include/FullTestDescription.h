#pragma once

#include "RealDescriptions.h"
#include "FullSuiteDescription.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace CxxTest
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class S>
class FullTestDescription : public RealTestDescription
{
	typedef void (S::*TTestFunc)();
	const FullSuiteDescription<S> &_suite;
	TTestFunc _func;
private:
	void runTest()
	{
		if ( _suite.realSuite() && _func )
			(_suite.realSuite()->*(_func))();
	}
public:
	FullTestDescription( List &argList, FullSuiteDescription<S> &argSuite, TTestFunc argFunc, unsigned argLine, const char *argTestName )
		: RealTestDescription( argList, argSuite, argLine, argTestName ), _suite( argSuite ), _func( argFunc ) {}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

