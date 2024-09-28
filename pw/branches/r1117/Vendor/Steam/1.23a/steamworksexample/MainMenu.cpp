//========= Copyright © 1996-2008, Valve LLC, All rights reserved. ============
//
// Purpose: Class to define the main game menu
//
// $NoKeywords: $
//=============================================================================


#include "stdafx.h"
#include "MainMenu.h"
#include "SpaceWar.h"

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CMainMenu::CMainMenu( IGameEngine *pGameEngine ) : CBaseMenu<EClientGameState>( pGameEngine )
{
	AddMenuItem( MenuItem_t( "Start New Server", k_EClientGameStartServer ) );
	AddMenuItem( MenuItem_t( "Find LAN Servers", k_EClientFindLANServers ) );
	AddMenuItem( MenuItem_t( "Find Internet Servers", k_EClientFindInternetServers ) );
	AddMenuItem( MenuItem_t( "Create Lobby", k_EClientCreatingLobby ) );
	AddMenuItem( MenuItem_t( "Find Lobby", k_EClientFindLobby ) );
	AddMenuItem( MenuItem_t( "Instructions", k_EClientGameInstructions ) );
	AddMenuItem( MenuItem_t( "Stats and Achievements", k_EClientStatsAchievements ) );
	AddMenuItem( MenuItem_t( "Leaderboards", k_EClientLeaderboards ) );
	AddMenuItem( MenuItem_t( "Group chat room", k_EClientClanChatRoom ) );
	AddMenuItem( MenuItem_t( "Remote Storage", k_EClientRemoteStorage ) );
	AddMenuItem( MenuItem_t( "Write Minidump", k_EClientMinidump ) );
	AddMenuItem( MenuItem_t( "Web Callback", k_EClientWebCallback ) );
	AddMenuItem( MenuItem_t( "Exit Game", k_EClientGameExiting ) );
}