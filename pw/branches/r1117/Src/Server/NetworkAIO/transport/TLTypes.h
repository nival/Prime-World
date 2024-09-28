#pragma once
#include <ace/Bound_Ptr.h>
#include <ace/Synch_Traits.h>
#include <ace/Thread_Mutex.h>
#include <System/Pointers/Pointers.h>

namespace TransportLayer
{
  namespace TL = TransportLayer;

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

  template<typename T>
  struct AsynchCompletionPointer
  {
    AsynchCompletionPointer(ACE_Strong_Bound_Ptr<T, ACE_SYNCH_MUTEX> const & sp)
      :sp_(sp)
    {
    }

    //  This constructor is workaround for Compiler Error C2683
    //  You cannot use dynamic_cast to convert from a non-polymorphic class (a class with no virtual functions)
    AsynchCompletionPointer(T* p)
    {
      sp_ = TL::GetStrongFromThis(p);
    }

    ACE_Strong_Bound_Ptr<T, ACE_SYNCH_MUTEX> sp_;
  };

  template<typename T1, typename T2>
  struct AsynchCompletionPointer2
  {
    AsynchCompletionPointer2(StrongMT<T1> const & sp1,
                             ACE_Strong_Bound_Ptr<T2, ACE_SYNCH_MUTEX> const & sp2)
      :sp1_(sp1),
      sp2_(sp2)
    {
    }

    ~AsynchCompletionPointer2()
    {
      sp1_ = 0;
      sp2_.reset();
    }

    StrongMT<T1> sp1_;
    ACE_Strong_Bound_Ptr<T2, ACE_SYNCH_MUTEX> sp2_;
  };

  class Connection;
  typedef ACE_Strong_Bound_Ptr<Connection, ACE_SYNCH_MUTEX>  ConnectionStrongPtr;
  typedef ACE_Strong_Bound_Ptr<Connection, ACE_SYNCH_MUTEX>  ConnectionSP;
  typedef ACE_Weak_Bound_Ptr<Connection, ACE_SYNCH_MUTEX>  ConnectionWeakPtr;
  typedef ACE_Weak_Bound_Ptr<Connection, ACE_SYNCH_MUTEX>  ConnectionWP;

  class ChannelSuperBase;
  typedef StrongMT<ChannelSuperBase>  IChannelInternalSP;

  class ConnectionManager;
  typedef ACE_Strong_Bound_Ptr<ConnectionManager, ACE_SYNCH_MUTEX>  ConnectionManagerStrongPtr;
  typedef ACE_Strong_Bound_Ptr<ConnectionManager, ACE_SYNCH_MUTEX>  ConnectionManagerSP;
  typedef ACE_Weak_Bound_Ptr<ConnectionManager, ACE_SYNCH_MUTEX>  ConnectionManagerWeakPtr;
  typedef ACE_Weak_Bound_Ptr<ConnectionManager, ACE_SYNCH_MUTEX>  ConnectionManagerWP;

  class MessageBlockFactory;
  typedef ACE_Strong_Bound_Ptr<MessageBlockFactory, ACE_SYNCH_MUTEX>  MessageBlockFactoryStrongPtr;
  typedef ACE_Strong_Bound_Ptr<MessageBlockFactory, ACE_SYNCH_MUTEX>  MessageBlockFactorySP;
  typedef ACE_Weak_Bound_Ptr<MessageBlockFactory, ACE_SYNCH_MUTEX>  MessageBlockFactoryWeakPtr;
  typedef ACE_Weak_Bound_Ptr<MessageBlockFactory, ACE_SYNCH_MUTEX>  MessageBlockFactoryWP;

  template<typename T>
  bool IsValid(ACE_Strong_Bound_Ptr<T, ACE_SYNCH_MUTEX> const & sp)
  {
    return !sp.null();
  }

  template<typename T>
  bool IsValid(StrongMT<T> const & sp)
  {
    return sp != 0;
  }

  template<typename T>
  void ResetPtr(ACE_Strong_Bound_Ptr<T, ACE_SYNCH_MUTEX> const & sp)
  {
    sp.reset();
  }

  template<typename T>
  void ResetPtr(StrongMT<T> & sp)
  {
    sp.Set(0);
  }
}

#include "transport/TLOpsPtr.h"
