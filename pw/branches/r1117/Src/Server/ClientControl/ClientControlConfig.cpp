#include "stdafx.h"

#include "ClientControlConfig.h"

NI_DEFINE_REFCOUNT( clientCtl::IConfigProvider );

namespace clientCtl
{

SConfig::SConfig() :
loginSvcUpdTimeout( 20.0f ),
userOperationTimeout( 15.0f )
{}


static SConfig s_config;

REGISTER_VAR( "client_ctl_login_svc_timeout",           s_config.loginSvcUpdTimeout, STORAGE_NONE );
REGISTER_VAR( "client_ctl_user_operation_timeout",      s_config.userOperationTimeout, STORAGE_NONE );


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

} //clientCtl
