#include "stdafx.h"
#include "PlacementConverter.h"

namespace EditorNative 
{
	void PlacementConverter::convertPlacement(DBTypes::Placement2^ from, DBTypes::Placement^ to)
	{
		to->location->x = from->translateX;
		to->location->y = from->translateY;
		to->location->z = from->translateZ;

		CQuat rotation;
		rotation.FromEulerAngles( ToRadian(from->rotationZ), ToRadian(from->rotationY), ToRadian(from->rotationX) );

		to->rotation->x = rotation.x;
		to->rotation->y = rotation.y;
		to->rotation->z = rotation.z;
		to->rotation->w = rotation.w;

		to->scale->x = from->scaleX;
		to->scale->y = from->scaleY;
		to->scale->z = from->scaleZ;
	}

	void PlacementConverter::convertPlacement(DBTypes::Placement^ from, DBTypes::Placement2^ to)
	{
		to->translateX = from->location->x;
		to->translateY = from->location->y;
		to->translateZ = from->location->z;

		CVec3 rotation;
		CQuat rot;
		rot.x = from->rotation->x;
		rot.y = from->rotation->y;
		rot.z = from->rotation->z;
		rot.w = from->rotation->w;
		rot.DecompEulerAngles( &rotation.z, &rotation.y, &rotation.x );

		to->rotationX = ToDegree(rotation.x);
		to->rotationY = ToDegree(rotation.y);
		to->rotationZ = ToDegree(rotation.z);

		to->scaleX = from->scale->x;
		to->scaleY = from->scale->y;
		to->scaleZ = from->scale->z;
	}
}