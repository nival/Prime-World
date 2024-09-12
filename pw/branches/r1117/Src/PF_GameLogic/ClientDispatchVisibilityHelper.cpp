#include "stdafx.h"
#include "ClientDispatchVisibilityHelper.h"

namespace NGameX
{

  void ClientDispatchVisibilityHelper::SetVisibility(NScene::SceneObject* const sceneObject, const bool visible)
  {
    if (_visible == visible)
      return;

    _visible = visible;

    if (!sceneObject)
      return;

    // TODO: ?
    if (!visible || !sceneObject->getVoxelGrid())
      sceneObject->EnableRender(_visible)
  }

  void ClientDispatchVisibilityHelper::InitVisibility(NScene::SceneObject* const sceneObject)
  {
    if (!sceneObject)
      return;

    if (!_visible)
      sceneObject->EnableRender(false);
  }

}