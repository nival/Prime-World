
#include "ChatProtocol.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_strings.h"

Job::Job (ChatProtocol      *chat,
          ACE_Message_Block *mb)
: chat_ (chat)
, mb_   (mb)
{
}

Job::~Job ()
{
    this->cancel ();
}

        
void 
Job::cancel () 
{ 
    if (this->chat_)
    {
        this->chat_->get_message_block_factory ()->free_msg (this->mb_);
    }
    this->reset ();
}

void
Job::set (Job & other) 
{
    this->chat_ = other.chat_;
    this->mb_ = other.mb_;
    other.reset ();
}

void 
Job::execute () 
{
    if (this->chat_)
    {
        this->chat_->process_message (this->mb_);
    }
    this->reset ();
}

void 
Job::reset () 
{
    this->chat_ = 0;
    this->mb_ = 0;
}



// *************************************************************
//   Chat Protocol - chat room 
// *************************************************************

ChatProtocol::ChatProtocol (JobThreadPool &  job_pool,
                            const ACE_TCHAR *name, 
                            int              log_level)
: Terabit::ProtocolFactory (name, log_level) 
, Terabit::Protocol        ((Terabit::ProtocolFactory &) (*this))
, mon_                     ()
, channels_                ()
, mb_factory_              (2048)
, job_pool_                (job_pool)
{
}

ChatProtocol::~ChatProtocol ()
{
    Guard_Monitor guard (mon_);
    ACE_ASSERT (channels_.empty());
}

Terabit::MessageBlockFactory * 
ChatProtocol::get_message_block_factory ()
{
    return &this->mb_factory_;
}

Terabit::Protocol *
ChatProtocol::create_protocol (const void *act)
{
    return  this;
}

void 
ChatProtocol::destroy_protocol (Terabit::Protocol * protocol) 
{ 
    return;
}

int
ChatProtocol::validate_connection (bool  success,
                                   const ACE_Addr &remote,
                                   const ACE_Addr &local,
                                   const void *act)
{
     return 0;
}

void
ChatProtocol::reset ()
{
}

int
ChatProtocol::on_channel_opened (Terabit::AsynchChannel *channel)
{
    channel->set_duplex_mode (false);
    channel->enable_read ();                 // this is default
    channel->enable_write_notifications ();  // this is not

    Guard_Monitor guard (mon_);
   
    ChannelData data = { 0, false};

    std::pair<ChannelMap::iterator, bool> rc = 
        channels_.insert(ChannelMap::value_type (channel, data ));

    ACE_ASSERT (rc.second == true);
    return 0;

}

void 
ChatProtocol::on_channel_closed (Terabit::AsynchChannel *channel)
{
    Guard_Monitor guard (mon_);

    ChannelMap::iterator itr = channels_.find (channel);
    ACE_ASSERT (itr != channels_.end ());

    ChannelData& data = itr->second;

    data.flg_del_ = true;

    while (data.count_ != 0)
    {
        guard.wait ();
    }

    channels_.erase (itr);
}

int
ChatProtocol::on_write_completed (Terabit::AsynchChannel *channel)
{
    channel->enable_read ();
    return 0;
}

int
ChatProtocol::on_read_completed (Terabit::AsynchChannel *channel,
                                 const char             *data,
                                 size_t                  length)
{
    unsigned int consumed = 0;

    channel->disable_read ();

    while (length > 0)
    {
        const char *msg = data;

        const char *ptr_nl = (const char*) ACE_OS::memchr (data, '\n', length);
        if (ptr_nl == 0)    // no NL in the buffer
        {
            if (length < channel->get_read_size())
            {
                break; // read more
            }

            // read buffer is full, but no NL
            return -1;  // protocol error
        }

        size_t  msglen = (ptr_nl - msg) + 1;

        if (enqueue_message (channel, msg, msglen) < 0)
        {
            return -1;
        }

        data   += msglen;
        length -= msglen;
        consumed += msglen;
    }
    return consumed;
}

int
ChatProtocol::enqueue_message(Terabit::AsynchChannel *channel,
                              const char             *data,
                              size_t                  length)
{
    ACE_TCHAR buf1 [256];
    ACE_TCHAR buf2 [128];
    
    TRB_Sock_Addr::to_string (channel->remote_addr(),
                              buf1,
                              sizeof (buf1)/sizeof (ACE_TCHAR));

    int len1 = ACE_OS::strlen  (buf1);
    int len2 = ACE_OS::sprintf (buf2, " (%d) :", channel->get_id ());

    ACE_Message_Block *mb = 
        mb_factory_.alloc_msg (len1 + len2 + length);
    
    if (mb == 0)
    {
        return -1;
    }

    mb->copy (buf1, len1);
    mb->copy (buf2, len2);
    mb->copy (data, length);

    Job job(this, mb);
    if (!this->get_job_pool().put (job))
    {
        return -1;
    }
    return length;
}

void
ChatProtocol::process_message (ACE_Message_Block *mb)
{
    Guard_Monitor guard (mon_);
    ChannelMap::iterator itr = channels_.begin();

    for (; itr != channels_.end(); ++itr)
    {
        Terabit::AsynchChannel *channel = itr->first;
        ChannelData&            data = itr->second;
        if (!data.flg_del_)
        {
          
            ++data.count_;
            {
                Save_Guard sg(guard, Save_Guard::RELEASE);

                ACE_Message_Block *tmp = mb->duplicate ();
                if (tmp)
                {
                    //tmp->copy (mb->rd_ptr(), mb->length ());

                    channel->start_write(*tmp);
                }
            }
            --data.count_;
        }
        if (data.flg_del_ && data.count_ == 0)
        {
            guard.broadcast ();
        }
    }
    this->mb_factory_.free_msg (mb);
}

