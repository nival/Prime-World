/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  @file ex7a.cpp  
**  
**  ex7a.cpp
**   
**  This program illustrates how the TRB_Proactor can be used to
**  implement an application that does various asynchronous
**  operations.
**  
**  @author Alexander Libman <libman@terabit.com.au>
**********************************************************************/

#include "Cfg.h"

#include "IOTerabit/TcpChannel.h"
#include "IOTerabit/ChannelManager.h"
#include "IOTerabit/ChannelAcceptor.h"
#include "IOTerabit/ChannelConnector.h"
#include "IOTerabit/ProtocolFactory_T.h"
#include "ChatProtocol.h"

using namespace Terabit;

static TestCfg cfg;

static ACE_TCHAR complete_message[1024] =
  ACE_TEXT ("Message                            ");



// *******************************************
//   Sender
// *******************************************
class SndProtocol : public Protocol
{
public:
   
    SndProtocol(ProtocolFactory& factory)
        : Protocol (factory)
    {
    }

    virtual ~SndProtocol() 
    {
    }
    
    virtual void reset ()
    {
    }

    virtual int on_channel_opened (AsynchChannel *channel)
    {
        //channel->set_duplex_mode (false);
        channel->enable_read ();                 // this is default
        channel->enable_write_notifications ();  // this is not
        return this->on_write_completed (channel);
    }
      
    
    virtual int on_write_completed (AsynchChannel *channel)
    {
        return channel->start_write(complete_message,
                                    sizeof(complete_message));
    }

    virtual int on_read_completed (AsynchChannel *channel,
                                   const char    *data,
                                   size_t         length)
    {
        return length;  // all data consumed
    }

      
    virtual int on_timeout (AsynchChannel *channel,
                            const void    *arg)
    {
        return -1;
    }

    virtual int check_activity (AsynchChannel *channel,
                               const ACE_Time_Value&  last_op_time)
    {
        return 0;
    }
};
// *************************************************************
//
// *************************************************************
typedef ProtocolFactory_T<SndProtocol> SndFactory;
typedef ChatProtocol                   RcvFactory;
// *************************************************************
//   Configuration helpers
// *************************************************************
int
run (int argc, ACE_TCHAR *argv[])
{
    int rc = 0;

    // factory for TcpChannels
    TcpChannelFactory channel_factory;
    channel_factory.set_pool_size (cfg.connections()*2, // min cache size
                                   (size_t) -1);        // max cache size
    

    // IO Thread Pool  for Channels and Connectors
    IOThreadPool task1 ("IOThreadPool-1",           // name for logging
                        cfg.proactor_type (),       // proactor type
                        cfg.leader_type () ,        // shared | dedicated
                        cfg.demultiplexors (),      // number or proactors
                        cfg.max_aio_operations (),  // max num aio or 0
                        cfg.sig_num ());            // for legacy

    // IO Thread Pool  for Acceptors
    IOThreadPool task2 ("IOThreadPool-2",           // name for logging
                        cfg.proactor_type (),       // proactor type
                        cfg.leader_type () ,        // shared | dedicated
                        1,                          // number or proactors
                        cfg.max_aio_operations (),  // max num aio or 0
                        cfg.sig_num ());            // for legacy

    // Worker thread pool for process requests
    JobThreadPool task3   ("JobPool");              // name


    // Channel Manager
    ChannelManager manager("Manager",          // name for logging
                           task1,              // IOThreadPool for channels
                           channel_factory);   // factory of channels

    ACE_Time_Value timeout (cfg.timeout(), 0);
    manager.set_timeout (timeout);                  // set check timeout
    manager.set_log_level (cfg.loglevel());         // set log level
    manager.open ();                                // open manager
 
    // Protocol Factories (user supplied)
    RcvFactory  r_factory (task3,                   // worker thread pool
                           "RcvFactory",            // name for logging
                           cfg.loglevel ());        // log level
    SndFactory  s_factory ("SndFactory",            // name for logging
                           cfg.loglevel ());        // log level

    // Acceptor
    ChannelAcceptor  acceptor  (task2,              // IOThreadPool for accepting
                                r_factory,          // factory of protocols
                                manager);           // channel manager

    // Connector
    ChannelConnector connector (task1,              // IOThreadPool for connecting
                                s_factory,          // factory of protocols
                                manager);           // channel manager

    acceptor.set_log_level  (1);                    // cfg.loglevel ());
    connector.set_log_level (1);                    // cfg.loglevel ());
    
    TRB_Sock_Addr listen_addr;
    TRB_Sock_Addr connect_addr;
    cfg.get_addresses (listen_addr, connect_addr);

    ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
    ACE_Time_Value time_end = ACE_OS::gettimeofday ();
    ACE_Time_Value time_run;

    // start with IOThreadPool with N threads
    if (task1.start (cfg.threads ()) != 0)
    {
        return -1;
    }
    if (task2.start (1) != 0)
    {
        return -1;
    }

    if (task3.start (1) != 0)
    {
        return -1;
    }


    std::cout << "========= Start Acceptor ================" 
        << std::endl;

    // start listen
    if (acceptor.start (listen_addr.get_ace_addr (), 20) == 0)
    {
        rc = 1;
    }

    time_begin = ACE_OS::gettimeofday ();
    
    std::cout << "========= Start Connecting ================" 
        << std::endl;
    // start M client connects
    for (u_int i = 0; i < cfg.connections (); ++i, ++rc)
    {
        if  (connector.start (connect_addr.get_ace_addr (),
                              (const void *) i) != 0)
        {
            break;
        }
    }

    ChannelManager::Statistic stat;


    if (rc > 0)
    {
        ACE_Time_Value  sleep_time (cfg.seconds());
            
        while ( sleep_time != ACE_Time_Value::zero)
        {
            ACE_Countdown_Time countdown ( & sleep_time );

            ACE_OS::sleep (sleep_time );
        }


        if (cfg.seconds () == 0)
        {
            bool flgExit = false;
            for (;!flgExit;)
            {
                char c;
                cout << "\nEnter:"
                     << "\n1 - stop  connector"
                     << "\n2 - stop  acceptor"
                     << "\n3  -stop  manager"
                     << "\nP - statistic"
                     << "\nQ   quit=>" 
                     << flush;
                cin.clear ();
                cin >> c;
                switch (toupper (c))
                {
                case '1':
                    connector.cancel();
                    connector.wait ();
                    break;
                case '2':
                    acceptor.cancel ();
                    acceptor.wait();
                    break;
                case '3':
                    manager.close ();
                    manager.wait ();
                    break;
                case 'Q':
                    flgExit = true;
                    break;
                case 'P':
                    break;
                }//switch
                manager.get_statistic(stat);
                cout << "\n*** Connector: PendingConnects="
                     << connector.get_pending_count ()
                     << "\n*** Acceptor: PendingAccepts="
                     << acceptor.get_pending_count ()
                     << "\n*** Channels: Current="
                     << stat.current_channels_
                     << " Peak="
                     << stat.peak_channels_
                     << " Total="
                     << stat.total_channels_
                     << "\n";                    
                    
            }//for
        }//if cfg.seconds
    }//if rc > 0

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) ******** Before Cancel And Wait *************\n")
        ACE_TEXT ("Acceptor: PendingOP=%d   Connector: PendingOP=%d\n"),
                acceptor.get_pending_count (),   // number_pending_accepts
                connector.get_pending_count ()   // number_pending_connects
                ));
    manager.print_statistic ();

    // Initiate cancelation of  all pending AIO 
    acceptor.cancel  ();    // Cancel Acceptor
    connector.cancel ();    // Cancel Connector
    manager.close ();       // Cancel all active connections

    task3.stop ();          // Stop Worker thread pool
    task3.purge ();         // 
    
    acceptor.wait ();       // Wait Acceptor
    connector.wait ();      // Wait Connector
    manager.wait ();        // Wait for termination of all active connections
    
    time_end = ACE_OS::gettimeofday ();
    time_run = time_end - time_begin;

   
    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) ******** After  Cancel And Wait *************\n")
        ACE_TEXT ("Acceptor: PendingOP=%d   Connector: PendingOP=%d\n"),
                acceptor.get_pending_count (),   // number_pending_accepts
                connector.get_pending_count ()   // number_pending_connects
                ));
    manager.print_statistic ();

    // Calclulate average transmission rate
    manager.get_statistic(stat);

    float  fsec   = (float)(time_run.msec()/1000);
    double fspeed1 = ((float) stat.total_snd_
                    +(float) stat.total_rcv_
                    );

    double fspeed2 = ((float) stat.total_w_
                    +(float) stat.total_r_
                    );

    if ( fsec > 0.1 )
    {
        fspeed1 /= fsec; 
        fspeed2 /= fsec; 
    }

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Effective run time = %f sec\n"),
                fsec));


    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Effective bytes/sec = %f   op/sec= %f\n"),
                fspeed1,
                fspeed2));

    
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Threads = %d BlkSize=%d\n"),
                cfg.threads(),
                cfg.blksize()));

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Stopping Thread Pools\n")));

    task3.stop ();          // Stop Worker thread pool
    task2.stop ();
    task1.stop ();
     
    return 0;
}

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("ex7a"));

  if (cfg.parse_args (argc, argv) < 0)
    return -1;

  // very important for POSIX, NO-OP for Windows
  BaseThreadPool::disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
  BaseThreadPool::disable_signal (SIGPIPE, SIGPIPE);
  BaseThreadPool::disable_signal (SIGIO, SIGIO);

  complete_message[sizeof(complete_message) - 2 ] = '\r';
  complete_message[sizeof(complete_message) - 1 ] = '\n';

  int rc = run (argc,argv);

  ACE_END_TEST;

  return rc;
}

