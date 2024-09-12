#include "stdafx.h"

#include "EditBoxDumper.h"
#include "LogHelpers.h"

namespace NLogg
{

EditBoxDumper::EditBoxDumper( CLogger *defaultLogger, HWND _ownerWindow ) : CDumper( defaultLogger ), ownerWindow( _ownerWindow )
{
  RECT rect;
  GetClientRect( ownerWindow, &rect );
  logWindow = CreateWindow( "EDIT", 0, WS_CHILD | WS_VISIBLE  | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_LEFT, 0, 0, rect.right, rect.bottom, ownerWindow, 0, 0, 0 );
  ownerThread = GetCurrentThreadId();

  text[0] = '\0';
  textPos = 0;
}



void EditBoxDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  NI_ASSERT( this != 0, "EditBoxDumper::OnDump fatal error" );

  threading::MutexLock lock( mutex );

  int length = 0;
  char buffer[1024];
  if ( entryInfo.level >= LEVEL_ASSERT )
    length = sprintf_s( buffer, "%s: %s\r\n", MessageLevelToString( entryInfo.level ), textOnly );
  else
    length = sprintf_s( buffer, "%s\r\n", textOnly );

  if ( length < 0 || length > 1024 )
    return;

  char* startPos = text;
  while ( textPos + length > 8191 + (size_t)( startPos - text ) )
  {
    char* pos = strchr( startPos, '\n' );
    startPos = pos + 1;

    // Не нашли '\n'
    if ( !pos )
    {
      textPos = 0;
      startPos = text;
      break;
    }
  }
 
  if ( startPos > text )
  {
    memcpy( text, startPos, textPos - ( startPos - text ) );
    textPos -= ( startPos - text );
  }

  if ( textPos + length > 8191 )
  {
    textPos = 0;
  }

  memcpy( text + textPos, buffer, length );
  textPos += length;
  text[textPos] = 0;
  if ( GetCurrentThreadId() == ownerThread )
  {
    SetWindowText( logWindow, text );
    SendMessage( logWindow, EM_LINESCROLL, 0, 32767 );
  }
}


void EditBoxDumper::ResizeLogWindow()
{
  RECT rect;
  GetClientRect( ownerWindow, &rect );
  SetWindowPos( logWindow, 0, 0, 0, rect.right, rect.bottom, SWP_NOZORDER );
}

} //namespace NLogg
