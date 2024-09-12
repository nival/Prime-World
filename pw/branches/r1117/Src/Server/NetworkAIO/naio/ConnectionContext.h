#pragma once
#include "naio/Types.h"
#include <ace/INET_Addr.h>

namespace naio
{
  class ConnectionContext
  {
    friend class ChannelManager;

  public:
    typedef ACE_Strong_Bound_Ptr<ConnectionContext, ACE_SYNCH_MUTEX>    StrongPtr;
    typedef ACE_Weak_Bound_Ptr<ConnectionContext, ACE_SYNCH_MUTEX>      WeakPtr;

  public:
    ConnectionContext(void* act)
      :usercontext_(act),
      connid_(static_cast< unsigned int >(-1))
    {}
    ~ConnectionContext()
    {}

  public:
    unsigned int id() const;
    unsigned int connid() const;
    void* userContext() const;
    void userContext(void* userctx);
    ChannelContextStrongPtr channelContext() const;
    bool invalid() const;
    ACE_INET_Addr localAddr() const;
    ACE_INET_Addr remoteAddr() const;

  private:
    void channelContext(ChannelContextStrongPtr const & spcc);

  private:
    ChannelContextWeakPtr wpctx_;
    void* usercontext_;
    unsigned int connid_;
  };

  inline
  unsigned int ConnectionContext::connid() const
  {
    return connid_;
  }

  inline
  void* ConnectionContext::userContext() const
  {
    return usercontext_;
  }

  inline
  void ConnectionContext::userContext(void* userctx)
  {
    usercontext_ = userctx;
  }
}
