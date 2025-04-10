// $Id: T_Test.cpp,v 1.15 2002/05/15 02:38:14 pgontla Exp $

#include "test_config.h"


#include "ace/Signal.h"
#include "ace/Service_Config.h"
#include "ace/Get_Opt.h"
//#include "ace/streams.h"

#include "TP_ReactorTask.h"
#include "TConnectionManager.h"
#include "TAcceptorConnector.h"

static TestCfg cfg;

static char data[] =
  "GET / HTTP/1.1\r\n"
  "Accept: */*\r\n"
  "Accept-Language: C++\r\n"
  "Accept-Encoding: gzip, deflate\r\n"
  "User-Agent: TPReactor_Test/1.0 (non-compatible)\r\n"
  "Connection: Keep-Alive\r\n"
  "\r\n" ;


// *************************************************************

class Receiver : public TConnection
{
public:
    Receiver () {}
    virtual ~Receiver () {};

    virtual const ACE_TCHAR * get_name (void) const
    {
        return "Receiver"; 
    }

    virtual int  on_open () 
    {
        ACE_Message_Block * mb = this->alloc_msg ();
        if (mb == 0)
        {
            return -1;
        }
        return this->start_read (*mb);
    }

    virtual int on_read_finished (ACE_Message_Block & mb,
                                  int error,
                                  int xfer_bytes)
    {
        if (error !=0 || xfer_bytes == 0)
        {
            return -1;
        }
        return this->start_write (mb);
    }

    virtual int on_write_finished (ACE_Message_Block & mb,
                                   int error)
    {
        if (error !=0)
        {
            return -1;
        }
        mb.reset ();
        return this->start_read (mb);
    }
};

class Sender : public TConnection
{
public:
    Sender () {}
    virtual ~Sender () {};

    virtual const ACE_TCHAR * get_name (void) const
    {
        return "Sender"; 
    }

    virtual int  on_open () 
    {
        ACE_Message_Block * mb = this->alloc_msg ();
        if (mb == 0 )
        {
            return 0;
        }

        mb->copy (data );
        mb->reset ();
        mb->wr_ptr (cfg.s_blksize ());

        return this->start_write (*mb);
    }

    virtual int on_read_finished (ACE_Message_Block & mb,
                                  int error,
                                  int xfer_bytes)
    {
        if (error !=0 || xfer_bytes == 0)
        {
            return -1;
        }

        mb.reset ();

        mb.copy (data );
        mb.reset ();
        mb.wr_ptr (cfg.blksize());
        
        return this->start_write (mb);
    }

    virtual int on_write_finished (ACE_Message_Block & mb,
                                   int error)
    {
        if (error !=0)
        {
            return -1;
        }
        mb.reset ();
        return this->start_read (mb);
    }
};

template class TConnectionFactory_T<Receiver>;
template class TConnectionFactory_T<Sender>;


typedef  TConnectionFactory_T<Receiver> RecvFactory;
typedef  TConnectionFactory_T<Sender>   SendFactory;



int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("TM_Test"));

  if (cfg.parse_args (argc, argv) < 0)
    return -1;

  disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
  disable_signal (SIGPIPE, SIGPIPE);
  disable_signal (SIGIO, SIGIO);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("FD_SETSIZE=%d ACE_FDSETSIZE=%d\n"),
              FD_SETSIZE,
              ACE_FD_SETSIZE));

  ACE_DEBUG ((LM_DEBUG,
             "s_blksize=%u r_blksize=%u win_size=%u\n",
              cfg.s_blksize(),
              cfg.r_blksize(),
              cfg.w_size()));


  int rc = 0;

  TP_ReactorTask     task1(cfg);
  RecvFactory        r_factory;
  SendFactory        s_factory;
  TConnectionManager r_mgr (task1, "RManager");
  TConnectionManager s_mgr (task1, "SManager");

  TAcceptor  acceptor (r_factory, r_mgr);
  TConnector connector(s_factory, s_mgr);
  


  ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
  ACE_Time_Value time_end = ACE_OS::gettimeofday ();
  ACE_Time_Value time_run;

  if (task1.start () == 0)
    {
      if (cfg.both() != 0 || cfg.connections () == 0) // Acceptor
        {
          if (acceptor.start (ACE_INET_Addr (cfg.listen_port())) == 0)
            rc = 1;
        }
      
      if (cfg.both() != 0 || cfg.connections () > 0) // Connector
        {
          ACE_INET_Addr addr;

          addr.set (cfg.connect_port(), cfg.connect_host());

          rc += connector.start (addr, cfg.connections ());
        }

      time_begin = ACE_OS::gettimeofday ();

      if (rc > 0)
        {
          task1.enable_event_loop();
          
          ACE_Time_Value  sleep_time (cfg.seconds());
           
          while ( sleep_time != ACE_Time_Value::zero)
            {
              ACE_Countdown_Time countdown ( & sleep_time );

              ACE_OS::sleep (sleep_time );
            }

          if (cfg.seconds() == 0)
            {
              // comment this later
              char c;
              cout << "Press any key to stop=>" << flush;
              cin.clear ();
              cin >> c;
            }
        }
    }

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

  task1.stop ();
  
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stop Connector/Senders: connections_=%d\n"),
              s_mgr.get_number_connections ()));
  connector.stop ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stop Acceptor/Receivers:connections_=%d\n"),
              r_mgr.get_number_connections()));
  acceptor.stop ();
  
  s_mgr.stop ();
  r_mgr.stop ();

  
  task1.reactor()->close();

   ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stopped Connector/Senders: connections_=%d\n"),
              s_mgr.get_number_connections ()));
  //connector.stop ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stopped Acceptor/Receivers:connections_=%d\n"),
              r_mgr.get_number_connections()));
  //acceptor.stop ();


  time_end = ACE_OS::gettimeofday ();
  time_run = time_end - time_begin;

  s_mgr.print_statistic ();
  r_mgr.print_statistic ();

 ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Threads = %d BlkSize=%d\n"),
              cfg.threads(),
              cfg.blksize()));

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Connections: Max=%d  S=%d R=%d \n"),
              cfg.connections (),
              s_mgr.get_peak_connections(),
              r_mgr.get_peak_connections()));


  float  fsec = (float)(time_run.msec()/1000);
  double fspeed = ((float) s_mgr.get_total_snd()
                  +(float) s_mgr.get_total_rcv()
                  +(float) r_mgr.get_total_snd()
                  +(float) r_mgr.get_total_rcv()
                  );

  if ( fsec > 0.1 )
    fspeed /= fsec; 

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Effective run time = %f sec\n"),
              fsec));


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Effective bytes/sec = %f\n"),
              fspeed));

 
  ACE_END_TEST;

  return 0;
}
