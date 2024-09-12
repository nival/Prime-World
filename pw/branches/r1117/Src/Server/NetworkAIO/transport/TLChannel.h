#pragma once
#include "transport/TLChannelBase.h"

class ACE_Message_Block;

namespace Terabit
{
  class MessageBlockFactory;
}

namespace Transport
{
  struct MessageBase;
  class MessageFactory;
  struct MessageMiscInfo;
}

namespace naio
{
  class Operation;
}

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelFactory;

  namespace op
  {
    class ChannelOp;
    class OpenChannel;
    class SendData;
    class CloseChannel;
    class PingChannel;
  }

  class Channel : public ChannelBase, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2(Channel, ChannelBase, BaseObjectMT)

    friend class TL::ChannelFactory;
    friend class TL::op::SendData;
    friend class TL::op::CloseChannel;
    friend class TL::op::PingChannel;

  public:
    Channel(bool isactive, Transport::Address const & addr, Transport::TLoginData const & logindata, Transport::MessageFactory* mf);
    ~Channel();

  public:
    void Close();

    const Transport::Address& GetAddress() const;
    Transport::TClientId GetInternalClientId() const;
    bool IsIncomingConnection() const;

    void SendMsg( Transport::MessageBase* pMessage );
    Transport::MessageBase* ReceiveMsg();
    Transport::MessageBase* PeekMsg();

    void SendRaw( const byte* data, int size );
    bool ReceiveRaw( vector<byte>* data );
    bool ReceiveRaw( vector<byte>* data, Transport::MessageMiscInfo & _miscInfo );
    bool PeekRaw( vector<byte>* data );

    Transport::Ping GetPingTime() const;

    void KeepAlivePeriod(unsigned int sec);

  private:

    void setStatus_(EChannelStatus::Enum _sts);
  };
}
