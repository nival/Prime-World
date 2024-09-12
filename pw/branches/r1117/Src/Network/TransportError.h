#pragma once
#include <System/EnumToString.h>

namespace Transport
{
  namespace EError
  {
    enum Enum
    {
      ALREADY_CLOSED = -3,
      NOT_FOUND = -2,
      FAIL = -1,
      OK = 0,
      IN_PROGRESS = 1,
      ALREADY_EXISTS = 2,
      ALREADY_IN_PROGRESS = 3,
    };

    NI_ENUM_DECL_STD;
  }
}
