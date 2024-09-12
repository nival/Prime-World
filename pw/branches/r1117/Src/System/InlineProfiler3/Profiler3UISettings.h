#ifndef INLINEPROFILER3UISETTINGS_H_INCLUDED
#define INLINEPROFILER3UISETTINGS_H_INCLUDED

#include "Profiler3UIWTL.h"
#include "Profiler3UIResource.h"

#include "InlineProfiler3Control.h"
#include "Profiler3UITimeline.h"
#include "Profiler3UIData.h"


namespace profiler3ui
{

struct SUISettingsData
{
  enum ERefreshInterval
  {
    eRefresh2,
    eRefresh5,
    eRefresh10,
    eRefresh15,
    eRefresh25
  };

  enum EDrawMax
  {
    eDrawMax1000,
    eDrawMax2000,
    eDrawMax3000,
    eDrawMax5000,
    eDrawMaxUnlim,
  };

  bool              sortCallgraphByTime;
  ERefreshInterval  refreshInterval;
  EDrawMax          drawMax;

  SUISettingsData() : sortCallgraphByTime( true ), refreshInterval( eRefresh15 ), drawMax( eDrawMax2000 )
  {}
};



class CSettingsDialog : public CDialogImpl<CSettingsDialog>
{
public:
  enum { IDD = IDD_SETTINGS };

  CSettingsDialog( const profiler3::SSettings & _samplingSettings, const SUISettingsData & _uiSettings ) :
  samplingSettings( _samplingSettings ),
  uiSettings( _uiSettings )
  {}

  const profiler3::SSettings & SamplingSettings() const { return samplingSettings; }
  const SUISettingsData & UISettings() const { return uiSettings; }

  BEGIN_MSG_MAP( CSettingsDialog )
    MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
    COMMAND_ID_HANDLER( IDOK, OnCloseButton )
    COMMAND_ID_HANDLER( IDCANCEL, OnCloseButton )
  END_MSG_MAP()


  LRESULT OnInitDialog( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled )
  {
    CenterWindow( GetParent() );

    CheckDlgButton( IDC_SORT_CALLGRAPH, uiSettings.sortCallgraphByTime ? BST_CHECKED : BST_UNCHECKED );

    int refrButtId = IDC_RADIO_REFRESH_2 + ( uiSettings.refreshInterval - SUISettingsData::eRefresh2 );
    NI_ASSERT( refrButtId >= IDC_RADIO_REFRESH_2 && refrButtId <= IDC_RADIO_REFRESH_25, "" );
    CheckDlgButton( refrButtId, BST_CHECKED );

    int drawMaxButtId = IDC_RADIO_EVENTS_1000 + ( uiSettings.drawMax - SUISettingsData::eDrawMax1000 );
    NI_ASSERT( drawMaxButtId >= IDC_RADIO_EVENTS_1000 && refrButtId <= IDC_RADIO_EVENTS_UNLIM, "" );
    CheckDlgButton( drawMaxButtId, BST_CHECKED );

    SetDlgItemInt( IDC_TIMELINE,                  (int)( 0.5 + samplingSettings.timelineLength ), FALSE );
    SetDlgItemInt( IDC_INITIAL_ROOT_EVENTS,       samplingSettings.initialRootEvents, FALSE );
    SetDlgItemInt( IDC_ROOT_EVENTS_LIMIT,         samplingSettings.rootEventsLimit, FALSE );
    SetDlgItemInt( IDC_INITIAL_SAMPLING_BUFFER,   samplingSettings.initialSamplingBuffer / 1024, FALSE );
    SetDlgItemInt( IDC_SAMPLING_BUFFER_LIMIT,     samplingSettings.samplingBufferLimit / 1024, FALSE );
    SetDlgItemInt( IDC_FLUSH_INTERVAL,            (int)( 0.5 + samplingSettings.dataFlushPeriod * 1e3 ), FALSE );
    SetDlgItemInt( IDC_WORST_EVENTS,              samplingSettings.maxWorstRootEvents, FALSE );

    return TRUE;
  }


  LRESULT OnCloseButton( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL & bHandled )
  {
    if ( wID == IDOK )
    {
      profiler3::SSettings tmp1;
      SUISettingsData tmp2;
      if ( !GetData( tmp1, tmp2 ) )
        return 0;
      samplingSettings = tmp1;
      uiSettings = tmp2;
    }

    EndDialog( wID );
    return 0;
  }


  bool GetData( profiler3::SSettings & _samplingSettings, SUISettingsData & _uiSettings )
  {
    _uiSettings.sortCallgraphByTime = ( IsDlgButtonChecked( IDC_SORT_CALLGRAPH ) == BST_CHECKED );

    for ( int id = IDC_RADIO_REFRESH_2; id <= IDC_RADIO_REFRESH_25; ++id )
      if ( IsDlgButtonChecked( id ) == BST_CHECKED )
        _uiSettings.refreshInterval = SUISettingsData::ERefreshInterval( SUISettingsData::eRefresh2 + ( id - IDC_RADIO_REFRESH_2 ) );

    for ( int id = IDC_RADIO_EVENTS_1000; id <= IDC_RADIO_EVENTS_UNLIM; ++id )
      if ( IsDlgButtonChecked( id ) == BST_CHECKED )
        _uiSettings.drawMax = SUISettingsData::EDrawMax( SUISettingsData::eDrawMax1000 + ( id - IDC_RADIO_EVENTS_1000 ) );

    unsigned timeline = 0;
    if ( !GetItemValue( IDC_TIMELINE, timeline, 1, 60 ) )
      return false;
    _samplingSettings.timelineLength = timeline;

    unsigned flushPeriod = 0;
    if ( !GetItemValue( IDC_FLUSH_INTERVAL,           flushPeriod, 100, 10000 ) )
      return false;
    _samplingSettings.dataFlushPeriod = flushPeriod * 1e-3;

    if ( !GetItemValue( IDC_INITIAL_ROOT_EVENTS,      _samplingSettings.initialRootEvents, 16, 65536 ) ) return false;
    if ( !GetItemValue( IDC_ROOT_EVENTS_LIMIT,        _samplingSettings.rootEventsLimit, 1, 65536 ) ) return false;
    if ( !GetItemValue( IDC_INITIAL_SAMPLING_BUFFER,  _samplingSettings.initialSamplingBuffer, 1, 4096 ) ) return false;
    if ( !GetItemValue( IDC_SAMPLING_BUFFER_LIMIT,    _samplingSettings.samplingBufferLimit, 1, 4096 ) ) return false;
    if ( !GetItemValue( IDC_WORST_EVENTS,             _samplingSettings.maxWorstRootEvents, 1, 10 ) ) return false;

    _samplingSettings.initialSamplingBuffer *= 1024;
    _samplingSettings.samplingBufferLimit *= 1024;

    return true;
  }


  bool GetItemValue( WORD wID, unsigned & value, unsigned _min, unsigned _max )
  {
    BOOL ok = FALSE;
    value = GetDlgItemInt( wID, &ok, TRUE );
    if ( ok && ( value >= _min ) && ( value <= _max ) )
      return true;

    if ( !ok )
      MessageBox( "Wrong parameter format!", "Error", MB_OK | MB_ICONERROR );
    else
      MessageBox( NI_STRFMT( "Value must be in range from %u to %u!", _min, _max ), "Error", MB_OK | MB_ICONERROR );
    GetDlgItem( wID ).SetFocus();
    return false;
  }

private:
  profiler3::SSettings  samplingSettings;
  SUISettingsData   uiSettings;
};

} //namespace profiler3ui

#endif //INLINEPROFILER3UISETTINGS_H_INCLUDED
