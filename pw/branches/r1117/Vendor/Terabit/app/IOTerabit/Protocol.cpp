
#include "IOTerabit/Protocol.h"
#include "ace/Log_Msg.h"

namespace Terabit {

Protocol::Protocol (ProtocolFactory & factory) 
: factory_ (factory)
{
    ;
}

Protocol::~Protocol () 
{
}

MessageBlockFactory *
Protocol::get_message_block_factory() const 
{ 
    return factory_.get_message_block_factory (); 
}

void
Protocol::on_channel_closed (AsynchChannel *channel)
{
    ACE_UNUSED_ARG (channel);
    factory_.destroy_protocol (this);
}

int
Protocol::on_write_completed (AsynchChannel *channel)
{
    ACE_UNUSED_ARG (channel);
    return 0;
}

int
Protocol::on_timeout (AsynchChannel *channel,
                      const void    *arg)
{
    ACE_UNUSED_ARG (channel);
    ACE_UNUSED_ARG (arg);
    return 0;
}

int 
Protocol::check_activity (AsynchChannel  *channel,
                          const ACE_Time_Value& last_op_time)
{
    ACE_UNUSED_ARG (channel);
    ACE_UNUSED_ARG (last_op_time);

    return 0;
}

//--------------------------------------------------------
//
//--------------------------------------------------------
ProtocolFactory::ProtocolFactory(const ACE_TCHAR *name,
                                 int              logLevel)
: name_       (name)
, log_level_  (logLevel)
{
}

ProtocolFactory::~ProtocolFactory()
{
}

}  //namespace Terabit 


