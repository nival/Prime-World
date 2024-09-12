#include "stdafx.h"
#include <System/systemStdAfx.h>
#include <stdlib.h>
#include <string>
#include <System/Base64.h>
#include <System/MemoryStream.h>

int Alert( const char *lpCaption, const char *lpText )
{
#ifndef _WIN32
    fprintf( stderr, "Message: '%s', Detail: '%s'\n", lpCaption, lpText );
    return 0;
#else
    return ::MessageBox( NULL, lpText, lpCaption, MB_OK );
#endif
}

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

namespace SteamStatus
{
  enum Enum
  {
    None,
    Pending,
    Success,
    Failure,
  };
}
struct SteamConnect
{
  SteamConnect():
  status(SteamStatus::None), 
  m_CallbackAuthSessionTicketResponse( this, &SteamConnect::OnAuthSessionTicketResponse ),
  unTokenLen(0)
  {}

  void Connect()
  {
    ISteamUser* pUser = SteamUser();

    if (pUser)
    {
      status = SteamStatus::Pending;
      HAuthTicket m_hAuthTicket = pUser->GetAuthSessionTicket( originalToken, sizeof(originalToken), &unTokenLen );
      m_hAuthTicket;

      unTokenLen += 1;
      char* s = encodedToken;
      for (unsigned int i=0;i<unTokenLen;++i)
      {
        s += sprintf(s, "%02X", unsigned char(originalToken[i]));
      }
      *s = 0;

      MemoryStream token(unTokenLen);
      MemoryStream base64;

      token.Write(originalToken, unTokenLen);
      token.Seek(0, SEEKORIGIN_BEGIN);
      Base64::EncodeURLSafe(token, base64);
      sAuthToken.reserve(base64.GetSize() + 1);
      sAuthToken.append(base64.GetBuffer(), base64.GetBuffer() + base64.GetSize());
    }
  }



  void Update()
  {
    SteamAPI_RunCallbacks();
    ::Sleep(5);
  }
  STEAM_CALLBACK( SteamConnect, OnAuthSessionTicketResponse, 
                  GetAuthSessionTicketResponse_t,
                  m_CallbackAuthSessionTicketResponse );


  std::string sAuthToken;
  SteamStatus::Enum status;
  char encodedToken[2048];
  char originalToken[2048];
  uint32 unTokenLen;
};

void SteamConnect::OnAuthSessionTicketResponse( GetAuthSessionTicketResponse_t *pParam )
{
  char buffer[1024*16];
  if ( pParam->m_hAuthTicket == k_HAuthTicketInvalid )
  {
    status = SteamStatus::Failure;
    char *s = buffer;
    s += sprintf(s, "{\n  \"status\" : 0\n}");
  }
  else 
  {
    status = SteamStatus::Success;
    CSteamID steamId = SteamUser()->GetSteamID();
    char *s = buffer;
    s += sprintf(s, "{\n  \"status\" : 1,\n \"snuid\" : %I64d,\n \"token\" : \"%s\",\n \"etoken\" : \"%s\",\n \"bytes\" : [ ", steamId.ConvertToUint64(), sAuthToken.c_str(), encodedToken);
    for (unsigned int i=0;i<unTokenLen;++i)
    {
      if (i != 0)
      {
        s += sprintf(s, ", ");
      }
      unsigned char value = (unsigned char)originalToken[i];
      s += sprintf(s, "%d", value);
    }
    s += sprintf(s, "]\n}\n");
//    Alert("Success", "Auth token is valid");
  }
  FILE* f = fopen("auth.txt", "wb");
  if (f)
  {
    fwrite(buffer, 1, strlen(buffer), f );
    fclose(f);
  }
  Sleep(20000);
}
void RunGameLoop()
{
    // test a user specific secret before entering main loop
    Steamworks_TestSecret();

  SteamConnect connect;
  connect.Connect();
  while (connect.status == SteamStatus::Pending)
  {
    connect.Update();
  }
}


//-----------------------------------------------------------------------------
// Purpose: Real main entry point for the program
//-----------------------------------------------------------------------------
#ifndef _PS3

static int RealMain( const char *pchCmdLine, HINSTANCE hInstance, int nCmdShow )
{
  nCmdShow;
  pchCmdLine;
  hInstance;

  if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ) )
    {
        // if Steam is not running or the game wasn't started through Steam, SteamAPI_RestartAppIfNecessary starts the 
        // local Steam client and also launches this game again.
        
        // Once you get a public Steam AppID assigned for this game, you need to replace k_uAppIdInvalid with it and
        // removed steam_appid.txt from the game depot.

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

    // do a DRM self check
    Steamworks_SelfCheck();

    RunGameLoop();

    // Shutdown the SteamAPI
    SteamAPI_Shutdown();

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
  hPrevInstance;
    return RealMain( lpCmdLine, hInstance, nCmdShow );
}
#endif
