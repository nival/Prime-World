#pragma once
#include "Transport.h"
#include "TransportMux.h"
#include "../System/ThreadHelpers.h"

namespace Transport
{
class IAddressTranslator;
class Channel;
class ChannelListener;

class TransportSystem : public BaseObjectMT, public ITransportSystem 
{
  NI_DECLARE_REFCOUNT_CLASS_2( TransportSystem, BaseObjectMT, ITransportSystem )

  TransportSystem() {}

  MessageFactory* factory;
  Network::INetworkDriver* pDriver;
  StrongMT<IAddressTranslator> pAddrResolver;
  CObj<threading::ITickerThread> pThread;

  hash_map<Network::NetAddress, ConnectionMux*> boundConnections;
  threading::Mutex boundConnectionsLock;

  typedef list<StrongMT<ChannelListener> > TListenerList;
  TListenerList serverConnections;

public:
  TransportSystem( Network::INetworkDriver* _pDriver, MessageFactory* _factory, IAddressTranslator* _pAddrResolver, bool startThread );
  ~TransportSystem();

  virtual Network::NetAddress AllocateServerAddress( const Network::NetAddress & _ip );

  StrongMT<IChannel> OpenChannel( const Address& address, const TLoginData& loginData, 
    unsigned int pingperiod = Transport::Defaults::GetPingPeriod(), unsigned int to = Transport::Defaults::GetOpenChannelTimeout() );

  StrongMT<IChannelListener> CreateChannelListener( TServiceId interfaceId );

  StrongMT<IChannel> OpenChannelDirect( const Address& address, const TLoginData& loginData, const Network::NetAddress& netAddress, 
                                        unsigned int pingperiod = Transport::Defaults::GetPingPeriod(), 
                                        unsigned int to = Transport::Defaults::GetOpenChannelTimeout() );
  StrongMT<IChannelListener> CreateChannelListenerDirect( Transport::TServiceId const & interfaceId, const string& listenAddress );

  virtual void AddFrontendAuth( const TServiceId & interfaceId, IFrontendTransportAuth * _auth ) { NI_ALWAYS_ASSERT("Not implemented"); }

  void Step();
  
  Network::INetworkDriver* GetNetworkDriver() const { return pDriver; }
  IAddressTranslator* GetAddressTranslator() const { return pAddrResolver; }
};

}