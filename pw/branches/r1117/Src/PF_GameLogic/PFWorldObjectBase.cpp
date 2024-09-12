#include "stdafx.h"

#include "PFClientObjectBase.h"
#include "PFWorldObjectBase.h"

namespace NWorld
{
  const char* BuildFormattedStringWithStep( const PFWorldObjectBase* pWo, const char* format, ... )
  {
    const unsigned int bufferSize = 2048;
    char traceMessage[bufferSize];
    traceMessage[0] = 0;

    va_list va;
    va_start( va, format );
    vsnprintf_s( &traceMessage[0], bufferSize - 1, bufferSize - 1, format, va );
    va_end( va );

    return NStr::StrFmt( "World step # %d. %s", pWo->GetWorld()->GetStepNumber(), traceMessage );
  }
} // namespace NWorld 

WORLD_OBJECT_FUNCTIONS_NM(PFWorldObjectBase, NWorld)
