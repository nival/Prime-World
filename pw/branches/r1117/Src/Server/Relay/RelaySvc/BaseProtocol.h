#pragma once

#include <IOTerabit/RefCntProtocol.h>
#include <IOTerabit/ProtocolFactory_T.h>
#include "TransportProtocol.h"
#include <mballocator/MessageBlockFactory.h>
#include <Network/TransportChannelType.h>

namespace Transport
{
  struct Address;
}

namespace Relay
{

class RelayChannelManager;
class Operation;

namespace Timer
{
  enum
  {
    NEW_CONNECTION = 0
  };
}

struct ConnectionSettings
{
  ConnectionSettings()
    :rcvbufSize_(0),
    soRcvbufSize_(-1),
    soSndbufSize_(-1),
    disableNagleAlgorithm_(false),
    enableWriteNotifications_(false)
  {
  }

  unsigned int rcvbufSize_;
  int soRcvbufSize_;
  int soSndbufSize_;
  bool disableNagleAlgorithm_;
  bool enableWriteNotifications_;
};

class BaseProtocol : public Terabit::RefCntProtocol, public ITransportBasedHandler
{
  friend class BaseChannel;

protected:
  struct OperationChain
  {
    OperationChain():first_(0), last_(0), count_(0) {}
    OperationChain(Operation* first, Operation* last):first_(first), last_(last)
    {
      if (first_)
        count_ = 1;
    }

    Operation* first_;
    Operation* last_;
    unsigned int count_;
  };

public:
  BaseProtocol(Terabit::ProtocolFactory& factory, bool packaddr, char const * tagname);
  virtual ~BaseProtocol();

  void* act() const { return act_; }
  void act(const void * p) { act_ = const_cast<void*>(p); }
  void set_message_block_factory(TL::MessageBlockFactorySP const & mbf);

protected:
  //  Terabit::RefCntProtocol interface
  virtual int  on_channel_up   (Terabit::AsynchChannel *channel);
  virtual void on_channel_done (Terabit::AsynchChannel *channel);
  virtual void on_reset ();
  virtual Terabit::MessageBlockFactory* get_message_block_factory() const;

  //  new BaseProtocol interface
  virtual int on_user_operation(Terabit::AsynchChannel *channel, Operation* op);

protected:
  virtual int applyConnectionSettings(Terabit::AsynchChannel *channel, ConnectionSettings const & cs);

protected:
  int SendOpenChannelResponse(Terabit::AsynchChannel *channel, bool result, Transport::Address const & caddr, 
    Transport::TPipeId const & pipeid, Transport::ChannelAddr const & raddr, Transport::EChannelType::Enum chnltype = Transport::EChannelType::Unicast);
  RelayChannelManager* manager(Terabit::AsynchChannel *channel) const { return (RelayChannelManager*)(channel->get_manager()); }

protected:
  Terabit::ProtocolFactory & factory_;
  TransportProtocolHandler transport_handler_;
  TL::MessageBlockFactorySP mbf_;
  void* act_;
};

}
