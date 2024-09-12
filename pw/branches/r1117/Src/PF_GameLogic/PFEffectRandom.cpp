#include "stdafx.h"
#include "PFClientLogicObject.h"
#include "PFEffectRandom.h"

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFEffectRandom::Apply(CPtr<PF_Core::ClientObjectBase> const &pObject)
{
  int const numEffects = GetDBEffect().effects.size();
  if (0 == numEffects)
    return;

  int const idx = NRandom::Random(numEffects);

  NDb::Ptr<NDb::EffectBase> pDBEffect = GetDBEffect().effects[idx];
  if (IsValid(pDBEffect))
  {
    pEffect = PF_Core::EffectsPool::Get()->Retrieve(pDBEffect);
    pEffect->Apply(pObject);
  }
}

}