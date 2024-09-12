#include "TamarinPCH.h"

#include "TextField.h"
#include "TextFieldAutoSize.h"
#include "TextFormat.h"

#include "../../TextTagsData.h"
#include "../../FontTags.h"
#include "../../FontsRenderInterface.h"
#include "../../FlashMovie.h"
#include "../../TextContainer.h"

#include "../display/Stage.h"
#include "../events/Event.h"
#include "../events/KeyboardEvent.h"


#include "../../FlashMovieAvmCore.h"

#include "../../../../FontRender.h"

namespace
{
  static NDebug::DebugVar<unsigned int> totalTextFieldCount( "TotalTextFieldCount", "PerfCnt" );

  bool TextFollowedBy( const wchar_t * txt, int index, int textSize, const wchar_t * searchPattern )
  {
    NI_VERIFY( txt, "", return false );
    NI_VERIFY( searchPattern, "", return false );

    int searchSize = wcslen( searchPattern );

    if (textSize - index < searchSize)
      return false;

    for(int i = index;  i < index + searchSize ; i++ )
    {
      if( txt[i] != searchPattern[i - index] )
        return false;
    }

    return true;
  }
}

namespace avmplus
{

void TextFieldObject::InitializeTextField()
{
  textFieldAutoSize = new TextFieldAutoSize( core() );

  textColor = flash::SWF_RGBA( 255, 255, 255 );
  alwaysShowSelection = false;

  drawBackground = false;
  drawBorder = false;
  backgroundColor = flash::SWF_RGBA( 255, 255, 255 );
  borderColor = flash::SWF_RGBA( 0, 0, 0 );

  drawBevel = false;
  bevelColor = flash::SWF_RGBA( 0, 0, 0 );

  caretIndex = 0;
  maxChars = 0;

  userInput = false;

  data = new flash::EditTextTagData;

  flash::Movie * movie = FlashCore()->GetMovie();

  textContainer = new flash::TextContainer( movie->Fonts(), movie->FontRender() );

  textContainer->SetNameMapInterface( movie->GetNameMapInterface() );

  totalTextFieldCount.AddValue(1);
}

TextFieldObject::~TextFieldObject() 
{
  SAFE_DELETE( textFieldAutoSize );
  totalTextFieldCount.DecValue(1);
}

void TextFieldObject::SetGlowHack( bool _useGlow, flash::SWF_RGBA& _color )
{
  drawBevel = _useGlow;
  bevelColor = _color;
}

void TextFieldObject::RemoveHTMLTags( const wchar_t * txt, nstl::wstring& targetString )
{
  targetString = txt;

  int nextSymbol = 0;
  int size = wcslen( txt );
  bool insideTag = false;

  const wchar_t * brTag = L"<br>";

  for ( int i = 0; i < size; ++i )
  {
    if ( txt[i] == L'<'  && !TextFollowedBy(txt, i, size, brTag))
    {
      insideTag = true;
      continue;
    }

    if ( txt[i] == L'>'  && insideTag)
    {
      insideTag = false;
      continue;
    }

    if ( !insideTag )
    {
      targetString[nextSymbol] = txt[i];
      nextSymbol++;
    }
  }

  if ( nextSymbol < size )
    targetString[nextSymbol] = 0;
}

void TextFieldObject::SetText( const wchar_t * txt )
{
  RemoveHTMLTags( txt, text );

  if ( data->font )
    textContainer->SetDefaultFont( data->font, data->FontHeight );
  else
    textContainer->CreateDefaultFont( data->FontHeight );

  NMarkup::EJustify::Enum justify = NMarkup::EJustify::Left;
  bool stretch = false;

  {
    switch( data->Align )
    {
    case flash::EEditTextAlign::Left:
      justify = NMarkup::EJustify::Left;
      break;

    case flash::EEditTextAlign::Right:
      justify = NMarkup::EJustify::Right;
      break;

    case flash::EEditTextAlign::Center:
      justify = NMarkup::EJustify::Center;
      break;

    case flash::EEditTextAlign::Justify:
      justify = NMarkup::EJustify::Left;
      stretch = true;
      break;
    }
  }

  NMarkup::TextMarkup& markup = textContainer->AccessMarkup();

  markup.SetDefaultParams( NMarkup::EVerticalAlign::Top, justify, data->WordWrap, stretch );

  markup.CondenseWhite(!userInput);
  markup.KeepSpacesBeforePunct(userInput);

  textContainer->ParseText( text.c_str(), boundingRect.GetWidth() - 4 * flash::TWIP, boundingRect.GetHeight() - 4 * flash::TWIP );
  UpdateBoundingRect();
  textContainer->ParseText( text.c_str(), boundingRect.GetWidth() - 4 * flash::TWIP, boundingRect.GetHeight() - 4 * flash::TWIP );
  UpdateBoundingRect();
  UpdateX();
}



void TextFieldObject::SetCaret( int pos )
{
  if ( pos < 0 )
    caretIndex = 0;
  else if ( pos > textContainer->Text().size() )
    caretIndex = textContainer->Text().size();
  else
    caretIndex = pos;
}

/*
//offset
flash::SWF_MATRIX offsMtx;
offsMtx.ConcatenateTranslation( 10, 10 );

flash::SWF_MATRIX mtx;
mtx.Concatenate( worldMatrix, offsMtx );
*/


void TextFieldObject::DoRender( Render::IFlashRenderer * _renderer, const flash::SWF_MATRIX & _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode )
{
  if ( !textContainer )
  {
    return;
  }

  flash::SWF_RGBA _textColor = textColor;
  _textColor.a = 255; //Let's hack alpha channel as Flash Player does
  flash::SWF_RGBA finalColor;

 
  flash::SWF_MATRIX finalMatrix;   
  flash::SWF_MATRIX towPixelShift;

  towPixelShift.m_[0][2] = 2.f * flash::TWIP;
  towPixelShift.m_[1][2] = 2.f * flash::TWIP;

  finalMatrix.Concatenate( _matrix, towPixelShift );

  _cxform.Transform( finalColor, _textColor );

  flash::Movie* flashMovie = FlashCore()->GetMovie();

  if ( flashMovie && flashMovie->IsBlocked() )
  {
    flashMovie->FadeBlockedColor( finalColor, IsNonBlocked() );
  }

  bool isEditMode = !data->ReadOnly; 
  flash::SWF_RECT cropRect = flash::SWF_RECT();
 
  NMarkup::TPoint caretOffset, caretSize;
  bool foundCaret = false; 

  int caretSizeOffset =  PIXELS_TO_TWIPS( 2 );
  int caretWidth = PIXELS_TO_TWIPS( 1 ) ;

  if (isEditMode)
  {
    //crop rect
    flash::SWF_POINT p;
    finalMatrix.Transform( p, flash::SWF_POINT( boundingRect.X1, boundingRect.Y1) );

    cropRect.X1 = p.X;
    cropRect.X2 = p.X + boundingRect.GetWidth();
    cropRect.Y1 = p.Y;
    cropRect.Y2 = p.Y + boundingRect.GetHeight();

    //input mode
    if ( get_stage()->get_focus() == this )
    {
      //caret
      int lineIndex = 0;
      foundCaret = textContainer->AccessMarkup().GetCharInfo( caretIndex, &caretOffset, &caretSize, &lineIndex ); 

      float caretOffsetX = boundingRect.GetWidth() - caretOffset.x - caretWidth - caretSizeOffset ;
      if (caretOffsetX<0)
      {
        flash::SWF_MATRIX offsMtx;
        offsMtx.ConcatenateTranslation( caretOffsetX, 0);

        flash::SWF_MATRIX newFinalMatrix;
        newFinalMatrix.Concatenate( finalMatrix, offsMtx );

        finalMatrix = newFinalMatrix;
      }
    }
  }

  _renderer->RenderTextBevel( drawBevel, bevelColor, UI::GetFontRenderer()->GetFontsTexture() );
  textContainer->Render( finalMatrix, finalColor, cropRect );
  _renderer->RenderTextBevel( false, bevelColor, UI::GetFontRenderer()->GetFontsTexture() );

  if ( isEditMode && foundCaret  )
  {
    nstl::vector<CVec2> caretLine(2);

    caretLine[0].x = caretOffset.x + caretSizeOffset;
    caretLine[0].y = caretOffset.y;
    caretLine[1].x = caretOffset.x + caretSizeOffset;
    caretLine[1].y = caretOffset.y + caretSize.y;

    _renderer->SetMatrix( finalMatrix );
    _renderer->SetLineWidth( caretWidth );
    _renderer->SetLineColor( finalColor );
    _renderer->DrawLineStrip( caretLine, -1 );
  }

//  if ( drawBorder )
//   {
//     flash::IFontRender * fontRender = FlashCore()->GetMovie()->FontRender();
// 
//     if ( fontRender )
//     {
//       flash::SWF_POINT p0;
//       _matrix.Transform( p0, flash::SWF_POINT( 0, 0 ) );
// 
//       flash::SWF_POINT p1( p0.X + get_width() * flash::TWIP, p0.Y + get_height() * flash::TWIP );
//       flash::SWF_POINT p2( p0.X + get_textWidth() * flash::TWIP, p0.Y + get_textHeight() * flash::TWIP );
// 
//       fontRender->DebugLine( p0.X, p0.Y, p0.X, p1.Y, flash::SWF_RGBA(0,255,0) );
//       fontRender->DebugLine( p1.X, p0.Y, p1.X, p1.Y, flash::SWF_RGBA(0,255,0) );
//       fontRender->DebugLine( p0.X, p0.Y, p1.X, p0.Y, flash::SWF_RGBA(0,255,0) );
//       fontRender->DebugLine( p0.X, p1.Y, p1.X, p1.Y, flash::SWF_RGBA(0,255,0) );
// 
//       fontRender->DebugLine( p0.X, p0.Y, p0.X, p2.Y, flash::SWF_RGBA(255,0,0) );
//       fontRender->DebugLine( p2.X, p0.Y, p2.X, p2.Y, flash::SWF_RGBA(255,0,0) );
//       fontRender->DebugLine( p0.X, p0.Y, p2.X, p0.Y, flash::SWF_RGBA(255,0,0) );
//       fontRender->DebugLine( p0.X, p2.Y, p2.X, p2.Y, flash::SWF_RGBA(255,0,0) );
//     }
//   }
}


void TextFieldObject::GetBounds( flash::SWF_RECT& _rect )
{
  _rect = boundingRect;
}

void TextFieldObject::OnFocusLoss( InteractiveObjectObject * nextFocused )
{
}



bool TextFieldObject::OnFocusGain( InteractiveObjectObject * prevFocused )
{
  InteractiveObjectObject::OnFocusGain( prevFocused );

  if ( data->ReadOnly )
    return false;

  return true;
}



void TextFieldObject::OnChar( int ch )
{
  if ( !iswprint( (wint_t)ch ) )
    return;
  if ( ch == VK_BACK )
    return;

  // NUM_TASK
  if ( iswspace( (wint_t)ch ) )
    if (ch != VK_SPACE)
      return;

  wchar_t str[2] = { (wchar_t)ch, 0 };

  //Dispatch event
  EventObject * event = CreateTextEvent( str );
  dispatchEventFunction( event );

  if (event->isDefaultPrevented())
    return;

  if (maxChars > 0)
  {
    const int curTextLen = textContainer->Text().length();

    if (curTextLen >= maxChars)
      return;
  }

  {
    const int prevTextLen = textContainer->Text().length();
    ReplaceText( caretIndex, caretIndex, str );
    const int curTextLen = textContainer->Text().length();

    if (curTextLen > prevTextLen)
      ++caretIndex;
  }
}



void TextFieldObject::OnKeyPressed( int code, bool down )
{
  avmplus::KeyboardEventClass * keybEventClass = FlashCore()->GetClassCache().GetClass<avmplus::KeyboardEventClass>( EFlashClassID::KeyboardEventClass );
  KeyboardEventObject * event = 
        keybEventClass->CreateKeyboardEvent( down ? "keyDown" : "keyUp", true, false, code, code, 0, false, false, false );
  dispatchEventFunction( event );

  if ( !down )
    return;

  if ( code == VK_LEFT )
    MoveCaret( -1 );
  else if ( code == VK_RIGHT )
    MoveCaret( +1 );
  else if ( code == VK_DELETE )
    ReplaceText( caretIndex, caretIndex + 1, L"" );
  else if ( code == VK_BACK )
  {
    int newCaret = caretIndex - 1;
    ReplaceText( caretIndex - 1, caretIndex, L"" );
    SetCaret( newCaret );
  }
  else if ( code == VK_HOME )
    SetCaret( 0 );
  else if ( code == VK_END )
    SetCaret( textContainer->Text().size() );
}



EventObject * TextFieldObject::CreateTextEvent( wchar_t * text )
{
  avmplus::ClassClosure * eventClass = FlashCore()->GetClassByName( "flash.events.TextEvent" );

  
  Atom args[] = 
  {
    0,
    FlashCore()->internConstantStringLatin1( "textInput" )->atom(), //type
    trueAtom, //bubbles
    trueAtom, //cancelable
    FlashCore()->internStringUTF16( (const wchar *)text )->atom(), //text
  };

  ScriptObject * scriptObject = FlashCore()->atomToScriptObject( eventClass->construct( 4, args ) );
  EventObject * eventObject = dynamic_cast<EventObject*>( scriptObject );

  //eventObject->SetPropertyByName( FlashCore()->internConstantStringLatin1( "bubbles" ), trueAtom );

  return eventObject;
}



void TextFieldObject::ReplaceText( int beginIndex, int endIndex, const wchar_t * text )
{
  wstring buffer = textContainer->Text();

  if ( beginIndex < 0 )
    return; //Flash legacy

  if ( endIndex > buffer.size() )
    endIndex = buffer.size();

  if ( endIndex < beginIndex )
    return; //Flash legacy

  int len = endIndex - beginIndex;

  buffer.replace( beginIndex, len, text, wcslen( text ) );

  SetText( buffer.c_str() );

  //Validate caret pos
  MoveCaret( 0 );
}



void TextFieldObject::SetData( flash::EditTextTagData * _data )
{
  data->Copy( _data );

  boundingRect = data->Bounds;
  lastBoundingRect = data->Bounds;

  SetText( data->InitialText.c_str() );

  textColor = data->TextColor;

  drawBackground = data->Border;
  drawBorder = data->Border;

  if (!data->font)
    data->FontHeight = 12 * flash::TWIP;

//  AquireDefaultFont();
}


void TextFieldObject::setTextFormat(TextFormatObject* format, int beginIndex, int endIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "setTextFormat" );
}


ArrayObject* TextFieldObject::getTextRuns(int beginIndex, int endIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getTextRuns" );
  return (ArrayObject*)0;
}


TextFormatObject* TextFieldObject::get_defaultTextFormat()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_defaultTextFormat" );
  return (TextFormatObject*)0;
}

DisplayObjectObject* TextFieldObject::getImageReference(AvmString id)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getImageReference" );
  return (DisplayObjectObject*)0;
}

/////Order begins

AvmString TextFieldObject::get_type()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_type" );
  return 0;
}


void TextFieldObject::set_type(AvmString value)
{
  //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_type" );
}


AvmString TextFieldObject::get_text()
{
  return String::createUTF16( core(), (const wchar*)textContainer->Text().c_str(), textContainer->Text().size() );
}


void TextFieldObject::set_text(AvmString value)
{
  StUTF16String tmp( value );
  SetText( (const wchar_t *)tmp.c_str() );
  SetCaret(tmp.length());
}


uint TextFieldObject::get_textColor()
{
  uint _textColor = textColor.GetUInt();
  return _textColor;
}


void TextFieldObject::set_textColor(uint value)
{
  textColor.SetUInt( value );
  textColor.a = 0;
}


bool TextFieldObject::get_multiline()
{
  return data->Multiline;
}


void TextFieldObject::set_multiline(bool value)

{
  data->Multiline = value;
}


bool TextFieldObject::get_wordWrap()
{
  return data->WordWrap;
}


void TextFieldObject::set_wordWrap(bool value)
{
  data->WordWrap = value;
  UpdateTextOutput();
}


AvmString TextFieldObject::get_autoSize()
{
  NI_VERIFY( textFieldAutoSize, "textFieldAutoSize should not be null", return 0 );
  return textFieldAutoSize->GetStringValue();
}


void TextFieldObject::set_autoSize(AvmString value)
{
  NI_VERIFY( textFieldAutoSize, "textFieldAutoSize should not be null", return );
  textFieldAutoSize->SetStringValue( value );

  SetText( text.c_str() );
}

void TextFieldObject::UpdateBoundingRect()
{
  //text width
  float textWidth = get_textWidth() * flash::TWIP;

  bool changeWidth = !data->WordWrap;
  textWidth = changeWidth? textWidth: boundingRect.GetWidth(); //use old width instead in case od word wrap

  switch ( textFieldAutoSize->GetValue() )
  {
  case ETextFieldAutoSize::CENTER:
    {
      float centerX = (boundingRect.X1 + boundingRect.X2 ) / 2.f;
      boundingRect.X1 = centerX - textWidth / 2.f;
      boundingRect.X2 = centerX + textWidth / 2.f;
    }
    break;
  case ETextFieldAutoSize::LEFT:
    boundingRect.X2 = boundingRect.X1 + textWidth;
    break;
  case ETextFieldAutoSize::RIGHT:
    boundingRect.X1 = boundingRect.X2 - textWidth;
    break;
  }

  //text height
  boundingRect.Y2 = get_textHeight() * flash::TWIP;

}

void TextFieldObject::UpdateX()
{
  float x1Old = lastBoundingRect.X1  / flash::TWIP;
  float x1New = boundingRect.X1  / flash::TWIP;
  float widthOld = lastBoundingRect.GetWidth()  / flash::TWIP;
  float widthNew = boundingRect.GetWidth()  / flash::TWIP;

  float x = DisplayObjectObject::get_x();

  switch ( textFieldAutoSize->GetValue() )
  {
  case ETextFieldAutoSize::CENTER:
    DisplayObjectObject::set_x( x + x1Old + 0.5f * widthOld - ( x1New + 0.5f * widthNew ) );
    break;
  case ETextFieldAutoSize::RIGHT:
    DisplayObjectObject::set_x( x + x1Old + widthOld - ( x1New + widthNew ) );
    break;
  }

  lastBoundingRect = boundingRect;
}

void TextFieldObject::set_x(double value) 
{ 
  NI_ASSERT( !_isnan( value ) && _finite( value ), "Wrong set_x value from script" );

  DisplayObjectObject::GetMatrix().m_[0][2] = PIXELS_TO_TWIPS( value ) - boundingRect.X1; 
}

void TextFieldObject::set_y(double value)
{
  NI_ASSERT( !_isnan( value ) && _finite( value ), "Wrong set_x value from script" );

  DisplayObjectObject::GetMatrix().m_[1][2] = PIXELS_TO_TWIPS( value ) - boundingRect.Y1; 
}

void TextFieldObject::set_width( double value )
{
  boundingRect.X2 = boundingRect.X1 + PIXELS_TO_TWIPS( value);

  UpdateTextOutput();
}

double TextFieldObject::get_width()
{
  return TWIPS_TO_PIXELS(boundingRect.GetWidth());
}

const flash::SWF_MATRIX& TextFieldObject::GetMatrix() const
{
  localMatrix = DisplayObjectObject::GetMatrix();
  localMatrix.m_[0][2] += boundingRect.X1;
  localMatrix.m_[1][2] += boundingRect.Y1;
  return localMatrix;
}

flash::SWF_MATRIX& TextFieldObject::GetMatrix()
{
  localMatrix = DisplayObjectObject::GetMatrix();
  localMatrix.m_[0][2] += boundingRect.X1;
  localMatrix.m_[1][2] += boundingRect.Y1;
  return localMatrix;
}

bool TextFieldObject::get_condenseWhite()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_condenseWhite" );
  return false;
}


void TextFieldObject::set_condenseWhite(bool value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_condenseWhite" );
}


AvmString TextFieldObject::get_htmlText()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_htmlText" );
  return 0;
}


void TextFieldObject::set_htmlText(AvmString value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_htmlText" );
}


int TextFieldObject::get_length()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_length" );
  return textContainer->Text().length();
}


int TextFieldObject::get_numLines()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_numLines" );
  return textContainer->AccessMarkup().LinesCount();
}


int TextFieldObject::getLineOffset(int lineIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getLineOffset" );
  NMarkup::TPoint min, max;
  int start = 0, length = 0;
  textContainer->AccessMarkup().GetLineInfo( lineIndex, min, max, start, length, 0 );
  return start;
}


int TextFieldObject::getLineLength(int lineIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getLineLength" );
  NMarkup::TPoint min, max;
  int start = 0, length = 0;
  textContainer->AccessMarkup().GetLineInfo( lineIndex, min, max, start, length, 0 );
  return length;
}


AvmString TextFieldObject::getLineText(int lineIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getLineText" );
  NMarkup::TPoint min, max;
  int start = 0, length = 0;
  wstring substr;
  textContainer->AccessMarkup().GetLineInfo( lineIndex, min, max, start, length, &substr );
  return String::createUTF16( core(), (const wchar*)substr.c_str(), substr.size() );
}


int TextFieldObject::get_maxChars()
{
  return maxChars;
}


void TextFieldObject::set_maxChars(int value)
{
  if (value < 0)
    maxChars = 0;
  else
    maxChars = value;
}


//http://help.adobe.com/en_US/AS3LCR/Flash_10.0/flash/text/TextField.html#replaceText()
//TODO: This method does not work if a style sheet is applied to the text field.
void TextFieldObject::replaceText(int beginIndex, int endIndex, AvmString newText)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "replaceText" );

  StUTF16String tmp( newText );
  ReplaceText( beginIndex, endIndex, (const wchar_t *)( tmp.c_str() ) );
}


double TextFieldObject::get_textWidth()
{
  NI_ASSERT( textContainer, "" );
  return textContainer->AccessMarkup().TextBounds().x / flash::TWIP + 4.f;
}


double TextFieldObject::get_textHeight()
{
  NI_ASSERT( textContainer, "" );
  return textContainer->AccessMarkup().TextBounds().y / flash::TWIP + 4.f;
}


int TextFieldObject::getCharIndexAtPoint(double x, double y)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getCharIndexAtPoint" );
  return 0;
}


int TextFieldObject::getLineIndexAtPoint(double x, double y)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getLineIndexAtPoint" );
  return 0;
}


ScriptObject/*Rectangle*/ * TextFieldObject::getCharBoundaries(int charIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getCharBoundaries" );
  return (ScriptObject/*Rectangle*/ *)0;
}


ScriptObject/*TextLineMetrics*/ * TextFieldObject::getLineMetrics(int lineIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getLineMetrics" );
  return (ScriptObject/*TextLineMetrics*/ *)0;
}


int TextFieldObject::getParagraphLength(int charIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getParagraphLength" );
  return 0;
}


int TextFieldObject::getFirstCharInParagraph(int charIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getFirstCharInParagraph" );
  return 0;
}


void TextFieldObject::set_scrollH(int value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_scrollH" );
}


void TextFieldObject::set_scrollV(int value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_scrollV" );
}


int TextFieldObject::get_scrollH()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_scrollH" );
  return 0;
}


int TextFieldObject::get_scrollV()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_scrollV" );
  return 0;
}


int TextFieldObject::get_maxScrollH()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_maxScrollH" );
  return 0;
}


int TextFieldObject::get_maxScrollV()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_maxScrollV" );
  return 0;
}


int TextFieldObject::get_bottomScrollV()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_bottomScrollV" );
  return 0;
}


bool TextFieldObject::get_mouseWheelEnabled()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_mouseWheelEnabled" );
  return false;
}


void TextFieldObject::set_mouseWheelEnabled(bool value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_mouseWheelEnabled" );
}


bool TextFieldObject::get_border()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_border" );
  return drawBorder;
}


void TextFieldObject::set_border(bool value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_border" );
  drawBorder = value;
}


uint TextFieldObject::get_borderColor()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_borderColor" );
  return borderColor.GetUInt();
}


void TextFieldObject::set_borderColor(uint value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_borderColor" );
  borderColor.SetUInt( value );
}


bool TextFieldObject::get_background()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_background" );
  return drawBackground;
}


void TextFieldObject::set_background(bool value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_background" );
  drawBackground = value;
}


uint TextFieldObject::get_backgroundColor()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_backgroundColor" );
  return backgroundColor.GetUInt();
}


void TextFieldObject::set_backgroundColor(uint value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_backgroundColor" );
  backgroundColor.SetUInt( value );
}


bool TextFieldObject::get_selectable()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_selectable" );
  return !data->NoSelect;
}


void TextFieldObject::set_selectable(bool value)
{
  data->NoSelect = !value;
}


bool TextFieldObject::get_alwaysShowSelection()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_alwaysShowSelection" );
  return alwaysShowSelection;
}


void TextFieldObject::set_alwaysShowSelection(bool value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_alwaysShowSelection" );
  alwaysShowSelection = value;
}


int TextFieldObject::get_selectionEndIndex()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_selectionEndIndex" );
  return 0;
}


int TextFieldObject::get_selectionBeginIndex()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_selectionBeginIndex" );
  return 0;
}


void TextFieldObject::setSelection(int beginIndex, int endIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "setSelection" );
}


double TextFieldObject::get_thickness()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_thickness" );
  return 0;
}


void TextFieldObject::set_thickness(double value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_thickness" );
}


double TextFieldObject::get_sharpness()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_sharpness" );
  return data->csmSettings.Sharpness;
}


void TextFieldObject::set_sharpness(double value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_sharpness" );
  data->csmSettings.Sharpness = value;
}


AvmString TextFieldObject::get_gridFitType()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_gridFitType" );

  switch( data->csmSettings.GridFit )
  {
    case flash::ECsmTextGridFit::Off:
      return String::createLatin1( core(), "none" );
    case flash::ECsmTextGridFit::Pixel:
      return String::createLatin1( core(), "pixel" );
    case flash::ECsmTextGridFit::SubPixel:
      return String::createLatin1( core(), "subpixel" );
  }
  return String::createLatin1( core(), "" );
}


void TextFieldObject::set_gridFitType(AvmString gridFitType)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_gridFitType" );

  StUTF8String tmp( gridFitType );
  const char * txt = tmp.c_str();
  if ( !strcmp( txt, "none" ) )
    data->csmSettings.GridFit = flash::ECsmTextGridFit::Off;
  else if ( !strcmp( txt, "pixel" ) )
    data->csmSettings.GridFit = flash::ECsmTextGridFit::Pixel;
  else if ( !strcmp( txt, "subpixel" ) )
    data->csmSettings.GridFit = flash::ECsmTextGridFit::SubPixel;
}


void TextFieldObject::set_antiAliasType(AvmString antiAliasType)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_antiAliasType" );
}


AvmString TextFieldObject::get_antiAliasType()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_antiAliasType" );
  return 0;
}


bool TextFieldObject::get_embedFonts()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_embedFonts" );
  return false;
}


void TextFieldObject::set_embedFonts(bool value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_embedFonts" );
}


void TextFieldObject::replaceSelectedText(AvmString value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "replaceSelectedText" );
}


AvmString TextFieldObject::get_restrict()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_restrict" );
  return 0;
}


void TextFieldObject::set_restrict(AvmString value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_restrict" );
}


int TextFieldObject::get_caretIndex()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_caretIndex" );
  return caretIndex;
}


///////////////////


void TextFieldObject::set_displayAsPassword(bool value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_displayAsPassword" );
}


AvmString TextFieldObject::getRawText()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getRawText" );
  return 0;
}


StyleSheetObject* TextFieldObject::get_styleSheet()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_styleSheet" );
  return (StyleSheetObject*)0;
}

bool TextFieldObject::get_useRichTextClipboard()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_useRichTextClipboard" );
  return false;
}

void TextFieldObject::set_defaultTextFormat(TextFormatObject* format)
{
  //NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_defaultTextFormat" );
  if (!format)
    return;

  //TODO add other params except text size
  data->FontHeight = format->GetSize()* flash::TWIP;

  UpdateTextOutput();
}


bool TextFieldObject::get_displayAsPassword()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "get_displayAsPassword" );
  return false;
}


void TextFieldObject::set_useRichTextClipboard(bool value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_useRichTextClipboard" );
}


void TextFieldObject::set_styleSheet(StyleSheetObject* value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "set_styleSheet" );
}


TextFormatObject* TextFieldObject::getTextFormat(int beginIndex, int endIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getTextFormat" );
  return (TextFormatObject*)0;
}

int TextFieldObject::getLineIndexOfChar(int charIndex)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextFieldObject", "getLineIndexOfChar" );
  return 0;
}

void TextFieldObject::UpdateTextOutput()
{
  SetText(text.c_str());
}

void TextFieldObject::OnMovedSized()
{
  UpdateTextOutput();
}

bool TextFieldObject::get_userInput()
{
  return userInput;
}

void TextFieldObject::set_userInput(bool value)
{
  if (userInput == value)
    return;

  userInput = value;

  UpdateTextOutput();
}


Atom TextFieldClass::construct(int argc, Atom* argv)
{
  TextFieldObject * textField = new (core()->GetGC(), ivtable()->getExtraSize()) TextFieldObject(ivtable(), prototype);
  return textField->atom();
}

} //namespace avmplus
