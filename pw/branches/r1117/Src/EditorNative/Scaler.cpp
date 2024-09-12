#include "stdafx.h"
#include "Scaler.h"
#include "Utility.h"
#include "MultiDirectionScalerElement.h"
#include "SingleDirectionScalerElement.h"

using namespace System::Drawing;
using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Scaling;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scaler::Scaler( ManipulatorsController ^controller )
:	Manipulator( controller ),
	elements( nullptr ),
	initialScale( gcnew Vector3( 1, 1, 1 ) ),
  manipulatorScale( gcnew Vector3( 1, 1, 1 ) )
{
	elements = gcnew array<ManipulatorElement^>( 4 )
		{
			gcnew MultiDirectionScalerElement( this, Color::Cyan ),
			gcnew SingleDirectionScalerElement( this, Color::Red, gcnew Vector3( 1, 0, 0 ) ),
			gcnew SingleDirectionScalerElement( this, Color::Lime, gcnew Vector3( 0, 1, 0 ) ),
			gcnew SingleDirectionScalerElement( this, Color::Blue, gcnew Vector3( 0, 0, 1 ) )
		};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scaler::StartDrag()
{
  ManipulatorScale = Scale;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scaler::EndDrag()
{
  ManipulatorScale = Scale;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scaler::Drag( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera )
{
	for each ( ScalerElement^ element in GraphicElements )
	{
		if ( element->IsCaptured )
		{
			IObjectTransformController^ tc = TransformController;
			const CVec3 newScale = element->CalculateNewScale( initialCursorPosition, delta, camera );

			Scale = CVec3(
				tc->ScalingX->IsEnabled ? RoundToBounds( newScale.x, tc->ScalingX->MinValue, tc->ScalingX->MaxValue ) : newScale.x,
				tc->ScalingY->IsEnabled ? RoundToBounds( newScale.y, tc->ScalingY->MinValue, tc->ScalingY->MaxValue ) : newScale.y,
				tc->ScalingZ->IsEnabled ? RoundToBounds( newScale.z, tc->ScalingZ->MinValue, tc->ScalingZ->MaxValue ) : newScale.z
				);
			break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scaler::OnTransformControllerChanged()
{
  ManipulatorScale = Scale;

	if ( !ReferenceEquals( TransformController, nullptr ) )
	{
		IObjectTransformController^ tc = TransformController;
		elements[0]->Enabled = tc->ScalingX->IsEnabled && tc->ScalingY->IsEnabled && tc->ScalingZ->IsEnabled;
		elements[1]->Enabled = tc->ScalingX->IsEnabled;
		elements[2]->Enabled = tc->ScalingY->IsEnabled;
		elements[3]->Enabled = tc->ScalingZ->IsEnabled;
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
