#include "stdafx.h"

#include "ClientWindow.h"
#include "GameStarter.h"
#include "LocationClientRunner.h"

#include "System/TextFileDumper.h"
#include "System/FileStreamDumper.h"
#include "System/AssertDumper.h"
#include "System/ConsoleDumper.h"
#include "System/EventDumper.h"
#include "System/DebugTraceDumper.h"

typedef threading::ProcessingThread<Location::LocationClientRunner> ClientThread;

bool ParseCommandLine( LPTSTR lpCmdLine, nstl::string& _address, nstl::string& _login, nstl::string& _pass )
{
  if ( ::strnlen_s( lpCmdLine, 1024 ) == 0 )
    return false;

  vector<string>  commands;
  NStr::SplitString( lpCmdLine, &commands, ' ' );

  if ( commands.size() == 1 || commands.size() == 3 )
  {
    _address = commands[0];

    if ( commands.size() == 3 )
    {
      _login = commands[1];
      _pass = commands[2];
    }

    return true;
  }

  systemLog( NLogg::LEVEL_MESSAGE ) << "Simple game" << endl;
  systemLog( NLogg::LEVEL_MESSAGE ) << "Usage: MainClient <login address> [login] [password]" << endl;

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
  NLogg::CTextFileDumper textLogDumper( &GetSystemLog(), "TextLog" );
  NLogg::CTextFileDumper perfTextLogDumper( &GetPerfLog(), "PerfLog" );
  NLogg::CAssertDumper g_assertDumper( &GetSystemLog(), "Assert" );
  NLogg::ConsoleDumper g_consoleDumper( &GetSystemLog(), "Console" );
  NLogg::CDebugTraceDumper g_debugTraceDumper( &GetSystemLog(), "DebugTrace" );
  NLogg::CEventDumper g_eventDumper( &GetSystemLog(), "Event" );

  CObj<Location::ClientWindow> clientWindow = new Location::ClientWindow();
  Location::GameStarter gameStarter;

  if ( !gameStarter.Start() )
    return 0xDEAD;

  nstl::string address;
  nstl::string login;
  nstl::string password;

  if ( !ParseCommandLine( lpCmdLine, address, login, password ) )
    return 0xDEAD;

  if ( !gameStarter.Connect( address.c_str(), login.c_str(), password.c_str() ) )
    return 0xDEAD;

  Location::LocationClientRunner* clientRunner = new Location::LocationClientRunner();
  clientRunner->Set( gameStarter.GetTransport() );
  ClientThread* clientThread = new ClientThread( *clientRunner );

  if ( !clientWindow->InitWindow( hInstance, 800, 600 ) )
    return 0xDEAD;

  while( !clientRunner->GetClient() )
    Sleep(1);
  clientWindow->SetLocationClient( clientRunner->GetClient() );
  clientRunner->GetClient()->SetDebugDraw( clientWindow );

  clientWindow->Run();

  clientThread->Stop( true, 2000 );
  delete clientRunner;
  delete clientThread;

  return 0;
}
