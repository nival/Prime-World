#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{
  class LuxBall;

  class LuxBallHitChainNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF4678AC0,LuxBallHitChainNotification)

  public:
    LuxBallHitChainNotification() {};

    bool fColorMatch;
    CPtr<LuxBall> wpBall;
  };

} //namespace PF_Minigames