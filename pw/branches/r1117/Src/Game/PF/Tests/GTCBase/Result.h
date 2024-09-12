#pragma once

namespace GameTestClient2
{
  namespace Result
  {
    typedef enum 
    {
      INVALID = -3,
      TIMEOUT = -2,
      FAIL = -1,
      SUCCESS = 0,
      IN_PROGRESS = 1,
      NO_SUCH_STAGE = 2,
      SCENARIO_FINISHED = 3,
    } Enum;
  };
}
