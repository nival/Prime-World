#include "stdafx.h"
#include "LobbyConfig.h"

namespace lobby
{

static SLobbyConfigData s_config;


REGISTER_VAR( "lobby_fixed_random",                   s_config.gameFixedRandom, STORAGE_NONE );
REGISTER_VAR( "lobby_dbg_status_interval",            s_config.statusDumpInterval, STORAGE_NONE );
REGISTER_VAR( "lobby_dbg_fat_status_interval",        s_config.fatStatusDumpInterval, STORAGE_NONE );
REGISTER_VAR( "lobby_my_ext_location",                s_config.myExternalLocation, STORAGE_NONE );
REGISTER_VAR( "lobby_load_notify_period",             s_config.loadNotifyPeriod, STORAGE_NONE );
REGISTER_VAR( "lobby_cluster_capacity",               s_config.loadCapacity, STORAGE_NONE );
REGISTER_VAR( "lobby_custom_autostart_players",       s_config.customAutoStartPlayers, STORAGE_NONE );
REGISTER_VAR( "lobby_hybrid_request_timeout",         s_config.hybridRequestTimeout, STORAGE_NONE );
REGISTER_VAR( "lobby_statistics_timeout",             s_config.statisticsAckTimeout, STORAGE_NONE );
REGISTER_VAR( "lobby_lost_gs_timeout",                s_config.lostGameServerTimeout, STORAGE_NONE );
REGISTER_VAR( "lobby_enable_dev_mode",                s_config.enableDevMode, STORAGE_NONE );
REGISTER_VAR( "lobby_game_finish_delivery_wait",      s_config.gameFinishDeliveryWait, STORAGE_NONE );
REGISTER_VAR( "lobby_game_finish_delivery_timeout",   s_config.gameFinishDeliveryTimeout, STORAGE_NONE );

REGISTER_VAR( "lobby_dev_balancer_mode",              s_config.developerBalanceMode, STORAGE_NONE );
REGISTER_VAR( "lobby_dev_balancer_uids",              s_config.developerBalanceUids, STORAGE_NONE );


class ConfigProviderPolicy
{
public:
  ConfigProviderPolicy() {}
  LobbyConfig * CreateNewConfig() { return new LobbyConfig( s_config ); }
};


StrongMT<IConfigProvider> CreateConfigFromStatics()
{
  return new Transport::ConfigProvider<SLobbyConfigData, ConfigProviderPolicy>;
}

} //namespace lobby
