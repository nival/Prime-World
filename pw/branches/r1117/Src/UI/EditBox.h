#pragma once
#include "ImageLabel.h"


namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EditBox : public ImageLabel
{
  NI_DECLARE_REFCOUNT_CLASS_1( EditBox, ImageLabel );

public:
  EditBox();

  virtual void OnInit();

  virtual bool OnKeyboardFocus( bool _focus );
  virtual void OnEnable( bool _enable );
  virtual bool OnMouseMove( const Point & mouse ) { ImageLabel::OnMouseMove( mouse ); return true; }
  virtual bool OnMouseDown( EMButton::Enum mbutton, const Point & point );
  virtual bool OnMouseUp( EMButton::Enum mbutton );
  virtual bool OnChar( int chr );

  virtual bool OnBind( const string & bind, float fDelta, bool *pResult );

  DECLARE_LUA_TYPEINFO(EditBox);

  const wstring& GetInputText();

  void SetInputText( wstring text );

  void SetInputNumber( int number );

  void Clear();

  DEFINE_LUA_PROPERTY(inputText, wstring, inputText );

private:
  wstring inputText;
  int cursorPos;
  bool showCursor;

  typedef bool ( EditBox::*TBindHandler )( void );
  hash_map< string, TBindHandler > bindHandlers;

  NDb::UIEditBoxLayout * GetEditBoxLayout() { return GetLayoutClone<NDb::UIEditBoxLayout>(); }

  virtual void Render();

public: //Temp
  bool EventEnd();
  bool EventHome();
  bool EventLeft();
  bool EventRight();
  bool EventBack();

private:
  bool EventDelete();
  bool EventTab();
  bool EventReturn();
  bool EventUp();
  bool EventDown();

  bool EventCtrlLeft();
  bool EventCtrlRight();
  bool EventPaste();
  bool EventCopy();
  bool EventCut();
  bool EventSelectAll();
  bool EventClear();

  void AddBindHandler( const char * bind, TBindHandler handler, int repeatStartDelay, int repeatDelay )
  {
    GetContext()->SetBind( bind, this, "", repeatStartDelay, repeatDelay );
    bindHandlers[ bind ] = handler;
  }

  virtual bool GetCustomCursor( string * name, const Point & screenCoords ) const;

  bool AddChar( const wchar_t chr );
  bool AddTag( const wstring & tag );
  bool CheckText();

  void UpdateText();

  void CopySelectionToClipboard();
  bool DeleteSelection();
  int GetSelectionBegin() const;
  int GetSelectionEnd() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsValidSymbol( wchar_t chr, NDb::EUITextEntryType eTextEntryType );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace UI

