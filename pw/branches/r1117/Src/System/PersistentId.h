#ifndef SYSTEM_PERSISTENTID_H_INCLUDED
#define SYSTEM_PERSISTENTID_H_INCLUDED

#include "DefaultTypes.h"

namespace nival
{

class PersistentId
{
public:
  typedef ni_detail::UInt64 TId;

  PersistentId() :
  startupKey( 0 ), counter( 1 )
  {
    __time32_t t = 0;
    _time32( &t );
    startupKey = (ni_detail::UInt32)t;
  }

  TId GetNext()
  {
    return ( ( (TId)startupKey ) << 32 ) | (TId)(counter++);
  }

private:
  ni_detail::UInt32 startupKey, counter;
};

};

#endif //SYSTEM_PERSISTENTID_H_INCLUDED
