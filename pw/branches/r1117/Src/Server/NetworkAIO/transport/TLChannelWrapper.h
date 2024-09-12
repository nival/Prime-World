#pragma once
#include <Network/Transport.h>
#include <transport/TLChannel.h>
//#include <transport/TLTypes.h>

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelWrapper : public Transport::IChannel, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( ChannelWrapper, Transport::IChannel, BaseObjectMT )

  public:
    ChannelWrapper();
    ChannelWrapper(TL::IChannelInternalSP const & spchnl);
    ~ChannelWrapper();

  public:
    //  Transport::IChannel
    Network::ConnectionState::Enum GetStatus() const;
    void Close();

    const Transport::Address& GetAddress() const;
    const Transport::TLoginData& GetLoginData() const;
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

    virtual void FillDebugString( string & _outStr ) {}

  private:
    StrongMT<Channel> sp_;
    mutable Transport::Ping ping_;
  };
}
