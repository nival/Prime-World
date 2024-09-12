#pragma once

#include "PFApplBuff.h"
#include "PFBaseUnitEvent.h"
#include "PFApplChannelling.h"
#include "PFFlagpole.h"
#include "PFPickupable.h"


namespace NWorld
{

class PFWorld;
class PFBaseUnit;
class PFEaselPlayer;

class PFApplDropTree : public DBLinker<PFBaseApplicator, NDb::DropTreeApplicator>
{
  WORLD_OBJECT_METHODS(0xF622B00, PFApplDropTree);
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplDropTree(PFApplCreatePars const &cp);
  PFApplDropTree() {}
protected:
  virtual bool Start();
	virtual int GetAcceptableTargetFlags() const { return Target::FLAG_OBJECT; }
	virtual int GetAcceptableUnitTypeFlags() const { return NDb::SPELLTARGET_TREE; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplRaiseFlag : public DBLinker<PFApplChannelling, NDb::RaiseFlagApplicator>
{
  WORLD_OBJECT_METHODS(0xB76AA40, PFApplRaiseFlag)
  ZDATA_(DBLinker)
  CPtr<PFFlagpole> pFlagpole;
  bool started;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pFlagpole); f.Add(3,&started); return 0; }
  PFApplRaiseFlag(PFApplCreatePars const &cp) : Base(cp), started( false ) {}
  PFApplRaiseFlag() : started( false ) {}
protected:
  virtual bool Start();
  virtual bool Step( float dtInSeconds );
  virtual void Fire();
  virtual void Cancel();

  virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplDealedDamageConverter: public DBLinker<PFBaseApplicator, NDb::DealedDamageConverterApplicator>
{
  WORLD_OBJECT_METHODS(0xE5CC395, PFApplDealedDamageConverter);
protected:
  ZDATA_(DBLinker)
  float scale;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&scale); return 0; }

  PFApplDealedDamageConverter(PFApplCreatePars const &cp) 
    : Base(cp), scale(GetDB().scale) {}
  PFApplDealedDamageConverter() {}

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds)
  {
    NI_ALWAYS_ASSERT("Must not get here");
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplSpellSwitch: public DBLinker<PFBaseApplicator, NDb::SpellSwitchApplicator>
{
  WORLD_OBJECT_METHODS(0x0E674B80, PFApplSpellSwitch);
protected:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplSpellSwitch(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplSpellSwitch() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds)
  {
    NI_ALWAYS_ASSERT("Must not get here");
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplWaitForSpell: public DBLinker<PFApplBuff, NDb::WaitForSpellApplicator>
{
	WORLD_OBJECT_METHODS(0x9E67ACC2, PFApplWaitForSpell);
protected:
	ZDATA_(DBLinker)
	CPtr<PFDispatch> pDispatch;
	bool             isDispatchFinished;
  CObj<PFSingleTargetSelector> pTargetSelector;
  bool             isFirstHitTargetFound;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pDispatch); f.Add(3,&isDispatchFinished); f.Add(4,&pTargetSelector); f.Add(5,&isFirstHitTargetFound); return 0; }

	PFApplWaitForSpell(PFApplCreatePars const &cp) : Base(cp), isDispatchFinished(false), isFirstHitTargetFound(false) {}
	PFApplWaitForSpell() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
  virtual void OnDispatchStep( PFDispatch* pDispatch );

protected:
	virtual bool Start();
	virtual void Stop();
	virtual bool Step(float dtInSeconds);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplNaftaTransfer: public DBLinker<PFBaseApplicator, NDb::NaftaTransferApplicator>
{
  WORLD_OBJECT_METHODS(0x0E676B41, PFApplNaftaTransfer);
protected:
  ZDATA_(DBLinker)
  float naftaTransferred;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&naftaTransferred); return 0; }

  PFApplNaftaTransfer(PFApplCreatePars const &cp) : Base(cp), naftaTransferred(0.0f) {}
  PFApplNaftaTransfer() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual float GetVariable(const char* sVariableName) const;
	virtual bool Start();
  virtual bool Step(float dtInSeconds)
  {
    NI_ALWAYS_ASSERT("Must not get here");
    return true;
  }
	virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplModifyTerrain: public DBLinker<PFBaseApplicator, NDb::ModifyTerrainApplicator>
{
	WORLD_OBJECT_METHODS(0x0E676B43, PFApplModifyTerrain);
protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFApplModifyTerrain(PFApplCreatePars const &cp) : Base(cp) {}
	PFApplModifyTerrain() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
	virtual bool Start();
  virtual bool Step(float dtInSeconds);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplWatch: public DBLinker<PFApplBuff, NDb::WatchApplicator>, public PFBaseUnitEventListener
{
	WORLD_OBJECT_METHODS(0x9E678B06, PFApplWatch);
protected:
	ZDATA_(DBLinker)
  ZNOPARENT(PFBaseUnitEventListener)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFApplWatch(PFApplCreatePars const &cp) : Base(cp) {}
	PFApplWatch() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
	virtual bool Start();
	virtual void Stop();
	virtual bool IsStackableWith(PFBaseApplicator *pAppl) const { return true; }
	virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplProgram: public DBLinker<PFApplBuff, NDb::ProgramApplicator>
{
	WORLD_OBJECT_METHODS(0x9E676A81, PFApplProgram);
protected:
	ZDATA_(DBLinker)

	int applicatorExecuting;
	CPtr<PFBaseApplicator> pApplExecuting;
  float                  currentDelayTimer;
  bool                   isDelayTimerEnabled;
	bool ready2Execute;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&applicatorExecuting); f.Add(3,&pApplExecuting); f.Add(4,&currentDelayTimer); f.Add(5,&isDelayTimerEnabled); f.Add(6,&ready2Execute); return 0; }

	PFApplProgram(PFApplCreatePars const &cp) : Base(cp), applicatorExecuting(-1), ready2Execute(true), currentDelayTimer(-1.0f), isDelayTimerEnabled(false) {}
	PFApplProgram() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
	virtual bool Start();
	virtual void Stop();
	virtual bool Step(float dtInSeconds);
	virtual void OnNotification(PFBaseApplicator &appl, NDb::EParentNotification note);

	virtual void DumpInfo(NLogg::CChannelLogger &logger) const;

	bool ExecuteNext();
	bool IsFinished() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplForAllTargets : public DBLinker<PFApplBuff, NDb::ForAllTargetsApplicator>
{
  WORLD_OBJECT_METHODS(0xB76BC80, PFApplForAllTargets);
protected:
  ZDATA_(DBLinker)
  int                    currentTarget;
  bool                   ready2Execute;
  CPtr<PFBaseApplicator> currentProgram;
  vector< Target >       targets;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&currentTarget); f.Add(3,&ready2Execute); f.Add(4,&currentProgram); f.Add(5,&targets); return 0; }

  PFApplForAllTargets(PFApplCreatePars const &cp) : Base(cp), currentTarget(-1), ready2Execute(false) {}
  PFApplForAllTargets() { }

  virtual float GetVariable(const char* sVariableName) const;
protected:
  virtual bool Start();
  virtual void Stop();
  virtual bool Step(float dtInSeconds);
  virtual void OnNotification(PFBaseApplicator &appl, NDb::EParentNotification note);
private:
  bool ExecuteNext();
  bool IsFinished() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplMovementControl: public DBLinker<PFApplBuff, NDb::MovementControlApplicator>
{
  WORLD_OBJECT_METHODS(0x2C67DB41, PFApplMovementControl);
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplMovementControl(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplMovementControl() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual void Enable();
	virtual void Disable();
	virtual bool IsStackableWithTheSameType() const { return false; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplChangeAnimSet : public DBLinker<PFApplBuff, NDb::ChangeAnimSetApplicator>
{
  WORLD_OBJECT_METHODS(0x2C67DB42, PFApplChangeAnimSet);
  int setId;
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplChangeAnimSet(PFApplCreatePars const &cp) : Base(cp), setId(-1) {}
  PFApplChangeAnimSet() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual void Stop();
  virtual bool IsStackableWithTheSameType() const { return false; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplChangeAnimation : public DBLinker<PFApplBuff, NDb::ChangeAnimationApplicator> 
{
  WORLD_OBJECT_METHODS(0x2C67DB43, PFApplChangeAnimation);
  int animId;
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplChangeAnimation(PFApplCreatePars const &cp) : Base(cp), animId(-1) {}
  PFApplChangeAnimation() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual void Enable();
  virtual void Disable();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplEye : public DBLinker<PFApplBuff, NDb::EyeApplicator> 
{
  WORLD_OBJECT_METHODS(0xF73BB41, PFApplEye);
  ZDATA_(DBLinker)
  int visUnitID0;
  int visUnitID1;
  Target eyeTarget;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&visUnitID0); f.Add(3,&visUnitID1); f.Add(4,&eyeTarget); return 0; }

  PFApplEye(PFApplCreatePars const &cp) : Base(cp), visUnitID0(-1), visUnitID1(-1), eyeTarget() {}
  PFApplEye() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

	virtual void Reset();

protected:
  virtual bool Start();
  virtual void Enable();
  virtual void Disable();
  virtual bool Step(float dtInSeconds);
  void UpdateEyePosition();
  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_POSITION | Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplLockTiles : public DBLinker<PFApplBuff, NDb::LockTilesApplicator>
{
  WORLD_OBJECT_METHODS(0xA0757341, PFApplLockTiles);
  ZDATA_(DBLinker)
	Placement place;
	CTRect<float> coll;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&place); f.Add(3,&coll); return 0; }

  PFApplLockTiles(PFApplCreatePars const &cp) : Base(cp), place(NULLPLACEMENT), coll() {}
  PFApplLockTiles() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual void Stop();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplMount : public DBLinker<PFApplBuff, NDb::MountApplicator>, public PFBaseUnitEventListener
{
  WORLD_OBJECT_METHODS(0xE7777B81, PFApplMount);
  
  ZDATA_(DBLinker)
  ZNOPARENT(PFBaseUnitEventListener)
	CPtr<PFBaseHero> pHero;
	CPtr<PFBaseMovingUnit> pMount;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pHero); f.Add(3,&pMount); return 0; }

  PFApplMount(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplMount() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual void Stop();
  virtual bool Step(float dtInSeconds);
  virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplScaleControl : public DBLinker<PFApplBuff, NDb::ScaleControlApplicator>
{
  WORLD_OBJECT_METHODS(0x9A9CA342, PFApplScaleControl);

  ZDATA_(DBLinker)
  float curScale;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&curScale); return 0; }

  PFApplScaleControl(PFApplCreatePars const &cp) : Base(cp), curScale(1.0) {}
  PFApplScaleControl() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  virtual void Reset();

protected:
  virtual void Enable();
  virtual void Disable();
  virtual void DumpInfo(NLogg::CChannelLogger &logger) const;
  virtual bool Step(float dtInSeconds);
private:
  void ApplyScale( float scale );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplPickupChanneling : public DBLinker<PFApplChannelling, NDb::PickupChannelingApplicator>
{
  WORLD_OBJECT_METHODS(0xE7A4F3C1, PFApplPickupChanneling)
  ZDATA_(DBLinker)
  CPtr<PFPickupableObjectBase> pPickupable;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pPickupable); return 0; }
  PFApplPickupChanneling(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplPickupChanneling() {}
protected:
  virtual bool Start();
  virtual void Fire();
  virtual void Stop();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplInvalidAbilityTarget : public DBLinker<PFApplBuff, NDb::InvalidAbilityTargetApplicator>
{
  WORLD_OBJECT_METHODS(0x15C7A801, PFApplInvalidAbilityTarget)
public:
  PFApplInvalidAbilityTarget();
  PFApplInvalidAbilityTarget(PFApplCreatePars const &cp);
protected:
  virtual void Enable();
  virtual void Disable();
private:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplDayNightTransition : public DBLinker<PFBaseApplicator, NDb::DayNightTransitionApplicator>
{
  WORLD_OBJECT_METHODS(0x15CBF340, PFApplDayNightTransition)
public:
  PFApplDayNightTransition();
  PFApplDayNightTransition(PFApplCreatePars const &cp);
protected:
  virtual bool Start();
};

class PFApplSetTimescale : public DBLinker<PFBaseApplicator, NDb::SetTimescaleApplicator>
{
	WORLD_OBJECT_METHODS(0x15CBF345, PFApplSetTimescale)
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
public:
	PFApplSetTimescale();
	PFApplSetTimescale(PFApplCreatePars const &cp);
protected:
	virtual bool Start();
};

}
