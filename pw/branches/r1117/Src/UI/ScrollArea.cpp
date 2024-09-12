#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../Scripts/lua.hpp"
#include "ScrollArea.h"

namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO(ScrollArea, Window)
  LUA_METHOD(GetScrollX)
  LUA_METHOD(GetScrollY)

  LUA_METHOD(SetHandleMsgForXScroll)
  LUA_METHOD(SetHandleMsgForYScroll)

  LUA_METHOD(SetScroll)

  LUA_METHOD(GetScrollXSize)
  LUA_METHOD(GetScrollYSize)

  LUA_METHOD(SetScrollXLimits)
  LUA_METHOD(SetScrollYLimits)
END_LUA_TYPEINFO(ScrollArea)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScrollArea::ScrollArea()
: scrollX(0)
, scrollY(0)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollArea::OnAddChild( Window *child )
{
  child->SetCropping( true );

  Window::OnAddChild( child );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollArea::OnInit()
{
  Window::OnInit();

  if ( GetScrollAreaLayout() )
  {
    YLimits() = GetScrollAreaLayout()->scrollYLimits;

    SetMsgHandlerInt( GetScrollAreaLayout()->handleMsgForXScroll.c_str(), "" );
    SetMsgHandlerInt( GetScrollAreaLayout()->handleMsgForYScroll.c_str(), "" );

    scrollX = 0;
    scrollY = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollArea::SetHandleMsgForXScroll( string msgName )
{
  SetMsgHandler( GetScrollAreaLayout()->handleMsgForXScroll.c_str(), "" );
  GetScrollAreaLayout()->handleMsgForXScroll = msgName;
  SetMsgHandlerInt( GetScrollAreaLayout()->handleMsgForXScroll.c_str(), "" );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollArea::SetHandleMsgForYScroll( string msgName )
{
  SetMsgHandler( GetScrollAreaLayout()->handleMsgForYScroll.c_str(), "" );
  GetScrollAreaLayout()->handleMsgForYScroll = msgName;
  SetMsgHandlerInt( GetScrollAreaLayout()->handleMsgForYScroll.c_str(), "" );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollArea::UpdateScrollAndShift( bool scrollLimitsChanged )
{
  if ( scrollLimitsChanged )
    if ( !GetScrollAreaLayout()->spawnMsgOnLimitsChanged.empty() )
      SendMsgAll( this, GetScrollAreaLayout()->spawnMsgOnLimitsChanged.c_str(), GetWindowName().c_str() );

  int dx = 0;
  int dy = 0;
  const float inEpsilon = FP_EPSILON;
  float rx = XLimits().inMax - XLimits().inMin;
  if ( fabs(rx) >= inEpsilon )
    dx = XLimits().outMin + (int)(((scrollX - XLimits().inMin) * (XLimits().outMax - XLimits().outMin)) / rx);
  float ry = YLimits().inMax - YLimits().inMin;
  if ( fabs(ry) >= inEpsilon )
    dy = YLimits().outMin + (int)(((scrollY - YLimits().inMin) * (YLimits().outMax - YLimits().outMin)) / ry);
  SetChildrenShift( -dx,-dy );

  //
  OnScrollUpdated();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollArea::EventMsg( const string & msg, const string & s, float n )
{
  if ( msg == GetScrollAreaLayout()->handleMsgForXScroll )
    SetScroll( n, scrollY );
  else if ( msg == GetScrollAreaLayout()->handleMsgForYScroll )
    SetScroll( scrollX, n );

  Window::EventMsg( msg,s,n );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ScrollArea::GetScrollX()
{
  const int dx = -GetChildrenShift().x;
  const int rx = XLimits().outMax - XLimits().outMin;
  if ( rx == 0 )
    return 0;
  return (float)(((dx - XLimits().outMin) * ( XLimits().inMax - XLimits().inMin )) / rx);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ScrollArea::GetScrollY()
{
  const int dy = -GetChildrenShift().y;
  const int ry = YLimits().outMax - YLimits().outMin;
  if ( ry == 0 )
    return 0;
  return (float)(((dy - YLimits().outMin) * ( YLimits().inMax - YLimits().inMin )) / ry);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollArea::SetScroll( float sx, float sy )
{
  scrollX = sx;
  scrollY = sy;
  UpdateScrollAndShift( false );
  Invalidate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollArea::SetScrollXLimits( float inMin, float inMax, int outMin, int outMax )
{
  if ( inMin == XLimits().inMin && inMax == XLimits().inMax && outMin == XLimits().outMin && outMax == XLimits().outMax )
    return;
  XLimits().inMin = inMin;
  XLimits().inMax = inMax;
  XLimits().outMin = outMin;
  XLimits().outMax = outMax;
  UpdateScrollAndShift( true );
  Invalidate();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollArea::SetScrollYLimits( float inMin, float inMax, int outMin, int outMax )
{
  if ( inMin == YLimits().inMin && inMax == YLimits().inMax && outMin == YLimits().outMin && outMax == YLimits().outMax )
    return;
  YLimits().inMin = inMin;
  YLimits().inMax = inMax;
  YLimits().outMin = outMin;
  YLimits().outMax = outMax;
  UpdateScrollAndShift( true );
  Invalidate();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_CONTROLTYPE( NDb::UIScrollAreaLayout, ScrollArea );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
