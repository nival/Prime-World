#include "stdafx.h"

#include "../Scripts/lua.hpp"
#include "ImageLabel.h"
#include "SkinStyles.h"
#include "System/NameMap.h"
#include "System/InlineProfiler.h"
#include "Resolution.h"


namespace UI
{

BEGIN_LUA_TYPEINFO( ImageLabel, NameMappedWindow )
  LUA_METHOD( SetCaptionTextA )
  LUA_METHOD( SetCaptionTextW )
  LUA_METHOD( GetCaptionText )

  LUA_METHOD( SetCaptionStyle )
  LUA_METHOD( SetCaptionMargins )

  LUA_METHOD( SetCaptionWordWrap )
  LUA_METHOD( SetCaptionStretch )

  LUA_METHOD( SetCaptionVAlign )
  LUA_METHOD( SetCaptionHAlign )
  LUA_METHOD( SetCaptionOpacity )

  LUA_METHOD( FixHeightToFitCaption )
  LUA_METHOD( FixWidthToFitCaption )
  LUA_METHOD( GetCaptionFitWidth )
  LUA_METHOD( GetCaptionFitHeight )

  LUA_METHOD( SetShapeType )

  LUA_METHOD( SetBackgroundColor )

  LUA_METHOD( SetMaterialCoef3 )
  LUA_METHOD( SetMaterialCoef4 )

  LUA_METHOD( SetBackgroundMaterialByName ) 

  LUA_METHOD_EX( "ForceTextUpdate", ForceTextUpdateLua )

END_LUA_TYPEINFO( ImageLabel )



void ImageLabel::OnInit()
{
  NameMappedWindow::OnInit();

  needUpdate = true;
  forbidSaturation = false;

  SetParametersFromDb();

  const NDb::UIImageLabelLayout * pLayout = GetImageLabelLayout();

  NDb::Ptr<NDb::BaseUIMaterial> shpMaterial;

  switch ( pLayout->shapeType )
  {
  case NDb::IMAGELABELSHAPETYPE_EMPTY:
    // processed dynamically in ::TestOpaque
    break;
  case NDb::IMAGELABELSHAPETYPE_SIMPLEBOX:
    // processed dynamically in ::TestOpaque
    break;
  case NDb::IMAGELABELSHAPETYPE_FROMSHAPESTYLE:
    // &TODO [AZ]
    // shpStyle = pLayout->shapeStyle;
    break;
  case NDb::IMAGELABELSHAPETYPE_FROMBACKGROUNDSTYLE:
    shpMaterial = pLayout->backgroundMaterial;
    break;
  case NDb::IMAGELABELSHAPETYPE_FROMSHAPEORBACKGROUNDSTYLE:
    // &TODO [AZ]
    // shpStyle = pLayout->shapeStyle;
    shpMaterial = pLayout->backgroundMaterial;
    break;
  case NDb::IMAGELABELSHAPETYPE_BYTEXT:
    // processed dynamically in ::TestOpaque
    break;
  default:
    NI_ASSERT( 0, NStr::StrFmt( "Unknown shape type (%d)!", pLayout->shapeType ) );
  }

  if ( shpMaterial )
    SetShapeMaterial( shpMaterial );

  Text.SetNameMapInterface( this );
  Text.SetText( pLayout->captionText.GetText() );
}



void ImageLabel::OnDataChanged()
{
  NameMappedWindow::OnDataChanged();

  SetParametersFromDb();

  NDb::UIImageLabelLayout *pLayout = GetImageLabelLayout();

  //Override caption form db
  pLayout->captionText.DropCache();
  Text.SetText( pLayout->captionText.GetText() );
  ResetNameMapAssociations();

  needUpdate = true;
}



void ImageLabel::OnRefresh( float deltaTime )
{
  NDb::UIImageLabelLayout *pLayout = GetImageLabelLayout();
  if ( needUpdate )
  {
    needUpdate = false;

    Rect imgRect = GetWindowRect();
    //SnapRectToScreenPixels( imgRect, ESnapOptions::RoundOff );
    BackGround.SetDrawRect( imgRect );

    Rect textRect = GetWindowRect();
    SnapRectToScreenPixels( textRect, /*ESnapOptions::RoundOff |*/ ESnapOptions::PreserveSize );
    textRect.x1 += pLayout->textMargins.x1;
    textRect.x2 -= pLayout->textMargins.x2;
    textRect.y1 += pLayout->textMargins.y1;
    textRect.y2 -= pLayout->textMargins.y2;
    Text.SetDrawRect( textRect );

    if ( GetImageLabelLayout()->needCrop )
    {
      textRect.Intersect( GetCropRect() );
      Text.SetCropRect( textRect );
    }
    else
      Text.SetCropRect( GetCropRect() );

    BackGround.SetCropRect( GetCropRect() );
  }

  BackGround.SetMaterialOpacity( GetOpacity() );
  Text.SetOpacity( pLayout->captionOpacity * GetOpacity() / 255.0f );

  Text.Update();

  NameMappedWindow::OnRefresh( deltaTime );
}



void ImageLabel::SetParametersFromDb()
{
  const NDb::UIImageLabelLayout * pLayout = GetImageLabelLayout();

  Text.SetVAlign( pLayout->textVAlign );
  Text.SetHAlign( pLayout->textHAlign );

  Text.EnableRawTextMode( pLayout->rawTextMode );

  SetCaptionWordWrap( pLayout->wordWrap );
  SetCaptionStretch( pLayout->stretchText );

  SetCaptionMargins( 
    pLayout->textMargins.left, pLayout->textMargins.right,
    pLayout->textMargins.top, pLayout->textMargins.bottom );

  SetBackgroundMaterial( pLayout->backgroundMaterial );

  SetCaptionStyle( pLayout->fontStyle.c_str() );
}



void ImageLabel::ForceTextUpdate( ETextUpdateMode::Enum mode )
{
  Text.ForceUpdate( mode );
}



bool ImageLabel::TestOpaque( int x, int y ) const
{
  const NDb::UIImageLabelLayout *pLayout = GetImageLabelLayout();
  if ( pLayout->shapeType == NDb::IMAGELABELSHAPETYPE_EMPTY )
    return false;

  if ( pLayout->shapeType == NDb::IMAGELABELSHAPETYPE_SIMPLEBOX )
    return true;

  if ( pLayout->shapeType == NDb::IMAGELABELSHAPETYPE_BYTEXT )
  {
    //NI_ASSERT( 0, "TODO: Must be implemented. Ask Eugene Germanov" );
    return false;
  }

  return BackGround.HitTest( x,y );
}



bool ImageLabel::SetFontStyle( TextComponent *component, const string &styleName )
{
  const NDb::UIFontStyle *pStyle = UI::SkinStyles::GetFontStyle( styleName );
  if ( !pStyle )
    return false;
  component->SetFontStyle( pStyle );
  return true;
}



void ImageLabel::Render()
{
  NI_PROFILE_FUNCTION
  bool oldValue = Render::GetUIRenderer()->ForbidSaturation( forbidSaturation);

  BackGround.Render();
  RenderBetweenBackgroundAndText();
  Text.Render();

  NameMappedWindow::Render();
  Render::GetUIRenderer()->ForbidSaturation(oldValue);
}



void ImageLabel::SetShapeType( int type )
{
  switch ( type )
  {
  case NDb::IMAGELABELSHAPETYPE_EMPTY:
  case NDb::IMAGELABELSHAPETYPE_SIMPLEBOX:
  case NDb::IMAGELABELSHAPETYPE_BYTEXT:
    GetImageLabelLayout()->shapeType = (NDb::EImageLabelShapeType)type;
    break;
  }
}



bool ImageLabel::SetShapeMaterial( const NDb::BaseUIMaterial * _material )
{
  if ( BackGround.SetShapeMaterial( _material ) )
  {
    GetImageLabelLayout()->shapeType = NDb::IMAGELABELSHAPETYPE_FROMSHAPEORBACKGROUNDSTYLE;
    return true;
  }

  return false;
}



bool ImageLabel::SetCaptionStyle( const char *styleName )
{
  return SetFontStyle( &Text, styleName );
}



bool ImageLabel::SetBackgroundMaterial( const NDb::BaseUIMaterial * _material )
{
  if ( !_material )
    return false;

  BackGround.SetImageMaterial( _material, GetContext() );
  //DebugTrace( "ImageLabel %s SetBackgroundMaterial to \"%s\"", pImageLabelLayout->name.c_str(), _material->GetDBID().GetFileName().c_str() );

  return true;
}



bool ImageLabel::SetBackgroundMaterialByName( const char *_resourceName )
{
  //DebugTrace( "ImageLabel %s SetBackgroundMaterialByName to \"%s\"", pImageLabelLayout->name.c_str(), _resourceName );
  return BackGround.SetImageMaterial( _resourceName, GetContext() );
}



void ImageLabel::SetCaptionMargins( int left, int right, int top, int bottom )
{
  NDb::UIImageLabelLayout *pLayout = GetImageLabelLayout();
  if (  pLayout->textMargins.x1 == left && pLayout->textMargins.x2 == right && 
    pLayout->textMargins.y1 == top && pLayout->textMargins.y2 == bottom )
    return;
  pLayout->textMargins.Set( left, top, right, bottom );
  needUpdate = true;

  Invalidate();
}



void ImageLabel::SetCaptionWordWrap( bool enable )
{
  Text.EnableWordWrap( enable );
}



void ImageLabel::SetCaptionStretch( bool enable )
{
  Text.SetStretchText( enable );
}



void ImageLabel::SetCaptionVAlign( int align )
{
  Text.SetVAlign( (NDb::EUITextVAlign)align );
}



void ImageLabel::SetCaptionHAlign( int align )
{
  Text.SetHAlign( (NDb::EUITextHAlign)align );
}



void ImageLabel::SetCaptionTextW( const wstring & text )
{
  Text.SetText( text );
  ResetNameMapAssociations();
}



string ImageLabel::GetCaptionText()
{    
  return NStr::ToMBCS( Text.GetText() ); 
}



void ImageLabel::SetCaptionTextA( const char *text )
{
  SetCaptionTextW( NStr::ToUnicode( text ) );
}



void ImageLabel::FixHeightToFitCaption( int minHeight, int extraMargin )
{
  ForceUpdate();
  NDb::UIImageLabelLayout *pLayout = GetImageLabelLayout();
  int newHeight = GetCaptionFitHeight() + pLayout->textMargins.y1 + pLayout->textMargins.y2 + extraMargin;
  if ( newHeight < GetSize().y )
  {
    if ( minHeight < 0 )
      return;
    if ( newHeight < minHeight )
      newHeight = minHeight;
  }

  SetSize( -1, newHeight, false );
  ForceUpdate();
}



void ImageLabel::FixWidthToFitCaption( int minWidth, int extraMargin )
{
  ForceUpdate();
  NDb::UIImageLabelLayout *pLayout = GetImageLabelLayout();
  int newWidth = GetCaptionFitWidth() + pLayout->textMargins.x1 + pLayout->textMargins.x2 + extraMargin;
  if ( newWidth < GetSize().x )
  {
    if ( minWidth < 0 )
      return;
    if ( newWidth < minWidth )
      newWidth = minWidth;
  }
  SetSize( newWidth, -1, false );
  ForceUpdate();
}



void ImageLabel::SetBackgroundColor( float r, float g, float b, float a )
{
  BackGround.SetMaterialColor( Render::HDRColor( r, g, b, a ) );
}



void  ImageLabel::SetBackgroundTexture(const Render::Texture2DRef &_pTexture)
{
  BackGround.SetImageTexture(_pTexture);
}



void ImageLabel::SetMaterialCoef3( float c3 )
{
  BackGround.SetMaterialCoef3( c3 );
}



void ImageLabel::SetMaterialCoef4( float c4 )
{
  BackGround.SetMaterialCoef3( c4 );
}



REGISTER_CONTROLTYPE( NDb::UIImageLabelLayout, ImageLabel );

} //namespace UI

NI_DEFINE_REFCOUNT( UI::ImageLabel );
