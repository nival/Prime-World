#pragma once

#include "Manipulator.h"

namespace EditorNative {
namespace Manipulators {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ref class ManipulatorElement abstract
	{
	protected:
		const static float INITIAL_ROD = 10;
    static float sizeCoeff = INITIAL_ROD;
	private:
		Manipulator^ tool;
		bool isSelected;
		bool isCaptured;
		System::Drawing::Color color;
		bool enabled;

	protected:
		ManipulatorElement( Manipulator^ tool, System::Drawing::Color color );
    Quaternion^ parentRotation;

	public:

    static void ResetSize()
    {
      SizeCoeff = INITIAL_ROD; 
    }

    property static float SizeCoeff
    {
      float get() { return sizeCoeff; }
			void set( float value ) { sizeCoeff = value; }
    }

		property CVec3 Location
		{
			CVec3 get() { return tool->Location; }
		}

		property CQuat Rotation
		{
			CQuat get() { return tool->Rotation; }
		}

		property CVec3 Scale
		{
			CVec3 get() { return tool->Scale; }
		}

		property bool Enabled
		{
			bool get() { return enabled; }
			void set( bool value ) { enabled = value; }
		}

	internal:
		void PerformDrawing( NScene::ICamera& camera );
		bool TryCapture( const CVec2& cursorPosition, NScene::ICamera& camera );
    virtual void UpdateParentRotation( bool IsGlobal, Quaternion^ rotation ) {}

		property bool IsSelected
		{
			bool get() { return isSelected; }
			void set( bool value );
		}

		property bool IsCaptured
		{
			bool get() { return isCaptured; }
			void set( bool value );
		}

	protected:
		virtual void Draw( NScene::ICamera& camera ) abstract;
		virtual bool CanBeSelected( const CVec2& cursorPosition, NScene::ICamera& camera ) abstract;

		float CalculateScale( const NScene::ICamera& camera );

		static CVec3 CalculateCameraLocation( const NScene::ICamera& camera );

		property System::Drawing::Color CurrentColor
		{
			System::Drawing::Color get();
		}

		virtual void OnSelectedChanged( bool selected ) {}
		virtual void OnCapturedChanged( bool captured ) {}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Manipulators
}	// namespace EditorNative
