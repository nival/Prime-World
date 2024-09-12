#pragma once

#include "EaselNotifications.h"
#include "LuxBallChain.h"

namespace PF_Minigames
{
  class LuxChainDestroyedNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0x97641280, LuxChainDestroyedNotification);
  public:
    LuxChainDestroyedNotification() {};

    CPtr<LuxBallChain> chain;

  };
} // namespace PF_Minigames