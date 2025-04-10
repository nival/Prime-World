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
 *  @file P_Test.cpp
 *
 *  P_Test.cpp
 *
 *  This program illustrates how the TRB_Proactor can be used to
 *  implement an application that does various asynchronous
 *  operations.
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"


#include "Cfg.h"
#include "PSession.h"

#include "ace/INET_Addr.h"
//#include "ace/Countdown_Time.h"

#include "Asynch_RW.h"

static TestCfg cfg;

static ACE_TCHAR complete_message[] =
  ACE_TEXT ("GET / HTTP/1.1\r\n")
  ACE_TEXT ("Accept: */*\r\n")
  ACE_TEXT ("Accept-Language: C++\r\n")
  ACE_TEXT ("Accept-Encoding: gzip, deflate\r\n")
  ACE_TEXT ("User-Agent: P_Test /1.0 (non-compatible)\r\n")
  ACE_TEXT ("Connection: Keep-Alive\r\n")
  ACE_TEXT ("\r\n");


#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class TRB_Asynch_Acceptor<PSession>;
template class TRB_Asynch_Connector<PSession>;
template class TRB_Asynch_RW<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>;
template class TRB_Asynch_RW_Stream<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate TRB_Asynch_Acceptor<PSession>
#pragma instantiate TRB_Asynch_Connector<PSession>
#pragma instantiate TRB_Asynch_RW<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>
#pragma instantiate TRB_Asynch_RW_Stream<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */



// *************************************************************
//   Receiver 
// *************************************************************

class Receiver : public PSession
{
public:
  Receiver  (void);
  ~Receiver (void);

  // Virtual from PSession
  virtual const ACE_TCHAR * get_name (void) const 
    {
       return ACE_TEXT("Receiver");
    }

  virtual void  cancel ();
  
  virtual int   is_safe_to_delete (void) const;

  /// This is called after the new connection has been accepted.
  virtual void open (ACE_HANDLE handle,
                     ACE_Message_Block &message_block);

  /**
   * @name AIO callback handling
   *
   * These methods are called by the framework
   */
  /// This is called when asynchronous <read> operation from the
  /// socket completes.
  virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

  /// This is called when an asynchronous <write> to the socket
  /// completes.
  virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);


private:
  int initiate_read_stream  (ACE_Message_Block * mb);
  int initiate_write_stream (ACE_Message_Block * mb);

  Asynch_RW_Stream  stream_;
};

// ***************************************************
Receiver::Receiver ()
: PSession ()
{
}

Receiver::~Receiver (void)
{
}

void
Receiver::cancel ()
{
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex());
    this->stream_.cancel_and_close();
}

int 
Receiver::is_safe_to_delete (void) const
{
    return !this->has_pending_io();
}

void
Receiver::open (ACE_HANDLE handle, ACE_Message_Block &)
{
    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        if (this->stream_.open (*this, 
            handle,
            0, // completion key,
            this->task().get_proactor(this->index()),
            1) == -1)
        {
            ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%t) %s %p\n"),
                this->get_name(),
                ACE_TEXT ("TRB_Asynch_RW_Stream::open")));
        }
        else
            this->initiate_read_stream (0);

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

int
Receiver::initiate_read_stream (ACE_Message_Block * mb)
{
    if (this->get_ref_cnt_r() != 0)
    {
        ACE_Message_Block::release(mb);
        return 0;
    }

    u_int blksize = this->config().r_blksize();
    u_int winsize = this->config().w_size();
    // flow control
    if ((u_long)(this->total_rcv_ - this->total_snd_) > winsize)
    {
        ACE_Message_Block::release(mb);
        return 0;
    }

    if (mb == 0)
    {
        ACE_NEW_RETURN (mb, ACE_Message_Block (blksize), -1);
    }  

    mb->reset();  

    // Inititiate read
    if (this->stream_.read (*mb, mb->space()) == -1)
    {
        ACE_Message_Block::release(mb);
        this->stream_.cancel_and_close();
        return -1;
    }

    this->ref_cnt_r_++;
    this->total_r_++;
    return 0;
}

int
Receiver::initiate_write_stream (ACE_Message_Block  * mb)
{
    if (mb == 0)
    {
        ACE_Message_Block::release(mb);
        return 0;
    }
    size_t nbytes = mb->length();

    if (nbytes == 0)
    {
        ACE_Message_Block::release(mb);
        return 0;
    }

    if (this->stream_.write (*mb, nbytes) == -1)
    {
        ACE_Message_Block::release(mb);
        this->stream_.cancel_and_close();
        return -1;
    }

    this->ref_cnt_w_++;
    this->total_w_++;
    return 0;
}

void
Receiver::handle_read_stream (const TRB_Asynch_Read_Stream::Result &result)
{
    this->trace_read_completion (result);

    // emulate long callback
    do_delay (cfg.delay());  // delay milliseconds

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex () );

        this->ref_cnt_r_--;

        ACE_Message_Block & mb = result.message_block ();

        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            this->initiate_write_stream (&mb);

            this->initiate_read_stream (0);
        }
        else
        {
            mb.release ();
        }

        if (result.error () != 0)
            this->stream_.cancel_and_close ();

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

void
Receiver::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
    this->trace_write_completion (result);

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        this->ref_cnt_w_--;

        ACE_Message_Block & mb = result.message_block ();

        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            this->initiate_read_stream (&mb);
        }
        else
        {
            mb.release ();
            this->stream_.cancel_and_close ();
        }

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

// *******************************************
//   Sender
// *******************************************
class Sender : public PSession
{
public:
  Sender  (void);
  ~Sender (void);

  // Virtual from PSession
  virtual const ACE_TCHAR * get_name (void) const 
    {
       return ACE_TEXT("Sender");
    }

  virtual void  cancel ();
  
  virtual int   is_safe_to_delete (void) const;

  /// This is called after the new connection has been accepted.
  virtual void open (ACE_HANDLE handle,
                     ACE_Message_Block &message_block);

  /**
   * @name AIO callback handling
   *
   * These methods are called by the framework
   */
  /// This is called when asynchronous <read> operation from the
  /// socket completes.
  virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

  /// This is called when an asynchronous <write> to the socket
  /// completes.
  virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);


private:
  int initiate_read_stream  (ACE_Message_Block *mb);
  int initiate_write_stream (ACE_Message_Block *mb);

  Asynch_RW_Stream  stream_;
};

// ************************************************

Sender::Sender ()
: PSession   ()
{
}

Sender::~Sender (void)
{
}

void
Sender::cancel ()
{
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());
    this->stream_.cancel_and_close();
}

int 
Sender::is_safe_to_delete (void) const
{
    return !this->has_pending_io();
}


void
Sender::open (ACE_HANDLE handle, ACE_Message_Block &)
{
    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        if (this->stream_.open (*this, 
            handle,
            0, // completion key,
            this->task().get_proactor(this->index()),
            1) == -1)
        {
            ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%t) %s %p\n"),
                this->get_name(),
                ACE_TEXT ("TRB_Asynch_RW_Stream::open")));
        }
        else
        {
            this->initiate_read_stream (0);
            this->initiate_write_stream (0);
        }

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

int
Sender::initiate_write_stream (ACE_Message_Block * mb)
{
    u_int blksize = this->config().s_blksize();
    u_int limit   = this->config().xfer_limit();
    u_int winsize = this->config().w_size();

    if (limit != 0 && this->total_snd_ >= limit)
    {
        ACE_Message_Block::release(mb);
        return 0;
    }

    u_long delta = this->total_snd_- this->total_rcv_;
    if (delta > winsize)
    {
        ACE_Message_Block::release(mb);
        return 0;
    }

    if (mb == 0)
    {
        ACE_NEW_RETURN (mb, ACE_Message_Block (blksize), -1);
    }

    mb->reset ();
    mb->copy (complete_message);
    mb->wr_ptr(mb->base() + mb->size ());

    if (this->stream_.write (*mb, mb->length ()) == -1)
    {
        ACE_Message_Block::release(mb);
        this->stream_.cancel_and_close();
        return -1;
    }

    this->ref_cnt_w_++;
    this->total_w_++;
    return 0;
}

int
Sender::initiate_read_stream (ACE_Message_Block * mb)
{
    u_int blksize = this->config().r_blksize();
    u_int limit   = this->config().xfer_limit();

    if (limit != 0 && this->total_rcv_ >= limit)
    {
        ACE_Message_Block::release(mb);
        return 0;
    }

    if (this->get_ref_cnt_r() != 0 )
    {
        ACE_Message_Block::release(mb);
        return 0;
    }

    if (mb == 0)
        ACE_NEW_RETURN (mb, ACE_Message_Block (blksize), -1);

    mb->reset ();
    
    // Inititiate read
    if (this->stream_.read (*mb, mb->space ()) == -1)
    {
        ACE_Message_Block::release(mb);
        this->stream_.cancel_and_close();
        return -1;
    }

    this->ref_cnt_r_++;
    this->total_r_++;
    return 0;
}

void
Sender::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
    this->trace_write_completion (result);

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        this->ref_cnt_w_--;

        ACE_Message_Block & mb = result.message_block ();

        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            this->initiate_write_stream (&mb);
            this->initiate_read_stream(0);
        }
        else
        {
            mb.release ();
            this->stream_.cancel_and_close ();
        }

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

void
Sender::handle_read_stream (const TRB_Asynch_Read_Stream::Result &result)
{
    this->trace_read_completion (result);

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        this->ref_cnt_r_--;

        ACE_Message_Block & mb = result.message_block ();

        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            this->initiate_read_stream (&mb);
            this->initiate_write_stream (0);
        }
        else
        {
            this->stream_.cancel_and_close ();
            mb.release ();
        }
        
        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

class RecvFactory : public PSessionFactory
{
public:
    virtual PSession*  create_session(PSessionManager & /*manager*/)
    {
        PSession * p = 0;
        ACE_NEW_RETURN (p, Receiver, 0);
        return p;
    }
};

class SendFactory : public PSessionFactory
{
public:
    virtual PSession*  create_session(PSessionManager & /*manager*/)
    {
        PSession * p = 0;
        ACE_NEW_RETURN (p, Sender, 0);
        return p;
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

    RecvFactory r_factory;
    SendFactory s_factory;

    PSessionManager r_manager (task1, r_factory,"R_Manager");
    PSessionManager s_manager (task1, s_factory,"S_Manager");

    Acceptor  acceptor  (r_manager);
    Connector connector (s_manager);

    ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
    ACE_Time_Value time_end = ACE_OS::gettimeofday ();
    ACE_Time_Value time_run;

    if (task1.start () == 0)
    {
        task1.enable_event_loop();

        ACE_Time_Value timeout (cfg.timeout(), 0);
        r_manager.set_timeout (timeout);
        s_manager.set_timeout (timeout);

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
    }

    time_begin = ACE_OS::gettimeofday ();

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
                cout << "\nPress Q to stop=>" << flush;
                cin.clear ();
                cin >> c;
                switch (toupper (c))
                {
                case 'Q':
                    flgExit = true;
                    break;
                case 'P':
                    cout << "\n*** Connector: PendingConnects="
                        << connector.get_ref_cnt()
                        << " Senders="
                        << s_manager.get_number_connections ()
                        << "\n*** Acceptor: PendingAccepts="
                        << acceptor.get_ref_cnt()
                        << " Receivers="
                        << r_manager.get_number_connections ();
                break;
                }//switch
            }//for
        }//if cfg.seconds
    }//if rc > 0


    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) *** Cancel Connector: PendingOP=%d Senders=%d\n"),
                connector.get_ref_cnt(),  // number_pending_connects
                s_manager.get_number_connections ()
                ));
     
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) *** Cancel Acceptor: PendingOP=%d Receivers=%d\n"),
                acceptor.get_ref_cnt(),  // number_pending_accepts
                r_manager.get_number_connections ()
                ));

    // Cancel all pending AIO on
    // Connector, Acceptor, all Senders, all Receivers
    connector.cancel ();
    acceptor.cancel  ();
    s_manager.cancel ();
    r_manager.cancel ();
       

    while ( !connector.is_safe_to_delete () ||
            !acceptor.is_safe_to_delete  () ||
            !s_manager.is_safe_to_delete () ||
            !r_manager.is_safe_to_delete () 
            )
    {
        task1.wait_signal ();
    }

    time_end = ACE_OS::gettimeofday ();
    time_run = time_end - time_begin;


    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

    task1.stop ();
     

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) *** Stop Connector: PendingOP=%d Senders=%d\n"),
                connector.get_ref_cnt (), // number_pending_connects
                s_manager.get_number_connections ()
                ));
     
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) *** Stop Acceptor: PendingOP=%d Receivers=%d\n"),
                acceptor.get_ref_cnt (),  //number_pending_accepts
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
                ACE_TEXT ("(%t) Sessions: Max=%d  S=%d R=%d \n"),
                cfg.connections (),
                s_manager.get_peak_connections (),
                r_manager.get_peak_connections ()));


    float  fsec = (float)(time_run.msec()/1000);
    double fbspeed = ((float) s_manager.get_total_snd()
                    +(float) s_manager.get_total_rcv()
                    +(float) r_manager.get_total_snd()
                    +(float) r_manager.get_total_rcv()
                    );

    double fmspeed = ((float) s_manager.get_total_w()
                    +(float) s_manager.get_total_r()
                    +(float) r_manager.get_total_w()
                    +(float) r_manager.get_total_r()
                    );

    if ( fsec > 0.1 )
    {
        fbspeed /= fsec; 
        fmspeed /= fsec; 
    }
    	

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Effective run time = %f sec\n"),
                fsec));


    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) Effective bytes/sec = %f op/sec=%f\n"),
                fbspeed, 
                fmspeed));

    return 0; 
}

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
    ACE_START_TEST (ACE_TEXT ("P_Test"));


    if (cfg.parse_args (argc, argv) < 0)
        return -1;

    disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
    disable_signal (SIGPIPE, SIGPIPE);
    disable_signal (SIGIO, SIGIO);

    //ACE_DEBUG ((LM_DEBUG,
    //            ACE_TEXT ("FD_SETSIZE=%d ACE_FD_SETSIZE=%d\n"),
    //            FD_SETSIZE,
    //            ACE_FD_SETSIZE));

    ACE_DEBUG ((LM_DEBUG,
             "s_blksize=%u r_blksize=%u win_size=%u\n",
              cfg.s_blksize(),
              cfg.r_blksize(),
              cfg.w_size()));


    run(argc, argv);

    ACE_END_TEST;

    return 0;
}

