#include "stdafx.h"

#include "DebugTraceDumper.h"
#include "LogHelpers.h"
#include "System/InlineProfiler.h"
#include <System/ported/cwfn.h>

#pragma warning( disable : 4996)

namespace NLogg
{

void CDebugTraceDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  NI_PROFILE_HEAVY_FUNCTION;

  if ( isMessageOnly )
  {
    OutputDebugString( textOnly );
    return;
  }

  static const int sz = 2048;

  char szBuffer[sz];

  if ( !entryInfo.filename )
    NStr::Printf( szBuffer, sz - 1, "%s", textOnly );
  else if ( entryInfo.line == -1 )
    NStr::Printf( szBuffer, sz - 1, "%s: %s", entryInfo.filename, textOnly );
  else
  {
    NStr::Printf( szBuffer, sz - 1, "%s(%d): %s", entryInfo.filename, entryInfo.line, textOnly );
  }

  szBuffer[sz - 1] = 0;

  // old time-formatting removed (moved to centralized WriteHeader)

  OutputDebugString( szBuffer );
}

}
