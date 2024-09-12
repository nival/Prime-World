//!Component("PF_GameLogic/PathFinder")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestAssertDumper.h"

#include "CommonPathFinder.h"
#include "ImportedStruct.h"
#include "Path.h"
#include "PathTools.h"
#include "PointChecking.h"
#include "StandartPath2.h"
#include "StaticPathInternal.h"
#include "PFBaseMovingUnit.h"
#include "PFClientBaseMovingUnit.h"
#include "PFClientHero.h"

#include "Mockup.test.h"

struct PathFinderTest2 : public CxxTest::TestSuite
{
  CObj<TestFileSystem> fileSystem;

  Strong<NGameX::MockAdventureScreen2> mockAdventureScreen;
  CObj<NWorld::PFWorld> world;
  
  int stepLength;

  void setUp()
  {
    fileSystem = new TestFileSystem( "../../../Data/", true, true );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( fileSystem, 0 ) );
        
    nstl::string mapName = "Maps/Test/PlaneMap/Test_PVP_1x1.ADMPDSCR.xdb";
    UI::SetUIRoot( NDb::Get<NDb::UIRoot>( NDb::DBID( "UI/UIRoot" ) ) );
    world = SetupTestWorld(mapName);
        
    stepLength = DEFAULT_GAME_STEP_LENGTH;
  }

  void tearDown()
  {
    UI::SetUIRoot( 0 );
    NDb::SessionRoot::InitRoot( 0 );
    NDb::SoundRoot::InitRoot( 0 );
    NDb::SetResourceCache( 0 );
    
    fileSystem = 0;
    world = 0;
  }

  Terrain::GridConstants  CreateGridConstants(const NDb::Terrain * terrain)
  {
    Terrain::GridConstants gridConstants;
    // copy given constants
    gridConstants.valid = true;
    gridConstants.metersPerElement = Terrain::Patch::SIZE_OF_PATCH;
    gridConstants.sizeInElements.x = terrain->elemXCount;
    gridConstants.sizeInElements.y = terrain->elemYCount;
    gridConstants.tilesPerElement  = terrain->tilesPerElement;
    gridConstants.texelsPerElement = 16;

    // fill derived constants
    gridConstants.worldSize.Set(
      (float)gridConstants.sizeInElements.x * gridConstants.metersPerElement,
      (float)gridConstants.sizeInElements.y * gridConstants.metersPerElement, 50.0f);
    gridConstants.metersPerTile = gridConstants.metersPerElement / (float)gridConstants.tilesPerElement;
    gridConstants.metersPerTexel = gridConstants.metersPerElement / (float)gridConstants.texelsPerElement;
    gridConstants.sizeInTiles.x = gridConstants.sizeInElements.x * gridConstants.tilesPerElement;
    gridConstants.sizeInTiles.y = gridConstants.sizeInElements.y * gridConstants.tilesPerElement;
    gridConstants.sizeInTexels.x = gridConstants.sizeInElements.x * gridConstants.texelsPerElement;
    gridConstants.sizeInTexels.y = gridConstants.sizeInElements.y * gridConstants.texelsPerElement;

    return gridConstants;
  }

  NWorld::PFWorld* SetupTestWorld(nstl::string mapName)
  {
    NDb::SessionRoot::InitRoot(NDb::DBID( "Session.ROOT" ));

    NCore::MapStartInfo startInfo;
    startInfo.mapDescName = mapName;
    //PlayerStartInfo( int playerID, ETeam::Enum teamID, EPlayerType::Enum playerType = EPlayerType::Invalid, int userID = -1 ) 
    startInfo.playersInfo.push_back( NCore::PlayerStartInfo( 0, NCore::ETeam::Team1, NCore::ETeam::Team1, NCore::EPlayerType::Human, 0) );
    startInfo.playersInfo.push_back( NCore::PlayerStartInfo( 1, NCore::ETeam::Team2, NCore::ETeam::Team2, NCore::EPlayerType::Human, 0) );


    NDb::Ptr<NDb::AdvMapDescription> pAdvMapDesc = NDb::Get<NDb::AdvMapDescription>( NDb::DBID( startInfo.mapDescName ) );
    NDb::Ptr<NDb::AdvMap> pAdvMap = pAdvMapDesc->map;
    NDb::Ptr<NDb::Terrain> dbTerrain = pAdvMap->terrain;
    NDb::Ptr<NDb::AdvMapSettings> advMapSettings = IsValid(pAdvMapDesc->mapSettings) ? (pAdvMapDesc->mapSettings) : (pAdvMap->mapSettings);

    Terrain::GridConstants params = CreateGridConstants(dbTerrain);

    float mapSizeX = params.worldSize.x;
    float mapSizeY = params.worldSize.y;

    mockAdventureScreen = new NGameX::MockAdventureScreen2(params);
    CObj<NWorld::PFWorld> world = new NWorld::PFWorld( startInfo, 0, mockAdventureScreen, 0 , stepLength);
    world->SetDebugRender( 0 );

    world->GetTileMap()->Prepare( mapSizeX, mapSizeY, params.metersPerTile );
    world->SetMapSize(CVec2(mapSizeX, mapSizeY));
    
    world->GetAIWorld()->SetVoxelMapSizes(world->GetTileMap());
    world->GetAIWorld()->SetMapData( pAdvMapDesc, advMapSettings );
    world->GetTileMap()->OnLoaded();
   
    world->GetNatureMap()->OnLoaded(dbTerrain);

    world->SetPathFinder( new Pathfinding::CCommonPathFinder( world->GetTileMap() ) );
    world->SetRoutPathfinder( new Pathfinding::RoutePathFinder( world->GetPathFinder() ) );

    int warFogObstacleVisibility = world->GetTileMap()->GetLenghtInTiles(pAdvMap->lightEnvironment->warFogObstacleVisibility);
    world->SetFogOfWar( new NWorld::FogOfWar(world, NDb::KnownEnum<NDb::EFaction>::sizeOf, world->GetTileMap()->GetSizeX(), world->GetTileMap()->GetSizeY(), 4, warFogObstacleVisibility) );

    const float goldPerTeam = advMapSettings->primeSettings.startPrimePerTeam;
    int goldPerPlayerInTeam1 = static_cast<int>( goldPerTeam );
    int goldPerPlayerInTeam2 = static_cast<int>( goldPerTeam );

    for (int i = 0, count = world->GetPlayersCount(); i < count; ++i)
    {
      NWorld::PFBaseHero* pHero = world->GetPlayer(i)->GetHero();
      if ( pHero )
        pHero->AddGold( (world->GetPlayer(i)->GetTeamID() == NCore::ETeam::Team1) ? goldPerPlayerInTeam1 : goldPerPlayerInTeam2, false );
    }

    //world->GetVisibilityMap()->OnInitialUpdate();

    NDb::SoundRoot::InitRoot( NDb::DBID( "Audio/SoundRoot" ) );

    return world.Extract();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void InitHeroSpawnInfo( NWorld::PFBaseHero::SpawnInfo &info, int playerId, int x, int y, const char* fileName )
  {
    info.playerId  = playerId;
    info.placement = Placement( CVec3( x, y, 0.f ) );
    info.inTeamId  = 1;
    info.isClone   = false;
    info.faction   = NDb::FACTION_FREEZE;
 
    NLogg::FailTestOnAnyError(false);
    DisableDebugAsserts();

    info.pHero = NDb::Get<NDb::BaseHero>( NDb::DBID( fileName ) );

    EnableDebugAsserts();
    NLogg::FailTestOnAnyError(true);
  }

  NWorld::PFBaseHero* CreateHero_( NWorld::PFWorld* pWorld, const NWorld::PFBaseHero::SpawnInfo &info )
  {
    NLogg::FailTestOnAnyError(false);
    DisableDebugAsserts();

    NDb::Ptr<NDb::BaseHero> holdHero = info.pHero;
    NWorld::PFBaseHero* pHero = NWorld::CreateHero( pWorld, info );

    EnableDebugAsserts();
    NLogg::FailTestOnAnyError(true);
    NI_ASSERT( pHero != 0 , "hero must be created");

    return pHero;
  }


  NWorld::PFBaseHero* CreateHero( NWorld::PFWorld* pWorld, int playerId, int x, int y, const char* fileName )
  {
    NWorld::PFBaseHero::SpawnInfo info;
    InitHeroSpawnInfo( info, playerId, x, y, fileName );
    return CreateHero_( pWorld, info );
  }

  void ExecGameCommands( NWorld::PFWorld* pWorld, CObj<NCore::WorldCommand> pCommand)
  {
    pCommand->Execute( pWorld );
  }

//////////////////////////////////////////////////////////////////////////


	// this simple code is leaks. do not know why
	void TestMemoryLeaks()
	{
    Terrain::GridConstants params;
    Strong<NGameX::MockAdventureScreen2> mockAdventureScreen = new NGameX::MockAdventureScreen2( params );
    NCore::MapStartInfo info;
		CObj<NWorld::PFWorld> world = new NWorld::PFWorld( info, 0, mockAdventureScreen, 0, stepLength );
    NDb::Ptr<NDb::Unit> dbUnit = new NDb::Unit();
		CObj<NWorld::PFBaseMovingUnit> unit = new NWorld::PFBaseMovingUnit( world, CVec3( 0, 0, 0 ), CVec2( 0, 0 ), *dbUnit );
		world->OnDestroyContents();
}

  void TestUpdateMovements()
  {
    CObj<NWorld::PFBaseHero> hero1 = CreateHero( world, 0, 1, 1, "Heroes/Rockman/_.HROB.xdb" );

		//const CVec3 start( 1.0f, 1.0f, 1.0f );
		const CVec3 roundedStart( 2.1875f, 2.1875f, 0 );
    /*NCore::MapStartInfo info;
		CObj<NWorld::PFWorld> world = new NWorld::PFWorld( info, 0, mockAdventureScreen, 0 );
		CPtr<NWorld::PFBaseMovingUnit> unit = new NWorld::PFBaseMovingUnit( world, start, CVec2( 0, 0 ), NDb::Unit() );*/
		hero1->MoveTo( CVec2( 10.0f, 10.0f ) );
		TS_ASSERT_EQUALS( roundedStart, hero1->GetPosition() );
		world->Step( 0.1f, 0.1f );
		world->Step( 0.1f, 0.1f );
 		TS_ASSERT_DIFFERS( roundedStart, hero1->GetPosition() );
 }

  void TestStraightMovements()
  {
    CObj<NWorld::PFBaseHero> hero1 = CreateHero( world, 0, 1, 1, "Heroes/Rockman/_.HROB.xdb" );

    const CVec3 start( 1.0f, 1.0f, 1.0f );
		
		hero1->MoveTo( hero1->GetPos() + CVec2( 0, 20.0f ) );
		while ( hero1->IsMoving() )
			world->Step( 20.f, 20.f );

		float pos = hero1->GetPosition().y;
		hero1->MoveTo( hero1->GetPos() + CVec2( 20.0f, 0 ) );
		for( int i = 0; i < 5; ++i )
		{
			world->Step( 0.1f, 0.1f );
			TS_ASSERT_DELTA( pos, hero1->GetPosition().y, 0.001f );
		}
	}

  void TestAsyncMoveGather()
  {
    // just to be sure
    //NGlobal::SetVar( "visual_unit", NGlobal::VariantValue( (int)NWorld::MovingUnit::LOCAL ), STORAGE_DONT_CARE );
    CObj<NWorld::PFBaseHero> hero1 = CreateHero( world, 0, 1, 1, "Heroes/Rockman/_.HROB.xdb" );

    const CVec2 asyncTarget( hero1->GetPos() + CVec2( 0, 20.0f ) );
    const CVec2 syncTarget( hero1->GetPos() + CVec2( 0, 10.0f ) );

    hero1->MoveTo( asyncTarget );
    for( int i = 0; i < 6; ++i )
			world->Step( 1.f, 1.f );

    //TODO ClientObject() can be null here. if adventure screen is not determined
    hero1->MoveTo( syncTarget );
    while ( hero1->IsMoving() )
			world->Step( 1.f, 1.f );

    /*CVec3 worldPos = hero1->GetPosition();
    CVec3 clientPos = hero1->ClientObject()->GetPosition().pos;
    TS_ASSERT_DELTA( fabs2( worldPos - clientPos ), 0.0f, 0.1f );*/
  }

  void TestAsyncMoveSlowDown()
  {
    // just to be sure
    //NGlobal::SetVar( "visual_unit", NGlobal::VariantValue( (int)NWorld::MovingUnit::LOCAL ), STORAGE_DONT_CARE );
    CObj<NWorld::PFBaseHero> hero1 = CreateHero( world, 0, 1, 1, "Heroes/Rockman/_.HROB.xdb" );

    const CVec2 target( hero1->GetPos() + CVec2( 0, 10.0f ) );

    hero1->MoveTo( target );
    for( int i = 0; i < 6; ++i )
			world->Step( 1.f, 1.f );

    hero1->MoveTo( target );
    while ( hero1->IsMoving() )
			world->Step( 1.f, 1.f );

    //TS_ASSERT_DELTA( fabs2( hero1->GetPosition() - hero1->ClientObject()->GetPosition().pos ), 0.0f, 0.1f );
  }
};