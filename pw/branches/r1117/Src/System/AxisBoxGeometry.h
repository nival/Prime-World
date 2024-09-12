#ifndef AXIS_BOX_GEOMETRY_H_
#define AXIS_BOX_GEOMETRY_H_


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Box points indices.
enum EBoxPoints
{
	BOX_BX_BY_BZ = 0,
	BOX_UX_BY_BZ = 1,
	BOX_BX_UY_BZ = 2,
	BOX_UX_UY_BZ = 3,
	BOX_BX_BY_UZ = 4,
	BOX_UX_BY_UZ = 5,
	BOX_BX_UY_UZ = 6,
	BOX_UX_UY_UZ = 7,

	BOX_COUNT		= 8,

	BOX_AXIS_X	 = 0x1,
	BOX_AXIS_Y	 = 0x2,
	BOX_AXIS_Z	 = 0x4,
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAxisBox
{
protected: // Attributes

	CVec3 vMin;	// Coordinates of minimum corner.
	CVec3 vMax;	// Coordinates of maximum corner.

public: // Construction/Deconstruction

	CAxisBox()
	{
		vMin = CVec3( +FP_MAX_VALUE, +FP_MAX_VALUE, +FP_MAX_VALUE );
		vMax = CVec3( -FP_MAX_VALUE, -FP_MAX_VALUE, -FP_MAX_VALUE );
	}

	CAxisBox(
			const CVec3 & _vMin,
			const CVec3 & _vMax
		)
	{
		vMin = _vMin;
		vMax = _vMax;
	}

  CAxisBox(
    const CVec3 & _vOrigin,
    const CVec3 & _vExtents,
    bool
    )
  {
    vMin = _vOrigin - _vExtents;
    vMax = _vOrigin + _vExtents;
  }

	CAxisBox(
			const CAxisBox & _Box
		)
	{
		vMin = _Box.vMin;
		vMax = _Box.vMax;
	}

public: // Operators

	bool operator == (
			const CAxisBox & _Box
		) const
	{
		return ( vMin == _Box.vMin ) && 
					 ( vMax == _Box.vMax );
	}

	bool operator != (
			const CAxisBox & _Box
		) const
	{
		return !( (*this) == _Box );
	}

public: // Acccessors

	// Return maximum value of box
	const CVec3 & GetMax() const
	{
		return vMax;
	}

	// Setup maximum value of box
	void SetMax(
			const CVec3 & _vMax
		)
	{
		vMax = _vMax;
	}

	// Return minimum value of box
	const CVec3 & GetMin() const
	{
		return vMin;
	}

	// Setup minimum value of box
	void SetMin(
			const CVec3 & _vMin
		)
	{
		vMin = _vMin;
	}

	// Return center of box
	const CVec3 GetOrigin() const
	{
		return ( vMax + vMin ) * 0.5f;
	}

	// Setup center of box
	void SetOrigin(
			const CVec3 & _vOrigin
		)
	{
		const CVec3 vE = GetExtents();
		vMin = _vOrigin - vE;
		vMax = _vOrigin + vE;
	}

	// Return extents of box
	const CVec3 GetExtents() const
	{
		return ( vMax - vMin ) * 0.5f;
	}

	// Setup extents of box
	void SetExtents(
			const CVec3 & _vExtents
		)
	{
		const CVec3 vO = GetOrigin();
		vMin = vO - _vExtents;
		vMax = vO + _vExtents;
	}

public: // Public methods

	// Expand current box by other
	void Expand(
			const CAxisBox & _Box
		)
	{
		if ( !_Box.IsEmpty() )
		{
			vMin.Minimize( _Box.GetMin() );
			vMax.Maximize( _Box.GetMax() );
		}
	}

	// Expand current box by point
	void Expand(
			const CVec3 & _Point
		)
	{
		vMin.Minimize( _Point );
		vMax.Maximize( _Point );
	}

	// Enlarge axis box by vector
	void Enlarge(
			const CVec3 & _vValue
		)
	{
		if ( !IsEmpty() )
		{
			vMin -= _vValue;
			vMax += _vValue;
		}
	}

public: // Generic Routines

	// Check empty axis box
	bool IsEmpty() const
	{
		return ( vMin.x > vMax.x ||
						 vMin.y > vMax.y ||
						 vMin.z > vMax.z );
	}
	
	// Check point in axis box
	bool IsContained(
			const CVec3 & _vPoint
		) const
	{
		return ( _vPoint.x >= vMin.x && _vPoint.y >= vMin.y && _vPoint.z >= vMin.z &&
						 _vPoint.x <= vMax.x && _vPoint.y <= vMax.y && _vPoint.z <= vMax.z );
	}

	// Return point of box
	__forceinline bool ComputeSurfacePoints(
			CVec3 _Points[BOX_COUNT]
		) const
	{
		if (IsEmpty())
			return false;

		// Compute extents and origin of box
		const CVec3 vP = GetOrigin();
		const CVec3 vE = GetExtents();

		// Fill result data
		for (unsigned long i = 0; i < BOX_COUNT; ++i)
		{
			// Build sign mask
			const CVec3 vSignMask(
					((i & BOX_AXIS_X) == 0) ? -1.0f : 1.0f,
					((i & BOX_AXIS_Y) == 0) ? -1.0f : 1.0f,
					((i & BOX_AXIS_Z) == 0) ? -1.0f : 1.0f
				);

			CVec3 vExt;
			vExt.Mul( vE, vSignMask );
			_Points[i].Add( vP, vExt );
		}

		return true;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsIntersectBoxBox(
		const CAxisBox & _Box1,
		const CAxisBox & _Box2
	)
{
	return ( 
					 _Box1.GetMin().x <= _Box2.GetMax().x &&
					 _Box1.GetMin().y <= _Box2.GetMax().y &&
					 _Box1.GetMin().z <= _Box2.GetMax().z &&

					 _Box2.GetMin().x <= _Box1.GetMax().x &&
					 _Box2.GetMin().y <= _Box1.GetMax().y &&
					 _Box2.GetMin().z <= _Box1.GetMax().z 
				 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
