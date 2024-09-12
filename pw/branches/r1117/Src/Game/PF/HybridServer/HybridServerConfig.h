#pragma once
#include "System/DefaultTypes.h"


namespace NCore
{
  struct ClientSettings;
}

namespace HybridServer
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SessionSettings
{
  int trustGap;
  int afkStepsCount;
  int afkStepsDisconnectCount;
  int simulationStep;
  int dumpStepsMaxCount;
  uint disconnectionGap;
  uint disconnectionWaterline;
  int connectionTimeout;
  int confirmFrequency;
  int firstConnectionTimeout;
  int snapshotRequestTimeout;
  int snapshotApplyTimeout;
  uint snapshotChunkSize;
  int snapshotChunkMaxCount;
  bool reconnectEnabled;
  int delayedCommandsWarningGap;
  int loadTimeoutSteps;
  int snapshotSendPerStep;
  int finishTimeoutSteps;
  int commandMaxSize;
  int commandsPerStepMaxSize;
  bool timescaleEnabled;
  int stepsDelayMin;
  int stepsDelayMax;
  int stepsDelayFrame;
  int reconnectTimeout;
  bool crcDataRequestsEnabled;
  int crcDataRequestsTimeout;
  int rollTimeout;
  int fastReconnectReserveSteps;
  bool sendAsyncToAllClientsEnabled;
  int disconnectAckTimeoutSteps;
  int spectatorsLimit;
  int logLag;
  bool multicastStepsEnabled;
  float timeScale;  // Currently not actually exposed to config, as unnecessary
  int playSameTeamTimeout;

  // 'pm' stands for 'protection magic'
  int pmConfirmFrequency;
  int pmTrustGap;
  int pmDelayGap;
  int pmDelayThreshold;
  int pmAsyncThreshold;

  SessionSettings()
    : trustGap(0)
    , afkStepsCount(0)
    , afkStepsDisconnectCount(0)
    , simulationStep(100)
    , dumpStepsMaxCount(2000)
    , disconnectionGap(0)
    , disconnectionWaterline(0)
    , connectionTimeout(0)
    , confirmFrequency(1)
    , firstConnectionTimeout(1200)
    , snapshotRequestTimeout(0)
    , snapshotApplyTimeout(600)
    , snapshotChunkSize(1024)
    , snapshotChunkMaxCount(4096)
    , reconnectEnabled(false)
    , delayedCommandsWarningGap(0)
    , loadTimeoutSteps(4200)
    , snapshotSendPerStep(64000)
    , finishTimeoutSteps(300)
    , commandMaxSize(256)
    , commandsPerStepMaxSize(64000)
    , timescaleEnabled(false)
    , stepsDelayMin(1)
    , stepsDelayMax(1)
    , stepsDelayFrame(0)
    , reconnectTimeout(0)
    , crcDataRequestsEnabled(false)
    , crcDataRequestsTimeout(500)
    , rollTimeout(0)
    , fastReconnectReserveSteps(0)
    , sendAsyncToAllClientsEnabled(false)
    , disconnectAckTimeoutSteps(0)
    , spectatorsLimit(0)
    , logLag(0)
    , multicastStepsEnabled(false)
    , timeScale(1.0f)
    , playSameTeamTimeout(0)
    , pmConfirmFrequency(2)
    , pmTrustGap(0)
    , pmDelayGap(0)
    , pmDelayThreshold(0)
    , pmAsyncThreshold(0)
  {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct HybridServerSettings
{
  bool enableStatistics;
  bool enableReplay;
  int rollRetryTimer;
  int logLagSlicer;

  HybridServerSettings()
    : enableStatistics( false )
    , enableReplay( false )
    , rollRetryTimer( 0 )
    , logLagSlicer(0)
  {}
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetSettings(HybridServerSettings * hybridServerSettings,
                 SessionSettings * sessionSettings,
                 NCore::ClientSettings * clientSettings);


} // namespace HybridServer
