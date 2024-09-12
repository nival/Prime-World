#include "stdafx.h"

#include "../Core/WorldCommand.h"

#include "Clinic.h"
#include "ClinicCommands.h"
#include "Minigames.h"
#include "MinigameWorldObject.h"
#include "MinigameSessionInterface.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEFINE_3_PARAM_CMD( 0x9D6314C0, StartClinicLevelCommand, CPtr<IWorldSessionInterface>, intrface, int, _levelID, bool, _startGame );
DEFINE_2_PARAM_CMD( 0x9D6314C1, StopClinicLevelCommand,  CPtr<IWorldSessionInterface>, intrface, PF_Minigames::MinigameCreeps, creepsToSpawn );
DEFINE_2_PARAM_CMD( 0x9D6314C2, ClinicClickCommand, CPtr<IWorldSessionInterface>, intrface, int, _objectID );
DEFINE_1_PARAM_CMD( 0x9D6314C3, ClinicRightClickCommand,  CPtr<IWorldSessionInterface>, intrface );
DEFINE_2_PARAM_CMD( 0xC5632AC0, ClinicBuyCommand, CPtr<IWorldSessionInterface>, intrface, int, _objectID );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NCore::WorldCommand* CreateStartClinicLevelCommand( IWorldSessionInterface* _sessionInterface, int _levelID, bool _startGame )
{
  return new StartClinicLevelCommand( _sessionInterface, _levelID, _startGame );
}

///////////////////////////////////////////////////////////////////////////1///////////////////////////////////////////////////
NCore::WorldCommand* CreateStopClinicLevelCommand( IWorldSessionInterface* _sessionInterface, const PF_Minigames::MinigameCreeps& creepsToSpawn )
{
  return new StopClinicLevelCommand( _sessionInterface, creepsToSpawn );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NCore::WorldCommand* CreateClinicClickCommand( IWorldSessionInterface* _sessionInterface, int _objectID )
{
  return new ClinicClickCommand( _sessionInterface, _objectID );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NCore::WorldCommand* CreateClinicRightClickCommand( IWorldSessionInterface* _sessionInterface )
{
  return new ClinicRightClickCommand( _sessionInterface );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NCore::WorldCommand* CreateClinicBuyCommand( IWorldSessionInterface* _sessionInterface, int _objectID )
{
  return new ClinicBuyCommand(_sessionInterface, _objectID);
}

static Clinic * HelpGetToClinic( IWorldSessionInterface * iface )
{
  Minigames * games = dynamic_cast<Minigames *>( iface->GetMinigames() );
  NI_ASSERT( games, "" );
  return games->GetNativeMinigame<Clinic>( "Clinic" );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StartClinicLevelCommand::Execute( NCore::IWorldBase* pWorld )
{
	CPtr<Clinic> clinic = HelpGetToClinic( intrface );
	
	if ( IsValid( clinic ) )
	{
		if ( _startGame )
			clinic->StartLevel( _levelID );
		else
			clinic->StartShop();
	}

  systemLog( NLogg::LEVEL_MESSAGE ) << "Clinic started"	<< endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StopClinicLevelCommand::Execute( NCore::IWorldBase* pWorld )
{
	CPtr<Clinic> clinic = HelpGetToClinic( intrface );

	if ( IsValid( clinic ) )
		clinic->StopLevel( creepsToSpawn );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicClickCommand::Execute( NCore::IWorldBase* pWorld )
{
	CPtr<Clinic> clinic = HelpGetToClinic( intrface );

	if ( !IsValid( clinic ) )
		return;

	CPtr<MinigameWorldObject> gameObject = clinic->GetWorldObject( _objectID );

	if ( IsValid( gameObject ) )
		gameObject->OnClick();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicRightClickCommand::Execute( NCore::IWorldBase* pWorld )
{
  CPtr<Clinic> clinic = HelpGetToClinic( intrface );

  if ( !IsValid( clinic ) )
    return;

  clinic->CancelPlayerQueue();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicBuyCommand::Execute( NCore::IWorldBase* pWorld )
{
	CPtr<Clinic> clinic = HelpGetToClinic( intrface );

	if ( !IsValid( clinic ) )
		return;

	CPtr<MinigameWorldObject> gameObject = clinic->GetWorldObject( _objectID );

	if ( IsValid( gameObject ) )
		gameObject->OnBuyCommand();
}

}; // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( StartClinicLevelCommand,    PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( StopClinicLevelCommand,     PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( ClinicClickCommand,         PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( ClinicRightClickCommand,    PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( ClinicBuyCommand,           PF_Minigames )
