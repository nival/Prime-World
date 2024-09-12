#include "stdafx.h"

#include "EaselGameData.h"
#include "EaselDebugDrawer.h"

#include "LuxPlatformTrajectory.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class CPlatformTrajectory implementation
//
//////////////////////////////////////////////////////////////////////////
CPlatformTrajectory::CPlatformTrajectory() 
					: trajectory(BORDER_WIDTH_OFFSET,
								 LOGIC_FIELD_WIDTH-BORDER_WIDTH_OFFSET,
								 LOGIC_FIELD_HEIGHT-BORDER_HEIGHT_OFFSET)
{

}

CPlatformTrajectory::~CPlatformTrajectory()
{

}

bool CPlatformTrajectory::CheckXPlaneIntersection(const int xPlane)
{
	if(xPlane < trajectory.GetPointAX() || xPlane > trajectory.GetPointBX())
		return false;

	return true;
}

SVector CPlatformTrajectory::GetMidPosition()
{
	SVector resultVec;
	resultVec.y = trajectory.GetPointAY();

	int iMidPosition = (trajectory.GetPointBX() - trajectory.GetPointAX())/2;
	resultVec.x = trajectory.GetPointAX() + iMidPosition;

	return resultVec;
}

void CPlatformTrajectory::DrawTrajectory()
{
	EaselDebugDrawer::Get()->DrawLine(trajectory.GetPointA(),trajectory.GetPointB(),COLOR_RED);	
}

}