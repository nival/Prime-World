#pragma once

#include "MinigameClientObject.h"

namespace UI
{
class ImageLabel;
class ProgressBar;
};

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Clinic;
class ClinicPlace;

namespace EPlaceDirtyState
{
  enum Enum
  {
    Clear,
    Soil50,
    Soil100,
  };
}

class ClinicPlaceClientObject : public MinigameClientObject
{
	OBJECT_BASIC_METHODS( ClinicPlaceClientObject )

public:
	ClinicPlaceClientObject();
	virtual ~ClinicPlaceClientObject();
	
  void SetClinic( Clinic * _clinic ) { clinic = _clinic; }
  void InitClinicPlace( ClinicPlace * _place, const NDb::DBSceneObject* _DBSceneObjectDirty50, const NDb::DBSceneObject* _DBSceneObjectDirty100 );

  virtual void Update( float deltaTime, bool gameOnPause );

  virtual void SetVisible( bool _visible );
  virtual bool IsVisible();

  virtual bool NeedHighlight() const;
  virtual const Render::HDRColor& GetHighlightColor() const;

  virtual MinigameClientObject * RedirectMouseOver();
  virtual void OnMouseEnter();
  virtual void OnMouseLeave();

private:
  //IOvertipTarget:
  virtual bool IsOvertipVisible() const { return visible; }
  virtual void SetupOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId);
  virtual void UpdateOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId);

  NScene::SceneObjectRef sceneObjectDirty50;
  NScene::SceneObjectRef sceneObjectDirty100;

	CPtr<NScene::CollisionHull> collisionHullDirty50;
  CPtr<NScene::CollisionHull> collisionHullDirty100;

  bool visible;
  EPlaceDirtyState::Enum dirtyState;

  CPtr<Clinic>  clinic;
  CPtr<ClinicPlace>  clinicPlace;

  Weak<UI::ImageLabel>  wndTick;
  Weak<UI::ProgressBar>  wndCooldown;
};

} // namespace PF_Minigames

