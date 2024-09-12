#pragma once

#include "BasicEffect.h"

namespace NScene { _interface IScene; }

namespace PF_Core
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GhostEffect : public EffectDBLinker<NDb::GhostEffect>
{
public:
	GhostEffect(const NDb::EffectBase &dbEffect) : EffectBase(dbEffect) {}
	void Init() { EffectBase::Init(); }

	virtual void Apply(CPtr<ClientObjectBase> const &pUnit);
  virtual void Update(float timeDelta);

  void SetPrototype(NScene::SceneObject const &obj);

protected:

  CPtr<ClientObjectBase> target;
  AutoPtr<NScene::SceneObject> sceneObj;
};

}
