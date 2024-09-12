#include "stdafx.h"
#include "PFMaleHero.h"
#include "PFTalent.h"
#include "PFBuildings.h"
#include "PFAIWorld.h"

#include "PFAIStates.h"
#include "PFAIHelper.h"
#include "PFAIController.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
  ///////////////////////////////////////////////////////////////////////////////
  //	AI states
  ///////////////////////////////////////////////////////////////////////////////

void AIMoveToState::OnEnter()
{
#if LOG_AI_MOVE
  CVec2 pos = pHelper->pUnit->GetPosition().AsVec2D();
  DBGM( "AI move: going to %g,%g (pos %g,%g, range = %g)", target.x, target.y, pos.x, pos.y, range  );
#endif // LOG_AI_MOVE
  canCombat ? pHelper->CombatMoveTo( target ) : pHelper->MoveTo( target ); ///?? can send MoveTo every OnStep()
}

bool AIMoveToState::OnStep( float dt )
{
  if ( pHelper->pUnit->IsPositionInRange( target, range ) )
  {
#if LOG_AI_MOVE
    CVec2 pos = pHelper->pUnit->GetPosition().AsVec2D();
    DBGM( "AI move: stopped at %g,%g", pos.x, pos.y );
#endif // LOG_AI_MOVE
     //pHelper->Stop();
     return true;
  }

  if ( canCombat && pHelper->pUnit->GetCurrentTarget() )
    return false;

  if ( delay++ < AiConst::MOVE_START_DELAY() )
    return false;

  if ( pHelper->IsMoving() )
    return false;

  return true;
}


AIMoveByLineState::AIMoveByLineState( const CPtr<PFBaseAIController>& pUnit, const vector<CVec2>& _road, bool _reverse, PFAIController* ctrl )
:	AIBaseState( pUnit, !_reverse ? MOVELINEFORWARD : MOVELINEBACKWARD )
,	road( _road )
, canCombat( !_reverse )
, ctrl( ctrl )
{
  if ( _reverse )
  {
    reverse( road.begin(), road.end() );
  }
  DBGM("AI line: init rev=%d, %d points", _reverse, road.size());
}

bool AIMoveByLineState::PushNextWaypoint()
{
  // find next road waypoint depending on current unit position
  CVec2 unitPos = pHelper->pUnit->GetPosition().AsVec2D();
  int nextPoint = GetNextRoutePoint( road, unitPos );

  if ( nextPoint >= road.size() )
  {
    DBGM( "AI line: finished" );
    return false;				// whole path was completed
  }
  
  PushState( new AIMoveToState( pOwner, CVec2( road[nextPoint] ), AiConst::MOVE_BY_LINE_SENS(), canCombat ) );
  return true;
}

bool AIMoveByLineState::OnStep( float dt )
{
  if ( IsValid(ctrl) && canCombat )
  {
    if ( ctrl->TryTeleport() )
      return false;
  }

  FSMStep( dt );
  if ( GetCurrentState() == NULL )
  {
    if ( !PushNextWaypoint() )
    {
      return true;
    }
  }
  return false;
}


void AIHealingState::OnLeave()
{
  pHelper->ResetHeal();
  DBG("--- stop healing");
}

bool AIHealingState::OnStep( float dt )
{
  const PFBaseMaleHero* pHero = pHelper->pUnit;

  if ( !IsUnitValid( pHero ) )
    return true;

  if( !pHelper->IsMoving() && !pHero->IsPositionInRange( pHero->GetSpawnPosition().AsVec2D(), pHero->GetObjectSize() ) )
    pHelper->MoveTo( pHero->GetSpawnPosition().AsVec2D() );

  // wait for healing
  float health, healthMax, mana, manaMax;
  pHelper->GetLife( health, healthMax );
  pHelper->GetMana( mana, manaMax );
  return ( health >= healthMax * 0.99f && mana >= manaMax * 0.99f );
}


bool AIShoppingState::OnStep( float dt )
{
  const NDb::ConsumablesShop* pShopInfo = IsValid(pShop) ? pShop->GetConsumablesShop() : 0;
  if ( !pShopInfo )
  {
    return true;
  }

  PFBaseHero* hero = pHelper->pUnit;
 
  for ( int id = 0; id < pShopInfo->items.size(); id++ )
  {
    const NDb::Ptr<NDb::Consumable> pConsumable = pShopInfo->items[id];
    if ( !pConsumable || !hero->CanTakeConsumable( pConsumable, 1 ) || !pShop->CanBuyConsumable( hero, id ) )
    {
      continue;
    }
    //DebugTrace( "[%d:%d] %s", group, id, pConsumable->GetDBID().GetFileName().c_str() );
    EConsumableType type = IdentifyConsumable( pConsumable );
    int maxCount = 0;
    switch ( type )
    {
    case OBJECT_HEALING_POTION:
      maxCount = pHelper->pDBBots->maxHealthPotion;
      break;
    case OBJECT_ENERGY_POTION:
      {
        maxCount = pHelper->pDBBots->maxManaPotion;
        for ( int i = 0; i < pHelper->pDBBots->doNotBuyMana.size(); i++ )
        {
          if ( pHelper->pDBBots->doNotBuyMana[i]->GetDBID() == hero->GetDbHero()->GetDBID() )
          {
            maxCount = 0;
            break;
          }
        }
        break;
      }
    case OBJECT_TELEPORT_SCROLL:
      maxCount = 0; // prevent buying teleporter scrolls
      break;
    }
    if ( maxCount <= 0 )
    {
      continue;
    }

    int ownedItems = pHelper->HasConsumable( type );
    if ( ownedItems >= maxCount )
    {
      continue;				// enough potions of this type
    }

    // buy this item
    DBG( "Buy consumable %d (%s), has %d", id, pConsumable->GetDBID().GetFileName().c_str(), ownedItems );
    for ( int i = ownedItems; i < maxCount; i++ )
      pHelper->BuyConsumable( pShop, id );
  }

  return true;
}

bool AIFlagRaisingState::OnStep( float dt )
{
  if (IsValid(pFlag) && pFlag->CanRaise(pHelper->pUnit->GetFaction()))
  {
    if(!pHelper->pUnit->IsPositionInRange(pFlag->GetPosition().AsVec2D(), range))
    {
      //DevTrace("pHelper->pUnit->GetPosition()[%f,%f]", pHelper->pUnit->GetPosition().AsVec2D().x, pHelper->pUnit->GetPosition().AsVec2D().y);
      if(/*!isMovingToFlag ||*/!pHelper->IsMoving())
      {
        //DevTrace("CombatMoveTo Flag[%08x]", (int)pFlag.GetPtr());
        pHelper->CombatMoveTo(pFlag->GetPosition().AsVec2D());
        /*isMovingToFlag = true;*/
      }
    }
    else
    {
      //DevTrace("RaiseFlag[%08x]", (int)pFlag.GetPtr());
      if(pFlag->CanRaise(pHelper->pUnit->GetFaction()))
        pHelper->RaiseFlag(pFlag);
    }
  }

  return true;
}

bool AIUseTeleportState::OnStep( float dt )
{
  pHelper->UsePortal( target );
  return true;
}

void AIUseTeleportState::OnLeave()
{
  if ( IsValid(ctrl) )
  {
    //pHelper->ResetHeal();
    ctrl->GoToEnemyBase();
  }
}


void AIGoToObjectState::OnEnter()
{
  PFBaseUnit* pUnit = pTarget;
  PFBaseMovingUnit* pMovingUnit = dynamic_cast<PFBaseMovingUnit*>( pUnit );
  if ( pMovingUnit )
  {
    float range = pHelper->GetWorld()->GetAIWorld()->GetAIParameters().followRange;
    float forcedRange = pHelper->pDBBots->forcedFollowRange;
    pHelper->Follow( pTarget, range, forcedRange );
    DBG( "Follow unit %s", pTarget->GetObjectTypeName() );
  }
  else
  {
    CVec2 pos = pTarget->GetPosition().AsVec2D();
    pHelper->MoveTo( pos );
    DBG( "Go To Object %s 's position at %g,%g", pTarget->GetObjectTypeName(), pos.x, pos.y );
  }
}

bool AIGoToObjectState::OnStep( float dt )
{
  PFShop* pShop = dynamic_cast<PFShop*>( pTarget.GetPtr() );
  if ( pShop )
  {
  	int money = pHelper->pUnit->GetGold();
    if ( money < pHelper->pDBBots->minShoppingMoney )
    {
      return true;
    }
  }

  bool v = !pHelper->IsMoving();
  if ( pHelper->pUnit->GetCurrentTarget() )		// do not lost state when fighting
  {
    v = false;
  }
  if ( delay++ < AiConst::MOVE_START_DELAY() )		// wait for MoveTo command execution
  {
    v = false;
  }
  if ( v )
  {
    CVec2 pos = pHelper->pUnit->GetPosition().AsVec2D();
    DBGM( "AI move: stop detected at %g,%g", pos.x, pos.y );
  }
  return v;
}


void AIAttackUnitState::OnEnter()
{
  PFBaseUnit* pUnit = pTarget;

  pHelper->Attack(pUnit);
  DBG( "Attack unit %s", pTarget->GetObjectTypeName() );
}

//const char* AIAttackUnitState::Name = "AttackUnit";

bool AIAttackUnitState::OnStep( float dt )
{
  if ( delay++ < AiConst::MOVE_START_DELAY() )		// wait for MoveTo command execution
    return false;

  if ( pHelper->pUnit->GetCurrentTarget() )
    return false;

  return true;
}

bool EscapeFromTowerState::OnStep( float dt )
{
  bool res = AIMoveToState::OnStep(dt);

  if ( IsValid(pTower) && checkTime < 0 ) 
  {
    if ( pHelper->pUnit->IsInRange(pTower, pTower->GetAttackRange()*1.5f) )
      checkTime = 1.0f;
    else
    {
      pHelper->Stop();
      return true;
    }
  }
  else
    checkTime -= dt;

  return res;
}


//=============================================================================
//
//=============================================================================

const char *PFAIStatesEnum_ToString( const PFAIStatesEnum value )
{
  switch( value )
  {
  case NONE :
    return "NONE";
  case ESCAPEFROMTOWER:
    return "ESCAPEFROMTOWER";
  case BACKTOWARFRONT:
    return "BACKTOWARFRONT";
  case ATTACKINGTOWER:
    return "ATTACKINGTOWER";
  case FLAGRAISING:
    return "FLAGRAISING";
  case COMBATMOVE:
    return "COMBATMOVE";
  case MOVE:
    return "MOVE";
  case HEALING:
    return "HEALING";
  case SHOPPING:
    return "SHOPPING";
  case TELEPORT:
    return "TELEPORT";
  case GOTOBUILDING:
    return "GOTOBUILDING";
  case ATTACKUNIT:
    return "ATTACKUNIT";
  case MOVELINEFORWARD:
    return "MOVELINEFORWARD";
  case MOVELINEBACKWARD:
    return "MOVELINEBACKWARD";
  default:
    return "UNKNOWN";
  }
};

} // namespace
