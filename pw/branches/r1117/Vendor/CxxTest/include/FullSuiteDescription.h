#pragma once

#include "RealDescriptions.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace CxxTest
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class S>
class FullSuiteDescription : public RealSuiteDescription
{
	S *_suite;
	List _tests;
	GlobalFixtureList *_globalFixtures;
	
	void setSuite( S *s ) { _suite = s; }
	
	void createSuite()
	{
		setSuite( new S() );
	}
	
	void destroySuite()
	{
		S *s = realSuite();
		setSuite( 0 );
		delete s;
	}
protected:
	virtual void registerTests( List &argTests ) = 0;
public:
	FullSuiteDescription() : RealSuiteDescription() {}
	~FullSuiteDescription()
	{
		for ( Link *link = _tests.head(); link != 0; )
		{
			Link *temp = link;
			link = link->next();
			delete temp;
		}
	}
	
	void initialize( const char *argFile, unsigned argLine, const char *argSuiteName, GlobalFixtureList &argGlobalFixtures )
	{
		_globalFixtures = &argGlobalFixtures;
		_tests.initialize();
		registerTests( _tests );
		RealSuiteDescription::initialize( argFile, argLine, argSuiteName, _tests );
	}

	S *realSuite() const { return _suite; }
	TestSuite *suite() const { return realSuite(); }
	
	bool setUp()
	{
		_TS_TRY {
			_TSM_ASSERT_THROWS_NOTHING( file(), line(), "Exception thrown from createSuite()", createSuite() );
			_TSM_ASSERT( file(), line(), "createSuite() failed", suite() != 0 );
		}
		_TS_CATCH_ABORT( { return false; } );
		
		if ( suite() == 0 )
			return false;

		return suite()->setUpSuite();
	}
	
	bool tearDown()
	{
		if ( !_suite )
			return true;

		bool ok = suite()->tearDownSuite();
		    
		_TS_TRY {
			_TSM_ASSERT_THROWS_NOTHING( file(), line(), "destroySuite() failed", destroySuite() );
		}
		_TS_CATCH_ABORT( { ok = false; } );

		return ok;
	}
	
  bool setUpGlobalFixtures()
  {
		for ( GlobalFixture *gf = _globalFixtures->firstGlobalFixture(); gf != 0; gf = gf->nextGlobalFixture() )
		{
			bool ok;
			_TS_TRY { ok = gf->setUp(); }
			_TS_LAST_CATCH( { ok = false; } );

			if ( !ok )
			{
				doFailTest( file(), line(), "Error in GlobalFixture::setUp()" );
				return false;
			}
		}

		return true;
	}
  
  bool tearDownGlobalFixtures()
  {
		for ( GlobalFixture *gf = _globalFixtures->lastGlobalFixture(); gf != 0; gf = gf->prevGlobalFixture() )
		{
			bool ok;
			_TS_TRY { ok = gf->tearDown(); }
			_TS_LAST_CATCH( { ok = false; } );

			if ( !ok )
			{
				doFailTest( file(), line(), "Error in GlobalFixture::tearDown()" );
				return false;
			}
		}

		return true;
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

