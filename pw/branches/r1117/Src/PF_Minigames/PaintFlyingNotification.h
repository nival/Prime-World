#pragma once

#include "PaintPoint.h"
#include "PaintFragment.h"

#include "EaselNotifications.h"

namespace PF_Minigames
{

class PaintFlyingNotification : public EaselNotifier::tNotification
{
  OBJECT_METHODS(0x9763CBC0,PaintFlyingNotification)

public:
  PaintFlyingNotification() {};

  SVector from;

  CPtr<CPainterPoint>  spTo;
};

class PaintFlyingInPointNotification : public EaselNotifier::tNotification
{
  OBJECT_METHODS(0xC86A4A00,PaintFlyingInPointNotification)

public:
  PaintFlyingInPointNotification() {};

  SVector from;
  SVector to;
  NDb::EColor paintColor;

};

} //namespace PF_Minigames