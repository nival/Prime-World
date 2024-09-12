#include "stdafx.h"
#include "StateLobby.h"
#include "../Core/NetMessagesProcessor.h"
#include "MessagesLobby.h"
#include "MessagesInGame.h"
#include "GameNode.h"
#include "StateInGameSingle.h"
#include "StateCreatingGame.h"
#include "StateWaitingRoomClient.h"
#include "StateWaitingRoomHost.h"

namespace 
{
  int                                  g_desiredTeam = -1;
  NCore::MapStartInfo::BalanceTeamMode g_balanceMode = NCore::MapStartInfo::BALANCE_ALL;
  int                                  g_humans      = -1; 

  bool SetBalanceTeamsMode( char const* name, vector<wstring> const& params )
  {
    if( params.empty() )
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "Usage: " << name << " mode" << endl 
        << "  available modes: 0 - do not balance teams, 1 - balance human players only, 2 - balance all" << endl
        << "  current value: " << g_balanceMode << endl;
    }
    else
    {
      const int value = NStr::ToInt(params[0].c_str());
      g_balanceMode = (NCore::MapStartInfo::BALANCE_NONE <= value && value <= NCore::MapStartInfo::BALANCE_ALL) ?
        ( NCore::MapStartInfo::BalanceTeamMode)value : NCore::MapStartInfo::BALANCE_NONE;
    }

    return true;
  }

  bool SetDesiredTeam( char const* name, vector<wstring> const& params )
  {
    if( params.empty() )
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "Usage: " << name << " team" << endl 
        << "  available team: 0 - left team, 1 - right team, -1 - don`t care" << endl
        << "  current value: " << g_desiredTeam << endl;
    }
    else
    {
      const int value = NStr::ToInt(params[0].c_str());
      g_desiredTeam = ( 0 == value || 1 == value ) ? value : -1;
    }

    return true;
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCore
{
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CStateLobby::CStateLobby(CoreFSM *pContext)
   : CoreFSMState(pContext)
   , m_startGame(false)
   , m_selectedHero(-1)
   , eGoTo(ET_NONE)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateLobby::Init()
{
  	pContext->RegisterMessageBuilder( GetTypeId(), &NCore::LobbyScreenState::NewLobbyScreenState );
    SubscribeUpdates();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateLobby::SubscribeUpdates()
{
	pContext->RegisterProcessorToCore( this );
  Subscribe( &CStateLobby::StartSingleGame );
  Subscribe( &CStateLobby::SelectHero );
  Subscribe( &CStateLobby::StartServerGame);
  Subscribe( &CStateLobby::StartClientGame );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateLobby::StartSingleGame( const SetInGameState& message )
{
  eGoTo = ET_SINGLE;
  m_startInfo = message.startInfo;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CStateLobby::StartServerGame( const StartServer& message )
{
  NI_VERIFY( !message.startInfo.mapName.empty(), "Invalid map!", return; );

  eGoTo = ET_SERVER;
  m_startInfo = message.startInfo;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateLobby::StartClientGame( const StartClient& message )
{
  eGoTo = ET_CLIENT;
  url = message.url;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CStateLobby::SelectHero( const struct SelectHeroMessage& message )
{
  // temporary: must send LobbyCommand later
  m_selectedHero = message.heroID;
}

IBaseFSMState* CStateLobby::Step(float dt)
{
  switch ( eGoTo )
  {
  case ET_SERVER:
    {

      NNet::IDriver* driver = NetMessagesProcessor::InitNet( false );
      // if map was specified
      if( !m_startInfo.mapName.empty() )
        return new WaitingRoomHostState( pContext, driver, m_startInfo, m_selectedHero, g_desiredTeam, g_balanceMode, g_humans);
      else
        return new CreatingGameState( pContext, driver );
    }

  case ET_CLIENT:
    {

      NNet::IDriver* driver = NetMessagesProcessor::InitNet( true );
      return new WaitingRoomClientState( pContext, driver, url, m_selectedHero, g_desiredTeam );
    }

  case ET_SINGLE:
    {					
      int pendingTeamChange = -1;
      vector<CObj<CGameNode>> nodes( 1, new CGameNode() );
      for ( int i = 0; i < m_startInfo.playersInfo.size(); ++i )
      {
        PlayerStartInfo& info = m_startInfo.playersInfo[i];
        info.nodeID           = 0;

        if( -1 != pendingTeamChange && pendingTeamChange != info.teamID )
        {
          info.teamID       = pendingTeamChange; 
          pendingTeamChange = -1;
        }

        if( 0 == i)
        { 
          info.playerType     = PLAYER_HUMAN;
          info.heroID         = max(0, m_selectedHero);

          if( -1 != g_desiredTeam && info.teamID != g_desiredTeam)
          {
            pendingTeamChange = info.teamID;
            info.teamID       = g_desiredTeam;
          }
        }
      }

      NI_ASSERT( -1 == pendingTeamChange, "Invalid team change!" );

      m_startInfo.BalanceTeams( g_balanceMode );

      const GameStartInfo info = { nodes,  m_startInfo };
      pContext->PushMessageFromCore( new GameStartedMessage( info ) );		

      return new InGameStateSingle( pContext, nodes, 0, m_startInfo.mapName );
    }
  //case ET_LOGIN:
  //  {
  //   return new CStateLogin(pContext);
  //  }
  }

  return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NCore

REGISTER_DEV_CMD( balance_teams, SetBalanceTeamsMode );
REGISTER_DEV_CMD( desired_team,  SetDesiredTeam );
REGISTER_DEV_VAR( "human_players", g_humans, STORAGE_NONE );
