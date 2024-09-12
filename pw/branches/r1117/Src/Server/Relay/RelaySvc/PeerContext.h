#pragma once
#include <IOTerabit/AsynchChannel.h>
#include <ace/Atomic_Op.h>
#include <Network/TransportUtils.h>
#include "Resource.h"

namespace Relay
{

typedef unsigned int  ContextId;
const ContextId INVALID_CONTEXT_ID = 0xFFFFFFFF;

class PeerContext : public Resource
{
  friend class Operation;

public:

  PeerContext()
    :id_(INVALID_CONTEXT_ID),
    disableReadCount_(0)
  {
  }

  ~PeerContext() {}

public:
  ContextId const & id() const;
  bool theSameChannel(Terabit::AsynchChannel* chnl) const;
  unsigned int channelId() const;

  int open(ContextId const & id, Terabit::AsynchChannelPtr const & chnl);
  bool close();

  unsigned long disableRead();
  unsigned long enableRead();

  ACE_Message_Block* allocMsg(size_t sz);
  void freeMsg(ACE_Message_Block* mb);

  Transport::TPipeId generatePipeId();
  void freePipeId(Transport::TPipeId const & _pid);
  int registerPipeId(Transport::TPipeId const & pid);
  int unregisterPipeId(Transport::TPipeId const & pid);

protected:
  Terabit::AsynchChannelPtr const & channel() const;

private:
  int registerPipeId_(Transport::TPipeId const & pid);
  int unregisterPipeId_(Transport::TPipeId const & pid);

private:
  ContextId id_;
  Terabit::AsynchChannelPtr channel_;
  ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> disableReadCount_;
  mutable ACE_Thread_Mutex mutex_;
  unsigned int channelId_;
  Transport::PipeIdGenerator pipeIdGenerator_;
  typedef vector<Transport::TPipeId> PipeIdsT;
  PipeIdsT registeredPipeIds_;
  mutable ACE_Thread_Mutex pipeidsMutex_;
};

inline
Terabit::AsynchChannelPtr const & PeerContext::channel() const
{
  return channel_;
}

inline
ContextId const & PeerContext::id() const
{
  return id_;
}

inline
bool PeerContext::theSameChannel(Terabit::AsynchChannel* chnl) const
{
  return (channelId_ == chnl->get_id());
}

inline
unsigned int PeerContext::channelId() const
{
  return channelId_;
}

}
