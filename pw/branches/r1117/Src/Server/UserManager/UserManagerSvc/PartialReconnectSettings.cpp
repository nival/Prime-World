#include "UserManagerSvc/stdafx.h"
#include "UserManagerSvc/PartialReconnectSettings.h"
#include "UserManagerSvc/UserManagerCfg.h"

namespace UserManager
{
  PartialReconnectSettings::PartialReconnectSettings()
    :supported_(Cfg::GetPartialReconnectSupport()),
    retries_(Cfg::GetPartialReconnectRetries()),
    retryTimeout_(Cfg::GetPartialReconnectRetryTimeout())
  {
  }

  PartialReconnectSettings::PartialReconnectSettings(bool _supported, unsigned int _retries, unsigned int _retryTimeout)
    :supported_(_supported),
    retries_(_retries),
    retryTimeout_(_retryTimeout)
  {
  }
}
