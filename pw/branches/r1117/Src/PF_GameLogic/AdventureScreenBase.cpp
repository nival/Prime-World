#include "stdafx.h"
#include "AdventureScreenBase.h"
#include "Core/CoreFSM.h"
#include "Client/ScreenCommands.h"

namespace NGameX
{

AdventureScreenBase::AdventureScreenBase() :
playerId(-1)
{
}



bool AdventureScreenBase::Init( UI::User * uiUser )
{
  return AdventureScreenBaseClient::Init( uiUser );
}



bool AdventureScreenBase::InitAdventuresBase( NCore::MapStartInfo const& info, NCore::ITransceiver *_pTransceiver, int _playerId, bool isSpectator )
{
  startInfo = info;  
  pTransceiver = _pTransceiver;

  NI_VERIFY( 0 < info.playersInfo.size(), "Must be at least one player!", return false );

  // single game  : all nodes are local nodes, only one player is human controlled: take first local node
  // network game : only one node is host node! 

  playerId = -1;
  int playersInfoSize = info.playersInfo.size();
  bool isReplay = IsInReplayMode();

  int teamPlayerId = 0;
  bool isTeamPlayer = false;

  for ( int i = 0; i < playersInfoSize; ++i )
  {
    int id = 0;
    if(isReplay)
    {
      id = info.playersInfo[i].playerID;
    }
    else
    {
      id = info.playersInfo[i].userID;
      isTeamPlayer = info.playersInfo[i].originalTeamID >= 0 ; 

      //for spectator mode. use dokt`s (team1) human player 
      if( isSpectator && ( id != -1 && isTeamPlayer ) )
      {
        teamPlayerId = i;
        if (info.playersInfo[i].originalTeamID == NCore::ETeam::Team1)
        {
          playerId = i;
          break;
        }
      }
    }

    if ( id == _playerId)
    {
      playerId = i;
      break;
    }
  }

  if(playerId == -1)
    playerId = teamPlayerId;

  return true;
}



void AdventureScreenBase::CloseScreen()
{
  NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( this ) );
}



bool AdventureScreenBase::IsInReplayMode() const
{
  return !startInfo.replayName.empty();
}

} // namespace NGameX
