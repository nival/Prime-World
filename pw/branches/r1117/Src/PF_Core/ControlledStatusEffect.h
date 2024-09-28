#pragma once

#include "../Scene/AnimatedSceneComponent.h"
#include "BasicEffect.h"

namespace PF_Core
{

class ControlledStatusEffect : public EffectDBLinker<NDb::ControlledStatusEffect, BasicEffectAttached>
{
  OBJECT_METHODS( 0xA06CEBC1, ControlledStatusEffect )
public:

  ControlledStatusEffect(const NDb::EffectBase &dbEffect);
  ControlledStatusEffect() {}

  void Apply(CPtr<PF_Core::ClientObjectBase> const &pUnit);
  virtual void Update(float timeDelta);
  virtual void OnEvent(NDb::EEffectEvent e, float timeDelta = 0.f);

	void SynchronizeWithPrototypeEffect(PF_Core::BasicEffectStandalone *pProtoEffect);

protected:

  Placement rootOriginalOffset;
  CPtr<PF_Core::ClientObjectBase> pTargetUnit;

  float timeToOriginalOffset; // time left to reach original offset
};

}
