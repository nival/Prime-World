#include "TamarinPCH.h"
#include "TextContainer.h"
#include "FontsDict.h"
#include "FontTags.h"
#include "FontsRenderInterface.h"

NI_DEFINE_REFCOUNT( flash::TextContainer );


namespace flash
{

TextContainerStyle::TextContainerStyle( TextContainer * _owner, IFontInstance * font ) :
owner( _owner ),
fontInstance( font )
{
}


NMarkup::TOffset TextContainerStyle::GetTextBounds( NMarkup::SBounds * bounds, const NMarkup::TChar * text, NMarkup::TOffset length, NMarkup::TUnit maxWidth ) const
{
  unsigned charsFitInMaxWidth = 0;
  float uiMaxWidth = maxWidth;
  bounds->width = fontInstance->GetStringLength( text, length, uiMaxWidth, &charsFitInMaxWidth, 0.0f );

  bounds->ascent = fontInstance->Ascent();
  bounds->descent = fontInstance->Descent();
  bounds->gapAbove = fontInstance->GapAbove();
  bounds->gapUnder = fontInstance->GapUnder();

  NI_ASSERT( bounds->ascent > 0, "" );
  NI_ASSERT( bounds->descent >= 0, "" );

  return charsFitInMaxWidth;
}



void TextContainerStyle::GetDefaultBounds( NMarkup::SBounds * bounds ) const
{
  bounds->ascent = fontInstance->Ascent();
  bounds->descent = fontInstance->Descent();
  bounds->gapAbove = fontInstance->GapAbove();
  bounds->gapUnder = fontInstance->GapUnder();
}



NMarkup::TUnit TextContainerStyle::DefaultGlyphWidth() const
{
  return fontInstance->DefaultGlyphWidth();
}


NMarkup::TUnit TextContainerStyle::DefaultLineGap() const
{
  return fontInstance->Height();
}


NMarkup::TUnit TextContainerStyle::VisualHeight() const
{
  return fontInstance->Ascent();
}


void TextContainerStyle::RenderText( const NMarkup::SBounds & bounds, const NMarkup::TPoint & offset, const NMarkup::TChar * text, NMarkup::TOffset length )
{
  NI_ASSERT( fontInstance && owner,  "" );

  const SWF_MATRIX & worldMatrix = owner->CurrentMatrix();

  flash::SWF_MATRIX offsMtx;
  offsMtx.ConcatenateTranslation( offset.x, offset.y );

  flash::SWF_MATRIX mtx;
  mtx.Concatenate( worldMatrix, offsMtx );

  fontInstance->RenderText( text, length, mtx, owner->DefaultColor(), owner->GetCropRect());
}





TextContainer::TextContainer()
{
}



TextContainer::TextContainer( FontsDictionary * dict, IFontRender * _fontRender ) 
: fontDictionary( dict )
, fontRender( _fontRender )
{
  markup.SetDefaultParams( NMarkup::EVerticalAlign::Top, NMarkup::EJustify::Left, true, false );
}



void TextContainer::CreateDefaultFont( int height )
{
  Strong<IFontInstance> inst = fontRender->FindFont( 0, height, false, false, 0 );
  NI_ASSERT( inst, "" );
  defaultFont = new TextContainerStyle( this, inst );
}



void TextContainer::SetDefaultFont( SwfFont * swfFont, int height )
{
  Strong<IFontInstance> inst = swfFont->GetRenderable( fontRender, height );
  if ( inst )
    defaultFont = new TextContainerStyle( this, inst );
}



void TextContainer::ParseText( const wchar_t * text, float _fieldWidth, float _fieldHeight )
{

  EnableNameMapRegistration( true );
  markup.Process( text, this, NMarkup::TPoint( _fieldWidth, _fieldHeight ), this );
  EnableNameMapRegistration( false );
}



void TextContainer::Render( const SWF_MATRIX & matrix, const SWF_RGBA & _defaultColor, const SWF_RECT & _cropRect )
{
  worldMatrix = matrix;
  defaultColor = _defaultColor;

  cropRect = _cropRect;

  markup.Render();

  worldMatrix.Identity();
  defaultColor = SWF_RGBA();
}



NMarkup::IStyle * TextContainer::GetStyle( const NMarkup::TChar * style )
{
  NI_ASSERT( defaultFont, "" );

  if ( !style )
    return defaultFont;

  SwfFont * swfFont = fontDictionary->GetFontByName( NStr::ToMBCS( style ).c_str() );
  if ( !swfFont )
    return defaultFont;

  //FIXME: пока мы не можем узнать нужную высоту шрифта; возьмем из дефолтового
  const int height = defaultFont->Renderable()->Height();

  IFontInstance * inst = swfFont->GetRenderable( fontRender, height );
  if ( !inst )
    return defaultFont;

  TFontsCache::iterator it = fontsCache.find( inst );
  if ( it == fontsCache.end() )
  {
    Strong<TextContainerStyle> & slot = fontsCache[inst];
    slot = new TextContainerStyle( this, inst );
    return slot;
  }

  return it->second;
}



NMarkup::IImage * TextContainer::CreateImage( NMarkup::TPoint * size, const NMarkup::TChar * image )
{
  return 0; //Upsupported for flash
}

} //namespace flash
