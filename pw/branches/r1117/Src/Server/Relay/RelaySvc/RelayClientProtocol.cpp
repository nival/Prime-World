#pragma warning( disable : 4996)
#include "stdafx.h"
#include <IOTerabit/AsynchChannel.h>
#include "TransportMessagesHeaders.h"
#include "NewClientVerifier.h"
#include "RelayChannelManager.h"
#include "ClientContext.h"
#include "OpenChnl2SvcOp.h"
#include "C2STransmissionOp.h"
#include "C2SPingOp.h"
#include "RelayServer2Cfg.h"
#include "RelayClientProtocol.h"
#include "System/DarkSide.h"

using namespace Terabit;
using namespace Transport;

namespace Relay
{

ACE_Atomic_Op<ACE_Thread_Mutex, long> RelayClientProtocol::count_;

RelayClientProtocol::RelayClientProtocol(Terabit::ProtocolFactory& factory)
  : BaseProtocol (factory, true, "Client"),
  userid_(0),
  channelid_(static_cast< unsigned int >(-1)),
  lastKeepaliveMsg_(0),
  lastKeepaliveMsgCheckTime_(0),
  totalWrittenBytes_(0),
  amountOfReadBytes_(0),
  totalReadBytes_(0)
{
}

RelayClientProtocol::~RelayClientProtocol()
{
}

int RelayClientProtocol::HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(m=%d)"), __FUNCTION__, pMsg->GetTypeId()));

  int rc = -1;
  RelayChannelManager* pMngr = manager(channel);

  if (!lastKeepaliveMsg_)
    lastKeepaliveMsg_ = ACE_OS::gettimeofday().sec();

  if (pMsg->clientAddress.target == ENetInterface::FrontEnd)
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("New client connection (ch=%d, c=%d)"), 
      channel->get_id(), pMsg->clientAddress.client));

    bool bres = false;
    Address& clientAddr = pMsg->clientAddress;

    //  verify client
    NewClientVerifier* clientVerifier = pMngr->newClientVerifier();
    if (clientVerifier && clientVerifier->VerifyClient(pMsg))
    {
      Transport::TClientId userid = pMsg->clientAddress.client;

      //  register client
      ClientContextSP pctx = pMngr->RegisterClient(channel->get_id(), userid);
      if (!pctx.null())
      {
        channelid_ = channel->get_id();
        userid_ = userid;

        channel->cancel_timer();  //  cancel new connection's timer

        wpctx_ = pctx;

        bres = true;
      }
      else
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s(c=%d m=%d). Can't register client"), __FUNCTION__, 
          pMsg->clientAddress.client, pMsg->GetTypeId()));
    }
    else
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s(c=%d m=%d). Client verification is failed"), __FUNCTION__, 
        pMsg->clientAddress.client, pMsg->GetTypeId()));

    rc = SendOpenChannelResponse(channel, bres, clientAddr, pMsg->localPipeId, ChannelAddr(EKnownPipeId::FrontEnd, clientAddr.client, clientAddr.sender));
    if (!bres)
      rc = -1;
  }
  else
    rc = HandleNewThroughConnection(pMsg, channel);

  return rc;
}

int RelayClientProtocol::HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, Terabit::AsynchChannel *channel)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(m=%d)"), __FUNCTION__, pMsg->GetTypeId()));

  int rc = -1;
  ClientContextSP spctx = wpctx_.strong();
  if (spctx.null())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s: client context is NULL(ch=%d c=%d)"), 
      __FUNCTION__, channel->get_id(), pMsg->clientAddress.client));
    return rc;
  }

  if (Transport::EChannelType::Unicast != pMsg->channelType)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: incorrect channel type(ch=%d c=%d chnlType=%s)"), __FUNCTION__, 
      channel->get_id(), pMsg->clientAddress.client, Transport::EChannelType::ToString(pMsg->channelType)));
    return rc;
  }

  OpenChnl2ClientOpPtr oc2c = spctx->FindOpenChnlOp(pMsg->localPipeId);
  if (oc2c)
  {
    rc = oc2c->Complete(pMsg);
    spctx->UnregisterOpenChnlOp(pMsg->localPipeId);
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: open channel operation is NOT found(c=%d m=%d)"), __FUNCTION__, 
      pMsg->clientAddress.client, pMsg->GetTypeId()));
  }

  return rc;
}

int RelayClientProtocol::HandleNewThroughConnection(Transport::OpenChannelRequest *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(m=%d)"), __FUNCTION__, pMsg->GetTypeId()));

  RelayChannelManager* pMngr = manager(channel);

  //  Note: there is no implementation of client verification in the current relay server

  ACE_ERROR((LM_INFO, ACE_TEXT("New channel requested (ch=%d, c=%d, cn=%s)"), 
    channel->get_id(), pMsg->clientAddress.client, pMsg->clientAddress.target.c_str()));

  //  get client context
  ClientContextSP spctx = wpctx_.strong();
  if (spctx.null())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("Client context is NULL(ch=%d c=%d svc=%s)"), 
      channel->get_id(), pMsg->clientAddress.client, pMsg->clientAddress.target.c_str()));

    return -1;
  }

  if (Transport::EChannelType::Unicast != pMsg->channelType)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s : incorrect channel type in request (ch=%d c=%d svc=%s chnlType=%s)"), __FUNCTION__,
      channel->get_id(), pMsg->clientAddress.client, pMsg->clientAddress.target.c_str(), Transport::EChannelType::ToString(pMsg->channelType)));
    return -1;
  }

  int rc = -1;
  //  find link for destination service
  TServiceId destsvc = pMsg->clientAddress.target;
  SvcConnectionManager* scm = pMngr->getSvcConnectionManager();
  if (!scm->IsKnownService(destsvc))
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("Unknown service acquired (ch=%d c=%d svc=%s)"), 
      channel->get_id(), spctx->userid(), destsvc.c_str()));
    
    Address const & clientAddr = pMsg->clientAddress;
    rc = SendOpenChannelResponse(channel, false, clientAddr, pMsg->localPipeId, 
      ChannelAddr(EKnownPipeId::Invalid, clientAddr.client, clientAddr.sender));
  }
  else
  {
    if (spctx->userid() == pMsg->clientAddress.client)
    {
      OpenChannelResponse ocr;
      ocr.success = false;
      ocr.clientAddress = pMsg->clientAddress;
      ocr.localPipeId = pMsg->localPipeId;
      ocr.remoteAddr = ChannelAddr(EKnownPipeId::Invalid, spctx->userid(), pMsg->clientAddress.sender);
      ocr.channelType = pMsg->channelType;

      AutoOpPtr<OpenChnl2SvcOp> ec2s(new OpenChnl2SvcOp(destsvc, pMngr->backendSvcid(), spctx, ocr, pMsg->loginData));

      BackendContextWeakPtr wpbc;
      rc = scm->Connect(ec2s.get(), wpbc);
      if (rc > 0)
      { //  connection already established
        BackendContextSP spbc = wpbc.strong();
        if (!spbc.null() && !spbc->isclosed())
        {
          //  connection alive, establish channel from backend context
          rc = ec2s->StartChannelCreation(spbc);
          if (0 == rc)
          {
            ec2s.release();
          }
          else
          {
            ACE_ERROR((LM_ERROR, ACE_TEXT("Can't start OpenChnl2Svc operation(svcid=%s cid=%d)"), 
              destsvc.c_str(), spctx->userid()));
          }
        }
        else
        {
          //  connection broken, try establish it again
          rc = scm->Connect(ec2s.get(),wpbc);
          if (0 == rc)
            ec2s.release();
          else // rc < 0
            ACE_ERROR((LM_ERROR, ACE_TEXT("Can't recover connection to service (svcid=%s cid=%d)"), 
                       destsvc.c_str(), spctx->userid()));
        }
      }
      else
      if (0 == rc)
      {
        ec2s.release();
      }

      if (rc < 0)
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("Can't connect to service (svcid=%s cid=%d)"), 
          destsvc.c_str(), spctx->userid()));

        //  error, send response immediately
        Address const & clientAddr = pMsg->clientAddress;
        rc = SendOpenChannelResponse(channel, false, clientAddr, pMsg->localPipeId, 
          ChannelAddr(EKnownPipeId::Invalid, clientAddr.client, clientAddr.sender));
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("Received clientid(%d) id is different from userid(%d). Close client connection."), 
        pMsg->clientAddress.client, spctx->userid()));
    }
  }

  return rc;
}

int RelayClientProtocol::HandleCloseChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  int rc = -1;

  ClientContextSP spctx = wpctx_.strong();
  if (spctx.null())
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. No context exists(c=%d p=%d ch=%d)"),
      __FUNCTION__, pMsg->clientAddress.client, pMsg->clientAddress.pipe, channel->get_id()));
    return rc;
  }

  if (spctx->isclosed())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Context already closed(c=%d p=%d ch=%d)"),
      __FUNCTION__, pMsg->clientAddress.client, pMsg->clientAddress.pipe, channel->get_id()));
    return rc;
  }

  if (pMsg->clientAddress.pipe >= Transport::EKnownPipeId::FirstCustomPipeId)
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("%s(c=%d p=%d ch=%d)"), 
      __FUNCTION__, pMsg->clientAddress.client, pMsg->clientAddress.pipe, channel->get_id()));

    spctx->TrackInputThreshold(pMsg->clientAddress.pipe);
    rc = spctx->CloseUnicastPipe(pMsg->clientAddress.pipe);
  }
  else
  if (Transport::EKnownPipeId::FrontEnd == pMsg->clientAddress.pipe)
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("%s. Frontend channel close(c=%d p=%d ch=%d)"), 
      __FUNCTION__, pMsg->clientAddress.client, pMsg->clientAddress.pipe, channel->get_id()));

    spctx->close();
    channel->close();
    rc = 0;
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Client try to close unknown client pipe(c=%d p=%d ch=%d)"), 
      __FUNCTION__, pMsg->clientAddress.client, pMsg->clientAddress.pipe, channel->get_id()));
  }

  return rc;
}

int RelayClientProtocol::HandleCloseMulticastChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_FUNCTION;

  ClientContextSP spctx = wpctx_.strong();
  if (spctx.null())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s: client context is NULL(ch=%d c=%d cpid=%d)"), 
      __FUNCTION__, channel->get_id(), pMsg->clientAddress.client, pMsg->clientAddress.pipe));

    return -1;
  }

  ACE_ERROR((LM_ERROR, ACE_TEXT("Client should not send close multicast channel message (ch=%d c=%d cpid=%d)"), 
    channel->get_id(), spctx->userid(), pMsg->clientAddress.pipe));

  return -1;
}

int RelayClientProtocol::HandlePingMessage(Transport::PingMessage *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_FUNCTION;

  int rc = -1;
  ClientContextSP spctx = wpctx_.strong();
  if (spctx.null())
  {
    ACE_DEBUG((LM_ERROR, ACE_TEXT("%s. No context exists(ch=%d)"),
      __FUNCTION__, channel->get_id()));
    return rc;
  }

  if (pMsg->requestingChannel.pipe == Transport::EKnownPipeId::FrontEnd)
  {
    PingMessage msg(*pMsg);
    msg.reply = true;
    return transport_handler_.HandleOutput(&msg, ChannelAddr(EKnownPipeId::NetLogic, msg.requestingChannel.client), channel);
  }
  else
  {
    Transport::TPipeId pid = pMsg->requestingChannel.pipe;
    UnicastPipeSP svcpipe = spctx->FindUnicastPipe(pid);
    if (!svcpipe.null())
    {
      if (!svcpipe->isclosed())
      {
        BackendContextSP spbc = svcpipe->svctx().strong();
        if (!spbc.null())
        {
          if (!spbc->isclosed())
          {
            AutoOpPtr<C2SPingOp> csop(new C2SPingOp(spctx, pid, svcpipe->svcpipeid(),
              spbc, pMsg->requestingChannel, pMsg->sendTime, pMsg->seqNum));

            SvcOperationsMapT::iterator it = svc2ops_.find(spbc->svctxid());
            if (it != svc2ops_.end())
            {
              //  добавляем операцию в цепочку операция для pipe
              ACE_ASSERT(0 == it->second.last_->next());
              it->second.last_->next(csop.get());
              it->second.last_ = csop.release();
              it->second.count_++;
            }
            else
            { //  first msg for pipe
              OperationChain opchain(csop.get(), csop.get());
              svc2ops_.insert(std::make_pair(spbc->svctxid(), opchain));
              csop.release();
            }
            rc = 0;
          }
          else
          {
            ACE_ERROR((LM_WARNING, ACE_TEXT("%s: backend service is already closed(c=%d p=%d svc=%s svctx=%d)"), 
              __FUNCTION__, spctx->userid(), pid, spbc->svcid().c_str(), spbc->id()));
            rc = 0;
          }
        }
        else
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("%s: backend service is already null(c=%d p=%d svc=%s)"), 
            __FUNCTION__, spctx->userid(), pid, svcpipe->svcid().c_str()));
          rc = 0;
        }
      }
      else
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s: underlying pipe is already closed(c=%d p=%d svc=%s)"), 
          __FUNCTION__, spctx->userid(), pid, svcpipe->svcid().c_str()));
        rc = 0;
      }
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Ping for non-exited pipe(pid=%d ch=%d)"),
        __FUNCTION__, pid, channel->get_id()));
    }
  }

  return rc;
}

int RelayClientProtocol::HandlePingMessage(Transport::ThroughPingMessage *pMsg, Terabit::AsynchChannel *channel)
{
  return -1;
}

int RelayClientProtocol::HandleInput(Terabit::AsynchChannel* channel, Transport::MessageHeader const & header,
                        Transport::MessageBase *pMsg)
{
  NI_PROFILE_BLOCK("RelayClientProtocol::HandleInput::msg");

  ClientContextSP spctx = wpctx_.strong();
  if (spctx.null())
  {
    ACE_DEBUG((LM_ERROR, ACE_TEXT("%s. No context exists(ch=%d)"),
      __FUNCTION__, channel->get_id()));
    return -1;
  }

  ACE_DEBUG((LM_TRACE, ACE_TEXT("RelayClientProtocol::HandleInput(u=%d p=%d c=%d s=%d m=%d)"), 
    spctx->userid(), header.pipe, header.client, header.sender, pMsg->GetTypeId()));

  int rc = -1;
  if (Transport::KeepAliveMessage::GetClassType() == pMsg->GetTypeId())
  {
    ACE_ERROR((LM_DEBUG, ACE_TEXT("Keepalive message received from client (u=%d ch=%d m=%d)"), 
      spctx->userid(), channel->get_id(), pMsg->GetTypeId()));
    lastKeepaliveMsg_ = ACE_OS::gettimeofday().sec();
    rc = 0;
  }
  else
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("Unhandled message received from client (u=%d,m=%d)"), spctx->userid(), pMsg->GetTypeId()));
    rc = 0; //  FIXME:  пока игнорируем
  }

  return rc;
}

int RelayClientProtocol::HandleInput(Terabit::AsynchChannel* channel, Transport::ChannelAddr const & caddr, 
                                     char const * data, size_t len)
{
  NI_PROFILE_BLOCK("RelayClientProtocol::HandleInput::data");

  ClientContextSP spctx = wpctx_.strong();
  if (spctx.null())
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. No context exists(ch=%d)"),
      __FUNCTION__, channel->get_id()));
    return -1;
  }

  ACE_DEBUG((LM_TRACE, ACE_TEXT("RelayClientProtocol::HandleInput(u=%d p=%d c=%d s=%d l=%d)"), 
    spctx->userid(), caddr.pipe, caddr.client, caddr.sender, len));

  if (caddr.client != spctx->userid())
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Incorrect client id(ch=%d c=%d receivedClientId=%d cpid=%d)"),
      __FUNCTION__, channel->get_id(), spctx->userid(), caddr.client, caddr.pipe));

    return -1;
  }

  if (caddr.pipe < EKnownPipeId::FirstCustomPipeId)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Incorrect pipe id(ch=%d c=%d cpid=%d)"),
      __FUNCTION__, channel->get_id(), spctx->userid(), caddr.pipe));
    return -1;
  }

  int rc = -1;

  UnicastPipeSP svcpipe = spctx->FindUnicastPipe(caddr.pipe);
  if (!svcpipe.null())
  {
    if (!svcpipe->isclosed())
    {
      BackendContextSP spbc = svcpipe->svctx().strong();
      if (!spbc.null())
      {
        if (!spbc->isclosed())
        {
          Transport::TPipeId cpid = caddr.pipe;
          Transport::TPipeId svcpid = svcpipe->svcpipeid();

          ACE_Time_Value now = ACE_OS::gettimeofday();

          if (spctx->trackInput() && cpid == spctx->getTrackedPipe())
          {
            ACE_Time_Value lasttv = spctx->getLastInputDataTime();
            ACE_Time_Value thresholdtv = lasttv + spctx->getLastInputDataTimeThreshold();

            if (lasttv != ACE_Time_Value::zero && thresholdtv != ACE_Time_Value::zero && 
                thresholdtv < now)
            {
              ACE_Time_Value delta = now - lasttv;
              double ddelta = (double)delta.msec()/1000;
              ACE_ERROR((LM_WARNING, ACE_TEXT("C2S input data time threshold(c=%d cpid=%d svc=%s svctx=%d svcpid=%d deltatime=%f sz=%d ch=%d threshold=%d)"), 
                spctx->userid(), cpid, spbc->svcid().c_str(), spbc->id(), svcpid, ddelta, len, channel->get_id(), spctx->getLastInputDataTimeThreshold()));
            }
            spctx->setLastInputDataTime(now);
          }

          if (RelayServer2Cfg::GetClientPacketSoftLimitPerCheckingPeriod())
          {
            PacketFreqCheckData pfcd;
            rc = svcpipe->checkC2SPacketFreqSoft(now, pfcd);
            if (rc < 0)
            {
              ACE_ERROR((LM_WARNING, ACE_TEXT("Client packet frequency soft limit is exceeded(c=%d cpid=%d svc=%s svctx=%d packets=%d period=%d ch=%d packetlimit=%d checkperiod=%d)"), 
                spctx->userid(), cpid, spbc->svcid().c_str(), spbc->id(), pfcd.packets_, pfcd.period_, channel->get_id(),
                RelayServer2Cfg::GetClientPacketSoftLimitPerCheckingPeriod(), RelayServer2Cfg::GetClientPacketFreqCheckingPeriod()));
              rc = 0;
            }
          }

          if (RelayServer2Cfg::GetClientPacketHardLimitPerCheckingPeriod())
          {
            PacketFreqCheckData pfcd;
            rc = svcpipe->checkC2SPacketFreqHard(now, pfcd);
            if (rc < 0)
            {
              ACE_ERROR((LM_ERROR, ACE_TEXT("Client packet frequency hard limit is exceeded(c=%d cpid=%d svc=%s svctx=%d packets=%d period=%d ch=%d packetlimit=%d checkperiod=%d)"), 
                spctx->userid(), cpid, spbc->svcid().c_str(), spbc->id(), pfcd.packets_, pfcd.period_, channel->get_id(),
                RelayServer2Cfg::GetClientPacketHardLimitPerCheckingPeriod(), RelayServer2Cfg::GetClientPacketFreqCheckingPeriod()));
              return rc;
            }
          }

          NI_PROFILE_BLOCK( "C2STransmissionOp" );

          ACE_DEBUG((LM_DEBUG, ACE_TEXT("C2S IN(c=%d cpid=%d svc=%s svctx=%d svcpid=%d sz=%d ch=%d)"), 
            spctx->userid(), cpid, spbc->svcid().c_str(), spbc->id(), svcpid, len, channel->get_id()));

          AutoOpPtr<C2STransmissionOp> csop(new C2STransmissionOp(spctx, cpid, svcpid,
            spbc, data, len, caddr.SeqNum()));

          bool seqCheckRes = true;
#ifndef TRANSPORT_SEQ_PACKET_CHECK
          if (caddr.SeqNum())
#endif
          {
            if (svcpipe->lastInC2SSeqNum() + 1 == caddr.SeqNum())
            {
              svcpipe->lastInC2SSeqNum(caddr.SeqNum());
            }
            else
            {
              ACE_DEBUG((LM_ERROR, ACE_TEXT("C2S: wrong message sequence (lisn=%d isn=%d c=%d svc=%s svctx=%d svcpid=%d sz=%d ch=%d)"), 
                svcpipe->lastInC2SSeqNum(), caddr.SeqNum(), spctx->userid(), spbc->svcid().c_str(), spbc->id(), svcpid, len, channel->get_id()));

              seqCheckRes = RelayServer2Cfg::GetKeepClientConnectionOnWrongSeqNumError();
              if (seqCheckRes)
                svcpipe->lastInC2SSeqNum(caddr.SeqNum());
            }
          }

          if (seqCheckRes)
          {
            NI_PROFILE_BLOCK( "svc2ops_.insert" );

            //  ставим операции в очередь
            SvcOperationsMapT::iterator it = svc2ops_.find(spbc->svctxid());
            if (it != svc2ops_.end())
            {
              //  добавляем операцию в цепочку операция для pipe
              ACE_ASSERT(0 == it->second.last_->next());
              it->second.last_->next(csop.get());
              it->second.last_ = csop.release();
              it->second.count_++;
            }
            else
            { //  first msg for pipe
              OperationChain opchain(csop.get(), csop.get());
              svc2ops_.insert(std::make_pair(spbc->svctxid(), opchain));
              csop.release();
            }

            rc = len;
          }
        }
        else
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("Backend service is already closed(c=%d p=%d svc=%s svctx=%d)"), 
            spctx->userid(), caddr.pipe, spbc->svcid().c_str(), spbc->id()));
          rc = len;
        }
      }
      else
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("Backend service is already null(c=%d p=%d svc=%s)"), 
          spctx->userid(), caddr.pipe, svcpipe->svcid().c_str()));
        rc = len;
      }
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("Underlying pipe is already closed(c=%d p=%d svc=%s)"), 
        spctx->userid(), caddr.pipe, svcpipe->svcid().c_str()));
      rc = len;
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("No pipe found for client(cpid=%d c=%d). C2S."), caddr.pipe, spctx->userid()));
  }

  return rc;
}

int RelayClientProtocol::HandleMulticastInput(Terabit::AsynchChannel* channel, Transport::ChannelAddr const & caddr, 
                                 char const * data, size_t len)
{
  ClientContextSP spctx = wpctx_.strong();
  if (spctx.null())
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. No context exists(ch=%d c=%d p=%d)"),
      __FUNCTION__, channel->get_id(), caddr.client, caddr.pipe));
    return -1;
  }

  ACE_ERROR((LM_ERROR, ACE_TEXT("%s: multicast data received from client(ch=%d c=%d len=%d receivedClientId=%d pid=%d)"), 
    __FUNCTION__, channel->get_id(), spctx->userid(), len, caddr.client, caddr.pipe));

  return -1;
}

int RelayClientProtocol::OnReadHandlingCompleted(int result, size_t len, const char *data, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d sz=%d)"), __FUNCTION__, channel->get_id(), len));

  int rc = -1;

  if (result < 0)
  {
    NI_PROFILE_BLOCK( "clean_ops" );

    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: clear operations due to failure(ch=%d length=%d ops=%d result=%d)"), 
      __FUNCTION__, channel->get_id(), len, svc2ops_.size(), result));

    //  очищаем уже созданные операции
    SvcOperationsMapT::iterator it = svc2ops_.begin();
    SvcOperationsMapT::iterator eit = svc2ops_.end();
    for(; it != eit; ++it)
    {
      Operation* op = it->second.first_;
      if (op)
        op->releaseRef();
    }
  }
  else
  {
    NI_PROFILE_BLOCK( "C2S_OPERATIONS" );

    ClientContextSP spctx = wpctx_.strong();
    if (spctx.null())
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. No context exists(ch=%d)"), 
        __FUNCTION__, channel->get_id()));
      //  мы можем оказаться здесь также когда клиент запросивший новое соединение 
      //  не прошел проверку(clientVerifier->VerifyClient())
      return -1;
    }

    SvcOperationsMapT::iterator it = svc2ops_.begin();
    SvcOperationsMapT::iterator eit = svc2ops_.end();
    for(; it != eit; ++it)
    {
      NI_PROFILE_BLOCK( "svc_transmission" );

      Operation* op = it->second.first_;
      BackendContextSP spbc = static_cast<C2SOp*>(op)->GetSvcCtx();
      if (!spbc->isclosed())
      {
        NI_PROFILE_BLOCK( "operations" );

        do
        {
          NI_PROFILE_BLOCK( "op_transmission" );

          rc = -1;
          Operation* nextop = op->next();
          op->next(0);

          if (OperationType::C2S_TRANSMISSION == op->type())
          {
            C2STransmissionOp* c2sop = (C2STransmissionOp*)op;
            Transport::TServiceId const svcid = c2sop->GetServiceId();
            Transport::TClientId const userid = c2sop->GetClientId();
            Transport::TPipeId const spid = c2sop->GetSvcPipeId();
            Transport::TPipeId const cpid = c2sop->GetClientPipeId();

            rc = c2sop->GetSvcCtx()->HandleOutput(c2sop);
            if (rc < 0)
            {
              ACE_ERROR((LM_ERROR, ACE_TEXT("C2S is FAILED(count=%d c=%d cpid=%d svc=%s svctx=%d svcpid=%d ch=%d)"), 
                it->second.count_, userid, cpid, svcid.c_str(), spbc->id(), spid, channel->get_id()));
            }
            else
            {
              ACE_DEBUG((LM_DEBUG, ACE_TEXT("C2S IN Completed(count=%d c=%d svc=%s svctx=%d sz=%d ch=%d)"), 
                it->second.count_, userid, svcid.c_str(), spbc->id(), len, channel->get_id()));
            }
          }
          else
          if (OperationType::C2S_PING == op->type())
          {
            C2SPingOp* c2sop = (C2SPingOp*)op;
            Transport::TServiceId const svcid = c2sop->GetServiceId();
            Transport::TClientId const userid = c2sop->GetClientId();
            Transport::TPipeId const spid = c2sop->GetSvcPipeId();
            Transport::TPipeId const cpid = c2sop->GetClientPipeId();

            rc = c2sop->GetSvcCtx()->HandleOutput(c2sop);
            if (rc < 0)
            {
              ACE_ERROR((LM_ERROR, ACE_TEXT("C2SPing is FAILED(count=%d c=%d cpid=%d svc=%s svctx=%d svcpid=%d ch=%d)"), 
                it->second.count_, userid, cpid, svcid.c_str(), spbc->id(), spid, channel->get_id()));
            }
            else
            {
              ACE_DEBUG((LM_DEBUG, ACE_TEXT("C2SPing IN Completed(count=%d c=%d svc=%s svctx=%d sz=%d ch=%d)"), 
                it->second.count_, userid, svcid.c_str(), spbc->id(), len, channel->get_id()));
            }
          }
          else
          {
            ACE_DEBUG((LM_ERROR, ACE_TEXT("%s: unexpected operation type(type=%d c=%d svc=%s svctx=%d ch=%d)"), 
              op->type(), spctx->userid(), spbc->svcid().c_str(), spbc->id(), channel->get_id()));
          }

          op = nextop;
        }
        while(0 == rc && op);
      }
      else
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("C2S is FAILED. Backend service is already closed(count=%d c=%d svc=%s svctx=%d ch=%d)"), 
          it->second.count_, spctx->userid(), spbc->svcid().c_str(), spbc->id(), channel->get_id()));
      }

      //  удаляем операции в случае фейла
      if (rc < 0 && op)
      {
        NI_PROFILE_BLOCK( "close operations" );

        do
        {
          NI_PROFILE_BLOCK( "close op" );
          Operation* tmp = op->next();
          op->Close();
          op = tmp;
        }
        while(op);
      }
    }
  }

  {
    NI_PROFILE_BLOCK( "svc2ops_.clear" );
    svc2ops_.clear();
  }

  return rc;
}

void RelayClientProtocol::OnPacketHandlingCompleted(int rc, size_t len, char const * data, Terabit::AsynchChannel *channel)
{
  ACE_DEBUG((LM_DEBUG, ACE_TEXT("Packet handling completed (ch=%d sz=%d)"), channel->get_id(), len));
}

void RelayClientProtocol::on_reset ()
{
  --count_;
  NI_ASSERT(count_ >= 0, "Count must be not less than 0");
  ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s(count=%d)"), __FUNCTION__, count_.value()));
  wpctx_.reset();
  userid_ = 0;
  channelid_ = static_cast< unsigned int >(-1);
  lastKeepaliveMsg_ = 0;
  lastKeepaliveMsgCheckTime_ = 0;
  totalWrittenBytes_ = 0;
  amountOfReadBytes_ = 0;
  totalReadBytes_ = 0;
}

int RelayClientProtocol::applyConnectionSettings(Terabit::AsynchChannel *channel)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));

  ConnectionSettings cs;
  cs.rcvbufSize_ = RelayServer2Cfg::GetClientReadSize();
  cs.disableNagleAlgorithm_ = RelayServer2Cfg::GetClientDisableNagleAlgorithm();
  cs.enableWriteNotifications_ = RelayServer2Cfg::GetClientWriteCompleteNotify();

  return BaseProtocol::applyConnectionSettings(channel, cs);
}

int RelayClientProtocol::on_channel_up (Terabit::AsynchChannel *channel)
{
  ++count_;
  ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s(id=%d count=%d)"), __FUNCTION__, channel->get_id(), count_.value()));

  int rc = applyConnectionSettings(channel);
  if (rc < 0)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't set connection settings(ch=%d)"), 
      __FUNCTION__, channel->get_id()));
    return rc;
  }

  //  register new connection
  RelayChannelManager* pMngr = manager(channel);
  pMngr->RegisterConnection(channel->get_id(), Terabit::AsynchChannelPtr(channel));

  if (RelayServer2Cfg::Get2NewConnectionTimeout() != 0)
  {
    ACE_Time_Value tv(RelayServer2Cfg::Get2NewConnectionTimeout());
    channel->start_timer(tv, reinterpret_cast<const void*>(Timer::NEW_CONNECTION));
  }

  return 0;
}

void RelayClientProtocol::on_channel_done (Terabit::AsynchChannel *channel)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(id=%d)"), __FUNCTION__, channel->get_id()));

  ClientContextSP spctx = wpctx_.strong();
  if (!spctx.null())
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("Closing client connection(c=%d ch=%d)"), 
      spctx->userid(), channel->get_id()));

    spctx->close();
    spctx->ClosePipes();

    manager(channel)->newClientVerifier()->NotifyClientDisconnected(spctx->userid());
    manager(channel)->RemoveClient(spctx->userid());
  }
  else
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("Closing unregistered client connection(ch=%d)"), 
      channel->get_id()));
    Terabit::AsynchChannelPtr spchnl = manager(channel)->UnregisterConnection(channel->get_id());
    if (!spchnl)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("Try unregister unregitered connection(ch=%d)"), 
        channel->get_id()));
    }
  }
}

int RelayClientProtocol::on_write_completed (Terabit::AsynchChannel *channel)
{
  if (RelayServer2Cfg::GetClientReportAmountOfWrittenBytes())
  {
    Terabit::AsynchChannel::Info info(channel->get_id());
    channel->get_info(info);
    unsigned long long diff = (unsigned long long)info.total_snd_ - totalWrittenBytes_;
    if (diff > RelayServer2Cfg::GetClientReportAmountOfWrittenBytes())
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("%s(ch=%d amountOfWrittenBytes=%d totalWrittenBytes=%d)"), 
        __FUNCTION__, channel->get_id(), RelayServer2Cfg::GetClientReportAmountOfWrittenBytes(), info.total_snd_));
      totalWrittenBytes_ = info.total_snd_;
    }
  }

  ACE_DEBUG((LM_DEBUG, ACE_TEXT("Client write completed (ch=%d)"), channel->get_id()));
  return 0;
}

int RelayClientProtocol::on_read_completed (Terabit::AsynchChannel *channel,
                               const char    *data,
                               size_t         length)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  if (RelayServer2Cfg::GetClientReportAmountOfReadBytes())
  {
    amountOfReadBytes_ += length;
    if (amountOfReadBytes_ > RelayServer2Cfg::GetClientReportAmountOfReadBytes())
    {
      totalReadBytes_ += amountOfReadBytes_;
      ACE_ERROR((LM_INFO, ACE_TEXT("%s(ch=%d length=%d amountOfReadBytes=%d totalReadBytes=%Q)"), 
        __FUNCTION__, channel->get_id(), length, amountOfReadBytes_, totalReadBytes_));
      amountOfReadBytes_ = 0;
    }
  }

  int rc = transport_handler_.getNetworkHandler().HandleInput(channel, data, length);
  OnReadHandlingCompleted(rc, length, data, channel);
  if (rc < 0)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: failed(ch=%d length=%d)"), 
      __FUNCTION__, channel->get_id(), length));
  }
  return rc;
}

int RelayClientProtocol::on_timeout (Terabit::AsynchChannel *channel,
                        const void    *arg)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));

  int rc = -1;
  if (Timer::NEW_CONNECTION == DarkSide::ptr2int<unsigned int>(arg))
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("New connection timer is expired (ch=%d, t/o = %d)"), 
      channel->get_id(), RelayServer2Cfg::Get2NewConnectionTimeout()));

    manager(channel)->UnregisterConnection(channel->get_id());
  }
  else
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("Unknown timer is expired (ch=%d)"), channel->get_id()));
  }

  return rc;
}

int RelayClientProtocol::check_activity (Terabit::AsynchChannel *channel, ACE_Time_Value const & )
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(id=%d)"), __FUNCTION__, channel->get_id()));

  ClientContextSP spctx = wpctx_.strong();
  if (spctx.null())
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s : client context is NULL (ch=%d)"), __FUNCTION__, channel->get_id()));
    return -1;
  }

  int rc = 0;
  time_t now = ACE_OS::gettimeofday().sec();
  if (now - lastKeepaliveMsgCheckTime_ >= RelayServer2Cfg::GetKeepAliveTimeout())
  {
    lastKeepaliveMsgCheckTime_ = ACE_OS::gettimeofday().sec();

    if (RelayServer2Cfg::GetKeepAliveTimeout() > 0)
    {
      time_t keepaliveTimeout = time_t(RelayServer2Cfg::GetKeepAliveTimeout());
      if (lastKeepaliveMsg_ && lastKeepaliveMsg_ + keepaliveTimeout < now)
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("'Keepalive' timeout is expired(ch=%d u=%d lastkeepalivemsg=%Q keepaliveto=%Q now=%Q)"), 
          channel->get_id(), spctx->userid(), lastKeepaliveMsg_, keepaliveTimeout, now));
        rc = -1;
      }
    }
  }

  if (rc >= 0 && RelayServer2Cfg::GetOpenClientChannelTimeout() > 0)
  {
    spctx->CheckOpenChnlOpTimeout();
  }

  return rc;
}

int RelayClientProtocol::on_user_operation(Terabit::AsynchChannel *channel, Operation* op)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d op=%d)"), __FUNCTION__, channel->get_id(), op->type()));

  int rc = -1;

  do
  {
    rc = -1;
    Operation* nextop = op->next();

    //switch(op->type())
    //{
    //default:
    //  ACE_ERROR((LM_ERROR, ACE_TEXT("%s(ch=%d o=%d). Unknown operation"), __FUNCTION__, channel->get_id(), op->type()));
    //  rc = -1;
    //}

    op = nextop;
  }
  while(0 == rc && op);

  return rc;
}

int RelayClientProtocol::HandleAddRecipientRequest(Transport::AddRecipientRequest *pMsg, Terabit::AsynchChannel *channel)
{
  return -1;
}

int RelayClientProtocol::HandleAddRecipientResponse(Transport::AddRecipientResponse *pMsg, Terabit::AsynchChannel *channel)
{
  return -1;
}

int RelayClientProtocol::HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, Terabit::AsynchChannel *channel)
{
  return -1;
}

}
