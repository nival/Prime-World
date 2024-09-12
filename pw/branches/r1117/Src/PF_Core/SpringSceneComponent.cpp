#include "stdafx.h"

#include "SpringSceneComponent.h"

namespace PF_Core
{

////////////////////////////////////////////////////////////////////////////////////////////////
// TargetedValue<CQuat, CQuat>
// 

template<>
float TargetedValue<CQuat>::Distance(CQuat v1, CQuat v2)
{
  float t = v1.Dot(v2);
  return fabs(acos(Clamp(t, -1.f, 1.f)));
}

template<>
bool TargetedValue<CQuat>::Update(CQuat target, float dt)
{
  float minCoef = 0.f;

  float d = Distance(val, target);
  if (d > 1e-5f)
  {
    minCoef = 1.f - dynamics.maxValue / d;
  }

  float coef = dynamics.speed * dt;
  coef = Clamp(coef, 0.f, 1.f);
  val.Slerp(Max(coef, minCoef), val, target);
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// SpringSceneComponent
////////////////////////////////////////////////////////////////////////////////////////////////

SpringSceneComponent::SpringSceneComponent( const NDb::SpringSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos )
  : SceneComponent(pObject, pObj, pos)
  , bTPlaceInited(false)
{
  NDb::SpringParamDynamics p, r, s;

  p = pObject->posDynamics;
  r = pObject->rotDynamics;
  s = pObject->scaleDynamics;

  if (p.maxValue < 0.f)
    p.maxValue = 100000.f; // max distance in meters

  if (r.maxValue < 0.f)
    r.maxValue = 2.f * FP_2PI; // max angle in radians
  else
    r.maxValue *= FP_PI / 180.f; // convert degrees to radians

  if (s.maxValue < 0.f)
    s.maxValue = 10000.f; // max scale difference

  Reset(tplace, new TargetedPlacement(p, r, s));
}

void SpringSceneComponent::Reinit()
{
  SceneComponent::Reinit();

  bTPlaceInited = false;
}

void SpringSceneComponent::Update( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  // remember current world place
  Placement curWP = worldPlacement;

  // perform standard update (world placement calculated the usual way)
  float timeDelta;
  if (!UpdateBasics(pars, parentPos, timeDiff, timeDelta))
    return;
  UpdateComponent(pars, parentPos, timeDelta);

  // calculate "lagging" world placement
  if (!bTPlaceInited)
  {
    tplace->Init(worldPlacement);
    bTPlaceInited = true;
  }
  else
  {
    tplace->Update(curWP, worldPlacement, timeDelta);
    worldPlacement = curWP;
  }

  PassUpdate2Children(pars, worldPlacement, timeDelta);
}

bool SpringSceneComponent::IsStayInWorld()
{
  return true;
}
}
