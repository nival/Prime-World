#include "GameBalancer/stdafx.h"
#include "GameBalancer/GameBalancerCfg.h"

namespace GameBalancer
{
  static int gameAllocResponseTimeout = 20;
  REGISTER_VAR( "game_alloc_response_timeout", gameAllocResponseTimeout, STORAGE_NONE );

  static int gameAllocNotifyTimeout = 60;
  REGISTER_VAR( "game_alloc_notify_timeout", gameAllocNotifyTimeout, STORAGE_NONE );

  static int gameBalancerTestStepFreq = 100;
  REGISTER_VAR( "game_balancer_test_stepfreq", gameBalancerTestStepFreq, STORAGE_NONE );

  static nstl::string gameBalancerTestSvcPath;
  REGISTER_VAR( "game_balancer_test_svcpath", gameBalancerTestSvcPath, STORAGE_NONE );

  static unsigned int gameSoftLimit = 100;
  REGISTER_VAR( "game_balancer_softlimit", gameSoftLimit, STORAGE_NONE );

  static unsigned int gameHardLimit = 200;
  REGISTER_VAR( "game_balancer_hardlimit", gameHardLimit, STORAGE_NONE );

  static unsigned int hostGameDistributionAccuracy = 10; //  гранулярность распределения игр по хостам с gamesvc
  REGISTER_VAR( "game_balancer_host_game_distribution_accuracy", hostGameDistributionAccuracy, STORAGE_NONE );

  int Cfg::GetSelfTestStepFreq()
  {
    return gameBalancerTestStepFreq;
  }

  nstl::string const &  Cfg::GetSelfTestSvcPath()
  {
    return gameBalancerTestSvcPath;
  }

  int Cfg::GetAllocResponseTimeout()
  {
    return gameAllocResponseTimeout;
  }

  int Cfg::GetAllocNotifyTimeout()
  {
    return gameAllocNotifyTimeout;
  }

  unsigned int Cfg::GetGameSoftLimit()
  {
    return gameSoftLimit;
  }

  unsigned int Cfg::GetGameHardLimit()
  {
    return gameHardLimit;
  }

  unsigned int Cfg::GetHostGameDistributionAccuracy()
  {
    return hostGameDistributionAccuracy;
  }
}
