#pragma warning( disable : 4996)
#include "stdafx.h"
#include <IOTerabit/AsynchChannel.h>
#include "TransportMessagesHeaders.h"
#include "RelayChannelManager.h"
#include "TransportProtocol.h"
#include "System/AddressOf.h"

using namespace Terabit;
using namespace Transport;

namespace Relay
{

#pragma warning( push )
#pragma warning( disable : 4355)

TransportProtocolHandler::TransportProtocolHandler(ITransportBasedHandler* input_handler, bool packaddr, char const * tagname)
  :input_handler_(input_handler),
  network_handler_(this, tagname)
#pragma warning( pop )
{
  if (!input_handler_)
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s::%s. Output mode"), __FUNCTION__, tagname));
}

TransportProtocolHandler::~TransportProtocolHandler()
{
}

int TransportProtocolHandler::HandleInput(Terabit::AsynchChannel *channel, const char *data, size_t length)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  FixedMemoryStream strm(const_cast<char*>(data), length);
  RelayChannelManager* rcm = (RelayChannelManager*)channel->get_manager();
  Transport::MessageFactory* msgFactory = rcm->messageFactory();

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::%s(l=%d)"), __FUNCTION__, tagname(), length));

  int rc = 0;
  while(0 == rc && strm.GetPosition() < (int)length)
  {
    NI_PROFILE_BLOCK("while");

    rc = -1;

    Transport::ChannelAddr  caddr;
    Transport::ReadAddress(nival::getaddressof( strm ), caddr);
    int msgtype = -1;

    if (EKnownPipeId::NetLogic == caddr.pipe)
    {
      if (ReadMessageType(nival::getaddressof( strm ), msgtype))
      {
        MessageBase* pMsg = 0;
        Transport::UnpackResult::Enum unpackrc = Transport::UnpackMessage(msgtype, msgFactory, nival::getaddressof( strm ), MAX_MSG_DATA_SIZE, pMsg);
        if(Transport::UnpackResult::OK == unpackrc && pMsg)
        {
          rc = HandleNetLogicMessage( pMsg, channel );
          msgFactory->Destroy(pMsg);
        }
        else
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s::%s. Can't unpack message(rc=%d ch=%d p=%d c=%d s=%d m=%d)"), 
            __FUNCTION__, tagname(), unpackrc, channel->get_id(), caddr.pipe, caddr.client, caddr.sender, msgtype));
      }
      else
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s::%s. Can't read message type(ch=%d p=%d c=%d s=%d)"), 
          __FUNCTION__, tagname(), channel->get_id(), caddr.pipe, caddr.client, caddr.sender, msgtype));
    }
    else
    if (EKnownPipeId::FrontEnd == caddr.pipe)
    {
      if (ReadMessageType(nival::getaddressof( strm ), msgtype))
      {
        MessageBase* pMsg = 0;
        Transport::UnpackResult::Enum unpackrc = Transport::UnpackMessage(msgtype, msgFactory, nival::getaddressof( strm ), MAX_MSG_DATA_SIZE, pMsg);
        if(Transport::UnpackResult::OK == unpackrc && pMsg)
        {
          Transport::MessageHeader header(caddr, msgtype);
          rc = input_handler_->HandleInput(channel,header, pMsg);
          msgFactory->Destroy(pMsg);
        }
        else
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s::%s. Can't unpack message(rc=%d ch=%d p=%d c=%d s=%d m=%d)"), 
            __FUNCTION__, tagname(), unpackrc, channel->get_id(), caddr.pipe, caddr.client, caddr.sender, msgtype));
      }
      else
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s::%s. Can't read message type(ch=%d p=%d c=%d s=%d)"), 
          __FUNCTION__, tagname(), channel->get_id(), caddr.pipe, caddr.client, caddr.sender, msgtype));
    }
    else
    {
      if (Transport::autoAssignClientId == caddr.client)
      {
        rc = input_handler_->HandleMulticastInput(channel, caddr, data + strm.GetPosition(), length - strm.GetPosition());
      }
      else
      {
        rc = input_handler_->HandleInput(channel, caddr, data + strm.GetPosition(), length - strm.GetPosition());
      }
      if (rc > 0)
      {
        strm.Seek(rc, SEEKORIGIN_OFFSET);
        rc = 0;
      }
    }
  }

  if (rc < 0)
    return rc;

  return strm.GetPosition();
}

int TransportProtocolHandler::HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  return input_handler_->HandleOpenChannelRequest(pMsg, channel);
}

int TransportProtocolHandler::HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  return input_handler_->HandleOpenChannelResponse(pMsg, channel);
}

int TransportProtocolHandler::HandleCloseChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  return input_handler_->HandleCloseChannel(pMsg, channel);
}

int TransportProtocolHandler::HandleCloseMulticastChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  return input_handler_->HandleCloseMulticastChannel(pMsg, channel);
}

int TransportProtocolHandler::HandleNetLogicMessage(MessageBase *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  if ( pMsg->GetTypeId() == ENetLogicMessage::OpenChannelReq )
  {
    Transport::OpenChannelRequest* pNewConnectionMsg = static_cast<Transport::OpenChannelRequest*>( pMsg );
    return HandleOpenChannelRequest(pNewConnectionMsg, channel);
  } 
  else if ( pMsg->GetTypeId() == ENetLogicMessage::CloseChannel )
  {
    Transport::CloseChannelMessage* pCloseConnectionMsg = static_cast<Transport::CloseChannelMessage*>( pMsg );
    if (pCloseConnectionMsg->clientAddress.client != Transport::autoAssignClientId)
      return HandleCloseChannel(pCloseConnectionMsg, channel);
    else
      return HandleCloseMulticastChannel(pCloseConnectionMsg, channel);
  }
  else
  if ( pMsg->GetTypeId() == ENetLogicMessage::OpenChannelResp)
  {
    Transport::OpenChannelResponse* pNewConnectionResMsg = static_cast<Transport::OpenChannelResponse*>( pMsg );
    return HandleOpenChannelResponse(pNewConnectionResMsg, channel);
  }
  else
  if ( pMsg->GetTypeId() == ENetLogicMessage::PingMessage)
  {
    Transport::PingMessage* pPingMsg = static_cast<Transport::PingMessage*>(pMsg);
    return HandlePingMessage(pPingMsg, channel);
  }
  else
  if ( pMsg->GetTypeId() == ENetLogicMessage::ThroughPingMessage)
  {
    Transport::ThroughPingMessage* pPingMsg = static_cast<Transport::ThroughPingMessage*>(pMsg);
    return HandlePingMessage(pPingMsg, channel);
  }
  else
  if (pMsg->GetTypeId() == ENetLogicMessage::AddRecipientReq)
  {
    Transport::AddRecipientRequest* pAddRecipient = static_cast<Transport::AddRecipientRequest*>(pMsg);
    return HandleAddRecipientRequest(pAddRecipient, channel);
  }
  else
  if (pMsg->GetTypeId() == ENetLogicMessage::RemoveRecipient)
  {
    Transport::RemoveRecipientMessage* pRemoveRecipient = static_cast<Transport::RemoveRecipientMessage*>(pMsg);
    return HandleRemoveRecipient(pRemoveRecipient, channel);
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s::%s(cmd=%s)"), __FUNCTION__, tagname(), "Unknown"));
    return -1;
  }
}

int TransportProtocolHandler::HandlePingMessage(Transport::PingMessage *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  return input_handler_->HandlePingMessage(pMsg, channel);
}

int TransportProtocolHandler::HandlePingMessage(Transport::ThroughPingMessage*pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_FUNCTION;
  return input_handler_->HandlePingMessage(pMsg, channel);
}

int TransportProtocolHandler::HandleAddRecipientRequest(Transport::AddRecipientRequest* pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_FUNCTION;
  return input_handler_->HandleAddRecipientRequest(pMsg, channel);
}

int TransportProtocolHandler::HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, Terabit::AsynchChannel *channel)
{
  NI_PROFILE_FUNCTION;
  return input_handler_->HandleRemoveRecipient(pMsg, channel);
}

int TransportProtocolHandler::HandleOutput(Transport::MessageBase* pMsg, Transport::ChannelAddr const & caddr, Terabit::AsynchChannel* channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::%s(p=%d c=%d s=%d m=%d)"), __FUNCTION__, tagname(),
    caddr.pipe, caddr.client, caddr.sender, pMsg->GetTypeId()));

  ACE_Message_Block* pmb = network_handler_.AllocBuffer(channel, 512); //  TODO: calculate msg size
  if (!pmb)
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(c=%d p=%d)"),
      __FUNCTION__, caddr.client, caddr.pipe));
    return 0;
  }

  FixedMemoryStream strm(pmb->wr_ptr(), pmb->space());
  Transport::PackNetMessage(caddr, pMsg, nival::getaddressof( strm ));
  pmb->wr_ptr(strm.GetPosition());

  return network_handler_.HandleOutput(channel, *pmb);
}

int TransportProtocolHandler::HandleOutput(char const * data, size_t size, Transport::ChannelAddr const & caddr, Terabit::AsynchChannel* channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::%s(p=%d c=%d s=%d l=%d)"), __FUNCTION__, tagname(),
    caddr.pipe, caddr.client, caddr.sender, size));

  ACE_Message_Block* pmb = network_handler_.AllocBuffer(channel, Transport::GetAddressSize(caddr) + size);
  if (!pmb)
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(sz=%d c=%d p=%d)"),
      __FUNCTION__, size, caddr.client, caddr.pipe));
    return -1;
  }

  {
    NI_PROFILE_BLOCK("write block");
    FixedMemoryStream strm(pmb->wr_ptr(), pmb->space());
    Transport::WriteAddress(nival::getaddressof( strm ), caddr);
    pmb->wr_ptr(strm.GetPosition());
    if (pmb->copy(data, size) < 0)
      return -1;
  }

  return network_handler_.HandleOutput(channel, *pmb);
}

int TransportProtocolHandler::HandleOutput(char const * data, size_t size, 
                                           Transport::ChannelAddr const & caddr, Terabit::AsynchChannel* channel,
                                           unsigned int& qlen, unsigned int& qlen_in_bytes)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::%s(p=%d c=%d s=%d l=%d)"), __FUNCTION__, tagname(),
    caddr.pipe, caddr.client, caddr.sender, size));

  ACE_Message_Block* pmb = network_handler_.AllocBuffer(channel, Transport::GetAddressSize(caddr) + size, caddr.client);
  if (!pmb)
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(sz=%d c=%d p=%d ch=%d)"),
      __FUNCTION__, size, caddr.client, caddr.pipe, channel->get_id()));
    return -1;
  }

  FixedMemoryStream strm(pmb->wr_ptr(), pmb->space());
  Transport::WriteAddress(nival::getaddressof( strm ), caddr);
  pmb->wr_ptr(strm.GetPosition());
  if (pmb->copy(data, size) < 0)
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Copy data to internal buffer is FAILED(sz=%d c=%d p=%d ch=%d)"),
      __FUNCTION__, size, caddr.client, caddr.pipe, channel->get_id()));
    return -1;
  }

  return network_handler_.HandleOutput(channel, *pmb, qlen, qlen_in_bytes);
}

int TransportProtocolHandler::HandleOutput(TransportMsg const * sctm, unsigned int count, Terabit::AsynchChannel* channel)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::%s(count=%d)"), __FUNCTION__, tagname(), count));

  int rc = -1;
  unsigned int i = 0;
  do
  {
    NI_PROFILE_BLOCK("message block");

    TransportMsg const & msg = sctm[i];
    rc = HandleOutput(msg.pmb_->base(), msg.pmb_->length(), msg.caddr_, channel);
    ++i;
  }
  while(0 == rc && i < count);

  if (rc < 0)
  {
    --i;
    ChannelAddr const & caddr = sctm[i].caddr_;
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s::%s Error(msgidx=%d p=%d c=%d s=%d ch=%d)"), 
      __FUNCTION__, tagname(), i, caddr.pipe, caddr.client, caddr.sender, channel->get_id()));
  }

  return rc;

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
