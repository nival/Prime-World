#pragma once

#include "NetworkProtocol.h"

namespace Transport
{
  struct MessageBase;
  struct MessageHeader;
  struct OpenChannelRequest;
  struct OpenChannelResponse;
  struct CloseChannelMessage;
  struct PingMessage;
  struct ThroughPingMessage;
  struct ChannelAddr;
  struct AddRecipientRequest;
  struct AddRecipientResponse;
  struct RemoveRecipientMessage;
}

namespace Relay
{

struct TransportMsg
{
  TransportMsg()
    :pmb_(0)
  {
  }

  TransportMsg(Transport::ChannelAddr const & caddr, ACE_Message_Block* pmb, unsigned long seqNum)
    :caddr_(caddr),
    pmb_(pmb),
    seqNum_(seqNum)
  {
  }

  Transport::ChannelAddr caddr_;
  ACE_Message_Block* pmb_;
  unsigned long seqNum_;
};


class ITransportBasedHandler
{
public:
  virtual int HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, Terabit::AsynchChannel *channel) = 0;
  virtual int HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, Terabit::AsynchChannel *channel) = 0;
  virtual int HandleCloseChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel) = 0;
  virtual int HandleCloseMulticastChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel) = 0;
  virtual int HandlePingMessage(Transport::PingMessage *pMsg, Terabit::AsynchChannel *channel) = 0;
  virtual int HandlePingMessage(Transport::ThroughPingMessage *pMsg, Terabit::AsynchChannel *channel) = 0;
  virtual int HandleAddRecipientRequest(Transport::AddRecipientRequest *pMsg, Terabit::AsynchChannel *channel) = 0;
  virtual int HandleAddRecipientResponse(Transport::AddRecipientResponse *pMsg, Terabit::AsynchChannel *channel) = 0;
  virtual int HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, Terabit::AsynchChannel *channel) = 0;

  virtual int HandleInput(Terabit::AsynchChannel* channel, Transport::MessageHeader const & header,
                          Transport::MessageBase *pMsg) = 0;
  virtual int HandleInput(Terabit::AsynchChannel* channel, Transport::ChannelAddr const & caddr, 
                          char const * data, size_t len) = 0;
  virtual int HandleMulticastInput(Terabit::AsynchChannel* channel, Transport::ChannelAddr const & caddr, 
                          char const * data, size_t len) = 0;
  virtual void OnPacketHandlingCompleted(int rc, size_t len, char const * data, Terabit::AsynchChannel *channel) = 0;
};

class TransportProtocolHandler : public INetworkBasedHandler
{
public:
  static const unsigned short  MSG_TYPE_SIZE = sizeof(int);
  static const unsigned short  MAX_MSG_DATA_SIZE = NetworkProtocolHandler::MAX_DATA_SIZE - sizeof(Transport::ChannelAddr) - MSG_TYPE_SIZE;

public:
  TransportProtocolHandler(ITransportBasedHandler* input_handler, bool packaddr, char const * tagname);
  ~TransportProtocolHandler();

public:
  NetworkProtocolHandler& getNetworkHandler();
  int HandleInput(Terabit::AsynchChannel *channel, const char *data, size_t length);
  int HandleOutput(Transport::MessageBase* pMsg, Transport::ChannelAddr const & addr, Terabit::AsynchChannel* channel);
  int HandleOutput(char const * data, size_t size, Transport::ChannelAddr const & addr, Terabit::AsynchChannel* channel);
  int HandleOutput(char const * data, size_t size, Transport::ChannelAddr const & addr, Terabit::AsynchChannel* channel,
    unsigned int& qlen, unsigned int& qlen_in_bytes);
  int HandleOutput(TransportMsg const * sctm, unsigned int count, Terabit::AsynchChannel* channel);

  char const * tagname() const;

private:
  //  net logic
  int HandleNetLogicMessage(Transport::MessageBase *pMsg, Terabit::AsynchChannel *channel);
  int HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, Terabit::AsynchChannel *channel);
  int HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, Terabit::AsynchChannel *channel);
  int HandleCloseChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel);
  int HandleCloseMulticastChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel);
  int HandlePingMessage(Transport::PingMessage *pMsg, Terabit::AsynchChannel *channel);
  int HandlePingMessage(Transport::ThroughPingMessage* pMsg, Terabit::AsynchChannel *channel);
  int HandleAddRecipientRequest(Transport::AddRecipientRequest* pMsg, Terabit::AsynchChannel *channel);
  int HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, Terabit::AsynchChannel *channel);

private:
  ITransportBasedHandler* input_handler_;
  NetworkProtocolHandler   network_handler_;
};

inline
NetworkProtocolHandler& TransportProtocolHandler::getNetworkHandler()
{
  return network_handler_;
}

inline
char const * TransportProtocolHandler::tagname() const
{
  return network_handler_.tagname();
}

}
