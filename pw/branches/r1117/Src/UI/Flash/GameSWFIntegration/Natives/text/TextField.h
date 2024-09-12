#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../display/InteractiveObject.h"


namespace flash
{
  _interface IFontInstance;
  class EditTextTagData;
  class TextContainer;
}


namespace avmplus
{

class TextFormatObject;
class ArrayObject;
class DisplayObjectObject;
class ScriptObject;
class StyleSheetObject;

class TextFieldAutoSize;


class TextFieldObject : public InteractiveObjectObject
{
public:
  //TODO fix args
  TextFieldObject( TextFieldClass * classType ) : InteractiveObjectObject( (InteractiveObjectClass*)classType ) { InitializeTextField(); }

  TextFieldObject( VTable *ivtable, ScriptObject *prototype ) : InteractiveObjectObject(ivtable, prototype) { InitializeTextField(); }

  ~TextFieldObject();

  void SetData( flash::EditTextTagData * _data );

  //Common function
  AvmString get_type();
  void set_type(AvmString value);

  AvmString get_text();
  void set_text(AvmString value);

  uint get_textColor();
  void set_textColor(uint value);

  //Text layout settings
  bool get_multiline();
  void set_multiline(bool value);
  bool get_wordWrap();
  void set_wordWrap(bool value);
  AvmString get_autoSize();
  void set_autoSize(AvmString value);
  bool get_condenseWhite();
  void set_condenseWhite(bool value);
  AvmString get_htmlText();
  void set_htmlText(AvmString value);

  //Text structure
  int get_length();

  int get_numLines();
  int getLineOffset(int lineIndex);
  int getLineLength(int lineIndex);
  int getLineIndexOfChar(int charIndex);
  AvmString getLineText(int lineIndex);

  int get_maxChars();
  void set_maxChars(int value);

  void replaceText(int beginIndex, int endIndex, AvmString newText);

  //Text geometrical information
  double get_textWidth();
  double get_textHeight();
  int getCharIndexAtPoint(double x, double y);
  int getLineIndexAtPoint(double x, double y);
  ScriptObject/*Rectangle*/ * getCharBoundaries(int charIndex);
  ScriptObject/*TextLineMetrics*/ * getLineMetrics(int lineIndex);

  //Paragraphs
  int getParagraphLength(int charIndex);
  int getFirstCharInParagraph(int charIndex);

  //Scrolling
  void set_scrollH(int value);
  void set_scrollV(int value);
  int get_scrollH();
  int get_scrollV();
  int get_maxScrollH();
  int get_maxScrollV();
  int get_bottomScrollV();
  bool get_mouseWheelEnabled();
  void set_mouseWheelEnabled(bool value);

  //Background and border visualisaton
  bool get_border();
  void set_border(bool value);
  uint get_borderColor();
  void set_borderColor(uint value);

  bool get_background();
  void set_background(bool value);
  uint get_backgroundColor();
  void set_backgroundColor(uint value);

  //Selection
  bool get_selectable();
  void set_selectable(bool value);
  bool get_alwaysShowSelection();
  void set_alwaysShowSelection(bool value);
  int get_selectionEndIndex();
  int get_selectionBeginIndex();
  void setSelection(int beginIndex, int endIndex);
  void replaceSelectedText(AvmString value);

  //Advanced text render
  double get_thickness();
  void set_thickness(double value);
  double get_sharpness();
  void set_sharpness(double value);
  AvmString get_gridFitType();
  void set_gridFitType(AvmString gridFitType);
  void set_antiAliasType(AvmString antiAliasType);
  AvmString get_antiAliasType();
  bool get_embedFonts();
  void set_embedFonts(bool value);

  //Editbox mode
  AvmString get_restrict();
  void set_restrict(AvmString value);
  int get_caretIndex();

  //custom
  bool get_userInput();
  void set_userInput(bool value);

  ///////////////////////////
  void setTextFormat(TextFormatObject* format, int beginIndex, int endIndex);
  ArrayObject* getTextRuns(int beginIndex, int endIndex); //Used in XML text parsing
  TextFormatObject* get_defaultTextFormat();
  DisplayObjectObject* getImageReference(AvmString id);
  void set_displayAsPassword(bool value);
  AvmString getRawText();
  StyleSheetObject* get_styleSheet();
  bool get_useRichTextClipboard();
  void set_defaultTextFormat(TextFormatObject* format);
  bool get_displayAsPassword();
  void set_useRichTextClipboard(bool value);
  void set_styleSheet(StyleSheetObject* value);
  TextFormatObject* getTextFormat(int beginIndex, int endIndex);

  virtual void set_x(double value);
  virtual void set_y(double value);
  virtual void set_width(double value);
  virtual double get_width();

  virtual const flash::SWF_MATRIX& GetMatrix() const;
  virtual flash::SWF_MATRIX& GetMatrix();

public:
  virtual void DoRender( Render::IFlashRenderer * _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode );
  virtual void GetBounds( flash::SWF_RECT& _rect );

  virtual void OnFocusLoss( InteractiveObjectObject * nextFocused );
  virtual bool OnFocusGain( InteractiveObjectObject * prevFocused );
  virtual void OnChar( int ch );
  virtual void OnKeyPressed( int code, bool down );

  virtual const char* GetDumpName() { return "<TextField>"; }

  void ReplaceText( int beginIndex, int endIndex, const wchar_t * text );

  virtual void SetGlowHack( bool useGlow, flash::SWF_RGBA& _color );

  virtual void OnMovedSized();

private:
  DECLARE_SLOTS_TextFieldObject;

  void UpdateTextOutput();

  void InitializeTextField();
  void SetText( const wchar_t * txt );
  void SetCaret( int pos );
  void MoveCaret( int shift ) { SetCaret( caretIndex + shift ); }

  void RemoveHTMLTags( const wchar_t * txt, nstl::wstring& targetString );

  EventObject * CreateTextEvent( wchar_t * text );

  void UpdateX();
  void UpdateBoundingRect();

  Strong<flash::EditTextTagData> data;
  Strong<flash::TextContainer> textContainer;

  //fields
  //TODO: implement visual
  flash::SWF_RGBA   textColor;
  bool              alwaysShowSelection;
  bool              drawBackground;
  flash::SWF_RGBA   backgroundColor;
  bool              drawBorder;
  flash::SWF_RGBA   borderColor;
  int               caretIndex;
  int               maxChars;

  bool              userInput;

  bool drawBevel;
  flash::SWF_RGBA bevelColor;

  TextFieldAutoSize* textFieldAutoSize;

  nstl::wstring text;

  flash::SWF_RECT boundingRect;
  flash::SWF_RECT lastBoundingRect;
  mutable flash::SWF_MATRIX localMatrix;
};





class TextFieldClass : public InteractiveObjectClass
{
public:
  TextFieldClass(VTable *vtable): InteractiveObjectClass(vtable)
  {
    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
    flashCore->GetClassCache().RegisterClass( EFlashClassID::TextFieldClass, this );
  }

  ~TextFieldClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TextFieldObject(ivtable, prototype);
  }  

  virtual Atom construct(int argc, Atom* argv);

  bool isFontCompatible(AvmString fontName, AvmString fontStyle)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldClass", "isFontCompatible" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_TextFieldClass;
};

} //namespace avmplus
