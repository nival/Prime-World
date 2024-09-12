#pragma once

#include "../Render/texture.h"
#include "Root.h"
#include "ImageComponent.h"
#include "FontRender.h"
#include "TextMarkup.h"
#include "TextComponentBasic.h"

namespace UI
{


namespace ETextUpdateMode
{
  enum Enum { None, KeepNamemaps, Full };
}

class TextComponent;


class TextComponentImage : public ImageComponent, public NMarkup::IImage
{
public:
  TextComponentImage() : owner( 0 ) {}
  void SetOwner( TextComponent * _owner ) { owner = _owner; }

  //NMarkup::IImage
  virtual void      RenderImage( const NMarkup::TPoint & offset, const NMarkup::TPoint & size );
private:
  TextComponent *       owner; //RAW pointer
};




//прослойка между интерфейсами NMarkup::IStyle и UI::IFontStyle
class TextComponentStyle : public NMarkup::IStyle
{
public:
  TextComponentStyle() : owner( 0 ) {}

  UI::IFontStyle * Get() { return style; }
  void Set( TextComponent * _owner, UI::IFontStyle * _style ) { owner = _owner; style = _style; }

  //NMarkup::IStyle:
  virtual NMarkup::TOffset  GetTextBounds( NMarkup::SBounds * bounds, const NMarkup::TChar * text, NMarkup::TOffset length, NMarkup::TUnit maxWidth ) const;
  virtual void GetDefaultBounds( NMarkup::SBounds * bounds ) const;
  virtual NMarkup::TUnit    DefaultGlyphWidth() const;
  virtual NMarkup::TUnit    DefaultLineGap() const;
  virtual NMarkup::TUnit    VisualHeight() const;
  virtual void              RenderText( const NMarkup::SBounds & bounds, const NMarkup::TPoint & offset, const NMarkup::TChar * text, NMarkup::TOffset length );

private:
  TextComponent *       owner; //RAW pointer
  Strong<UI::IFontStyle>  style;
};



class TextComponent : public NMarkup::IUiRender, public TextComponentBasic
{
public:
	TextComponent();

  void SetText( const wstring & _text );
  const wstring & GetText() const { return text; }

  void SetTexturePoolId( ScreenLogicBase * _logicAsTexturePool ) { logicAsTexturePool = _logicAsTexturePool; }

  void ForceUpdate( ETextUpdateMode::Enum mode = ETextUpdateMode::Full );

	void SetFontStyle( const NDb::UIFontStyle * _pFontStyle );
  void OverrideFontStyle( IFontStyle * style );

  void EnableRawTextMode( bool enable );

  void EnableWordWrap( bool enable ) { ChangeParam( wordWrap, enable ); }
  void SetStretchText( bool enable ) { ChangeParam( stretchText, enable ); }

	void SetVAlign( NDb::EUITextVAlign align ) { ChangeParam( vAlign, align); }
	void SetHAlign( NDb::EUITextHAlign align ) { ChangeParam( hAlign, align); }

  void SetDrawRect( const Rect & rect ) { if ( !drawRect.HasSameSize( rect ) ) ForceUpdate( ETextUpdateMode::KeepNamemaps ); drawRect = rect; }
	void SetCropRect( const Rect & rect ) { cropRect = rect; needUpdateImages = true; }
  void SetOpacity( float _opacity ) { ChangeParam( opacity, _opacity ); }
  void SetDefaultColor( const Render::Color & color ) { ChangeParam( defaultColor, color ); }

  void SetCursorMaterial( const NDb::BaseUIMaterial *_pCursorMaterial, ScreenLogicBase * logicAsTexturePool ) { cursor.SetImageMaterial( _pCursorMaterial, logicAsTexturePool ); cursorWidth = _pCursorMaterial ? _pCursorMaterial->imageSize.x : 0; }
	int GetCursorMaxPosition() const { return text.length(); }
	int GetCursorPosition() const { return cursorPos; }
	void SetCursorPosition( int pos ) { cursorPos = pos; }

	struct SCursorInfo
  {
    float x, y, h;
    int line;
    SCursorInfo( float _x = 0, float _y = 0, float _h = 0, int _line = 0 ) :
    x( _x ), y( _y ), h( _h ), line( _line )
    {}
  };

	bool GetCursorInfo( SCursorInfo * info );

	enum EFindCursorMode
	{
		FINDCURSOR_BY_XY,
		FINDCURSOR_MOVE_UP,
		FINDCURSOR_MOVE_DOWN,
		FINDCURSOR_MOVE_TO_ROW_BEGIN,
		FINDCURSOR_MOVE_TO_ROW_END,
	};
	int FindCursorPosition( const SCursorInfo & fromInfo, EFindCursorMode mode );

	int GetLinesCount() { Update(); return markup.LinesCount(); }
	float GetTextHeight() { Update(); return markup.TextBounds().y; }
	float GetTextWidth() { Update(); return markup.TextBounds().x; }

  const Rect & GetDrawRect() const { return drawRect; }
  const Rect & GetCropRect() const { return cropRect; }
  float Opacity() const { return opacity; }
  const Render::Color & DefaultColor() const { return defaultColor; }

  bool NeedUpdateImages() const { return needUpdateImages; }

  void Update();

	virtual void Render();

protected:
  bool GetCursorInfoImpl( SCursorInfo * info, int localCursorPos );

  //NMarkup::IUiRender:
  virtual NMarkup::IStyle * GetStyle( const NMarkup::TChar * style );
  virtual NMarkup::IImage * CreateImage( NMarkup::TPoint * size, const NMarkup::TChar * image );

private:
	void SetupParams();

  template < typename T >
  void ChangeParam( T & target, const T & value )
  {
    if( target != value )
    {
      target = value;
      ForceUpdate( ETextUpdateMode::KeepNamemaps );
    }
  }

  void OnStyleResourceChanged( const NDb::DBID & )
  {
    ForceUpdate( ETextUpdateMode::KeepNamemaps );
  }

private:
  typedef map<Strong<UI::IFontStyle>, TextComponentStyle>  TFontStyles;
  typedef list<TextComponentImage> TImages;

	wstring text;

  NMarkup::TextMarkup markup;

	NDb::ChangeablePtr<NDb::UIFontStyle> dbDefaultFontStyle;
  TextComponentStyle defaultFontStyleOverride;

  TFontStyles   fontStyles;

	bool wordWrap;
  bool stretchText;
  bool rawTextMode;

	NDb::EUITextVAlign vAlign;
	NDb::EUITextHAlign hAlign;

	Rect drawRect;
	Rect cropRect;
	float opacity;
  Render::Color defaultColor;

  ETextUpdateMode::Enum updateMode;
	bool needUpdateImages;

	TImages images;

	ImageComponent cursor;
	int cursorWidth;
	int cursorPos;

  Weak<ScreenLogicBase> logicAsTexturePool;
};

} //namespace UI
