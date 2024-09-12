#pragma once
#include <ace/Synch_T.h>
#include <ace/Bound_Ptr.h>

namespace Relay
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

class UnicastPipe;

typedef ACE_Strong_Bound_Ptr<UnicastPipe, ACE_SYNCH_MUTEX>    UnicastPipeStrongPtr;
typedef UnicastPipeStrongPtr                                  UnicastPipeSP;
typedef ACE_Weak_Bound_Ptr<UnicastPipe, ACE_SYNCH_MUTEX>      UnicastPipeWeakPtr;
typedef UnicastPipeWeakPtr                                    UnicastPipeWP;

class MulticastPipe;
typedef ACE_Strong_Bound_Ptr<MulticastPipe, ACE_SYNCH_MUTEX>    MulticastPipeStrongPtr;
typedef MulticastPipeStrongPtr                                  MulticastPipeSP;
typedef ACE_Weak_Bound_Ptr<MulticastPipe, ACE_SYNCH_MUTEX>      MulticastPipeWeakPtr;
typedef MulticastPipeWeakPtr                                    MulticastPipeWP;

class ClientContext;
typedef ACE_Strong_Bound_Ptr<ClientContext, ACE_SYNCH_MUTEX>  ClientContextStrongPtr;
typedef ClientContextStrongPtr                                ClientContextSP;
typedef ACE_Weak_Bound_Ptr<ClientContext, ACE_SYNCH_MUTEX>    ClientContextWeakPtr;
typedef ClientContextWeakPtr                                  ClientContextWP;

class BackendContext;
typedef ACE_Strong_Bound_Ptr<BackendContext, ACE_SYNCH_MUTEX>  BackendContextStrongPtr;
typedef BackendContextStrongPtr                                BackendContextSP;
typedef ACE_Weak_Bound_Ptr<BackendContext, ACE_SYNCH_MUTEX>    BackendContextWeakPtr;
typedef BackendContextWeakPtr                                  BackendContextWP;

}
