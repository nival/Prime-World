#ifndef RDPTESTSERVER_H_INCLUDED
#define RDPTESTSERVER_H_INCLUDED

#include "RdpTest.h"


namespace ni_udp
{
  class ISocketServer;
  class ISocket;
}


namespace ni_rnd
{
  class IGenerator;
}


class TestRdpServerContext : public TestRdpContext
{
  NI_DECLARE_REFCOUNT_CLASS_1( TestRdpServerContext, TestRdpContext );

public:
  TestRdpServerContext( const RdpTestSettings & _sett, int _id ) :
  TestRdpContext( _sett, _id )
  {
  }

private:
  /*
  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionClosed( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionFailed( ni_udp::IRdpConnection * _conn );
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );
  */
};



class TestRdpServer : public ni_udp::IRdpListenContextCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TestRdpServer, ni_udp::IRdpListenContextCallback, BaseObjectMT );

public:
  TestRdpServer( TestRdpTransport * _transport, const RdpTestSettings & _sett );

  void Poll();

protected:
  typedef std::list<StrongMT<TestRdpServerContext> >  Contexts;

  const RdpTestSettings             settings;
  threading::Mutex                  mutex;
  StrongMT<TestRdpTransport>        transport;
  StrongMT<ni_udp::IRdpListenContext> listener;
  Contexts                          contexts;
  int                               nextId;

  virtual ni_udp::IRdpConnectionCallback * OnConnectionEstablished( ni_udp::IRdpConnection * _conn, const ni_udp::NetAddr & _remoteAddr );
};

#endif //RDPTESTSERVER_H_INCLUDED
