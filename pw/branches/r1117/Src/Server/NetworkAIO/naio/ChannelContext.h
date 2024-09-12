#pragma once
#include <ace/Bound_Ptr.h>
#include <IOTerabit/AsynchChannel.h>
#include "naio/Types.h"

namespace naio
{
  typedef unsigned int  ChannelContextId;
  const ChannelContextId INVALID_CONTEXT_ID = 0xFFFFFFFF;

  class ChannelContext : public StrongFromThis<ChannelContext>
  {
    friend class ChannelManager;

  public:
    typedef ACE_Strong_Bound_Ptr<ChannelContext, ACE_SYNCH_MUTEX>    StrongPtr;
    typedef ACE_Weak_Bound_Ptr<ChannelContext, ACE_SYNCH_MUTEX>      WeakPtr;

  public:
    ChannelContext(Terabit::AsynchChannelPtr const & channel, ConnectionContextStrongPtr const & spconn);
    ~ChannelContext();

  public:
    ChannelContextId id() const
    {
      return id_;
    }

    void id(ChannelContextId const & _id)
    {
      id_ = _id;
    }

    Terabit::AsynchChannelPtr const & channel() const
    {
      return channel_;
    }

    ConnectionContextStrongPtr const & connctx() const
    {
      return spconn_;
    }

  private:
    ChannelContextId id_;
    Terabit::AsynchChannelPtr channel_;
    ConnectionContextStrongPtr spconn_;
  };
}
