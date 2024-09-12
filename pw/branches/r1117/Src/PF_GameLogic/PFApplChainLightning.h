#pragma once

#include "PFApplicator.h"

namespace NWorld
{

class PFWorld;
class PFBaseUnit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplChainLightning: public DBLinker<PFBaseApplicator, NDb::ChainLightningApplicator>
{
  WORLD_OBJECT_METHODS(0xE5CC396, PFApplChainLightning);

  CPtr<PFBaseUnit> pBestTarget; // this variable is used when in operator()
protected:
  ZDATA_(DBLinker)
  int numJumpsLeft;
  float onJumpSpellScale;
  float betweenJumpsTimeInterval;
  float range;
	float scale;
  CVec3 startDispatchPos;
  float timeTillJump;
  vector<CPtr<PFBaseUnit> > affectedUnits;
  CPtr<PFBaseUnit> pPrevTargetUnit;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&numJumpsLeft); f.Add(3,&onJumpSpellScale); f.Add(4,&betweenJumpsTimeInterval); f.Add(5,&range); f.Add(6,&scale); f.Add(7,&startDispatchPos); f.Add(8,&timeTillJump); f.Add(9,&affectedUnits); f.Add(10,&pPrevTargetUnit); return 0; }

  PFApplChainLightning(PFApplCreatePars const &cp) 
    : Base(cp),
      pBestTarget(NULL),
      numJumpsLeft(RetrieveParam(GetDB().numJumps, 1)),
      onJumpSpellScale(GetDB().onJumpSpellScale),
      betweenJumpsTimeInterval(GetDB().betweenJumpsTimeInterval),
      range( RetrieveParam(GetDB().range, 0.0f) ),
			scale(1.0f),
      startDispatchPos(VNULL3),
      timeTillJump(0.0f)
  {
  }
  PFApplChainLightning(): 
    pBestTarget(NULL),
    numJumpsLeft(0),
    onJumpSpellScale(0.0f),
    betweenJumpsTimeInterval(1.0f),
    range(10.0f),
    scale(1.0f),
    startDispatchPos(VNULL3),
    timeTillJump(0.0f) {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
  void operator()( PFBaseUnit &unit );

  virtual bool NeedToStopOnDeath() const { return false; }
  virtual bool NeedToDisableOnDeath() const { return false; }

  virtual void OnDispatchMissed( const PFDispatch* _pDispatch );
protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds);

	// From IMiscFormulaPars
  virtual float GetScale() const { return scale * Base::GetScale(); }

private:
  void ApplyEffect( const NDb::Ptr<NDb::EffectBase>& pDBEffect, PFBaseUnit* pTarget );
  void AttackUnit(CPtr<PFBaseUnit> const &pTargetUnit);
  void DoIt();
};

}