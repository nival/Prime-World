#pragma once

#include "SceneTypes.h"
#include "Camera.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Input
{
  class Event;
}

namespace NScene
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_interface ICameraController;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class CameraControllersContainer : public CObjectBase
	{
		OBJECT_METHODS( 0x1F4A8B13, CameraControllersContainer );

		typedef list<CPtr<ICameraController> > TCameraControllers;

		CObj<ICamera> pCamera;
		TCameraControllers cameraControllers;
		TCameraControllers cameraEffects;
    SCameraPosition curPos;
    bool bEnableEffects;
	private:
		void EraseInvalidFrom( TCameraControllers& controllers );
		void EraseInvalid();
		ICameraController* SelectFirstActiveController() const;

		CameraControllersContainer() {}
	public:
		CameraControllersContainer( ICamera *_pCamera );

		void Step( Time timeDiff );
		bool ProcessEvent( const Input::Event &event );
    void EnableEffects(bool bEnable) { bEnableEffects = bEnable; }

		// Hight level _interface
		void AddCameraController( ICameraController *pCameraController );
    ICameraController* GetActiveController() const { return SelectFirstActiveController(); }
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}