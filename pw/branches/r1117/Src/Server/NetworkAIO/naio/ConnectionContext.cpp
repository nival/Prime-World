#include "naio/stdafx.h"
#include "naio/ConnectionContext.h"
#include "naio/ChannelContext.h"
#include <IOTerabit/AsynchChannel.h>

namespace naio
{
  unsigned int ConnectionContext::id() const
  {
    ChannelContextStrongPtr spctx = wpctx_.strong();
    if (!spctx.null())
      return spctx->id();

    return static_cast< unsigned int >(-1);
  }

  ChannelContextStrongPtr ConnectionContext::channelContext() const
  {
    return wpctx_.strong();
  }

  void ConnectionContext::channelContext(ChannelContextStrongPtr const & spcc)
  {
    ACE_ASSERT(!spcc.null());
    wpctx_ = spcc;
    connid_ = spcc->channel()->get_id();
  }

  bool ConnectionContext::invalid() const
  {
    return wpctx_.strong().null();
  }

  ACE_INET_Addr ConnectionContext::localAddr() const
  {
    ChannelContextStrongPtr spcc = wpctx_.strong();
    if (!spcc.null())
    {
      ACE_Addr const & addr = spcc->channel()->local_addr();
      if (AF_INET == addr.get_type())
      {
        return ACE_INET_Addr(static_cast<const ACE_INET_Addr&> (addr));
      }
    }

    return ACE_INET_Addr();
  }

  ACE_INET_Addr ConnectionContext::remoteAddr() const
  {
    ChannelContextStrongPtr spcc = wpctx_.strong();
    if (!spcc.null())
    {
      ACE_Addr const & addr = spcc->channel()->remote_addr();
      if (AF_INET == addr.get_type())
      {
        return ACE_INET_Addr(static_cast<const ACE_INET_Addr&> (addr));
      }
    }

    return ACE_INET_Addr();
  }

}
