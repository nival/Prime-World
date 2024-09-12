#include "NetworkProtocol.h"

using namespace Terabit;

namespace netlib
{
  NetworkProtocol::NetworkProtocol(Terabit::ProtocolFactory& factory, char const * tagname)
    :naio::Protocol(factory, tagname)
  {
    ACE_OS::strncpy(&tagname_[0], tagname, sizeof(tagname_)-1);
  }

  NetworkProtocol::~NetworkProtocol()
  {
  }

  int NetworkProtocol::HandleInput(size_t length, const char *data, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    ACE_DEBUG((LM_TRACE, ACE_TEXT("(%t) %T %s::%s(l=%d)\n"), __FUNCTION__, tagname(), length));

    if (length < HEADER_SIZE)
      return 0;

    unsigned short packet_size = *((unsigned short*)data);
    if (length - HEADER_SIZE < packet_size)
      return 0;

    size_t consumed_bytes = 0;
    size_t remain_bytes = length - HEADER_SIZE;
    char const * pdata = data + HEADER_SIZE;

    do
    {
      consumed_bytes += HEADER_SIZE;

      //////////////////////////////////////////////////////////////////////////
      //  TODO: add real handling here
      //////////////////////////////////////////////////////////////////////////
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t)%T %s::%s Handling (packet size=%d)\n"), 
        __FUNCTION__, tagname(), packet_size));
      int rc = packet_size;

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

  int NetworkProtocol::HandleOutput(size_t length, const char *data, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    ACE_DEBUG((LM_TRACE, ACE_TEXT("(%t) %T %s::%s(l=%d)\n"), __FUNCTION__, tagname(), length));

    if (length > MAX_DATA_SIZE)
      return naio::status::FAIL;

    ACE_Message_Block* pout = outmbf.alloc_msg(HEADER_SIZE + length);
    if (!pout)
      return naio::status::FAIL;

    unsigned short bodylen = unsigned short(length);
    pout->copy((char*)&length, sizeof(HEADER_SIZE));
    pout->copy(data, length);

    return length;
  }
}
