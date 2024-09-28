
#include "IOTerabit/RefCntProtocol.h"
#include "ace/Log_Msg.h"

namespace Terabit {

RefCntProtocol::RefCntProtocol (ProtocolFactory & factory) 
: Protocol (factory)
, channel_ (0)
, self_    (0)
{
    ;
}

RefCntProtocol::~RefCntProtocol () 
{
    ACE_ASSERT (this->channel_ == 0);
    ACE_ASSERT (!this->self_);
}

void
RefCntProtocol::reset ()
{
    ACE_ASSERT (this->channel_ == 0);
    ACE_ASSERT (!this->self_);
    RefCount::set (0);
    this->on_reset ();
}

void
RefCntProtocol::free ()
{
    this->get_protocol_factory ().destroy_protocol (this);
}

int 
RefCntProtocol::on_channel_opened (AsynchChannel *channel)
{
    RefCountPtr tmp (this);
    {
        RefCountGuard guard (*this);
        ACE_ASSERT (this->channel_ == 0);
        this->channel_ = channel;
        this->self_.swap (tmp);
    }
    return this->on_channel_up (channel);
}

void 
RefCntProtocol::on_channel_closed (AsynchChannel *channel)
{
    this->on_channel_done (channel);
    RefCountPtr tmp (0);
    {
        RefCountGuard guard (*this);
        this->channel_ = 0;
        this->self_.swap (tmp);
    }
}

int 
RefCntProtocol::close ()
{
    AsynchChannelPtr tmp (0);
    {
        RefCountGuard guard (*this);
        if (this->channel_ == 0)
        {
            return 1; // closed
        }
        tmp = this->channel_;
    }


    AsynchChannel::State state = tmp->close (true);
    if (state == AsynchChannel::ST_CLOSED)
    {
        return 1;
    }
    return 0;
}


}  //namespace Terabit 


