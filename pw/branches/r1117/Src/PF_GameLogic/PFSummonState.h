#pragma once

#include "PFFsm.h"
#include "PFBaseMovingUnit.h"

namespace NWorld
{

class PFSummonAIBaseState
  : public PFBaseMovingUnitState
  , public PFHFSM
{
  WORLD_OBJECT_METHODS(0xF618400, PFSummonAIBaseState);

  enum ESummonTask
  {
    ST_NONE = 0,
    ST_MOVE_TO_MASTER_DESTINATION,
    ST_BACK_TO_FORMATION_PLACE,
    ST_RETURN_TO_LASH_RANGE,
  };

public:
  PFSummonAIBaseState( const CPtr<PFBaseMovingUnit>& pOwner );
  void SetIgnoreTimer( float fTime ) { ignoreTargetsTimer = fTime; }
  void SetWantedDestination( const CVec2& dest ) { masterDestination = dest; }

  bool CanSelectTarget( const PFBaseUnit*  ) const { return ignoreTargetsTimer <= 0; }
  
protected:
  virtual bool OnStep( float dt );
  PFSummonAIBaseState() : maxEscortDistance( 0.0f )
    , lastMasterDestination( 0.0f, 0.0f )
    , masterDestination( 0.0f, 0.0f )
    , returnToMasterTimeout(0.0f)
    , currentTask(ST_BACK_TO_FORMATION_PLACE)
    , ignoreTargetsTimer(0.0f)
    , isStationarySummon(false)
    { }
  
private:
  ZDATA_(PFBaseMovingUnitState);
  ZPARENT(PFHFSM);
  CPtr<PFBaseUnit>     pMaster;
  float                maxEscortDistance;
  CVec2                lastMasterDestination;
  ESummonTask          currentTask;
  bool                 isStationarySummon;
  float                returnToMasterTimeout;
  float                ignoreTargetsTimer;
  CVec2                masterDestination;

  
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,(PFHFSM*)this); f.Add(3,&pMaster); f.Add(4,&maxEscortDistance); f.Add(5,&lastMasterDestination); f.Add(6,&currentTask); f.Add(7,&isStationarySummon); f.Add(8,&returnToMasterTimeout); f.Add(9,&ignoreTargetsTimer); f.Add(10,&masterDestination); return 0; }
};

class PFSummonAIAttackState
  : public PFBaseMovingUnitState
  , public PFHFSM
{
  WORLD_OBJECT_METHODS(0xF618482, PFSummonAIAttackState);

public:
  PFSummonAIAttackState( CPtr<PFBaseMovingUnit> const& pOwner, CPtr<PFBaseUnit> pTarget, bool bStrongTarget = true );

protected:
  virtual bool OnStep(float dt);
  virtual void OnEnter();
  virtual void OnLeave();
  PFSummonAIAttackState() : maxChaseDistance(0.0f), bStrongTarget(false), isStationarySummon(false), leashRange (0.f) {}

private:
  ZDATA_(PFBaseMovingUnitState);
  ZPARENT(PFHFSM);
  CPtr<PFBaseUnit>      pMaster;
  float                 maxChaseDistance;
  bool                  bStrongTarget;
  bool                  isStationarySummon;
  CPtr<PFBaseUnit>      pTarget;
  float leashRange;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,(PFHFSM*)this); f.Add(3,&pMaster); f.Add(4,&maxChaseDistance); f.Add(5,&bStrongTarget); f.Add(6,&isStationarySummon); f.Add(7,&pTarget); f.Add(8,&leashRange); return 0; }
};
/* оказался не нужен, пока что оставляю в коде на какое-то время - а вдруг дизайнеры опять что-то придумают 
class PFSummonAIResponseState
  : public PFBaseMovingUnitState
  , public PFHFSM
{
  WORLD_OBJECT_METHODS(0xB1A53B00, PFSummonAIResponseState);

public:
  PFSummonAIResponseState( CPtr<PFBaseMovingUnit> const& pOwner, const CVec2& masterDestination, float responseTime );

protected:
  virtual bool OnStep( float dt );
  PFSummonAIResponseState() : ignoreTargetsTimer( 0.0f ), moveToDestination( false ) { }

private:
  ZDATA_(PFBaseMovingUnitState);
  ZPARENT(PFHFSM);
  CPtr<PFBaseUnit>     pMaster;
  float                ignoreTargetsTimer;
  CVec2                masterDestination;
  bool                 moveToDestination;
  

  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,(PFHFSM*)this); f.Add(3,&pMaster); f.Add(4,&ignoreTargetsTimer); f.Add(5,&masterDestination); f.Add(6,&moveToDestination); return 0; }
};
*/
}
