#pragma once
#include <netlayer/NLNetworkHandler.h>
#include <naio/ConnectionContext.h>

namespace NetworkLayer
{
  namespace NL = NetworkLayer;

  class Connection;

  struct Msg
  {
    Msg()
      :pmb_(0)
    {
    }

    Msg(ACE_Message_Block* pmb)
      :pmb_(pmb)
    {
    }

    ACE_Message_Block* pmb_;
  };

  class ServerHandler : public NL::INetworkBasedHandler
  {
  public:
    ServerHandler();
    ~ServerHandler();

  public:
    ACE_Message_Block* AllocBuffer(Terabit::MessageBlockFactory & outmbf, unsigned int dataSize);

    NL::NetworkHandler& getNetworkHandler();
    naio::StatusT HandleInput(size_t length, const char *data, size_t & readBytes,
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleOutput(size_t size, char const * data, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);

  private:
    NL::NetworkHandler  network_handler_;
  };

  inline
  NetworkHandler& ServerHandler::getNetworkHandler()
  {
    return network_handler_;
  }
}
