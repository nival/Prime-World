#pragma once

namespace NGameX
{

class ClientDispatchVisibilityHelper
{
public:
  ClientDispatchVisibilityHelper()
    : _visible(true)
  {
  }

  void SetVisibility(NScene::SceneObject* const sceneObject, const bool visible);

  template <typename T>
  void UpdateVisibility(NScene::SceneObject* const sceneObject, T* const clientObject)
  {
    typename T::WorldObjectType* const worldObject = clientObject->WorldObject();

    if (!worldObject)
      return;

    NGameX::AdventureScreen * screen = NGameX::AdventureScreen::Instance();

    const NDb::EFaction playerFaction = screen->GetPlayerFaction();

    if (IsValid(worldObject->GetSender()))
    {
      if (worldObject->GetSender()->GetFaction() == playerFaction)
      {
        SetVisibility(sceneObject, true);
        return;
      }
    }

    if (worldObject->GetTarget().IsUnit())
    {

    }

    if ( worldObject->GetSender() && ( worldObject->GetSender()->GetFaction() == screen->GetPlayerFaction())) 
    {
      SetVisibility(sceneObject, true);
    }
    else if ( worldObject->GetTarget().IsUnit() && (worldObject->GetTarget().GetUnit()->GetFaction() == screen->GetPlayerFaction())) 
    {
      SetVisibility(sceneObject, true);
    }
    else
    {
      if (const VisibilityMapClient * pVisMap = screen->GetClientVisibilityMap())
      {
        SetVisibility(sceneObject, pVisMap->IsPointVisible(worldObject->GetCurrentPosition().AsVec2D()));
      }
      else
      {
        SetVisibility(sceneObject, false);
      }
    }
  }
protected:
  void InitVisibility( NScene::SceneObject* const sceneObject );
private:
  bool _visible;
};

}