#pragma once

#include "../PF_Core/BasicEffect.h"
#include "../PF_Core/EffectsPool.h"
#include "DBPFEffect.h"

namespace NScene { _interface IScene; }

namespace NGameX
{

class PFClientBaseUnit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFAuraEffect : public PF_Core::EffectDBLinker<NDb::AuraEffect>
{
public:
	PFAuraEffect(const NDb::EffectBase &dbEffect) : EffectBase(dbEffect) {}

	virtual void Apply(CPtr<PF_Core::ClientObjectBase> const &pObject);

protected:
	virtual void Die();
  virtual void DieImmediate();

private:
	CPtr<PFClientBaseUnit> pUnit;
};

}
