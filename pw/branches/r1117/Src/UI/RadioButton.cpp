#include "stdafx.h"

#include "../Scripts/lua.hpp"

#include "RadioButton.h"
#include "RadioPanel.h"

namespace UI
{


BEGIN_LUA_TYPEINFO(RadioButton, CommonControl)
  LUA_METHOD( SetSelected )
  LUA_METHOD( RadioGroup )
  LUA_READONLY_PROPERTY( isSelected )
END_LUA_TYPEINFO( RadioButton )



void RadioButton::OnInit()
{
  CommonControl::OnInit();

  buttonStyle = ERBS_None;
  isSelected = false;
}



void RadioButton::OnEnable( bool _enable )
{
  if ( _enable )
  {
    RemoveButtonStyle( ERBS_MouseOver );
  }
  else
  {
    SetButtonStyle( buttonStyle );
  }

  CommonControl::OnEnable( _enable );
}



void RadioButton::OnShow( bool _show )
{
  if ( _show )
  {
    RemoveButtonStyle(ERBS_Flashing);
    RemoveButtonStyle( ERBS_MouseOver );
  }
  else
  {
    SetButtonStyle( buttonStyle );
  }

  CommonControl::OnShow( _show );
}



void RadioButton::OnInvalidate()
{
  SetButtonStyle( buttonStyle );

  CommonControl::OnInvalidate();
}



void RadioButton::OnMouseOver( bool over, const Point & mouse )
{
  if ( over )
  {
    RemoveButtonStyle( ERBS_Flashing );
    AddButtonStyle( ERBS_MouseOver );

    if ( IsFullyEnabled() )
      PlayHiliteSound();
  }
  else
  {
    RemoveButtonStyle( ERBS_MouseOver );
  }

  CommonControl::OnMouseOver( over, mouse );
}



bool RadioButton::OnMouseDown( EMButton::Enum mbutton, const Point & point )
{
  if ( IsMouseActionUsable( mbutton ) )
    GetContext()->CaptureMouse( this );

  PlayActivationSound();

  CommonControl::OnMouseDown( mbutton, point );
  return true;
}



bool RadioButton::OnMouseUp( EMButton::Enum mbutton )
{
  if ( IsMouseActionUsable( mbutton ) )
  {
    GetContext()->ReleaseMouse();

    if ( HasButtonStyle( ERBS_MouseOver ) )
    {
      SetSelected( true, GetRadioLayout()->group );
      EventAction( mbutton );
      return false;
    }
  }

  CommonControl::OnMouseUp( mbutton );
  return true;
}



bool RadioButton::HasButtonStyle( RadioButtonStyle style ) const
{
  return (buttonStyle & style) != 0;
}



void RadioButton::AddButtonStyle( RadioButtonStyle style )
{
  SetButtonStyle((RadioButtonStyle)(buttonStyle|style));
}



void RadioButton::RemoveButtonStyle( RadioButtonStyle style )
{
  SetButtonStyle((RadioButtonStyle)(buttonStyle&~style));
}



void RadioButton::SetButtonStyle( RadioButtonStyle style )
{
  buttonStyle = style;

  if ( !IsFullyEnabled() )
  {
    if ( isSelected )
    {
      if ( !SetBackgroundMaterial( GetRadioLayout()->disabledSelectedMaterial ) )
        SetBackgroundMaterial( GetRadioLayout()->backgroundMaterial );
    }
    else
    {
      if ( !SetBackgroundMaterial( GetRadioLayout()->disabledMaterial ) )
        SetBackgroundMaterial( GetRadioLayout()->backgroundMaterial );
    }
    return;
  }

  switch(buttonStyle)
  {
  case ERBS_None:
    SetBackgroundMaterial( GetRadioLayout()->backgroundMaterial );
    break;
  case ERBS_MouseOver :
    if( !SetBackgroundMaterial( GetRadioLayout()->highlightMaterial ) )
      SetBackgroundMaterial( GetRadioLayout()->backgroundMaterial );
    break;
  case ERBS_ButtonSelected :
    SetBackgroundMaterial( GetRadioLayout()->selectedMaterial );
    break;
  case ERBS_ButtonSelectedAndOver :
    SetBackgroundMaterial( GetRadioLayout()->selectedMaterial );
    break;
  case ERBS_Flashing :
    SetBackgroundMaterial( GetRadioLayout()->flashedMaterial );
    break;
  }
}



Window* RadioButton::FindRadioPanel()
{
  if ( GetParent() )
  {
    Window *tmp = GetParent();
    while ( tmp && dynamic_cast<RadioPanel*>(tmp) == 0 )
      tmp = tmp->GetParent();

    return tmp;
  }

  return 0;
}



void RadioButton::FindGroupButtons( Window *pFrom, vector<Weak<RadioButton>>& result )
{
  if ( !pFrom )
    return;

  if( RadioButton *pButton = dynamic_cast<RadioButton*>( pFrom ) )
  {
    result.push_back( pButton );
    return;
  }

  int count = pFrom->GetChildrenCount();
  for ( int i = 0; i < count; ++i )
  {
    FindGroupButtons( pFrom->GetChild( i ), result );
  }
}



void RadioButton::DeselectGroupButtons()
{
  if ( Window* pPanel = FindRadioPanel() )
  {
    int group = GetRadioLayout()->group;

    vector<Weak<RadioButton>> buttons;
    FindGroupButtons( pPanel, buttons );
    for ( int i = 0; i < buttons.size(); ++i)
    {
      if ( buttons[i].Get() != this )
        buttons[i]->SetSelected( false, group );
    }
  }
}



void RadioButton::SetSelected( bool selected, int group )
{
  if ( isSelected == selected )
    return;

  isSelected = selected;

  if ( group == GetRadioLayout()->group && selected )
  {
    DeselectGroupButtons();
    RemoveButtonStyle(ERBS_Flashing);
    AddButtonStyle(ERBS_ButtonSelected);
  }
  else
  {
    RemoveButtonStyle(ERBS_ButtonSelected);
  }
}



bool RadioButton::GetCustomCursor( string * name, const Point & screenCoords ) const
{
  if ( !name )
    return false;

  if (HasButtonStyle( ERBS_ButtonSelected ))
  {
    if ( GetWindowLayout()->cursors.normal.empty() )
      return false;
    *name = GetWindowLayout()->cursors.normal;
    return true;
  }

  if ( GetWindowLayout()->cursors.pushable.empty() )
    return false;

  *name = GetWindowLayout()->cursors.pushable;

  return true;
}



REGISTER_CONTROLTYPE( NDb::UIRadioButtonLayout, RadioButton );

}
