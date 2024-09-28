#include "stdafx.h"

#include "Core/Transceiver.h"
#include "System/SyncProcessorState.h"

#include "EaselMinigame.h"

#include "DBEasel.h"

#include "Minigames.h"
#include "MinigameCommands.h"

#include "EaselScreenLobby.h"
#include "EaselScreenLogic.h"
#include "EaselScreenResults.h"
#include "EaselScreenLogicLobby.h"
#include "EaselScreenLogicResults.h"
#include "EaselFailScreenLogic.h"
#include "EaselCommands.h"

#include "EaselPriestess.h"

#include "EaselWorld.h"
#include "EaselDef.h"

#include "EaselNotifications.h"

#include "LuxGameLogic.h"
#include "LuxGameBoard.h"

#include "../PF_GameLogic/PFStatistics.h"
#include "../PF_GameLogic/PFWorld.h"
#include "../PF_GameLogic/PFMinigamePlace.h"
#include "../PF_GameLogic/AdventureScreen.h"
#include "../PF_GameLogic/SessionEventType.h"

#include "../Sound/EventScene.h"
#include "../PF_GameLogic/DBSound.h"

#include "../PF_GameLogic/PFEaselPlayer.h"

#include "EaselView.h"

namespace PF_Minigames
{

float g_easelResultsDelay = 0.1f;
REGISTER_DEV_VAR("Easel_Results_Delay",g_easelResultsDelay,STORAGE_NONE);

//float g_easelInternalStepper = 0.1f;
//REGISTER_DEV_VAR("Easel_Stepper",g_easelInternalStepper,STORAGE_NONE);

bool g_easelShowRemoteView = false;
REGISTER_DEV_VAR("Easel_ShowRemoteView",g_easelShowRemoteView, STORAGE_NONE);

int REGEN_BOOSTS_ON_FAIL_STREAK = 3;
REGISTER_DEV_VAR("Easel_BoostRegen_OnFail",REGEN_BOOSTS_ON_FAIL_STREAK,STORAGE_NONE);

int REGEN_BOOSTS_ON_WON_STREAK  = 1;
REGISTER_DEV_VAR("Easel_BoostRegen_OnWin",REGEN_BOOSTS_ON_WON_STREAK,STORAGE_NONE);

int GenerateRandomSeed()
{
  return GetTickCount();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselMinigame::EaselMinigame( PF_Core::IWorld* _pWorld, bool _local ) :
PF_Core::WorldObjectBase( _pWorld, false ),
SingleMinigame( _local ? NDb::MINIGAMECLIENTTYPE_LOCAL : NDb::MINIGAMECLIENTTYPE_REMOTE )
, paintID(-1)
, levelID(-1)
, easelLocalState(STATE_DISABLED)
, nextItemTransferId( 0 )
, remoteLevelStarted(false)
, stepReminder(0.f)
, isLocal( _local )
, wonStreak(0)
, failStreak(0)
, player(NULL)
, ejectStage(0)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::StartLevelLocal(int _levelID,int _paintID)
{
  NI_VERIFY(easelLocalState == STATE_LOBBY, "Easel: start game called outside of lobby scope", return false);

  int randomSeed = GenerateRandomSeed();

  if ( !IsValid( localGame ) )
    return false;

  localGame->StartLevel(_paintID,_levelID, randomSeed, player );
  easelLocalState = STATE_GAME;

  paintID = _paintID;
  levelID = _levelID;

  // screens ....
  screensManager.GetLobbyScreen()->ShowMainWindow( false );
  screensManager.PushEaselScreen();

  // starting remote level
  SendStartLevelWorldCommand(_levelID,_paintID,randomSeed);

  ChangeVisualState(NDb::MINIGAMEVISUALSTATE_EASEL_INGAME);

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::StopLevelLocal()
{
  if ( LocalStopLevelImpl() )
  {
    ShowLobbyScreen();

    ChangeVisualState(NDb::MINIGAMEVISUALSTATE_EASEL_LOBBY);
  }  
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::LocalStopLevelImpl()
{
  DebugTrace( "EaselMinigame::LocalStopLevelImpl!" );

  NI_VERIFY( easelLocalState == STATE_GAME || easelLocalState == STATE_GAME_WON || easelLocalState == STATE_GAME_FAILED, "", return false );

  if ( !localGame )
    return false;

  localGame->StopLevel();

  easelLocalState = STATE_LOBBY;

  // stopping remote level
  SendStopLevelWorldCommand();
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::StopGameImpl()
{
  DebugTrace( "EaselMinigame::StopGameImpl!" );

  NI_VERIFY( easelLocalState == STATE_LOBBY, "", return false );

  if ( localGame )
    localGame->GetClient().Reset( true );

  if ( remoteGame )
    remoteGame->GetClient().Reset( true );

  easelLocalState = STATE_DISABLED;

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::StartLevelWorld( int _levelID, int _paintID, int _seed )
{
  // update boosts for level
  NI_VERIFY( remoteGame->GetData(), "remoteGame: game data is invalid", return false );

  levelID = _levelID;
  paintID = _paintID;

  GetSessionInterface()->LogMinigameEvent(SessionEventType::MG2LevelStarted, levelID, paintID);

  // start remote client level
  remoteGame->StartLevel(_paintID, _levelID, _seed, player);

  remoteLevelStarted = true;

  if ( !localGame )
    ChangeVisualState(NDb::MINIGAMEVISUALSTATE_EASEL_INGAME);

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::OnWorldStopLevel()
{
  remoteGame->StopLevel();

  remoteLevelStarted = false;

  if ( !localGame )
    ChangeVisualState(NDb::MINIGAMEVISUALSTATE_EASEL_LOBBY);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::DoStep( uint _stepCount, short _inputX, short _inputY, bool _mouseLeft, bool _mouseRight )
{
  SyncProcessorState();
  NI_VERIFY( remoteGame, "No remoteGame", return false );

  float _gameTime = GetWorld()->GetStepLengthInSeconds(); // production
  EaselStepInfo stepInfo;
  stepInfo.stepID = _stepCount;
  stepInfo.inputState.mousePos.x = _inputX;
  stepInfo.inputState.mousePos.y = _inputY;
  stepInfo.inputState.mouseLeftButton = _mouseLeft;
  stepInfo.inputState.mouseRightButton = _mouseRight;

  stepInfo.deltaTime = 0; // Хак, позволяет провести инпут
  remoteGame->StepM( stepInfo );
  
  EaselStepInfo info;
  info.deltaTime = _gameTime * 1000;
  info.inputState.mousePos   = SVector(0,0);
  remoteGame->StepM( info );

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::OnKeyboardEventLocal( EEaselKeyboardEvents::Enum event )
{
  if( sessionHatch )
    sessionHatch->SendKeyboardEventCommand( event );

  if ( localGame )
    return localGame->ProcessKeyboardEvent( event );

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::OnKeyboardEventCmd( EEaselKeyboardEvents::Enum event )
{
  if ( remoteGame )
    remoteGame->ProcessKeyboardEvent( event );
}

IWorldSessionInterface * EaselMinigame::GetSessionInterface()
{
  NI_VERIFY(IsValid(remoteGame->GetWorldSessionInterface()),"session interface is not valid", return 0);
  return remoteGame->GetWorldSessionInterface();
}



void EaselMinigame::OnRegenerateBoostsCmd( bool haveToBuy, int newLevelID, int seed )
{
  if( IsValid( remoteGame ) )
    remoteGame->RegenerateBoosts( haveToBuy, newLevelID, seed );
}



void EaselMinigame::OnTransferItemCmd( NWorld::PFBaseHero * target, int transactionId )
{
  if( !IsValid( remoteGame ) )
    return;

  bool transferResult = remoteGame->TransferItem( target, transactionId );

  //Local loopback:
  if ( pendingItemTransfers.find( transactionId ) != pendingItemTransfers.end() )
  {
    pendingItemTransfers.erase( transactionId );
    completedItemTransfers.push_back( pair<int, bool>( transactionId, transferResult ) );
  }
}



void EaselMinigame::OnPlacementChanged(const Placement& _oldPlacement, const Placement& _newPlacement)
{
  if ( IsValid( localGame ) )
    localGame->ChangePlacement( _newPlacement );
  
  if ( remoteGame )
    remoteGame->ChangePlacement( _newPlacement );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::OnInit()
{
  NI_VERIFY(IsValid(GetMinigames()), "EaselMinigame: init failed - minigames object is invalid", return false);

  if(!SingleMinigame::OnInit())
  {
    return false;
  }

  sessionHatch = new EaselCommandsSender();
  sessionHatch->Init( this );
  
  if ( isLocal )
  {
    localGame = new EaselLocal( 0 );
    localGame->SetCommandsHatch(sessionHatch);

    IWorldSessionInterface * sessionInterface = GetMinigames()->GetWorldSessionInterface();

    if (!sessionInterface)
      return false;

    if ( !localGame->Init( GetScene(), sessionInterface , GetMinigames()->GetPlacement().pos ) )
      return false;   
    
    sessionInterface->SetNaftaInfoProvider(localGame->GetWorld()->GetPriestessProxy());
  }

  //Crosslink between L and R easels
  IRemoteToLocalLink * featCallback = localGame ? dynamic_cast<IRemoteToLocalLink *>( localGame->GetWorld()->GetPriestessProxy() ) : 0;

  bool nullRemoteView =  isLocal && !g_easelShowRemoteView;
  remoteGame = new EaselRemote( GetWorld(), featCallback, nullRemoteView );
  
  if ( !remoteGame->Init( GetScene(), GetMinigames()->GetWorldSessionInterface(),  GetMinigames()->GetPlacement().pos) )
  {
    return false;
  }

  if ( localGame )
  {
    // need to init regen options
    REGEN_BOOSTS_ON_WON_STREAK = localGame->GetData()->gameboosts.rerollOnWinStreak;
    REGEN_BOOSTS_ON_FAIL_STREAK = localGame->GetData()->gameboosts.rerollOnFailStreak;
  }

  remoteGame->SetLocalGame( localGame );

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::Start( NWorld::PFMinigamePlace * place )
{
  NI_VERIFY( IsValid( place ), "EaselMinigame: start minigame failed - minigame place is invalid", return false );
  SetMinigamePlace( place );

  player = place->CurrentEaselPlayer();

  const Placement& _placement = place->GetMinigamePlacement();

  if ( localGame )
    localGame->ChangePlacement(_placement);

  if ( remoteGame )
    remoteGame->ChangePlacement(_placement);
  
  if ( localGame )
    easelLocalState = STATE_LOBBY;

  if ( isLocal )
    NGameX::AdventureScreen::Instance()->SetGameMenuMinigameInterface( this );

  ChangeVisualState(NDb::MINIGAMEVISUALSTATE_EASEL_LOBBY);

  ejectStage = 0;

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::StartClient()
{
  NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_MINIGAME_02, false );

  NI_ASSERT( localGame, "" );

  screensManager.Init( this );

  NI_VERIFY(easelLocalState == STATE_LOBBY, "Easel: minigame client started already", return false);
  
  // easel must have valid associated minigames object
  if ( !IsValid( GetMinigames() ) )
    return false;
  
  ShowLobbyScreen();

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::Leave()
{
  DebugTrace("EaselMinigame::Leave");

  if ( remoteLevelStarted ) // From reconnect
    OnWorldStopLevel();

  if ( easelLocalState == STATE_GAME )
  {
    LocalStopLevelImpl();
  }

  if ( ( easelLocalState == STATE_GAME ) || ( easelLocalState == STATE_LOBBY ) )
  {
    if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
    {
      advScreen->SetGameMenuMinigameInterface( 0 );
      advScreen->ActivateSessionSoundScene();
    }

    StopGameImpl();
  }

  //In case of external closure we must take care of our screens
  screensManager.PopEaselScreen();
  screensManager.PopLobbyScreen();
  screensManager.PopFailureScreen();
  screensManager.PopResultsScreen();

  ChangeVisualState( NDb::MINIGAMEVISUALSTATE_SESSION );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING

void EaselMinigame::OnCheatDropCooldownsCommand()
{
  if ( remoteGame )
    remoteGame->CheatResetCooldowns();
}

void EaselMinigame::OnCheatWinGameCommand()
{
  DevTrace("EaselMinigame::OnCheatWinGameCommand()");
  //EaselLocalState::STATE_GAME_WON
  if ( remoteGame )
    remoteGame->CheatWinGame();
}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::InitiatePause( bool enablePause )
{
  //WARNING: Sending world command before changing local Easel
  if ( SingleMinigame::InitiatePause( enablePause ) )
  {
    localGame->PauseLevel( enablePause );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::RegenerateBoosts( bool haveToBuy, int levelID )
{
  if ( !IsValid( localGame ) )
    return false;

  int seed = GenerateRandomSeed();

  localGame->RegenerateBoosts( haveToBuy, levelID, seed );

  if ( sessionHatch )
    sessionHatch->SendRegenerateBoostsCommand( levelID, seed, haveToBuy );

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::Local_StartItemTransfer( NWorld::PFBaseHero * target )
{
  if ( !IsValid( localGame ) || !sessionHatch )
    return;

  if ( !pendingItemTransfers.empty() )
    return;

  int transId = nextItemTransferId++;
  pendingItemTransfers.insert( transId );

  sessionHatch->SendTransferItemCommand( target, transId );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::Local_PopItemTransferResult( bool & isSuccessfull )
{
  if ( completedItemTransfers.empty() )
    return false;

  const TCompletedItemTransfers::value_type & front = completedItemTransfers.front();
//  id = front.first;
  isSuccessfull = front.second;

  completedItemTransfers.pop_front();
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::OnExitImmediate()
{
  ChangeVisualState( NDb::MINIGAMEVISUALSTATE_EASEL_LEAVINGLOBBY );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::LogMinigameEvent( SessionEventType::EventType eventType, int param1, int param2 )
{
  if ( IWorldSessionInterface * pWorldSessionInterface = GetSessionInterface() )
  {
    pWorldSessionInterface->LogMinigameEvent(eventType, param1, param2);
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::OnLevelWonLocal()
{
  GetSessionInterface()->LogMinigameEvent(SessionEventType::MG2LevelWon, levelID, paintID);

  easelLocalState = STATE_GAME_WON;
  wonStreak++;
  failStreak = 0;

  if( !( wonStreak % REGEN_BOOSTS_ON_WON_STREAK ) )
    RegenerateBoosts( false, GetLevelID() );

  screensManager.CreateResultsScreen();
  screensManager.PopEaselScreen();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::OnLevelFailedLocal()
{
  GetSessionInterface()->LogMinigameEvent(SessionEventType::MG2LevelFailed, levelID, paintID);

  easelLocalState = STATE_GAME_FAILED;
  wonStreak = 0;
  failStreak++;

  if( failStreak % REGEN_BOOSTS_ON_FAIL_STREAK == 0 )
    RegenerateBoosts( false, GetLevelID() );

  screensManager.CreateFailureScreen();
  screensManager.PopEaselScreen();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::ProcessLocalStepFromUpdate( float _deltaTime )
{
  if ( easelLocalState != STATE_GAME || IsPaused() || !IsValid(localGame) )
    return;

  float commonDelta = _deltaTime + stepReminder;

  float stepLengthInSeconds = GetWorld()->GetStepLengthInSeconds();
  stepReminder = fmod( commonDelta, stepLengthInSeconds );
  int numSubSteps = Float2Int( floor( commonDelta / stepLengthInSeconds ) );

  for ( int i = 0; i < numSubSteps; ++i )
  {
    switch ( easelLocalState )
    { 
    case STATE_GAME:

      localGame->StepM( stepLengthInSeconds );

      if ( localGame->GetWorld()->GetLogic()->GetGameBoard()->GetBoardState() == BOARDSTATE_LEVEL_WON_FINAL )
        OnLevelWonLocal();
      else if ( localGame->GetWorld()->GetLogic()->GetGameBoard()->GetBoardState() == BOARDSTATE_LEVEL_FAIL_FINAL )
        OnLevelFailedLocal();

      break;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::OnStep( float deltaTime ) 
{
  sessionHatch->PushNextCommand();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::Update( float deltaTime, bool gameOnPause )
{
  // NUM_TASK "аварийное извлечение" из миниигры растянуто во времени, чтобы успевала отрабатывать логика скринов
  switch (ejectStage)
  {
  case 1:
    --ejectStage;
    ExitLobbyScreen(true);
    break;
  case 2:
    --ejectStage;
    AbortMinigameLevel();
    break;
  default:
    break;
  }

  ProcessLocalStepFromUpdate( deltaTime );

  if ( IsValid( localGame ) )
    localGame->Update( deltaTime, gameOnPause );

  if ( remoteGame )
    remoteGame->Update( deltaTime, gameOnPause );

  SingleMinigame::Update( deltaTime, gameOnPause );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::OnPause( bool _isPaused )
{
  remoteGame->PauseLevel( _isPaused );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::DBID & EaselMinigame::GetDBID( Easel* easel ) const
{ 
  if ( IsValid( easel )  )
  {
    return easel->GetData()->GetDBID();
  }
  else
  {
    static NDb::DBID nullid;
    return nullid;
  }
} 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::DBID & EaselMinigame::GetDBID() const
{
  if ( isLocal )
    return GetDBID( localGame );
  else
    return GetDBID( remoteGame );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::PlaceUnderFogOfWar( bool underFogOfWar )
{
  if ( remoteGame )
    remoteGame->GetClient().ShowAll( !underFogOfWar );
}

void EaselMinigame::CheatWinGame()
{
#ifndef _SHIPPING
  if ( localGame )
    localGame->CheatWinGame();

  if ( IsValid( GetMinigames() ) )
    if ( IsValid( GetMinigames()->GetMain() ) )
    {
      CObj<NCore::WorldCommand> cmd = CreateEaselCheatWinGame( GetMinigames()->GetWorldSessionInterface() );
      GetMinigames()->GetMain()->SendWorldCommand( cmd );
    }
#endif

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::CheatDropCooldowns()
{
  // Хоть этот код исполняется уже из World Step,
  // но что бы сохранить схему работы remote и local миров Изела,
  // мы воспользуемся командой

#ifndef _SHIPPING
  if ( localGame )
    localGame->CheatResetCooldowns();

  if ( IsValid( GetMinigames() ) )
    if ( IsValid( GetMinigames()->GetMain() ) )
    {
      CObj<NCore::WorldCommand> cmd = CreateEaselCheatDropCooldowns( GetMinigames()->GetWorldSessionInterface() );
      GetMinigames()->GetMain()->SendWorldCommand( cmd );
    }
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::SendLeaveMinigameCommand( IWorldSessionInterface * _worldInterface )
{
  if ( IsValid( sessionHatch ) )
    sessionHatch->SendLeaveMinigameCommand(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::SendPauseMinigameCommand( IWorldSessionInterface * _worldInterface, bool enablePause )
{
  if ( IsValid( sessionHatch ) )
    sessionHatch->SendPauseMinigameCommand( enablePause ); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::NeedToShowMinigameMenuItems()
{
  if ( easelLocalState == STATE_GAME )
    if ( IsValid( screensManager.GetMainScreenLogic() ) )
      return true;
  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselMinigame::OnGameMenuEscapeButton()
{
  //NUM_TASK debugging, remove it when its closed
  DebugTrace( "OnGameMenuEscapeButton: easelLocalState = %d, screensManager.GetLobbyScreenLogic() = 0x%08x", (int)easelLocalState, (void*)screensManager.GetLobbyScreenLogic() );

  if ( easelLocalState == STATE_LOBBY )
  {
    if (ExitLobbyScreen(false))
      return true;
  }

  if ( easelLocalState == STATE_GAME )
  {
    if ( IsValid( screensManager.GetResultsScreenLogic() ) )
    {
      return true;
    }

    if ( IsValid( screensManager.GetFailureScreenLogic() ) )
    {
      screensManager.GetFailureScreenLogic()->Exit();
      return true;
    }

    if ( OnKeyboardEventLocal( EEaselKeyboardEvents::SkipMovie ) )
      return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::OnGameMenuPopup()
{
  if ( easelLocalState == STATE_GAME )
    InitiatePause( true );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::GameMenuClosed()
{
  if ( easelLocalState == STATE_GAME )
    InitiatePause( false );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::AbortMinigameLevel()
{
  if ( easelLocalState == STATE_GAME )
  {
    InitiatePause( false );

    if ( IsValid( screensManager.GetMainScreenLogic() ) )
      screensManager.GetMainScreenLogic()->ExitGame();
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::ShowLobbyScreen()
{
  int maxAvailableLevel = CalculateMaxAvailableLevel();
  NI_VERIFY(maxAvailableLevel >= 0, "EaselMinigame: invaid max available level", return);

  EaselScreenLobby * lobby = screensManager.GetLobbyScreen();
  if ( !IsValid( lobby ) )
  {
    lobby = screensManager.CreateLobbyScreen();
    lobby->SetMaxLevel( maxAvailableLevel );
  }
  else
  {
    lobby->SetMaxLevel( maxAvailableLevel );
    lobby->UpdateLobby();
    lobby->ShowMainWindow( true );
  }

  NSoundScene::UnPauseMusic();
}

bool EaselMinigame::ExitLobbyScreen(const bool force /*= false*/)
{
  if (!screensManager.GetLobbyScreen())
    return false;
  if (!screensManager.GetLobbyScreenLogic())
    return false;

  const bool canExit = (screensManager.GetLobbyScreen()->State() == ELobbyScreenState::Normal);

  if (!canExit && !force)
    return false;

  screensManager.GetLobbyScreenLogic()->ExitGame();
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EaselMinigame::CalculateMaxAvailableLevel()
{
  NI_VERIFY(IsValid(GetMinigames())
    , "EaselMinigame: unable calculate max available level for lobby screen - associated minigames object is invalid"
    , return 0);
  NI_VERIFY(IsValid(GetMinigames()->GetWorldSessionInterface())
    , "EaselMinigame: unable calculate max available level for lobby screen  - sesion interface is invalid"
    , return 0);

  int priestessNafta = GetMinigames()->GetWorldSessionInterface()->GetTotalNaftaEarned();
  int maxLevel = 0; 

  const NDb::DBEaselData* data = 0;

  if ( !IsValid( localGame ) )
    if ( !IsValid( remoteGame ) )
      return 0;
    else
      data = remoteGame->GetData();
  else
    data = localGame->GetData();

  NI_VERIFY( data, "EaselMinigame: game data is invalid", return 0);

  const NDb::Ptr<NDb::DBPriestessStats>& stats = data->priestessStats;
  NI_VERIFY(IsValid(stats), "EaselMinigame: priestess stats are invalid", return 0);
  NI_VERIFY(stats->stats.size() == NDb::KnownEnum<NDb::EPriestessLevel> ::sizeOf, "EaselMinigame: priestess stats are invalid", return 0);

  for(int i = 0; i < NDb::KnownEnum<NDb::EPriestessLevel>::sizeOf; ++i)
  {
    const NDb::Ptr<NDb::DBPriestessLevelStats>& levelStats = stats->stats[i];
    NI_VERIFY(IsValid(levelStats), "EaselMinigame: priestess level stats are invalid", continue);

    if(stats->stats[i]->naftaRequired > priestessNafta)
    {
      break;
    }

    maxLevel = i;
  }

  return maxLevel;
}


int EaselMinigame::GetLevelForPaintID( int paintId )
{
  const NDb::DBEaselData* data = 0;

  if ( !IsValid( localGame ) )
    if ( !IsValid( remoteGame ) )
      return 0;
    else
      data = remoteGame->GetData();
  else
    data = localGame->GetData();

  NI_VERIFY( data, "EaselMinigame: game data is invalid", return 0);

  if ( paintId > 0 && paintId <= data->game->availabilityTable.size() )
  {
    int lev = data->game->availabilityTable[paintId-1];
    return lev;
  }
  
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::SendStartLevelWorldCommand(int _levelID,int _paintID,int _randomSeed)
{
  if ( IsValid( sessionHatch ) )
    sessionHatch->SendLevelStartCommand(_levelID,_paintID,_randomSeed);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselMinigame::SendStopLevelWorldCommand()
{
  if(IsValid(sessionHatch))
    sessionHatch->SendLevelStopCommand();
}

//////////////////////////////////////////////////////////////////////////
void EaselMinigame::UpdateLevelAvailability()
{
  int maxAvailableLevel = CalculateMaxAvailableLevel();
  EaselScreenLobby * lobby = screensManager.GetLobbyScreen();
  if (IsValid(lobby))
  {
    lobby->SetMaxLevel( maxAvailableLevel );
    lobby->UpdateLobby();
  }
}

void EaselMinigame::OnSerialize( IBinSaver &f )
{

}

void EaselMinigame::OnMapLoaded()
{
  if ( IsValid( localGame ) )
    localGame->PrefetchData();
  else if ( IsValid( remoteGame ) )
    remoteGame->PrefetchData();
}

void EaselMinigame::OnAfterReset()
{
  if ( !remoteLevelStarted || !IsValid(remoteGame) )
    return;
  
  remoteGame->GetView()->InitAfterWorld( remoteGame->GetWorld() );

  ChangeVisualState(NDb::MINIGAMEVISUALSTATE_EASEL_INGAME);
}

void EaselMinigame::Eject()
{
  switch (easelLocalState)
  {
  case STATE_DISABLED:
    break;
  case STATE_LOBBY:
    ejectStage = 1;
    break;
  case STATE_GAME:
    ejectStage = 2;
    break;
  case STATE_GAME_WON:
  case STATE_GAME_FAILED:
    NI_ALWAYS_ASSERT("Eject() is not allowed!");
    break;
  }
}

}

REGISTER_SAVELOAD_CLASS_NM( EaselMinigame, PF_Minigames )
