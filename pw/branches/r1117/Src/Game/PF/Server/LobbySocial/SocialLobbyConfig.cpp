#include "stdafx.h"
#include "SocialLobbyConfig.h"

namespace socialLobby
{

static SConfig & Cfg()
{
  static SConfig cfg;
  return cfg;
}


REGISTER_VAR( "soclobby_accept_timeout",          Cfg().acceptTimeout, STORAGE_NONE );
REGISTER_VAR( "soclobby_guard_lobby_timeout",     Cfg().guardLobbyTimeout, STORAGE_NONE );
REGISTER_VAR( "soclobby_reconnect_timeout",       Cfg().reconnectTimeout, STORAGE_NONE );
REGISTER_VAR( "soclobby_backup_timeout_short",    Cfg().backupTimeoutShort, STORAGE_NONE );
REGISTER_VAR( "soclobby_backup_timeout_long",     Cfg().backupTimeoutLong, STORAGE_NONE );
REGISTER_VAR( "soclobby_stat_wait_time_line",     Cfg().mmWaitTimeLineLength, STORAGE_NONE );
REGISTER_VAR( "soclobby_stat_wait_time_factor",   Cfg().mmWaitTimeFactor, STORAGE_NONE );
REGISTER_VAR( "soclobby_stat_wait_time_limit",    Cfg().mmWaitTimeLimit, STORAGE_NONE );
REGISTER_VAR( "soclobby_debug_info_on_ping",      Cfg().debugInfoOnPing, STORAGE_NONE );
REGISTER_VAR( "soclobby_party_members_timeout",   Cfg().partyMembersTimeout, STORAGE_NONE );
REGISTER_VAR( "soclobby_conn_lost_timeout",       Cfg().connectionLostTimeout, STORAGE_NONE );
REGISTER_VAR( "soclobby_officer_lobby_rating",    Cfg().officerLobbyRating, STORAGE_NONE );
REGISTER_VAR( "soclobby_verbosity_level",         Cfg().verbosityLevel, STORAGE_NONE );
REGISTER_VAR( "soclobby_mm_logic_setup_timeout",  Cfg().mmLogicSetupTimeout, STORAGE_NONE );
REGISTER_VAR( "soclobby_ping_scale_threshold",    Cfg().pingScaleThreshold, STORAGE_NONE );
REGISTER_VAR( "soclobby_ping_scale_factor",       Cfg().pingScaleFactor, STORAGE_NONE );
REGISTER_VAR( "soclobby_pvx_disconn_timeout",     Cfg().pvxDisconnectTimeout, STORAGE_NONE );
REGISTER_VAR( "soclobby_merge_client_revisions",  Cfg().clientRevisionsMerge, STORAGE_NONE );
REGISTER_VAR( "soclobby_max_spectators",          Cfg().maxSpectators, STORAGE_NONE );

REGISTER_VAR( "soclobby_pinned_locations",        Cfg().pinnedLocations, STORAGE_NONE );
REGISTER_VAR( "soclobby_pinned_locations_priority", Cfg().pinnedLocationsPriority, STORAGE_NONE );
REGISTER_VAR( "soclobby_pinned_locations_threshold", Cfg().pinnedLocationsThreshold, STORAGE_NONE );

Strong<Config> CreateConfigFromStatics()
{
  return new Config( Cfg() );
}

} //namespace socialLobby
