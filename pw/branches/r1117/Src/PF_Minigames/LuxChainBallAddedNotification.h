#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{
  class LuxBall;
  class LuxPath;

  class LuxChainBallAddedNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF4666380, LuxChainBallAddedNotification);
  public:
    LuxChainBallAddedNotification() {};

    CPtr<LuxPath>  path;
    CPtr<LuxBall> ball;

  };
}