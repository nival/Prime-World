#pragma once

#include "BaseProtocol.h"
#include "ClientContext.h"
#include "BaseProtocolFactory.h"

namespace Relay
{

class RelayChannelManager;

class RelayClientProtocol : public BaseProtocol
{
public:
  RelayClientProtocol(Terabit::ProtocolFactory& factory);
  virtual ~RelayClientProtocol();

public:
  //  ITransportBasedHandler
  virtual int HandleOpenChannelRequest(Transport::OpenChannelRequest *pMsg, Terabit::AsynchChannel *channel);
  virtual int HandleOpenChannelResponse(Transport::OpenChannelResponse *pMsg, Terabit::AsynchChannel *channel);
  virtual int HandleCloseChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel);
  virtual int HandleCloseMulticastChannel(Transport::CloseChannelMessage *pMsg, Terabit::AsynchChannel *channel);
  virtual int HandlePingMessage(Transport::PingMessage *pMsg, Terabit::AsynchChannel *channel);
  virtual int HandlePingMessage(Transport::ThroughPingMessage *pMsg, Terabit::AsynchChannel *channel);
  virtual int HandleAddRecipientRequest(Transport::AddRecipientRequest *pMsg, Terabit::AsynchChannel *channel);
  virtual int HandleAddRecipientResponse(Transport::AddRecipientResponse *pMsg, Terabit::AsynchChannel *channel);
  virtual int HandleRemoveRecipient(Transport::RemoveRecipientMessage *pMsg, Terabit::AsynchChannel *channel);
  virtual int HandleInput(Terabit::AsynchChannel* channel, Transport::MessageHeader const & header,
                          Transport::MessageBase *pMsg);
  virtual int HandleInput(Terabit::AsynchChannel* channel, Transport::ChannelAddr const & caddr, 
                          char const * data, size_t len);
  virtual int HandleMulticastInput(Terabit::AsynchChannel* channel, Transport::ChannelAddr const & caddr, 
                          char const * data, size_t len);
  virtual void OnPacketHandlingCompleted(int rc, size_t len, char const * data, Terabit::AsynchChannel *channel);

public:
  //  Terabit::Protocol interface
  virtual void on_reset ();
  virtual int on_channel_up (Terabit::AsynchChannel *channel);
  virtual void on_channel_done (Terabit::AsynchChannel *channel);
  virtual int on_read_completed (Terabit::AsynchChannel *channel, const char *data, size_t length);
  virtual int on_write_completed (Terabit::AsynchChannel *channel);
  virtual int on_timeout (Terabit::AsynchChannel *channel, const void *arg);
  virtual int check_activity (Terabit::AsynchChannel *channel, const ACE_Time_Value&  last_op_time);

  //  BaseProtocol interface
  virtual int on_user_operation(Terabit::AsynchChannel *channel, Operation* op);

private:
  int applyConnectionSettings(Terabit::AsynchChannel *channel);

  int OnReadHandlingCompleted(int result, size_t len, const char *data, Terabit::AsynchChannel *channel);

  int HandleNewThroughConnection(Transport::OpenChannelRequest *pMsg, Terabit::AsynchChannel *channel);

private:
  ClientContextWP wpctx_;
  volatile time_t lastKeepaliveMsg_;
  volatile time_t lastKeepaliveMsgCheckTime_;

  typedef std::map<Transport::TServiceId, BaseProtocol::OperationChain> SvcOperationsMapT;
  SvcOperationsMapT  svc2ops_;

  //  temp variables for debug
  Transport::TClientId userid_;
  unsigned int channelid_;
  unsigned long long totalWrittenBytes_;
  unsigned int amountOfReadBytes_;
  unsigned long long totalReadBytes_;

  static ACE_Atomic_Op<ACE_Thread_Mutex, long> count_;
};

typedef BaseProtocolFactory<RelayClientProtocol> ClientProtocolFactory;

}
