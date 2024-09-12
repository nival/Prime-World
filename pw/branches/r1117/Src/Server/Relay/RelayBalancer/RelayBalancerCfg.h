#pragma once

#include "RelayBalancer/RelayUserLimits.h"

namespace Relay
{
  namespace Balancer
  {
    struct Cfg
    {
      static RelayAllocationMode::Enum GetRelayAllocationMode();
      static unsigned int GetUserSoftLimitDefault();
      static unsigned int GetUserHardLimitDefault();
      static unsigned int GetIncomingClientNotifyTimeout();
      static unsigned int GetHostUserDistributionAccuracy();
      static unsigned int GetRelayHostUserSoftLimitDefault();
      static unsigned int GetRelayHostUserHardLimitDefault();
      static unsigned int GetLoadSetSize();
      static unsigned int GetUsersConnectTimeoutExpiredThreshold();
      static unsigned int GetRelayAllocationFailureThreshold();
      static unsigned int GetOfflineRelayInLoadSetTimeout();
      static UserLimitsT GetRelayHostLimits();
      static UserLimitsT GetRelayRoleLimits();
    };
  }
}
