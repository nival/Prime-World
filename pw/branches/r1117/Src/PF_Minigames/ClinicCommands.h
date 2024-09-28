#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCore
{
  class WorldCommand;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

_interface IWorldSessionInterface;

NCore::WorldCommand* CreateStartClinicLevelCommand( IWorldSessionInterface* _sessionInterface, int _levelID, bool _startGame );
NCore::WorldCommand* CreateStopClinicLevelCommand( IWorldSessionInterface* _sessionInterface, const PF_Minigames::MinigameCreeps& creepsToSpawn );
NCore::WorldCommand* CreateClinicClickCommand( IWorldSessionInterface* _sessionInterface, int _objectID );
NCore::WorldCommand* CreateClinicRightClickCommand( IWorldSessionInterface* _sessionInterface );
NCore::WorldCommand* CreateClinicBuyCommand( IWorldSessionInterface* _sessionInterface, int _objectID );

}; // namespace PF_Minigames
