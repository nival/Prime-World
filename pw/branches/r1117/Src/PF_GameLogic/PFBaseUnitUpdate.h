#pragma once

#error "Removed from project by BVS (12.12.2008) due to world-client communication simplification"

namespace NWorld
{
	_interface IBaseUnitUpdate
	{
		// base path unit updates
		virtual void OnMoveTo(     const CVec2& vPos )    = 0;
    virtual void OnTeleportTo( const CVec2& vPos )		= 0;
		virtual void OnStop()															= 0;
	};

}