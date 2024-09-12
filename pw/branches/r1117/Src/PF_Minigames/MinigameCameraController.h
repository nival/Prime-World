#pragma once

#include "../Scene/DBScene.h"
#include "../Scene/Camera.h"
#include "../Scene/CameraController.h"
#include "../Scene/CameraInputModifier.h"
#include "SpringInterpoler.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MinigameCameraController : public NScene::ICameraController
{
	OBJECT_BASIC_METHODS(MinigameCameraController);

public:
	MinigameCameraController();

	// From ICameraController
	virtual const bool IsEffect() const { return false; }
	virtual const bool IsActive() const { return true; }

	virtual void Update( NScene::SCameraPosition* pNewPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& dummy, NScene::Time timeDiff );
	virtual bool ProcessEvent( const Input::Event &	_eEvent );

  void EnableInterpolation( bool enable );

  bool IsCameraInWantedPosition() const;

	// From MinigameCameraController
	void SetTarget( const Placement& target );	
  void LockTarget( bool _lock ) { lockTarget = _lock; }

  // change camera params 
  void ChangeCamera( const NDb::ViewCamera& cameraDB );
  void ChangeCamera( const NScene::SCameraPosition& position );

  // change camera params with respect to camera resolution
  void ApplyResolutionModifcators();

  NScene::SCameraPosition GetCameraParams() const;
  
private:
	virtual void SetCamera( NScene::ICamera* _pCamera ) { pCamera = _pCamera; }
	void UpdateStep( NScene::SCameraPosition* pNewPos, const NScene::SCameraPosition& currentPos, const NScene::SCameraPosition& dummy, NScene::Time timeDiff );

  void RecalculateWantedPosition();

  bool IsNearPositions(const NScene::SCameraPosition& first, const NScene::SCameraPosition& second) const;

	CPtr<NScene::ICamera> pCamera;

  NScene::SCameraPosition wantedPosition;
  float wantedFov;

  SpringInterpoler<CVec3, SpringInterpolerVec3Policy> positionInterpolator;
  SpringInterpoler<float, SpringInterpolerAngularPolicy> yawInterpolator;
  SpringInterpoler<float, SpringInterpolerAngularPolicy> pitchInterpolator;
  SpringInterpoler<float, SpringInterpolerAngularPolicy> rollInterpolator;
  SpringInterpoler<float, SpringInterpolerFloatPolicy> rodInterpolator;
  SpringInterpoler<float, SpringInterpolerFloatPolicy> fovInterpolator;

	NScene::Time deltaReminder;

  Placement target;
  bool lockTarget;
  NScene::SCameraPosition basePosition;
};

} // namespace PF_Minigames
