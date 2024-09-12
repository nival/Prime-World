#include "Stdafx.h"
#include "User.h"

#include "Window.h"
#include "ScreenLogicBase.h"
#include "Resolution.h"
#include "DebugDraw.h"

#include "../System/InlineProfiler.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int g_hoverTooltipTime = 500;
REGISTER_VAR( "ui_tooltip_hover_time", g_hoverTooltipTime, STORAGE_NONE );

static int MOUSE_MOVE_DELTA = 3;
REGISTER_VAR( "ui_mouse_move_delta", MOUSE_MOVE_DELTA, STORAGE_NONE );


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
User::User() :
mouseMoveEventBind( "win_mouse_move" ), mouseOutEventBind( "win_mouse_out" ),
mouseOverWindowUpdated( false ),
mouseOverTime( 0.0f ),
tooltipShown( false ),
dropTargetIsValid( false )
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::UpdateMouseMove( const Point & mouseCoords )
{
  lastMouseCoords = mouseCoords;

  const bool moved = ( abs( mouseCoords.x - lastQuantizedMouseCoords.x ) > MOUSE_MOVE_DELTA ) ||
                     ( abs( mouseCoords.y - lastQuantizedMouseCoords.y ) > MOUSE_MOVE_DELTA );
  if( moved )
  {
    lastQuantizedMouseCoords = mouseCoords;
    ResetTooltipMouse();
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::UpdateMouseOver( Window * newOverWindow, const Point & mousePos )
{
  if( newOverWindow != mouseOverWindow )
  {
    if( mouseOverWindow )
      mouseOverWindow->EventMouseOver( false, mousePos );

    if( newOverWindow )
      newOverWindow->EventMouseOver( true, mousePos );

    mouseOverWindow = newOverWindow;
  }

  mouseOverWindowUpdated = true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::SetKeyboardFocus( Window * newFocusWindow )
{
  if( newFocusWindow != keyboardFocus )
  {
    if( keyboardFocus )
    {
      keyboardFocus->EventKeyboardFocus( false );
      if ( Debug::MouseTraceEnabled() )
      {
        Debug::Color c( 255, 255, 0 );
        float dur = 1.0f;
        Debug::AddRect( keyboardFocus->winRect, c, dur );
        Debug::AddLine( keyboardFocus->winRect.GetLeftTop(), keyboardFocus->winRect.GetRightBottom(), c, dur );
        Debug::AddLine( keyboardFocus->winRect.GetLeftBottom(), keyboardFocus->winRect.GetRightTop(), c, dur );
      }
    }

    if ( newFocusWindow )
      newFocusWindow->EventKeyboardFocus( true );

    keyboardFocus = newFocusWindow;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::Step( float deltaTime )
{
  NI_PROFILE_FUNCTION

  if( mouseOverWindow && !mouseCaptureTarget )
  {
    mouseOverTime += deltaTime;

    const float timelimit = 1e-3f * g_hoverTooltipTime;
    if( !tooltipShown && ( mouseOverTime > timelimit ) )
    {
      tooltipShown = true;
      mouseOverWindow->EventTooltip( lastMouseCoords );
    }
  }
  else
    ResetTooltipMouse();

  if ( keyboardFocus )
  {
    if ( !keyboardFocus->IsFullyVisible() || !keyboardFocus->IsFullyEnabled() )
      SetKeyboardFocus( 0 );
    else
      if ( Debug::MouseTraceEnabled() )
        Debug::AddRect( keyboardFocus->winRect, Debug::Color( 255, 255, 255 ) );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::StartEvent( const Input::Event & event )
{
  if ( mouseMoveEventBind.ProcessEvent( event ) )
  {
    mouseOverWindowUpdated = false;

    UpdateMouseMove( ExtractMsgCoords( event.SysParams() ) );
  }
  else if( mouseOutEventBind.ProcessEvent( event ) )
  {
    UpdateMouseOver( 0, ExtractMsgCoords( event.SysParams() ) );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::EndEvent( const Input::Event & event )
{
  if ( mouseMoveEventBind.ProcessEvent( event ) )
  {
    if( !mouseOverWindowUpdated )
      UpdateMouseOver( 0, ExtractMsgCoords( event.SysParams() ) );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::ForceTooltip( const Point & mouseCoords )
{
  lastQuantizedMouseCoords = lastMouseCoords = mouseCoords;

  if( mouseOverWindow )
    mouseOverWindow->EventTooltip( lastMouseCoords );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::ResetTooltipMouse()
{
  mouseOverTime = 0;
  tooltipShown = false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::SetMouseCapture( Window * target )
{
  mouseCaptureTarget = target;

  if( mouseCaptureTarget )
  {
    const char * dbId = mouseCaptureTarget->GetWindowLayout()->GetDBID().GetId().c_str();
    DebugTrace( "Mouse captured by '%s' (%s)", mouseCaptureTarget->GetWindowName().c_str(), dbId );
  }
  else
  {
    DebugTrace( "Mouse capture released" );
  }

  ResetTooltipMouse();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool User::StartDrag( Window * target, const char * id, int offsX, int offsY )
{
  if ( !dragAndDropId.empty() || dragTarget || !target )
    return false;

  dragLimits.Set( 0, 0, GetUIScreenResolution().x, GetUIScreenResolution().y );
  if ( !target->EventStartDrag( id ) )
    return false;

  dragAndDropId = id;
  dragTarget = target;
  dropTarget = 0;

  dndTargetOriginalPos = target->GetWindowRect().GetLeftTop();
  dragOffset.x = ( offsX < 0 ) ? ( lastMouseCoords.x - dndTargetOriginalPos.x ) : offsX;
  dragOffset.y = ( offsY < 0 ) ? ( lastMouseCoords.y - dndTargetOriginalPos.y ) : offsY;

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::Drop( bool restoreLocation )
{
  if ( !dragTarget || dragAndDropId.empty() )
    return;

  dragTarget->EventDrop( dragAndDropId.c_str(), dropTarget ? dropTarget : 0 );

  if ( restoreLocation )
    RestoreDNDLocation();

  ResetDragAndDrop();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::CancelDrag()
{
  if ( !dragTarget || dragAndDropId.empty() )
    return;

  if ( dragTarget )
  {
    RestoreDNDLocation();
    dragTarget->EventCancelDrag( dragAndDropId.c_str() );
  }

  ResetDragAndDrop();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::ModifyDragLimits( const Rect & limits )
{
  dragLimits = limits;

  dragLimits.left   = Max( (LinearCoord)0, dragLimits.left );
  dragLimits.right  = Min( GetUIScreenResolution().x, dragLimits.right );
  dragLimits.top    = Max( (LinearCoord)0, dragLimits.top );
  dragLimits.bottom = Min( GetUIScreenResolution().y, dragLimits.bottom );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::ImplUpdateDragAndDrop( Window * _dropTarget )
{
  //Handle unpredicted window death etc.
  if ( dragAndDropId.empty() || !dragTarget )
  {
    ResetDragAndDrop();
    return;
  }

  //Handle the drag itself
  if ( lastDragPos != lastMouseCoords )
  {
    Point location( lastMouseCoords.x - dragOffset.x, lastMouseCoords.y - dragOffset.y );

    location.x = Max( location.x, dragLimits.x1);
    location.y = Max( location.y, dragLimits.y1);
    location.x = Min( location.x, dragLimits.x2 - dragTarget->GetSize().x );
    location.y = Min( location.y, dragLimits.y2 - dragTarget->GetSize().y );

    if ( dragTarget->GetParent() )
      location = dragTarget->GetParent()->ScreenToLocal( location );
    
    dragTarget->SetLocation( location.x, location.y );
    dragTarget->EventDragMove( dragAndDropId.c_str() );
    lastDragPos = lastMouseCoords;
  }

  //Handle drop target changes
  if ( dropTargetIsValid && !dropTarget )
  {
    dragTarget->EventDropTarget( dragAndDropId.c_str(), false, 0 );
    dropTarget = 0;
    dropTargetIsValid = false;
  }

  if ( _dropTarget != dropTarget )
  {
    if ( dropTargetIsValid )
      dragTarget->EventDropTarget( dragAndDropId.c_str(), false, dropTarget );

    dropTargetIsValid = _dropTarget;
    dropTarget = dropTargetIsValid ? _dropTarget : 0;

    if ( dropTargetIsValid )
      dragTarget->EventDropTarget( dragAndDropId.c_str(), true, dropTarget );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::RestoreDNDLocation()
{
  if ( !dragTarget )
    return;

  Point to = dndTargetOriginalPos;
  if ( dragTarget->GetParent() )
    to = dragTarget->GetParent()->ScreenToLocal( to );
  dragTarget->SetLocation( to.x, to.y );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void User::ResetDragAndDrop()
{
  dragAndDropId.clear();
  dragTarget = 0;
  dropTarget = 0;
  dndTargetOriginalPos.Set( 0, 0 );
  dragOffset.Set( 0, 0 );
  lastDragPos.Set( 0, 0 );
}

} //namespace UI


NI_DEFINE_REFCOUNT( UI::User )
