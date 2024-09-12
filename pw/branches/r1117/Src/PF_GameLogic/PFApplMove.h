#pragma once

#include "PFApplBuff.h"
#include "PFApplicator.h"
#include "PFCreature.h"

namespace NWorld
{

class PFWorld;
class PFBaseUnit;
class PFBaseMovingUnit;
class PFSingleTargetSelector;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplMoveTo: public DBLinker<PFApplBuff, NDb::MoveToApplicator>
{
  WORLD_OBJECT_METHODS(0x0E676B42, PFApplMoveTo);
    
  explicit PFApplMoveTo() : targetPosition(VNULL2), ghostMoveIndex(-1), isMoveDirect(false), isNotStackable(false) {}

  ZDATA_(DBLinker)
  int ghostMoveIndex;
  CObj<IPFState> moveState;
  bool isMoveDirect;
  bool isNotStackable;
protected:
  CVec2 targetPosition;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&ghostMoveIndex); f.Add(3,&moveState); f.Add(4,&isMoveDirect); f.Add(5,&isNotStackable); f.Add(6,&targetPosition); return 0; }

  PFApplMoveTo(PFApplCreatePars const &cp) : Base(cp), targetPosition(VNULL2), ghostMoveIndex(-1), isMoveDirect(false), isNotStackable(false) {}

  bool IsMoveDirect() const { return isMoveDirect; }
  bool IsNotStackable() const { return isNotStackable; }

protected:
  virtual bool Start();
  virtual void Stop();
  virtual bool Step(float dtInSeconds);
  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_ALL; }
private:
  bool MoveIt(const CVec2 &pos);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplKickAway: public DBLinker<PFBaseApplicator, NDb::KickAwayApplicator>
{
  WORLD_OBJECT_METHODS(0xE5CC393, PFApplKickAway);
protected:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplKickAway(PFApplCreatePars const &cp) 
    : Base(cp) {}
  PFApplKickAway() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplShift : public DBLinker<PFBaseApplicator, NDb::ShiftApplicator>
{
  WORLD_OBJECT_METHODS(0x1E726441, PFApplShift);
protected:
  ZDATA_(DBLinker)
	CObj<PFSingleTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

  PFApplShift(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplShift() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplThrow : public DBLinker<PFBaseApplicator, NDb::ThrowApplicator>
{
  WORLD_OBJECT_METHODS( 0x1E729C41, PFApplThrow );
  PFApplThrow() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  bool CheckFly();
  bool StartFly();

  CObj<PF_Core::BasicEffect> pFlyEffect;
  CObj<PF_Core::BasicEffect> pLandingEffect;

  ZDATA_( DBLinker )

  bool isFlying;
  bool hasStartedTakeOff;
  Target targ;
  int ghostMoveIndex;
  float originalSpeed;
  
protected:
  CPtr<PFCreature> pTargetUnit;
	float flightTime;
	float animatedTime;
  bool bStarted;
  CObj<IPFState> lastTargetState;
  CPtr<PFBaseUnit>  lastTargetTarget;

  CObj<PFSingleTargetSelector> hitTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,( DBLinker *)this); f.Add(2,&isFlying); f.Add(3,&hasStartedTakeOff); f.Add(4,&targ); f.Add(5,&ghostMoveIndex); f.Add(6,&originalSpeed); f.Add(7,&pTargetUnit); f.Add(8,&flightTime); f.Add(9,&animatedTime); f.Add(10,&bStarted); f.Add(11,&lastTargetState); f.Add(12,&lastTargetTarget); f.Add(13,&hitTargetSelector); return 0; }

  PFApplThrow( PFApplCreatePars const &cp )
  : Base(cp)
  , flightTime(0.0f)
  , animatedTime(0.0f)
  , heightModifier(1.0f)
  , bStarted(false)
  , isFlying(false)
  , hasStartedTakeOff(false)
  , targ()
  , ghostMoveIndex(-1)
  , originalSpeed(0.0f)
  , hitTargetSelector()
  {}

protected:
  float heightModifier; // 0...1

  virtual bool Start();
  virtual void Stop();

  virtual void PrepareFlyEffect();
  virtual void ApplyFlyEffect();
  virtual void KillFlyEffect();
  
  virtual bool NeedToStopOnDeath() const;
  virtual bool NeedToStopOnSenderDeath() const;
  virtual bool NeedToDisableOnDeath() const;
  virtual bool CanBeAppliedOnDead();

  virtual bool Step( float dtInSeconds );

	virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
	virtual int GetAcceptableUnitTypeFlags() const
	{
		return NDb::SPELLTARGET_HEROMALE | NDb::SPELLTARGET_HEROFEMALE | NDb::SPELLTARGET_CREEP | NDb::SPELLTARGET_SIEGECREEP
      | NDb::SPELLTARGET_SUMMON | NDb::SPELLTARGET_ALLNEUTRALS | NDb::SPELLTARGET_DUMMYUNIT | NDb::SPELLTARGET_FACTIONCHAMPION;
	}

  bool CheckHit() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplFly : public DBLinker<PFBaseApplicator, NDb::FlyApplicator>
{
  WORLD_OBJECT_METHODS( 0x2B789AC1, PFApplFly );
  PFApplFly() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  void StartFly();
  bool CheckFly();
  void UpdateLifeTime( float newLifeTime );

  vector<int> oldAnimations;

  ZDATA_( DBLinker )

  int ghostMoveIndex;

protected:
  CPtr<PFCreature> pTargetUnit;
  bool bStarted;
  float animatedTime;
  float lifeTime;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,( DBLinker *)this); f.Add(2,&ghostMoveIndex); f.Add(3,&pTargetUnit); f.Add(4,&bStarted); f.Add(5,&animatedTime); f.Add(6,&lifeTime); return 0; }

  PFApplFly( PFApplCreatePars const &cp )
    : Base(cp)
    , bStarted(false)
    , ghostMoveIndex(-1)
    , animatedTime(0.0f)
    , lifeTime(0.0f)
  {}

protected:
   virtual bool Start();
   virtual bool Step( float dtInSeconds );
   virtual void Stop();
   virtual void Reset();

   void ReplaceAnimations();
   void RollbackAnimations();

private:
  void ClientStartFly();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplAttract: public DBLinker<PFBaseApplicator, NDb::AttractApplicator>
{
  WORLD_OBJECT_METHODS(0xF61F481, PFApplAttract);
protected:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplAttract(PFApplCreatePars const &cp) 
    : Base(cp) {}
  PFApplAttract() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplAttackTarget: public DBLinker<PFApplBuff, NDb::AttackTargetApplicator>, public PFBaseUnitEventListener
{
	WORLD_OBJECT_METHODS(0x9E678B07, PFApplAttackTarget);
protected:
	ZDATA_(DBLinker)
	ZNOPARENT(PFBaseUnitEventListener)
	CPtr<PFBaseUnit>  pTarget2Attack;
	NDb::EParentNotification event2Send;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTarget2Attack); f.Add(3,&event2Send); return 0; }

	PFApplAttackTarget(PFApplCreatePars const &cp) : Base(cp), event2Send(NDb::PARENTNOTIFICATION_NA) {}
	PFApplAttackTarget() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
	bool DoAttack();

	virtual bool Start();
	virtual void Stop();
	virtual bool Step(float dtInSeconds);

	virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent);

	virtual void DumpInfo(NLogg::CChannelLogger &logger) const;

	virtual bool IsStackableWithTheSameType() const { return false; }

	virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
	virtual int GetAcceptableUnitTypeFlags() const 
	{ 
    return NDb::SPELLTARGET_HEROMALE | NDb::SPELLTARGET_HEROFEMALE | NDb::SPELLTARGET_CREEP | NDb::SPELLTARGET_SIEGECREEP
      | NDb::SPELLTARGET_SUMMON | NDb::SPELLTARGET_ALLNEUTRALS | NDb::SPELLTARGET_DUMMYUNIT | NDb::SPELLTARGET_FACTIONCHAMPION; 
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplTeleport: public DBLinker<PFBaseApplicator, NDb::TeleportApplicator>
{
	WORLD_OBJECT_METHODS(0x9E67C3C0, PFApplTeleport);
public:
	PFApplTeleport(PFApplCreatePars const &cp) : Base(cp) {}
	PFApplTeleport() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
	virtual bool Start();
	virtual bool Step(float dtInSeconds)
	{
		NI_ALWAYS_ASSERT("Must not get here");
		return true;
	}
	virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PFApplGhostMove : public DBLinker<PFApplBuff, NDb::GhostMoveApplicator>
{
  WORLD_OBJECT_METHODS(0xB74F481, PFApplGhostMove);
  ZDATA_(DBLinker)
  int ghostMoveIndex;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&ghostMoveIndex); return 0; }
  PFApplGhostMove(PFApplCreatePars const &cp) : Base(cp), ghostMoveIndex(-1) {}
  PFApplGhostMove() : ghostMoveIndex(-1) {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
protected:
  virtual bool Start();
  virtual void Stop();
};


}