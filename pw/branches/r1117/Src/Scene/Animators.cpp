#include "stdafx.h"
#include "Animators.h"
#include "AnimSequencer.h"
#include "../System/Transform.h"
#include "../System/Spline.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ConstantAnimator::GetAnimBlendFactor( Time time ) 
{ 
	float relTime = time - startTime;
	if ( relTime <= 0 )
		return 0.001f;
	else if ( relTime < blendTime )
		return relTime / blendTime;

	return 1.f; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Time ConstantAnimator::GetAnimTime( Time time ) const 
{ 
	return time - startTime; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CubicSplineAnimPos::Setup( const vector<AnimPos> path, const AnimPos& startDir, const AnimPos& endDir, float tension )
{
	int sz = path.size();
	vector<CVec3> temp1;
	temp1.resize( sz );

	for( int i = 0; i < sz; ++i )
		temp1[i] = path[i].pos;

	if ( !CCubicSpline3D::Setup( temp1, startDir.pos, endDir.pos, tension ) ) 
		return false;

	vector<float> temp;
	temp.resize( sz + 2 );

	SHMatrix coefs;
	CCubicSpline1D::FillCoefMatrix( coefs, tension );

	//float startYaw = DirAngle( -startDir.y, -startDir.x );
	//float startPitch = atan2f( startDir.z, sqrt( sqr( startDir.x ) + sqr( startDir.y ) ) );

	//float endYaw = DirAngle( -endDir.y, -endDir.x );
	//float endPitch = atan2f( endDir.z, sqrt( sqr( endDir.x ) + sqr( endDir.y ) ) );

	temp[0] = startDir.yaw;
	for( int i = 0; i < sz; ++i )
		temp[i + 1] = path[i].yaw;
	temp[sz + 1] = endDir.yaw;
	yaw.Setup( coefs, temp );


	temp[0] = startDir.pitch;
	for( int i = 0; i < sz; ++i )
		temp[i + 1] = path[i].yaw;
	temp[sz + 1] = endDir.pitch;
	pitch.Setup( coefs, temp );

	temp[0] = startDir.roll;
	for( int i = 0; i < sz; ++i )
		temp[i + 1] = path[i].yaw;
	temp[sz + 1] = endDir.roll;
	roll.Setup( coefs, temp );

	return true;
}	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MoveFullAnimator::MoveFullAnimator(	Time _startTime, Time _blendTime, float _speed, const vector<AnimPos> &_points, const AnimPos &_startPos, const AnimPos &_endPos, const SMoveAnimationOptions &options )
: startTime(_startTime),speed(_speed), useYaw(options.useYaw), usePitch(options.usePitch), useRoll(options.useRoll)
, startBlendTime( options.startBlend ), endBlendTime( options.endBlend ), blendTime(_blendTime)
{
	AnimPos startDir, endDir;

	if ( options.useStartPos )
	{
		startDir = _startPos;
		_startPos.GetDir( &startDir.pos );
	}
	else
	{
		startDir.pos = (_points.begin() + 1)->pos - (_points.begin())->pos; 
		startDir.yaw = DirAngle( startDir.pos.y, startDir.pos.x );
		startDir.pitch = -atan2f( startDir.pos.z, sqrt( sqr( startDir.pos.x ) + sqr( startDir.pos.y ) ) );
	}

	if ( options.useEndPos )
	{
		endDir = _endPos;
		_endPos.GetDir( &endDir.pos );
	}
	else
	{
		endDir.pos = (_points.end() - 2)->pos - (_points.end() - 1)->pos;
		startDir.yaw = DirAngle( endDir.pos.y, endDir.pos.x );
		startDir.pitch = -atan2f( endDir.pos.z, sqrt( sqr( endDir.pos.x ) + sqr( endDir.pos.y ) ) );
	}

	spline.Setup( _points, startDir, endDir, 0.f );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Time MoveFullAnimator::GetMoveTime() const
{
	return spline.GetTotalLength() / speed + startBlendTime + endBlendTime - ( sqr(startBlendTime) + sqr(endBlendTime) )/ 2.f;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MoveFullAnimator::GetTransform( SHMatrix *pRes, Time time )
{
	Time endTime = GetMoveTime();
	Time relTime = Clamp( time - startTime, (Time)0, endTime );
	float pathPos = 0;

	if ( relTime < startBlendTime )
	{
		pathPos = speed * relTime * relTime / ( 2 * startBlendTime );
	}
	else if( relTime < ( endTime - endBlendTime ) )
	{
		pathPos = speed * startBlendTime / 2;
		pathPos += speed * ( relTime - startBlendTime );
	}
	else if( relTime < endTime )
	{
		pathPos = speed * startBlendTime / 2;
		pathPos += speed * ( endTime - endBlendTime - startBlendTime );
		float t0 = relTime - ( endTime - endBlendTime );
		pathPos += speed * t0  - speed / ( 2 * endBlendTime ) * t0 * t0;
	}
	else 
		pathPos = endTime * speed;

//	systemLog( NLogg::LEVEL_DEBUG ) << "@" << time << " Pos =" << pathPos / spline.GetTotalLength() << " = " << pathPos << endl;

	AnimPos pos;
	CVec3 dir;
	spline.GetValue( &pos, pathPos );
	spline.GetDiff( &dir, pathPos );

	float yaw = useYaw ? pos.yaw : DirAngle( dir.y, dir.x ); 
//	float pitch = usePitch ? pos.pitch : -atan2f( dir.z, sqrt( sqr( dir.x ) + sqr( dir.y ) ) );
//	float roll = useRoll ? pos.roll : 0.f;

	MakeMatrix( pRes, 0, yaw, 0, pos.pos );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float MoveFullAnimator::GetAnimSpeed( Time time ) 
{ 
	float relTime = time - startTime;
	float endTime = GetMoveTime();

	if ( relTime <= 0 )
		return 0.f;
	else if ( relTime < startBlendTime )
		return relTime / startBlendTime;
	else if( relTime < ( endTime - endBlendTime ) )
		return 1.f;
	else if( relTime < endTime )
		return ( endTime - relTime ) / endBlendTime;

	return 0.f;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Time MoveFullAnimator::GetAnimTime( Time time ) const
{
	float relTime = time - startTime;
	float endTime = GetMoveTime();

	if ( relTime <= 0 )
		return 0.f;
	else if ( relTime < startBlendTime )
		return sqr( relTime ) / startBlendTime / 2.f;
	else if( relTime < ( endTime - endBlendTime ) )
		return startBlendTime / 2.f + ( relTime - startBlendTime );
	else if( relTime < endTime )
		return startBlendTime / 2.f + ( endTime - endBlendTime - startBlendTime ) +  sqr( endTime - relTime ) / endBlendTime / 2.f;

	return startBlendTime / 2.f + ( endTime - endBlendTime - startBlendTime ) +  endBlendTime / 2.f;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float MoveFullAnimator::GetAnimBlendFactor( Time time ) 
{ 
	float relTime = time - startTime;
	if ( relTime <= 0 )
		return 0.001f;
	else if ( relTime < blendTime )
		return relTime / blendTime;

	return 1.f; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
