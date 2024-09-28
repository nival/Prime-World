#include "stdafx.h"
#include "Profiler3UITimeline.h"
#include "System/ThreadNames.h"


namespace profiler3ui
{

const COLORREF CProfilerTimeline::ColorPivots[] = { RGB( 0, 0, 255 ), RGB( 0, 255, 0 ), RGB( 255, 0, 0 ) };
const int CProfilerTimeline::ColorPivotsNumber = sizeof( CProfilerTimeline::ColorPivots ) / sizeof( COLORREF );

CProfilerTimeline::CProfilerTimeline( ITimelineSelection * selectionCallback ) :
m_selectionCallback( selectionCallback ),
m_drawnProfilerTime( 0 ), m_drawnTimeFactor( 1.0 ),
m_pageFrom( 0 ), m_pageTo( 0 ),
m_rangeFrom( 0 ), m_rangeTo( 0 ),
m_minimalPage( 0 ),
m_hilitedThread( 0 ), m_selectedThread( 0 ),
m_hilitedEvent( -1 ), m_selectedEvent( -1 ),
m_textColor( 0 ),
m_maxEventsToDraw( 1024 )
{
  LOGFONT lf;
  ::GetObject( (HFONT)GetStockObject( DEFAULT_GUI_FONT ), sizeof( lf ), &lf );
  CreateFont( lf );
}



void CProfilerTimeline::SubclassWindow( HWND hWnd )
{
  CWindowImpl<CProfilerTimeline, CWindow>::SubclassWindow( hWnd );

  m_backGroundBrush.CreateSolidBrush( RGB( 0, 0, 0 ) );
  m_threadBgBrush.CreateSolidBrush( RGB( 48, 48, 48 ) );;
  m_selectionBrush.CreateSolidBrush( RGB( 255, 255, 255 ) );
  m_selectedEventBrush.CreateHatchBrush( 4, RGB( 128, 128, 128 ) );

  SetupGradient();
  
  m_textColor = RGB( 255, 247, 161 );
  SetFont( "Arial", 8 );

  m_timelinePen.CreatePen( PS_SOLID, 0, RGB( 255, 255, 255 ) );

  SetWindowText( "" );
}


//HACK: Circumvent runtime check in GetGValue() due to silly (WORD) conversion
#if defined(GetGValue)
#undef GetGValue
inline BYTE GetGValue( COLORREF rgb ) { return (BYTE)(( rgb & 0x0000ff00 ) >> 8); }
#endif


void CProfilerTimeline::SetupGradient()
{
  float shade = 1.0f;
  for ( int i = 0; i < ShadeGrades; ++i )
  {
    m_gradientBrushes[i].clear();
    m_gradientBrushes[i].resize( ColorsNumber );
    NI_ASSERT( ColorPivotsNumber >= 2, "" );
    NI_ASSERT( ColorsNumber >= ColorPivotsNumber, "" );
    for ( int j = 0; j < ColorsNumber; ++j )
    {
      //Integer lerp
      const int ColorsMax = ColorsNumber - 1;

      int factor = j * ( ColorPivotsNumber - 1 );
      int pivot0 = factor / ColorsMax;
      int pivot1 = Min( pivot0 + 1, ColorPivotsNumber - 1 );

      int leftover = factor - pivot0 * ColorsMax;

      int r = ( GetRValue( ColorPivots[pivot0] ) * ( ColorsMax - leftover ) + GetRValue( ColorPivots[pivot1] ) * leftover ) / ColorsMax;
      int g = ( GetGValue( ColorPivots[pivot0] ) * ( ColorsMax - leftover ) + GetGValue( ColorPivots[pivot1] ) * leftover ) / ColorsMax;
      int b = ( GetBValue( ColorPivots[pivot0] ) * ( ColorsMax - leftover ) + GetBValue( ColorPivots[pivot1] ) * leftover ) / ColorsMax;
      int sum = Max( r, Max( g, b ) );
      if ( sum > 0 )
      {
        r = (int)( shade * ( r * 255 / sum ) );
        g = (int)( shade * ( g * 255 / sum ) );
        b = (int)( shade * ( b * 255 / sum ) );
      }

      m_gradientBrushes[i][j].CreateSolidBrush( RGB( r, g, b ) );
    }

    shade *= (float)ShadeDegree / 100.0f;
  }
}



void CProfilerTimeline::PaintGradient( CDC & dc )
{
  const int SQ_SZ = 10;
  for ( int j = 0; j < m_gradientBrushes[0].size(); ++j )
  {
    CRect rect( HorizMargins, TopMargin, HorizMargins, TopMargin + SQ_SZ );
    rect.left += j * SQ_SZ;
    rect.right += ( j + 1 ) * SQ_SZ;
    ::FillRect( dc, rect, m_gradientBrushes[0][j] );
  }
}



void CProfilerTimeline::SetRange( profiler3::FTime from, profiler3::FTime to, profiler3::FTime minimalPage )
{
  NI_VERIFY( ( from <= 0 ) && ( to <= 0 ) && ( from < to ), "Wrong time range", return );
  m_rangeFrom = from;
  m_rangeTo = to;
  m_minimalPage = minimalPage;
  m_pageFrom = from;
  m_pageTo = to;
}



void CProfilerTimeline::Zoom( float scale )
{
  const profiler3::FTime page = m_pageTo - m_pageFrom;
  const profiler3::FTime newPage = Max( m_minimalPage, page * scale );

  const profiler3::FTime halfDelta = 0.5 * ( newPage - page );
  m_pageTo += halfDelta;
  m_pageFrom -= halfDelta;
  LimitScroll();
}



void CProfilerTimeline::ScrollRelative( float pageScale )
{
  const profiler3::FTime delta = pageScale * ( m_pageTo - m_pageFrom );
  m_pageFrom += delta;
  m_pageTo += delta;
  LimitScroll();
}



void CProfilerTimeline::ScrollAbs( float pos )
{
  const profiler3::FTime page = m_pageTo - m_pageFrom;
  m_pageFrom = m_rangeFrom * ( 1.0f - pos ) + pos * m_rangeTo;
  m_pageTo = m_pageFrom + page;
  LimitScroll();
}



void CProfilerTimeline::LimitScroll()
{
  profiler3::FTime page = m_pageTo - m_pageFrom;
  page = Min( page, m_rangeTo - m_rangeFrom );
  page = Max( page, m_minimalPage );

  if ( m_pageFrom < m_rangeFrom )
    m_pageFrom = m_rangeFrom;

  m_pageTo = m_pageFrom + page;

  if ( m_pageTo > m_rangeTo )
  {
    m_pageTo = m_rangeTo;
    m_pageFrom = m_pageTo - page;
  }
}


void CProfilerTimeline::SetupScrollBar( CScrollBar & bar, int degrees )
{
  profiler3::FTime page = m_pageTo - m_pageFrom;
  profiler3::FTime range = m_rangeTo - m_rangeFrom;

  SCROLLINFO si;
  ZeroMemory( &si, sizeof( si ) );
  si.cbSize = sizeof( si );
  si.fMask = SIF_PAGE | SIF_POS | SIF_DISABLENOSCROLL;
  si.nPage = (int)( degrees * page / range + 0.5 );
  si.nPos = (int)( degrees * ( m_pageFrom - m_rangeFrom ) / range + 0.5 );
  bar.SetScrollInfo( &si );
}



LRESULT CProfilerTimeline::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{       
  NI_ASSERT( m_hWnd, "" );

  CRect clientRect;
  GetClientRect( clientRect );

  CPaintDC paintDc( m_hWnd );

  CBitmap bitmap;
  BOOL memBitmapCreated = ( bitmap.CreateCompatibleBitmap( paintDc, clientRect.Width(), clientRect.Height() ) != NULL );
  NI_VERIFY( memBitmapCreated, "", return 0 );

  CDC memDc;
  bool memDcCreated = ( memDc.CreateCompatibleDC( paintDc ) != NULL );
  NI_VERIFY( memDcCreated, "", return 0 );

  HGDIOBJ hPrevBmp = ::SelectObject( memDc, bitmap );

  //Do the drawing
  ::FillRect( memDc, clientRect, m_backGroundBrush );

  m_drawnProfilerTime = profiler3::GetControl()->ProfilerTime( &m_drawnTimeFactor );
  PaintThreads( memDc, clientRect );

  //copy buffer
  paintDc.BitBlt( 0, 0, clientRect.Width(), clientRect.Height(), memDc, 0, 0, SRCCOPY );

  ::SelectObject( memDc, hPrevBmp );

  return TRUE;
}



LRESULT CProfilerTimeline::OnMouseButtonDown( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled, bool leftButton )
{
  CPoint pt( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );

  CRect clientRect;
  GetClientRect( clientRect );

  profiler3::TThreadId tid = 0;
  int eid = -1;
  if ( !HitTestThreads( tid, eid, clientRect, pt ) )
  {
    tid = 0;
    eid = -1;
  }

  //We can never reset thread selection
  if ( !tid )
    tid = m_selectedThread;

  const bool changed = ( ( m_selectedThread != tid ) || ( m_selectedEvent != eid ) );
  m_selectedThread = tid;
  m_selectedEvent = eid;

  if ( m_selectionCallback )
    if ( leftButton )
      m_selectionCallback->OnTimelineLeftClick( tid, eid, pt, changed );
    else
      m_selectionCallback->OnTimelineRightClick( tid, eid, pt, changed );
  return 0;
}



LRESULT CProfilerTimeline::OnMouseMove( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled )
{
  CPoint pt( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );

  CRect clientRect;
  GetClientRect( clientRect );

  profiler3::TThreadId tid = 0;
  int eid = -1;
  if ( !HitTestThreads( tid, eid, clientRect, pt ) )
  {
    tid = 0;
    eid = -1;
  }

  const bool notify = ( ( m_hilitedThread != tid ) || ( m_hilitedEvent != eid ) );
  m_hilitedThread = tid;
  m_hilitedEvent = eid;

  if ( notify && m_selectionCallback )
    m_selectionCallback->OnTimelineHilite( tid, eid );
  return 0;
}



bool CProfilerTimeline::GetThreadRect( CRect & result, const CRect & srcRect, int index, int count )
{
  const int fieldHeight = srcRect.Height() - TopMargin - BottomMargin;

  if ( fieldHeight <= MaxBarHeight ) //Field is too small
    return false;

  int barHeight = ( fieldHeight + BarsMargins ) / count - BarsMargins;
  NI_ASSERT( barHeight >= 0, "" );

  barHeight = Min( barHeight, MaxBarHeight );

  result.left = srcRect.left + HorizMargins;
  result.right = srcRect.right - HorizMargins;
  result.bottom = srcRect.bottom - BottomMargin - ( count - 1 - index ) * ( barHeight + BarsMargins );
  result.top = result.bottom - barHeight;

  return true;
}



bool CProfilerTimeline::GetEventRect( CRect & result, const CRect & threadRect, const profiler3::SRootEventDesc & event, profiler3::FTime fromTime, profiler3::FTime toTime )
{
  if ( event.startTime > toTime )
    return false;

  if ( event.startTime + event.duration < fromTime )
    return false;

  const double k = threadRect.Width() / ( toTime - fromTime );

  result.left = threadRect.left + (int)( 0.5 + ( event.startTime - fromTime ) * k );
  result.right = threadRect.left + (int)( 0.5 + ( event.startTime + event.duration - fromTime ) * k );

  //Force visibility of microscopic events
  if ( result.right <= result.left ) result.right = result.left + 1;

  result.left = Max( result.left, threadRect.left );
  result.right = Min( result.right, threadRect.right );
  result.top = threadRect.top;
  result.bottom = threadRect.bottom;
  return true;
}



void CProfilerTimeline::PaintThreads( CDC & dc, const CRect & clientRect )
{
  PaintTimeline( dc, clientRect );
  PaintGradient( dc );

  int count = Min( (int)m_data->GetEnabledThreadsCount(), MaxThreadsToDisplay );;
  if ( !count )
    return;

  {
    profiler3::TThreadId threadId = 0;
    for ( int i = 0; i < count; ++i )
    {
      profiler3::TOsThreadId osThreadId = 0;
      const profiler3::TRootEventsDescription * rootEvents = m_data->GetNextEnabledThreadRootEvents( threadId, osThreadId );
      if ( !rootEvents )
        break;

      CRect rect;
      if ( !GetThreadRect( rect, clientRect, i, count ) )
        continue;

      PaintSingleThread( dc, rect, threadId, osThreadId, *rootEvents );
    }
  }
}



void CProfilerTimeline::PaintSingleThread( CDC & dc, const CRect & rect, profiler3::TThreadId threadId, profiler3::TOsThreadId osThreadId, const profiler3::TRootEventsDescription & rootEvents )
{
  ::FillRect( dc, rect, m_threadBgBrush );

  profiler3::FTime fromTime = m_drawnProfilerTime + m_pageFrom, toTime = m_drawnProfilerTime + m_pageTo;

  bool hilite = false;
  if ( m_hilitedThread )
    hilite = ( threadId == m_hilitedThread );
  else if ( m_selectedThread )
    hilite = ( threadId == m_selectedThread );

  //Find indices range
  int fromIdx = Max( 0, profiler3::GetControl()->SearchRootEvents( rootEvents, fromTime ) );
  int toIdx = Min( (int)rootEvents.size(), profiler3::GetControl()->SearchRootEvents( rootEvents, toTime ) + 1 );

  NI_VERIFY( fromIdx >= 0 && fromIdx <= rootEvents.size(), "", return );
  NI_VERIFY( toIdx >= 0, "", return );

  bool displayWarninig = false;
  if ( m_maxEventsToDraw && ( ( toIdx - fromIdx ) > (int)m_maxEventsToDraw ) )
  {
    displayWarninig = true;
    toIdx = fromIdx - m_maxEventsToDraw;
  }

  //Find min and max durations in view
  profiler3::FTime minDuration = 0, maxDuration = 0;
  for ( int i = fromIdx; i < toIdx; ++i )
  {
    const float d = rootEvents[i].duration;
    if ( i == fromIdx )
    {
      minDuration = d;
      maxDuration = d;
    }
    else
    {
      if ( d < minDuration ) minDuration = d;
      if ( d > maxDuration ) maxDuration = d;
    }
  }
  profiler3::FTime medDuration = 0.5 * ( minDuration + maxDuration );
  minDuration = Min( minDuration, medDuration * 0.5 );
  maxDuration = Max( maxDuration, medDuration * 1.5 );
  profiler3::FTime deltaDuration = maxDuration - minDuration;

  //Draw events
  CRect hilitedEventRect, selectedEventRect;

  int maxx = rect.left;
  for ( int i = fromIdx; i < toIdx; ++i )
  {
    const profiler3::SRootEventDesc & event = rootEvents[i];

    CRect evtRect;
    if ( !GetEventRect( evtRect, rect, event, fromTime, toTime ) )
      continue;

    //Cut down draw calls:
    if ( evtRect.right <= maxx )
      continue;

    if ( ( threadId == m_hilitedThread ) && ( event.id == m_hilitedEvent ) )
      hilitedEventRect = evtRect;
    if ( ( threadId == m_selectedThread ) && ( event.id == m_selectedEvent ) )
      selectedEventRect = evtRect;

    const int brushSet = ( hilite ? 1 : 2 ) - ( event.id % 2 );
    const vector<CBrush> & brushes = m_gradientBrushes[brushSet];
    const double factor = ( event.duration - minDuration ) / deltaDuration;
    const int brushIdx = Clamp( (int)( 0.5 + ( brushes.size() - 1 ) * factor ), 0, brushes.size() - 1 );

    ::FillRect( dc, evtRect, brushes[brushIdx] );

    maxx = evtRect.right;
  }

  PaintSelectionRect( dc, hilitedEventRect );
  PaintSelectionRect( dc, selectedEventRect );

  if ( displayWarninig )
    PaintText( dc, rect, NI_STRFMT( "Warning! Too many events to display. Try to zoom in to view all of them." ), 0, 0 );

  PaintText( dc, rect, NI_STRFMT( "%s (0x%04x)", threading::GetDebugThreadName( osThreadId ), osThreadId ), -1, 0 );
}



void CProfilerTimeline::PaintTimeline( CDC & dc, const CRect & rect )
{
  CRect tmRect;
  tmRect.left = rect.left + HorizMargins;
  tmRect.right = rect.right - HorizMargins;
  tmRect.bottom = rect.bottom - TimelineMargin;
  tmRect.top = rect.bottom - BottomMargin;

  HPEN oldPen = dc.SelectPen( m_timelinePen );

  dc.MoveTo( tmRect.left, tmRect.bottom - TimelineTick );
  dc.LineTo( tmRect.left, tmRect.bottom );
  dc.LineTo( tmRect.right, tmRect.bottom );
  dc.LineTo( tmRect.right, tmRect.bottom - TimelineTick );

  dc.SelectPen( oldPen );

  PaintText( dc, tmRect, NI_STRFMT( " From: %.3f sec", m_pageFrom ), -1, -1 );
  PaintText( dc, tmRect, NI_STRFMT( "To: %.3f sec ", m_pageTo ), +1, -1 );
  PaintText( dc, tmRect, NI_STRFMT( "View: %.3f sec", m_pageTo - m_pageFrom ), 0, -1 );
}



void CProfilerTimeline::PaintText( CDC & dc, const CRect & rect, const char * text, int horizJustify, int vertJustify )
{
  COLORREF crOldText = dc.SetTextColor( m_textColor );
  HFONT hOldFont = dc.SelectFont( m_Font );

  UINT fmt = DT_SINGLELINE;
  if ( horizJustify < 0 )
    fmt |= DT_LEFT;
  else if ( horizJustify > 0 )
    fmt |= DT_RIGHT;
  else
    fmt |= DT_CENTER;

  if ( vertJustify > 0 )
    fmt |= DT_TOP;
  else if ( vertJustify < 0 )
    fmt |= DT_BOTTOM;
  else
    fmt |= DT_VCENTER;

  dc.SetBkMode( TRANSPARENT );

  RECT textRect = rect;
  dc.DrawText( text, strlen( text ), &textRect, fmt );

  dc.SelectFont( hOldFont );
  dc.SetTextColor( crOldText );  
}



void CProfilerTimeline::PaintSelectionRect( CDC & dc, const CRect & rect )
{
  if ( rect.IsRectNull() )
    return;
  ::FrameRect( dc, rect, m_selectionBrush );
  const int margin = 2;
  if ( ( rect.Width() > 2 * margin ) && ( rect.Height() > 2 * margin ) )
    ::FrameRect( dc, CRect( rect.left + margin, rect.top + margin, rect.right - margin, rect.bottom - margin ), m_selectionBrush );
}



bool CProfilerTimeline::HitTestThreads( profiler3::TThreadId & threadId, int & eventId, const CRect & clientRect, const CPoint & point ) const
{
  int count = Min( (int)m_data->GetEnabledThreadsCount(), MaxThreadsToDisplay );;
  if ( !count )
    return false;

    profiler3::TThreadId tid = 0;
    for ( int i = 0; i < count; ++i )
    {
      profiler3::TOsThreadId osThreadId = 0;
      const profiler3::TRootEventsDescription * rootEvents = m_data->GetNextEnabledThreadRootEvents( tid, osThreadId );
      if ( !rootEvents )
        break;

      CRect rect;
      if ( !GetThreadRect( rect, clientRect, i, count ) )
        continue;

      if ( !PtInRect( rect, point ) )
        continue;

      threadId = tid;

      eventId = HitTestSingleThread( rect, point, threadId, *rootEvents  );
      return true;
    }

  return false;
}



int CProfilerTimeline::HitTestSingleThread( const CRect & rect, const CPoint & point, profiler3::TThreadId threadId, const profiler3::TRootEventsDescription & rootEvents ) const
{
  NI_VERIFY( rect.Width() > 0, "", return -1 );

  profiler3::FTime fromTime = m_drawnProfilerTime + m_pageFrom, toTime = m_drawnProfilerTime + m_pageTo;

  double factor = (double)( point.x - rect.left ) / (double)rect.Width();
  profiler3::FTime timeApprox = fromTime + ( toTime - fromTime ) * factor;

  int baseIdx = profiler3::GetControl()->SearchRootEvents( rootEvents, timeApprox );
  int fromIdx = Max( 0, baseIdx - 1 );
  int toIdx = Min( baseIdx + 1, rootEvents.size() );

  for ( int i = fromIdx; i < toIdx; ++i )
  {
    const profiler3::SRootEventDesc & event = rootEvents[i];

    CRect evtRect;
    if ( !GetEventRect( evtRect, rect, event, fromTime, toTime ) )
      continue;

    if ( !PtInRect( evtRect, point ) )
      continue;

    return event.id;
  }

  return -1;
}

} //namespace profiler3ui
