#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{
  class LuxBallMissNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0x9763FB80,LuxBallMissNotification)

  public:
    LuxBallMissNotification() {};

    CPtr<LuxBall> wpBall;
  };
} //namespace PF_Minigames