#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{
  class LuxBallEntersTunnelNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF467EA40, LuxBallEntersTunnelNotification)
  public:
    LuxBallEntersTunnelNotification() {}

    CPtr<LuxBall> ball;
  };

  class LuxBallLeavesTunnelNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF467EA41, LuxBallLeavesTunnelNotification)
  public:
    LuxBallLeavesTunnelNotification() {}

    CPtr<LuxBall> ball;
  };

} // PF_Minigames