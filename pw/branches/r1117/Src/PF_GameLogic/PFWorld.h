#pragma once

#include "Core/GameTypes.h"
#include "System/RandomGenerator.h"
#include "libdb/Db.h"
#include "PF_Core/World.hpp"
#include "PF_Core/WorldObject.h"
#include "Scene/Scene.h"
#include "System/BitData.h"
#include "System/Singleton.h"
#include "Render/debugrenderer.h"
#include "IAdventureScreen.h"
#include "WorldChecker.h"
#include "PFResourcesCollectionClient.h"
#include "System/StarForce/StarForce.h"
#include "SmartRandom.h"
#include "FPUState.h"
#include "Core/Scheduler.h"



namespace PF_Minigames
{
  class IMinigamesMain;
}

namespace NGameX
{
_interface IAdventureScreen;
}

namespace NDb
{
  struct AdvMap;
  struct AdvMapDescription;
  struct AdvMapSettings;
  struct Talent;
  struct Consumable;
  struct BotsSettings;
}

namespace Pathfinding
{
  class CCommonPathFinder;
  class RoutePathFinder;
}

namespace NCore
{
  class PackedWorldCommand;
}

class LoadingProgress;



namespace NWorld
{

class TileMap;
class CollisionResolver;
class PFPlayer;
class PFVoxelMap;
class PFAIWorld;
class PFWorldNatureMap;
class PFStatistics;
class TriggerMarkerHandler;
class PFAIContainer;
class PFBaseUnit;
class FogOfWar;
class PFCommonCreep;
class PFTalent;
class PFConsumableAbilityData;
class PFNeutralCreepSpawner;
class PFMainBuilding;

class MapLoadingController;
class DayNightController;

typedef StrongMT<MapLoadingController> MapLoadingControllerPtr;

namespace EMapLoadStages
{
  enum Enum
  {
    Environment,
    Terrain,
    PathFinding,
    Scene,
    MapObjects,
    Heroes,
    HeightMap
  };
};


typedef map<int, int> TPersistentScores;

class PFWorldProtection;

class PFWorld : public PF_Core::World
{
  OBJECT_METHODS( 0x2C5BDC80, PFWorld );

  PFWorld();

  CPtr<NScene::IScene>    pScene;
  CObj<PF_Minigames::IMinigamesMain> minigamesMain;

  CPtr<PFResourcesCollection> resourcesCollection;

  typedef hash_map< string, NDb::Ptr< NDb::DbResource > > PrecachedResources;
  PrecachedResources preResources;

  static int              instanceCount;
  Render::IDebugRender   *debugRender;

  CObj<Pathfinding::CCommonPathFinder> pathFinder;
  CObj<Pathfinding::RoutePathFinder> routPathFinder;

  Weak<NGameX::IAdventureScreen> adventureScreen;
  NDb::Ptr<NDb::AdvMapDescription> advMapDescription;

	WorldChecker worldChecker;

  const NDb::SoundAmbienceMap* ambienceMap;

  unsigned int            fPUState;       // Intentionally not serialized

  MapLoadingControllerPtr mapLoadingController;

  ZDATA_(PF_Core::World)
  CObj<TileMap>           pTileMap;
  CObj<FogOfWar>          warFog;

  CObj<CollisionResolver> pResolver;
  CObj<PFAIWorld>         pAIWorld;
  CObj<PFAIContainer>     pAIContainer;
  CObj<PFWorldNatureMap>  pNatureMap;
  CObj<PFStatistics>      pStatistics;

  CVec2                   mapSize;    
  vector<CObj<PFPlayer> > players;
	vector<CObj<PFBaseUnit> > deadUnits;
  vector<CObj<PFMainBuilding> > mainBuildings;

  int                     step;
  float                   timeElapsed;

  NRandom::RandomGenerator randGen;
  SmartRandomGenerator    smartRandGen;
  bool                    manualGameFinish;
  int                     humanPlayersCount;
  CObj<TriggerMarkerHandler> triggerMarkerHandler;
  int                     totalCreepsCount;
  bool                    allScriptFunctionsEnabled;
  nfpu::FPUStatesData     fPUStatesData;
  int                     stepLength;
  float                   stepLengthInSeconds;
  
  int                     defeatedFaction; //faction who first lost main building

  CObj<PFWorldProtection> protection;

  CObj<DayNightController>  dayNightController;
  float                   timeScale;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::World*)this); f.Add(2,&pTileMap); f.Add(3,&warFog); f.Add(4,&pResolver); f.Add(5,&pAIWorld); f.Add(6,&pAIContainer); f.Add(7,&pNatureMap); f.Add(8,&pStatistics); f.Add(9,&mapSize); f.Add(10,&players); f.Add(11,&deadUnits); f.Add(12,&mainBuildings); f.Add(13,&step); f.Add(14,&timeElapsed); f.Add(15,&randGen); f.Add(16,&smartRandGen); f.Add(17,&manualGameFinish); f.Add(18,&humanPlayersCount); f.Add(19,&triggerMarkerHandler); f.Add(20,&totalCreepsCount); f.Add(21,&allScriptFunctionsEnabled); f.Add(22,&fPUStatesData); f.Add(23,&stepLength); f.Add(24,&stepLengthInSeconds); f.Add(25,&defeatedFaction); f.Add(26,&protection); f.Add(27,&dayNightController); f.Add(28,&timeScale); return 0; }
  
  PFWorld( const NCore::MapStartInfo & info, NScene::IScene * _scene, NGameX::IAdventureScreen * _screen,
            PFResourcesCollection * _collection, int _stepLength, bool _aiForLeaversEnabled, int _aiForLeaversThreshold );
  virtual void OnDestroyContents();

  void SetDebugRender( Render::IDebugRender * ptr ) { debugRender = ptr; }

  MapLoadingControllerPtr GetMapLoadingController() const { return mapLoadingController; }
  void SetMapLoadingController(const MapLoadingControllerPtr& ptr) { mapLoadingController = ptr; }

  bool LoadMap(const NDb::AdvMapDescription * advMapDescription, const NDb::AdventureCameraSettings * cameraSettings, const NCore::TPlayersStartInfo & playersInfo, LoadingProgress * progress, bool isReconnecting );

  PFResourcesCollection* GetResourcesCollection() 
  { 
    return (IsValid(resourcesCollection) ? resourcesCollection : NULL); 
  }
	WorldChecker* GetWorldChecker()
	{
		return &worldChecker;
	}
  void Reset();
  void ResetClientObjects();

  float GetTimeScale() const { return timeScale; }
  void SetTimeScale(float scale) { timeScale = scale; }

  const NDb::AdvMapDescription *GetMapDescription() { return advMapDescription; }
  TileMap           *GetTileMap() const { return pTileMap; }
  PFAIWorld         *GetAIWorld() const { return pAIWorld; }
  PFStatistics      *GetStatistics() { return pStatistics; }
  PFStatistics      *GetStatistics() const { return pStatistics; }
  FogOfWar          *GetFogOfWar() const {return warFog;}
  PFWorldNatureMap  *GetNatureMap()     { return pNatureMap; }
  PFAIContainer     *GetAIContainer() const { return pAIContainer; }
  CollisionResolver *GetCollisionResolver() const { return pResolver; }
  const NDb::SoundAmbienceMap* GetAmbienceMap() { return ambienceMap; }
  void SetAIContainer( PFAIContainer* AIC ) { pAIContainer = AIC; }
  NGameX::IAdventureScreen * GetIAdventureScreen() {return adventureScreen;}
  NGameX::IAdventureScreen const* GetIAdventureScreen() const {return adventureScreen;}

  void RegisterCreep(const PFCommonCreep*) { ++totalCreepsCount; }
  void UnregisterCreep(const PFCommonCreep*);
  const int GetRegisteredCreepsCount() const { return totalCreepsCount; }  


  //pathfinding
  Pathfinding::CCommonPathFinder * GetPathFinder() {return pathFinder;}
  Pathfinding::RoutePathFinder * GetRoutPathfinder() {return routPathFinder;}

  void SetPathFinder( Pathfinding::CCommonPathFinder* _pathFinder ) { pathFinder = _pathFinder; }
  void SetRoutPathfinder( Pathfinding::RoutePathFinder* _pathFinder ) { routPathFinder = _pathFinder; }
  void SetFogOfWar( FogOfWar* _warFog ) { warFog = _warFog; }

  PF_Minigames::IMinigamesMain * GetMinigamesMain() { return minigamesMain; }

  PFWorldNatureMap const* GetNatureMap() const    { return pNatureMap; }

  NRandom::RandomGenerator * GetRndGen() { return &randGen; }
  SmartRandomGenerator* GetSmartRndGen() { return &smartRandGen; }

  PFPlayer*  GetPlayer(int id) const;
  PFPlayer*  GetPlayerByUID(int userId) const;
  const int  GetPlayersCount() const { return players.size(); }
  bool IsAllScriptFunctionsEnabled() const { return allScriptFunctionsEnabled; }
  const int  GetPresentPlayersCount() const;
  const int  GetPresentPlayersCount(NDb::EFaction faction) const;
  virtual int GetStepLength() const { return stepLength; }
  virtual float GetStepLengthInSeconds() const { return stepLengthInSeconds; }

  virtual void UpdatePlayerStatuses(const NCore::TStatuses & statuses);

  virtual void ExecuteCommands(const NCore::TPackedCommands & commands);

  virtual bool Step(float dtInSeconds, float dtLocal);
  virtual void CalcCRC( IBinSaver& f, bool fast );

  virtual int GetStepNumber() const { return step; }

  void SetMapSize(CVec2 const &_mapSize) { mapSize = _mapSize; }
  CVec2 const& GetMapSize() const { return mapSize; }

  NScene::IScene *GetScene() const { return pScene; }
  float GetTimeElapsed() const {return timeElapsed;}

	void StoreDeadUnit(PFBaseUnit *pUnit);
  
  static NCore::IWorldBase* CreatePFWorld()
  {
    return new NWorld::PFWorld();
  }

  void OnGameFinished( NDb::EFaction failedFaction );
  void GameFinish( NDb::EFaction failedFaction );

  void SetManualGameFinish(bool _manualGameFinish) { manualGameFinish = _manualGameFinish; }
  bool GetManualGameFinish() const { return manualGameFinish; }

  Render::IDebugRender *GetDebugRender() { return debugRender; }

  virtual bool CanCreateClients();

  virtual void Save() const { worldChecker.Save(); }
  virtual void Load() { worldChecker.Load(); }

  virtual void StopMovingUnits();

  void SyncFPUStart( nfpu::ActionType actionType );
  void SyncFPUEnd( nfpu::ActionType actionType );

  void AddAI( PFBaseHero* hero, int lineNumber );
  void RemoveAI( PFBaseHero* hero );

  const NDb::BotsSettings * GetBotsSettings() const;

  void NotifyTalentCastProcessed(const NWorld::PFTalent*);
  void NotifyConsumableProcessed(const NWorld::PFConsumableAbilityData*);
  void NotifyCreepSpawnerCleaned( const NWorld::PFNeutralCreepSpawner* pSpawner, const NWorld::PFBaseUnit* pKiller );

  bool IsFactionDefeated(const NDb::EFaction& faction);
  void SetDefeatedFaction(const NDb::EFaction& faction);

  virtual bool HasProtection() const
  {
#ifndef STARFORCE_PROTECTED
    return false;
#else
    return true;
#endif
  }

  virtual bool PollProtectionResult(NCore::ProtectionResult& result);
  virtual void SetProtectionUpdateFrequency(const int offset, const int frequency);

  const CObj<DayNightController>& GetDayNightController() const { return dayNightController; }

  bool IsDay() const;
  bool IsNight() const;
private:
  void LockOutsideCameraArea(const NDb::AdventureCameraSettings * cameraSettings);
  void InitMinigames();
  void KillDeadUnits( bool fullCleanup = false );
  void LoadPrecachedResources(const NDb::AdvMapDescription * advMapDescription);
  bool LoadSceneMapObjects( const NDb::AdvMapDescription* advMapDesc, const NCore::TPlayersStartInfo & players, const bool isTutorial, LoadingProgress * progress );

  bool CanTrackPlayersBehaviour(const NCore::MapStartInfo& msi) const;

  friend WorldChecker;

  STARFORCE_EXPORT void ProtectionCheck();
};
  
} //namespace NWorld
