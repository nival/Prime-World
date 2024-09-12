#pragma once
#include "CommonControl.h"

namespace UI
{

enum CheckBoxStyle
{
  ECBS_None = 0,
  ECBS_MouseOver = 1,
  ECBS_ButtonChecked = 2,
  ECBS_ButtonCheckedAndOver = 3
};


class CheckBox : public CommonControl
{
  NI_DECLARE_REFCOUNT_CLASS_1( CheckBox, CommonControl );

public:
  CheckBox() : buttonStyle(ECBS_None), isSelected(false) {}

  bool IsSelected() const { return isSelected; }
  void SetSelected( bool selected );

  DECLARE_LUA_TYPEINFO( CheckBox );
  DEFINE_LUA_READONLY_PROPERTY( isSelected, bool, isSelected );

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
  CheckBoxStyle buttonStyle;
  bool isSelected;

  NDb::UICheckBoxLayout * GetCheckBoxLayout() { return GetLayoutClone<NDb::UICheckBoxLayout>(); }

  bool HasButtonStyle( CheckBoxStyle style ) const;
  void SetButtonStyle( CheckBoxStyle style );
  void AddButtonStyle( CheckBoxStyle style );
  void RemoveButtonStyle( CheckBoxStyle style );

  virtual bool GetCustomCursor( string * name, const Point & screenCoords ) const;
};

} //namespace UI
