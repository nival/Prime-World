#pragma once

namespace threading
{
  class ITPJob
  {
  public:
    virtual void Execute() = 0;
  };
}
