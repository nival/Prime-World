#include "stdafx.h"
#include "MapStartup.h"
#include "AsyncMapStartup.h"
#include "MapLoadingUtility.hpp"

#include "PFWorld.h"
#include "Core/CoreFSM.h"
#include "System/SyncProcessorState.h"
#include "System/LoadingProgress.h"
#include "Terrain/Terrain.h"

#include "../System/InlineProfiler.h"
#include "PFAIWorld.h"
#include "PFAIContainer.h"
#include "CommonPathFinder.h"
#include "WarFog.h"

static string s_camera_override;
REGISTER_VAR( "session_camera", s_camera_override, STORAGE_USER );

NI_DEFINE_REFCOUNT( NWorld::MapLoadingJob );


namespace
{
static int g_readWorldFromFile = 0;
}


namespace NWorld
{

MapLoadingJob::MapLoadingJob( NCore::IWorldBase * _world, const NCore::MapStartInfo & _mapStartInfo, const  NDb::AdvMapDescription * _advMapDescription, const NDb::AdvMapSettings * _advMapSettings, const NDb::AdvMap * _advMap, bool _isReconnecting )
: world( dynamic_cast<PFWorld * >( _world ) )
, mapStartInfo( _mapStartInfo )
, advMapDescription (_advMapDescription)
, advMapSettings(_advMapSettings)
, advMap (_advMap)
, isReconnecting(_isReconnecting)
{
  progress = new LoadingProgress;
  progress->InitPartialWeight( EMapLoadStages::Environment,   1.0f );
  progress->InitPartialWeight( EMapLoadStages::Terrain,       1.0f );
  progress->InitPartialWeight( EMapLoadStages::PathFinding,   1.0f );
  progress->InitPartialWeight( EMapLoadStages::Scene,         1.0f );
  progress->InitPartialWeight( EMapLoadStages::MapObjects,    15.0f );
  progress->InitPartialWeight( EMapLoadStages::Heroes,        5.0f );
  progress->InitPartialWeight( EMapLoadStages::HeightMap,     1.0f );
}



bool MapLoadingJob::InitializeEnvironment()
{
  NI_PROFILE_FUNCTION_MEM;

  CObj<NScene::IScene> pScene = world->GetScene();

  NI_VERIFY( pScene, "Can not obtain valid main scene", return false; );

  pScene->LoadTerrain( advMap->terrain );
  pScene->LoadAdvMapLightEnvironment( advMap->lightEnvironment, NDb::LIGHTENVIRONMENT_DAY );
  pScene->LoadAdvMapLightEnvironment( advMap->nightLightEnvironment, NDb::LIGHTENVIRONMENT_NIGHT );

  // CRAP {
  const Terrain::GridConstants & params = pScene->GetGridConstants();
  world->SetMapSize( CVec2( params.worldSize.x, params.worldSize.y ) );

  // ensure height map is ready
  Terrain::Terrain *pTerrain = pScene->GetTerrain();
  pTerrain->Update();  // will build height map
  // CRAP }

  pScene->LoadAdvMapSoundEnvironment( advMap->soundEnvironment );

  if ( !advMap->waterMapFileName.empty() )
  {
    pScene->LoadWaterMap( advMap->waterMapFileName );
  }

  pScene->LoadObjectLayer( 1, advMap->ObjectsLayerFileName );

  return true;
}



bool MapLoadingJob::DoTheJob()
{
  NI_PROFILE_FUNCTION_MEM;

  NI_VERIFY( IsValid(advMapDescription), NStr::StrFmt( "Couldn't get map descriptor '%s'", mapStartInfo.mapDescName.c_str() ), return false );
  NI_VERIFY( IsValid(advMap), NStr::StrFmt( "Couldn't get map for '%s'", mapStartInfo.mapDescName.c_str() ), return false );
  NI_VERIFY( IsValid(advMapSettings), NStr::StrFmt( "Couldn't get map settings for '%s'", mapStartInfo.mapDescName.c_str() ), return false );

  MAP_LOADING_SCOPE(world->GetMapLoadingController());

  // сильная ссылка не даст уничтожить ресурсы, пока карта грузится
  const CObj<PFResourcesCollection> worldResourcesCollection(world->GetResourcesCollection());

  SetupCamera();

  world->SyncFPUStart( nfpu::AT_MAP_LOAD );

  if ( !InitializeEnvironment() )
  {
    NI_ALWAYS_ASSERT( "Failed to initialize world  properly!" );
    return false;
  }
  progress->SetPartialProgress( EMapLoadStages::Environment, 1.0f );

  if ( !world->LoadMap( advMapDescription, camSettings, mapStartInfo.playersInfo, progress, isReconnecting || g_readWorldFromFile ) )
  {
    MAP_LOADING_IP;
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Failed to load map: %s", advMap->GetDBID().GetFileName() ) );
    return false;
  }

  if (g_readWorldFromFile)
  {
    DebugTrace( "Start loading world from file..." );
    world->GetAIWorld()->ClearVoxelMap();
    world->GetWorldChecker()->Load();
    world->Reset();
    if (world->GetAIContainer())
      world->GetAIContainer()->OnReconnect();

    //world->GetFogOfWar()->ResetVisibility(); // No need currently. Visibility is serialized.
    NGlobal::SetVar( "load_world", 1, STORAGE_NONE );
  }

  world->SyncFPUEnd( nfpu::AT_MAP_LOAD );

  DebugTrace( "Map '%s' loaded", advMap->GetDBID().GetFileName().c_str() );
  return true;
}



void MapLoadingJob::SetupCamera()
{
  NI_ASSERT( advMap, "" );

  camSettings = advMap->cameraSettings;

  if ( camSettings )
  {
    if ( !camSettings->name.empty() )
      return;
    if ( s_camera_override.empty() )
      return;
  }

  //Camera is default, check if replacement requested from console var
  const vector<NDb::Ptr<NDb::AdventureCameraSettings>> & cameras = NDb::SessionRoot::GetRoot()->visualRoot->cameras;

  // Weird algo to select/replace camera settings
  // (c) Epic (NUM_TASK)
  NDb::Ptr<NDb::AdventureCameraSettings> defaultCam;
  for ( int i = 0; i < cameras.size(); ++i )
  {
    NI_DATA_VERIFY( cameras[i], NStr::StrFmt( "Null camera resource in '%s'", NDb::SessionRoot::GetRoot()->visualRoot->GetDBID().GetFormatted().c_str() ), continue );

    if ( !defaultCam || cameras[i]->name.empty() )
      defaultCam = cameras[i];

    if ( s_camera_override.empty() )
    {
      if ( cameras[i]->name.empty() )
      {
        camSettings = cameras[i];
        break;
      }
    }
    else if ( !_stricmp( cameras[i]->name.c_str(), s_camera_override.c_str() ) )
    {
      camSettings = cameras[i];
      break;
    }
  }

  NI_VERIFY( camSettings, "No proper camera settings defined", camSettings = defaultCam );
}

} //namespace NWorld


REGISTER_DEV_VAR( "read_world_from_file", g_readWorldFromFile, STORAGE_NONE )
