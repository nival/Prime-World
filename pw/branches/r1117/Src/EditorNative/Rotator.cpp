#include "stdafx.h"
#include "EditorScene.h"
#include "Rotator.h"

using namespace System::Drawing;
using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Rotation;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Rotator::Rotator( ManipulatorsController^ controller )
:	Manipulator( controller ),
	elements( nullptr )
{
	elements = gcnew array<ManipulatorElement^>( 4 )
		{
			gcnew CameraPlaneRotatorElement( this, Color::Cyan ),
			gcnew AxisRotatorElement( this, Color::Lime ),
			gcnew AxisRotatorElement( this, Color::Red, gcnew Quaternion( CQuat( float( PI / 2 ), V3_AXIS_Y ) ) ),
			gcnew AxisRotatorElement( this, Color::Blue, gcnew Quaternion( CQuat( float( PI / 2 ), V3_AXIS_X ) ) )
		};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Rotator::Drag( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera )
{
	for each ( RotatorElement^ element in GraphicElements )
	{
		if ( element->IsCaptured )
		{
			const CQuat newRotation = element->CalculateNewRotation( initialCursorPosition, delta, camera );

			float yaw, pitch, roll;
			newRotation.DecompEulerAngles( &yaw, &pitch, &roll );

			IObjectTransformController^ tc = TransformController;
			if (
				yaw <= tc->RotationYaw->MaxValue &&
				pitch <= tc->RotationPitch->MaxValue &&
				roll <= tc->RotationRoll->MaxValue &&
				yaw >= tc->RotationYaw->MinValue &&
				pitch >= tc->RotationPitch->MinValue &&
				roll >= tc->RotationRoll->MinValue
				)
			{
				Rotation = newRotation;
			}
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Rotator::UpdateParentRotation()
{
  for each ( ManipulatorElement^ element in elements )
    element->UpdateParentRotation( IsGlobal, Quaternion::Identity );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Rotator::OnTransformControllerChanged()
{
	if ( !ReferenceEquals( TransformController, nullptr ) )
	{
		IObjectTransformController^ tc = TransformController;
		elements[0]->Enabled = tc->RotationYaw->IsEnabled && tc->RotationPitch->IsEnabled && tc->RotationRoll->IsEnabled;
		elements[1]->Enabled = tc->RotationYaw->IsEnabled;
		elements[2]->Enabled = tc->RotationPitch->IsEnabled;
		elements[3]->Enabled = tc->RotationRoll->IsEnabled;

    UpdateParentRotation();
	}
	else
	{
		for each ( ManipulatorElement^ element in elements )
		{
			element->Enabled = false;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
