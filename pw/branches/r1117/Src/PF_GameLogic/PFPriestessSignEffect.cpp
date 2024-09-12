#pragma once

#include "stdafx.h"

#include "../PF_Core/EffectsPool.h"
#include "../PF_GameLogic/PFAIWorld.h"
#include "PFPriestessSignEffect.h"

using namespace NScene;

namespace NGameX
{

PriestessSignEffect::PriestessSignEffect(const NDb::EffectBase &dbEffect)
: EffectDBLinker<NDb::PriestessSignEffect, PF_Core::BasicEffectStandalone>(dbEffect)
, state(STATE_IDLE)
{
}

void PriestessSignEffect::Init()
{
  BasicEffectStandalone::Init();

  // store initial component placement (will restore it on death)
  AnimatedSceneComponent *pAnim = GetAnimRoot();
  if (pAnim)
  {
    scPosBackup = pAnim->GetPlacement();
  }

  NI_DATA_ASSERT(GetRootComponent()->GetParentTransformUsageFlags() & NDb::ATTACHFLAGS_USEPARENTROTATION,
                 "Priestess sign effect should have USEPARENTROTATION, otherwise orientation to path will not work");

  state = STATE_WAITDEATHEFFECT;

  // Бывший тип self, сейчас это эффект, который раждается умирающим и умирает, 
  // когда Ready2Die() вернет true или по DieImmediate()
  bDying = true;
}

void PriestessSignEffect::Apply(CPtr<PF_Core::ClientObjectBase> const &pUnit)
{
  pTargetCreature = dynamic_cast<PFClientCreature*>(pUnit.GetPtr());
  if ( IsValid(pTargetCreature) && pTargetCreature->IsVisible() )
  {
    BasicEffectStandalone::Apply(pUnit);
  }
  else
  {
    state = STATE_IDLE;
  }
}

void PriestessSignEffect::Update(float timeDelta)
{
  SceneComponentsEffect::Update(timeDelta);

  // if no animRoot -- we got nothing reasonable to do
  AnimatedSceneComponent *pAnim = GetAnimRoot();
  if (!pAnim)
  {
    DieImmediate();
    NI_ALWAYS_ASSERT("Can't find animated root component");
    return;
  }

  switch (state)
  {
    case STATE_WAITDEATHEFFECT:
    {
      if (!IsValid(pTargetCreature) ||
          pTargetCreature->GetLifeState() < PFClientCreature::Dying)
      {
        // creature has disappeared or been resurrected
        // no need to play full effect
        DieImmediate();
        break;
      }

      if (HasTargetCreatureStartedDeathEffect())
      {
        pSoulEffect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectStandalone>( GetDBEffect().soulEffect );
        if (pSoulEffect)
        {
          pSoulEffect->Apply(pTargetCreature.GetPtr());
          pSoulEffect->GetSceneObject()->UpdateForced( 0.0f, false, pTargetCreature->IsVisible() );
        }

        InitFlyIn();
        state = STATE_FLYIN;
      }
      break;
    }

    case STATE_FLYIN:
    {
      // update position on fly-in path
      flyInPos.Step(timeDelta);
      Placement const &animPos = flyInPos.GetPlacement();
      
      // calculate actual local offset
      CVec3 pos;
      flyInAdj.Transform(animPos.pos, pos);
      
      pAnim->SetPlacement( Placement(PlaceSoulSphereIntoPos(pos), pAnim->GetPlacement().rot/* flyInAdj.rot * animPos.rot */, pAnim->GetPlacement().scale /* animPos.scale */) );

      // check that we successfully placed soul sphere on path
      // This kind of test definitely should be performed, but bone matrices were not recalculated yet. So it would fail.
      // NI_ASSERT(fabs(GetRelativeSoulSpherePos() - pos) < 1e-3f, "Failed to place soul sphere on path");

      // check for end of state
      countdown -= timeDelta;
      if (countdown < 0.f)
      {
        if (IsValid(pSoulEffect))
        {
          pSoulEffect->DieImmediate();
          pSoulEffect = 0;
        }

        int idx = pAnim->GetMainAnimGraph()->GetNodeIDByNameSlow( GetDBEffect().flyOutAnim.c_str() );
        countdown = pAnim->GetAnimDuration(idx);
        pAnim->StartAnimation(idx);

        state = STATE_FLYOUT;
      }
      break;
    }

    case STATE_FLYOUT:
    {
      countdown -= timeDelta;
      if (countdown < 0.f)
      {
        DieImmediate();
      }
      break;
    }
  }
}

void PriestessSignEffect::DieImmediate()
{
  // restore original component placement
  // This is a kind of hack -- when we are swapping hierarchies with attached priestess sign
  // our placement correction will affect its position which should not happen.
  AnimatedSceneComponent *pAnim = GetAnimRoot();
  if (pAnim)
  {
    pAnim->SetPlacement(scPosBackup);
  }

  pTargetCreature = 0;

  BasicEffectStandalone::DieImmediate();
}

void PriestessSignEffect::InitFlyIn()
{
  if (GetDBEffect().flyInPath)
  {
    flyInPos.Init( GetDBEffect().flyInPath->placement, 0.f );
  }
  countdown = flyInPos.EvaluateAnimationLength();

  CVec3 startPos = flyInPos.GetPlacement().pos;
  CVec3 actualStartPos = GetRelativeSoulSpherePos();
  CVec3 actualEndPos = GetRelativeSoulSphereDestinationPos();
  CVec3 relStartPos = actualStartPos - actualEndPos;

  NI_DATA_VERIFY(fabs(startPos.AsVec2D()) > 0.f && startPos.z > 0.f, "Priestess fly-in path should not start in (x=0, y=0, z=0)", return);

  // build adjustment matrix
  {
    // rotation
    CVec2 sp  = startPos.AsVec2D();
    CVec2 asp = relStartPos.AsVec2D();
    float spLen  = fabs(sp),
      aspLen = fabs(asp);
    sp  /= spLen;

    if (aspLen > 0.f)
    {
      asp /= aspLen;
      float s = Cross(sp, asp);
      float c = sp.Dot(asp);

      SHMatrix m;
      Identity(&m);
      m._11 = c;   m._12 = -s;
      m._21 = s;   m._22 = c;
      flyInAdj.rot.FromEulerMatrix(m);

      CVec3 testSP =  CVec3(sp.x, sp.y, 0.f),
            testASP = CVec3(asp.x, asp.y, 0.f),
            testRot = flyInAdj.rot.Rotate(testSP);
      NI_ASSERT(fabs(testRot - testASP) < 1e-3f, "Incorrect quaternion");
    }
    else
    {
      flyInAdj.rot = QNULL;
    }

    // scale
    float scaleXY = aspLen / spLen;
    flyInAdj.scale = CVec3(scaleXY, scaleXY, relStartPos.z / startPos.z);

    // position
    flyInAdj.pos = actualEndPos;

    CVec3 testPos;
    flyInAdj.Transform(startPos, testPos);
    NI_ASSERT(fabs(testPos - actualStartPos) < 1e-3f, "Incorrect adjustment matrix");
  }

  AnimatedSceneComponent *pAnim = GetAnimRoot();
  if (pAnim)
  {
    GetAnimRoot()->StartAnimation(GetDBEffect().flyInAnim);
  }
}

bool PriestessSignEffect::HasTargetCreatureStartedDeathEffect()
{
  const NWorld::PFCreature *pWO = dynamic_cast<const NWorld::PFCreature*>(pTargetCreature->WorldObject());
  if (!pWO)
  {
    return true;
  }

  NI_DATA_VERIFY(pWO->GetDeathParams(), "Death parameters are not setted", return false;)

  float onUnitDieEffectOffset = pWO->GetDeathParams()->effectOffset;
  if ( pTargetCreature->GetTimeDead() > onUnitDieEffectOffset )
  {
    return true;
  }

  return false;
}

// returns soul sphere destination offset relative to scene object pivot
CVec3 PriestessSignEffect::GetRelativeSoulSphereDestinationPos()
{
  if (!IsValid(pSoulEffect))
  {
    return VNULL3;
  }

  Locator const *pL = pSoulEffect->GetSceneObject()->FindLocator(GetDBEffect().destinationLocator.c_str());
  if (pL)
  {
    CVec3 pos;
    pL->CalculateWorldPosition(pos);
    
    Matrix43 m;
    GetSceneObject()->GetPosition().GetMatrix(&m);
    m = m.GetInversed();
    pos = Transform(pos, m);
    return pos;
  }

  return VNULL3;
}

// returns soul sphere offset in scene object CS
CVec3 PriestessSignEffect::GetRelativeSoulSpherePos()
{
  AnimatedSceneComponent *pAnim = GetAnimRoot();
  NI_VERIFY(pAnim, "Can't find root anim component", return VNULL3);

  Locator const *pL = GetSceneObject()->FindLocator(GetDBEffect().soulEffect->parentType.c_str());
  if (pL)
  {
    CVec3 wpos;
    pL->CalculateWorldPosition(wpos);
    Matrix43 m;
    GetSceneObject()->GetPosition().GetMatrix(&m);
    m = m.GetInversed();
    return Transform(wpos, m);
  }

  return pAnim->GetPlacement().pos;
}

// returns position for anim component that will place soul sphere into specified position
CVec3 PriestessSignEffect::PlaceSoulSphereIntoPos(CVec3 const &pos)
{
  AnimatedSceneComponent *pAnim = GetAnimRoot();
  NI_VERIFY(pAnim, "Can't find root anim component", return VNULL3);

  Locator const *pL = GetSceneObject()->FindLocator(GetDBEffect().soulEffect->parentType.c_str());
  if (pL)
  {
    CVec3 ssPos = GetRelativeSoulSpherePos();
    return pos + (pAnim->GetPlacement().pos - ssPos);
  }

  return pos;
}

} //namespace PF_Core

BASIC_REGISTER_CLASS( NGameX::PriestessSignEffect);
