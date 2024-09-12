#ifndef COLLISIONRESOLVER_H_14A2D6B1_A35
#define COLLISIONRESOLVER_H_14A2D6B1_A35

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
class MovingUnit;
class PFBaseMovingUnit;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CollisionResolver : public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0x4979F400, CollisionResolver );

  friend class  PFBaseMovingUnit;

	CollisionResolver() { }
public:
	CollisionResolver( PFWorld* world ) : PFWorldObjectBase( world, 0 ) { }
	void Resolve( const vector<PFBaseMovingUnit*> units, float timeDelta ) const;
	virtual bool NeedToBeStepped() { return false; }

private:
  struct UnitInfo
  {
    MovingUnit* unit;
	  CCircle     bounds;
	  SRect       speedRect;
	  bool        blockedBefore;
	  bool				blockedNow;
  };

  struct CollideInfo
  {
	  // input values ...
	  UnitInfo*		infoA;
	  UnitInfo*		infoB;
	  float				speedA;			// may differ from active unit's speed
	  float				speedB;
	  // output values ...
	  float				collideTime;
	  // state for A
	  CVec2				predictedPosA;
	  CVec2				predictedDirA;
	  // state for B
	  CVec2				predictedPosB;
	  CVec2				predictedDirB;

    void Swap();
    bool IsAOnBackOfB() const;
    bool IsBOnBackOfA() const;
  };

  struct PredictedUnitState
  {
	  MovingUnit* pUnit;
	  CVec2			pos;						// current (predicted) unit origin
	  CVec2			dir;						// current move direction
	  CVec2			dest;						// current unit destination
	  int				curPoint;				// current point index in splineTiles and pPath
	  float			speed;					// unit speed for prediction

	  PredictedUnitState( MovingUnit* unit );

	  bool Advance( float toMove );
	  bool IsIntersected( const PredictedUnitState& other ) const;
  };

  SRect GetSpeedRect( MovingUnit const * unit) const;
  SRect GetSpeedRect( MovingUnit const * unit, float speedScale, float extraSize ) const;
  CCircle GetSpeedCircle( MovingUnit* unit, float speedScale, float extraSize ) const;

	// utility function for qsort()
  static int UnitInfoSorter( const void* a, const void* b );

  // predict collision using unit path and speed; returns true when collision is predicted
  bool PredictCollision( CollideInfo& C, float maxTime ) const;

  // processing collision in different states
  void CollideMoving( CollideInfo& C, float timeDelta ) const;
	void CollideBlocked( CollideInfo& C, float timeDelta ) const;
	// tick collision state without real collision
	void CollisionIdle( MovingUnit* unit, bool blockedBefore, float timeDelta ) const;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //#define COLLISIONRESOLVER_H_14A2D6B1_A35