#include "stdafx.h"
#include "GameStatistics.h"


static bool g_enableDebugStatistics = true;
REGISTER_VAR( "enable_debug_statistics", g_enableDebugStatistics, STORAGE_NONE );


namespace StatisticService
{

bool GameStatistics::IsDebugStatisticsAvailable() const
{
  return gameStatisticsDebug && g_enableDebugStatistics;
}


void GameStatistics::RemoveStepTimeFlags(int _stepTimeFlags) 
{
  stepTimeFlags &= ~_stepTimeFlags;

  for (int i = 0; i < sizeof(int)*8; ++i)
  {
    if (_stepTimeFlags & int(1))
    {
      stepTimeFlagsRemovalTime[i] = time(0);
    }
    _stepTimeFlags = _stepTimeFlags>>1;
  }
}


void GameStatistics::ApplyStepTimeFlags(RPC::ExceedingStepTimeInfo& info)
{
  info.typeId |= stepTimeFlags;

  for (int i = 0, flag = 1; i < stepTimeFlagsRemovalTime.size(); ++i, flag = flag<<1)
  {
    if (stepTimeFlagsRemovalTime[i] >= info.startTime && stepTimeFlagsRemovalTime[i] <= info.finishTime)
    {
      info.typeId |= flag;
    }
  }
}

} // namespace StatisticService

NI_DEFINE_REFCOUNT( StatisticService::GameStatistics )
