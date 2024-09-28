#pragma once

namespace naio
{
  namespace status
  {
    enum Enum
    {
      INVALID = -3,
      NO_MEMORY = -2,
      FAIL = -1,
      SUCCESS = 0,
      IN_PROGRESS = 1,
      CLOSE = 2
    };
  }

  typedef status::Enum StatusT;

  typedef unsigned int ConnectionIdT;
}
