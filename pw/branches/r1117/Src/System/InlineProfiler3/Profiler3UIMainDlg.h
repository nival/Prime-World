#ifndef INLINEPROFILER3UIMAINDLG_H_INCLUDED
#define INLINEPROFILER3UIMAINDLG_H_INCLUDED

#include "Profiler3UIWTL.h"
#include "Profiler3UIResource.h"

#include "InlineProfiler3Control.h"
#include "Profiler3UITimeline.h"
#include "Profiler3UIData.h"
#include "Profiler3UISettings.h"


namespace profiler3ui
{

class CMainDlg : public CDialogImpl<CMainDlg>, public CDialogResize<CMainDlg>, public CMessageFilter, ITimelineSelection
{
public:
  enum { IDD = IDD_MAIN_DLG };

  CMainDlg( CAppModule & module );

  ~CMainDlg();

  virtual BOOL PreTranslateMessage(MSG* pMsg)
  {
    return ::IsDialogMessage(m_hWnd, pMsg);
  }

  BEGIN_DLGRESIZE_MAP( CMainDlg )    
    DLGRESIZE_CONTROL( IDC_PROFILING_RESULTS_FRAME, DLSZ_SIZE_X | DLSZ_SIZE_Y )
    DLGRESIZE_CONTROL( IDC_CALLGRAPH,       DLSZ_SIZE_X | DLSZ_SIZE_Y )
    DLGRESIZE_CONTROL( IDC_FUNCTIONS,       DLSZ_SIZE_X | DLSZ_SIZE_Y )

    DLGRESIZE_CONTROL( IDC_THREADS_STATIC,  DLSZ_MOVE_X )
    DLGRESIZE_CONTROL( IDC_THREADS,         DLSZ_MOVE_X | DLSZ_SIZE_Y )

    DLGRESIZE_CONTROL( IDC_CONTROL_STATIC,  DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_DEAD_THREADS,    DLSZ_MOVE_X | DLSZ_MOVE_Y)
    DLGRESIZE_CONTROL( IDC_PAUSE,           DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_COPY_CALLGRAPH,  DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_DISABLE,         DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_SETTINGS,        DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_LITE_MODE,       DLSZ_MOVE_X | DLSZ_MOVE_Y )

    DLGRESIZE_CONTROL( IDC_TIMELINE_STATIC, DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_VMEM_STATIC,     DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_VMEM,            DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_MHZ_STATIC,      DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_MHZ,             DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_TIME_STATIC,     DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_TIME,            DLSZ_MOVE_X | DLSZ_MOVE_Y )

    DLGRESIZE_CONTROL( IDC_TIMELINE,        DLSZ_SIZE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_TIMELINE_SCROLL, DLSZ_SIZE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_INFO,            DLSZ_SIZE_X | DLSZ_MOVE_Y )

    DLGRESIZE_CONTROL( IDC_ZOOMIN,          DLSZ_MOVE_X | DLSZ_MOVE_Y )
    DLGRESIZE_CONTROL( IDC_ZOOMOUT,         DLSZ_MOVE_X | DLSZ_MOVE_Y )
  END_DLGRESIZE_MAP()

  BEGIN_MSG_MAP( CMainDlg )
    MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )

    COMMAND_ID_HANDLER( IDOK, OnOK )
    COMMAND_ID_HANDLER( IDCANCEL, OnCancel )
    COMMAND_ID_HANDLER( IDC_DEAD_THREADS, OnDeadThreads )
    COMMAND_ID_HANDLER( IDC_PAUSE, OnPause )
    COMMAND_ID_HANDLER( IDC_DISABLE, OnDisableAll )
    COMMAND_ID_HANDLER( IDC_LITE_MODE, OnLiteMode )
    COMMAND_ID_HANDLER( IDC_ZOOMIN, OnZoomIn )
    COMMAND_ID_HANDLER( IDC_ZOOMOUT, OnZoomOut )
    COMMAND_ID_HANDLER( IDC_RADIO_CALLGRAPH, OnResultViewButton )
    COMMAND_ID_HANDLER( IDC_RADIO_FUNCTIONS, OnResultViewButton )
    COMMAND_ID_HANDLER( IDC_COPY_CALLGRAPH, OnCopyCallgraphButton )
    COMMAND_ID_HANDLER( IDC_SETTINGS, OnSettingsButton )
    COMMAND_RANGE_HANDLER( ID_MENU_FIRST_WORST_EVENT, ID_MENU_LAST_WORST_EVENT, OnCtxMenuWorstEvent );
    MESSAGE_HANDLER( WM_TIMER, OnTimer )
    MESSAGE_HANDLER( WM_SYSCOMMAND, OnSysCommand )
    MESSAGE_HANDLER( WM_HSCROLL, OnHScroll )
    MESSAGE_HANDLER( WM_MOUSEWHEEL, OnMouseWheel )
    NOTIFY_HANDLER( IDC_THREADS, LVN_ITEMCHANGED, OnLVItemChanged )
    NOTIFY_HANDLER( IDC_CALLGRAPH, TVN_SELCHANGED, OnTvnSelChanged )
    NOTIFY_HANDLER( IDC_FUNCTIONS, LVN_ITEMCHANGED, OnLvnFunctionsSelChanged )
    NOTIFY_HANDLER( IDC_FUNCTIONS, LVN_COLUMNCLICK, OnLvnColumnClick )

    //REFLECT_NOTIFICATIONS()
    CHAIN_MSG_MAP( CDialogResize<CMainDlg> )
  END_MSG_MAP()

  LRESULT OnInitDialog( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled );

  LRESULT OnDeadThreads( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    profiler3::GetControl()->CleanupDeadThreads();
    m_buttDeadThreads.EnableWindow( FALSE );
    return 0;
  }

  LRESULT OnPause( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    profiler3::GetControl()->Pause( !profiler3::GetControl()->IsPaused() );
    UpdateButtons();
    return 0;
  }


  LRESULT OnDisableAll( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    m_data->EnableSampling( 0, false );
    UpdateButtons();
    return 0;
  }


  LRESULT OnLiteMode( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    UINT check = IsDlgButtonChecked( IDC_LITE_MODE );
    if ( check == BST_CHECKED )
      profiler3::GetControl()->EnableLiteMode( true );
    else if ( check == BST_UNCHECKED )
      profiler3::GetControl()->EnableLiteMode( false );
    return 0;
  }


  LRESULT OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
  {
    return 0;
  }


  LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
  {
    CloseDialog(wID);
    return 0;
  }


  LRESULT OnZoomIn( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    m_timeline.Zoom( 0.5f );
    m_timeline.SetupScrollBar( m_timelineScroll, SCROLL_DEGREES );
    return 0;
  }


  LRESULT OnZoomOut( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    m_timeline.Zoom( 2.0f );
    m_timeline.SetupScrollBar( m_timelineScroll, SCROLL_DEGREES );
    return 0;
  }


  LRESULT OnResultViewButton( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    UpdateResultViewType( wID );
    return 0;
  }


  LRESULT OnCopyCallgraphButton( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    DumpCallgraphToClipboard();
    return 0;
  }


  LRESULT OnSettingsButton( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled );


  LRESULT OnCtxMenuWorstEvent( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    profiler3::TThreadId threadId = m_timeline.SelectedThread();
    if ( !threadId )
      return 0;

    const profiler3::SWorstEventsSet * worstEvents = m_data->GetWorstEventsSet( threadId );
    NI_VERIFY( worstEvents, "Unknonwn thread", return 0 );

    unsigned eventIndex = wID - ID_MENU_FIRST_WORST_EVENT;
    //FIXME: If profiler is not paused, then worst events likely
    //will be changed while popup menu is on screen
    NI_VERIFY( eventIndex < (size_t)worstEvents->events.size(), "Wrong worst event menu item", return 0 );
    const profiler3::SSingleWorstEvent & worstEvent = worstEvents->events[eventIndex];
    DisplayCallGraph( worstEvent.samplingData );
    return 0;
  }

  LRESULT OnTimer( UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
  {
    m_data->Update();

    m_timeline.InvalidateRect( NULL, FALSE );

    UpdateThreadsList();

    m_MHz.SetWindowText( NI_STRFMT( "%.1f", m_timeline.LastDrawnTimeFactor() * 1e-6 ) );
    m_timeDisplay.SetWindowText( NI_STRFMT( "%.2f", m_timeline.LastDrawnProfilerTime() ) );

    m_memUsage.SetWindowText( NI_STRFMT( "%u", m_data->GetProcessMemoryUsage() / ( 1024u * 1024u ) ) );

    return 0;
  }


  LRESULT OnSysCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
  {
    UINT uCmdType = (UINT)wParam;

    if ( ( uCmdType & 0xFFF0 ) == IDM_ABOUTBOX )
    {
      //CAboutDlg dlg;
      //dlg.DoModal();
    }
    else
      bHandled = FALSE;

    return 0;
  }


  LRESULT OnHScroll( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled );
  LRESULT OnMouseWheel( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled );
  LRESULT OnLVItemChanged( int, LPNMHDR pnmh, BOOL & bHandled );
  LRESULT OnTvnSelChanged( int idCtrl, LPNMHDR pnmh, BOOL & bHandled );
  LRESULT OnLvnFunctionsSelChanged( int idCtrl, LPNMHDR pnmh, BOOL & bHandled );
  LRESULT OnLvnColumnClick( int idCtrl, LPNMHDR pnmh, BOOL & bHandled );

  //ITimelineSelection
  virtual void OnTimelineHilite( profiler3::TThreadId threadId, int eventId );
  virtual void OnTimelineLeftClick( profiler3::TThreadId threadId, int eventId, const CPoint & coords, bool changed );
  virtual void OnTimelineRightClick( profiler3::TThreadId threadId, int eventId, const CPoint & coords, bool changed );

private:
  enum
  {
    THREAD_LIST_COLUMN_SAMPLING = 0,
    THREAD_LIST_COLUMN_TID = 1,
    THREAD_LIST_COLUMN_NAME = 2,
    THREAD_LIST_COLUMN_CPU = 3,

    FUNCTIONS_COLUMN_NAME = 0,
    FUNCTIONS_COLUMN_CALLS,
    FUNCTIONS_COLUMN_TOTAL,
    FUNCTIONS_COLUMN_TOTAL_OWN,
    FUNCTIONS_COLUMN_MEMORY_DELTA,
    FUNCTIONS_COLUMN_ALLOCS_DELTA,
    FUNCTIONS_COLUMN_TOTAL_ALLOCS,

    IMAGELIST_TIMINGS = 1,
    IMAGELIST_MEMORY = 2
  };

  enum { SCROLL_DEGREES = 30000 };

  CAppModule & m_module;

  CProfilerTimeline   m_timeline;
  CListViewCtrl       m_threads;
  CButton             m_buttDeadThreads;
  CTreeViewCtrl       m_callgraph;
  CListViewCtrl       m_functions;
  CImageList          m_images;
  CStatic             m_status, m_MHz, m_timeDisplay, m_memUsage;
  CScrollBar          m_timelineScroll;

  CButton             m_buttPause;
  CButton             m_buttDisableAll;

  Strong<SamplingData>  m_data;

  int                 m_functionsSortColumn;
  bool                m_functionsInverseSort;

  SUISettingsData     m_uiSettings;

  Strong<profiler3::CallGraphNode> m_callgraphRootNode;
  profiler3::TTotalEventInfos m_currentSamplingTotals;

  typedef map<int, Strong<profiler3::CallGraphNode>> TCallgraphDict;
  TCallgraphDict      m_callgraphDict;

  void SetupThreadsList();
  void SetupTimeline();
  void UpdateTimeline();
  void SetupCallGraphView();
  void SetRefresh();
  void SetTimelineEventsLimit();
  void UpdateThreadsList();
  void UpdateButtons();
  void CloseDialog(int nVal);
  void UpdateResultViewType( int radioButtId );
  void DisplayCallGraph( const vector<ni_detail::Byte> & data );
  void FillCallgraphView( HTREEITEM parentItem, profiler3::CallGraphNode * node );
  void FillFunctionsView();
  void SortFunctinosList( int column, bool reset = false );
  static int CALLBACK FunctinosSortCallback( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );
  int CompareTwoEvents( profiler3::TEventId eventId1, profiler3::TEventId eventId2 );
  void PutEventInfoInStatus( profiler3::TEventId eventId, profiler3::CallGraphNode * node );
  void DumpCallgraphToClipboard();
  bool CopyStringToClipboard( const string & text );
};

} //namespace profiler3ui

#endif //INLINEPROFILER3UIMAINDLG_H_INCLUDED
