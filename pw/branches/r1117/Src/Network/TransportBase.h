#ifndef TRANSPORTBASE_H_INCLUDED
#define TRANSPORTBASE_H_INCLUDED

#include "Transport.h"

namespace Transport
{

class TransportSystemBase : public BaseObjectMT, public ITransportSystem
{
  NI_DECLARE_REFCOUNT_CLASS_2( TransportSystemBase, BaseObjectMT, ITransportSystem )
public:
  explicit TransportSystemBase();
  ~TransportSystemBase();

  void SetAddressTranslator( IAddressTranslator * _at ) { addressTranslator = _at; }

  virtual StrongMT<IChannel> OpenChannel( const Address& address, const TLoginData& loginData, unsigned int pingperiod, unsigned int to );
  virtual StrongMT<IChannelListener> CreateChannelListener( TServiceId interfaceId );

  virtual IAddressTranslator * GetAddressTranslator() const { return addressTranslator; }

  virtual void AddFrontendAuth( const TServiceId & interfaceId, IFrontendTransportAuth * _auth ) {}

private:
  //MessageFactory* factory;
  StrongMT<IAddressTranslator> addressTranslator;
};

} //namespace Transport

#endif //TRANSPORTBASE_H_INCLUDED
