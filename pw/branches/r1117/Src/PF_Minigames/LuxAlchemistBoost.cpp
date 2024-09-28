#include "stdafx.h"

#include "LuxAlchemistBoost.h"

#include "LuxGameLogic.h"

#include "LuxAlchemistBoostsNotifications.h"

#include "PaintLogic.h"


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxAlchemistBoost::LuxAlchemistBoost(  PF_Core::IWorld* _pWorld, Easel * _easel, const nstl::string &_refstrName, long _cooldown, int _accessLevel,
                                      int _price, int _alchemistTime, int _additionalPaint, float _paintMult ) :
LuxBoost( _pWorld, _easel, NDb::BOOSTTYPE_ALCHEMIST, _refstrName, _cooldown, _accessLevel, _price ),
alchemistTimeLeft(0),
alchemistTime(_alchemistTime),
unusedPaintAmount(0),
additionalPaint(_additionalPaint),
paintMult(_paintMult),
isActive(false)
{
}


float LuxAlchemistBoost::ActivityProgress() const
{
  return ( alchemistTime - alchemistTimeLeft ) / alchemistTime;
}
 
void LuxAlchemistBoost::OnUnusedPaint( LuxGameLogic* _gameLogic, const SVector& explosionPoint, NDb::EColor explosionColor, int explodedBallsNum )
{
  unusedPaintAmount += explodedBallsNum;

  if ( IsValid( _gameLogic->GetNotifier() ) )
    _gameLogic->GetNotifier()->Notify( * new LuxAlchemistIncomingFlowNotification( explosionColor, explosionPoint ) );
}

EEaselBoostFireMode::Enum LuxAlchemistBoost::vFireBoost( LuxGameLogic* _gameLogic )
{
  isActive = true;
  alchemistTimeLeft = alchemistTime;
  unusedPaintAmount = 0;

  return EEaselBoostFireMode::Activated;
}


void LuxAlchemistBoost::vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic )
{
  if ( !isActive )
    return;

  alchemistTimeLeft -= deltaTime;

  if ( alchemistTimeLeft < 0.f )
  {
    int fillAmount = additionalPaint + floorf( unusedPaintAmount * paintMult );

    if ( fillAmount <= 0 )
      return;

    _gameLogic->GetPaintLogic()->FillWithUnusedPaint( fillAmount );

    isActive = false;  // boost operation time has been ended
    alchemistTimeLeft = 0.f;
  }
}

void LuxAlchemistBoost::Abort()
{
  isActive = false;
}


} //namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( LuxAlchemistBoost, PF_Minigames );