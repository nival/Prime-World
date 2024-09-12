#include "stdafx.h"

#include "../Scripts/lua.hpp"
#include "CheckBox.h"

namespace UI
{


BEGIN_LUA_TYPEINFO( CheckBox, CommonControl )
  LUA_METHOD( SetSelected )
  LUA_READONLY_PROPERTY( isSelected )
END_LUA_TYPEINFO( CheckBox )



void CheckBox::OnInit()
{
  CommonControl::OnInit();

  buttonStyle = ECBS_None;
  isSelected = false;
}



void CheckBox::OnEnable( bool _enable )
{
  if ( _enable )
  {
    RemoveButtonStyle( ECBS_MouseOver );
  }
  else
  {
    SetButtonStyle( buttonStyle );
  }

  CommonControl::OnEnable( _enable );
}



void CheckBox::OnShow( bool _show )
{
  if ( _show )
  {
    RemoveButtonStyle( ECBS_MouseOver );
  }

  CommonControl::OnShow( _show );
}



void CheckBox::OnInvalidate()
{
  SetButtonStyle( buttonStyle );

  CommonControl::OnInvalidate();
}



void CheckBox::OnMouseOver( bool over, const Point & mouse )
{
  if ( over )
  {
    AddButtonStyle( ECBS_MouseOver );

    if ( IsFullyEnabled() )
      PlayHiliteSound();
  }
  else
  {
    RemoveButtonStyle( ECBS_MouseOver );
  }

  CommonControl::OnMouseOver( over, mouse );
}



bool CheckBox::OnMouseDown( EMButton::Enum mbutton, const Point & point )
{
  if ( IsMouseActionUsable( mbutton ) )
    GetContext()->CaptureMouse( this );

  PlayActivationSound();

  CommonControl::OnMouseDown( mbutton, point );
  return true;
}



bool CheckBox::OnMouseUp( EMButton::Enum mbutton )
{
  if ( IsMouseActionUsable( mbutton ) )
  {
    GetContext()->ReleaseMouse();

    if ( HasButtonStyle( ECBS_MouseOver ) )
    {
      SetSelected( !isSelected );
      EventAction( mbutton );
      return false;
    }
  }

  CommonControl::OnMouseUp( mbutton );
  return true;
}



bool CheckBox::HasButtonStyle( CheckBoxStyle style ) const
{
  return ( buttonStyle & style ) != 0;
}



void CheckBox::AddButtonStyle( CheckBoxStyle style )
{
  SetButtonStyle( (CheckBoxStyle)( buttonStyle | style ) );
}



void CheckBox::RemoveButtonStyle( CheckBoxStyle style )
{
  SetButtonStyle( (CheckBoxStyle)( buttonStyle & ~style ) );
}



void CheckBox::SetButtonStyle( CheckBoxStyle style )
{
  buttonStyle = style;

  NDb::UICheckBoxLayout *pLayout = GetCheckBoxLayout();
  if ( !IsFullyEnabled() )
  {
    bool ok = isSelected ? 
      SetBackgroundMaterial( pLayout->disabledCheckedMaterial ) : 
      SetBackgroundMaterial( pLayout->disabledMaterial );

    if ( !ok )
      SetBackgroundMaterial( pLayout->backgroundMaterial );

    return;
  }

  switch( buttonStyle )
  {
  case ECBS_None:
    SetBackgroundMaterial( pLayout->backgroundMaterial );
    break;
  case ECBS_MouseOver :
    if( !SetBackgroundMaterial( pLayout->highlightMaterial ) )
      SetBackgroundMaterial( pLayout->backgroundMaterial );
    break;
  case ECBS_ButtonChecked :
    SetBackgroundMaterial( pLayout->checkedMaterial );
    break;
  case ECBS_ButtonCheckedAndOver :
    SetBackgroundMaterial( pLayout->highlightCheckedMaterial );
    break;
  }
}



void CheckBox::SetSelected( bool selected )
{
  if ( isSelected == selected )
    return;

  if ( selected )
  {
    AddButtonStyle(ECBS_ButtonChecked);
  }
  else
  {
    RemoveButtonStyle(ECBS_ButtonChecked);
  }

  isSelected = selected;
}



bool CheckBox::GetCustomCursor( string * name, const Point & screenCoords ) const
{
  if ( !name )
    return false;

  if ( GetWindowLayout()->cursors.pushable.empty() )
    return false;

  *name = GetWindowLayout()->cursors.pushable;
  return true;
}


REGISTER_CONTROLTYPE( NDb::UICheckBoxLayout, CheckBox );

} //namespace UI
