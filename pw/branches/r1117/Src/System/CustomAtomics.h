#ifndef SYSTEM_CUSTOMATOMICS_H_INCLUDED
#define SYSTEM_CUSTOMATOMICS_H_INCLUDED

#include "ported/types.h"
#include "interlocked.h"

namespace threading
{

__forceinline
LONG InterlockedIncrementNonZero( LONG volatile * dest )
{
  LONG prev;
  while( true )
  {
    prev = *dest;
    if ( !prev )
      return 0;
    if ( nival::CAS( *dest, prev, prev + 1 ) )
      return prev;
  }
}

} // namespace threading

#endif //SYSTEM_CUSTOMATOMICS_H_INCLUDED
