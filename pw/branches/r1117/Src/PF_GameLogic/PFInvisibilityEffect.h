#pragma once

#include "../PF_Core/ScaleColorEffect.h"

namespace PF_Core
{
  class ColorModificationChannel;
}

namespace NGameX
{

class PFClientLogicObject;

class InvisibilityEffect : public PF_Core::EffectDBLinker<NDb::InvisibilityEffect, PF_Core::ScaleColorEffect>
{
  OBJECT_METHODS(0xB7323C1, InvisibilityEffect);
public:
  InvisibilityEffect(const NDb::EffectBase &dbEffect) 
    : PF_Core::EffectDBLinker<NDb::InvisibilityEffect, PF_Core::ScaleColorEffect>(dbEffect) 
  {}
  InvisibilityEffect() {};

  virtual void Apply(CPtr<PF_Core::ClientObjectBase> const &pObject);
protected:
  virtual void Apply(float t, bool);

  CPtr<NGameX::PFClientLogicObject> pClientLogicObject;
};

}