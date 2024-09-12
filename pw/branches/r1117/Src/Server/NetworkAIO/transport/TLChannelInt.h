#pragma once
#include "transport/TLTypes.h"
#include <System/EnumToString.h>
#include <Network/TransportUtils.h>
#include <Network/TransportAddress.h>
#include <Network/TransportLoginData.h>
#include "mballocator/MessageBlockType.h"
#include <Network/TransportChannelType.h>
#include <Network/TransportMessagesResults.h>

class ACE_Message_Block;

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace EChannelStatus
  {
    enum Enum
    {
      INVALID = -4,
      INIT =-3,
      CLOSING = -2,
      CLOSED = -1,
      CONNECTED = 0,  //  >= 0 - channel is operable, < 0 - non-operable
      CONNECTING = 1,
    };

    NI_ENUM_DECL_STD;
  }

  class ChannelSuperBase : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( ChannelSuperBase, IBaseInterfaceMT );

  public:
    ChannelSuperBase(Transport::EChannelType::Enum _type, bool _active, Transport::Address const & _taddr);
    virtual ~ChannelSuperBase();

  public:
    ///  open channel actively
    virtual int onOpenChannel(bool success, Transport::ChannelAddr const & remoteAddr) = 0;
    ///  channel open passively
    virtual int onOpenChannel(Transport::Address const & addr, Transport::TPipeId& pipeid) = 0;

    virtual void onOpenChannelNotify() = 0;

    ///  allocator methods
    virtual ACE_Message_Block* allocMsgBlock_(size_t len, MBType::Enum _type) = 0;
    virtual ACE_Message_Block* allocMsgBlock_(size_t len, char const * data, MBType::Enum _type) = 0;
    virtual void freeMsgBlock_(ACE_Message_Block* mb) = 0;

    virtual ACE_Message_Block* packMessage(Transport::MessageBase* pmsg) = 0;
    virtual Transport::MessageBase* unpackMessage(ACE_Message_Block* mb) = 0;

    virtual TL::ConnectionWP getConnection() = 0;

    virtual void close(bool active) = 0;

    virtual void setPing(long ping, unsigned long seqnum) = 0;

    virtual unsigned long lastRecvSeqNum() const = 0;

    virtual int enqueueRecv(size_t len, char const * data) = 0;

    virtual void lastRecvSeqNum(unsigned long seqnum) = 0;

    virtual int completeOp(op::ChannelOpPtr const & op) = 0;

    virtual int checkActivity(ACE_Time_Value const & now) = 0;

    virtual unsigned int openTimeout() const = 0;

    virtual Transport::TLoginData const & openChannelKey() const = 0;

    virtual int OnAddRecipientResponse(Transport::TClientId const & _recipient, Transport::AddRecipientResult::Enum _res) { return 0; };

    virtual int OnRemoveRecipient(Transport::TClientId const & _recipient) { return 0; };

  public:
    Transport::ChannelAddr const & chaddr() const { return chaddr_; }
    Transport::Address const & taddr() const { return taddr_; }
    bool active() const { return active_; }

    EChannelStatus::Enum status() const { return _GetStatus(); }
    void close();

    Transport::EChannelType::Enum channeltype() const { return channeltype_; }

  protected:
    EChannelStatus::Enum _SetStatus(EChannelStatus::Enum _sts);

    EChannelStatus::Enum _GetStatus() const { return (EChannelStatus::Enum)sts_.value(); }

    void chaddr(Transport::ChannelAddr const & _chaddr) { chaddr_ = _chaddr; }

    void chaddr(Transport::TClientId const & _clientid, Transport::TPipeId const & _pipeid) {
      chaddr_.client = _clientid;
      chaddr_.pipe = _pipeid;
    }

  private:
    Transport::ChannelAddr chaddr_;
    Transport::Address taddr_;
    bool active_;
    ACE_Atomic_Op<ACE_Thread_Mutex, long> sts_;
    Transport::EChannelType::Enum channeltype_;
  };
}
