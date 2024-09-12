#ifndef LOBBYCONFIG_H_INCLUDED
#define LOBBYCONFIG_H_INCLUDED

#include "ServerAppBase/ConfigProvider.h"


namespace lobby
{

struct SLobbyConfigData
{
  int         gameFixedRandom;
  float       statusDumpInterval;
  float       fatStatusDumpInterval;
  string      myExternalLocation;
  float       loadNotifyPeriod;
  unsigned    loadCapacity;
  int         customAutoStartPlayers;
  float       hybridRequestTimeout;
  float       statisticsAckTimeout;
  float       lostGameServerTimeout;
  bool        enableDevMode;
  float       gameFinishDeliveryWait;
  float       gameFinishDeliveryTimeout;
  int         developerBalanceMode;
  string      developerBalanceUids;

  SLobbyConfigData() :
  gameFixedRandom( 0 ),
  statusDumpInterval( 30.0f ),
  fatStatusDumpInterval( 0.0f ),
  myExternalLocation( string() ),
  loadNotifyPeriod( 10.0f ),
  loadCapacity( 10000 ),
  customAutoStartPlayers( 0 ),
  hybridRequestTimeout( 30.0f ),
  statisticsAckTimeout( 10.0f ),
  lostGameServerTimeout( 10.0f ),
  enableDevMode( true ),
  gameFinishDeliveryWait( 5.0f ),
  gameFinishDeliveryTimeout( 60.0f * 30.0f ),
  developerBalanceMode( 0 ),
  developerBalanceUids( string() )
  {}
};


typedef Transport::IConfigProvider<SLobbyConfigData> IConfigProvider;
typedef IConfigProvider::TConfig LobbyConfig;

StrongMT<IConfigProvider> CreateConfigFromStatics();

} //namespace lobby

#endif //LOBBYCONFIG_H_INCLUDED
