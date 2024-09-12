#pragma once

#include "ManipulatorsController.h"

namespace EditorNative {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ref class EditorScene;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Manipulators {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class ManipulatorsController;
	ref class ManipulatorElement;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class Manipulator abstract
	{
	private:
		ManipulatorsController^ controller;
		Vector3^ location;
		bool enabled;
    bool isGlobal;
    static const float SIZE_STEP = 1.5f;
  protected:
        Quaternion^ rotation;
	internal:
		Manipulator( ManipulatorsController^ controller );

	internal:
		void Draw( NScene::ICamera& camera );

    virtual void StartDrag(){}
		virtual void Drag( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera ) abstract;
    virtual void EndDrag(){}
		bool TryCapture( const CVec2& cursorPosition, NScene::ICamera& camera );
		void Uncapture();

    void ResetSize();
    void IncreaseSize();
    void DecreaseSize();

		property CVec3 Location
		{
			CVec3 get() { return controller->Location; }
			void set( CVec3 value ) { controller->Location = value; }
		}

		property CQuat Rotation
		{
			CQuat get() { return controller->Rotation; }
			void set( CQuat value ) { controller->Rotation = value; }
		}

		property CVec3 Scale
		{
			CVec3 get() { return controller->Scale; }
			void set( CVec3 value ) { controller->Scale = value; }
		}

		property bool Enabled
		{
			bool get() { return enabled; }
			void set( bool value ) { enabled = value; }
		}

    property bool IsGlobal
		{
			bool get() { return isGlobal; }
			void set( bool value ) 
      { 
        isGlobal = value;
        UpdateParentRotation();
      }
		}

		virtual void OnTransformControllerChanged() abstract;

	protected:
		virtual property array<ManipulatorElement^>^ GraphicElements
		{
			virtual array<ManipulatorElement^>^ get() abstract;
		}

		property IObjectTransformController^ TransformController
		{
			IObjectTransformController^ get() { return controller->TransformController; }
		}

    virtual void UpdateParentRotation() abstract;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Manipulators
}	// namespace EditorNative
