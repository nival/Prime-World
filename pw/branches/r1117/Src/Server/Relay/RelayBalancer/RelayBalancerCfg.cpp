#include "RelayBalancer/stdafx.h"
#include "RelayBalancer/RelayBalancerCfg.h"

namespace Relay
{
  namespace Balancer
  {
    unsigned int userSoftLimitDefault = 250;
    REGISTER_VAR( "rb_user_softlimit_default", userSoftLimitDefault, STORAGE_NONE );

    unsigned int userHardLimitDefault = 500;
    REGISTER_VAR( "rb_user_hardlimit_default", userHardLimitDefault, STORAGE_NONE );

    unsigned int incomingClientNotifyTimeout = 30;
    REGISTER_VAR( "rb_incoming_client_notify_timeout", incomingClientNotifyTimeout, STORAGE_NONE );

    unsigned int hostUserDistributionAccuracy = 50; //  гранул€рность распределени€ юзеров по хостам с relay'€ми
    REGISTER_VAR( "rb_host_user_distribution_accuracy", hostUserDistributionAccuracy, STORAGE_NONE );

    unsigned int relayHostUserSoftLimitDefault = 0;
    REGISTER_VAR( "rb_relay_host_user_soft_limit_default", relayHostUserSoftLimitDefault, STORAGE_NONE );

    unsigned int relayHostUserHardLimitDefault = 0;
    REGISTER_VAR( "rb_relay_host_user_hard_limit_default", relayHostUserHardLimitDefault, STORAGE_NONE );

    unsigned int loadSetSize = 0;
    REGISTER_VAR( "rb_load_set_size", loadSetSize, STORAGE_NONE );

    unsigned int usersConnectTimeoutExpiredThreshold = 100;
    REGISTER_VAR( "rb_users_connect_timeout_expired_threshold", usersConnectTimeoutExpiredThreshold, STORAGE_NONE );

    unsigned int relayAllocationFailureThreshold = 5;
    REGISTER_VAR( "rb_relay_allocation_failure_threshold", relayAllocationFailureThreshold, STORAGE_NONE );

    unsigned int offlineRelayInLoadSetTimeout = 30;
    REGISTER_VAR( "rb_offline_relay_in_load_set_timeout", offlineRelayInLoadSetTimeout, STORAGE_NONE );

    static UserLimitsT roleUserLimits;
    static threading::Mutex roleUserLimitsMux; //  need for correct config reloading

    static UserLimitsT relayHostUserLimits;
    static threading::Mutex relayHostUserLimitsMux; //  need for correct config reloading

    static RelayAllocationMode::Enum relayAllocationMode = RelayAllocationMode::default_mode;
    static threading::Mutex relayAllocationModeMux;

    unsigned int Cfg::GetUserSoftLimitDefault()
    {
      return userSoftLimitDefault;
    }

    unsigned int Cfg::GetUserHardLimitDefault()
    {
      return userHardLimitDefault;
    }

    unsigned int Cfg::GetIncomingClientNotifyTimeout()
    {
      return incomingClientNotifyTimeout;
    }

    unsigned int Cfg::GetHostUserDistributionAccuracy()
    {
      return hostUserDistributionAccuracy;
    }

    unsigned int Cfg::GetRelayHostUserSoftLimitDefault()
    {
      return relayHostUserSoftLimitDefault;
    }

    unsigned int Cfg::GetRelayHostUserHardLimitDefault()
    {
      return relayHostUserHardLimitDefault;
    }

    unsigned int Cfg::GetLoadSetSize()
    {
      return loadSetSize;
    }

    unsigned int Cfg::GetUsersConnectTimeoutExpiredThreshold()
    {
      return usersConnectTimeoutExpiredThreshold;
    }

    unsigned int Cfg::GetRelayAllocationFailureThreshold()
    {
      return relayAllocationFailureThreshold;
    }

    unsigned int Cfg::GetOfflineRelayInLoadSetTimeout()
    {
      return offlineRelayInLoadSetTimeout;
    }

    static bool HandleCmdRelayHostUserLimit( char const * name, vector<wstring> const & params )
    {
      threading::MutexLock lock(relayHostUserLimitsMux);

      bool res = false;
      //  command format: rb_relay_host_user_limit <host_external_ip> <softuserlimit> <harduserlimit>
      if ((2 == params.size() && !params[0].empty() && !params[1].empty()) ||
          (3 == params.size() && !params[0].empty() && !params[1].empty() && !params[2].empty()))
      {
        string hostip = NStr::ToMBCS(params[0]);
        int softuserlimit = NStr::ToInt(params[1]);
        int harduserlimit = softuserlimit;
        if (3 == params.size())
          harduserlimit = NStr::ToInt(params[2]);

        if (softuserlimit <= harduserlimit)
        {
          relayHostUserLimits[hostip] = UserLimits(softuserlimit, harduserlimit);
          res = true;
        }
        else
        {
          LOG_E(0).Trace("Command '%s': softlimit must be less or equal to hardlimit(softlimit=%d hardlimit=%d)", name, softuserlimit, harduserlimit);
        }
      }

      if (!res)
      {
        //  usage
        LOG_E(0).Trace("Command '%s': incorrect format. Usage: %s <host_external_ip> <softuserlimit> <harduserlimit>", name, name);
      }

      return res;
    }
    REGISTER_CMD( rb_relay_host_user_limit, HandleCmdRelayHostUserLimit );

    UserLimitsT Cfg::GetRelayHostLimits()
    {
      threading::MutexLock lock(relayHostUserLimitsMux);
      return relayHostUserLimits;
    }

    static bool HandleCmdRoleUserLimit( char const * name, vector<wstring> const & params )
    {
      threading::MutexLock lock(roleUserLimitsMux);

      bool res = false;
      //  command format: rb_relay_role_user_limit <svcrole> <softuserlimit> <harduserlimit>
      if ((2 == params.size() && !params[0].empty() && !params[1].empty()) ||
        (3 == params.size() && !params[0].empty() && !params[1].empty() && !params[2].empty()))
      {
        string svcrole = NStr::ToMBCS(params[0]);
        if (svcrole == "\"\"" || svcrole == "\'\'")
          svcrole.clear();

        int softuserlimit = NStr::ToInt(params[1]);
        int harduserlimit = softuserlimit;
        if (3 == params.size())
          harduserlimit = NStr::ToInt(params[2]);

        if (softuserlimit <= harduserlimit)
        {
          roleUserLimits[svcrole] = UserLimits(softuserlimit, harduserlimit);
          res = true;
        }
        else
        {
          LOG_E(0).Trace("Command '%s': softlimit must be less or equal to hardlimit(softlimit=%d hardlimit=%d)", name, softuserlimit, harduserlimit);
        }
      }

      if (!res)
      {
        //  usage
        LOG_E(0).Trace("Command '%s': incorrect format. Usage: %s <svcrole> <softuserlimit> <harduserlimit>", name, name);
      }

      return res;
    }
    REGISTER_CMD( rb_relay_role_user_limit, HandleCmdRoleUserLimit );

    UserLimitsT Cfg::GetRelayRoleLimits()
    {
      threading::MutexLock lock(roleUserLimitsMux);
      return roleUserLimits;
    }

    static bool HandleCmdRelayAllocationMode( char const * name, vector<wstring> const & params )
    {
      bool res = true;

      threading::MutexLock lock(relayAllocationModeMux);

      //  command format: rb_relay_allocation_mode <allocation_mode>
      if (1 == params.size() && !params[0].empty())
      {
        string mode = NStr::ToMBCS(params[0]);
        if ("primary_relays_only" == mode)
          relayAllocationMode = RelayAllocationMode::primary_relays_only;
        else
        if ("secondary_relays_optional" == mode)
          relayAllocationMode = RelayAllocationMode::secondary_relays_optional;
        else
        if ("secondary_relays_mandatory" == mode)
          relayAllocationMode = RelayAllocationMode::secondary_relays_mandatory;
        else
        {
          res = false;
          LOG_E(0).Trace("Command '%s': value '%s' is NOT valid", name, params[0].c_str());
        }
      }
      else
      {
        res = false;
        //  usage
        LOG_E(0).Trace("Command '%s': incorrect format. Usage: %s <mode>", name, name);
      }

      return res;
    }
    REGISTER_CMD( rb_relay_allocation_mode, HandleCmdRelayAllocationMode );

    RelayAllocationMode::Enum Cfg::GetRelayAllocationMode()
    {
      threading::MutexLock lock(relayAllocationModeMux);
      return relayAllocationMode;
    }

  }
}
