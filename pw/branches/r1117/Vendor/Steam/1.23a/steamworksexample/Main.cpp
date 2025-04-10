//====== Copyright � 1996-2008, Valve Corporation, All rights reserved. =======
//
// Purpose: Main file for the SteamworksExample app
//
//=============================================================================

#include "stdafx.h"

#if defined(WIN32)
    #include "gameenginewin32.h"
    #define atoll _atoi64
#elif defined(OSX)
	#include "GameEngine.h"
	extern IGameEngine *CreateGameEngineOSX();
#endif

#include "SpaceWarClient.h"

//-----------------------------------------------------------------------------
// Purpose: Wrapper around SteamAPI_WriteMiniDump which can be used directly 
// as a se translator
//-----------------------------------------------------------------------------
#ifdef _WIN32
void MiniDumpFunction( unsigned int nExceptionCode, EXCEPTION_POINTERS *pException )
{
	// You can build and set an arbitrary comment to embed in the minidump here,
	// maybe you want to put what level the user was playing, how many players on the server,
	// how much memory is free, etc...
	SteamAPI_SetMiniDumpComment( "Minidump comment: SteamworksExample.exe\n" );

	// The 0 here is a build ID, we don't set it
	SteamAPI_WriteMiniDump( nExceptionCode, pException, 0 );
}
#endif


//-----------------------------------------------------------------------------
// Purpose: Helper to display critical errors
//-----------------------------------------------------------------------------
int Alert( const char *lpCaption, const char *lpText )
{
#ifndef _WIN32
    fprintf( stderr, "Message: '%s', Detail: '%s'\n", lpCaption, lpText );
	return 0;
#else
    return ::MessageBox( NULL, lpText, lpCaption, MB_OK );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: callback hook for debug text emitted from the Steam API
//-----------------------------------------------------------------------------
extern "C" void __cdecl SteamAPIDebugTextHook( int nSeverity, const char *pchDebugText )
{
	// if you're running in the debugger, only warnings (nSeverity >= 1) will be sent
	// if you add -debug_steamapi to the command-line, a lot of extra informational messages will also be sent
	::OutputDebugString( pchDebugText );

	if ( nSeverity >= 1 )
	{
		// place to set a breakpoint for catching API errors
		int x = 3;
		x = x;
	}
}


//-----------------------------------------------------------------------------
// Purpose: Extracts some feature from the command line
//-----------------------------------------------------------------------------
void ParseCommandLine( const char *pchCmdLine, const char **ppchServerAddress, const char **ppchLobbyID )
{
	// Look for the +connect ipaddress:port parameter in the command line,
	// Steam will pass this when a user has used the Steam Server browser to find
	// a server for our game and is trying to join it. 
	const char *pchConnectParam = "+connect";
	const char *pchConnect = strstr( pchCmdLine, pchConnectParam );
	*ppchServerAddress = NULL;
	if ( pchConnect && strlen( pchCmdLine ) > (pchConnect - pchCmdLine) + strlen( pchConnectParam ) + 1 )
	{
		// Address should be right after the +connect, +1 on the end to skip the space
		*ppchServerAddress = pchCmdLine + ( pchConnect - pchCmdLine ) + strlen( pchConnectParam ) + 1;
	}

	// look for +connect_lobby lobbyid paramter on the command line
	// Steam will pass this in if a user taken up an invite to a lobby
	const char *pchConnectLobbyParam = "+connect_lobby";
	const char *pchConnectLobby = strstr( pchCmdLine, pchConnectParam );
	*ppchLobbyID = NULL;
	if ( pchConnectLobby && strlen( pchCmdLine ) > (pchConnectLobby - pchCmdLine) + strlen( pchConnectLobbyParam ) + 1 )
	{
		// Address should be right after the +connect, +1 on the end to skip the space
		*ppchLobbyID = pchCmdLine + ( pchConnectLobby - pchCmdLine ) + strlen( pchConnectLobbyParam ) + 1;
	}
}


//-----------------------------------------------------------------------------
// Purpose: Main loop code shared between all platforms
//-----------------------------------------------------------------------------
void RunGameLoop( IGameEngine *pGameEngine, const char *pchServerAddress, const char *pchLobbyID )
{
	// Make sure it initialized ok
	if ( pGameEngine->BReadyForUse() )
	{
		// Initialize the game
		CSpaceWarClient *pGameClient = new CSpaceWarClient( pGameEngine );

		// Black background
		pGameEngine->SetBackgroundColor( 0, 0, 0, 0 );

		// If +connect was used to specify a server address, connect now
		pGameClient->ExecCommandLineConnect( pchServerAddress, pchLobbyID );

		// test a user specific secret before entering main loop
		Steamworks_TestSecret();

		pGameClient->RetrieveEncryptedAppTicket();

		while( !pGameEngine->BShuttingDown() )
		{
			if ( pGameEngine->StartFrame() )
			{
				pGameEngine->UpdateGameTickCount();

				// Run a game frame
				pGameClient->RunFrame();
				pGameEngine->EndFrame();

				// Sleep to limit frame rate
				while( pGameEngine->BSleepForFrameRateLimit( MAX_CLIENT_AND_SERVER_FPS ) )
				{
					// Keep running the network on the client at a faster rate than the FPS limit
					pGameClient->ReceiveNetworkData();
				}
			}			
		}

		delete pGameClient;
	}

	// Cleanup the game engine
	delete pGameEngine;
}


//-----------------------------------------------------------------------------
// Purpose: Real main entry point for the program
//-----------------------------------------------------------------------------
#ifndef _PS3

static int RealMain( const char *pchCmdLine, HINSTANCE hInstance, int nCmdShow )
{
	
	if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ) )
	{
		// if Steam is not running or the game wasn't started through Steam, SteamAPI_RestartAppIfNecessary starts the 
		// local Steam client and also launches this game again.
		
		// Once you get a public Steam AppID assigned for this game, you need to replace k_uAppIdInvalid with it and
		// removed steam_appid.txt from the game depot.

		return EXIT_FAILURE;
	}
	

	// Init Steam CEG
	if ( !Steamworks_InitCEGLibrary() )
	{
		OutputDebugString( "Steamworks_InitCEGLibrary() failed\n" );
		Alert( "Fatal Error", "Steam must be running to play this game (InitDrmLibrary() failed).\n" );
		return EXIT_FAILURE;
	}

	// Initialize SteamAPI, if this fails we bail out since we depend on Steam for lots of stuff.
	// You don't necessarily have to though if you write your code to check whether all the Steam
	// interfaces are NULL before using them and provide alternate paths when they are unavailable.
	//
	// This will also load the in-game steam overlay dll into your process.  That dll is normally
	// injected by steam when it launches games, but by calling this you cause it to always load,
	// even when not launched via steam.
	if ( !SteamAPI_Init() )
	{
		OutputDebugString( "SteamAPI_Init() failed\n" );
		Alert( "Fatal Error", "Steam must be running to play this game (SteamAPI_Init() failed).\n" );
		return EXIT_FAILURE;
	}

	// set our debug handler
	SteamClient()->SetWarningMessageHook( &SteamAPIDebugTextHook );

	// Tell Steam where it's overlay should show notification dialogs, this can be top right, top left,
	// bottom right, bottom left. The default position is the bottom left if you don't call this.  
	// Generally you should use the default and not call this as users will be most comfortable with 
	// the default position.  The API is provided in case the bottom right creates a serious conflict 
	// with important UI in your game.
	SteamUtils()->SetOverlayNotificationPosition( k_EPositionTopRight );

	const char *pchServerAddress, *pchLobbyID;
	ParseCommandLine( pchCmdLine, &pchServerAddress, &pchLobbyID );
	// do a DRM self check
	Steamworks_SelfCheck();

	// Construct a new instance of the game engine 
	// bugbug jmccaskey - make screen resolution dynamic, maybe take it on command line?
	IGameEngine *pGameEngine = 
#if defined(_WIN32)
        new CGameEngineWin32( hInstance, nCmdShow, 1024, 768 );
#elif defined(OSX)
        CreateGameEngineOSX();
#endif
    
	// This call will block and run until the game exits
	RunGameLoop( pGameEngine, pchServerAddress, pchLobbyID );

	// Shutdown the SteamAPI
	SteamAPI_Shutdown();

	// Shutdown Steam CEG
	Steamworks_TermCEGLibrary();

	// exit
	return EXIT_SUCCESS;	
}
#endif

//-----------------------------------------------------------------------------
// Purpose: Main entry point for the program -- win32
//-----------------------------------------------------------------------------
#ifdef WIN32
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR     lpCmdLine,
					 int       nCmdShow)
{
	// All we do here is call the real main function after setting up our se translator
	// this allows us to catch exceptions and report errors to Steam.
	//
	// Note that you must set your compiler flags correctly to enable structured exception 
	// handling in order for this particular setup method to work.

	if ( IsDebuggerPresent() )
	{
		// We don't want to mask exceptions (or report them to Steam!) when debugging.
		// If you would like to step through the exception handler, attach a debugger
		// after running the game outside of the debugger.
		return RealMain( lpCmdLine, hInstance, nCmdShow );
	}

	_set_se_translator( MiniDumpFunction );
	try  // this try block allows the SE translator to work
	{
		return RealMain( lpCmdLine, hInstance, nCmdShow );
	}
	catch( ... )
	{
		return -1;
	}
}
#endif

#ifdef OSX
int main(int argc, const char **argv)
{
    char szCmdLine[1024];
    char *pszStart = szCmdLine;
    char * const pszEnd = szCmdLine + Q_ARRAYSIZE(szCmdLine);

    *szCmdLine = '\0';
    
    for ( int i = 1; i < argc; i++ )
    {
        const char *parm = argv[i];
        while ( *parm && (pszStart < pszEnd) )
        {
            *pszStart++ = *parm++;
        }
        
        if ( pszStart >= pszEnd )
            break;
        
        if ( i < argc-1 )
            *pszStart++ = ' ';
    }
    
    szCmdLine[Q_ARRAYSIZE(szCmdLine) - 1] = '\0';
    
    return RealMain( szCmdLine, 0, 0 );
}
#endif
