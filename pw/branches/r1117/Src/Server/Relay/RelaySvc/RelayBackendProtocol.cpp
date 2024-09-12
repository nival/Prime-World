#pragma warning( disable : 4996)
#include "stdafx.h"
#include "IOTerabit/AsynchChannel.h"
#include "RelayChannelManager.h"
#include "TransportMessagesHeaders.h"
#include "BackendContext.h"
#include "OpenChnl2SvcOp.h"
#include "C2STransmissionOp.h"
#include "RelayServer2Cfg.h"
#include <ace/OS_NS_sys_socket.h>
#include "RelayBackendProtocol.h"
#include "MulticastPipe.h"

using namespace Terabit;
using namespace Transport;

namespace Relay
{

RelayBackendProtocol::RelayBackendProtocol(Terabit::ProtocolFactory& factory)
  : BaseProtocol(factory, false, "Backend"),
  totalWrittenBytes_(0),
  amountOfReadBytes_(0),
  totalReadBytes_(0),
  svcPingSeqNum_(0),
  lastestInternalServicePingTime_(0)
{
}

RelayBackendProtocol::~RelayBackendProtocol()
{
}

int RelayBackendProtocol::applyConnectionSettings(Terabit::AsynchChannel *channel)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));

  ConnectionSettings cs;
  cs.rcvbufSize_ = RelayServer2Cfg::GetBackendReadSize();
  cs.disableNagleAlgorithm_ = RelayServer2Cfg::GetBackendDisableNagleAlgorithm();
  cs.enableWriteNotifications_ = RelayServer2Cfg::GetBackendWriteCompleteNotify();

  return BaseProtocol::applyConnectionSettings(channel, cs);
}

int RelayBackendProtocol::on_channel_up (Terabit::AsynchChannel *channel)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));

  int rc = applyConnectionSettings(channel);
  if (rc < 0)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't set connection settings(ch=%d)"), 
      __FUNCTION__, channel->get_id()));
    return rc;
  }

  if (act())
  {
    RelayChannelManager* pMngr = manager(channel);
    SvcConnectionManager* scm = pMngr->getSvcConnectionManager();
    SvcConnectionManager::ICallback* pcb = reinterpret_cast<SvcConnectionManager::ICallback*>(act());
    AutoOpPtr<OpenChnl2SvcOp> apec2s(reinterpret_cast<OpenChnl2SvcOp*>(pcb->act()));

    ACE_ERROR((LM_INFO, ACE_TEXT("Connection to service established (ch=%d, c=%d, svc=%s)"), 
      channel->get_id(), apec2s->GetClientCtx()->userid(), apec2s->GetDstSvcId().c_str()));

    //  register service
    BackendContextSP spbc = pMngr->RegisterService(apec2s->GetDstSvcId(), channel);
    if (!spbc.null())
    {
      if (!spbc->isclosed())
      {
        spctx_ = spbc;

        scm->OnConnectionCompleted(pcb, spbc);

        rc = apec2s->StartChannelCreation(spbc);
        if (0 == rc)
          apec2s.release();
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s: service context already CLOSED(svc=%s svctx=%d ch=%d)"), 
          __FUNCTION__, spbc->svcid().c_str(), spbc->id(), channel->get_id()));
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s: can't register service(ch=%d svc=%s)"), __FUNCTION__, 
        channel->get_id(), apec2s->GetDstSvcId()));
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: connection to service established, but async completion token is null(ch=%d)"), 
      __FUNCTION__, channel->get_id()));
  }

  return rc;
}

void RelayBackendProtocol::on_channel_done (Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return );

  ACE_ERROR((LM_INFO, ACE_TEXT("%s (ch=%d svc=%s svctx=%d)"), 
    __FUNCTION__, channel->get_id(), spbc->svcid().c_str(), spbc->id()));

  spbc->close(true);

  manager(channel)->RemoveService(spbc->id());
}

int RelayBackendProtocol::HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, 
                                                   Terabit::AsynchChannel *channel)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d m=%d)"), __FUNCTION__, 
    channel->get_id(), pMsg->GetTypeId()));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  RelayChannelManager* pmngr = manager(channel);

  ACE_ERROR((LM_INFO, ACE_TEXT("Open multicast channel request received(s=%s t=%s svc=%s senderPipeid=%d)"), 
    pMsg->clientAddress.source.c_str(), pMsg->clientAddress.target.c_str(), spbc->svctxid().c_str(), pMsg->localPipeId));

  int rc = 0;
  if (Transport::EChannelType::Multicast != pMsg->channelType)
  {
    rc = -1;
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Incorrect channel type. Only multicast channels accepted (ch=%d s=%s t=%s svc=%s chnlType=%s)"), 
      __FUNCTION__, channel->get_id(), pMsg->clientAddress.source.c_str(), 
      pMsg->clientAddress.target.c_str(), spbc->svctxid().c_str(), Transport::EChannelType::ToString(pMsg->channelType)));
  }
  else
  if (pmngr->backendSvcid() != pMsg->clientAddress.target)
  {
    rc = -1;
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Wrong target (ch=%d s=%s t=%s svc=%s)"), 
      __FUNCTION__, channel->get_id(), pMsg->clientAddress.source.c_str(), 
      pMsg->clientAddress.target.c_str(), spbc->svctxid().c_str()));
  }

  if (rc < 0)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("Open multicast channel FAILED(s=%s t=%s svc=%s senderPipeid=%d)"), 
      pMsg->clientAddress.source.c_str(), pMsg->clientAddress.target.c_str(), spbc->svctxid().c_str(), pMsg->localPipeId));

    rc = SendOpenChannelResponse(channel, false, pMsg->clientAddress, pMsg->localPipeId, 
      ChannelAddr(EKnownPipeId::Invalid, pMsg->clientAddress.client, pMsg->clientAddress.client), pMsg->channelType);
    return 0;
  }

  MulticastPipeSP pipe = spbc->RegisterMulticastPipe();
  if (!pipe.null())
  {
    rc = SendOpenChannelResponse(channel, true, pMsg->clientAddress, pMsg->localPipeId, 
      ChannelAddr(pipe->svcpipeid(), pMsg->clientAddress.client, pMsg->clientAddress.client), pMsg->channelType);
    if (rc < 0)
      ACE_ERROR((LM_WARNING, ACE_TEXT("Can't send an open multicast channel response (s=%s t=%s svc=%s svcpid=%d senderPipeid=%d)"), 
        pMsg->clientAddress.source.c_str(), pMsg->clientAddress.target.c_str(), pipe->svctxid().c_str(), pipe->svcpipeid(), pMsg->localPipeId));
    else
      ACE_ERROR((LM_INFO, ACE_TEXT("Open multicast channel response sent(s=%s t=%s svc=%s svcpid=%d senderPipeid=%d)"), 
        pMsg->clientAddress.source.c_str(), pMsg->clientAddress.target.c_str(), pipe->svctxid().c_str(), pipe->svcpipeid(), pMsg->localPipeId));
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't create multicast pipe(ch=%d svc=%s t=%s)"), 
      __FUNCTION__, channel->get_id(), spbc->svctxid().c_str(), pMsg->clientAddress.target.c_str()));
  }

  return 0;
}

int RelayBackendProtocol::HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d m=%d c=%d p=%d)"), __FUNCTION__, 
    channel->get_id(), pMsg->GetTypeId(), pMsg->remoteAddr.client, pMsg->localPipeId));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  int rc = 0;
  AutoOpPtr<OpenChnl2SvcOp> apec2sop(spbc->FindOpenChnlOp(BackendPipeId(pMsg->remoteAddr.client, pMsg->localPipeId)));
  if (apec2sop.get())
  {
    rc = apec2sop->OnChannelEstablished((pMsg->success ? OpenChnl2SvcOp::Result::SUCCESS : OpenChnl2SvcOp::Result::DECLINED), pMsg, spbc);
    if (rc < 0)
    {
      //  close client
      apec2sop->GetClientCtx()->closeConnection();

      rc = 0; //  ошибка в обработке клиентской операции не может быть причиной
              //  закрытия соединения с сервисом
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("Can't find OpenChnl2SvcOp (ch=%d c=%d t=%s s=%s rc=%d)"), 
      channel->get_id(), pMsg->clientAddress.client, pMsg->clientAddress.target.c_str(), pMsg->clientAddress.source.c_str(), pMsg->remoteAddr.client));
  }

  return rc;
}

int RelayBackendProtocol::HandleCloseChannel(Transport::CloseChannelMessage *pMsg, 
                                             Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d m=%d)"), __FUNCTION__, 
    channel->get_id(), pMsg->GetTypeId()));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  int rc = 0;
  ChannelAddr const & caddr = pMsg->clientAddress;
  RelayChannelManager* pmngr = manager(channel);
  ClientContextSP spcc = pmngr->FindClient(pMsg->clientAddress.client);
  if (!spcc.null())
  {
    if (!spcc->isclosed())
    {
      UnicastPipeSP svcpipe = spcc->FindUnicastPipe(spbc->svcid(), caddr.pipe);
      if (!svcpipe.null())
      {
        if (svcpipe->close())
        {
          Transport::TPipeId cpid = svcpipe->cpipeid();
          Transport::TPipeId svcpid = caddr.pipe;

          ACE_DEBUG((LM_DEBUG, ACE_TEXT("S2C Close channel(svc=%s svctx=%d svcpid=%d c=%d cpid=%d ch=%d)"), 
            spbc->svcid().c_str(), spbc->id(), svcpid, caddr.client, cpid, channel->get_id()));

          //  check sequence
#ifndef TRANSPORT_SEQ_PACKET_CHECK
          if (caddr.SeqNum())
#endif
          {
            if (svcpipe->lastInS2CSeqNum() + 1 == caddr.SeqNum())
            {
              svcpipe->lastInS2CSeqNum(caddr.SeqNum());
            }
            else
            {
              ACE_ERROR((LM_ERROR, ACE_TEXT("Close channel: wrong message sequence (lisn=%d isn=%d c=%d svc=%s svctx=%d svcpid=%d ch=%d)"), 
                svcpipe->lastInS2CSeqNum(), caddr.SeqNum(), spcc->userid(), spbc->svcid().c_str(), spbc->id(), svcpid, channel->get_id()));
              ACE_ASSERT(!"Close channel: wrong message sequence");
            }
          }

          spcc->TrackInputThreshold(cpid);

          spbc->DetachUnicastPipe(svcpipe);

          Transport::CloseChannelMessage msg;
          msg.clientAddress = ChannelAddr(svcpipe->cpipeid(), spcc->userid(), autoAssignClientId, svcpipe->lastInS2CSeqNum());
          rc = spcc->HandleCloseChannel(&msg);
          if (rc < 0)
          {
            ACE_ERROR((LM_ERROR, ACE_TEXT("%s: can't send close channel msg to client(c=%d cch=%d cpid=%d svc=%s svctx=%d svcpid=%d sch=%d)"), 
              __FUNCTION__, spcc->userid(), spcc->channelId(), cpid, spbc->svcid().c_str(), spbc->id(), svcpid, channel->get_id()));
          }
          else
          {
            ACE_ERROR((LM_INFO, ACE_TEXT("%s: send close channel msg to client(c=%d cch=%d cpid=%d svc=%s svctx=%d svcpid=%d sch=%d)"), 
              __FUNCTION__, spcc->userid(), spcc->channelId(), cpid, spbc->svcid().c_str(), spbc->id(), svcpid, channel->get_id()));
          }

          rc = 0;
        }
        else
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("Pipe is already closed(c=%d cpid=%d spid=%d svc=%s svctx=%d ch=%d)"), 
            caddr.client, svcpipe->cpipeid(), svcpipe->svcpipeid(), spbc->svcid().c_str(), spbc->id(), channel->get_id()));
          rc = 0;
        }
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("No pipe found for client(c=%d p=%d ch=%d)"), caddr.client, caddr.pipe, channel->get_id()));
        rc = 0;
      }
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("Client contexts is already closed(c=%d ch=%d)"), caddr.client, channel->get_id()));
      rc = 0;
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("Client is not found(c=%d ch=%d)"), caddr.client, channel->get_id()));
    rc = 0;
  }

  return rc;
}


int RelayBackendProtocol::HandleCloseMulticastChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d m=%d)"), __FUNCTION__, 
    channel->get_id(), pMsg->GetTypeId()));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  int rc = 0;
  ChannelAddr const & caddr = pMsg->clientAddress;

  //  unregister pipe
  MulticastPipeSP pipe = spbc->UnregisterMulticastPipe(caddr.pipe);
  if (!pipe.null())
  {
    if (pipe->close())
    {
      pipe->HandleCloseChannel();
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: pipe is not found(svctxid=%s pid=%d ch=%d)"), 
      __FUNCTION__, spbc->svctxid().c_str(), caddr.pipe, channel->get_id()));
  }

  return rc;
}

int RelayBackendProtocol::HandlePingMessage(Transport::PingMessage *pMsg, Terabit::AsynchChannel *channel)
{
  int rc = -1;
  if (pMsg->reply)
  {
    rc = 0;

    unsigned long long nowms = 0;
    ACE_OS::gettimeofday().msec(static_cast< long >( nowms ));
    unsigned long long ping = nowms - pMsg->sendTime;

    ACE_ERROR((LM_INFO, ACE_TEXT("%s. Ping is %d ms(seqnum=%d p=%d c=%d s=%d ch=%d)"), __FUNCTION__,
      (long)ping, pMsg->seqNum, pMsg->requestingChannel.pipe, 
      pMsg->requestingChannel.client, pMsg->requestingChannel.sender, channel->get_id()));
  }
  else
  {
    PingMessage msg(*pMsg);
    msg.reply = true;
    rc = transport_handler_.HandleOutput(&msg, ChannelAddr(EKnownPipeId::NetLogic, msg.requestingChannel.client), channel);
  }

  return rc;
}

int RelayBackendProtocol::HandlePingMessage(Transport::ThroughPingMessage *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_FUNCTION;

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d c=%d)"), __FUNCTION__, 
    channel->get_id(), pMsg->requestingChannel.client));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  int rc = -1;
  ClientContextSP spcc = spbc->FindClientContext(pMsg->requestingChannel.client);
  if (!spcc.null())
  {
    rc = spcc->HandleOutput(pMsg);
    if (rc < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s.ping: can't send data to client(c=%d cch=%d svc=%s svctx=%d sch=%d)"), 
        __FUNCTION__, spcc->userid(), spcc->channelId(), spbc->svcid().c_str(), spbc->id(), channel->get_id()));
      rc = 0;
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("No client(c=%d ch=%d) found"), pMsg->requestingChannel.client, channel->get_id()));
    rc = 0;
  }

  return rc;
}

int RelayBackendProtocol::HandleInput(Terabit::AsynchChannel* channel, Transport::MessageHeader const & header,
                                      Transport::MessageBase *pMsg)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d p=%d c=%d s=%d m=%d)"), __FUNCTION__, 
    channel->get_id(), header.pipe, header.client, header.sender, pMsg->GetTypeId()));

  return -1;
}

int RelayBackendProtocol::HandleInput(Terabit::AsynchChannel* channel, Transport::ChannelAddr const & caddr, char const * data, size_t len)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d l=%d p=%d c=%d seq=%d)"), __FUNCTION__, 
    channel->get_id(), len, caddr.pipe, caddr.client, caddr.SeqNum()));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  int rc = -1;
  ClientContextSP spcc = spbc->FindClientContext(caddr.client);
  if (!spcc.null())
  {
    UnicastPipeSP svcpipe = spcc->FindUnicastPipe(spbc->svcid(), caddr.pipe);
    if (!svcpipe.null())
    {
      Transport::TPipeId cpid = svcpipe->cpipeid();
      Transport::TPipeId svcpid = caddr.pipe;

      ACE_DEBUG((LM_DEBUG, ACE_TEXT("S2C IN(svc=%s svctx=%d svcpid=%d c=%d cpid=%d sz=%d ch=%d)"), 
        spbc->svcid().c_str(), spbc->id(), svcpid, caddr.client, cpid, len, channel->get_id()));

      //  check sequence
#ifndef TRANSPORT_SEQ_PACKET_CHECK
      if (caddr.SeqNum())
#endif
      {
        if (svcpipe->lastInS2CSeqNum() + 1 == caddr.SeqNum())
        {
          svcpipe->lastInS2CSeqNum(caddr.SeqNum());
        }
        else
        {
          ACE_ERROR((LM_ERROR, ACE_TEXT("S2C: wrong message sequence (lisn=%d isn=%d c=%d svc=%s svctx=%d svcpid=%d sz=%d ch=%d)"), 
            svcpipe->lastInS2CSeqNum(), caddr.SeqNum(), spcc->userid(), spbc->svcid().c_str(), spbc->id(), svcpid, len, channel->get_id()));
          ACE_ASSERT(!"S2C: wrong message sequence");
        }
      }

      StrongMT<ITrafficTracker> tt = svcpipe->trafficTracker();
      if (tt)
        tt->HandlePacket(caddr, data, len);

      rc = spcc->HandleOutput(cpid, data, len, caddr.SeqNum());
      if (rc < 0)
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s: can't send data to client(c=%d cch=%d cpid=%d svc=%s svctx=%d svcpid=%d sz=%d sch=%d)"), 
          __FUNCTION__, spcc->userid(), spcc->channelId(), cpid, spbc->svcid().c_str(), spbc->id(), svcpid, len, channel->get_id()));
      }

      rc = len;
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("No pipe(%d) found for client(%d). S2C."), caddr.pipe, caddr.client));
      rc = len;
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("No client(c=%d ch=%d) found"), caddr.client, channel->get_id()));
    rc = len;
  }

  return rc;
}

int RelayBackendProtocol::HandleMulticastInput(Terabit::AsynchChannel* channel, Transport::ChannelAddr const & caddr, 
                                               char const * data, size_t len)
{
  NI_PROFILE_FUNCTION;

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d l=%d p=%d c=%d seq=%d)"), __FUNCTION__, 
    channel->get_id(), len, caddr.pipe, caddr.client, caddr.SeqNum()));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  int rc = -1;
  MulticastPipeSP pipe = spbc->FindMulticastPipe(caddr.pipe);
  if (!pipe.null())
  {
    rc = pipe->HandleOutput(data, len);
  }
  rc = len;

  return rc;
}

void RelayBackendProtocol::OnPacketHandlingCompleted(int rc, size_t len, char const * data, Terabit::AsynchChannel *channel)
{
  ACE_DEBUG((LM_DEBUG, ACE_TEXT("Packet handling completed (ch=%d sz=%d)"), channel->get_id(), len));
}

void RelayBackendProtocol::on_reset ()
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s()"), __FUNCTION__));
  spctx_.reset();
}

int RelayBackendProtocol::on_write_completed (Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  if (RelayServer2Cfg::GetBackendReportAmountOfWrittenBytes())
  {
    Terabit::AsynchChannel::Info info(channel->get_id());
    channel->get_info(info);
    unsigned long long diff = (unsigned long long)info.total_snd_ - totalWrittenBytes_;
    if (diff > RelayServer2Cfg::GetBackendReportAmountOfWrittenBytes())
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("%s(ch=%d amountOfWrittenBytes=%d totalWrittenBytes=%d)"), 
        __FUNCTION__, channel->get_id(), RelayServer2Cfg::GetBackendReportAmountOfWrittenBytes(), info.total_snd_));
      totalWrittenBytes_ = info.total_snd_;
    }
  }

  ACE_DEBUG((LM_DEBUG, ACE_TEXT("Backend write completed (ch=%d)"), channel->get_id()));
  return 0;
}

int RelayBackendProtocol::on_read_completed (Terabit::AsynchChannel *channel,
                                            const char    *data,
                                            size_t         length)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  if (RelayServer2Cfg::GetBackendReportAmountOfReadBytes())
  {
    NI_PROFILE_BLOCK("ReportAmountOfReadBytes");

    amountOfReadBytes_ += length;
    if (amountOfReadBytes_ > RelayServer2Cfg::GetBackendReportAmountOfReadBytes())
    {
      totalReadBytes_ += amountOfReadBytes_;
      ACE_ERROR((LM_INFO, ACE_TEXT("%s( ch=%d length=%d amountOfReadBytes=%d totalReadBytes=%Q)"), 
        __FUNCTION__, channel->get_id(), length, amountOfReadBytes_, totalReadBytes_ ));
      amountOfReadBytes_ = 0;
    }
  }

  NI_PROFILE_BLOCK("HandleInput");
  return transport_handler_.getNetworkHandler().HandleInput(channel, data, length);
}

int RelayBackendProtocol::on_timeout (Terabit::AsynchChannel *channel,
                                     const void    *arg)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  return -1;
}

int RelayBackendProtocol::check_activity (Terabit::AsynchChannel *channel,
                                         const ACE_Time_Value&  last_op_time)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  ACE_ERROR((LM_INFO, ACE_TEXT("%s(svcid=%s svctx=%d ch=%d)"), __FUNCTION__, spbc->svcid().c_str(), spbc->id(), channel->get_id()));

  int rc = 0;
  if (RelayServer2Cfg::GetInternalServicePingPeriod() > 0)
  {
    time_t now = ACE_OS::gettimeofday().sec();
    if (now - lastestInternalServicePingTime_ >= RelayServer2Cfg::GetInternalServicePingPeriod())
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("%s: start internal service ping(svcid=%s svctx=%d ch=%d)"), 
        __FUNCTION__, spbc->svcid().c_str(), spbc->id(), channel->get_id()));

      lastestInternalServicePingTime_ = now;

      //  send ping
      Transport::PingMessage msg;
      msg.requestingChannel = Transport::ChannelAddr(Transport::EKnownPipeId::NetLogic, Transport::autoAssignClientId);
      msg.seqNum = ++svcPingSeqNum_;
      msg.reply = false;
      ACE_OS::gettimeofday().msec(static_cast< long >( msg.sendTime ));
      rc = transport_handler_.HandleOutput(&msg, ChannelAddr(EKnownPipeId::NetLogic, Transport::autoAssignClientId), channel);
    }
  }

  if (rc >= 0 && RelayServer2Cfg::GetOpenBackendChannelTimeout() > 0)
  {
    rc = spbc->CheckOpenChnlOpTimeout();
  }

  return rc;
}

int RelayBackendProtocol::on_user_operation(Terabit::AsynchChannel *channel, Operation* op)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d op=%d)"), __FUNCTION__, 
    channel->get_id(), op->type()));

  int rc = -1;

  do
  {
    rc = -1;
    Operation* nextop = op->next();

    switch(op->type())
    {
      case OperationType::C2S_TRANSMISSION:
      {
        C2STransmissionOp* csop = static_cast<C2STransmissionOp*>(op);
        rc = csop->Complete(channel, &transport_handler_);
      }
      break;

      default:
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s(ch=%d op=%d). Unknown operation"), __FUNCTION__, 
          channel->get_id(), op->type()));
        op->Close();
      }
    }

    op = nextop;
  }
  while(0 == rc && op);

  if (rc < 0)
  {
    //  TODO:
    //  удалять необработанные операции в цепочке?
  }

  //  TODO:
  //  если случилась ошибка в обработке операции(rc < 0) -> это не повод закрывать соединение с сервисом
  //  нужна специальная обработка для каждой конкретной операции
  return 0;
}

int RelayBackendProtocol::ValidateContext(BackendContextSP const & _ctx, char const * const _funcname, int _chnlid) const
{
  NI_PROFILE_FUNCTION;

  if (_ctx.null())
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s(ch=%d). Context is null"), _funcname, _chnlid));
    return -1;
  }

  if (_ctx->isclosed())
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: context is CLOSED(svcid=%s svctx=%d ch=%d)"), _funcname, 
      _ctx->svcid(), _ctx->id(), _chnlid));
    return -1;
  }

  return 0;
}

int RelayBackendProtocol::HandleAddRecipientRequest(Transport::AddRecipientRequest *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_FUNCTION;

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d pipe=%d recipient=%d)"), __FUNCTION__, 
    channel->get_id(), pMsg->caddr.pipe, pMsg->recipient));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  MulticastPipeSP pipe = spbc->FindMulticastPipe(pMsg->caddr.pipe);
  if (!pipe.null())
  {
    //  find client by recipient id
    ClientContextSP spcc = spbc->FindClientContext(pMsg->recipient);
    if (!spcc.null() && !spcc->isclosed())
    {
      //  open channel to client
      OpenChnl2ClientOpPtr op(new OpenChnl2ClientOp(spbc, pipe, spcc, *pMsg), false);
      int rc = op->Start();
      if (rc < 0)
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("Can't start open channel to client(ch=%d pipe=%d recipient=%d)"), __FUNCTION__, 
          channel->get_id(), pMsg->caddr.pipe, pMsg->recipient));
      }
    }
    else
    {
      SendAddRecipientResponse(channel, Transport::AddRecipientResult::NO_CLIENT, pipe->svcpipeid(), pMsg->recipient);
    }
  }
  else
  {
    SendAddRecipientResponse(channel, Transport::AddRecipientResult::NO_CHANNEL, pMsg->caddr.pipe, pMsg->recipient);
  }

  return 0;
}

int RelayBackendProtocol::SendAddRecipientResponse(Terabit::AsynchChannel *channel, AddRecipientResult::Enum result, Transport::TPipeId pipe, 
                                                   Transport::TClientId const & recipient)
{
  NI_PROFILE_FUNCTION;

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d,r=%d)"), __FUNCTION__, channel->get_id(), result));

  AddRecipientResponse msg;
  msg.result = result;
  msg.caddr = ChannelAddr(pipe, Transport::autoAssignClientId);
  msg.recipient = recipient;

  return transport_handler_.HandleOutput(&msg, ChannelAddr(EKnownPipeId::NetLogic, msg.caddr.client), channel);
}

int RelayBackendProtocol::HandleAddRecipientResponse(Transport::AddRecipientResponse *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_FUNCTION;

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  ACE_ERROR((LM_ERROR, ACE_TEXT("%s: service MUST NOT send add recipient response (spid=%d recipient=%d svc=%s)"), 
    __FUNCTION__, pMsg->caddr.pipe, pMsg->recipient, spbc->svctxid().c_str()));

  return -1;
}

int RelayBackendProtocol::HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, Terabit::AsynchChannel *channel)
{
  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d pipe=%d recipient=%d)"), __FUNCTION__, 
    channel->get_id(), pMsg->caddr.pipe, pMsg->recipient));

  BackendContextSP spbc = spctx_;
  VALIDATE_CONTEXT(spbc, __FUNCTION__, channel->get_id(), return -1);

  MulticastPipeSP pipe = spbc->FindMulticastPipe(pMsg->caddr.pipe);
  if (!pipe.null())
  {
    Transport::TPipeId cpid = pipe->RemoveRecipient(pMsg->recipient);
    if (cpid != Transport::EKnownPipeId::Invalid)
    {
      //  find client by recipient id
      ClientContextSP spcc = spbc->FindClientContext(pMsg->recipient);
      if (!spcc.null() && !spcc->isclosed())
      {
        Transport::CloseChannelMessage ccm;
        ccm.clientAddress = ChannelAddr(cpid, pMsg->recipient);
        if (spcc->HandleCloseChannel(&ccm, false) < 0)
          ACE_ERROR((LM_WARNING, ACE_TEXT("%s: can't send close channel message to client(c=%d cpid=%d spid=%d svc=%s)"), 
            __FUNCTION__, pMsg->recipient, cpid, pipe->svcpipeid(), spbc->svctxid().c_str()));
        else
          ACE_ERROR((LM_INFO, ACE_TEXT("%s: send close channel message successfully(c=%d cpid=%d spid=%d svc=%s)"), 
            __FUNCTION__, pMsg->recipient, cpid, pipe->svcpipeid(), spbc->svctxid().c_str()));
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s: client is NOT found or client is already closed(c=%d svc=%s)"), 
          __FUNCTION__, pMsg->recipient, spbc->svctxid().c_str()));
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s: no such recipient in multicast channel(c=%d spid=%d svc=%s)"), 
        __FUNCTION__, pMsg->recipient, pipe->svcpipeid(), spbc->svctxid().c_str()));
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s: multicast pipe is NOT found (spid=%d recipient=%d svc=%s)"), 
      __FUNCTION__, pMsg->caddr.pipe, pMsg->recipient, spbc->svctxid().c_str()));
  }

  return 0;
}

}
