#pragma once

#include "../PF_Core/BasicEffect.h"
#include "../PF_Core/EffectsPool.h"
#include "DBPFEffect.h"

namespace NScene { _interface IScene; }

namespace NGameX
{

struct IAnimatedClientObject;
class PFClientBaseUnit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFPlayAnimEffect : public PF_Core::EffectDBLinker<NDb::PlayAnimationEffect>
{
public:
	PFPlayAnimEffect(const NDb::EffectBase &dbEffect) : EffectBase(dbEffect), pOwner(0), pAnimated(0) {}
	void Init() { EffectBase::Init(); }

	virtual void Apply(CPtr<PF_Core::ClientObjectBase> const &pUnit);

protected:
	virtual void Die();
  virtual void DieImmediate();

private:
  CPtr<PFClientBaseUnit>       pOwner;
	IAnimatedClientObject        *pAnimated;
	unsigned int                 returnStateId;
};

}
