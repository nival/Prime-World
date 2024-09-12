#include "naio/stdafx.h"
#include "naio/ChannelContext.h"
#include "naio/ConnectionContext.h"

namespace naio
{

ChannelContext::ChannelContext(Terabit::AsynchChannelPtr const & channel, 
                               ConnectionContextStrongPtr const & spconn)
  :id_((ChannelContextId)-1),
  channel_(channel),
  spconn_(spconn)
{
}

ChannelContext::~ChannelContext()
{

}

}
