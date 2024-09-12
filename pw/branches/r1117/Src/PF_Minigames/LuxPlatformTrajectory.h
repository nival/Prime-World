#pragma once

#include "EaselTrajectory.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// common platform trajectory object with its functionality
//
// current class is a dummy class used for basic platform operations
// because data types are not defined yet
//
//////////////////////////////////////////////////////////////////////////
class CPlatformTrajectory
{
public:
	CPlatformTrajectory();
	~CPlatformTrajectory();
	
	// intersection checkings
	bool CheckXPlaneIntersection(const int xPlane);

	// positioning methods
	SVector GetMidPosition();    // get middle line position (usefull for start platform positioning)

	//
	// UNDONE !!! реализовать ....
	//

	// platform trajectory draw (call only if debug drawer is enabled)
	void DrawTrajectory();

private:
	CPlatformTrajectory(const CPlatformTrajectory &rhs);
	CPlatformTrajectory& operator=(const CPlatformTrajectory &rhs);

	// trajectory representation
	CHorizLineTrajectory trajectory;  // у нас пока заглушка с горизонтальными линиями траектории

protected:

};

}