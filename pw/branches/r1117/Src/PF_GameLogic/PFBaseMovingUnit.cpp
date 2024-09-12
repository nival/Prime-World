#include "stdafx.h"
#include "StandartPath2.h"
#include "StaticPathInternal.h"
#include "PFBaseMovingUnit.h"
#include "WarFog.h"
#include "TileMap.h"
#include "PathMap.h"
#include "PFWorldNatureMap.h"
#include "PFVoxelMap.h"
#include "CommonPathFinder.h"
#include "RoutePathFinder.h"
#include "PathChecker.h"
#include "PFStatistics.h"
#include "CollisionResolver.h"
#include "System/Bresenham.h"
#include "System/InlineProfiler.h"
#include "System/LogFileName.h"

#if defined(VISUAL_CUTTED)
#include "../Game/PF/Audit/ClientStubs.h"
#endif

#include "PFClientBaseMovingUnit.h"
#include "PFClientCreature.h"

#include "ClientVisibilityHelper.h"

namespace
{
  struct ScopedFlag : NonCopyable
  {
    explicit ScopedFlag(bool& flag)
      : flag(flag)
    {
      flag = true;
    }

    ~ScopedFlag()
    {
      flag = false;
    }
  private:
    ScopedFlag();

    bool& flag;
  };
}


/************************************************************\
	Some problems:
	- check the following places:
	  * pWorld, GetWorld()
	  - pOwner calls (some calls should go from local unit, some - from world)
	  - handRestrict
	- check access to PFBaseMovingUnit::world  (in h-file too!)
\************************************************************/

// synchronous/asynchronous code control (mostly for debugging)
// Debug: choose unit to visualize as client
// error detection
//#define CATCH_ASYNC_STATES			1		// catch invalid states when calling MakeAsynchronous(); unstable, so disabled
																		// (possible assert in correct situation: calling MakeAsynchronous() from WORLD phase)

// debugging
//#define DISABLE_PATH_SMOOTHING	1		// for testing
//#define RECOVER_TEST						1		// test lock recover capabilities (allows to disable it from console)
//#define DEBUG_COLLISION					1

#define RANDOM_MAX						1024

namespace
{
  //len in tiles from which we begin to use rout path finder
  static const int ROUTE_PATH_USAGE_LEN = 100;
  bool g_dumpPath=false;
}

namespace NWorld
{
static bool g_lockMove = false;							// debug: disable movement of WORLD unit (for asynchronous tests)

static bool g_reversePathOff = false;

static const float BYPASSING_TIMEOUT = 0.5f;
static const float BLOCKED_TIMEOUT   = 0.1f;
//static const float MAX_MOVE_DELAY    = 0.5f;  // seconds
static const float STD_FRAME_LENGTH  = 0.1f;  // seconds
static const float MIN_ASYNC_TIME    = STD_FRAME_LENGTH;

static float maxLocalSpeedCoeff = 0.5f;				// maximal difference (normalized) between speed of local and world units
static float maxLocalSpeedDist  = 10.0f;			// take better name? distance between local and world units when modified speed is saturated
static float maxDistToMergePath = 2.0f;				// maximal distance between units (in unit size units) when we can switch local unit to
																							// use path of world unit for faster synchronization

// constants to control incremental path rebuild
static const float MAX_INCREMENTAL_DELTA = 3.0f; // meters
static const int   MAX_INCREMENTAL_TIMES = 10;   // number of incremental updates until full rebuild

static const int MAX_RECALC_PATH_PER_STEP = 10;  // Maximum path recalculation tries per unit in one step

MovingUnit::MovingUnit(const CVec3 &pos, const CVec2 & direction, TileMap *pTileMap, const NDb::Unit &unitDesc)
: pMap(pTileMap)
, pOwner( 0 )
, origin( pos.AsVec2D() )
, moveState(MOVE_STATE_IDLE)
, moveFlags(0)
, stateTime(STD_FRAME_LENGTH) // allow delayed MoveTo() on spawn
, stateTimeout(0.0f)
, timeStanding(0.0f)
, speed(0.0f)
, speedScale(1.0f)
, ghostModeIndex(-1)
, vShortTarget(VNULL2)
, vFarTarget(VNULL2)
, vLastMoveTarget(VNULL2)
, stopDistance(0.0f)
, pStaticPath(NULL)
, pPath(NULL)
, isMarkedOnMap(false)
, moveDir(direction)  // non-null vector
, pAttached(NULL)
, followDistance(-1.0f)
, pFollowed(NULL)
, isFollowing(false)
, pBlocker(NULL)
, numIncrementalUpdates(0)
, bSplineRequiresExtraPoint(false)
, curGhostMode(0)
, holdingPosition(false)
, evading(false)
, chasing(false)
, isFollowingForced(false)
, ignoreCollision(false)
{
	splinePoint.resize(NUM_SPLINE_POINTS);
	splineTiles.resize(NUM_SPLINE_POINTS * MAX_SPLINE_TILES);
  ClearSpline();
}

void MovingUnit::Init(PFBaseMovingUnit *_pOwner )
{
  pOwner = _pOwner;

  InitMapMode();
  PlaceUnit( origin );
	MarkTiles();
  pathFindingSteps = GetPathFindingSteps();
}



void MovingUnit::InitMapMode()
{
	if ( GetGhostMode() != 0 )
	{
    mapMode = 0;
    mapModeStatic = 0;

    if ( ( GetGhostMode() & NDb::GHOSTMOVEMODE_IGNORESTATIC ) == 0 )
      mapModeStatic |= MAP_MODE_STATIC;
    if ( ( GetGhostMode() & NDb::GHOSTMOVEMODE_IGNOREBUILDINGS ) == 0 )
      mapModeStatic |= MAP_MODE_BUILDING;
    if ( ( GetGhostMode() & NDb::GHOSTMOVEMODE_IGNOREDYNAMIC ) == 0 )
      mapMode |= MAP_MODE_DYNAMIC;
	}
	else
	{
		mapMode       = MAP_MODE_DYNAMIC;
    mapModeStatic = MAP_MODE_ALL_STATICS;
	}

  mapModeAll = mapMode | mapModeStatic;
  if ( !pOwner->IsHero() && ( ( mapModeAll & MAP_MODE_DYNAMIC ) != 0 ) )
    mapModeAll |= MAP_MODE_IDLE;
}

void MovingUnit::RecalculateGhostMode()
{
  curGhostMode = 0;

  for ( int i = ghostMode.size() - 1; i >= 0; i-- )
  {
    if ( ghostMode[i].override )
    {
      curGhostMode = ghostMode[i].mode;
      return;
    }
    else
    {
      curGhostMode |= ghostMode[i].mode;
    }
  }
}

void MovingUnit::ApplyGhostMode()
{
  RecalculateGhostMode();
  UnmarkTiles();
  InitMapMode();
  MarkTiles();
}

int MovingUnit::SetGhostMode( int _mode, bool _override )
{
  ghostModeIndex++;
  ghostMode.push_back( GhostModeType( ghostModeIndex, _mode, _override ) );
  
  ApplyGhostMode();

  return ghostModeIndex;
}

void MovingUnit::ResetGhostMode( int _index )
{
  bool isIndexFound = false;

  for ( vector<GhostModeType>::iterator iter = ghostMode.end() - 1; iter >= ghostMode.begin(); iter-- )
  {
    if ( iter->index == _index )
    {
      ghostMode.erase( iter );
      isIndexFound = true;

      if ( ghostMode.empty() )
      {
        ghostModeIndex = -1;
      }

      break;
    }
  }
  NI_VERIFY( isIndexFound, NStr::StrFmt( "GhostMode modifier with index %d not found", _index ), return );

  ApplyGhostMode();
}

const CVec2 MovingUnit::GetCenter(CVec2 const& vec) const
{
  return vec;
}

const CVec2 MovingUnit::GetOrigin(CVec2 const& vec) const
{
  return vec;
}

void MovingUnit::AttachUnit(CPtr<PFBaseMovingUnit> const& pUnit)
{
	NI_VERIFY(IsValid(pUnit), "Trying to attach invalid unit!", return;);

	DetachUnit();
	pAttached = pUnit;
	MovingUnit &other = pAttached->world;
	other.SetState( MOVE_STATE_MOUNTED );
	other.UnmarkTiles();
}

void MovingUnit::DetachUnit()
{
	if (IsValid(pAttached))
	{
		MovingUnit &other = pAttached->world;
		other.moveState = MOVE_STATE_IDLE;					// prevent assert on Stop (bypass error detection)
		other.TeleportTo(other.GetCenter());				// place in nearest available position
		// NOTE: will not collide with moving unit; example: when detaching unit while moving,
		// both units will became locked (until recovered)
	}
	pAttached = NULL;
}

void MovingUnit::FollowTo( const CPtr<PFBaseMovingUnit>& pUnit, bool forced )
{
  if ( pUnit == pFollowed )
  {
    return;
  }

	Stop();
  if ( IsUnitValid( pUnit ) )
  {
    pFollowed      = pUnit;
    followDistance = fabs( pUnit->GetPosition().AsVec2D() - GetCenter() );
    isFollowing    = true;
    isFollowingForced = forced;
  }
  else if( !isFollowingForced || forced )
  {
    pFollowed      = NULL;
    followDistance = -1.0f;
    isFollowing    = false;
    isFollowingForced = false;
  }
}

void MovingUnit::BlockedBy(MovingUnit *otherUnit)
{
	if (moveState == MOVE_STATE_NO_PATH)
		return;		// no path has higher priority
	NI_ASSERT(otherUnit != this, "Bad 'otherUnit'");

	pBlocker = otherUnit->pOwner;
	SetState( MOVE_STATE_BLOCKED, BLOCKED_TIMEOUT );
	MarkTiles();
}

void MovingUnit::BypassingUnit(MovingUnit *otherUnit)
{
	NI_ASSERT(otherUnit != this, "Bad 'otherUnit'");
	pBlocker = otherUnit->pOwner;
	SetState(MOVE_STATE_START_BYPASSING, BYPASSING_TIMEOUT);
}

void MovingUnit::PathFailed()
{
	if ( moveState == MOVE_STATE_IDLE )
	{
		// NI_ALWAYS_ASSERT( "PathFailed() while not moving" ); //?? remove this ?
		return;
	}

  if ( fabs2( vFarTarget - origin ) <= fabs2( pMap->GetTileSize() * 2.0f ) )
	{
		// path is finished
		Stop();
		return;
	}

	SetState( MOVE_STATE_NO_PATH );
	MarkTiles();
}

void MovingUnit::Wait(float minTime, float maxTime)
{
	float time = minTime;
	if (maxTime > 0)
	{
		time += pOwner->random / (float)RANDOM_MAX * (maxTime - minTime);
	}
	SetState( MOVE_STATE_WAITING, time );
	MarkTiles();
}

bool MovingUnit::BypassPoint(CVec2 const& point, int pointSize, float maxOverhead)
{
  NI_PROFILE_FUNCTION

	MapModeChanger mode(mapMode, pMap);
	// lock larger rect ...
	pMap->MarkUnitTiles(point, pointSize, true, pOwner->IsRounded());
	bool result = RecomputePath(ceil(maxOverhead / pMap->GetTileSize()));
	pMap->MarkUnitTiles(point, pointSize, false, pOwner->IsRounded());
	return result;
}

void MovingUnit::SetState(EMoveState newState, float timeout)
{
	if (newState == MOVE_STATE_START_MOVING ||
			newState == MOVE_STATE_START_BYPASSING ||
			newState == MOVE_STATE_MOVING ||
			newState == MOVE_STATE_BYPASSING)
	{
		NI_ASSERT(pPath, "pPath is NULL");
	}

	NI_ASSERT(moveState != MOVE_STATE_MOUNTED, "Changing moveState while mounted!");

#if !NO_MERGE
#  if CATCH_ASYNC_STATES
	// local unit should not be modified when owner is synchronous ... let's check it!
	NI_ASSERT(!(type == LOCAL && pOwner->isSync && pOwner->world.moveState != newState), "Found Local.SetState for synchronous unit!");
#  endif
#endif

	if (moveState == newState)
	{
		// state is not changed, should update timeout
		stateTimeout = stateTime + timeout;
	}
	else
	{
		moveState    = newState;
		stateTimeout = timeout;
		stateTime    = 0;
	}
}

void MovingUnit::StartMoving()
{
	NI_ASSERT(pPath, "pPath is NULL");
	SetState( MOVE_STATE_MOVING );
  UnmarkTiles();
	// reset collision state
	pBlocker = NULL;
}

bool MovingUnit::ShouldLockMap() const
{
  const bool isInGhostMove  = ( GetGhostMode() != 0 );
  const bool isStateLocking = ( ( moveState == MOVE_STATE_IDLE )      || ( moveState == MOVE_STATE_WAITING ) ||
                                ( moveState == MOVE_STATE_COLLIDING ) || ( moveState == MOVE_STATE_BLOCKED ) ||
                                ( moveState == MOVE_STATE_NO_PATH ) );

  return ( !isInGhostMove && isStateLocking );
}

inline void MovingUnit::MarkTilesInternal( bool mark )
{
  if(!IsValid(pOwner))
    return;

  {
    MapModeChanger mode( mapMode, pMap );
    pMap->MarkUnitTiles( origin, pOwner->GetObjectDynamicTileSize(), mark, pOwner->IsRounded() );
    // We need mode.~MapModeChanger() here
  }

  if ( mapMode == MAP_MODE_DYNAMIC )
  {
    MapModeChanger mode( MAP_MODE_IDLE, pMap );
    pMap->MarkUnitTiles( origin, pOwner->GetObjectTileSize(), mark, pOwner->IsRounded() );
  }

  isMarkedOnMap = mark;
}

inline void MovingUnit::MarkTiles()
{
	if ( ShouldLockMap() && !isMarkedOnMap )
  {
    MarkTilesInternal( true );
  }
}

inline void MovingUnit::UnmarkTiles( bool forced /* = false */ )
{
	if ( ( forced || !ShouldLockMap() ) && isMarkedOnMap )
	{
    MarkTilesInternal( false );
  }
}

void MovingUnit::SetCenter(const CVec2& pos)
{
	origin = pos;
	pOwner->position = GetCenter3();
}

void MovingUnit::SetOrigin(const CVec2& pos)
{
	origin = pos;
	pOwner->position = GetCenter3();
}

void MovingUnit::UpdateMoveDir( const CVec2& dst )
{
  CVec2 dir = dst - origin;
  if ( fabs2( dir ) < 0.0001f )
  {
    return;	// keep old direction
  }

  moveDir = dir;
  Normalize( &moveDir );
}

int MovingUnit::GetPathFindingSteps() const
{
  if ( IsValid( pOwner ) )
  {
    if ( IsValid( pOwner->GetMasterUnit() ) )
    {
      if ( pOwner->GetMasterUnit()->DbUnitDesc() )
      {
        return pOwner->GetMasterUnit()->DbUnitDesc()->pathFindingSteps;
      }
      else
      {
        return 1;
      }
    }
    else
    {
      if ( pOwner->DbUnitDesc() )
      {
        return pOwner->DbUnitDesc()->pathFindingSteps;
      }
      else
      {
        return 1;
      }
    }
  }

  return 1;
}

PFBaseUnit* MovingUnit::GetRealOwner() const
{
  if ( IsValid( pOwner ) )
  {
    if ( IsValid( pOwner->GetMasterUnit() ) )
    {
      return pOwner->GetMasterUnit();
    }
    return pOwner;
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Client notifications
///////////////////////////////////////////////////////////////////////////////////////////////////
STARFORCE_FORCE_INLINE void MovingUnit::NotifyClientMove( bool animate )
{
  using namespace NGameX;

  struct Local
  {
    static inline bool IsVisibleForPlayer(NWorld::PFLogicObject* const worldObject, PFClientLogicObject* const clientObject)
    {
      const ClientVisibilityFlags flags(ClientVisibilityHelper::GetFlags(clientObject));

      if (ClientVisibilityHelper::IsVisibleForPlayer(flags))
        return true;

      const CDynamicCast<PFClientCreature> creature(clientObject);

      if (!IsValid(creature))
        return false;

      if (!ClientVisibilityHelper::IsPartialVisibilityApplicable(flags))
        return false;

      return creature->IsPartiallyVisible();
    }
  };

  if (!IsValid(pOwner))
    return;
  if (!IsValid(pOwner->ClientObject()))
    return;

  if (!Local::IsVisibleForPlayer(pOwner, pOwner->ClientObject()))
    return;

  pOwner->ClientObject()->OnMoveTo( GetCenter(), animate );
}


STARFORCE_FORCE_INLINE void MovingUnit::NotifyClientStop()
{
	if ( IsValid(pOwner) && IsValid( pOwner->ClientObject() ) )
		pOwner->ClientObject()->OnStop();
}


STARFORCE_FORCE_INLINE void MovingUnit::NotifyClientTeleport()
{
	if ( IsValid(pOwner) && IsValid( pOwner->ClientObject() ) )
  {
    pOwner->ClientObject()->OnTeleportTo( GetCenter() );
  }
}

STARFORCE_FORCE_INLINE bool MovingUnit::ClientIsVisible() const
{
	if ( IsValid(pOwner) && IsValid( pOwner->ClientObject() ) )
  {
    return pOwner->ClientObject()->IsVisible();
  }
  
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Other notifications
///////////////////////////////////////////////////////////////////////////////////////////////////
inline void MovingUnit::NotifyMoving( bool teleported )
{
	timeStanding = 0;
	pOwner->NotifyMoving( teleported );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Path building tools
///////////////////////////////////////////////////////////////////////////////////////////////////
bool MovingUnit::UseRoutePathFinder(SVector const & startPoint, SVector const & endPoint) const
{
  // Don't use routes for creeps. they have way points
  // [AV] In my opinion only (true)heroes should use such stuff
  if ( pOwner->IsCreep() )
    return false;

  // Use route pathfinder only for long distances
  SVector pointsDelta(startPoint - endPoint);
  if (pointsDelta * pointsDelta < ROUTE_PATH_USAGE_LEN * ROUTE_PATH_USAGE_LEN)
    return false;

  // Use routes only if map settings allow that
  return pOwner->GetWorld()->GetNatureMap()->GetUseRoadInPathFinding();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CCommonStaticPath* MovingUnit::CreateStaticPath( const SVector& start, const SVector& end )
{
  MapModeChanger mode( mapModeStatic, pMap );
  // validate start and end points
  if ( pMap->IsPointOutsideMap( start.x, start.y )  || pMap->IsPointOutsideMap( end.x, end.y ))
    return 0;

  Pathfinding::RoutePathFinder * routePathFinder = GetRoutePathFinder();
  Pathfinding::CCommonPathFinder * pathFinder = GetPathFinder();

  // build path
  pathFinder->SetChecking(pChecking);
  
  bool useRoutePathFinder = UseRoutePathFinder(start, end);

  int routePathLength = useRoutePathFinder? routePathFinder->FindPath( start, end, pOwner->GetUnitRadius(), pathFindingSteps ): 0;

  //means no path if 0
  if (!routePathLength)
    routePathLength = INT_MAX;

  const vector<SVector> & routePath = routePathFinder->GetPath();
  const vector<SVector> & normalPath = pathFinder->GetCurrentPath();

  int commonPathLength = INT_MAX;
  if ( pathFinder->CreatePath( pOwner->GetUnitRadius(), pOwner->GetUnitRadius(), start, end, start, pChecking, -1, pathFindingSteps ) )
  {
    commonPathLength = Pathfinding::CalculatePathLen(normalPath, 0, pathFinder->GetPathLength());
  }

  if (commonPathLength == INT_MAX )
  {
    return 0;
  }

  bool shouldUseRoutPathFinder = (routePathLength < commonPathLength);

  if (shouldUseRoutPathFinder)
  {
    if ( g_dumpPath )
    {
      pMap->Dump( NDebug::GenerateDebugFileName( "path", "tga" ).c_str(), NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, 0, &routePath );
      g_dumpPath = false;
    }
    return new CCommonStaticPath( pOwner->GetWorld(), routePath, routePath.size() );
  }
  else 
  {
    if ( g_dumpPath )
    {
      vector<SVector> currentPath;
      currentPath.insert( currentPath.end(), normalPath.begin(), normalPath.begin()+pathFinder->GetPathLength() );
      pMap->Dump( NDebug::GenerateDebugFileName( "path", "tga" ).c_str(), NWorld::MAP_MODE_BUILDING | NWorld::MAP_MODE_STATIC, &currentPath );
      g_dumpPath = false;
    }
    return new CCommonStaticPath( pOwner->GetWorld(), normalPath, pathFinder->GetPathLength() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CStandartPath2* MovingUnit::CreateStandartPath()
{
  MapModeChanger mode( mapModeAll, pMap );

  int objectTileSize= pOwner->GetObjectTileSize();
  int objectDynTileSize = pOwner->GetObjectDynamicTileSize();

  CStandartPath2* pPath = new CStandartPath2( GetPathFinder(), objectTileSize, pOwner->IsHero() ? objectDynTileSize : objectTileSize, pStaticPath, pChecking, origin, vFarTarget, pMap, pathFindingSteps );
  vFarTarget = pPath->GetFinishPoint();
  return pPath;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// Will create path from vCurrentPos to vFarTarget.
// Function assumes that unit's tiles are not marked.
// References in B2:
// - CreateStaticPathToPoint()
// - CBasePathUnit::CreateBigStaticPath()
// - CInGroupPathBasis::CanGoToFormationPos()
bool MovingUnit::CreatePath( bool needReversePath )
{
	NI_ASSERT(pMap, "No TileMap object!");

  if ( g_reversePathOff )
    needReversePath = false;

  SVector start = pMap->GetTile(origin);
  SVector end   = pMap->GetTile(vFarTarget);

  // —мотрим пр€мой путь
  pStaticPath = CreateStaticPath( start, end );
  if ( !pStaticPath )
  {
    Stop();
    return false;
  }
  
  CVec2 reverseTarget = pMap->GetPointByTile( start );

  // ≈сли хотим более качественно найти путь ( дл€ героев ), то смотрим и обратный путь
  CObj<CCommonStaticPath> pStaticPathReverse;
  if ( needReversePath )
  {
    CVec2 originalTarget = pMap->GetPointByTile( end );
	  if ( pChecking )
    {
      pChecking = new RangeChecking( reverseTarget, pOwner, stopDistance );
    }
    // »щем путь от конца уже найденного пути
    pStaticPathReverse = CreateStaticPath( pStaticPath->GetFinishTile(), start );

    if ( pChecking )
    {
      pChecking = new RangeChecking( originalTarget, pOwner, stopDistance );
    }
  }

  // Ќичего не нашли - выходим
  if ( !pStaticPath && !pStaticPathReverse )
  {
    Stop();
    return false;
  }
  // Ќашли только обратный путь - примен€ем его
  else if ( !pStaticPath && pStaticPathReverse )
  {
    pStaticPath = pStaticPathReverse;
    pStaticPath->ReversePath();
  }
  // Ќашли оба - смотрим тот, который короче
  else if ( pStaticPath && pStaticPathReverse )
  {
    if ( pStaticPath->GetLength() > pStaticPathReverse->GetLength() )
    {
      pStaticPath = pStaticPathReverse;
      pStaticPath->ReversePath();
    }
  }

  NI_VERIFY(pStaticPath->GetLength(), "Static path with 0 len was created? 0_o", return false);

  pPath = CreateStandartPath();

  vShortTarget = origin;
	return true;
}

struct PathChecker : public IPathValidator
{
	int maxOverhead;

	PathChecker(int _maxOverhead)
	:	maxOverhead(_maxOverhead)
	{}
	virtual bool CheckPath(int prevPathLen, int newPathLen)
	{
		return (prevPathLen + maxOverhead >= newPathLen);
	}
};

bool MovingUnit::MoveToShort(CVec2 dest)
{
  MapModeChanger mode(mapModeAll, pMap);

  bool ret = true;
	bool wasMarkedOnMap = isMarkedOnMap;
  bool needUpdate = false;
  UnmarkTiles( true );

  {
    NI_PROFILE_BLOCK( "RecalcPath" );

	  if (!pPath)
	  {
		  MoveTo(dest, 0, 0);
      needUpdate = true;
	  }
	  else
	  {
      if (pPath->GetFinishPoint() != pMap->GetPointByTile(pMap->GetTile(dest)))
      {
		    // numSplineTiles = number of currently skipped path tiles; real length of current
		    // path is (numSplineTiles + pPath->remainingLength)
        int allowedOverhead = -1;
		    PathChecker checker(allowedOverhead + numSplineTiles);
        ret = pPath->CalcShortPath(pMap->GetTile(dest), origin, pMap->GetTile(origin /* splineTiles[0]*/), allowedOverhead >= 0 ? &checker : NULL, pathFindingSteps );
        needUpdate = true;
      }
	  }
  }

	if ( wasMarkedOnMap )
  {
    MarkTiles();
  }

	if (!ret)
		return false;

	if (needUpdate && !UpdatePath())				// rebuild spline etc
		return false;

	NI_ASSERT(pPath, "pPath is NULL");
	return true;
}

bool MovingUnit::RecomputePath(int allowedOverhead)
{
	MapModeChanger mode(mapModeAll, pMap);

	bool ret;
	bool wasMarkedOnMap = isMarkedOnMap;
  UnmarkTiles( true );

  {
    NI_PROFILE_BLOCK( "RecalcPath" );

	  if (!pPath)
	  {
      ret = CreatePath( GetRealOwner() ? GetRealOwner()->IsHero() : false );
	  }
	  else
	  {
		  // numSplineTiles = number of currently skipped path tiles; real length of current
		  // path is (numSplineTiles + pPath->remainingLength)
		  PathChecker checker(allowedOverhead + numSplineTiles);
      ret = pPath->RecalcPath( origin, pMap->GetTile(origin /* splineTiles[0]*/), allowedOverhead >= 0 ? &checker : NULL, pathFindingSteps );
	  }
  }

	if ( wasMarkedOnMap )
  {
    MarkTiles();
  }

	if (!ret)
		return false;

	if (!UpdatePath())				// rebuild spline etc
		return false;

	NI_ASSERT(pPath, "pPath is NULL");
	return true;
}

// Based on B2's CStandartSmoothPathBasis::Init()
// Performs additional path validation, plus reinitializes spline.
// Returns 'false' when created path is empty.
// Note: result value of UpdatePath is equals to (pPath != NULL)
bool MovingUnit::UpdatePath()
{
	MapModeChanger mode(mapModeAll, pMap);

	ClearSpline();
	if (pPath)
	{
		if (pPath->IsFinished() || pPath->GetStartPoint() == pPath->GetFinishPoint())
			pPath = 0;			// reached path finish point, remove path
	}

	if (!pPath)
		return false;

  bSplineRequiresExtraPoint = false;

	// prepare spline
  pPath->Shift( 1, pathFindingSteps );		// skip first path point, should equals to start point
	// initialize spline; note: we require working path between points 1 and 2
	InitSpline(true);		// now, path will be between spline control points 2 and 3
	InitSpline();				// now, 1st part of path will be between points 1 and 2
	InitSpline();				// now, 1st part of path will be between points 1 and 2
	//StraightSpline();
	// update moveDir before movement take place
	UpdateMoveDir(pPath->PeekPoint(0));

  // Check from TickMove
  if ( ( pPath->IsFinished() && origin == pPath->GetFinishPoint() ) ||
    ( splinePoint[0] == splinePoint[1] && splinePoint[1] == splinePoint[2] && splinePoint[2] == splinePoint[3] ) )
    return false;

	return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Walking along spline path
///////////////////////////////////////////////////////////////////////////////////////////////////

bool MovingUnit::CheckSplineControlPoint()
{
	SVector p0 = pMap->GetTile(pPath->PeekPoint(0));
	SVector p1 = pMap->GetTile(pPath->PeekPoint(1));
  //NI_ASSERT(abs(p0.x - p1.x) <= 1 && abs(p0.y - p1.y) <= 1, "Too far!");

	// direction p0->p1
	SVector dir1 = p1 - p0;
  SVector dir1Normalized = dir1;

  // Ugly hack, to handle baggy pathfinder behaviour, when it generates path with holes
  if (abs(dir1Normalized.x)==2)
    dir1Normalized.x *= 0.5f;
  if (abs(dir1Normalized.y)==2)
    dir1Normalized.y *= 0.5f;

	// remember 2 latest movement directions
	SVector dirP0 = splineDir0;
	SVector dirP1 = splineDir1;
	if (dirP0 != dir1Normalized)
	{
		splineDir1 = splineDir0;
		splineDir0 = dir1Normalized;
	}

  SVector dirN;
  dirN = dir1;
  dirN.TurnLeft();

	// direction was not changed since last time
	if (dir1Normalized == dirP0 && splineSegmentLen == 0)
  {
    // Make additional control point in places where path goes around corners 
    if ( bSplineRequiresExtraPoint )
    {
      // checking 2 adjacent points perpendicular to movement direction
      if (!pMap->CanUnitGo(pOwner->GetUnitRadius(), pOwner->GetUnitDynamicRadius(), p0 + dirN)
       || !pMap->CanUnitGo(pOwner->GetUnitRadius(), pOwner->GetUnitDynamicRadius(), p0 - dirN))
      {
        bSplineRequiresExtraPoint = false;
        return true;
      }
    }
		return false;
  }

	splineSegmentLen++;

	// checking 2 adjacent points perpendicular to movement direction
  if (!pMap->CanUnitGo(pOwner->GetUnitRadius(), pOwner->GetUnitDynamicRadius(), p0 + dirN)
   || !pMap->CanUnitGo(pOwner->GetUnitRadius(), pOwner->GetUnitDynamicRadius(), p0 - dirN))
  {
    bSplineRequiresExtraPoint = true;
    return true;
  }

	// path is broken (not straight line)
	if (dir1Normalized != dirP0 && dir1Normalized != dirP1)
  {
    bSplineRequiresExtraPoint = true;
		return true;
  }

	splineSegmentLen++;
	return false;
}

void MovingUnit::InitSpline(bool firstTime)
{
	if (firstTime)
	{
		SVector p0 = pMap->GetTile(pPath->PeekPoint(0));
		SVector p1 = pMap->GetTile(pPath->PeekPoint(1));
		splineDir0 = splineDir1 = p1 - p0;
	}

	// now, should get next spline point
#if !DISABLE_PATH_SMOOTHING
	splineSegmentLen = 0;
	for (int i = 0; i < MAX_SPLINE_TILES && pPath->CanPeek(0); i++)
	{
		// skip equal points (CStandartPath2 bug)
		while (pPath->CanPeek(1) && pPath->PeekPoint(0) == pPath->PeekPoint(1))
			pPath->Shift( 1, pathFindingSteps );
//		DebugTrace("... [%d] point %g %g", pPath->CanPeek(0), pPath->PeekPoint(0).x, pPath->PeekPoint(0).y);
		// analyze 2 next points
		if (CheckSplineControlPoint())
		{
//			DebugTrace("... CONTROL POINT");
			break;
		}
		// IMPORTANT: do not smooth first 2 tiles of path - for better RecomputePath()
		// Idea: when one unit is bypassing another (moving/stopped), possibly these
		// units are near one to another - should perform precise movement, don't use
		// splines ...
		if (firstTime)
			break;
		AddSplineTile(pPath->PeekPoint(0));
		pPath->Shift( 1, pathFindingSteps );
	}
#endif // DISABLE_PATH_SMOOTHING

	// shift spline construction points
	splinePoint[0] = splinePoint[1];
	splinePoint[1] = splinePoint[2];
	splinePoint[2] = splinePoint[3];
	// get next path point as splinePoint[3]
//	DebugTrace("... [%d] END point %g %g", pPath->CanPeek(0), pPath->PeekPoint(0).x, pPath->PeekPoint(0).y);
	if (pPath->CanPeek(0)) // if path is finished - do last point will be the same
	{
		splinePoint[3] = pPath->PeekPoint(0);
		pPath->Shift( 1, pathFindingSteps );
		AddSplineTile(splinePoint[3]);
	}

//	for (int j = 0; j < 4; j++) DebugTrace("... spline[%d] = %g %g", j, splinePoint[j].x, splinePoint[j].y);
	// recreate spline
	splineIter = 0;
	spline.Init(splinePoint[0], splinePoint[1], splinePoint[2], splinePoint[3]);
}

void MovingUnit::StraightSpline()
{
	CVec2 sppath = splinePoint[3]-splinePoint[0];
	splinePoint[1] = splinePoint[0]+sppath/3.0f;
	splinePoint[2] = splinePoint[0]+2.0f*sppath/3.0f;
	splineIter = 0;
	spline.Init(splinePoint[0], splinePoint[1], splinePoint[2], splinePoint[3]);
}

CVec2 MovingUnit::IterateSpline()
{
	NI_ASSERT(moveState == MOVE_STATE_MOVING || moveState == MOVE_STATE_BYPASSING, "Bad moveState");
	if (splineIter < CBSpline::N_OF_ITERATONS)
	{
		spline.Iterate();
		splineIter++;
	}
	else
	{
		// spline's "t" variable becomes 1.0f, advance spline control points
		InitSpline();
	}
	return spline.GetPoint();
}

void MovingUnit::ClearSpline()
{
	splinePoint[0] = splinePoint[1] = splinePoint[2] = splinePoint[3] = origin;
	splineIter = numSplineTiles = 0;
}

void MovingUnit::DropSplineTiles(int count)
{
	if (count >= numSplineTiles)
	{
		numSplineTiles = 0;
		return;
	}
	numSplineTiles -= count;
	memmove(&splineTiles[0], &splineTiles[count], numSplineTiles * sizeof(splineTiles[0]));
}

void MovingUnit::AddSplineTile(CVec2 const& tile)
{
	if (numSplineTiles && tile == splineTiles[numSplineTiles-1])
		return;
	if (numSplineTiles >= splineTiles.size())
		DropSplineTiles(1);
	splineTiles[numSplineTiles++] = tile;
}

bool MovingUnit::ValidatePath(bool fast)
{
  NI_PROFILE_FUNCTION

	if (!pPath)					// just in case
		return false;

	bool result = true;
	int toDrop = -1;
	SVector prevTile(-1, -1);

	// determine number of checking tiles
	int tilesToCheck = numSplineTiles;

	int objectRadius = pOwner->GetUnitRadius();
	int objectDynRadius = pOwner->GetUnitDynamicRadius();
	for (int i = 0; i < tilesToCheck; i++)
	{
		SVector tile = pMap->GetTile(splineTiles[i]);
		if (!fast)
		{
			if (result)
			{
				if (i == 0)
					result = pMap->CanUnitGo(objectRadius, objectDynRadius, tile); // here prevTile is invalid
				else
					result = pMap->CanUnitGoByDir(objectRadius, objectDynRadius, prevTile, tile - prevTile);
			}
		}
		prevTile = tile;

		if (toDrop != i-1)
		{
			// previous point is not dropped, ignore rest path
			if (fast)
				break;				// fast mode - do not process remainder of path
			continue;
		}
		if (i == numSplineTiles - 1)
			continue;				// last point, no next tile
		CVec2 dirToUnit = origin - splineTiles[i];
		CVec2 dirToMove = splineTiles[i+1] - splineTiles[i];
		float dot = dirToMove * dirToUnit;
		// here: if dot>0 then point[i] is already passed, otherwise - this point is in forward direction
		if (dot >= -0.01f)
			toDrop = i;
	}
	if (toDrop >= 0)
		DropSplineTiles(toDrop + 1);
//	DebugTrace("Validate: %g %g -> %d", origin.x, origin.y, result);
	return result;
}

bool MovingUnit::ValidatePos( CVec2 pos )
{
  if ( !pPath )					// just in case
  {
    return false;
  }

  MapModeChanger mode( mapModeStatic, pMap );

  return pMap->CanUnitGo( pOwner->GetUnitRadius(), pOwner->GetUnitDynamicRadius(), pMap->GetTile( pos ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// High-level unit control
///////////////////////////////////////////////////////////////////////////////////////////////////

void MovingUnit::MoveTo( const CVec2& target, float stopDistance, IPointChecking* pointChecking )
{
	NI_VERIFY( moveState != MOVE_STATE_MOUNTED, "Calling MoveTo for mounted unit", return ); // error for WORLD only
	if ( isFollowing )
  {
    return;
  }

	pUnitTarget = NULL;
	MoveToInternal( target, stopDistance, pointChecking );
}

void MovingUnit::MoveTo( PFBaseUnit* target, float stopDistance, IPointChecking* pointChecking )
{
  NI_VERIFY( moveState != MOVE_STATE_MOUNTED, "Calling MoveTo for mounted unit", return ); // error for WORLD only
  if ( isFollowing )
  {
    return;
  }

	pUnitTarget = target;
	MoveToInternal( pUnitTarget->GetPosition().AsVec2D(), stopDistance, pointChecking ); // not moving unit (building)
}

void MovingUnit::MoveToInternal( const CVec2& target, float _stopDistance, IPointChecking* pointChecking )
{
	CVec2 roundedTarget = pMap->GetPointByTile( pMap->GetTile( target ) );	// round target position to a nearest tile
	CVec2 realTarget    = GetOrigin( roundedTarget );	  										// unit center -> unit origin
	// reject repeated MoveTo() commands when target is not changed
	if ( ( moveState != MOVE_STATE_IDLE ) && ( realTarget == vLastMoveTarget ) )
  {
    return;					              // already moving to this point
  }

	stopDistance = _stopDistance;

	CVec2 oldTarget = vFarTarget;
  vLastMoveTarget = realTarget;
  vFarTarget = target; // remember target

	// prepare point checking
	if ( !pointChecking && stopDistance )
  {
    pointChecking = new RangeChecking( roundedTarget, pOwner, stopDistance );
  }
	pChecking = pointChecking;

  if ( moveState == MOVE_STATE_MOVING )
  {
    numIncrementalUpdates++;
    if ( numIncrementalUpdates < MAX_INCREMENTAL_TIMES )
	  {
		  const float newTargetDelta2 = fabs2( realTarget - oldTarget );
		  if ( newTargetDelta2 < fabs2( MAX_INCREMENTAL_DELTA ) )
		  {
			  // try to make incremental path update
			  if ( pPath->TryUpdatePath( realTarget ) )
			  {
				  numIncrementalUpdates++;
				  return;
			  }
		  }
	  }
  }
	numIncrementalUpdates = 0;

  bool wasMarkedOnMap = isMarkedOnMap;
  UnmarkTiles( true );				  	// for CreatePath()

  CreatePath( GetRealOwner() ? GetRealOwner()->IsHero() : false );
	if ( UpdatePath() )
	{
		// MOVE_STATE_START_MOVING is used to resolve collisions before move;
		// when ghost mode is on, can start moving immediately
		SetState( ( GetGhostMode() == 0 ) ? MOVE_STATE_START_MOVING : MOVE_STATE_MOVING );

		// We started moving
		pOwner->EventHappened( PFBaseUnitEvent( NDb::BASEUNITEVENT_MOVE ) );
	}
	else
	{
		Stop();	///?? NO_PATH with small timeout
		// update moveDir anyway
		UpdateMoveDir( vFarTarget );
	}

  if ( wasMarkedOnMap )
  {
    MarkTiles();										// restore mark if needed
  }
}

void MovingUnit::Stop( bool notifyClient /* = true */ )
{
  // ignore if mounted
  if ( moveState == MOVE_STATE_MOUNTED )
    return;

	pPath       = NULL;
	pStaticPath = NULL;
	pBlocker    = NULL;

	pUnitTarget = NULL;

	if ( moveState != MOVE_STATE_IDLE )
  {
    SetState( MOVE_STATE_IDLE );
  }

  MarkTiles();

	//TODO: NUM_TASK
	if (notifyClient)
		NotifyClientStop();

	moveFlags = 0;                     // reset moveFlags
}

bool MovingUnit::TeleportTo( const CVec2& target, bool notifyClient /* = true */ )
{
	const float radiusToLook = MAX_UNIT_SIZE * pMap->GetTileSize();
	bool result = PlaceUnit( target, radiusToLook );
	vFarTarget = origin;
  //NI_ASSERT( type == WORLD || pOwner->asyncCmdCount > 0 || fabs2( vFarTarget - pOwner->pUnit[type]->vFarTarget ) < pOwner->GetObjectSize() * 4, "vFarTarget too far" );

  if ( notifyClient )
  {
    NotifyClientTeleport();
  }
	Stop( notifyClient );
	NotifyMoving( true ); // notify position change to all depending systems
	return result;
}

bool MovingUnit::MoveToSpecial( const CVec2& target, bool notifyClient )
{
  // by design: throw breaks follow
  FollowTo( NULL );

	Stop( notifyClient );
	SetState( MOVE_STATE_SPECIAL_MOVE );
	UnmarkTiles();

	pUnitTarget = NULL; // done in Stop() too
	vFarTarget = GetOrigin( target );

  return true;
}

bool MovingUnit::MoveToSpecial( const CPtr<PFBaseUnit>& target, bool notifyClient )
{
  // by design: throw breaks follow
  FollowTo( NULL );

	Stop( notifyClient );
	SetState( MOVE_STATE_SPECIAL_MOVE );
	UnmarkTiles();

	pUnitTarget = target;
	vFarTarget = GetOrigin( pUnitTarget->GetPosition().AsVec2D() );

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Unit 'thinking'
///////////////////////////////////////////////////////////////////////////////////////////////////

void MovingUnit::TickMove(float timeDelta)
{
  NI_PROFILE_FUNCTION
  
	// B2 reference for spline path moving:
	//   CStandartSmoothPathBasis::MoveUnit()

	// compute distance to move in current step
	float toMove = speed * timeDelta;

  int recalcPathCounter = 0;

	UnmarkTiles();
	CVec2 prevPos = origin;

  while ( !IsColliding() )
	{
    NI_VERIFY( recalcPathCounter <= MAX_RECALC_PATH_PER_STEP, 
      NStr::StrFmt( "Maximum(%d) path recalculations reached at [%f,%f]", 
        MAX_RECALC_PATH_PER_STEP, GetCenter().x, GetCenter().y ), Stop(); break; );

		CVec2 delta = vShortTarget - origin;
		float dist = fabs( delta );	// vector length

		if ( dist <= toMove )
		{
			// moving to far distance; skip next point
      if ( !ValidatePos( vShortTarget ) )
      {
        CVec2 oldTarget = vShortTarget;

        if (RecomputePath())
        {
          vShortTarget = IterateSpline();
          if ( vShortTarget != oldTarget )
          {
            ++recalcPathCounter;
            continue;
          }
        }

        Stop();
        break;
      }

      toMove -= dist;
			SetOrigin( vShortTarget );
			if ( !pPath || ( pPath->IsFinished() && origin == pPath->GetFinishPoint() ) ||
					 ( splinePoint[0] == splinePoint[1] && splinePoint[1] == splinePoint[2] && splinePoint[2] == splinePoint[3] ) )
			{
				// a whole path was done, or spline was degenerated to a single point
				Stop();
				break;
			}

			// advance spline point and vShortTarget
			vShortTarget = IterateSpline();
			continue;
		}
		// here: should move unit somewhere between vCurrentPos and vShortTarget
    CVec2 nextPos = origin + delta * toMove / dist;
    if ( !ValidatePos( nextPos ) )
    {
      CVec2 oldTarget = vShortTarget;

      if (RecomputePath())
      {
        vShortTarget = IterateSpline();
        if ( vShortTarget != oldTarget )
        {
          ++recalcPathCounter;
          continue;
        }
      }

      struct NearestPoint
      {
        CVec2 point;
        float minDelta;
        CVec2 nearestPathPoint;
        NearestPoint(const CVec2& _point) : point(_point), minDelta(-1.f) {}
        void operator()(const CVec2& _vec)
        {
          CVec2 vec = _vec - point;
          float dist = fabs( vec );
          if( dist < minDelta || minDelta < 0.f )
          {
            minDelta = dist;
            nearestPathPoint = _vec;
          }
        }
      } func( vShortTarget );
      // суть этой страшной конструкции в том, что func передаЄтс€ по ссылке а не по значению
      nstl::for_each<nstl::vector<Protection::HiddenVar<CVec2, 30>::T>::iterator,NearestPoint&>( splineTiles.begin(), splineTiles.end(), func ); 

      if( func.nearestPathPoint == origin ) // это значит что скорости слишком мало, чтобы перейти в другой тайл.  ейз маловеро€тный
      {
        Stop();
        break;
      }

      if( !ValidatePos( func.nearestPathPoint ) )
      {
        Stop();
        break;
      }

      SetOrigin( func.nearestPathPoint );

      if( !RecomputePath() )
      {
        Stop();
        break;
      }

      // compute moveDir
      moveDir = func.nearestPathPoint - origin;
      Normalize( &moveDir );
      break;
    }
    SetOrigin( nextPos );

    // compute moveDir
    moveDir = delta;
    Normalize( &moveDir );

    break;
	}
	ValidatePath(true);	// skip passed splineTiles

	// update tile map
	MarkTiles();

	// update client unit
	if ( fabs(origin - prevPos) > 0.01f )		// is position changed inside loop above?
		NotifyClientMove();
	else
		NotifyClientStop();

	// stop animation for static states
	if (moveState != MOVE_STATE_MOVING &&
			moveState != MOVE_STATE_BYPASSING &&
			moveState != MOVE_STATE_START_BYPASSING &&
			moveState != MOVE_STATE_BLOCKED) // NUM_TASK: this state is static, but we don't want to stop move animation
		NotifyClientStop();
}


void MovingUnit::TickMoveSpecial(float timeDelta)
{
	NI_ASSERT( moveState == MOVE_STATE_SPECIAL_MOVE, "TickMoveSpecial in wrong state" );

	const float SPECIAL_MOVE_STEP = pMap->GetTileSize() / 3.0f;

  MapModeChanger mode( mapModeAll, pMap);

	// compute distance to move in current step
	float toMove = speed * timeDelta;
	CVec2 delta = vFarTarget - origin;
	float dist = fabs(delta);	// vector length
	if (toMove > dist)
		toMove = dist;

	bool stopping = false;
	CVec2 check   = origin;
	CVec2 prevPos = origin;
	while (toMove > 0)
	{
		float moveStep = toMove;
		if (toMove > SPECIAL_MOVE_STEP)
			moveStep = SPECIAL_MOVE_STEP;
		else
			moveStep = toMove;
		toMove -= moveStep;

		check = check + delta * moveStep / dist;

    SVector tileToCheck = pMap->GetTile( check );
    if ( pMap->IsPointOutsideMap( tileToCheck.x, tileToCheck.y ) ||
       ( ( mapModeAll != 0 ) && !( moveFlags & MOVE_FLAG_NO_COLLIDE ) &&
         !pMap->CanUnitGo( pOwner->GetUnitRadius(), pOwner->GetUnitDynamicRadius(), tileToCheck ) ) )
    {
      // stop on collision
      stopping = true;
      break;
    }

		// point is ok, advance unit origin
		SetOrigin(check);
	}

	dist = fabs(vFarTarget - origin);
	if ( dist < EPS_VALUE )
	{
		// stop on reaching destination point
		stopping = true;
		SetOrigin(vFarTarget); // exact value
	}

	if (origin != prevPos)		// is position changed inside loop above?
		NotifyClientMove( false );

	if (stopping)
	{
		Stop(false);
		NotifyClientStop();			// custom callback
	}
}

// Step movement logic of the higher level
void MovingUnit::Step( float timeDelta )
{
	NI_VERIFY( !isFollowing || ( pUnitTarget == NULL ), "Multiple states activated", return );

	// step "following" state
	if ( isFollowing )
	{
	  if ( !IsUnitValid( pFollowed ) )
		{
			isFollowing = false;
			pFollowed   = NULL;
			Stop();
		}
		else
		{
      if ( !pOwner->IsTargetInRange( pFollowed, followDistance ) )
      {
        MoveToInternal( pFollowed->GetPosition().AsVec2D(), followDistance, NULL );
      }
			else
      {
        Stop();
      }
		}
	}

	// step moving to pUnitTarget
	if ( IsValid(pUnitTarget) )
	{
		if ( !IsUnitValid( pUnitTarget ) )
		{
			pUnitTarget = NULL;
		}
		else
		{
			// update destination position
      const CVec2& pos = pUnitTarget->GetPosition().AsVec2D();
			if ( moveState == MOVE_STATE_SPECIAL_MOVE )
      {
        vFarTarget = GetOrigin( pos );
      }
			else
      {
        MoveToInternal( pos, stopDistance, NULL );
      }
		}
	}
}

// called from UpdateMovements() (before collision)
void MovingUnit::PreStep(float timeDelta)
{
  NI_PROFILE_FUNCTION
  
	// should update unit's speed before collision
	if (!(moveFlags & MOVE_FLAG_OVERRIDE_SPEED))
	{
		float speed = max(0.0001f, pOwner->GetMoveSpeedMpS()) * speedScale;

		NI_ASSERT(speed > 0, "Returned speed value is <= 0!");
		SetUnitSpeed(speed);
	}
}

// called from UpdateMovements() (after collision) -> PFBaseMovingUnit::MovingUnitStep()
void MovingUnit::MovingUnitStep(float timeDelta)
{
  NI_PROFILE_FUNCTION
  
	if (moveState == MOVE_STATE_DEAD)
		return;

	if (timeDelta <= 0.001f)		// skip zero timeDelta
		return;


	CVec2 prevPos = origin;

	// Update standing time (it will be dropped while moving)
	timeStanding += timeDelta;

  if (moveState == MOVE_STATE_MOUNTED)	 // moved by parent unit
  {
    // do nothing
  }
  else
  {
    MapModeChanger mode( mapModeAll, pMap );
    if ( moveState == MOVE_STATE_SPECIAL_MOVE )
    {
      TickMoveSpecial( timeDelta );
    }
    // regular moving code
    else
    {
      if ( pOwner->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDMOVE ) )
		  {
			  // movement is forbidden
			  if ( IsMoving() )
        {
          NotifyClientStop();
        }
      }
      else
      {
        // perform movement
        if ( moveState != MOVE_STATE_IDLE )
        {
          TickMove( timeDelta );
        }
      }
    }
  }
	// tick state time
	stateTime += timeDelta;
	
  RecryptImpl();

	// movement notification to client
	if (origin != prevPos)
		NotifyMoving(false);

	// move attached unit
	UpdateAttachedMovement();
}


void MovingUnit::UpdateAttachedMovement()
{
  if (IsValid(pAttached))
	{
		MovingUnit &attached = pAttached->world;
		NI_ASSERT(attached.moveState == MOVE_STATE_MOUNTED, "Wrong state of mounted unit");
		attached.SetCenter(GetCenter());
		attached.NotifyMoving(false);
    attached.UpdateAttachedMovement();
	}
}


void MovingUnit::UpdateMovements(const PFVoxelMap *pVoxelMap, const CollisionResolver* pResolver, TileMap *pMap, float timeDelta) // static
{
  NI_PROFILE_FUNCTION

	// collect all PFBaseMovingUnit objects
	vector<PFBaseMovingUnit*> units;
	PFBaseMovingUnit::GetAllUnits( pVoxelMap, units, false );
	const int numUnits = units.size();

  // call PreStep() for all units
  if (timeDelta <= 0.0f)
    return;

  for ( int i = 0; i < numUnits; i++)
	  units[i]->world.PreStep(timeDelta);

  pResolver->Resolve( units, timeDelta );

	// tick all PFBaseMovingUnit objects
  {
    NI_PROFILE_BLOCK( "UnitsStep" );

	  for ( int i = 0; i < numUnits; i++)
      units[i]->MovingUnitStep(timeDelta);
  }
} //MovingUnit::UpdateMovements

void MovingUnit::Reset( TileMap* _pMap )
{
	pMap = _pMap;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Miscellaneous
///////////////////////////////////////////////////////////////////////////////////////////////////

bool MovingUnit::IsTerrainNative( float x, float y ) const
{
  int nativeTerrain = pOwner->GetFaction();
  int currentTerrain = pOwner->GetWorld()->GetNatureMap()->GetNatureInPoint( x, y );
  return ( nativeTerrain == currentTerrain );
}

bool MovingUnit::IsTerrainNative( SVector tile ) const
{
  int nativeTerrain = pOwner->GetFaction();
  CVec2 pos = GetCenter( pMap->GetPointByTile( tile ) );
  int currentTerrain = pOwner->GetWorld()->GetNatureMap()->GetNatureInPoint( pos.x, pos.y );
  return ( nativeTerrain == currentTerrain );
}

bool MovingUnit::IsTerrainNative() const
{
  return IsTerrainNative( pOwner->GetPos().x, pOwner->GetPos().y );
}

bool MovingUnit::CanOccupyPosition( CVec2 const& position )
{
  bool wasMarkedOnMap = isMarkedOnMap;
  UnmarkTiles( true );

  SVector tile = pMap->GetTile(GetOrigin(position));
  MapModeChanger mode( mapModeAll, pMap );
  bool isTilePassable = pMap->CanUnitGo( pOwner->GetUnitRadius(), pOwner->GetUnitDynamicRadius(), tile );

  if ( wasMarkedOnMap )
  {
    MarkTiles();
  }

  return isTilePassable;
}

// Verify unit position in order to place unit to TileMap. If position is blocked,
// will find nearby free position. If failed, return 'false'.
// Note: this function will not work when (indirectly) called from PFAdvMap::Fill(),
// because TileMap will be updated only when map is fully loaded.
// For dropping items it supports now search with checking walkability and specifying a size of a unit, which should be able to reach droped item
bool MovingUnit::FindFreePlace(CVec2 const& newPosition, float radius, CVec2& foundPosition, bool ignoreUnits, bool nativeTerrainOnly, bool checkWalkable /*= false*/, float size /*= -1.0f*/, int mapModeFlags, bool checkLineOfSight /*=false*/ )
{
	if ( GetGhostMode() != 0 )
		ignoreUnits = true;

  bool wasMarkedOnMap = isMarkedOnMap;
  UnmarkTiles( true );             // unmark tiles for clean process

	int placeRadius = Round(radius / pMap->GetTileSize());
  int objectTileRadius = (size < 0.0f) ? pOwner->GetUnitRadius() : size;

  // Get tile of the owners position for walkability checks
  SVector tileOwner = pMap->GetTile(GetOrigin(pOwner->GetPosition().AsVec2D()));

	SVector tile  = pMap->GetTile(GetOrigin(newPosition));
	foundPosition = GetCenter(pMap->GetPointByTile(tile)); // rounded position

  Pathfinding::CCommonPathFinder * pathFinder = GetPathFinder();

  // check center
  MapModeChanger mode( mapModeFlags ? mapModeFlags : (ignoreUnits ? (mapModeAll & ~mapMode) : mapModeAll), pMap);
  bool checkVisibility = checkLineOfSight ? pOwner->CanSee( tile ) : true;
	if ( pMap->CanUnitGo( objectTileRadius, tile ) && checkVisibility && ( !nativeTerrainOnly || IsTerrainNative( tile ) ) )
	{
    // If walkability checks required - process the check
    if (!checkWalkable || checkWalkable && pathFinder->Walkable(tileOwner, tile, objectTileRadius, objectTileRadius))
    {
		  if ( wasMarkedOnMap )
      {
        MarkTiles();
      }
		  return true;
    }
	}

	// place for unit is locked by another unit, try to find nearest free place
	bool found = false;
	SVector tile2;
#define CHECK(_x,_y)                                                                                    \
	tile2.x = _x; tile2.y = _y;                                                                           \
  checkVisibility = checkLineOfSight ? pOwner->CanSee( tile2 ) : true;                                  \
	if ( pMap->CanUnitGo( objectTileRadius, tile2 ) && checkVisibility && ( !nativeTerrainOnly || IsTerrainNative( tile2 ) ) ) \
	{                                                                                                     \
    if (!checkWalkable                                                                                  \
        || checkWalkable && pathFinder->Walkable(tileOwner, tile2, objectTileRadius, objectTileRadius)) \
    {                                                                                                   \
		  found = true;                                                                                     \
		  break;                                                                                            \
    }                                                                                                   \
	}

  for (int dist = 1; dist <= objectTileRadius + placeRadius; ++dist)
  {
    for ( int d = 0; d < dist; ++d )
    {
      CHECK( tile.x + d,     tile.y + dist );
      CHECK( tile.x - d,     tile.y - dist );
      CHECK( tile.x - dist,  tile.y + d );
      CHECK( tile.x + dist,  tile.y - d );
      CHECK( tile.x - d - 1, tile.y + dist );
      CHECK( tile.x + d + 1, tile.y - dist );
      CHECK( tile.x - dist,  tile.y - d - 1);
      CHECK( tile.x + dist,  tile.y + d + 1);
    }
    if (found)
      break;
  }
#undef CHECK

	if ( wasMarkedOnMap )
  {
    MarkTiles();
  }

	if (found)
	{
		// tile was found, convert to 'float' position
		foundPosition = GetCenter(pMap->GetPointByTile(tile2));
	}
	return found;
}

bool MovingUnit::FindFreePlace(CVec2 const& newPosition, CVec2 const &attractPoint, float radius, float attractPower, CVec2& foundPosition, bool ignoreUnits, bool nativeTerrainOnly, int mapModeFlags, bool checkLineOfSight /*=false*/ )
{
  if ( GetGhostMode() != 0 )
  {
    ignoreUnits = true;
  }

  bool wasMarkedOnMap = isMarkedOnMap;
  UnmarkTiles( true );             // unmark tiles for clean process

	int placeRadius = Round(radius / pMap->GetTileSize());
	int objectTileRadius = pOwner->GetUnitRadius();

	SVector tile  = pMap->GetTile(GetOrigin(newPosition));
	SVector tileA = pMap->GetTile(GetOrigin(attractPoint));
	foundPosition = GetCenter(pMap->GetPointByTile(tile)); // rounded position

	// check newPosition itself
  MapModeChanger mode( mapModeFlags ? mapModeFlags : (ignoreUnits ? (mapModeAll & ~mapMode) : mapModeAll), pMap);
  bool checkVisibility = checkLineOfSight ? pOwner->CanSee( tile ) : true;                                  
  if ( pMap->CanUnitGo( objectTileRadius, tile ) && checkVisibility && ( !nativeTerrainOnly || IsTerrainNative( tile ) ) )
	{
		if ( wasMarkedOnMap )
    {
      MarkTiles();
    }
		return true;
	}

	NI_VERIFY(attractPower >= 0 && attractPower <= 1, "attractPower is not in range [0,1]", attractPower = Clamp(attractPower, 0.0f, 1.0f));
	float wf = 0.5f + attractPower / 2; // attractPower=0 => radial function, =1 => linear function
#define WEIGHT(dx,dy)  ( (dy) * wf + (dx) * (1 - wf) )  // lerp function

	float bestWeight = placeRadius * 1000; // just a large number

	bool found = false;
	SVector foundTile, tile2;

	CBres bres;
	bres.InitPoint(tile, tileA);
	SVector curPoint = tile;
	// get near-to-perpendicular vector for (tile -> tileA) direction
	SVector shift(0, 0);
	if (abs(tile.x - tileA.x) < abs(tile.y - tileA.y))
		shift.x = 1;
	else
		shift.y = 1;
	// let's go ...
	for (int dx = 0; dx < placeRadius; dx++)
	{
		if (curPoint == tileA)
			break;							// in a case when distance(tile-tileA) < radius; CBres should pass destination point (tileA), so this condition is correct
		// check tile on a line (tile -> tileA)
		float w = WEIGHT(dx,0);
		if (w > bestWeight)
			break;							// optimization: result will not became better, stop search
		// assume for optimizations:
		// 1) weight with dy==0 is better than weight with the same dx and dy>0
		// 2) when dx1<dx2, weight(dx1,dy)<weight(dx2,dy)
    checkVisibility = checkLineOfSight ? pOwner->CanSee( curPoint ) : true;
		if ( pMap->CanUnitGo( objectTileRadius, curPoint ) && checkVisibility && ( !nativeTerrainOnly || IsTerrainNative( curPoint ) ) )
		{
			bestWeight = w;
			found      = true;
			foundTile  = curPoint;
			break;							// found point on a straight line, all other points will be worse
		}
		// check tiles on a (almost) perpendicular line
		for (int dy = 1; dy < placeRadius / 2; dy++)
		{
			w = WEIGHT(dx,dy);
			if (w > bestWeight)
				break;						// optimization ... (see above)
			SVector tile2 = curPoint + shift * dy;	// offset by perpendicular in one direction ...
			if ( !pMap->CanUnitGo( objectTileRadius, tile2 ) || !( !nativeTerrainOnly || IsTerrainNative( tile2 ) ) )
			{
				tile2 = curPoint - shift * dy;				// ... and in opposite direction
				if ( !pMap->CanUnitGo( objectTileRadius, tile2 ) || !( !nativeTerrainOnly || IsTerrainNative( tile2 ) ) )
					continue;				// both points are inaccessible, continue with different dy
			}
      
      bool checkVisibility = checkLineOfSight ? pOwner->CanSee( curPoint ) : true;
      
      if( !checkVisibility )
        continue;
			// can place unit here, remember point
			bestWeight = w;
			found      = true;
			foundTile  = tile2;
		}

		// advance curPoint
		bres.MakeStep();
		curPoint += bres.GetDirection();
	}
#undef WEIGHT

	if ( wasMarkedOnMap )
  {
    MarkTiles();
  }

	if (found)
	{
		// tile was found, convert to 'float' position
		foundPosition = GetCenter(pMap->GetPointByTile(foundTile));
	}
	return found;
}

bool MovingUnit::FindFreePlace2(CVec2 const& newPosition, CVec2 const &attractPoint, float radius, CVec2& foundPosition, bool ignoreUnits, bool nativeTerrainOnly, float size /*= -1.0f*/, int mapModeFlags, bool checkLineOfSight /*=false*/ )
{
  if ( GetGhostMode() != 0 )
    ignoreUnits = true;

  bool wasMarkedOnMap = isMarkedOnMap;
  UnmarkTiles( true );             // unmark tiles for clean process

  const int placeRadius = Round(radius / pMap->GetTileSize());
  const int objectTileRadius = (size < 0.0f) ? pOwner->GetUnitRadius() : size;
  const float placeRadius2 = placeRadius * placeRadius;

  SVector tileA = pMap->GetTile(GetOrigin(attractPoint));
  SVector tile  = pMap->GetTile(GetOrigin(newPosition));
  foundPosition = GetCenter(pMap->GetPointByTile(tile)); // rounded position

  // check center
  MapModeChanger mode( mapModeFlags ? mapModeFlags : (ignoreUnits ? (mapModeAll & ~mapMode) : mapModeAll), pMap);
  bool checkVisibility = checkLineOfSight ? pOwner->CanSee( tile ) : true;
  if ( pMap->CanUnitGo( objectTileRadius, tile ) && checkVisibility && ( !nativeTerrainOnly || IsTerrainNative( tile ) ) )
  {
    if ( wasMarkedOnMap )
    {
      MarkTiles();
    }
    return true;
  }

  // place for unit is locked by another unit, try to find nearest free place
  bool found = false;
  SVector tile2;
#define CHECK(_x,_y)                                                                                    \
  tile2.x = _x; tile2.y = _y;                                                                           \
  checkVisibility = checkLineOfSight ? pOwner->CanSee( tile2 ) : true;                                  \
  if ( fabs2( tile2 - tileA ) <= placeRadius2 && pMap->CanUnitGo( objectTileRadius, tile2 ) && checkVisibility && ( !nativeTerrainOnly || IsTerrainNative( tile2 ) ) ) \
  {                                                                                                     \
    found = true;                                                                                       \
    break;                                                                                              \
  }

  for (int dist = 1; dist <= objectTileRadius + placeRadius; ++dist)
  {
    for ( int d = 0; d < dist; ++d )
    {
      CHECK( tile.x + d,     tile.y + dist );
      CHECK( tile.x - d,     tile.y - dist );
      CHECK( tile.x - dist,  tile.y + d );
      CHECK( tile.x + dist,  tile.y - d );
      CHECK( tile.x - d - 1, tile.y + dist );
      CHECK( tile.x + d + 1, tile.y - dist );
      CHECK( tile.x - dist,  tile.y - d - 1);
      CHECK( tile.x + dist,  tile.y + d + 1);
    }
    if (found)
      break;
  }
#undef CHECK

  if ( wasMarkedOnMap )
  {
    MarkTiles();
  }

  if (found)
  {
    // tile was found, convert to 'float' position
    foundPosition = GetCenter(pMap->GetPointByTile(tile2));
  }
  return found;
}

bool MovingUnit::PlaceUnit( CVec2 const& newPosition, float maxRadius, bool ignoreUnits, bool nativeTerrainOnly, bool notifyClient )
{
  bool wasMarkedOnMap = isMarkedOnMap;
  UnmarkTiles( true );

	// Try to place unit
	CVec2 foundPosition;
	bool result = true;

  if(ignoreCollision)
    foundPosition = newPosition;
  else
    result = FindFreePlace( newPosition, maxRadius, foundPosition, ignoreUnits, nativeTerrainOnly );

	if ( result )
  {
    SetCenter( foundPosition );
    if ( notifyClient )
    {
      NotifyClientTeleport();
    }
  }

	if ( wasMarkedOnMap )
  {
    MarkTiles();
  }

	return result;
}

PathMap* MovingUnit::BuildPathMap(float maxDist)
{
  bool wasMarkedOnMap = isMarkedOnMap;
  UnmarkTiles( true );

  PathMap* result = new PathMap( pMap, GetCenter(), pOwner->GetUnitRadius(), maxDist, false );

  if ( wasMarkedOnMap )
  {
    MarkTiles();
  }

  return result;
}

void MovingUnit::OnDie()
{
	Stop(); // reset paths
	SetState(MOVE_STATE_DEAD);
	UnmarkTiles();
}

float MovingUnit::CheckStraightMove(CVec2 const &target, int mapModeFlags)
{
	MapModeChanger mode(mapModeFlags == 0 ? mapModeAll : mapModeFlags, pMap);

	// should analyze TileMap without marks of this unit
  bool wasMarkedOnMap = isMarkedOnMap;
  UnmarkTiles( true );

	// trace map by straight line between current unit origin and target
	SVector start = pMap->GetTile(origin);
	SVector end   = pMap->GetTile(GetOrigin(target));

  CBres bres;
  bres.InitPoint( start, end );
  SVector lastTile = start;

  while (lastTile != end)
  {
    bres.MakeStep();
    SVector dir = bres.GetDirection();
    if(!pMap->CanUnitGoByDir( pOwner->GetUnitRadius(), pOwner->GetUnitDynamicRadius(), lastTile, dir ))
      break;
    lastTile += dir;
  }

	// restore mark state
	if ( wasMarkedOnMap )
  {
    MarkTiles();
  }

	// return distance between start and end points
	return fabs(pMap->GetPointByTile(lastTile) - pMap->GetPointByTile(start));
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Unit collector
///////////////////////////////////////////////////////////////////////////////////////////////////

struct MovingUnitsCollector : NonCopyable
{
	MovingUnitsCollector(vector<PFBaseMovingUnit*> &_movingUnits, bool _markedOnly, const PFBaseMovingUnit *_skipUnit = NULL)
	: movingUnits(_movingUnits)
	, markedOnly(_markedOnly)
	, skipUnit(_skipUnit)
	{}

	void operator ()(PFBaseUnit &unit)
	{
		CDynamicCast<PFBaseMovingUnit> movUnit = &unit;
		if (!movUnit)
			return;										// different type
		if (movUnit == skipUnit)
			return;
		if (markedOnly && !movUnit->IsMarkedOnMap())
			return;
		EMoveState state = movUnit->world.moveState;
		if (state == MOVE_STATE_DEAD || // dead units are not marked on the map
				state == MOVE_STATE_MOUNTED)
			return;
		// remember unit
		if (!movingUnits.size())
			movingUnits.reserve(256);	// 256 - common max number of moving units
		movingUnits.push_back(movUnit);
	}

	vector<PFBaseMovingUnit*> &movingUnits;
	bool                      markedOnly;
	const PFBaseMovingUnit    *skipUnit;
};

struct PushableUnitsCollector : NonCopyable
{
  PushableUnitsCollector(vector<PFBaseMovingUnit*> &_pushableUnits, vector<PFBaseMovingUnit*> &_nonPushableUnits, bool _markedOnly, const PFBaseMovingUnit *_skipUnit = NULL)
    : pushableUnits(_pushableUnits)
    , nonPushableUnits(_nonPushableUnits)
    , markedOnly(_markedOnly)
    , skipUnit(_skipUnit)
  {}

  void operator()(PFBaseUnit &unit)
  {
    CDynamicCast<PFBaseMovingUnit> movUnit = &unit;
    if (!movUnit)
      return;										// different type
    if (movUnit == skipUnit)
      return;
    if (markedOnly && !movUnit->IsMarkedOnMap())
      return;

    EMoveState state = movUnit->world.moveState;
    if (state == MOVE_STATE_DEAD || // dead units are not marked on the map
        state == MOVE_STATE_MOUNTED ||
        state == MOVE_STATE_SPECIAL_MOVE)
      return;

    if ( unit.CheckFlagType( NDb::UNITFLAGTYPE_IGNOREPUSH ) )
      nonPushableUnits.push_back( movUnit );
    else
      pushableUnits.push_back( movUnit );
  }

  vector<PFBaseMovingUnit*> &nonPushableUnits;
  vector<PFBaseMovingUnit*> &pushableUnits;
  bool                      markedOnly;
  const PFBaseMovingUnit    *skipUnit;
};


void PFBaseMovingUnit::GetAllUnits(const PFVoxelMap *pVoxelMap,
	vector<PFBaseMovingUnit*> &_movingUnits, bool _markedOnly, const PFBaseMovingUnit *_skipUnit)
{
	MovingUnitsCollector collector(_movingUnits, _markedOnly, _skipUnit);
	pVoxelMap->ForAllUnits(collector);
}

void PFBaseMovingUnit::GetPushableUnitsInRange(const PFVoxelMap *pVoxelMap, const CVec2 &center, float radius,
                       vector<PFBaseMovingUnit*> &_pushableUnits, vector<PFBaseMovingUnit*> &_nonPushableUnits, bool _markedOnly, const PFBaseMovingUnit *_skipUnit)
{
  PushableUnitsCollector collector(_pushableUnits, _nonPushableUnits, _markedOnly, _skipUnit);
  pVoxelMap->ForAllUnitsInRange(CVec3(center, 0), radius, collector);
}

void PFBaseMovingUnit::GetAllUnitsInRangeConsiderSize(const PFVoxelMap *pVoxelMap, const CVec2 &center, float radius,
                                          vector<PFBaseMovingUnit*> &_movingUnits, bool _markedOnly, const PFBaseMovingUnit *_skipUnit)
{
  MovingUnitsCollector collector(_movingUnits, _markedOnly, _skipUnit);
  pVoxelMap->ForAllUnitsInRangeConsiderSize(CVec3(center, 0), radius, collector);
}


///////////////////////////////////////////////////////////////////////////////
// PFBaseMovingUnit
///////////////////////////////////////////////////////////////////////////////
PFBaseMovingUnit::PFBaseMovingUnit(PFWorld* pWorld, const CVec3 &pos, const CVec2 & direction, const NDb::Unit &unitDesc)
: PFBaseUnit(pWorld, pos, &unitDesc)
, world(position, direction, GetTileMap(), unitDesc)
, isMount( false )
, forbidStop ( false )
, doNotTeleportInStepInvisibility(false)
{
	random = pWorld->GetRndGen()->Next(RANDOM_MAX);
}

// We needs a correct initialization of some MovingUnit fields even in default constructor
PFBaseMovingUnit::PFBaseMovingUnit()
: isMount( false )
, forbidStop ( false )
, doNotTeleportInStepInvisibility(false)
{
}




void PFBaseMovingUnit::Initialize(InitData const& data)
{
  PFBaseUnit::Initialize( data );
  world.Init( this );
}

void PFBaseMovingUnit::AttachUnit(CPtr<PFBaseMovingUnit> const& pUnit)
{
	world.AttachUnit(pUnit);
}

void PFBaseMovingUnit::DetachUnit()
{
	NI_VERIFY(world.pAttached, "DetachUnit without AttachUnit", return);
	world.DetachUnit();
}

int PFBaseMovingUnit::GetUnitRadius() const
{
  return Max( 1, GetObjectTileSize() / 2 );
}

int PFBaseMovingUnit::GetUnitDynamicRadius() const
{
  return Max( 1, GetObjectDynamicTileSize() / 2 );
}

// NOTE about order of world/local commands:
// we should move/stop world unit after local, because if we will do this in reverse order
// world may move/stop before calling MakeAsynchronous(), which will cause problem: local will
// move/stop too, even when not desired.


bool PFBaseMovingUnit::MoveTo( const CVec2& target, float stopDistance /* = 0.0f */, IPointChecking* pointChecking /* = NULL */ )
{
	if ( g_lockMove )
  {
    return false;
  }

  // MapModeChanger mode(0x100, world.pMap); // find "holes" in map mode changes (set to invalid map mode)

  NI_ASSERT( ( stopDistance == 0.0f ) || !pointChecking, "Should not specify both stopDistance and pointChecking" );

	// else - local unit will react to AsyncMoveTo() and not react to MoveTo()
	world.MoveTo( target, stopDistance, pointChecking );
	return world.IsMoving();
}

bool PFBaseMovingUnit::MoveTo( PFBaseUnit* target, float stopDistance /* = 0.0f */, IPointChecking* pointChecking /* = NULL */ )
{
	if ( !IsValid( target ) )
  {
    return false;
  }

  NI_ASSERT( ( stopDistance == 0.0f ) || !pointChecking, "Should not specify both stopDistance and pointChecking" );

  world.MoveTo( target, stopDistance, pointChecking );
	return world.IsMoving();
}

void PFBaseMovingUnit::SetMoveFlags(unsigned value)
{
	world.moveFlags = value;
}

float PFBaseMovingUnit::SetUnitSpeed(float value)
{
	world.SetUnitSpeed(value * world.speedScale);
	return world.GetUnitSpeed();
}

void PFBaseMovingUnit::NotifyDispatchesOnTargetTeleport()
{
  // notify inbound dispatches
    for ( ring::Range<PFDispatchUniformLinearMove::UnitDispatchesRing> it( inboundDispatches ); it; )
    {
      PFDispatchUniformLinearMove* pDispatch = &(*it);
      ++it;
      pDispatch->OnTargetTeleport();
    }
}

bool PFBaseMovingUnit::TeleportTo( const CVec2& target, bool instantMove /* = true */, bool notifyDispatches /* = true*/ )
{
	bool result = world.TeleportTo( target, instantMove );
	if ( !instantMove )
  {
    world.NotifyClientMove( false );
  }

	//// notify inbound dispatches
  if ( notifyDispatches )
  {
    NotifyDispatchesOnTargetTeleport();
  }

  if (NGameX::AdventureScreen * adventureScreen = NGameX::AdventureScreen::Instance())
  {
    if ( adventureScreen->IsObservingObject( this ) )
    {
      adventureScreen->MoveCameraTo( this, false );
    }
  }

	return result;
}


void PFBaseMovingUnit::Stop( bool notifyClient /*= true*/ )
{
  if( !forbidStop )
  {
    world.Stop( notifyClient );
    OnStopped();
  }
}


// generic step for unit
bool PFBaseMovingUnit::Step(float dtInSeconds)
{
  const ScopedFlag denyTeleportInStepInvisibility(doNotTeleportInStepInvisibility);

	if (world.moveState != MOVE_STATE_DEAD)
	{
		// do not update dead units
		random = pWorld->GetRndGen()->Next(RANDOM_MAX);
		world.Step(dtInSeconds);
	}
	
	const bool PrevClientVisible = world.ClientIsVisible();
	const bool result = PFBaseUnit::Step(dtInSeconds);
	
	if( !PrevClientVisible && world.ClientIsVisible() ) 
	  world.NotifyClientTeleport();
	
	return result;
}

void PFBaseMovingUnit::StepInvisibility()
{
  if (doNotTeleportInStepInvisibility)
  {
    PFBaseUnit::StepInvisibility();
  }
  else
  {
    const bool PrevClientVisible = world.ClientIsVisible();

    PFBaseUnit::StepInvisibility();

    if( !PrevClientVisible && world.ClientIsVisible() ) 
      world.NotifyClientTeleport();
  }
}

// moving unit step, called from static UpdateMovements()
void PFBaseMovingUnit::MovingUnitStep(float worldTimeDelta)
{
	// call this function before Step() for correct handling of speedScaleLocal
	world.MovingUnitStep(worldTimeDelta);
	// update PFBaseMovingUnit
	position = world.GetCenter3();
}

void PFBaseMovingUnit::NotifyMoving(bool teleported )
{
  if (!IsDead())
  {
    UpdateWarFog();
  }

	GetVoxelMap()->OnUnitMove(*this);

  if (teleported && IsHero())
    GetWorld()->GetStatistics()->NotifyTeleport(*this);
}

void PFBaseMovingUnit::UpdateWarFog()
{
  PFWorld * pWorld = GetWorld();
  NI_VERIFY(pWorld, "Failed to get World!", return);
  FogOfWar * pWarFog = pWorld->GetFogOfWar();
  NI_VERIFY(pWarFog, "Failed to get War Fog!", return);
  TileMap * pTileMap = pWorld->GetTileMap();
  NI_VERIFY(pTileMap, "Failed to get Tile map!", return);

  for (int i=0; i < visUnitData.size(); ++i)
  {
    if (visUnitData[i].warFogObjectID != WAR_FOG_BAD_ID)
    {
      pWarFog->MoveObject(visUnitData[i].warFogObjectID, pTileMap->GetTile(position.AsVec2D()));
    }
  }
}

PathMap* PFBaseMovingUnit::BuildPathMap(float maxDist)
{
	return world.BuildPathMap(maxDist);
}

void PFBaseMovingUnit::OnDie()
{
	world.OnDie();
	PFBaseUnit::OnDie();
}

void PFBaseMovingUnit::OnUnitDie( CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
	world.OnDie();
	PFBaseUnit::OnUnitDie(pKiller, flags, pDamageDesc);
}

float PFBaseMovingUnit::CheckStraightMove(CVec2 const &target, int mapModeFlags)
{
	return world.CheckStraightMove(target, mapModeFlags);
}

///////////////////////////////////////////////////////////////////////////////
// Place unit with pushing other units
///////////////////////////////////////////////////////////////////////////////

static CVec2 UnitRangeSorterBase;

int MovingUnit::UnitRangeSorter(const void* _A, const void* _B) // static function
{
	const PFBaseMovingUnit* A = *(const PFBaseMovingUnit**) _A;
	const PFBaseMovingUnit* B = *(const PFBaseMovingUnit**) _B;

	float distA = fabs2(A->position.AsVec2D() - UnitRangeSorterBase);
	float distB = fabs2(B->position.AsVec2D() - UnitRangeSorterBase);

	return Sign(distA - distB);
}

Pathfinding::CCommonPathFinder * MovingUnit::GetPathFinder()
{
  Pathfinding::CCommonPathFinder * pathFinder = pOwner->GetWorld()->GetPathFinder();
  NI_ASSERT(IsValid(pathFinder), "pathFinder should be valid!");

  return pathFinder;
}

Pathfinding::RoutePathFinder* MovingUnit::GetRoutePathFinder()
{
  Pathfinding::RoutePathFinder * routePathFinder = pOwner->GetWorld()->GetRoutPathfinder();
  NI_ASSERT(IsValid(routePathFinder), "pathFinder should be valid!");

  return routePathFinder;
}

bool PFBaseMovingUnit::PlaceUnit( CVec2 const& newPosition, bool ignoreUnits, bool nativeTerrainOnly, bool notifyClient )
{
  return world.PlaceUnit( newPosition, MAX_UNIT_SIZE * world.pMap->GetTileSize(), ignoreUnits, nativeTerrainOnly, notifyClient );
}

void PFBaseMovingUnit::Reset()
{
  PFBaseUnit::Reset();
  world.Reset( GetWorld()->GetTileMap() );
}

void PFBaseMovingUnit::OnGameFinished( const NDb::EFaction failedFaction )
{
  PFBaseUnit::OnGameFinished( failedFaction );
  Stop();
}

// After this operation unit will be marked on map
// "force" argument allows to fully perform this operation even when current unit's position
// is the same as "newPosition" (will push units collided with me).
void PFBaseMovingUnit::PlaceUnitWithPush(const CVec2& newPosition0, float pushRadius, bool force, bool nativeTerrainOnly)
{
	int i;

  NI_VERIFY(false == IsDead(), "Unable to place dead units", return);

	// correct unit's position to avoid collision with static map layers
	// (newPosition0 -> newPosition)
	// this is required for correct pushing of other units, plus this will allow
	// us to faster process placing "inside" building when there is no other units
	// disturbing this process
	CVec2 newPosition;
	FindFreePlace(newPosition0, pushRadius, newPosition, true, nativeTerrainOnly);

	TileMap *pMap   = GetTileMap();
	SVector dstTile = pMap->GetTile(world.GetOrigin(newPosition));
	// sanity check
	if (dstTile == pMap->GetTile(world.origin) && !force)
		return;					// already in place

	// find all pushable units marked on tile map in specified radius 
	vector<PFBaseMovingUnit*> pushableUnits;
  vector<PFBaseMovingUnit*> nonPushableUnits;

	GetPushableUnitsInRange(GetVoxelMap(), newPosition, pushRadius, pushableUnits, nonPushableUnits, false, this );

	const int numPushables = pushableUnits.size();
  const int numNonPushables = nonPushableUnits.size();

	if ( numPushables + numNonPushables == 0 )
	{
		// no nearby units, simply teleport to destination point
		world.TeleportTo(newPosition);	/// client notification is here
		return;
	}

  bool isThereNoUnitsNearby = true;

	// sort units by distance
	UnitRangeSorterBase = newPosition;
  if ( numPushables > 0 )
  {
	  qsort( &pushableUnits[0], numPushables, sizeof(PFBaseMovingUnit*), MovingUnit::UnitRangeSorter );
    const float distToNearestUnit = fabs( newPosition - pushableUnits[0]->world.GetCenter() );
    const float unitSizes = GetObjectSize() + pushableUnits[0]->GetObjectSize();
    if ( distToNearestUnit <= unitSizes ) 
    {
      isThereNoUnitsNearby = false;
    }
  }
  if ( numNonPushables > 0 )
  {
    qsort( &nonPushableUnits[0], numNonPushables, sizeof(PFBaseMovingUnit*), MovingUnit::UnitRangeSorter );
    if ( isThereNoUnitsNearby )
    {
      const float distToNearestUnit = fabs( newPosition - nonPushableUnits[0]->world.GetCenter() );
      const float unitSizes = GetObjectSize() + nonPushableUnits[0]->GetObjectSize();
      if ( distToNearestUnit <= unitSizes ) 
      {
        isThereNoUnitsNearby = false;
      }
    }
  }

	// place units separately
	MovingUnit * thisUnit = &world;

	if ( isThereNoUnitsNearby )
	{
		// not intersected, target place is free
		// can teleport here immediately
		MapModeChanger mode(thisUnit->mapModeAll, pMap);
    if ( pMap->CanUnitGo( GetUnitRadius(), dstTile ) )
		{
			thisUnit->TeleportTo(newPosition);		/// client notification is here
			return;
		}
	}

	// remove marks for all pushable units
	for (i = 0; i < numPushables; i++)
	{
    pushableUnits[i]->world.UnmarkTiles( true );
	}

  // find position between non-pushable units
  if ( numNonPushables > 0 )
  {
    FindFreePlace(newPosition, pushRadius, newPosition, false, nativeTerrainOnly);
  }

  // place at new position
  thisUnit->TeleportTo(newPosition);		/// client notification is here

  const float extraSize = GetObjectSize();

	// push and place other pushable units
	for (i = 0; i < numPushables; i++)
	{
		MovingUnit *unit = &pushableUnits[i]->world;

    CVec2 oldUnitPos, newUnitPos;
    oldUnitPos = newUnitPos = unit->GetCenter();
    const float checkSize = (unit->pOwner->GetObjectSize() + extraSize) * 2.0f;
    // place unit nearby our unit (desired variant)
    if (!unit->FindFreePlace(oldUnitPos, newPosition, checkSize, 0.9f, newUnitPos, false, nativeTerrainOnly))
    {
      // another one fallback: use placing without attract point and with a larger search radius
      if (!unit->FindFreePlace(oldUnitPos, pushRadius, newUnitPos, false, nativeTerrainOnly))
      {
        // unable to change unit placement ...
        newUnitPos = oldUnitPos;
      }
    }
    if (newUnitPos != oldUnitPos)
    {
      unit->TeleportTo(newUnitPos); // here: client notification is disabled, we will make custom notify
      unit->NotifyClientMove( false );       // client-side slide effect
    }

		unit->MarkTiles();
		if ( unit->IsMoving() && !unit->IsMovingSpecial() )
			unit->Wait(0, 0.5f);

    NI_ASSERT( unit->isMarkedOnMap || ( unit->GetGhostMode() != 0 ),
      NStr::StrFmt( "Unit should became locked on map (state=%d, lock=%d)", unit->moveState, unit->ShouldLockMap() ) );
	}
}

///////////////////////////////////////////////////////////////////////////////
REGISTER_DEV_VAR("reverse_path_off", g_reversePathOff, STORAGE_NONE);

REGISTER_DEV_VAR("lock_world_move", g_lockMove, STORAGE_NONE);
// tune synchronization system
REGISTER_DEV_VAR("max_local_speed_coeff", maxLocalSpeedCoeff, STORAGE_NONE);
REGISTER_DEV_VAR("max_local_speed_dist",  maxLocalSpeedDist,  STORAGE_NONE);
REGISTER_DEV_VAR("max_dist_merge_path",   maxDistToMergePath, STORAGE_NONE);
REGISTER_DEV_VAR( "dump_path", g_dumpPath, STORAGE_NONE );
} // namespace

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFBaseMovingUnit, NWorld)
REGISTER_WORLD_OBJECT_NM(ObjectRangeChecking, NWorld)
REGISTER_WORLD_OBJECT_NM(RangeChecking, NWorld)
