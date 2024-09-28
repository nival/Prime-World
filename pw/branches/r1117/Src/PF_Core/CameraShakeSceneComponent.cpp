#include "stdafx.h"
#include "../Scene/CameraControllersContainer.h"
#include "CameraShakeSceneComponent.h"

namespace PF_Core
{

CameraShakeSceneComponent::CameraShakeSceneComponent(const NDb::CameraShakeSceneComponent* pObject,
                                                     const NDb::AttachedSceneComponent* pObj,
                                                     const Placement& pos)
  : SceneComponent(pObject, pObj, pos)
  , pDBObj(pObject)
  , pScene(NULL)
  , lastUpdateFrame(0)
  , animLength(0.f)
{
  if (pDBObj->displacement)
  {
    NScene::AnimatedPlacement dp;
    dp.Init(pDBObj->displacement->placement, 0.f);
    animLength = dp.EvaluateAnimationLength();
  }
}

float CameraShakeSceneComponent::GetPureAnimLength()
{
  return Max(SceneComponent::GetPureAnimLength(), animLength);
}

void CameraShakeSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float /*timeDiff*/ )
{
  ++lastUpdateFrame;
  pScene = dynamic_cast<NScene::Scene*>(pars.pScene);
  if (IsValid(pCameraShaker) && !pCameraShaker->IsActive())
  {
    StopShake();
  }
}

void CameraShakeSceneComponent::RenderToQueue(class Render::BatchQueue& /*queue*/,
                                              const struct Render::SceneConstants& /*sceneConstants*/)
{
  if (pScene && !IsValid(pCameraShaker))
  {
    if (pDBObj->displacement)
    {
      pCameraShaker = new CameraShakeController(pDBObj->displacement->placement, this, pDBObj->range);
      pScene->GetCameraControllers()->AddCameraController(pCameraShaker);
    }
    else
    {
      DisableStrong(true);
    }
  }
}

void CameraShakeSceneComponent::StopShake()
{
  if (IsValid(pCameraShaker))
  {
    pCameraShaker = NULL;
    EnableWeak(false);
  }
}

}
