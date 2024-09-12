#pragma once

#include "EaselNotifications.h"
#include "LuxBoard.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// this notification is send when game board needs to change it state
//
//////////////////////////////////////////////////////////////////////////
class LuxBoardRequestStateChangeNotification : public EaselNotifier::tNotification
{
  OBJECT_METHODS(0xF466C480, LuxBoardRequestStateChangeNotification);
public:
  LuxBoardRequestStateChangeNotification() {}

  LuxBoardType   boardType;
  LuxBoardState  currState;
  LuxBoardState  requestState;
};

}