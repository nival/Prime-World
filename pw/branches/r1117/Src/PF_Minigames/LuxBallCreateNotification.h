#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{

class LuxBallCreateNotification : public EaselNotifier::tNotification
{
	OBJECT_METHODS(0x99639AC1, LuxBallCreateNotification)
public:
	LuxBallCreateNotification() {}

	CPtr<LuxBall> ball;
};

} // PF_Minigames