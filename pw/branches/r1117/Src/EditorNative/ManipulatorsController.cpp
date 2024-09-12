#include "stdafx.h"
#include "Mover.h"
#include "Rotator.h"
#include "Scaler.h"
#include "ManipulatorsController.h"

using namespace EditorNative;
using namespace EditorNative::Manipulators;
using namespace EditorNative::Manipulators::Moving;
using namespace EditorNative::Manipulators::Rotation;
using namespace EditorNative::Manipulators::Scaling;

static bool ValidController( ManipulatorTypes manipulator, IObjectTransformController^ tc )
{
	return 
		manipulator == ManipulatorTypes::Mover && ( tc->MovingX->IsEnabled || tc->MovingY->IsEnabled || tc->MovingZ->IsEnabled ) ||
		manipulator == ManipulatorTypes::Rotator && ( tc->RotationYaw->IsEnabled || tc->RotationPitch->IsEnabled || tc->RotationRoll->IsEnabled ) ||
		manipulator == ManipulatorTypes::Scaler && ( tc->ScalingX->IsEnabled || tc->ScalingY->IsEnabled || tc->ScalingZ->IsEnabled );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ManipulatorsController::ManipulatorsController()
{
	manipulators.Add( ManipulatorTypes::Mover, gcnew Mover( this ) );
	manipulators.Add( ManipulatorTypes::Rotator, gcnew Rotator( this ) );
	manipulators.Add( ManipulatorTypes::Scaler, gcnew Scaler( this ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::StartDrag(bool isCommonCenter)
{
  Manipulator^ manipulator = GetCurrent();

	if ( manipulator != nullptr )
	  manipulator->StartDrag();

  if ( HasController )
	  transformController->IsCommonCenter = isCommonCenter;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::Drag( const CVec2& initialCursorPosition, const CVec2& delta, NScene::ICamera& camera )
{
  Manipulator^ manipulator = GetCurrent();

	if ( manipulator != nullptr )
	  manipulator->Drag( initialCursorPosition, delta, camera );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::EndDrag()
{
  Manipulator^ manipulator = GetCurrent();

	if ( manipulator != nullptr )
	  manipulator->EndDrag();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::Draw( NScene::ICamera &camera )
{
  Manipulator^ manipulator = GetCurrent();
  
  if ( manipulator != nullptr )
    manipulator->Draw( camera );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::IsGlobal::set( bool value )
{
  isGlobal = value;

  for each(Manipulator^ manipulator in manipulators.Values)
  {
    if ( manipulator != nullptr )
      manipulator->IsGlobal = value;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::Location::set( CVec3 value )
{
	if ( HasController )
	{
		transformController->Location = gcnew Vector3( value );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 ManipulatorsController::Location::get()
{
	if ( HasController )
	{
		return transformController->Location->Native;
	}
	else
	{
		return VNULL3;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::Rotation::set( CQuat value )
{
	if ( HasController )
	{
		transformController->Rotation = gcnew Quaternion( value );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CQuat ManipulatorsController::Rotation::get()
{
	if ( HasController )
	{
		return transformController->Rotation->Native;
	}
	else
	{
		return Quaternion::Identity->Native;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::Scale::set( CVec3 value )
{
	if ( HasController )
	{
		transformController->Scale = gcnew Vector3( value );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 ManipulatorsController::Scale::get()
{
	if ( HasController )
	{
		return transformController->Scale->Native;
	}
	else
	{
		return CVec3( 1, 1, 1 );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::SetState( ManipulatorTypes manipulatorType, IObjectTransformController^ controller )
{
	if (
		!ReferenceEquals( controller, nullptr ) &&
		manipulatorType != ManipulatorTypes::None &&
		ValidController( manipulatorType, controller )
		)
	{
		currentManipulator = manipulatorType;
		transformController = controller;
	}
	else
	{
		currentManipulator = ManipulatorTypes::None;
		transformController = nullptr;
	}

	for each ( Manipulator^ manipulator in manipulators.Values )
	{
		manipulator->OnTransformControllerChanged();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ManipulatorsController::TryCapture( const CVec2& cursorPosition, NScene::ICamera& camera )
{
	Manipulator^ manipulator = GetCurrent();

  if( manipulator != nullptr )
    return manipulator->TryCapture( cursorPosition, camera );

  return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::Uncapture()
{
  Manipulator^ manipulator = GetCurrent();

  if( manipulator != nullptr )
    manipulator->Uncapture();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::ResetManipulatorSize()
{
  Manipulator^ manipulator = GetCurrent();

  if( manipulator != nullptr )
    manipulator->ResetSize();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::IncreaseManipulatorSize()
{
  Manipulator^ manipulator = GetCurrent();

  if( manipulator != nullptr )
    manipulator->IncreaseSize();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManipulatorsController::DecreaseManipulatorSize()
{
  Manipulator^ manipulator = GetCurrent();

  if( manipulator != nullptr )
    manipulator->DecreaseSize();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Manipulator^ ManipulatorsController::GetCurrent()
{
  Manipulator^ manipulator = nullptr;
	
  if ( HasController )
	  manipulators.TryGetValue( currentManipulator, manipulator );

  return manipulator;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////