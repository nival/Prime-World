#include "stdafx.h"

#include <conio.h> 

#include "System/StdOutDumper.h"
#include "System/TextFileDumper.h"
#include "System/CmdLine.h"
#include "System/Logger.h"
#include "System/TimeUtils.h"

#include "Network/Network.h"
#include "Network/Initializer.h"
#include "Network/TransportSystem.h"
#include "Network/TransportInitializer.h"
#include "Network/AddressTranslator.h"
#include "Network/FreePortsFinder.h"
#include "Network/ClientTransportSystem.h"
#include "Network/PeerDiscoverer/PeerDiscoverer.h"
#include "Network/LowLevelPinger/Pinger.h"

#include "TestEcho/TestEchoClient.h"

struct SConfiguration
{
  bool directConnect;
  string serverAddr;
  string login;
  string password;
  int delay;

  int id;
  int numClients;
  string myIp;

  SConfiguration() : directConnect(false), serverAddr("SITE.com:35001"), login("a"), delay(100), id(0), numClients(-1) {}  
};


struct TestEchoClientRunner : public TestEcho::ITestEchoClientP2PCallback
{
  CPtr<Network::INetworkDriver> networkDriver;
  SConfiguration conf;
  NLogg::CLoggerStream& logger;
  vector<pair<int, Transport::IChannel*>> channels;
  CObj<LowLevelPinger::Pinger> lowLevelPinger;

  TestEchoClientRunner& operator=( const TestEchoClientRunner& ) {}

  virtual void PeersReceived( const vector<TestEcho::SPeerInfo>& peers )
  {
    for ( int i = 0; i < peers.size(); ++i )
    {
      lowLevelPinger->ConnectTo( peers[i].userId, peers[i].directPingIp.c_str() );
    }
  }

  virtual void StartP2PTest( const vector<pair<int, Transport::IChannel*>>& _channels )
  {
    channels = _channels;
  }

  TestEchoClientRunner( Network::INetworkDriver* _networkDriver, const SConfiguration& _conf, NLogg::CLoggerStream& _logger ) : networkDriver(_networkDriver), conf(_conf), logger(_logger)  {}

  int Process( const bool& isRunning )
  {
    CObj<Transport::ClientTransportSystem> csystem;
    CObj<Transport::ITransportSystem> transport;
    CObj<Transport::IChannel> chan;
    CObj<TestEcho::TestEchoClient> client;

    int userId = conf.id;
    if ( !conf.directConnect )
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "Connecting to login server " << conf.serverAddr << "..." << endl;

      csystem = new Transport::ClientTransportSystem( networkDriver, Transport::GetGlobalMessageFactory(), Network::GetFreePortsFinder() );

      systemLog(NLogg::LEVEL_MESSAGE) << "Logging to server..." << endl;
      csystem->Login( conf.serverAddr, conf.login, conf.password, 0 );

      while( csystem->GetLoginResult() == Login::ELoginResult::NoResult )
      {
        Sleep(1);
      }
      if ( csystem->GetLoginResult() != Login::ELoginResult::Success )
      {
        systemLog(NLogg::LEVEL_MESSAGE) << "Could not log on. Exiting." << endl;
        return 1;
      }
      csystem->GetPeerDiscoverer()->SetMaxOptionalConnections( 0 );
      userId = csystem->GetUserId();

      chan = csystem->OpenChannel( TestEcho::serviceId );
    }
    else
    {
      Transport::DummyAddressResolver myAddrResolver( conf.serverAddr );

      systemLog( NLogg::LEVEL_MESSAGE ) << "Connecting to " << conf.serverAddr << "..." << endl;

      transport = Transport::CreateTransportSystem( networkDriver, Transport::GetGlobalMessageFactory(), &myAddrResolver );
      chan = transport->OpenChannel( Transport::Address( TestEcho::serviceId, userId ) ,"" );
    }

    client = new TestEcho::TestEchoClient( chan );

    while ( !client->IsConnected() && isRunning )
    {
      client->Step();
      Sleep(1);
    }

    lowLevelPinger = new LowLevelPinger::Pinger( 500, userId, "LowPing" );
    string directIp = Network::GetHostIPByName( "localhost" );
    directIp += ":" + NStr::IntToStr( lowLevelPinger->GetListenPort() ); 

    Transport::DummyAddressResolver r("");
    client->InitP2PTest( Transport::CreateTransportSystem( networkDriver, Transport::GetGlobalMessageFactory(), &r ), conf.myIp, directIp, this );
    
    systemLog( NLogg::LEVEL_MESSAGE ) << "Logged in." << endl;

    if ( conf.numClients > 0  )
    {
      while( client->GetP2PTestConnectedCount() < conf.numClients && isRunning )
      {
        client->Step();
        Sleep( 100 );
      }

      if ( !isRunning )
        return 1;

      systemLog( NLogg::LEVEL_MESSAGE ) << "All peers connected. Starting..." << endl;
      client->GetServer()->StartTest();
    }

    while ( channels.empty() && isRunning )
    {
      client->Step();
      Sleep( 10 );
    }

    systemLog( NLogg::LEVEL_MESSAGE ) << "Peer connections established." << endl;

    GetLagLog().Start( "LowPing" );
    GetLagLog().Start( "P2PLag" );
    
    logger << conf.myIp << endl;
    logger <<  "time,";
    for( int i = 0; i < channels.size(); ++i )
    {
      const string& ip = client->GetPeersDiscoverer()->GetChannelIp( channels[i].first );
      logger << ip << ",";
    }
    logger << endl;

    const char* smsg20 = "01234567890123456789";
    //const char* smsg80 = "qwertyuiopasdfghjklz01234567890123456789qwertyuiopasdfghjklz01234567890123456789"
    //                     "qwertyuiopasdfghjklz01234567890123456789qwertyuiopasdfghjklz01234567890123456789"
    //                     "qwertyuiopasdfghjklz01234567890123456789qwertyuiopasdfghjklz01234567890123456789"
    //                     "qwertyuiopasdfghjklz01234567890123456789qwertyuiopasdfghjklz01234567890123456789";

    DWORD connectionsListsLastUpdate = ::GetTickCount();
    const int connectionsListsUpdateInterval = 100;
    while ( isRunning )
    { 
      vector<byte> recv;
      for( int i = 0; i < channels.size(); ++i )
      {
        while( channels[i].second->ReceiveRaw( &recv ) )
          ;
        channels[i].second->SendRaw( (const byte*)smsg20, 20 );
      }

      DWORD now = ::GetTickCount();
      if ( ( now - connectionsListsLastUpdate ) > connectionsListsUpdateInterval )
      {
        connectionsListsLastUpdate = now;

        struct tm curTime;
        GetOsLocalTime( &curTime );

        logger << curTime.tm_hour << ":" << curTime.tm_min << ":" << curTime.tm_sec << ","; 
        for ( int i = 0; i < channels.size(); ++i )
        {
          int ping = channels[i].second->GetPingTime();

          GetLagLog().Log( "P2PLag", userId, channels[i].first, ping );

          logger <<  ping << ",";
        }
        logger << endl;
      }


      Sleep( conf.delay );
    }

    return 0;
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void __stdcall PrintDebugVarCallback( const wchar_t* screen, const wchar_t* name, const NDebug::IDebugVar* var )
{
  static wchar_t value[128];
  var->FormatValue( value, sizeof( value ) / sizeof( wchar_t ) );

  if ( NStr::SearchFirst( NStr::ToMBCS( name ).c_str(), " to:", NStr::SASCIICharsComparer() ) >= 0 )
    return;

  systemLog( NLogg::LEVEL_MESSAGE ) << wstring(name) << ": " << wstring(value) << endl;
}

void PrintNetStats()
{
  int nScreen = 0;
  while ( wcscmp( NDebug::GetDebugScreenName( nScreen ), L"Net" ) != 0 ) 
    ++nScreen;

  NDebug::ProcessScreenDebugVars( nScreen, PrintDebugVarCallback );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{ 
  NLogg::CStdOutDumper g_stdoutDumper( &GetSystemLog(), "Stdout" );

  SConfiguration conf;
  NCmdLine::CCmdLine cmdLine( 
    "Nival RPC ping test utility. Usage: \n"
    "start server TestEchoServerApp\n"
    "run PingTesterApp -direct -server <ip:port> -clients <N=number of apps in test>\n"
    "run N-1 copies of PingTesterApp -direct -server <TestEchoServerApp ip:port>"
    );

  cmdLine.AddOption("-direct", &conf.directConnect, true, "Connect to echo server directly, bypassing login and relay server" );
  cmdLine.AddOption("-server", &conf.serverAddr, "Login or testEcho (if --direct) server address and port" );
  cmdLine.AddOption("-user", &conf.login, "Username to pass to login server" );
  cmdLine.AddOption("-password", &conf.password, "Password to pass to login server" );
  cmdLine.AddOption("-delay", &conf.delay, "Delay between command sends, ms" );
  cmdLine.AddOption("-clients", &conf.numClients, "Wait for N clients and start test" );

  NCmdLine::CCmdLine::EProcessResult result = cmdLine.Process( argc, argv );

  if ( conf.serverAddr.empty() || result != NCmdLine::CCmdLine::PROC_RESULT_OK )
  {
    printf( "Test type must be specified" );
    return cmdLine.PrintUsage( "" );
  }

  Network::InitFreePortsFinder( 1055 );
  CObj<Network::INetworkDriver> networkDriver = Network::Initialize();

  conf.myIp = Network::GetHostIPByName( "localhost" );
  conf.myIp += ":" + NStr::IntToStr( Network::GetFreePortsFinder()->GetFreePort() ); 
  int i1,i2,i3,i4,p;
  sscanf_s( conf.myIp.c_str(), "%d.%d.%d.%d:%d", &i1,&i2,&i3,&i4,&p );
  conf.id = (i3 << 24 ) + (i4 <<16) + p; 


  NLogg::CLoggerStream logger( 0, "dump", NLogg::LEVEL_MESSAGE );
  NLogg::CStdOutDumper dumper2( &logger, "std" );

  TestEchoClientRunner* runner = new TestEchoClientRunner( networkDriver, conf, logger );
  threading::ProcessingThread<TestEchoClientRunner>* runnerThread = new threading::ProcessingThread<TestEchoClientRunner> ( *runner );

  systemLog( NLogg::LEVEL_MESSAGE ) << "Ping test started, press F10 + F12 to close."<< endl;

  while (::GetAsyncKeyState( VK_F10 ) == 0 || ::GetAsyncKeyState( VK_F12 ) == 0)
  {
    //PrintNetStats();
    Sleep( 2000 );
  } 

  runnerThread->Stop( true, 5000 );
  delete runnerThread;
  delete runner;

  return 0;
}

