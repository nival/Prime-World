#pragma once
#include "../Scene/SceneComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneObject.h"
#include "../Scene/SceneObjectCreation.h"
#include "DBEffect.h"
#include "BasicEffect.h"

namespace NDb
{
	struct BasicEffectStandalone;
}

namespace PF_Core
{

class EffectGenSceneComponent : public NScene::SceneComponent
{
public:
	EffectGenSceneComponent( const NDb::EffectGenSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );

  virtual void OnAfterAdded(NScene::SceneObject *pObject);

  virtual void Attach( SceneComponent* toadd );

  virtual void Deinit();
  virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );
	virtual void RenderToQueue( class Render::BatchQueue& /*queue*/, const struct Render::SceneConstants& /*sceneConstants*/ );

private:
  void SpawnEffect();
  void DebugRender();

  NDb::Ptr<NDb::EffectGenSceneComponent> pDBObj;
  ScopedPtr<EffectSelector> pEffect;
  NScene::IScene *pScene;
  int   nextEffectIdx;
  float timeToNextSpawn;
};

}

