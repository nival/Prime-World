#pragma once
#include "CommonControl.h"

namespace UI
{
class RadioPanel;

enum RadioButtonStyle
{
  ERBS_None = 0,
  ERBS_MouseOver = 1,
  ERBS_ButtonSelected = 2,
  ERBS_ButtonSelectedAndOver = 3,
  ERBS_Flashing = 4
};



class RadioButton : public CommonControl
{
  NI_DECLARE_REFCOUNT_CLASS_1( RadioButton, CommonControl );

public:
  RadioButton() : buttonStyle( ERBS_None ), isSelected( false ) {}

  int RadioGroup() const { return GetRadioLayout()->group; }
  void SetSelected( bool selected, int group );
  void Flash() { SetButtonStyle( ERBS_Flashing ); } 

  DECLARE_LUA_TYPEINFO(RadioButton);
  DEFINE_LUA_READONLY_PROPERTY(isSelected, bool, isSelected);

protected:
  virtual void OnInit();

  virtual void OnEnable( bool _enable );
  virtual void OnShow( bool _show );
  virtual void OnInvalidate();

  virtual bool OnMouseMove( const Point & mouse ) { CommonControl::OnMouseMove( mouse ); return true; }
  virtual void OnMouseOver( bool over, const Point & mouse );
  virtual bool OnMouseDown( EMButton::Enum mbutton, const Point & point );
  virtual bool OnMouseUp( EMButton::Enum mbutton );

private:
  RadioButtonStyle buttonStyle;
  bool isSelected;

  NDb::UIRadioButtonLayout * GetRadioLayout() { return GetLayoutClone<NDb::UIRadioButtonLayout>(); }
  const NDb::UIRadioButtonLayout * GetRadioLayout() const { return GetLayoutClone<NDb::UIRadioButtonLayout>(); }

  Window *FindRadioPanel();
  void FindGroupButtons( Window *pFrom, vector<Weak<RadioButton>>& result );
  void DeselectGroupButtons();

  bool HasButtonStyle( RadioButtonStyle style ) const;
  void SetButtonStyle( RadioButtonStyle style );
  void AddButtonStyle( RadioButtonStyle style );
  void RemoveButtonStyle( RadioButtonStyle style );

  virtual bool GetCustomCursor( string * name, const Point & screenCoords ) const;
};

} //namespace UI
