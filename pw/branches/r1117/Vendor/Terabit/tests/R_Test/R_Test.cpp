// $Id: T_Test.cpp,v 1.15 2002/05/15 02:38:14 pgontla Exp $
//============================================================================
// = AUTHOR
//      Alexander Libman <libman@terabit.com.au>
//
//============================================================================

#include "test_config.h"

#include "R_Test.h"

#include "ace/Signal.h"
#include "ace/Service_Config.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"
//#include "ace/Countdown_Time.h"


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
RTask::RTask (TestCfg & cfg)
: cfg_           (cfg)
, lock_          ()
, sem_           (0)
, flg_stop_      (false)
, reactor_impl_  ()
, task_reactor_  (&reactor_impl_, 0)
{
    this->reactor (&task_reactor_);
}

RTask::~RTask() 
{ 
    this->reactor (0);
    ACE_ASSERT(this->thr_count() == 0);
}

int
RTask::start (void)
{
    {
        ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX,
                          monitor,
                          this->lock_,
                          -1);

        if (this->activate (THR_NEW_LWP, 1) == -1)
            ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("(%t) %p.\n"),
                             ACE_TEXT ("unable to activate RTask")),
                             -1);
    }

    this->sem_.acquire ();
    return 0;
}

int
RTask::stop ()
{
    {
        ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX,
                          monitor,
                          this->lock_,
                          -1);

        this->flg_stop_ = true;

        task_reactor_.end_reactor_event_loop ();
    }
    this->wait();
    return 0;
}

int
RTask::svc (void)
{
    ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX,
                        monitor,
                        this->lock_,
                        -1);

    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) RTask started\n")));

    disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
    disable_signal (SIGPIPE, SIGPIPE);

    
    task_reactor_.owner (ACE_Thread::self());
    this->sem_.release (1);

    while (!flg_stop_)
    {
        monitor.release ();

        task_reactor_.run_reactor_event_loop ();
        //task_reactor.reset_reactor_event_loop();

        monitor.acquire ();
    }

    
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) RTask finished\n")));
    return 0;
}

// *************************************************************

Acceptor::Acceptor ()
:   ACE_Acceptor<Receiver,ACE_SOCK_ACCEPTOR> ((ACE_Reactor * )0),
    mutex_    (),
    sem_      (0),
    connections_ (0),
    total_snd_(0),
    total_rcv_(0),
    total_w_  (0),
    total_r_  (0),
    flg_cancel_(0)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
  {
     this->list_connections_[i] =0;
  }
}

Acceptor::~Acceptor (void)
{
  stop ();
}

int
Acceptor::stop (void)
{
  // this method can be called only after reactor event loop id done
  // in all threads

  while (1)
  {
      {
        ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);
        if (this->connections_ == 0)
        {
            break;
        }
      }
      this->sem_.acquire ();
  }
  return 0;
} 

int
Acceptor::cancel(void)
{

  this->close();
  this->reactor (0);
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);
  this->flg_cancel_ = 1;

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
  {
    if (this->list_connections_[i] !=0)
    {
        this->list_connections_[i]->cancel ();
    }
  }

  return 0;
}


void
Acceptor::on_new_receiver (Receiver &rcvr)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);
  this->connections_++;
  this->list_connections_[ rcvr.index_] = & rcvr;
  ACE_DEBUG ((LM_DEBUG,
              "Receiver::CTOR connections_=%d\n",
              this->connections_));
}

void
Acceptor::on_delete_receiver (Receiver &rcvr)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  this->connections_--;

  this->total_snd_ += rcvr.get_total_snd ();
  this->total_rcv_ += rcvr.get_total_rcv ();
  this->total_w_   += rcvr.get_total_w ();
  this->total_r_   += rcvr.get_total_r ();

  if (rcvr.index_ < MAX_CONNECTIONS
      && this->list_connections_[rcvr.index_] == &rcvr)
    this->list_connections_[rcvr.index_] = 0;

  ACE_TCHAR bufs [256];
  ACE_TCHAR bufr [256];

  ACE_OS::sprintf ( bufs , ACE_TEXT ("%ld(%ld)"),
                    rcvr.get_total_snd (),
                    rcvr.get_total_w () );

  ACE_OS::sprintf ( bufr , ACE_TEXT ("%ld(%ld)"),
                    rcvr.get_total_rcv (),
                    rcvr.get_total_r ());

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Receiver::~DTOR index=%d snd=%s rcv=%s connections_=%d\n"),
              rcvr.index_,
              bufs,
              bufr,
              this->connections_));

  if (this->connections_ == 0)
  {
      sem_.release (1);
  }
}

int
Acceptor::start (const ACE_INET_Addr &addr, ACE_Reactor * reactor)
{
  this->reactor (reactor);

  if (ACE_Acceptor<Receiver,ACE_SOCK_ACCEPTOR>
      ::open (addr, reactor, ACE_NONBLOCK) < 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "Acceptor::start () - open failed"),
                       -1);
  }
  return 0;
}

int
Acceptor::make_svc_handler (Receiver *&sh)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  if (connections_ >= MAX_CONNECTIONS || flg_cancel_ != 0)
  {
    return -1;
  }

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
  {
      if (this->list_connections_ [i] == 0)
      {
        ACE_NEW_RETURN (sh,
                        Receiver (this , i),
                        -1);
        return 0;
      }
  }
  return -1;
}

// *************************************************************

Receiver::Receiver (Acceptor * acceptor, int index)
  : acceptor_ (acceptor),
    index_    (index),
    total_snd_(0),
    total_rcv_(0),
    total_w_  (0),
    total_r_  (0),
    flg_cancel_(0)
{
  this->reactor (0);

  if (acceptor_ != 0)
    acceptor_->on_new_receiver (*this);
}


Receiver::~Receiver (void)
{
  this->reactor (0);
  if (acceptor_ != 0)
    acceptor_->on_delete_receiver (*this);

  this->index_ = -1;
}

int
Receiver::open (void *)
{
   // ACE_Guard<ACE_Recursive_Thread_Mutex> locker (mutex_);
    if (this->activate (THR_NEW_LWP, 1) == -1)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("(%t) %p.\n"),
                         ACE_TEXT ("unable to activate thread")),
                        -1);
    return 0;
}

int 
Receiver::cancel ()
{
    this->flg_cancel_ = 1;
    this->peer().close_reader();
    this->peer().close_writer();
    return 0;
}

int 
Receiver::svc ()
{
    this->peer().disable(ACE_NONBLOCK);

    while (!should_finish ())
    {
	    ACE_Message_Block * mb = new ACE_Message_Block (cfg.r_blksize());

        int rc = this->peer ().recv (mb->rd_ptr (), mb->space());

        this->total_r_++;

        if (rc <= 0)
        {
            break;
        }

        mb->wr_ptr (rc);
        this->total_rcv_ += rc;

	    do_delay (cfg.delay());  // delay milliseconds

        rc = this->peer ().send (mb->rd_ptr (), mb->length ());
        this->total_w_++;
        if (rc <= 0)
        {
            break;
        }
        this->total_snd_ += rc;
        mb->reset ();

        ACE_Message_Block::release(mb);
    }

    return 0;
}
// *************************************************************

Connector::Connector ()
:   ACE_Connector<Sender,ACE_SOCK_CONNECTOR> ((ACE_Reactor *) 0),
    mutex_    (),
    sem_      (0),
    connections_ (0),
    total_snd_(0),
    total_rcv_(0),
    total_w_  (0),
    total_r_  (0),
    flg_cancel_(0)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
  {
     this->list_connections_[i] = 0;
  }
}

Connector::~Connector (void)
{
  stop ();
}

int
Connector::cancel(void)
{

  this->close ();
  this->reactor (0);

  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
  {
      if (this->list_connections_[i] !=0)
      {
        this->list_connections_[i]->cancel ();
      }
  }

  return 0;
}
int
Connector::begin(void)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
  {
      if (this->list_connections_[i] !=0)
      {
        this->list_connections_[i]->begin();
      }
  }

  return 0;
}

int
Connector::stop ()
{

  while (1)
  {
      {
        ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);
        if (this->connections_ == 0)
        {
            break;
        }
      }
      this->sem_.acquire ();
  }
  return 0;
}

void
Connector::on_new_sender (Sender & sndr)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);
  this->connections_++;
  this->list_connections_[sndr.index_] = &sndr;
  ACE_DEBUG ((LM_DEBUG,
              "Sender::CTOR connections_=%d\n",
              this->connections_));
}

void
Connector::on_delete_sender (Sender & sndr)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  this->connections_--;
  this->total_snd_ += sndr.get_total_snd();
  this->total_rcv_ += sndr.get_total_rcv();
  this->total_w_   += sndr.get_total_w();
  this->total_r_   += sndr.get_total_r();

  if (sndr.index_ < MAX_CONNECTIONS
      && this->list_connections_[sndr.index_] == &sndr)
    this->list_connections_[sndr.index_] = 0;

  ACE_TCHAR bufs [256];
  ACE_TCHAR bufr [256];

  ACE_OS::sprintf ( bufs , ACE_TEXT ("%ld(%ld)"),
                    sndr.get_total_snd(),
                    sndr.get_total_w() );

  ACE_OS::sprintf ( bufr , ACE_TEXT ("%ld(%ld)"),
                    sndr.get_total_rcv(),
                    sndr.get_total_r() );

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Sender::~DTOR index=%d snd=%s rcv=%s connections_=%d\n"),
              sndr.index_,
              bufs,
              bufr,
              this->connections_));

  if (this->connections_ == 0)
  {
      sem_.release (1);
  }
}

int
Connector::start (const ACE_INET_Addr & addr, int num, ACE_Reactor * reactor)
{

  if (ACE_Connector<Sender,ACE_SOCK_CONNECTOR>
      ::open (reactor,ACE_NONBLOCK) < 0)
    ACE_ERROR_RETURN
      ((LM_ERROR,
        "%p\n",
        "Connector::start () - open failed"),
       0);

  int rc = 0;

  ACE_Synch_Options opt(ACE_Synch_Options::USE_REACTOR,
                        ACE_Time_Value::zero);   //  (seconds,0));

  for (rc = 0 ; rc < num ; rc++)
    {
      Sender * sender = 0;

      if (ACE_Connector<Sender,ACE_SOCK_CONNECTOR>
          ::connect (sender,
                     addr,
                     opt) < 0)
        {
          if ( ACE_OS::last_error() == EWOULDBLOCK)
            continue;

          ACE_ERROR_RETURN
            ((LM_ERROR,
              "%p\n",
              "Connector::start () - connect failed"),
              rc);
        }
    }

  return rc;
}

int
Connector::make_svc_handler (Sender * & sh)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  if (connections_ >= MAX_CONNECTIONS || flg_cancel_ != 0)
    return -1;

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
    if (this->list_connections_ [i] == 0)
      {
        ACE_NEW_RETURN (sh,
                        Sender (this , i),
                        -1);
        return 0;
      }

  return -1;
}

// *************************************************************

Sender::Sender (Connector* connector, int index)
  : connector_ (connector),
    index_ (index),
    mtx_       (),
    cond_      (mtx_),
    total_snd_ (0),
    total_rcv_ (0),
    total_w_   (0),
    total_r_   (0),
    flg_cancel_(0),
    flg_begin_ (0)
{
  this->reactor (0);
  if (connector_ != 0)
    connector_->on_new_sender (*this);

}


Sender::~Sender (void)
{
  this->reactor (0);
  if (connector_ != 0)
    connector_->on_delete_sender (*this);

  this->index_ = -1;
}

int
Sender::open (void *)
{
   // ACE_Guard<ACE_Recursive_Thread_Mutex> locker (mutex_);

    if (this->activate (THR_NEW_LWP, 1) == -1)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("(%t) %p.\n"),
                         ACE_TEXT ("unable to activate thread")),
                        -1);
    return 0;
}

int 
Sender::cancel ()
{
    this->flg_cancel_ = 1;
    this->peer().close_reader();
    this->peer().close_writer();
    return 0;
}
int 
Sender::begin()
{
    ACE_Guard<ACE_Thread_Mutex> guard(mtx_);
    flg_begin_ = 1;
    cond_.signal();
    return 0;
}

int 
Sender::svc ()
{
    u_int blk = cfg.s_blksize ();

    if (blk < sizeof(data)+1 )
    {
        blk = sizeof(data)+1;
    }

    this->peer().disable(ACE_NONBLOCK);

    for (;;)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(mtx_);
        if (flg_begin_)
            break;
        cond_.wait();

    }

    while (!should_finish ())
    {
	    ACE_Message_Block * mb = new ACE_Message_Block (blk);

        mb->reset ();
        mb->copy(data);
        
        int rc = this->peer ().send (mb->rd_ptr (), mb->size());
        this->total_w_++;
        if (rc <= 0)
        {
            break;
        }
        this->total_snd_ += rc;

        mb->reset ();

        
        rc = this->peer ().recv (mb->rd_ptr (), mb->space());

        this->total_r_++;

        if (rc <= 0)
        {
            break;
        }

        mb->wr_ptr (rc);
        this->total_rcv_ += rc;
		ACE_Message_Block::release (mb);

    }

    return 0;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class ACE_Svc_Tuple<Sender>;
template class ACE_Map_Manager<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >;
template class ACE_Map_Entry<int, ACE_Svc_Tuple<Sender> * >;
template class ACE_Map_Iterator<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >;
template class ACE_Map_Reverse_Iterator<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >;
template class ACE_Map_Iterator_Base<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >;
template class ACE_Connector<Sender,ACE_SOCK_CONNECTOR>;
template class ACE_Acceptor<Receiver,ACE_SOCK_ACCEPTOR>;
template class ACE_Svc_Handler<ACE_SOCK_STREAM,ACE_MT_SYNCH>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate ACE_Svc_Tuple<Sender>
#pragma instantiate ACE_Map_Manager<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >
#pragma instantiate ACE_Map_Entry<int, ACE_Svc_Tuple<Sender> * >
#pragma instantiate ACE_Map_Iterator<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >
#pragma instantiate ACE_Map_Reverse_Iterator<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >
#pragma instantiate ACE_Map_Iterator_Base<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >
#pragma instantiate ACE_Connector<Sender,ACE_SOCK_CONNECTOR>
#pragma instantiate ACE_Acceptor<Receiver,ACE_SOCK_ACCEPTOR>
#pragma instantiate ACE_Svc_Handler<ACE_SOCK_STREAM,ACE_MT_SYNCH>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */


int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("R_Test"));

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

  RTask     task1(cfg);
  Acceptor  acceptor;
  Connector connector;

  ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
  ACE_Time_Value time_end = ACE_OS::gettimeofday ();
  ACE_Time_Value time_run;

  if (task1.start()== 0)
  {

    if (acceptor.start (ACE_INET_Addr (cfg.listen_port()), task1.reactor()) >= 0)
    {
        rc = 1;
    }
      
    if (cfg.connections () > 0) // Connector
    {
         ACE_INET_Addr addr;
         addr.set (cfg.connect_port(), cfg.connect_host());
         rc += connector.start (addr, cfg.connections (), task1.reactor());
    }

    time_begin = ACE_OS::gettimeofday ();
    connector.begin();

    ACE_Time_Value  sleep_time (cfg.seconds());
           
    while ( sleep_time != ACE_Time_Value::zero)
    {
        ACE_Countdown_Time countdown ( & sleep_time );
        ACE_OS::sleep (sleep_time );
    }

    if (cfg.seconds() == 0)
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
                    cout << "\n*** Connector: Senders="
                        << connector.get_number_connections ()
                        << "\n*** Acceptor: Receivers="
                        << acceptor.get_number_connections ();
                break;
                }//switch
            }//for
    }

    task1.stop();
  }

  u_int  num_ssn_s = connector.get_number_connections ();
  u_int  num_ssn_r = acceptor.get_number_connections ();


  // As Proactor event loop now is inactive it is safe to destroy all
  // Senders
  connector.cancel();
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stop Connector/Senders: connections_=%d\n"),
              num_ssn_s));
  connector.stop ();

  // As Proactor event loop now is inactive it is safe to destroy all
  // Receivers
  acceptor.cancel ();
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stop Acceptor/Receivers:connections_=%d\n"),
              num_ssn_r));
  acceptor.stop ();

  time_end = ACE_OS::gettimeofday ();
  time_run = time_end - time_begin;

  u_long snd_bytes_s = connector.get_total_snd();
  u_long rcv_bytes_s = connector.get_total_rcv();
  u_long snd_op_s = connector.get_total_w();
  u_long rcv_op_s = connector.get_total_r();

  u_long snd_bytes_r = acceptor.get_total_snd();
  u_long rcv_bytes_r = acceptor.get_total_rcv();
  u_long snd_op_r = acceptor.get_total_w();
  u_long rcv_op_r = acceptor.get_total_r();


  //Print statistic
  ACE_TCHAR bufs [256];
  ACE_TCHAR bufr [256];

  ACE_OS::sprintf (bufs, ACE_TEXT ("%lu(%lu)"),
                   snd_bytes_s,
                   snd_op_s);

  ACE_OS::sprintf (bufr, ACE_TEXT ("%lu(%lu)"),
                   rcv_bytes_s,
                   rcv_op_s);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Connector/Senders  total bytes: snd=%s rcv=%s\n"),
              bufs,
              bufr));

  ACE_OS::sprintf (bufs, ACE_TEXT ("%lu(%lu)"),
                   snd_bytes_r,
                   snd_op_r);

  ACE_OS::sprintf (bufr, ACE_TEXT ("%lu(%lu)"),
                   rcv_bytes_r,
                   rcv_op_r);
  
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Acceptor/Receivers total bytes: snd=%s rcv=%s\n"),
              bufs,
              bufr));

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Threads = %d BlkSize=%d\n"),
              cfg.threads(),
              cfg.blksize()));

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Sessions = %d (%d) \n"),
              rc-1,
              cfg.connections ()));


  float  fsec = (float)(time_run.msec()/1000);
  double fbspeed = ((float) snd_bytes_s
                  +(float) snd_bytes_r
                  +(float) rcv_bytes_s
                  +(float) rcv_bytes_r
                  );

  double fmspeed = ((float) snd_op_s
                  +(float)  rcv_op_s
                  +(float)  snd_op_r
                  +(float)  rcv_op_r
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
              ACE_TEXT ("(%t) Effective bytes/sec = %f  op/sec = %f\n"),
              fbspeed, 
              fmspeed));



  ACE_END_TEST;

  return 0;
}
