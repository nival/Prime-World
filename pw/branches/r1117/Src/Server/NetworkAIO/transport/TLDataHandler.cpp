#include "transport/stdafx.h"
#include "transport/TLDataHandler.h"
#include "transport/TLConnection.h"
#include "transport/TLChannelInt.h"
#include <Network/TransportUtils.h>
#include "transport/TLChannelFactory.h"
#include <ace/OS_NS_sys_time.h>
#include <Network/TransportMessages.h>
#include "transport/TLChannelOp.h"

namespace TransportLayer
{
#pragma warning( push )
#pragma warning( disable : 4355)
  DataHandler::DataHandler(Transport::MessageFactory* pMsgFactory, TL::ChannelFactory* chnlFactory, bool packaddr)
    :tph_(this, pMsgFactory, packaddr),
    chnlFactory_(chnlFactory)
#pragma warning( pop )
  {
  }

  DataHandler::~DataHandler()
  {
  }

  naio::StatusT 
  DataHandler::HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, 
                                   naio::ConnectionContextStrongPtr const & spconnctx, 
                                   Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d t=%s s=%s)"), __FUNCTION__,
      pMsg->clientAddress.client, pMsg->clientAddress.target.c_str(), pMsg->clientAddress.source.c_str()));

    TL::ConnectionSP spconn = connection(spconnctx);
    if (spconn.null())
    {
      return naio::status::FAIL;
    }

    if (Transport::EChannelType::Unicast != pMsg->channelType)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s : incorrect channel type (c=%d t=%s s=%s chnlType=%s)"), 
        pMsg->clientAddress.client, pMsg->clientAddress.target.c_str(), pMsg->clientAddress.source.c_str(), Transport::EChannelType::ToString(pMsg->channelType)));
      return naio::status::FAIL;
    }

    Transport::ChannelAddr chnlAddr(Transport::EKnownPipeId::Invalid, pMsg->clientAddress.client);

    naio::StatusT sts = naio::status::FAIL;
    TL::IChannelInternalSP spchnl = chnlFactory_->CreateChannel(pMsg->channelType, false, spconn, pMsg->clientAddress, pMsg->loginData, tph_.messageFactory(), 0, 0);
    if (TL::IsValid(spchnl))
    {
      Transport::TPipeId pipeid = Transport::EKnownPipeId::Invalid;
      int rc = spchnl->onOpenChannel(pMsg->clientAddress, pipeid);
      if (0 == rc && pipeid != Transport::EKnownPipeId::Invalid)
      {
        chnlAddr = spchnl->chaddr();

        ACE_ERROR((LM_INFO, ACE_TEXT("[TL] New channel accepted (c=%d t=%s p=%d)"), 
          pMsg->clientAddress.client, pMsg->clientAddress.target.c_str(), pipeid));

        sts = OpenChannelResponseOutput(pMsg->channelType, true, pMsg->clientAddress, pMsg->localPipeId, spchnl->chaddr(), 
          spconnctx, outmbf, poutmb);
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] New channel DECLINED (c=%d t=%s)"), 
          pMsg->clientAddress.client, pMsg->clientAddress.target.c_str()));

        sts = OpenChannelResponseOutput(pMsg->channelType,false, pMsg->clientAddress, pMsg->localPipeId, chnlAddr, 
          spconnctx, outmbf, poutmb);
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] New channel DECLINED. Can't create channel (c=%d t=%s)"), 
        pMsg->clientAddress.client, pMsg->clientAddress.target.c_str()));

      sts = OpenChannelResponseOutput(pMsg->channelType,false, pMsg->clientAddress, pMsg->localPipeId, chnlAddr, 
        spconnctx, outmbf, poutmb);
    }

    return sts;
  }

  naio::StatusT 
  DataHandler::OpenChannelResponseOutput(Transport::EChannelType::Enum _channeltype, bool result, Transport::Address const & caddr, 
    Transport::TPipeId const & pipeid, Transport::ChannelAddr raddr,
    naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    Transport::OpenChannelResponse msg;
    msg.success = result;
    msg.clientAddress = caddr;
    msg.localPipeId = pipeid;
    msg.remoteAddr = raddr;
    msg.channelType = _channeltype;

    return tph_.HandleOutput(&msg, Transport::ChannelAddr(Transport::EKnownPipeId::NetLogic, msg.clientAddress.client), spconn, outmbf, poutmb);
  }

  naio::StatusT 
  DataHandler::HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, 
                                         naio::ConnectionContextStrongPtr const & spconnctx, 
                                         Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    naio::StatusT sts = naio::status::SUCCESS;
    TL::ConnectionSP spconn = connection(spconnctx);
    if (TL::IsValid(spconn))
    {
      int rc = spconn->completeOpenChannel(pMsg);
      if (rc < 0)
        naio::status::FAIL;
    }

    return sts;
  }

  naio::StatusT 
  DataHandler::HandleCloseChannel(Transport::CloseChannelMessage *pMsg, 
                                  naio::ConnectionContextStrongPtr const & spconnctx)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_ERROR((LM_INFO, ACE_TEXT("%s(p=%d c=%d s=%d)"), __FUNCTION__,
      pMsg->clientAddress.pipe, pMsg->clientAddress.client, pMsg->clientAddress.sender));

    naio::StatusT sts = naio::status::FAIL;
    TL::ConnectionSP spconn = connection(spconnctx);
    if (TL::IsValid(spconn))
    {
      TL::IChannelInternalSP spchnl = spconn->findChannel(pMsg->clientAddress);
      if (TL::IsValid(spchnl))
      {
        spchnl->close(false);
        spconn->onChannelClosed(spchnl);
        sts = naio::status::SUCCESS;
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Channel is not found(p=%d c=%d s=%d)"), __FUNCTION__,
          pMsg->clientAddress.pipe, pMsg->clientAddress.client, pMsg->clientAddress.sender));

        sts = naio::status::SUCCESS;  //  QFIX(NUM_TASK) - из-за corrupted data присланных одним клиентом на lobby сервис,
                                      //  пострадали все клиенты - закрыли коннекшн relay - lobby.
                                      //  Fix будет делаться по задаче NUM_TASK & NUM_TASK
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Connection is invalid(p=%d c=%d s=%d)"), __FUNCTION__,
        pMsg->clientAddress.pipe, pMsg->clientAddress.client, pMsg->clientAddress.sender));
    }

    return sts;
  }

  naio::StatusT 
  DataHandler::HandlePingMessage(Transport::PingMessage *pMsg, naio::ConnectionContextStrongPtr const & spconnctx, 
                                 Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_FUNCTION;

    naio::StatusT sts = naio::status::FAIL;
    TL::ConnectionSP spconn = connection(spconnctx);
    if (!TL::IsValid(spconn))
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Connection is invalid(p=%d c=%d s=%d)"), __FUNCTION__,
        pMsg->requestingChannel.pipe, pMsg->requestingChannel.client, pMsg->requestingChannel.sender, spconnctx->connid()));
      return sts;
    }

    TL::IChannelInternalSP spchnl = spconn->findChannel(Transport::ChannelAddr(pMsg->requestingChannel.pipe, pMsg->requestingChannel.client));
    if (!TL::IsValid(spchnl) && Transport::EKnownPipeId::NetLogic != pMsg->requestingChannel.pipe)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Channel is not found(p=%d c=%d s=%d ch=%d)"), __FUNCTION__,
        pMsg->requestingChannel.pipe, pMsg->requestingChannel.client, pMsg->requestingChannel.sender, spconnctx->connid()));
      sts = naio::status::SUCCESS;  //  QFIX(NUM_TASK) - норм фикс NUM_TASK & NUM_TASK
      return sts;
    }

    Transport::TServiceId target;
    if (TL::IsValid(spchnl))
    {
      target = spchnl->taddr().target;
    }
    else
    if (Transport::EKnownPipeId::NetLogic == pMsg->requestingChannel.pipe)
    {
      target = "netlogic";
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Unknown pipe(p=%d c=%d s=%d ch=%d)"), __FUNCTION__,
        pMsg->requestingChannel.pipe, pMsg->requestingChannel.client, pMsg->requestingChannel.sender, spconnctx->connid()));
      sts = naio::status::SUCCESS;
      return sts;
    }

    if (pMsg->reply)
    {
      unsigned long long nowms = 0;
      ACE_OS::gettimeofday().msec(static_cast< long int >( nowms ));
      unsigned long long ping = nowms - pMsg->sendTime;

      if (ping >= 0)
      {
        if (TL::IsValid(spchnl))
          spchnl->setPing(ping, pMsg->seqNum);

        ACE_ERROR((LM_INFO, ACE_TEXT("%s. Ping is %d ms(svc=%s seqnum=%d p=%d c=%d s=%d ch=%d)"), __FUNCTION__,
          (long)ping, target.c_str(), pMsg->seqNum, pMsg->requestingChannel.pipe, 
          pMsg->requestingChannel.client, pMsg->requestingChannel.sender, spconnctx->connid()));
      }
      else
      {

        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Ping is negative %d ms(svc=%s seqnum=%d p=%d c=%d s=%d ch=%d)"), __FUNCTION__,
          (long)ping, target.c_str(), pMsg->seqNum, 
          pMsg->requestingChannel.pipe, pMsg->requestingChannel.client, pMsg->requestingChannel.sender, spconnctx->connid()));
      }

      sts = naio::status::SUCCESS;
    }
    else
    {
      Transport::PingMessage msg;
      msg.reply = true;
      msg.requestingChannel = pMsg->requestingChannel;
      msg.sendTime = pMsg->sendTime;
      msg.seqNum = pMsg->seqNum;

      sts = tph_.HandleOutput(&msg, Transport::ChannelAddr(Transport::EKnownPipeId::NetLogic, pMsg->requestingChannel.client), spconnctx, outmbf, poutmb);
    }

    return sts;
  }

  naio::StatusT 
  DataHandler::HandlePingMessage(Transport::ThroughPingMessage *pMsg, naio::ConnectionContextStrongPtr const & spconnctx, 
                                 Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_FUNCTION;

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d p=%d ch=%d)"), __FUNCTION__,
      pMsg->requestingChannel.client, pMsg->requestingChannel.pipe, spconnctx->connid()));

    TL::ConnectionSP spconn = connection(spconnctx);
    if (spconn.null())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Connection is NULL(c=%d p=%d)"), __FUNCTION__,
        pMsg->requestingChannel.client, pMsg->requestingChannel.pipe));

      return naio::status::FAIL;
    }

    if (!pMsg->reply)
    {
      Transport::ThroughPingMessage pingResponse(*pMsg);
      pingResponse.reply = true;
      return tph_.HandleOutput(&pingResponse, Transport::ChannelAddr(Transport::EKnownPipeId::NetLogic, pMsg->requestingChannel.client), 
        spconnctx, outmbf, poutmb);
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Unexpected through ping message(c=%d p=%d ch=%d)"), __FUNCTION__,
        pMsg->requestingChannel.client, pMsg->requestingChannel.pipe, spconnctx->connid()));
      NI_ALWAYS_ASSERT(NI_STRFMT("Unexpected through ping message(c=%d p=%d ch=%d)", 
        pMsg->requestingChannel.client, pMsg->requestingChannel.pipe, spconnctx->connid()));

      return naio::status::SUCCESS;
    }
  }

  naio::StatusT 
  DataHandler::HandleAddRecipientResponse(Transport::AddRecipientResponse *pMsg, naio::ConnectionContextStrongPtr const & spconnctx)
  {
    NI_PROFILE_FUNCTION;

    Transport::ChannelAddr const & caddr = pMsg->caddr;

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d p=%d ch=%d)"), __FUNCTION__,
      pMsg->recipient, pMsg->caddr.pipe, spconnctx->connid()));

    naio::StatusT sts = naio::status::FAIL;
    TL::ConnectionSP spconn = connection(spconnctx);
    if (TL::IsValid(spconn))
    {
      TL::IChannelInternalSP spchnl = spconn->findChannel(pMsg->caddr);
      if (TL::IsValid(spchnl))
      {
        if (Transport::EChannelType::Multicast == spchnl->channeltype())
        {
          int rc = spchnl->OnAddRecipientResponse(pMsg->recipient, pMsg->result);
          if (rc >= 0)
            sts = naio::status::SUCCESS;
        }
        else
        {
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Wrong channel type(ctx=%d p=%d c=%d s=%d)"), 
            __FUNCTION__, spconnctx->id(), caddr.pipe, caddr.client, caddr.sender));
        }
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Channel is NULL(ctx=%d p=%d c=%d s=%d)"), 
          __FUNCTION__, spconnctx->id(), caddr.pipe, caddr.client, caddr.sender));
        sts = naio::status::SUCCESS;
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Channel not found (ctx=%d p=%d c=%d s=%d)"), 
        __FUNCTION__, spconnctx->id(), caddr.pipe, caddr.client, caddr.sender));
      sts = naio::status::SUCCESS;
    }

    return sts;
  }

  naio::StatusT 
  DataHandler::HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, naio::ConnectionContextStrongPtr const & spconnctx)
  {
    NI_PROFILE_FUNCTION;

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(p=%d c=%d recipient=%d)"), __FUNCTION__,
      pMsg->caddr.pipe, pMsg->caddr.client, pMsg->recipient));

    Transport::ChannelAddr const & caddr = pMsg->caddr;
    naio::StatusT sts = naio::status::FAIL;
    TL::ConnectionSP spconn = connection(spconnctx);
    if (TL::IsValid(spconn))
    {
      TL::IChannelInternalSP spchnl = spconn->findChannel(pMsg->caddr);
      if (TL::IsValid(spchnl))
      {
        if (Transport::EChannelType::Multicast == spchnl->channeltype())
        {
          spchnl->OnRemoveRecipient(pMsg->recipient);
          sts = naio::status::SUCCESS;
        }
        else
        {
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Wrong channel type(ctx=%d p=%d c=%d s=%d)"), 
            __FUNCTION__, spconnctx->id(), caddr.pipe, caddr.client, caddr.sender));
        }
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Channel is NULL(ctx=%d p=%d c=%d s=%d)"), 
          __FUNCTION__, spconnctx->id(), caddr.pipe, caddr.client, caddr.sender));
        sts = naio::status::SUCCESS;
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Channel not found (ctx=%d p=%d c=%d s=%d)"), 
        __FUNCTION__, spconnctx->id(), caddr.pipe, caddr.client, caddr.sender));
      sts = naio::status::SUCCESS;
    }

    return sts;
  }

  naio::StatusT 
  DataHandler::HandleInput(Transport::ChannelAddr const & caddr, size_t len, char const * data, 
    naio::ConnectionContextStrongPtr const & spconnctx, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(p=%d c=%d s=%d seq=%d l=%d)"), __FUNCTION__,
      caddr.pipe, caddr.client, caddr.sender, caddr.SeqNum(), len));

    naio::StatusT sts = naio::status::FAIL;
    TL::ConnectionSP spconn = connection(spconnctx);
    if (TL::IsValid(spconn))
    {
      TL::IChannelInternalSP spchnl = spconn->findChannel(caddr);
      if (TL::IsValid(spchnl))
      {
        if (0 == spchnl->lastRecvSeqNum())
        {
          spchnl->lastRecvSeqNum(caddr.SeqNum());
        }
        else
        {
          if (caddr.ConsistensyCheck(spchnl->lastRecvSeqNum()) < 0)
          {
            NI_ASSERT(spchnl->lastRecvSeqNum() + 1 == caddr.SeqNum(), 
              NI_STRFMT("WRONG RECV SEQUENCE(lastrecv=%d recv=%d c=%d t=%s s=%s)", 
              spchnl->lastRecvSeqNum(), caddr.SeqNum(), spchnl->taddr().client, 
              spchnl->taddr().target.c_str(), spchnl->taddr().source.c_str()));
          }
          else
          {
            spchnl->lastRecvSeqNum(caddr.SeqNum());
          }
        }

        if (0 == spchnl->enqueueRecv(len, data))
        {
          sts = naio::status::SUCCESS;
        }
        else
        {
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't put recv data in recv queue(ctx=%d p=%d c=%d s=%d)"), 
            __FUNCTION__, spconnctx->id(), caddr.pipe, caddr.client, caddr.sender));
        }
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Channel not found (ctx=%d p=%d c=%d s=%d)"), 
          __FUNCTION__, spconnctx->id(), caddr.pipe, caddr.client, caddr.sender));

        //  QFIX(NUM_TASK): на АП3 сразу после команды на закрытие канала с релея приходили данные для этого канала
        //                  пока непонятно почему, - просто обрабатываем эту ситуацию, чтобы не закрывать соединение к сервису
        sts = naio::status::SUCCESS;
      }
    }

    return sts;
  }

  void DataHandler::OnPacketHandlingCompleted(int rc, size_t len, char const * data, 
    naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
  }

  naio::StatusT 
  DataHandler::HandleOutput(Transport::ChannelAddr const & caddr, size_t len, char const * data, 
                            naio::ConnectionContextStrongPtr const & spconnctx,
                            Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    NI_ASSERT(caddr.pipe > Transport::EKnownPipeId::Invalid, "Pipe id is invalid");

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(p=%d c=%d s=%d l=%d)"), __FUNCTION__,
      caddr.pipe, caddr.client, caddr.sender, len));

    return tph_.HandleOutput(len, data, caddr, spconnctx, outmbf, poutmb);
  }

  naio::StatusT 
  DataHandler::HandleOutput(Transport::MessageBase* pMsg, Transport::ChannelAddr const & caddr, 
    naio::ConnectionContextStrongPtr const & spconn, 
    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    NI_ASSERT(caddr.pipe > Transport::EKnownPipeId::Invalid, "Pipe id is invalid");

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(p=%d c=%d s=%d msg=%d)"), __FUNCTION__,
      caddr.pipe, caddr.client, caddr.sender, pMsg->GetTypeId()));

    return tph_.HandleOutput(pMsg, caddr, spconn, outmbf, poutmb);
  }

  TL::ConnectionSP 
  DataHandler::connection(naio::ConnectionContextStrongPtr const & spconn) const
  {
    return reinterpret_cast<AsynchCompletionPointer<TL::Connection>*>(spconn->userContext())->sp_;
  }
}
