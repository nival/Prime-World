#pragma once

#include "BaseProtocol.h"
#include "BaseProtocolFactory.h"
#include "Network/TransportMessages.h"

namespace Relay
{

class OpenChnl2SvcOp;

class RelayBackendProtocol : public BaseProtocol
{
public:
  RelayBackendProtocol(Terabit::ProtocolFactory& factory);
  virtual ~RelayBackendProtocol();

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
  virtual int HandleInput(Terabit::AsynchChannel* channel, Transport::ChannelAddr const & caddr, char const * data, size_t len);
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
  //  BaseProtocol interface
  int applyConnectionSettings(Terabit::AsynchChannel *channel);

  int ValidateContext(BackendContextSP const & _ctx, char const * const _funcname, int _chnlid) const;

  int SendAddRecipientResponse(Terabit::AsynchChannel *channel, Transport::AddRecipientResult::Enum result, Transport::TPipeId pipe, 
                               Transport::TClientId const & recipient);

private:
  BackendContextSP spctx_;
  unsigned long long totalWrittenBytes_;
  unsigned int amountOfReadBytes_;
  unsigned long long totalReadBytes_;
  unsigned long svcPingSeqNum_;
  volatile time_t lastestInternalServicePingTime_;
};

typedef BaseProtocolFactory<RelayBackendProtocol> BackendProtocolFactory;

#define VALIDATE_CONTEXT( _ctx, _funcname, _chnlid, _error_statement ) { int _rc_ = ValidateContext(_ctx, _funcname, _chnlid); if (_rc_ < 0) _error_statement; }

}
