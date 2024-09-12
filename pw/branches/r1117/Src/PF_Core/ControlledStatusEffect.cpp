#pragma once

#include "stdafx.h"

#include "../PF_Core/EffectsPool.h"
#include "ControlledStatusEffect.h"

using namespace NScene;

namespace PF_Core
{

ControlledStatusEffect::ControlledStatusEffect(const NDb::EffectBase &dbEffect)
  : EffectDBLinker<NDb::ControlledStatusEffect, BasicEffectAttached>(dbEffect)
  , rootOriginalOffset(NULLPLACEMENT)
{
  // store original offset (will be manually moving the component)
  if (root)
  {
    rootOriginalOffset = root->GetPlacement();
  }
}

void ControlledStatusEffect::Apply(CPtr<PF_Core::ClientObjectBase> const &pUnit)
{
  BasicEffectAttached::Apply(pUnit);
  pTargetUnit = pUnit;
}

void ControlledStatusEffect::Update(float timeDelta)
{
  BasicEffectAttached::Update(timeDelta);

  // update offset
  if (GetRootComponent() &&
      timeToOriginalOffset > 0.f)
  {
    if (timeToOriginalOffset < 1e-5f ||
        timeToOriginalOffset - timeDelta < 0.f)
    {
      // we should be already there
      // just set final correct placement
      timeToOriginalOffset = 0.f;
      GetRootComponent()->SetPlacement(rootOriginalOffset);
    }
    else
    {
      Placement pl;
      pl.Interpolate(GetRootComponent()->GetOriginalPlacement(), rootOriginalOffset, timeDelta / timeToOriginalOffset);
      GetRootComponent()->SetPlacement(pl);
      timeToOriginalOffset -= timeDelta;
    }
  }
}

void ControlledStatusEffect::OnEvent(NDb::EEffectEvent e, float timeDelta)
{
  // on DEATH event we replace attached effect with standalone version (scene components inherited)
  if (e == NDb::EFFECTEVENT_DEATH &&
      GetDBEffect().onDeathEffect)
  {
    // remember current root component position
    Placement rootWC = GetRootComponent()->GetWorldPlacement();
    Placement rootOrigOffset = GetRootComponent()->GetOriginalPlacement();

    CObj<PF_Core::BasicEffectStandalone> pEffect = EffectsPool::Get()->Retrieve<BasicEffectStandalone>( GetDBEffect().onDeathEffect );
    if (pEffect)
    {
      SwapHierarchy(*pEffect.GetPtr());
    }
    
    if (IsValid(pTargetUnit))
    {
      pEffect->Apply(pTargetUnit);
    }

    // set standalone effect's position to component's position (leaving out just it's original offset)
    {
      Matrix43 orig;
      rootOrigOffset.GetMatrix(&orig);
      orig = orig.GetInversed();
      
      Matrix43 lm;
      rootWC.GetMatrix(&lm);
      lm = lm * orig;

      Placement basicPlace;
      basicPlace.FromMatrix(lm);
      pEffect->SetPosition(basicPlace);
    }

    // clear locator position
    pEffect->GetRootComponent()->SetLocatorPos(VNULL3, QNULL, CVec3(1.f, 1.f, 1.f));

    // test that component's position hasn't changed after swapping
    Placement newRootWC = pEffect->GetSceneObject()->GetPosition() + pEffect->GetRootComponent()->GetPlacement();
    NI_ASSERT(fabs(newRootWC.pos - rootWC.pos) < 1e-3f, "Conversion to standalone effect failed to preserve position");

    // Actually, there is little chance any dying mechanics would work correctly with swapped-in hierarchy.
    // So this effect should disappear immediately, bypassing common dying procedure. Unfortunately such
    // behaviour is unexpected by applicator and will cause crash. For now we depend on applicator to kill
    // the effect. And we will disable all components so that nothing stops it from dying immediately.
//    DieImmediate();
    {
      struct Trav : public ISceneComponentProcessor
      {
        virtual void operator()(SceneComponent *pSC) 
        { 
          pSC->DisableStrong(true);
        }
      } f;

      ForAllRootSceneComponents(f);
    }
    return;
  }

  NScene::AnimatedSceneComponent *pAnimRoot = GetAnimRoot();
  if (pAnimRoot)
  {
    if (timeDelta > 0.f)
    {
      if (!GetDBEffect().eventActions[e].marker.empty())
      {
        pAnimRoot->GetMainAnimGraph()->ReachMarkerByTime(GetDBEffect().eventActions[e].marker, static_cast<int>(timeDelta * 1e+3));
        return;
      }
      
      NI_ALWAYS_ASSERT("Animation marker should be specified");
    }

    if (!GetDBEffect().eventActions[e].animation.empty())
    {
      pAnimRoot->StartAnimation(GetDBEffect().eventActions[e].animation);
    }
  }
}

void ControlledStatusEffect::SynchronizeWithPrototypeEffect(PF_Core::BasicEffectStandalone *pProtoEffect)
{
  NI_ASSERT(pProtoEffect, "Invalid effect pointer");

  // calculate world matrices for attached effect
  if (pSceneObject)
  {
    pSceneObject->UpdateForced();
  }
  
  // remember root component world placement
  Placement rootWC = pProtoEffect->GetRootComponent()->GetWorldPlacement();

  // construct new root offset
  Placement newOffs = NULLPLACEMENT;
  {
    Matrix43 awc;
    GetRootComponent()->GetWorldPlacement().GetMatrix(&awc);
    awc = awc.GetInversed();

    Matrix43 swc;
    rootWC.GetMatrix(&swc);

    Matrix43 offs;
    GetRootComponent()->GetOriginalPlacement().GetMatrix(&offs);
    offs = offs * awc * swc;
    
    newOffs.FromMatrix(offs);
  }
  
  SwapHierarchy(*pProtoEffect);

  timeToOriginalOffset = 1.f;

  // adjust attached effect root offset to match standalone effect's placement
  GetRootComponent()->SetPlacement(newOffs);

  // calculate world matrices for attached effect
  if (pSceneObject)
  {
    pSceneObject->UpdateForced();
  }
}

} //namespace PF_Core

BASIC_REGISTER_CLASS( PF_Core::ControlledStatusEffect);
