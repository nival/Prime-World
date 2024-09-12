#pragma once

namespace NGameX
{

class VisibilityHelper
{
  bool bVisible;

public:
  VisibilityHelper() : bVisible(true) {}

  void SetVisibility( NScene::SceneObject* so, bool bVisible_);
  template <typename T>
  void UpdateVisibility( NScene::SceneObject* so, T* obj )
  {
    if (!obj->WorldObject())
      return;

    NGameX::AdventureScreen * screen = NGameX::AdventureScreen::Instance();

    if ( obj->WorldObject()->GetSender() && ( obj->WorldObject()->GetSender()->GetFaction() == screen->GetPlayerFaction())) 
    {
      SetVisibility(so, true);
    }
    else if ( obj->WorldObject()->GetTarget().IsUnit() && (obj->WorldObject()->GetTarget().GetUnit()->GetFaction() == screen->GetPlayerFaction())) 
    {
      SetVisibility(so, true);
    }
    else
    {
      if (const VisibilityMapClient * pVisMap = screen->GetClientVisibilityMap())
      {
        SetVisibility(so, pVisMap->IsPointVisible(obj->WorldObject()->GetCurrentPosition().AsVec2D()));
      }
      else
      {
        SetVisibility(so, false);
      }
    }
  }

protected:
  void InitVisibility( NScene::SceneObject* so );
};
}