#include "stdafx.h"

#include "Profiler3UIMainDlg.h"
#include "System/RegistryStorage.h"
#include "System/ThreadNames.h"

namespace profiler3ui
{

class ProfilerUIRegistry : public registry::Storage {
  NI_DECLARE_REFCOUNT_CLASS_1( ProfilerUIRegistry, registry::Storage );
public:
  ProfilerUIRegistry() :
  registry::Storage( "Nanoprofiler\\UI" )
  {
    NI_REGISTER_ENUM_VALUE( SUISettingsData::eRefresh2 );
    NI_REGISTER_ENUM_VALUE( SUISettingsData::eRefresh5 );
    NI_REGISTER_ENUM_VALUE( SUISettingsData::eRefresh10 );
    NI_REGISTER_ENUM_VALUE( SUISettingsData::eRefresh15 );
    NI_REGISTER_ENUM_VALUE( SUISettingsData::eRefresh25 );

    NI_REGISTER_ENUM_VALUE( SUISettingsData::eDrawMax1000 );
    NI_REGISTER_ENUM_VALUE( SUISettingsData::eDrawMax2000 );
    NI_REGISTER_ENUM_VALUE( SUISettingsData::eDrawMax3000 );
    NI_REGISTER_ENUM_VALUE( SUISettingsData::eDrawMax5000 );
    NI_REGISTER_ENUM_VALUE( SUISettingsData::eDrawMaxUnlim );
  }
};




CMainDlg::CMainDlg( CAppModule & module ) :
m_module( module ),
m_timeline( this ),
m_functionsSortColumn( FUNCTIONS_COLUMN_TOTAL ),
m_functionsInverseSort( true )
{
  m_data = new SamplingData;

  profiler3::SSettings sett;
  profiler3::GetControl()->GetSettings( sett );
  Strong<registry::Storage> reg = new registry::Storage( "Nanoprofiler" );
  sett.timelineLength         = 1e-3 * reg->ReadDword( "Timeline Length", (DWORD)( 1e3 * sett.timelineLength ) );
  sett.dataFlushPeriod        = 1e-3 * reg->ReadDword( "Data Flush Period", (DWORD)( 1e3 * sett.dataFlushPeriod ) );
  sett.initialSamplingBuffer  = reg->ReadDword( "Initial Sampling Buffer", sett.initialSamplingBuffer );
  sett.samplingBufferLimit    = reg->ReadDword( "Sampling Buffer Limit", sett.samplingBufferLimit );
  sett.initialRootEvents      = reg->ReadDword( "Initial Root Events", sett.initialRootEvents );
  sett.rootEventsLimit        = reg->ReadDword( "Root Events Limit", sett.rootEventsLimit );
  sett.maxWorstRootEvents     = reg->ReadDword( "Max Worst Root Events", sett.maxWorstRootEvents );
  profiler3::GetControl()->Setup( sett );
  profiler3::GetControl()->EnableLiteMode( reg->ReadDword( "Lite Mode", 1 ) ? true : false );

  Strong<ProfilerUIRegistry> uiReg = new ProfilerUIRegistry;
  m_uiSettings.sortCallgraphByTime = uiReg->ReadDword( "Sort Callgraph By Time", m_uiSettings.sortCallgraphByTime ? 1 : 0 ) ? true : false;
  m_uiSettings.refreshInterval = uiReg->ReadEnum( "Refresh Interval", m_uiSettings.refreshInterval );
  m_uiSettings.drawMax = uiReg->ReadEnum( "Draw Max", m_uiSettings.drawMax );
}



CMainDlg::~CMainDlg()
{
  m_images.Destroy();
}



LRESULT CMainDlg::OnInitDialog( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled )
{
  // center the dialog on the screen
  CenterWindow();

  DlgResize_Init();

  TCHAR szTitle[1024] = _T( "" ), szModule[768] = _T( "" );
  GetWindowText( szTitle, 192 );
  GetModuleFileName( NULL, szModule, 768 );
  StrCat( szTitle, _T( ": " ) );
  StrCat( szTitle, szModule );
  SetWindowText( szTitle );

  // set icons
  HICON hIcon = (HICON)::LoadImage( m_module.GetResourceInstance(), MAKEINTRESOURCE( IDI_PROFILER ), 
    IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
  SetIcon(hIcon, TRUE);

  HICON hIconSmall = (HICON)::LoadImage( m_module.GetResourceInstance(), MAKEINTRESOURCE( IDI_PROFILER ), 
    IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
  SetIcon(hIconSmall, FALSE);

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  _ASSERTE((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  _ASSERTE(IDM_ABOUTBOX < 0xF000);

  CMenu SysMenu = GetSystemMenu(FALSE);
  if(::IsMenu(SysMenu))
  {
    TCHAR szAboutMenu[256];
    if( ::LoadString( m_module.GetResourceInstance(), IDS_ABOUTBOX, szAboutMenu, 255 ) > 0 )
    {
      SysMenu.AppendMenu( MF_SEPARATOR );
      SysMenu.AppendMenu( MF_STRING, IDM_ABOUTBOX, szAboutMenu );
    }
  }
  SysMenu.Detach();

  // register object for message filtering
  CMessageLoop* pLoop = m_module.GetMessageLoop();
  pLoop->AddMessageFilter(this);

  m_images.Create( IDB_IMAGES, 20, 0, RGB( 0, 255, 255 ) );

  SetupThreadsList();
  SetupTimeline();
  UpdateTimeline();
  SetTimelineEventsLimit();
  SetupCallGraphView();

  m_status.Attach( GetDlgItem( IDC_INFO ) );
  m_MHz.Attach( GetDlgItem( IDC_MHZ ) );
  m_timeDisplay.Attach( GetDlgItem( IDC_TIME ) );
  m_memUsage.Attach( GetDlgItem( IDC_VMEM ) );

  m_buttPause.Attach( GetDlgItem( IDC_PAUSE ) );
  m_buttDisableAll.Attach( GetDlgItem( IDC_DISABLE ) );
  UpdateButtons();

  SetRefresh();
  return TRUE;
}



void CMainDlg::SetupThreadsList()
{
  m_threads.Attach( GetDlgItem( IDC_THREADS ) );
  m_threads.SetExtendedListViewStyle( LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT );
  m_threads.SetExtendedListViewStyle( LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES );
  // fill in the headers

  m_threads.AddColumn( _T("On"),          THREAD_LIST_COLUMN_SAMPLING );
  m_threads.AddColumn( _T("Thread Id"),   THREAD_LIST_COLUMN_TID );
  m_threads.AddColumn( _T("Thread Name"), THREAD_LIST_COLUMN_NAME );
  m_threads.AddColumn( _T("CPU"),         THREAD_LIST_COLUMN_CPU );

  m_threads.SetColumnWidth( THREAD_LIST_COLUMN_SAMPLING,  LVSCW_AUTOSIZE_USEHEADER );
  m_threads.SetColumnWidth( THREAD_LIST_COLUMN_TID,       LVSCW_AUTOSIZE_USEHEADER );
  m_threads.SetColumnWidth( THREAD_LIST_COLUMN_NAME,      LVSCW_AUTOSIZE_USEHEADER );
  m_threads.SetColumnWidth( THREAD_LIST_COLUMN_CPU,       LVSCW_AUTOSIZE_USEHEADER );

  m_buttDeadThreads.Attach( GetDlgItem( IDC_DEAD_THREADS ) );
}



void CMainDlg::SetupTimeline()
{
  m_timeline.SetData( m_data );
  m_timeline.SubclassWindow( GetDlgItem( IDC_TIMELINE ) );

  m_timelineScroll.Attach( GetDlgItem( IDC_TIMELINE_SCROLL ) );
  m_timelineScroll.SetScrollRange( 0, SCROLL_DEGREES );
}



void CMainDlg::UpdateTimeline()
{
  m_timeline.SetRange( -profiler3::GetControl()->TimelineLength(), 0, 0.01 );
  m_timeline.SetupScrollBar( m_timelineScroll, SCROLL_DEGREES );
}



void CMainDlg::SetupCallGraphView()
{
  m_callgraph.Attach( GetDlgItem( IDC_CALLGRAPH ) );
  m_callgraph.SetExtendedStyle( TVS_EX_DOUBLEBUFFER, TVS_EX_DOUBLEBUFFER );
  m_callgraph.SetImageList( m_images, TVSIL_STATE );

  m_functions.Attach( GetDlgItem( IDC_FUNCTIONS ) );
  m_functions.SetExtendedListViewStyle( LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT );
  m_functions.SetImageList( m_images, LVSIL_STATE );
  m_functions.AddColumn( _T("Location"),            FUNCTIONS_COLUMN_NAME );
  m_functions.AddColumn( _T(" Calls "),             FUNCTIONS_COLUMN_CALLS );
  m_functions.AddColumn( _T("Total time, ms"),      FUNCTIONS_COLUMN_TOTAL );
  m_functions.AddColumn( _T("Total own time, ms"),  FUNCTIONS_COLUMN_TOTAL_OWN );
  m_functions.AddColumn( _T("Memory delta"),        FUNCTIONS_COLUMN_MEMORY_DELTA );
  m_functions.AddColumn( _T("Allocs delta"),        FUNCTIONS_COLUMN_ALLOCS_DELTA );
  m_functions.AddColumn( _T("Allocs number"),       FUNCTIONS_COLUMN_TOTAL_ALLOCS );

  CRect listRect;
  m_functions.GetWindowRect( listRect );
  m_functions.SetColumnWidth( FUNCTIONS_COLUMN_NAME,          listRect.Width() / 3 );
  m_functions.SetColumnWidth( FUNCTIONS_COLUMN_CALLS,         LVSCW_AUTOSIZE_USEHEADER );
  m_functions.SetColumnWidth( FUNCTIONS_COLUMN_TOTAL,         LVSCW_AUTOSIZE_USEHEADER );
  m_functions.SetColumnWidth( FUNCTIONS_COLUMN_TOTAL_OWN,     LVSCW_AUTOSIZE_USEHEADER );
  m_functions.SetColumnWidth( FUNCTIONS_COLUMN_MEMORY_DELTA,  LVSCW_AUTOSIZE_USEHEADER );
  m_functions.SetColumnWidth( FUNCTIONS_COLUMN_ALLOCS_DELTA,  LVSCW_AUTOSIZE_USEHEADER );
  m_functions.SetColumnWidth( FUNCTIONS_COLUMN_TOTAL_ALLOCS,  LVSCW_AUTOSIZE_USEHEADER );

  CheckDlgButton( IDC_RADIO_CALLGRAPH, BST_CHECKED );

  UpdateResultViewType( IDC_RADIO_CALLGRAPH );
}



void CMainDlg::SetRefresh()
{
  const int ID = 1;

  KillTimer( ID );

  int period = 100;
  switch( m_uiSettings.refreshInterval )
  {
    case SUISettingsData::eRefresh2:    period = 500;   break;
    case SUISettingsData::eRefresh5:    period = 200;   break;
    case SUISettingsData::eRefresh10:   period = 100;   break;
    case SUISettingsData::eRefresh15:   period = 66;    break;
    case SUISettingsData::eRefresh25:   period = 40;    break;
  }

  SetTimer( ID, period );
}



void CMainDlg::SetTimelineEventsLimit()
{
  unsigned number = 1000;
  switch( m_uiSettings.drawMax )
  {
    case SUISettingsData::eDrawMax1000:   number = 1000;   break;
    case SUISettingsData::eDrawMax2000:   number = 2000;   break;
    case SUISettingsData::eDrawMax3000:   number = 3000;   break;
    case SUISettingsData::eDrawMax5000:   number = 5000;   break;
    case SUISettingsData::eDrawMaxUnlim:  number = 0;   break;
  }
  m_timeline.SetMaxEventsToDraw( number );
}



void CMainDlg::UpdateThreadsList()
{
  vector<int> toRemove;
  for ( int item = m_threads.GetNextItem( -1, LVNI_ALL ); item != -1; item = m_threads.GetNextItem( item, LVNI_ALL ) )
  {
    profiler3::TThreadId threadId = (profiler3::TThreadId)m_threads.GetItemData( item );

    SamplingData::SThreadInformation info;
    if ( !m_data->GetThreadInfo( threadId, info ) )
    {
      toRemove.push_back( item );
      continue;
    }

    m_threads.SetCheckState( item, info.samplingEnabled );

    m_threads.AddItem( item, THREAD_LIST_COLUMN_TID, NI_STRFMT( info.alive ? "0x%04x" : "dead (0x%04x)", info.osThreadId ) );
    m_threads.AddItem( item, THREAD_LIST_COLUMN_CPU, NI_STRFMT( "%d(%d)", info.userTimePerc + info.kernelTimePerc, info.kernelTimePerc ) );
  }

  //remove absent threads
  for ( int i = 0; i < toRemove.size(); ++i )
    m_threads.DeleteItem( toRemove[i] );

  //And now add new threads
  vector<profiler3::TThreadId> newThreads;
  m_data->PopNewThreads( newThreads );
  for ( int i = 0; i < newThreads.size(); ++i )
  {
    const profiler3::TThreadId threadId = newThreads[i];

    SamplingData::SThreadInformation info;
    bool result = m_data->GetThreadInfo( threadId, info );
    NI_VERIFY( result, "", continue );

    int count = m_threads.GetItemCount();
    int actualItem = m_threads.InsertItem( count, "" );
    m_threads.AddItem( actualItem, THREAD_LIST_COLUMN_TID, NI_STRFMT( "0x%04x", info.osThreadId ) );
    m_threads.AddItem( actualItem, THREAD_LIST_COLUMN_NAME, threading::GetDebugThreadName( info.osThreadId ) );
    m_threads.AddItem( actualItem, THREAD_LIST_COLUMN_CPU, "" );
    m_threads.SetItemData( actualItem, threadId );
  }

  m_buttDeadThreads.EnableWindow( m_data->GetDeadThreadsCount() > 0 );
}



void CMainDlg::UpdateButtons()
{
  const bool paused = profiler3::GetControl()->IsPaused();

  TCHAR szPauseButtText[256] = _T( "" );
  if ( ::LoadString( m_module.GetResourceInstance(), paused ? IDS_RESUME_BUTTON : IDS_PAUSE_BUTTON, szPauseButtText, 255 ) > 0 )
    m_buttPause.SetWindowText( szPauseButtText );

  unsigned enabledThreads = m_data->GetEnabledThreadsCount();
  m_buttDisableAll.EnableWindow( enabledThreads > 0 );

  CheckDlgButton( IDC_LITE_MODE, profiler3::GetControl()->IsLiteModeEnabled() ? BST_CHECKED : BST_UNCHECKED );
}



void CMainDlg::CloseDialog(int nVal)
{
  {
    profiler3::SSettings sett;
    profiler3::GetControl()->GetSettings( sett );
    Strong<registry::Storage> reg = new registry::Storage( "Nanoprofiler" );
    reg->StoreDword( "Timeline Length", (DWORD)( sett.timelineLength * 1e3 ) );
    reg->StoreDword( "Data Flush Period", (DWORD)( sett.dataFlushPeriod * 1e3 ) );
    reg->StoreDword( "Initial Sampling Buffer", sett.initialSamplingBuffer );
    reg->StoreDword( "Sampling Buffer Limit", sett.samplingBufferLimit );
    reg->StoreDword( "Initial Root Events", sett.initialRootEvents );
    reg->StoreDword( "Root Events Limit", sett.rootEventsLimit );
    reg->StoreDword( "Max Worst Root Events", sett.maxWorstRootEvents );
    reg->StoreDword( "Lite Mode", profiler3::GetControl()->IsLiteModeEnabled() ? 1 : 0 );

    Strong<ProfilerUIRegistry> uiReg = new ProfilerUIRegistry;
    uiReg->StoreDword( "Sort Callgraph By Time", m_uiSettings.sortCallgraphByTime ? 1 : 0 );
    uiReg->StoreEnum( "Refresh Interval", m_uiSettings.refreshInterval );
    uiReg->StoreEnum( "Draw Max", m_uiSettings.drawMax );
  }

  DestroyWindow();
  ::PostQuitMessage(nVal);
}



LRESULT CMainDlg::OnSettingsButton( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
{
  profiler3::SSettings samplSett;
  profiler3::GetControl()->GetSettings( samplSett );

  CSettingsDialog settingsDlg( samplSett, m_uiSettings );
  if ( settingsDlg.DoModal( *this ) == IDOK )
  {
    profiler3::GetControl()->Setup( settingsDlg.SamplingSettings() );
    m_uiSettings = settingsDlg.UISettings();
    UpdateTimeline();
    SetRefresh();
    SetTimelineEventsLimit();
  }
  return 0;
}



LRESULT CMainDlg::OnHScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
  int scrollType = LOWORD( wParam );
  switch ( scrollType )
  {
  case SB_THUMBTRACK :
  case SB_THUMBPOSITION :
    {
      int pos = HIWORD( wParam );
      m_timeline.ScrollAbs( pos / (float)SCROLL_DEGREES );
      m_timelineScroll.SetScrollPos( pos );
      break;
    }

  case SB_LINELEFT:
  case SB_LINERIGHT:
  case SB_PAGELEFT:
  case SB_PAGERIGHT:
    {
      float amount = ( ( scrollType == SB_LINELEFT ) || ( scrollType == SB_LINERIGHT ) ) ? 0.1f : 1.0f;
      amount *= ( ( scrollType == SB_LINELEFT ) || ( scrollType == SB_PAGELEFT ) ) ? -1.0f : +1.0f;

      m_timeline.ScrollRelative( amount );
      m_timeline.SetupScrollBar( m_timelineScroll, SCROLL_DEGREES );
      break;
    }

  case SB_ENDSCROLL:
    break;
  }
  return 0;
}



LRESULT CMainDlg::OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled )
{
  int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
  //POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
  CPoint point( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
  ScreenToClient( &point );

  CRect rect;
  m_timeline.GetWindowRect( rect );
  ScreenToClient( rect );

  if ( !PtInRect( rect, point ) )
    return TRUE;

  m_timeline.Zoom( zDelta > 0 ? 0.5 : 2.0 );
  m_timeline.SetupScrollBar( m_timelineScroll, SCROLL_DEGREES );
  return 0;
}



LRESULT CMainDlg::OnLVItemChanged(int, LPNMHDR pnmh, BOOL&)
{
  const NMLISTVIEW * pnmv = (NMLISTVIEW *)pnmh;

  if ( pnmv->iItem < 0 )
    return 0;
  if ( !( pnmv->uChanged & LVIF_STATE ) )
    return 0;

  profiler3::TThreadId threadId = (profiler3::TThreadId)m_threads.GetItemData( pnmv->iItem );
  if ( !threadId )
    return 0;

  if ( pnmv->uNewState & LVIS_SELECTED )
    m_timeline.SelectThread( threadId );

  UINT state = ( pnmv->uNewState & TVIS_STATEIMAGEMASK );
  if ( state == INDEXTOSTATEIMAGEMASK( 2 ) )
    m_data->EnableSampling( threadId, true );
  else if ( state == INDEXTOSTATEIMAGEMASK( 1 ) )
    m_data->EnableSampling( threadId, false );
  else
    return 0;

  UpdateButtons();
  return 0;
}



LRESULT CMainDlg::OnTvnSelChanged( int idCtrl, LPNMHDR pnmh, BOOL & bHandled )
{
  NMTREEVIEW * tv = (NMTREEVIEW *)pnmh;
  NI_VERIFY( tv->itemNew.mask & TVIF_HANDLE, "", return 0 );
  HTREEITEM item = tv->itemNew.hItem;

  int cgDictId = (int)m_callgraph.GetItemData( item );
  TCallgraphDict::iterator dictIt = m_callgraphDict.find( cgDictId );
  NI_VERIFY( dictIt != m_callgraphDict.end(), "", return 0 );

  PutEventInfoInStatus( dictIt->second->Data().eventId, dictIt->second );
  return 0;
}



LRESULT CMainDlg::OnLvnFunctionsSelChanged( int idCtrl, LPNMHDR pnmh, BOOL & bHandled )
{
  const NMLISTVIEW * pnmv = (NMLISTVIEW *)pnmh;

  if ( ( pnmv->uChanged & LVIF_STATE ) && ( pnmv->uNewState & LVIS_SELECTED ) )
  {
    profiler3::TEventId eventId = (profiler3::TEventId)m_functions.GetItemData( pnmv->iItem );
    PutEventInfoInStatus( eventId, 0 );
  }
  return 0;
}



LRESULT CMainDlg::OnLvnColumnClick( int idCtrl, LPNMHDR pnmh, BOOL & bHandled )
{
  SortFunctinosList( ( ( NMLISTVIEW *)pnmh )->iSubItem );
  return 0;
}



void CMainDlg::OnTimelineHilite( profiler3::TThreadId threadId, int eventId )
{
  if ( !threadId || ( eventId <= 0 ) )
  {
    if ( m_timeline.SelectedThread() && ( m_timeline.SelectedEvent() > 0 ) )
    {
      threadId = m_timeline.SelectedThread();
      eventId = m_timeline.SelectedEvent();
    }
    else
    {
      m_status.SetWindowText( "" );
      return;
    }
  }

  profiler3::TOsThreadId osThreadId;
  const profiler3::SRootEventDesc * rootEventDesc = m_data->GetRootEvent( threadId, eventId, osThreadId );
  if ( !rootEventDesc )
    return;

  m_status.SetWindowText( NI_STRFMT( "Root event %d from thread 0x%04x: %.3f ms", eventId, osThreadId, rootEventDesc->duration * 1e3 ) );
}



void CMainDlg::OnTimelineLeftClick( profiler3::TThreadId threadId, int eventId, const CPoint & coords, bool changed )
{
  if ( !changed )
    return;

  for ( int item = m_threads.GetNextItem( -1, LVNI_ALL ); item != -1; item = m_threads.GetNextItem( item, LVNI_ALL ) )
  {
    profiler3::TThreadId tid = (profiler3::TThreadId)m_threads.GetItemData( item );
    if ( tid == threadId )
    {
      m_threads.SelectItem( item );
      break;
    }
  }

  if ( eventId >= 0 )
  {
    vector<ni_detail::Byte> buffer;
    profiler3::GetControl()->GetRootEventBytes( threadId, eventId, buffer );
    DisplayCallGraph( buffer );
  }
}



void CMainDlg::OnTimelineRightClick( profiler3::TThreadId threadId, int eventId, const CPoint & coords, bool changed )
{
  if ( !threadId )
    return;

  CMenu menu;
  if ( !menu.LoadMenu( IDR_CONTEXTMENU ) )
    return;

  bool paused = profiler3::GetControl()->IsPaused();

  const profiler3::SWorstEventsSet * worstEvents = m_data->GetWorstEventsSet( threadId );
  NI_VERIFY( worstEvents, "Unknonwn thread", return );

  for ( int i = 0; i < worstEvents->events.size(); ++i )
  {
    MENUITEMINFO item;
    ZeroMemory( &item, sizeof( item ) );
    item.cbSize = sizeof( item );
    item.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STRING | MIIM_STATE;
    item.fState = paused ? 0 : MFS_DISABLED;
    item.fType = MFT_STRING;
    item.wID = ID_MENU_FIRST_WORST_EVENT + i;
    item.dwTypeData = (LPSTR)NI_STRFMT( "Display worst event #%d, %.3f ms",
      worstEvents->events[i].id, worstEvents->events[i].duration * 1e3 );
    menu.InsertMenuItem( 0, FALSE, &item );
  }

  CMenuHandle menuPopup = menu.GetSubMenu( 0 );
  if ( menuPopup == NULL )
    return;

  CRect rect;
  m_timeline.GetWindowRect( &rect );
  menuPopup.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, rect.left + coords.x, rect.top + coords.y, *this );
}



void CMainDlg::UpdateResultViewType( int radioButtId )
{
  m_callgraph.ShowWindow( ( radioButtId == IDC_RADIO_CALLGRAPH ) ? SW_SHOW : SW_HIDE );
  m_functions.ShowWindow( ( radioButtId == IDC_RADIO_FUNCTIONS ) ? SW_SHOW : SW_HIDE );
}



void CMainDlg::DisplayCallGraph( const vector<ni_detail::Byte> & data )
{
  if ( data.empty() )
    return;

  m_currentSamplingTotals.clear();
  m_callgraphRootNode = 0;
  m_callgraphRootNode = profiler3::GetControl()->CollectCallGraph( &data[0], data.size(), m_currentSamplingTotals );

  m_callgraph.DeleteAllItems();
  m_callgraphDict.clear();

  FillCallgraphView( NULL, m_callgraphRootNode );

  FillFunctionsView();

  GetDlgItem( IDC_COPY_CALLGRAPH ).EnableWindow();
}



void CMainDlg::FillCallgraphView( HTREEITEM parentItem, profiler3::CallGraphNode * node )
{
  const profiler3::SEventInfo & event = profiler3::GetControl()->GetEventInfo( node->Data().eventId );
  
  const char * text = NI_STRFMT( "%s:  %.3f (%.3f own) ms  in  %u call(s)",
    event.name.c_str(),
    1e3 * node->Data().span, 1e3 * node->Data().meTime, node->Data().calls );

  int cgDictId = m_callgraphDict.size();
  m_callgraphDict[cgDictId] = node;

  HTREEITEM item = m_callgraph.InsertItem( text, parentItem, NULL );
  m_callgraph.SetItemData( item, (DWORD_PTR)cgDictId );

  int imageIndex = node->Data().hasAllocsInfo ? IMAGELIST_MEMORY : IMAGELIST_TIMINGS;
  m_callgraph.SetItemState( item, INDEXTOSTATEIMAGEMASK( imageIndex ), TVIS_STATEIMAGEMASK );

  if ( m_uiSettings.sortCallgraphByTime )
  {
    //let's sort nodes by duration
    vector<Strong<profiler3::CallGraphNode>>  nodes;
    nodes.reserve( node->Subnodes().size() );
    for ( profiler3::TCallGraphNodes::iterator it = node->Subnodes().begin(); it != node->Subnodes().end(); ++it )
      nodes.push_back( it->second );

    //bubbles are such bubbles!
    for ( int i = 0; i < nodes.size(); ++i )
      for ( int j = i + 1; j < nodes.size(); ++j )
        if ( nodes[i]->Data().span < nodes[j]->Data().span )
          swap( nodes[i], nodes[j] );

    for ( int i = 0; i < nodes.size(); ++i )
      FillCallgraphView( item, nodes[i] );
  }
  else
  {
    for ( profiler3::TCallGraphNodes::iterator it = node->Subnodes().begin(); it != node->Subnodes().end(); ++it )
     FillCallgraphView( item, it->second );
  }
}



static string MemorySizeToStr( int size )
{
  if ( abs( size ) <= 1024 )
    return NI_STRFMT( "%d bytes", size );
  if ( abs( size ) <= 1024 * 1024 )
    return NI_STRFMT( "%d kb", size / 1024 );
  return NI_STRFMT( "%d mb", size / ( 1024 * 1024 ) );
}



void CMainDlg::FillFunctionsView()
{
  m_functions.DeleteAllItems();

  for ( profiler3::TTotalEventInfos::const_iterator it = m_currentSamplingTotals.begin(); it != m_currentSamplingTotals.end(); ++it )
  {
    const profiler3::TEventId eventId = it->first;
    const profiler3::SEventInfo & event = profiler3::GetControl()->GetEventInfo( eventId );
    const profiler3::STotalEventInfo & info = it->second;
    
    int item = m_functions.InsertItem( m_functions.GetItemCount(), event.name.c_str() );
    m_functions.AddItem( item, FUNCTIONS_COLUMN_CALLS, NI_STRFMT( "%d", info.calls ) );
    m_functions.AddItem( item, FUNCTIONS_COLUMN_TOTAL, NI_STRFMT( "%.3f", info.time * 1e3 ) );
    m_functions.AddItem( item, FUNCTIONS_COLUMN_TOTAL_OWN, NI_STRFMT( "%.3f", info.ownTime * 1e3 ) );
    m_functions.AddItem( item, FUNCTIONS_COLUMN_MEMORY_DELTA, MemorySizeToStr( info.memoryDelta ).c_str() );
    m_functions.AddItem( item, FUNCTIONS_COLUMN_ALLOCS_DELTA, NI_STRFMT( "%d", info.allocsDelta ) );
    m_functions.AddItem( item, FUNCTIONS_COLUMN_TOTAL_ALLOCS, NI_STRFMT( "%u", info.allocs ) );
    m_functions.SetItemData( item, (DWORD_PTR)eventId );

    int imageIndex = info.hasAllocsInfo ? IMAGELIST_MEMORY : IMAGELIST_TIMINGS;
    m_functions.SetItemState( item, INDEXTOSTATEIMAGEMASK( 1 + imageIndex ), LVIS_STATEIMAGEMASK );
  }

  SortFunctinosList( FUNCTIONS_COLUMN_TOTAL, true );
}



void CMainDlg::SortFunctinosList( int column, bool reset )
{
  if ( ( m_functionsSortColumn != column ) || reset )
    m_functionsInverseSort = false;
  else
    m_functionsInverseSort = !m_functionsInverseSort;

  m_functionsSortColumn = column;

  m_functions.SortItems( FunctinosSortCallback, (LPARAM)this );

  m_functions.SetSelectedColumn( m_functionsSortColumn );
}



int CALLBACK CMainDlg::FunctinosSortCallback( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
  CMainDlg * This = (CMainDlg *)lParamSort;
  return This->CompareTwoEvents( (profiler3::TEventId)lParam1, (profiler3::TEventId)lParam2 );
}



int CMainDlg::CompareTwoEvents( profiler3::TEventId eventId1, profiler3::TEventId eventId2 )
{
  int result = 0;
  if ( m_functionsSortColumn == FUNCTIONS_COLUMN_NAME )
  {
    const profiler3::SEventInfo & event1 = profiler3::GetControl()->GetEventInfo( eventId1 );
    const profiler3::SEventInfo & event2 = profiler3::GetControl()->GetEventInfo( eventId2 );
    result = strcmp( event1.name.c_str(), event2.name.c_str() );
  }
  else
  {
    profiler3::TTotalEventInfos & totals = m_currentSamplingTotals;
    profiler3::TTotalEventInfos::iterator it1 = totals.find( eventId1 );
    profiler3::TTotalEventInfos::iterator it2 = totals.find( eventId2 );

    NI_VERIFY( ( it1 != totals.end() ) && ( it2 != totals.end() ), "sorting unknown events!", return 0 );
    switch ( m_functionsSortColumn )
    {
      default:
        break;

      case FUNCTIONS_COLUMN_CALLS:
        if ( it1->second.calls < it2->second.calls ) result = -1;
        if ( it1->second.calls > it2->second.calls ) result = +1;
        break;

      case FUNCTIONS_COLUMN_TOTAL:
        if ( it1->second.time < it2->second.time ) result = -1;
        if ( it1->second.time > it2->second.time ) result = +1;
        break;

      case FUNCTIONS_COLUMN_TOTAL_OWN:
        if ( it1->second.ownTime < it2->second.ownTime ) result = -1;
        if ( it1->second.ownTime > it2->second.ownTime ) result = +1;
        break;

      case FUNCTIONS_COLUMN_MEMORY_DELTA:
        if ( it1->second.memoryDelta < it2->second.memoryDelta ) result = -1;
        if ( it1->second.memoryDelta > it2->second.memoryDelta ) result = +1;
        break;

      case FUNCTIONS_COLUMN_ALLOCS_DELTA:
        if ( it1->second.allocsDelta < it2->second.allocsDelta ) result = -1;
        if ( it1->second.allocsDelta > it2->second.allocsDelta ) result = +1;
        break;

      case FUNCTIONS_COLUMN_TOTAL_ALLOCS:
        if ( it1->second.allocs < it2->second.allocs ) result = -1;
        if ( it1->second.allocs > it2->second.allocs ) result = +1;
        break;
    }
  }

  if ( m_functionsInverseSort )
      result = -result;

  return result;
}



void CMainDlg::PutEventInfoInStatus( profiler3::TEventId eventId, profiler3::CallGraphNode * node )
{
  if ( !eventId )
    return;

  profiler3::TTotalEventInfos::iterator it = m_currentSamplingTotals.find( eventId );
  NI_VERIFY( it != m_currentSamplingTotals.end(), "Unknown event", return );
  const profiler3::STotalEventInfo & totals = it->second;

  const profiler3::SEventInfo & info = profiler3::GetControl()->GetEventInfo( eventId );

  string text = NI_STRFMT( "Event '%s'\nSource: %s(%d)\n", info.name.c_str(), info.file.c_str(), info.line );

  if ( node && node->Data().hasAllocsInfo )
    text += NI_STRFMT( "Memory delta: %s (in %i allocs), allocs made: %u\n",
                          MemorySizeToStr( node->Data().memoryDelta ).c_str(), (int)node->Data().allocsDelta, node->Data().allocs );

  if ( totals.hasAllocsInfo )
    text += NI_STRFMT( "Total memory delta: %s (in %i allocs), total allocs made: %u\n",
                        MemorySizeToStr( totals.memoryDelta ).c_str(), (int)totals.allocsDelta, totals.allocs );

  text += NI_STRFMT(
    "%u total calls, %.3f ms total time, %.3f ms total own time\n",
    totals.calls, 1e3 * totals.time, 1e3 * totals.ownTime );

  m_status.SetWindowText( NI_STRFMT( text.c_str() ) );
}



void CMainDlg::DumpCallgraphToClipboard()
{
  if ( !m_callgraphRootNode || m_currentSamplingTotals.empty() )
    return;

  struct CGDumper : public profiler3::IDumpCallback 
  {
    string text;

    virtual void DumpLine( const char * str )
    {
      text += str;
      text += "\r\n";
      if ( IsDebuggerPresent() )
      {
        OutputDebugString( str );
        OutputDebugString( "\n" );
      }
    }
  } dumper;

  profiler3::GetControl()->DumpCallgraph( m_callgraphRootNode, m_currentSamplingTotals, &dumper, IsDebuggerPresent() );

  CopyStringToClipboard( dumper.text );
}



bool CMainDlg::CopyStringToClipboard( const string & text )
{
  BOOL result = FALSE;

  result = OpenClipboard();
  NI_VERIFY( result, "OpenClipboard failed", return false );

  result = EmptyClipboard();
  NI_VERIFY( result, "EmptyClipboard failed", CloseClipboard(); return false );

  HGLOBAL hCopy = GlobalAlloc( GMEM_MOVEABLE, ( text.size() + 1 ) * sizeof( TCHAR ) );
  NI_VERIFY( hCopy, "GlobalAlloc failed", CloseClipboard(); return false );

  LPTSTR pCopy = (LPTSTR)GlobalLock( hCopy );
  memcpy( pCopy, text.c_str(), ( text.size() + 1 ) * sizeof( TCHAR ) );
  GlobalUnlock( hCopy ); 

  HANDLE hData = SetClipboardData( CF_TEXT, hCopy ); 
  NI_VERIFY( hData, "SetClipboardData failed", CloseClipboard(); return false );

  result = CloseClipboard();
  NI_VERIFY( result, "CloseClipboard failed", return false );

  return true;
}

} //namespace profiler3ui
