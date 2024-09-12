#pragma once

namespace UserManager
{
  struct Cfg
  {
    static unsigned int GetUserShadowLifetime();
    static unsigned int GetAllocateRelayReturnTimeout();
    static unsigned int GetAllocateRelayCallbackTimeout();
    static unsigned int GetPartialReconnectRetryTimeout();
    static unsigned int GetPartialReconnectRetries();
    static bool GetPartialReconnectSupport();
  };
}
