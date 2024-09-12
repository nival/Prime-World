#include "stdafx.h"

#include "../Scripts/lua.hpp"
#include "Button.h"
#include "../Render/materialspec.h"

namespace UI
{

BEGIN_LUA_TYPEINFO( Button, CommonControl )
END_LUA_TYPEINFO( Button )


void Button::OnInit()
{
  CommonControl::OnInit();

  buttonStyle = EButtonStyle::None;
}



void Button::OnEnable( bool _enable )
{
  if ( !_enable )
    RemoveButtonStyle( EButtonStyle::Flashing | EButtonStyle::MouseDown );
  else
    SetButtonStyle( buttonStyle );

  CommonControl::OnEnable( _enable );
}



void Button::OnShow( bool _show )
{
  if ( !_show )
    RemoveButtonStyle( EButtonStyle::Flashing | EButtonStyle::MouseDown );

  CommonControl::OnShow( _show );
}



void Button::OnInvalidate()
{
  CommonControl::OnInvalidate();

  SetButtonStyle( buttonStyle );
}



void Button::OnMouseOver( bool over, const Point & mouse )
{
  if ( over )
  {
    RemoveButtonStyle( EButtonStyle::Flashing );
    AddButtonStyle( EButtonStyle::MouseOver );
    PlayHiliteSound();
  }
  else
  {
    RemoveButtonStyle( EButtonStyle::MouseOver );
  }

  CommonControl::OnMouseOver( over, mouse );
}



bool Button::OnMouseMove( const Point & mouse )
{
  CommonControl::OnMouseMove( mouse );
  return true;
}



bool Button::OnMouseDown( EMButton::Enum mbutton, const Point & point )
{
  if ( OnGeneralMouseDown( mbutton ) )
    return true;

  CommonControl::OnMouseDown( mbutton, point );
  return true;
}



bool Button::OnGeneralMouseDown( EMButton::Enum mbutton )
{
  if( HasButtonStyle( EButtonStyle::MouseDown ) )
    return true;

  if ( !IsMouseActionUsable( mbutton ) )
    return true;

  activationButton = mbutton;

  SetFocus( true );

  GetContext()->CaptureMouse( this );
  AddButtonStyle(EButtonStyle::MouseDown);

  PlayActivationSound();

  return false;
}



bool Button::OnMouseUp( EMButton::Enum mbutton )
{
  if ( mbutton == activationButton )
  {
    GetContext()->ReleaseMouse();

    if( HasButtonStyle( EButtonStyle::MouseOver ) && HasButtonStyle( EButtonStyle::MouseDown ) )
    {
      EventAction( activationButton );
    }
    RemoveButtonStyle( EButtonStyle::MouseDown );
    return true;
  }

  return CommonControl::OnMouseUp( mbutton );
}



bool Button::OnDoubleClick( EMButton::Enum mbutton, const Point & point )
{
  if ( OnGeneralMouseDown( mbutton ) )
    return true;

  return CommonControl::OnDoubleClick( mbutton, point );
}



bool Button::OnKeyboardFocus( bool gotFocus )
{
  return CommonControl::OnKeyboardFocus( gotFocus );
}



bool Button::OnChar( int ch )
{
  bool proc = CommonControl::OnChar( ch );
  
  const int ESC_CODE = 27;

  if( ch == ESC_CODE )
  {
    RemoveButtonStyle( EButtonStyle::MouseDown );
    proc = true;
  }

  return proc;
}



bool Button::OnActivationBind()
{
  if( !HasButtonStyle( EButtonStyle::MouseDown ) )
  {
    PlayActivationSound();
    EventAction( activationButton );
    return true;
  }

  return false;
}



void Button::OnDataChanged()
{
  CommonControl::OnDataChanged();
}



void Button::Flash( bool enable )
{
  if ( enable )
    SetButtonStyle( EButtonStyle::Flashing );
  else
    RemoveButtonStyle( EButtonStyle::Flashing );
}



void Button::EmulatePress( bool on )
{
  if ( emulatePress != on )
  {
    emulatePress = on;

    UpdateButtonMaterials();
    UpdateButtonMaterialPins();
  }
}



bool Button::HasButtonStyle( unsigned style ) const
{
  return buttonStyle & style;
}



void Button::AddButtonStyle( unsigned style )
{
  SetButtonStyle( buttonStyle | style );
}



void Button::RemoveButtonStyle( unsigned style )
{
  SetButtonStyle( buttonStyle & ~style );
}



void Button::SetButtonStyle( unsigned style )
{
  buttonStyle = style;

  UpdateButtonMaterials();
  UpdateButtonMaterialPins();
}



bool Button::SetBackgroundMaterial( const NDb::BaseUIMaterial * _material )
{
  if ( CommonControl::SetBackgroundMaterial( _material ) )
  {
    if ( currentTexture )
      CommonControl::SetBackgroundTexture( currentTexture );

    return true;
  }

  return false;
}



bool Button::SetBackgroundMaterialByName( const char *_resourceName )
{
  if ( CommonControl::SetBackgroundMaterialByName( _resourceName ) )
  {
    if ( currentTexture )
      CommonControl::SetBackgroundTexture( currentTexture );

    return true;
  }

  return false;
}



void Button::SetBackgroundTexture( const Render::Texture2DRef &_pTexture )
{
  currentTexture = _pTexture;
  SetButtonStyle( buttonStyle );
}



bool Button::GetCustomCursor( string * name, const Point & screenCoords ) const
{
  if ( !name )
    return false;

  if (HasButtonStyle( EButtonStyle::MouseDown ))
  {
    if ( GetWindowLayout()->cursors.pushing.empty() )
      return false;
    *name = GetWindowLayout()->cursors.pushing;
    return true;
  }

  if ( GetWindowLayout()->cursors.pushable.empty() )
    return false;

  *name = GetWindowLayout()->cursors.pushable;
  return true;
}



void Button::UpdateButtonMaterials()
{
  const NDb::UIButtonLayout * pLayout = GetButtonLayout();

  if ( pLayout->viewMode != NDb::UIBUTTONVIEWMODE_BYMATERIALS )
    return;

  if ( !IsFullyEnabled() )
  {
    SetBackgroundMaterial( pLayout->disabledMaterial ? pLayout->disabledMaterial : pLayout->backgroundMaterial );
    return;
  }

  bool drawPressed = ( buttonStyle & EButtonStyle::MouseDown ) && ( buttonStyle & EButtonStyle::MouseOver );
  drawPressed = drawPressed || emulatePress;

  if ( drawPressed )
  {
    SetBackgroundMaterial( pLayout->pushedMaterial );
  }
  else if ( ( buttonStyle & EButtonStyle::MouseDown ) || ( buttonStyle & EButtonStyle::MouseOver ) )
  {
    if ( pLayout->highlightMaterial )
      SetBackgroundMaterial( pLayout->highlightMaterial );
    else
      SetBackgroundMaterial( pLayout->backgroundMaterial );
  }
  else if ( buttonStyle & EButtonStyle::Flashing )
  {
    SetBackgroundMaterial( pLayout->flashedMaterial );
  }
  else
  {
    SetBackgroundMaterial( pLayout->backgroundMaterial );
  }
}



void Button::UpdateButtonMaterialPins()
{
  const NDb::UIButtonLayout * pLayout = GetButtonLayout();

  const bool noDisablePin = ( pLayout->viewMode == NDb::UIBUTTONVIEWMODE_BYPINSWITHOUTDISABLEPIN );
  if ( ( pLayout->viewMode != NDb::UIBUTTONVIEWMODE_BYPINS ) && !noDisablePin )
    return;

  Render::BaseMaterial * material = GetRenderMaterial().GetRenderMaterial();
  if ( !material )
    return;

  //FIXME: Very unclear BUT right Pressed vs Hilited logic
  const bool enabled = IsFullyEnabled();
  const bool pressed = enabled && ( emulatePress || ( ( buttonStyle & EButtonStyle::MouseDown ) && ( buttonStyle & EButtonStyle::MouseOver ) ) );
  const bool hilited = enabled && !pressed && ( buttonStyle & EButtonStyle::MouseDown ) || ( buttonStyle & EButtonStyle::MouseOver ) || ( buttonStyle & EButtonStyle::Flashing );

  if ( !noDisablePin )
    material->SetDisablePin( enabled ? NDb::BOOLEANPIN_NONE : NDb::BOOLEANPIN_PRESENT );

  material->SetPressedPin( pressed ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE );
  material->SetHighlightPin( hilited ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE );

  //Trick to update some material params
  SetBackgroundMaterial( pLayout->backgroundMaterial );
}



REGISTER_CONTROLTYPE( NDb::UIButtonLayout, Button );

} //namespace UI

NI_DEFINE_REFCOUNT( UI::Button );
