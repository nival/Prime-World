#ifndef _MAIN_FRAME_H_
#define _MAIN_FRAME_H_

#ifdef WIN32
  #pragma warning( push )
  #pragma warning( disable: 4201 ) // warning C4201: nonstandard extension used : nameless struct/union
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "HPTimer.h"
//
namespace NMainFrame
{

_interface ICloseApplicationHandler : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1(ICloseApplicationHandler, IBaseInterfaceST);

  virtual bool OnCloseApplication() = 0;
};

struct SWindowsMsg
{
  enum EMsg
  {
    MOUSE_WHEEL,
    MOUSE_MOVE,
    MOUSE_OUT,
    MOUSE_DISABLED,
    MOUSE_RB_DOWN,
    MOUSE_LB_DOWN,
    MOUSE_RB_UP,
    MOUSE_LB_UP,
    MOUSE_RB_DBLCLK,
    MOUSE_LB_DBLCLK,
    KEY_DOWN,
    KEY_UP,
    KEY_CHAR,
    TIME,
    CLOSE
  };
  NHPTimer::STime time;
  EMsg msg;
  union
  {
    struct { int x, y; };				 // mouse
    struct { int nKey, nRep; };	 // key
  };
  unsigned long dwFlags;
};
// WinFrame _interface
bool GetMessage( SWindowsMsg *pRes );
bool IsAppActive();
bool IsAppNotMinimized();
bool IsExit();

void Exit();
void Exit( const nstl::string& exitCode );
void SetExitCode( const nstl::string& exitCode );
const nstl::string& GetExitCode();

HWND GetWnd();
void  SetWnd(HWND _hwnd);
HINSTANCE GetInstance();
void PumpMessages();
bool InitApplication( HINSTANCE hInstance, const char *pszAppName, const char *pszWndName, LPCWSTR nIcon, bool fullscreen, int width, int height, HWND hUseWindow );
void ShutdownApplication();

void SetCursor( HCURSOR _hCursor );
void ShowCursor( bool bShow );
HCURSOR GetCurrentCursor();
void EnableCursorManagement( bool bEnable );
bool UpdateCursorRectInt( const char* name, const vector<wstring> &paramsSet );
void ResizeWindow( unsigned long width, unsigned long height, bool isFullScreen );

void DumpWindowStyle( DWORD dwStyle );
void DumpExWindowStyle( DWORD dwStyle );

void ApplyNewParams( unsigned long width, unsigned long height, bool isFullScreen );
void SetActualClipCursorRect();

void SetCloseHandler( ICloseApplicationHandler* handler );

} //namespace NMainFrame

void SetStepCallback( void (*_stepFunc)() );

#ifdef WIN32
#pragma warning( pop )
#endif  

#endif
