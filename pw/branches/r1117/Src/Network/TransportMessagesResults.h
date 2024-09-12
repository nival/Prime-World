#pragma once

namespace Transport
{
  namespace AddRecipientResult
  {
    enum Enum
    {
      NO_CLIENT = -3,
      NO_CHANNEL = -2,
      FAIL = -1,
      OK = 0,
      RECIPIENT_ALREADY_EXISTS = 1,
    };
  }
}
