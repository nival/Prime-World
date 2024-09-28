#pragma once
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "TestSuite.h"
#include "GlobalFixture.h"
#include "FullSuiteDescription.h"
#include "FullTestDescription.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma comment( lib, "CxxTest.lib" )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CXX_REGISTER_GLOBAL_FIXTURE_FUNCTION "__CxxRegisterGlobalFixture"
#define CXX_REGISTER_TEST_SUITE_FUNCTION "__CxxRegisterTestSuite"
#define CXX_SETUP_TEST_LISTENER_FUNCTION "__CxxSetupTestListener"
typedef void (*TCxxRegisterGlobalFixtureFunc)( CxxTest::GlobalFixtureList &globalFixtures );
typedef void (*TCxxRegisterTestSuiteFunc)( CxxTest::GlobalFixtureList &globalFixtures, CxxTest::SuiteDescriptionList &suiteDescriptions );
typedef void (*TCxxSetupTestListener)( CxxTest::TestListener *listener );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global Fixtures
#define CXX_REGISTER_GLOBAL_FIXTURE( fixtute_class )																																					\
extern "C" __declspec( dllexport ) void __CxxRegisterGlobalFixture##fixtute_class( CxxTest::GlobalFixtureList &globalFixtures )	\
{																																																															\
	CxxTest::GlobalFixture *pFixture = new fixtute_class();																																			\
	pFixture->attach( globalFixtures );																																													\
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CXX_SETUP_WORLD( unique_name )																																												\
class CSetupWorld##unique_name : public CxxTest::GlobalFixture																																\
{																																																															\
public:																																																												\
	bool setUpWorld();																																																					\
};																																																														\
CXX_REGISTER_GLOBAL_FIXTURE( CSetupWorld##unique_name );																																			\
bool CSetupWorld##unique_name::setUpWorld()
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CXX_TEAR_DOWN_WORLD( unique_name )																																										\
class CTearDownWorld##unique_name : public CxxTest::GlobalFixture																															\
{																																																															\
public:																																																												\
	bool tearDownWorld();																																																				\
};																																																														\
CXX_REGISTER_GLOBAL_FIXTURE( CTearDownWorld##unique_name );																																		\
bool CTearDownWorld##unique_name::tearDownWorld()
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Suites
#define CXX_REGISTER_TEST_SUITE( suite_class )																																								\
class CSuiteDescription##suite_class : public CxxTest::FullSuiteDescription<suite_class>																			\
{																																																															\
	typedef suite_class TSuiteClass;																																														\
protected:																																																										\
	void registerTests( CxxTest::List &argTests );																																							\
};																																																														\
extern "C" __declspec( dllexport ) void __CxxRegisterTestSuite##suite_class( CxxTest::GlobalFixtureList &globalFixtures,			\
	CxxTest::SuiteDescriptionList &suiteDescriptions )																																					\
{																																																															\
	CSuiteDescription##suite_class *pSuiteDescription = new CSuiteDescription##suite_class();																		\
	pSuiteDescription->initialize( __FILE__, __LINE__, #suite_class, globalFixtures );																						\
	pSuiteDescription->attach( suiteDescriptions );																																							\
}																																																															\
void CSuiteDescription##suite_class##::registerTests( CxxTest::List &argTests )
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tests
#define CXX_REGISTER_TEST_FUNCTION( func_name )																																								\
	new CxxTest::FullTestDescription<TSuiteClass>( argTests, *this, &TSuiteClass::##func_name##, __LINE__, #func_name )
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple test
#define CXX_TEST( unique_name )																																																\
class CTestSuite##unique_name : public CxxTest::TestSuite																																			\
{																																																															\
public:																																																												\
	void unique_name();																																																					\
};																																																														\
CXX_REGISTER_TEST_SUITE( CTestSuite##unique_name )																																						\
{																																																															\
	CXX_REGISTER_TEST_FUNCTION( unique_name );																																									\
}																																																															\
void CTestSuite##unique_name##::##unique_name##()
