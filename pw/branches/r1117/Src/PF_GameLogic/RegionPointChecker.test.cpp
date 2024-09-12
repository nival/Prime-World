//!Component("PF_GameLogic/RegionPointChecker")
//!Component('System/Dumpers')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestAssertDumper.h"
#include "System/DebugTraceDumper.h"

#include "RegionPointChecker.h"

struct RoutePathFinderTest : public CxxTest::TestSuite
{
  virtual void setUp()
  {
  }
  virtual void tearDown()
  {
  }

vector<SVector> CreateRegion( int x, int y, int width, int height )
{
  vector<SVector> result;
  result.reserve( width * height );

  for( int dx = 0; dx < width; ++dx )
  {
    for( int dy = 0; dy < height; ++dy )
    {
      result.push_back( SVector( x + dx, y + dy ) );
    }
  } 

  return result;
}

void TestTileInsideChecker()
{
  NWorld::RegionPointChecker checker( 0, CreateRegion( 10, 10, 10, 10 ), 2 );
  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 10, 10 ) ) );
  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 20, 10 ) ) );
  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 20, 20 ) ) );
  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 10, 20 ) ) );
}

void TestTileOutsideChecker()
{
  NWorld::RegionPointChecker checker( 0, CreateRegion( 10, 10, 10, 10 ), 2 );
  TS_ASSERT_EQUALS( false, checker.IsGoodTile( SVector( 5, 5 ) ) );
  TS_ASSERT_EQUALS( false, checker.IsGoodTile( SVector( 25, 5 ) ) );
  TS_ASSERT_EQUALS( false, checker.IsGoodTile( SVector( 25, 25 ) ) );
  TS_ASSERT_EQUALS( false, checker.IsGoodTile( SVector( 5, 25 ) ) );
  TS_ASSERT_EQUALS( false, checker.IsGoodTile( SVector( 10, 22 ) ) );
}

void TestTileInsideUnitRadius()
{
  NWorld::RegionPointChecker checker( 0, CreateRegion( 10, 10, 10, 10 ), 2 );
  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 9, 9 ) ) );
  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 20, 9 ) ) );
  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 20, 20 ) ) );
  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 9, 20 ) ) );
  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 10, 21 ) ) );
}

void TestRegionOnBounds()
{
  NWorld::RegionPointChecker checker( 0, CreateRegion( 1, 1, 10, 10 ), 3 );

  TS_ASSERT_EQUALS( true, checker.IsGoodTile( SVector( 1, 1 ) ) );
}

};