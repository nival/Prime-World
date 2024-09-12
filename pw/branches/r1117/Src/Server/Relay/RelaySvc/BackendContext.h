#pragma once

#include "PeerContext.h"
#include "Network/TransportUtils.h"
#include <ace/Bound_Ptr.h>
#include "TransportProtocol.h"
#include <map>
#include "Types.h"
#include "ITrafficTrackerFactory.h"

namespace Relay
{

class ClientContext;
class OpenChnl2SvcOp;
class C2STransmissionOp;
class C2SPingOp;

struct BackendPipeId
{
  Transport::TClientId cid_;
  Transport::TPipeId pid_;

  BackendPipeId(Transport::TClientId const & cid, Transport::TPipeId const & pid)
    :cid_(cid),
    pid_(pid)
  {
  }

  bool operator == (BackendPipeId const & bpid) const
  {
    return (cid_ == bpid.cid_ && pid_ == bpid.pid_);
  }

  bool operator < (BackendPipeId const & bpid) const
  {
    if (cid_ < bpid.cid_ || (cid_ == bpid.cid_ && pid_ < bpid.pid_))
      return true;

    return false;
  }
};

static const BackendPipeId INVALID_BACKEND_PIPE_ID(Transport::autoAssignClientId, Transport::EKnownPipeId::Invalid);

typedef unsigned int  ServiceId;
const ServiceId INVALID_SERVICE_ID = INVALID_CONTEXT_ID;

class BackendContext : public PeerContext, public StrongFromThis<BackendContext>
{
public:
  BackendContext();
  ~BackendContext();

public:

  int open(Transport::TServiceId const & svcid, ContextId const & id, Terabit::AsynchChannelPtr const & chnl,
           StrongMT<ITrafficTrackerFactory> const & ttf);
  bool close(bool active);

  BackendPipeId RegisterOpenChnlOp(OpenChnl2SvcOp* op);
  OpenChnl2SvcOp* FindOpenChnlOp(BackendPipeId const & bpid);
  OpenChnl2SvcOp* UnregisterOpenChnlOp(BackendPipeId const & bpid);
  int CheckOpenChnlOpTimeout();

  Transport::TPipeId GeneratePipeId(Transport::TClientId const & cid);
  void FreePipeId(Transport::TClientId const& cid);

  int HandleOpenChannelRequest(Transport::OpenChannelRequest* pMsg, Transport::TClientId const & cid);
  int HandleOutput(C2STransmissionOp* op);
  int HandleOutput(C2SPingOp* op);
  int HandleCloseChannel(Transport::CloseChannelMessage* pMsg);
  int HandleAddRecipientResponse(Transport::AddRecipientResponse* pMsg);
  int HandleRemoveRecipient(Transport::RemoveRecipientMessage* pMsg);

  unsigned long disableRead();
  unsigned long enableRead();

  bool AttachUnicastPipe(UnicastPipeSP const & sp);
  void DetachUnicastPipe(UnicastPipeSP const & sp);
  UnicastPipeSP FindUnicastPipe(Transport::TClientId const & cid);
  unsigned int UnicastPipeCount() const;

  MulticastPipeSP RegisterMulticastPipe();
  MulticastPipeSP FindMulticastPipe(Transport::TPipeId const & _pipeid);
  MulticastPipeSP UnregisterMulticastPipe(Transport::TPipeId const & _pipeid);

  ClientContextSP FindClientContext(Transport::TClientId const & cid);

  long openingChannelTimeoutCounter() const;
  long incOpeningChannelTimeoutCounter();
  void resetOpeningChannelTimeoutCounter();

public:
  Transport::TServiceId const & svcid() const;
  Transport::TServiceId const & svctxid() const;
  StrongMT<ITrafficTrackerFactory> trafficTrackerFactory() const;

private:
  typedef std::map<BackendPipeId, OpenChnl2SvcOp*>  OpenChnlOpsT;
  typedef std::map<Transport::TClientId, Transport::ClientIdGenerator> User2IdGenMapT;
  typedef std::map<Transport::TClientId, UnicastPipeSP> User2UnicastPipeT;
  typedef std::map<Transport::TPipeId, MulticastPipeSP> MulticastPipesT;

  ACE_Thread_Mutex openChnlOpsMutex_;
  OpenChnlOpsT openChnlOps_;
  ACE_Atomic_Op<ACE_Thread_Mutex, long> openingChannelTimeoutCounter_;

  ACE_Thread_Mutex user2idgenMutex_;
  User2IdGenMapT user2idgen_;

  mutable ACE_Thread_Mutex user2pipeMutex_;
  User2UnicastPipeT user2pipe_;

  Transport::TServiceId svcid_;
  Transport::TServiceId svctxid_;
  TransportProtocolHandler tph_;

  StrongMT<ITrafficTrackerFactory> ttf_;

  MulticastPipesT  multicastPipes_;
  mutable ACE_Thread_Mutex multicastPipesMutex_;
};

inline
Transport::TServiceId const & BackendContext::svcid() const
{
  return svcid_;
}

inline
Transport::TPipeId BackendContext::GeneratePipeId(Transport::TClientId const & cid)
{
  ACE_Guard<ACE_Thread_Mutex> lock(user2idgenMutex_);
  Transport::ClientIdGenerator& gen = user2idgen_[cid];
  return gen.Generate();
}

inline
void BackendContext::FreePipeId(Transport::TClientId const & cid)
{
  ACE_Guard<ACE_Thread_Mutex> lock(user2idgenMutex_);
  User2IdGenMapT::iterator it = user2idgen_.find(cid);
  if (it != user2idgen_.end())
    it->second.Release(cid);
}

inline
StrongMT<ITrafficTrackerFactory> BackendContext::trafficTrackerFactory() const
{
  return ttf_;
}

inline
unsigned int BackendContext::UnicastPipeCount() const
{
  ACE_Guard<ACE_Thread_Mutex> lock(user2pipeMutex_);
  return user2pipe_.size();
}

inline
Transport::TServiceId const & BackendContext::svctxid() const
{
  return svctxid_;
}

inline
long BackendContext::openingChannelTimeoutCounter() const
{
  return openingChannelTimeoutCounter_.value();
}

inline
long BackendContext::incOpeningChannelTimeoutCounter()
{
  return ++openingChannelTimeoutCounter_;
}

inline
void BackendContext::resetOpeningChannelTimeoutCounter()
{
  openingChannelTimeoutCounter_ = 0;
}

}
