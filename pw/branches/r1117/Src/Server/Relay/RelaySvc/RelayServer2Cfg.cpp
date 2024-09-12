#include "stdafx.h"
#include "Network/stdafx.h"
#include "System/Commands.h"
#include "RelayServer2Cfg.h"
#include "Coordinator/ServiceRole.h"

namespace Relay
{

static int rs2Threads = 0;
static int rs2KeepAliveTimeout = 60; // 0 - отключить
static int rs2LogLevel = 2;
static int rs2IOTerabitLogLevel = 2;
static int rs2BackendSoRcvBuf = -1;
static int rs2BackendSoSndBuf = -1;
static int rs2BackendReadSize = 64*1024;
static int rs2ClientSoRcvBuf = -1;
static int rs2ClientSoSndBuf = -1;
static int rs2ClientReadSize = 4096;
static int rs2NewConnectionTimeout = 20;
static int rs2CheckConnectionActivityTimeout = 120;
static int rs2ClientWriteCompleteNotify = 1;
static int rs2BackendWriteCompleteNotify = 1;
static int rs2ClientDisableNagleAlgorithm = 1;
static int rs2BackendDisableNagleAlgorithm = 1;
static int rs2ClientOutputQueueWarningThreshold = 600;
static int rs2ClientOutputQueueLimit = 8*1024;
static int rs2ClientMessageBlockHeapDumpFreq = 100000;
static int rs2ClientMessageBlockHeapPerConnection = 0;
static int rs2BackendMessageBlockHeapDumpFreq = 100000;
static int rs2BackendMessageBlockHeapPerConnection = 1;
static int rs2ClientTrackInput = 0;
static int rs2ClientInputNotificationThreshold = 60;
static string rs2ClientTrackedSvc = "";
static unsigned int rs2BackendReportAmountOfReadBytes = 10*1024*1024;
static unsigned int rs2BackendReportAmountOfWrittenBytes = 10*1024*1024;
static unsigned int rs2ClientReportAmountOfReadBytes = 1024*1024;
static unsigned int rs2ClientReportAmountOfWrittenBytes = 1024*1024;
static int rs2KeepClientConnectionOnWrongSeqNumError = 0;
static unsigned int rs2OpenBackendChannelTimeout = 0; //  seconds
static unsigned int rs2SvcPingLoggingFreq = 0;
static string rs2SvcRole = Coordinator::defaultServiceRole.c_str();
static int rs2BackendWriteBlockUseThreshold = 50;
static int rs2ClientWriteBlockUseThreshold = 100;
static unsigned long long rs2ClientWriteBlockUseThresholdFilter[64];
static unsigned int rs2ClientWriteBlockUseThresholdFilterSize = 0;
static bool rs2ClientWriteBlockUseThresholdLogEveryone = false;
static unsigned int rs2TrackGameSessionRpcClass = 0xfb78bcd4; //  IGameClient
static int rs2TrackGameSessionRpcMethodIdx = 1;  //  Step
static unsigned int rs2TrackGameSessionStepPeriodThreshold = 102;
static unsigned int rs2ChannelsPerBackendConnection = 50;
static int rs2OpeningChannelTimeoutCountThreshold = 20;
static unsigned int rs2InternalServicePingPeriod = 0;
static unsigned int rs2ClientPacketFreqCheckingPeriod = 1000;
static unsigned int rs2ClientPacketSoftLimitPerCheckingPeriod = 20;
static unsigned int rs2ClientPacketHardLimitPerCheckingPeriod = 40;
static unsigned int rs2OpenClientChannelTimeout = 20; //  seconds

REGISTER_VAR( "rs2_threads", rs2Threads, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_keepalive_timeout", rs2KeepAliveTimeout, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_loglevel", rs2LogLevel, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_ioterabit_loglevel", rs2IOTerabitLogLevel, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_backend_so_rcvbuf", rs2BackendSoRcvBuf, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_backend_so_sndbuf", rs2BackendSoSndBuf, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_backend_readsize", rs2BackendReadSize, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_client_so_rcvbuf", rs2ClientSoRcvBuf, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_client_so_sndbuf", rs2ClientSoSndBuf, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_client_readsize", rs2ClientReadSize, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_newconnection_timeout", rs2NewConnectionTimeout, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_check_connection_activity_timeout", rs2CheckConnectionActivityTimeout, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_client_write_complete_notify", rs2ClientWriteCompleteNotify, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_backend_write_complete_notify", rs2BackendWriteCompleteNotify, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_client_disable_nagle_algorithm", rs2ClientDisableNagleAlgorithm, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_backend_disable_nagle_algorithm", rs2BackendDisableNagleAlgorithm, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_client_output_queue_warning_threshold", rs2ClientOutputQueueWarningThreshold, STORAGE_GLOBAL );
REGISTER_VAR( "rs2_client_output_queue_limit", rs2ClientOutputQueueLimit, STORAGE_GLOBAL );
REGISTER_VAR("rs2_client_message_block_heap_dump_freq", rs2ClientMessageBlockHeapDumpFreq, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_message_block_heap_per_connection", rs2ClientMessageBlockHeapPerConnection, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_message_block_write_use_threshold", rs2ClientWriteBlockUseThreshold, STORAGE_GLOBAL);
REGISTER_CMD(rs2_client_message_block_use_threshold_filter, RelayServer2Cfg::ParseClientWriteBlockUseThresholdFilter);
REGISTER_VAR("rs2_client_message_block_use_threshold_log_everyone", rs2ClientWriteBlockUseThresholdLogEveryone, STORAGE_GLOBAL);
REGISTER_VAR("rs2_backend_message_block_heap_dump_freq", rs2BackendMessageBlockHeapDumpFreq, STORAGE_GLOBAL);
REGISTER_VAR("rs2_backend_message_block_heap_per_connection", rs2BackendMessageBlockHeapPerConnection, STORAGE_GLOBAL);
REGISTER_VAR("rs2_backend_message_block_write_use_threshold", rs2BackendWriteBlockUseThreshold, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_track_input", rs2ClientTrackInput, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_input_notification_threshold", rs2ClientInputNotificationThreshold, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_tracked_service", rs2ClientTrackedSvc, STORAGE_GLOBAL);
REGISTER_VAR("rs2_backend_report_amount_of_read_bytes", rs2BackendReportAmountOfReadBytes, STORAGE_GLOBAL);
REGISTER_VAR("rs2_backend_report_amount_of_written_bytes", rs2BackendReportAmountOfWrittenBytes, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_report_amount_of_read_bytes", rs2ClientReportAmountOfReadBytes, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_report_amount_of_written_bytes", rs2ClientReportAmountOfWrittenBytes, STORAGE_GLOBAL);
REGISTER_VAR("rs2_keep_client_connection_on_wrong_seq_num_error", rs2KeepClientConnectionOnWrongSeqNumError, STORAGE_GLOBAL);
REGISTER_VAR("rs2_open_backend_channel_timeout", rs2OpenBackendChannelTimeout, STORAGE_GLOBAL);
REGISTER_VAR("rs2_svcping_logging_freq", rs2SvcPingLoggingFreq, STORAGE_GLOBAL);
REGISTER_VAR("rs2_service_role", rs2SvcRole, STORAGE_GLOBAL);
REGISTER_VAR("rs2_track_game_session_rpc_class", rs2TrackGameSessionRpcClass, STORAGE_GLOBAL);
REGISTER_VAR("rs2_track_game_session_methond_idx", rs2TrackGameSessionRpcMethodIdx, STORAGE_GLOBAL);
REGISTER_VAR("rs2_track_game_session_step_period_threshold", rs2TrackGameSessionStepPeriodThreshold, STORAGE_GLOBAL);
REGISTER_VAR("rs2_channels_per_backend_connection", rs2ChannelsPerBackendConnection, STORAGE_GLOBAL);
REGISTER_VAR("rs2_opening_channel_timeout_count_threshold", rs2OpeningChannelTimeoutCountThreshold, STORAGE_GLOBAL);
REGISTER_VAR("rs2_internal_service_ping_period", rs2InternalServicePingPeriod, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_packet_freq_checking_period", rs2ClientPacketFreqCheckingPeriod, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_packet_soft_limit_per_checking_period", rs2ClientPacketSoftLimitPerCheckingPeriod, STORAGE_GLOBAL);
REGISTER_VAR("rs2_client_packet_hard_limit_per_checking_period", rs2ClientPacketHardLimitPerCheckingPeriod, STORAGE_GLOBAL);
REGISTER_VAR("rs2_open_client_channel_timeout", rs2OpenClientChannelTimeout, STORAGE_GLOBAL);

int RelayServer2Cfg::GetThreads()
{
  return rs2Threads;
}

int RelayServer2Cfg::GetKeepAliveTimeout()
{
  return rs2KeepAliveTimeout;
}

int RelayServer2Cfg::GetLogLevel()
{
  return rs2LogLevel;
}

int RelayServer2Cfg::GetIOTerabitLogLevel()
{
  return rs2IOTerabitLogLevel;
}

int RelayServer2Cfg::GetBackendSoRcvBuf()
{
  return rs2BackendSoRcvBuf;
}

int RelayServer2Cfg::GetBackendSoSndBuf()
{
  return rs2BackendSoSndBuf;
}

int RelayServer2Cfg::GetBackendReadSize()
{
  return rs2BackendReadSize;
}

int RelayServer2Cfg::GetClientSoRcvBuf()
{
  return rs2ClientSoRcvBuf;
}

int RelayServer2Cfg::GetClientSoSndBuf()
{
  return rs2ClientSoSndBuf;
}

int RelayServer2Cfg::GetClientReadSize()
{
  return rs2ClientReadSize;
}

int RelayServer2Cfg::Get2NewConnectionTimeout()
{
  return rs2NewConnectionTimeout;
}

int RelayServer2Cfg::GetCheckConnectionActivityTimeout()
{
  return rs2CheckConnectionActivityTimeout;
}

int RelayServer2Cfg::GetBackendWriteCompleteNotify()
{
  return rs2BackendWriteCompleteNotify;
}
int RelayServer2Cfg::GetClientWriteCompleteNotify()
{
  return rs2ClientWriteCompleteNotify;
}

int RelayServer2Cfg::GetBackendDisableNagleAlgorithm()
{
  return rs2BackendDisableNagleAlgorithm;
}

int RelayServer2Cfg::GetClientDisableNagleAlgorithm()
{
  return rs2ClientDisableNagleAlgorithm;
}

int RelayServer2Cfg::GetClientOutputQueueWarningThreshold()
{
  return rs2ClientOutputQueueWarningThreshold;
}

int RelayServer2Cfg::GetClientOutputQueueLimit()
{
  return rs2ClientOutputQueueLimit;
}

int RelayServer2Cfg::GetClientMessageBlockHeapDumpFreq()
{
  return rs2ClientMessageBlockHeapDumpFreq;
}
int RelayServer2Cfg::GetClientMessageBlockHeapPerConnection()
{
  return rs2ClientMessageBlockHeapPerConnection;
}
int RelayServer2Cfg::GetBackendMessageBlockHeapDumpFreq()
{
  return rs2BackendMessageBlockHeapDumpFreq;
}

int RelayServer2Cfg::GetBackendMessageBlockHeapPerConnection()
{
  return rs2BackendMessageBlockHeapPerConnection;
}

int RelayServer2Cfg::GetClientTrackInput()
{
  return rs2ClientTrackInput;
}

int RelayServer2Cfg::GetClientInputNotificationThreshold()
{
  return rs2ClientInputNotificationThreshold;
}

string const & RelayServer2Cfg::GetClientTrackedSvc()
{
  return rs2ClientTrackedSvc;
}

unsigned int RelayServer2Cfg::GetBackendReportAmountOfReadBytes()
{
  return rs2BackendReportAmountOfReadBytes;
}

unsigned int RelayServer2Cfg::GetBackendReportAmountOfWrittenBytes()
{
  return rs2BackendReportAmountOfWrittenBytes;
}

unsigned int RelayServer2Cfg::GetClientReportAmountOfReadBytes()
{
  return rs2ClientReportAmountOfReadBytes;
}

unsigned int RelayServer2Cfg::GetClientReportAmountOfWrittenBytes()
{
  return rs2ClientReportAmountOfWrittenBytes;
}

bool RelayServer2Cfg::GetKeepClientConnectionOnWrongSeqNumError()
{
  return (rs2KeepClientConnectionOnWrongSeqNumError != 0);
}

unsigned int RelayServer2Cfg::GetOpenBackendChannelTimeout()
{
  return rs2OpenBackendChannelTimeout;
}

unsigned int RelayServer2Cfg::GetSvcPingLoggingFreq()
{
  return rs2SvcPingLoggingFreq;
}

string const & RelayServer2Cfg::GetSvcRole()
{
  return rs2SvcRole;
}

int RelayServer2Cfg::GetBackendWriteBlockUseThreshold()
{
  return rs2BackendWriteBlockUseThreshold;
}

int RelayServer2Cfg::GetClientWriteBlockUseThreshold()
{
  return rs2ClientWriteBlockUseThreshold;
}

bool RelayServer2Cfg::ParseClientWriteBlockUseThresholdFilter(const char *name, vector<wstring> const & params)
{
  int j = 0;
  for(int i = 0; i < params.size(); ++i)
  {
    // unsigned long long l = _wcstoui64(params[i].c_str(), 0, 10);
    unsigned long long l = wcstoui64(params[i].c_str());
    if (l != _UI64_MAX && l != 0)
    {
      rs2ClientWriteBlockUseThresholdFilter[j] = l;
      ++j;
    }
  }

  rs2ClientWriteBlockUseThresholdFilterSize = j;

  return true;
}

unsigned long long const * RelayServer2Cfg::GetClientWriteBlockUseThresholdFilter()
{
  return rs2ClientWriteBlockUseThresholdFilter;
}

unsigned int RelayServer2Cfg::GetClientWriteBlockUseThresholdFilterSize()
{
  return rs2ClientWriteBlockUseThresholdFilterSize;
}

bool RelayServer2Cfg::GetClientWriteBlockUseThresholdLogEveryone()
{
  return rs2ClientWriteBlockUseThresholdLogEveryone;
}

unsigned int RelayServer2Cfg::GetTrackGameSessionRpcClass()
{
  return rs2TrackGameSessionRpcClass;
}

int RelayServer2Cfg::GetTrackGameSessionRpcMethodIdx()
{
  return rs2TrackGameSessionRpcMethodIdx;
}

unsigned int RelayServer2Cfg::GetTrackGameSessionStepPeriodThreshold()
{
  return rs2TrackGameSessionStepPeriodThreshold;
}

unsigned int RelayServer2Cfg::GetChannelsPerBackendConnection()
{
  return rs2ChannelsPerBackendConnection;
}

int RelayServer2Cfg::GetOpeningChannelTimeoutCountThreshold()
{
  return rs2OpeningChannelTimeoutCountThreshold;
}

unsigned int RelayServer2Cfg::GetInternalServicePingPeriod()
{
  return rs2InternalServicePingPeriod;
}

unsigned int RelayServer2Cfg::GetClientPacketFreqCheckingPeriod()
{
  return rs2ClientPacketFreqCheckingPeriod;
}

unsigned int RelayServer2Cfg::GetClientPacketSoftLimitPerCheckingPeriod()
{
  return rs2ClientPacketSoftLimitPerCheckingPeriod;
}

unsigned int RelayServer2Cfg::GetClientPacketHardLimitPerCheckingPeriod()
{
  return rs2ClientPacketHardLimitPerCheckingPeriod;
}

unsigned int RelayServer2Cfg::GetOpenClientChannelTimeout()
{
  return rs2OpenClientChannelTimeout;
}

}
