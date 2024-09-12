#pragma once

//#include "../System/SharedPtr.h"

#include "LuxPlatform.h"
#include "EaselNotifications.h"

namespace PF_Minigames
{

class LuxPlatformCreateNotification : public EaselNotifier::tNotification
{
	OBJECT_METHODS(0x99639C80, LuxPlatformCreateNotification);
public:
	LuxPlatformCreateNotification() {}

	SharedPtr<LuxPlatform> platform;
};

} // PF_Minigames