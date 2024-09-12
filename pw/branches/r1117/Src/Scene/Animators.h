#pragma once
#include "AnimSequencer.hpp"
#include "../System/FastMath.h"
#include "../System/Spline.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float DirAngle( const float fDirY, const float fDirX )
{
	if ( fDirX == 0.f && fDirY == 0.f )
		return 0;
	CVec2 vDir( -fDirY, fDirX );
	NMath::NormalizeFast( &vDir.x, &vDir.y );
	return NMath::GetAngle( vDir );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float DirAngle( const CVec3 &vFrom, const CVec3 &vTo )
{
	return DirAngle(vTo.y - vFrom.y, vTo.x - vFrom.x);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConstantAnimator: public Animator
{
	OBJECT_BASIC_METHODS(ConstantAnimator);

	Time startTime;
	Time endTime;
	SHMatrix place;
	Time blendTime;
	ConstantAnimator() {}
public:	
	ConstantAnimator( Time _startTime, Time _endTime, Time _blendTime, const SHMatrix& _place )
		: startTime(_startTime), endTime(_endTime), place(_place), blendTime(_blendTime) {}
	Time GetStartTime() const { return startTime; }
	Time GetEndTime() const { return endTime; }
	void GetTransform( SHMatrix *pRes, Time time ) { *pRes = place; }
	float GetAnimSpeed( Time time ) { return 1.f; }
	float GetAnimBlendFactor( Time time );
	bool CanBlendPosition() const { return false; }
	Time GetAnimTime( Time time ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CubicSplineAnimPos : public CCubicSpline3D
{
	CCubicSpline1D yaw;
	CCubicSpline1D pitch;
	CCubicSpline1D roll;
public:
	CubicSplineAnimPos() {}
	bool Setup( const vector<AnimPos> path, const AnimPos& startDir, const AnimPos& endDir, float tension = 0.f );

	void GetValue( AnimPos* pRes, float t )
	{
		int seg;
		float t1;
		FindSegment( &seg, &t1, t );
		pRes->pos.x = x.GetValue( seg, t1 );
		pRes->pos.y = y.GetValue( seg, t1 );
		pRes->pos.z = z.GetValue( seg, t1 );
		pRes->yaw = yaw.GetValue( seg, t1 );
		pRes->pitch = pitch.GetValue( seg, t1 );
		pRes->roll = roll.GetValue( seg, t1 );
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MoveFullAnimator : public Animator
{
	OBJECT_BASIC_METHODS(MoveFullAnimator);

	Time startTime;
	CubicSplineAnimPos spline;
	float speed; // in meters per second

	bool useYaw;
	bool usePitch;
	bool useRoll;

	Time startBlendTime;
	Time endBlendTime;

	Time blendTime;
private:
	MoveFullAnimator() {}
	Time GetMoveTime() const;
public:
	MoveFullAnimator(	Time _startTime, Time _blendTime, float _speed, const vector<AnimPos> &_points, const AnimPos &_startPos, const AnimPos &_endPos, const SMoveAnimationOptions &options );

	Time GetStartTime() const { return startTime; }
	Time GetEndTime() const { return startTime + GetMoveTime() - blendTime; }
	void GetTransform( SHMatrix *pRes, Time time );
	float GetAnimSpeed( Time time );
	float GetAnimBlendFactor( Time time );
	bool CanBlendPosition() const { return true; }


	Time GetAnimTime( Time time ) const;
};			 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
