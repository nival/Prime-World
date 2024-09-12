#include "stdafx.h"
#include "ConnectionsContainer.h"
#include "Connection.h"
#include "DriverSettings.h"

namespace Network
{

static float s_connectionTimeout = 60 * 90.0;
REGISTER_VAR( "login_conn_timeout2", s_connectionTimeout, STORAGE_GLOBAL);


  ConnectionsContainer::ConnectionsContainer() :
  addedConn( false ),
  lastConnectionsLeakReport( 0 )
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void ConnectionsContainer::AddConnection(StrongMT<Connection>& connection )
  {
    mutex.Lock();
    toAddConns.push_back( connection );
    addedConn = true;
    mutex.Unlock();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void ConnectionsContainer::Step()
  {
    timer::Time now = timer::Now();

    if ( addedConn )
    {
      mutex.Lock();
      for ( int i = 0; i < toAddConns.size(); i++ )
        connections.push_back( ConnSlot( toAddConns[ i ], now + s_connectionTimeout ) );

      toAddConns.clear();
      addedConn = false;
      mutex.Unlock();
    }

    if ( connections.size() > 4096 )
    {
      if ( now > lastConnectionsLeakReport + 20.0 )
      {
        lastConnectionsLeakReport = now;
        WarningTrace( "Too many connections in ConnectionsContainer (leaked?). number=%d", connections.size() );
      }
    }

    int connsNum = connections.size();
    int remainsNum = connsNum % FD_SETSIZE;
    for ( int i = 0;  i < connsNum / FD_SETSIZE; i++ )
      ProcessConnections( i * FD_SETSIZE, FD_SETSIZE );
    ProcessConnections( connsNum - remainsNum, remainsNum );

    CleanupErasedConnections( now );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void ConnectionsContainer::ProcessConnections( int first, int num )
  {
    timeval timeout;
    fd_set readSet, writeSet, exceptSet;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;//SELECT_TIMEOUT_MICRO;
    FD_ZERO( &readSet );
    FD_ZERO( &writeSet );
    FD_ZERO( &exceptSet );

    NI_VERIFY( num <= FD_SETSIZE, "too many connections for one select call", /* nothing to do */ );
    // добавляем в множества
    for ( int i = first; i < first + num && i < first + FD_SETSIZE; i++ )
      connections[i].conn->AddSelf( &readSet, &writeSet, &exceptSet );
    // выбираем сокеты с событиями
    select( num, &readSet, &writeSet, &exceptSet, &timeout );

    for ( int j = first; j < first + num && j < first + FD_SETSIZE; j++ )
    {
      StrongMT<Connection> conn = connections[j].conn;
      // обрабатываем события
      conn->DoIO( &readSet, &writeSet, &exceptSet );

      if ( conn->WantAsyncClose() )
        conn->Close();

      // если закрыт, то обнуляем и удаляем
      if ( conn->GetStatus() == ConnectionState::Closed )
      {
        connections[j].conn = 0;
        Instrumentation::activeConnections.DecValue( 1 );
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void ConnectionsContainer::CleanupErasedConnections( timer::Time _now )
  {
    int connsNum = connections.size();
    int cnt = 0;
    for ( int i = 0; i < connsNum; i++ )
    {
      const bool expired = connections[i].conn.Valid() && ( _now > connections[i].expires );

      if ( expired )
        ErrorTrace( "Login-like connection expired. timeout=%.1f, num=%d", s_connectionTimeout, connections.size() );

      if ( connections[i].conn && !expired )
      {
        if ( cnt != i )
        {
          connections[ cnt ] = connections[ i ];
          connections[ i ].conn = 0;
        }
        cnt++;
      }
    }
    connections.erase( connections.begin() + cnt, connections.end() );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void ConnectionsContainer::Clear()
  {
    connections.clear();
    toAddConns.clear();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
