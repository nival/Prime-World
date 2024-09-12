#include "stdafx.h"
#include "WebServer.h"
#include "WebServerMongoose.h"

namespace webServer
{

IWebServerInstance * CreateInstance( IWebServerCallback * _callback, int _port, int _threadsNumber, bool _keepAlive, int _maxReqSize, const char * _ipFilter )
{
  return new MongooseServer( _callback, _port, _threadsNumber, _keepAlive, _maxReqSize, _ipFilter );
}

} //namespace webServer
