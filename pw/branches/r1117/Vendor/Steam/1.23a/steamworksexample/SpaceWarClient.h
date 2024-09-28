//========= Copyright � 1996-2008, Valve LLC, All rights reserved. ============
//
// Purpose: Main class for the space war game client
//
// $NoKeywords: $
//=============================================================================

#ifndef SPACEWARCLIENT_H
#define SPACEWARCLIENT_H


#include "GameEngine.h"
#include "SpaceWar.h"
#include "Messages.h"
#include "StarField.h"
#include "Sun.h"
#include "Ship.h"
#include "StatsAndAchievements.h"
#include "RemoteStorage.h"

// Forward class declaration
class CConnectingMenu;
class CMainMenu; 
class CQuitMenu;
class CSpaceWarServer;
class CServerBrowser;
class CLobbyBrowser;
class CLobby;
class CLeaderboards;
class CClanChatRoom;
class CP2PAuthPlayer;
class CP2PAuthedGame;
class CVoiceChat;

// Height of the HUD font
#define HUD_FONT_HEIGHT 18

// Height for the instructions font
#define INSTRUCTIONS_FONT_HEIGHT 24

// Enum for various client connection states
enum EClientConnectionState
{
	k_EClientNotConnected,							// Initial state, not connected to a server
	k_EClientConnectedPendingAuthentication,		// We've established communication with the server, but it hasn't authed us yet
	k_EClientConnectedAndAuthenticated,				// Final phase, server has authed us, we are actually able to play on it
};

// a game server as shown in the find servers menu
struct ServerBrowserMenuData_t
{
	EClientGameState m_eStateToTransitionTo;
	CSteamID m_steamIDGameServer;
};

// a lobby as shown in the find lobbies menu
struct LobbyBrowserMenuItem_t
{
	CSteamID m_steamIDLobby;
	EClientGameState m_eStateToTransitionTo;
};

// a user as shown in the lobby screen
struct LobbyMenuItem_t
{
	enum ELobbyMenuItemCommand
	{
		k_ELobbyMenuItemUser,
		k_ELobbyMenuItemStartGame,
		k_ELobbyMenuItemToggleReadState,
		k_ELobbyMenuItemLeaveLobby,
		k_ELobbyMenuItemInviteToLobby
	};

	CSteamID m_steamIDUser;		// the user who this is in the lobby
	ELobbyMenuItemCommand m_eCommand;
	CSteamID m_steamIDLobby;	// set if k_ELobbyMenuItemInviteToLobby	
};

// a leaderboard item
struct LeaderboardMenuItem_t
{
	bool m_bBack;
	bool m_bNextLeaderboard;
};


class CSpaceWarClient 
{
public:
	//Constructor
	CSpaceWarClient( IGameEngine *pEngine );

	// Shared init for all constructors
	void Init( IGameEngine *pGameEngine );

	// Destructor
	~CSpaceWarClient();

	// Run a game frame
	void RunFrame();

	// Checks for any incoming network data, then dispatches it
	void ReceiveNetworkData();

	// Connect to a server at a given IP address or game server steamID
	void InitiateServerConnection( CSteamID steamIDGameServer );
	void InitiateServerConnection( uint32 unServerAddress, const int32 nPort );

	// Send data to a client at the given ship index
	bool BSendServerData( const void *pData, uint32 nSizeOfData );

	// Menu callback handler (handles a bunch of menus that just change state with no extra data)
	void OnMenuSelection( EClientGameState eState ) { SetGameState( eState ); }

	// Menu callback handler (handles server browser selections with extra data)
	void OnMenuSelection( ServerBrowserMenuData_t selection ) 
	{ 
		if ( selection.m_eStateToTransitionTo == k_EClientGameConnecting )
		{
			InitiateServerConnection( selection.m_steamIDGameServer );
		}
		else
		{
			SetGameState( selection.m_eStateToTransitionTo ); 
		}
	}

	void OnMenuSelection( LobbyBrowserMenuItem_t selection )
	{
		// start joining the lobby
		if ( selection.m_eStateToTransitionTo == k_EClientJoiningLobby )
		{
			SteamAPICall_t hSteamAPICall = SteamMatchmaking()->JoinLobby( selection.m_steamIDLobby );
			// set the function to call when this API completes
			m_SteamCallResultLobbyEntered.Set( hSteamAPICall, this, &CSpaceWarClient::OnLobbyEntered );
		}

		SetGameState( selection.m_eStateToTransitionTo );
	}

	void OnMenuSelection( LobbyMenuItem_t selection );
	void OnMenuSelection( LeaderboardMenuItem_t selection );
	void OnMenuSelection( ERemoteStorageSyncMenuCommand selection );

	// Set game state
	void SetGameState( EClientGameState eState );
	EClientGameState GetGameState() { return m_eGameState; }

	// set failure text
	void SetConnectionFailureText( const char *pchErrorText );

	// Were we the winner?
	bool BLocalPlayerWonLastGame();

	// Get the steam id for the local user at this client
	CSteamID GetLocalSteamID() { return m_SteamIDLocalUser; }

	// Get the local players name
	const char* GetLocalPlayerName() 
	{ 
		return SteamFriends()->GetFriendPersonaName( m_SteamIDLocalUser ); 
	}

	// Scale screen size to "real" size
	float PixelsToFeet( float flPixels );

	// Get a Steam-supplied image
	HGAMETEXTURE GetSteamImageAsTexture( int iImage );

	void RetrieveEncryptedAppTicket();

	void ExecCommandLineConnect( const char *pchServerAddress, const char *pchLobbyID );

private:

	// Receive a response from the server for a connection attempt
	void OnReceiveServerInfo( CSteamID steamIDGameServer, bool bVACSecure, const char *pchServerName );

	// Receive a response from the server for a connection attempt
	void OnReceiveServerAuthenticationResponse( bool bSuccess, uint32 uPlayerPosition );

	// Receive a state update from the server
	void OnReceiveServerUpdate( ServerSpaceWarUpdateData_t *pUpdateData );

	// Handle the server exiting
	void OnReceiveServerExiting();

	// Disconnects from a server (telling it so) if we are connected
	void DisconnectFromServer();

	// game state changes
	void OnGameStateChanged( EClientGameState eGameStateNew );

	// Draw the HUD text (should do this after drawing all the objects)
	void DrawHUDText();

	// Draw instructions for how to play the game
	void DrawInstructions();

	// Draw text telling the players who won (or that their was a draw)
	void DrawWinnerDrawOrWaitingText();

	// Draw text telling the user that the connection attempt has failed
	void DrawConnectionFailureText();

	// Draw connect to server text
	void DrawConnectToServerText();

	// Draw text telling the user a connection attempt is in progress
	void DrawConnectionAttemptText();

	// Updates what we show to friends about what we're doing and how to connect
	void UpdateRichPresenceConnectionInfo();

	// Server we are connected to
	CSpaceWarServer *m_pServer;

	// SteamID for the local user on this client
	CSteamID m_SteamIDLocalUser;

	// Our ship position in the array below
	uint32 m_uPlayerShipIndex;

	// List of steamIDs for each player
	CSteamID m_rgSteamIDPlayers[MAX_PLAYERS_PER_SERVER];

	// Ships for players, doubles as a way to check for open slots (pointer is NULL meaning open)
	CShip *m_rgpShips[MAX_PLAYERS_PER_SERVER];

	// Player scores
	uint32 m_rguPlayerScores[MAX_PLAYERS_PER_SERVER];

	// Who just won the game? Should be set if we go into the k_EGameWinner state
	uint32 m_uPlayerWhoWonGame;

	// Current game state
	EClientGameState m_eGameState;

	// true if we only just transitioned state
	bool m_bTransitionedGameState;

	// Font handle for drawing the HUD text
	HGAMEFONT m_hHUDFont;

	// Font handle for drawing the instructions text
	HGAMEFONT m_hInstructionsFont;

	// Time the last state transition occurred (so we can count-down round restarts)
	uint64 m_ulStateTransitionTime;

	// Time we started our last connection attempt
	uint64 m_ulLastConnectionAttemptRetryTime;

	// Time we last got data from the server
	uint64 m_ulLastNetworkDataReceivedTime;

	// Time when we sent our ping
	uint64 m_ulPingSentTime;

	// Text to display if we are in an error state
	char m_rgchErrorText[256];

	// Server address data
	CSteamID m_steamIDGameServer;
	uint32 m_unServerIP;
	uint16 m_usServerPort;
	HAuthTicket m_hAuthTicket;

	// keep track of if we opened the overlay for a gamewebcallback
	bool m_bSentWebOpen;

	// simple class to marshal callbacks from pinging a game server
	class CGameServerPing : public ISteamMatchmakingPingResponse
	{
	public:
		CGameServerPing()
		{
			m_hGameServerQuery = HSERVERQUERY_INVALID;
			m_pSpaceWarsClient = NULL;
		}

		void RetrieveSteamIDFromGameServer( CSpaceWarClient *pSpaceWarClient, uint32 unIP, uint16 unPort )
		{
			m_pSpaceWarsClient = pSpaceWarClient;
			m_hGameServerQuery = SteamMatchmakingServers()->PingServer( unIP, unPort, this );
		}

		void CancelPing()
		{
			m_hGameServerQuery = HSERVERQUERY_INVALID;
		}

		// Server has responded successfully and has updated data
		virtual void ServerResponded( gameserveritem_t &server )
		{
			if ( m_hGameServerQuery != HSERVERQUERY_INVALID && server.m_steamID.IsValid() )
			{
				m_pSpaceWarsClient->InitiateServerConnection( server.m_steamID );
			}

			m_hGameServerQuery = HSERVERQUERY_INVALID;
		}

		// Server failed to respond to the ping request
		virtual void ServerFailedToRespond()
		{
			m_hGameServerQuery = HSERVERQUERY_INVALID;
		}

	private:
		HServerQuery m_hGameServerQuery;	// we're ping a game server, so we can convert IP:Port to a steamID
		CSpaceWarClient *m_pSpaceWarsClient;
	};
	CGameServerPing m_GameServerPing;
	

	// Track whether we are connected to a server (and what specific state that connection is in)
	EClientConnectionState m_eConnectedStatus;

	// Star field instance
	CStarField *m_pStarField;

	// Sun instance
	CSun *m_pSun;

	// Main menu instance
	CMainMenu *m_pMainMenu;

	// Connecting menu instance
	CConnectingMenu *m_pConnectingMenu;

	// Pause menu instance
	CQuitMenu *m_pQuitMenu;

	// pointer to game engine instance we are running under
	IGameEngine *m_pGameEngine;

	// track which steam image indexes we have textures for, and what handle that texture has
	std::map<int, HGAMETEXTURE> m_MapSteamImagesToTextures;

	CStatsAndAchievements *m_pStatsAndAchievements;

	CLeaderboards *m_pLeaderboards;
	CClanChatRoom *m_pClanChatRoom;
	CServerBrowser *m_pServerBrowser;

	CRemoteStorage *m_pRemoteStorage;

	// lobby handling
	// the name of the lobby we're connected to
	CSteamID m_steamIDLobby;
	// callback for when we're creating a new lobby
	void OnLobbyCreated( LobbyCreated_t *pCallback, bool bIOFailure );
	CCallResult<CSpaceWarClient, LobbyCreated_t> m_SteamCallResultLobbyCreated;
	// callback for when we've joined a lobby
	void OnLobbyEntered( LobbyEnter_t *pCallback, bool bIOFailure );
	CCallResult<CSpaceWarClient, LobbyEnter_t> m_SteamCallResultLobbyEntered;

	// callback for when the lobby game server has started
	STEAM_CALLBACK( CSpaceWarClient, OnLobbyGameCreated, LobbyGameCreated_t, m_LobbyGameCreated );
	STEAM_CALLBACK( CSpaceWarClient, OnGameJoinRequested, GameRichPresenceJoinRequested_t, m_GameJoinRequested );
	STEAM_CALLBACK( CSpaceWarClient, OnAvatarImageLoaded, AvatarImageLoaded_t, m_AvatarImageLoadedCreated );

	// callbacks for Steam connection state
	STEAM_CALLBACK( CSpaceWarClient, OnSteamServersConnected, SteamServersConnected_t, m_SteamServersConnected );
	STEAM_CALLBACK( CSpaceWarClient, OnSteamServersDisconnected, SteamServersDisconnected_t, m_SteamServersDisconnected );
	STEAM_CALLBACK( CSpaceWarClient, OnSteamServerConnectFailure, SteamServerConnectFailure_t, m_SteamServerConnectFailure );
	STEAM_CALLBACK( CSpaceWarClient, OnGameOverlayActivated, GameOverlayActivated_t, m_CallbackGameOverlayActivated );
	
	// callback when getting the results of a web call
	STEAM_CALLBACK( CSpaceWarClient, OnGameWebCallback, GameWebCallback_t, m_CallbackGameWebCallback );

	// lobby browser menu
	CLobbyBrowser *m_pLobbyBrowser;

	// local lobby display
	CLobby *m_pLobby;
	
	// p2p game auth manager
	CP2PAuthedGame *m_pP2PAuthedGame;
	
	// p2p voice chat 
	CVoiceChat *m_pVoiceChat;

	// connection handler
	STEAM_CALLBACK( CSpaceWarClient, OnP2PSessionConnectFail, P2PSessionConnectFail_t, m_CallbackP2PSessionConnectFail );

	// ipc failure handler
	STEAM_CALLBACK( CSpaceWarClient, OnIPCFailure, IPCFailure_t, m_IPCFailureCallback );

	// Steam wants to shut down, Game for Windows applications should shutdown too
	STEAM_CALLBACK( CSpaceWarClient, OnSteamShutdown, SteamShutdown_t, m_SteamShutdownCallback );

	// Called when SteamUser()->RequestEncryptedAppTicket() returns asynchronously
	void OnRequestEncryptedAppTicket( EncryptedAppTicketResponse_t *pEncryptedAppTicketResponse, bool bIOFailure );
	CCallResult< CSpaceWarClient, EncryptedAppTicketResponse_t > m_SteamCallResultEncryptedAppTicket;
};

// Must define this stuff before BaseMenu.h as it depends on calling back into us through these accessors
extern CSpaceWarClient *g_pSpaceWarClient;
CSpaceWarClient *SpaceWarClient();

#endif // SPACEWARCLIENT_H
