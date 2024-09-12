#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{
  class EaselLevelWonBeginNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF466C481, EaselLevelWonBeginNotification);
  public:

    EaselLevelWonBeginNotification() {}
  };

  class EaselLevelWonSkipNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF467E201, EaselLevelWonSkipNotification);
  public:
    EaselLevelWonSkipNotification() {}
  };
}