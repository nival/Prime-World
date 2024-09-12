#ifndef FLASH_TEXTCONTAINER_H_INCLUDED
#define FLASH_TEXTCONTAINER_H_INCLUDED

#include "../../TextMarkup.h"
#include "SwfTypes.h"
#include "../../TextComponentBasic.h"

namespace flash
{

class SwfFont;
class FontsDictionary;

_interface IFontRender;
_interface IFontInstance;

class TextContainer;


class TextContainerStyle : public NMarkup::IStyle, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( TextContainerStyle, BaseObjectST );
public:
  TextContainerStyle( TextContainer * _owner, IFontInstance * font );

  IFontInstance * Renderable() const { return fontInstance; }

private:
  TextContainerStyle() {}

  //NMarkup::IStyle
  virtual NMarkup::TOffset GetTextBounds( NMarkup::SBounds * bounds, const NMarkup::TChar * text, NMarkup::TOffset length, NMarkup::TUnit maxWidth ) const;
  virtual void GetDefaultBounds( NMarkup::SBounds * bounds ) const;
  virtual NMarkup::TUnit DefaultGlyphWidth() const;
  virtual NMarkup::TUnit DefaultLineGap() const;
  virtual NMarkup::TUnit VisualHeight() const;
  virtual void RenderText( const NMarkup::SBounds & bounds, const NMarkup::TPoint & offset, const NMarkup::TChar * text, NMarkup::TOffset length );

  Weak<TextContainer>   owner;
  Strong<IFontInstance>   fontInstance;
};



//TODO: rename to 'FlashTextComponent'
class TextContainer : public NMarkup::IUiRender, public UI::TextComponentBasic, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( TextContainer, BaseObjectST );

public:
  TextContainer( FontsDictionary * dict, IFontRender * _fontRender );

  void CreateDefaultFont( int height );
  void SetDefaultFont( SwfFont * swfFont, int height );

  void ParseText( const wchar_t * text, float _fieldWidth, float _fieldHeight );

  void Render( const SWF_MATRIX & matrix, const SWF_RGBA & _defaultColor, const SWF_RECT & _cropRect );

  const SWF_MATRIX & CurrentMatrix() const { return worldMatrix; }
  const SWF_RGBA  & DefaultColor() const { return defaultColor; }
  const SWF_RECT  &  GetCropRect() const {return cropRect;}

  const wstring & Text() const { return markup.Text(); }

  NMarkup::TextMarkup & AccessMarkup() { return markup; }
  const NMarkup::TextMarkup & AccessMarkup() const { return markup; }

  TextContainerStyle* GetDefaultFont() { return defaultFont; }

private:
  TextContainer();

  //NMarkup::IUiRender:
  virtual NMarkup::IStyle * GetStyle( const NMarkup::TChar * style );
  virtual NMarkup::IImage * CreateImage( NMarkup::TPoint * size, const NMarkup::TChar * image );

  typedef map<Strong<IFontInstance>, Strong<TextContainerStyle>>  TFontsCache;

  Strong<FontsDictionary> fontDictionary;
  Strong<IFontRender>     fontRender;

  Strong<TextContainerStyle>  defaultFont;
  TFontsCache           fontsCache;

  NMarkup::TextMarkup   markup;

  SWF_MATRIX            worldMatrix;
  SWF_RGBA              defaultColor;
  SWF_RECT              cropRect;
};

} //namespace flash

#endif //FLASH_TEXTCONTAINER_H_INCLUDED
