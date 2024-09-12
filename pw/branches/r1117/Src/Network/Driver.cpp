#include "stdafx.h"
#include "Driver.h"
#include "ConnectionManager.h"
#include "Errors.h"
#include "Socket.h"

#include "System/DebugVar.h"
#include "System/ThreadNames.h"
#include "System/sleep.h"


namespace Network
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  Driver::Driver(EDriverTrafficType::Enum tt)
  {
    bool startupSuccess = InitSocketEngine();

    SetTrafficType( tt );

    NI_VERIFY( startupSuccess, NI_STRFMT( "Error initializing WinSock: %s", SocketErrorToString( GetSocketError() ) ), return );

    driverThread = new threading::ProcessingThread<Driver>( *this );
    threadStarted.Wait();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  Driver::~Driver()
  {
    driverThread->Stop( true, 3000 );
    delete driverThread;
    linkManagers.clear();
    container.Clear();

    CleanupSocketEngine();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  IConnectionsManager* Driver::CreateConnectionListener( const string& url, bool useCompression )
  {
    StrongMT<IncomingConnectionManager> linkManager = new IncomingConnectionManager( url.c_str(), useCompression, settings );
    if ( linkManager->GetListenerStatus() == ConnectionState::Closed ) // socket open error 
      return 0;

    {
      threading::MutexLock lock(mutex);
      linkManagers.push_back( linkManager );
    }

    return linkManager;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  StrongMT<IConnection> Driver::Connect( const string& url, bool useCompression )
  {
    if (url.empty())
      return StrongMT<IConnection>(0);

    StrongMT<Connection> pConnection = new Connection( settings );
    if ( useCompression )
      pConnection->EnableCompression();
    if( !pConnection->Connect( url.c_str() ) )
    {
      const int error = GetSocketError();
      error;
      // TODO: add error handling
      return StrongMT<IConnection>( 0 );
    }
    else
    {
      Instrumentation::activeConnections.AddValue( 1 );
      container.AddConnection( pConnection );
      return StrongMT<IConnection>( pConnection );
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void Driver::Step()
  {
  
    Instrumentation::counterNet_DriverStep.Start( true );
    Instrumentation::messagesReceived.AddValue( 0 );
    Instrumentation::bytesReceived.AddValue( 0 );
    Instrumentation::messagesSent.AddValue( 0 );
    Instrumentation::bytesSent.AddValue( 0 );

    container.Step();

    {
      threading::MutexLock lock(mutex);
      for (int i = 0; i < linkManagers.size(); i++)
      {
        if( linkManagers[i] )
          linkManagers[i]->Step();
      }
    }

    Instrumentation::counterNet_DriverStep.Stop();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int Driver::Process( volatile bool& isRunning )
  {
    threading::SetDebugThreadName( "Network Driver" );

    threadStarted.Set();
    while ( isRunning )
    {
      nival::sleep( settings.networkThreadSleepInterval );
      Step();
    }
    return 0;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  static ConnectionSettings extraLightTrafficSettings( 4 * 1024, 4 * 1024, 2, 1 );
  static ConnectionSettings lightTrafficSettings( 32 * 1024, 64 * 1024, 2, 1 );
  static ConnectionSettings heavyTrafficSettings( 256 * 1024, 512 * 1024, 2, 20 );

  void Driver::SetTrafficType( EDriverTrafficType::Enum value )
  {
    switch( value )
    {
    case EDriverTrafficType::ExtraLight:
      settings = extraLightTrafficSettings; 
      break;
    case EDriverTrafficType::Light:
        settings = lightTrafficSettings; 
        break;
    case EDriverTrafficType::Heavy:
      settings = heavyTrafficSettings; 
      break;
    }
    settings.pAlloc = alloc;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Driver::SetStreamAllocator( IStreamAllocator* _alloc )
  {
    alloc = _alloc;
    settings.pAlloc = alloc;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
