#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "IObjectTransformController.h"

namespace EditorNative {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ref class EditorScene;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public enum class ManipulatorTypes
{
	None,
	Mover,
	Rotator,
	Scaler
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Manipulators {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class Manipulator;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class ManipulatorsController sealed
	{
	private:
		System::Collections::Generic::Dictionary<ManipulatorTypes, Manipulator^> manipulators;
		ManipulatorTypes currentManipulator;
		IObjectTransformController^ transformController;
    bool isGlobal;

	internal:
		ManipulatorsController();

	internal:
		void Draw( NScene::ICamera& camera );

		void SetState( ManipulatorTypes manipulatorType, IObjectTransformController^ controller );
		void SetInactiveState() { SetState( ManipulatorTypes::None, nullptr ); }

    void StartDrag( bool isGlobal );
		void Drag( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera );
    void EndDrag();
		bool TryCapture( const CVec2& cursorPosition, NScene::ICamera& camera );
		void Uncapture();
    
    void ResetManipulatorSize();
    void IncreaseManipulatorSize();
    void DecreaseManipulatorSize();
  
    property bool IsGlobal
		{
      bool get(){ return isGlobal; }
			void set( bool value );
		}

		property CVec3 Location
		{
			CVec3 get();
			void set( CVec3 value );
		}

		property CQuat Rotation
		{
			CQuat get();
			void set( CQuat value );
		}

		property CVec3 Scale
		{
			CVec3 get();
			void set( CVec3 value );
		}

		property ManipulatorTypes CurrentManipulator
		{
			ManipulatorTypes get() { return currentManipulator; }
		}

		property IObjectTransformController^ TransformController
		{
			IObjectTransformController^ get() { return transformController; }
		}

	private:
    Manipulator^ GetCurrent();

		property bool HasController
		{
			bool get() { return !ReferenceEquals( transformController, nullptr ); }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Manipulators
}	// namespace EditorNative
