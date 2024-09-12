#include "transport/stdafx.h"
#include "ClientTransportConfig.h"
#include "Network/ClusterConfiguration.h"

namespace Transport
{
  static int s_LogLevel = 2;
  REGISTER_VAR("transport_log_level", s_LogLevel, STORAGE_NONE);
  static int s_DisableNagleAlgorithm = 1; //  -1 - system value, 0 - turn off, 1 - turn on
  REGISTER_VAR("transport_disable_nagle_algorithm", s_DisableNagleAlgorithm, STORAGE_NONE);
  static int s_ReadBlockSize = 64*1024;
  REGISTER_VAR("transport_read_block_size", s_ReadBlockSize, STORAGE_NONE);
  static int s_CheckConnectionActivityTimeout = 5;
  REGISTER_VAR("transport_check_connection_activity_timeout", s_CheckConnectionActivityTimeout, STORAGE_NONE);
  static int s_KeepalivePeriod = 30;
  REGISTER_VAR("transport_keepalive_period", s_KeepalivePeriod, STORAGE_NONE);
  static int s_NumberOfThreads = 2;
  REGISTER_VAR("transport_threads", s_NumberOfThreads, STORAGE_NONE);

  int ClientCfg::GetLogLevel()
  {
    return s_LogLevel;
  }

  int ClientCfg::DisableNagleAlgorithm()
  {
    return s_DisableNagleAlgorithm;
  }

  int ClientCfg::GetReadBlockSize()
  {
    return s_ReadBlockSize;
  }

  int ClientCfg::GetCheckConnectionActivityTimeout()
  {
    return s_CheckConnectionActivityTimeout;
  }

  int ClientCfg::GetKeepalivePeriod()
  {
    return s_KeepalivePeriod;
  }

  int ClientCfg::GetNumberOfThreads()
  {
    return s_NumberOfThreads;
  }

  string const & ClientCfg::GetLoginAddress()
  {
    return Network::GetLoginServerAddress();
  }
}
