#include "stdafx.h"

#include "NewLoginConfig.h"

NI_DEFINE_REFCOUNT( newLogin::IConfigProvider );

namespace newLogin
{

SConfig::SConfig() :
firstDevUid( 1000 ),
sessionKeyExpire( 60.0f * 80.0f ),
helloWaitTimeout( 10.0f ),
processingTimeout( 20.0f ),
emptyLinksTimeout( 120.0f ),
svcLinksLimit( 16 ),
loadUpdatePeriod( 10.0f ),
rdpLogEvents( 1 ),
udpSockBufferSize( 65536 ),
threadPriority( 1 )
{}


static SConfig s_config;

REGISTER_VAR( "login_first_dev_uid",                      s_config.firstDevUid, STORAGE_NONE );
REGISTER_VAR( "login_session_key_expire",                 s_config.sessionKeyExpire, STORAGE_NONE );
REGISTER_VAR( "login_hello_timeout",                      s_config.helloWaitTimeout, STORAGE_NONE );
REGISTER_VAR( "login_processing_timeout",                 s_config.processingTimeout, STORAGE_NONE );
REGISTER_VAR( "login_empty_links_timeout",                s_config.emptyLinksTimeout, STORAGE_NONE );
REGISTER_VAR( "login_svc_links_limit",                    s_config.svcLinksLimit, STORAGE_NONE );
REGISTER_VAR( "login_load_update_period",                 s_config.loadUpdatePeriod, STORAGE_NONE );
REGISTER_VAR( "login_rdp_log_events",                     s_config.rdpLogEvents, STORAGE_NONE );
REGISTER_VAR( "login_thread_priority",                    s_config.threadPriority, STORAGE_NONE );


class ConfigProviderPolicy
{
public:
  ConfigProviderPolicy() {}
  IConfigProvider::TConfig * CreateNewConfig() { return new IConfigProvider::TConfig( s_config ); }
};


StrongMT<IConfigProvider> CreateConfigFromStatics()
{
  return new Transport::ConfigProvider<SConfig, ConfigProviderPolicy>;
}

} //newLogin
