#include "stdafx.h"
#include "LobbyConnection.h"
#include <winsock2.h>
#include "System\StarForce\StarForce.h"
#include <Tlhelp32.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Раньше этот класс был написан при помощи boost::asio, но выяснилось, что
//конструктор boost::asio::io_service падает при запуске под Wine на движке WS8WineCXG10.1.1.
//С обычным wine-1.3.32 всё в порядке. Определение BOOST_ASIO_DISABLE_IOCP не помогает.
class CastleConnection: public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( CastleConnection, BaseObjectST )  

public:
#pragma code_seg(push, "~")
  STARFORCE_EXPORT CastleConnection( int port )
  {
    STARFORCE_STOPWATCH();

    WORD versionRequested = MAKEWORD( 2, 2 );
    WSADATA wsaData = { 0 };
    ::WSAStartup( versionRequested, &wsaData );

    hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if( hSocket == SOCKET_ERROR )
    {
      DebugTrace( "Create socket error" );
      return;   
    }

    sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(port);

    if ( connect(hSocket, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR )
    {
      DebugTrace( "Socket connection error" );
      return;    
    }

    DebugTrace( "Connection with lobby established" );

    const int flag = 1;
    setsockopt( hSocket, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int) );  
  }
#pragma code_seg(pop)

  ~CastleConnection()
  {
    if( hSocket != SOCKET_ERROR )
    { 
      shutdown( hSocket, SD_BOTH );
      closesocket( hSocket );
    }

    ::WSACleanup();
  }

  void DoSendCommand( const char *s )
  {
    if( hSocket == SOCKET_ERROR )
      return;

    if( send(hSocket, s, strlen(s), 0) == SOCKET_ERROR )
      DebugTrace( "Socket write error" );
    else
      DebugTrace( "Command send: %s", s );
  }

  void DoUpdate( float seconds )
  {
    //Nothing
  }

private:
  int hSocket;
}; 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class DummyCaslteLink : public ICastle, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( DummyCaslteLink, ICastle, BaseObjectST );

public:

  DummyCaslteLink() {}

  virtual void Update( float seconds ) {}
  virtual void StartRender() {}
  virtual void ReturnToCastle() {}
  virtual void QuitGame() {}
};


// DWORD castleProcess = 0;

// void OnCreateWndHook( WPARAM wParam, LPARAM lParam )
// {
//   LPCBT_CREATEWND createWnd = (LPCBT_CREATEWND)lParam;
//   createWnd->lpcs->style &= ~WS_VISIBLE;
//   //      createWnd->lpcs->cx = 50;
//   //      createWnd->lpcs->cy = 50;
//   //      createWnd->lpcs->x = 0;
//   //      createWnd->lpcs->y = 0;
// 
//   WNDCLASS oldClass;
//   GetClassInfo( createWnd->lpcs->hInstance, createWnd->lpcs->lpszClass, &oldClass );
// 
//   char _message[2048];
// 
//   sprintf_s( _message, 2048, "Class: %s ( hi: %p ) ( brush %p ) %d %d %d %d", oldClass.lpszClassName, oldClass.hInstance, oldClass.hbrBackground,
//     createWnd->lpcs->cx,
//     createWnd->lpcs->cy,
//     createWnd->lpcs->x,
//     createWnd->lpcs->y );
// 
//   MessageBox( NULL, _message, "Ping", MB_OK );
// 
//   WNDCLASS newWndClass = { 
//     oldClass.style | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
//     oldClass.lpfnWndProc,
//     oldClass.cbClsExtra,
//     oldClass.cbWndExtra,
//     oldClass.hInstance,
//     oldClass.hIcon,
//     oldClass.hCursor,
//     (HBRUSH)GetStockObject( NULL_BRUSH ),
//     oldClass.lpszMenuName,
//     "UnityWndClass_PW" //oldClass.lpszClassName,
//   };
// 
//   BOOL _unreg = UnregisterClass( createWnd->lpcs->lpszClass, createWnd->lpcs->hInstance );
//   ATOM _reg = RegisterClass( &newWndClass );
// 
//   WNDCLASS newClass;
//   GetClassInfo( createWnd->lpcs->hInstance, newWndClass.lpszClassName, &newClass );
// 
//   sprintf_s( _message, 2048, "New Class: %s ( hi: %p ) ( ureg: %ld, reg: %hd ) ( brush %p, null brush %p )", 
//       newClass.lpszClassName, oldClass.hInstance, 
//       _unreg, _reg,
//       newClass.hbrBackground, (HBRUSH)GetStockObject( NULL_BRUSH ) );
//   MessageBox( NULL, _message, "Ping", MB_OK );
// 
//   HRGN hrgn = CreateRectRgn(0,0,0,0);
//   SetWindowRgn( (HWND)wParam, hrgn, TRUE );
// }
// 
// LRESULT CALLBACK CbtHook( int nCode, WPARAM wParam, LPARAM lParam )
// {
//   if ( HCBT_CREATEWND == nCode )
//   {
//     static bool firstTime = true;
//     if ( !firstTime )
//       return 0;
//     firstTime = false;
// 
//     OnCreateWndHook( wParam, lParam );
//   } 
//   else if (  HCBT_MOVESIZE == nCode  )
//   {
// //     static bool firstTime = true;
// //     if ( !firstTime )
// //       return 0;
// //     firstTime = false;
// // 
// //     LPRECT lpRect = (LPRECT)lParam;
// // 
// //     char _message[2048];
// // 
// //     sprintf_s( _message, 2048, "New size: b:%ld t:%ld l:%ld r:%ld", 
// //       lpRect->bottom,
// //       lpRect->top,
// //       lpRect->left,
// //       lpRect->right );
// // 
// //     MessageBox( NULL, _message, "SetSize", MB_OK );
// 
// //    ShowWindow( (HWND)wParam, SW_HIDE );
//   }
//   else if ( HCBT_ACTIVATE == nCode )
//   {
//     ShowWindow( (HWND)wParam, SW_HIDE );
//     SetWindowRgn( (HWND)wParam, NULL, TRUE );
// 
//     //    ShowWindow( (HWND)wParam, SW_HIDE );
//   }
// 
//   return 0; //CallNextHookEx( 0, nCode, wParam, lParam );
// }


// HINSTANCE GetProcessHInstance(  DWORD dwProcessId )
// {
//   HANDLE hModulesSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwProcessId ); 
// 
//   if ( hModulesSnap == INVALID_HANDLE_VALUE ) 
//     return 0; 
// 
//   MODULEENTRY32 me32 = {0};
//   me32.dwSize = sizeof( MODULEENTRY32 ); 
// 
//   if ( Module32First( hModulesSnap, &me32 ) ) 
//   { 
//     do 
//     {
//       nstl::string moduleName = me32.szExePath;
// 
//       if ( moduleName.find( "castle.exe" ) != nstl::wstring::npos )
//         return me32.hModule;
// 
//     } while ( Module32Next( hModulesSnap, &me32 ) );
//   }
// 
//   return 0; 
// }

class RealCastleLink : public ICastle, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( RealCastleLink, ICastle, BaseObjectST );

public:

  RealCastleLink( int port, const char* _castleCmdLine, HINSTANCE _instance, HWND _sessionWnd )
    : castleConnection()
  {
    if (port > 0)
      castleConnection = new CastleConnection( port );

    restartCastle = false;
    sessionWnd = _sessionWnd;
    appInstance = _instance;

    if ( Compatibility::IsRunnedUnderWine() )
      return;

    if ( !_castleCmdLine )
      return;

    castleCmdLine = _castleCmdLine;

    if ( castleCmdLine.empty() || castleCmdLine == "do_not_restart" )
      return;

    restartCastle = true;
  }

  virtual void Update( float seconds ) 
  {
    if ( castleConnection )
      castleConnection->DoUpdate( seconds );
  }
  
  virtual void StartRender() 
  {
    if ( castleConnection )
      castleConnection->DoSendCommand( "StartRender\n" );
  }

  virtual void ReturnToCastle() 
  {
    if ( restartCastle )
    {
      SetCurrentDirectory( "./../../Castle" );

      PROCESS_INFORMATION pi;
      STARTUPINFO si;

      ZeroMemory(&si, sizeof(si));
      si.cb = sizeof(si);

      ZeroMemory(&pi, sizeof(pi));

	  
	  castleCmdLine.replace(castleCmdLine.find("<"), 1, "\"");
	  castleCmdLine.replace(castleCmdLine.find(">"), 1, "\"");

      TCHAR commandLine[2048];
      sprintf_s( commandLine, "%s", castleCmdLine.c_str() );

      ShowWindow( sessionWnd, SW_HIDE );
      Sleep(100);

      if ( !CreateProcess(NULL, commandLine, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi) )
      {
        ErrorTrace( "Could not restart Castle" );
		DWORD result = GetLastError();
		if ( result != 0 )
		{
		  TCHAR buffer[2048];
		  TCHAR cTemp[512];
		  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 0, result, 0, cTemp, 512, NULL);
		  sprintf_s(buffer, 2048, "Error %d: %s Command line: %s", result, cTemp, commandLine);
		  ErrorTrace(buffer);
		}
      }

      SetCurrentDirectory( "./../PvP/Bin" );
    }
    else if ( castleConnection )
    {
      castleConnection->DoSendCommand( "ReturnToCastle\n" );
    }
  }
  
  virtual void QuitGame() 
  {
    if ( !restartCastle && castleConnection )
      castleConnection->DoSendCommand( "QuitGame\n" );
  }

private:
  Strong<CastleConnection> castleConnection;
  bool restartCastle;
  nstl::string castleCmdLine;

  HWND sessionWnd;
  HINSTANCE appInstance;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Strong<ICastle> CreateCastleLink( int port, const char* castleCmdLine, HINSTANCE _instance, HWND _sessionWnd  )
{
  return new RealCastleLink( port, castleCmdLine, _instance, _sessionWnd );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Strong<ICastle> CreateDummyCastleLink()
{
  return new DummyCaslteLink();
}
