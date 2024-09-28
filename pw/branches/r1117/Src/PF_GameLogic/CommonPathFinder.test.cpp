//!Component("PF_GameLogic/CommonPathFinder")
//!Component("System/Savers")
//!Component("System/FileSystem/TestFileSystem")
//!Component('System/Dumpers')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestAssertDumper.h"

#include "TileMap.h"
#include "CommonPathFinder.h"
#include "System/Bresenham.h"
#include "System/BinChunkSerializer.h"
#include "System/FileSystem/FileStream.h"
#include "System/DebugTraceDumper.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlaceObstacle( NWorld::TileMap* tileMap, int x, int y, int width, int height )
{
	CTRect<float> coll( 0, 0, width, height );
	vector<CTPoint<int>> mask;
	for( int x = coll.x1; x < coll.x2; ++x )
	{
		for( int y = coll.y1; y < coll.y2; ++y )
			mask.push_back( CTPoint<int>( x, y ) );
	}
	Placement place( CVec3( x, y, 0 ), QNULL, CVec3( 1, 1, 1 ) );

  vector<SVector> occupiedTiles;
  tileMap->FillOccupiedTiles( occupiedTiles,coll, 1.0f, mask, place);
	tileMap->MarkObject(occupiedTiles, true, NWorld::MAP_MODE_STATIC);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PathFinderTest : public CxxTest::TestSuite
{
  CObj<NWorld::TileMap> tileMap;
  CObj<NWorld::TileMap> worlTileMap;

  CObj<Pathfinding::CCommonPathFinder> commonPathfinder;
  CObj<Pathfinding::CCommonPathFinder> worldPathfinder;

  void CreteTileMap(string fileName, CObj<NWorld::TileMap> & tileM)
  {
    tileM = new NWorld::TileMap();
   
    CObj<FileStream> pStream = new FileStream( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    CObj<IBinSaver> pSaver = CreateReadBinSaver( pStream,	0 );
    pSaver->Add( 1, &tileM );
  }

  virtual void setUpSuite()
  {
    CreteTileMap("worldMap.tilemap", worlTileMap);
    worldPathfinder = new Pathfinding::CCommonPathFinder( worlTileMap );
  }

  virtual void setUp()
  {
    tileMap = new NWorld::TileMap();
    tileMap->Prepare( 200, 60, 1.0f );
    tileMap->OnLoaded();
    commonPathfinder = new Pathfinding::CCommonPathFinder( tileMap );
  }

  virtual void tearDown()
  {
    commonPathfinder = 0;
    tileMap = 0; 
  }

  bool CreatePath(const SVector & start, const SVector & end)
  {
    return commonPathfinder->CreatePath(2,2, start, end, start, 0, -1, 0);
  }

  //10 mls just too much

  void TestLongFindPath()
  {
    NWorld::MapModeChanger mapModeChanger(5, worlTileMap);

    SVector start(59, 360);
    SVector end(515, 202);
    //SVector end(440, 240);

    bool pathFound = worldPathfinder->CreatePath(5,5, start, end, start, 0, -1, 0);

    NI_ASSERT (pathFound, "path not found");

    vector<SVector> path(worldPathfinder->GetPathLength());

    worldPathfinder->GetTiles(&path[0], worldPathfinder->GetPathLength());

    worlTileMap->Dump( "TestLongFindPath.tga", NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, &path);
  }



	//       BBBBBBBBBBB  
	//               BBB   
	//      Start*   BBB  * Finish
  //               BBB
  //       BBBBBBBBBBB
	//
  
	void TestRouteSelectionWithBlocks()
	{
    PlaceObstacle( tileMap, 10, 10, 40, 10);
    PlaceObstacle( tileMap, 10, 40, 40, 10);
    PlaceObstacle( tileMap, 40, 20, 10, 20);

		
		NI_ASSERT (CreatePath(SVector(20, 30), SVector(60, 30)), "path not found");
    
    vector<SVector> path(commonPathfinder->GetPathLength());

    commonPathfinder->GetTiles(&path[0], commonPathfinder->GetPathLength());

    tileMap->Dump( "TestRouteSelectionWithBlocks.tga", NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, &path);
    
    //TODO compare this with the correct tga 
    
	}

  //               BBB   
  //          A*   BBB   * B
  //               BBB

  void TestApproachingToObstacle()
  {
    int left = 50;
    int top = 20;
    int size = 9;
    
    int vertMiddle = top + size/2;

    PlaceObstacle( tileMap, left, top, size, size);
    
    //FROM LEFT
    NI_ASSERT (CreatePath(SVector(left -5, vertMiddle), SVector(left, vertMiddle)), "path not found");

    vector<SVector> pathLeft(commonPathfinder->GetPathLength());
    commonPathfinder->GetTiles(&pathLeft[0], commonPathfinder->GetPathLength());

    int leftDistance = left - pathLeft[pathLeft.size()-1].x;
    NI_ASSERT(leftDistance == 0, "stand not close enough");

    
    //FROM RIGHT
    NI_ASSERT (CreatePath(SVector(left + size + 5, vertMiddle), SVector(left + size -1, vertMiddle)), "path not found");

    vector<SVector> pathRight(commonPathfinder->GetPathLength());
    commonPathfinder->GetTiles(&pathRight[0], commonPathfinder->GetPathLength());

    int rightDistance =  pathRight[pathRight.size()-1].x - left - size+1;
    NI_ASSERT(rightDistance == 0, "stand not close enough");

    vector<SVector> path(pathLeft);

    int totalSize = pathLeft.size()+pathRight.size();
    path.resize(totalSize);

    for (int i = pathLeft.size(); i< totalSize; i++)
    {
      path[i]= pathRight[i- pathLeft.size()];
    }
    

     tileMap->Dump( "TestApproachingToObstacle.tga", NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, &path);
  }
 
  void TestNoPathCorner()
  {
   NWorld::MapModeChanger mapModeChanger(5, worlTileMap);

   SVector start(477, 355);
   SVector end(494, 403);

   bool pathFound = worldPathfinder->CreatePath(4,4, start, end, start, 0, -1, 0) && worldPathfinder->GetPathLength()>1;

   NI_ASSERT (pathFound, "path not found");

   vector<SVector> path(worldPathfinder->GetPathLength());

   worldPathfinder->GetTiles(&path[0], worldPathfinder->GetPathLength());

   worlTileMap->Dump( "TestNoPathCorner.tga", NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, &path);
  }

  void TestLongCycle()
  {
    NWorld::MapModeChanger mapModeChanger(5, worlTileMap);

    SVector start(67, 348);
    SVector end(67, 330);

    bool pathFound = worldPathfinder->CreatePath(4,4, start, end, start, 0, -1, 0) && worldPathfinder->GetPathLength()>1;

    NI_ASSERT (pathFound, "path not found");

    vector<SVector> path(worldPathfinder->GetPathLength());

    worldPathfinder->GetTiles(&path[0], worldPathfinder->GetPathLength());
    path.push_back(end);

    worlTileMap->Dump( "TestLongCycle.tga", NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, &path);
  }

  void TestTowerAttack()
  {
    NWorld::MapModeChanger mapModeChanger(5, worlTileMap);

    SVector start(198, 452);
    SVector end(175, 447);

    bool pathFound = worldPathfinder->CreatePath(4,4, start, end, start, 0, -1, 0) && worldPathfinder->GetPathLength()>1;

    NI_ASSERT (pathFound, "path not found");

    vector<SVector> path(worldPathfinder->GetPathLength());

    worldPathfinder->GetTiles(&path[0], worldPathfinder->GetPathLength());
    path.push_back(end);

    worlTileMap->Dump( "TestTowerAttack.tga", NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, &path);
  }

  void TestTooLongPath()
  {
    NWorld::MapModeChanger mapModeChanger(5, worlTileMap);

    //from(270, 422) to(84, 405)
    //from(656, 389) to(16, 50)

    SVector start(656, 389);
    SVector end(16, 50);

    bool pathFound = worldPathfinder->CreatePath(4,4, start, end, start, 0, -1, 0) && worldPathfinder->GetPathLength()>1;

    NI_ASSERT (pathFound, "path not found");

    vector<SVector> path(worldPathfinder->GetPathLength());

    worldPathfinder->GetTiles(&path[0], worldPathfinder->GetPathLength());
    path.push_back(end);

    worlTileMap->Dump( "TestTooLongPath.tga", NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, &path);
  }

  void TestBypass()
  {
    SVector start( 512, 634 );
    SVector end( 570, 644 );

    bool pathFound = worldPathfinder->CreatePath( 4, 4, start, end, start, 0, -1, 0 ) && worldPathfinder->GetPathLength() > 1;
    TS_ASSERT( pathFound );

    vector<SVector> path(worldPathfinder->GetPathLength());
    worldPathfinder->GetTiles(&path[0], worldPathfinder->GetPathLength());
    worlTileMap->Dump( "TestBypass.tga", NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, &path);
  }
};
