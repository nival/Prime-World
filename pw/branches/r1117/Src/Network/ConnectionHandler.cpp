#include "stdafx.h"
#include "ConnectionHandler.h"

namespace Network
{


static float s_connectionTimeout = 60 * 90.0;
REGISTER_VAR( "login_conn_timeout", s_connectionTimeout, STORAGE_GLOBAL);

ConnectionHandler::ConnectionHandler( Network::INetworkDriver* _pDriver, const Network::NetAddress& _loginServerAddress, ::SSL_CTX* _secureContext ) :
secureContext(_secureContext),
lastLeakReport( 0 )
{
  pManager = _pDriver->CreateConnectionListener( _loginServerAddress );
}



ConnectionHandler::~ConnectionHandler()
{
  for ( TConnSlots::iterator it = connSlots.begin();it != connSlots.end() ; ++it )
  {
    if( it->conn )
      it->conn->AsyncClose();
  }
}



void ConnectionHandler::Step(IConnectionProcessor* processor)
{
  timer::Time now = timer::Now();

  if ( pManager )
  {
    TConnections newConnections;
    pManager->GetNewConnections( newConnections );

    static int total_new_connections = 0;
    total_new_connections += newConnections.size();
    if ( newConnections.size() )
      LOG_D(0) << "ConnectionHandler: new connections count=" << newConnections.size() << ", total=" << total_new_connections;

    for ( TConnections::iterator it = newConnections.begin(); it != newConnections.end() ; ++it )
    {
      if ( secureContext )
        (*it)->StartSSL( secureContext, true );
      connSlots.push_back( ConnSlot( *it, now + s_connectionTimeout ) );
      processor->OnNewConnection(*it);
    }
  }

  if ( connSlots.size() > 4096 )
    if ( now > lastLeakReport + 20.0 )
    {
      lastLeakReport = now;
      WarningTrace( "Too many connections in ConnectionHandler (leaked?). number=%d", connSlots.size() );
    }

  for ( TConnSlots::iterator it = connSlots.begin(); it != connSlots.end(); )
  {
    StrongMT<Network::IConnection> conn = it->conn;
    if ( !conn )
    {
      it = connSlots.erase( it );
      continue;
    }

    if ( now > it->expires )
    {
      ErrorTrace( "Login connection expired. timeout=%.1f, num=%d", s_connectionTimeout, connSlots.size() );
      it = connSlots.erase( it ); 
      continue;
    }

    CObj<Stream> stream = conn->Receive();

    bool dropConnection = false;
    if ( stream )
    {
      dropConnection = processor->ProcessPacket(stream.GetPtr(), conn);
      conn->ReleaseReceived( stream );
      stream = 0;
    }

    if ( dropConnection || conn->GetStatus() == Network::ConnectionState::Closed )
    {
      processor->OnDropConnection( it->conn );
      it = connSlots.erase(it); 
    }
    else
    {
      ++it;
    }
  }
}

} // Network