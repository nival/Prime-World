#pragma once

#include "PFApplicator.h"
#include "../PF_Core/BasicEffect.h"

namespace PF_Core
{
	class BasicEffect;
}

namespace NWorld
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplBuff: public PFBaseApplicator
{
  WORLD_OBJECT_METHODS(0xE5CC381, PFApplBuff);

public:
  PFApplBuff(PFApplCreatePars const &cp);
  PFApplBuff(): isInterrupted(false) {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  virtual float GetLifetime() const { return lifeTime; }
  virtual float GetDuration() const { return duration; }

  // from IMiscFormulaPars
  virtual float GetVariable(const char *varName) const;

  void SetLifetime( float newLifetime ) { lifeTime = newLifetime; }
  void SetDuration( float newDuration ) { duration = newDuration; }

  void RestartEffects();

  virtual float GetModifiedDuration(float original) const { return original; }

protected:
	virtual bool Init();
  virtual bool Start();
  virtual void Stop();
  virtual bool Step(float dtInSeconds);
  virtual bool CanBeAppliedOnDead();

	virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }

	virtual void Enable();
  virtual void Disable();
  virtual void AfterStartEffects() {}

  virtual void DumpInfo(NLogg::CChannelLogger &logger) const;

  virtual bool GetRemainingLifeTime(float &time) const;

  virtual bool NeedToStopOnDeath() const;
  virtual bool NeedToStopOnSenderDeath() const;
  virtual bool NeedToDisableOnDeath() const;

  virtual void PrepareEffects( bool manualDeathTypeOnly );

  vector<CObj<PF_Core::BasicEffect>> effects;

  void SetInterrupted(bool interrupt){isInterrupted = interrupt;}
  bool GetInterrupted(){return isInterrupted;}

private:
  void KillEffects();
  virtual PFLogicObject* GetEffectOrigin();
  virtual PFLogicObject* GetEffectTarget();

private:
  ZDATA_(PFBaseApplicator)
  float lifeTime;
  float duration;
  Placement receiverPlacementOnStart;
  bool isInterrupted;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseApplicator*)this); f.Add(2,&lifeTime); f.Add(3,&duration); f.Add(4,&receiverPlacementOnStart); f.Add(5,&isInterrupted); return 0; }
};


class PFApplAddApplicatorDuration: public DBLinker<PFBaseApplicator, NDb::AddApplicatorDuration>
{
  WORLD_OBJECT_METHODS(0x2B82CC81, PFApplAddApplicatorDuration);

public:
  PFApplAddApplicatorDuration( const PFApplCreatePars& cp ) : Base( cp ) { }

protected:
  PFApplAddApplicatorDuration() { }
  virtual bool Start();
};

}
