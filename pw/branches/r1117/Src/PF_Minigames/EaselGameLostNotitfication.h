#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{
  class EaselGameLostNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF466C482, EaselGameLostNotification);
  public:
    EaselGameLostNotification() {}
  };
}