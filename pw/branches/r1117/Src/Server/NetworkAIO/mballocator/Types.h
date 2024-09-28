#pragma once
#include <ace/Bound_Ptr.h>
#include <ace/Synch_Traits.h>
#include <ace/Thread_Mutex.h>

namespace TransportLayer
{
  class MessageBlockFactory;
  typedef ACE_Strong_Bound_Ptr<MessageBlockFactory, ACE_SYNCH_MUTEX>  MessageBlockFactoryStrongPtr;
  typedef ACE_Strong_Bound_Ptr<MessageBlockFactory, ACE_SYNCH_MUTEX>  MessageBlockFactorySP;
  typedef ACE_Weak_Bound_Ptr<MessageBlockFactory, ACE_SYNCH_MUTEX>  MessageBlockFactoryWeakPtr;
  typedef ACE_Weak_Bound_Ptr<MessageBlockFactory, ACE_SYNCH_MUTEX>  MessageBlockFactoryWP;
}

namespace TL = TransportLayer;
