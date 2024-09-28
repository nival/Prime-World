#pragma once
#include "../Scene/SceneComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneObject.h"
#include "../Scene/SceneObjectCreation.h"
#include "../Scene/ParticleSceneComponent.h"
#include "BasicEffect.h"
#include "DBEffect.h"

namespace NDb
{
	struct BasicEffectStandalone;
}

namespace PF_Core
{

class ParticleSceneComponentWithEffect : public NScene::ParticleSceneComponent
{
public:
	ParticleSceneComponentWithEffect( const NDb::ParticleSceneComponentWithEffect* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );

  virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );

private:

  NDb::Ptr<NDb::ParticleSceneComponentWithEffect> pDBObj;
  vector<CObj<BasicEffectStandalone>>  effectInstances;
};

}

