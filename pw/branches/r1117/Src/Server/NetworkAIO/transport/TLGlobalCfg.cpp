#include "transport/stdafx.h"
#include "transport/TLGlobalCfg.h"

namespace TransportLayer
{
  static int s_Threads = 0;
  REGISTER_VAR("tl_threads", TransportLayer::s_Threads, STORAGE_GLOBAL);
  static int s_ReadBlockSize = 512*1024;
  REGISTER_VAR("tl_read_block_size", s_ReadBlockSize, STORAGE_GLOBAL);
  static int s_SoRcvbuf = 512*1024;
  REGISTER_VAR("tl_so_rcvbuf", s_SoRcvbuf, STORAGE_GLOBAL);
  static unsigned int s_MaxWriteBlockSize = 1*1024*1024;
  REGISTER_VAR( "tl_max_write_block_size", s_MaxWriteBlockSize, STORAGE_GLOBAL );
  static int s_SoSndbuf = 512*1024;
  REGISTER_VAR("tl_so_sndbuf", s_SoSndbuf, STORAGE_GLOBAL);
  static int s_DisableNagleAlgorithm = 1;
  REGISTER_VAR("tl_disable_nagle_algorithm", s_DisableNagleAlgorithm, STORAGE_GLOBAL);
  static int s_SoKeepalive = 1;
  REGISTER_VAR("tl_so_keepalive", s_SoKeepalive, STORAGE_GLOBAL);
  static int s_LogLevel = 2; //  messages + errors
  REGISTER_VAR("tl_log_level", s_LogLevel, STORAGE_GLOBAL);
  static int s_TerabitLogLevel = 2; //  errors only
  REGISTER_VAR("tl_terabit_log_level", s_TerabitLogLevel, STORAGE_GLOBAL);
  static int s_MessageBlockHeapDumpFreq = 100000;
  REGISTER_VAR("tl_message_block_heap_dump_freq", s_MessageBlockHeapDumpFreq, STORAGE_GLOBAL);
  static int s_MessageBlockHeapPerConnection = 0;
  REGISTER_VAR("tl_message_block_heap_per_connection", s_MessageBlockHeapPerConnection, STORAGE_GLOBAL);
  static int s_MessageBlockNotypeUseThreshold = 50;
  REGISTER_VAR("tl_message_block_notype_use_threshold", s_MessageBlockNotypeUseThreshold, STORAGE_GLOBAL);
  static int s_MessageBlockWriteUseThreshold = 50;
  REGISTER_VAR("tl_message_block_write_use_threshold", s_MessageBlockWriteUseThreshold, STORAGE_GLOBAL);
  static int s_MessageBlockReadUseThreshold = 100;
  REGISTER_VAR("tl_message_block_read_use_threshold", s_MessageBlockReadUseThreshold, STORAGE_GLOBAL);
  static int s_LogWrittenBytes = 0;
  REGISTER_VAR("tl_log_written_bytes", s_LogWrittenBytes, STORAGE_GLOBAL);
  static int s_CheckActivityTimeout = 30;
  REGISTER_VAR("tl_check_activity_timeout", s_CheckActivityTimeout, STORAGE_GLOBAL);

  int GlobalCfg::GetThreads()
  {
    return s_Threads;
  }

  int GlobalCfg::GetReadBlockSize()
  {
    return s_ReadBlockSize;
  }

  int GlobalCfg::GetSoRcvbuf()
  {
    return s_SoRcvbuf;
  }

  unsigned int GlobalCfg::GetMaxWriteBlockSize()
  {
    return s_MaxWriteBlockSize;
  }

  int GlobalCfg::GetSoSndbuf()
  {
    return s_SoSndbuf;
  }

  int GlobalCfg::GetDisableNagleAlgorithm()
  {
    return s_DisableNagleAlgorithm;
  }

  int GlobalCfg::GetSoKeepalive()
  {
    return s_SoKeepalive;
  }

  int GlobalCfg::GetLogLevel()
  {
    return s_LogLevel;
  }

  int GlobalCfg::GetTerabitLogLevel()
  {
    return s_TerabitLogLevel;
  }

  int GlobalCfg::GetMessageBlockHeapDumpFreq()
  {
    return s_MessageBlockHeapDumpFreq;
  }

  int GlobalCfg::GetMessageBlockHeapPerConnection()
  {
    return s_MessageBlockHeapPerConnection;
  }

  int GlobalCfg::GetLogWrittenBytes()
  {
    return s_LogWrittenBytes;
  }

  int GlobalCfg::GetMessageBlockNotypeUseThreshold()
  {
    return s_MessageBlockNotypeUseThreshold;
  }

  int GlobalCfg::GetMessageBlockWriteUseThreshold()
  {
    return s_MessageBlockWriteUseThreshold;
  }

  int GlobalCfg::GetMessageBlockReadUseThreshold()
  {
    return s_MessageBlockReadUseThreshold;
  }

  unsigned int GlobalCfg::GetCheckActivityTimeout()
  {
    return s_CheckActivityTimeout;
  }
}
