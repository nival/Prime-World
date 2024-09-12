#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{

  class LuxBallFiredNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0x9763FB40,LuxBallFiredNotification)

  public:
    LuxBallFiredNotification() {};

    CPtr<LuxBall> ball;
  };

} //namespace PF_Minigames