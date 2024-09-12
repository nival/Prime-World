#pragma warning( push )
#pragma warning( disable : 4996)
#include "stdafx.h"
#include "TransportMessagesHeaders.h"
#include "BackendContext.h"
#include "RelayServer2Cfg.h"
#include "ClientContext.h"
#include "MulticastPipe.h"
#pragma warning( pop )

using namespace Transport;

namespace Relay
{

ClientContext::ClientContext()
  :tph_(0, true, "ClientContext"),
  trackInput_(false),
  trackedPipe_(EKnownPipeId::Invalid),
  logQlenThresholdFlag(0)
{
}

ClientContext::~ClientContext()
{
}

UnicastPipeSP ClientContext::RegisterUnicastPipe(TServiceId const & svcid, BackendContextSP const & spbc, 
                                          Transport::TPipeId const & cpid, Transport::TPipeId const & svcpid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_ASSERT(ENetInterface::Invalid != svcid);

  ACE_Guard<ACE_Thread_Mutex> lock(unicastPipesMutex_);

  UnicastPipeSP pipe = FindUnicastPipe_(svcid, svcpid);
  if (pipe.null())
  {
    TPipeId pipeid = cpid;
    if (EKnownPipeId::Invalid == pipeid)
    {
      pipeid = generatePipeId();
      if (EKnownPipeId::Invalid == pipeid)
        return pipe;
    }

    StrongMT<ITrafficTracker> tt;
    StrongMT<ITrafficTrackerFactory> ttf = spbc->trafficTrackerFactory();
    if (ttf)
      tt = ttf->CreateTrafficTracker();

    pipe = UnicastPipeSP(new UnicastPipe(svcid, svcpid, spbc, tt, userid(), pipeid, 
      GetStrongFromThis(static_cast<StrongFromThis<ClientContext>*>(this))));

    if (spbc->AttachUnicastPipe(pipe))
    {
      unicastPipes_.push_back(pipe);

      if (trackInput_ && 
        0 == NStr::NCmp(svcid.c_str(), trackedSvcId_.c_str(), trackedSvcId_.size()))
      {
        trackedPipe_ = cpid;
        lastInputDataTime_ = ACE_OS::gettimeofday();
      }
    }
    else
    {
      pipe.reset();

      ACE_ERROR((LM_WARNING, ACE_TEXT("%s: can't attach unicast pipe to backend context(c=%d cpid=%d svcid=%s svcpid=%d ch=%d)"), 
        __FUNCTION__, userid(), cpid, svcid.c_str(), svcpid, channelId()));
    }
  }
  else
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s: pipe is already registered(c=%d cpid=%d svcid=%s svcpid=%d ch=%d)"), 
      __FUNCTION__, userid(), cpid, svcid.c_str(), svcpid, channelId()));
  }

  return pipe;
}

int ClientContext::UnregisterUnicastPipe(Transport::TPipeId const & cpid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(unicastPipesMutex_);
  UnicastPipesT::iterator it = unicastPipes_.begin(), itEnd = unicastPipes_.end();
  for ( ;it != itEnd ; ++it )
  {
    UnicastPipeSP const & svcpipe = *it;
    if (cpid == svcpipe->cpipeid())
    {
      svcpipe->close();
      unicastPipes_.erase(it);
      return 0;
    }
  }

  ACE_ERROR((LM_WARNING, ACE_TEXT("%s: pipe NOT FOUND(cpid=%d c=%d ch=%d)"), 
    __FUNCTION__, cpid, userid_, channelId()));
  return -1;
}

UnicastPipeSP ClientContext::FindUnicastPipe(Transport::TPipeId const & cpid)
{
  NI_PROFILE_BLOCK(__FUNCTION__)
  ACE_Guard<ACE_Thread_Mutex> lock(unicastPipesMutex_);
  return  FindUnicastPipe_(cpid);
}

UnicastPipeSP ClientContext::FindUnicastPipe(Transport::TServiceId const & svcid, Transport::TPipeId const & svcpid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(unicastPipesMutex_);
  return FindUnicastPipe_(svcid, svcpid);
}

UnicastPipeSP ClientContext::FindUnicastPipe_(Transport::TServiceId const & svcid, Transport::TPipeId const & svcpid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  UnicastPipesT::iterator it = unicastPipes_.begin(), itEnd = unicastPipes_.end();
  for ( ;it != itEnd ; ++it )
  {
    if (svcid == (*it)->svcid() && svcpid == (*it)->svcpipeid())
      return (*it);
  }

  return UnicastPipeSP();
}

UnicastPipeSP ClientContext::FindUnicastPipe_(Transport::TPipeId const & cpid)
{
  NI_PROFILE_FUNCTION;

  UnicastPipesT::iterator it = unicastPipes_.begin(), itEnd = unicastPipes_.end();
  for ( ;it != itEnd ; ++it )
  {
    if( (*it)->cpipeid() == cpid)
    {
      return (*it);
    }
  }

  return UnicastPipeSP();
}

int ClientContext::open(ClientId const & userid, Terabit::AsynchChannelPtr const & chnl,
                        bool trackInput, Transport::TServiceId const & trackedSvcId, unsigned int notificationThreshold)
{
  NI_PROFILE_FUNCTION;

  userid_ = userid;
  trackInput_ = trackInput;
  trackedSvcId_ = trackedSvcId;
  lastInputDataTimeThreshold_ = notificationThreshold;
  return PeerContext::open(userid, chnl);
}

void ClientContext::close()
{
  PeerContext::close();
}

void ClientContext::closeConnection()
{
  channel()->close();
}

int ClientContext::HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg)
{
  NI_PROFILE_FUNCTION;

  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : client context is already closed(ch=%d c=%d t=%s s=%s)"), __FUNCTION__, 
      channelId(), userid(), pMsg->clientAddress.target.c_str(), pMsg->clientAddress.source.c_str()));
    return -1;
  }

  return tph_.HandleOutput(pMsg, ChannelAddr( EKnownPipeId::NetLogic, pMsg->clientAddress.client ), channel().get());
}

int ClientContext::HandleOpenChannelRequest(Transport::OpenChannelRequest* pMsg)
{
  NI_PROFILE_FUNCTION;

  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : client context is already closed(ch=%d c=%d t=%s s=%s)"), __FUNCTION__, 
      channelId(), userid(), pMsg->clientAddress.target.c_str(), pMsg->clientAddress.source.c_str()));
    return -1;
  }

  return tph_.HandleOutput(pMsg, ChannelAddr( EKnownPipeId::NetLogic, pMsg->clientAddress.client ), channel().get());
}

int ClientContext::HandleCloseChannel(Transport::CloseChannelMessage* pMsg, bool checkPipe)
{
  NI_PROFILE_FUNCTION;

  int rc = -1;
  if (pMsg->clientAddress.client != userid())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s: msg's client id and userid is different(ch=%d msgcid=%d ctxcid=%d)"), 
      __FUNCTION__, channelId(), pMsg->clientAddress.client, userid()));
    return rc;
  }

  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : client context is already closed(ch=%d c=%d p=%d)"), __FUNCTION__, 
      channelId(), userid(), pMsg->clientAddress.pipe));
    return rc;
  }

  if (checkPipe)
  {
    UnicastPipeSP sppipe = FindUnicastPipe(pMsg->clientAddress.pipe);
    if (!sppipe.null())
    {
      rc = tph_.HandleOutput(pMsg, ChannelAddr( EKnownPipeId::NetLogic, pMsg->clientAddress.client ), channel().get());
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s: pipe NOT found(ch=%d cid=%d cpid=%d)"), __FUNCTION__, 
        channelId(), userid(), pMsg->clientAddress.pipe));
    }
  }
  else
  {
    rc = tph_.HandleOutput(pMsg, ChannelAddr( EKnownPipeId::NetLogic, pMsg->clientAddress.client ), channel().get());
  }

  return rc;
}

int ClientContext::HandleOutput(Transport::TPipeId const & cpid, char const * data, size_t size, unsigned long seqNum)
{
  NI_PROFILE_FUNCTION;

  int rc = -1;

  Transport::ChannelAddr caddr(cpid, userid_);
  caddr.SeqNum(seqNum);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d p=%d seq=%d size=%d ch=%d)"), __FUNCTION__, 
    caddr.client, caddr.pipe, caddr.SeqNum(), size, channelId()));

  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : client context is already closed(ch=%d c=%d p=%d l=%d)"), __FUNCTION__, 
      channelId(), userid(), caddr.pipe, size));
    return rc;
  }

  unsigned int qlen = 0;
  unsigned int qlen_in_bytes = 0;
  rc = tph_.HandleOutput(data, size, caddr, channel().get(), qlen, qlen_in_bytes);
  if (0 == rc)
  {
    if (RelayServer2Cfg::GetClientOutputQueueWarningThreshold())
    {
      unsigned int qlenWarningThreshold = RelayServer2Cfg::GetClientOutputQueueWarningThreshold();
      if (qlen_in_bytes > qlenWarningThreshold)
      {
        long curValue = ++logQlenThresholdFlag;
        if (1 == curValue)
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("Client output queue size warning UP(c=%d ch=%d datasize=%d qlen=%d qsize=%d qwarning=%d)"),
            userid(), channelId(), size, qlen, qlen_in_bytes, qlenWarningThreshold));
        }
      }
      else
      {
        if (0 == qlen_in_bytes && logQlenThresholdFlag > 0)
        {
          logQlenThresholdFlag = 0;
          ACE_ERROR((LM_WARNING, ACE_TEXT("Client output queue size warning DOWN(c=%d ch=%d datasize=%d qwarning=%d)"),
            userid(), channelId(), size, qlenWarningThreshold));
        }
      }
    }

    if (RelayServer2Cfg::GetClientOutputQueueLimit() != 0 &&
        qlen_in_bytes > (unsigned int)RelayServer2Cfg::GetClientOutputQueueLimit())
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Client output queue size limit is EXCEEDED (c=%d ch=%d datasize=%d qlen=%d qsize=%d qlimit=%d)"),
        __FUNCTION__, userid(), channelId(), size, qlen, qlen_in_bytes, RelayServer2Cfg::GetClientOutputQueueLimit()));

      channel()->close();
      rc = -1;
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. TransportProtocolHandler.HandleOutput is FAILED(c=%d ch=%d)"),
      __FUNCTION__, userid(), channelId()));
  }

  return rc;
}

int ClientContext::HandleOutput(Transport::ThroughPingMessage* pmsg)
{
  NI_PROFILE_FUNCTION;

  int rc = -1;

  Transport::ChannelAddr caddr(Transport::EKnownPipeId::NetLogic, userid_);
  if (isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : client context is already closed(ch=%d c=%d p=%d)"), __FUNCTION__, 
      channelId(), userid(), pmsg->requestingChannel.pipe));
    return rc;
  }

  Transport::PingMessage pingmsg;
  pingmsg.reply = true;
  pingmsg.requestingChannel = pmsg->requestingChannel;
  pingmsg.sendTime = pmsg->sendTime;
  pingmsg.seqNum = pmsg->seqNum;

  rc = tph_.HandleOutput(&pingmsg, caddr, channel().get());
  if (rc < 0)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. TransportProtocolHandler.HandleOutput is FAILED(c=%d ch=%d)"),
      __FUNCTION__, userid(), channelId()));

    channel()->close();
  }

  return rc;
}

void ClientContext::TrackInputThreshold(Transport::TPipeId const & cpid)
{
  UnicastPipeSP svcpipe = FindUnicastPipe(cpid);
  if (!svcpipe.null())
  {
    if (trackInput() && cpid == getTrackedPipe())
    {
      ACE_Time_Value now = ACE_OS::gettimeofday();
      ACE_Time_Value lasttv = getLastInputDataTime();
      ACE_Time_Value thresholdtv = lasttv + getLastInputDataTimeThreshold();

      if (lasttv != ACE_Time_Value::zero && thresholdtv != ACE_Time_Value::zero && 
          thresholdtv < now)
      {
        ACE_Time_Value delta = now - lasttv;
        double ddelta = (double)delta.msec()/1000;

        ACE_ERROR((LM_WARNING, ACE_TEXT("input data time threshold(c=%d cpid=%d svcpid=%d deltatime=%f ch=%d threshold=%d)"), 
          userid(), cpid, svcpipe->svcpipeid(), ddelta, channelId(), getLastInputDataTimeThreshold()));
      }
      setLastInputDataTime(now);
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("No pipe(%d) found for client(%d)"), cpid, userid()));
  }
}

int ClientContext::CloseUnicastPipe(Transport::TPipeId const & cpid)
{
  int rc = 1;
  UnicastPipeSP svcpipe = FindUnicastPipe(cpid);
  if (!svcpipe.null())
  {
    ACE_Guard<ACE_Thread_Mutex> lock(unicastPipesMutex_);
    rc = CloseUnicastPipe_(svcpipe);
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: can't find unicast pipe(c=%d cpid=%d)"), __FUNCTION__, userid(), cpid));
  }

  return rc;
}

void ClientContext::ClosePipes()
{
  NI_PROFILE_FUNCTION;
  {
    ACE_Guard<ACE_Thread_Mutex> lock(multicastPipesMutex_);
    for (MulticastPipesT::const_iterator cit = multicastPipes_.begin(); cit != multicastPipes_.end(); ++cit)
    {
      RemoveFromMulticastPipe(*cit);
    }
    multicastPipes_.clear();
  }

  {
    ACE_Guard<ACE_Thread_Mutex> lock(unicastPipesMutex_);
    for (UnicastPipesT::const_iterator cit = unicastPipes_.begin(); cit != unicastPipes_.end(); ++cit)
    {
      CloseUnicastPipe_(*cit);
    }
  }
}

int ClientContext::CloseUnicastPipe_(UnicastPipeSP const & svcpipe)
{
  NI_PROFILE_FUNCTION;

  int rc = -1;
  int cpid = svcpipe->cpipeid();
  if (svcpipe->close())
  {
    //  если закрываем мы, то отсылаем сообщение на закрытие канала
    BackendContextSP spb =  svcpipe->svctx();
    if (!spb.null())
    {
      if (!spb->isclosed())
      {
        spb->DetachUnicastPipe(svcpipe);

        Transport::CloseChannelMessage ccmsg;
        ccmsg.clientAddress = Transport::ChannelAddr(svcpipe->svcpipeid(), svcpipe->cid());
        rc = spb->HandleCloseChannel(&ccmsg);
        if (rc < 0)
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("%s: can't send close channel msg(c=%d cpid=%d svc=%s)"), __FUNCTION__, userid(), cpid, svcpipe->svctxid().c_str()));
        }
        else
        {
          ACE_ERROR((LM_INFO, ACE_TEXT("%s: send close channel msg(c=%d cpid=%d svc=%s)"), __FUNCTION__, userid(), cpid, svcpipe->svctxid().c_str()));
        }
      }
      else
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s: backend context already closed(c=%d cpid=%d svc=%s)"), __FUNCTION__, userid(), cpid, svcpipe->svctxid().c_str()));
        rc = 0;
      }
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s: backend context already NULL(c=%d cpid=%d svc=%s)"), __FUNCTION__, userid(), cpid, svcpipe->svctxid().c_str()));
      rc = 0;
    }
  }
  else
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s: pipe is already closed(c=%d cpid=%d svc=%s)"), __FUNCTION__, userid(), cpid, svcpipe->svctxid().c_str()));
    rc = 0;
  }

  return rc;
}

Transport::TPipeId ClientContext::RegisterOpenChnlOp(OpenChnl2ClientOpPtr const & op)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);

  Transport::TPipeId pid = openingChannelPipes_.Generate();
  if (Transport::EKnownPipeId::Invalid != pid)
  {
    if (!openChnlOps_.insert(std::make_pair(pid, op)).second)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s: operation with such pipeid already registered(c=%d pid=%d)"), __FUNCTION__, userid(), pid));
      openingChannelPipes_.Release(pid);
      pid = Transport::EKnownPipeId::Invalid;
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: can't generate pipeid(c=%d)"), __FUNCTION__, userid()));
  }

  return pid;
}

OpenChnl2ClientOpPtr ClientContext::FindOpenChnlOp(Transport::TPipeId const & _pid) const
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);
  OpenChnlOpsT::const_iterator cit = openChnlOps_.find(_pid);
  if (cit != openChnlOps_.end())
    return cit->second;
  else
    return 0;
}

OpenChnl2ClientOpPtr ClientContext::UnregisterOpenChnlOp(Transport::TPipeId const & _pid)
{
  NI_PROFILE_FUNCTION;

  ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);
  OpenChnlOpsT::iterator it = openChnlOps_.find(_pid);
  if (it != openChnlOps_.end())
  {
    OpenChnl2ClientOpPtr op = it->second;
    openChnlOps_.erase(it);
    openingChannelPipes_.Release(_pid);
    return op;
  }
  else
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s: no such open channel operation(c=%d pid=%d)"), __FUNCTION__, userid(), _pid));
  }

  return 0;
}

void ClientContext::CheckOpenChnlOpTimeout()
{
  if (!RelayServer2Cfg::GetOpenClientChannelTimeout())
    return;

  ACE_Guard<ACE_Thread_Mutex> lock(openChnlOpsMutex_);
  time_t now = ACE_OS::gettimeofday().sec();

  OpenChnlOpsT openingChannelOps = openChnlOps_;
  for(OpenChnlOpsT::const_iterator it = openingChannelOps.begin(); it != openingChannelOps.end(); ++it)
  {
    OpenChnl2ClientOpPtr op = it->second;
    if (now - op->startTime() > RelayServer2Cfg::GetOpenClientChannelTimeout())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s: open channel operation is timed out(c=%d svc=%s svcpid=%d)"), 
        __FUNCTION__, userid(), op->pipe()->svctxid().c_str(), op->pipe()->svcpipeid()));

      Transport::OpenChannelResponse fakemsg;
      fakemsg.channelType = Transport::EChannelType::Unicast;
      fakemsg.success = false;
      op->Complete(&fakemsg);

      UnregisterOpenChnlOp(op->localpid());
    }
  }
}

int ClientContext::AttachMulticastPipe(MulticastPipeSP const & _pipe)
{
  NI_PROFILE_FUNCTION;

  int rc = -1;
  for (MulticastPipesT::const_iterator it = multicastPipes_.begin(); it != multicastPipes_.end(); ++it)
  {
    MulticastPipeSP const & pipe = *it;
    if (pipe == _pipe)
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s: such pipe already registered(c=%d svc=%s pid=%d)"), 
        __FUNCTION__, userid(), _pipe->svctxid().c_str(), _pipe->svcpipeid()));
      return rc;
    }
  }

  ACE_ERROR((LM_INFO, ACE_TEXT("%s: client attached to multicast pipe(c=%d svc=%s pid=%d)"), 
    __FUNCTION__, userid(), _pipe->svctxid().c_str(), _pipe->svcpipeid()));

  multicastPipes_.push_back(_pipe);
  return true;
}

int ClientContext::RemoveFromMulticastPipe(MulticastPipeSP const & _pipe)
{
  NI_PROFILE_FUNCTION;

  int rc = -1;
  if (_pipe->isopen())
  {
    Transport::TPipeId pipeid = _pipe->RemoveRecipient(userid());
    if (pipeid != Transport::EKnownPipeId::Invalid)
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("%s: client removed frome multicast pipe(c=%d svc=%s svcpid=%d)"), 
        __FUNCTION__, userid(), _pipe->svctxid().c_str(), _pipe->svcpipeid()));

      BackendContextSP spb =  _pipe->svctx();
      if (!spb.null())
      {
        if (!spb->isclosed())
        {
          Transport::RemoveRecipientMessage rrmsg;
          rrmsg.caddr = ChannelAddr(_pipe->svcpipeid(), Transport::autoAssignClientId);
          rrmsg.recipient = userid();
          rc = spb->HandleRemoveRecipient(&rrmsg);
          if (rc < 0)
          {
            ACE_ERROR((LM_WARNING, ACE_TEXT("%s: can't send remove recipient msg(c=%d svc=%s svcpid=%d)"), 
              __FUNCTION__, userid(), _pipe->svctxid().c_str(), _pipe->svcpipeid()));
          }
          else
          {
            ACE_ERROR((LM_INFO, ACE_TEXT("%s: send remove recipient msg(c=%d svc=%s svcpid=%d)"), 
              __FUNCTION__, userid(), _pipe->svctxid().c_str(), _pipe->svcpipeid()));
          }
        }
        else
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("%s: backend context already closed(c=%d svc=%s)"), __FUNCTION__, userid(), _pipe->svctxid().c_str()));
          rc = 0;
        }
      }
      else
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s: backend context already NULL(c=%d svc=%s)"), __FUNCTION__, userid(), _pipe->svctxid().c_str()));
        rc = 0;
      }
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s: client is not recipient in multicast pipe(c=%d svc=%s svcpid=%d)"), 
        __FUNCTION__, userid(), _pipe->svctxid().c_str(), _pipe->svcpipeid()));
    }
  }
  else
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s: pipe is already closed(c=%d svc=%s svcpid=%d)"), 
      __FUNCTION__, userid(), _pipe->svctxid().c_str(), _pipe->svcpipeid()));
    rc = 0;
  }

  return rc;
}

}
