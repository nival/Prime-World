#pragma once

#include "ObjectsPool.h"
#include "DBEffect.h"
#include "BasicEffect.h"

namespace PF_Core
{

class EnableSCEffect : public EffectDBLinker<NDb::EnableSCEffect>
{
public:
  EnableSCEffect(const NDb::EffectBase &dbEffect) : EffectBase(dbEffect), pUnit(0) {}

  virtual void Apply(CPtr<ClientObjectBase> const &pUnit_);

protected:
  virtual void Die();
  virtual void DieImmediate();

  CPtr<ClientObjectBase>  pUnit;
};

}
