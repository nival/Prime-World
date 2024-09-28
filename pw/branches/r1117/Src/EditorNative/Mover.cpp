#include "stdafx.h"
#include "Utility.h"
#include "EditorScene.h"
#include "Mover.h"

using namespace System::Drawing;
using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Moving;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mover::Mover( ManipulatorsController^ controller )
: Manipulator( controller ),
	elements( nullptr )		
{
	elements = gcnew array<ManipulatorElement^>( 4 )
		{
			gcnew CameraPlaneMoverElement( this, Color::Cyan ),
			gcnew AxisMoverElement( this, Color::Red ),
      gcnew AxisMoverElement( this, Color::Lime, gcnew Quaternion( CQuat( float( PI / 2 ), V3_AXIS_Z ) ) ),
			gcnew AxisMoverElement( this, Color::Blue, gcnew Quaternion( CQuat( float( -PI / 2 ), V3_AXIS_Y ) ) )
		};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mover::Drag( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera )
{
	for each ( MoverElement^ element in GraphicElements )
	{
		if ( element->IsCaptured )
		{
			IObjectTransformController^ tc = TransformController;
			const CVec3 newLocation = element->CalculateNewLocation( initialCursorPosition, delta, camera );

			Location = CVec3(
				tc->MovingX->IsEnabled ? RoundToBounds( newLocation.x, tc->MovingX->MinValue, tc->MovingX->MaxValue ) : newLocation.x,
				tc->MovingY->IsEnabled ? RoundToBounds( newLocation.y, tc->MovingY->MinValue, tc->MovingY->MaxValue ) : newLocation.y,
				tc->MovingZ->IsEnabled ? RoundToBounds( newLocation.z, tc->MovingZ->MinValue, tc->MovingZ->MaxValue ) : newLocation.z
				);
			break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mover::UpdateParentRotation()
{
  for each ( ManipulatorElement^ element in elements )
    element->UpdateParentRotation( IsGlobal, !IsGlobal ? gcnew Quaternion(Rotation) : Quaternion::Identity );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mover::OnTransformControllerChanged()
{
	if ( !ReferenceEquals( TransformController, nullptr ) )
	{
		IObjectTransformController^ tc = TransformController;
		elements[0]->Enabled = tc->MovingX->IsEnabled && tc->MovingY->IsEnabled && tc->MovingZ->IsEnabled;
		elements[1]->Enabled = tc->MovingX->IsEnabled;
		elements[2]->Enabled = tc->MovingY->IsEnabled;
		elements[3]->Enabled = tc->MovingZ->IsEnabled;

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
