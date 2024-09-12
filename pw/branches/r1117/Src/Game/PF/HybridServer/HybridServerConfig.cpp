
#include "HybridServerConfig.h"
#include "PeeredTypes.h"


static int gameTrustGap = 0;
REGISTER_VAR( "game_trust_gap", gameTrustGap, STORAGE_NONE );

static float gameDisconnectGap = 0.0f;
REGISTER_VAR( "game_disconnect_gap", gameDisconnectGap, STORAGE_NONE );

static int gameDisconnectWaterline = 0;
REGISTER_VAR( "game_disconnect_waterline", gameDisconnectWaterline, STORAGE_NONE );

static float gameAfkTime = 0.0f;
REGISTER_VAR( "game_afc_time", gameAfkTime, STORAGE_NONE );

static float gameAfkDisconnectTime = 0.0f;
REGISTER_VAR( "game_afc_disconnect_time", gameAfkDisconnectTime, STORAGE_NONE );

static int gameSnapshotChunkSize = 1024;
REGISTER_VAR( "game_snapshot_chunk_size", gameSnapshotChunkSize, STORAGE_NONE );

static int gameSnapshotChunkMaxCount = 4096;
REGISTER_VAR( "game_snapshot_chunk_max_count", gameSnapshotChunkMaxCount, STORAGE_NONE );

static int gameSnapshotSendPerStep = 64000;
REGISTER_VAR( "game_snapshot_send_per_step", gameSnapshotSendPerStep, STORAGE_NONE );

static int gameSaveReplay = 0;
REGISTER_VAR( "game_save_replay", gameSaveReplay, STORAGE_NONE );

static int gameDumpSteps = 1200;
REGISTER_VAR( "game_dump_steps", gameDumpSteps, STORAGE_NONE );

static float gameConnectionTimeout = 7.0f;
REGISTER_VAR( "game_connect_timeout", gameConnectionTimeout, STORAGE_NONE );

static float gameLoadTimeout = 420.0f;
REGISTER_VAR( "game_load_timeout", gameLoadTimeout, STORAGE_NONE );

static float gameFirstConnectionTimeout = 120.0f;
REGISTER_VAR( "game_first_connect_timeout", gameFirstConnectionTimeout, STORAGE_NONE );

static int gameConfirmFrequency = 1;
REGISTER_VAR( "game_confirm_frequency", gameConfirmFrequency, STORAGE_NONE );

static int gameSimulationStep = 100;
REGISTER_VAR( "game_simulation_step", gameSimulationStep, STORAGE_NONE );

static int gameLogLevel = 1;    
REGISTER_VAR( "game_log_level", gameLogLevel, STORAGE_NONE );

static float gameSnapshotRequestTimeout = 0.0f; // 0 = disabled
REGISTER_VAR( "game_snapshot_request_timeout", gameSnapshotRequestTimeout, STORAGE_NONE );

static float gameSnapshotApplyTimeout = 60.0f;
REGISTER_VAR( "game_snapshot_apply_timeout", gameSnapshotApplyTimeout, STORAGE_NONE );

static int gameReconnectEnabled = 0;  // 0 = disabled
REGISTER_VAR( "game_reconnect_enabled", gameReconnectEnabled, STORAGE_NONE );

static int gameDelayedCommandsWarningGap = 10;  // 10 steps
REGISTER_VAR( "game_delayed_commands_warning_gap", gameDelayedCommandsWarningGap, STORAGE_NONE );

static float gameFinishTimeout = 30.0f;
REGISTER_VAR( "game_finish_timeout", gameFinishTimeout, STORAGE_NONE );

static int gameCommandMaxSize = 256;
REGISTER_VAR( "game_command_max_size", gameCommandMaxSize, STORAGE_NONE );

static int gameCommandsPerStepMaxSize = 64000; // 64k to match the transport's packet size limit
REGISTER_VAR( "game_commands_per_step_max_size", gameCommandsPerStepMaxSize, STORAGE_NONE );

static int gameTimescaleEnabled = 0;
REGISTER_VAR( "game_timescale_enabled", gameTimescaleEnabled, STORAGE_NONE );

static int gameStepsDelayMin = 1;
REGISTER_VAR( "game_steps_delay_min", gameStepsDelayMin, STORAGE_NONE );

static int gameStepsDelayMax = 1;
REGISTER_VAR( "game_steps_delay_max", gameStepsDelayMax, STORAGE_NONE );

static float gameStepsDelayFrame = 0.0f;
REGISTER_VAR( "game_steps_delay_frame", gameStepsDelayFrame, STORAGE_NONE );

static float gameReconnectTimeout = 0.0f;
REGISTER_VAR( "game_reconnect_timeout", gameReconnectTimeout, STORAGE_NONE );

static int gameCrcDataRequestsEnabled = 0;
REGISTER_VAR( "game_crc_data_requests_enabled", gameCrcDataRequestsEnabled, STORAGE_NONE );

static float gameCrcDataRequestsTimeout = 50.0f;
REGISTER_VAR( "game_crc_data_requests_timeout", gameCrcDataRequestsTimeout, STORAGE_NONE );

static float gameRollTimeout = 0.0f;
REGISTER_VAR( "game_roll_timeout", gameRollTimeout, STORAGE_NONE );

static float gameRollRetryTimer = 0.0f;
REGISTER_VAR( "game_roll_retry_timer", gameRollRetryTimer, STORAGE_NONE );

static float gameFastReconnectReserveTime = 0.0f;
REGISTER_VAR( "game_fast_reconnect_reserve_time", gameFastReconnectReserveTime, STORAGE_NONE );

static int gameSendAsyncToAllClientsEnabled = 0;
REGISTER_VAR( "game_send_async_to_all_clients_enabled", gameSendAsyncToAllClientsEnabled, STORAGE_NONE );

static float gameDisconnectAckTimeout = 0.0f;
REGISTER_VAR( "game_disconnect_ack_timeout", gameDisconnectAckTimeout, STORAGE_NONE );

static int enableStatistics = 0;
REGISTER_VAR("game_enable_statistics", enableStatistics, STORAGE_NONE);

static int gameSpectatorsLimit = 0;
REGISTER_VAR("game_spectators_limit", gameSpectatorsLimit, STORAGE_NONE);

static int gameLogLagScheduler = 0;
REGISTER_VAR("game_log_lag_scheduler", gameLogLagScheduler, STORAGE_NONE);

static int gameLogLagSlicer = 0;
REGISTER_VAR("game_log_lag_slicer", gameLogLagSlicer, STORAGE_NONE);

static int gameMulticastStepsEnabled = 0;
REGISTER_VAR("game_multicast_steps_enabled", gameMulticastStepsEnabled, STORAGE_NONE);

static float gameProtectionMagicConfirmTimeout = 15.f;
REGISTER_VAR( "game_protection_magic_confirm_timeout", gameProtectionMagicConfirmTimeout, STORAGE_NONE );

static int gameProtectionMagicConfirmFrequency = 2;
REGISTER_VAR( "game_protection_magic_confirm_frequency", gameProtectionMagicConfirmFrequency, STORAGE_NONE );

static float gameProtectionMagicReceiveTimeout = 5.f;
REGISTER_VAR( "game_protection_magic_receive_timeout", gameProtectionMagicReceiveTimeout, STORAGE_NONE );

static int gameProtectionMagicAsyncThreshold = 10;
REGISTER_VAR( "game_protection_magic_async_threshold", gameProtectionMagicAsyncThreshold, STORAGE_NONE );

static int gameProtectionMagicDelayThreshold = 10;
REGISTER_VAR( "game_protection_magic_delay_threshold", gameProtectionMagicDelayThreshold, STORAGE_NONE );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Client specific game settings, which aren't related to client-server interaction

static int gameMinigameEnabled = 1;
REGISTER_VAR( "game_minigame_enabled", gameMinigameEnabled, STORAGE_NONE );

static float gameLogicParam1 = 0.0f;
REGISTER_VAR( "game_logic_param_1", gameLogicParam1, STORAGE_NONE );

static int gameShowHeroLevel = 0;
REGISTER_VAR( "game_show_hero_level", gameShowHeroLevel, STORAGE_NONE );

static int gameShowHeroRating = 0;
REGISTER_VAR( "game_show_hero_rating", gameShowHeroRating, STORAGE_NONE );

static int gameShowHeroForce = 0;
REGISTER_VAR( "game_show_hero_force", gameShowHeroForce, STORAGE_NONE );

static int gameShowDeltaRaiting = 0;
REGISTER_VAR( "game_show_delta_raiting", gameShowDeltaRaiting, STORAGE_NONE );

static int gameShowLocale = 0;
REGISTER_VAR( "game_show_locale", gameShowLocale, STORAGE_NONE );

static int gameShowGuildEmblem = 0;
REGISTER_VAR( "game_show_guild_emblem", gameShowGuildEmblem, STORAGE_NONE );

static string gameShareUrl = "";
REGISTER_VAR( "game_share_url", gameShareUrl, STORAGE_NONE );

static int gameAiForLeaversEnabled = 0;
REGISTER_VAR( "game_ai_for_leavers_enabled", gameAiForLeaversEnabled, STORAGE_NONE );

static float gameAiForLeaversThreshold = 5.0f;
REGISTER_VAR( "game_ai_for_leavers_threshold", gameAiForLeaversThreshold, STORAGE_NONE );


namespace
{
  // Converts time in seconds to steps count, according to step length setting
  int TimeToSteps(float seconds)
  {
    return seconds * (1000.f / gameSimulationStep);
  }
}


namespace HybridServer
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetSettings(HybridServerSettings * hybridServerSettings,
                 SessionSettings * sessionSettings,
                 NCore::ClientSettings * clientSettings)
{
  if (hybridServerSettings)
  {
    hybridServerSettings->enableStatistics = enableStatistics;
    hybridServerSettings->enableReplay = gameSaveReplay;
    hybridServerSettings->rollRetryTimer = TimeToSteps(gameRollRetryTimer);
    hybridServerSettings->logLagSlicer = gameLogLagSlicer;
  }

  if (sessionSettings)
  {
    sessionSettings->simulationStep = gameSimulationStep;
    sessionSettings->dumpStepsMaxCount = gameDumpSteps; 
    sessionSettings->trustGap = gameTrustGap;
    sessionSettings->afkStepsCount = TimeToSteps(gameAfkTime);
    sessionSettings->afkStepsDisconnectCount = TimeToSteps(gameAfkDisconnectTime);
    sessionSettings->disconnectionGap = TimeToSteps(gameDisconnectGap);
    sessionSettings->disconnectionWaterline = gameDisconnectWaterline;
    sessionSettings->connectionTimeout = TimeToSteps(gameConnectionTimeout);
    sessionSettings->confirmFrequency = gameConfirmFrequency;
    sessionSettings->firstConnectionTimeout = TimeToSteps(gameFirstConnectionTimeout);
    sessionSettings->snapshotRequestTimeout = TimeToSteps(gameSnapshotRequestTimeout);
    sessionSettings->snapshotApplyTimeout = TimeToSteps(gameSnapshotApplyTimeout);
    sessionSettings->snapshotChunkSize = gameSnapshotChunkSize;
    sessionSettings->snapshotChunkMaxCount = gameSnapshotChunkMaxCount;
    sessionSettings->reconnectEnabled = gameReconnectEnabled;
    sessionSettings->delayedCommandsWarningGap = gameDelayedCommandsWarningGap;
    sessionSettings->loadTimeoutSteps = TimeToSteps(gameLoadTimeout);
    sessionSettings->snapshotSendPerStep = gameSnapshotSendPerStep;
    sessionSettings->finishTimeoutSteps = TimeToSteps(gameFinishTimeout);
    sessionSettings->commandMaxSize = gameCommandMaxSize;
    sessionSettings->commandsPerStepMaxSize = gameCommandsPerStepMaxSize;
    sessionSettings->timescaleEnabled = gameTimescaleEnabled;
    sessionSettings->stepsDelayMin = gameStepsDelayMin;
    sessionSettings->stepsDelayMax = gameStepsDelayMax;
    sessionSettings->stepsDelayFrame = TimeToSteps(gameStepsDelayFrame);
    sessionSettings->reconnectTimeout = TimeToSteps(gameReconnectTimeout);
    sessionSettings->crcDataRequestsEnabled = gameCrcDataRequestsEnabled;
    sessionSettings->crcDataRequestsTimeout = TimeToSteps(gameCrcDataRequestsTimeout);
    sessionSettings->rollTimeout = TimeToSteps(gameRollTimeout);
    sessionSettings->fastReconnectReserveSteps = TimeToSteps(gameFastReconnectReserveTime);
    sessionSettings->sendAsyncToAllClientsEnabled = gameSendAsyncToAllClientsEnabled;
    sessionSettings->disconnectAckTimeoutSteps = TimeToSteps(gameDisconnectAckTimeout);
    sessionSettings->spectatorsLimit = gameSpectatorsLimit;
    sessionSettings->logLag = gameLogLagScheduler;
    sessionSettings->multicastStepsEnabled = gameMulticastStepsEnabled;

    sessionSettings->pmConfirmFrequency = gameProtectionMagicConfirmFrequency;
    sessionSettings->pmTrustGap = TimeToSteps(gameProtectionMagicConfirmTimeout);
    sessionSettings->pmDelayGap = TimeToSteps(gameProtectionMagicReceiveTimeout);
    sessionSettings->pmDelayThreshold = gameProtectionMagicDelayThreshold;
    sessionSettings->pmAsyncThreshold = gameProtectionMagicAsyncThreshold;
  }

  if (clientSettings)
  {
    clientSettings->minigameEnabled = gameMinigameEnabled;
    clientSettings->logicParam1 = gameLogicParam1;
    clientSettings->showHeroLevel = gameShowHeroLevel;
    clientSettings->showHeroRating = gameShowHeroRating;
    clientSettings->showHeroForce = gameShowHeroForce;
    clientSettings->showDeltaRaiting = gameShowDeltaRaiting;
    clientSettings->showLocale = gameShowLocale;
    clientSettings->showGuildEmblem = gameShowGuildEmblem;
    clientSettings->shareUrl = gameShareUrl;
    clientSettings->aiForLeaversEnabled = gameAiForLeaversEnabled;
    clientSettings->aiForLeaversThreshold = TimeToSteps(gameAiForLeaversThreshold);
  }
}

} // namespace HybridServer
