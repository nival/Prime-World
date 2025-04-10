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
*  @file F_Test.cpp
*
*  F_Test.cpp
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


template class TRB_Asynch_Acceptor <PSession>;
template class TRB_Asynch_Connector <PSession>;
template class TRB_Asynch_RW <TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>;
template class TRB_Asynch_RWT_Stream <TRB_Asynch_Read_Stream,
                                      TRB_Asynch_Write_Stream,
                                      TRB_Asynch_Transmit_File>;

template class TRB_Asynch_RW_File <TRB_Asynch_Read_File,TRB_Asynch_Write_File>;


static TestCfg cfg;


// *************************************************************
//   Receiver 
// *************************************************************

class Receiver : public PSession
{
public:
    Receiver  (void);
    virtual ~Receiver (void);

    // Virtual from PSession
    virtual const ACE_TCHAR * get_name (void) const 
    {
        return ACE_TEXT("Receiver");
    }



    /// This is called after the new connection has been accepted.
    virtual void open (ACE_HANDLE handle,
        ACE_Message_Block &message_block);

    /**
    * @name AIO callback handling
    *
    * These methods are called by the framework
    */
    virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

    virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);

    virtual void handle_write_file (const TRB_Asynch_Write_File::Result &result);

private:

    bool open_streams (ACE_HANDLE hsocket);

    u_long   offset_low_;
    u_long   offset_high_;
};

// ***************************************************
Receiver::Receiver ()
: PSession     ()
, offset_low_  (0)
, offset_high_ (0)
{
}

Receiver::~Receiver (void)
{
}

bool 
Receiver::open_streams (ACE_HANDLE hsocket)
{
    if (this->stream_.open (*this, 
                            hsocket,
                            0, // completion key,
                            this->task().get_proactor((u_int) index_),
                            true) == -1)
    {
        ACE_ERROR((LM_ERROR,
            ACE_TEXT ("(%t) %s %p\n"),
            this->get_name(),
            ACE_TEXT ("Receiver::open_streams: socket stream failed")));
        return false;
    }

    char filename [ MAXPATHLEN];
    ACE_OS::snprintf (filename, MAXPATHLEN, "%sF_Test_Recv.%08u", 
                      ACE_LOG_DIRECTORY,
                      (u_int) index());


#ifdef _WIN32
    int perm = 0;
    ACE_HANDLE hfile = ACE_OS::open (filename,
                                      O_CREAT | 
                                      O_TRUNC |
                                      O_RDWR |
                                      FILE_FLAG_OVERLAPPED ,
                                      perm);
#else
    int perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    ACE_HANDLE hfile = ACE_OS::open (filename,
                                      O_CREAT | 
                                      O_TRUNC |
                                      O_RDWR |
                                      //O_DIRECT |
                                      FILE_FLAG_OVERLAPPED ,
                                      perm);
#endif


    if (hfile == ACE_INVALID_HANDLE ||
        this->file_.open (*this, 
                          hfile,
                          0, // completion key,
                          this->task().get_proactor((u_int) index_),
                          true) == -1)
    {
        ACE_ERROR((LM_ERROR,
            ACE_TEXT ("(%t) %s %p\n"),
            this->get_name(),
            ACE_TEXT ("Receiver::open_streams: file stream failed")));
        return false;
    }

    return true;
}

void
Receiver::open (ACE_HANDLE handle, ACE_Message_Block &)
{
    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        bool rc = open_streams (handle);

        if (rc)
        {
            this->initiate_read(-1, -1);
        }

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}



void
Receiver::handle_read_stream (const TRB_Asynch_Read_Stream::Result &result)
{
    this->trace_read_completion (result, "stream");

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex () );

        this->ref_cnt_r_--;

        ACE_Message_Block & mb = result.message_block ();

        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            static const char separator1 [] = "\r\n-------- begin read data -----\r\n";
            static const char separator2 [] = "\r\n-------- end   read data -----\r\n";

            static const size_t l1 = sizeof (separator1) - 1;
            static const size_t l2 = sizeof (separator2) - 1;

            this->initiate_write (offset_low_, offset_high_, 
                                  separator1, l1);
            offset_low_ += l1;

            this->initiate_write (offset_low_, offset_high_, mb);
            offset_low_ += result.bytes_transferred ();

            this->initiate_write (offset_low_, offset_high_, 
                                  separator2, l2);
            offset_low_ += l2;

            this->initiate_read (-1, -1);
        }
        else
        {
            mb.release ();
        }

        if (result.error () != 0)
            this->do_cancel ();

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

void
Receiver::handle_write_file (const TRB_Asynch_Write_File::Result &result)
{
    this->trace_write_completion (result, "file");

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        this->ref_cnt_w_--;

        ACE_Message_Block & mb = result.message_block ();

        mb.release ();

        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            //this->initiate_read_stream ();
        }
        else
        {
            this->do_cancel ();
        }

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

void
Receiver::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
    this->trace_write_completion (result, "stream");

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        this->ref_cnt_w_--;

        ACE_Message_Block & mb = result.message_block ();

        mb.release ();

        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            //this->initiate_read_stream ();
        }
        else
        {
            this->do_cancel ();
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
    virtual ~Sender (void);

    // Virtual from PSession
    virtual const ACE_TCHAR * get_name (void) const 
    {
        return ACE_TEXT("Sender");
    }

    /// This is called after the new connection has been accepted.
    virtual void open (ACE_HANDLE handle,
        ACE_Message_Block &message_block);

    /**
    * @name AIO callback handling
    *
    * These methods are called by the framework
    */
    virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

    virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);

    virtual void handle_transmit_file (const TRB_Asynch_Transmit_File::Result &result);


private:
    bool open_streams (ACE_HANDLE hsocket);
    ACE_Message_Block  mbHeader_;
    ACE_Message_Block  mbTrailer_;

};

// ************************************************
static const char * strHdr  = "\n=========== Header  ==========\n";
static const char * strTail = "\n=========== Trailer ==========\n";

Sender::Sender ()
: PSession   ()
, mbHeader_  (1024)
, mbTrailer_ (1024)
{

    mbHeader_.copy ( strHdr, strlen (strHdr));
    mbTrailer_.copy ( strTail, strlen (strTail));
}

Sender::~Sender (void)
{
}


bool 
Sender::open_streams (ACE_HANDLE hsocket)
{
    if (this->stream_.open (*this, 
        hsocket,
        0, // completion key,
        this->task().get_proactor((u_int) index_),
        true) == -1)
    {
        ACE_ERROR((LM_ERROR,
            ACE_TEXT ("(%t) %s %p\n"),
            this->get_name(),
            ACE_TEXT ("Sender::open_streams: socket stream failed")));
        return false;
    }

    ACE_HANDLE hfile = ACE_OS::open (config().filename().c_str(),
                                      O_RDONLY |
                                      FILE_FLAG_OVERLAPPED |
                                      FILE_FLAG_SEQUENTIAL_SCAN);

    if (hfile == ACE_INVALID_HANDLE ||
        this->file_.open (*this, 
                          hfile,
                          0, // completion key,
                          this->task().get_proactor((u_int) index_),
                          true) == -1)
    {
        ACE_ERROR((LM_ERROR,
            ACE_TEXT ("(%t) %s %p\n"),
            this->get_name(),
            ACE_TEXT ("Sender::open_streams: file stream failed")));
        return false;
    }

    return true;
}

void
Sender::open (ACE_HANDLE handle, ACE_Message_Block &)
{
    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        bool rc = open_streams (handle);
        
        if (rc)
        {
            this->initiate_read (-1, -1);

            mbHeader_.reset ();
            mbHeader_.wr_ptr  (strlen (strHdr));
            mbTrailer_.reset ();
            mbTrailer_.wr_ptr (strlen (strTail));
            
            this->initiate_transmit (file_.get_handle(),
                                     &mbHeader_,
                                     &mbTrailer_);
        }

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

void
Sender::handle_transmit_file (const TRB_Asynch_Transmit_File::Result &result)
{
    this->trace_transmit_completion (result);

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        this->ref_cnt_w_--;

        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            mbHeader_.reset ();
            mbHeader_.wr_ptr  (strlen (strHdr));
            mbTrailer_.reset ();
            mbTrailer_.wr_ptr (strlen (strTail));
            
            this->initiate_transmit (file_.get_handle(),
                                     &mbHeader_,
                                     &mbTrailer_);
        }
        else
        {
            this->do_cancel ();
        }


        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

void
Sender::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
    this->trace_write_completion (result, "stream");

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        this->ref_cnt_w_--;

        ACE_Message_Block & mb = result.message_block ();

        
        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            mb.reset ();
            mb.wr_ptr (mb.space ());
            this->initiate_write (-1, -1, mb);
            //this->initiate_read_stream();
        }
        else
        {
            mb.release ();
            this->do_cancel ();
        }


        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

void
Sender::handle_read_stream (const TRB_Asynch_Read_Stream::Result &result)
{
    this->trace_read_completion (result, "stream");

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        this->ref_cnt_r_--;

        ACE_Message_Block & mb = result.message_block ();


        if (result.error () == 0 && result.bytes_transferred () > 0)
        {
            mb.reset ();
            this->initiate_read (-1, -1, mb);
        }
        else
        {
            mb.release();
            this->do_cancel ();
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

    TRB_Sock_Addr listen_addr;
    TRB_Sock_Addr connect_addr;
    cfg.get_addresses (listen_addr, connect_addr);    


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
            // Simplify, initial read with zero size
            if (acceptor.start (listen_addr.get_ace_addr ()) == 0)
                rc = 1;
        }

        if (cfg.both() != 0 || cfg.connections () > 0) // Connector
        {
            rc += connector.start (connect_addr.get_ace_addr (),
                                   cfg.connections ());
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
    ACE_START_TEST (ACE_TEXT ("F_Test"));


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

