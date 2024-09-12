#ifndef RDPTESTCLIENT_H_INCLUDED
#define RDPTESTCLIENT_H_INCLUDED

#include "RdpTest.h"


class TestRdpClient : public TestRdpContext
{
  NI_DECLARE_REFCOUNT_CLASS_1( TestRdpClient, TestRdpContext );

public:
  TestRdpClient( const RdpTestSettings & _sett, int _id );

  bool ConnectTo( TestRdpTransport * _transport, const char * _serverAddr );

protected:
  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn );
};

#endif //RDPTESTCLIENT_H_INCLUDED
