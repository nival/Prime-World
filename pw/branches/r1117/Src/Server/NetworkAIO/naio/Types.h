#pragma once

#include "naio/Status.h"
#include <ace/Bound_Ptr.h>
#include <ace/Synch_Traits.h>
#include <ace/Thread_Mutex.h>
#include <ace/Log_Msg_Callback.h>

namespace naio
{

  template<typename T>
  class StrongFromThis
  {
  public:
    void setWeakPtr(ACE_Weak_Bound_Ptr<T, ACE_SYNCH_MUTEX> const & wp)
    {
      wp_ = wp;
    }

    ACE_Strong_Bound_Ptr<T, ACE_SYNCH_MUTEX> getStrongPtr() const
    {
      return wp_.strong();
    }

    ACE_Weak_Bound_Ptr<T, ACE_SYNCH_MUTEX> const & getWeakPtr() const
    {
      return wp_;
    }

  private:
    ACE_Weak_Bound_Ptr<T, ACE_SYNCH_MUTEX> wp_;
  };

  template<typename T>
  ACE_Strong_Bound_Ptr<T, ACE_SYNCH_MUTEX> GetStrongFromThis(StrongFromThis<T>* p)
  {
    return p->getWeakPtr().strong();
  }

  class ChannelContext;
  typedef ACE_Strong_Bound_Ptr<ChannelContext, ACE_SYNCH_MUTEX> ChannelContextStrongPtr;
  typedef ACE_Strong_Bound_Ptr<ChannelContext, ACE_SYNCH_MUTEX> ChannelContextSP;
  typedef ACE_Weak_Bound_Ptr<ChannelContext, ACE_SYNCH_MUTEX> ChannelContextWeakPtr;
  typedef ACE_Weak_Bound_Ptr<ChannelContext, ACE_SYNCH_MUTEX> ChannelContextWP;

  class ConnectionContext;
  typedef ACE_Strong_Bound_Ptr<ConnectionContext, ACE_SYNCH_MUTEX>    ConnectionContextStrongPtr;
  typedef ACE_Strong_Bound_Ptr<ConnectionContext, ACE_SYNCH_MUTEX>    ConnectionContextSP;
  typedef ACE_Weak_Bound_Ptr<ConnectionContext, ACE_SYNCH_MUTEX>      ConnectionContextWeakPtr;
  typedef ACE_Weak_Bound_Ptr<ConnectionContext, ACE_SYNCH_MUTEX>      ConnectionContextWP;

  class Driver;
  typedef ACE_Strong_Bound_Ptr<Driver, ACE_SYNCH_MUTEX>    DriverStrongPtr;
  typedef ACE_Strong_Bound_Ptr<Driver, ACE_SYNCH_MUTEX>    DriverSP;
  typedef ACE_Weak_Bound_Ptr<Driver, ACE_SYNCH_MUTEX>      DriverWeakPtr;
  typedef ACE_Weak_Bound_Ptr<Driver, ACE_SYNCH_MUTEX>      DriverWP;

  typedef ACE_Strong_Bound_Ptr< ::ACE_Log_Msg_Callback, ACE_SYNCH_MUTEX >    LogMsgCallbackStrongPtr;
  typedef ACE_Strong_Bound_Ptr< ::ACE_Log_Msg_Callback, ACE_SYNCH_MUTEX >    LogMsgCallbackSP;

  class Acceptor;
  typedef ACE_Strong_Bound_Ptr<naio::Acceptor, ACE_SYNCH_MUTEX> AcceptorStrongPtr;
  typedef ACE_Strong_Bound_Ptr<naio::Acceptor, ACE_SYNCH_MUTEX> AcceptorSP;
  typedef ACE_Weak_Bound_Ptr<naio::Acceptor, ACE_SYNCH_MUTEX> AcceptorWeakPtr;
  typedef ACE_Weak_Bound_Ptr<naio::Acceptor, ACE_SYNCH_MUTEX> AcceptorWP;

}
