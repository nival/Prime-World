//!Component( "Network/RealDriver" )
//!Component( "Network/FreePortsFinder" )
//!Component( "System/Timer" )
//!Component( "System/Dumpers" )
//!Component( "Network/StreamAllocator" )

#include <cxxtest/TestSuite.h>
#include <Ws2spi.h>
#include "stdafx.h"
#include "Initializer.h"
#include "Connection.h"
#include "Address.h"
#include "FreePortsFinder.h"
#include "DriverSettings.h"
#include "StreamAllocator.h"

#include "System/HPTimer.h"


#define WAIT( X )                         \
{ int guard = 100;                        \
  while( !(X) && --guard > 0 ) Sleep(10); \
}

static void DrWebBugWorkAround()
{
  HMODULE hdrweb = NULL;
  do
  {
    hdrweb = GetModuleHandle("drwebsp.dll");
    if(hdrweb)
    {
      FreeLibrary(hdrweb);
      //give them time to wrap up
      Sleep(10);
    }
  }
  while(hdrweb != NULL);
}

  static const char *pPublicKey =
    "-----BEGIN PUBLIC KEY-----\n\
TEST PUBLIC\n\
-----END PUBLIC KEY-----\n";
  static const char *pPrivateKey =
    "-----BEGIN RSA PRIVATE KEY-----\n\
TEST\n\
-----END RSA PRIVATE KEY-----\n";

struct NetworkSuite : public CxxTest::TestSuite 
{
	Network::INetworkDriver* pServerDriver;
	Network::INetworkDriver* pClientDriver;

	StrongMT<Network::IConnectionsManager> pIncommingConnections;
	StrongMT<Network::IConnection> pClientConnection;
	StrongMT<Network::IConnection> pServerConnection;	

	int port;
	char serverAddress[16];
	char* portPointer;




	NetworkSuite() : port( 12008 ), portPointer( serverAddress + 10 )
	{
		const char* address = "127.0.0.1:12000";
		::memcpy( serverAddress, address, strlen( address ) );
	}

  void EnumThreads( nstl::vector<DWORD>& threadIds )
  {
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (h != INVALID_HANDLE_VALUE) 
    {
      THREADENTRY32 te;
      te.dwSize = sizeof(te);
      if (Thread32First(h, &te)) 
      {
        do 
        {
          if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(te.th32OwnerProcessID)) 
          {
            if ( te.th32OwnerProcessID == GetCurrentProcessId() )
            {
              threadIds.push_back(te.th32ThreadID);
            }
          }
          te.dwSize = sizeof(te);
        } while (Thread32Next(h, &te));
      }
      CloseHandle(h);
    }
  }
	virtual void setUp() 
	{
    //remember thread list on start up
    nstl::vector<DWORD> threadList;
    EnumThreads(threadList);
    TS_ASSERT(threadList.size() <= 2);
		pServerDriver = Network::Initialize();
		pClientDriver = Network::Initialize();

    pServerDriver->SetStreamAllocator( new Network::MockStreamAllocator() );
    pClientDriver->SetStreamAllocator( new Network::MockStreamAllocator() );

    _itoa_s( port++, portPointer, 6, 10 );
    pIncommingConnections = pServerDriver->CreateConnectionListener( serverAddress, false );
    TS_ASSERT( IsValid( pIncommingConnections ) );

    CreateConnectionsPair();

	}
  void CreateConnectionsPair() 
  {
    if ( pClientConnection )
      pClientConnection->AsyncClose();
    if ( pServerConnection )
      pServerConnection->AsyncClose();

    pClientConnection = pClientDriver->Connect( serverAddress, false );
    TS_ASSERT( IsValid( pClientConnection ) );

    Network::TNewConnections connections;
    { 
      int guard = 100;

      while ( connections.empty() && --guard > 0 )
      {
        pIncommingConnections->GetNewConnections( connections );
        Sleep( 10 );
      }
    }

    if( !connections.empty() )
      pServerConnection = connections.front();
  }

	virtual void tearDown()
	{
		pIncommingConnections = 0;
		pClientConnection->AsyncClose();
    pServerConnection->AsyncClose();		
    pClientConnection = 0;
		pServerConnection = 0;		

		delete pServerDriver;
		pServerDriver = 0;
		delete pClientDriver;
		pClientDriver = 0;

    DrWebBugWorkAround();
	}

  
  void TestStreamAllocator()
  {
    const char* data = "0123456789";
    Network::MockStreamAllocator* sh1 = new Network::MockStreamAllocator();
    Network::MockStreamAllocator* sh2 = new Network::MockStreamAllocator();

    pServerDriver->SetStreamAllocator( sh1 );
    pClientDriver->SetStreamAllocator( sh2 );

    _itoa_s( port++, portPointer, 6, 10 );
    pIncommingConnections = pServerDriver->CreateConnectionListener( serverAddress, false );
    TS_ASSERT( IsValid( pIncommingConnections ) );

    CreateConnectionsPair();

    CObj<Stream> pSentStream = pClientConnection->GetBufferToSend();
    TS_ASSERT_EQUALS( sh2->streamsInUse.size(), 1 );
    pSentStream->Write( data, ::strlen( data ) );
    pClientConnection->Send( pSentStream );
    TS_ASSERT_EQUALS( sh2->streamsInUse.size(), 1 ); //?

    CObj<Stream> pReceivedStream;
    WAIT( (pReceivedStream = pServerConnection->Receive()) != 0 )
    TS_ASSERT( pReceivedStream );
    TS_ASSERT_EQUALS( sh2->streamsInUse.size(), 0 );
    TS_ASSERT_EQUALS( sh1->streamsInUse.size(), 1 );
    pServerConnection->ReleaseReceived( pReceivedStream );
    TS_ASSERT_EQUALS( sh1->streamsInUse.size(), 0 );
  }

  void TestStreamAllocator2()
  {
    const char* data = "0123456789";
    Network::StreamAllocator* sh1 = new Network::StreamAllocator();
    Network::StreamAllocator* sh2 = new Network::StreamAllocator();
    pServerDriver->SetStreamAllocator( sh1 );
    pClientDriver->SetStreamAllocator( sh2 );

    _itoa_s( port++, portPointer, 6, 10 );
    pIncommingConnections = pServerDriver->CreateConnectionListener( serverAddress, false );
    TS_ASSERT( IsValid( pIncommingConnections ) );

    CreateConnectionsPair();

    CObj<Stream> pSentStream = pClientConnection->GetBufferToSend();
    //TS_ASSERT_EQUALS( sh2->streamsInUse.size(), 1 );
    pSentStream->Write( data, ::strlen( data ) );
    pClientConnection->Send( pSentStream );
    //TS_ASSERT_EQUALS( sh2->streamsInUse.size(), 1 ); //?

    CObj<Stream> pReceivedStream;
    WAIT( (pReceivedStream = pServerConnection->Receive()) != 0 )
      TS_ASSERT( pReceivedStream );
    //TS_ASSERT_EQUALS( sh2->streamsInUse.size(), 0 );
    //TS_ASSERT_EQUALS( sh1->streamsInUse.size(), 1 );
    pServerConnection->ReleaseReceived( pReceivedStream );
    //TS_ASSERT_EQUALS( sh1->streamsInUse.size(), 0 );
  }

	void testSetAddress()
	{
		const char port[] = "16000";		
		StrongMT<Network::IConnectionsManager> pIncommingConnections = pServerDriver->CreateConnectionListener( port );
		TS_ASSERT( IsValid( pIncommingConnections ) );

		StrongMT<Network::IConnection> pClientConnection = pClientDriver->Connect( ( string( "127.0.0.1:" ) + port ).c_str() );
		TS_ASSERT( IsValid( pClientConnection ) );
		TS_ASSERT( pServerConnection->GetStatus() == Network::ConnectionState::Connected );

		Sleep( 200 );

    Network::TNewConnections connections;
    pIncommingConnections->GetNewConnections( connections );
		TS_ASSERT( !connections.empty() );
	}

	void testDriverInitialization()
	{
		TS_ASSERT( pServerDriver );
		TS_ASSERT( pClientDriver );
		TS_ASSERT( pServerConnection );
		TS_ASSERT( pClientConnection );
		TS_ASSERT( pServerConnection->GetStatus() == Network::ConnectionState::Connected );
		TS_ASSERT( pClientConnection->GetStatus() == Network::ConnectionState::Connected );
	}

	void testSendingData()
	{
    const char* data = "0123456789";
    const char* data2 = "abdcvfthfdabdcvfthfd";

		// send data
		CObj<Stream> pSentStream = pClientConnection->GetBufferToSend();
		pSentStream->Write( data, ::strlen( data ) );
    //int m1 = GetMallocs();
		TS_ASSERT( pClientConnection->Send( pSentStream ) );

    pSentStream = pClientConnection->GetBufferToSend();
    pSentStream->Write( data2, ::strlen( data2 ) );
    TS_ASSERT( pClientConnection->Send( pSentStream ) );

		// receive data
    CObj<Stream> pReceivedStream;
    while( !(pReceivedStream = pServerConnection->Receive()) )
      Sleep( 10 );
		TS_ASSERT( IsValid( pReceivedStream ) && !memcmp( data, pReceivedStream->GetBuffer(), pReceivedStream->GetSize() ) );
    pServerConnection->ReleaseReceived( pReceivedStream );

    while( !(pReceivedStream = pServerConnection->Receive()) )
      Sleep( 10 );
    TS_ASSERT( IsValid( pReceivedStream ) && !memcmp( data2, pReceivedStream->GetBuffer(), pReceivedStream->GetSize() ) );
    pServerConnection->ReleaseReceived( pReceivedStream );
    //int m4 = GetMallocs();
    //___TS_ASSERT_EQUALS(__FILE__,__LINE__, m1, m4, "Mallocs in network driver!" )
	}

  void TestLargeMessage()
  {
    CObj<Stream> pSentStream = pClientConnection->GetBufferToSend();
    const char* data = "0123456789";

    //int m1 = GetMallocs();

    pSentStream->Write( data, ::strlen( data ) );
    TS_ASSERT( pClientConnection->Send( pSentStream ) );

    pSentStream = pClientConnection->GetBufferToSend();
    pSentStream->SetSize( 50000 );
    for ( int i = 1; i < 5000; ++i )
      pSentStream->Write( data, ::strlen( data ) );
    TS_ASSERT( pClientConnection->Send( pSentStream ) );

    pSentStream = pClientConnection->GetBufferToSend();
    pSentStream->Write( data, ::strlen( data ) );
    TS_ASSERT( pClientConnection->Send( pSentStream ) );

    //int m2 = GetMallocs();
    //___TS_ASSERT_EQUALS(__FILE__,__LINE__, m1 + 4, m2, "Mallocs in network driver!" )

    Sleep(100);
    // receive data
    CObj<Stream> pReceivedStream;

    while( !(pReceivedStream = pServerConnection->Receive()) )
      Sleep( 10 );
    TS_ASSERT_EQUALS( pReceivedStream->GetSize(), 10 )
    TS_ASSERT( !memcmp( data, pReceivedStream->GetBuffer(), 10 ) );
    pServerConnection->ReleaseReceived( pReceivedStream );

    while( !(pReceivedStream = pServerConnection->Receive()) )
      Sleep( 10 );
    TS_ASSERT_EQUALS( pReceivedStream->GetSize(), 50000 )
    TS_ASSERT( !memcmp( data, pReceivedStream->GetBuffer(), 10 ) );
    pServerConnection->ReleaseReceived( pReceivedStream );

    while( !(pReceivedStream = pServerConnection->Receive()) )
      Sleep( 10 );
    TS_ASSERT_EQUALS( pReceivedStream->GetSize(), 10 )
      TS_ASSERT( !memcmp( data, pReceivedStream->GetBuffer(), 10 ) );
    pServerConnection->ReleaseReceived( pReceivedStream );

    //int m4 = GetMallocs();
    //___TS_ASSERT_EQUALS(__FILE__,__LINE__, m1 + 5, m4, "Mallocs in network driver!" )
  }

  void testClose()
	{
    //pIncommingConnections = pServerDriver->CreateConnectionListener( serverAddress, false );

    StrongMT<Network::IConnection> pClientConnection1 = pClientDriver->Connect( serverAddress );
    TS_ASSERT( IsValid( pClientConnection1 ) );

    while( pClientConnection1->GetStatus() == Network::ConnectionState::Connecting )
      Sleep( 5 );
    TS_ASSERT_EQUALS( pClientConnection1->GetStatus(), Network::ConnectionState::Connected ); 

    Network::TNewConnections connections;
    while ( connections.empty() )
    {
      pIncommingConnections->GetNewConnections( connections );
    }

    StrongMT<Network::IConnection> pServerConnection1 = connections[0];
    connections.clear();



    StrongMT<Network::IConnection> pClientConnection2 = pClientDriver->Connect( serverAddress );
    TS_ASSERT( IsValid( pClientConnection2 ) );

    while( pClientConnection2->GetStatus() == Network::ConnectionState::Connecting )
      Sleep( 5 );
		TS_ASSERT_EQUALS( pClientConnection2->GetStatus(), Network::ConnectionState::Connected ); 

    while ( connections.empty() )
      pIncommingConnections->GetNewConnections( connections );
		StrongMT<Network::IConnection> pServerConnection2 = connections[0];
    connections.clear();

    TS_ASSERT_DIFFERS( pServerConnection1->GetStatus(), Network::ConnectionState::Closed ); 
    TS_ASSERT_DIFFERS( pServerConnection2->GetStatus(), Network::ConnectionState::Closed ); 

		// close client2 connection
		pServerConnection2->AsyncClose();
    while( pClientConnection2->GetStatus() != Network::ConnectionState::Closed )
      Sleep(5);

    TS_ASSERT_DIFFERS( pClientConnection1->GetStatus(), Network::ConnectionState::Closed ); 
    TS_ASSERT_DIFFERS( pServerConnection1->GetStatus(), Network::ConnectionState::Closed ); 
    TS_ASSERT_EQUALS( pClientConnection2->GetStatus(), Network::ConnectionState::Closed ); 
    TS_ASSERT_EQUALS( pServerConnection2->GetStatus(), Network::ConnectionState::Closed ); 
    pClientConnection1->AsyncClose();
    pServerConnection1->AsyncClose();
 	}

  void SendReceiveLargeMessage( bool useCompression, int testNo )
  {
    _itoa_s( port++, portPointer, 6, 10 );
    StrongMT<Network::IConnectionsManager> pIncommingConnections = pServerDriver->CreateConnectionListener( serverAddress, useCompression );

    StrongMT<Network::IConnection> pClientConnection = pClientDriver->Connect( serverAddress, useCompression );

    Network::TNewConnections connections;
    { 
      int guard = 100;

      while ( connections.empty() && --guard > 0 )
      {
        pIncommingConnections->GetNewConnections( connections );
        Sleep( 10 );
      }
    }

    StrongMT<Network::IConnection> pServerConnection = connections.front();

    CObj<Stream> pBaseStream = new MemoryStream();
    const char* data = "0123456789";
    pBaseStream->SetSize( 50000 );
    for ( int i = 1; i < 5000; ++i )
    {
      pBaseStream->Write( data, ::strlen( data ) );
    }

    if ( testNo == 1 )
    {
      for( int i = 0; i < 10; ++i )
      {
        int guard;
        CObj<Stream> pReceivedStream;

        CObj<Stream> pSentStream = pClientConnection->GetBufferToSend();
        pBaseStream->Seek( 0, SEEKORIGIN_BEGIN );
        pSentStream->CopyFrom( pBaseStream );
        pClientConnection->Send( pSentStream );
        guard = 100;
        while( !(pReceivedStream = pServerConnection->Receive() ) && --guard > 0 )
          Sleep( 10 );

        TS_ASSERT( pReceivedStream );
        TS_ASSERT_EQUALS( pReceivedStream->GetSize(), 50000 );
        TS_ASSERT( !memcmp( data, pReceivedStream->GetBuffer(), 10 ) );
        pServerConnection->ReleaseReceived( pReceivedStream );

        pSentStream = pServerConnection->GetBufferToSend();
        pBaseStream->Seek( 0, SEEKORIGIN_BEGIN );
        pSentStream->CopyFrom( pBaseStream );
        pServerConnection->Send( pSentStream );
        guard = 100;
        while( !(pReceivedStream = pClientConnection->Receive()) && --guard > 0 )
          Sleep( 10 );
        TS_ASSERT( pReceivedStream );
        TS_ASSERT_EQUALS( pReceivedStream->GetSize(), 50000 );
        TS_ASSERT( !memcmp( data, pReceivedStream->GetBuffer(), 10 ) );
        pClientConnection->ReleaseReceived( pReceivedStream );
      }

    }
    else if ( testNo == 2 )
    {
      for( int i = 0; i < 10; ++i )
      {
        CObj<Stream> pSentStream = pClientConnection->GetBufferToSend();
        pBaseStream->Seek( 0, SEEKORIGIN_BEGIN );
        pSentStream->CopyFrom( pBaseStream );
        pClientConnection->Send( pSentStream );
      }
      for( int i = 0; i < 10; ++i )
      {
        int guard;
        CObj<Stream> pReceivedStream;

        guard = 100;
        while( !(pReceivedStream = pServerConnection->Receive() ) && --guard > 0 )
          Sleep( 10 );

        TS_ASSERT( pReceivedStream );
        TS_ASSERT_EQUALS( pReceivedStream->GetSize(), 50000 );
        TS_ASSERT( !memcmp( data, pReceivedStream->GetBuffer(), 10 ) );
        pServerConnection->ReleaseReceived( pReceivedStream );
      }
    }

    pServerConnection->AsyncClose();
    pClientConnection->AsyncClose();
  }


  void TestCompression1()
  {
    int sentBefore = Network::Instrumentation::bytesSent.GetTotal();
    SendReceiveLargeMessage( false, 1 );
    int sentAfter = Network::Instrumentation::bytesSent.GetTotal();

    TS_ASSERT_DELTA( sentAfter - sentBefore, 1000000, 100 );

    int sentBefore2 = Network::Instrumentation::bytesSent.GetTotal();
    SendReceiveLargeMessage( true, 1 );
    int sentAfter2 = Network::Instrumentation::bytesSent.GetTotal();

    TS_ASSERT_LESS_THAN( sentAfter2 - sentBefore2, 3000 );
  }

  void TestCompression2()
  {
   int sentBefore = Network::Instrumentation::bytesSent.GetTotal();
    SendReceiveLargeMessage( false, 2 );
    int sentAfter = Network::Instrumentation::bytesSent.GetTotal();

    TS_ASSERT_DELTA( sentAfter - sentBefore, 500000, 100 );

    int sentBefore2 = Network::Instrumentation::bytesSent.GetTotal();
    SendReceiveLargeMessage( true, 2 );
    int sentAfter2 = Network::Instrumentation::bytesSent.GetTotal();

    TS_ASSERT_DELTA( sentAfter2 - sentBefore2, 1330, 100 );
  }

  void testDriversStress()
	{
    static const char testMessage[] = "abcd";

		struct STestDriver
		{
			Network::INetworkDriver* pDriver;
			StrongMT<Network::IConnectionsManager> pManager;
			StrongMT<Network::IConnection> pConn1;
			StrongMT<Network::IConnection> pConn2;
		};

		const int THREADS = 40;
		STestDriver drivers[THREADS];

		int basePort = port;
		port += THREADS;
		for( int i = 0; i < THREADS; ++i )
		{
			drivers[i].pDriver = Network::Initialize();
			char buf[128];
			sprintf_s( buf, "127.0.0.1:%d", basePort + i );
			drivers[i].pManager = drivers[i].pDriver->CreateConnectionListener( buf );
		}
		Sleep( 200 );
		for( int i = 0; i < THREADS; ++i )
		{
			char buf[128];
			sprintf_s( buf, "127.0.0.1:%d", basePort + i );
			drivers[i].pConn1 = drivers[i].pDriver->Connect( buf );
		}
		Sleep( 200 );
		for( int i = 0; i < THREADS; ++i )
    {
      Network::TNewConnections temp;
      { 
        int guard = 100;

        while ( temp.empty() && --guard > 0 )
        {
          drivers[i].pManager->GetNewConnections( temp );
          Sleep( 10 );
        }
      }

      drivers[i].pConn2 = temp[0];
		}

    NHPTimer::STime startTime;
    NHPTimer::GetTime( startTime );

		for ( int cycle = 0; cycle < 30; ++ cycle )
		{
			for( int i = 0; i < THREADS; ++i )
			{
        for( int round = 0; round < 4; ++round )
        {
          CObj<Stream> pS1 = drivers[i].pConn1->GetBufferToSend();
          pS1->Write( &i, 4 );
          pS1->Write( &cycle, 4 );
          pS1->Write( testMessage, ARRAY_SIZE( testMessage ) );
          drivers[i].pConn1->Send( pS1 );
        }
			}
			int nRcv = 0;
      int nRcvAttempts = 0;
      Sleep(10);
			while( nRcv < THREADS * 4 )
			{
				for( int i = 0; i < THREADS; ++i )
				{
					CObj<Stream> pS2 = drivers[i].pConn2->Receive();
          ++nRcvAttempts;
					if ( pS2 )
					{
						int _i, _cycle;
						pS2->Read( &_i, 4 );
						pS2->Read( &_cycle, 4 );
						TS_ASSERT_EQUALS( _i, i );
						TS_ASSERT_EQUALS( _cycle, cycle );
						++nRcv;
            drivers[i].pConn2->ReleaseReceived( pS2 );
					}
				}
				Sleep(0);
			}
      nRcvAttempts += nRcv;

			Sleep( 3 - cycle % 2 + 10 / nRcvAttempts );
		}

    double time = NHPTimer::GetTimePassedAndUpdateTime( startTime );

    systemLog( NLogg::LEVEL_DEBUG ) << "Time passed: " << time << " seconds "<< endl;
		for( int i = 0; i < THREADS; ++i )
		{
			delete drivers[i].pDriver;
			drivers[i].pDriver = 0;
			drivers[i].pManager = 0;
		}
	} 

  void TestAsyncConnect()
  {
    Network::SetConnectTimeout( 5000 );

    _itoa_s( port++, portPointer, 6, 10 );

    Network::ConnectionListener listener( serverAddress );

    pClientConnection = pClientDriver->Connect( serverAddress );
    TS_ASSERT_EQUALS( pClientConnection->GetStatus(), Network::ConnectionState::Connecting );
    Sleep(500);
    TS_ASSERT_EQUALS( pClientConnection->GetStatus(), Network::ConnectionState::Connecting );
    listener.Listen();
    Network::Address addr;
    SOCKET sock = listener.Accept( &addr );
    while ( ( sock = listener.Accept( &addr )) == INVALID_SOCKET )
      Sleep(10);

    WAIT( pClientConnection->GetStatus() == Network::ConnectionState::Connected );
    TS_ASSERT_EQUALS( pClientConnection->GetStatus(), Network::ConnectionState::Connected );
  }

  void TestConnectTimeout()
  {
    Network::SetConnectTimeout( 200 );

    _itoa_s( port++, portPointer, 6, 10 );

    Network::ConnectionListener listener( serverAddress );

    pClientConnection = pClientDriver->Connect( serverAddress );
    TS_ASSERT_EQUALS( pClientConnection->GetStatus(), Network::ConnectionState::Connecting );
    Sleep(500);
    TS_ASSERT_EQUALS( pClientConnection->GetStatus(), Network::ConnectionState::Closed );

    Network::SetConnectTimeout( 10000 );
  }
};

struct FreePortsFinderTest : public CxxTest::TestSuite 
{
  virtual void tearDown()
  {
    DrWebBugWorkAround();
  }

  void testFinder()
  {
    StrongMT<Network::INetworkDriver> pServerDriver = Network::Initialize();

    StrongMT<Network::IFreePortsFinder>  finder = Network::NewFreePortsFinder( 35000 );

    char serverAddress[16];

    int port1 = finder->GetFreePort();

    _itoa_s( port1, serverAddress, 10 );
    StrongMT<Network::IConnectionsManager> con1 = pServerDriver->CreateConnectionListener( serverAddress );
    TS_ASSERT( con1 != 0 );

    int port2 = finder->GetFreePort();
    TS_ASSERT_DIFFERS( port1, port2 );

     _itoa_s( port2, serverAddress, 10 );
    StrongMT<Network::IConnectionsManager> con2 = pServerDriver->CreateConnectionListener( serverAddress );
    TS_ASSERT( con2 != 0 );

    _itoa_s( port2 + 1, serverAddress, 10 );
    StrongMT<Network::IConnectionsManager> con3 = pServerDriver->CreateConnectionListener( serverAddress );
    TS_ASSERT( con3 != 0 );

    int port3 = finder->GetFreePort();
    TS_ASSERT_DIFFERS( port2, port3 );
    TS_ASSERT_DIFFERS( port2 + 1, port3 );

    _itoa_s( port3 + 1, serverAddress, 10 );
    StrongMT<Network::IConnectionsManager> con4 = pServerDriver->CreateConnectionListener( serverAddress );
    TS_ASSERT( con4 != 0 );
  }
};



