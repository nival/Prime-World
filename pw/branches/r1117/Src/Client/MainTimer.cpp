#include "stdafx.h"

#include "System/RandomGen.h"
#include "UI/FrameTimeRender.h"

#include "MainTimer.h"

static float g_timeScale = 1.0f;
static float g_fixedTimeDelta  = 0.0f;
static float g_maxTimeDelta    = 0.2f;
static float g_timeDeltaJitter = 0.0f;
static bool  g_fixedTimeDeltaSync = false;

static bool  g_enableTimeLogging = false;

#define TIME_LOGGING

namespace NMainLoop
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{

bool  timeInitialized = false;
float lastTime;
float lastTimeDelta;
NHPTimer::STime lastRealTime;

// Constants
#ifdef TIME_LOGGING
const int   timeLogBufferSize = 512;

struct TimeRecord
{
	float time;
	float realTime;
	float delta;
	bool  isStepFrame;
};

TimeRecord timeLog[timeLogBufferSize];
int timeLogPointer = 0;

int rewindTimeLogIndex(int i) { return (i > 0 ? i : timeLogBufferSize) - 1; }
#endif // TIME_LOGGING

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GetTime() { return lastTime; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NHPTimer::STime GetHPTime() { return lastRealTime; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GetTimeDelta() { return lastTimeDelta; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GetTimeScale() { return g_timeScale; }
void SetTimeScale( float scale ) { g_timeScale = scale; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarkStepFrame()
{
#ifdef TIME_LOGGING
	if (g_enableTimeLogging)
	{
		timeLog[rewindTimeLogIndex(timeLogPointer)].isStepFrame = true;
	}
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetTemporaryTimeDelta( float val )
{
  lastTimeDelta = val; 
}

void SetTemporaryTime( float val )
{
  lastTime = val;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void UpdateTime()
{
	if ( !timeInitialized )
	{
		NHPTimer::GetTime( lastRealTime );
		lastTime          = 0.0f;
		lastTimeDelta     = 0.0f;
		timeInitialized = true;
		return;
	}

	float newTimeDelta = NHPTimer::GetTimePassedAndUpdateTime( lastRealTime );

  NDebug::SetFrameTime( newTimeDelta );

	if (g_fixedTimeDelta > 0.0f)
	{
		float overridenTimeDelta = g_fixedTimeDelta;
		if (g_timeDeltaJitter > 0.0f)
			overridenTimeDelta += NRandom::Random(-g_timeDeltaJitter, g_timeDeltaJitter);
		if (g_fixedTimeDeltaSync && overridenTimeDelta > newTimeDelta)
		{
			NHPTimer::STime curTime;
			do 
			{
				NHPTimer::GetTime( curTime );
				curTime -= lastRealTime;
			} while (NHPTimer::Time2Seconds( curTime ) < (overridenTimeDelta - newTimeDelta));
		}
		newTimeDelta = overridenTimeDelta;
	}

	newTimeDelta = Min( newTimeDelta, g_maxTimeDelta );
	
	lastTimeDelta = newTimeDelta * g_timeScale;
	lastTime += lastTimeDelta;

#ifdef TIME_LOGGING
  if (g_enableTimeLogging)
	{
		timeLog[timeLogPointer].isStepFrame = false;
		timeLog[timeLogPointer].realTime = float(NHPTimer::Time2Seconds(lastRealTime));
		timeLog[timeLogPointer].time     = lastTime;
		timeLog[timeLogPointer].delta    = lastTimeDelta;
		timeLogPointer = (timeLogPointer + 1) % timeLogBufferSize;
	}
#endif
}

}

#ifdef TIME_LOGGING

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DumpTimeLog(char const* name, vector<wstring> const& params)
{
	using namespace NMainLoop;

	if (!g_enableTimeLogging)
		return true;

	DebugTrace("Time delta dump (scale = %f)", g_timeScale);

	int index = rewindTimeLogIndex(timeLogPointer);
	while (index != timeLogPointer)
	{
		DebugTrace("%4.2f %4.3f %4.3f %s", timeLog[index].delta * 1000.0f, timeLog[index].time, timeLog[index].realTime, 
			timeLog[index].isStepFrame ? "STEP!!!" : "");
		index = rewindTimeLogIndex(index);
	} 

	return true;
}


REGISTER_DEV_VAR( "timelog", g_enableTimeLogging, STORAGE_NONE );
REGISTER_DEV_CMD( timelogdump, DumpTimeLog );
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DEV_VAR( "timefixedelta", g_fixedTimeDelta, STORAGE_NONE );
REGISTER_DEV_VAR( "timejitter",    g_timeDeltaJitter, STORAGE_NONE );
REGISTER_DEV_VAR( "timefixedsync", g_fixedTimeDeltaSync, STORAGE_NONE );

