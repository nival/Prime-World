#ifndef FLASH2_FONTSRENDERINTERFACE_H_INCLUDED
#define FLASH2_FONTSRENDERINTERFACE_H_INCLUDED

namespace gameswf
{
  struct matrix;
}


namespace flash
{

struct SWF_RECT;
struct SWF_RGBA;
struct SWF_MATRIX;

_interface IFontInstance : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IFontInstance, IBaseInterfaceST )

  virtual void    RenderGlyph( wchar_t c, const SWF_MATRIX & _matrix, const SWF_RGBA & color ) = 0;
  virtual void    RenderText( const wchar_t * text, unsigned length, const SWF_MATRIX & _matrix, const SWF_RGBA & color, const SWF_RECT & cropRect ) = 0;
  virtual float   GetStringLength( const wchar_t * text, unsigned length, float maxWidth, unsigned * charsFitIn, float additionalAdvance ) = 0;
  virtual float   Height() const = 0;
  virtual float   Ascent() const = 0;
  virtual float   Descent() const = 0;
  virtual float   GapAbove() const = 0;
  virtual float   GapUnder() const = 0;
  virtual float   DefaultGlyphWidth() const = 0;
  virtual void    SetBevel( bool _drawBevel, const SWF_RGBA& _color ) = 0;
};



struct SFontMetricInfo
{
  float   ascent;
  float   descent;
  float   leading;

  SFontMetricInfo() : ascent( 0 ), descent( 0 ), leading( 0 ) {}
  SFontMetricInfo( float _ascent, float _descent, float _leading ) : ascent( _ascent ), descent( _descent ), leading( _leading ) {}
};



_interface IFontRender : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IFontRender, IBaseInterfaceST )

  virtual void SetViewport( int x, int y, int width, int height ) = 0;
  virtual void SetMovieRect( float x, float y, float width, float height ) = 0; //Flash twips
  virtual IFontInstance * FindFont( const char * name, int height, bool bold, int italic, const SFontMetricInfo * metric ) = 0; //Font height is in twips
  virtual void DebugLine( float x0, float y0, float x1, float y1, const SWF_RGBA & color ) = 0;
};

} //namespace flash

#endif //FLASH2_FONTSRENDERINTERFACE_H_INCLUDED
