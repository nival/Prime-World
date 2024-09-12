//!Component("PF_GameLogic/TileMap")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestAssertDumper.h"

#include "TileMap.h"
struct TileMapTest : public CxxTest::TestSuite
{
  CObj<NWorld::TileMap> tileMap;

  virtual void setUp()
  {
    tileMap = new NWorld::TileMap();
  }

  virtual void tearDown()
  {
    tileMap = 0; 
  }

  void TestTileMapCreation()
  {
    tileMap->Prepare( 10, 12, 1.0f );
    TS_ASSERT_EQUALS( 10, tileMap->GetSizeX() );
    TS_ASSERT_EQUALS( 12, tileMap->GetSizeY() );
  }

  void TestTileMapInitialLocking()
  {
    tileMap->Prepare( 24, 24, 1.0f );
    tileMap->OnLoaded();

		for( int i = 0; i < 6; ++i )
		{
			TS_ASSERT_EQUALS( true, tileMap->CanUnitGo( i + 0, SVector( i, i ) ) );
			TS_ASSERT_EQUALS( true, tileMap->CanUnitGo( i + 0, SVector( 23 - i, i ) ) );
			TS_ASSERT_EQUALS( true, tileMap->CanUnitGo( i + 0, SVector( i, 23 - i ) ) );
			TS_ASSERT_EQUALS( true, tileMap->CanUnitGo( i + 0, SVector( 23 - i, 23 - i ) ) );

			/*TS_ASSERT_EQUALS( false, tileMap->CanUnitGo( i + 1, SVector( i, i ) ) );
			TS_ASSERT_EQUALS( false, tileMap->CanUnitGo( i + 1, SVector( 23 - i, i ) ) );
			TS_ASSERT_EQUALS( false, tileMap->CanUnitGo( i + 1, SVector( i, 23 - i ) ) );
			TS_ASSERT_EQUALS( false, tileMap->CanUnitGo( i + 1, SVector( 23 - i, 23 - i ) ) );*/
		}
  }

  void TestHugeTileMap()
  {
    tileMap->Prepare( 256, 130, 1.0f );
    tileMap->OnLoaded();
		TS_ASSERT_EQUALS( true, tileMap->CanUnitGo( 1, SVector( 128, 128 ) ) );
  }

  void TestTileMapMode()
  {
    tileMap->Prepare( 16, 16, 1.0f );
    for ( unsigned short i = 1; i < 16; i++ )
    {
      NWorld::MapModeChanger mode ( i, tileMap );
      TS_ASSERT_EQUALS( i, tileMap->GetMode() );
    }
  }
};
