#include "stdafx.h"

#include "LuxBoost.h"

#include "LuxDef.h"
#include "DBEasel.h"
#include "Easel.h"
#include "EaselWorld.h"
#include "EaselNotifications.h"
#include "PF_GameLogic/DBMinigamesTypes.h"
#include "EaselPriestess.h"


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN( LuxBoostNameMapProxy )
  NAMEMAP_FUNC_RO( price, &LuxBoostNameMapProxy::GetPrice )
NAMEMAP_END
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool EASEL_BOOSTS_COOLDOWN_ENABLE = true;

REGISTER_DEV_VAR( "Easel_Boosts_Cooldown_Enable", EASEL_BOOSTS_COOLDOWN_ENABLE, STORAGE_NONE );




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBoost::LuxBoost( PF_Core::IWorld* _pWorld, Easel * _easel, NDb::EBoostType _type, const nstl::string & _refstrName, long _cooldown, int _accessLevel, int _price ) :
PF_Core::WorldObjectBase( _pWorld, false ),
boostPrice( _price ),
boostCooldown( _cooldown * 1000 ),
boostName( _refstrName ),
boostType( _type ),
canAccess( false ),
coolingDownNow( false ),
canBuy( false ),
waiting( false ),
cooldownCurrent( 0 ),
pathID( -1 ),
easel( _easel )
{
  NI_ASSERT( IsValid( easel ), "" );

  notifier = easel->GetNotifier();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBoost::~LuxBoost()
{
  cooldownCurrent = 0;
  coolingDownNow  = false;

  boostName.clear();
  boostCooldown    = 0;
  boostPrice       = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBoost::ResetCooldown()
{
  cooldownCurrent = 0;
  coolingDownNow = false;
  waiting = false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBoost::StartCooldown()
{
  cooldownCurrent = 0;
  coolingDownNow  = true;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBoost::FireBoost( LuxGameLogic* _gameLogic )
{
  if ( coolingDownNow  )
    return;

  EEaselBoostFireMode::Enum result = vFireBoost( _gameLogic );

  if ( result == EEaselBoostFireMode::Activated )
  {
    waiting = true;
    CompleteBoostFire();
  }
  else if ( result == EEaselBoostFireMode::WaitingActivation )
    waiting = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBoost::CompleteBoostFire()
{
  if ( waiting )
  {
    waiting = false;
    StartCooldown();
    WriteOffFee();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBoost::ProcessStep( int _deltaTime, int _gamelevel, int _priestessgold, LuxGameLogic* _gameLogic )
{
  // checking cooldown
  if ( coolingDownNow  )
    IncrementCurrentCooldown( _deltaTime );

  canAccess = true;

  if(_priestessgold < boostPrice)
    canBuy = false;
  else
    canBuy = true;

  vProcessStep( _deltaTime, _gameLogic );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBoost::IncrementCurrentCooldown( long _incCooldown )
{
  if( boostCooldown == 0 || _incCooldown <= 0 )
    return;   // nothing to do ()

  if( !EASEL_BOOSTS_COOLDOWN_ENABLE )
  {
    cooldownCurrent = 0;
    coolingDownNow = false;
  }
  else
  {
    cooldownCurrent += _incCooldown;
    if( cooldownCurrent >=  GetCooldown())
    {
      cooldownCurrent = 0;
      coolingDownNow = false;
    }
    else
      coolingDownNow = true;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBoost::WriteOffFee()
{
  NI_VERIFY( IsValid( easel ), "", return );

  EaselPriestess * priestess = easel->GetWorld()->GetPriestessProxy();

  int price = GetPrice();
  priestess->TakeGold(price);
}

long LuxBoost::GetCooldown() const
{
  return boostCooldown;
}

int LuxBoost::GetPrice() const
{
  return boostPrice;
}

long LuxBoost::GetCurrentCooldown() const
{
  return cooldownCurrent;
}
} //namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( LuxBoost, PF_Minigames );
