#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{

class LuxBall;

class LuxBallColorChangedNotification : public EaselNotifier::tNotification
{
  OBJECT_METHODS(0x9763CC00, LuxBallColorChangedNotification)
public:
  LuxBallColorChangedNotification() {}

  CPtr<LuxBall> ball;
};

} // PF_Minigames