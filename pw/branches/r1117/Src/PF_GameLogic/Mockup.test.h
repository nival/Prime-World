#ifndef MOCKUP_TEST_H
#define MOCKUP_TEST_H
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

namespace NGameX
  {
  class MockAdventureScreen2: public IAdventureScreen, public BaseObjectST
    {
    NI_DECLARE_REFCOUNT_CLASS_2( MockAdventureScreen2, IAdventureScreen, BaseObjectST );

    const int sizeInTilesX;
    const int sizeInTilesY;

    MockAdventureScreen2():
    sizeInTilesX(0),
      sizeInTilesY(0)
      {}
    public:

      MockAdventureScreen2(Terrain::GridConstants gridConstants):
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
  
#endif MOCKUP_TEST_H
