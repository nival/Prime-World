#include "stdafx.h"
#include "EaselCommands.h"

#include "../Core/WorldCommand.h"

#include "Minigames.h"
#include "MinigamesMain.h"

#include "Easel.h"

#include "../PF_GameLogic/SessionEventType.h"


namespace PF_Minigames
{

// Common commands
DEFINE_1_PARAM_CMD( 0xC565EB01, LeaveMinigameCommand,  CPtr<IWorldSessionInterface>, intrface );
DEFINE_2_PARAM_CMD( 0xC5636C00, PauseMinigameCommand,  CPtr<IWorldSessionInterface>, intrface, bool, enablePause );

// Easel commands
DEFINE_4_PARAM_CMD( 0xF4682A80, EaselStartLevelCommand, CPtr<IWorldSessionInterface>, intrface, int, levelID, int, paintID, int, randomSeed );
DEFINE_2_PARAM_CMD( 0xF4682A81, EaselStopLevelCommand, CPtr<IWorldSessionInterface>, intrface, uint, stepID );
DEFINE_6_PARAM_CMD( 0xF46ADB40, EaselRemoteUpdateCommand, CPtr<IWorldSessionInterface>, intrface, uint, stepID , short, inputX, short, inputY, bool, mouseLeft, bool, mouseRight );
DEFINE_3_PARAM_CMD( 0xF4683400, EaselBoostFiredCommand, CPtr<IWorldSessionInterface>, intrface, uint, stepID, NDb::EBoostType, boostType );
DEFINE_4_PARAM_CMD( 0xF469BB41, EaselRegenerateBoostsCommand, CPtr<IWorldSessionInterface>, intrface, int, levelID, int, randomSeed, bool, needToPay );
DEFINE_2_PARAM_CMD( 0xC572C440, EaselKeyboardEventCommand, CPtr<IWorldSessionInterface>, intrface, EEaselKeyboardEvents::Enum, event );
DEFINE_3_PARAM_CMD( 0xC5829500, EaselTransferItemCommand, CPtr<IWorldSessionInterface>, sessionInterface, CPtr<NWorld::PFBaseHero>, target, int, transactionId );

#ifndef _SHIPPING
DEFINE_1_PARAM_CMD( 0xC5716280, EaselCheatDropCooldownsCommand, CPtr<IWorldSessionInterface>, sessionInterface );
DEFINE_1_PARAM_CMD( 0x5BAC5B01, EaselCheatWinGameCommand, CPtr<IWorldSessionInterface>, sessionInterface );
#endif



void LeaveMinigameCommand::Execute( NCore::IWorldBase* pWorld )
{
  intrface->OnLeaveMinigameCmd();
}



void PauseMinigameCommand::Execute( NCore::IWorldBase* pWorld )
{
  CPtr<Minigames> minigames = dynamic_cast<Minigames *>( intrface->GetMinigames() );

  if ( IsValid( minigames ) )
    minigames->PauseMinigame(enablePause);
}



Easel* GetEaselGame( IWorldSessionInterface* _sessionInterface, bool local )
{
  Minigames *minigames = dynamic_cast<Minigames *>( _sessionInterface->GetMinigames() );
  CPtr<EaselMinigame> easelMinigame = minigames->GetNativeMinigame<EaselMinigame>("Easel");

  if( !IsValid( easelMinigame ) )
    return 0;

  return local ? easelMinigame->GetLocalEasel() : easelMinigame->GetRemoteEasel();
}

void EaselStartLevelCommand::Execute( NCore::IWorldBase * world )
{
  Minigames *minigames = dynamic_cast<Minigames *>( intrface->GetMinigames() );
  CPtr<EaselMinigame> easel = minigames->GetNativeMinigame<EaselMinigame>("Easel");
  if( !IsValid( easel ) )
    return;

  int maxLevel = easel->CalculateMaxAvailableLevel();

  if ( levelID <= maxLevel && (maxLevel+1) >= easel->GetLevelForPaintID( paintID+1 ) ) // levelID = currentLevel - 1; paintID = paintID - 1
  {
    DebugTrace( "Start level %d, paint %d", levelID, paintID );
    easel->StartLevelWorld( levelID, paintID, randomSeed );
  }
  else
  {
    DebugTrace( "ERROR Start level %d, paint %d, maxLevel %d levelforPaint %d", levelID, paintID, easel->CalculateMaxAvailableLevel(), easel->GetLevelForPaintID( paintID+1 ) );
  }
}


void EaselStopLevelCommand::Execute( NCore::IWorldBase * world )
{
  Minigames *minigames = dynamic_cast<Minigames *>( intrface->GetMinigames() );
  CPtr<EaselMinigame> easel = minigames->GetNativeMinigame<EaselMinigame>("Easel");
  if(!IsValid(easel))
    return;

  DebugTrace( "Execute stop level connad" );
  easel->OnWorldStopLevel(); 
}



void EaselRemoteUpdateCommand::Execute( NCore::IWorldBase * )
{
  Minigames * minigames = dynamic_cast<Minigames *>( intrface->GetMinigames() );
  CPtr<EaselMinigame> easelMG = minigames->GetNativeMinigame<EaselMinigame>( "Easel" );
  if(!IsValid( easelMG ))
    return;

  easelMG->DoStep( stepID, inputX, inputY, mouseLeft, mouseRight );
}



void EaselBoostFiredCommand::Execute( NCore::IWorldBase * )
{
  intrface->LogMinigameEvent(SessionEventType::MG2BoostUsage, boostType, 0);

  CPtr<Easel> game = GetEaselGame( intrface, false );
  game->OnBoost( boostType );
}

void EaselKeyboardEventCommand::Execute( NCore::IWorldBase * )
{
  Minigames * minigames = dynamic_cast<Minigames *>( intrface->GetMinigames() );
  CPtr<EaselMinigame> easel = minigames->GetNativeMinigame<EaselMinigame>( "Easel" );
  if( !IsValid( easel ) )
    return;

  easel->OnKeyboardEventCmd( event );
}



void EaselTransferItemCommand::Execute( NCore::IWorldBase * )
{
  Minigames * minigames = dynamic_cast<Minigames *>( sessionInterface->GetMinigames() );
  CPtr<EaselMinigame> easel = minigames->GetNativeMinigame<EaselMinigame>( "Easel" );
  if( !IsValid( easel ) )
    return;

  easel->OnTransferItemCmd( target, transactionId );
}



#ifndef _SHIPPING
NCore::WorldCommand* CreateEaselCheatDropCooldowns( IWorldSessionInterface* _sessionInterface )
{
  return new EaselCheatDropCooldownsCommand( _sessionInterface );
}

void EaselCheatDropCooldownsCommand::Execute( NCore::IWorldBase * )
{
  Minigames * minigames = dynamic_cast<Minigames *>( sessionInterface->GetMinigames() );
  CPtr<EaselMinigame> easel = minigames->GetNativeMinigame<EaselMinigame>( "Easel" );
  if(!IsValid( easel ))
    return;

  if( IsValid( easel ) )
    easel->OnCheatDropCooldownsCommand();
}

NCore::WorldCommand* CreateEaselCheatWinGame( IWorldSessionInterface* _sessionInterface )
{
  return new EaselCheatWinGameCommand( _sessionInterface );
}

void EaselCheatWinGameCommand::Execute( NCore::IWorldBase * )
{
  Minigames * minigames = dynamic_cast<Minigames *>( sessionInterface->GetMinigames() );
  CPtr<EaselMinigame> easel = minigames->GetNativeMinigame<EaselMinigame>( "Easel" );
  if(!IsValid( easel ))
    return;

  if( IsValid( easel ) )
    easel->OnCheatWinGameCommand();
}
#endif
void EaselRegenerateBoostsCommand::Execute( NCore::IWorldBase * )
{
  Minigames * minigames = dynamic_cast<Minigames *>( intrface->GetMinigames() );
  CPtr<EaselMinigame> easel = minigames->GetNativeMinigame<EaselMinigame>( "Easel" );
  if( IsValid( easel ) )
    easel->OnRegenerateBoostsCmd( needToPay, levelID, randomSeed );
}



EaselCommandsSender::EaselCommandsSender() :
  currentStepID(0)
{
}



EaselCommandsSender::~EaselCommandsSender()
{
}



void EaselCommandsSender::Init( EaselMinigame* _minigame )
{
  if( IsValid( _minigame ) )
  {
    minigameMain =_minigame->GetMinigames()->GetNativeMain();
    session = _minigame->GetMinigames()->GetWorldSessionInterface();

    minigameClient = _minigame;
  }
}



void EaselCommandsSender::PushNextCommand()
{
//  DebugTrace( "MG COMMAND SIZE: %d", commandStack.size() );

  if ( !commandStack.empty() )
  {
//    DebugTrace( "MG COMMAND INSIDE" );

    CObj<NCore::WorldCommand> _command = commandStack.front();
    commandStack.pop_front();

    if ( IsValid( _command ) )
    {
//      DebugTrace( "MG COMMAND: %s", _command->GetObjectTypeName() );
      minigameMain->SendWorldCommand( _command );
    }
  }
}



void EaselCommandsSender::SendLeaveMinigameCommand()
{
  CObj<NCore::WorldCommand> _command = new LeaveMinigameCommand( session );
  commandStack.push_back( _command );
}



void EaselCommandsSender::SendPauseMinigameCommand( bool enablePause )
{
  CObj<NCore::WorldCommand> _command = new PauseMinigameCommand( session, enablePause );
  commandStack.push_back( _command );
}


void EaselCommandsSender::SendBoostFiredCommand( NDb::EBoostType boostType )
{
  CObj<NCore::WorldCommand> _command = new EaselBoostFiredCommand( session, currentStepID, boostType );
  commandStack.push_back( _command );

  // local command
  CPtr<Easel> game = GetEaselGame( session, true );
  game->OnBoost( boostType );
}



void EaselCommandsSender::SendRemoteUpdateCommand( uint _stepIDer, short _inputX, short _inputY, bool _mouseLeft, bool _mouseRight )
{
  currentStepID = _stepIDer;

  CObj<NCore::WorldCommand> _command = new EaselRemoteUpdateCommand( session, _stepIDer, _inputX, _inputY, _mouseLeft, _mouseRight );
  commandStack.push_back( _command );
}



void EaselCommandsSender::SendLevelStartCommand(int _levelID,int _paintID,int _randomSeed)
{
  CObj<NCore::WorldCommand> _command = new EaselStartLevelCommand( session, _levelID, _paintID, _randomSeed );
  commandStack.push_back( _command );
}



void EaselCommandsSender::SendLevelStopCommand()
{
  CObj<NCore::WorldCommand> _command =  new EaselStopLevelCommand( session, currentStepID );
  commandStack.push_back( _command );
}



void EaselCommandsSender::SendRegenerateBoostsCommand( int _levelID, int _randomSeed, bool _needToPay )
{
  CObj<NCore::WorldCommand> _command = new EaselRegenerateBoostsCommand( session, _levelID, _randomSeed, _needToPay );
  commandStack.push_back( _command );
}

void EaselCommandsSender::SendKeyboardEventCommand( EEaselKeyboardEvents::Enum event )
{
  CObj<NCore::WorldCommand> _command = new EaselKeyboardEventCommand( session, event );
  commandStack.push_back( _command );
}



void EaselCommandsSender::SendTransferItemCommand( NWorld::PFBaseHero * target, int transactionId )
{
  CObj<NCore::WorldCommand> _command = new EaselTransferItemCommand( session, target, transactionId );
  commandStack.push_back( _command );
}

} // PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( LeaveMinigameCommand, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( PauseMinigameCommand, PF_Minigames )


REGISTER_SAVELOAD_CLASS_NM( EaselStartLevelCommand, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselStopLevelCommand, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselRemoteUpdateCommand, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselBoostFiredCommand, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselRegenerateBoostsCommand, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselKeyboardEventCommand, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselTransferItemCommand, PF_Minigames )
#ifndef _SHIPPING
REGISTER_SAVELOAD_CLASS_NM( EaselCheatDropCooldownsCommand, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselCheatWinGameCommand, PF_Minigames )
#endif

REGISTER_SAVELOAD_CLASS_NM( EaselCommandsSender, PF_Minigames )
