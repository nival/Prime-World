#pragma once

#include <string>

#include "Network/Transport.h"
#include <RPC/RPC.h>
#include "System/Thread.h"
#include "ServerAppBase/NivalService.h"
#include "WebServer/WebServer.h"

namespace HttpGateway
{

static const char * ServiceInterfaceId = "gateway";

// forwards
class Service; 
class GatewayJsonHandler;



class WebServer : public webServer::IWebServerCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( WebServer, webServer::IWebServerCallback, BaseObjectMT );

public:
  WebServer( GatewayJsonHandler * _handler, unsigned _port );

  void PopApproxLoadStatistics( LONG & hits, LONG & size, LONG & elapsed );
  webServer::IWebServerInstance * WebServerInst() const { return webSrv; }
  LONG CriticalErrorCounter() const { return webSrv->CriticalErrorCounter(); }

private:
  const int                                 port;
  StrongMT<GatewayJsonHandler>              handler;
  StrongMT<webServer::IWebServerInstance>   webSrv;
  volatile LONG                             processedReqNumber, processedReqSize, processingTime;

  //webServer::IWebServerCallback
  virtual void ProcessRequest( webServer::IWebServerRequest * _request, const string & rawPostBody, timer::Time dbgElapsed );
};



// main class, Http Gateway Service
class Service : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( Service, Transport::BaseService );

public:
  Service( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );
  
private:
  unsigned                        httpPort;
  StrongMT<WebServer>             webSrv;
  StrongMT<GatewayJsonHandler>    jsonHandler;
  timer::Time                     lastPollTime;
  timer::Time                     lastWebServerDbgDump;

  timer::Time                     lastCritErrorCheck;
  LONG                            lastCritErrorCount;
  timer::Time                     critErrorCooldownEnds;

  virtual void Poll( timer::Time _now );
};

} //namespace HttpGateway
