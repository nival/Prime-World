#pragma once

#include "../PF_Core/BasicEffect.h"
#include "../PF_Core/EffectsPool.h"
#include "DBPFEffect.h"

namespace NGameX
{
  class PFClientLogicObject;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFMinimapEffect : public PF_Core::EffectDBLinker<NDb::MinimapEffect>
  {
    OBJECT_METHODS( 0xE78B9480, PFMinimapEffect )
  public:
    PFMinimapEffect( const NDb::EffectBase& dbEffect) : EffectBase( dbEffect ), index(-1) { }

    virtual void Apply(CPtr<PF_Core::ClientObjectBase> const &pObject);
    virtual void Update(float timeDelta);
  protected:
    virtual void Die();

  private:
    PFMinimapEffect() {};

    CPtr<PFClientLogicObject> pObject;
    int index;
  };

}
