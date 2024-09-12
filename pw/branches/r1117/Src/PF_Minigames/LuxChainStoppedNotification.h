#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{
  class LuxChainStoppedNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF466BB81, LuxChainStoppedNotification);
  public:
    LuxChainStoppedNotification() {};
  };
}