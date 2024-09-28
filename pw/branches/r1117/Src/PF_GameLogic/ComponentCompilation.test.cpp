//!Component("PF_GameLogic/PF_GameLogic")
//!Component("System/FileSystem/TestFileSystem")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestAssertDumper.h"

#include "PFWorld.h"
#include "IAdventureScreen.h"
#include "../Core/WorldCommand.h"
#include "../System/FileSystem/TestFileSystem.h"

#include "PFHero.h"
#include "PFAIWorld.h"
#include "TileMap.h"
#include "PFWorldNatureMap.h"
#include "HeroActions.h"

#include "DBSessionRoots.h"
#include "Terrain/Terrain.h"
#include "Terrain/DBTerrain.h"
#include "Terrain/BezierSurface.h"
#include "PFHeroStatistics.h"
#include "../Scene/Camera.h"
#include "../UI/Root.h"
#include "DBSound.h"
#include "RoutePathFinder.h"
#include "WarFog.h"


static const wstring MY_NAME_TEST = L"test";

namespace NGameX
{
class MockAdventureScreen: public IAdventureScreen, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockAdventureScreen, IAdventureScreen, BaseObjectST );

  const int sizeInTilesX;
  const int sizeInTilesY;

  MockAdventureScreen():
    sizeInTilesX(0),
    sizeInTilesY(0)
  {}
public:

  MockAdventureScreen(Terrain::GridConstants gridConstants):
    sizeInTilesX(gridConstants.sizeInTiles.x),
    sizeInTilesY(gridConstants.sizeInTiles.y)
  {}
  virtual void SetMessage( wstring const &msg, DWORD lifeTime ) {};
  virtual void SendGameCommand( NCore::WorldCommand* command ) {};
  virtual void PrecacheResources() {};

  virtual CArray2D<float> const& GetHeightsAsFloat() const
  {
    static CArray2D<float> heights(sizeInTilesX, sizeInTilesY);
    return heights;
  }

  virtual CArray2D<unsigned short> const& GetHeightsAsShort()  const
  {
    static CArray2D<unsigned short> heights(sizeInTilesX, sizeInTilesY);
    return heights;
  }

  virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName ) {}
  virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const NDb::DbResource * excludePart ) {}
  virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const nstl::list<const NDb::DbResource*>& excludes ) {}

  virtual bool CanCreateClients() { return false;}

  virtual void SetDebugMessage(nstl::string const & msg) {};

  virtual void NotifyPushedLine(const NWorld::PFBuilding * quarter, const NWorld::PFBaseUnit * killer) {}
  virtual void NotifyOfSimpleUIEvent( NWorld::PFBaseHero * hero,  NDb::EErrorMessageType msg ) {}
  virtual void NotifySoldiersFirstSpawned() {}
  virtual void ProcessGamePause(EPauseMode pause, int playerWhoPressedPause) {}
  virtual const wstring& GetPlayerName(int playerId) const { return MY_NAME_TEST; }
  virtual NDb::EFaction GetPlayerFaction() const { return NDb::FACTION_FREEZE; }

  virtual void LogSessionEvent( NWorld::PFBaseHero const * hero, SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params ) {}
  virtual void LogSessionEvent( NWorld::PFBaseHero const * hero, SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params, int worldStep ) {}
  virtual void LogWorldSessionEvent( SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params ) {}
  virtual void LogHeroDamage(const NWorld::HeroOpponent &opponent, unsigned int abilityId, const NWorld::HeroDamage &damage, bool dealt) {}

  virtual void OnVictory( NDb::EFaction _failedFaction, int _surrenderVotes ) {}
  virtual void DumpState( const char* stateClass, const char* state ) {}
  virtual NWorld::ImpulsiveBuffsManager * GetImpulseBuffsManager() { return 0; }
  virtual NWorld::PFBaseHero * GetLoggerHero() { return 0; }
  virtual void StartGlobalSounds() {}
  virtual void StopGlobalSounds() {}
  virtual void StartAmbientSound() {}
  virtual void StopAmbientSound() {}
  virtual void UpdateAmbientSound(NScene::SCameraPosition const& camPos) {}

  virtual void  SetNaftaInfoProvider(INaftaInfoProvider * _naftaInfoProvider) {}

  virtual void DisableRenderWarFog(NWorld::PFBaseHero const * hero, bool disable) {}

  virtual void OnHeroDamaged(NWorld::PFBaseHero const * hero) {}

  virtual void ReservePureClientObjects( unsigned int n ) {}
  virtual void PushPureClientObject( PFPureClientObject* pPureClientObject ) {}

  virtual void OnClientStatusChange( int userId, int newStatus, int step, NWorld::PFPlayer * player = 0 ) {}
  virtual void OnPlayerDisconnected(NWorld::PFPlayer * player, int lastStep) {}
};

}
struct ComponentCompilationTest  : public CxxTest::TestSuite
{
  CObj<TestFileSystem> fileSystem;
  int stepLength;

  Strong<NGameX::MockAdventureScreen> mockAdventureScreen;
  void setUp()
  {
    fileSystem = new TestFileSystem( "../../../Data/", true, true );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( fileSystem, 0 ) );
    stepLength = DEFAULT_GAME_STEP_LENGTH;
  }

  void tearDown()
  {
    NDb::SetResourceCache( 0 );
    fileSystem = 0;
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

    mockAdventureScreen = new NGameX::MockAdventureScreen (params);
    CObj<NWorld::PFWorld> world = new NWorld::PFWorld( startInfo, 0, mockAdventureScreen, 0, stepLength );
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


  void test_Move()
  {
    nstl::string mapName = "Maps/Test/PlaneMap/Test_PVP_1x1.ADMPDSCR.xdb";
    UI::SetUIRoot( NDb::Get<NDb::UIRoot>( NDb::DBID( "UI/UIRoot" ) ) );
    CObj<NWorld::PFWorld> world = SetupTestWorld(mapName);

    CObj<NWorld::PFBaseHero> hero1 = CreateHero( world, 0, 1, 1, "Heroes/Rockman/_.HROB.xdb" );
 
    TS_ASSERT_EQUALS( hero1->GetPos().x, 2.1875f );
    TS_ASSERT_EQUALS( hero1->GetPos().y, 2.1875f );

    world->Step( 0.1f, 0.1f );

    ExecGameCommands( world, NWorld::CreateCmdMoveHero( hero1, CVec2( 10, 10 ), false ) );

    world->Step( 0.1f, 0.1f );
    TS_ASSERT_EQUALS( hero1->IsMoving(), true ); 

    do 
    {
      world->Step( 0.1f, 0.1f );
    } 
    while ( hero1->IsMoving());

    TS_ASSERT_DELTA( hero1->GetPos().x, 10.0f, 0.5f );
    TS_ASSERT_DELTA( hero1->GetPos().y, 10.0f, 0.5f );
    UI::SetUIRoot( 0 );
    NDb::SessionRoot::InitRoot( 0 );
    NDb::SoundRoot::InitRoot( 0 );
    
    hero1 = 0;
    world = 0;
  }

};

//REGISTER_SAVELOAD_CLASS_NM(MockAdventureScreen, NGameX);