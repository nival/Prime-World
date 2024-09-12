#include "stdafx.h"

#include "FontStyle.h"

#include "../Render/MaterialSpec.h"

namespace UI
{

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

FontStyle::FontStyle() :
uiFontStyle( this, &FontStyle::OnStyleResourceChanged ),
renderMaterial( 0 ),
defaultSize( 20 ),
isModified( false )
{
}



FontStyle::FontStyle( const NDb::UIFontStyle* _uiFontStyle ) :
uiFontStyle( this, &FontStyle::OnStyleResourceChanged ),
renderMaterial( 0 ),
defaultSize( 20 ),
isModified( false )
{
  SetStyle( _uiFontStyle );
}



FontStyle::~FontStyle()
{
  if ( renderMaterial )
    delete renderMaterial;
  renderMaterial = 0;
}



void FontStyle::OnStyleResourceChanged( const NDb::DBID & )
{
  SetupMaterial();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FontStyle::SetStyle( const NDb::UIFontStyle* _uiFontStyle )
{
  uiFontStyle = _uiFontStyle;
  SetupMaterial();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FontStyle::SetDefaultSize( int size )
{
  NI_ASSERT( !uiFontStyle, "" );
  defaultSize = size;
  SetupMaterial();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IAlphabet * FontStyle::GetAlphabet() 
{ 
  if ( alphabet.Valid() )
    return alphabet;

  SetupMaterial();

  return alphabet; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FontStyle::SetupMaterial()
{
  if ( renderMaterial )
    delete renderMaterial;
  renderMaterial = 0;

  NDb::UIFontMaterial fontMaterialDesc;

  if ( uiFontStyle )
  {
    fontMaterialDesc.PrimaryColor = uiFontStyle->primaryColor;
    fontMaterialDesc.SecondaryColor = uiFontStyle->secondaryColor;
    fontMaterialDesc.DrawContour = uiFontStyle->drawContour ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE;
    fontMaterialDesc.renderState = uiFontStyle->renderState;
  }
  else
  {
    fontMaterialDesc.PrimaryColor = Render::HDRColor( 1.f, 1.f, 1.f, 1.f );
    fontMaterialDesc.SecondaryColor = Render::HDRColor( 0.f, 0.f, 0.f, 1.f );
    fontMaterialDesc.DrawContour = NDb::BOOLEANPIN_NONE;
    fontMaterialDesc.renderState.blendMode = NDb::BLENDMODE_LERPBYALPHA;
  }

  fontMaterialDesc.DiffuseMap.samplerState.addressU = NDb::TEXTUREADDRESSTYPE_CLAMP;
  fontMaterialDesc.DiffuseMap.samplerState.addressV = NDb::TEXTUREADDRESSTYPE_CLAMP;
  fontMaterialDesc.DiffuseMap.samplerState.addressW = NDb::TEXTUREADDRESSTYPE_CLAMP;

  fontMaterialDesc.DiffuseMap.samplerState.magFilter = NDb::MAGFILTERTYPE_LINEAR;
  fontMaterialDesc.DiffuseMap.samplerState.minFilter = NDb::MINFILTERTYPE_LINEAR;
  fontMaterialDesc.DiffuseMap.samplerState.mipFilter = NDb::MIPFILTERTYPE_POINT;

  renderMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( NDb::UIFontMaterial::typeId ) );
  renderMaterial->FillMaterial( &fontMaterialDesc, 0, false );

  renderMaterial->SetUseDiffuse( NDb::BOOLEANPIN_PRESENT );
  renderMaterial->GetDiffuseMap()->SetTexture( GetFontRenderer()->GetFontsTexture() );

  //Font metrics
  if ( uiFontStyle )
    alphabet = FindAlphabet( uiFontStyle );
  else
    alphabet = GetFontRenderer()->FindNearestAlphabet( 0, defaultSize, false, false, false, false );
  NI_ASSERT( alphabet, "" );

  float addLineGap = uiFontStyle ? uiFontStyle->lineGap : 1.0f;
  SFontRenderTweaks tweaks;
  tweaks.additionalAdvance = uiFontStyle ? uiFontStyle->additionalAdvance : 0.0f;
  tweaks.spaceScale = uiFontStyle ? uiFontStyle->spaceScale : 1.0f;
  alphabet->SetupMetric( metric, 0.5f * addLineGap, 0.5f * addLineGap, tweaks );

  isModified = true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IAlphabet * FontStyle::FindAlphabet( const NDb::UIFontStyle * dbStyle )
{
  NI_ASSERT( dbStyle, "" );

  bool systemFont = !dbStyle->fontFamily.empty();
  const char * ttfFileName = systemFont ? dbStyle->fontFamily.c_str() : dbStyle->ttfFileName.c_str();
  int size = dbStyle->fontSize;
  bool bold = dbStyle->bold;
  bool italic = dbStyle->italic;

  return GetFontRenderer()->FindNearestAlphabet( ttfFileName, size, systemFont, bold, italic, false );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FontStyle::DrawString( const wchar_t * text, unsigned length, float x, float y, const Render::Color & color, const Rect & cropRect )
{
  //we've got a _baseline_ offset as 'y' here
  //So we have to offset text to account 'lineGap'

  if ( !alphabet.Valid() )
    SetupMaterial();

  NI_VERIFY( alphabet, "", return );
  alphabet->DrawString( text, length, x, y + metric.gapAbove, renderMaterial, color, cropRect, metric.tweaks, CVec2( 1.f, 1.f ) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float FontStyle::GetStringLength( const wchar_t * text, unsigned length )
{
  if ( !alphabet.Valid() )
    SetupMaterial();

  NI_VERIFY( alphabet, "", return 0.0f );
  return alphabet->GetStringLength( text, length, 0, 0, metric.tweaks );
}

/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NMarkup::TOffset FontStyle::GetTextBounds( NMarkup::SBounds * bounds, const NMarkup::TChar * text, NMarkup::TOffset length, NMarkup::TUnit maxWidth ) const
{
  
}
*/
} // namespace UI
