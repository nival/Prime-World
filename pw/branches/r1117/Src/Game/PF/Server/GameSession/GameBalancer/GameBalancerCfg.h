#pragma once

namespace GameBalancer
{
  struct Cfg
  {
    static int GetSelfTestStepFreq();
    static nstl::string const & GetSelfTestSvcPath();

    static int GetAllocResponseTimeout();
    static int GetAllocNotifyTimeout();

    static unsigned int GetGameSoftLimit();
    static unsigned int GetGameHardLimit();
    static unsigned int GetHostGameDistributionAccuracy();
  };
}
