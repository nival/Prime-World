#include "UserManagerSvc/stdafx.h"
#include "UserManagerSvc/UserManagerCfg.h"

static unsigned int s_userShadowLifetime = 60;
REGISTER_VAR( "usermgr_user_shadow_lifetime", s_userShadowLifetime, STORAGE_GLOBAL);
static unsigned int s_allocateRelayReturnTimeout = 20;
REGISTER_VAR( "usermgr_allocate_relay_return_timeout", s_allocateRelayReturnTimeout, STORAGE_GLOBAL);
static unsigned int s_allocateRelayCallbackTimeout = 20;
REGISTER_VAR( "usermgr_allocate_relay_callback_timeout", s_allocateRelayCallbackTimeout, STORAGE_GLOBAL);
static unsigned int s_PartialReconnectRetryTimeout = 40;
REGISTER_VAR( "usermgr_partial_reconnect_retry_timeout", s_PartialReconnectRetryTimeout, STORAGE_NONE );
static unsigned int s_PartialReconnectRetries = 2;
REGISTER_VAR( "usermgr_partial_reconnect_retries", s_PartialReconnectRetries, STORAGE_NONE );
bool s_PartialReconnectSupport = true; //  поддерживаем ли partial reconnect, информация отсылается клиенту,
                                        //  и клиент не пытается делать partial reconnect при разрыве secondary соединения,
                                        //  т.е. это способ отключать фичу
REGISTER_VAR( "usermgr_partial_reconnect_support", s_PartialReconnectSupport, STORAGE_NONE );

namespace UserManager
{
  unsigned int Cfg::GetUserShadowLifetime()
  {
    return s_userShadowLifetime;
  }

  unsigned int Cfg::GetAllocateRelayReturnTimeout()
  {
    return s_allocateRelayCallbackTimeout;
  }

  unsigned int Cfg::GetAllocateRelayCallbackTimeout()
  {
    return s_allocateRelayCallbackTimeout;
  }

  unsigned int Cfg::GetPartialReconnectRetryTimeout()
  {
    return s_PartialReconnectRetryTimeout;
  }

  unsigned int Cfg::GetPartialReconnectRetries()
  {
    return s_PartialReconnectRetries;
  }

  bool Cfg::GetPartialReconnectSupport()
  {
    return s_PartialReconnectSupport;
  }
}
