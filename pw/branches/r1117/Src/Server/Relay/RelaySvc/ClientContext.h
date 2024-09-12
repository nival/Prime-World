#pragma once

#include "PeerContext.h"
#include "Network/TransportUtils.h"
#include <ace/Bound_Ptr.h>
#include <ace/Atomic_Op.h>
#include "TransportProtocol.h"
#include "UnicastPipe.h"
#include "OpenChnl2ClientOp.h"
#include <map>

namespace Relay
{

class BackendContext;

typedef Transport::TClientId ClientId;
const ClientId INVALID_CLIENT_ID = INVALID_CONTEXT_ID;

class ClientContext : public PeerContext, public StrongFromThis<ClientContext>
{
public:
  typedef vector<UnicastPipeSP> UnicastPipesT;
  typedef std::vector<MulticastPipeSP> MulticastPipesT;

public:
  ClientContext();
  ~ClientContext();

  int open(ClientId const & cid, Terabit::AsynchChannelPtr const & chnl,
    bool trackInput, Transport::TServiceId const & trackedSvcId, unsigned int notificationThreshold);
  void close();
  void closeConnection();

public:

  void userid(ClientId const & userid);
  ClientId const & userid() const;

  size_t UnicastPipeCount() const;

  bool trackInput() const;
  void trackInput(bool f);

  Transport::TServiceId const & getTrackedSvcId() const;
  Transport::TPipeId const & getTrackedPipe() const;

  ACE_Time_Value const & getLastInputDataTime();
  void setLastInputDataTime(ACE_Time_Value const & tv);

  ACE_Time_Value const & getLastInputDataTimeThreshold();
  void setLastInputDataTimeThreshold(ACE_Time_Value const & tv);

public:

  UnicastPipeSP RegisterUnicastPipe(Transport::TServiceId const & svcid, 
                                  BackendContextSP const & spbc, 
                                  Transport::TPipeId const & cpid, 
                                  Transport::TPipeId const & svcpid);

  UnicastPipeSP FindUnicastPipe(Transport::TPipeId const & cpid);
  UnicastPipeSP FindUnicastPipe(Transport::TServiceId const & svcid, Transport::TPipeId const & svcpid);
  int UnregisterUnicastPipe(Transport::TPipeId const & cpid);

  Transport::TPipeId RegisterOpenChnlOp(OpenChnl2ClientOpPtr const & op);
  OpenChnl2ClientOpPtr FindOpenChnlOp(Transport::TPipeId const & _pid) const;
  OpenChnl2ClientOpPtr UnregisterOpenChnlOp(Transport::TPipeId const & _pid);
  void CheckOpenChnlOpTimeout();

  int HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg);
  int HandleOpenChannelRequest(Transport::OpenChannelRequest* pMsg);
  int HandleCloseChannel(Transport::CloseChannelMessage* pMsg, bool checkPipe = true);
  int HandleOutput(Transport::TPipeId const & cpid, char const * data, size_t size, unsigned long seqNum);
  int HandleOutput(Transport::ThroughPingMessage* pmsg);

  void TrackInputThreshold(Transport::TPipeId const & cpid);
  int CloseUnicastPipe(Transport::TPipeId const & cpid);
  void ClosePipes();

  int AttachMulticastPipe(MulticastPipeSP const & _pipe);
  int RemoveFromMulticastPipe(MulticastPipeSP const & _pipe);

private:
  UnicastPipeSP FindUnicastPipe_(Transport::TServiceId const & svcid, Transport::TPipeId const & svcpid);
  UnicastPipeSP FindUnicastPipe_(Transport::TPipeId const & cpid);
  int CloseUnicastPipe_(UnicastPipeSP const & _pipe);

private:

  ClientId  userid_;

  UnicastPipesT  unicastPipes_;
  mutable ACE_Thread_Mutex unicastPipesMutex_;

  TransportProtocolHandler tph_;

  //  track input params
  bool                  trackInput_;
  ACE_Time_Value        lastInputDataTime_;
  ACE_Time_Value        lastInputDataTimeThreshold_;
  Transport::TServiceId trackedSvcId_;
  Transport::TPipeId    trackedPipe_;

  ACE_Atomic_Op<ACE_Thread_Mutex, long> logQlenThresholdFlag;

  typedef std::map<Transport::TPipeId, OpenChnl2ClientOpPtr>  OpenChnlOpsT;

  mutable ACE_Thread_Mutex openChnlOpsMutex_;
  OpenChnlOpsT openChnlOps_;
  Transport::PipeIdGenerator openingChannelPipes_;

  MulticastPipesT  multicastPipes_;
  mutable ACE_Thread_Mutex multicastPipesMutex_;
};

inline
void ClientContext::userid(ClientId const & userid)
{
  userid_ = userid;
}

inline
ClientId const & ClientContext::userid() const
{
  return userid_;
}

inline
size_t ClientContext::UnicastPipeCount() const
{
  ACE_Guard<ACE_Thread_Mutex> lock(unicastPipesMutex_);
  return unicastPipes_.size();
}

inline
bool ClientContext::trackInput() const
{
  return trackInput_;
}

inline
void ClientContext::trackInput(bool f)
{
  trackInput_ = f;
}

inline
Transport::TServiceId const & ClientContext::getTrackedSvcId() const
{
  return trackedSvcId_;  
}

inline
Transport::TPipeId const & ClientContext::getTrackedPipe() const
{
  return trackedPipe_;
}

inline
ACE_Time_Value const & ClientContext::getLastInputDataTime()
{
  return lastInputDataTime_;

}

inline
void ClientContext::setLastInputDataTime(ACE_Time_Value const & tv)
{
  lastInputDataTime_ = tv;
}

inline
ACE_Time_Value const & ClientContext::getLastInputDataTimeThreshold()
{
  return lastInputDataTimeThreshold_;
}

inline
void ClientContext::setLastInputDataTimeThreshold(ACE_Time_Value const & tv)
{
  lastInputDataTimeThreshold_ = tv;
}

}
