#include "stdafx.h"
#include "../Core/GameCommand.h"
#include "../Core/Scheduler.h"
#include "PFMaleHero.h"
#include "PFTalent.h"
#include "HeroActions.h"					    
#include "PFConsumable.h"
#include "PFCommonCreep.h"				
#include "PFWorldNatureMap.h"
#include "PFMainBuilding.h"
#include "System/RandomGen.h"	
#include "System/InlineProfiler.h"

#include "PFAIController.h"
#include "PFAIContainer.h"
#include "PFAIStates.h"

#include "TargetSelectorHelper.hpp"

static const float	MAX_WAR_FRONT_DISTANCE    = 3.0f;			// maximal distance from war front which AI unit can walk
static const float  MAX_WAR_FRONT_TIMEDIST    = 100.0f;		// meters * seconds
static const float	ROAD_SHIFT_DISTANCE       = 3.0f;		  // shift road's waypoints distance for up to 3 prallel moving lines

namespace 
{
  static bool g_debugAIStates = false;
}

REGISTER_DEV_VAR("debug_ai_states", g_debugAIStates, STORAGE_NONE);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{

PFAIController::PFAIController( PFBaseHero* hero, NCore::ITransceiver* transceiver, int line, int shift )
  : PFBaseAIController(hero, transceiver)
  , lineNumber( 0 )					///?? different value
  , isRespawned( false )    // Is respawned flag. Used to start things on respawn, but after "battle start delay"
  , healing( HEAL_NONE )
  , healingTick( 0 )
  , warFrontTimeDist( 0 )
  , useConsumableDelay( 0 )
  , activateTalentDelay( 0 )
  , useTalentDelay( 0 )
  , usePotionDelay( 0 )
  , blessDelay( 0 )
  , mountDelay( 0 )
  ,findFlagDelay(0)
{
  if ( IsValid(GetHelper().pDBBots) && GetHelper().pDBBots->midOnly )
    SetLine( 1, shift );
  else
    SetLine( line, shift );
}


TalentWrapper PFAIController::GetLastTalent()
{
  const int numSlots  = NDb::KnownEnum<NDb::ETalentSlot>::sizeOf;
  const int numLevels = NDb::KnownEnum<NDb::ETalentLevel>::sizeOf;

  return TalentWrapper( GetHero(), numLevels - 1, numSlots - 1 );
}

bool PFAIController::CanUseConsumable( int slot )
{
  if ( useConsumableDelay > 0 )
  {
    return false;			// timed out
  }
  PFConsumable const* pConsumable = GetHero()->GetConsumable( slot );
  if ( !pConsumable )
  {
    return false;			// empty slot
  }
  return pConsumable->CanBeUsed();
}

void PFAIController::UseConsumable( int slot, PFLogicObject* pTarget )
{
  DBG( "UseConsumable at slot %d", slot );
  GetHelper().UseConsumable( slot, Target( pTarget ? pTarget : GetHero() ) );
  useConsumableDelay = AiConst::USE_CONSUMABLE_DELAY();
}

void PFAIController::UseConsumable( int slot, const CVec2& target )
{
  DBG( "UseConsumable at slot %d", slot );
  GetHelper().UseConsumable( slot, Target( CVec3( target, 1.0f ) ) );
  useConsumableDelay = AiConst::USE_CONSUMABLE_DELAY();
}


void PFAIController::SetLine( int num, int shift /*=0*/ )
{
	if ( num < 0 )
  {
    num = NRandom::Random( NDb::KnownEnum<NDb::ENatureRoad>::sizeOf );
  }

	lineNumber = num;
  lineShift = shift;

	if ( !GetRoute( GetHero()->GetWorld(), GetHero()->GetFaction(), lineNumber, road ) )
	{
		NI_ALWAYS_ASSERT( "SetLine: bad line number" );
	}
	else
	{
    if (lineShift && road.size() > 1)
    {
      int i;

      for (i = 0; i < road.size() - 1; i++)
      {
        ShiftWaypoint(road[i], road[i+1], lineShift, ROAD_SHIFT_DISTANCE);
      }

      // The last waypoint has an oposit refference waypoint, therefore lineShift flag is inverted
      ShiftWaypoint(road[i], road[i-1], -lineShift, ROAD_SHIFT_DISTANCE);
    }

    // Add quarters between the road and the main building, 
    // so the hero will less tend to skip last towers and quarters
    vector<PFQuarters*> quarters;
    if ( FindQuarters( GetHero()->GetWorld(), GetHero()->GetOppositeFaction(), quarters ) )
    {
      for (int i = 0; i < quarters.size(); ++i)
      {
        if (IsValid(quarters[i]) && num == (int)quarters[i]->GetRouteId())
        {
          CVec2 dstPos = quarters[i]->GetPosition().AsVec2D();
          int nextPoint = GetNextRoutePoint( road, dstPos );
          if ( nextPoint >= road.size() )
		        road.push_back( dstPos );
        }
      }
    }

		// note: currently GetRoute() will return incomplete line - it's end will be behind
		// enemy base entrance; for better results we should append enemy main building position
		vector<PFMainBuilding*> buildings;
		if ( !FindMainBuildings( GetHero()->GetWorld(), GetHero()->GetOppositeFaction(), buildings ) )
    {
      return;
    }
		PFMainBuilding* building = buildings[0];
    CVec2 lastRoadPos = road[road.size()-1];
    CVec2 dir = lastRoadPos - building->GetPosition().AsVec2D();
    dir /= dir.Length();
		CVec2 dstPos = building->GetPosition().AsVec2D() + dir * (building->GetObjectSize()*0.5f);
		road.push_back( dstPos );
	}
}

void PFAIController::WalkByRoad( bool backToBase )
{
  if ( !GetHero() || GetHero()->IsMounted() && !GetHero()->CanControlMount() )
  {
    return;
  }

	DBG( "AI queue: walk road, back=%d", backToBase );
	if ( road.empty() )
  {
    return;
  }

  //DevTrace("%08x : PFHFSM::PushState(%s)", int(this), "AIMoveByLineState");
  PushState( new AIMoveByLineState( this, road, backToBase, this ) );
}

void PFAIController::RaiseFlags()
{
  const AIBaseState* currentState = CurrentState();
  if ( currentState && ( currentState->stateType == ESCAPEFROMTOWER 
    || currentState->stateType == BACKTOWARFRONT || currentState->stateType == ATTACKINGTOWER
    || currentState->stateType == FLAGRAISING) )	// can compare pointers here
  {
    return;
  }

  PFBaseUnit* pEnemy = GetHelper().FindEnemyNear();
  if ( !pEnemy )
  {
    struct FlagPoleFinder
    {
      FlagPoleFinder() : found(false) {}
      bool operator()( PFLogicObject& _unit )
      {
        if ( _unit.GetUnitType() == NDb::UNITTYPE_FLAGPOLE )
        {
          found = true;
          unit = dynamic_cast<PFFlagpole*>(&_unit);
          
          if(unit && unit->IsRising())
          {
            found = false;
            return false;
          }
          
          return true;
        }

        return false;
      }
      bool found;
      PFFlagpole* unit;
    } flagPoleFinder;

    int targetTypesToFind = NDb::SPELLTARGET_FLAGPOLE;
    GetHero()->GetWorld()->GetAIWorld()->ForAllUnitsInRange( GetHero()->GetPosition(), GetHero()->GetVisibilityRange(), flagPoleFinder, UnitMaskingPredicate( GetHero()->GetOppositeFactionFlags(), targetTypesToFind, GetHero() ) );

    if ( !flagPoleFinder.found )
      return;

    if( flagPoleFinder.unit && flagPoleFinder.unit->CanRaise(  GetHero()->GetFaction() ) )
    {
      //DevTrace("%08x : PFHFSM::PushState(%s)", int(this), "AIFlagRaisingState");
      //IPFState* state = GetCurrentState();

      //if(state && state->GetTypeId() == AIBaseState::typeId)
      //{
      //  AIBaseState *baseState = dynamic_cast<AIBaseState*>(state);
      //  if(!baseState || (baseState && baseState->stateType != FLAGRAISING))
      //    PushState( new AIFlagRaisingState( this, flagPoleFinder.unit ) );
      //}
      //else
        PushState( new AIFlagRaisingState( this, flagPoleFinder.unit ) );
    }
  }
}

void PFAIController::GoToSpawnPos()
{
  if ( GetHero()->IsMounted() && !GetHero()->CanControlMount() )
  {
    return;
  }

	DBG("AI queue: go to spawn pos");
	PushState( new AIMoveToState( this, GetHero()->GetSpawnPosition().AsVec2D(), AiConst::MOVE_BY_LINE_SENS() ) );  // go to spwan pos
	GoToOwnBase();
}

void PFAIController::GoToShop()
{
  if ( GetHero()->IsMounted() && !GetHero()->CanControlMount() )
  {
    return;
  }

	DBG( "AI queue: go to shop" );
	int money = GetHero()->GetGold();
	if ( money < GetHelper().pDBBots->minShoppingMoney /*|| !hero->HasEmptyConsumableSlot()*/ )
	{
		DBG( "Can't shopping: no money (gold=%d)", money );
		return;																							// cannot shopping
	}

	vector<PFShop*> shops;
	if ( !FindShop( GetHero()->GetWorld(), GetHero()->GetFaction(), shops ) )
	{
		DBG( "Can't shopping: no shop found!" );
		return;
	}
	// find shop access point
	PFShop* shop = shops[0];
	// push states
	PushState( new AIShoppingState( this, shop ) );						// shopping itself
#if 0
	CVec2 dstPos = shop->GetPosition().AsVec2D();
	PushState( new AIMoveToState( this, dstPos, 0.0f ) );			// go to shop
#else
	PushState( new AIGoToObjectState( this, shop ) );
#endif
	GoToOwnBase();
}

void PFAIController::Heal( bool respawned )
{
	DBG("*** HEAL ***");
	if (!respawned && usePotionDelay <= 0)
	{
		int index = 0;
		if ( GetHelper().HasConsumable( OBJECT_HEALING_POTION, &index ) )
		{
			if ( CanUseConsumable( index ) )
			{
				UseConsumable( index );
				usePotionDelay = AiConst::USE_POTION_DELAY();		// prevent from using healing potion again for a short time
				return;
			}
		}
	}
	healing = respawned ? HEAL_HEALING : HEAL_RETREAT;
	GoToShop();
	PushState( new AIHealingState( this ) );
	GoToSpawnPos();
}

void PFAIController::RecoverMana()
{
	int index = 0;
	if ( GetHelper().HasConsumable( OBJECT_ENERGY_POTION, &index ) )
	{
		if ( CanUseConsumable( index ) )
		{
			UseConsumable( index );
			usePotionDelay = AiConst::USE_POTION_DELAY();
		}
	}
}

void PFAIController::RecoverHealth()
{
	int index = 0;
	if ( GetHelper().HasConsumable( OBJECT_HEALING_POTION, &index ) )
	{
		if ( CanUseConsumable( index ) )
		{
			UseConsumable( index );
			usePotionDelay = AiConst::USE_POTION_DELAY();
		}
	}
}

void PFAIController::ActivateTalents()
{
	// process delay
	if ( --activateTalentDelay > 0 )
  {
    return;
  }
	activateTalentDelay = AiConst::ACTIVATE_TALENT_DELAY();

	// find talent to activate
  TalentWrapper toActivate( GetHero(), 0, 0 );

	for ( TalentWrapper i = GetFirstTalent(); i.IsValid(); ++i )
	{
		if ( i.CanBeActivated() && i.IsPreferable( toActivate ) )
    {
      toActivate = i;
    }
	}

  if ( !toActivate.CanBeActivated() )
  {
    return;								// nothing to activate
  }

	// activate
	DBG( "*** Activating talent %s ***", toActivate.GetName() );
	GetHelper().ActivateTalent( toActivate );
}

void PFAIController::UseTalents()
{
	// process delay
	if ( --useTalentDelay > 0 )
  {
    return;
  }
	useTalentDelay = AiConst::USE_TALENT_DELAY();

	// enumerate abilities and use when possible
  struct ToUse
  {
    TalentWrapper talentWrapper;
    Target target;

    ToUse( const TalentWrapper& _talentWrapper, Target _target ) : talentWrapper( _talentWrapper ), target( _target ) { }

    ToUse()
    {
      talentWrapper = TalentWrapper();
      target = Target();
    }
  };

  nstl::vector<ToUse> talentsToUse;
  int bestPriority = -1;

  for ( TalentWrapper i = GetFirstTalent(); i.IsValid(); ++i )
  {
    if ( !i.IsActivated() || !i.IsActive() )
    {
      continue;
    }

    // get ability
    int priority = i.GetPriority();
		const PFTalent* pTalent = i.GetTalent();
		if ( !pTalent )
    {
      continue;
    }

    // If switchable ability was selected and it is on - do nothing (recast would toggle it off before the timeout)
    if ( ( pTalent->GetType() == NDb::ABILITYTYPE_SWITCHABLE ) && pTalent->IsOn() )
    {
      continue;
    }

    // check usability and find any target for this ability
    const CheckValidAbilityTargetCondition condition;

		Target target;
		if ( !pTalent->FindMicroAITargetTemp( target, condition ) )
    {
      continue;
    }

    NI_VERIFY( ( target.IsObject() || target.IsPosition() ), "Wrong ability target", continue; );

    if ( priority >= bestPriority )
    {
      if ( priority > bestPriority )
      {
        bestPriority = priority;
        talentsToUse.clear();
      }
      talentsToUse.push_back( ToUse( i, target ) );
    }
	}

	// use random of the bests talent

  const unsigned int numTalents = talentsToUse.size();
  if ( numTalents == 0 )
  {
    return;
  }

  int talentIndex = 0;
  if ( numTalents > 1 )
  {
    talentIndex = NRandom::Random( numTalents - 1 );
  }

  TalentWrapper toUse( talentsToUse[talentIndex].talentWrapper );
  Target target = talentsToUse[talentIndex].target;
  GetHelper().UseTalent( toUse, target );
}


void PFAIController::ProcessHealing()
{
	usePotionDelay--;

	float health, healthMax;
	GetHelper().GetLife( health, healthMax );
  
  const float c_healthFractionToRetreat = GetHelper().pDBBots->healthFractionToRetreatToBase;
  const float c_healthToRetreat = GetHelper().pDBBots->healthToRetreatToBase;
  const float c_healthToMoveBack = GetHelper().pDBBots->healthFractionToMoveToFront;
  

	bool needHealing = ( health < healthMax * c_healthFractionToRetreat || health < c_healthToRetreat );
  bool needMoveBackToFront = ( health > healthMax * c_healthToMoveBack );

	if ( healing == HEAL_NONE )
	{
		healingTick = 0;
		if ( needHealing )
    {
      Heal( false );
    }
	}
	else if ( healing != HEAL_HEALING )
	{
		// currently healing
		healingTick++;
		if ( healingTick < AiConst::ABANDON_HEALING_DELAY() && needMoveBackToFront )
		{
			// healed while walking
			// code similar to OnDie()
			Cleanup();			 // reset state machine
			healing = HEAL_NONE;
			healingTick = 0;
			DBG("*** BACK TO GAME ***");
			OnBecameIdle();
		}
	}

	float mana, manaMax;
	GetHelper().GetMana( mana, manaMax );
  if ( mana / manaMax < GetHelper().pDBBots->manaUsePotionThreshold )
  {
    RecoverMana();
  }

  if ( health / healthMax < GetHelper().pDBBots->healthUsePotionThreshold )
  {
    RecoverHealth();
  }
}

class CheckWarFrontState : public AIMoveToState
{
  CPtr<PFCreepSpawner> pSpawner;
  float checkTime;
public:
  CheckWarFrontState( 
    const CPtr<PFBaseAIController>& pUnit, 
    const PFCreepSpawner* _pSpawner, 
    const CVec2& _target ) : AIMoveToState(pUnit, _target, MAX_WAR_FRONT_DISTANCE, false) 
  {
    checkTime = 1.5f;
    pSpawner = const_cast<PFCreepSpawner*>(_pSpawner);
  }

  virtual bool OnStep( float dt )
  {
    bool res = AIMoveToState::OnStep(dt);

    if ( IsValid(pSpawner) && checkTime < 0 ) 
    {
      CVec2 warFront = pSpawner->GetFront();
      PFAIController* pUnitAICtrl = static_cast<PFAIController*>(pOwner.GetPtr());      
      if ( pUnitAICtrl &&
        pHelper->pUnit->IsPositionInRange(warFront, pHelper->pUnit->GetAttackRange()*1.5f) && 
        CompareRoutePoints( pUnitAICtrl->GetRoad(), pHelper->pUnit->GetPos(), warFront ) )
      {
        pHelper->Stop();
        return true;
      }
      else
        checkTime = 1.5f;
    }
    else
      checkTime -= dt;

    return res;
  }
};

void PFAIController::CheckWarFront( float timeDelta )
{
	if ( healing )		// do not override healing command
  {
    return;
  }

  const AIBaseState* currentState = CurrentState();
  if ( currentState && ( currentState->stateType == BACKTOWARFRONT 
                      || currentState->stateType == ESCAPEFROMTOWER
                      || currentState->stateType == FLAGRAISING ))
  {
    return;
  }

	NDb::ERoute routeId = ( NDb::ERoute ) lineNumber; //?? convert types
  PFAIWorld const* pAIWorld = GetHero()->GetWorld()->GetAIWorld();
	const PFCreepSpawner *spawner = pAIWorld->GetSpawner( GetHero()->GetOppositeFaction(), routeId );
	if ( !spawner )
  {
    return;
  }
  const CVec2 borderPoint = pAIWorld->GetBorderAtRoute( GetHero()->GetFaction(), routeId ); // most outlying tower(s)
	CVec2 warFront = spawner->GetFront(); // farthest creep
  if ( borderPoint != VNULL2 && CompareRoutePoints( road, warFront, borderPoint ) ) // find the most distant of two
  {
    warFront = borderPoint;
  }
	CVec2 unitPos  = GetHero()->GetPosition().AsVec2D();
	float warFrontDist = fabs( warFront - unitPos );

	if ( warFrontDist > MAX_WAR_FRONT_DISTANCE && !CompareRoutePoints( road, unitPos, warFront ) )
	{
		// accumulate distance * time
		warFrontTimeDist += ( warFrontDist - MAX_WAR_FRONT_DISTANCE ) * timeDelta;
	}
	else
	{
		// reset "distance * time" parameter
		warFrontTimeDist = 0;
	}

	if ( warFrontTimeDist > MAX_WAR_FRONT_TIMEDIST )
	{
    DBG("*** BACK TO WAR FRONT ***");
		// behind war front
		AIBaseState* newState = new CheckWarFrontState( this, spawner, warFront ); // (non-combat) move to war front
		newState->stateType = BACKTOWARFRONT;
		PushState(newState);
	}
}


CVec2 PFAIController::GetRoadPointByOffset( CVec2 const& pos, float offset )
{
  if ( road.size() > 1 )
  {
    int nearestPoint = 0;
    float positionDist = 0.0f;
    GetNearestPathPoint( road, pos, nearestPoint, positionDist );
    return GetOffsetPointAlongPath( road, nearestPoint, positionDist + offset );
  }
  return pos;
}

void PFAIController::AttackTower()
{
  if ( healing )		// do not override healing command
  {
    return;
  }

  const AIBaseState* currentState = CurrentState();
  if ( currentState && ( currentState->stateType == ESCAPEFROMTOWER ||
    currentState->stateType == BACKTOWARFRONT || currentState->stateType == ATTACKINGTOWER) )
  {
    return;
  }

  TowerFinder towerFinder;

  GetWorld()->GetAIWorld()->ForAllInRange( GetHero()->GetPosition(), GetHero()->GetVisibilityRange(), towerFinder, UnitMaskingPredicate(GetHero(), NDb::ESpellTarget( NDb::SPELLTARGET_TOWER | NDb::SPELLTARGET_ENEMY | NDb::SPELLTARGET_MAINBUILDING ) ));

  if ( !towerFinder.found )
    return;

  if( !towerFinder.unit->IsInRange( GetHero(), GetHero()->GetTargetingRange() ) )
  {
    DBG("*** ATTACK TOWER ***");
    AIBaseState* newState = new AIMoveToState( this, towerFinder.unit->GetPos(), GetHero()->GetTargetingRange(), true ); // walk to tower and combat auto-attack
    newState->stateType = ATTACKINGTOWER;
    PushState(newState);
  }
}

void PFAIController::DoNotAttackTower()
{
  if ( healing )		// do not override healing command
  {
    return;
  }

  const AIBaseState* currentState = CurrentState();
  if ( currentState && ( currentState->stateType == ESCAPEFROMTOWER ) )	// can compare pointers here
  {
    return;
  }

  TowerFinder towerFinder;

  GetWorld()->GetAIWorld()->ForAllInRange( GetHero()->GetPosition(), GetHero()->GetVisibilityRange(), towerFinder, UnitMaskingPredicate(GetHero(), NDb::ESpellTarget( NDb::SPELLTARGET_TOWER | NDb::SPELLTARGET_ENEMY | NDb::SPELLTARGET_MAINBUILDING ) ));

  if ( !towerFinder.found )
    return;

  float escapeTowerDistance = GetHelper().pDBBots->escapeTowerDistance;

  PFBaseUnit* pTowerUnit = dynamic_cast<PFBaseUnit*>(towerFinder.unit);
  if (pTowerUnit)
    escapeTowerDistance = pTowerUnit->GetVisibilityRange() * 1.7f;

  // negative distance means go back
  CVec2 rallyPoint = GetRoadPointByOffset( towerFinder.unit->GetPosition().AsVec2D(), -escapeTowerDistance );

  DBG("*** ESCAPE FROM TOWER ***");
  // behind war front
  AIBaseState* newState = new EscapeFromTowerState( this, pTowerUnit, rallyPoint, MAX_WAR_FRONT_DISTANCE ); // (non-combat) move to rally point
  newState->stateType = ESCAPEFROMTOWER;
  PushState(newState);
}

void PFAIController::EscapeFromTower()
{
  if ( healing )		// do not override healing command
  {
    return;
  }

  const AIBaseState* currentState = CurrentState();
  if ( currentState && ( currentState->stateType == ESCAPEFROMTOWER ) )	// can compare pointers here
  {
    return;
  }

  
  float health, healthMax;
  GetHelper().GetLife( health, healthMax );

  if (health/healthMax >= 0.95f)
    return;

  TowerFinder towerFinder;
  GetHero()->ForAllAttackersOnce( towerFinder );

  if ( !towerFinder.found )
    return;

  float escapeTowerDistance = GetHelper().pDBBots->escapeTowerDistance;

  PFBaseUnit* pTowerUnit = dynamic_cast<PFBaseUnit*>(towerFinder.unit);
  if (pTowerUnit)
    escapeTowerDistance = pTowerUnit->GetVisibilityRange() * 1.7f;

  //PFMainBuilding* pMainBuilding = dynamic_cast<PFMainBuilding*>(towerFinder.unit);
  //if (pMainBuilding )
    //escapeTowerDistance = pTowerUnit->GetAttackRange() * 2.2f;
  
  // negative distance means go back
  CVec2 rallyPoint = GetRoadPointByOffset( towerFinder.unit->GetPosition().AsVec2D(), -escapeTowerDistance );

  DBG("*** ESCAPE FROM TOWER ***");
  // behind war front
  AIBaseState* newState = new EscapeFromTowerState( this, pTowerUnit, rallyPoint, MAX_WAR_FRONT_DISTANCE ); // (non-combat) move to rally point
  newState->stateType = ESCAPEFROMTOWER;
  PushState(newState);
}

void PFAIController::OnDie()
{
	Cleanup();		// reset state machine
	healing = HEAL_NONE;
	healingTick = 0;
}

void PFAIController::OnRespawn()
{
  isRespawned = true;
  GoToShop();
}

void PFAIController::Step( float timeDelta )
{
  if ( GetWorld() && GetWorld()->GetAIWorld() && GetWorld()->GetAIWorld()->WasGameFinished() )
    return;

  PFBaseAIController::Step(timeDelta);

  if (IsDead())
    return;

  if ( useConsumableDelay > 0 )
  {
    useConsumableDelay--;
  }

  if ( GetHelper().CheckResetHealing() )
  {
    healing = HEAL_NONE;
  }

  if ( GetHero()->IsInChannelling() )
  {
    return;
  }

  if (isRespawned)
  {
    // If the hero respawned recently, he should attack enemy base, 
    // but only if we are not under "battle start delay".
    if ( GetWorld()->GetTimeElapsed() > GetHelper().pDBBots->timeToGo )
    {
      // Main AI target
      GoToEnemyBase();
      isRespawned = false;
      // Heal if needed
      Heal(true);
    }
  }

	// call parent method
	FsmStep( timeDelta );

	// work with talents
	ActivateTalents();
	UseTalents();

	// heal when needed
	ProcessHealing();

  //try raise flags in visibility range
  if(findFlagDelay++ <= AiConst::FIND_FLAG_DELAY())
  {
    RaiseFlags();
    findFlagDelay = 0;
  }

  // Если не форпост - то атакуем башню
  if ( !GetHelper().pDBBots->midOnly )
    AttackTower();
  else
    DoNotAttackTower();

  // escape from attacking tower
  EscapeFromTower();

	// check war front
	CheckWarFront( timeDelta );

  if (g_debugAIStates && GetCurrentStateName())
  {
    CVec3 pos = GetHero()->GetPosition();
    pos.z += 6.0f;
    Render::Color white( 255, 255, 255, 255 );
    Render::DebugRenderer::DrawText3D( GetCurrentStateName(), pos, 20, white);
  }
}

void PFAIController::OnBecameIdle()
{
	DBG( "*** IDLE ***" );

  // If hero is idle after respawn - he shouldn't attack. 
  // He has another logic to handle the "after respawn state".
  if (!isRespawned)
  {
    GoToEnemyBase();
  }
}

void PFAIController::GoToEnemyBase() 
{ 
  WalkByRoad( false );
}

bool PFAIController::TryTeleport()
{
  if ( GetWorld()->GetTimeElapsed() < GetHelper().pDBBots->timeToTeleport  )
    return false;

  PFTower* tower = 0;
  vector<PFAIWorld::BuildingsRoute>::iterator route = GetWorld()->GetAIWorld()->GetRoute( GetHero()->GetFaction(), (NDb::ERoute)lineNumber );

  vector<PFAIWorld::BuildingsRoute::RouteLevel>::iterator iLevel;
  for (int i = 0; i < route->levels.size(); ++i)
  {
    bool isFound = false;
    iLevel = route->GetLevel(i);
    for (int towerIdx = 0; towerIdx < iLevel->towersIDs.size(); ++towerIdx)
    {
      CObjectBase* pObjectBase = GetWorld()->GetObject(iLevel->towersIDs[towerIdx]);
      if (pObjectBase->GetTypeId() == PFTower::typeId)
      {
        PFTower* foundTower = static_cast<PFTower*>(pObjectBase);
        if (!foundTower->IsDead())
        {
          tower = foundTower;
          isFound = true;
          break;
        }
      }
    }
    if (isFound)
      break;
  }

  if ( !tower )
    return false;

  CVec2 dist = GetHelper().pUnit->GetPos() - tower->GetPos();
  if ( dist.Length() < 50.0f )
    return false;

  if ( GetHero()->GetFaction() == NDb::FACTION_BURN )
  {
    if ( GetHelper().pUnit->GetPos().x < tower->GetPos().x )
    {
      return false;
    }
  }
  if ( GetHero()->GetFaction() == NDb::FACTION_FREEZE )
  {
    if ( GetHelper().pUnit->GetPos().x > tower->GetPos().x )
    {
      return false;
    }
  }

  Target target( tower->GetPos() );
  bool portalReady = GetHero()->GetPortal()->CanBeUsed();
  if ( portalReady )
  {
    bool canCast = !GetHero()->GetPortal()->CheckCastLimitations( target );
    if ( canCast )
    {
      PushState( new AIUseTeleportState( this, target ) );
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}

} // namespace

BASIC_REGISTER_CLASS(NWorld::PFAIController)