#pragma once
#include "transport/TLTransportProtocol.h"
#include "transport/TLTypes.h"
#include <Network/TransportUtils.h>
#include <Network/TransportChannelType.h>

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelFactory;

  class DataHandler : public ITransportBasedHandler
  {
  public:
    DataHandler(Transport::MessageFactory* pMsgFactory, TL::ChannelFactory* chnlFactory, bool packaddr);
    ~DataHandler();

  public:
    virtual naio::StatusT HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual naio::StatusT HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, 
      Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual naio::StatusT HandleCloseChannel(Transport::CloseChannelMessage *pMsg, naio::ConnectionContextStrongPtr const & spconn);
    virtual naio::StatusT HandlePingMessage(Transport::PingMessage *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual naio::StatusT HandlePingMessage(Transport::ThroughPingMessage *pMsg, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual naio::StatusT HandleAddRecipientResponse(Transport::AddRecipientResponse *pMsg, naio::ConnectionContextStrongPtr const & spconn);
    virtual naio::StatusT HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, naio::ConnectionContextStrongPtr const & spconn);
    virtual naio::StatusT HandleInput(Transport::ChannelAddr const & caddr, size_t len, char const * data, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual void OnPacketHandlingCompleted(int rc, size_t len, char const * data, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);

    naio::StatusT HandleOutput(Transport::ChannelAddr const & caddr, size_t len, char const * data, naio::ConnectionContextStrongPtr const & spconn, \
      Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    naio::StatusT HandleOutput(Transport::MessageBase* pMsg, Transport::ChannelAddr const & caddr, 
      naio::ConnectionContextStrongPtr const & spconn, 
      Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);

    naio::StatusT OpenChannelResponseOutput(Transport::EChannelType::Enum _channeltype, bool result, Transport::Address const & caddr, 
      Transport::TPipeId const & pipeid, Transport::ChannelAddr raddr,
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);

    unsigned int GetFinalOutputDataSize(Transport::ChannelAddr const & caddr, unsigned int datasize);
    unsigned int GetFinalOutputDataSize(Transport::ChannelAddr const & caddr, Transport::MessageBase* msg);

  public:
    TL::TransportProtocolHandler& getTransportHandler();
    NetworkLayer::NetworkHandler& getNetworkHandler();

  private:
    TL::ConnectionSP connection(naio::ConnectionContextStrongPtr const & spconn) const;

  private:
    TL::TransportProtocolHandler tph_;
    TL::ChannelFactory* chnlFactory_;
  };

  inline
  TL::TransportProtocolHandler& DataHandler::getTransportHandler()
  {
    return tph_;
  }

  inline
  NetworkLayer::NetworkHandler& DataHandler::getNetworkHandler()
  {
    return tph_.getNetworkHandler();
  }

  inline
  unsigned int DataHandler::GetFinalOutputDataSize(Transport::ChannelAddr const & caddr, unsigned int datasize)
  {
    return tph_.GetFinalOutputDataSize(caddr, datasize);
  }

  inline
  unsigned int DataHandler::GetFinalOutputDataSize(Transport::ChannelAddr const & caddr, Transport::MessageBase* msg)
  {
    return tph_.GetFinalOutputDataSize(caddr, msg);
  }
}
