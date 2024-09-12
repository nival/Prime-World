#pragma once

#include "../PF_Core/ControlledStatusEffect.h"
#include "DBPFEffect.h"

#include "PFCreature.h"
#include "PFClientCreature.h"

namespace NGameX
{

class PriestessSignEffect : public PF_Core::EffectDBLinker<NDb::PriestessSignEffect, PF_Core::BasicEffectStandalone>
{
  OBJECT_METHODS( 0xA06CEC01, PriestessSignEffect )
public:
  enum State
  {
    STATE_IDLE,
    STATE_WAITDEATHEFFECT,
    STATE_FLYIN,
    STATE_FLYOUT
  };

  PriestessSignEffect(const NDb::EffectBase &dbEffect);
  PriestessSignEffect() {}

  virtual void Init();
  virtual void Apply(CPtr<PF_Core::ClientObjectBase> const &pUnit);
  virtual void Update(float timeDelta);
  virtual void DieImmediate();
  virtual bool Ready2Die() { return false; }

protected:
  bool HasTargetCreatureStartedDeathEffect();
  CVec3 GetRelativeSoulSphereDestinationPos();
  CVec3 GetRelativeSoulSpherePos();
  CVec3 PlaceSoulSphereIntoPos(CVec3 const &pos);
  void InitFlyIn();


  CPtr<NGameX::PFClientCreature> pTargetCreature;
  State  state;
  CObj<PF_Core::BasicEffectStandalone> pSoulEffect;
  NScene::AnimatedPlacement  flyInPos;
  Placement scPosBackup;
  Placement flyInAdj;
  float  countdown;
};

}
