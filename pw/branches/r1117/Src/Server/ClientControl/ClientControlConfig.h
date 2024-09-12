#ifndef CLIENTCONTROL_CONFIG_H_INCLUDED
#define CLIENTCONTROL_CONFIG_H_INCLUDED

#include "ServerAppBase/ConfigProvider.h"


namespace clientCtl
{

struct SConfig
{
  float     loginSvcUpdTimeout;
  float     userOperationTimeout;

  SConfig();
};



typedef Transport::IConfigProvider<SConfig> IConfigProvider;
typedef IConfigProvider::TConfig Config;

StrongMT<IConfigProvider> CreateConfigFromStatics();

} //namespace clientCtl

#endif // CLIENTCONTROL_CONFIG_H_INCLUDED
