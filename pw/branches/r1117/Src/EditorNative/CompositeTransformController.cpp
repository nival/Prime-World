#include "Stdafx.h"
#include "Utility.h"
#include "CompositeTransformController.h"

using namespace EditorNative;
using namespace EditorNative::Manipulators;

static void UpdateMinMax( TransformParameters^ parameters, float currentValue, float% min, float% max )
{
	const float currentMin = currentValue - parameters->MinValue;

	if ( currentMin < min )
	{
		min = currentMin;
	}

	const float currentMax = parameters->MaxValue - currentValue;

	if ( currentMax > max )
	{
		max = currentMax;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CompositeTransformController::CompositeTransformController( array<IObjectTransformController^>^ _controllers )
: controllers ( _controllers ),
	tempRotation( _controllers->Length > 0 ? controllers[0]->Rotation : Quaternion::Identity ),
	tempScale( Vector3::Ones )
{
	float movingXMin = float::MaxValue;
	float movingXMax = float::MinValue;

	float movingYMin = float::MaxValue;
	float movingYMax = float::MinValue;

	float movingZMin = float::MaxValue;
	float movingZMax = float::MinValue;

	float rotationYawMin = float::MaxValue;
	float rotationYawMax = float::MinValue;

	float rotationPitchMin = float::MaxValue;
	float rotationPitchMax = float::MinValue;

	float rotationRollMin = float::MaxValue;
	float rotationRollMax = float::MinValue;

	float scalingXMin = float::MaxValue;
	float scalingXMax = float::MinValue;

	float scalingYMin = float::MaxValue;
	float scalingYMax = float::MinValue;

	float scalingZMin = float::MaxValue;
	float scalingZMax = float::MinValue;

	for each ( IObjectTransformController^ controller in controllers )
	{
		UpdateMinMax( controller->MovingX, controller->Location->X, movingXMin, movingXMax );
		UpdateMinMax( controller->MovingY, controller->Location->Y, movingYMin, movingYMax );
		UpdateMinMax( controller->MovingZ, controller->Location->Z, movingZMin, movingZMax );

		UpdateMinMax( controller->RotationYaw, controller->Rotation->Yaw, rotationYawMin, rotationYawMax );
		UpdateMinMax( controller->RotationPitch, controller->Rotation->Pitch, rotationPitchMin, rotationPitchMax );
		UpdateMinMax( controller->RotationRoll, controller->Rotation->Roll, rotationRollMin, rotationRollMax );

		UpdateMinMax( controller->ScalingX, controller->Scale->X, scalingXMin, scalingXMax );
		UpdateMinMax( controller->ScalingY, controller->Scale->Y, scalingYMin, scalingYMax );
		UpdateMinMax( controller->ScalingZ, controller->Scale->Z, scalingZMin, scalingZMax );
	}

	CVec3 sumLocation = VNULL3;
	for each ( IObjectTransformController^ controller in controllers )
	{
		sumLocation += controller->Location->Native;
	}
	tempLocation = gcnew Vector3( sumLocation / controllers->Length );

	movingX = gcnew TransformParameters( tempLocation->X - movingXMin, tempLocation->X + movingXMax );
	movingY = gcnew TransformParameters( tempLocation->Y - movingYMin, tempLocation->Y + movingYMax );
	movingZ = gcnew TransformParameters( tempLocation->Z - movingZMin, tempLocation->Z + movingZMax );

	rotationYaw = gcnew TransformParameters( -rotationYawMin, rotationYawMax );
	rotationPitch = gcnew TransformParameters( -rotationPitchMin, rotationPitchMax );
	rotationRoll = gcnew TransformParameters( -rotationRollMin, rotationRollMax );

	scalingX = gcnew TransformParameters( tempScale->X - scalingXMin, tempScale->X + scalingXMax );
	scalingY = gcnew TransformParameters( tempScale->Y - scalingYMin, tempScale->Y + scalingYMax );
	scalingZ = gcnew TransformParameters( tempScale->Z - scalingZMin, tempScale->Z + scalingZMax );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CompositeTransformController::Location::set( Vector3^ value )
{
	const CVec3 delta = value->Native - tempLocation->Native;
	for each ( IObjectTransformController^ controller in controllers )
	{
		controller->Location += gcnew Vector3( delta );
	}
	tempLocation = value;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CompositeTransformController::Rotation::set( Quaternion^ value )
{
  if( controllers->Length <= 1 || !IsCommonCenter)
  {
    CQuat native = value->Native;
    native.Normalize();

    for each ( IObjectTransformController^ controller in controllers )
      controller->Rotation = gcnew Quaternion( native );
  }
  else
  {
    CQuat delta = value->Native * tempRotation->Inverted->Native;
    delta.Normalize();

    for each ( IObjectTransformController^ controller in controllers )
    {
      const CVec3 prevRelativeLocation = controller->Location->Native - tempLocation->Native;
      const CVec3 currentRelativeLocation = delta.Rotate( prevRelativeLocation );
      controller->Location += gcnew Vector3( currentRelativeLocation - prevRelativeLocation );
      controller->Rotation *= gcnew Quaternion( delta );
    }
  }

  tempRotation = value;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CompositeTransformController::Scale::set( Vector3^ value )
{
  for each ( IObjectTransformController^ controller in controllers )
  {
	  controller->Scale = gcnew Vector3(ComponentProduct( ComponentInvProduct( controller->Scale->Native, tempScale->Native ), value->Native ));
  }

  //включен режим глобального скейла
  if( controllers->Length > 1 && IsCommonCenter )
  {   
    //ищем центр объектов
    CVec3 center = CVec3( 0, 0, 0 );

    for each ( IObjectTransformController^ controller in controllers )
    {
      center = center + controller->Location->Native;
    }

    center = CVec3( center.x / controllers->Length, 
                    center.y / controllers->Length, 
                    center.z / controllers->Length );


    for each ( IObjectTransformController^ controller in controllers )
    {
      CVec3 move = CVec3(
        (controller->Location->X - center.x) * value->X / tempScale->X,
        (controller->Location->Y - center.y) * value->Y / tempScale->Y,
         controller->Location->Z - center.z //не меняем высоту объектов
        );

      controller->Location = gcnew Vector3( move + center );
    }
  }

  tempScale = value;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////