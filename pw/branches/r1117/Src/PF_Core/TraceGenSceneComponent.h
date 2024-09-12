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

class TraceGenSceneComponent;

class Trace
{
public:
  Trace(const NDb::Trace *pDBObj, const string *locator = NULL);
  void SpawnEffect(TraceGenSceneComponent *pOwner, NScene::IScene *pScene);

private:
  NDb::Ptr<NDb::Trace> pDBObj;
  const string *locator;
  ScopedPtr<EffectSelector> pWaterEffect;
  ScopedArray< ScopedPtr<EffectSelector> > pTerrainEffects;
};

class TraceGenSceneComponent : public NScene::SceneComponent
{
public:
	TraceGenSceneComponent( const NDb::TraceGenSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );
  ~TraceGenSceneComponent();

  virtual void OnAfterAdded(NScene::SceneObject *pObject);
  virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );
	virtual void RenderToQueue( class Render::BatchQueue& /*queue*/, const struct Render::SceneConstants& /*sceneConstants*/ );

  NScene::SceneObject *GetSceneObject() { return pSceneObject; }

  void AllowGenerate()
  {
    if (forbidGenerateCounter == 0)
      return;

    --forbidGenerateCounter;
  }
  void ForbidGenerate()
  {
    ++forbidGenerateCounter;
  }
private:
  void Generate(NScene::IScene *pScene);
  void DebugRender();


  NDb::Ptr<NDb::TraceGenSceneComponent> pDBObj;
  ScopedPtr<Trace>  defaultTrace;
  map<int, Trace*>  traceByAnim;

  NScene::SceneObject *pSceneObject;

  unsigned forbidGenerateCounter;
};

}

