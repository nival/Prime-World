#include <windows.h>
#include <shlwapi.h>
#include <crtdbg.h>

extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;

#pragma warning( disable: 4800 ) // warning C4800: 'type' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning( disable: 4100 ) // warning C4100: 'identifier' : unreferenced formal parameter
#pragma warning( disable: 4127 ) // warning C4127: conditional expression is constant

size_t StrLength( LPCTSTR str )
{
  return StrCSpn( str, TEXT( "" ) );
}

//#define PW_CREATE_TEST_PLUGIN_WINDOW

#ifdef PW_CREATE_TEST_PLUGIN_WINDOW

static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

HWND DebugCreateWindow( HINSTANCE hInstance )
{
  WNDCLASS wndClass = { 0, WndProc, 0, 0, hInstance,
    NULL/*LoadIcon( hInstance, nIcon )*/,
    0, 
    (HBRUSH)GetStockObject( NULL_BRUSH ), // NULL_BRUSH // WHITE_BRUSH
    NULL, "PWPluginWindowClass" };
  wndClass.style |= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  ATOM atomWndClassName = RegisterClass( &wndClass );
  atomWndClassName;

  DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
  DWORD dwExStyle = WS_EX_APPWINDOW;
  return CreateWindowEx( dwExStyle, "PWPluginWindowClass", "PW Window", dwStyle,
    50, 50, 800, 600,
    0, 0, hInstance, 0 );
}

#else //PW_CREATE_TEST_PLUGIN_WINDOW

HWND DebugCreateWindow( HINSTANCE hInstance ) { return 0; }

#endif //PW_CREATE_TEST_PLUGIN_WINDOW


typedef void WINAPIV TStartPWPlugin( HWND hWnd );


#ifndef DO_NOT_USE_DLLMAIN
bool LaunchGameDll()
{
  const size_t MAX_MOD_NAME = 1024;
  TCHAR szModuleName[MAX_MOD_NAME] = TEXT("");

  DWORD result = GetModuleFileName( GetModuleHandle( NULL ), szModuleName, MAX_MOD_NAME );
  if ( !result || ( result == MAX_MOD_NAME ) )
    return false;

  LPTSTR slash = StrRChr( szModuleName, NULL, TEXT( '\\' ) );
  if ( !slash )
    return false;

  slash[1] = 0;

  LPCTSTR pszDllName = TEXT( "PW_Client.dll" );

  const size_t MAX_DLL_NAME = 1536;
  TCHAR szDllName[MAX_DLL_NAME] = TEXT("");

  _ASSERT( MAX_MOD_NAME + StrLength( pszDllName ) + 1 < MAX_DLL_NAME );

  StrCpy( szDllName, szModuleName );
  StrCat( szDllName, pszDllName );

  HMODULE hDll = LoadLibraryEx( szDllName, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
  if ( !hDll )
    return false;

  TStartPWPlugin * proc = (TStartPWPlugin *)GetProcAddress( hDll, "StartPWApplication" );//TEXT( "StartPWApplication" ) );
  if ( !proc )
    return false;

  (*proc)( DebugCreateWindow( GetModuleHandle( NULL ) ) );

  FreeLibrary( hDll );
  return true;
}
#else
  extern "C" void WINAPIV StartPWApplication( HWND hWnd );
#endif


int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, char * lpCmdLine, int nCmdShow )
{
	SetProcessDPIAware();

#ifndef DO_NOT_USE_DLLMAIN
  if ( !LaunchGameDll() )
  {
    MessageBox( 0, TEXT( "Could not launch main executable. Please re-install the application." ), TEXT( "Unpredictable Error" ), MB_OK | MB_ICONERROR );
  }
#else 
  StartPWApplication( DebugCreateWindow( GetModuleHandle( NULL ) ) );
#endif
    
  return 0;
}
