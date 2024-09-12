#pragma once
#include "MatchMakingTypes.h"

namespace MatchMaking
{
  class Session;

  class IManagerNotifier
  {
  public:
    virtual void OnGameSessionStarted(Session const * s) = 0;
  };
}
