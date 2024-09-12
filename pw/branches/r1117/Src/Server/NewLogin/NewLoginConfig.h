#ifndef NEWLOGIN_CONFIG_H_INCLUDED
#define NEWLOGIN_CONFIG_H_INCLUDED

#include "ServerAppBase/ConfigProvider.h"


namespace newLogin
{

struct SConfig
{
  unsigned    firstDevUid;
  float       sessionKeyExpire;
  float       helloWaitTimeout;
  float       processingTimeout;
  float       emptyLinksTimeout;
  unsigned    svcLinksLimit;
  float       loadUpdatePeriod;
  unsigned    rdpLogEvents;
  int         udpSockBufferSize;
  int         threadPriority;

  SConfig();
};



typedef Transport::IConfigProvider<SConfig> IConfigProvider;
typedef IConfigProvider::TConfig Config;

StrongMT<IConfigProvider> CreateConfigFromStatics();

} //namespace newLogin

#endif // NEWLOGIN_CONFIG_H_INCLUDED
