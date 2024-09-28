#include "stdafx.h"
#include "Easel.h"

#include "../System/Basic.h"
#include "../Scene/SceneObjectCreation.h"

#include "../UI/Root.h"
#include "../UI/Window.h"

#include "EaselWorldClientConvertHelper.h"

#include "EaselWorld.h"
#include "LuxBoost.h"
#include "EaselView.h"
#include "EaselSoundsInterface.h"

#include "LuxGameLogic.h"
#include "BoostBoard.h"
#include "LuxGameBoard.h"

#include "../Render/debugrenderer.h"
#include "../PF_Core/BasicEffect.h"
#include "../PF_Core/EffectsPool.h"
#include "../PF_Core/LightningEffect.h"

#include "LuxDef.h"

#include "System/RandomGenerator.h"

#include "PF_GameLogic/AdventureScreen.h"

namespace PF_Minigames
{

static float g_easelElevation = 0.0f;
REGISTER_DEV_VAR("Easel_Elevation",g_easelElevation, STORAGE_NONE);

static bool g_isEaselPrefetched = false; 


Easel::Easel( PF_Core::IWorld* _pWorld ) :
  PF_Core::WorldObjectBase( _pWorld, false ),
  firstTrajectory(true),
  lastTrajectory(-1),
  randomSeed(0)
{
  int precacheDepth = 20;
  easelData = NDb::Precache<NDb::DBEaselData>(NDb::DBID("Minigames/Minigame02/GameLogic/EaselMinigameData.xdb"), precacheDepth );
  NI_VERIFY( !easelData.IsEmpty(), "DB resource for 'Easel' minigame should be valid", return );

  trajectoryUseCount.resize( easelData->game->trajectories.size(), 0 );

  currentBoost[0] = NDb::BOOSTTYPE_PAINTBLAST;
  currentBoost[1] = NDb::BOOSTTYPE_ALCHEMIST;
  currentBoost[2] = NDb::BOOSTTYPE_SORTER;
}

Easel::~Easel()
{
  Render::UnloadTexturePool( this );
}

bool Easel::Init( NScene::IScene * _scene, IWorldSessionInterface * _worldSessionFace, const CVec3 & _minigamePos )
{
  if( !_scene )
    return false;

  NI_ASSERT( _worldSessionFace , "" );

  convertHelper = new EaselWorldClientConvertHelper();
  easelStatistics.SetEasel( this );

  scene = _scene;
  worldSessIFace = _worldSessionFace;
 
  easelNotifier = new EaselNotifier( GetPFWorld() );

  world = CreateWorldObject();
  view = CreateViewObject( this );
 
  // must be placed first because of the initialization ....
  world->Init(*this);         // initializing logic

  // helper object initialization
  convertHelper->Init(CPtr<Easel>(this), _minigamePos);
  client.Reset( true );
  
  return true;
}

int Easel::GetBoostPrice( NDb::EBoostType _type )
{
  switch( _type )
  {
  case NDb::BOOSTTYPE_PAINTBLAST: return easelData->gameboosts.paintblast.boostBase.price; 
  case NDb::BOOSTTYPE_FREEZE: return easelData->gameboosts.freeze.boostBase.price; 
  case NDb::BOOSTTYPE_JOKER: return easelData->gameboosts.joker.boostBase.price; 
  case NDb::BOOSTTYPE_SORTER: return easelData->gameboosts.sorter.boostBase.price; 
  case NDb::BOOSTTYPE_MAGNET: return easelData->gameboosts.magnet.boostBase.price; 
  case NDb::BOOSTTYPE_ALCHEMIST: return easelData->gameboosts.alchemist.boostBase.price; 
  }

  return 0;
}


int Easel::GetLevelBoostCount( int levelID )
{
  if ( levelID == 0 )
    return 0;
  else
    return easelData->gameboosts.slots[ levelID ] + 1;
}

int Easel::GetRegenerateBoostPrice( int levelID )
{
  NDb::EBoostsCategory currCategory = easelData->gameboosts.slots[ levelID ];  // levels match zero
  return easelData->gameboosts.regenPrices[ currCategory ];
}


bool Easel::CanRegenerateBoosts( int levelID, int gold )
{
  if ( !easelData->gameboosts.canReroll[ levelID ] )
    return false;

  return ( GetRegenerateBoostPrice( levelID ) <=  gold );
}

void Easel::GetBoostTypesForSlot( int slotID, int levelID, BoostTypes& types, NDb::EBoostType exceptType )
{
  if ( levelID == 0 )
    return;

  if ( slotID == 0 && levelID == 1 )
  {
    types.push_back( NDb::BOOSTTYPE_PAINTBLAST );
  }

  int _numBoosts = NDb::KnownEnum<NDb::EBoostType>::SizeOf();

  for ( int i = 0; i < _numBoosts; ++i )
  {
    if( easelData->gameboosts.boostsTemplate[i].boostCategory == slotID &&
        easelData->gameboosts.boostsTemplate[i].boostUsage == NDb::BOOSTUSAGE_INGAME &&
        i != exceptType )
    {
      types.push_back( (NDb::EBoostType)i );
    }
  } 
}

void Easel::RegenerateBoosts( bool haveToBuy, int levelID, int seed )
{
  CPtr<IPriestessProxy> priestess = world->GetPriestessProxy();

  if ( !CanRegenerateBoosts( levelID, priestess->GetGold() ) )
    return;

  int levelBoostCount = GetLevelBoostCount( levelID );

  int slotToChange = NRandom::RandomFromSeed( seed, 0, levelBoostCount - 1 );

  BoostTypes newTypes;
  GetBoostTypesForSlot( slotToChange, levelID, newTypes, currentBoost[ slotToChange ] );

  if ( newTypes.empty() )
    return;

  NDb::EBoostType newType = newTypes[ NRandom::RandomFromSeed( seed, 0, newTypes.size() - 1 ) ];
  currentBoost[ slotToChange ] = newType;

  if ( haveToBuy )
    priestess->TakeGold( GetRegenerateBoostPrice( levelID ) );
}

bool Easel::ChangePlacement(const Placement& _placement)
{
  if(IsValid(convertHelper) ==  false)
    return false;

  NI_ASSERT(_placement.scale.x == _placement.scale.y && _placement.scale.y == _placement.scale.z,  "Easel: minigame placement scale is non unified" );

  easelPlacement = _placement;

  easelPlacement.pos.z += g_easelElevation;

  convertHelper->SetPlacement(easelPlacement);

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Easel::CheatResetCooldowns()
{
  CPtr<LuxBoostBoard> boostBoard = world->GetLogic()->GetBoostBoard();

  if ( !IsValid( boostBoard ) )
    return;

  for ( Boosts::const_iterator it = boostBoard->GetBoosts().begin(); it != boostBoard->GetBoosts().end(); ++it )
  {
    (*it)->ResetCooldown();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Easel::CheatWinGame()
{
  DevTrace("Easel::CheatWinGame()");
  CPtr<LuxGameBoard> gameBoard = world->GetLogic()->GetGameBoard();

  if ( !IsValid( gameBoard ) )
    return;
  
  gameBoard->SetBoardState(BOARDSTATE_LEVEL_WON);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Easel::StartLevel( int paintId, int levelID, int seed, NWorld::PFEaselPlayer* player )
{
  DebugTrace( "Easel::StartLevel!" );

  if ( !IsValid(world) || !IsValid(view) )
    return;

  view->Reset();
  client.Reset( false );

  // setting random 
  SetRandomSeed(seed);

  // get pointer to new level statistics 
  const CObj<EaselLevelStatistics>& levelStatistics 
    = easelStatistics.StartGatherFoNewLevel( PF_Core::WorldObjectBase::GetWorld(), paintId, levelID);

  world->GetPriestessProxy()->ClearRewardItem();

  world->StartGame(levelID, levelStatistics, player );

  view->InitAfterWorld( world );
}

void Easel::StopLevel()
{
  if ( IsValid( view ) && IsValid( world ) )
    view->ReleaseAfterWorld( world );

  DebugTrace( "Easel::StopLevel!" );

  if( IsValid( world ) )
    world->StopGame();

  client.Reset( false );

  if ( IsValid( view ) )
    view->Reset();
  
  easelStatistics.StopGatherForLevel();
}

bool Easel::PauseLevel( bool _fPause )
{
  if ( _fPause  )
  {
    GetWorld()->GetSound()->OnGamePaused();
  }
  else
  { 
    GetWorld()->GetSound()->OnGameResumed();
  }

  return true;
}

void Easel::StepM( float deltaTime )
{
  client.Step( deltaTime );

  if( IsValid( view )  && IsValid( world ) )
    view->Step( deltaTime, world );
}

bool Easel::Update( float deltaTime, bool gameOnPause )
{
  client.Update( deltaTime, gameOnPause );

  if( IsValid( view ) )
    view->Update( deltaTime, world );
  
  return true;
}

bool Easel::ProcessMouseMove(const CVec2& _pos)
{
  NI_ALWAYS_ASSERT("illegal call");
  return false;
}

bool Easel::ProcessMouseEvent( EEaselMouseEvents::Enum _key )
{
  NI_ALWAYS_ASSERT("illegal call");
  return false;
}


bool Easel::ProcessKeyboardEvent( EEaselKeyboardEvents::Enum event )
{
  return world ? world->ProcessKeyboardEvent( event ) : false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Easel::ReserveSceneObject( const NDb::Ptr<NDb::DBSceneObject>& db, int reserve )
{
  if(!IsValid(db))
  {
    return;
  }

  NScene::SceneObjectsPool::Get()->Reserve(GetScene(), db, reserve, BADNODENAME );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Easel::ReserveStandaloneEffect( const NDb::Ptr<NDb::BasicEffectStandalone>& db, int reserve )
{
  if(!IsValid(db))
  {
    return;
  }

  CObj<PF_Core::BasicEffectStandalone> effect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectStandalone>(db);
  effect->DieImmediate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Easel::ReserveAttachedEffect( const NDb::Ptr<NDb::BasicEffectAttached>& db, int reserve )
{
  if(!IsValid(db))
  {
    return;
  }

  CObj<PF_Core::BasicEffectAttached> effect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectAttached>(db);
  effect->DieImmediate();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselWorld* Easel::CreateWorldObject()
{
  NI_ALWAYS_ASSERT("illegal call");
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselView* Easel::CreateViewObject( Easel* _easel )
{
  NI_ALWAYS_ASSERT("illegal call");
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Easel::PrefetchData()
{
  if ( g_isEaselPrefetched )
    return;

  g_isEaselPrefetched = true;

  for ( int i = 0; i < easelData->artifacts.artifact.size(); ++i )
  {
    NGameX::AdventureScreen::Instance()->PreloadEffectsInResourceTree( easelData->artifacts.artifact[i], BADNODENAME );
  }

  for ( int i = 0; i < easelData->gameboosts.images.size(); ++i )
  {
    if ( IsValid( easelData->gameboosts.images[i] ) )
      CObj<Render::Texture> texture = easelData->gameboosts.images[i]->Load();
  }

  NDb::Ptr<NDb::DBEaselCommon> commonData = easelData->commonParams;
  if(!IsValid(commonData))
  {
    return;
  }

  NHPTimer::STime time;
  NHPTimer::GetTime( time );

  for( int i = 0; i < NDb::KnownEnum<NDb::ECursor>::sizeOf; ++i )
  {
    ReserveStandaloneEffect(commonData->aimCursors.cursors[i]);
  }

  for( int i = 0; i < NDb::KnownEnum<NDb::EColor>::sizeOf - 1; ++i )
  {
    ReserveSceneObject(commonData->balls.colorBalls[i], 20);
  }

  ReserveStandaloneEffect(commonData->balls.paintBlastBall);
  ReserveStandaloneEffect(commonData->balls.paintBlastBallFlying);
  ReserveSceneObject(commonData->balls.jokerBall);

  ReserveStandaloneEffect(commonData->effects.paintblastExplosion);
  ReserveStandaloneEffect(commonData->effects.freezeEffect);
  ReserveAttachedEffect(commonData->effects.coinPickUp);
  ReserveAttachedEffect(commonData->alchemistPot);
  ReserveStandaloneEffect(commonData->effects.gameStartEffect);
  ReserveStandaloneEffect(commonData->effects.gameWonEffect);
  ReserveStandaloneEffect(commonData->effects.sortEffect);

  ReserveSceneObject(commonData->tunnels.tunnel);
  ReserveStandaloneEffect(commonData->effects.pathfinderHead);
  ReserveStandaloneEffect(commonData->effects.pathfinderTail);
  ReserveStandaloneEffect(commonData->effects.ballExplosion, 20);

  ReserveSceneObject( commonData->startPipe );
  ReserveSceneObject( commonData->endWell );
  ReserveStandaloneEffect( commonData->magnetEffects.magnetHighlight, 24 );
  ReserveStandaloneEffect( commonData->magnetEffects.magnetPreselect, 1 );
  ReserveStandaloneEffect( commonData->magnetEffects.magnet, 1 );
  ReserveStandaloneEffect( commonData->glueEffect);

  ReserveSceneObject( commonData->platform.platformObject );
  ReserveStandaloneEffect( commonData->platform.laserPointer );
  ReserveAttachedEffect( commonData->platform.laserSource );
  CObj<PF_Core::LightningEffect> effect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::LightningEffect>(commonData->platform.laser);
  effect->Die();

  ReserveStandaloneEffect( commonData->effects.flowTouchEffect );

  int numFlowGroups = commonData->effects.flowGroups.size();
  for ( int i = 0; i < numFlowGroups; ++i )
  {
    const NDb::DBEaselFlowEffectGroup& flowGroup = commonData->effects.flowGroups[i];
    ReserveStandaloneEffect(flowGroup.flowEffect, 10);
  }

  for ( int i = 0; i < NDb::KnownEnum<NDb::EFallingObject>::sizeOf; ++i )
  {
    ReserveSceneObject(commonData->fallingObjects[i], 10);
  }

  struct Preloader : public NDb::IResourcesProcessor
  {
    void * cacheID;

    virtual bool Call( const NDb::DBID& dbid, const NDb::DbResource* pResource )
    {
      const NDb::Material* material = dynamic_cast<const NDb::Material*>( pResource );

      if ( material )
      {
        Render::Material* renderMaterial = Render::CreateRenderMaterialInPool( material, cacheID );
        delete renderMaterial;
      }

      return true;
    }

    virtual bool LoadResources() { return true; }

    Preloader() : cacheID( 0 ) {} 
  } preloadFunctor;

  preloadFunctor.cacheID = this;

  easelScreenCache = UI::GetScreenLayout( "EaselScreen" );
  failScreenCache = UI::GetScreenLayout( "Minigame02Fail" );
  lobbyScreenCache = UI::GetScreenLayout( "Minigame02Lobby" );
  newboostScreenCache = UI::GetScreenLayout( "Minigame02NewBoost" );
  resultsScreenCache = UI::GetScreenLayout( "Minigame02Results" );
  tutorScreenCache = UI::GetScreenLayout( "Minigame02Tutor" );

  
  if ( IsValid(easelData) && IsValid(easelData->game) )
  {
    ReserveSceneObject(easelData->game->paint.paintQuad);

    const NDb::DBPaint & paints = easelData->game->paint;
    for(int i=0; i< paints.picture.size();i++)
    {
      const NDb::DBPicture & picture = paints.picture[i];

      for (int j=0; j<picture.pictureparams.size();j++)
      {
        NDb::Ptr<NDb::DBPainterFragment> fragment = picture.pictureparams[j];

        if (!IsValid(fragment))
          continue;
        preloadFunctor.Call(fragment->paintMaterial->GetDBID(), fragment->paintMaterial);

        for (int k=0; k<fragment->painterFragment.listFragments.size();k++)
        {
          const NDb::DBFragment & dbFragment = fragment->painterFragment.listFragments[k];
          preloadFunctor.Call(dbFragment.completeEffectMaterial->GetDBID(), dbFragment.completeEffectMaterial);
        }
      }
    }
  }

  DebugTrace( "Easel::PrefetchData: %2.3f", NHPTimer::GetTimePassedAndUpdateTime( time ) );
}


void Easel::OnBoost( NDb::EBoostType _type )
{
  world->GetLogic()->GetBoostBoard()->FireBoost( _type );
}


int Easel::SelectTrajectory()
{
  int level = GetLevelID();

  if ( firstTrajectory && level == 0 )
    return easelData->game->firstLevelForceTrajectory;

  NDb::EDifficultyLevel newDifficulty = easelData->game->levels[ level ].difficulty;

  firstTrajectory = false;

  int minUsedCount = INT_MAX;
  int trajectoryNumber = 0;

  int i = 0;

  for ( ; i < trajectoryUseCount.size(); ++i )
  {
    trajectoryUseCount[i] = abs(trajectoryUseCount[i]);

    NDb::EDifficultyLevel thisDifficulty = easelData->game->trajectories[i]->difficulty;

    if ( thisDifficulty != newDifficulty )
    {
      trajectoryUseCount[i] = -trajectoryUseCount[i];
    }
    else if ( lastTrajectory == i )
    {
      trajectoryUseCount[i] = -trajectoryUseCount[i];
    }
    else if ( trajectoryUseCount[i] < minUsedCount )
    {
      trajectoryNumber = 1;
      minUsedCount = trajectoryUseCount[i];
    }
    else if ( trajectoryUseCount[i] == minUsedCount )
    {
      trajectoryNumber += 1;
    }
  }

  // randomize
  NI_VERIFY( trajectoryNumber > 0, "TrajectoryRandomSelector: there is no trajectory with selected difficulty", return -1 );
  int select = NRandom::RandomFromSeed( GetRandomSeed() , 0, trajectoryNumber - 1);

  // select level
  for ( i = 0; i < trajectoryUseCount.size(); ++i )
  {
    if (trajectoryUseCount[i] != minUsedCount )
      continue;

    if ( select == 0 )
      break;

    select -= 1;
  }

  trajectoryUseCount[i]++;
  lastTrajectory = i;

  return lastTrajectory;
}

const NDb::DBPriestessLevelStats* Easel::GetPriestessLevelStats()
{
  return easelData->priestessStats->stats[ GetLevelID() ];
}

const NDb::DBPainterFragment* Easel::GetPainterLevelData()
{
  return easelData->game->paint.picture[ GetPaintID() ].pictureparams[ GetLevelID() ];
}


void Easel::Copy( Easel* _remoteCopy )
{
  if ( !IsValid( _remoteCopy ) )
    return;

  currentBoost = _remoteCopy->currentBoost;
  trajectoryUseCount = _remoteCopy->trajectoryUseCount;
  firstTrajectory = _remoteCopy->firstTrajectory;
  lastTrajectory = _remoteCopy->lastTrajectory;

  easelStatistics.Copy( _remoteCopy->easelStatistics );
}



} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( Easel, PF_Minigames )
