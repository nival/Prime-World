
#include <windows.h>
#include <stdio.h>

#include <Vendor/DirectX/Include/d3d9.h>
#include <Vendor/DirectX/Include/d3dx9.h>
#include <Vendor/DirectX/Include/DxErr.h>
#include <time.h>

static bool doExit = false;
static bool startPWClient = false;
static bool PWClientStarted = false;
static ATOM atomWndClassName = 0;

typedef void WINAPIV TStartPWPlugin( HWND hWnd, int width, int height, bool fullscreen, const char* sessionID );

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  switch ( uMsg )
  {
    case WM_CLOSE:
      PostQuitMessage( 0 );
      return 0;

    case WM_LBUTTONDOWN:
      doExit = true;
      break;

    case WM_RBUTTONDOWN:
      startPWClient = true;
      break;
  }

  return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

// LRESULT CALLBACK WndProcForPW( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
// {
//   switch ( uMsg )
//   {
//   case WM_PAINT:
//     {
//       {
//         HDC hDC = (HDC)wParam;
//         RECT clientRect;
//         GetClientRect( hWnd, &clientRect );
// 
//         COLORREF clrOld = ::SetBkColor( hDC, RGB(0,0,0) );
//         ::ExtTextOut( hDC, 0, 0, ETO_OPAQUE, &clientRect, NULL, 0, NULL );
//         ::SetBkColor( hDC, clrOld );
//       }
//     }
//     break;
//   }
// 
//   return DefWindowProc( hWnd, uMsg, wParam, lParam );
// }

class MainLoop
{
public:
  
  MainLoop() : pDevice( 0 )
  {
    pD3D = Direct3DCreate9( D3D_SDK_VERSION );
  }

  ~MainLoop()
  {
    if ( pDevice )
      pDevice->Release();

    pDevice = 0;

    pD3D->Release();
    pD3D = 0;
  }

  void PumpMessages( double sec = 0 )
  {
    MSG msg;

    doExit = false;

    const clock_t endwait = static_cast<clock_t>( clock() + sec * CLOCKS_PER_SEC );

    for ( ;; )
    {
      if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE) )
      {     
        if ( msg.message == WM_QUIT )
          doExit = true;
        else
        {
          TranslateMessage( &msg );
          DispatchMessage( &msg );
        }
      }
      else if( clock() >= endwait )
        return;
     }
  }

  HWND CreateWndDirect3d( LPCSTR pszApp, LPCSTR pszWnd, unsigned dwWidth, unsigned dwHeight, WNDPROC wndProc )
  {
    // create and register class style
    // Register the windows class
    WNDCLASS wndClass = { 0, wndProc, 0, 0, hInstance,
      0,
      0, 
      (HBRUSH)GetStockObject( NULL_BRUSH ),
      NULL, pszApp };
    wndClass.style |= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    atomWndClassName = RegisterClass( &wndClass );


    //Create transparent window 
    HWND newWnd = CreateWindowEx( 0, pszApp, pszWnd, WS_POPUP | WS_VISIBLE,
      0, 0, dwWidth, dwHeight,
      0, 0, hInstance, 0 );

    if ( !newWnd )
      return 0;

    ShowWindow( newWnd, SW_SHOW );
    UpdateWindow( newWnd );

    hCursor = LoadCursor( NULL, IDC_ARROW );
    ::SetCursor( hCursor );

    return newWnd;
  }
  
  HWND CreateWndBlock( LPCSTR pszApp, LPCSTR pszWnd, WNDPROC wndProc )
  {
    // create and register class style
    // Register the windows class
    WNDCLASS wndClass = { 0, wndProc, 0, 0, hInstance,
      0,
      0, 
      (HBRUSH)GetStockObject( BLACK_BRUSH ),
      NULL, pszApp };
    wndClass.style |= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    atomWndClassName = RegisterClass( &wndClass );


    //Create transparent window 
    HWND newWnd = CreateWindowEx( WS_EX_TOPMOST | WS_EX_TOOLWINDOW, pszApp, pszWnd, WS_POPUP | WS_VISIBLE,
      -4000, -4000, 8000, 8000,
      0, 0, hInstance, 0 );

    if ( !newWnd )
      return 0;

    SetWindowLong( newWnd, GWL_WNDPROC, (LONG)wndProc );

    ShowWindow( newWnd, SW_SHOW );
    UpdateWindow( newWnd );

    hCursor = LoadCursor( NULL, IDC_ARROW );
    ::SetCursor( hCursor );

    return newWnd;
  }

  void CreateRenderer( int _width, int _height, bool _fullscreen )
  {
    width = _width;
    height = _height;
    fullscreen = _fullscreen;

    CreateOrReset( true, _fullscreen );
  }

  void CreateOrReset( bool create, bool fullscreen )
  {
    UINT AdapterToUse = D3DADAPTER_DEFAULT;
    D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;

    DWORD dwCreateFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;

    D3DPRESENT_PARAMETERS pp; 

    ZeroMemory(&pp, sizeof(pp));
    pp.hDeviceWindow = hWnd;
    pp.BackBufferWidth = width;
    pp.BackBufferHeight = height;
    pp.Windowed = fullscreen ? FALSE : TRUE;
    pp.FullScreen_RefreshRateInHz = fullscreen ? 70 : 0;
    pp.EnableAutoDepthStencil = true;
    pp.AutoDepthStencilFormat = D3DFMT_D24S8;
    pp.SwapEffect = fullscreen ? D3DSWAPEFFECT_FLIP : D3DSWAPEFFECT_COPY;
    pp.BackBufferFormat = D3DFMT_A8R8G8B8;
    pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    // Try to create chosen device
    HRESULT hr;
    
    if ( create )
    {
      hr = pD3D->CreateDevice( AdapterToUse, DeviceType, (HWND)hWnd, 
        dwCreateFlags,	&pp, &pDevice );
    }
    else
    {
      hr = pDevice->Reset( &pp );
    }

    // Notify about failure
    if ( FAILED(hr) )
    {
      char error[1024];
      sprintf_s( error, "0x%08X (%s)", hr, DXGetErrorStringA(hr) );
      OutputDebugStr( error );
    }
  }

  void Init( HINSTANCE _hInstance, const char *pszAppName, const char *pszWndName, int _width, int _height, bool _fullscreen )
  {
    hInstance = _hInstance;

    ZeroMemory( &curDevMode, sizeof(DEVMODE) );

    curDevMode.dmSize = sizeof(DEVMODE);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &curDevMode);

    hWnd = CreateWndDirect3d( pszAppName, pszWndName, _width, _height, WndProc );
    CreateRenderer( _width, _height, _fullscreen );
  }

  void Draw()
  {
    if ( pDevice )
    {
      if ( pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET || pDevice->TestCooperativeLevel() == D3DERR_DEVICELOST )
        CreateOrReset( false, fullscreen );

      pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
      pDevice->Present( NULL, NULL, hWnd, NULL);
    }
  }

  void Run()
  {
    while ( !doExit )
    {
      PumpMessages();
      
      if( !PWClientStarted )
        Draw();

      if ( startPWClient && !PWClientStarted )
      {
        PWClientStarted = true;
        startPWClient = false;
        StartPWClientAsProcess();
      }
    }
  }

  bool StartPWClient()
  {
//     const size_t MAX_MOD_NAME = 1024;
//     TCHAR szModuleName[MAX_MOD_NAME] = "";
// 
//     DWORD result = GetModuleFileName( GetModuleHandle( NULL ), szModuleName, MAX_MOD_NAME );
//     if ( !result || ( result == MAX_MOD_NAME ) )
//       return false;
// 
//     LPTSTR slash = StrRChr( szModuleName, NULL, TEXT( '\\' ) );
//     if ( !slash )
//       return false;
// 
//     slash[1] = 0;
// 
//    TCHAR szDirectory[MAX_PATH] = "";
//    ::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
//     LPSTR dir = StrCat(szDirectory, TEXT("/../PvP/Bin"));
//     SetCurrentDirectory(dir);
//     ::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
//     LPSTR pszDllName = StrCat(szDirectory, TEXT("/PW_Client.dll"));

    SetCurrentDirectory("../../_Debug/");
    HMODULE hDll = LoadLibraryEx( "PW_Client.dll", NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
    SetCurrentDirectory("../../Bin/");

    TCHAR szDirectory[MAX_PATH] = "";
    ::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);

    if ( !hDll )
    {
      return false;
    }

    //MessageBox(0,sessionID,"SessionID",MB_OK);

    TStartPWPlugin* proc = (TStartPWPlugin*)GetProcAddress( hDll, TEXT( "StartPWPlugin" ) );

    if ( !proc )
    {
      return false;
    }

    proc( 0, width, height, fullscreen, 0/*"Test/Test/Test"*/ );

    FreeLibrary( hDll );
    return true;
  }

  static bool StartPW( int width, int height, int fullscreen )
  {
    STARTUPINFO         si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    ZeroMemory(&pi, sizeof(pi));
  
    // Start the child process. 
    SetCurrentDirectory("..\\..\\..\\Bin");

    char commandLine[2048];
    sprintf_s( commandLine, "..\\Src\\_Release\\PW_Game.exe parentWidth %d parentHeight %d parentFullscreen %d", 
      width, height, (int)fullscreen );

    return CreateProcess(NULL, commandLine, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi) != FALSE; 
  }

  bool StartPWClientAsProcess()
  {
    hWndForPW = CreateWndBlock( "A", "B", DefWindowProc );

    APPBARDATA data = {};

    data.cbSize = sizeof(data);
    data.hWnd = ::FindWindow( "Shell_TrayWnd", NULL );
    data.lParam = ABS_AUTOHIDE;
    //SHAppBarMessage( ABM_SETSTATE, &data );
    
    ShowCursor( FALSE );

    PumpMessages(2);
    
    DEVMODE newDevMode = curDevMode;
    newDevMode.dmPelsWidth =  width;
    newDevMode.dmPelsHeight = height;
    newDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    ChangeDisplaySettings( &newDevMode, CDS_UPDATEREGISTRY | CDS_NORESET );
    
    PumpMessages(2);
     
    //CreateOrReset( false, false );
    ShowWindow(hWnd, SW_FORCEMINIMIZE ); 
    
    PumpMessages(2);
     
    StartPW( width, height, fullscreen );
  
    PumpMessages(10);
        
    data.lParam = 0;
    //SHAppBarMessage( ABM_SETSTATE, &data );
    
    newDevMode.dmPelsWidth =  curDevMode.dmPelsWidth;
    newDevMode.dmPelsHeight = curDevMode.dmPelsHeight;
    ChangeDisplaySettings( &newDevMode, CDS_UPDATEREGISTRY | CDS_NORESET );
    PumpMessages(2); 
    DestroyWindow( hWndForPW ); 
    ShowCursor( TRUE );
    
    return true;   
  }

private:

  HINSTANCE hInstance;
  HWND hWnd;
  HWND hWndForPW;
  HCURSOR hCursor;
  DEVMODE curDevMode;

  HANDLE hPWProcess;

  int width;
  int height;
  bool fullscreen;

  IDirect3D9*           pD3D;
  IDirect3DDevice9*     pDevice;
};

int main(int argc, char* argv[])
{
  MainLoop firstPart;
  MainLoop secondPart;

  int width = 1024;
  int height = 768;
  bool fullscreen = true;

  firstPart.Init( GetModuleHandle( NULL ), "FullScreenTest", "FullScreenTest", width, height, fullscreen );
  firstPart.Run();

	return 0;
}

