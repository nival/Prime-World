#include "stdafx.h"
#include "ConnectionManager.h"
#include "Connection.h"
#include "Errors.h"
#include "DriverSettings.h"
#include "Socket.h"

namespace Network
{
  IncomingConnectionManager::IncomingConnectionManager( const char* url, bool _useCompressionForNewConnections, const ConnectionSettings& _settings )
    : myURL( url )
    , listener( url )
    , useCompressionForNewConnections( _useCompressionForNewConnections )
    , settings( _settings )
  {
    bool res = listener.Listen();
    NI_ASSERT( res, "Error listening for socket" );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  IncomingConnectionManager::~IncomingConnectionManager()
  {
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void IncomingConnectionManager::GetNewConnections(  TNewConnections& _newConnections )
  {
    threading::MutexLock lock( newConnectionsMutex );

    _newConnections.swap( newConnections );
    newConnections.clear();
  }

  void IncomingConnectionManager::Step()
  {
    socket_type dataSocket = listener.Accept( &remote );
    while ( dataSocket != BAD_SOCKET )
    {
      Instrumentation::activeConnections.AddValue( 1 );

      {
        threading::MutexLock lock( newConnectionsMutex );

        StrongMT<Connection> conn = new Connection( settings, dataSocket, remote );

        if ( useCompressionForNewConnections )
          conn->EnableCompression();
        container.AddConnection( conn );

        newConnections.push_back( conn );
      }

      // get next connection
      dataSocket = listener.Accept( &remote );
    }
 
    container.Step();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ConnectionState::Enum IncomingConnectionManager::GetListenerStatus()
  {
    return listener.GetStatus();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void IncomingConnectionManager::SetMessageReservedSpace( int space )
  {
    settings.reservedSpaceOnMessageStart = space;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

