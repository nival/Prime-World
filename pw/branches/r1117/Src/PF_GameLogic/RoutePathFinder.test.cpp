//!Component("PF_GameLogic/RoutePathFinder")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestAssertDumper.h"

#include "TileMap.h"
#include "CommonPathFinder.h"
#include "RoutePathFinder.h"
#include "System/Bresenham.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<SVector> CreateRoute( const SVector& p1, const SVector& p2 )
{
  vector<SVector> result;
  result.push_back( p1 );
  result.push_back( p2 );
  
  return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<SVector> CreateRoute( const SVector& p1, const SVector& p2, const SVector& p3 )
{
  vector<SVector> result;
  result.push_back( p1 );
  result.push_back( p2 );
  result.push_back( p3 );
  
  return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<SVector> CreateRoute( const SVector& p1, const SVector& p2, const SVector& p3, const SVector& p4 )
{
  vector<SVector> result;
  result.push_back( p1 );
  result.push_back( p2 );
  result.push_back( p3 );
  result.push_back( p4 );
  
  return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<SVector> CreateRoute( const SVector& p1, const SVector& p2, const SVector& p3, const SVector& p4, const SVector& p5, const SVector& p6 )
{
  vector<SVector> result;
  result.push_back( p1 );
  result.push_back( p2 );
  result.push_back( p3 );
  result.push_back( p4 );
  result.push_back( p5 );
  result.push_back( p6 );
  
  return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComparePath( const vector<SVector>& path, const vector<SVector>& route )
{
  CBres b;
  int index = 0;
  
  for( int i = 0; i < route.size() - 1; ++i )
  {
    b.InitPoint( route[i], route[i + 1] );
    while ( b.GetDirection() != route[i + 1] && index < path.size() )
    {
      TS_ASSERT_EQUALS( b.GetDirection(), path[index] );
      b.MakePointStep();
      ++index;
    }
  }
  if ( index < path.size() )
  {
    TS_ASSERT_EQUALS( b.GetDirection(), path[index] );
    ++index;
  }
  TS_ASSERT_EQUALS( path.size(), index );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlaceObstacle2( NWorld::TileMap* tileMap, int x, int y, int width, int height )
{
  vector<SVector> mask;
	for( int dx = 0; dx < width; ++dx )
	{
		for( int dy = 0; dy < height; ++dy )
      mask.push_back( SVector( x + dx, y + dy ) );
	}
	Placement place( CVec3( x, y, 0 ), QNULL, CVec3( 1, 1, 1 ) );
	tileMap->MarkObject( mask, true, NWorld::MAP_MODE_STATIC );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct RoutePathFinderTest2 : public CxxTest::TestSuite
{
  CObj<NWorld::TileMap> tileMap;
  CObj<Pathfinding::CCommonPathFinder> commonPathfinder;
  CObj<Pathfinding::RoutePathFinder> routePathfinder;

  virtual void setUp()
  {
    tileMap = new NWorld::TileMap();
    tileMap->Prepare( 200, 50, 1.0f );
    tileMap->OnLoaded();
    commonPathfinder = new Pathfinding::CCommonPathFinder( tileMap );
    routePathfinder = new Pathfinding::RoutePathFinder(commonPathfinder);
  }

  virtual void tearDown()
  {
    routePathfinder = 0;
    commonPathfinder = 0;
    tileMap = 0; 
  }

  //  * Start
  //   
  //  *
  //  |
  //  |
  //  *----*   * Finish
  void TestSimplePathFinding()
  {
    routePathfinder->AddRoute(  CreateRoute( SVector( 10, 10 ), SVector( 10, 20 ), SVector( 20, 20 ) ), 1 );
    
		TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath(  SVector( 10, 5 ), SVector( 25, 20 ), 2, 1 ) );
    ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 10, 5 ), SVector( 10, 20 ), SVector( 25, 20 ) ) );
  }

  //    * Start
  //  *----*----*    * Finish
  void TestPerpendicularPathfinding()
  {
    routePathfinder->AddRoute( CreateRoute( SVector( 10, 10 ), SVector( 20, 10 ), SVector( 30, 10 ) ), 1 );

    TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath( SVector( 12, 8 ), SVector( 40, 10 ), 2, 1 ) );
    //in this case we cut a corner here so 15,10 is a mid point
    ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 12, 8 ), SVector( 15, 10 ), SVector( 40, 10 ) ) );
  }

  //  Start
  //  *    *----*----*
  //               * Finish
  void TestPerpendicularPathfindingAtFinish()
  {
    routePathfinder->AddRoute( CreateRoute( SVector( 10, 10 ), SVector( 20, 10 ), SVector( 30, 10 ) ), 1 );

    TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath(  SVector( 5, 10 ), SVector( 28, 14 ), 2, 1 ) );
    ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 5, 10 ), SVector( 22, 10 ), SVector( 28, 14 ) ) );
  }

  //  Start
  //  *----*----*    * Finish
  void TestStartOnRoute()
  {
    routePathfinder->AddRoute( CreateRoute( SVector( 10, 10 ), SVector( 20, 10 ), SVector( 30, 10 ) ), 1 );

    TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath( SVector( 10, 10 ), SVector( 40, 10 ), 2, 1 ) );
    ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 10, 10 ), SVector( 40, 10 ) ) );
  }

  //  Start
  //  *    *----*----* Finish
  void TestFinishOnRoute()
  {
    routePathfinder->AddRoute( CreateRoute( SVector( 10, 10 ), SVector( 20, 10 ), SVector( 30, 10 ) ), 1 );

    TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath( SVector( 5, 10 ), SVector( 30, 10 ), 2, 1 ) );
    ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 5, 10 ), SVector( 30, 10 ) ) );
  }

  //      * Start            * Finish
  //  *---------------------------------*-----*
  void TestRouteOnOneSegment()
  {
    routePathfinder->AddRoute( CreateRoute( SVector( 10, 10 ), SVector( 40, 10 ), SVector( 50, 10 ) ), 1 );

    TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath( SVector( 15, 8 ), SVector( 30, 5 ), 2, 1 ) );
    ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 15, 8 ), SVector( 17, 10 ), SVector( 22, 10 ), SVector( 30, 5 ) ) );
  }

  //  * Start            * Finish
  //      *------------*------------------*
  void TestRouteOnOneSegment2()
  {
    routePathfinder->AddRoute( CreateRoute( SVector( 15, 10 ), SVector( 30, 10 ), SVector( 100, 10 ) ), 1 );

    TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath( SVector( 12, 5 ), SVector( 32, 5 ), 2, 1 ) );
    ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 12, 5 ), SVector( 15, 10 ), SVector( 30, 10 ), SVector( 32, 5 ) ) );
  }

  //    Start            Finish
  //  *-*----------------*---*------------------*
  void TestRouteOnOneSegment3()
  {
    routePathfinder->AddRoute( CreateRoute( SVector( 15, 10 ), SVector( 40, 10 ) ), 1 );

    TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath( SVector( 20, 10 ), SVector( 35, 10 ), 2, 1 ) );
    ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 20, 10 ), SVector( 35, 10 ) ) );
  }

  //    Start            
  //  *-*------------*   * Finish
  void TestRouteOnOneSegment4()
  {
    routePathfinder->AddRoute( CreateRoute( SVector( 15, 10 ), SVector( 40, 10 ) ), 1 );

    TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath( SVector( 20, 10 ), SVector( 50, 10 ), 2, 1 ) );
    ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 20, 10 ), SVector( 50, 10 ) ) );
  }

  //      * Start            
  //  *---------------------------------*
  //        * Finish
  void TestRouteOnOneSegmentNoPath()
  {
    //there should be no path this way. cause cutting corners will rot the path
    routePathfinder->AddRoute( CreateRoute( SVector( 10, 10 ), SVector( 100, 10 ), SVector( 110, 10 )), 1 );
    TS_ASSERT_EQUALS( 0, routePathfinder->FindPath( SVector( 20, 0 ), SVector( 22, 10 ), 2, 1 ) );
  }

  //     
  //  Start            Finish
  //  *-------*-------*
  void TestRoutPathWeight()
  {
    routePathfinder->AddRoute( CreateRoute( SVector( 10, 30 ), SVector( 20, 30 ), SVector( 40, 30 ) ), 1 );
    TS_ASSERT_EQUALS( 232, routePathfinder->FindPath( SVector( 10, 30 ), SVector( 40, 30 ), 2, 1 ) );
  }

	//          BBB  *-----------------*
	//          BBB                        * Finish
	//  *       BBB  *-----------------*
	//  Start   BBB
	//          ...
  //  BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
	void TestRouteSelectionWithBlocks()
	{
    PlaceObstacle2( tileMap, 30, 25, 3, 25 );
		routePathfinder->AddRoute( CreateRoute( SVector( 40, 30 ), SVector( 70, 30 ) ), 1 );
		routePathfinder->AddRoute( CreateRoute( SVector( 40, 40 ), SVector( 70, 40 ) ), 1 );
		TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath( SVector( 15, 40 ), SVector( 75, 35 ), 1, 1 ) );
    //ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 15, 40 ), SVector( 29, 24 ), SVector( 33, 24 ), SVector( 40, 30 ), SVector( 70, 30 ), SVector( 75, 35 ) ) );
	}

	//          BBB  *-----------------*
	//          BBB                        * Start
	//  *       BBB  *-----------------*
	//  Finish  BBB
	//          ...
  //  BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
  void TestRoutesSelectionWithBlocks2()
  {
    PlaceObstacle2( tileMap, 30, 25, 3, 25 );
		routePathfinder->AddRoute( CreateRoute( SVector( 40, 30 ), SVector( 70, 30 ) ), 1 );
		routePathfinder->AddRoute( CreateRoute( SVector( 40, 40 ), SVector( 70, 40 ) ), 1 );
		TS_ASSERT_DIFFERS( 0, routePathfinder->FindPath( SVector( 75, 35 ), SVector( 15, 40 ), 1, 1 ) );
    //ComparePath( routePathfinder->GetPath(), CreateRoute( SVector( 75, 35 ), SVector( 70, 30 ), SVector( 40, 30 ), SVector( 33, 24 ), SVector( 29, 24 ), SVector( 15, 40 ) ) );
  }
};
