#pragma once
#include <System/EnumToString.h>

namespace Transport
{
  namespace EChannelType
  {
    enum Enum
    {
      Invalid = -1,
      Unicast,
      Multicast,
    };
    NI_ENUM_DECL_STD;
  }
}
