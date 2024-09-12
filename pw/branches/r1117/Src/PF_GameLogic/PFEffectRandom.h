#pragma once

#include "../PF_Core/BasicEffect.h"
#include "../PF_Core/EffectsPool.h"
#include "DBPFEffect.h"

namespace NScene { _interface IScene; }

namespace NGameX
{
  class PFClientBaseUnit;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEffectRandom : public PF_Core::EffectDBLinker<NDb::RandomEffect>
  {
  public:
    PFEffectRandom(const NDb::EffectBase &dbEffect) : EffectBase(dbEffect) {}

    virtual void Apply(CPtr<PF_Core::ClientObjectBase> const &pObject);

  protected:
    virtual void Die() 
    { 
      if (IsValid(pEffect))
      {
        pEffect->Die(); 
        pEffect = 0;
      }

      BasicEffect::Die();
    }

  private:
    CObj<BasicEffect> pEffect;
  };

}
