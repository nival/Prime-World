#include "stdafx.h"
#include "TransportBase.h"
#include "Network/AddressTranslator.h"
#include "System/InlineProfiler.h"

NI_DEFINE_REFCOUNT( Transport::IChannel );
NI_DEFINE_REFCOUNT( Transport::IFrontendTransportAuth );


namespace Transport
{

TransportSystemBase::TransportSystemBase()
{
}



TransportSystemBase::~TransportSystemBase()
{
}



StrongMT<IChannel> TransportSystemBase::OpenChannel( const Address & address, const TLoginData & loginData, unsigned int pingperiod, unsigned int to )
{
  NI_PROFILE_FUNCTION;

  if ( !addressTranslator )
    return 0;

  Transport::Address addr(address);
  addr.target = addressTranslator->GetLastServiceInstance( address.target );
  Network::NetAddress naddr = addressTranslator->GetSvcAddress( addr.target );

  return OpenChannelDirect( addr, loginData, naddr );
}



StrongMT<IChannelListener> TransportSystemBase::CreateChannelListener( TServiceId interfaceId )
{
  NI_PROFILE_FUNCTION;

  if ( !addressTranslator )
    return 0;

  Network::NetAddress naddr = addressTranslator->GetSvcAddress( interfaceId );
  if ( naddr.empty() )
  {
    naddr = AllocateServerAddress( addressTranslator->GetServerIp() );

    addressTranslator->DefineRoute( interfaceId, naddr );
    naddr = addressTranslator->GetSvcAddress( interfaceId );
  }

  DebugTrace( "Creating service '%s' listener on ip=%s", interfaceId.c_str(), naddr );
  if ( naddr.empty() )
    return 0;

  return CreateChannelListenerDirect( interfaceId, naddr );
}

} //namespace Transport
