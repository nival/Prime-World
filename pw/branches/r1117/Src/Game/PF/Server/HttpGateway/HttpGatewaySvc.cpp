#include "stdafx.h"
#include "HttpGatewaySvc.h"
#include "Server/LobbySocial/RISocialLobby.auto.h"
#include "Server/LobbySocial/RISocialLobbyNotify.auto.h"
#include "Server/LobbySocial/LISocialLobbyNotify.auto.h"
#include "Server/Roll/LRollClient.auto.h"
#include "GatewayJSonHandler.h"
#include "System/InlineProfiler.h"
#include "HttpGatewayLog.inl"


namespace HttpGateway
{

static unsigned s_basePort = 34000;
REGISTER_VAR( "http_gateway_base_port", s_basePort, STORAGE_NONE );

static unsigned g_requestLimit = 1024;
REGISTER_VAR( "http_gateway_request_limit", g_requestLimit, STORAGE_NONE );

static unsigned g_threadsNumber = 10;
REGISTER_VAR( "http_gateway_threads", g_threadsNumber, STORAGE_NONE );

static bool g_keepAlive = true;
REGISTER_VAR( "http_gateway_keep_alive", g_keepAlive, STORAGE_NONE );

static float g_dbgLoadDumpPeriod = 60.0f;
REGISTER_VAR( "http_gateway_load_dump_period", g_dbgLoadDumpPeriod, STORAGE_NONE );

static float g_critErrorCheckInterval = 60.0f;
REGISTER_VAR( "http_gateway_crit_error_check_interval", g_critErrorCheckInterval, STORAGE_NONE );

static int g_critErrorLimit = 4;
REGISTER_VAR( "http_gateway_crit_error_limit", g_critErrorLimit, STORAGE_NONE );

static float g_critErrorCooldown = 30.0f;
REGISTER_VAR( "http_gateway_crit_error_check_cooldown", g_critErrorCooldown, STORAGE_NONE );



WebServer::WebServer( GatewayJsonHandler * _handler, unsigned _port ) :
port( _port ),
handler( _handler ),
processedReqNumber( 0 ), processedReqSize( 0 ), processingTime( 0 )
{
  webSrv = webServer::CreateInstance( this, port, g_threadsNumber, g_keepAlive, g_requestLimit, 0 );

  SVC_LOG_MSG.Trace( "Listening for http on port %d (%d threads, %d request limit)", port, g_threadsNumber, g_requestLimit );
}



void WebServer::ProcessRequest( webServer::IWebServerRequest * _request, const string & rawPostBody, timer::Time dbgElapsed )
{
  NI_PROFILE_FUNCTION;

  SVC_LOG_MSG.Trace( "Processing HTTP request. size=%d, port=%d", rawPostBody.size(), port );

  InterlockedIncrement( &processedReqNumber );
  InterlockedExchangeAdd( &processedReqSize, (LONG)rawPostBody.size() );
  InterlockedExchangeAdd( &processingTime, (LONG)( dbgElapsed * 1e3 ) );

  string action = _request->GetQueryVar( "action", 64 );
  if ( action == "mm" )
  {
    NI_PROFILE_BLOCK( "mm" );

    if ( rawPostBody.empty() )
    {
      _request->WriteString( "No jason data found" );
      SVC_LOG_ERR.Trace( "No jason data in 'action' request" );
      return;
    }

    std::string reply;
    handler->HandleJson( reply, rawPostBody.c_str() );

    NI_PROFILE_BLOCK( "Writing Reply" );
#define MYNEWLINE "\r\n"
    _request->WriteString( "HTTP/1.0 200 OK" MYNEWLINE );
    _request->WriteString( "Content-Type: application/json" MYNEWLINE );
    _request->WriteString( NI_STRFMT( "Content-Length: %d" MYNEWLINE, reply.size() ) );
    _request->WriteString( "Content-Type: application/json" MYNEWLINE MYNEWLINE );
    _request->WriteString( reply.c_str() );
  }
  else
  {
    _request->WriteString( "No action defined" );
    SVC_LOG_ERR.Trace( "No action defined" );
    return;
  }
}



void WebServer::PopApproxLoadStatistics( LONG & hits, LONG & size, LONG & elapsed )
{
  hits = InterlockedExchange( &processedReqNumber, 0L );
  size = InterlockedExchange( &processedReqSize, 0L );
  elapsed = InterlockedExchange( &processingTime, 0L );
}







inline bool ParseUInt( unsigned & u, const string & s ) {
  unsigned tmp = 0;
  int n = 0;
  if ( sscanf( s.c_str(), "%u%n", &tmp, &n ) == 1 )
    if ( n == s.length() ) {
      u = tmp;
      return true;
    }

  return false;
}




Service::Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams ),
httpPort( s_basePort ),
lastPollTime( 0 ),
lastWebServerDbgDump( timer::Now() ),
lastCritErrorCheck( 0 ),
lastCritErrorCount( 0 ),
critErrorCooldownEnds( 0 )
{
  DebugTrace( "HttpGateway cmd line: %s", ServerCmdLine() );

  unsigned portIndex = 0;
  Transport::TServerCmdLine::const_iterator it = ServerCmdLine().find( "gwportindex" );
  if ( it != ServerCmdLine().end() )
    if ( ParseUInt( portIndex, it->second ) )
      SVC_LOG_MSG.Trace( "HTTP port index set from command-line: %u", portIndex );
    else
      SVC_LOG_WRN.Trace( "Wrong 'gwportindex' command line option format (%s)", it->second );

  httpPort += portIndex;

  RegisterBackendAttach<socialLobby::INotify, socialLobby::LINotify>();
  RegisterBackendAttach<roll::IClient, roll::LIClient>();

  jsonHandler = new GatewayJsonHandler( BackendGk() );
}



void Service::Poll( timer::Time _now )
{
  timer::Time t = _now;

  timer::Time pollTime = t - lastPollTime;
  if ( lastPollTime && ( pollTime > 1.0 ) )
    SVC_LOG_ERR.Trace( "HTTP gateway poll exceeded: %.1f sec", pollTime );
  lastPollTime = t;

  if ( jsonHandler )
    jsonHandler->Poll();

  if ( !webSrv && jsonHandler->Ready() )
  {
    if ( t < critErrorCooldownEnds )
      return;

    SVC_LOG_MSG.Trace( "Starting web server..." );
    webSrv = new WebServer( jsonHandler, httpPort );
    lastCritErrorCount = 0;
    critErrorCooldownEnds = 0;
  }

  if ( webSrv && g_critErrorLimit )
    if ( t > lastCritErrorCheck + g_critErrorCheckInterval )
    {
      lastCritErrorCheck = t;

      LONG count = webSrv->CriticalErrorCounter();
      LONG errorDelta = count - lastCritErrorCount;
      lastCritErrorCount = count;

      if ( errorDelta >= g_critErrorLimit ) {
        //Too many errors; Let's try restarting web server...
        SVC_LOG_CRI.Trace( "Too many web-server faults detected (%d in %.1f sec)! Restarting web server in %.1f seconds...", errorDelta, g_critErrorCheckInterval, g_critErrorCooldown );
        webSrv = 0;
        critErrorCooldownEnds = t + g_critErrorCooldown;
      }
    }

  if ( webSrv )
    if ( t > ( lastWebServerDbgDump + g_dbgLoadDumpPeriod ) )
    {
      lastWebServerDbgDump = t;

      LONG hits = 0, size = 0, elapsed = 0;
      webSrv->PopApproxLoadStatistics( hits, size, elapsed );

      LONG entries = webSrv->WebServerInst()->DbgRequestHandlerEntryCounter();
      LONG listenThreadPolls = webSrv->WebServerInst()->DbgListenThreadPollCounter();
      SVC_LOG_MSG.Trace( "Load statistics: requests=%d, bytes=%d, entries=%d, avgTimeMs=%d, listenPolls=%d", hits, size, entries, hits ? ( elapsed / hits ) : 0, listenThreadPolls );
    }
}

} // namespace HttpGateway
