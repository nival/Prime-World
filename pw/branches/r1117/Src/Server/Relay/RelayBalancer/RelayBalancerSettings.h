#pragma once

#include "RelayBalancer/RelayUserLimits.h"

namespace Relay
{
  namespace Balancer
  {
    class Settings
    {
    public:
      Settings();
      ~Settings();

      RelayAllocationMode::Enum relayAllocationMode() const;
      unsigned int userSoftLimitDefault() const;
      unsigned int userHardLimitDefault() const;
      unsigned int incomingClientNotifyTimeout() const;
      unsigned int hostUserDistributionAccuracy() const;
      unsigned int relayHostUserSoftLimitDefault() const;
      unsigned int relayHostUserHardLimitDefault() const;
      unsigned int loadSetSize() const;
      unsigned int usersConnectTimeoutExpiredThreshold() const;
      unsigned int relayAllocationFailureThreshold() const;
      unsigned int offlineRelayInLoadSetTimeout() const;
      UserLimits relayHostUserLimit(string const & _hostip) const;
      UserLimits relayRoleUserLimit(string const & _svcrole) const;

      void dump(char const * _header = 0, char const * _footter = 0) const;

    private:
      RelayAllocationMode::Enum relayAllocationMode_;
      unsigned int userSoftLimitDefault_;
      unsigned int userHardLimitDefault_;
      unsigned int incomingClientNotifyTimeout_;
      unsigned int hostUserDistributionAccuracy_;
      unsigned int relayHostUserSoftLimitDefault_;
      unsigned int relayHostUserHardLimitDefault_;
      unsigned int loadSetSize_;
      unsigned int usersConnectTimeoutExpiredThreshold_;
      unsigned int relayAllocationFailureThreshold_;
      unsigned int offlineRelayInLoadSetTimeout_;

      UserLimitsT roleUserLimits_;
      UserLimitsT hostUserLimits_;
    };

    inline
    RelayAllocationMode::Enum Settings::relayAllocationMode() const
    {
      return relayAllocationMode_;
    }

    inline
    unsigned int Settings::userSoftLimitDefault() const
    {
      return userSoftLimitDefault_;
    }

    inline
    unsigned int Settings::userHardLimitDefault() const
    {
      return userHardLimitDefault_;
    }

    inline
    unsigned int Settings::incomingClientNotifyTimeout() const
    {
      return incomingClientNotifyTimeout_;
    }

    inline
    unsigned int Settings::hostUserDistributionAccuracy() const
    {
      return hostUserDistributionAccuracy_;
    }

    inline
    unsigned int Settings::relayHostUserSoftLimitDefault() const
    {
      return relayHostUserSoftLimitDefault_;
    }

    inline
    unsigned int Settings::relayHostUserHardLimitDefault() const
    {
      return relayHostUserHardLimitDefault_;
    }

    inline
    unsigned int Settings::loadSetSize() const
    {
      return loadSetSize_;
    }

    inline
    unsigned int Settings::usersConnectTimeoutExpiredThreshold() const
    {
      return usersConnectTimeoutExpiredThreshold_;
    }

    inline
    unsigned int Settings::relayAllocationFailureThreshold() const
    {
      return relayAllocationFailureThreshold_;
    }

    inline
    unsigned int Settings::offlineRelayInLoadSetTimeout() const
    {
      return offlineRelayInLoadSetTimeout_;
    }

    inline
    UserLimits Settings::relayHostUserLimit(string const & _hostip) const
    {
      UserLimitsT::const_iterator cit = hostUserLimits_.find(_hostip);
      if (hostUserLimits_.end() == cit)
        return UserLimits(relayHostUserSoftLimitDefault(), relayHostUserHardLimitDefault());

      return cit->second;
    }

    inline
    UserLimits Settings::relayRoleUserLimit(string const & _svcrole) const
    {
      UserLimitsT::const_iterator cit = roleUserLimits_.find(_svcrole);
      if (roleUserLimits_.end() == cit)
        return UserLimits(userSoftLimitDefault(), userHardLimitDefault());

      return cit->second;
    }
  }
}
