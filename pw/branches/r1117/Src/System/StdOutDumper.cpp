#include "stdafx.h"

#include "StdOutDumper.h"
#include "LogHelpers.h"
#include "System/InlineProfiler.h"

namespace NLogg
{

void CStdOutDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  NI_PROFILE_HEAVY_FUNCTION;

  fputs( isMessageOnly ? textOnly : headerAndText, pFile );
}

}
