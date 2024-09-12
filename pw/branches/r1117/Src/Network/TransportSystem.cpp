#include "stdafx.h"
#include "TransportSystem.h"
#include "AddressTranslator.h"
#include "TransportChannelListener.h"
#include "TransportChannel.h"
#include "System/sleep.h"

namespace Transport
{
  IMPLEMENT_TICKER( TransportSystem, Step )
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TransportSystem::TransportSystem( Network::INetworkDriver* _pDriver, MessageFactory* _factory, IAddressTranslator* _pAddrResolver, bool startThread ) 
  : pDriver(_pDriver), factory(_factory), pAddrResolver(_pAddrResolver)
  {
    NI_ALWAYS_ASSERT( "Obsolette code" );

    if( startThread )
      pThread =  threading::ITickerThread::Create( new TransportSystemTicker( this ), "Transport" );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TransportSystem::~TransportSystem()
  {
    pThread = 0;

    hash_map<Network::NetAddress, ConnectionMux*>::iterator it = boundConnections.begin(), itEnd = boundConnections.end(); 
    for ( ;it != itEnd ; ++it )
    {
      delete (*it).second;
    }
  }



  Network::NetAddress TransportSystem::AllocateServerAddress( const Network::NetAddress & _ip )
  {
    NI_ALWAYS_ASSERT( "Not implemented" );
    return Network::NetAddress();
  }


  StrongMT<IChannel>  TransportSystem::OpenChannel( const Address& _address, const TLoginData& loginData, 
    unsigned int /*pingperiod*/, unsigned int /*to*/ )
  {
    Address address = _address;
    address.target = pAddrResolver->GetLastServiceInstance( address.target );
    Network::NetAddress naddr = pAddrResolver->GetSvcAddress( address.target );

    return OpenChannelDirect( address, loginData, naddr );
  }



  StrongMT<IChannelListener> TransportSystem::CreateChannelListener( TServiceId interfaceId )
  {
    Network::NetAddress backAddr = AllocateServerAddress( pAddrResolver->GetServerIp() );
    pAddrResolver->DefineRoute( interfaceId, backAddr );

    Network::NetAddress naddr = pAddrResolver->GetSvcAddress( interfaceId );

    StrongMT<Network::IConnectionsManager> pManager = pDriver->CreateConnectionListener( naddr );

    if ( !pManager )
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "Error listening for interface " << interfaceId.c_str() << " on " << naddr << endl;
      return 0;
    }

    systemLog( NLogg::LEVEL_MESSAGE ) << "Listening for interface " << interfaceId.c_str() << " on " << naddr << endl;

    StrongMT<ChannelListener> listener = new ChannelListener( interfaceId, factory, pManager, pDriver->GetStreamAllocator() );
    serverConnections.push_back( listener );
    return StrongMT<IChannelListener>( listener );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  StrongMT<IChannel> TransportSystem::OpenChannelDirect( const Address& address, const TLoginData& loginData, 
    const Network::NetAddress& netAddress, unsigned int /*pingperiod*/, unsigned int /*to*/ )
  { 
    threading::MutexLock lock(boundConnectionsLock);
    if ( boundConnections.find( netAddress ) == boundConnections.end() )
    {
      StrongMT<Network::IConnection> pConn = pDriver->Connect( netAddress );
      if ( !pConn || pConn->GetStatus() == Network::ConnectionState::Closed )
        return StrongMT<IChannel>(0);

      ConnectionMux* connection = new ConnectionMux;
      connection->Init( factory, pConn, false, 0, pDriver->GetStreamAllocator() );
      boundConnections[ netAddress ] = connection;
    }

    systemLog( NLogg::LEVEL_MESSAGE ) << "Opening new channel for " << AddressToString( address ) << " on " << netAddress << endl;

    ConnectionMux* proxy = boundConnections[ netAddress ];

    return proxy->OpenChannel( address, loginData );
  }
  

  StrongMT<IChannelListener> TransportSystem::CreateChannelListenerDirect( Transport::TServiceId const & interfaceId, const string& listenAddress )
  {
    StrongMT<Network::IConnectionsManager> pManager = pDriver->CreateConnectionListener( listenAddress );

    if ( !pManager )
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "Error listening on " << listenAddress << endl;
      return 0;
    }

    systemLog( NLogg::LEVEL_MESSAGE ) << "Listening on " << listenAddress << endl;
    StrongMT<ChannelListener> listener = new ChannelListener( TServiceId(), factory, pManager, pDriver->GetStreamAllocator() );
    serverConnections.push_back( listener );
    return StrongMT<IChannelListener>( listener );
  }



  void TransportSystem::Step()
  {
    {
      threading::MutexLock lock(boundConnectionsLock);
      for ( hash_map<Network::NetAddress, ConnectionMux*>::iterator it = boundConnections.begin() ;it != boundConnections.end() ; )
      {
        (*it).second->Step();
        
        if ( (*it).second->HasNetConnection() )
          ++it;
        else
        {
          hash_map<Network::NetAddress, ConnectionMux*>::iterator itOld = it;
          ++it;
          delete itOld->second;
          boundConnections.erase( itOld );
        }
      }
    }

    {
      TListenerList::iterator it = serverConnections.begin(), itEnd = serverConnections.end(); 
      for ( ;it != itEnd ; ++it )
      {
        (*it)->Step();	
      }
    }

    nival::sleep( 5 );
  }


  ITransportSystem* CreateTransportSystem( Network::INetworkDriver* pDriver, MessageFactory* factory, IAddressTranslator* pAddrResolver )
  {
    return new TransportSystem( pDriver, factory, pAddrResolver, true );
  }

}// namespace Transport

