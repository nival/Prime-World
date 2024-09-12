#pragma once
#include "../System/matrix43.h"

namespace NScene
{

class TimeMutator
{
	float speed;
	float offset;
	float cycleLength;
	int   cycleCount;
	float duration;
	float totalTime;
	float time;

	int curCycleCount;

	bool isInit;

public:

	TimeMutator() : speed(1.f), offset(0.f), cycleLength(0.f), cycleCount(0), isInit(false),
									duration(1000.f), time(0.f), curCycleCount(0), totalTime(0.f) {};
	
	void SetTimeParams( float _speed, float _offset, float _cycleLength, int _cycleCount, float _duration, float _total );
	void SetSpeed( float _speed );
	void Reinit();
	void Update( const float timeDiff );
	float GetDT( const float timeDiff );
	bool CanUpdate();
	bool CanRender();
	float GetTime();
	float GetAbsoluteTime( float t ) const;

};

}