#pragma once

#include "stdafx.h"
#include "../Scene/SceneObjectCreation.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "GhostEffect.h"

namespace PF_Core
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GhostEffect::Apply(CPtr<ClientObjectBase> const &pUnit)
{
  target = pUnit;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GhostEffect::Update(float timeDelta)
{
  if (IsValid(target) && Get(sceneObj) && target->GetSceneObject())
  {
    sceneObj->SetPosition(target->GetSceneObject()->GetPosition().pos + CVec3(2.f, -2.f, 1.f));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GhostEffect::SetPrototype(NScene::SceneObject const &obj)
{
  // @todo  make semi-transparent copy of scene object

  NScene::AnimatedSceneComponent const *pComp = dynamic_cast<NScene::AnimatedSceneComponent const *>(obj.GetRootComponent());
  sceneObj = NScene::CreateSceneObject(obj.GetScene(), *pComp->GetDBComponent());
  sceneObj->UpdateForced();
  sceneObj->AddToScene(obj.GetScene());
}


}