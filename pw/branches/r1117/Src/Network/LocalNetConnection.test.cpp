//!Component("Network/LocalNetDriver")
//!Component("System/Asserts")
#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "LocalNetDriver.h"

using namespace Network;

char testMessage[] = "abcd";

DWORD __stdcall TestThreadProc( void *pParam )
{
	Network::IConnection* pConn = (Network::IConnection*)pParam;

	int inCounter = 0;

	for ( int i = 0; i < 10; ++i )
	{
		CObj<Stream> pS1 = pConn->GetBufferToSend();
		pS1->Write( testMessage, ARRAY_SIZE( testMessage ) );
		pS1->Write( &i, 4 );
		pConn->Send( pS1 );

		CObj<Stream> pS2 = pConn->Receive();
		if ( pS2 )
		{
			char buf[128];
			pS2->Read( buf, ARRAY_SIZE( testMessage ) );
			TS_ASSERT( strcmp( buf, testMessage ) == 0 );
			int t;
			pS2->Read( &t, 4 );
			TS_ASSERT( t == inCounter );

			++inCounter;

      pConn->ReleaseReceived( pS2 );
		}
		Sleep( 3 - ( i % 2 ) );
	}

	return 0;
}

struct TestLocalNetConnection : public CxxTest::TestSuite 
{

	void TestStatus()
	{
		StrongMT<LocalNetConnection> pConn = new LocalNetConnection( 0, 0, false );
		Network::IConnection* pClientSide = pConn->GetClientEnd( Network::NetAddress( "12" ) );
		Network::IConnection* pServerSide = pConn->GetServerEnd( Network::NetAddress( "15" ) );

		//TS_ASSERT_DIFFERS( pClientSide->GetLocalAddress(), pClientSide->GetRemoteAddress() );
		//TS_ASSERT_EQUALS( pClientSide->GetLocalAddress(), pServerSide->GetRemoteAddress() );
		//TS_ASSERT_EQUALS( pServerSide->GetLocalAddress(), pClientSide->GetRemoteAddress() );

		TS_ASSERT_EQUALS( pClientSide->GetStatus(), Network::ConnectionState::Connected );
		TS_ASSERT_EQUALS( pServerSide->GetStatus(), Network::ConnectionState::Connected );

		pServerSide->AsyncClose();

		TS_ASSERT_EQUALS( pClientSide->GetStatus(), Network::ConnectionState::Closed );
	}

	void TestMessages()
	{
		StrongMT<LocalNetConnection> pConn = new LocalNetConnection( 0, 0, false );
		Network::IConnection* pClientSide = pConn->GetClientEnd( Network::NetAddress( "12" ) );
		Network::IConnection* pServerSide = pConn->GetServerEnd( Network::NetAddress( "15" ) );

		CObj<Stream> pS1 = new MemoryStream();
		char buf[] = "abcd";
		pS1->Write( buf, 5 );

		CObj<Stream> pS2 = pServerSide->Receive();
		TS_ASSERT( pS2 == 0 );

		pClientSide->Send( pS1 );
									 
		pS2 = pServerSide->Receive();
		TS_ASSERT( pS2 != 0 );
		TS_ASSERT_EQUALS( pS2->GetBuffer()[1], 'b' );
    pServerSide->ReleaseReceived( pS2 );

		for ( int i = 0; i < 5; ++i )
		{
			pS1 = pServerSide->GetBufferToSend();
			pS1->Write( &i, 4 );
			pServerSide->Send( pS1 );
      pS1 = pClientSide->GetBufferToSend();
      pS1->Write( &i, 4 );
			pClientSide->Send( pS1 );
		}

		for ( int i = 0; i < 5; ++i )
		{
			pS2 = pClientSide->Receive();
			TS_ASSERT( pS2 != 0 );
			TS_ASSERT_EQUALS( ((int*)pS2->GetBuffer())[0], i );
      pClientSide->ReleaseReceived( pS2 );
			pS2 = pServerSide->Receive();
			TS_ASSERT( pS2 != 0 );
			TS_ASSERT_EQUALS( ((int*)pS2->GetBuffer())[0], i );
      pServerSide->ReleaseReceived( pS2 );
		}

		pS2 = pClientSide->Receive();
		TS_ASSERT( pS2 == 0 );
  }

	void TestMT()
	{
		StrongMT<LocalNetConnection> pConn = new LocalNetConnection( 0, 0, false );
		Network::IConnection* pClientSide = pConn->GetClientEnd( Network::NetAddress( "12" ) );
		Network::IConnection* pServerSide = pConn->GetServerEnd( Network::NetAddress( "15" ) );

		HANDLE h1 = CreateThread( 0, 0, &TestThreadProc, (void*)pClientSide, 0, 0 );
		HANDLE h2 = CreateThread( 0, 0, &TestThreadProc, (void*)pServerSide, 0, 0 );

		TS_ASSERT_DIFFERS( WaitForSingleObject( h1, 5000 ), WAIT_TIMEOUT );
		TS_ASSERT_DIFFERS( WaitForSingleObject( h2, 5000 ), WAIT_TIMEOUT );
	}

	void TestNetDriver()
	{
		StrongMT<Network::LocalNetDriver> pD = new LocalNetDriver();
    
		Network::IConnectionsManager* pListener1 = pD->CreateConnectionListener( Network::NetAddress( "345" ) );

		Network::IConnection* pC1 = pD->Connect( Network::NetAddress( "345" ) );
		TS_ASSERT_EQUALS( pC1->GetStatus(), Network::ConnectionState::Connected );

		Network::IConnection* pC2 = pD->Connect( Network::NetAddress( "456" ) );
		TS_ASSERT_EQUALS( pC2->GetStatus(), Network::ConnectionState::Closed );

    Network::TNewConnections temp;
		pListener1->GetNewConnections( temp );
		TS_ASSERT_EQUALS( temp.size(), 1 );

		Network::IConnectionsManager* pListener2 = pD->CreateConnectionListener( Network::NetAddress( "456" ) );
		pC2 = pD->Connect( Network::NetAddress( "456" ) );
		TS_ASSERT_EQUALS( pC2->GetStatus(), Network::ConnectionState::Connected );


		char buf1[] = "abcde";
		char buf2[] = "fghd";
		CObj<Stream> pS1 = new MemoryStream();
		pS1->Write( buf1, ARRAY_SIZE( buf1 ) );
		CObj<Stream> pS2 = new MemoryStream();
		pS2->Write( buf2, ARRAY_SIZE( buf2 ) );

		pC1->Send( pS1 );

		Network::IConnection* pRConn1 = pListener1->GetConnections()[0];
		CObj<Stream> pR1 = pRConn1->Receive();

		TS_ASSERT( pR1 != 0 );
		TS_ASSERT_EQUALS( pR1->GetSize(), pS1->GetSize() );
    pRConn1->ReleaseReceived( pR1 );

		pListener2->GetConnections()[0]->Send( pS2 );
		pR1 = pC2->Receive();

		TS_ASSERT( pR1 != 0 );
		TS_ASSERT_EQUALS( pR1->GetSize(), pS2->GetSize() );
    pC2->ReleaseReceived( pR1 );
	}

	void TestLocalHostConnection()
	{
		StrongMT<Network::INetworkDriver> pD = new LocalNetDriver();

		pD->CreateConnectionListener( Network::NetAddress( "345" ) );

		Network::IConnection* pC1 = pD->Connect( Network::NetAddress( "localhost:345" ) );
		TS_ASSERT_EQUALS( pC1->GetStatus(), Network::ConnectionState::Connected );
	}

	void TestPingEmulation()
	{
		StrongMT<Network::LocalNetDriver> pD = new LocalNetDriver();

		Network::IConnectionsManager* pListener1 = pD->CreateConnectionListener( Network::NetAddress( "345" ) );

		pD->SetNewConnectionsLatency( 100 );
		Network::IConnection* pC1 = pD->Connect( Network::NetAddress( "345" ) );

    Network::TNewConnections newConnections;
    pListener1->GetNewConnections( newConnections );
		Network::IConnection* pS1 = newConnections[0];

		char buf1[] = "abcde";
		CObj<Stream> pS = new MemoryStream();
		pS->Write( buf1, ARRAY_SIZE( buf1 ) );
		CObj<Stream> pR1;

		pC1->Send( pS );
		Sleep( 50 );
		pR1 = pS1->Receive();
		TS_ASSERT( pR1 == 0 );
		Sleep( 70 );
		pR1 = pS1->Receive();
		TS_ASSERT( pR1 != 0 );
    pS1->ReleaseReceived( pR1 );

		pS1->Send( pS );
		Sleep( 50 );
		pR1 = pC1->Receive();
		TS_ASSERT( pR1 == 0 );
		Sleep( 70 );
		pR1 = pC1->Receive();
		TS_ASSERT( pR1 != 0 );
    pC1->ReleaseReceived( pR1 );

		pD->SetNewConnectionsLatency( 20 );

		Network::IConnection* pC2 = pD->Connect( Network::NetAddress( "345" ) );
    Network::TNewConnections newConnections2;
    pListener1->GetNewConnections( newConnections2 );
		Network::IConnection* pS2 = newConnections2[0];

 		pS1->Send( pS );
		pS2->Send( pS );
		Sleep( 50 );
		pR1 = pC1->Receive();
		TS_ASSERT( pR1 == 0 );
		pR1 = pC2->Receive();
		TS_ASSERT( pR1 != 0 );
    pC2->ReleaseReceived( pR1 );
		Sleep( 70 );
		pR1 = pC1->Receive();
		TS_ASSERT( pR1 != 0 );
    pC1->ReleaseReceived( pR1 );

		pD->SetOpenConnectionsLatency( 30 );
		pS1->Send( pS );
		pS2->Send( pS );
		Sleep( 10 );
		pR1 = pC1->Receive();
		TS_ASSERT( pR1 == 0 );
		pR1 = pC2->Receive();
		TS_ASSERT( pR1 == 0 );
		Sleep( 30 );
		pR1 = pC1->Receive();
		TS_ASSERT( pR1 != 0 );
    pC1->ReleaseReceived( pR1 );
		pR1 = pC2->Receive();
		TS_ASSERT( pR1 != 0 );
    pC2->ReleaseReceived( pR1 );
	}

  void TestConnectLatency()
  {
    StrongMT<Network::LocalNetDriver> pD = new LocalNetDriver();
    pD->SetConnectDelay( 100 );

    Network::IConnectionsManager* pListener1 = pD->CreateConnectionListener( Network::NetAddress( "345" ) );
    vector<StrongMT<Network::IConnection>> temp;

    StrongMT<Network::IConnection> pC1 = pD->Connect( Network::NetAddress( "345" ) );
    Network::TNewConnections newConnections;
    TS_ASSERT_EQUALS( pC1->GetStatus(), Network::ConnectionState::Connecting );
    pListener1->GetNewConnections( newConnections );
    TS_ASSERT_EQUALS( newConnections.size(), 0 );

    Sleep(120);
    TS_ASSERT_EQUALS( pC1->GetStatus(), Network::ConnectionState::Connected );
    pListener1->GetNewConnections( newConnections );
    TS_ASSERT_EQUALS( newConnections.size(), 1 );
    TS_ASSERT_EQUALS( newConnections[0]->GetStatus(), Network::ConnectionState::Connected ); 

  }

  void TestConnectionDisabling()
  {
    StrongMT<Network::LocalNetDriver> pD = new LocalNetDriver();
    pD->SetConnectDelay( 50 );

    StrongMT<Network::IConnectionsManager> pListener1 = pD->CreateConnectionListener( Network::NetAddress( "345" ) );
    StrongMT<Network::IConnectionsManager> pListener2 = pD->CreateConnectionListener( Network::NetAddress( "678" ) );
    
    pD->EnableConnectionToListener( Network::NetAddress( "678" ), false );

    StrongMT<Network::IConnection> pC1 = pD->Connect( Network::NetAddress( "345" ) );
    TS_ASSERT_EQUALS( pC1->GetStatus(), Network::ConnectionState::Connecting );

    StrongMT<Network::IConnection> pC2 = pD->Connect( Network::NetAddress( "678" ) );
    TS_ASSERT_EQUALS( pC2->GetStatus(), Network::ConnectionState::Connecting );
    Sleep( 100 );

    Network::TNewConnections newConnections1;
    Network::TNewConnections newConnections2;

    TS_ASSERT_EQUALS( pC1->GetStatus(), Network::ConnectionState::Connected );
    pListener1->GetNewConnections( newConnections1 );
    TS_ASSERT_EQUALS( newConnections1.size(), 1 );
    TS_ASSERT_EQUALS( pC2->GetStatus(), Network::ConnectionState::Closed );
    pListener2->GetNewConnections( newConnections2 );
    TS_ASSERT_EQUALS( newConnections2.size(), 0 );

    pD->EnableConnectionToListener( Network::NetAddress( "678" ), true );
    pD->EnableConnectionToListener( Network::NetAddress( "345" ), false );

    TS_ASSERT_EQUALS( pC1->GetStatus(), Network::ConnectionState::Connected );
    TS_ASSERT_EQUALS( pC2->GetStatus(), Network::ConnectionState::Closed );

    pD->SetConnectDelay( 0 );

    StrongMT<Network::IConnection> pC3 = pD->Connect( Network::NetAddress( "345" ) );
    StrongMT<Network::IConnection> pC4 = pD->Connect( Network::NetAddress( "678" ) );
    TS_ASSERT_EQUALS( pC3->GetStatus(), Network::ConnectionState::Closed );
    TS_ASSERT_EQUALS( pC4->GetStatus(), Network::ConnectionState::Connected );
  }

#define WAIT( X )                         \
  { int guard = 100;                        \
  while( !(X) && --guard > 0 ) Sleep(10); \
  }

};
