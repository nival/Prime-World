#pragma once

struct IXmlSaver;
#include "../System/Placement.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPlacement
{
private:
	Matrix43 matrix;
	Placement place;
  CVec3 rotation2;

public:
	CPlacement();
	CPlacement( const CVec3& location, const CQuat& rotation, const CVec3& scale );

	const Matrix43& GetMatrix() const
	{
		return matrix;
	}

	const Placement& GetPlace() const
	{
		return place;
	}

  const CVec3& GetEulerRotation() const
  {
    return rotation2;
  }

	const CPlacement& operator = ( const Matrix43& matrix )
	{
		place.FromMatrix( matrix );
		this->matrix = matrix;
		return *this;
	}

	int operator&( IXmlSaver &f );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
