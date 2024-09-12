#pragma once

#include "BasicEffect.h"

namespace PF_Core
{

class StatusEffect : public EffectDBLinker<NDb::StatusEffect, BasicEffectAttached>
{
  OBJECT_METHODS( 0xA06CCB83, StatusEffect )
public:
  StatusEffect(const NDb::EffectBase &dbEffect) : EffectDBLinker<NDb::StatusEffect, BasicEffectAttached>(dbEffect) {}
  StatusEffect() {}

  virtual void Attach(NScene::SceneObject *pObj);

  void Attach(NScene::SceneObject *pObj, NDb::EStatusEffectSlot slot);
};

}
