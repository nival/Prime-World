#pragma once

namespace Relay
{

class RelayServer2Cfg
{
public:
  static int GetThreads();
  static int GetKeepAliveTimeout();
  static int GetLogLevel();
  static int GetIOTerabitLogLevel();
  static int GetBackendSoRcvBuf();
  static int GetBackendSoSndBuf();
  static int GetBackendReadSize();
  static int GetClientSoRcvBuf();
  static int GetClientSoSndBuf();
  static int GetClientReadSize();
  static int Get2NewConnectionTimeout();
  static int GetCheckConnectionActivityTimeout();
  static int GetBackendWriteCompleteNotify();
  static int GetClientWriteCompleteNotify();
  static int GetBackendDisableNagleAlgorithm();
  static int GetClientDisableNagleAlgorithm();
  static int GetClientOutputQueueWarningThreshold();
  static int GetClientOutputQueueLimit();
  static int GetClientMessageBlockHeapDumpFreq();
  static int GetClientMessageBlockHeapPerConnection();
  static int GetBackendMessageBlockHeapDumpFreq();
  static int GetBackendMessageBlockHeapPerConnection();
  static int GetClientTrackInput();
  static int GetClientInputNotificationThreshold();
  static string const & GetClientTrackedSvc();
  static unsigned int GetBackendReportAmountOfReadBytes();
  static unsigned int GetBackendReportAmountOfWrittenBytes();
  static unsigned int GetClientReportAmountOfReadBytes();
  static unsigned int GetClientReportAmountOfWrittenBytes();
  static bool GetKeepClientConnectionOnWrongSeqNumError();
  static unsigned int GetOpenBackendChannelTimeout();
  static unsigned int GetSvcPingLoggingFreq();
  static string const & GetSvcRole();
  static int GetBackendWriteBlockUseThreshold();
  static int GetClientWriteBlockUseThreshold();
  static bool ParseClientWriteBlockUseThresholdFilter(const char *name, vector<wstring> const & params);
  static unsigned long long const * GetClientWriteBlockUseThresholdFilter();
  static unsigned int GetClientWriteBlockUseThresholdFilterSize();
  static bool GetClientWriteBlockUseThresholdLogEveryone();
  static unsigned int GetTrackGameSessionStepPeriodThreshold();
  static unsigned int GetTrackGameSessionRpcClass();
  static int GetTrackGameSessionRpcMethodIdx();
  static unsigned int GetChannelsPerBackendConnection();
  static int GetOpeningChannelTimeoutCountThreshold();
  static unsigned int GetInternalServicePingPeriod();
  static unsigned int GetClientPacketFreqCheckingPeriod();
  static unsigned int GetClientPacketSoftLimitPerCheckingPeriod();
  static unsigned int GetClientPacketHardLimitPerCheckingPeriod();
  static unsigned int GetOpenClientChannelTimeout();
};

}
