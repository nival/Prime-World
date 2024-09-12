#pragma once
#include "../Scene/SceneComponent.h"
#include "../Scene/Scene.hpp"
#include "DBEffect.h"
#include "CameraShakeController.h"

namespace PF_Core
{

class CameraShakeSceneComponent : public NScene::SceneComponent
{
public:
	CameraShakeSceneComponent( const NDb::CameraShakeSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );
  ~CameraShakeSceneComponent() {}

  float GetPureAnimLength();

  virtual void UpdateComponent( UpdatePars &pars, const Placement& /*parentPos*/, float /*timeDiff*/ );
	virtual void RenderToQueue( class Render::BatchQueue& /*queue*/, const struct Render::SceneConstants& /*sceneConstants*/ );

  int  GetLastUpdateFrame() const { return lastUpdateFrame; }
  void StopShake();

private:
  NDb::Ptr<NDb::CameraShakeSceneComponent> pDBObj;
  float animLength;
  NScene::Scene *pScene;
  CObj<CameraShakeController>  pCameraShaker;
  int lastUpdateFrame;
};

}

