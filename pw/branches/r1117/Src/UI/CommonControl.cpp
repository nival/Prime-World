#include "stdafx.h"
#include "CommonControl.h"
#include "Sound/EventScene.h"
#include "Render/MaterialSpec.h"


namespace UI
{


BEGIN_LUA_TYPEINFO( CommonControl, ImageLabel )
  LUA_METHOD( PlayHiliteSound )
  LUA_METHOD( SetActivationBind )
END_LUA_TYPEINFO( CommonControl )



void CommonControl::OnInit()
{
  ImageLabel::OnInit();
}



bool CommonControl::SetBackgroundMaterial( const NDb::BaseUIMaterial * _material )
{
  bool result = ImageLabel::SetBackgroundMaterial( _material );

  if ( !diffuseTextureOverride )
    return result;

  Render::Texture2DRef renderTex = Render::Load2DTextureFromFile( diffuseTextureOverride->textureFileName );
  if ( renderTex )
    SetBackgroundTexture( renderTex );

  return result;
}



void CommonControl::OverrideDiffuseTexture( const NDb::Texture * _texture )
{
  diffuseTextureOverride = _texture;
  Invalidate();
}



bool CommonControl::IsMouseActionUsable( EMButton::Enum button )
{
  switch ( GetCommonCtlLayout()->mouseActions )
  {
    case NDb::UICONTROLMOUSEACTIONS_LEFT:
      return ( button == EMButton::Left );
    
    case NDb::UICONTROLMOUSEACTIONS_RIGHT:
      return ( button == EMButton::Right );

    case NDb::UICONTROLMOUSEACTIONS_BOTH:
      return ( button == EMButton::Left ) || ( button == EMButton::Right );

    default:
      return false;
  }
}



bool CommonControl::OnActivationBind( const string & commandName )
{
  if ( GetCommonCtlLayout()->activationBind == commandName )
    return OnActivationBind();

  return false;
}



void CommonControl::PlayHiliteSound()
{
  NSoundScene::EventStart( GetCommonCtlLayout()->soundHilite );
}



void CommonControl::SetActivationBind( const char * commandName )
{
  GetCommonCtlLayout()->activationBind = commandName;
}

} //namespace UI
