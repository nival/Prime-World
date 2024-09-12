#include "stdafx.h"
#include "TimeMutator.h"

namespace NScene
{

void TimeMutator::SetTimeParams( float _speed, float _offset, float _cycleLength, int _cycleCount, float _duration, float _total )
{
	isInit = false;
	time = 0.f;
	curCycleCount = 0;
	speed = _speed;
	offset = _offset*speed;
	cycleLength = _cycleLength;
	cycleCount = _cycleCount;
	duration = _duration*speed;
	totalTime = _total;

	if ( cycleCount == 0 && duration < 0.00001f )
	{
		duration = 1e20f;
	}
	if ( duration < 0.00001f )
	{
		duration = totalTime;
	}
}

void TimeMutator::SetSpeed( float _speed )
{
	speed = _speed;
}

void TimeMutator::Reinit()
{
	time          = 0.f;
	curCycleCount = 0;
}

void TimeMutator::Update( const float timeDiff )
{
	if ( !isInit )
	{
		isInit = true;
		return;
	}

	time += timeDiff*speed;
	if ( time - offset > duration )
	{
		curCycleCount++;
		time = offset;
	}
}

bool TimeMutator::CanUpdate()
{
	if ( time < offset )
	{
		return false;
	}

	if ( curCycleCount > cycleCount && cycleCount != 0 )
	{
		return false;
	}

	return true;
}

bool TimeMutator::CanRender()
{
	if ( time < offset )
	{
		return false;
	}

	if ( curCycleCount >= cycleCount && cycleCount != 0 )
	{
		return false;
	}

	return true;
}

float TimeMutator::GetTime()
{
	return time - offset > 0.f ? time - offset : 0.f;
}

float TimeMutator::GetAbsoluteTime( float t ) const
{
	if (speed > 0.0001f)
		return t/speed;
	else
		return 10000.0f; // @BVS@TODO What number should I return?
}

float TimeMutator::GetDT( const float timeDiff )
{
	return timeDiff*speed;
}

}