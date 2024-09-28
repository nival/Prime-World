#pragma once

namespace NDb
{
  struct AdvMapObject;
  struct Node;
  enum   EOrientation;
}

namespace NScene
{
  class SceneObject;
  _interface IScene;
}

namespace NGameX
{
  AutoPtr<NScene::SceneObject> CreateSceneObject(NDb::AdvMapObject const* pObject, int id, 
    NScene::IScene* pAtScene);

  float NormalizeAngle(float angle);
}