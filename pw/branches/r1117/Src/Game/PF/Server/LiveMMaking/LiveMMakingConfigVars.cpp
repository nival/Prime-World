#include "stdafx.h"
#include "LiveMMakingConfigVars.h"
#include "MMakingLog.h"

namespace mmaking
{

SMMConfig::SMMConfig() :
logLevel( ELogLevel::Normal ),
testManoeuvresWaitThreshold( 0 ),
trainingManoeuvres( false ),
localeTable( "ru" ),
geolocationTable( "ru0" ),
mockMatchmaking( false ),
sleepMs( 1 ),
checkRevision( true ), fullDumpLimit( 100 ), fullDumpPeriod( 30.0 ),
smartDumpTime( 5.0f ),
activeRequestLineLength( 300 ), activeGameRequestLineLength( 30 ),
debugLogging( false ),
threads( 4 ),
manoeuvresEnabled( true ),
international( true ),
ignorePings( false ),
donorLocale( "" ),
isolatedLocales( "" ),
mockMinimumUserWait( 10.0f ),
disabledHeroes( "" ),
disabledBotSkins( "" ),
enableRandomQueueIterator(1),
enablePlayerRatingMM(true),
orderTeamFormation(0)
{}


static SMMConfig s_liveMmCfg;

REGISTER_VAR( "mmaking_log_level",                  s_liveMmCfg.logLevel, STORAGE_NONE );
REGISTER_VAR( "mmaking_test_manoeuvres_wait",       s_liveMmCfg.testManoeuvresWaitThreshold, STORAGE_NONE );
REGISTER_VAR( "mmaking_test_training_manoeuvres",   s_liveMmCfg.trainingManoeuvres, STORAGE_NONE );
REGISTER_VAR( "mmaking_locales",                    s_liveMmCfg.localeTable, STORAGE_NONE );
REGISTER_VAR( "mmaking_locations",                  s_liveMmCfg.geolocationTable, STORAGE_NONE );
REGISTER_VAR( "mmaking_check_revision",             s_liveMmCfg.checkRevision, STORAGE_NONE );
REGISTER_VAR( "mmaking_full_dump_limit",            s_liveMmCfg.fullDumpLimit, STORAGE_NONE );
REGISTER_VAR( "mmaking_full_dump_time",             s_liveMmCfg.fullDumpPeriod, STORAGE_NONE );
REGISTER_VAR( "mmaking_smart_dump_time",            s_liveMmCfg.smartDumpTime, STORAGE_NONE );
REGISTER_VAR( "mmaking_active_requests_limit",      s_liveMmCfg.activeRequestLineLength, STORAGE_NONE );
REGISTER_VAR( "mmaking_active_game_requests_limit", s_liveMmCfg.activeGameRequestLineLength, STORAGE_NONE );
REGISTER_VAR( "mmaking_debug_logging",              s_liveMmCfg.debugLogging, STORAGE_NONE );
REGISTER_VAR( "mmaking_threads",                    s_liveMmCfg.threads, STORAGE_NONE );
REGISTER_VAR( "mmaking_enable_manoeuvres",          s_liveMmCfg.manoeuvresEnabled, STORAGE_NONE );
REGISTER_VAR( "mmaking_international",              s_liveMmCfg.international, STORAGE_NONE );
REGISTER_VAR( "mmaking_ignore_pings",               s_liveMmCfg.ignorePings, STORAGE_NONE );
REGISTER_VAR( "mmaking_donor_locale",               s_liveMmCfg.donorLocale, STORAGE_NONE );
REGISTER_VAR( "mmaking_isolated_locales",           s_liveMmCfg.isolatedLocales, STORAGE_NONE );
REGISTER_VAR( "mmaking_sleep_ms",                   s_liveMmCfg.sleepMs, STORAGE_NONE );
REGISTER_VAR( "mmaking_test_minimal_wait",          s_liveMmCfg.mockMinimumUserWait, STORAGE_NONE );
REGISTER_VAR( "mmaking_mock_production",            s_liveMmCfg.mockMatchmaking, STORAGE_NONE );
REGISTER_VAR( "mmaking_disabled_heroes",            s_liveMmCfg.disabledHeroes, STORAGE_NONE );
REGISTER_VAR( "mmaking_disabled_bot_skins",         s_liveMmCfg.disabledBotSkins, STORAGE_NONE );
REGISTER_VAR( "mmaking_enable_random_queue_iterator", s_liveMmCfg.enableRandomQueueIterator, STORAGE_NONE );
REGISTER_VAR( "mmaking_enable_player_rating_mm",     s_liveMmCfg.enablePlayerRatingMM, STORAGE_NONE );
REGISTER_VAR( "mmaking_order_team_formation",     s_liveMmCfg.orderTeamFormation, STORAGE_NONE );

StrongMT<MMConfig> CreateConfigFromStatics()
{
  return new MMConfig( s_liveMmCfg );
}

} //namespace mmaking
