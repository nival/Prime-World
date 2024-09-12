#pragma once
#include "SceneComponent.h"
#include "Scene.h"

namespace NScene
{

class TestSceneComponent : public SceneComponent
{
public:
	TestSceneComponent() {}
	TestSceneComponent( const Placement& pos );
  ~TestSceneComponent() {}

  virtual void UpdateComponent( UpdatePars& pars, const Placement& parentPos, float timeDiff );
};

}

