
//!Component('PF_GameLogic/PF_GameLogic')


#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestAssertDumper.h"

#include "PF_GameLogic/PFWorld.h"
#include "PF_GameLogic/PFHero.h"
#include "PF_GameLogic/PFHeroStatistics.h"

#include "Scene/Camera.h"
#include "Terrain/Terrain.h"

#include "System/FileSystem/TestFileSystem.h"
#include "UI/Root.h"

#include "PF_GameLogic/DBSound.h"

namespace NGameX
{
class MockAdventureScreen3: public IAdventureScreen, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockAdventureScreen3, IAdventureScreen, BaseObjectST );

  const int sizeInTilesX;
  const int sizeInTilesY;

  MockAdventureScreen3():
    sizeInTilesX(0),
    sizeInTilesY(0)
  {}
public:

  MockAdventureScreen3(Terrain::GridConstants gridConstants):
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

struct PFWorldTest : public CxxTest::TestSuite
{
  int stepLength;
  
  void setUp()
  {
    stepLength = DEFAULT_GAME_STEP_LENGTH;
  }

  void TestSimple() // 91 Build error
  {
    CObj<TestFileSystem> fileSystem = new TestFileSystem( "../../../Data/", true, true );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( fileSystem, 0 ) );

    UI::SetUIRoot( NDb::Get<NDb::UIRoot>( NDb::DBID( "UI/UIRoot" ) ) );
    NDb::SessionRoot::InitRoot(NDb::DBID( "Session.ROOT" ));
    NDb::SoundRoot::InitRoot( NDb::DBID( "Audio/SoundRoot" ) );
    Terrain::GridConstants gridConstants;
    Strong<NGameX::MockAdventureScreen3> mockAdventureScreen = new NGameX::MockAdventureScreen3( gridConstants );
    NCore::MapStartInfo info; 
    CObj<NWorld::PFWorld> world = new NWorld::PFWorld( info, 0, mockAdventureScreen, 0, stepLength );
    UI::SetUIRoot( 0 );
    NDb::SessionRoot::InitRoot( 0 );
    NDb::SoundRoot::InitRoot( 0 );
    NDb::SetResourceCache( 0 );
    fileSystem = 0;
  } 
};
