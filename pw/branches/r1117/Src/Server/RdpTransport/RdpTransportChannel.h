#ifndef RDPTRANSPORTCHANNEL_H_INCLUDED
#define RDPTRANSPORTCHANNEL_H_INCLUDED

#include "Network/Transport.h"
#include "Network/RUDP/IRdp.h"
#include "System/Schedule.h"
#include "RdpTransportUtils.h"
#include <list>


namespace rdp_transport
{

class IMessageAllocator;
class Message;
class Channel;

class IDelayedAcceptCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IDelayedAcceptCallback, IBaseInterfaceMT );
public:
  virtual void DelayedChannelAcceptFailed( Channel * _chan ) = 0;
  virtual void AcceptDelayedChannel( Channel * _chan ) = 0;
};



namespace EChanRole
{
  enum Enum { Undefined, Active, ActiveDelayed, Reactive, ReactiveDelayed };
};


class Channel : public Transport::IChannel, public ni_udp::IRdpConnectionCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( Channel, Transport::IChannel, ni_udp::IRdpConnectionCallback, BaseObjectMT );

public:
  Channel( EChanRole::Enum _role, const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData, const CommonCtx & _ctx );
  ~Channel();

  const ni_udp::NetAddr & RemoteAddr() const { return remoteAddr; }
  EChanRole::Enum Role() const { return role; }

  bool InitAsActive( ni_udp::IRdp * _rdp, const ni_udp::NetAddr & _remoteAddr, unsigned _remoteMux );
  bool InitAsReactive( ni_udp::IRdpConnection * _conn, IDelayedAcceptCallback * _delayedAcceptCb, timer::Time _delay );

  void PostponeMsg( const byte * _data, int _size );

  //IChannel
  virtual Network::ConnectionState::Enum GetStatus() const;
  virtual void Close();

  virtual const Transport::Address & GetAddress() const { return transportAddress; }
  virtual const Transport::TLoginData & GetLoginData() const { return loginData; }
  virtual Transport::TClientId GetInternalClientId() const { return transportAddress.client; }
  virtual bool IsIncomingConnection() const { return ( role != EChanRole::Active ) && ( role != EChanRole::ActiveDelayed ); }

  virtual void SendMsg( Transport::MessageBase * pMessage );
  virtual Transport::MessageBase * ReceiveMsg();
  virtual Transport::MessageBase * PeekMsg();

  virtual void SendRaw( const byte * data, int size );
  virtual bool ReceiveRaw( vector<byte> * data );
  virtual bool ReceiveRaw( vector<byte> * data, Transport::MessageMiscInfo & _miscInfo );
  virtual bool PeekRaw( vector<byte> * data );

  virtual Transport::Ping GetPingTime() const;
  virtual void FillDebugString( string & _outStr );

protected:
  //IRdpConnectionCallback
  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionClosed( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionFailed( ni_udp::IRdpConnection * _conn );
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );

  ni_udp::IRdpConnection * RdpConnection() const { return connection; }

  void DelayedAccept();
  void CloseDelayedChannel( const char * _dbgReason );
  void DelayedActiveConnectionEstablished();

  //overridable
  virtual void OnRdpConnectionChange() {}

private:
  const static size_t MAX_MSG_SIZE = 65536;
  typedef std::list<StrongMT<Message>> Queue;

  const EChanRole::Enum   role;
  const ni_udp::NetAddr   remoteAddr;
protected://UGLY
  Transport::Address      transportAddress;
private:
  threading::Mutex        generalMutex;
  Network::ConnectionState::Enum state;
  Transport::TLoginData   loginData;
  Transport::Ping         pingData;

  CommonCtx               commonCtx;

  WeakMT<IDelayedAcceptCallback> delayedAcceptCb;

  StrongMT<ni_udp::IRdpConnection> connection;

  Queue                   outgoing;

  threading::Mutex        incomingMutex;
  Queue                   incoming;

  void OnDelayedAcceptTimeout( TScheduleAuxParam );
  bool TryPostponeMsg( const byte * _data, int _size, bool _force );
  void ClearInBuffers();
  void ClearOutBuffers();
  void FlushOutgoingDataUnsafe();
  static size_t NivalSerialize( void * buffer, size_t bufSize, Transport::MessageBase * tmsg );
};

} //namesapce rdp_transport

#endif //RDPTRANSPORTCHANNEL_H_INCLUDED
