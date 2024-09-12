#pragma once

#include "../PF_Core/BasicEffect.h"
#include "../PF_Core/EffectsPool.h"
#include "DBPFEffect.h"

namespace NGameX
{

class PFClientCreature;
class SingleSceneObjectHolder;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFUnitSceneObjectModify : public PF_Core::EffectDBLinker<NDb::UnitSceneObjectModify>
{
public:
	PFUnitSceneObjectModify(const NDb::EffectBase &dbEffect) : EffectBase(dbEffect) {}

	virtual void Apply(CPtr<PF_Core::ClientObjectBase> const &pObject);

protected:
  virtual void Update(float timeDelta);

  virtual void Die();

private:
	AutoPtr<SingleSceneObjectHolder> pSceneObjectHolder;
	CPtr<PFClientCreature>           pCreature;
};

}
