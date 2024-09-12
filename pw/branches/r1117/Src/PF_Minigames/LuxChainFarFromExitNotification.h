#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{

  class LuxChainFarFromExitNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF465F480, LuxChainFarFromExitNotification);
  public:
    LuxChainFarFromExitNotification() { pathID = 0; };

    int pathID;
  };

} // namespace PF_Minigames