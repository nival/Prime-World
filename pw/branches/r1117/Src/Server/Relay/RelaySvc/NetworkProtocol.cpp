#pragma warning( disable : 4996)
#include "stdafx.h"
#include <IOTerabit/AsynchChannel.h>
#include "NetworkProtocol.h"

using namespace Terabit;

namespace Relay
{

NetworkProtocolHandler::NetworkProtocolHandler(INetworkBasedHandler* input_handler, char const * tagname)
  :input_handler_(input_handler)
{
  ACE_OS::strncpy(&tagname_[0], tagname, sizeof(tagname_)-1);
}

NetworkProtocolHandler::~NetworkProtocolHandler()
{
}

int NetworkProtocolHandler::HandleInput(Terabit::AsynchChannel *channel, const char *data, size_t length)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::%s(l=%d)"), __FUNCTION__, tagname(), length));

  if (length < HEADER_SIZE)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s::%s. Data size less than header size(ch=%d l=%d)"), 
      __FUNCTION__, tagname(), channel->get_id(), length));
    return 0;
  }

  unsigned short packet_size = *((unsigned short*)data);
  if (length - HEADER_SIZE < packet_size)
  {
    if (channel->get_read_size() == length)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s::%s. Packet size bigger than read buffer(ch=%d psize=%d l=%d readsize=%d)"), 
        __FUNCTION__, tagname(), channel->get_id(), packet_size, length, channel->get_read_size()));
      return -1;
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s::%s. Packet size bigger than incoming data size(ch=%d psize=%d l=%d readsize=%d)"), 
        __FUNCTION__, tagname(), channel->get_id(), packet_size, length, channel->get_read_size()));
      return 0;
    }
  }

  size_t consumed_bytes = 0;
  size_t remain_bytes = length - HEADER_SIZE;
  char const * pdata = data + HEADER_SIZE;

  do
  {
    consumed_bytes += HEADER_SIZE;
    int rc = input_handler_->HandleInput(channel, pdata, packet_size);
    if (rc <= 0)
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s::%s: handling is failed(ch=%d psize=%d readbytes=%d l=%d readsize=%d)"), 
        __FUNCTION__, tagname(), channel->get_id(), packet_size, rc, length, channel->get_read_size()));
      return -1;
    }

    if (rc != packet_size)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s::%s read bytes is NOT equeal to packet size(ch=%d psize=%d readbytes=%d l=%d readsize=%d)"), 
        __FUNCTION__, tagname(), channel->get_id(), packet_size, rc, length, channel->get_read_size()));
      return -1;
    }

    consumed_bytes += rc;
    remain_bytes -= rc;
    pdata += rc;

    if (remain_bytes >= HEADER_SIZE)
    {
      packet_size = *((unsigned short*)pdata);
      pdata += HEADER_SIZE;
      remain_bytes -= HEADER_SIZE;
    }
    else
      packet_size = MAX_PACKET_SIZE;
  }
  while(packet_size <= remain_bytes);

  return consumed_bytes;
}

int NetworkProtocolHandler::HandleOutput(Terabit::AsynchChannel *channel, ACE_Message_Block& mb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_ASSERT(mb.length() <= MAX_PACKET_SIZE);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::%s(l=%d)"), __FUNCTION__, tagname(), mb.length()));

  {
    NI_PROFILE_BLOCK("write block");
    //  write body size in header
    unsigned short bodylen = static_cast< unsigned short >(mb.length() - HEADER_SIZE);
    mb.wr_ptr(mb.base()); 
    mb.copy((char*)&bodylen, sizeof(bodylen));
    mb.wr_ptr(bodylen);
  }

  NI_PROFILE_BLOCK("start_write");
  return channel->start_write(mb);
}

int NetworkProtocolHandler::HandleOutput(Terabit::AsynchChannel *channel, ACE_Message_Block& mb,
                 unsigned int& qlen, unsigned int& qlen_in_bytes)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_ASSERT(mb.length() <= MAX_PACKET_SIZE);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s::%s(l=%d)"), __FUNCTION__, tagname(), mb.length()));

  NI_PROFILE_BLOCK("write body");
  //  write body size in header
  unsigned short bodylen = static_cast< unsigned short >(mb.length() - HEADER_SIZE);
  mb.wr_ptr(mb.base()); 
  mb.copy((char*)&bodylen, sizeof(bodylen));
  mb.wr_ptr(bodylen);

  NI_PROFILE_BLOCK("start_write");
  int rc = channel->start_write(mb, qlen, qlen_in_bytes);
  if (rc < 0)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. start_write is FAILED(sz=%d ch=%d)"),
    __FUNCTION__, mb.length(), channel->get_id()));
  }
  return rc;
}

ACE_Message_Block* NetworkProtocolHandler::AllocBuffer(Terabit::AsynchChannel *channel, unsigned int bodySize, unsigned long long tag)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  if (bodySize > MAX_PACKET_SIZE - HEADER_SIZE)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Try allocate packet with body bigger then allowed(sz=%d allowed=%d tag=%d)"),
      __FUNCTION__, bodySize, MAX_PACKET_SIZE - HEADER_SIZE, tag));

    return 0;
  }

  ACE_Message_Block* pmb = channel->alloc_msg(HEADER_SIZE + bodySize, tag);
  if (!pmb)
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(sz=%d tag=%d)"),
      __FUNCTION__, HEADER_SIZE + bodySize, tag));
    return 0;
  }

  pmb->wr_ptr(HEADER_SIZE);
  return pmb;
}

}
