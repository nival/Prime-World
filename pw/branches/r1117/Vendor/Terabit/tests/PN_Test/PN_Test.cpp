/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
**
**
**********************************************************************/

// ============================================================================
/**
 *  @file PN_Test.cpp
 *
 *  PN_Test.cpp
 *
 *  This program illustrates how the TRB_Proactor can be used to
 *  implement an application that does various asynchronous
 *  operations.
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"
//#include "ace/Countdown_Time.h"

#include "ARWConnection.h"

static TestCfg cfg;

static ACE_TCHAR complete_message[] =
  ACE_TEXT ("GET / HTTP/1.1\r\n")
  ACE_TEXT ("Accept: */*\r\n")
  ACE_TEXT ("Accept-Language: C++\r\n")
  ACE_TEXT ("Accept-Encoding: gzip, deflate\r\n")
  ACE_TEXT ("User-Agent: P_Test /1.0 (non-compatible)\r\n")
  ACE_TEXT ("Connection: Keep-Alive\r\n")
  ACE_TEXT ("\r\n");

// *************************************************************
//   Receiver 
// *************************************************************

class RcvProtocol : public PConnectionProtocol
{
public:
   
  RcvProtocol(PConnection * connection)
    : PConnectionProtocol (connection)
    {;}

  virtual ~RcvProtocol() 
    {;}

protected:
    virtual void on_start ();
    virtual void on_read_finished (const char *data,
                                   size_t bytes_transferred,
                                   int  error);
          
    virtual void on_write_finished (const char *data,
                                    size_t bytes_transferred,
                                    int  error);
};

void RcvProtocol::on_start ()
{
   this->read();
}

void
RcvProtocol::on_read_finished (const char *data,
                               size_t bytes_transferred,
                               int  error)
{
  if (bytes_transferred == 0 || error != 0)
  {
    return;
  }
    
  // emulate long callback
  do_delay (cfg.delay());  // delay milliseconds

  this->write(data, bytes_transferred);

  //u_int blksize = this->get_connection()->config().r_blksize();
  //u_int winsize = this->get_connection()->config().w_size();

  //// flow control
  //if ((u_long)(this->get_connection()->get_total_rcv () - 
  //             this->get_connection()->get_total_snd () > winsize))
  //  return; 
  //        
  //this->read();
}

void
RcvProtocol::on_write_finished (const char *data,
                               size_t bytes_transferred,
                               int  error)
{

  ////u_int blksize = this->get_connection()->config().r_blksize();
  //u_int winsize = this->get_connection()->config().w_size();

  //// flow control
  //if ((u_long)(this->get_connection()->get_total_rcv () - 
  //             this->get_connection()->get_total_snd () > winsize))
  //  return; 
          
  this->read();
}

// *******************************************
//   Sender
// *******************************************
class SndProtocol : public PConnectionProtocol
{
public:
   
  SndProtocol(PConnection * connection)
    : PConnectionProtocol (connection)
    {
      ACE_OS::memset(out_msg_, 0, sizeof(out_msg_));
      ACE_OS::strcpy(out_msg_, complete_message);
    }

  virtual ~SndProtocol() 
    {;}

    
protected:
    virtual void on_start ();
    virtual void on_read_finished (const char *data,
                                   size_t bytes_transferred,
                                   int  error);
          
    virtual void on_write_finished (const char *data,
                                    size_t bytes_transferred,
                                    int  error);
private:
   char out_msg_[1024];
};

void 
SndProtocol::on_start ()
{
   this->read();   // full duplex

   this->write(out_msg_, sizeof(out_msg_));
}
void
SndProtocol::on_read_finished (const char *data,
                               size_t bytes_transferred,
                               int  error)
{
  if (bytes_transferred == 0 || error != 0)
  {
    return;
  }
  
  this->read ();

}

void
SndProtocol::on_write_finished (const char *data,
                                size_t bytes_transferred,
                                int  error)
{
  if (bytes_transferred == 0 || error != 0)
  {
    return;
  }
  this->write(out_msg_, sizeof(out_msg_));

  //this->on_start (); // full duplex 
  //this->read();        // half duplex
}

// *************************************************************
//
// *************************************************************

class RecvFactory : public PConnectionFactory
{
public:
  virtual PConnection*  create_connection(PConnectionManager & /*manager*/)
    {
      PConnection * p = 0;
      ACE_NEW_RETURN (p, ARWConnection, 0);
      return p;
    }
  virtual void destroy_connection  (PConnection * connection) 
    {
      delete connection;
    }

  virtual PConnectionProtocol * create_protocol(PConnection * connection)
    {
       PConnectionProtocol * p = 0;
       ACE_NEW_RETURN (p, RcvProtocol (connection), 0);
       return p;
    }

  virtual void destroy_protocol (PConnectionProtocol * protocol) 
    { 
      delete protocol;
    }


};

class SendFactory : public PConnectionFactory
{
public:
  virtual PConnection*  create_connection(PConnectionManager & /*manager*/)
    {
      PConnection * p = 0;
      ACE_NEW_RETURN (p, ARWConnection, 0);
      return p;
    }
  virtual void destroy_connection  (PConnection * connection) 
    {
      delete connection;
    }

  virtual PConnectionProtocol * create_protocol(PConnection * connection)
    {
       PConnectionProtocol * p = 0;
       ACE_NEW_RETURN (p, SndProtocol (connection), 0);
       return p;
    }

  virtual void destroy_protocol (PConnectionProtocol * protocol) 
    { 
      delete protocol;
    }

};

// *************************************************************
//   Configuration helpers
// *************************************************************
int
run (int argc, ACE_TCHAR *argv[])
{
    int rc = 0;

    ProactorTask task1(cfg);
    if (task1.start () != 0)
    {
        task1.stop ();
        return -1;
    }
    
    task1.enable_event_loop();
    
    RecvFactory r_factory;
    SendFactory s_factory;

    PConnectionManager r_manager (task1, r_factory,"R_Manager");
    PConnectionManager s_manager (task1, s_factory,"S_Manager");

    ACE_Time_Value timeout (cfg.timeout(), 0);
    r_manager.set_timeout (timeout);
    s_manager.set_timeout (timeout);

    Acceptor  acceptor  (r_manager);
    Connector connector (s_manager);

    TRB_Sock_Addr listen_addr;
    TRB_Sock_Addr connect_addr;
    cfg.get_addresses (listen_addr, connect_addr);

    ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
    ACE_Time_Value time_end = ACE_OS::gettimeofday ();
    ACE_Time_Value time_run;

    if (cfg.both() != 0 || cfg.connections () == 0) // Acceptor
    {
        // Simplify, initial read with zero size
        if (acceptor.start (listen_addr.get_ace_addr ()) == 0)
            rc = 1;
    }

    if (cfg.both() != 0 || cfg.connections () > 0) // Connector
    {
        rc += connector.start (connect_addr.get_ace_addr (),
                               cfg.connections ());
    }
    

    if (rc > 0)
    {
        //task1.enable_event_loop();
            
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
                     << "\n3  -stop  senders"
                     << "\n4  -stop  receivers"
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
                    s_manager.cancel ();
                    while (!s_manager.is_safe_to_delete ())
                    {
                       task1.wait_signal ();
                    }
                    break;
                case '4':
                    r_manager.cancel ();
                    while (!r_manager.is_safe_to_delete ())
                    {
                       task1.wait_signal ();
                    }
                    break;
                case 'Q':
                    flgExit = true;
                    break;
                case 'P':
                    break;
                }//switch
                cout << "\n*** Connector: PendingConnects="
                    << connector.get_pending_count ()
                    << " Senders="
                    << s_manager.get_number_connections ()
                    << "\n*** Acceptor: PendingAccepts="
                    << acceptor.get_pending_count ()
                    << " Receivers="
                    << r_manager.get_number_connections ();
            }//for
        }//if cfg.seconds
    }//if rc > 0

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) *** Cancel Acceptor: PendingOP=%d Receivers=%d\n"),
                acceptor.get_pending_count (),  // number_pending_accepts
                r_manager.get_number_connections ()
                ));

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) *** Cancel Connector: PendingOP=%d Senders=%d\n"),
                connector.get_pending_count (),  // number_pending_connects
                s_manager.get_number_connections ()
                ));
     
    // Cancel all pending AIO on
    // Connector, Acceptor, all Senders, all Receivers
    acceptor.cancel  ();
    connector.cancel ();

    s_manager.cancel ();
    r_manager.cancel ();
 
    acceptor.wait ();
    connector.wait ();

    while (!s_manager.is_safe_to_delete () ||
           !r_manager.is_safe_to_delete () )
    {
        task1.wait_signal ();
    }

    time_end = ACE_OS::gettimeofday ();
    time_run = time_end - time_begin;

    cout << "\n*** Connector: PendingConnects="
        << connector.get_pending_count ()
        << " Senders="
        << s_manager.get_number_connections ()
        << "\n*** Acceptor: PendingAccepts="
        << acceptor.get_pending_count ()
        << " Receivers="
        << r_manager.get_number_connections ()
        << endl;

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

    task1.stop ();
     

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) *** Stop Connector: PendingOP=%d Senders=%d\n"),
                connector.get_pending_count (), // number_pending_connects
                s_manager.get_number_connections ()
                ));
     
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) *** Stop Acceptor: PendingOP=%d Receivers=%d\n"),
                acceptor.get_pending_count (),  //number_pending_accepts
                r_manager.get_number_connections ()
                ));


    //Print statistic
    s_manager.print_statistic ();
    r_manager.print_statistic ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Threads = %d BlkSize=%d\n"),
                cfg.threads(),
                cfg.blksize()));

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Connections: Max=%d  S=%d R=%d \n"),
                cfg.connections (),
                s_manager.get_peak_connections(),
                r_manager.get_peak_connections()));


    float  fsec = (float)(time_run.msec()/1000);
    double fspeed = ((float) s_manager.get_total_snd()
                    +(float) s_manager.get_total_rcv()
                    +(float) r_manager.get_total_snd()
                    +(float) r_manager.get_total_rcv()
                    );

    if ( fsec > 0.1 )
        fspeed /= fsec; 

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Effective run time = %f sec\n"),
                fsec));


    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Effective bytes/sec = %f\n"),
                fspeed));

    return 0;
}

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("PN_Test"));

  if (cfg.parse_args (argc, argv) < 0)
    return -1;

  disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
  disable_signal (SIGPIPE, SIGPIPE);
  disable_signal (SIGIO, SIGIO);

  //ACE_DEBUG ((LM_DEBUG,
  //            ACE_TEXT ("FD_SETSIZE=%d ACE_FDSETSIZE=%d\n"),
  //            FD_SETSIZE,
  //            ACE_FD_SETSIZE));

  ACE_DEBUG ((LM_DEBUG,
             "s_blksize=%u r_blksize=%u win_size=%u\n",
              cfg.s_blksize(),
              cfg.r_blksize(),
              cfg.w_size()));


  int rc = run (argc,argv);

  ACE_END_TEST;

  return rc;
}

