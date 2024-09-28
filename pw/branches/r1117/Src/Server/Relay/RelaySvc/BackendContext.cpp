#pragma warning( disable : 4996)
#include "stdafx.h"
#include "TransportMessagesHeaders.h"
#include "ClientContext.h"
#include "OpenChnl2SvcOp.h"
#include "C2STransmissionOp.h"
#include "C2SPingOp.h"
#include "MulticastPipe.h"
#include "BackendContext.h"
#include "RelayServer2Cfg.h"

using namespace Transport;

namespace Relay
{

BackendContext::BackendContext()
  :tph_(0, false, "BackendContext")
{
}

BackendContext::~BackendContext()
{
  NI_PROFILE_FUNCTION;

  ACE_ERROR((LM_INFO, ACE_TEXT("%s (svc=%s svctx=%d)"), 
    __FUNCTION__, svcid().c_str(), id()));

  {
    ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);
    openChnlOps_.clear();
  }

  {
    ACE_Guard<ACE_Thread_Mutex> lock(user2idgenMutex_);
    user2idgen_.clear();
  }
}

int BackendContext::open(Transport::TServiceId const & svcid, ContextId const & id, Terabit::AsynchChannelPtr const & chnl, 
                         StrongMT<ITrafficTrackerFactory> const & ttf)
{
  NI_PROFILE_FUNCTION;

  svcid_ = svcid;
  Transport::GenerateServiceName(svcid, id, &svctxid_);
  ttf_ = ttf;
  return PeerContext::open(id, chnl);
}

bool BackendContext::close(bool active)
{
  NI_PROFILE_FUNCTION;

  if (PeerContext::close())
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("%s (svc=%s svctx=%d svcpipes=%d active=%d)"), 
      __FUNCTION__, svcid().c_str(), id(), UnicastPipeCount(), active));

    if (active)
    {
      //  close multicast pipe
      {
        ACE_Guard<ACE_Thread_Mutex> lock(multicastPipesMutex_);
        for(MulticastPipesT::const_iterator it = multicastPipes_.begin(); it != multicastPipes_.end(); ++it)
        {
          MulticastPipeSP const & pipe = it->second;
          if (pipe->isopen())
          {
            pipe->HandleCloseChannel();
            unregisterPipeId(pipe->svcpipeid());
          }
        }
        multicastPipes_.clear();
      }

      //  send close info
      ACE_Guard<ACE_Thread_Mutex> lock(user2pipeMutex_);
      for(User2UnicastPipeT::const_iterator it=user2pipe_.begin(); it!=user2pipe_.end(); ++it)
      {
        UnicastPipeSP sp(it->second);
        if (sp->close())
        {
          ClientContextSP spcc = sp->cctx().strong();
          if (!spcc.null())
          {
            if (!spcc->isclosed())
            {
              Transport::CloseChannelMessage msg;
              msg.clientAddress = ChannelAddr(sp->cpipeid(), spcc->userid(), autoAssignClientId, sp->lastInS2CSeqNum()+1);
              sp->lastInS2CSeqNum(sp->lastInS2CSeqNum()+1);
              int rc = spcc->HandleCloseChannel(&msg);
              if (rc < 0)
              {
                ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Can't send close channel msg(c=%d svc=%s svctx=%d)"), 
                           __FUNCTION__, spcc->userid(), svcid().c_str(), id()));
              }
              else
              {
                ACE_ERROR((LM_INFO, ACE_TEXT("%s. Send close channel msg(c=%d svc=%s svctx=%d cpid=%d)"), 
                    __FUNCTION__, spcc->userid(), svcid().c_str(), id(), sp->cpipeid()));
              }

              //  unregister unicast pipe in client context
              spcc->UnregisterUnicastPipe(sp->cpipeid());
            }
            else
            {
              ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Client context is already closed(c=%d svc=%s svctx=%d)"), 
                __FUNCTION__, spcc->userid(), svcid().c_str(), id()));
            }
          }
          else
          {
            ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Client context is null(c=%d svc=%s svctx=%d)"), 
              __FUNCTION__, sp->cid(), svcid().c_str(), id()));
          }
        }
        else
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Pipe is already closed(c=%d svc=%s svctx=%d cpid=%d spid=%d)"), 
            __FUNCTION__, sp->cid(), svcid().c_str(), id(), sp->cpipeid(), sp->svcpipeid()));
        }
      }
      user2pipe_.clear();

      //  send failure on open channel operations
      {
        ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);
        OpenChnlOpsT::iterator it = openChnlOps_.begin();
        while (it != openChnlOps_.end())
        {
          OpenChnl2SvcOp* op = it->second;
          //  create fake result message
          Transport::OpenChannelResponse fakemsg = op->GetOpenChannelResponse();
          fakemsg.localPipeId = op->GetBackendPipeId().pid_;
          int rc = op->OnChannelEstablished(OpenChnl2SvcOp::Result::FAIL, &fakemsg, this->getStrongPtr());
          if (rc < 0)
          {
            //  close client
            op->GetClientCtx()->closeConnection();
          }
          
          it = openChnlOps_.begin();
        }
      }
    }

    return true;
  }
  else
  {
    //  already closed
    ACE_ERROR((LM_INFO, ACE_TEXT("%s. Context is already closed(svc=%s svctx=%d)"), 
      __FUNCTION__, svcid().c_str(), id()));
    return false;
  }
}

BackendPipeId BackendContext::RegisterOpenChnlOp(OpenChnl2SvcOp* op)
{
  NI_PROFILE_FUNCTION;

  BackendPipeId bpid = INVALID_BACKEND_PIPE_ID;
  ClientContextSP spcc = op->GetClientCtx();
  if (!spcc.null())
  {
    Transport::TPipeId pid = GeneratePipeId(spcc->userid());
    if (Transport::EKnownPipeId::Invalid != pid)
    {
      ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);
      if (openChnlOps_.insert(std::make_pair(BackendPipeId(spcc->userid(), pid), op)).second)
      {
        bpid.cid_ = spcc->userid();
        bpid.pid_ = pid;
      }
      else
      {
        FreePipeId(pid);
      }
    }
  }

  return bpid;
}

OpenChnl2SvcOp* BackendContext::FindOpenChnlOp(BackendPipeId const & bpid)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);
  OpenChnlOpsT::const_iterator cit = openChnlOps_.find(bpid);
  if (cit != openChnlOps_.end())
    return cit->second;
  else
    return 0;
}

OpenChnl2SvcOp* BackendContext::UnregisterOpenChnlOp(BackendPipeId const & bpid)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);
  OpenChnl2SvcOp* op = 0;
  OpenChnlOpsT::iterator it = openChnlOps_.find(bpid);
  if (it != openChnlOps_.end())
  {
    op = it->second;
    openChnlOps_.erase(it);
    FreePipeId(bpid.pid_);
  }

  return op;
}

int BackendContext::CheckOpenChnlOpTimeout()
{
  NI_PROFILE_FUNCTION;

  {
    ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);
    time_t now = ACE_OS::gettimeofday().sec();

    OpenChnlOpsT openingChannelOps = openChnlOps_;
    for(OpenChnlOpsT::const_iterator it = openingChannelOps.begin(); it != openingChannelOps.end(); ++it)
    {
      OpenChnl2SvcOp* op = it->second;
      if (now - op->GetStartTime() > RelayServer2Cfg::GetOpenBackendChannelTimeout())
      {
        Transport::OpenChannelResponse fakemsg = op->GetOpenChannelResponse();
        op->OnChannelEstablished(OpenChnl2SvcOp::Result::TIMEOUT, &fakemsg, GetStrongFromThis(this));
      }
    }
  }

  if (RelayServer2Cfg::GetOpeningChannelTimeoutCountThreshold() && 
      openingChannelTimeoutCounter() >= RelayServer2Cfg::GetOpeningChannelTimeoutCountThreshold())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Opening channel timeout counter reaches threshold(ch=%d svcid=%s to=%d threshold=%d)"), 
      __FUNCTION__, channelId(), svcid().c_str(), RelayServer2Cfg::GetOpenBackendChannelTimeout(), RelayServer2Cfg::GetOpeningChannelTimeoutCountThreshold()));

    return -1;
  }

  return 0;
}

unsigned long BackendContext::disableRead()
{
  NI_PROFILE_FUNCTION;

  unsigned int cnt = PeerContext::disableRead();
  if (1 == cnt)
  {
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s: done(ch=%d)"), 
      __FUNCTION__, channelId()));
  }
  return cnt;
}

int BackendContext::HandleOpenChannelRequest(Transport::OpenChannelRequest* pMsg, Transport::TClientId const & cid)
{
  NI_PROFILE_FUNCTION;

  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : backend context is already closed(ch=%d c=%d t=%s s=%s)"), __FUNCTION__, 
      channelId(), cid, pMsg->clientAddress.target.c_str(), pMsg->clientAddress.source.c_str()));
    return -1;
  }

  return tph_.HandleOutput(pMsg, ChannelAddr( EKnownPipeId::NetLogic, cid, pMsg->clientAddress.client ), channel().get());
}

int BackendContext::HandleOutput(C2STransmissionOp* op)
{
  NI_PROFILE_FUNCTION;

  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : backend context is already closed(ch=%d c=%d cpid=%d svc=%s svcpid=%d)"), __FUNCTION__, 
      channelId(), op->GetClientId(), op->GetClientPipeId(), svctxid().c_str(), op->GetSvcPipeId()));
    return -1;
  }

  return op->Complete(channel().get(), &tph_);
}

int BackendContext::HandleOutput(C2SPingOp* op)
{
  NI_PROFILE_FUNCTION;
  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : backend context is already closed(ch=%d c=%d cpid=%d svc=%s svcpid=%d)"), __FUNCTION__, 
      channelId(), op->GetClientId(), op->GetClientPipeId(), svctxid().c_str(), op->GetSvcPipeId()));
    return -1;
  }

  return op->Execute(channel().get(), &tph_);
}

int BackendContext::HandleCloseChannel(Transport::CloseChannelMessage* pMsg)
{
  NI_PROFILE_FUNCTION;

  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : backend context is already closed(ch=%d c=%d svc=%s svcpid=%d)"), __FUNCTION__, 
      channelId(), pMsg->clientAddress.client, svctxid().c_str(), pMsg->clientAddress.pipe));
    return -1;
  }

  return tph_.HandleOutput(pMsg, ChannelAddr( EKnownPipeId::NetLogic, pMsg->clientAddress.client ), channel().get());
}

int BackendContext::HandleAddRecipientResponse(Transport::AddRecipientResponse* pMsg)
{
  NI_PROFILE_FUNCTION;

  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : backend context is already closed(ch=%d c=%d svc=%s svcpid=%d)"), __FUNCTION__, 
      channelId(), pMsg->recipient, svctxid().c_str(), pMsg->caddr.pipe));
    return -1;
  }

  return tph_.HandleOutput(pMsg, ChannelAddr( EKnownPipeId::NetLogic, pMsg->caddr.client ), channel().get());
}

int BackendContext::HandleRemoveRecipient(Transport::RemoveRecipientMessage* pMsg)
{
  NI_PROFILE_FUNCTION;

  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : backend context is already closed(ch=%d c=%d svc=%s svcpid=%d)"), __FUNCTION__, 
      channelId(), pMsg->recipient, svctxid().c_str(), pMsg->caddr.pipe));
    return -1;
  }

  return tph_.HandleOutput(pMsg, ChannelAddr( EKnownPipeId::NetLogic, pMsg->caddr.client ), channel().get());
}


unsigned long BackendContext::enableRead()
{
  NI_PROFILE_FUNCTION;

  unsigned int cnt = PeerContext::enableRead();
  if (0 == cnt)
  {
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s: done(ch=%d)"), 
      __FUNCTION__, channelId()));
  }
  return cnt;
}

bool BackendContext::AttachUnicastPipe(UnicastPipeSP const & sp)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(user2pipeMutex_);
  std::pair<User2UnicastPipeT::iterator, bool> pr = user2pipe_.insert(std::make_pair(sp->cid(), sp));
  return pr.second;
}

void BackendContext::DetachUnicastPipe(UnicastPipeSP const & sp)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(user2pipeMutex_);
  User2UnicastPipeT::iterator it = user2pipe_.find(sp->cid());
  if (it != user2pipe_.end())
  {
    user2pipe_.erase(it);
  }
  else
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Can't find unicast pipe to detach(c=%d svcid=%s ch=%d)"), __FUNCTION__, 
      sp->cid(), svcid().c_str(), channelId()));
  }
}

UnicastPipeSP BackendContext::FindUnicastPipe(Transport::TClientId const & cid)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(user2pipeMutex_);
  User2UnicastPipeT::iterator it = user2pipe_.find(cid);
  if (it != user2pipe_.end())
  {
    return it->second;
  }

  return UnicastPipeSP();
}

ClientContextSP BackendContext::FindClientContext(Transport::TClientId const & cid)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(user2pipeMutex_);
  User2UnicastPipeT::iterator it = user2pipe_.find(cid);
  if (it != user2pipe_.end())
  {
    return it->second->cctx().strong();
  }

  return ClientContextSP();
}

MulticastPipeSP BackendContext::RegisterMulticastPipe()
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(multicastPipesMutex_);
  MulticastPipeSP pipe;

  Transport::TPipeId pid = generatePipeId();
  if (Transport::EKnownPipeId::Invalid == pid)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: no pipeid available(svcid=%s svctx=%s)"), 
      __FUNCTION__, svcid().c_str(), svctxid().c_str()));
    return pipe;
  }

  StrongMT<ITrafficTracker> tt;
  StrongMT<ITrafficTrackerFactory> ttf = trafficTrackerFactory();
  if (ttf)
    tt = ttf->CreateTrafficTracker();

  pipe.reset(new MulticastPipe(svcid(), pid, GetStrongFromThis(static_cast<StrongFromThis<BackendContext>*>(this)), tt));
  if (!multicastPipes_.insert(std::make_pair(pid, pipe)).second)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: pipe is already registered(pid=%d svcid=%s svctxid=%s)"), 
      __FUNCTION__, pid, svcid().c_str(), svctxid().c_str()));

    freePipeId(pid);
    pipe.reset(0);
    return pipe;
  }

  return pipe;
}

MulticastPipeSP BackendContext::FindMulticastPipe(Transport::TPipeId const & _pipeid)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(multicastPipesMutex_);
  MulticastPipesT::const_iterator cit = multicastPipes_.find(_pipeid);
  if (cit != multicastPipes_.end())
  {
    return cit->second;
  }

  return MulticastPipeSP();
}

MulticastPipeSP BackendContext::UnregisterMulticastPipe(Transport::TPipeId const & _pipeid)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(multicastPipesMutex_);
  MulticastPipesT::iterator it = multicastPipes_.find(_pipeid);
  if (it != multicastPipes_.end())
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("Unregister multicast pipe(spid=%d svc=%s)"), _pipeid, svctxid().c_str()));

    MulticastPipeSP pipe(it->second);
    multicastPipes_.erase(it);
    unregisterPipeId(_pipeid);
    return pipe;
  }

  return MulticastPipeSP();
}

}
