#ifndef UI_BUTTON_H_INCLUDED
#define UI_BUTTON_H_INCLUDED

#include "CommonControl.h"

namespace UI
{

namespace EButtonStyle
{
  enum Enum
  {
    None            = 0,
    MouseOver       = 1,
    MouseDown       = 2,
    MousePressedAndOver = 3,
    Flashing        = 4,
    All             = MouseOver | MouseDown | Flashing
  };
}


class Button : public CommonControl
{
  NI_DECLARE_REFCOUNT_CLASS_1( Button, CommonControl );

public:
  Button() : buttonStyle( EButtonStyle::None ), activationButton( EMButton::Left ), emulatePress( false ) {}

  virtual void OnInit();
  virtual void OnEnable( bool _enable );
  virtual void OnShow( bool _show );
  virtual void OnInvalidate();
  virtual void OnMouseOver( bool over, const Point & mouse );
  virtual bool OnMouseMove( const Point & mouse );
  virtual bool OnMouseDown( EMButton::Enum mbutton, const Point & point );
  virtual bool OnMouseUp( EMButton::Enum mbutton );
  virtual bool OnDoubleClick( EMButton::Enum mbutton, const Point & point );
  virtual bool OnKeyboardFocus( bool gotFocus );
  virtual bool OnChar( int ch );
  virtual bool OnActivationBind();

  virtual void OnDataChanged();

  void Flash( bool enable );
  bool IsFlashing() const { return HasButtonStyle( EButtonStyle::Flashing ); }

  void EmulatePress( bool on );

  // from ImageLabel
  virtual bool SetBackgroundMaterial( const NDb::BaseUIMaterial * _material );
  virtual bool SetBackgroundMaterialByName( const char *_resourceName );
  virtual void SetBackgroundTexture(const Render::Texture2DRef &_pTexture);

  DECLARE_LUA_TYPEINFO(Button);

private:
  Render::Texture2DRef currentTexture;
  unsigned buttonStyle;
  EMButton::Enum activationButton;
  bool emulatePress;

  NDb::UIButtonLayout * GetButtonLayout() { return GetLayoutClone<NDb::UIButtonLayout>(); }

  bool OnGeneralMouseDown( EMButton::Enum mbutton );

  bool HasButtonStyle( unsigned style ) const;
  void SetButtonStyle( unsigned style );
  void AddButtonStyle( unsigned style );
  void RemoveButtonStyle( unsigned style );

  virtual bool GetCustomCursor( string * name, const Point & screenCoords ) const;

  void UpdateButtonMaterials();
  void UpdateButtonMaterialPins();
};

} //namespace UI

#endif //UI_BUTTON_H_INCLUDED
