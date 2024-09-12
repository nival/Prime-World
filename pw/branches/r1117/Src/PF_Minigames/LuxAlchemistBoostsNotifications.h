#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{

class CPainterPoint;
class CPaintFragment;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LuxAlchemistIncomingFlowNotification : public EaselNotifier::tNotification
{
  OBJECT_METHODS( 0xC56C3C80, LuxAlchemistIncomingFlowNotification);

public:
  LuxAlchemistIncomingFlowNotification() {};
  LuxAlchemistIncomingFlowNotification( NDb::EColor _color, const SVector & _fromPoint ) : color( _color ), fromPoint( _fromPoint ) {}

  NDb::EColor color;
  SVector     fromPoint;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LuxAlchemistOutgoinFlowNotification : public EaselNotifier::tNotification
{
  OBJECT_METHODS( 0xC56C7440, LuxAlchemistOutgoinFlowNotification);

public:
  LuxAlchemistOutgoinFlowNotification() {};
  LuxAlchemistOutgoinFlowNotification( NDb::EColor _color, CPainterPoint * _toPoint ) :
  color( _color ), toPoint( _toPoint ) {}

  NDb::EColor color;
  CPtr<CPainterPoint> toPoint;
};


} // PF_Minigames