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
*  @file F2_Test.cpp
*
*  F2_Test.cpp
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


template class TRB_Asynch_RW_File <TRB_Asynch_Read_File,TRB_Asynch_Write_File>;


static TestCfg cfg;


// *************************************************************
//   FSession 
// *************************************************************

class FSession : public PSession
{
public:
    FSession  (void);
    virtual ~FSession (void);

    // Virtual from PSession
    virtual const ACE_TCHAR * get_name (void) const 
    {
        return ACE_TEXT("FSession");
    }



    virtual int open ();
    
    /**
    * @name AIO callback handling
    *
    * These methods are called by the framework
    */
    virtual void handle_read_file (const TRB_Asynch_Read_File::Result &result);

    virtual void handle_write_file (const TRB_Asynch_Write_File::Result &result);

private:

    u_long   offset_low_;
    u_long   offset_high_;
};

// ***************************************************
FSession::FSession ()
: PSession     ()
, offset_low_  (0)
, offset_high_ (0)
{
}

FSession::~FSession (void)
{
}

int 
FSession::open ()
{
    enum { NUM_INITIAL_READS = 3 };

    int rc = 0;
    {
        ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, monitor, this->mutex (), -1);

        ACE_HANDLE h_read = ACE_OS::open (config().filename().c_str(),
                                          O_RDONLY |
                                          FILE_FLAG_OVERLAPPED |
                                          FILE_FLAG_SEQUENTIAL_SCAN);

        if (h_read == ACE_INVALID_HANDLE ||
            this->file_read_.open (*this, 
                                h_read,
                                0, // completion key,
                                this->task().get_proactor((u_int) index_),
                                true) == -1)
        {
            ACE_ERROR((LM_ERROR,
                ACE_TEXT ("(%t) %s %p\n"),
                    this->get_name(),
                    ACE_TEXT ("FSession::open input file failed")));

            rc = -1;
        }

        if (rc == 0)
        {
            char filename [ MAXPATHLEN];
            ACE_OS::snprintf (filename, MAXPATHLEN, "%sF2_Test_Recv.%08u", 
                              ACE_LOG_DIRECTORY,
                              (u_int) index());

 #ifdef _WIN32
            int perm = 0;
#else
            int perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
#endif

            ACE_HANDLE h_write = ACE_OS::open (filename,
                                               O_CREAT | 
                                               O_TRUNC |
                                               O_RDWR |
                                               //O_DIRECT |
                                               FILE_FLAG_OVERLAPPED ,
                                               perm);

            if (h_write == ACE_INVALID_HANDLE ||
                this->file_write_.open (*this, 
                                        h_write,
                                        0, // completion key,
                                        this->task().get_proactor((u_int) index_),
                                        true) == -1)
            {
                ACE_ERROR((LM_ERROR,
                    ACE_TEXT ("(%t) %s %p\n"),
                    this->get_name(),
                    ACE_TEXT ("FSession::open output file failed")));
                rc = -1;
            }
        }

        if (rc == 0)
        {
            u_int blksize = this->config().s_blksize();

            for (int i=0; i < NUM_INITIAL_READS; ++i)
            {
                this->initiate_read(offset_low_, offset_high_, blksize);
                offset_low_ += blksize;
            }
        }
        
        if (!is_safe_to_delete())
            return rc;
    }
    this->manager()->destroy_session(this);
    return rc;
}



void
FSession::handle_read_file (const TRB_Asynch_Read_File::Result &result)
{
    this->trace_read_completion (result, "file");

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex () );

        this->ref_cnt_r_--;

        ACE_Message_Block & mb = result.message_block ();

        u_int blksize = this->config().s_blksize();
        u_long error = result.error ();

        if (error == 0)
        {
            if (result.bytes_transferred () > 0)
            {
                this->initiate_write (result.offset (),
                                      result.offset_high (),
                                      mb);
            }
            else
            {
                mb.release ();
                // do loop , i.e. read again
                offset_low_ = 0;
                offset_high_ = 0;
            }

            this->initiate_read(offset_low_, offset_high_, blksize);
            offset_low_ += blksize;

        }
        else
        {
            mb.release ();
            // separate errors:
            // #ifdef _WIN32   ERROR_HANDLE_EOF
           
            // do loop , i.e. read again
            offset_low_ = 0;
            offset_high_ = 0;

            this->initiate_read(offset_low_, offset_high_, blksize);
            offset_low_ += blksize;

            // alternative
            //default:
            //    mb.release ();
            //    this->do_cancel ();
            //    break;
        }

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}

void
FSession::handle_write_file (const TRB_Asynch_Write_File::Result &result)
{
    this->trace_write_completion (result, "file");

    {
        ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

        this->ref_cnt_w_--;

        ACE_Message_Block & mb = result.message_block ();

        mb.release ();

        if (result.error () != 0 ||
            result.bytes_transferred () != result.bytes_requested ())
        {
            this->do_cancel ();
        }

        if (!is_safe_to_delete())
            return;
    }
    this->manager()->destroy_session(this);
}


class FSessionFactory : public PSessionFactory
{
public:
    virtual PSession*  create_session(PSessionManager & /*manager*/)
    {
        PSession * p = 0;
        ACE_NEW_RETURN (p, FSession, 0);
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

    FSessionFactory factory;

    PSessionManager manager (task1, factory,"Manager");


    ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
    ACE_Time_Value time_end = ACE_OS::gettimeofday ();
    ACE_Time_Value time_run;

    if (task1.start () == 0)
    {
        task1.enable_event_loop();

        ACE_Time_Value timeout (cfg.timeout(), 0);
        manager.set_timeout (timeout);
        
        for (size_t i = 0; i < cfg.connections(); ++i)
        {
            PSession *session = manager.create_session ();
            if (session)
            {
                session->open ();
            }
        }
    }

    time_begin = ACE_OS::gettimeofday ();


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
                cout << "\n***  FSessions="
                    << manager.get_number_connections ();
                break;
            }//switch
        }//for
    }//if cfg.seconds


    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) *** Cancel: FSessions=%d\n"),
        manager.get_number_connections ()
        ));

    // Cancel all pending AIO on
    // Connector, Acceptor, all Senders, all FSessions
    manager.cancel ();


    while (!manager.is_safe_to_delete ())
    {
        task1.wait_signal ();
    }

    time_end = ACE_OS::gettimeofday ();
    time_run = time_end - time_begin;


    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

    task1.stop ();

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) *** Stop: FSessions=%d\n"),
        manager.get_number_connections ()
        ));



    //Print statistic
    manager.print_statistic ();

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) Threads = %d BlkSize=%d\n"),
        cfg.threads(),
        cfg.blksize()));

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) Sessions: Max=%d  Peak=%d \n"),
        cfg.connections (),
        manager.get_peak_connections ()));


    float  fsec = (float)(time_run.msec()/1000);
    double fbspeed = ((float) manager.get_total_snd()
                     +(float) manager.get_total_rcv()
                     );

    double fmspeed = ((float) manager.get_total_w()
                     +(float) manager.get_total_r()
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
    ACE_START_TEST (ACE_TEXT ("F2_Test"));


    if (cfg.parse_args (argc, argv) < 0)
        return -1;

    disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
    disable_signal (SIGPIPE, SIGPIPE);
    disable_signal (SIGIO, SIGIO);


    ACE_DEBUG ((LM_DEBUG,
        "s_blksize=%u r_blksize=%u win_size=%u\n",
        cfg.s_blksize(),
        cfg.r_blksize(),
        cfg.w_size()));


    run(argc, argv);

    ACE_END_TEST;

    return 0;
}

