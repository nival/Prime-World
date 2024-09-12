#pragma once

#include "EaselNotifications.h"
#include "LuxBallChain.h"

namespace PF_Minigames
{
  //////////////////////////////////////////////////////////////////////////
  //
  // all board chains are falling inside well
  //
  //////////////////////////////////////////////////////////////////////////
  class LuxChainsFallingNotification : public EaselNotifier::tNotification
  {
    OBJECT_METHODS(0xF467EB02, LuxChainsFallingNotification);
  public:
    LuxChainsFallingNotification() {};
  };
} // namespace PF_Minigames