#pragma once

#include "../Render/texture.h"
#include "TextMarkupCommon.h"
#include "Defines.h"

namespace Render
{
  class BaseMaterial;
}

//TODO: rename namespace 'UI' to 'fonts' or 'fontRender'
namespace UI
{

const static int FONT_TEXTURE_SIZE = 2048;

struct Glyph
{
  float u1, v1, u2, v2;
  float width;
  float height;
  float offsetW;
  float offsetH;
  float A, B, C;
};



struct SFontRenderTweaks
{
  float   additionalAdvance;
  float   spaceScale;

  SFontRenderTweaks() : additionalAdvance( 0 ), spaceScale( 1.0f ) {}
};



struct SFontMetric
{
  float ascent;
  float descent; //P o s i t i v e   value

  float gapAbove, gapUnder;

  SFontRenderTweaks tweaks;

  float defaultGlyphWidth;

  // Row step:
  float RowStep() const { return ascent + descent + gapAbove + gapUnder; }

  SFontMetric() : 
  ascent( 0 ), descent( 0 ),
  gapAbove( 0 ), gapUnder( 0 ),
  defaultGlyphWidth( 0 )
  {}
};



_interface IAlphabet : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IAlphabet, IBaseInterfaceST )

  virtual const Glyph& GetGlyph( wchar_t symbol ) = 0;
  virtual void    SetupMetric( SFontMetric & metric, float gapAbove, float gapUnder, const SFontRenderTweaks & tweaks ) const = 0;
	virtual float   GetStringLength( const wchar_t *text, unsigned length, float maxWidth, unsigned * charsFitIn, const SFontRenderTweaks & tweaks ) = 0;
	virtual void    DrawString( const wchar_t *text, unsigned length, float x, float y, Render::BaseMaterial * fontMaterial, const Render::Color & color, const Rect & cropRect, const SFontRenderTweaks & tweaks, const CVec2& _scale ) = 0;

  //Obsolette function!
  virtual float   GetHeightScale() const = 0; //FIXME: Remove this function; it only used in some broken debug render
};



_interface IFontStyle : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IFontStyle, IBaseInterfaceST )

  virtual const NDb::UIFontStyle * GetStyle() const = 0;
  virtual Render::BaseMaterial * GetMaterial() = 0;
  virtual bool CheckModified() = 0; //Resets modification flag
  
  virtual void DrawString( const wchar_t * text, unsigned length, float x, float y, const Render::Color & color, const Rect & cropRect ) = 0;
  virtual float GetStringLength( const wchar_t * text, unsigned length ) = 0;

  virtual IAlphabet * GetAlphabet() = 0;

  virtual const SFontMetric & GetMetric() const = 0;
};



_interface IFontRenderer : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IFontRenderer, IBaseInterfaceST )

  virtual void Initialize() = 0;
  virtual void Release() = 0;

  virtual Render::Texture2DRef & GetFontsTexture() = 0;

  virtual IAlphabet * FindNearestAlphabet( const char * ttfFileName, int size, bool systemFont, bool bold, bool italic, bool forFlash ) = 0;

  virtual const Rect & GetNoCropRect() = 0;

  virtual IFontStyle* GetFontStyle( const NDb::UIFontStyle* _style ) = 0; 
  virtual IFontStyle* GetDebugFontStyle( int size ) = 0; 
};


// @AZ@TODO get rid of singleton nature
IFontRenderer* GetFontRenderer();

} // namespace UI
