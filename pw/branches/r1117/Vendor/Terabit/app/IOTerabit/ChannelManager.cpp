#include "IOTerabit/IOThreadPool.h"
#include "IOTerabit/ChannelManager.h"
#include "IOTerabit/Protocol.h"
#include "ace/OS_NS_stdio.h"

namespace Terabit {

// *************************************************************
//
// *************************************************************
void
ChannelManager::Statistic::print (const ACE_TCHAR * mgr_name)
{
    if (!mgr_name) 
    {
        mgr_name = "";
    }

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("========= ChannelManager : %s =================\n")
        ACE_TEXT ("Channels : Total=%Q Limit=%d Peak=%d Current=%d\n")
        ACE_TEXT ("Read     : bytes=%Q operations=%Q\n")
        ACE_TEXT ("Write    : bytes=%Q operations=%Q\n"),
        mgr_name,
        this->total_channels_,
        this->max_channels_,
        this->peak_channels_,
        this->current_channels_,
        this->total_rcv_,
        this->total_r_,
        this->total_snd_,
        this->total_w_));
}

// *************************************************************
//  ChannelManager  - container and object manager
//  for Channel objects
// *************************************************************

ChannelManager::ChannelManager (const ACE_TCHAR *       name,
                                IOThreadPool &          task,
                                AsynchChannelFactory &  factory)
: monitor_         ()
, task_            (task)
, factory_         (factory)
, name_            (name)
, stats_           ()
, state_           (ST_INIT)
, flags_           (0)
, timer_id_        (-1)
, timeout_         (ACE_Time_Value::zero)
, log_level_       (2)
, active_channels_ ()
, check_iterator_  ()
, mb_factory_      (0)
{
}

ChannelManager::~ChannelManager (void)
{
    this->close ();
    this->wait ();
}

void
ChannelManager::get_statistic(Statistic & stats)
{
    Guard_Monitor guard (monitor_);
    stats = this->stats_;
}

void
ChannelManager::print_statistic()
{
   Statistic  stats;
   this->get_statistic (stats);
   stats.print (this->get_name ());
}


int
ChannelManager::wait(void)
{
    Guard_Monitor guard (monitor_);
    while (!this->active_channels_.empty () ||
           this->timer_id_ != -1)
    {
        guard.wait ();
    }

    if (this->state_ == ST_CANCEL)
    {
        this->state_ = ST_CLOSED;
    }

    return 0;
}

int
ChannelManager::open ()
{
    Guard_Monitor guard (monitor_);
    switch (this->state_)
    {
    case ST_ACTIVE:   return  0;   // ignore
    case ST_CANCEL:   return -1;   // can be re-reopened after ST_CLOSED
    default:          break;
    }

    this->state_ = ST_ACTIVE;
    this->start_timer_internal ();
    return 0;
}

void
ChannelManager::close (void)
{
    Guard_Monitor guard (monitor_);
    if (this->state_ == ST_ACTIVE)
    {
        this->state_ = ST_CANCEL;
        this->cancel_timer_internal ();
        this->close_channels_internal (guard);
    }
}


bool
ChannelManager::set_message_block_factory (MessageBlockFactory * mb_factory)
{
    Guard_Monitor guard (monitor_);
    switch (this->state_)
    {
    case ST_INIT:     break;
    case ST_CLOSED:   break;
    default:          return false;
    }
    this->mb_factory_ = mb_factory;
    return true;
}

void
ChannelManager::close_channels (void)
{
    Guard_Monitor guard (monitor_);
    this->close_channels_internal (guard);
}

void
ChannelManager::check_channels (void)
{
    Guard_Monitor guard (monitor_);
    this->check_channels_internal (guard);
}

void
ChannelManager::close_channels_internal (Guard_Monitor& guard)
{
    // private method: called with locked monitor_
    if (ACE_BIT_ENABLED (this->flags_, FLG_CLOSE_ACTIVE))
    {
        return;
    }

    ACE_SET_BITS (this->flags_, FLG_CLOSE_ACTIVE);

    while (ACE_BIT_ENABLED (this->flags_, FLG_CHECK_ACTIVE))
    {
        guard.wait ();
    }

    ACE_ASSERT (ACE_BIT_DISABLED (this->flags_, FLG_FREE_CHANNEL));

    this->check_iterator_ = active_channels_.begin ();

    while (this->check_iterator_ !=  this->active_channels_.end ())
    {
        AsynchChannel *channel = *this->check_iterator_;
        {
            Save_Guard anti_guard (guard, Save_Guard::RELEASE);
            channel->close ();
        }

        ++this->check_iterator_;
        if (ACE_BIT_ENABLED (this->flags_, FLG_FREE_CHANNEL))
        {
            this->free_channel_internal (channel);
            ACE_CLR_BITS (this->flags_, FLG_FREE_CHANNEL);
        }
    }

    ACE_CLR_BITS (this->flags_, FLG_CLOSE_ACTIVE);

    if (this->state_ != ST_ACTIVE &&
        active_channels_.empty () &&
        this->timer_id_ == -1)
    {
       guard.broadcast ();
    }
}

void
ChannelManager::check_channels_internal (Guard_Monitor& guard)
{
    // private method: called with locked monitor_
    if (ACE_BIT_ENABLED (this->flags_, 
                         FLG_CHECK_ACTIVE | FLG_CLOSE_ACTIVE))
    {
        return;
    }

    ACE_SET_BITS (this->flags_, FLG_CHECK_ACTIVE);

    ACE_ASSERT (ACE_BIT_DISABLED (this->flags_, FLG_FREE_CHANNEL));

    this->check_iterator_ = active_channels_.begin ();

    while (this->check_iterator_ !=  this->active_channels_.end ())
    {
        AsynchChannel *channel = *this->check_iterator_;
        {
            Save_Guard anti_guard (guard, Save_Guard::RELEASE);
            channel->check_activity ();
        }

        ++this->check_iterator_;
        if (ACE_BIT_ENABLED (this->flags_, FLG_FREE_CHANNEL))
        {
            this->free_channel_internal (channel);
            ACE_CLR_BITS (this->flags_, FLG_FREE_CHANNEL);
        }
    }

    ACE_CLR_BITS (this->flags_, FLG_CHECK_ACTIVE);

    if (ACE_BIT_ENABLED (this->flags_, FLG_CLOSE_ACTIVE) ||
       ( this->state_ != ST_ACTIVE &&
         active_channels_.empty () &&
         this->timer_id_ == -1))
    {
       guard.broadcast ();
    }
}

void
ChannelManager::start_timer_internal ()
{
    // private method: called with locked monitor_
    if (this->state_ != ST_ACTIVE)
    {
        if (active_channels_.empty ())
        {
            monitor_.broadcast ();
        }
        return;
    }
 
    if (this->timer_id_ != -1 ||
        this->timeout_ == ACE_Time_Value::zero)
    {
        return;
    }

    ACE_Time_Value abs_time = this->timeout_;

    TRB_Proactor *proactor = this->task_.get_proactor (0);

    this->timer_id_ = proactor->schedule_timer (*this,
                                                0,
                                                abs_time);
}

void
ChannelManager::cancel_timer_internal (void) 
{
    // private method: called with locked monitor_
    if (this->timer_id_ != -1)
    {
        TRB_Proactor *proactor = this->task_.get_proactor (0);

        int rc = proactor->cancel_timer (this->timer_id_);

        if (rc == 0) //  timer was not found 
        {
            return;  //  we have pending timer notification
        }

        this->timer_id_ = -1;  // timer cancelled
    }

    if (this->state_ != ST_ACTIVE && active_channels_.empty ())
    {
        monitor_.broadcast ();
    }
}

void
ChannelManager::handle_time_out (const ACE_Time_Value & /* tv */,
                                 const void *   /* pArg */)
{
    Guard_Monitor guard (monitor_);

    this->timer_id_ = -1;  // timer cancelled

    if (this->state_ != ST_ACTIVE)
    {
        if (active_channels_.empty ())
        {
            monitor_.broadcast ();
        }
        return;
    }

    // check activity on channels
    this->check_channels_internal (guard);

    this->start_timer_internal ();
}

AsynchChannel *
ChannelManager::allocate_channel ()
{
    Guard_Monitor guard (monitor_);

    // check if we can create a channel
    if (this->state_ != ST_ACTIVE ||
        this->stats_.current_channels_ >= this->stats_.max_channels_)
    {
        return 0;
    }

    AsynchChannel *channel = this->factory_.create_channel ();
    if (channel == 0)
    {
        return 0;
    }
    
    // set manager and proactor for the channel
    channel->set_manager (this);

    // add to the active channels
    active_channels_.insert_channel (channel);

    // update statistics
    ++this->stats_.total_channels_;
    ++this->stats_.current_channels_;
    if (this->stats_.peak_channels_ < this->stats_.current_channels_)
    {
        this->stats_.peak_channels_ = this->stats_.current_channels_;
    }

    return channel;
}

void
ChannelManager::free_channel (AsynchChannel *channel)
{
    AsynchChannel::Info info;
    channel->get_info (info);

    //if (this->get_log_level () < 2)
    {
         info.print ("FINISHED");
    }
    Guard_Monitor guard (monitor_);

    this->stats_.total_snd_ += info.total_snd_;
    this->stats_.total_rcv_ += info.total_rcv_;
    this->stats_.total_w_   += info.total_w_;
    this->stats_.total_r_   += info.total_r_;

    if (ACE_BIT_ENABLED (this->flags_, 
                         FLG_CHECK_ACTIVE | FLG_CLOSE_ACTIVE) &&
        channel == *this->check_iterator_ )
    {
        ACE_SET_BITS (this->flags_, FLG_FREE_CHANNEL);
        return;
    }

    this->free_channel_internal (channel);
}

void
ChannelManager::free_channel_internal (AsynchChannel *channel)
{
    this->active_channels_.remove_channel (channel);

    --this->stats_.current_channels_;

    this->factory_.destroy_channel (channel);

    // notify if necessary
    if (this->state_ != ST_ACTIVE &&
        active_channels_.empty () &&
        this->timer_id_ == -1)
    {
        monitor_.broadcast ();
    }
}

}  //namespace Terabit 


