#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{

class LuxBallDeleteNotification : public EaselNotifier::tNotification
{
	OBJECT_METHODS(0x99639D00, LuxBallDeleteNotification)
public:
  LuxBallDeleteNotification() : ballPointer(0) {}

	void* ballPointer;
};

} // PF_Minigames