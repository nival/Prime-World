#pragma warning( disable : 4996)
#include "stdafx.h"
#include <IOTerabit/TcpChannel.h>
#include <IOTerabit/ChannelManager.h>
#include <IOTerabit/ChannelAcceptor.h>
#include <IOTerabit/ChannelConnector.h>
#include <fstream>

#include "NewClientVerifier.h"
#include "RelayChannelManager.h"
#include "RelayClientProtocol.h"
#include "RelayBackendProtocol.h"
#include "BaseChannel.h"
#include "ClientAcceptor.h"
#include "RelayServer2Cfg.h"
#include "RelaySvc/IOThreadPool.h"
#include "RelayClientsVerifier.h"
#include "GameSvcTrafficTrackerFactory.h"

#include "RelayServer2.h"

using namespace Terabit;

namespace Relay
{



void RelayServer2::ThreadMain( volatile bool & _isRunning )
{
  int loglevel = RelayServer2Cfg::GetLogLevel();
  u_long logmask = u_long(-1);
  if (3 == loglevel)
  {
    logmask = LM_NOTICE | LM_WARNING | LM_ERROR | LM_CRITICAL;
    logStream->SetDefaultMinLevelFilter(NLogg::LEVEL_WARNING);
  }
  else
  if (2 == RelayServer2Cfg::GetLogLevel())
  {
    logmask = LM_INFO | LM_NOTICE | LM_WARNING | LM_ERROR | LM_CRITICAL;
    logStream->SetDefaultMinLevelFilter(NLogg::LEVEL_MESSAGE);
  }
  else
  if (1 == RelayServer2Cfg::GetLogLevel())
  {
    logmask = LM_DEBUG | LM_INFO | LM_NOTICE | LM_WARNING | LM_ERROR | LM_CRITICAL;
    logStream->SetDefaultMinLevelFilter(NLogg::LEVEL_DEBUG);
  }
  ACE_LOG_MSG->priority_mask (logmask, ACE_Log_Msg::PROCESS);

  ACE_LOG_MSG->set_flags (ACE_Log_Msg::MSG_CALLBACK);
  ACE_LOG_MSG->clr_flags (ACE_Log_Msg::STDERR);
  ACE_LOG_MSG->msg_callback (logcb);

  ACE_ERROR((LM_INFO, ACE_TEXT("Relay server starting ...")));

  BaseChannelFactory<BaseChannel> channel_factory(0, 0);

  // IO Thread Pool for Channels, Acceptors, Connectors
  IOThreadPool tp("RelayServerIOThreadPool", logcb);

  NewClientVerifier ncv((Transport::IClientsVerifier*)verifier.Get());

  const bool packClientAddress = true;

  RelayChannelManager manager("RelayServerManager", tp, channel_factory, 
    CoordClient()->GetBackendAddressTranslator(), &factory, packClientAddress, &ncv, SvcId(), backendSvcid );

  if ( RelayServer2Cfg::GetTrackGameSessionStepPeriodThreshold() )
  {
    Transport::TServiceId gamesvcls("gamesvc");
    StrongMT<ITrafficTrackerFactory> spttf = new GameSvcTrafficTrackerFactory( gamesvcls, SvcId() );
    manager.RegisterTrafficTrackerFactory( gamesvcls, spttf );
  }

  //  'check connection activity timeout' используется для проверки keepalive клиентов
  //  см. RelayClientProtocol::check_activity()
  ACE_Time_Value timeout (RelayServer2Cfg::GetCheckConnectionActivityTimeout(), 0);
  manager.set_timeout (timeout);

  loglevel = RelayServer2Cfg::GetIOTerabitLogLevel();
  manager.set_log_level (loglevel);     // set log level

  //  init client acceptor
  TL::MessageBlockFactorySP client_mbf;
  if (!RelayServer2Cfg::GetClientMessageBlockHeapPerConnection())
  {
    client_mbf = TL::MessageBlockFactorySP(new TL::MessageBlockFactory("clients", RelayServer2Cfg::GetClientMessageBlockHeapDumpFreq()));
    client_mbf->threshold(TL::MBType::NOTYPE_BLOCK, RelayServer2Cfg::GetClientWriteBlockUseThreshold(), 
      RelayServer2Cfg::GetClientWriteBlockUseThresholdFilter(), RelayServer2Cfg::GetClientWriteBlockUseThresholdFilterSize(),
      RelayServer2Cfg::GetClientWriteBlockUseThresholdLogEveryone());
    client_mbf->threshold(TL::MBType::WRITE_BLOCK, RelayServer2Cfg::GetClientWriteBlockUseThreshold(), 
      RelayServer2Cfg::GetClientWriteBlockUseThresholdFilter(), RelayServer2Cfg::GetClientWriteBlockUseThresholdFilterSize(),
      RelayServer2Cfg::GetClientWriteBlockUseThresholdLogEveryone());
    client_mbf->threshold(TL::MBType::READ_BLOCK, RelayServer2Cfg::GetClientWriteBlockUseThreshold(), 
      RelayServer2Cfg::GetClientWriteBlockUseThresholdFilter(), RelayServer2Cfg::GetClientWriteBlockUseThresholdFilterSize(),
      RelayServer2Cfg::GetClientWriteBlockUseThresholdLogEveryone());
  }

  ClientProtocolFactory  frontend_factory ("RelayFrontendFactory", client_mbf, loglevel);
  ClientAcceptor  frontend_acceptor(tp, frontend_factory, manager);
  frontend_acceptor.set_log_level(loglevel);

  //  init backend acceptor
  TL::MessageBlockFactorySP backend_mbf;
  if (!RelayServer2Cfg::GetBackendMessageBlockHeapPerConnection())
  {
    backend_mbf = TL::MessageBlockFactorySP(new TL::MessageBlockFactory("all_backends", RelayServer2Cfg::GetBackendMessageBlockHeapDumpFreq()));
    backend_mbf->threshold(TL::MBType::NOTYPE_BLOCK, RelayServer2Cfg::GetBackendWriteBlockUseThreshold());
    backend_mbf->threshold(TL::MBType::WRITE_BLOCK, RelayServer2Cfg::GetBackendWriteBlockUseThreshold());
    backend_mbf->threshold(TL::MBType::READ_BLOCK, RelayServer2Cfg::GetBackendWriteBlockUseThreshold());
  }
  BackendProtocolFactory  backend_factory ("RelayBackendFactory", backend_mbf, loglevel);
  ChannelAcceptor  backend_acceptor(tp, backend_factory, manager);
  backend_acceptor.set_log_level(loglevel);

  // init backend connection manager
  SvcConnectionManager svcConnectionMngr(tp, backend_factory, manager, &manager);
  manager.setSvcConnectionManager(&svcConnectionMngr);

  ACE_Time_Value time_begin = ACE_OS::gettimeofday ();

  // start with IOThreadPool with N threads
  int threads = RelayServer2Cfg::GetThreads();
  if (threads < 0)
    threads = 0;

  if (0 == threads)
  {
#if defined( NV_WIN_PLATFORM )
    SYSTEM_INFO sysinfo;
    GetSystemInfo( &sysinfo );
    threads = sysinfo.dwNumberOfProcessors;
#elif defined( NV_LINUX_PLATFORM )
    threads = sysconf(_SC_NPROCESSORS_CONF);
#endif
  }

   //  Logging configuration
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("Relay process id [%d]"), ACE_OS::getpid()));
    ACE_ERROR((LM_INFO, ACE_TEXT("==============================")));
    ACE_ERROR((LM_INFO, ACE_TEXT("Relay configuration:")));
    ACE_ERROR((LM_INFO, ACE_TEXT("client listen address: %s"), frontendListenAddr.c_str()));
    ACE_ERROR((LM_INFO, ACE_TEXT("backend listen address: %s"), backendListenAddr.c_str()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_threads: %d"), threads));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_keepalive_timeout: %d sec"), RelayServer2Cfg::GetKeepAliveTimeout()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_newconnection_timeout: %d sec"), RelayServer2Cfg::Get2NewConnectionTimeout()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_check_connection_activity_timeout: %d sec"), RelayServer2Cfg::GetCheckConnectionActivityTimeout()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_loglevel: %d"), RelayServer2Cfg::GetLogLevel()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_ioterabit_loglevel: %d"), RelayServer2Cfg::GetIOTerabitLogLevel()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_so_rcvbuf: %d bytes"), RelayServer2Cfg::GetBackendSoRcvBuf()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_so_sndbuf: %d bytes"), RelayServer2Cfg::GetBackendSoSndBuf()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_readsize: %d bytes"), RelayServer2Cfg::GetBackendReadSize()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_so_rcvbuf: %d bytes"), RelayServer2Cfg::GetClientSoRcvBuf()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_so_sndbuf: %d bytes"), RelayServer2Cfg::GetClientSoSndBuf()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_readsize: %d bytes"), RelayServer2Cfg::GetClientReadSize()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_write_complete_notify: %d"), RelayServer2Cfg::GetClientWriteCompleteNotify()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_write_complete_notify: %d"), RelayServer2Cfg::GetBackendWriteCompleteNotify()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_disable_nagle_algorithm: %d"), RelayServer2Cfg::GetClientDisableNagleAlgorithm()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_disable_nagle_algorithm: %d"), RelayServer2Cfg::GetBackendDisableNagleAlgorithm()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_output_queue_limit: %d"), RelayServer2Cfg::GetClientOutputQueueLimit()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_message_block_heap_dump_freq: %d"), RelayServer2Cfg::GetClientMessageBlockHeapDumpFreq()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_message_block_heap_per_connection: %d"), RelayServer2Cfg::GetClientMessageBlockHeapPerConnection()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_message_block_write_use_threshold: %d"), RelayServer2Cfg::GetClientWriteBlockUseThreshold()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_message_block_heap_dump_freq: %d"), RelayServer2Cfg::GetBackendMessageBlockHeapDumpFreq()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_message_block_heap_per_connection: %d"), RelayServer2Cfg::GetBackendMessageBlockHeapPerConnection()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_message_block_write_use_threshold: %d"), RelayServer2Cfg::GetBackendWriteBlockUseThreshold()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_track_input: %d"), RelayServer2Cfg::GetClientTrackInput()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_input_notification_threshold: %d"), RelayServer2Cfg::GetClientInputNotificationThreshold()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_tracked_service: %s"), RelayServer2Cfg::GetClientTrackedSvc().c_str()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_report_amount_of_read_bytes: %d"), RelayServer2Cfg::GetBackendReportAmountOfReadBytes()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_backend_report_amount_of_written_bytes: %d"), RelayServer2Cfg::GetBackendReportAmountOfWrittenBytes()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_report_amount_of_read_bytes: %d"), RelayServer2Cfg::GetClientReportAmountOfReadBytes()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_client_report_amount_of_written_bytes: %d"), RelayServer2Cfg::GetClientReportAmountOfWrittenBytes()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_keep_client_connection_on_wrong_seq_num_error: %d"), RelayServer2Cfg::GetKeepClientConnectionOnWrongSeqNumError()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_open_backend_channel_timeout: %d"), RelayServer2Cfg::GetOpenBackendChannelTimeout()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_svcping_logging_freq: %d"), RelayServer2Cfg::GetSvcPingLoggingFreq()));
    ACE_ERROR((LM_INFO, ACE_TEXT("rs2_service_role: %s"), RelayServer2Cfg::GetSvcRole().c_str()));
    ACE_ERROR((LM_INFO, ACE_TEXT("==============================")));
  }

  string hostCcuCounterName;
  Network::GetHost( frontendListenAddr, hostCcuCounterName );
  NDebug::DebugVar<volatile int> ccuCounter( hostCcuCounterName.c_str(), SvcId().c_str() );
  RegisterPerfCounter( hostCcuCounterName, (NDebug::IDebugVar*)&ccuCounter, true );

  int rc = -1;
  rc = tp.start (threads);
  if (0 == rc)
  {
    rc = manager.open ();
    if (0 == rc)
    {
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("Start client acceptor at %s"), frontendListenAddr.c_str()));
      TRB_Sock_Addr frontend_listen_addr = TRB_Sock_Addr(ACE_INET_Addr( frontendListenAddr.c_str()));
      rc = frontend_acceptor.start (frontend_listen_addr.get_ace_addr(), 20);
      if (0 == rc)
      {
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("Start backend acceptor at %s"), backendListenAddr.c_str()));
        TRB_Sock_Addr relay2client_listen_addr_ = TRB_Sock_Addr(ACE_INET_Addr(backendListenAddr.c_str()));
        rc = backend_acceptor.start(relay2client_listen_addr_.get_ace_addr(), 20);
        if (0 == rc)
        {
          ACE_ERROR((LM_INFO, ACE_TEXT("Relay server started successfully")));

          unsigned long stepCount = 0;

          //  step client verifier
          ACE_Time_Value tv( 0, CustomParams().sleep * 1000 );
          while(0 == rc)
          {
            rc = justAnEventToWait.wait(&tv, 0);
            if (rc < 0 && ETIME == errno)
            {
              BaseService::PollInternal();

              if (!stepCount)
              {
                verifier->Step();
                ccuCounter.SetValue(verifier->ccu());
              }

              ++stepCount;
              if (stepCount > 10)
                stepCount = 0;

              rc = 0;
            }
            else
            if ( !_isRunning || ( 0 == rc ) )
              //  event in signaled state
              rc = 1;
          }

          rc = 0;
        }
      }
      else
      {
        ACE_ERROR((LM_CRITICAL, ACE_TEXT("Client acceptor's start is FAILED(addr = %s)"), frontendListenAddr.c_str()));
      }
    }
    else
    {
      ACE_ERROR ((LM_CRITICAL, ACE_TEXT ("Channel manager.open failed")));
    }
  }
  else
  {
    ACE_ERROR ((LM_CRITICAL, ACE_TEXT ("Thread pool start is FAILED(threads=%d)"), threads));
  }

  if (0 == rc)
    ACE_ERROR((LM_INFO, ACE_TEXT("Relay server stopping ...")));

  // Initiate cancelation of  all pending AIO 
  frontend_acceptor.cancel();    // Cancel Acceptor
  manager.close ();       // Cancel all active connections

  frontend_acceptor.wait ();       // Wait Acceptor
  manager.wait ();        // Wait for termination of all active connections

  UnregisterPerfCounter( hostCcuCounterName );

  tp.stop ();

  if (rc != 0)
  {
    ACE_ERROR ((LM_ERROR, ACE_TEXT ("Relay server start is FAILED")));
  }
  else
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("Relay server stopped")));
  }
}

} //namespace Relay
