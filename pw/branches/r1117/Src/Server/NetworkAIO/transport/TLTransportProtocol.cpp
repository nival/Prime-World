#include "transport/stdafx.h"
#include "transport/TLTransportProtocol.h"
#include <IOTerabit/AsynchChannel.h>
#include <Network/TransportMessages.h>
#include <System/AddressOf.h>

namespace TransportLayer
{

#pragma warning( push )
#pragma warning( disable : 4355)
TransportProtocolHandler::TransportProtocolHandler(ITransportBasedHandler* input_handler, 
                                                   Transport::MessageFactory* pMsgFactory, 
                                                   bool packaddr)
  :input_handler_(input_handler),
  network_handler_(this),
  msgFactory_(pMsgFactory)
#pragma warning( pop )
{
  ACE_ASSERT(input_handler_);
}

TransportProtocolHandler::~TransportProtocolHandler()
{
}

ACE_Message_Block* 
TransportProtocolHandler::AllocBuffer(Terabit::MessageBlockFactory & outmbf, 
                                      Transport::ChannelAddr const & caddr, unsigned int dataSize)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  return network_handler_.AllocBuffer(outmbf, Transport::GetAddressSize(caddr) + dataSize);
}

naio::StatusT TransportProtocolHandler::HandleInput(size_t length, const char *data, size_t& readBytes, 
                naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  FixedMemoryStream strm(const_cast<char*>(data), length);
  Transport::MessageFactory* msgFactory = msgFactory_;

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(l=%d)"), __FUNCTION__, length));

  naio::StatusT rc = naio::status::SUCCESS;
  while(0 == rc && strm.GetPosition() < (int)length)
  {
    NI_PROFILE_BLOCK("while");

    rc = naio::status::FAIL;

    Transport::ChannelAddr  caddr;
    Transport::ReadAddress(nival::getaddressof( strm ), caddr);
    int msgtype = -1;

    if (Transport::EKnownPipeId::NetLogic == caddr.pipe)
    {
      if (Transport::ReadMessageType(nival::getaddressof( strm ), msgtype))
      {
        Transport::MessageBase* pMsg = 0;
        Transport::UnpackResult::Enum unpackrc = Transport::UnpackMessage(msgtype, msgFactory, nival::getaddressof( strm ), MAX_MSG_DATA_SIZE, pMsg);
        if(Transport::UnpackResult::OK == unpackrc && pMsg)
        {
          rc = HandleNetLogicMessage( pMsg, spconn, outmbf, poutmb );
          msgFactory->Destroy(pMsg);
        }
        else
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't unpack message(rc=%d ch=%d p=%d c=%d s=%d m=%d)"), 
            __FUNCTION__, unpackrc, spconn->id(), caddr.pipe, caddr.client, caddr.sender, msgtype));
      }
      else
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't read message type(ch=%d p=%d c=%d s=%d)"), 
          __FUNCTION__, spconn->id(), caddr.pipe, caddr.client, caddr.sender));
    }
    else
    {
      rc = input_handler_->HandleInput(caddr, length - strm.GetPosition(), data + strm.GetPosition(), 
                                      spconn, outmbf, poutmb);
      if (naio::status::SUCCESS == rc)
        strm.Seek(length - strm.GetPosition(), SEEKORIGIN_OFFSET);
    }
  }

  if (naio::status::SUCCESS == rc)
  {
    readBytes = strm.GetPosition();
  }

  return rc;
}

naio::StatusT 
TransportProtocolHandler::HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, naio::ConnectionContextStrongPtr const & spconn, 
                                              Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  return input_handler_->HandleOpenChannelRequest(pMsg, spconn, outmbf, poutmb);
}

naio::StatusT 
TransportProtocolHandler::HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, naio::ConnectionContextStrongPtr const & spconnctx, 
                                                    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  return input_handler_->HandleOpenChannelResponse(pMsg, spconnctx, outmbf, poutmb);
}

naio::StatusT 
TransportProtocolHandler::HandleCloseChannel(Transport::CloseChannelMessage *pMsg, naio::ConnectionContextStrongPtr const & spconn)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  return input_handler_->HandleCloseChannel(pMsg, spconn);
}

naio::StatusT 
TransportProtocolHandler::HandlePingMessage(Transport::PingMessage *pMsg, naio::ConnectionContextStrongPtr const & spconn, 
                                            Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  NI_PROFILE_FUNCTION;
  return input_handler_->HandlePingMessage(pMsg, spconn, outmbf, poutmb);
}

naio::StatusT 
TransportProtocolHandler::HandlePingMessage(Transport::ThroughPingMessage *pMsg, naio::ConnectionContextStrongPtr const & spconn, 
                                Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  NI_PROFILE_FUNCTION;
  return input_handler_->HandlePingMessage(pMsg, spconn, outmbf, poutmb);
}

naio::StatusT 
TransportProtocolHandler::HandleAddRecipientResponse(Transport::AddRecipientResponse *pMsg, naio::ConnectionContextStrongPtr const & spconn)
{
  NI_PROFILE_FUNCTION;
  return input_handler_->HandleAddRecipientResponse(pMsg, spconn);
}

naio::StatusT 
TransportProtocolHandler::HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, naio::ConnectionContextStrongPtr const & spconn)
{
  NI_PROFILE_FUNCTION;
  return input_handler_->HandleRemoveRecipient(pMsg, spconn);
}

naio::StatusT 
TransportProtocolHandler::HandleNetLogicMessage(Transport::MessageBase *pMsg, naio::ConnectionContextStrongPtr const & spconn, 
                                                Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  if ( pMsg->GetTypeId() == Transport::ENetLogicMessage::OpenChannelReq )
  {
    Transport::OpenChannelRequest* pNewConnectionMsg = static_cast<Transport::OpenChannelRequest*>( pMsg );
    return HandleOpenChannelRequest(pNewConnectionMsg, spconn, outmbf, poutmb);
  } 
  else if ( pMsg->GetTypeId() == Transport::ENetLogicMessage::CloseChannel )
  {
    Transport::CloseChannelMessage* pCloseConnectionMsg = static_cast<Transport::CloseChannelMessage*>( pMsg );
    return HandleCloseChannel(pCloseConnectionMsg, spconn);
  }
  else
  if ( pMsg->GetTypeId() == Transport::ENetLogicMessage::OpenChannelResp)
  {
    Transport::OpenChannelResponse* pNewConnectionResMsg = static_cast<Transport::OpenChannelResponse*>( pMsg );
    return HandleOpenChannelResponse(pNewConnectionResMsg, spconn, outmbf, poutmb);
  }
  else
  if ( pMsg->GetTypeId() == Transport::ENetLogicMessage::PingMessage)
  {
    Transport::PingMessage* pPingMsg = static_cast<Transport::PingMessage*>(pMsg);
    return HandlePingMessage(pPingMsg, spconn, outmbf, poutmb);
  }
  else
  if ( pMsg->GetTypeId() == Transport::ENetLogicMessage::ThroughPingMessage)
  {
    Transport::ThroughPingMessage* pPingMsg = static_cast<Transport::ThroughPingMessage*>(pMsg);
    return HandlePingMessage(pPingMsg, spconn, outmbf, poutmb);
  }
  else
  if ( pMsg->GetTypeId() == Transport::ENetLogicMessage::AddRecipientResp)
  {
    Transport::AddRecipientResponse* pAddRecipientResp = static_cast<Transport::AddRecipientResponse*>(pMsg);
    return HandleAddRecipientResponse(pAddRecipientResp, spconn);
  }
  else
  if ( pMsg->GetTypeId() == Transport::ENetLogicMessage::RemoveRecipient)
  {
    Transport::RemoveRecipientMessage* pRemoveRecipient = static_cast<Transport::RemoveRecipientMessage*>(pMsg);
    return HandleRemoveRecipient(pRemoveRecipient, spconn);
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s(cmdid=%d)"), __FUNCTION__, (int)pMsg->GetTypeId()));
    return naio::status::FAIL;
  }
}

naio::StatusT 
TransportProtocolHandler::HandleOutput(Transport::MessageBase* pMsg, Transport::ChannelAddr const & caddr, 
                                       naio::ConnectionContextStrongPtr const & spconn, 
                                       Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::msg(p=%d c=%d s=%d m=%d)"), __FUNCTION__,
    caddr.pipe, caddr.client, caddr.sender, pMsg->GetTypeId()));

  NI_ASSERT(caddr.pipe > Transport::EKnownPipeId::Invalid, "Pipe id is invalid");

  unsigned int msgsz = GetFinalOutputDataSize(caddr, pMsg);
  ACE_Message_Block* pmb = network_handler_.AllocBuffer(outmbf, msgsz);
  if (!pmb)
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(c=%d p=%d)"),
      __FUNCTION__, caddr.client, caddr.pipe));
    return naio::status::NO_MEMORY;
  }

  {
    NI_PROFILE_BLOCK("PackNetMessage");
    FixedMemoryStream strm(pmb->wr_ptr(), pmb->space());
    Transport::PackNetMessage(caddr, pMsg, nival::getaddressof( strm ));
    pmb->wr_ptr(strm.GetPosition());
    poutmb = pmb;
  }

  return network_handler_.HandleOutput(*pmb, true, spconn, outmbf, poutmb);
}

naio::StatusT 
TransportProtocolHandler::HandleOutput(size_t size, char const * data, Transport::ChannelAddr const & caddr, 
                                       naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::data(p=%d c=%d s=%d l=%d)"), __FUNCTION__,
    caddr.pipe, caddr.client, caddr.sender, size));

  NI_ASSERT(caddr.pipe > Transport::EKnownPipeId::Invalid, "Pipe id is invalid");

  ACE_Message_Block* pmb = AllocBuffer(outmbf, caddr, size);
  if (!pmb)
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(sz=%d c=%d p=%d)"),
      __FUNCTION__, size, caddr.client, caddr.pipe));
    return naio::status::NO_MEMORY;
  }

  {
    NI_PROFILE_BLOCK("PackData");
    FixedMemoryStream strm(pmb->wr_ptr(), pmb->space());
    Transport::WriteAddress(nival::getaddressof( strm ), caddr);
    pmb->wr_ptr(strm.GetPosition());
    if (pmb->copy(data, size) < 0)
      return naio::status::FAIL;
  }

  poutmb = pmb;
  return network_handler_.HandleOutput(*pmb, true, spconn, outmbf, poutmb);
}

naio::StatusT 
TransportProtocolHandler::HandleOutput(TransportMsg const * sctm, unsigned int& count, 
                                       naio::ConnectionContextStrongPtr const & spconn, 
                                       Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(count=%d)"), __FUNCTION__, count));

  naio::StatusT sts = naio::status::FAIL;
  unsigned int i = 0;
  ACE_Message_Block* plastmb = 0;
  do
  {
    NI_PROFILE_BLOCK("do while");

    TransportMsg const & msg = sctm[i];
    ACE_Message_Block* pmb = 0;
    sts = HandleOutput(msg.pmb_->length(), msg.pmb_->base(), msg.caddr_, spconn, outmbf, pmb);
    if (!poutmb)
    {
      poutmb = pmb;
      plastmb = poutmb;
    }
    else
    {
      plastmb->cont(pmb);
      plastmb = pmb;
    }

    ++i;
  }
  while(naio::status::SUCCESS == sts && i < count);

  if (sts != naio::status::SUCCESS)
  {
    --i;
    Transport::ChannelAddr const & caddr = sctm[i].caddr_;
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s Error(msgidx=%d p=%d c=%d s=%d ch=%d)"), 
      __FUNCTION__, i, caddr.pipe, caddr.client, caddr.sender, spconn->connid()));
  }

  count = i;

  return sts;

/*
  unsigned int msgOffset = 0;
  do
  {
    //  вычисляем кол-во сообщений помещающихся в сетевой пакет
    size_t total_mb_len = 0;
    unsigned int msgCount = msgOffset;
    while (msgCount < count && total_mb_len <= NetworkProtocolHandler::MAX_DATA_SIZE)
    {
      total_mb_len += sctm[msgCount].pmb_->length();
      ++msgCount;
    }
    if (total_mb_len > NetworkProtocolHandler::MAX_DATA_SIZE)
    {
      total_mb_len -= sctm[msgCount].pmb_->length();
      --msgCount;
    }

    //  вычисляем размер и выделяем память под body
    unsigned int bodySize = Transport::GetAddressSize(sctm[0].caddr_, packaddr_)*msgCount + total_mb_len;
    ACE_Message_Block* pmb = network_handler_.AllocBuffer(channel, bodySize);

    //  сериализуем сообщения в body
    unsigned int j = msgOffset;
    while (j < msgCount)
    {
      TransportMsg const & msg = sctm[j];

      //  write msg address
      FixedMemoryStream strm(pmb->wr_ptr(), pmb->space());
      Transport::WriteAddress(&strm, msg.caddr_, packaddr_);
      pmb->wr_ptr(strm.GetPosition());
      //  write msg body
      pmb->copy(msg.pmb_->base(), msg.pmb_->length());

      ++j;
    }

    rc = network_handler_.HandleOutput(channel, *pmb);

    msgOffset += msgCount;
  }
  while (0 == rc && msgOffset < count);
*/
}

}
