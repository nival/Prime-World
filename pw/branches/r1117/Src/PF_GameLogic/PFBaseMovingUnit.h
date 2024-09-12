#pragma once

#include "PathTools.h"
#include "PFBaseUnit.h"
#include "System\StarForce\HiddenVars.h"

class CCommonStaticPath;
enum EPathRestriction;
namespace NGameX { class PFClientBaseMovingUnit; }

namespace NWorld
{
_interface IPointChecking;
class CStandartPath2;
class TileMap;
class PathMap;
class PFVoxelMap;

// There are three major states: idle, moving and colliding. Colliding may be different.
// WARNING: adding or reordering states here may break collision system! Do not edit
//          this enum unless you are really understand, what are you doing!
enum EMoveState
{
	MOVE_STATE_DEAD,						// unit is dead; this is a possible state
	MOVE_STATE_IDLE,						// unit is standing and does not moves
	MOVE_STATE_MOVING,					// unit is walking without collision
	MOVE_STATE_BYPASSING,				// unit is moving around specific unit
	// special movement states
	MOVE_STATE_SPECIAL_MOVE,
	MOVE_STATE_MOUNTED,					// unit is moved synchronously with other unit
	// MOVE_STATE_COLLIDING is not used, it is a divider between normal and colliding states
	MOVE_STATE_COLLIDING,
	// other colliding types should go after MOVE_STATE_COLLIDING (see IsColliding())
	// note: all these types suppose unit is not moving now because of some collision
	// (but IsMoving() will return true!)
	MOVE_STATE_START_MOVING,		// -> MOVING; found ability to move, will start moving next frame if possible
	MOVE_STATE_START_BYPASSING,	// -> BYPASSING; path was changed, should be re-checked on next tick
	MOVE_STATE_WAITING,					// cannot bypath unit with optimal path (with some restrictions)
	MOVE_STATE_BLOCKED,					// cannot bypass some unit without restrictions (but path is exists)
	MOVE_STATE_NO_PATH					// unit is completely surrounded by non-moving objects
};

struct CollideInfo;						// forward declaration; declared in cpp

enum MoveFlags
{
	MOVE_FLAG_NO_COLLIDE			= 1,	// do not collide with map at all
	MOVE_FLAG_OVERRIDE_SPEED	= 2		// do not compute speed from game logic
};


class MovingUnit
{
	friend class  PFBaseMovingUnit;
  friend class  CollisionResolver;
	friend struct PredictedUnitState;
	friend struct MovingUnitsCollector;
  friend struct PushableUnitsCollector;

  struct GhostModeType
  {
  ZDATA
    int index;
    int mode;
    bool override;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&index); f.Add(3,&mode); f.Add(4,&override); return 0; }
    GhostModeType() : index(0), mode(0), override(false) {}
    GhostModeType( int _index, int _mode, int _override ) : index( _index ), mode( _mode ), override ( _override ) {}
  };
 
public:
  typedef Protection::HiddenVar<CVec2, 6> TFarTarget;
  typedef Protection::HiddenVar<CVec2, 8> TMoveDir;
    
public:
	static const int PLACE_UNIT_RADIUS = 4;

	// helper for PFBaseMovingUnit's default constructor to keep pOwner and type always correct
	MovingUnit() : pOwner(0), pMap(0), ghostModeIndex(-1), curGhostMode(0), isFollowingForced(false), ignoreCollision(false) {}
	MovingUnit(const CVec3 &pos,const CVec2 & direction, TileMap *pTileMap, const NDb::Unit &unitDesc);

  void Init(PFBaseMovingUnit *pOwner );
	bool IsMoving() const { return moveState >  MOVE_STATE_IDLE; }
  bool IsMovingSpecial() const { return moveState == MOVE_STATE_SPECIAL_MOVE; }
  bool IsColliding() const { return moveState >= MOVE_STATE_COLLIDING; }
  TFarTarget::TConstRef GetDestination() const { return vFarTarget; }
  bool IsHoldingPosition() const        { return holdingPosition; }

  void OnHold( bool bHold ) { holdingPosition = bHold; }

  bool IsEvading() const { return evading; }
  void OnEvading( bool bEvade ) { evading = bEvade; }

  bool IsChasing() const { return chasing; }
  void OnChasing( bool bChase ) { chasing = bChase; }

	// movement control
  void MoveTo( const CVec2& target, float stopDistance, IPointChecking* pointChecking );
  void MoveTo( PFBaseUnit*  target, float stopDistance, IPointChecking* pointChecking );
	bool TeleportTo( const CVec2& target, bool notifyClient = true );
  void Stop( bool notifyClient = true );

	// Special movement functions
	// Movement by static map (completely ignoring moving units) by straight line.
	// Movement will be stopped on collision with static map object (entering IDLE state).
	// No client callbacks executed.
  bool MoveToSpecial( const CVec2&            target, bool notifyClient = true );
  bool MoveToSpecial( const CPtr<PFBaseUnit>& target, bool notifyClient = true );

  void FollowTo( const CPtr<PFBaseMovingUnit>& pUnit , bool forced = false);

  int  GetGhostMode() const { return curGhostMode; }
  int  SetGhostMode( int _mode, bool _override );
  void ResetGhostMode( int _index );

  CPtr<PFBaseMovingUnit> GetFollowedBy() const { return pFollowed; }
	// utilities
	// check movement possibility; returns maximal movement distance
	float CheckStraightMove(CVec2 const &target, int mapModeFlags = 0);
	// build map for available paths; note: higher maxDistance values will
	// consume more memory and CPU !
	PathMap* BuildPathMap(float maxDist);

	// collect and analyze collision between units, then update movement
	static void UpdateMovements(const PFVoxelMap *pVoxelMap, const CollisionResolver* pResolver, TileMap *pMap, float worldTimeDelta);

	void Reset( TileMap* _pMap );

  void UpdateAttachedMovement();

  void SetPlaceUnitIgnoreCollision(bool ignore) {ignoreCollision = ignore;}

protected:
	static const int NUM_SPLINE_POINTS = 4; // should not change this!
	static const int MAX_SPLINE_TILES  = 10; // maximal distance between spline control points, in tiles

	// interface for derived classes
	void  SetUnitSpeed(float _speed) { speed = _speed; }
	float GetUnitSpeed()             { return speed;   }

	// unit lifetime (should be 'protected', but can be used from unit's FSM ...)
	void Step(float timeDelta);					// called from World::Step()
	void PreStep(float timeDelta);			// called before UpdateMovements()
	void MovingUnitStep(float timeDelta);	// called after UpdateMovements()
	void NotifyMoving(bool teleported);

  bool IsTerrainNative( float x, float y ) const;
  bool IsTerrainNative( SVector tile ) const;
  bool IsTerrainNative() const;

	// unit destruction
	void OnDie();

	void AttachUnit(CPtr<PFBaseMovingUnit> const& pUnit);
	void DetachUnit();
  CPtr<PFBaseMovingUnit> const& GetAttachUnit() const { return pAttached; }

  bool ShouldLockMap() const;

	CPtr<TileMap>     pMap;


	ZDATA
	// unit state
  Protection::HiddenVar<CVec2, 2>::T	origin;						// coordinate of unit's corner (for pathfinder)
	EMoveState				moveState;				// current state; should be modified by SetState() only
	unsigned					moveFlags;				// set of MOVE_FLAG_... values
	float							stateTime;				// amount of time (seconds), unit state is not changed
	float							stateTimeout;
	float             timeStanding;			// amount of time (seconds), unit position was not changed
	float							speedScale;				// used for slowdown
	// unit parameters
	float							speed;

  vector<GhostModeType> ghostMode;
  int ghostModeIndex;
  int curGhostMode;
  
  // movement state and parameters
	Protection::HiddenVar<CVec2, 3>::T	vShortTarget;			// next path point unit moving to
  TFarTarget::T	vFarTarget;				// final path point
	Protection::HiddenVar<CVec2, 7>::T	vLastMoveTarget;	// remembered target point to buffer sequential move commands to the same point
  CPtr<PFBaseUnit>	pUnitTarget; // unit we are moving to; when !IsValid(pUnitTarget) - use vFarTarget
	ZNOCRC
	CObj<CCommonStaticPath>	pStaticPath;
	CObj<CStandartPath2>		pPath;
	CObj<IPointChecking>		pChecking;
	// smoothing path using spline
	CBSpline					spline;						// current spline
	int								splineIter;
	nstl::vector<Protection::HiddenVar<CVec2, 29>::T>	splinePoint; // points for spline construction
	SVector						splineDir0;
	SVector						splineDir1;
	int								splineSegmentLen;
	nstl::vector<Protection::HiddenVar<CVec2, 30>::T> splineTiles; // path points for spline construction
	int								numSplineTiles;
	int								numIncrementalUpdates;
  bool              bSplineRequiresExtraPoint;
	// this field were moved outside of zdata block, because "const MovingUnit*" cannot be parsed correctly
	CPtr<PFBaseMovingUnit> pBlocker;		// MOVE_STATE_BLOCKED, MOVE_STATE_BYPASSING; used for comparison only
	// invariant data
	CPtr<PFBaseMovingUnit> pOwner;
	int								mapMode;					// MAP_MODE_DYNAMIC[_A]
	int								mapModeStatic;		// MAP_MODE_DYNAMIC[_A]
	int								mapModeAll;				// MAP_MODE_ALL[_A]
	ZNOCRCEND
	float							stopDistance;			// used internally for pUnitTarget
  ZNOCRC
	bool							isMarkedOnMap;		// when true, unit is currently marked on TileMap
  ZNOCRCEND
	TMoveDir::T	moveDir;
  //int               oldAngleDi f[6];
  //int               oldAngleIndex;
	CPtr<PFBaseMovingUnit> pAttached;		// attached unit

	float										followDistance;
	CPtr<PFBaseMovingUnit>	pFollowed;
	bool										isFollowing;
  bool                    holdingPosition;
  int 	                  pathFindingSteps;
  bool                    evading;
  bool                    chasing;
  bool										isFollowingForced;

  //suppress FindFreePlace in PlaceUnit 
  bool                    ignoreCollision;

public:
	ZEND int operator&( IBinSaver &f ) { f.Add(2,&origin); f.Add(3,&moveState); f.Add(4,&moveFlags); f.Add(5,&stateTime); f.Add(6,&stateTimeout); f.Add(7,&timeStanding); f.Add(8,&speedScale); f.Add(9,&speed); f.Add(10,&ghostMode); f.Add(11,&ghostModeIndex); f.Add(12,&curGhostMode); f.Add(13,&vShortTarget); f.Add(14,&vFarTarget); f.Add(15,&vLastMoveTarget); f.Add(16,&pUnitTarget);  if(!f.IsChecksum()){ f.Add(17,&pStaticPath); f.Add(18,&pPath); f.Add(19,&pChecking); f.Add(20,&spline); f.Add(21,&splineIter); f.Add(22,&splinePoint); f.Add(23,&splineDir0); f.Add(24,&splineDir1); f.Add(25,&splineSegmentLen); f.Add(26,&splineTiles); f.Add(27,&numSplineTiles); f.Add(28,&numIncrementalUpdates); f.Add(29,&bSplineRequiresExtraPoint); f.Add(30,&pBlocker); f.Add(31,&pOwner); f.Add(32,&mapMode); f.Add(33,&mapModeStatic); f.Add(34,&mapModeAll);  } f.Add(35,&stopDistance);  if(!f.IsChecksum()){ f.Add(36,&isMarkedOnMap);  } f.Add(37,&moveDir); f.Add(38,&pAttached); f.Add(39,&followDistance); f.Add(40,&pFollowed); f.Add(41,&isFollowing); f.Add(42,&holdingPosition); f.Add(43,&pathFindingSteps); f.Add(44,&evading); f.Add(45,&chasing); f.Add(46,&isFollowingForced); f.Add(47,&ignoreCollision); return 0; }

protected:
  void RecryptImpl()
  {	
    Recrypt(origin);
    Recrypt(vShortTarget);
    Recrypt(vFarTarget);
    Recrypt(vLastMoveTarget);
    Recrypt(spline);
  }

private:
  void RecalculateGhostMode();
  void ApplyGhostMode();
  Pathfinding::CCommonPathFinder * GetPathFinder();
  Pathfinding::RoutePathFinder* GetRoutePathFinder();

  bool UseRoutePathFinder(SVector const & startPoint, SVector const & endPoint) const;

  CCommonStaticPath * CreateStaticPath( const SVector& start, const SVector& end );
  CStandartPath2* CreateStandartPath();

	void InitMapMode();
	// walking along path
	bool CreatePath( bool needReversePath );
  bool CreatePathFromSync();
  bool NeedPathFromSync() const;
	// recompute pPath, when new obstacle found; will not allow new path, when recomputed path is
	// much longer than ideal path
  bool MoveToShort(CVec2 dest);
	bool RecomputePath(int allowedOverhead = -1);
	bool UpdatePath();
	bool ValidatePath(bool fast);
  bool ValidatePos( CVec2 pos );
	bool CheckSplineControlPoint();
	bool BypassPoint(CVec2 const& point, int pointSize, float maxOverhead);

	// collision control
	void SetState(EMoveState newState, float timeout = 0);
	void StartMoving();
	void BlockedBy(MovingUnit *otherUnit);
	void BypassingUnit(MovingUnit *otherUnit);
	void PathFailed();
	void Wait(float minTime, float maxTime = 0);

	// spline
	void InitSpline(bool firstTime = false);
	void StraightSpline();
	CVec2 IterateSpline();
	void AddSplineTile(CVec2 const& tile);
	void DropSplineTiles(int count);
	void ClearSpline();

	void TickMove(float timeDelta);
	void TickMoveSpecial(float timeDelta);

	void MoveToInternal( const CVec2& target, float stopDistance, IPointChecking* pointChecking );

  void MarkTilesInternal( bool mark );
  void UnmarkTiles( bool forced = false );
	void MarkTiles();

	// set new unit position, with finding for free place
	bool PlaceUnit( const CVec2& newPosition, float radius = PLACE_UNIT_RADIUS, bool ignoreUnits = false, bool nativeTerrainOnly = false, bool notifyClient = false );
	bool FindFreePlace(CVec2 const& newPosition, float radius, CVec2& foundPosition, bool ignoreUnits, bool nativeTerrainOnly, bool checkWalkable = false, float size = -1.0f, int mapModeFlags = 0, bool checkLineOfSight = false);
	bool FindFreePlace(CVec2 const& newPosition, CVec2 const &attractPoint, float radius, float attractPower, CVec2& foundPosition, bool ignoreUnits, bool nativeTerrainOnly, int mapModeFlags = 0, bool checkLineOfSight = false);
  bool FindFreePlace2(CVec2 const& newPosition,  CVec2 const &attractPoint, float radius, CVec2& foundPosition, bool ignoreUnits, bool nativeTerrainOnly, float size = -1.0f, int mapModeFlags = 0, bool checkLineOfSight = false);
  bool CanOccupyPosition( CVec2 const& position );

	// client notifications
	bool IsClientUnit() const;
	void NotifyClientMove(bool animate = true);
	void NotifyClientStop();
	void NotifyClientTeleport();
	bool ClientIsVisible() const;
	
	// conversion of pathfinder coordinates to map coordinates and vice versa
	const CVec2 GetCenter(CVec2 const& origin) const;		// path -> map
	const CVec2 GetOrigin(CVec2 const& center) const;   // map -> path
	const CVec2 GetCenter() const        { return origin;              }
	const CVec3 GetCenter3() const       { return CVec3( origin, 0.0f ); }
	void SetCenter(CVec2 const& _center);
	void SetOrigin(CVec2 const& _origin);

	void UpdateMoveDir(CVec2 const& dst);

	static int  UnitRangeSorter(const void* _A, const void* _B);

  int GetPathFindingSteps() const;
  PFBaseUnit* GetRealOwner() const;
};

class PFBaseMovingUnit : public PFBaseUnit

{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0xE5CBCC2, PFBaseMovingUnit, NGameX::PFClientBaseMovingUnit);

	friend class  MovingUnit;
  friend class  CollisionResolver;
	friend struct PredictedUnitState;
	friend struct MovingUnitsCollector;
  friend struct PushableUnitsCollector;

	bool IsSameTarget() const;

public:
	PFBaseMovingUnit(PFWorld* pWorld, const CVec3 &pos, const CVec2 & direction, const NDb::Unit &unitDesc);

  virtual void Initialize(InitData const& data);
  virtual bool Step(float dtInSeconds);

  virtual bool GetNeedRotate() const { return false; }
  virtual void SetNeedRotate( bool /* _needRotate */ ) { }
  virtual void RotateIfNeeded() { };

	// movement control
	bool MoveTo( const CVec2& target, float stopDistance = 0.0f, IPointChecking* pointChecking = NULL );
	bool MoveTo( PFBaseUnit*  target, float stopDistance = 0.0f, IPointChecking* pointChecking = NULL );
	bool TeleportTo( const CVec2& target, bool instantMove = true, bool notifyDispatches = true );
  void Stop( bool notifyClient = true );
  void SetForbidStop( const bool _forbidStop ) { forbidStop = _forbidStop; }

  virtual void OnStopped(){ }

  // Special movement functions
  // Movement by static map (completely ignoring moving units) by straight line.
  // Movement will be stopped on collision with static map object (entering IDLE state).
  // No client callbacks executed.
  bool MoveToSpecial( const CVec2&            target, bool notifyClient = true ) { return world.MoveToSpecial( target, notifyClient ); }
  bool MoveToSpecial( const CPtr<PFBaseUnit>& target, bool notifyClient = true ) { return world.MoveToSpecial( target, notifyClient ); }

  void FollowTo( const CPtr<PFBaseMovingUnit>& pUnit, bool forced = false ) { world.FollowTo( pUnit, forced ); }
  CPtr<PFBaseMovingUnit> GetFollowedBy() const { return world.pFollowed; }

  int  GetGhostMode() const                      { return world.GetGhostMode(); }
  int  SetGhostMode( int _mode, bool _override ) { return world.SetGhostMode( _mode, _override ); }
  void ResetGhostMode( int _index )              { world.ResetGhostMode( _index ); }

	virtual void Reset();

  virtual void OnGameFinished( const NDb::EFaction failedFaction );

  void SetMount( bool _isMount )
  {
    isMount = _isMount;
  }

  virtual bool IsMount() const
  {
    return isMount;
  }

  void SetMoveFlags(unsigned value = 0);
	unsigned GetMoveFlags() const     { return world.moveFlags; }
	float SetUnitSpeed(float value); // override speed, valid for MOVE_FLAG_OVERRIDE_SPEED only; will return actual unit speed

	// utilities

	// check movement possibility; returns maximal movement distance
	float CheckStraightMove(CVec2 const &target, int mapModeFlags = 0);

	// Finds free plase to drop some item. Checks posibility to reach that point from the unit position. If size is specified - checks walkability using that size, instead unit's size
	inline bool FindFreePlaceForDrop(CVec2 const& newPosition, float radius, CVec2& foundPosition, float size = -1.0f, bool ignoreUnits = false, bool nativeTerrainOnly = false)
	{ return world.FindFreePlace(newPosition, radius, foundPosition, ignoreUnits, nativeTerrainOnly, true, size); }
	// set new unit position, with finding for free place
//	bool PlaceUnit(CVec2 const& newPosition, float radius = MovingUnit::PLACE_UNIT_RADIUS);
	// find free place for unit
	inline bool FindFreePlace(CVec2 const& newPosition, float radius, CVec2& foundPosition, bool ignoreUnits = false, bool nativeTerrainOnly = false, int mapModeFlags = 0, bool checkLineOfSight = false)
	{ return world.FindFreePlace(newPosition, radius, foundPosition, ignoreUnits, nativeTerrainOnly, false, -1.0f, mapModeFlags, checkLineOfSight); }
	inline bool FindFreePlace(CVec2 const& newPosition, CVec2 const &attractPoint, float radius, float attractPower, CVec2& foundPosition, bool ignoreUnits = false, bool nativeTerrainOnly = false, int mapModeFlags = 0, bool checkLineOfSight = false)
	{ return world.FindFreePlace(newPosition, attractPoint, radius, attractPower, foundPosition, ignoreUnits, nativeTerrainOnly, mapModeFlags, checkLineOfSight); }
  inline bool FindFreePlace2(CVec2 const& newPosition,  CVec2 const &attractPoint, float radius, CVec2& foundPosition, bool ignoreUnits = false, bool nativeTerrainOnly = false, int mapModeFlags = 0, bool checkLineOfSight = false)
  { return world.FindFreePlace2(newPosition, attractPoint, radius, foundPosition, ignoreUnits, nativeTerrainOnly, -1.0f, mapModeFlags, checkLineOfSight); }
  inline bool CanOccupyPosition( CVec2 const& position )
  { return world.CanOccupyPosition( position ); }

  bool PlaceUnit( const CVec2& newPosition, bool ignoreUnits, bool nativeTerrainOnly, bool notifyClient = false );
	void PlaceUnitWithPush( const CVec2& newPosition, float pushRadius, bool force = false, bool nativeTerrainOnly = false );

	// build map for available paths; note: higher maxDistance values will
	// consume more memory and CPU !
	PathMap* BuildPathMap(float maxDist);

	virtual bool IsMoving() const         { return world.IsMoving();    }
  bool IsMovingSpecial() const          { return world.IsMovingSpecial(); }
  bool IsColliding() const              { return world.IsColliding(); }
	bool IsMounted() const                { return world.moveState == MOVE_STATE_MOUNTED; }
	bool IsMarkedOnMap() const            { return world.isMarkedOnMap;    }
  MovingUnit::TMoveDir::TConstRef GetMoveDirection() const { return world.moveDir;       }
  MovingUnit::TFarTarget::TConstRef GetDestination() const   { return world.GetDestination(); }
  bool IsHoldingPosition() const        { return world.IsHoldingPosition(); }
  virtual bool IsEvading() const        { return world.IsEvading(); }

  virtual bool IsChasing() const         { return world.IsChasing();    }
  virtual void OnChasing(bool bChase)   { world.OnChasing(bChase); }


  virtual void OnEvading(bool bEvade)   { world.OnEvading(bEvade); }
  virtual void OnHold( bool bHold )     { world.OnHold( bHold ); }

  void SetMoveDirection( CVec2 const &dst ) { world.UpdateMoveDir( dst ); }

	virtual float GetTimeStanding() const { return world.timeStanding;  }

  // unit collector
  static void GetAllUnits(const PFVoxelMap *pVoxelMap,
    vector<PFBaseMovingUnit*> &movingUnits, bool markedOnly, const PFBaseMovingUnit *skipUnit = NULL);
  static void GetPushableUnitsInRange(const PFVoxelMap *pVoxelMap, const CVec2 &center, float radius,
    vector<PFBaseMovingUnit*> &_pushableUnits, vector<PFBaseMovingUnit*> &_nonPushableUnits, bool _markedOnly, const PFBaseMovingUnit *_skipUnit = NULL );
  static void GetAllUnitsInRangeConsiderSize(const PFVoxelMap *pVoxelMap, const CVec2 &center, float radius,
    vector<PFBaseMovingUnit*> &movingUnits, bool markedOnly, const PFBaseMovingUnit *skipUnit = NULL);

  void AttachUnit(CPtr<PFBaseMovingUnit> const& pUnit);
	void DetachUnit();
  CPtr<PFBaseMovingUnit> const& GetAttachUnit() const { return world.GetAttachUnit(); }

  int GetUnitRadius() const;
  int GetUnitDynamicRadius() const;

  virtual void UpdateWarFog();

	// interface for derived classes
	float GetUnitSpeed() const { return world.speed; }

  //notify inbound dispatches
  void NotifyDispatchesOnTargetTeleport();

  void SetPlaceUnitIgnoreCollision(bool ignore) { world.SetPlaceUnitIgnoreCollision(ignore);}

protected:
	// default constructor is required for all CObjectBase classes, and should be available for derived classes
	PFBaseMovingUnit();

	// unit lifetime
	void MovingUnitStep(float worldTimeDelta);
	void NotifyMoving( bool teleported );

  virtual void StepInvisibility();

	// unit destruction
	virtual void OnDie();
  virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc = 0);

  // minor optimization
  bool doNotTeleportInStepInvisibility;

	ZDATA_(PFBaseUnit)
	MovingUnit				world;
	int								random;															// 0..1023, updated on every Step()
  bool              isMount;
  bool              forbidStop;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseUnit*)this); f.Add(2,&world); f.Add(3,&random); f.Add(4,&isMount); f.Add(5,&forbidStop); return 0; }

protected:
	// data for asynchronous unit
	//MovingUnit				local;
	//MovingUnit				*pUnit[MovingUnit::TYPE_COUNT];			// points to world and local; used to access unit by type
	//bool							isSync;															// when true, world and local should be the same
 // int               asyncCmdCount;
	//float							asyncTime;													// number of seconds unit is asynchronous

	//inline MovingUnit& unit(MovingUnit::Type type) { return *pUnit[type]; }

	// callbacks
	// Called when ValidatePath() returns false
	virtual void OnInvalidPath() {}

#ifndef _SHIPPING
  virtual CObj<NDebug::DebugObject> CreateDebugObject();
public:
	void ShowPaths(Render::IDebugRender* pRender) const;
	void ShowSpeed(Render::IDebugRender* pRender) const;
	void ShowSectors(Render::IDebugRender* pRender) const;
	void ShowPredict(Render::IDebugRender* pRender) const;
  void ShowUnit(Render::IDebugRender* pRender) const;
#endif // _SHIPPING
};

} // namespace
