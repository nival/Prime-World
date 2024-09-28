#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Scripts/lua.hpp"
#include "EditBox.h"
#include "SkinStyles.h"
#include "NivalInput/Binds.h"

namespace UI
{
static int g_editBoxRepeatStartDelay = 500;
static int g_editBoxRepeatDelay = 50;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO(EditBox, ImageLabel)
  LUA_METHOD(SetInputText) 
  LUA_METHOD(SetInputNumber)
  LUA_METHOD(Clear)
  LUA_METHOD(EventBack)
  LUA_METHOD(EventLeft)
  LUA_METHOD(EventRight)
  LUA_METHOD(EventHome)
  LUA_METHOD(EventEnd)
  LUA_PROPERTY(inputText)
END_LUA_TYPEINFO(EditBox)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditBox::EditBox()
: cursorPos(0)
, showCursor( false )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditBox::Render()
{
  GetTextComponent().SetCursorPosition( IsFullyEnabled() && showCursor ? cursorPos : -1 );

  ImageLabel::Render();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::OnBind( const string & bind, float fDelta, bool *pResult )
{
  hash_map<string,TBindHandler>::const_iterator it = bindHandlers.find( bind );
  if ( it == bindHandlers.end() )
    return false;
  TBindHandler handler = it->second;
  if ( handler )
  {
    const bool result = (this->*handler)();
    if ( pResult )
      *pResult = result;
  }
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditBox::OnInit()
{
  ImageLabel::OnInit();

  const int repeatStartDelay = g_editBoxRepeatStartDelay;
  const int repeatDelay = g_editBoxRepeatDelay;

  AddBindHandler( "editline_end", &EditBox::EventEnd, repeatStartDelay, repeatDelay );
  AddBindHandler( "editline_home", &EditBox::EventHome, repeatStartDelay, repeatDelay );
  AddBindHandler( "editline_left", &EditBox::EventLeft, repeatStartDelay, repeatDelay );
  AddBindHandler( "editline_right", &EditBox::EventRight, repeatStartDelay, repeatDelay );
  AddBindHandler( "editline_back", &EditBox::EventBack, repeatStartDelay, repeatDelay );
  AddBindHandler( "editline_delete", &EditBox::EventDelete, repeatStartDelay, repeatDelay );
  //AddBindHandler( "editline_tab", &EditBox::EventTab, 0,0 );

  AddBindHandler( "editline_return", &EditBox::EventReturn, 0,0 );
  AddBindHandler( "editline_up", &EditBox::EventUp, 0,0 );
  AddBindHandler( "editline_down", &EditBox::EventDown, 0,0 );

  AddBindHandler( "editline_wordleft", &EditBox::EventCtrlLeft, repeatStartDelay, repeatDelay );
  AddBindHandler( "editline_wordright", &EditBox::EventCtrlRight, repeatStartDelay, repeatDelay );

  AddBindHandler( "editline_paste", &EditBox::EventPaste, 0,0 );
  AddBindHandler( "editline_copy", &EditBox::EventCopy, 0,0 );
  AddBindHandler( "editline_cut", &EditBox::EventCut, 0,0 );
  AddBindHandler( "editline_clear", &EditBox::EventClear, 0,0 );

  GetTextComponent().SetCursorMaterial( GetEditBoxLayout()->cursorMaterial, GetContext() );
  GetTextComponent().EnableRawTextMode( true );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditBox::SetInputText( wstring text )
{
  if ( inputText == text )
    return;
  inputText = text;
  cursorPos = inputText.size();
  UpdateText();

  Invalidate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const wstring& EditBox::GetInputText()
{
  return inputText;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditBox::SetInputNumber( int number )
{
  wstring text = NStr::ToUnicode( NStr::IntToStr( number ) );
  SetInputText( text );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditBox::Clear()
{
  inputText.clear();
  cursorPos = 0;

  UpdateText();

  Invalidate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::OnKeyboardFocus( bool _focus )
{
  Input::Binds *binds = Input::BindsManager::Instance()->GetBinds();

  if(binds)
  {
    if ( _focus )
      binds->MuteNonDefaultSections( (BaseObjectST *)this );
    else
      binds->UnmuteNonDefaultSections( (BaseObjectST *)this );
  }

  showCursor = _focus;
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditBox::OnEnable( bool _enable )
{
  NDb::UIEditBoxLayout *pLayout = GetEditBoxLayout();
  if ( _enable )
  {
    SetBackgroundMaterial( pLayout->backgroundMaterial );
  }
  else
  {
    if ( !SetBackgroundMaterial( pLayout->disabledMaterial ) )
      SetBackgroundMaterial( pLayout->backgroundMaterial );
  }

  ImageLabel::OnEnable( _enable );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::OnChar( int chr )
{
  if ( !iswprint( chr ) )
    return false;
  if ( iswcntrl( chr ) )
    return false;

  //process the character
  AddChar( chr );

  return ImageLabel::OnChar( chr );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventReturn()
{
  if ( !IsFocused() )
    return false;

  const int maxRows = GetEditBoxLayout()->maxLines;
  if ( maxRows <= 1 )
    return false; // not multiline

  const int rows = GetTextComponent().GetLinesCount();
  if ( rows >= maxRows )
    return true; // eat event, but do nothing (already max. rows)

  AddTag( L"br" );

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventUp()
{
  if ( !IsFocused() )
    return false;

  GetTextComponent().SetCursorPosition( cursorPos );

  TextComponent::SCursorInfo info;
  GetTextComponent().GetCursorInfo( &info );
  cursorPos = GetTextComponent().FindCursorPosition( info, TextComponent::FINDCURSOR_MOVE_UP );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventDown()
{
  if ( !IsFocused() )
    return false;

  GetTextComponent().SetCursorPosition( cursorPos );

  TextComponent::SCursorInfo info;
  GetTextComponent().GetCursorInfo( &info );
  cursorPos = GetTextComponent().FindCursorPosition( info, TextComponent::FINDCURSOR_MOVE_DOWN );
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::OnMouseDown( EMButton::Enum mbutton, const Point & point )
{
  if ( mbutton == EMButton::Left )
  {
    SetFocus( true );

    const Rect margins = GetCaptionMargins();
    const Rect winRect = GetWindowRect();
    TextComponent::SCursorInfo info( point.x - winRect.x1 - margins.x1, point.y - winRect.y1 - margins.y1, 0, 0 );
    cursorPos = GetTextComponent().FindCursorPosition( info, TextComponent::FINDCURSOR_BY_XY );
  }

  ImageLabel::OnMouseDown( mbutton, point );
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::OnMouseUp( EMButton::Enum mbutton )
{
  ImageLabel::OnMouseUp( mbutton );
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventTab()
{
  if ( !IsFocused() )
    return false;

  const wstring OldText = inputText;
  const int OldCursorPos = cursorPos;

  NDb::EUITextEntryType type = GetEditBoxLayout()->textEntryType;
  if ( type != NDb::UITEXTENTRYTYPE_IDENTIFIER && type != NDb::UITEXTENTRYTYPE_NUMERIC && type != NDb::UITEXTENTRYTYPE_PLAYERNAME )
  {
    inputText.insert( inputText.begin() + cursorPos, VK_SPACE );
    inputText.insert( inputText.begin() + cursorPos, VK_SPACE );
    inputText.insert( inputText.begin() + cursorPos, VK_SPACE );
    inputText.insert( inputText.begin() + cursorPos, VK_SPACE );
    cursorPos += 4;
    if ( !CheckText() )
    {
      inputText = OldText;
      cursorPos = OldCursorPos;
      return true;
    }
    UpdateText();
    Invalidate();
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventBack()
{
  if ( !IsFocused() )
    return false;

  if ( cursorPos > 0 )
  {
    if ( inputText[ cursorPos-1 ] == L'>' )
    {
      int ln = 1;
      while ( cursorPos-ln-1 >= 0 && inputText[ cursorPos-ln-1 ] != L'<' )
        ++ln;
      if ( cursorPos-ln-1 >= 0 && inputText[ cursorPos-ln-1 ] == L'<' )
        ++ln;
      inputText.erase( cursorPos-ln, ln );
      cursorPos -= ln;
    }
    else
    {
      inputText.erase( cursorPos - 1, 1 );
      --cursorPos;
    }
  }

  CheckText();
  UpdateText();
  Invalidate();
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventDelete()
{
  if ( !IsFocused() )
    return false;

  if ( cursorPos < inputText.size() )
  {
    if ( inputText[ cursorPos ] == L'<' )
    {
      int ln = 1;
      while( cursorPos+ln < inputText.size() && inputText[cursorPos+ln] != L'>' )
        ++ln;
      if ( cursorPos+ln < inputText.size() && inputText[cursorPos+ln] == L'>' )
        ++ln;
      inputText.erase( cursorPos, ln );
    }
    else
    {
      inputText.erase( cursorPos, 1 );
    }
  }

  CheckText();
  UpdateText();
  Invalidate();
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventLeft()
{
  if ( !IsFocused() )
    return false;

  if ( cursorPos <= 0 || cursorPos > inputText.size() )
    return false;
  --cursorPos;

  if ( inputText[ cursorPos ] == L'>' )
  {
    while ( cursorPos > 0 && inputText[cursorPos] != L'<' )
      --cursorPos;
  }

  UpdateText();
  Invalidate();
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventRight()
{
  if ( !IsFocused() )
    return false;

  if ( cursorPos < 0 || cursorPos >= inputText.size() )
    return false;
  ++cursorPos;

  if ( cursorPos > 0 )
    if ( inputText[ cursorPos-1 ] == L'<' )
    {
      while ( cursorPos < inputText.size() && inputText[cursorPos] != L'>' )
        ++cursorPos;
      if ( cursorPos < inputText.size() && inputText[cursorPos] == L'>' )
        ++cursorPos;
    }

    UpdateText();
    Invalidate();
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventHome()
{
  if ( !IsFocused() )
    return false;

  TextComponent::SCursorInfo info;
  GetTextComponent().GetCursorInfo( &info );
  cursorPos = GetTextComponent().FindCursorPosition( info, TextComponent::FINDCURSOR_MOVE_TO_ROW_BEGIN );

  UpdateText();
  Invalidate();
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventEnd()
{
  if ( !IsFocused() )
    return false;

  TextComponent::SCursorInfo info;
  GetTextComponent().GetCursorInfo( &info );
  cursorPos = GetTextComponent().FindCursorPosition( info, TextComponent::FINDCURSOR_MOVE_TO_ROW_END );

  UpdateText();
  Invalidate();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventCtrlLeft()
{
  if ( !IsFocused() )
    return false;

  if ( cursorPos <= 0 )
    return false;

  while( cursorPos > 0 && ( iswspace(inputText[cursorPos-1]) && inputText[cursorPos-1] != L'>' ) )
    --cursorPos;

  if ( cursorPos > 0 )
  {
    wchar_t wch = inputText[cursorPos-1];
    if ( wch == L'>' )
    {
      --cursorPos;
      while ( cursorPos > 0 && inputText[cursorPos] != L'<' )
        --cursorPos;
    }
    else if ( iswalpha(wch) )
    {
      while( cursorPos > 0 && iswalpha(inputText[cursorPos-1]) )
        --cursorPos;
    }
    else
    {
      while( cursorPos > 0 && !iswalpha(inputText[cursorPos-1]) )
        --cursorPos;
    }
  }

  UpdateText();
  Invalidate();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventCtrlRight()
{
  if ( !IsFocused() )
    return false;

  if ( cursorPos < inputText.size() )
  {
    wchar_t wch = inputText[cursorPos];
    if ( wch == L'<' )
    {
      while ( cursorPos < inputText.size() && inputText[cursorPos] != L'>' )
        ++cursorPos;
      if ( cursorPos < inputText.size() && inputText[cursorPos] == L'>' )
        ++cursorPos;
    }
    else if ( iswalpha(inputText[cursorPos]) )
    {
      while( cursorPos < inputText.size() && iswalpha(inputText[cursorPos]) )
        ++cursorPos;
    }
    else
    {
      while( cursorPos < inputText.size() && !iswalpha(inputText[cursorPos]) )
        ++cursorPos;
    }
  }

  while( cursorPos < inputText.size() && iswspace(inputText[cursorPos]) )
    ++cursorPos;

  UpdateText();
  Invalidate();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventPaste()
{
  if ( !IsFocused() )
    return false;

  if ( !IsClipboardFormatAvailable(CF_UNICODETEXT) ) 
    return true; 
  if ( !OpenClipboard( 0 ) ) 
    return true;

  HANDLE h = GetClipboardData(CF_UNICODETEXT);
  if ( NULL != h )
  {
    LPWSTR lptstr = (LPWSTR)GlobalLock(h); 
    if ( lptstr != NULL ) 
    { 
      wstring Inserted(lptstr);
      GlobalUnlock(h); 
      CloseClipboard();

      const wstring oldText = inputText;
      const int oldCursorPos = cursorPos;
      const int StrLen = Inserted.size();
      for ( int i = 0; i < StrLen; ++i )
      {
        if ( !IsValidSymbol( Inserted[i], GetEditBoxLayout()->textEntryType ) )
          return true;
      }

      DeleteSelection();
      wstring sBegin = oldText.substr(0, Max(Min(oldText.size(), cursorPos), 0));
      wstring sEnd   = oldText.substr(Max(Min(oldText.size(), cursorPos), 0));
      Inserted = sBegin + Inserted;
      Inserted += sEnd;
      cursorPos = Min(inputText.size(), cursorPos);
      inputText.insert( inputText.begin() + Max(0, cursorPos), Inserted.begin(), Inserted.end() );

      cursorPos += Inserted.size();
      if ( !CheckText() )
      {
        inputText = oldText;
        cursorPos = oldCursorPos;
        UpdateText();
        Invalidate();
        return true;
      }
      UpdateText();
      Invalidate();
    }
    else
      CloseClipboard();
  }
  else
    CloseClipboard();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventCopy()
{
  if ( !IsFocused() )
    return false;

  EventSelectAll();
  CopySelectionToClipboard();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventCut()
{
  if ( !IsFocused() )
    return false;

  EventSelectAll();
  CopySelectionToClipboard();

  DeleteSelection();
  UpdateText();
  Invalidate();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventClear()
{
  if ( !IsFocused() )
    return false;

  EventSelectAll();

  DeleteSelection();
  UpdateText();
  Invalidate();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::EventSelectAll()
{
  if ( !IsFocused() )
    return false;
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::GetCustomCursor( string * name, const Point & screenCoords ) const
{
  if ( !name )
    return false;

  if ( GetWindowLayout()->cursors.pushable.empty() )
    return false;

  *name = GetWindowLayout()->cursors.pushable;
  return true;		
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::AddChar( const wchar_t chr )
{
  const wstring OldText = inputText;
  const int OldCursorPos = cursorPos;
  if ( IsValidSymbol( chr, GetEditBoxLayout()->textEntryType ) )
  {
    size_t insertAt = Clamp( cursorPos, 0, inputText.size() );
    inputText.insert( inputText.begin() + insertAt, chr );

    cursorPos++;
    if ( !CheckText() )
    {
      inputText = OldText;
      cursorPos = OldCursorPos;
      return false;
    }
    UpdateText();
    Invalidate();
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::AddTag( const wstring & _tag )
{
  wstring tag = L"<";
  tag += _tag;
  tag += L">";

  const wstring OldText = inputText;
  const int OldCursorPos = cursorPos;

  const size_t pos = size_t( Max(0,Min( int(inputText.size()), cursorPos)) );
  inputText.insert( pos, tag.c_str() );
  cursorPos += tag.length();

  if ( !CheckText() )
  {
    inputText = OldText;
    cursorPos = OldCursorPos;
    return false;
  }

  UpdateText();
  Invalidate();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::CheckText()
{
  int maxLen = GetEditBoxLayout()->maxLength;
  if ( maxLen != -1 && inputText.size() > maxLen )
    return false;

  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditBox::CopySelectionToClipboard()
{
  if ( !OpenClipboard( 0 ) ) 
    return; 

  if ( inputText.length() <= 0 )
  {
    CloseClipboard();
    return;
  }

  const int beginSelection = GetSelectionBegin();
  const int endSelection = GetSelectionEnd();

  EmptyClipboard(); 

  // Allocate a global memory object for the text. 
  HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (endSelection - beginSelection + 1) * sizeof(char)); 
  if ( hglbCopy == NULL ) 
  { 
    CloseClipboard(); 
    return; 
  } 

  // get selection
  wstring ToCopy = &inputText[beginSelection];
  ToCopy.resize( endSelection - beginSelection );
  const string szToCopy( NStr::ToMBCS( ToCopy ) );

  // Lock the handle and copy the text to the buffer. 
  LPTSTR lptstrCopy = (LPTSTR)GlobalLock( hglbCopy ); 

  memcpy( lptstrCopy, szToCopy.c_str(), (szToCopy.size()) * sizeof(char) ); 
  lptstrCopy[szToCopy.size()] = (char) 0;    // null character 
  GlobalUnlock( hglbCopy ); 

  SetClipboardData( CF_TEXT, hglbCopy ); 
  CloseClipboard(); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditBox::DeleteSelection()
{
  inputText.erase(GetSelectionBegin(),GetSelectionEnd());
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditBox::UpdateText()
{
  cursorPos = Clamp( cursorPos, 0, inputText.length() );

  if( GetEditBoxLayout()->isPassword )
  {
    wstring fakeText;
    fakeText.resize( inputText.size(), L'*' );
    SetCaptionTextW( fakeText );
  }
  else
    SetCaptionTextW( inputText );

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Real Selection noew is not yet implemented
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EditBox::GetSelectionBegin() const
{
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EditBox::GetSelectionEnd() const
{
  return inputText.size();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	int EditBox::GetSelection( const int size )
//	{
//		if ( inputText.empty() )
//			return 0;

//int oldSize = 0; //sizer.targetSize;

//sizer.targetSize = size;
//wstring Tmp = inputText.substr( beginText );
//sizer.Process( Tmp );

//sizer.targetSize = oldSize;

//		return 0; //sizer.result.begin()->size();
//	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsSymbolIn( wchar_t chr, const wstring &szSymbols )
{
  return find( szSymbols.begin(), szSymbols.end(), chr ) != szSymbols.end();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsValidSymbol( wchar_t chr, NDb::EUITextEntryType eTextEntryType )
{
  static const wstring InValidSymbols = L"<>";
  int nLen = InValidSymbols.size();
  for ( int i = 0; i < nLen; i++ )
  {
    if ( chr == InValidSymbols[i] )
      return false;
  }

  switch ( eTextEntryType )
  {
    case NDb::UITEXTENTRYTYPE_NUMERIC:
      {
        static const wstring ValidSymbols = L"0123456789";
        return IsSymbolIn( chr, ValidSymbols );
      }
      break;
    case NDb::UITEXTENTRYTYPE_IDENTIFIER:
      {
        //проверим, что символ удовлетвор€ет требовани€м GameSpy NickName
        static const wstring ValidSymbols = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]\\`_^{|}-";
        return IsSymbolIn( chr, ValidSymbols );
      }
      break;
    case NDb::UITEXTENTRYTYPE_PLAYERNAME:
      {
        static const wstring InValidSymbols = L"&\"<>=\r\n";
        return !IsSymbolIn( chr, InValidSymbols );
      }
      break;
    case NDb::UITEXTENTRYTYPE_CONSOLE:
      {
        static const wstring InValidSymbols = L"`~\r\n";
        return !IsSymbolIn( chr, InValidSymbols );
      }
      break;

      /*
    case NDb::TEXTENTRYTYPE_FILENAME:
      {
      //проверим, что символ удовлетвор€ет требовани€м FileName symbols
      //wstringValidSymbols = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]`_^{}-!@#$%^&()+=~";
      static const wstring InvalidSymbols = L"\\/|:*?\"<>\r\n";
      return !IsSymbolIn( chr, InvalidSymbols );
      }
      break;
    case NDb::TEXTENTRYTYPE_GAME_SPY:
      {
      //проверим, что символ удовлетвор€ет требовани€м GameSpy NickName
      static const wstring ValidSymbols = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]\\`_^{|}-";
      return IsSymbolIn( chr, ValidSymbols );
      }
      break;
    case NDb::TEXTENTRYTYPE_UBI:
      {
      //проверим, что символ удовлетвор€ет требовани€м UbiCom
      static const wstring ValidSymbols = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_.-";
      return IsSymbolIn( chr, ValidSymbols );
      }
      break;
      */

    case NDb::UITEXTENTRYTYPE_FREE:
      break;
    default:
      return false;
  }
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_CONTROLTYPE( NDb::UIEditBoxLayout, EditBox );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace UI

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace UI;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_VAR( "ui_editbox_repeat_startdelay", g_editBoxRepeatStartDelay, STORAGE_NONE );
REGISTER_VAR( "ui_editbox_repeat_delay", g_editBoxRepeatDelay, STORAGE_NONE );
