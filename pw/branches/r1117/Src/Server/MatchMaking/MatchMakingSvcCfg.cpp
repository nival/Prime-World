#include "stdafx.h"
#include "MatchMakingTypes.h"
#include "MatchMakingSvcCfg.h"

namespace MatchMaking
{
  static int sessionSize = MatchMaking::DEFAULT_SESSION_SIZE;
  static int statisticMode = 0;

  REGISTER_VAR( "tmm_session_size", sessionSize, STORAGE_GLOBAL );
  REGISTER_VAR( "tmm_statistic_mode", statisticMode, STORAGE_GLOBAL );

  int Cfg::GetSessionSize()
  {
    return sessionSize;
  }

  bool Cfg::StatisticModeOn()
  {
    return (statisticMode != 0);
  }
}
