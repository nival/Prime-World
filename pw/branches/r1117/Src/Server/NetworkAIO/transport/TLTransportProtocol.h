#pragma once
#include <netlayer/NLNetworkHandler.h>
#include <Network/TransportUtils.h>
#include <naio/ConnectionContext.h>

namespace Transport
{
  struct MessageBase;
  struct MessageHeader;
  struct OpenChannelRequest;
  struct OpenChannelResponse;
  struct CloseChannelMessage;
  struct PingMessage;
  struct ThroughPingMessage;
  struct AddRecipientResponse;
  struct RemoveRecipientMessage;
}

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class Connection;

  struct TransportMsg
  {
    TransportMsg()
      :pmb_(0)
    {
    }

    TransportMsg(Transport::ChannelAddr const & caddr, ACE_Message_Block* pmb)
      :caddr_(caddr),
      pmb_(pmb)
    {
    }

    Transport::ChannelAddr caddr_;
    ACE_Message_Block* pmb_;
  };

  class ITransportBasedHandler
  {
  public:
    virtual naio::StatusT HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual naio::StatusT HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, 
      Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual naio::StatusT HandleCloseChannel(Transport::CloseChannelMessage *pMsg, naio::ConnectionContextStrongPtr const & spconn) = 0;
    virtual naio::StatusT HandlePingMessage(Transport::PingMessage *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual naio::StatusT HandlePingMessage(Transport::ThroughPingMessage *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual naio::StatusT HandleAddRecipientResponse(Transport::AddRecipientResponse *pMsg, naio::ConnectionContextStrongPtr const & spconn) = 0;
    virtual naio::StatusT HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, naio::ConnectionContextStrongPtr const & spconn) = 0;
    //virtual naio::StatusT HandleInput(Transport::MessageHeader const & header, Transport::MessageBase *pMsg,
    //  naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual naio::StatusT HandleInput(Transport::ChannelAddr const & caddr, size_t len, char const * data, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual void OnPacketHandlingCompleted(int rc, size_t len, char const * data, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
  };

  class TransportProtocolHandler : public NetworkLayer::INetworkBasedHandler
  {
  public:
    static const unsigned short  MSG_TYPE_SIZE = sizeof(int);
    static const unsigned short  MAX_MSG_DATA_SIZE = NetworkLayer::NetworkHandler::MAX_DATA_SIZE - sizeof(Transport::ChannelAddr) - MSG_TYPE_SIZE;

  public:
    TransportProtocolHandler(ITransportBasedHandler* input_handler, Transport::MessageFactory* pMsgFactory, 
      bool packaddr);
    ~TransportProtocolHandler();

  public:
    ACE_Message_Block* AllocBuffer(Terabit::MessageBlockFactory& outmbf, 
      Transport::ChannelAddr const & caddr, unsigned int dataSize);
    unsigned int GetFinalOutputDataSize(Transport::ChannelAddr const & caddr, unsigned int bodySize);
    unsigned int GetFinalOutputDataSize(Transport::ChannelAddr const & caddr, Transport::MessageBase* msg);

    NetworkLayer::NetworkHandler& getNetworkHandler();
    naio::StatusT HandleInput(size_t length, const char *data, size_t & readBytes,
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleOutput(Transport::MessageBase* pMsg, Transport::ChannelAddr const & addr, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleOutput(size_t size, char const * data, Transport::ChannelAddr const & addr, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleOutput(TransportMsg const * sctm, unsigned int& count, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);

    Transport::MessageFactory* messageFactory() const;

  private:
    //  net logic
    naio::StatusT HandleNetLogicMessage(Transport::MessageBase *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleCloseChannel(Transport::CloseChannelMessage *pMsg, naio::ConnectionContextStrongPtr const & spconn);
    naio::StatusT HandlePingMessage(Transport::PingMessage *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandlePingMessage(Transport::ThroughPingMessage *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleAddRecipientResponse(Transport::AddRecipientResponse *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn);
    naio::StatusT HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn);

    TL::Connection* connection(naio::ConnectionContextStrongPtr const & spconn) const
    {
      return reinterpret_cast<TL::Connection*>(spconn->userContext());
    }

  private:
    ITransportBasedHandler* input_handler_;
    NetworkLayer::NetworkHandler   network_handler_;
    Transport::MessageFactory* msgFactory_;
  };

  inline
  NetworkLayer::NetworkHandler& TransportProtocolHandler::getNetworkHandler()
  {
    return network_handler_;
  }

  inline
  Transport::MessageFactory* TransportProtocolHandler::messageFactory() const
  {
    return msgFactory_;
  }

  inline
  unsigned int TransportProtocolHandler::GetFinalOutputDataSize(Transport::ChannelAddr const & caddr, unsigned int bodySize)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    return network_handler_.GetFinalOutputDataSize(Transport::GetAddressSize(caddr) + bodySize);
  }

  inline
  unsigned int TransportProtocolHandler::GetFinalOutputDataSize(Transport::ChannelAddr const & caddr, Transport::MessageBase* msg)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    unsigned int msgsz = Transport::GetMessageSize(msg);
    return GetFinalOutputDataSize(caddr, msgsz);
  }
}
