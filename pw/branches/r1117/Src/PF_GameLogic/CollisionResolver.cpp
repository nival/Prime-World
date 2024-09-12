#include "StdAfx.h"

#include "PFBaseMovingUnit.h"
#include "PFBaseUnit.h"
#include "CommonPathFinder.h"
#include "StandartPath2.h"
#include "TileMap.h"

#include "CollisionResolver.h"

#include "../System/InlineProfiler.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
  static const float EXTRA_TRACE_SIZE = 1.0f;
  static const float MAX_PREDICT_TIME = 2.0f;  // seconds

  static const float MAX_PREDICT_PATH = 30.0f;	// meters
  static const float MAX_TIME_STEP    = 0.5f;		// seconds
  static const float MAX_PATH_STEP    = 1.0f;		// meters

  static const float MIN_WAIT_TIME = 0.2f;
  static const float MAX_WAIT_TIME = 0.5f;

  static const float DISTANCE_TO_SLOW  = 1.0f;
  static const float DISTANCE_TO_STOP  = 0.3f;
  static const float SLOW_SPEED        = 0.5f;

  static const float SCALE_RECT = (float)1/7;

  float GetSizeForCollisions(NWorld::PFBaseUnit const * pUnitA, NWorld::PFBaseUnit const * pUnitB)
  {
    if (pUnitA->IsHero())
  	  return pUnitB->GetObjectDynamicTileSize();
    else
      return pUnitB->GetObjectSize();
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CollisionResolver::CollideInfo
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionResolver::CollideInfo::Swap()
{
  // swap info
  UnitInfo* tmp1 = infoA;
  infoA = infoB;
  infoB = tmp1;
  // swap speed
  float tmp2 = speedA;
  speedA = speedB;
  speedB = tmp2;
  // swap pos
  CVec2 tmp3 = predictedPosA;
  predictedPosA = predictedPosB;
  predictedPosB = tmp3;
  // swap dir
  tmp3 = predictedDirA;
  predictedDirA = predictedDirB;
  predictedDirB = tmp3;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CollisionResolver::CollideInfo::IsAOnBackOfB() const
{
	const CVec2 relPosA = predictedPosA - predictedPosB;
	return relPosA * predictedDirB < 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CollisionResolver::CollideInfo::IsBOnBackOfA() const
{
	const CVec2 relPosB = predictedPosB - predictedPosA;
	return relPosB * predictedDirA < 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PredictedUnitState
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CollisionResolver::PredictedUnitState::PredictedUnitState( MovingUnit* unit )
  :	pUnit(unit)
  ,	pos(unit->origin)
  , dir(VNULL2)
  , dest(unit->origin)
  ,	curPoint(0)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CollisionResolver::PredictedUnitState::Advance(float toMove)
{
	if (!pUnit->pPath)				// this unit is stopped
		return true;

	while (true)
	{
		CVec2 delta = dest - pos;
		float dist = fabs(delta);

		if (dist <= toMove)
		{
			toMove -= dist;
			pos = dest;

			// get next path point ...
			if (curPoint < MovingUnit::NUM_SPLINE_POINTS - 2)
			{
				// ... from splinePoint[]
				dest = pUnit->splinePoint[curPoint + 2];
			}
			else
			{
				// ... or from pPath
				if (!pUnit->pPath)
				{
//??					NI_ALWAYS_ASSERT("unit has no path");
					return false;  // no path built
				}
				int peekIndex = curPoint - 2;
				if (!pUnit->pPath->CanPeek(peekIndex))
					return false;	 // pPath is not yet built, stop shifting
				CVec2 newPoint = pUnit->pPath->PeekPoint(peekIndex);
				if (newPoint == dest)
				{
					// path is finished
					return false;
				}
				dest = newPoint;
			}

			dir = dest - pos;
			Normalize(&dir);
			curPoint++;
			continue;
		}

		// advance position toward current destination point
		pos = pos + delta * toMove / dist;
		break;
	}

	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CollisionResolver::PredictedUnitState::IsIntersected( const PredictedUnitState &other ) const
{
	// we are comparing unit's origin + size (note: origin, not position)
	float size = GetSizeForCollisions(pUnit->pOwner, pUnit->pOwner);
	float otherSize = GetSizeForCollisions(pUnit->pOwner, other.pUnit->pOwner);

	SVector posTile = pUnit->pOwner->GetWorld()->GetTileMap()->GetTile(pos);
	SVector posTileOther = pUnit->pOwner->GetWorld()->GetTileMap()->GetTile(other.pos);

	if (posTile.x + size < posTileOther.x)
		return false;
	if (posTile.y + size < posTileOther.y)
		return false;
	if (posTileOther.x + otherSize < posTile.x)
		return false;
	if (posTileOther.y + otherSize < posTile.y)
		return false;

	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CollisionResolver
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionResolver::Resolve( const vector<PFBaseMovingUnit*> units, float timeDelta ) const
{
  int i, j;

  const int numUnits = units.size();

	{
    NI_PROFILE_BLOCK( "HugeInnerLoop" )
		// collect units for collision
		vector<UnitInfo> infos;
		infos.resize(numUnits);

		// simple optimization: compute circle instead of rect, collide circle-by-circle (very fast),
		// and if collided - then intersect rects
		int numInfos = 0;
		for (i = 0; i < numUnits; i++)
		{
			MovingUnit *unit = &units[i]->world;
			unit->speedScale = 1.0f;                           // init speedScale
			if ( unit->moveState == MOVE_STATE_SPECIAL_MOVE || // by design ...
           // unit->moveState == MOVE_STATE_DEAD         || // do not collide with corpses - skipped by MovingUnitsCollector
           // unit->moveState == MOVE_STATE_MOUNTED      || // ... - skipped by MovingUnitsCollector
					( unit->GetGhostMode() != 0 ) )                // "ghosts" are not collided
      {
        continue;
      }

      ///?? possibly, add special "bool noCollision" field and use it when needed

			// try to recreate path for blocked units
			///?? Improvement notes:
			///?? 1) performance: possibly, should do this periodically (not every Step())
			///?? 2) after some delay unit should be converted to IDLE state
			if ( (!unit->pPath && unit->moveState != MOVE_STATE_IDLE && unit->moveState != MOVE_STATE_WAITING)
					|| unit->moveState == MOVE_STATE_NO_PATH )
				unit->RecomputePath();
			// ignore unit without path (this unit is not moving, it should be locked on map)
			// (but allow idle units)
			if (!unit->pPath || unit->moveState == MOVE_STATE_IDLE)
			{
				NI_ASSERT(unit->isMarkedOnMap, "Unit without path is not marked on TileMap");
				// Only check those units, which are not marked on map - other units are processed by
				// ValidatePath().
				// Note: idle units will be processed by collision, if their idle time is less than
				// MAX_PREDICT_TIME. This is done to resolve collisions in following situation: 1st unit
				// is moving then stopped, 2nd unit is following 1st then should bypass it. Its spline
				// should be recomputed. Easiest way to detect this case is to collide using boxes ...
//				if (unit->stateTime > MAX_PREDICT_TIME)
//					continue;
			}
			// process WAITING units
			if (unit->moveState == MOVE_STATE_WAITING && unit->stateTime > unit->stateTimeout)
			{
				if (!unit->pPath)
					unit->PathFailed();
				else
					unit->SetState(MOVE_STATE_START_MOVING);
			}
			// note: here unit can be both locked or unlocked on map (for example, in MOVING or
			// BLOCKED_UNIT states, sometimes in IDLE ...)
			// setup info
			UnitInfo& info = infos[numInfos++];
			//UnitInfo& info = infos[0];
			info.unit          = unit;
			info.bounds        = GetSpeedCircle( unit, 1, EXTRA_TRACE_SIZE );
			info.speedRect     = GetSpeedRect( unit, SCALE_RECT, EXTRA_TRACE_SIZE );
			info.blockedBefore = unit->IsColliding();
			info.blockedNow    = false;
			// WAITING units not collided
			if (unit->moveState == MOVE_STATE_WAITING)
				info.blockedNow = true;
		}

		// prioritize unit processing by state
    if (numInfos > 0)
    {
      qsort(&infos[0], numInfos, sizeof(UnitInfo), &CollisionResolver::UnitInfoSorter );
    }

		// statistics
		int numCollis0 = 0, numCollis1 = 0, numCollis2 = 0, numCollis3 = 0;

		// collide each unit with others
		for (i = 0; i < numInfos; i++) // note: we will process last unit in this loop too
		{
			UnitInfo &infoA = infos[i];
			MovingUnit *unitA = infoA.unit;

			for (j = i + 1; j < numInfos; j++)
			{
				UnitInfo &infoB = infos[j];
				MovingUnit *unitB = infoB.unit;

        if ( unitB->pOwner->IsHero() && !unitA->pOwner->IsHero() && unitA->pOwner->GetFaction() == unitB->pOwner->GetFaction() )
          continue;

				if (unitA->moveState == MOVE_STATE_IDLE || unitA->moveState == MOVE_STATE_NO_PATH ||
						unitA->moveState == MOVE_STATE_WAITING)
					break;		// unit becomes blocked or idle while processing other units

				if (unitB->moveState == MOVE_STATE_IDLE || unitB->moveState == MOVE_STATE_NO_PATH ||
						unitB->moveState == MOVE_STATE_WAITING ||
            (unitB->moveState == MOVE_STATE_BLOCKED && infoB.blockedNow))
					continue;		// possible situation ...

				// prepare CollideInfo for PredictCollision()
				CollideInfo C;
				C.infoA  = &infoA;
				C.infoB  = &infoB;
				C.speedA = unitA->speed;
				C.speedB = unitB->speed;
				// collision test
				bool collided = false;
				numCollis0++;
				collided = infoA.bounds.IsIntersected(infoB.bounds);					// quick circle intersection
				if (collided)
				{
					numCollis1++;
					collided = infoA.speedRect.IsIntersected(infoB.speedRect);	// slower oriented rect intersection
					if (collided)
					{
						numCollis2++;
						collided = PredictCollision(C, MAX_PREDICT_TIME);					// precise collision test with prediction
					}
				}

				if (!collided)																								// these units are not collided, there is nothing to do
					continue;

				if (unitA->moveState == MOVE_STATE_BLOCKED && unitB->moveState == MOVE_STATE_BLOCKED)
///				if (unitA->IsColliding() && unitB->IsColliding())
				{
					// wait some random delay, allow other units to continue movement without
					// collision with unitA
					unitA->Wait(MIN_WAIT_TIME, MAX_WAIT_TIME);
					infoA.blockedNow = true;
					break;
				}

				// process collision
				numCollis3++;
				switch (C.infoA->unit->moveState)
				{
				case MOVE_STATE_MOVING:
				case MOVE_STATE_BYPASSING:
					CollideMoving(C, timeDelta);
					break;
				case MOVE_STATE_START_MOVING:
				case MOVE_STATE_START_BYPASSING:
				case MOVE_STATE_BLOCKED:
					CollideBlocked(C, timeDelta);
					break;
				default:
          NI_ALWAYS_ASSERT( NStr::StrFmt( "Unknown moveState: %d/%d", C.infoA->unit->moveState, C.infoB->unit->moveState ) );
				}
			} // end of loop for unitB

			if ( !infoA.blockedNow && unitA->moveState != MOVE_STATE_IDLE )
				CollisionIdle(unitA, infoA.blockedBefore, timeDelta);
		}

		// now, process collision with marked-on-map units (one unit is moving,
		// another unit is just stopped)
		for (i = 0; i < numInfos-1; i++) // compare pairs only
		{
			UnitInfo &infoA = infos[i];
			MovingUnit *unitA = infoA.unit;

			for (j = i + 1; j < numInfos; j++)
			{
				UnitInfo &infoB = infos[j];
				MovingUnit *unitB = infoB.unit;

        if ( unitA->pOwner->IsHero() && unitB->pOwner->GetUnitType() == NDb::UNITTYPE_SUMMON )
          continue;

				bool movingA = unitA->IsMoving() && !unitA->IsColliding();
				bool movingB = unitB->IsMoving() && !unitB->IsColliding();

				if (movingA == movingB)			// both stopped or both moving
					continue;

				// predict static units for first MAX_PREDICT_TIME seconds only
				if (!movingA && unitA->stateTime > MAX_PREDICT_TIME)
					continue;
				if (!movingB && unitB->stateTime > MAX_PREDICT_TIME)
					continue;

				// quick collision test
				if (!infoA.speedRect.IsIntersected(infoB.speedRect))
					continue;

				CollideInfo C;
				C.infoA  = &infoA;
				C.infoB  = &infoB;
				C.speedA = movingA ? unitA->speed : 0;
				C.speedB = movingB ? unitB->speed : 0;

				if (!movingA)								// now, C.A is moving, and C.B is stopped
					C.Swap();
				if (!PredictCollision(C, 2 * timeDelta))	// predict for next 2 frames only
					continue;									// not collided

        if (C.infoA->unit->pPath && C.infoA->unit->pPath->IsFinished() && IsValid(unitA->pMap) 
          && fabs(C.infoA->unit->origin - C.infoA->unit->pPath->GetFinishPoint()) < unitA->pMap->GetTileSize()
          && IsValid(C.infoA->unit->pOwner))
        {
          C.infoA->unit->pOwner->Stop();
          continue;
        }

				if (!C.infoA->unit->RecomputePath())
					C.infoA->unit->BlockedBy(C.infoB->unit);
			}
		}

		///---------------------------------
	} // end of BIG_LOOP
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SRect CollisionResolver::GetSpeedRect( MovingUnit const * unit) const
{
  return GetSpeedRect(unit, SCALE_RECT, EXTRA_TRACE_SIZE);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SRect CollisionResolver::GetSpeedRect( MovingUnit const * unit, float speedScale, float extraSize ) const
{
	float halfSize = unit->pOwner->GetObjectSize() / 2.0f;
	SRect result;
	if (!unit->IsMoving())
		speedScale = 0;

  CVec2 startPoint = unit->GetCenter();
  float backSize = halfSize + extraSize;
  float aheadSize = halfSize + extraSize + unit->speed * speedScale * unit->pOwner->GetObjectTileSize();

  //move to half forward
  //startPoint += moveDir * aheadSize;
	result.InitRect(
		startPoint,												  // position
		unit->moveDir,														// orientation
		aheadSize,			
		backSize,								
		( halfSize + extraSize ) // width
	);
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCircle CollisionResolver::GetSpeedCircle( MovingUnit* unit, float speedScale, float extraSize ) const
{
	CCircle result;
	if (!unit->IsMoving())
		speedScale = 0;
	float halfDist = unit->speed * speedScale / 2; // center will be in a middle of this path
	result.center = unit->GetCenter() + unit->moveDir * halfDist;
	result.r      = ( halfDist + unit->pOwner->GetObjectSize() / 2.0f + extraSize );
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CollisionResolver::UnitInfoSorter( const void* a, const void* b ) // static function
{
	const UnitInfo* unitInfoA = (const UnitInfo*)a;
	const UnitInfo* unitInfoB = (const UnitInfo*)b;

  int diff1 = unitInfoB->unit->pOwner->GetUnitType() - unitInfoA->unit->pOwner->GetUnitType();
  if (diff1)
    return diff1;
	// sort by moveState (smaller moveState first)
  diff1 = unitInfoA->unit->moveState - unitInfoB->unit->moveState;
	if (diff1)
		return diff1;
	///!! revert back A-B ?
	// sort by size (larger size first)
	float diff2 = unitInfoB->unit->pOwner->GetObjectSize() - unitInfoA->unit->pOwner->GetObjectSize();
	if (diff2)
		return Sign(diff2);
	// sort by speed (larger speed first)
	diff2 = unitInfoB->unit->GetUnitSpeed() - unitInfoA->unit->GetUnitSpeed();
	if (diff2)
		return Sign(diff2);
	// both items has equal keys
	// sort by world ID to keep array order (make qsort stable)
	return unitInfoA->unit->pOwner->GetObjectId() - unitInfoB->unit->pOwner->GetObjectId();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function will return time (in seconds) to collide two units. If not colliding, it will return -1.
// If units are collided in their current (initial) state, function will return 0.
bool CollisionResolver::PredictCollision( CollideInfo& C, float maxTime ) const // static
{
  NI_PROFILE_FUNCTION

	MovingUnit* unitA = C.infoA->unit;
	MovingUnit* unitB = C.infoB->unit;

///	if (unitA->ShouldLockMap() && unitB->ShouldLockMap())			// both units are stopped ...
///		return false;

	if ((C.speedA <= 0 && !unitA->ShouldLockMap()) || (C.speedB <= 0 && !unitB->ShouldLockMap()))
	{
		//DebugTrace("Invalid unitA or unitB speed: A(state=%d, speed=%g, lock=%d/%d) B(state=%d, speed=%g, lock=%d/%d), type=%d",
		//	unitA->moveState, C.speedA, unitA->ShouldLockMap(), unitA->isMarkedOnMap,
		//	unitB->moveState, C.speedB, unitB->ShouldLockMap(), unitB->isMarkedOnMap,
		//	unitA->type
		//);
		//NI_ALWAYS_ASSERT("Invalid unitA or unitB speed (more details in log)");
		return false;
	}

	NI_ASSERT(unitA->pOwner->GetObjectSize() + unitB->pOwner->GetObjectSize() < MAX_PREDICT_PATH / 2, "MAX_PREDICT_PATH is too small");

	// initialize prediction objects
	PredictedUnitState stateA(unitA);
	PredictedUnitState stateB(unitB);
	// compute maximal time interval and time step to predict
	maxTime = min(maxTime, MAX_PREDICT_TIME); //??
	float timeStep = MAX_TIME_STEP;
	if (C.speedA)
	{
		maxTime  = min(maxTime, MAX_PREDICT_PATH / C.speedA);
		timeStep = min(timeStep, MAX_PATH_STEP   / C.speedA);
	}
	if (C.speedB)
	{
		maxTime  = min(maxTime, MAX_PREDICT_PATH / C.speedB);
		timeStep = min(timeStep, MAX_PATH_STEP   / C.speedB);
	}

	// detect growing distance between units
	float dist2 = fabs2(stateA.pos - stateB.pos);
	int numChecks = 0;

	// perform prediction
	for (float curTime = 0; curTime < maxTime; curTime += timeStep)
	{
		// check collision
		if (stateA.IsIntersected(stateB))
		{
			C.collideTime   = curTime;
			C.predictedPosA = stateA.pos;
			C.predictedDirA = stateA.dir;
			C.predictedPosB = stateB.pos;
			C.predictedDirB = stateB.dir;
			return true;
		}
		// advance unit positions by a fixed time (timeStep)
		float toMoveA = C.speedA * timeStep;
		if (!stateA.Advance(toMoveA))
			return false;
		float toMoveB = C.speedB * timeStep;
		if (!stateB.Advance(toMoveB))
			return false;
		// check for reducing distance
		float dist2new = fabs2(stateA.pos - stateB.pos);
		if (dist2new >= dist2 - 0.01f)
			numChecks++;
		else
			numChecks = 0;
		dist2 = dist2new;
		if (numChecks >= 2)		// distance is not reduced for 2 iterations
			return false;
	}

	// collision has not predicted
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Should refactor this function
/// 1) backA/backB: can perform C.Swap() immediately after C.DetectCollisionSides()
void CollisionResolver::CollideMoving( CollideInfo& C, float timeDelta ) const
{
	// unitA is MOVING
	// unitB is MOVING, BYPASSING, BLOCKED etc
	MovingUnit* unitA = C.infoA->unit;
	MovingUnit* unitB = C.infoB->unit;

	// process blocked units
	if ((unitB->moveState == MOVE_STATE_COLLIDING) && (C.collideTime <= timeDelta))
	{
		// colliding with less than 2 frames
		unitB->BlockedBy(unitA);
		C.infoB->blockedNow = true;
		return;
	}

	// here: both units are moving
  bool backA = C.IsAOnBackOfB();
  bool backB = C.IsBOnBackOfA();

	if (unitA->moveState == MOVE_STATE_BYPASSING && unitA->pBlocker != unitB->pOwner)
	{
		// already bypassing someone
		if (unitB->moveState == MOVE_STATE_BYPASSING)
		{
			// colliding 2 bypassing units
			if (C.collideTime > DISTANCE_TO_STOP)
			{
				if (C.collideTime <= DISTANCE_TO_SLOW)
				{
					// slowdown one of the units
					if (backA && !backB)
						unitA->speedScale = SLOW_SPEED;
					else
						unitB->speedScale = SLOW_SPEED;
				}
				return;				// not too soon
			}
			///?? 1) may be A->B and B->A -- should correct paths for one/both units

			///?? 2) should check units relative positions, select unit to stop
			if (backA && !backB || !unitA->pOwner->IsHero() && unitB->pOwner->IsHero())
			{
				unitA->BlockedBy(unitB);
				C.infoA->blockedNow = true;
				return;
			}

			unitB->BlockedBy(unitA);
			C.infoB->blockedNow = true;
			return;
		}
	}

	// here: A is MOVING, B either MOVING or BYPASSING

	if (backA != backB)
	{
		if (backB)
		{
			C.Swap();
			unitA = C.infoA->unit;
			unitB = C.infoB->unit;
		}
		// now: A on back of B
		if (C.collideTime * C.speedA / unitA->pMap->GetTileSize() > 0)
		{
			float size = GetSizeForCollisions(unitA->pOwner, unitB->pOwner);
			if (unitA->BypassPoint(C.predictedPosB, size, 4.0f * unitA->speed))
			{
				unitA->BypassingUnit(unitB);
				return;
			}
		}
		if (C.collideTime > DISTANCE_TO_STOP)	// collision is not too soon
		{
			if (C.collideTime <= DISTANCE_TO_SLOW)
				unitA->speedScale = SLOW_SPEED;
			return;															// return anyway
		}
		// not bypassed - wait
		unitA->BlockedBy(unitB);
		C.infoA->blockedNow = true;
		return;
	}

	// here: units A and B have crossing courses

	///!! should analyze: who will free path first
	///!! possibly, compare speeds first - priority for fastest units

	if (unitA->speed >= unitB->speed && unitA->moveState != MOVE_STATE_BYPASSING)
	{
		// A is on back of B or B is already bypassing someone
		float size = GetSizeForCollisions(unitA->pOwner, unitB->pOwner);
		if (unitA->BypassPoint(C.predictedPosB, size, 4.0f * unitA->speed)) // 4 seconds of movement
		{
			unitA->BypassingUnit(unitB);
			return;
		}
	}

	if (unitA->speed < unitB->speed && unitB->moveState != MOVE_STATE_BYPASSING)
	{
		float size = GetSizeForCollisions(unitB->pOwner, unitA->pOwner);
		if (unitB->BypassPoint(C.predictedPosA, size, 4.0f * unitB->speed)) // 4 seconds of movement
		{
			unitB->BypassingUnit(unitA);
			return;
		}
	}

	if (C.collideTime > DISTANCE_TO_STOP && C.collideTime)
	{
		// slowdown one of the units
		if (backA && !backB)
			unitA->speedScale = SLOW_SPEED;
		else
			unitB->speedScale = SLOW_SPEED;
		return;
	}

	if (C.collideTime <= DISTANCE_TO_STOP)
	{
		// select, which unit will be stopped
		if (backA && !backB || !unitA->pOwner->IsHero() && unitB->pOwner->IsHero())
		{
			unitA->BlockedBy(unitB);
			C.infoA->blockedNow = true;
		}
		else
		{
			unitB->BlockedBy(unitA);
			C.infoB->blockedNow = true;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionResolver::CollideBlocked(CollideInfo& C, float timeDelta) const
{
	// This function currently supports A in start moving/bypassing or blocked condition and B in any

  // This verify checks current use condition for this function. 
  // If you plan to call it in additional cases - some refactoring may be needed.
  NI_VERIFY( C.infoA->unit->moveState == MOVE_STATE_START_MOVING
             || C.infoA->unit->moveState == MOVE_STATE_START_BYPASSING
             || C.infoA->unit->moveState == MOVE_STATE_BLOCKED,
             "Wrong unit A state for CollideBlocked function!", return; );

	// if at least one of these units is blocked on current frame, we can ignore collision
	if (C.infoA->blockedNow || C.infoB->blockedNow)
		return;

	MovingUnit* unitA = C.infoA->unit;
	MovingUnit* unitB = C.infoB->unit;

  if (unitB->IsMoving() && !unitB->IsColliding() || unitB->pOwner->IsHero() && (unitB->moveState == MOVE_STATE_START_MOVING || unitB->moveState == MOVE_STATE_START_BYPASSING))
  {
    // B has more priority than A
    if (C.collideTime <= DISTANCE_TO_STOP)
    {
      unitA->BlockedBy(unitB);
      C.infoA->blockedNow = true;
    }
    return;
  }
  else if (unitA->moveState == MOVE_STATE_START_MOVING ||	unitA->moveState == MOVE_STATE_START_BYPASSING)
  {
    // A has more priority than B
    if (C.collideTime <= DISTANCE_TO_STOP)
    {
      unitB->BlockedBy(unitA);
      C.infoB->blockedNow = true;
    }
    return;
  }

	// If we get here - both are blocked/waiting. Try to bypass.

	bool backA = C.IsAOnBackOfB();
	bool backB = C.IsBOnBackOfA();

	if (backA != backB)
	{
		if (backB)
		{
			C.Swap();
			unitA = C.infoA->unit;
			unitB = C.infoB->unit;
		}

		float size = GetSizeForCollisions(unitA->pOwner, unitB->pOwner);
		if (unitA->BypassPoint(C.predictedPosB, size, 4.0f * unitA->speed))
		{
			unitA->BypassingUnit(unitB);
			return;
		}
	}

	// here we can perform more complex analysis, but for now its simple ...
	// Can analyze: total waiting time, unit's size, relative positions etc
  if (C.collideTime <= DISTANCE_TO_STOP)
  {
    unitB->BlockedBy(unitA);
    C.infoB->blockedNow = true;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionResolver::CollisionIdle( MovingUnit* unit, bool blockedBefore, float timeDelta ) const
{
	// resume movement for units, which are no longer blocked
	// note: cannot check unit->IsColliding(), because it is not modified above

	if (!unit->pPath || unit->moveState == MOVE_STATE_MOVING)
		return;

	if (unit->moveState == MOVE_STATE_START_BYPASSING)
	{
		// keep timeout
		unit->SetState(MOVE_STATE_BYPASSING, unit->stateTimeout);
		return;
	}

	if (unit->moveState == MOVE_STATE_START_MOVING)
	{
		unit->StartMoving();
		return;
	}

	if (unit->moveState == MOVE_STATE_BLOCKED && unit->stateTime < unit->stateTimeout)
	{
		return;																// remains blocked until timeout finished
	}

	if (blockedBefore)	// blocked -> not blocked
	{
		unit->SetState(MOVE_STATE_START_MOVING);
		return;
	}

	if (unit->moveState == MOVE_STATE_BYPASSING)
	{
		if (unit->stateTime > unit->stateTimeout)
			unit->SetState(MOVE_STATE_MOVING);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_WORLD_OBJECT_NM( CollisionResolver, NWorld );
