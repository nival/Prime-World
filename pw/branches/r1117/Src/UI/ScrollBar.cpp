#include "stdafx.h"
#include "../Scripts/lua.hpp"
#include "ScrollBar.h"
#include "ScrollList.h"

namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO(ScrollBar, Window)
  LUA_METHOD(SetButtonStep)

  LUA_METHOD(GetNumPositions)
  LUA_METHOD(SetNumPositions)

  LUA_METHOD(GetScrollPosition)
  LUA_METHOD(SetScrollPosition)

  LUA_METHOD(GetScrollValue)
  LUA_METHOD(SetScrollValue)
END_LUA_TYPEINFO(ScrollBar)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScrollBar::ScrollBar() :
needUpdate( true )
, needForcedUpdate( true )
, leverSize(0)
, firstButtonSize(0)
, secondButtonSize(0)
, pFocusElementState(0)
, actionPosTrace( false )
, numPositions(0)
, buttonStep(0)
, position(0)
, leverDragBase(0)
, buttonRepeatRate( DEFAULT_BUTTON_REPEAT_RATE )
, buttonRepeatWait( DEFAULT_BUTTON_REPEAT_WAIT )
, buttonRepeatSide(0)
{
  // ? set mousewheel priority and exclusivity
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScrollBar::GetTotalSizeInt() const
{
  const bool horizontal = ( GetScrollBarLayout()->scrollBarType == NDb::UISCROLLBARTYPE_HORIZONTAL );
  return horizontal ? GetWindowRect().GetSizeX() : GetWindowRect().GetSizeY();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScrollBar::GetLeverCoordinateInt() const
{
  if ( numPositions <= 1 )
    return 0;
  return firstButtonSize + ((( GetTotalSizeInt() - firstButtonSize - secondButtonSize - leverSize ) * position ) / (numPositions-1));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScrollBar::EElement ScrollBar::GetElementInt( int coordinate ) const
{
  if ( coordinate < 0 )
    return ELEMENT_NONE;

  const int r1 = firstButtonSize;
  if ( coordinate < r1 )
    return ELEMENT_FIRSTBUTTON;

  const int r3 = GetTotalSizeInt();
  const int r2 = r3 - secondButtonSize;
  if ( coordinate >= r2 && coordinate < r3 )
    return ELEMENT_SECONDBUTTON;

  const int rL = GetLeverCoordinateInt();
  if ( coordinate >= rL && coordinate < rL + leverSize )
    return ELEMENT_LEVER;

  return ELEMENT_NONE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScrollBar::EElement ScrollBar::GetElementByCoordsInt( const Point & screenCoords ) const
{
  return GetElementInt( IsHorizontal() ? ( screenCoords.x - GetWindowRect().x1 ) : ( screenCoords.y - GetWindowRect().y1 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScrollBar::SElementState *ScrollBar::GetElementStateInt( ScrollBar::EElement element )
{
  if ( element == ELEMENT_FIRSTBUTTON )
    return &firstButtonState;
  if ( element == ELEMENT_LEVER )
    return &leverState;
  if ( element == ELEMENT_SECONDBUTTON )
    return &secondButtonState;
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::ModifyElementStateStyleInt( SElementState & elementState, NDb::EUIScrollBarElementStyle style, bool add )
{
  //if ( style == NDb::UISCROLLBARELEMENTSTYLE_HILITED )
  //{
  //  const bool hasStyle = (elementState.value & style);
  //  if ( add && !hasStyle )
  //    UI::PlaySound( "default_enter" );
  //  else if ( !add && hasStyle )
  //    UI::PlaySound( "default_leave" );
  //}

  if ( add )
    elementState.value = (NDb::EUIScrollBarElementStyle)(elementState.value |  style);
  else
    elementState.value = (NDb::EUIScrollBarElementStyle)(elementState.value & ~style);

  if ( elementState.value != elementState.oldValue )
  {
    needUpdate = true;
    Invalidate();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::SetElementImageMaterialInt( ImageComponent & image, const vector<NDb::Ptr<NDb::BaseUIMaterial>> & styles, NDb::EUIScrollBarElementStyle style )
{
  if ( style == NDb::UISCROLLBARELEMENTSTYLE_DISABLED )
    style = NDb::UISCROLLBARELEMENTSTYLE_PRESSED;
  if ( !IsFullyEnabled() )
    style = NDb::UISCROLLBARELEMENTSTYLE_DISABLED; // disabled style
  if ( style < 0 || style >= styles.size() )
    return;

  image.SetImageMaterial( styles[style], GetContext() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::ButtonStepInt( bool inc )
{
  int k = inc ? 1 : -1;
  if ( buttonStep > 0 )
    SetScrollPosition( GetScrollPosition() + k * buttonStep );
  else
    SetScrollValue( GetScrollValue() + k * 0.05f );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::SetScrollPositionInt( int x, int y, int delta )
{
  int offset = 0;
  if ( IsHorizontal() )
    offset = (x + delta) - (GetWindowRect().x1 + firstButtonSize);
  else
    offset = (y + delta) - (GetWindowRect().y1 + firstButtonSize);

  const int leverAreaSize = GetTotalSizeInt() - firstButtonSize - secondButtonSize - leverSize;
  if ( leverAreaSize > 0 )
    SetScrollPosition( (offset * (numPositions-1) + leverAreaSize/2) / leverAreaSize );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::OnInit()
{
  Window::OnInit();

  eventButtonClick = "default_scrollbar_button_click";
  eventLeverJump   = "default_scrollbar_lever_jump" ;
  eventLeverDrag   = "default_scrollbar_lever_drag";

  if ( GetScrollBarLayout() )
  {
    position = 0;
    buttonStep = 1;
    numPositions = 1;
    SetNumPositions( GetScrollBarLayout()->discretePositionsCount );

    firstButtonState.Updated();
    secondButtonState.Updated();
    leverState.Updated();

    needForcedUpdate = true;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::AttachScrollArea( ScrollArea* area )
{
  attachedScrollArea = area;
  UpdateScrollParameters();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::UpdateScrollParameters()
{
  if(attachedScrollArea)
  {
    int xSize = 0;
    int ySize = 0;
    UI::ScrollList * attachedScrollList = dynamic_cast<UI::ScrollList *>( attachedScrollArea.Get() );
    if(GetScrollBarLayout()->discreteType == NDb::UIDISCRETETYPE_RELATIVETOITEMSCOUNT && attachedScrollList)
    {
      const CTPoint<int> listSz = attachedScrollArea->GetSize();
      const CTPoint<int> itemSz = attachedScrollList->GetMaxRealItemSize();
      int xListItems = itemSz.x ? max(1, listSz.x / itemSz.x) : 1;
      int yListItems = itemSz.y ? max(1, listSz.y / itemSz.y) : 1;

      xSize = max(1, attachedScrollList->GetItemsCount() - xListItems + 1);
      ySize = max(1, attachedScrollList->GetItemsCount() - yListItems + 1);


      SetButtonStep(1);
    }
    else
    {
      xSize = attachedScrollArea->GetScrollXSize();
      ySize = attachedScrollArea->GetScrollYSize();
    }

    if( GetScrollBarLayout()->scrollBarType == NDb::UISCROLLBARTYPE_VERTICAL )
      SetNumPositions(ySize);
    else if( GetScrollBarLayout()->scrollBarType == NDb::UISCROLLBARTYPE_HORIZONTAL )
      SetNumPositions(xSize);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::OnRefresh( float deltaTime )
{
  UpdateScrollParameters();

  if ( needUpdate || needForcedUpdate )
  {
    needUpdate = false;

    if ( needForcedUpdate )
      LeverArea.SetImageMaterial( IsFullyEnabled() ? GetScrollBarLayout()->leverAreaMaterial : GetScrollBarLayout()->leverAreaDisabledMaterial, GetContext() );

    if ( firstButtonState.Changed() || needForcedUpdate )
      SetElementImageMaterialInt( FirstButton, GetScrollBarLayout()->firstButtonMaterials, firstButtonState.value );
    if ( leverState.Changed() || needForcedUpdate )
      SetElementImageMaterialInt( Lever, GetScrollBarLayout()->leverMaterials, leverState.value );
    if ( secondButtonState.Changed() || needForcedUpdate )
      SetElementImageMaterialInt( SecondButton, GetScrollBarLayout()->secondButtonMaterials, secondButtonState.value );

    const Rect & winRect = GetWindowRect();

    const bool horizontal = IsHorizontal();

    const int totalSize = GetTotalSizeInt();
    const int perpSize = horizontal ? winRect.GetSizeY() : winRect.GetSizeX();

    if ( firstButtonSize <= 0 || firstButtonSize > totalSize/2 )
      firstButtonSize = Max( 0, Min( GetScrollBarLayout()->firstButtonSize > 0 ? GetScrollBarLayout()->firstButtonSize : perpSize, totalSize/2 ) );

    if ( secondButtonSize <= 0 || secondButtonSize > totalSize/2 )
      secondButtonSize = Max( 0, Min( GetScrollBarLayout()->secondButtonSize > 0 ? GetScrollBarLayout()->secondButtonSize : perpSize, totalSize/2 ) );

    const int leverAreaSize = totalSize - firstButtonSize - secondButtonSize;

    if ( leverSize <= 0 || leverSize > leverAreaSize/2 )
      leverSize = Max( 0, Min( GetScrollBarLayout()->leverSize > 0 ? GetScrollBarLayout()->leverSize : ( numPositions > 1 && leverAreaSize/numPositions >= perpSize ? leverAreaSize/numPositions : 2*perpSize ), leverAreaSize/2 ) );

    Rect rect = winRect;
    float & r1 = horizontal ? rect.x1 : rect.y1;
    float & r2 = horizontal ? rect.x2 : rect.y2;
    const float r0 = r1;

    r2 = r1 + firstButtonSize;
    FirstButton.SetDrawRect( rect );
    r1 = r2;
    r2 += leverAreaSize;
    LeverArea.SetDrawRect( rect );
    r1 = r2;
    r2 += secondButtonSize;
    SecondButton.SetDrawRect( rect );
    r1 = r0 + GetLeverCoordinateInt();
    r2 = r1 + leverSize;
    Lever.SetDrawRect( rect );

    const Rect & cropRect = GetCropRect();
    LeverArea.SetCropRect( cropRect );
    FirstButton.SetCropRect( cropRect );
    SecondButton.SetCropRect( cropRect );
    Lever.SetCropRect( cropRect );

    needForcedUpdate = false;
  }

  LeverArea.SetMaterialOpacity( GetOpacity() );
  FirstButton.SetMaterialOpacity( GetOpacity() );
  SecondButton.SetMaterialOpacity( GetOpacity() );
  Lever.SetMaterialOpacity( GetOpacity() );

  //LeverArea.Update();
  //FirstButton.Update();
  //SecondButton.Update();
  //Lever.Update();

  Window::OnRefresh( deltaTime );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::Render()
{
  Window::Render();

  LeverArea.Render();
  FirstButton.Render();
  SecondButton.Render();
  Lever.Render();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScrollBar::EElement ScrollBar::GetElementFromElementStateInt( SElementState *pState )
{
  if ( pState == &leverState )
    return ELEMENT_LEVER;
  if ( pState == &firstButtonState )
    return ELEMENT_FIRSTBUTTON;
  if ( pState == &secondButtonState )
    return ELEMENT_SECONDBUTTON;
  return ELEMENT_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::OnEnable( bool _enable )
{
  needForcedUpdate = true;
  Invalidate();

  Window::OnEnable( _enable );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollBar::OnMouseMove( const Point & mouse )
{
  if ( actionPosTrace )
    actionPos = mouse;

  EElement element;
  if ( pFocusElementState )
  {
    element = GetElementFromElementStateInt( pFocusElementState );
  }
  else
  {
    element = GetElementByCoordsInt( mouse );
  }

  ModifyElementStateStyleInt( firstButtonState , NDb::UISCROLLBARELEMENTSTYLE_HILITED, element == ELEMENT_FIRSTBUTTON );
  ModifyElementStateStyleInt( leverState       , NDb::UISCROLLBARELEMENTSTYLE_HILITED, element == ELEMENT_LEVER );
  ModifyElementStateStyleInt( secondButtonState, NDb::UISCROLLBARELEMENTSTYLE_HILITED, element == ELEMENT_SECONDBUTTON );

  if ( pFocusElementState == &leverState && numPositions > 1 )
  {
    SetScrollPositionInt( mouse.x, mouse.y, -leverDragBase );
  }

  Window::OnMouseMove( mouse );

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::OnMouseOver( bool over, const Point & mouse )
{
  if ( !over )
  {
    ModifyElementStateStyleInt( firstButtonState , NDb::UISCROLLBARELEMENTSTYLE_HILITED, false );
    ModifyElementStateStyleInt( leverState       , NDb::UISCROLLBARELEMENTSTYLE_HILITED, false );
    ModifyElementStateStyleInt( secondButtonState, NDb::UISCROLLBARELEMENTSTYLE_HILITED, false );
  }

  Window::OnMouseOver( over, mouse );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollBar::OnMouseDown( EMButton::Enum mbutton, const Point & point )
{
  if ( mbutton != EMButton::Left )
    return true;

  GetContext()->CaptureMouse( this );

  SetFocus( true );

  actionPos = point;
  actionPosTrace = true;

  EElement element = GetElementByCoordsInt( point );

  pFocusElementState = GetElementStateInt( element );
  if ( pFocusElementState )
    ModifyElementStateStyleInt( *pFocusElementState, NDb::UISCROLLBARELEMENTSTYLE_PRESSED, true );

  if ( element == ELEMENT_FIRSTBUTTON )
  {
    buttonRepeatSide = -1;
    SetTimeTrigger( buttonRepeatWait * 1e-3f );
  }
  else if ( element == ELEMENT_SECONDBUTTON )
  {
    buttonRepeatSide = 1;
    SetTimeTrigger( buttonRepeatWait * 1e-3f );
  }

  if ( pFocusElementState == &leverState )
  {
    if ( IsHorizontal() )
      leverDragBase = point.x - (GetWindowRect().x1 + GetLeverCoordinateInt());
    else
      leverDragBase = point.y - (GetWindowRect().y1 + GetLeverCoordinateInt());

    //NSoundScene::EventStart( eventLeverDrag );
  }

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollBar::OnMouseUp( EMButton::Enum mbutton )
{
  if ( mbutton != EMButton::Left )
    return true;

  GetContext()->ReleaseMouse();

  actionPosTrace = false;

  EElement focusElement = GetElementFromElementStateInt( pFocusElementState );

  if ( pFocusElementState )
  {
    ModifyElementStateStyleInt( *pFocusElementState, NDb::UISCROLLBARELEMENTSTYLE_PRESSED, false );
    ModifyElementStateStyleInt( *pFocusElementState, NDb::UISCROLLBARELEMENTSTYLE_HILITED, false );
    pFocusElementState = 0;
  }

  buttonRepeatSide = 0;

  if ( true )
  {
    if ( focusElement == ELEMENT_FIRSTBUTTON || focusElement == ELEMENT_SECONDBUTTON )
    {
      ButtonStepInt( focusElement == ELEMENT_SECONDBUTTON );
      //NSoundScene::EventStart( eventButtonClick );
    }

    if ( focusElement == ELEMENT_NONE )
    {
      SetScrollPositionInt( actionPos.x, actionPos.y, -leverSize/2 );
      //NSoundScene::EventStart( eventLeverJump );
    }
  }

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollBar::OnScroll( int delta )
{
  if ( delta < 0 )
    ButtonStepInt( false );
  else if ( delta > 0 )
    ButtonStepInt( true );

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::OnTimeTrigger()
{
  if(buttonRepeatSide != 0 && buttonRepeatRate > 0)
  {
    ButtonStepInt(buttonRepeatSide > 0);
    SetTimeTrigger( 1.f / buttonRepeatRate );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollBar::GetCustomCursor( string * name, const Point & screenCoords ) const
{
  if ( !name )
    return false;

  string const *pCursor = NULL;

  EElement element = GetElementByCoordsInt( screenCoords );
  if ( element == ELEMENT_FIRSTBUTTON )
    pCursor = (pFocusElementState == &firstButtonState) ? &GetWindowLayout()->cursors.pushing : &GetWindowLayout()->cursors.pushable;
  else if ( element == ELEMENT_SECONDBUTTON )
    pCursor = (pFocusElementState == &secondButtonState) ? &GetWindowLayout()->cursors.pushing : &GetWindowLayout()->cursors.pushable;
  else if ( element == ELEMENT_LEVER )
    pCursor = (pFocusElementState == &leverState) ? &GetWindowLayout()->cursors.dragging : &GetWindowLayout()->cursors.dragable;

  if (pCursor && !pCursor->empty())
  {
    *name = *pCursor;
    return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::SetButtonStep( int step )
{
  if ( buttonStep <= 0 )
    return;
  buttonStep = Max( 1, step );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScrollBar::GetNumPositions()
{
  if ( buttonStep <= 0 )
    return 0;
  return numPositions;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::SetNumPositions( int _numPositions )
{
  if ( numPositions == _numPositions )
    return;
  float val = GetScrollValue();
  numPositions = Max( 0, _numPositions );
  if ( numPositions <= 0 )
  {
    buttonStep = 0;
    numPositions = nondiscreteNumPositions;
  }
  else
  {
    if ( buttonStep == 0 )
      buttonStep = 5;
  }
  SetScrollValue( val );
  leverSize = 0;
  needUpdate = true;
  Invalidate();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::SetScrollPosition( int pos )
{
  pos = Max( 0, Min( pos, numPositions-1 ) );
  if ( position == pos )
    return;
  position = pos;
  needUpdate = true;
  Invalidate();

  if ( IsFullyEnabled() )
  {
    if ( !GetScrollBarLayout()->spawnMsgOnScrolled.empty() )
      FireCustomUserMessage( GetScrollBarLayout()->spawnMsgOnScrolled );
    if ( attachedScrollArea )
    {
      int x = attachedScrollArea->GetScrollX();
      int y = attachedScrollArea->GetScrollY();
      if( GetScrollBarLayout()->scrollBarType == NDb::UISCROLLBARTYPE_VERTICAL )
        attachedScrollArea->SetScroll(x, GetScrollValue());
      else if( GetScrollBarLayout()->scrollBarType == NDb::UISCROLLBARTYPE_HORIZONTAL )
        attachedScrollArea->SetScroll(GetScrollValue(), y);
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ScrollBar::GetScrollValue()
{
  if ( numPositions <= 1 )
    return 0.0f;
  return float(position) / float(numPositions-1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollBar::SetScrollValue( float x )
{
  x = Clamp( x, 0.0f, 1.0f );
  const int pos = Max( 0, Min( numPositions-1, (int)(x * (numPositions-1)) ) );
  SetScrollPosition( pos );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_CONTROLTYPE( NDb::UIScrollBarLayout, ScrollBar );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
