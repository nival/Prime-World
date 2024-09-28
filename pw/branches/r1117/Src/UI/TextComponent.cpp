#include "stdafx.h"

#include "TextComponent.h"
#include "Root.h"
#include "SkinStyles.h"
#include "Resolution.h"
#include "System/InlineProfiler.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

NMarkup::TOffset TextComponentStyle::GetTextBounds( NMarkup::SBounds * bounds, const NMarkup::TChar * text, NMarkup::TOffset length, NMarkup::TUnit maxWidth ) const
{
  NI_ASSERT( style, "" );
  IAlphabet * alpha = style->GetAlphabet();
  NI_VERIFY( alpha, "", return 0 );

  const SFontMetric & metric = style->GetMetric();

  unsigned charsFitInMaxWidth = 0;
  bounds->width = alpha->GetStringLength( text, length, maxWidth, &charsFitInMaxWidth, metric.tweaks );
  bounds->ascent = metric.ascent;
  bounds->descent = metric.descent;
  bounds->gapAbove = metric.gapAbove;
  bounds->gapUnder = metric.gapUnder;

  NI_ASSERT( bounds->ascent > 0, "" );
  NI_ASSERT( bounds->descent >= 0, "" );

  return charsFitInMaxWidth;
}



void TextComponentStyle::GetDefaultBounds( NMarkup::SBounds * bounds ) const
{
  NI_ASSERT( style, "" );
  const SFontMetric & metric = style->GetMetric();

  bounds->ascent = metric.ascent;
  bounds->descent = metric.descent;
  bounds->gapAbove = metric.gapAbove;
  bounds->gapUnder = metric.gapUnder;
}



NMarkup::TUnit TextComponentStyle::DefaultGlyphWidth() const
{
  NI_ASSERT( style, "" );

  const float scale = style->GetStyle() ? style->GetStyle()->spaceScale : 1.0f;
  return scale * style->GetMetric().defaultGlyphWidth;
}



NMarkup::TUnit TextComponentStyle::DefaultLineGap() const
{
  NI_ASSERT( style, "" );
  return style->GetMetric().RowStep();
}



NMarkup::TUnit TextComponentStyle::VisualHeight() const
{
  NI_ASSERT( style, "" );
  return style->GetMetric().ascent;
}



void TextComponentStyle::RenderText( const NMarkup::SBounds & bounds, const NMarkup::TPoint & offset, const NMarkup::TChar * text, NMarkup::TOffset length )
{
  NI_ASSERT( owner && style, "" );
  const NDb::UIFontStyle * dbStyle = style->GetStyle();

  Render::Color color;
  if ( !dbStyle )
  {
    const Render::Color & clr = owner->DefaultColor();
    color = Render::Color( clr.R, clr.G, clr.B, Clamp( (int)( owner->Opacity() * 255 ), 0, 255 ) );
  }
  else
  {
    color.R = dbStyle->primaryColor.R * 255;
    color.G = dbStyle->primaryColor.G * 255;
    color.B = dbStyle->primaryColor.B * 255;
    color.A = Clamp( (int)(dbStyle->primaryColor.A * owner->Opacity() * 255), 0, 255 );
  }

  const Rect & drawRect = owner->GetDrawRect();
  const float x = drawRect.left + offset.x;
  const float y = drawRect.top + offset.y;

  if ( style )
    style->DrawString( text, length, x, y, color, owner->GetCropRect() );
}



void TextComponentImage::RenderImage( const NMarkup::TPoint & offset, const NMarkup::TPoint & size )
{
  NI_ASSERT( owner, "" );

  if ( owner->NeedUpdateImages() )
  {
    int intOpa = Clamp( (int)(owner->Opacity() * 255), 0, 255 );

    const Rect & drawRect = owner->GetDrawRect();
    const float x = drawRect.left + offset.x;
    const float y = drawRect.top + offset.y;
    Rect rect( x, y, x + size.x, y + size.y );
    SnapRectToScreenPixels( rect );
    SetDrawRect( rect );
    SetCropRect( owner->GetCropRect() );
    SetMaterialOpacity( intOpa );
    SetRenderable( true );
  }

  Render();
}







#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

TextComponent::TextComponent() :
dbDefaultFontStyle( this, &TextComponent::OnStyleResourceChanged ),
wordWrap( true ), stretchText( false ), rawTextMode( false ),
vAlign( NDb::UITEXTVALIGN_TOP ), hAlign( NDb::UITEXTHALIGN_LEFT ),
drawRect(0,0,0,0), cropRect(0,0,0,0),
opacity(1),
updateMode( ETextUpdateMode::Full ), needUpdateImages( true ),
cursorWidth(0), cursorPos(-1)
{
}



void TextComponent::SetText( const wstring & _text )
{
  if ( _text != text )
  {
    text = _text;
    ForceUpdate( ETextUpdateMode::Full );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextComponent::ForceUpdate( ETextUpdateMode::Enum mode )
{
  updateMode = Max( updateMode, mode );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextComponent::SetFontStyle( const NDb::UIFontStyle * _pFontStyle )
{
  if ( dbDefaultFontStyle != _pFontStyle )
  {
    dbDefaultFontStyle = _pFontStyle;
    ForceUpdate( ETextUpdateMode::KeepNamemaps );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextComponent::OverrideFontStyle( IFontStyle * style )
{
  if ( defaultFontStyleOverride.Get() == style )
    return;

  defaultFontStyleOverride.Set( this, style );
  ForceUpdate( ETextUpdateMode::KeepNamemaps );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextComponent::EnableRawTextMode( bool enable )
{
  ChangeParam( rawTextMode, enable );
  markup.CondenseWhite( !enable );
  markup.EnableTags( !enable );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextComponent::SetupParams()
{
  Point drawSize = drawRect.GetSize();

  NMarkup::EVerticalAlign::Enum align = NMarkup::EVerticalAlign::Top;
  NMarkup::EJustify::Enum just = NMarkup::EJustify::Left;

  switch( vAlign )
  {
    case NDb::UITEXTVALIGN_TOP:
      align = NMarkup::EVerticalAlign::Top;
      break;
    case NDb::UITEXTVALIGN_CENTER:
      align = NMarkup::EVerticalAlign::Center;
      break;
    case NDb::UITEXTVALIGN_BOTTOM:
      align = NMarkup::EVerticalAlign::Bottom;
      break;
  }

  switch( hAlign )
  {
    case NDb::UITEXTHALIGN_LEFT:
      just = NMarkup::EJustify::Left;
      break;
    case NDb::UITEXTHALIGN_CENTER:
      just = NMarkup::EJustify::Center;
      break;
    case NDb::UITEXTHALIGN_RIGHT:
      just = NMarkup::EJustify::Right;
      break;
  }

  markup.SetDefaultParams( align, just, wordWrap, stretchText );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextComponent::Update()
{
  NI_PROFILE_FUNCTION

  if ( updateMode == ETextUpdateMode::None )
    return;

  if ( !dbDefaultFontStyle.IsEmpty() )
    dbDefaultFontStyle = UI::SkinStyles::GetFontStyle( dbDefaultFontStyle->styleName );

  SetupParams();

  needUpdateImages = true;
  images.clear();
  fontStyles.clear();

  NMarkup::TPoint drawSize( drawRect.GetSize().x, drawRect.GetSize().y );

  if ( updateMode == ETextUpdateMode::Full )
    EnableNameMapRegistration( true );

  wchar_t z = 0;
  const wchar_t * txt = text.empty() ? &z : &text[0];
  markup.Process( txt, this, drawSize, this );

  updateMode = ETextUpdateMode::None;
  EnableNameMapRegistration( false );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TextComponent::GetCursorInfoImpl( SCursorInfo * info, int localCursorPos )
{
  if ( localCursorPos < 0 )
    return false;

  Update();

  NMarkup::TPoint cursorOffset;
  NMarkup::TPoint cursorSize;
  int cursorLine = 0;
  if( markup.GetCharInfo( localCursorPos, &cursorOffset, &cursorSize, &cursorLine ) )
  {
    info->x = cursorOffset.x + cursorSize.x;
    info->y = cursorOffset.y;
    info->h = cursorSize.y;
    info->line = cursorLine;
    return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TextComponent::GetCursorInfo( TextComponent::SCursorInfo * info )
{
  return GetCursorInfoImpl( info, cursorPos );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TextComponent::FindCursorPosition( const SCursorInfo & fromInfo, EFindCursorMode mode )
{
  Update();

  bool found = false;
  int bestPos = cursorPos;
  int bestDelta = 0;
  for ( int i = 0; i <= text.size(); ++i )
  {
    SCursorInfo info;
    if( !GetCursorInfoImpl( &info, i ) )
      continue;

    if ( mode == FINDCURSOR_MOVE_UP || mode == FINDCURSOR_MOVE_DOWN )
    {
      if ( info.line == fromInfo.line + (mode == FINDCURSOR_MOVE_DOWN ? 1 : -1) )
      {
        const int delta = abs( info.x - fromInfo.x );
        if ( !found || bestDelta > delta )
        {
          found = true;
          bestPos = i;
          bestDelta = delta;
        }
      }
    }
    else if ( mode == FINDCURSOR_MOVE_TO_ROW_BEGIN )
    {
      if ( info.line == fromInfo.line && ( !found || i < bestPos ) )
      {
        found = true;
        bestPos = i;
      }
    }
    else if ( mode == FINDCURSOR_MOVE_TO_ROW_END )
    {
      if ( info.line == fromInfo.line && ( !found || i > bestPos ) )
      {
        found = true;
        bestPos = i;
      }
    }
    else if ( mode == FINDCURSOR_BY_XY )
    {
      const int dx = abs( info.x - fromInfo.x );
      const int dy = abs( info.y + info.h / 2 - fromInfo.y );
      const int delta = dx * dx + dy * dy;
      if ( !found || delta < bestDelta )
      {
        found = true;
        bestPos = i;
        bestDelta = delta;
      }
    }
  }

  const int result = bestPos;
  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextComponent::Render() // IREF
{
  NI_PROFILE_FUNCTION

  // Check if fully cropped
  Rect rect = drawRect;
  rect.Intersect( cropRect );
  if ( rect.IsEmpty() )
    return;

  // Update if needed
  Update();

  markup.Render();

  if ( cursorPos >= 0 )
  {
    SCursorInfo cursorInfo;
    GetCursorInfo( &cursorInfo );
    cursor.SetRenderable( true );
    cursor.SetDrawRect( Rect( drawRect.left + cursorInfo.x, drawRect.top + cursorInfo.y, drawRect.left + cursorInfo.x + cursorWidth, drawRect.top + cursorInfo.y + cursorInfo.h ) );
    cursor.SetMaterialOpacity( opacity * 255 );
    cursor.SetCropRect( cropRect );
    cursor.Render();
  }
  else
  {
    cursor.SetRenderable( false );
  }

  needUpdateImages = false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NMarkup::IStyle * TextComponent::GetStyle( const NMarkup::TChar * style )
{
  if ( !style && defaultFontStyleOverride.Get() )
    return &defaultFontStyleOverride;

  const NDb::UIFontStyle * dbStyle = style ? UI::SkinStyles::GetFontStyle( NStr::ToMBCS( style ) ) : 0;

  if( !dbStyle )
    dbStyle = dbDefaultFontStyle;

  Strong<UI::IFontStyle> uiStyle = GetFontRenderer()->GetFontStyle( dbStyle );

  TFontStyles::iterator it = fontStyles.find( uiStyle );
  if ( it != fontStyles.end() )
    return &it->second;

  TextComponentStyle & result = fontStyles[uiStyle];
  result.Set( this, uiStyle );
  return &result;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NMarkup::IImage * TextComponent::CreateImage( NMarkup::TPoint * size, const NMarkup::TChar * image )
{
  needUpdateImages = true;

	images.push_back();
  TextComponentImage * pImage = &images.back();
  pImage->SetOwner( this );

  const NDb::BaseUIMaterial * pMaterial = UI::SkinStyles::GetImageMaterial( NStr::ToMBCS( image ) );

  //Напишем ошибку, если такой картинки не нашлось
  if( !pMaterial )
  {
    wstring tmp = text;
    const size_t MAX_LEN = 128;
    if( tmp.length() > MAX_LEN )
    {
      tmp.resize(MAX_LEN, L' ' );
      tmp += L"...";
    }

    NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Text-image '%s' not found! Source text was: '%s'", NStr::ToMBCS( image ).c_str(), NStr::ToMBCS( tmp ).c_str() ) );
    return 0;
  }

	pImage->SetImageMaterial( pMaterial, logicAsTexturePool );

  if( pMaterial )
  {
    size->x = (NMarkup::TUnit)pMaterial->imageSize.x;
    size->y = (NMarkup::TUnit)pMaterial->imageSize.y;
  }
  else
    size->x = size->y = 0;

  return pImage;
}

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
