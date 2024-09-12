#pragma once

#include "PFDispatch.h"

namespace NGameX
{
  class PFDispatchUniformLinearMove;
  class PFDispatchWithLink;
  class PFDispatchByTime;
  class PFDispatchRockmanMace;
}

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFDispatchImmediate : public DBLinker<PFDispatch, NDb::DispatchImmediate>
{
  WORLD_OBJECT_METHODS(0x1E5C64E1, PFDispatchImmediate)
  // Dispatch immediate doesn't require client object (pClientObject will be 0)
public:
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
  PFDispatchImmediate(CreateParams const &cp): Base(cp) {}
private:
  PFDispatchImmediate() {}
  virtual void OnStart();
  virtual bool Step(float dtInSeconds);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFDispatchContinuous : public DBLinker<PFDispatch, NDb::DispatchContinuous>
{
  WORLD_OBJECT_METHODS(0xA067A480, PFDispatchContinuous)
public:
  PFDispatchContinuous(CreateParams const &cp);
  ~PFDispatchContinuous();
protected:
  PFDispatchContinuous() {}
  virtual void OnStart();
  virtual bool Step(float dtInSeconds);
	virtual void Die();

  virtual void AddPersistentApplicators( vector<NDb::Ptr<NDb::BaseApplicator>> const& newPersistentApplicators, PFAbilityData* upgrader = NULL );
  
  ZDATA_(DBLinker)
  PFBaseApplicator::AppliedRing  persistentApplicators;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&persistentApplicators); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFDispatchUniformLinearMove : public DBLinker<PFDispatchContinuous, NDb::DispatchLinear>
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x1E5C64C1, PFDispatchUniformLinearMove, NGameX::PFDispatchUniformLinearMove)
public:
  seDECLARE_CPTRRING( PFDispatchUniformLinearMove, unitDispatchesPart, UnitDispatchesRing );

  PFDispatchUniformLinearMove(CreateParams const &cp);
  virtual void CreateClientDispatch();

	virtual void Reset();

  CVec2 const &GetCurPos() const {return curPos;}
  float GetSpeed() const { return speed; } 
  float GetStartTime() const {return m_startTime;}
  
  // target found a way of evading the collision
  // dispatch will continue moving to the last known target position
  void DropTarget();

  virtual void OnStart();
  virtual void OnTargetTeleport();
  virtual void OnStopAttackingTarget();

	virtual CVec3 GetCurrentPosition() const { return CVec3(curPos.x, curPos.y, 0.f); }
  virtual bool IsSuspended() const { return suspendTime > EPS_VALUE; }
  void ForceArrive( Target const& target, bool playApplyEffect );
protected:
  PFDispatchUniformLinearMove() {}
  ~PFDispatchUniformLinearMove() { UnitDispatchesRing::safeRemove(this); }
  virtual bool OnArrive( bool canApply, bool playApplyEffect = true );
  virtual void OnDie() { UnitDispatchesRing::safeRemove(this); PFDispatchContinuous::OnDie(); }
  virtual void SetNewTarget( const Target & _target );

private:
  virtual bool Step(float dtInSeconds);
	void UpdatePersistentApplicatorsPosition();

  ZDATA_(DBLinker)
protected:
  CVec2 curPos;
  CVec2 lastTargetPos;
  float speed;
  float m_startTime;
  float travelledDistance;
  float maxDistance;

  CVec2 originalSenderPos;
  CVec2 originalDir;
  float clientStartDelay;
  float suspendTime;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&curPos); f.Add(3,&lastTargetPos); f.Add(4,&speed); f.Add(5,&m_startTime); f.Add(6,&travelledDistance); f.Add(7,&maxDistance); f.Add(8,&originalSenderPos); f.Add(9,&originalDir); f.Add(10,&clientStartDelay); f.Add(11,&suspendTime); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFDispatchByTime : public DBLinker<PFDispatchContinuous, NDb::DispatchByTime>
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x1E5C346A, PFDispatchByTime, NGameX::PFDispatchByTime)
public:
  PFDispatchByTime(CreateParams const &cp);
  virtual void CreateClientDispatch();

  CVec3 const &GetDestination() const {return destination;}
	virtual void Reset();

private:
  PFDispatchByTime() {}

  virtual void OnStart();
  virtual bool Step(float dtInSeconds);

  ZDATA_(DBLinker)
  CVec3 destination;
  float duration;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&destination); f.Add(3,&duration); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFDispatchWithLink : public DBLinker<PFDispatchUniformLinearMove, NDb::DispatchLinearWithLink>
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0xA067BBC1, PFDispatchWithLink, NGameX::PFDispatchWithLink)
public:
  PFDispatchWithLink(CreateParams const &cp) : Base(cp) {}
  virtual void CreateClientDispatch();
	virtual void Reset();

protected:
  PFDispatchWithLink() {}

  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFDispatchRockmanMace : public DBLinker<PFDispatchWithLink, NDb::DispatchRockmanMace>
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0xA073CA82, PFDispatchRockmanMace, NGameX::PFDispatchRockmanMace)
public:
  PFDispatchRockmanMace(CreateParams const &cp);
  virtual void CreateClientDispatch();
	virtual void Reset();

protected:
  PFDispatchRockmanMace() {}
  virtual bool OnArrive(bool canApply, bool playApplyEffect = true );

private:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
};

}
