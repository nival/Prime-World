
#include "ChatProtocol.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_strings.h"

// *************************************************************
//   Chat Protocol - chat room 
// *************************************************************

ChatProtocol::ChatProtocol (const ACE_TCHAR *name, 
                            int              log_level)
: Terabit::ProtocolFactory (name, log_level) 
, Terabit::Protocol        ((Terabit::ProtocolFactory &) (*this))
, mon_                     ()
, channels_                ()
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
    return 0;
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
ChatProtocol::on_read_completed (Terabit::AsynchChannel *channel,
                                 const char             *data,
                                 size_t                  length)
{
    unsigned int consumed = 0;

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

        if (process_message (channel, msg, msglen) < 0)
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
ChatProtocol::process_message(Terabit::AsynchChannel *channel,
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


    iovec iov [3];
    iov[0].iov_base = buf1;
    iov[0].iov_len  = len1;
    iov[1].iov_base = buf2;
    iov[1].iov_len  = len2;
    iov[2].iov_base = (char*) data;
    iov[2].iov_len  = length;


    Guard_Monitor guard (mon_);
    ChannelMap::iterator itr = channels_.begin();

    for (; itr != channels_.end(); ++itr)
    {
        Terabit::AsynchChannel *channel = itr->first;
        ChannelData&            data = itr->second;
        if (data.flg_del_)
        {
            continue;
        }

        ++data.count_;
        {
            //Save_Guard sg(guard, Save_Guard::RELEASE);
            channel->start_write(iov, 3);
        }
        --data.count_;
         if (data.flg_del_ && data.count_ == 0)
         {
             guard.broadcast ();
         }
    }
    return 0;
}

