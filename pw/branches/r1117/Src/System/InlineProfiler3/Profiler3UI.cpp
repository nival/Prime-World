#include "stdafx.h"
#include "Profiler3UI.h"
#include "System/JobThread.h"
#include "System/MainFrame.h"

#include "Profiler3UIMainDlg.h"

namespace profiler3ui
{


CAppModule s_WtlApp;


void Init()
{
  NI_VERIFY( profiler3::GetControl()->Initialized(), "Profiler sampler was not initialized!", return );

#if (_WIN32_IE >= 0x0300)
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_BAR_CLASSES;	// change to support other controls
	::InitCommonControlsEx(&iccx);
#else
	::InitCommonControls();
#endif


  s_WtlApp.Init( NULL, GetModuleHandle( NULL ) );

  // force message queue to be created
  //MSG msg;
  //::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
}



void Shutdown()
{
  NI_ASSERT( profiler3::GetControl()->Initialized(), "Profiler sampler was not initialized!" );

  s_WtlApp.Term();
}




class UiThread : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( UiThread, threading::IThreadJob, BaseObjectMT )

public:
  UiThread( HWND _hParentWnd = 0 ) :
  hParentWnd( _hParentWnd )
  {
  }

  virtual void Work( volatile bool & isRunning )
  {
    CMessageLoop theLoop;
    s_WtlApp.AddMessageLoop( &theLoop );

    CMainDlg dlgMain( s_WtlApp );

    if( !dlgMain.Create( hParentWnd ) )
    {
      NI_ALWAYS_ASSERT( "Main dialog creation failed!" );
      return;
    }

    dlgMain.ShowWindow( WS_VISIBLE );

    theLoop.Run();

    s_WtlApp.RemoveMessageLoop();
  }

private:
  HWND hParentWnd;
};


static StrongMT<threading::JobThread> s_uiThread;


bool Show( HWND hParentWnd )
{
  if ( s_uiThread )
    if ( !s_uiThread->Wait( 0 ) )
      return false;

  s_uiThread = 0;

  s_uiThread = new threading::JobThread( new UiThread( hParentWnd ), "ProfilerUIThread", 10000 );

  return true;
}



bool Hide()
{
  if ( !s_uiThread )
    return false;

  s_uiThread = 0;

  return true;
}


bool s_ShowUI( char const* name, vector<wstring> const& params )
{
  if ( ( params.size() != 0 ) )
  {
    MessageTrace( "Usage: profiler_show_ui <show>|<hide>" );
    return true;
  }

  //HWND hParent = NMainFrame::IsFullscreen() ? NMainFrame::GetWnd() : NULL;
  //HWND hParent = NMainFrame::GetWnd();
  Show( 0 );
	return true;
}

REGISTER_DEV_CMD( profiler_show_ui, s_ShowUI );

} //namespace profiler3ui
