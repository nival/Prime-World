#include "stdafx.h"
#include "SpinLock.h"
#include "interlocked.h"

namespace threading
{

bool SpinLock::InternalLock( int spinCount ) const
{
  int i = spinCount;
  while ( true )
  {
    LONG check = nival::CAS_ex( gate, LockValueFree, LockValueBusy );
    if ( check == LockValueFree )
      return true;

    while ( ( gate != LockValueFree ) && ( i != 0 ) )
    {
      if ( i > 0 )
        --i;
    }

    if ( i == 0 )
      return false;
    if ( i > 0 )
      --i;
  }
  return false;
}

}; //namespace threading
