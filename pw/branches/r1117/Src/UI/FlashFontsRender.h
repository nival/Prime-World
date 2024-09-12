#ifndef FLASHFONTSRENDER_H_INCLUDED
#define FLASHFONTSRENDER_H_INCLUDED

#include "Flash/GameSWFIntegration/FontsRenderInterface.h"
#include "Defines.h"
#include "FontRender.h"

namespace Render
{
  class BaseMaterial;
}


namespace UI
{

_interface IAlphabet;

class FlashFontsRender;


class FlashFontInstance : public flash::IFontInstance, public BaseObjectST
{
   NI_DECLARE_REFCOUNT_CLASS_2( FlashFontInstance, flash::IFontInstance, BaseObjectST )

public:
  FlashFontInstance( FlashFontsRender * _owner, float _originalHeight, const char * _name, bool _bold, int _italic );
  ~FlashFontInstance();

private:
  //IFontInstance
  virtual void    RenderGlyph( wchar_t c, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color );
  virtual void    RenderText( const wchar_t * text, unsigned length, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color, const flash::SWF_RECT & cropRect  );
  virtual float   GetStringLength( const wchar_t * text, unsigned length, float maxWidth, unsigned * charsFitIn, float additionalAdvance );
  virtual float   Height() const { return Ui2Twips( metric.RowStep() ); }
  virtual float   Ascent() const {  return Ui2Twips( metric.ascent ); }
  virtual float   Descent() const { return Ui2Twips( metric.descent ); }
  virtual float   GapAbove() const { return Ui2Twips( metric.gapAbove ); }
  virtual float   GapUnder() const { return Ui2Twips( metric.gapUnder ); }
  virtual float   DefaultGlyphWidth() const { return Ui2Twips( metric.defaultGlyphWidth, false ); }
  virtual void    SetBevel( bool _drawBevel, const flash::SWF_RGBA& _color );

  float Twips2Ui( float twips, bool YAxis = true ) const;
  float Ui2Twips( float ui, bool YAxis = true ) const;

  void SetupRenderMaterial( bool _drawBevel, const flash::SWF_RGBA& _color );

  void CheckAlphabet();

  Weak<FlashFontsRender>  owner;
  Weak<IAlphabet>         alphabet;
  Weak<IAlphabet>         scaledAlphabet;
  SFontMetric             metric;
  Render::BaseMaterial *  material;

  float originalHeight;
  nstl::string originalName;
  bool originalBold;
  int originalItalic;
  int lastScaledHeight;
};



class FlashFontsRender : public flash::IFontRender, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( FlashFontsRender, flash::IFontRender, BaseObjectST )

public:
  FlashFontsRender();

  const Rect & Viewport() const { return viewport; }
  const Rect & MovieRect() const { return movieRect; }

  //Movie size in UI pixels / Movie size in TWIPS
  float XScale() const { return xscale; }
  float YScale() const { return yscale; }

  //IFontRender
  virtual void SetViewport( int x, int y, int width, int height );
  virtual void SetMovieRect( float x, float y, float width, float height ); //Flash twips
  virtual flash::IFontInstance * FindFont( const char * name, int height, bool bold, int italic, const flash::SFontMetricInfo * metric );
  virtual void DebugLine( float x0, float y0, float x1, float y1, const flash::SWF_RGBA & color );

private:
  void CalcScale();

  typedef map<Weak<IAlphabet>, Strong<FlashFontInstance>>  TFontsCache;

  TFontsCache   cashe;
  Rect          viewport;
  Rect          movieRect; //Twips
  float         xscale, yscale;
};

} //namespace UI

#endif //FLASHFONTSRENDER_H_INCLUDED
