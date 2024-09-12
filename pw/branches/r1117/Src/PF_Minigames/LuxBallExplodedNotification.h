#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{
  class LuxBallExplodedNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF4643400, LuxBallExplodedNotification)
  public:
    LuxBallExplodedNotification() {}

    CPtr<LuxBall> ball;
  };

} // PF_Minigames