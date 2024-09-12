#ifndef RDPTEST_H_INCLUDED
#define RDPTEST_H_INCLUDED

//#include "Network/RUDP/ISockSrv.h"
#include "Network/RUDP/IRdp.h"
#include "System/Histogram.h"
#include <map>
#include <vector>
#include <list>
#include <Pdh.h>


namespace ni_udp
{
  class ISocketServer;
  class ISocket;
}


namespace ni_rnd
{
  class IGenerator;
}



struct TestRdpTransport : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( TestRdpTransport, BaseObjectMT );

public:
  TestRdpTransport() {}
  bool Init( const char * _bindAddr, bool _randomizePort, unsigned _buffer );

  ni_udp::NetAddr                   bindAddr;
  StrongMT<ni_udp::ISocketServer>   sockServer;
  StrongMT<ni_udp::IRdp>            rdp;
  Strong<ni_rnd::IGenerator>        rnd;
};



struct RdpTestSettings
{
  int       helloBurstLength;
  float     minSendPeriod, maxSendPeriod;
  unsigned  minDataSize, maxDataSize;
  float     minLifetime, maxLifetime;

  RdpTestSettings() :
  helloBurstLength( 3 ),
  minSendPeriod( 0.1f ), maxSendPeriod( 10.0f ),
  maxDataSize( 10000 ),
  minLifetime( 45.0f ), maxLifetime( 75.0f )
  {}
};





namespace RdpTestMsg
{

enum EType { TypeBurst = 1, TypePing = 2, TypePong = 3 };

struct Header
{
  const static int OpenMarker = 0xfadec0de;

  int   openMarker;
  int   type;
  int   index;

  explicit Header( int _type = 0 ) :
  openMarker( OpenMarker ),
  type( _type ),
  index( 0 )
  {}
};


struct HelloBurst : public Header
{
  int   total;

  HelloBurst() : 
  Header( TypeBurst ),
  total( 0 )
  {}
};


struct Ping : public Header
{
  unsigned  sum, factor;

  explicit Ping( bool _pong ) :
  Header( _pong ? TypePong : TypePing ),
  sum( 0 ),
  factor( 0 )
  {}
};

} //namespace RdpTestMsg





class TestRdpContext : public ni_udp::IRdpConnectionCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TestRdpContext, ni_udp::IRdpConnectionCallback, BaseObjectMT );

public:
  struct EStatus {
    enum Enum { Starting, Connecting, Working, Finished, Failed };
  };

  TestRdpContext( const RdpTestSettings & _sett, int _id );

  int Id() const { return id; }
  void Init( ni_udp::IRdpConnection * _conn, TestRdpTransport * _transport );
  void LimitLifetime();
  EStatus::Enum Poll();

protected:
  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionClosed( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionFailed( ni_udp::IRdpConnection * _conn );
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );

  virtual bool OnMessage( const RdpTestMsg::Header * _hdr, size_t _size );

  void SwitchUnsafe( EStatus::Enum _st );
  void Fail();
  void SendSingleBurstMsg();
  void SendSinglePingMsg( timer::Time _now );

  const RdpTestSettings       settings;
  const int                   id;

  typedef std::map<int, timer::Time> PingLog;

  threading::Mutex            mutex;
  EStatus::Enum               status;
  StrongMT<ni_udp::IRdpConnection> conn;
  StrongMT<TestRdpTransport>  transport;
  int                         outgoingBurstIndex;
  int                         incomingBurstIndex, incomingBurstTotal;
  timer::Time                 nextPingTime;
  int                         nextPingIndex;
  timer::Time                 startTime, lifetime;
  PingLog                     pingLog;
  std::vector<byte>           sendBuffer;
};

#endif //RDPTEST_H_INCLUDED
