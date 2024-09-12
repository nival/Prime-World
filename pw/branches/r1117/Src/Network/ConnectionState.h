#pragma once
#include <System/EnumToString.h>

namespace Network
{
  namespace ConnectionState
  {
    enum Enum
    {
      /** Address initialized, no connection attempted yet. */
      Initialized = 0,
      /** Connection request issued, awaiting connection state. */
      Connecting,
      /** Connected; ready to stats/debug data. */
      Connected,
      /** Closed, either manually or as a result of an error. */
      Closed,
      Invalid
    };

    NI_ENUM_DECL_STD;

    inline
    char const * name(Enum sts)
    {
      return ToString(sts);
    }
  }
}
