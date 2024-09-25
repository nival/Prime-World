#include "TConnectionManager.h"
#include "TP_ReactorTask.h"

// *************************************************************
//  TTConnectionManager  - container and object manager
//  for TConnection objects
// *************************************************************

TConnectionManager::TConnectionManager (TP_ReactorTask &  task,
                                      const ACE_TCHAR * name)
: mtx_          ()
, sem_          (0)
, task_         (task)
, name_         (name)
, total_snd_    (0)
, total_rcv_    (0)
, total_w_      (0)
, total_r_      (0)
, flg_stop_     (0)
, num_connections_ (0)
, peak_connections_(0)
, timeout_      (ACE_Time_Value::zero)
, timer_id_     (-1)
{
    this->reactor ( task.reactor ());

    for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
        this->list_connections_[i] = 0;
    }
}

TConnectionManager::~TConnectionManager (void)
{
    this->stop();
    this->wait();

    ACE_GUARD (TMutex, monitor, this->mtx_);
    this->reactor (0);

    ACE_ASSERT(this->num_connections_ == 0);
}

void 
TConnectionManager::print_statistic(void)
{
    //Print statistic
    ACE_TCHAR bufs [256];
    ACE_TCHAR bufr [256];

    ACE_OS::sprintf (bufs, ACE_TEXT ("%lu(%lu)"),
                    this->get_total_snd (),
                    this->get_total_w ());

    ACE_OS::sprintf (bufr, ACE_TEXT ("%lu(%lu)"),
                    this->get_total_rcv (),
                    this->get_total_r ());

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) %s total bytes(operations): snd=%s rcv=%s\n"),
                this->get_name(),
                bufs,
                bufr));
}

int
TConnectionManager::is_safe_to_delete (void)
{
    ACE_GUARD_RETURN (TMutex, monitor, this->mtx_,0);

    return (this->num_connections_ == 0 && this->timer_id_ == -1);
}

int
TConnectionManager::wait(void)
{
    while (!is_safe_to_delete())
    {
        this->sem_.acquire ();
    }
    return 0;
}

int
TConnectionManager::stop (void)
{
    ACE_GUARD_RETURN (TMutex, monitor, this->mtx_, -1);

    this->flg_stop_ = 1;

    this->cancel_timer ();

    // Propagate cancel to all connections
    for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
        if (this->list_connections_[i] != 0)
        {
            this->list_connections_[i]->stop ();
        }
    }
    return 0;
}

void
TConnectionManager::check (void)
{
    ACE_GUARD (TMutex, monitor, this->mtx_);

    // Propagate check to all connections
    for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
        if (this->list_connections_[i] != 0)
        {
            this->list_connections_[i]->check ();
        }
    }
}

void
TConnectionManager::cancel_timer (void)
{
    if (this->timer_id_ != -1)
    {
        int rc = this->task().reactor()->cancel_timer (this->timer_id_);

        if (rc != 0)
        {
            this->timer_id_ = -1;
        }
    }
}

void
TConnectionManager::start_timer (void) 
{
    if (this->should_stop())
    {
        if (this->is_safe_to_delete())
        {
            this->sem_.release(1);
        }
        return;
    }

    if (this->timer_id_ != -1 ||
        this->timeout_ == ACE_Time_Value::zero)
    {
        return;
    }

    ACE_Time_Value abs_time = this->timeout_;

    this->timer_id_ = 
        this->task().reactor()->schedule_timer (this,
                                                0,
                                                abs_time);
}

int
TConnectionManager::handle_timeout ( const ACE_Time_Value & /* tv */,
                                   const void *   /* pArg */)
{
    this->check();

    ACE_GUARD_RETURN (TMutex, monitor, this->mtx_, -1);

    //ACE_DEBUG((LM_DEBUG,
    //              ACE_TEXT ("(%t) %s handle timeout\n"),
    //              this->get_name ()));

        
    this->timer_id_ = -1;

    this->start_timer ();
    return 0;
}

void
TConnectionManager::set_timeout (const ACE_Time_Value & timeout)
{
    ACE_GUARD (TMutex, monitor, this->mtx_);

    this->timeout_ = timeout;

    this->start_timer ();
}

TConnection *
TConnectionManager::create_connection (TConnectionFactory & con_factory)
{
    ACE_GUARD_RETURN (TMutex, monitor, this->mtx_, 0);

    if (this->num_connections_ >= MAX_CONNECTIONS || 
        this->flg_stop_ )
    {
        return 0;
    }

    TConnection * connection = 0;
    u_int i = 0;

    for (; i < MAX_CONNECTIONS; ++i)
    {
        if (this->list_connections_[i] == 0)
        {
            connection = con_factory.create_connection ();
            break;
        }
    }

    if (connection == 0)
    {
        return 0;
    }

    this->list_connections_[i] = connection;
    this->num_connections_++;

    if (this->num_connections_ > this->peak_connections_)
    {
        this->peak_connections_ = this->num_connections_;
    }

    connection->reactor (this->reactor ());

    connection->setup (&con_factory, this, i);
    
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) %s=%d NEW %s=%d\n"),
                this->get_name(),
                this->num_connections_,
                connection->get_name(),
                i));

    return connection;
}

void
TConnectionManager::destroy_connection(TConnection * connection)
{
    ACE_GUARD (TMutex, monitor, this->mtx_);
      
    u_int index = connection->index();

    ACE_ASSERT(connection->manager () == this);
    ACE_ASSERT(index < MAX_CONNECTIONS);
    ACE_ASSERT(connection == this->list_connections_[index]);
      
    this->total_snd_ += connection->get_total_snd();
    this->total_rcv_ += connection->get_total_rcv();
    this->total_w_   += connection->get_total_w();
    this->total_r_   += connection->get_total_r();

      
    this->num_connections_--;
    this->list_connections_[index] = 0;


    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("(%t) %s=%d: DEL %s=%d S=%d(%d) R=%d(%d)\n"),
                this->get_name(),
                this->num_connections_,
                connection->get_name(),
                index,
                connection->get_total_snd(),
                connection->get_total_w(),
                connection->get_total_rcv(),
                connection->get_total_r()));

       
    TConnectionFactory * factory = connection->factory ();
    connection->setup (0, 0, -1);
    factory->destroy_connection(connection);

    if (this->is_safe_to_delete())
    {
        this->sem_.release(1);
    }
}




