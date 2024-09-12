#pragma once

namespace Relay
{
  namespace Balancer
  {
    struct UserLimits
    {
      unsigned int softlimit_;
      unsigned int hardlimit_;

      UserLimits()
        :softlimit_(0),
        hardlimit_(0)
      {}

      UserLimits(unsigned int _softlimit, unsigned int _hardlimit)
        :softlimit_(_softlimit),
        hardlimit_(_hardlimit)
      {}

      unsigned int softlimit() const
      {
        return softlimit_;
      }

      unsigned int hardlimit() const
      {
        return hardlimit_;
      }
    };

    typedef map<string, UserLimits> UserLimitsT;
  }
}
