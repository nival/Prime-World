#include "stdafx.h"
#include "PFWorld.h"
#include "PFPlayer.h"
#include "PFAdvMap.h"
#include "DBAdvMap.h"
#include "TileMap.h"
#include "WarFog.h"
#include "TriggerMarkerHandler.h"
#include "PFWorldNatureMap.h"
#include "PFAIWorld.h"
#include "PFAIContainer.h"
#include "PFStatistics.h"
#include "PFDispatchStrike1.h"
#include "PFPureClientCritter.h"
#include "../System/SyncProcessorState.h"
#include "../System/InlineProfiler.h"
#include "PFBaseMovingUnit.h"
#include "PFBuildings.h"        // for AddMapObject() - building detection
#include "PFLogicDebug.h"
#include "PFGameLogicDebugVisual.h"
#include "DBTalent.h"

#include "Terrain/Terrain.h"
#include "Core/WorldCommand.h"
#include "Core/Transceiver.h"
#include "Core/CoreFSM.h"

#include "PF_Minigames/MinigameSessionInterface.h"

#include "IAdventureScreen.h"

#include "PFBuildings.h"
#include "PFChest.h" 
#include "PFCommonCreep.h"
#include "PFRoadFlagpole.h"
#include "PFScriptedFlagpole.h"
#include "PFGlyph.h"
#include "PFMainBuilding.h"
#include "PFNeutralCreep.h"
#include "PFSimpleObject.h"
#include "PFTower.h"
#include "PFTree.h"
#include "PFMinigamePlace.h"
#include "../Scene/VertexColorManager.h"
#include "PFMaleHero.h"
#include "PFTalent.h"

#include "HeroSpawn.h"
#include "../System/Win32Random.h"
#include "../System/LoadingProgress.h"

#include "PF_Core/EffectsPool.h"

#include "Scripts/FuncCallMacroses.h"

//pathfinding

#include "CommonPathFinder.h"
#include "RoutePathFinder.h"
#include "CollisionResolver.h"

//#include "../Render/debugrenderer.h"
//#include "../Render/renderresourcemanager.h"

#include "PFDebug.h"
#include "PFLogicConst.h"

#ifndef VISUAL_CUTTED
#include "../Client/MainTimer.h"
#endif

#include "HybridServer/Peered.h"

#include "MapLoadingUtility.hpp"

#include "PlayerBehaviourTracking.h"
#include "PFWorldProtection.h"
#include "DayNightController.h"

#include "PFClientVisibilityMap.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NI_DEFINE_REFCOUNT( NGameX::IAdventureScreen );

static NDebug::DebugVar<int> mainPerf_PFWorld_StepId              ( "StepId", "MainPerf" );

static NDebug::DebugVar<int> time_syncTime("Transciever|SyncTime", "" );
static NDebug::DebugVar<int> time_localTime("Transciever|LocalTime", "" );

namespace 
{
  static float g_noTrees = 0.0f;
  REGISTER_DEV_VAR( "no_trees", g_noTrees, STORAGE_NONE );

  DEV_VAR_STATIC bool g_enableBehaviourTracking = true;
  REGISTER_DEV_VAR("enable_behaviour_tracking", g_enableBehaviourTracking, STORAGE_NONE);
}

REGISTER_SAVELOAD_CLASS_NM(PFWorld, NWorld);

namespace NWorld
{
int PFWorld::instanceCount = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<bool checkTrees> class ObjectsLoaderBase : public NonCopyable
{
  virtual PF_Core::WorldObjectBase* CreateObject(const NDb::AdvMapObject &_obj) = 0;

protected:
  PFWorld* const pWorld;
  PFAIContainer* const pAIContainer;
  NScene::IScene* const pScene;

  ObjectsLoaderBase(PFWorld* _pWorld) : pScene(_pWorld->GetScene()), pWorld(_pWorld), pAIContainer(_pWorld->GetAIContainer()) {}

public:
  bool Load(const vector<NDb::AdvMapObject> &objects, int typeId, const char* typeName, int & totalLoaded, LoadingProgress * progress)
  {
    NI_PROFILE_FUNCTION_MEM;
    NHPTimer::STime time;
    NHPTimer::GetTime( time );
    int objCount = 0;

    NScene::MeshVertexColorsManager* const pVCM = pScene->GetMeshVertexColorsManager();

    bool bLoaded = false;
    int idx = 0;
    for ( vector<NDb::AdvMapObject>::const_iterator it = objects.begin(), end = objects.end(); it != end; ++it, ++idx )
    {
      NI_DATA_VERIFY( IsValid( it->gameObject ), NStr::StrFmt("Invalid gameObject assigned to advmap object #%d at %2.3f х %2.3f", it - objects.begin(), it->offset.GetPlace().pos.x, it->offset.GetPlace().pos.y ), continue; );

      if(it->gameObject->GetObjectTypeID() == (DWORD)typeId )
      {
        bLoaded = true;
        if(pVCM)
          pVCM->AdvMapObjectVCBegin(idx);

        if( !checkTrees || g_noTrees <= NWin32Random::Random(0.01f, 1.0f - 0.01f) )
        {
          PF_Core::WorldObjectBase* pObject = CreateObject(*it);
          pObject->SetMapObject(true);
          pAIContainer->RegisterObject(pObject, it->scriptName, it->scriptGroupName);
          ++objCount;
        }

        if(pVCM)
          pVCM->AdvMapObjectVCEnd(idx);

        if ( progress )
          progress->SetPartialProgress( EMapLoadStages::MapObjects, ( ++totalLoaded ) / (float)objects.size() );
      }
    }

    DebugTrace( "%s: %2.3f", typeName, NHPTimer::GetTimePassedAndUpdateTime( time ) );

    return bLoaded;
  }
};

//=================================================================================================================
template<class T, bool checkTrees = false> class ObjectsLoader : public ObjectsLoaderBase<checkTrees>
{
  virtual PF_Core::WorldObjectBase* CreateObject(const NDb::AdvMapObject &_obj) { return new T(pWorld, _obj); }

public:
  ObjectsLoader(PFWorld* _pWorld) : ObjectsLoaderBase(_pWorld) {}
};

template<class T>
bool LoadPureClientObjectsOfType( NGameX::IAdventureScreen* pScreen, NScene::IScene* pScene,
                                  const vector<NDb::AdvMapObject>& objects, int typeId, const char* typeName, int& totalLoaded,
                                  LoadingProgress* progress )
{
  NI_PROFILE_FUNCTION_MEM;
  NHPTimer::STime time;
  NHPTimer::GetTime( time );

  bool bLoaded = false;
  {
    int idx = 0;
    pScreen->ReservePureClientObjects( objects.size() );
    for ( vector<NDb::AdvMapObject>::const_iterator it = objects.begin(); it != objects.end(); it++, idx++ )
    {
      NI_DATA_VERIFY( IsValid( it->gameObject ),
                      NStr::StrFmt( "Invalid gameObject assigned to advmap object #%d at %2.3f х %2.3f",
                                    it - objects.begin(), it->offset.GetPlace().pos.x, it->offset.GetPlace().pos.y ), continue );

      if ( it->gameObject->GetObjectTypeID() != (DWORD)typeId )
      {
        continue;
      }

      if ( pScene->GetMeshVertexColorsManager() )
      {
        pScene->GetMeshVertexColorsManager()->AdvMapObjectVCBegin( idx );
      }
      bLoaded = true;

      if ( pScene->GetMeshVertexColorsManager() )
      {
        pScene->GetMeshVertexColorsManager()->AdvMapObjectVCEnd( idx );
      }

      NGameX::PFPureClientObject* pObject = new T( *it, pScene );
      pScreen->PushPureClientObject( pObject );

      if ( progress )
      {
        totalLoaded++;
        progress->SetPartialProgress( EMapLoadStages::MapObjects, 1.0f * totalLoaded / objects.size() );
      }
    }
  }

  DebugTrace( "%s: %2.3f", typeName, NHPTimer::GetTimePassedAndUpdateTime( time ) );

  return bLoaded;
}


#pragma warning( push )
#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

PFWorld::PFWorld() :
timeElapsed(0.f), 
manualGameFinish(false), 
humanPlayersCount(0),
worldChecker(this),
ambienceMap(NULL), 
stepLength(DEFAULT_GAME_STEP_LENGTH),
protection(),
dayNightController(),
timeScale(NMainLoop::GetTimeScale())
{
}



PFWorld::PFWorld(const NCore::MapStartInfo & info,
                 NScene::IScene * _scene,
                 NGameX::IAdventureScreen * _screen,
                 PFResourcesCollection* _collection,
                 int _stepLength,
                 bool _aiForLeaversEnabled,
                 int _aiForLeaversThreshold) :
step( -1 ),
timeElapsed( 0.f ),
pScene( _scene ),
adventureScreen( _screen ),
manualGameFinish(false),
humanPlayersCount(0),
worldChecker(this), 
ambienceMap(NULL),
resourcesCollection(_collection),
totalCreepsCount(0),
allScriptFunctionsEnabled(false),
stepLength(_stepLength),
stepLengthInSeconds(stepLength/1000.0f),
defeatedFaction(NGameX::FACTION_UNKNOWN),
protection(),
dayNightController(),
timeScale(NMainLoop::GetTimeScale())
{
  NI_PROFILE_FUNCTION

  pTileMap        = new TileMap( this );
  pResolver       = new CollisionResolver( this );
  pAIWorld        = new PFAIWorld( this );
  pNatureMap      = new PFWorldNatureMap(this);
  pStatistics     = new PFStatistics( this );

  dayNightController = new DayNightController(this);

  minigamesMain = NULL;
  //pStatistics->ForAll(StatTrav());

  randGen.SetSeed( info.randomSeed );

  // Map description should already be loaded before< so we just get it from db cache here
  advMapDescription = NDb::Get<NDb::AdvMapDescription>( NDb::DBID( info.mapDescName ) );

  bool aiForLeaversEnabled = false;
  if (_aiForLeaversEnabled)
  {
    if (const NDb::BotsSettings * pDBBotsSettings = GetBotsSettings())
    {
      if (pDBBotsSettings->enableBotsAI)
      {
        bool newbieGame = true;
        for(int i = 0, nPlayers = info.playersInfo.size(); i < nPlayers; ++i)
        {
          const NCore::PlayerStartInfo & desc = info.playersInfo[i];
          if (desc.playerType != NCore::EPlayerType::Invalid && desc.playerInfo.basket != NCore::EBasket::Newbie)
          {
            newbieGame = false;
            break;
          }
        }
        aiForLeaversEnabled = newbieGame;
      }
    }
  }

  const bool enableBehaviourTrackingForThisGame = CanTrackPlayersBehaviour(info);

  players.resize( info.playersInfo.size() );
  for(int i = 0, nPlayers = info.playersInfo.size(); i < nPlayers; ++i)
  {
    const NCore::PlayerStartInfo & desc = info.playersInfo[i];

    // также не отслеживаем поведение ботов и новичков
    const bool enableBehaviourTracking =
      (enableBehaviourTrackingForThisGame) &&
      (desc.userID > 0) &&
      (desc.playerInfo.basket != NCore::EBasket::Newbie);

    players[desc.playerID] = new PFPlayer(
      this,
      desc.playerID,
      desc.teamID,
      desc.originalTeamID,
      desc.userID,
      desc.zzimaSex,
      aiForLeaversEnabled,
      _aiForLeaversThreshold,
      desc.playerInfo.chatMuted,
      enableBehaviourTracking);

    if (players[desc.playerID]->GetUserID() > 0)
    {
      ++humanPlayersCount;
    }
  }

	deadUnits.reserve(20); // 20 dead units per step

  if(instanceCount == 0)
  {
    InitLogicDebugManager();
  }
  ++instanceCount;

  smartRandGen.Init( &randGen );

  protection = PFWorldProtection::Create(this);
}



void PFWorld::OnDestroyContents()
{
  --instanceCount;
  if(instanceCount == 0)
  {
    DeinitLogicDebugManager();
  }

  // cleanup all units
  TObjects objects = GetObjects();
	for(TObjects::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
  {
    if (IsValid(it->second))
    {
      PFBaseUnit *pUnit = dynamic_cast<PFBaseUnit*>(it->second.GetPtr());
      if (pUnit)
        pUnit->CleanupAfterDeath(true);
    }
  }

  KillDeadUnits(true);

  preResources.clear();

#ifndef _SHIPPING
  NDebug::DebugObject::ClearAll();
#endif

  World::OnDestroyContents();
}



void PFWorld::InitMinigames()
{
  NI_PROFILE_FUNCTION;

  NI_ASSERT( pScene, "" );

  NDb::Ptr<NDb::MinigamesBasic> ptr = NDb::Get<NDb::MinigamesBasic>( NDb::DBID( "Minigames/MinigameCommon.xdb" ) );
  minigamesMain = ptr->Construct();
  if (IsValid(minigamesMain))
    minigamesMain->Set( pScene, this );
}



bool PFWorld::LoadMap( const NDb::AdvMapDescription * _advMapDescription, const NDb::AdventureCameraSettings * cameraSettings, const NCore::TPlayersStartInfo & playersInfo, LoadingProgress * progress, bool isReconnecting )
{
  NI_PROFILE_FUNCTION_MEM;

  MAP_LOADING_SCOPE(mapLoadingController);

  advMapDescription = _advMapDescription;

  NDb::Ptr<NDb::AdvMap> advMap = advMapDescription->map;
  NI_VERIFY( IsValid(advMap), "Couldn't get map", return false );

  NDb::Ptr<NDb::AdvMapSettings> advMapSettings = IsValid(advMapDescription->mapSettings) ? (advMapDescription->mapSettings) : (advMap->mapSettings);
  NI_VERIFY( IsValid(advMapSettings), "Couldn't get map settings", return false );

  NI_ASSERT( advMap->ambienceMap.texture, "Couldn't get ambienceMap's texture" );
  if( advMap->ambienceMap.texture )
    ambienceMap = &advMap->ambienceMap;

  allScriptFunctionsEnabled = humanPlayersCount == 1 || advMapSettings->enableAllScriptFunctions;

  triggerMarkerHandler = new TriggerMarkerHandler( this, advMapSettings );

  // Training stuff
  int trainingUserId = -1;
  for ( int i = 0, playersInfoCnt = playersInfo.size(); i < playersInfoCnt; i++ )
  {
    if ( playersInfo[i].playerType == NCore::EPlayerType::Human )
    {
      trainingUserId = playersInfo[i].userID;
      break;
    }
  }
  const bool isTraining = advMapDescription->mapType == NDb::MAPTYPE_TRAINING || advMapDescription->mapType == NDb::MAPTYPE_SERIES;
  // 

  {
    MAP_LOADING_IP;

    NI_PROFILE_BLOCK_MEM( "Phase1" );

    pTileMap->Prepare(advMap->terrain->elemXCount * advMap->terrain->tilesPerElement,
      advMap->terrain->elemYCount * advMap->terrain->tilesPerElement,
      pScene->GetGridConstants().metersPerTile);
    
    LockOutsideCameraArea(cameraSettings);

    pAIWorld->SetVoxelMapSizes(pTileMap);
    pNatureMap->OnLoaded(advMap->terrain);
    progress->SetPartialProgress( EMapLoadStages::Terrain, 1.0f );

    MAP_LOADING_IP;

    pathFinder = new Pathfinding::CCommonPathFinder( pTileMap );
    routPathFinder = new Pathfinding::RoutePathFinder(pathFinder);
    int warFogObstacleVisibility = pTileMap->GetLenghtInTiles(advMap->lightEnvironment->warFogObstacleVisibility);
    warFog = new FogOfWar(this, NDb::KnownEnum<NDb::EFaction>::sizeOf, pTileMap->GetSizeX(), pTileMap->GetSizeY(), 4, warFogObstacleVisibility);

    MAP_LOADING_IP;
    
    if (pNatureMap->GetUseRoadInPathFinding())
    {
      for (int iRoute = 0; iRoute < NDb::KnownEnum<NDb::ENatureRoad>::sizeOf; ++iRoute)
      {
          vector<CVec2> const& road = pNatureMap->GetLogicRoad((NDb::ENatureRoad)iRoute);
          vector<SVector> tileRoad;
          tileRoad.reserve(road.size());

          for (int i = 0; i< road.size(); i++)
            tileRoad.push_back(pTileMap->GetTile(road[i]));

          routPathFinder->AddRoute(tileRoad, 1);
      }
    }

    progress->SetPartialProgress( EMapLoadStages::PathFinding, 1.0f );

    MAP_LOADING_IP;

    pAIWorld->SetMapData(advMapDescription, advMapSettings);

    if ( advMapDescription->scoringTable )
    {
      pStatistics->SetScoringTable( advMapDescription->scoringTable );
    }

#ifndef VISUAL_CUTTED
    MAP_LOADING_IP;

    if (IsValid(pScene))
    {
      if (advMap->bakedLighting.vertexColorsFileName != "")
      {
        pScene->CreateMeshVertexColorsManager();
        pScene->GetMeshVertexColorsManager()->Load(advMap->bakedLighting.vertexColorsFileName);
      }

      pScene->InitSHGrid(advMap->bakedLighting);

      // initialize dynamic lighting
      Render::AABB worldAABB;
      worldAABB.halfSize = 0.5f * pScene->GetGridConstants().worldSize;
      worldAABB.center = worldAABB.halfSize;
      Render::LightsManager* pLightMan = Render::GetLightsManager();
      pLightMan->SetBounds(worldAABB);
      pLightMan->CreateLights(advMap->pointLights);
    }
#endif
  }
  progress->SetPartialProgress( EMapLoadStages::Scene, 1.0f );

  MAP_LOADING_IP;

  pTileMap->ApplyHeightMap(adventureScreen->GetHeightsAsFloat());

  if( !LoadSceneMapObjects( advMapDescription, playersInfo, advMapDescription->mapType == NDb::MAPTYPE_TUTORIAL, progress ) )
    return false;

  LoadPrecachedResources( advMapDescription );

  progress->SetPartialProgress( EMapLoadStages::MapObjects, 1.0f );

  if (IsValid(dayNightController))
    dayNightController->Initialize();

  {
    MAP_LOADING_IP;

    NI_PROFILE_BLOCK_MEM( "Phase2" );

    pTileMap->OnLoaded();

    if (advMap->lightEnvironment->warFogUseHeightsDelta)
    {
      warFog->ApplyHeightMap( adventureScreen->GetHeightsAsFloat(), pScene->GetHeightsController() );
      warFog->ApplyHeightSettings(advMap->lightEnvironment->warFogUseHeightsDelta, 
                                    advMap->lightEnvironment->warFogMaxHeightsDelta);
    }

    MAP_LOADING_IP;

    //
    const float goldPerTeam = advMapSettings->primeSettings.startPrimePerTeam;
    const int goldPerPlayer = static_cast<int>( goldPerTeam / (float)advMapDescription->teamSize );

    PFBaseHero* trainingHero = 0;
    for (int i = 0, count = GetPlayersCount(); i < count; ++i)
    {
      PFBaseHero* pHero = GetPlayer(i)->GetHero();
      if ( pHero )
        pHero->AddGold( goldPerPlayer, false );

      // Get training hero
      if ( isTraining && GetPlayer(i)->GetUserID() == trainingUserId )
          trainingHero = pHero;
      if ( !advMapSettings->enablePortalTalent )
      {
        if ( PFBaseMaleHero* pMaleHero = dynamic_cast<PFBaseMaleHero*>(pHero) )
          pMaleHero->GetPortal()->AddForbid();
      }
    }

    MAP_LOADING_IP;

    // Calculate stats modifier for buildings and creeps
    pAIWorld->ApplyForceModifiers(advMapSettings->force, advMapSettings->trainingForceCoeff, advMapDescription->mapType, trainingHero);

    pAIContainer->BuildIdNameMap();

    pAIContainer->SetScriptAreas( advMap->scriptAreas );

    if (!advMapSettings->scriptFileName.empty())
    {
      NI_ASSERT(pAIContainer, "AIContainer wasn't set before map load finish!");
      vector<NDb::ResourceDesc> null;
      pAIContainer->LoadScript(advMapSettings->scriptFileName, 
        advMapSettings->dictionary ? advMapSettings->dictionary->resources : null, isReconnecting );
    }

    progress->SetPartialProgress( EMapLoadStages::HeightMap, 1.0f );
  }

  return true;
}

void PFWorld::LoadPrecachedResources(const NDb::AdvMapDescription * advMapDescription)
{
  MAP_LOADING_SCOPE(mapLoadingController);

  const int precacheDepth = 20;
  NDb::Ptr<NDb::SessionRoot> pRoot = NDb::SessionRoot::GetRoot();

  const vector<NDb::Ptr<NDb::BasicEffectAttached>> &selfAuraEffects = pRoot->visualRoot->selfAuraEffects;
  const vector<NDb::Ptr<NDb::BasicEffectAttached>> &auraEffects = pRoot->visualRoot->auraEffects.auraEffects;
  const vector<NDb::Ptr<NDb::UnitLogicParameters>> &unitParameters = pRoot->logicRoot->unitLogicParameters->unitParameters;
  
  for( int i = 0; i < selfAuraEffects.size(); i++ )
  {
    CObj<PF_Core::BasicEffect> pEffect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectAttached>( selfAuraEffects[i] );
    pEffect->DieImmediate();
    pEffect->DieImmediate();
  }
  for( int i = 0; i < auraEffects.size(); i++ )
  {
    CObj<PF_Core::BasicEffect> pEffect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectAttached>( auraEffects[i] );
    pEffect->DieImmediate();
    pEffect->DieImmediate();
  }

  NDb::Ptr<NDb::AnimSet> pAnimSet = pRoot->visualRoot->animSets.sets[NDb::ANIMSETID_CREEP];
  preResources[ pAnimSet->GetDBID().GetFileName() ] = pAnimSet;

  for( int i = 0; i < unitParameters.size(); i++ )
  {
    MAP_LOADING_IP_VOID;

    if( unitParameters[i] )
    {
      unitParameters[i]->defaultStats.GetPtr();
      unitParameters[i]->targetingPars.GetPtr();
    }
  }

  for (nstl::map<uint, NDb::Ptr<NDb::MarketingEventRollItem>>::const_iterator i = resourcesCollection->GetMarketingItems().begin(); i!= resourcesCollection->GetMarketingItems().end(); i++)
  {
    MAP_LOADING_IP_VOID;

    NDb::Precache<NDb::MarketingEventRollItem>( (*i).second->GetDBID(), 2, true );
  }
  

  const vector<NDb::Ptr<NDb::AchievBase>> &achievementsList = GetStatistics()->DbScoring()->achievementsList;
  for( int i = 0; i < achievementsList.size(); i++ )
  {
    MAP_LOADING_IP_VOID;

    if(achievementsList[i])
      preResources[ achievementsList[i]->GetDBID().GetFileName() ] = NDb::Precache<NDb::AchievBase>( achievementsList[i]->GetDBID(), precacheDepth );
  }

  if( GetAmbienceMap() )
  {
    GetIAdventureScreen()->PreloadEffectsInResourceTree( GetAmbienceMap()->texture, BADNODENAME );
  }

  preResources[ pRoot->visualRoot->uiEvents->GetDBID().GetFileName() ] = NDb::Precache<NDb::UIEventsCustom>( pRoot->visualRoot->uiEvents->GetDBID(), 5, true ); 
  GetIAdventureScreen()->PreloadEffectsInResourceTree( pRoot->visualRoot->uiEvents, BADNODENAME );

  NDb::Ptr<NDb::ScoringTable> scoring = pRoot->logicRoot->scoringTable;

  GetIAdventureScreen()->PreloadEffectsInResourceTree( scoring, BADNODENAME );

  MAP_LOADING_IP_VOID;

  NDb::Ptr<NDb::AdvMapSettings> advMapSettings = 
    IsValid(advMapDescription->mapSettings) ? (advMapDescription->mapSettings) : (advMapDescription->map->mapSettings);
  NI_VERIFY( IsValid(advMapSettings), "Couldn't get map settings", return; );

  if(advMapSettings->dictionary) 
  {
    const vector<NDb::ResourceDesc> &resources = advMapSettings->dictionary->resources;
    NI_ASSERT(advMapSettings->dictionary->resources.size()!=0, "Resources array in dictionary is empty");

    for( int i = 0; i < resources.size(); i++ )
    {
      MAP_LOADING_IP_VOID;

      NI_VERIFY(resources[i].resource, "Bad resource in dictionary array", continue);
      DebugTrace( "resources[%d]: %s", i, resources[i].resource->GetDBID().GetFileName());
      preResources[ resources[i].resource->GetDBID().GetFileName() ] = 
        NDb::Precache<NDb::DbResource>( resources[i].resource->GetDBID(), 14, true );
      GetIAdventureScreen()->PreloadEffectsInResourceTree( resources[i].resource, BADNODENAME );
    }
  }

  MAP_LOADING_IP_VOID;

  if( advMapSettings->hintsCollection && !advMapSettings->hintsCollection->GetDBID().IsInlined() )
  {
    preResources[ advMapSettings->hintsCollection->GetDBID().GetFileName() ] = 
      NDb::Precache<NDb::HintsCollection>( advMapSettings->hintsCollection->GetDBID(), precacheDepth );
  }

  MAP_LOADING_IP_VOID;

  if( advMapSettings->dialogsCollection && !advMapSettings->dialogsCollection->GetDBID().IsInlined() )
  {
    preResources[ advMapSettings->dialogsCollection->GetDBID().GetFileName() ] = 
      NDb::Precache<NDb::DialogsCollection>( advMapSettings->dialogsCollection->GetDBID(), precacheDepth, true );
  }

  MAP_LOADING_IP_VOID;

  if ( advMapSettings->primeSettings.neutralKillExperienceModifier )
  {
    preResources[ advMapSettings->primeSettings.neutralKillExperienceModifier->GetDBID().GetFileName() ] = 
      NDb::Precache<NDb::KillExperienceModifier>( advMapSettings->primeSettings.neutralKillExperienceModifier->GetDBID(), precacheDepth );
  }

  MAP_LOADING_IP_VOID;

  if ( advMapSettings->overrideBotsSettings && !advMapSettings->overrideBotsSettings->GetDBID().IsInlined() )
  {
    preResources[ advMapSettings->overrideBotsSettings->GetDBID().GetFileName() ] = 
      NDb::Precache<NDb::HintsCollection>( advMapSettings->overrideBotsSettings->GetDBID(), precacheDepth );
  }

  MAP_LOADING_IP_VOID;

  if ( advMapSettings->customBattleStartAnnouncement.imageBurn )
    GetIAdventureScreen()->PreloadEffectsInResourceTree( advMapSettings->customBattleStartAnnouncement.imageBurn, BADNODENAME );

  MAP_LOADING_IP_VOID;

  if ( advMapSettings->customBattleStartAnnouncement.imageFreeze )
    GetIAdventureScreen()->PreloadEffectsInResourceTree( advMapSettings->customBattleStartAnnouncement.imageFreeze, BADNODENAME );

  MAP_LOADING_IP_VOID;

  GetIAdventureScreen()->PreloadEffectsInResourceTree( NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->consumableGroups, BADNODENAME );
}

bool PFWorld::LoadSceneMapObjects( const NDb::AdvMapDescription* advMapDesc, const NCore::TPlayersStartInfo & players, const bool isTutorial, LoadingProgress * progress )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( advMapDesc,          "Invalid advMap resource!", return false );
  NI_VERIFY( IsValid(pScene),  "Invalid scene!",           return false );

  MAP_LOADING_SCOPE(mapLoadingController);
  MAP_LOADING_IP;

  PushDXPoolGuard dxPool("Game objects");

  TSpawnInfo heroesSpawnInfo;
  heroesSpawnInfo.resize( NDb::KnownEnum<NDb::ETeamID>::SizeOf() ); // do not use invalid team

  const vector<NDb::AdvMapObject> &objects = advMapDesc->map->objects;

  int objectsLoaded = 0;
  ObjectsLoader<PFWarFogUnblock>(this).Load(objects, NDb::WarFogUnblock::typeId, "WarFogUnblock", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFSimpleObject>(this).Load(objects, NDb::SimpleObject::typeId, "SimpleObject", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFSimpleObject>(this).Load(objects, NDb::GameObject::typeId, "GameObject", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFSimpleObject>(this).Load(objects, NDb::Road::typeId, "Road", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFRoadFlagpole>(this).Load(objects, NDb::Flagpole::typeId, "Flagpole", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFScriptedFlagpole>(this).Load(objects, NDb::ScriptedFlagpole::typeId, "Flagpole", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFCreepSpawner>(this).Load(objects, NDb::AdvMapCreepSpawner::typeId, "AdvMapCreepSpawner", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFNeutralCreepSpawner>(this).Load(objects, NDb::AdvMapNeutralCreepSpawner::typeId, "AdvMapNeutralCreepSpawner", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFTree, true>(this).Load(objects, NDb::TreeObject::typeId, "TreeObject", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFMultiStateObject>(this).Load(objects, NDb::MultiStateObject::typeId, "MultiStateObject", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFUsableBuilding>(this).Load(objects, NDb::UsableBuilding::typeId, "UsableBuilding", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFSimpleBuilding>(this).Load(objects, NDb::Building::typeId, "Building", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFGlyphSpawner>(this).Load(objects, NDb::GlyphSpawner::typeId, "GlyphSpawner", objectsLoaded, progress); MAP_LOADING_IP;
  ObjectsLoader<PFShop>(this).Load(objects, NDb::Shop::typeId, "Shop", objectsLoaded, progress ); MAP_LOADING_IP;
#ifndef VISUAL_CUTTED
  if( ObjectsLoader<PFMinigamePlace>(this).Load(objects, NDb::MinigamePlace::typeId, "MinigamePlace", objectsLoaded, progress) )
  {
    InitMinigames();
  }
  LoadPureClientObjectsOfType<NGameX::PFPureClientCritter>( adventureScreen, pScene, objects, NDb::Critter::typeId, "Critter", objectsLoaded, progress ); MAP_LOADING_IP;
#endif
  ObjectsLoader<PFTower>(this).Load(objects, NDb::Tower::typeId, "Tower", objectsLoaded, progress); MAP_LOADING_IP;
  progress->SetPartialProgress( EMapLoadStages::MapObjects, 0.95f );

  // должен загружаться последним, так как может унлокать тайлы
  ObjectsLoader<PFAdvMapObstacle, false>(this).Load(objects, NDb::AdvMapObstacle::typeId, "AdvMapObstacle", objectsLoaded, progress); MAP_LOADING_IP;

  {
    NI_PROFILE_BLOCK_MEM( "OtherObjects" );

    // fill map with static objects
    int idx              = 0;
    int objCount         = 0;
    int heroSpawnerCount = 0;
    for ( vector<NDb::AdvMapObject>::const_iterator it = objects.begin(), end = objects.end(); it != end; ++it, ++idx )
    {
      MAP_LOADING_IP;

      NI_DATA_VERIFY( IsValid( it->gameObject ), NStr::StrFmt("Invalid gameObject assigned to advmap object #%d at %2.3f х %2.3f", it - objects.begin(), it->offset.GetPlace().pos.x, it->offset.GetPlace().pos.y ), continue; );
      if (pScene->GetMeshVertexColorsManager())
      {
        pScene->GetMeshVertexColorsManager()->AdvMapObjectVCBegin(idx);
      }

      PF_Core::WorldObjectBase* pObject = 0;
      switch ( it->gameObject->GetObjectTypeID() )
      {
      case NDb::HeroPlaceHolder::typeId:
        if(NDb::HeroPlaceHolder const* placeholder = dynamic_cast<NDb::HeroPlaceHolder const*>(it->gameObject.GetPtr()))
        {
          ++objCount;
          ++heroSpawnerCount;
          HeroSpawnInfo info;
          info.placement   = it->offset.GetPlace();
          info.placeholder = placeholder;

          heroesSpawnInfo[placeholder->teamId].push_back(info);
        }
        break;
      case NDb::Quarter::typeId:
        ++objCount;
        pObject = new PFQuarters(this, *it);
        break;
      case NDb::MainBuilding::typeId:
        {
          ++objCount;
          PFMainBuilding* const mb = new PFMainBuilding(this, *it);
          mainBuildings.push_back(mb);
          pObject = mb;
        }
        break;
      case NDb::Fountain::typeId:
        ++objCount;
        pObject = new PFFountain(this, *it);
        break;
      case NDb::AdvMapCameraSpline::typeId:
        pAIContainer->RegisterCameraSpline( it->gameObject->GetDBID(), it->offset.GetPlace() );
        break;
      case NDb::ScriptPath::typeId:
        pAIContainer->RegisterScriptPath( it->scriptName, dynamic_cast<const NDb::ScriptPath*>(it->gameObject.GetPtr()) );
      case NDb::ScriptPolygonArea::typeId:
        pAIContainer->RegisterPolygonArea( it->scriptName, dynamic_cast<const NDb::ScriptPolygonArea*>(it->gameObject.GetPtr()) );
        break;
      }

      if (pObject)
      {
        pAIContainer->RegisterObject(pObject, (*it).scriptName, (*it).scriptGroupName );
      }

      if (pScene->GetMeshVertexColorsManager())
      {
        pScene->GetMeshVertexColorsManager()->AdvMapObjectVCEnd(idx);
      }
    }

    MAP_LOADING_IP;

    // yes, it's hacky
    if ( heroSpawnerCount )
    {
      bool spawned = SpawnHeroes( this, advMapDesc, players, isTutorial, &heroesSpawnInfo, pScene, progress );
      MAP_LOADING_IP;
      NI_ASSERT( spawned, "Failed to spawn players!" );
    }
  }

  return true;

}


PFPlayer* PFWorld::GetPlayer(int id) const
{
  NI_VERIFY(0<= id && id < players.size(), "Trying to get player by wrong id!", return NULL; );
  return players[id];
}

PFPlayer* PFWorld::GetPlayerByUID(int userId) const
{
  for (int i = 0; i < players.size(); i++)
  {
    NWorld::PFPlayer * player = players[i];

    if (player && player->GetUserID() == userId)
    {
      return player;
    }
  }
  return 0;
}

const int  PFWorld::GetPresentPlayersCount() const
{
  int count = 0;
  for(vector<CObj<PFPlayer> >::const_iterator it = players.begin(), end = players.end(); it != end; ++it)
    if((*it)->GetHero())
      ++count;

  return count;
}

const int  PFWorld::GetPresentPlayersCount(NDb::EFaction faction) const
{
  int count = 0;

  for (vector<CObj<PFPlayer> >::const_iterator it = players.begin(), end = players.end(); it != end; ++it)
    if (const PFBaseHero * pHero = (*it)->GetHero())
      if (pHero->GetFaction() == faction)
        ++count;

  return count;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::UpdatePlayerStatuses(const NCore::TStatuses & statuses)
{
  for (int i = 0; i < statuses.size(); ++i)
  {
    if (PFPlayer * player = GetPlayerByUID(statuses[i].clientId))
    {
      const NCore::ClientStatus & clientStatus = statuses[i];

      // пишем в статистику
      PFBaseHero* hero = player->GetHero();
      if ( hero )
      {
        NWorld::PFHeroStatistics* stat = hero->GetHeroStatistics();
        if ( stat )
        {
          stat->SetLeaveStatus( clientStatus.status );
          if ( clientStatus.status == Peered::Away )
            stat->AddAfk();
        }
      }

      adventureScreen->OnClientStatusChange(clientStatus.clientId, clientStatus.status, clientStatus.step);

      {
        const bool disconnected = Peered::IsDisconnectedStatus(clientStatus.status);
        const bool leaver = (clientStatus.status == Peered::RefusedToReconnect);

        player->SetDisconnected(disconnected, leaver);
      }

      bool isPlayingOld = player->IsPlaying();
      bool isPlayingNew = Peered::IsPlayingStatus(clientStatus.status);

      if (isPlayingOld != isPlayingNew)
      {
        player->SetIsPlaying(isPlayingNew);

        if (!isPlayingNew)
        {
          adventureScreen->OnPlayerDisconnected(player, clientStatus.step);
        }
      }

      bool isActiveOld = player->IsActive();
      bool isActiveNew = (clientStatus.status == Peered::Active);

      if (isActiveOld != isActiveNew)
      {
        player->SetIsActive(isActiveNew);

        const bool afk = (clientStatus.status == Peered::Away);

        if (afk)
          PlayerBehaviourTracking::DispatchEvent(player, EPlayerBehaviourEvent::Gone);
      }
    }
    else
    {
      NI_ALWAYS_ASSERT(NStr::StrFmt("UpdatePlayerStatuses: Player not found (uid=%d)", statuses[i].clientId));
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::ExecuteCommands(const NCore::TPackedCommands & commands)
{
  NI_PROFILE_FUNCTION

  SyncFPUStart( nfpu::AT_CMD_EXECUTE );

  for( NCore::TPackedCommands::const_iterator it = commands.begin(); it != commands.end(); ++it )
  {
    CObj<NCore::WorldCommand> wcmd = (*it)->GetWorldCommand( GetPointerSerialization() );

    if ( wcmd && wcmd->CanExecute() )
    {
      wcmd->Execute( this );
    }
  }

  SyncFPUEnd( nfpu::AT_CMD_EXECUTE );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFWorld::Step(float dtInSeconds, float dtLocal)
{
  NI_PROFILE_FUNCTION

  SyncFPUStart( nfpu::AT_WORLD_STEP );

  if( IsPaused() )
  {
    if ( IsValid( pAIContainer ) ) 
      pAIContainer->Step( dtInSeconds );

    SyncFPUEnd( nfpu::AT_WORLD_STEP );

    return true;
  }

  if (GetDebugRender())
  {
    NI_PROFILE_BLOCK( "Debug Render clear" );
    GetDebugRender()->ClearBuffer(Render::DRBUFFER_STEP);
  }

	NI_VERIFY(dtInSeconds > 0 || dtLocal > 0, "Stepping PFWorld with zero time deltas", return true);

  time_syncTime.AddValue( dtInSeconds * 1000.f );
  time_localTime.AddValue( dtLocal * 1000.f );

  if(dtInSeconds <= 0 && dtLocal > 0)
    return true;

  ++step;
  mainPerf_PFWorld_StepId.SetValue(step);
  {
    timeElapsed += dtInSeconds;

    pAIWorld->Update(dtInSeconds);

    {
      NI_PROFILE_BLOCK( "CoreStep" );

      LogStepBegin(step);
      PF_Core::World::Step(dtInSeconds, dtLocal); // step parent class

		  KillDeadUnits();
    }
  }

  {
    NI_PROFILE_BLOCK( "update movements and warfog" );
    MovingUnit::UpdateMovements( GetAIWorld(), pResolver, GetTileMap(), dtInSeconds );
    if ( IsValid( warFog ) )
      warFog->StepVisibility(dtInSeconds);  
    pNatureMap->OnStep(dtInSeconds);
  }

#ifdef STARFORCE_PROTECTED
  {
    NI_PROFILE_BLOCK("protection update");
    protection->Update();
  }
#endif // STARFORCE_PROTECTED

  {
    NI_PROFILE_BLOCK("day-night controller update");
    if (IsValid(dayNightController))
      dayNightController->Update(dtInSeconds);
  }

  // step statistics system
  pStatistics->OnStep(dtInSeconds);

  if( IsValid( triggerMarkerHandler ) )
    triggerMarkerHandler->Step(dtInSeconds);

  if ( minigamesMain )
    minigamesMain->Step( dtInSeconds );

  if ( IsValid( pAIContainer ) ) 
    pAIContainer->Step( dtInSeconds );

  smartRandGen.Cleanup();

  SyncFPUEnd( nfpu::AT_WORLD_STEP );

#ifndef VISUAL_CUTTED
	NMainLoop::MarkStepFrame();
#endif
  
#ifndef _SHIPPING
  NDebug::DebugObject::ProcessAll( GetDebugRender() );
#endif  

  ProtectionCheck();

  return true;
}


void PFWorld::CalcCRC( IBinSaver& f, bool fast )
{
  if ( !fast )
  {
    CPtr<PFWorld> pTmp(this); 
    f.Add( 1, &pTmp );
  }
  else
  {
    int idChunk = 0;

    for(int i = 0, size = players.size(); i < size; ++i)
    {
      PFPlayer* player = players[i];
      if ( !IsValid( player ) )
        continue;
      PFBaseHero* hero = player->GetHero();
      if ( !IsValid( hero ) )
        continue;

      int subChunkId = 0;

      f.StartChunk(idChunk, 1, IBinSaver::CHUNK_COBJECTBASE);

      CVec3 pos = hero->GetPosition();
      f.Add( ++subChunkId, &pos );
      float value;
      value = hero->GetHealth();
      f.Add( ++subChunkId, &value );
      value = hero->GetMana();
      f.Add( ++subChunkId, &value );
      value = hero->GetNafta();
      f.Add( ++subChunkId, &value );

      for( int stat = 0; stat < NDb::KnownEnum<NDb::EStat>::sizeOf; ++stat )
      {
        value = hero->GetStat( (NDb::EStat)stat )->GetValue();
        f.Add( ++subChunkId, &value );
      }

      PlayerBehaviourTracking::UpdateFastCRC(player, f, ++subChunkId);

      f.FinishChunk();

      ++idChunk;
    }

    {
      int subChunkId = 0;

      f.StartChunk(idChunk, 1, IBinSaver::CHUNK_COBJECTBASE);

      if (PFScript * pLuaScript = pAIContainer->GetLuaScript())
      {
        f.Add(++subChunkId, pLuaScript);
      }

      if (IsValid(dayNightController))
      {
        float value = dayNightController->GetNightFraction();
        f.Add(++subChunkId, &value);
      }

      // timescale
      {
        float value = GetTimeScale();
        f.Add(++subChunkId, &value);
      }

//       // double check timescale - check global var
//       {
//         float value = NMainLoop::GetTimeScale();
//         f.Add(++subChunkId, &value);
//       }

#ifdef _SHIPPING
      // visibility map mode
      {
        DI_WEAK(NGameX::VisibilityMapClient) visMap;

        bool value = true;

        if (IsValid(visMap) && NGameX::EVisMapMode::IsValid(visMap->GetMode()))
        {
          // TODO: double check?
          if (GetIAdventureScreen()->IsSpectator())
          {
            value =
              (visMap->GetMode() == NGameX::EVisMapMode::Combined) ||
              (visMap->GetMode() == NGameX::EVisMapMode::FromFaction(GetIAdventureScreen()->GetPlayerFaction()));

            // NUM_TASK hacky "fix" to overcome visMap mode changing lag after switching to another player
            {
              static unsigned failures = 0U;
              static const unsigned failuresAllowed = 2U;

              if (value)
              {
                failures = 0U;
              }
              else if (failures < failuresAllowed)
              {
                ++failures;

                value = true;
              }
            }
          }
          else
          {
            value =
              (visMap->GetMode() == NGameX::EVisMapMode::FromFaction(GetIAdventureScreen()->GetPlayerFaction()));
          }
        }

        f.Add(++subChunkId, &value);
      }

      // main buildings
      {
        for (int i = 0, count = mainBuildings.size(); i < count; ++i)
        {
          PFMainBuilding* const mb = mainBuildings[i];

          float value = mb->GetHealth();
          f.Add(++subChunkId, &value);
          value = mb->GetMaxHealth();
          f.Add(++subChunkId, &value);
        }
      }
#endif

      f.FinishChunk();

      ++idChunk;
    }
  }
}


void PFWorld::StoreDeadUnit(PFBaseUnit *pUnit)
{
  NI_ASSERT( step != -1, "Kill unit before world create! Reconnect may fail!" ); // NUM_TASK
	deadUnits.push_back(CObj<PFBaseUnit>(pUnit));
}

//////////////////////////////////////////////////////////////////////////
void PFWorld::UnregisterCreep(const PFCommonCreep*) 
{ 
  NI_VERIFY(totalCreepsCount > 0, "Nothing to unregister!", return); 
  --totalCreepsCount; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::OnGameFinished( NDb::EFaction failedFaction )
{
  if (!manualGameFinish && IsFactionDefeated(failedFaction))
  {
    GameFinish( failedFaction );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::GameFinish( NDb::EFaction failedFaction )
{
  //PFAIWorld::OnGameFinished() resets voting info;
  //GetSurrenderVotes() should be called before
  int surrenderVotes = pAIWorld->GetSurrenderVotes( failedFaction );

  pAIWorld->OnGameFinished( failedFaction );
  adventureScreen->OnVictory( failedFaction, surrenderVotes );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::KillDeadUnits(bool fullCleanup)
{
  NI_PROFILE_FUNCTION

  for (int i = 0; i < deadUnits.size(); ++i)
  {
    if (PFBaseUnit * unit = deadUnits[i])
    {
      unit->CleanupAfterDeath(fullCleanup);
    }
    else
    {
      NI_ALWAYS_ASSERT_TRACE( "Dead unit already removed" );
    }
  }

  deadUnits.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFWorld::CanCreateClients()
{
  return adventureScreen ? adventureScreen->CanCreateClients() : false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::StopMovingUnits()
{
  if (pAIWorld)
  {
    struct MovingUnitStopper : public NonCopyable
    {
      void operator()(NWorld::PFLogicObject & object)
      {
        if (PFBaseMovingUnit * unit = dynamic_cast<PFBaseMovingUnit*>(&object))
          unit->Stop();
      }
    } movingUnitStopper;

    pAIWorld->ForAllUnits(movingUnitStopper);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::SyncFPUStart( nfpu::ActionType actionType )
{
  fPUState = GetProcessorState();
  SyncProcessorState();
  fPUStatesData.SetStartState( actionType, GetProcessorState() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::SyncFPUEnd( nfpu::ActionType actionType )
{
  fPUStatesData.SetFinishState( actionType, GetProcessorState() );
  SetProcessorState( fPUState );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::AddAI( PFBaseHero* hero, int line )
{
  NI_VERIFY(hero, "Invalid hero!", return;);

  if (pAIContainer)
    pAIContainer->Add( hero, line );

  if (adventureScreen)
    adventureScreen->OnStartAiForPlayer( hero->GetPlayer() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::RemoveAI( PFBaseHero* hero )
{
  NI_VERIFY(hero, "Invalid hero!", return;);

  if (pAIContainer)
    pAIContainer->Remove( hero );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::BotsSettings * PFWorld::GetBotsSettings() const
{
  NI_VERIFY(IsValid(advMapDescription), "Invalid map description!", return 0;);

  const NDb::BotsSettings * pDBBotsSettings = 0;

  const NDb::AdvMapSettings * desc = IsValid(advMapDescription->mapSettings) ? advMapDescription->mapSettings 
                                                                             : advMapDescription->map->mapSettings;

  NI_VERIFY(desc, "Invalid map settings!", return 0;);

  pDBBotsSettings = IsValid(desc->overrideBotsSettings) ? desc->overrideBotsSettings : GetAIWorld()->GetAIParameters().botsSettings;

  return pDBBotsSettings;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::LockOutsideCameraArea(const NDb::AdventureCameraSettings * cameraSettings )
{
  NI_PROFILE_FUNCTION
  NI_VERIFY(cameraSettings, "invalid camera", return);
  NI_VERIFY(IsValid(pTileMap), "invalid tile map", return);
  
  int xrad = pTileMap->GetLenghtInTiles(cameraSettings->limitRadiusHor);
  int yrad = pTileMap->GetLenghtInTiles(cameraSettings->limitRadiusVert);

  // Apply lock multipliers, if they are not zero
  if (cameraSettings->lockMultRadiusHor)
    xrad *= cameraSettings->lockMultRadiusHor;
  if (cameraSettings->lockMultRadiusVert)
    yrad *= cameraSettings->lockMultRadiusVert;

  int width = pTileMap->GetSizeX();
  int height = pTileMap->GetSizeY();

  SVector center(width/2, height/2);

  // Apply locking circle center offsets: first - camera offset, 
  // second - lock ofset relative to the camera offset.
  center += cameraSettings->centerOffset + cameraSettings->lockCenterOffset;

  vector<SVector> lockedTiles;
  lockedTiles.reserve(300000);

  for (int i=0; i<width; i++)
  {
    for (int j=0; j<height;j++)
    {
      SVector pos(i,j);
      pos-=center;

      bool outside = (fabs2(pos.x)/fabs2(xrad) + fabs2(pos.y)/fabs2(yrad))>1;  
      if (outside)
      {
        lockedTiles.push_back(SVector(i,j));
      }
    }
  }
  pTileMap->MarkObject(lockedTiles, true, MAP_MODE_BUILDING);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::Reset()
{
  deadUnits.reserve(20); // 20 dead units per step

  smartRandGen.Init( &randGen );

  ResetClientObjects();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::ResetClientObjects()
{
  adventureScreen->OnTimeScaleChanged(timeScale);

	TObjects& objs = GetObjects();

	for (TObjects::iterator it = objs.begin(); it != objs.end(); it++ )
	{
		if ( IsValid(it->second) )
			it->second->DoReset();
	}

	TWeakObjects& weakObjs = GetWeakObjects();

	for (TWeakObjects::iterator it = weakObjs.begin(); it != weakObjs.end(); it++ )
	{
		if ( IsValid(it->second) )
			it->second->DoReset();

	}
}

void PFWorld::NotifyTalentCastProcessed( const PFTalent* pTalent)
{
  if(!IsValid(pTalent)) return;
  if (PFScript * pScript = pAIContainer->GetLuaScript())
  {
    string talentId = pTalent->GetTalentDesc()->persistentId;
    const CPtr<PFBaseUnit> pOwner = pTalent->GetOwner();
    int ownerWOID = IsValid(pOwner) ? pOwner->GetWOID() : 0;

    CALL_LUA_FUNCTION_ARG2( pScript, "OnTalentCastProcessed", false, talentId, ownerWOID);
  }
}

void PFWorld::NotifyConsumableProcessed( const PFConsumableAbilityData* pConsumable)
{
  if(!IsValid(pConsumable)) return;

  if (PFScript * pScript = pAIContainer->GetLuaScript())
  {
    string talentId = IsValid(pConsumable->GetUsingConsumable()) ? pConsumable->GetUsingConsumable()->GetDBDesc()->persistentId : "";
    const PFAbilityData* pAbilityData = dynamic_cast<const PFAbilityData*>(pConsumable);
    PFBaseUnit* pOwner = IsValid(pAbilityData)? pAbilityData->GetOwner() : NULL;
    int ownerWOID = IsValid(pOwner) ? pOwner->GetWOID() : 0;
    
    CALL_LUA_FUNCTION_ARG2( pScript, "OnConsumableCastProcessed", false, talentId, ownerWOID);
  }
}

void PFWorld::NotifyCreepSpawnerCleaned( const PFNeutralCreepSpawner* pSpawner, const PFBaseUnit* pKiller )
{
  if( !IsValid(pSpawner) ) return;

  if (PFScript * pScript = pAIContainer->GetLuaScript())
  {
    CALL_LUA_FUNCTION_ARG2( pScript, "OnCreepSpawnerCleaned", false, pSpawner->GetSpawnerName(), 
      IsValid(pKiller) ? pKiller->GetWOID() : -1);
  }
}

bool PFWorld::IsFactionDefeated(const NDb::EFaction& faction)
{ 
  return defeatedFaction == static_cast<int>(faction) ? true : false;
}

void PFWorld::SetDefeatedFaction(const NDb::EFaction& faction)
{ 
  if(defeatedFaction == NGameX::FACTION_UNKNOWN)
    defeatedFaction = static_cast<int>(faction);
}

bool PFWorld::CanTrackPlayersBehaviour(const NCore::MapStartInfo& msi) const
{
  const bool replayMode = !msi.replayName.empty();

  if (replayMode)
  {
    DebugTrace("Player behaviour tracking is disabled in replay mode");
    return false;
  }

  bool canTrack = g_enableBehaviourTracking;

#ifdef _SHIPPING
  if (canTrack)
  {
    if (msi.isCustomGame)
      canTrack = false;
  }

  if (canTrack)
  {
    NI_ASSERT(IsValid(advMapDescription), "");

    if (advMapDescription->mapType != NDb::MAPTYPE_PVP)
      canTrack = false;
  }

  if (canTrack)
  {
    NCore::TPlayersStartInfo::const_iterator it = msi.playersInfo.begin();
    NCore::TPlayersStartInfo::const_iterator it_end = msi.playersInfo.end();
    for (; it != it_end; ++it)
    {
      NCore::TPlayersStartInfo::const_reference psi = *it;

      if (psi.userID > 0)
        continue;

      canTrack = false;
      break;
    }
  }
#endif

  DebugTrace("Player behaviour tracking is %s for this game", (canTrack ? "enabled" : "disabled"));

  return canTrack;
}

bool PFWorld::PollProtectionResult(NCore::ProtectionResult& result)
{
  return protection ? protection->PopResult(result) : false;
}

void PFWorld::SetProtectionUpdateFrequency(const int offset, const int frequency)
{
  if (IsValid(protection))
    protection->SetUpdateFrequency(offset, frequency);
}

bool PFWorld::IsDay() const
{
  if (IsValid(dayNightController))
    return dayNightController->IsDay();
  return true;
}

bool PFWorld::IsNight() const
{
  if (IsValid(dayNightController))
    return dayNightController->IsNight();
  return false;
}

} // namespace NWorld
