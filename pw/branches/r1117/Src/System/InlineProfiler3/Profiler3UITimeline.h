#ifndef PROFILER3UITIMELINE_H_INCLUDED
#define PROFILER3UITIMELINE_H_INCLUDED

#include "Profiler3UIWTL.h"
#include "Profiler3UIData.h"

namespace profiler3ui
{

_interface ITimelineSelection
{
  virtual void OnTimelineHilite( profiler3::TThreadId threadId, int eventId ) = 0;
  virtual void OnTimelineLeftClick( profiler3::TThreadId threadId, int eventId, const CPoint & coords, bool changed ) = 0;
  virtual void OnTimelineRightClick( profiler3::TThreadId threadId, int eventId, const CPoint & coords, bool changed ) = 0;
};



class CProfilerTimeline : public CWindowImpl<CProfilerTimeline, CWindow> 
{
  const static int MaxThreadsToDisplay = 8;
  const static int MaxBarHeight = 30;
  const static int BarsMargins = 5;
  const static int TopMargin = 8;
  const static int BottomMargin = 24;
  const static int HorizMargins = 8;
  const static int TimelineMargin = 4;
  const static int TimelineTick = 8;

  const static int ColorsNumber = 10;
  const static int ShadeGrades = 3;
  const static int ShadeDegree = 70;
  const static COLORREF ColorPivots[];
  const static int ColorPivotsNumber;

public:
  CProfilerTimeline( ITimelineSelection * selectionCallback );

  virtual ~CProfilerTimeline() {}

  void SubclassWindow( HWND hWnd );

  void SetData( SamplingData * data )
  {
    m_data = data;
  }

  profiler3::FTime LastDrawnProfilerTime() const {  return m_drawnProfilerTime; }
  profiler3::FTime LastDrawnTimeFactor() const { return m_drawnTimeFactor; }

  void SetMaxEventsToDraw( unsigned number ) { m_maxEventsToDraw = number; }

  void SelectThread( profiler3::TThreadId threadId )
  {
    if ( m_selectedThread == threadId )
      return;

    m_selectedThread = threadId;
    m_selectedEvent = -1;
  }

  profiler3::TThreadId SelectedThread() const { return m_selectedThread; }
  int SelectedEvent() const { return m_selectedEvent; }

  void SetRange( profiler3::FTime from, profiler3::FTime to, profiler3::FTime minimalPage );
  void Zoom( float scale );
  void ScrollRelative( float pageScale );
  void ScrollAbs( float pos );
  void SetupScrollBar( CScrollBar & bar, int degrees );

private:
  BEGIN_MSG_MAP( CProfilerTimeline )
    MESSAGE_HANDLER( WM_PAINT, OnPaint )
    MESSAGE_HANDLER( WM_LBUTTONDOWN, OnMouseButtonDownTmpl<true> )
    MESSAGE_HANDLER( WM_RBUTTONDOWN, OnMouseButtonDownTmpl<false> )
		MESSAGE_HANDLER( WM_MOUSEMOVE, OnMouseMove )
  END_MSG_MAP()

  void SetupGradient();
  void PaintGradient( CDC & dc );
  void LimitScroll();

  LRESULT OnPaint( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
  LRESULT OnMouseButtonDown( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled, bool leftButton );
  LRESULT OnMouseMove( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled );

  template<bool leftButton>
  LRESULT OnMouseButtonDownTmpl( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled ) {
    return OnMouseButtonDown( uMsg, wParam, lParam, bHandled, leftButton );
  }


  void SetFont( const char * FontName, const int nSize )
  {
    LOGFONT lf;

    m_Font.GetLogFont(&lf);

    strcpy_s( lf.lfFaceName, FontName );

    HDC hDC         = GetDC();
    int nLogPixY    = GetDeviceCaps( hDC, LOGPIXELSY );
    ReleaseDC(hDC);

    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfHeight = -MulDiv( nSize, nLogPixY, 72 ); //Standard conversion
    lf.lfWeight = FW_BOLD;

    CreateFont( lf );
  }


  void CreateFont( const LOGFONT & lf )
  {
    if ( m_Font.m_hFont )
      m_Font.DeleteObject();

    bool bCreated = m_Font.CreateFontIndirect( &lf ) != NULL;
    NI_ASSERT( bCreated, "" );
  }

  static bool GetThreadRect( CRect & result, const CRect & srcRect, int index, int count );
  static bool GetEventRect( CRect & result, const CRect & threadRect, const profiler3::SRootEventDesc & event, profiler3::FTime fromTime, profiler3::FTime toTime );
  void PaintThreads( CDC & dc, const CRect & rect );
  void PaintSingleThread( CDC & dc, const CRect & rect, profiler3::TThreadId threadId, profiler3::TOsThreadId osThreadId, const profiler3::TRootEventsDescription & rootEvents );
  void PaintTimeline( CDC & dc, const CRect & rect );
  void PaintText( CDC & dc, const CRect & rect, const char * text, int horizJustify, int vertJustify );
  void PaintSelectionRect( CDC & dc, const CRect & rect );

  bool HitTestThreads( profiler3::TThreadId & threadId, int & eventId, const CRect & clientRect, const CPoint & point ) const;
  int HitTestSingleThread( const CRect & rect, const CPoint & point, profiler3::TThreadId threadId, const profiler3::TRootEventsDescription & rootEvents ) const;

  Strong<SamplingData>  m_data;

  ITimelineSelection *  m_selectionCallback;

  profiler3::FTime      m_drawnProfilerTime;
  profiler3::FTime      m_drawnTimeFactor;

  profiler3::FTime      m_rangeFrom, m_rangeTo;
  profiler3::FTime      m_minimalPage;
  profiler3::FTime      m_pageFrom, m_pageTo;
  profiler3::TThreadId  m_hilitedThread;
  profiler3::TThreadId  m_selectedThread;
  int                   m_hilitedEvent;
  int                   m_selectedEvent;

  CBrush                m_backGroundBrush;
  CBrush                m_threadBgBrush;
  vector<CBrush>        m_gradientBrushes[ShadeGrades];
  CBrush                m_selectionBrush;
  CBrush                m_selectedEventBrush;
  COLORREF              m_textColor;
  CPen                  m_timelinePen;

  CFont                 m_Font;

  unsigned              m_maxEventsToDraw;
};

} //namespace profiler3ui

#endif //PROFILER3UITIMELINE_H_INCLUDED
