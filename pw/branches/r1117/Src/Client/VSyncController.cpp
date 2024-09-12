#include "stdafx.h"
#include "../System/HPTimer.h"
#include "../Render/renderer.h"

static int g_externalSyncCount = 1;
static float g_timeShift = 1.0f;
REGISTER_DEV_VAR( "sync_frame_count", g_externalSyncCount, STORAGE_NONE );
static NDebug::DebugVar<float> vsync_Delta( "Delta", "PerfCnt" );

namespace NMainLoop
{
namespace VSyncController
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
	NHPTimer::STime startTime = 0;
	int   syncFrameNumber = 1; // Sync every syncFrameNumber frame


	float MeasureTimeDelta()
	{
		NHPTimer::STime endTime;
		NHPTimer::GetTime(endTime);
		endTime -= startTime;
		return float(NHPTimer::Time2Seconds(endTime));
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GetSyncTimeDelta()
{
	const Render::RenderMode &mode = Render::GetRenderer()->GetCurrentRenderMode();
	if (mode.vsyncCount > 0 && mode.refreshRate > 0)
		return 1.0f / float(mode.refreshRate); // Vsync is on
	else
		return 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaitBeforePresent()
{
  const float syncTimeDelta = GetSyncTimeDelta();

	// First frame?
	if (startTime == 0 || syncTimeDelta == 0.0f) 
		return;

	syncFrameNumber = g_externalSyncCount;

	float timeDelta  = MeasureTimeDelta();
	float time2Check = syncTimeDelta * syncFrameNumber;
	if (timeDelta < time2Check)
	{
		time2Check -= syncTimeDelta * (1.0f - g_timeShift);
		if (timeDelta < time2Check)
		{
			DebugTrace("Wait for %3.1f msecs to reach %3.1f", (time2Check - timeDelta) * 1000.f, time2Check * 1000.0f);
			do 
			{
				timeDelta = MeasureTimeDelta();
			} while (timeDelta < time2Check); // Wait for half of the frame
		}
	} // end if (timeDelta < time2Check)
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CalculatePresentCount()
{
  const float syncTimeDelta = GetSyncTimeDelta();

	// First frame?
	if (startTime == 0 || syncTimeDelta == 0.0f) 
		return 1;

	syncFrameNumber = g_externalSyncCount;

	float timeDelta  = MeasureTimeDelta();
	return Max(0, syncFrameNumber - int(ceil(timeDelta / syncTimeDelta))) + 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarkPresentFinished()
{
	vsync_Delta.SetValue( float(NHPTimer::GetTimePassedAndUpdateTime(startTime)) * 1000.0f );
}

}
}