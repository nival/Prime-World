#pragma once

#include "../Scene/CameraController.h"
#include "../Scene/Camera.h"
#include "../Scene/CameraInputModifier.h"
#include "../Scene/DBScene.h"

namespace NScene { _interface IScene; }

namespace PF_Core
{

class CameraShakeSceneComponent;

class CameraShakeController : public NScene::ICameraController
{
  void SetCamera( NScene::ICamera *_pCamera )
  {
    pCamera = _pCamera;
    totalTime = 0.f;
  }

  CameraShakeController() {}

public:
  CameraShakeController(NDb::AnimatedPlacement const &displacement, CameraShakeSceneComponent *pSource = NULL, float range = 0.f);

  virtual const bool IsEffect() const { return true; }
  virtual const bool IsActive() const { return bActive; }
  virtual bool ProcessEvent( const Input::Event& _eEvent ) { return false; }

  virtual void Update( 
    NScene::SCameraPosition	*pWantedPos,
    const NScene::SCameraPosition &currentPos,
    const NScene::SCameraPosition &wantedPos,
    NScene::Time timeDiff
    );

  OBJECT_BASIC_METHODS( CameraShakeController );

protected:
  NDb::AnimatedPlacement const *displacement;
  ///< affected camera
  CPtr<NScene::ICamera> pCamera;
  CameraShakeSceneComponent *pSource;
  int   componentLastUpdateFrame;
  float range;
  bool  bActive;
  float totalTime;
};

}
