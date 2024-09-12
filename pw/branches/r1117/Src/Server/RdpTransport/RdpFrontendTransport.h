#ifndef RDPFRONTENDTRANSPORT_H_INCLUDED
#define RDPFRONTENDTRANSPORT_H_INCLUDED

#include "RdpTransportBase.h"


namespace rdp_transport
{

class SocketFactory;

class PrimaryFrontend : public PrimaryBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( PrimaryFrontend, PrimaryBase );

public:
  PrimaryFrontend( Transport::MessageFactory * _msgFact, Transport::IAddressTranslator * _at, const ni_udp::NetAddr & _defaultSocketAddr );

protected:
  //PrimaryBase
  virtual void ImplSetupRdpOptions( ni_udp::RdpOptions & _opt );
  virtual StrongMT<Listener> ImplCreateChannelListener( Transport::TServiceId const & _interfaceId );
  virtual StrongMT<Channel> ImplCreateOutgoingChannel( const ni_udp::NetAddr & _rdpRemoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData );

  //ITransportSystem
  virtual void AddFrontendAuth( const Transport::TServiceId & interfaceId, Transport::IFrontendTransportAuth * _auth );

private:
  typedef std::map<Transport::TServiceId, StrongMT<Transport::IFrontendTransportAuth> > AuthList;

  threading::Mutex  mutex;
  AuthList  authList;
};

} //namespace rdp_transport

#endif RDPFRONTENDTRANSPORT_H_INCLUDED
