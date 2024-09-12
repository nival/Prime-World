#include "RelayBalancer/stdafx.h"
#include "RelayBalancer/RelayBalancerSettings.h"
#include "RelayBalancer/RelayBalancerCfg.h"

namespace Relay
{
  namespace Balancer
  {
    Settings::Settings()
      :relayAllocationMode_(Cfg::GetRelayAllocationMode()),
      userSoftLimitDefault_(Cfg::GetUserSoftLimitDefault()),
      userHardLimitDefault_(Cfg::GetUserHardLimitDefault()),
      incomingClientNotifyTimeout_(Cfg::GetIncomingClientNotifyTimeout()),
      hostUserDistributionAccuracy_(Cfg::GetHostUserDistributionAccuracy()),
      relayHostUserSoftLimitDefault_(Cfg::GetRelayHostUserSoftLimitDefault()),
      relayHostUserHardLimitDefault_(Cfg::GetRelayHostUserHardLimitDefault()),
      loadSetSize_(Cfg::GetLoadSetSize()),
      usersConnectTimeoutExpiredThreshold_(Cfg::GetUsersConnectTimeoutExpiredThreshold()),
      relayAllocationFailureThreshold_(Cfg::GetRelayAllocationFailureThreshold()),
      offlineRelayInLoadSetTimeout_(Cfg::GetOfflineRelayInLoadSetTimeout())
    {
      roleUserLimits_ = Cfg::GetRelayRoleLimits();
      hostUserLimits_ = Cfg::GetRelayHostLimits();
    }

    Settings::~Settings()
    {
    }

    void Settings::dump(char const * _header, char const * _footter) const
    {
      if (_header)
        LOG_M(RBLOG).Trace("======= %s =======", _header);
      else
        LOG_M(RBLOG).Trace("======= %s =======", __FUNCTION__);

      LOG_M(RBLOG).Trace("relayAllocationMode = %s", RelayAllocationMode::ToString(relayAllocationMode_));
      LOG_M(RBLOG).Trace("userSoftLimit = %d", userSoftLimitDefault_);
      LOG_M(RBLOG).Trace("userHardLimit = %d", userHardLimitDefault_);
      LOG_M(RBLOG).Trace("incomingClientNotifyTimeout = %d", incomingClientNotifyTimeout_);
      LOG_M(RBLOG).Trace("hostUserDistributionAccuracy = %d", hostUserDistributionAccuracy_);
      LOG_M(RBLOG).Trace("relayHostUserSoftLimitDefault = %d", relayHostUserSoftLimitDefault_);
      LOG_M(RBLOG).Trace("relayHostUserHardLimitDefault = %d", relayHostUserHardLimitDefault_);
      LOG_M(RBLOG).Trace("loadSetSize = %d", loadSetSize_);
      LOG_M(RBLOG).Trace("usersConnectTimeoutExpiredThreshold = %d", usersConnectTimeoutExpiredThreshold_);
      LOG_M(RBLOG).Trace("relayAllocationFailureThreshold = %d", relayAllocationFailureThreshold_);
      LOG_M(RBLOG).Trace("offlineRelayInLoadSetTimeout = %d", offlineRelayInLoadSetTimeout_);

      if (roleUserLimits_.size())
      {
        LOG_M(RBLOG).Trace("--- User limits by service role begin ---");
        for(UserLimitsT::const_iterator cit = roleUserLimits_.begin(); cit != roleUserLimits_.end(); ++cit)
        {
          LOG_M(RBLOG).Trace("Role=%s softlimit=%d hardlimit=%d", cit->first.c_str(), cit->second.softlimit(), cit->second.hardlimit());
        }
        LOG_M(RBLOG).Trace("--- User limits by service role end ---");
      }
      else
      {
        LOG_M(RBLOG).Trace("There is no user limits by service roles");
      }

      if (hostUserLimits_.size())
      {
        LOG_M(RBLOG).Trace("--- Host user limits begin ---");
        for(UserLimitsT::const_iterator cit = hostUserLimits_.begin(); cit != hostUserLimits_.end(); ++cit)
        {
          LOG_M(RBLOG).Trace("Host=%s softlimit=%d hardlimit=%d", cit->first.c_str(), cit->second.softlimit(), cit->second.hardlimit());
        }
        LOG_M(RBLOG).Trace("--- Host user limits end ---");
      }
      else
      {
        LOG_M(RBLOG).Trace("There is no host user limits");
      }

      if (_footter)
        LOG_M(RBLOG).Trace("======= %s =======", _footter);
      else
        LOG_M(RBLOG).Trace("======= %s =======", __FUNCTION__);
    }

  }
}
