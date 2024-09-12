#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// current notification is sent by boost object to notify about it's state
//
//////////////////////////////////////////////////////////////////////////
class LuxSorterBoostFiredNotification : public EaselNotifier::tNotification
{
  OBJECT_METHODS(0xF4689400, LuxSorterBoostFiredNotification);
public:
  LuxSorterBoostFiredNotification() {}
};

} // PF_Minigames