#pragma once

#include <naio/Protocol.h>

namespace netlib
{
  class NetworkProtocol : public naio::Protocol
  {
  public:
    static const unsigned short  HEADER_SIZE = sizeof(unsigned short);
    static const unsigned short  MAX_PACKET_SIZE = 0xFFFF;
    static const unsigned short  MAX_DATA_SIZE = MAX_PACKET_SIZE - HEADER_SIZE;

  public:
    NetworkProtocol(Terabit::ProtocolFactory& factory, char const * tagname);
    ~NetworkProtocol();

  public:
    virtual int HandleInput(size_t length, const char *data, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual int HandleOutput(size_t length, const char *data, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
  };
}
