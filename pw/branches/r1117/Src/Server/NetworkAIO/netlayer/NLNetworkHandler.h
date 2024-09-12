#pragma once
#include <naio/Types.h>

class ACE_Message_Block;

namespace Terabit
{
  class MessageBlockFactory;
}

namespace NetworkLayer
{
  namespace NL = NetworkLayer;

  class INetworkBasedHandler
  {
  public:
    virtual naio::StatusT HandleInput(size_t length, const char *data, size_t& readBytes, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
  };

  class NetworkHandler
  {
  public:
    static const unsigned short  HEADER_SIZE = sizeof(unsigned short);
    static const unsigned short  MAX_PACKET_SIZE = 0xFFFF;
    static const unsigned short  MAX_DATA_SIZE = MAX_PACKET_SIZE - HEADER_SIZE;

  public:
    NetworkHandler(INetworkBasedHandler* input_handler);
    ~NetworkHandler();

  public:
    ACE_Message_Block* AllocBuffer(Terabit::MessageBlockFactory& outmbf, unsigned int bodySize);
    unsigned int GetFinalOutputDataSize(unsigned int bodySize);

    naio::StatusT HandleInput(size_t length, const char *data, size_t& readBytes, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleOutput(ACE_Message_Block& mb, bool preallocated, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);

  private:
    void writeBodyLength(ACE_Message_Block & mb);

  private:
    INetworkBasedHandler* input_handler_;
  };

  inline
  unsigned int NetworkHandler::GetFinalOutputDataSize(unsigned int bodySize)
  {
    return HEADER_SIZE + bodySize;
  }
}
