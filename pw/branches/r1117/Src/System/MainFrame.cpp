#include "StdAfx.h"
#include "MainFrame.h"
#include "Thread.h"
#include "FileSystem/FileUtils.h"
#include "FileSystem/FilePath.h"
#include "StackWalk.h"
#include "BSUtil.h"
#include "../System/InlineProfiler.h"

#include <MemoryLib/NewHandler.h>

DEV_VAR_STATIC bool s_backgroundLogic = true;
REGISTER_DEV_VAR("enable_background_logic", s_backgroundLogic, STORAGE_NONE);

static bool s_clipCursorInWindowedMode = true;
REGISTER_VAR("enable_cursor_clip", s_clipCursorInWindowedMode, STORAGE_USER);

////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace NMainFrame;
////////////////////////////////////////////////////////////////////////////////////////////////////
static HWND hWnd = 0;														// window handle
static HWND hWndSplashScreen;
static HINSTANCE hInstance = 0;									// instance handle
static ATOM atomWndClassName = 0;								// atom window class name identification (assigned during registration)
static volatile bool bExit = false;
static volatile bool bActive = true;
static volatile bool bNotMinimized = true;
static threading::Mutex msgs;
static nstl::vector<SWindowsMsg> msgList;
static int currentMsgIndex=0;
static HCURSOR hCursor;
static bool bManageCursor = true;
static bool s_bMinimizeOnDeactivate = false;
static bool bAppAlwaysActive = false;
static bool s_fullscreen = false;
static bool s_borderless = false;
static WNDPROC s_OldWindowProc = 0;
static ULONG s_prevScreenWidth = 0;
static ULONG s_prevScreenHeight = 0;

static DWORD wndCaptionSize = 0;
static DWORD wndXBorderSize = 0;
static DWORD wndBottomBorderSize = 0;

static Weak<ICloseApplicationHandler> closeHandler;

static nstl::string s_exitCode = "";
static bool cursorClipDisabled = false;

static CTPoint<int> g_windowCenterPos( -1, -1 );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline LONG Width( const RECT &r )
{
  return r.right - r.left;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline LONG Height( const RECT &r )
{
  return r.bottom - r.top;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class PosT>
inline void SetPos( const PosT &pos, RECT &rect )
{
  rect.right += pos.x - rect.left; 
  rect.bottom += pos.y - rect.top; 
  rect.left = pos.x; 
  rect.top = pos.y;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
struct SSaveCursorClip
{
	~SSaveCursorClip() { ClipCursor(0); }
} doSaveCursorClip;

////////////////////////////////////////////////////////////////////////////////////////////////////
static void ResetExit()
{
	bExit = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NMainFrame::GetMessage( SWindowsMsg *pRes )
{
  threading::MutexLock lock( msgs );
	if ( currentMsgIndex < msgList.size() )
	{
		*pRes = msgList[currentMsgIndex++];
		return true;
	}
	pRes->msg = SWindowsMsg::TIME;
	NHPTimer::GetTime( pRes->time );
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool NMainFrame::IsAppActive()
{
	return bActive;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool NMainFrame::IsAppNotMinimized()
{
	return bNotMinimized;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static void SetActive( bool _bActive )
{
	bNotMinimized = _bActive;	 
	
	if ( bAppAlwaysActive )
		return;

	bActive = _bActive;				// activation flag 
	if ( s_bMinimizeOnDeactivate )
	{
    if ( !bActive )
			ShowWindow( hWnd, SW_MINIMIZE );
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool NMainFrame::IsExit()
{
	return bExit;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static void AddMsgCursor();

static const uint uTimerID = 17;

void NMainFrame::PumpMessages()
{
  NI_PROFILE_FUNCTION

	ResetExit();

  // Should send mouse position continuously for smooth performance
  AddMsgCursor();

  // Now we are ready to receive and process Windows messages
	static MSG msg;
	while ( PeekMessageW( &msg, 0, 0, 0, PM_REMOVE ) )
	{
		if ( msg.message == WM_QUIT )
			bExit = true;
    else
		{
			TranslateMessage( &msg );
			DispatchMessageW( &msg );
		}
	}
}

HWND NMainFrame::GetWnd()
{
	return hWnd;
}

void  NMainFrame::SetWnd(HWND _hwnd)
{
  hWnd = _hwnd;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
HINSTANCE NMainFrame::GetInstance()
{
	return hInstance;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMainFrame
{

void SetEditorWnd( HWND _hWnd )
{
	hWnd = _hWnd;
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NMainFrame::Exit()
{
  PostQuitMessage(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NMainFrame::Exit( const nstl::string& exitCode )
{
  SetExitCode( exitCode );
  PostQuitMessage(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NMainFrame::SetExitCode( const nstl::string& exitCode )
{
  s_exitCode = exitCode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const nstl::string& NMainFrame::GetExitCode()
{
  return s_exitCode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void AddMsg( SWindowsMsg::EMsg msg, int x, int y, DWORD dwFlags )
{
  NI_PROFILE_FUNCTION

	NHPTimer::STime time;
	NHPTimer::GetTime( time );
	threading::MutexLock lock( msgs );
	if (currentMsgIndex >= msgList.size())
	{
		currentMsgIndex = 0;
		msgList.clear();
	}
	if (msgList.size() >= msgList.capacity())
	{
	    int oldSize = msgList.capacity();
		msgList.reserve(oldSize+oldSize/2+1);
	}
	SWindowsMsg &m = msgList.push_back();
	m.time = time;
	m.msg = msg;
	m.x = x;
	m.y = y;
	m.dwFlags = dwFlags;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

static void OnWmMove( HWND hWnd, int x, int y )
{
  if( !s_fullscreen )
  {
    RECT rect;
    if( ::GetClientRect(GetWnd(), &rect) )
    {        
      g_windowCenterPos.x = x + Width(rect) / 2;   
      g_windowCenterPos.y = y + Height(rect) / 2; 
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

static bool CreateWnd( LPCSTR pszApp, LPCSTR pszWnd, unsigned dwWidth, unsigned dwHeight, LPCWSTR nIcon, HWND hParentWnd )
{
	// create and register class style
				// Register the windows class

  wstring wcharBuffer;
  NStr::ToUnicode( &wcharBuffer, string( pszApp ) );
  LPCWSTR pszAppW = wcharBuffer.c_str();

  
	WNDCLASSW wndClass = { 0, WndProc, 0, 0, hInstance,
    LoadIconW( hInstance, nIcon), //TODO nIcon might be an actual image instead of resource
												0, 
												(HBRUSH)GetStockObject( NULL_BRUSH ),
												NULL, pszAppW};
	wndClass.style |= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	atomWndClassName = RegisterClassW( &wndClass );


  if( g_windowCenterPos.x == -1 && g_windowCenterPos.y == -1 )
  {
    g_windowCenterPos.x = GetSystemMetrics( SM_CXSCREEN ) / 2;
    g_windowCenterPos.y = GetSystemMetrics( SM_CYSCREEN ) / 2; 
  }

  wstring wcharBuffer2;
  NStr::ToUnicode( &wcharBuffer2, string( pszWnd ) );
  LPCWSTR pszWndW = wcharBuffer2.c_str();
  
  //Create transparent window 
  hWnd = CreateWindowExW( hParentWnd ? 0 : WS_EX_APPWINDOW , pszAppW, pszWndW, (hParentWnd ? WS_CHILD : WS_POPUP) | WS_VISIBLE | WS_SYSMENU,
												 g_windowCenterPos.x - dwWidth / 2, g_windowCenterPos.y - dwHeight / 2, dwWidth, dwHeight,
												 hParentWnd, 0, hInstance, 0 );

	if ( !hWnd )
	{
		//ThrowException( "Can't create main app window\n" );
		return false;
	}
	
  ShowWindow( hWnd, SW_SHOWNOACTIVATE );
  UpdateWindow( hWnd );

	// eliminate cursor once for this widow
	//::SetCursor( hCursor );

	hCursor = LoadCursor( NULL, IDC_ARROW );

  ni_detail::SetNewHandler(hWnd);
  SetWnd(hWnd);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void SetClipCursorRect( HWND _hWnd )
{
	RECT r;
	if (!GetWindowRect( _hWnd, &r ))
	  return;
	
  if ( !s_fullscreen && !s_borderless )
	{
    //NUM_TASK Сессия в оконном режиме - курсор не должен покидать пределы окна
    if (s_clipCursorInWindowedMode && !cursorClipDisabled)
    {
      r.top += wndCaptionSize;
      r.left += wndXBorderSize;
      r.right -= wndXBorderSize;
      r.bottom -= wndBottomBorderSize;
    }
    else
    {
      ClipCursor(0); 
      return;
    }
	}

  ClipCursor( &r );
	POINT p;
	GetCursorPos( &p );
	SetCursorPos( p.x, p.y );
}


////////////////////////////////////////////////////////////////////////////////////////////////////
static void (*StepFunc)() = 0;

void SetStepCallback( void (*_stepFunc)() ) { StepFunc = _stepFunc; }

////////////////////////////////////////////////////////////////////////////////////////////////////
// did not know how to return NCHitTest
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  NI_PROFILE_FUNCTION

  const uint uTimerPeriod = 34;
  static bool timerWasSet = false;


  switch ( uMsg )
  {
		//TODO:
		//case WM_NCACTIVATE:
		//	SetActive( wParam != 0 );
		//	return s_fullscreen ? 1 : 0;

    case WM_PAINT:
      break;
    case WM_GETMINMAXINFO:
      {
        MINMAXINFO *minMaxInfo = (MINMAXINFO*)lParam;
        minMaxInfo->ptMinTrackSize.x = 100;
        minMaxInfo->ptMinTrackSize.y = 100;
        minMaxInfo->ptMaxTrackSize.x = 0xFFFF;;
        minMaxInfo->ptMaxTrackSize.y = 0xFFFF;
        minMaxInfo->ptMaxSize.x = 0xFFFF;
        minMaxInfo->ptMaxSize.y = 0xFFFF;
        break;
      }
    case WM_SETCURSOR:
      ::SetCursor( hCursor );
      switch (LOWORD(lParam))
      {
      case HTCLOSE:
      case HTMAXBUTTON:
      case HTMINBUTTON:
        cursorClipDisabled = true;
        break;

      default:
        if(IsAppActive() && cursorClipDisabled)
        {
          // If we hover over title bar icons clipping is disabled. 
          // If we move into client area again make sure to re-enable clipping.
          cursorClipDisabled = false;
          SetClipCursorRect(hWnd);
        }
      }
      return TRUE;
    case WM_POWERBROADCAST:
      switch( wParam )
      {
      case PBT_APMQUERYSUSPEND:
        // At this point, the app should save any data for open
        // network connections, files, etc., and prepare to go into
        // a suspended mode.
        return TRUE;

      case PBT_APMRESUMESUSPEND:
        // At this point, the app should recover any data, network
        // connections, files, etc., and resume running from when
        // the app was suspended.
        return TRUE;
      }
      break;

    case WM_SYSCOMMAND:
      {
        // Prevent moving/sizing and power loss in fullscreen mode
        switch( wParam )
        {
          //case SC_MOVE:
        case SC_SIZE:
        case SC_MAXIMIZE:
        case SC_KEYMENU:
        case SC_MONITORPOWER:
        case SC_SCREENSAVE:
          return 1; // in both modes is prevented
        }
        break;
      }
    case WM_CLOSE:
      {
        bool processed = false;

        if ( IsValid(closeHandler) )
        {
          if ( closeHandler->OnCloseApplication() )
          {
            processed = true;
          }
        }

        if ( !processed )
        {
          PostQuitMessage( 0 );
        }
      }
    return 0;
    case WM_ACTIVATEAPP:
      SetActive( wParam != 0 );
      break;
    case WM_SIZE:
      {
        break;
      }
    case WM_MOVE:
      OnWmMove( hWnd, (int)(short) LOWORD(lParam), (int)(short) HIWORD(lParam) );
      break;
    case WM_ACTIVATE:
      {
        NI_PROFILE_BLOCK( "WM_ACTIVATE" )

        switch ( LOWORD(wParam) )
        {
        case WA_CLICKACTIVE:					// activate window
        case WA_ACTIVE:
        {
          bool minimized = HIWORD( wParam ) ? true : false;
          
          if ( !minimized && hWnd )
          {
             SetClipCursorRect( hWnd );
              
              //Мак, при закрытии модального окна, не присылает WM_ACTIVATEAPP и
              //поэтому, например, после ассерта приложение игнорирует 
              //клавиатуру и мышь.
              //Не очень понятно почему здесь не вызывается SetActive, но,
              //на всякий случай, будем делать это только под Mac
              if( Compatibility::IsRunnedUnderWine() )
                SetActive( true );  
          }
          else
            cursorClipDisabled = false;
          
          break;
        }
        case WA_INACTIVE:					 // deactivate window
          SetActive( false );
          ClipCursor( 0 );
          RECT r;
          if ( !GetClientRect( GetWnd(), &r ) )
            break;
            
          break;
        }
      }
      break;

    case WM_MOUSEMOVE:
      // Don't do it here, see: AddMsgCursor()
      // AddMsg( SWindowsMsg::MOUSE_MOVE, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF, wParam );
      break;
    case WM_RBUTTONDOWN:
      ::SetCapture( hWnd );
      AddMsg( SWindowsMsg::MOUSE_RB_DOWN, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF, wParam );
      break;
    case WM_RBUTTONDBLCLK:
      ::SetCapture( hWnd );
      AddMsg( SWindowsMsg::MOUSE_RB_DBLCLK, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF, wParam );
      break;
    case WM_RBUTTONUP:
      AddMsg( SWindowsMsg::MOUSE_RB_UP, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF, wParam );
      ::ReleaseCapture();
      break;
    case WM_LBUTTONDOWN:
      ::SetCapture( hWnd );
      AddMsg( SWindowsMsg::MOUSE_LB_DOWN, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF, wParam );
      break;
    case WM_LBUTTONDBLCLK:
      ::SetCapture( hWnd );
      AddMsg( SWindowsMsg::MOUSE_LB_DBLCLK, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF, wParam );
      break;
    case WM_LBUTTONUP:
      AddMsg( SWindowsMsg::MOUSE_LB_UP, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF, wParam );
      ::ReleaseCapture();
      break;
    case WM_MOUSEWHEEL:
      AddMsg( SWindowsMsg::MOUSE_WHEEL, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF, wParam );
      break;
    case WM_KEYDOWN:
      AddMsg( SWindowsMsg::KEY_DOWN, wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF );
      break;
    case WM_KEYUP:
      AddMsg( SWindowsMsg::KEY_UP, wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF );
      break;
    case WM_CHAR:
      AddMsg( SWindowsMsg::KEY_CHAR, wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFFFF );
      break;

    case WM_ENTERSIZEMOVE:
      cursorClipDisabled = false;
      if(s_backgroundLogic) {
        timerWasSet = SetTimer(hWnd, uTimerID, uTimerPeriod, NULL);
        //TraceMsg("Creating timer");
      }
      break;

    case WM_EXITSIZEMOVE:
      cursorClipDisabled = false;
      if(s_backgroundLogic && timerWasSet) {
        KillTimer(hWnd, uTimerID);
        timerWasSet = false;
        //TraceMsg("Killing timer");
      }
      SetActualClipCursorRect();
      break;

    case WM_ENTERMENULOOP:
      if(s_backgroundLogic) {
        timerWasSet = SetTimer(hWnd, uTimerID, uTimerPeriod, NULL);
        //TraceMsg("Creating timer");
        break;
      }
    case WM_EXITMENULOOP:
      if(s_backgroundLogic && timerWasSet) {
        KillTimer(hWnd, uTimerID);
        timerWasSet = false;
        //TraceMsg("Killing timer");
        break;
      }

    case WM_TIMER:
      if(s_backgroundLogic && wParam == uTimerID) {
          if(StepFunc)
            StepFunc();
          //TraceMsg("Timer tick processed");
          return 0; 
      }
  }
  return DefWindowProcW( hWnd, uMsg, wParam, lParam );
}



bool NMainFrame::InitApplication( HINSTANCE hInstance, const char *pszAppName, const char *pszWndName, LPCWSTR nIcon, bool fullscreen, int width, int height, HWND hUseWindow )
{
  DebugTrace( "Fullscreen: %i", fullscreen? 1:0 );
	::hInstance = hInstance;

  s_fullscreen = fullscreen;
  s_borderless = s_fullscreen;
	
  if ( hUseWindow )
  {
    if ( !CreateWnd( pszAppName, pszWndName, width, height, nIcon, 0 ) )
      return false;

//     ::hWnd = hUseWindow;
// 
//     s_OldWindowProc = (WNDPROC)GetWindowLong( hWnd, GWL_WNDPROC );
//     // Устанавливаем наш PW'шный
//     SetWindowLong( hWnd, GWL_WNDPROC, (LONG)WndProc );
// 
//     hCursor = LoadCursor( hInstance, IDC_ARROW );
  }
  else
  {
	  if ( !CreateWnd( pszAppName, pszWndName, width, height, nIcon, 0 ) )
		  return false;
  }
	NBSU::SetBSUWindow( GetWnd() );

  wndCaptionSize = ::GetSystemMetrics( SM_CYCAPTION ) + ::GetSystemMetrics( SM_CYEDGE ) + ::GetSystemMetrics( SM_CYBORDER );
  wndXBorderSize = (::GetSystemMetrics( SM_CXEDGE ) + ::GetSystemMetrics( SM_CXBORDER ));
  wndBottomBorderSize = (::GetSystemMetrics( SM_CYEDGE ) + ::GetSystemMetrics( SM_CYBORDER ));


	return true;
}



void ShutdownApplication()
{
  if ( hWnd && s_OldWindowProc )
    SetWindowLong( hWnd, GWL_WNDPROC, (LONG)s_OldWindowProc );
}



void NMainFrame::SetCursor( HCURSOR _hCursor )
{
	if ( !bManageCursor )
		return;

	if ( hCursor == _hCursor )
		return;
	hCursor = _hCursor;
	::SetCursor( hCursor );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NMainFrame::ShowCursor( bool bShow )
{
	if ( !bManageCursor )
		return;
	static bool bIsShown = (bool)3;
	if ( bIsShown == bShow )
		return;
	bIsShown = bShow;
	if ( bShow )
	{
		::ShowCursor( TRUE );
		::SetCursor( hCursor );
	}
	else
		::ShowCursor( FALSE );
}

HCURSOR NMainFrame::GetCurrentCursor()
{
  return hCursor;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static NMainFrame::SWindowsMsg::EMsg GetLocalCursorPos( int & x, int & y )
{
	x = y = 0;

	RECT rc;
			  
	if ( !GetClientRect( NMainFrame::GetWnd(), &rc ) )
    return SWindowsMsg::MOUSE_DISABLED;

  POINT pt = { 0, 0 };
	if ( !GetCursorPos( &pt ) )
		return SWindowsMsg::MOUSE_DISABLED;

  if ( !ScreenToClient( NMainFrame::GetWnd(), &pt ) )
    return SWindowsMsg::MOUSE_DISABLED;
    
  if( !IsAppActive() )
    return SWindowsMsg::MOUSE_DISABLED;
    
  x = pt.x;
  y = pt.y;
    
  if( pt.x < rc.left || pt.x >= rc.right || pt.y < rc.top || pt.y >= rc.bottom )
    return SWindowsMsg::MOUSE_OUT;

	return SWindowsMsg::MOUSE_MOVE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AddMsgCursor()
{
  NI_PROFILE_FUNCTION

  //@iA@TODO: сделать отправку сообщения только при изменении координат
	int x,y;

  const NMainFrame::SWindowsMsg::EMsg msg = GetLocalCursorPos( x, y );
	AddMsg( msg, x, y, 0 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NMainFrame::EnableCursorManagement( bool bEnable )
{
	bManageCursor = bEnable;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void AlignRect( const RECT &outer, RECT &inner )
{
  POINT newPos = { inner.left, inner.top };

  if( inner.right > outer.right )
    newPos.x -= inner.right - outer.right;

  if( inner.bottom > outer.bottom )
    newPos.y -= inner.bottom - outer.bottom;

  if( newPos.x < outer.left )
    newPos.x = outer.left;
      
  if( newPos.y < outer.top )
    newPos.y = outer.top;
    
  SetPos( newPos, inner );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static RECT GetVirtualScreenRect()
{
  RECT screenRect;

  screenRect.left = ::GetSystemMetrics(SM_XVIRTUALSCREEN);
  screenRect.top = ::GetSystemMetrics(SM_YVIRTUALSCREEN);
  screenRect.right = screenRect.left + ::GetSystemMetrics(SM_CXVIRTUALSCREEN);
  screenRect.bottom = screenRect.top + ::GetSystemMetrics(SM_CYVIRTUALSCREEN);

  return screenRect;
}    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static RECT GetMonitorRect( const RECT &windowRect )
{
  //Находим координаты и размер монитора на котором находится окно
  HMONITOR hMon = ::MonitorFromRect( &windowRect, MONITOR_DEFAULTTOPRIMARY );

  if( hMon == NULL )
    return GetVirtualScreenRect();

  MONITORINFOEX monInfo;
  monInfo.cbSize = sizeof(monInfo);
    
  if( !::GetMonitorInfo(hMon, &monInfo) )
    return GetVirtualScreenRect();  
    
  //Монитор может находиться в полноэкранном режиме и тогда его разрешение не соответствуют
  //разрешению оконного режима. В этом случае находим разрешение монитора в реестре и  
  //корректируем значения
  DEVMODE devMode;
  
  devMode.dmSize = sizeof(devMode);
  devMode.dmDriverExtra = 0;
  
  if( !::EnumDisplaySettings(monInfo.szDevice, ENUM_REGISTRY_SETTINGS, &devMode) )
    return monInfo.rcWork;
  
  //Увеличиваем размер рабочей области монитора на разницу между оригинальным 
  //разрешением монитора и текущем разрешением
  RECT res = { 
    monInfo.rcWork.left, monInfo.rcWork.top, 
    monInfo.rcWork.right + (devMode.dmPelsWidth - Width(monInfo.rcMonitor)), 
    monInfo.rcWork.bottom + (devMode.dmPelsHeight - Height(monInfo.rcMonitor))
  };
  
  return res;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NMainFrame::ResizeWindow( unsigned long width, unsigned long height, bool isFullScreen, bool isBorderless )
{
  //http://cboard.cprogramming.com/game-programming/56863-directx-mode-switching-fullscreen-windowed.html
  //http://www.gamedev.ru/code/forum/?id=15956
  const DWORD dwStyleFullscreen = WS_POPUP;
  const DWORD dwExStyleFullscreen = WS_EX_TOPMOST;
  const DWORD dwStyleNonFullscreen = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  const DWORD dwExStyleNonFullscreen = 0;

  const HWND hWindow = GetWnd();

  DWORD dwStyle = ::GetWindowLong(hWindow, GWL_STYLE);
  DWORD dwExStyle = ::GetWindowLong(hWindow, GWL_EXSTYLE);
  RECT rect;
  
  dwStyle |= WS_VISIBLE;

  if( isFullScreen )
  {
    ::SetRect( &rect, 0, 0, width, height );
    dwStyle = ( dwStyle & ~dwStyleNonFullscreen ) | dwStyleFullscreen;
    dwExStyle = ( dwExStyle & ~dwExStyleNonFullscreen ) | dwExStyleFullscreen;
  }
  else
  {
    //Центр окна должен остаться в той же позиции
    POINT newPos;

    newPos.x = g_windowCenterPos.x - (int)width / 2;
    newPos.y = g_windowCenterPos.y - (int)height / 2;
                                             
    dwStyle = ( dwStyle & ~dwStyleFullscreen ) | dwStyleNonFullscreen;
    dwExStyle = ( dwExStyle & ~dwExStyleFullscreen ) | dwExStyleNonFullscreen;

    ::SetRect( &rect, newPos.x, newPos.y, newPos.x + width, newPos.y + height );

    // Override fullscreen/windowed
    if (isBorderless) {
      dwStyle = dwStyleFullscreen;
      ::SetRect( &rect, 0, 0, width, height );
    }
  }

  ::SetWindowLong(hWindow, GWL_STYLE, dwStyle);
  ::SetWindowLong(hWindow, GWL_EXSTYLE, dwExStyle);

  if( !isFullScreen && !isBorderless )
  {
    ::AdjustWindowRectEx( &rect, 
      ::GetWindowLong(hWindow, GWL_STYLE), 
      ::GetMenu(hWindow) != NULL, 
      ::GetWindowLong(hWindow, GWL_EXSTYLE) 
    );
        
    //Нужно добиться того чтобы окно всегда влезало в монитор на котором оно находится
    AlignRect( GetMonitorRect(rect), rect );
  }
     
  s_fullscreen = isFullScreen;
  s_borderless = isBorderless;
   
  // adjust the size of the window
  ::SetWindowPos(
      hWindow, isFullScreen ? NULL : HWND_NOTOPMOST, 
      rect.left, rect.top, Width(rect) , Height(rect), 
      SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_SHOWWINDOW | SWP_FRAMECHANGED 
  );
    
  SetClipCursorRect( hWindow );
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void NMainFrame::ApplyNewParams( unsigned long width, unsigned long height, bool isFullScreen, bool isBorderless )
{
  ResizeWindow( width, height, isFullScreen, isBorderless );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NMainFrame::UpdateCursorRectInt( const char*, const vector<wstring> & )
{
	SetActualClipCursorRect();
	return true;
}

void NMainFrame::SetActualClipCursorRect()
{
  SetClipCursorRect( NMainFrame::GetWnd() );
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//TODO: move this stuff into appropriate place
struct SStyleSlot
{
  DWORD         style;
  const char *  name;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
static SStyleSlot s_stylesInfo[] =
{
  { WS_OVERLAPPED, "WS_OVERLAPPED" },
  { WS_POPUP, "WS_POPUP" },
  { WS_CHILD, "WS_CHILD" },
  { WS_MINIMIZE, "WS_MINIMIZE" },
  { WS_VISIBLE, "WS_VISIBLE" },
  { WS_DISABLED, "WS_DISABLED" },
  { WS_CLIPSIBLINGS, "WS_CLIPSIBLINGS" },
  { WS_CLIPCHILDREN, "WS_CLIPCHILDREN" },
  { WS_MAXIMIZE, "WS_MAXIMIZE" },
  { WS_BORDER, "WS_BORDER" },
  { WS_DLGFRAME, "WS_DLGFRAME" },
  { WS_VSCROLL, "WS_VSCROLL" },
  { WS_HSCROLL, "WS_HSCROLL" },
  { WS_SYSMENU, "WS_SYSMENU" },
  { WS_THICKFRAME, "WS_THICKFRAME" },
  { WS_GROUP, "WS_GROUP" },
  { WS_TABSTOP, "WS_TABSTOP" },
  { WS_MINIMIZEBOX, "WS_MINIMIZEBOX" },
  { WS_MAXIMIZEBOX, "WS_MAXIMIZEBOX" },
  { 0, 0 }
};


////////////////////////////////////////////////////////////////////////////////////////////////////
static SStyleSlot s_exStylesInfo[] =
{
  { WS_EX_DLGMODALFRAME, "WS_EX_DLGMODALFRAME" },
  { WS_EX_NOPARENTNOTIFY, "WS_EX_NOPARENTNOTIFY" },
  { WS_EX_TOPMOST, "WS_EX_TOPMOST" },
  { WS_EX_ACCEPTFILES, "WS_EX_ACCEPTFILES" },
  { WS_EX_TRANSPARENT, "WS_EX_TRANSPARENT" },
  { WS_EX_MDICHILD, "WS_EX_MDICHILD" },
  { WS_EX_TOOLWINDOW, "WS_EX_TOOLWINDOW" },
  { WS_EX_WINDOWEDGE, "WS_EX_WINDOWEDGE" },
  { WS_EX_CLIENTEDGE, "WS_EX_CLIENTEDGE" },
  { WS_EX_CONTEXTHELP, "WS_EX_CONTEXTHELP" },
  { WS_EX_RIGHT, "WS_EX_RIGHT" },
  { WS_EX_LEFT, "WS_EX_LEFT" },
  { WS_EX_RTLREADING, "WS_EX_RTLREADING" },
  { WS_EX_LTRREADING, "WS_EX_LTRREADING" },
  { WS_EX_LEFTSCROLLBAR, "WS_EX_LEFTSCROLLBAR" },
  { WS_EX_RIGHTSCROLLBAR, "WS_EX_RIGHTSCROLLBAR" },
  { WS_EX_CONTROLPARENT, "WS_EX_CONTROLPARENT" },
  { WS_EX_STATICEDGE, "WS_EX_STATICEDGE" },
  { WS_EX_APPWINDOW, "WS_EX_APPWINDOW" },
  { WS_EX_LAYERED, "WS_EX_LAYERED" },
  { WS_EX_NOINHERITLAYOUT, "WS_EX_NOINHERITLAYOUT" },
  { WS_EX_LAYOUTRTL, "WS_EX_LAYOUTRTL" },
  { WS_EX_COMPOSITED, "WS_EX_COMPOSITED" },
  { WS_EX_NOACTIVATE, "WS_EX_NOACTIVATE" },
  { 0, 0 }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NMainFrame::DumpWindowStyle( DWORD dwStyle )
{
  for( SStyleSlot * s = s_stylesInfo; s->name; ++s )
    if ( ( dwStyle & s->style ) == s->style )
      DebugTrace( "  %s", s->name );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NMainFrame::DumpExWindowStyle( DWORD dwStyle )
{
  for( SStyleSlot * s = s_exStylesInfo; s->name; ++s )
    if ( ( dwStyle & s->style ) == s->style )
      DebugTrace( "  %s", s->name );
}


void NMainFrame::SetCloseHandler( ICloseApplicationHandler* handler )
{
  // handler may be nullptr
  closeHandler = handler;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CommandQuit( const char *name, const vector<wstring> &params )
{
	NMainFrame::Exit( "" );
	return true;
}

NI_DEFINE_REFCOUNT( NMainFrame::ICloseApplicationHandler );

////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_VAR( "minimize_on_deactivate", s_bMinimizeOnDeactivate, STORAGE_NONE );
REGISTER_VAR( "app_always_active", bAppAlwaysActive, STORAGE_USER );
REGISTER_VAR( "window_pos_x", g_windowCenterPos.x, STORAGE_USER );
REGISTER_VAR( "window_pos_y", g_windowCenterPos.y, STORAGE_USER );

////////////////////////////////////////////////////////////////////////////////////////////////////
//START_REGISTER(WinFrame)
//REGISTER_VAR_EX( "minimize_on_deactivate", NGlobal::VarBoolHandler, &s_bMinimizeOnDeactivate, true, STORAGE_NONE );
//REGISTER_VAR_EX( "app_always_active", NGlobal::VarBoolHandler, &bAppAlwaysActive, false, STORAGE_USER );
REGISTER_CMD( update_cursor_rect, NMainFrame::UpdateCursorRectInt )

REGISTER_CMD( quit, CommandQuit )
REGISTER_CMD( exit, CommandQuit )
//FINISH_REGISTER

#ifdef _DEBUG_TERMINATE // defined in NewHandler.h

static bool DebugTerminate_( const char *name, const nstl::vector<nstl::wstring> &params )
{
  ni_detail::DebugTerminate();
  return true;
}
REGISTER_CMD(debug_terminate, DebugTerminate_);
#endif // _DEBUG_TERMINATE

static bool ToggleCursorClip(const char *name, const nstl::vector<nstl::wstring> &params)
{
  s_clipCursorInWindowedMode = !s_clipCursorInWindowedMode;
  NMainFrame::SetActualClipCursorRect();
  return true;
}

REGISTER_CMD( toggle_cursor_clip, ToggleCursorClip );

