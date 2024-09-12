#include "StdAfx.h"
#include "FlashFontsRender.h"

#include "FontRender.h"
#include "Resolution.h"
#include "DebugDraw.h"
#include "../Render/MaterialSpec.h"
#include "Flash/GameSWFIntegration/SwfTypes.h"


static bool gDebugDrawFonts = false;
REGISTER_DEV_VAR( "flash_debug_fonts", gDebugDrawFonts, STORAGE_NONE );

const static float FLASH_SCALE_HACK = 0.7f; //HACK: во флэше размер шрифта задается как row step, у нас - как ascent


namespace UI
{

FlashFontInstance::FlashFontInstance( FlashFontsRender * _owner, float _originalHeight, const char * _name, bool _bold, int _italic ) :
owner( _owner ),
material( 0 ),
originalHeight(_originalHeight),
lastScaledHeight(_originalHeight),
originalName(_name),
originalBold(_bold),
originalItalic(_italic)
{
  CheckAlphabet();  

  if ( alphabet )
  {
    alphabet->SetupMetric( metric, 0.0f, 0.0f, SFontRenderTweaks() );

    float heightLeftover = originalHeight - ( metric.ascent + metric.descent );
    if ( heightLeftover > 0 )
      metric.gapAbove = heightLeftover;

    SetupRenderMaterial( false, flash::SWF_RGBA( 0,0,0 ) );
  }
}

FlashFontInstance::~FlashFontInstance()
{
  if ( material )
    delete material;
  material = 0;
}

void FlashFontInstance::CheckAlphabet()
{
  if ( !alphabet.Valid() )
  {
    alphabet = UI::GetFontRenderer()->FindNearestAlphabet( originalName.c_str(), originalHeight, true, originalBold, originalItalic, true );
  }
}

void FlashFontInstance::SetupRenderMaterial( bool _drawBevel, const flash::SWF_RGBA& _color )
{
  NDb::UIFontMaterial fontMaterialDesc;

  fontMaterialDesc.PrimaryColor = Render::HDRColor( 1.f, 1.f, 1.f, 1.f );
  fontMaterialDesc.SecondaryColor = Render::HDRColor( _color.r / 255.f, _color.g / 255.f, _color.b / 255.f, _color.a / 255.f );
  fontMaterialDesc.DrawContour = _drawBevel ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE;
  fontMaterialDesc.renderState.blendMode = NDb::BLENDMODE_LERPBYALPHA;

  fontMaterialDesc.DiffuseMap.samplerState.addressU = NDb::TEXTUREADDRESSTYPE_CLAMP;
  fontMaterialDesc.DiffuseMap.samplerState.addressV = NDb::TEXTUREADDRESSTYPE_CLAMP;
  fontMaterialDesc.DiffuseMap.samplerState.addressW = NDb::TEXTUREADDRESSTYPE_CLAMP;

  fontMaterialDesc.DiffuseMap.samplerState.magFilter = NDb::MAGFILTERTYPE_LINEAR;
  fontMaterialDesc.DiffuseMap.samplerState.minFilter = NDb::MINFILTERTYPE_LINEAR;
  fontMaterialDesc.DiffuseMap.samplerState.mipFilter = NDb::MIPFILTERTYPE_POINT;

  if ( !material )
    material = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( NDb::UIFontMaterial::typeId ) );

  material->FillMaterial( &fontMaterialDesc, 0, false );

  material->SetUseDiffuse( NDb::BOOLEANPIN_PRESENT );
  material->GetDiffuseMap()->SetTexture( UI::GetFontRenderer()->GetFontsTexture() );
}

void FlashFontInstance::SetBevel( bool _drawBevel, const flash::SWF_RGBA& _color )
{
  SetupRenderMaterial( _drawBevel, _color );
}


void FlashFontInstance::RenderGlyph( wchar_t c, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color )
{
  RenderText( &c, 1, _matrix, color, flash::SWF_RECT());
}



void FlashFontInstance::RenderText( const wchar_t * str, unsigned length, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color, const flash::SWF_RECT & cropRect )
{
  NI_VERIFY( owner, "", return );

  flash::SWF_POINT p;
  _matrix.Transform( p, flash::SWF_POINT( 0, 0 ) );

  const Rect & viewport = owner->Viewport();

  p.X = viewport.x1 + p.X * owner->XScale();
  p.Y = viewport.y1 + p.Y * owner->YScale();

  if ( gDebugDrawFonts )
    UI::Debug::AddLine( UI::Point( p.X, p.Y ), UI::Point( p.X, p.Y ), UI::Debug::Color( 255, 0, 0 ) );

  CheckAlphabet();  

  if ( !alphabet.Valid() )
    return;

  UI::Rect cropRectangle;
  
  if (cropRect.GetWidth() != 0 || cropRect.GetHeight() != 0)
  {
    cropRectangle.x1 = viewport.x1 + cropRect.X1* owner->XScale();
    cropRectangle.x2 = viewport.x1 + cropRect.X2 *owner->XScale();
    cropRectangle.y1 = viewport.y1 + cropRect.Y1* owner->YScale();
    cropRectangle.y2 = viewport.y1 + cropRect.Y2*owner->YScale();
  }
 
  CVec2 scale( _matrix.GetXScale(), _matrix.GetYScale() );

  if ( scale.x > 1.f || scale.y > 1.f )
  {
    float maxScale = max( scale.x, scale.y );

    int newScaledHeight = floorf( originalHeight * maxScale );

    if ( newScaledHeight != lastScaledHeight || !scaledAlphabet.Valid() )
    {
      scaledAlphabet = UI::GetFontRenderer()->FindNearestAlphabet( originalName.c_str(), newScaledHeight, true, originalBold, originalItalic, true );
      lastScaledHeight = newScaledHeight;
    }

    scale /= maxScale;

    if ( scaledAlphabet )
      scaledAlphabet->DrawString( str, length, p.X, p.Y, material, Render::Color( color.r, color.g, color.b, color.a ), cropRectangle, SFontRenderTweaks(), scale );
  }
  else
  {
    alphabet->DrawString( str, length, p.X, p.Y, material, Render::Color( color.r, color.g, color.b, color.a ), cropRectangle, SFontRenderTweaks(), scale );
  }

}


float FlashFontInstance::GetStringLength( const wchar_t * text, unsigned length, float maxWidth, unsigned * charsFitIn, float additionalAdvance )
{
  CheckAlphabet();

  if ( !alphabet.Valid() )
    return 0;

  NI_VERIFY( owner, "", return 0 );

  const float xscale = owner->XScale();

  float uiMaxWidth = maxWidth * xscale;
  float uiAddAdv = additionalAdvance * xscale;

  SFontRenderTweaks tweaks;
  tweaks.additionalAdvance = uiAddAdv;
  return alphabet->GetStringLength( text, length, uiMaxWidth, charsFitIn, tweaks ) / xscale;
}


float FlashFontInstance::Twips2Ui( float twips, bool YAxis ) const
{
  NI_ASSERT( owner, "" );
  return twips * ( YAxis ? owner->YScale() : owner->XScale() );
}


float FlashFontInstance::Ui2Twips( float ui, bool YAxis ) const
{
  NI_ASSERT( owner, "" );
  return ui / ( YAxis ? owner->YScale() : owner->XScale() );
}








FlashFontsRender::FlashFontsRender() :
viewport( 0, 0, 100, 100 ),
xscale( 1.0f ), yscale( 1.0f )
{
}


void FlashFontsRender::SetViewport( int x, int y, int width, int height )
{
  viewport.Set( x, y, x + width, y + height );
  CalcScale();
}



void FlashFontsRender::SetMovieRect( float x, float y, float width, float height )
{
  movieRect.Set( x, y, x + width, y + height );
  CalcScale();
}



flash::IFontInstance * FlashFontsRender::FindFont( const char * name, int height, bool bold, int italic, const flash::SFontMetricInfo * metric )
{
  float ascent = height * yscale;

  return new FlashFontInstance( this, ascent, name ? name : "", bold, italic );

//   Weak<IAlphabet> alphabet = UI::GetFontRenderer()->FindNearestAlphabet( name, ascent, true, bold, italic, true );
// 
//   NI_VERIFY( alphabet, NStr::StrFmt( "Font '%s' not found!", name ), return 0 );
// 
//   Strong<FlashFontInstance> & slot = cashe[alphabet];
// 
//   if ( !slot )
//     slot = new FlashFontInstance( this, alphabet, ascent, name ? name : "", bold, italic );
// 
//   return slot;
}



void FlashFontsRender::DebugLine( float x0, float y0, float x1, float y1, const flash::SWF_RGBA & color )
{
  UI::Point p0, p1;
  p0.x = viewport.x1 + ( x0 - movieRect.x1 ) * xscale;
  p0.y = viewport.y1 + ( y0 - movieRect.y1 ) * yscale;
  p1.x = viewport.x1 + ( x1 - movieRect.x1 ) * xscale;
  p1.y = viewport.y1 + ( y1 - movieRect.y1 ) * yscale;

  UI::Debug::AddLine( p0, p1, UI::Debug::Color( color.r, color.g, color.g ) );
}



void FlashFontsRender::CalcScale()
{
  if ( movieRect.IsEmpty() )
    return;

  xscale = (float)viewport.Width() / (float)movieRect.Width();
  yscale = (float)viewport.Height() / (float)movieRect.Height();
}

} //namespace UI
