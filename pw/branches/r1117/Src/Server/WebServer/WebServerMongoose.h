#ifndef WEBSERVERMONGOOSE_H_INCLUDED
#define WEBSERVERMONGOOSE_H_INCLUDED

#include "WebServer.h"

extern "C"
{
  struct mg_context;
  struct mg_connection;
  struct mg_request_info;
  enum mg_event;
}

namespace webServer
{

class MongooseServer : public IWebServerInstance, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MongooseServer, IWebServerInstance, BaseObjectMT );
public:
  MongooseServer( IWebServerCallback * _callback, int _port, int _threadsNumber, bool _keepAlive, int _maxReqSize, const char * _ipFilter );
  ~MongooseServer();

  virtual bool IsStarted() const { return mgCtx ? true : false; }
  virtual LONG DbgRequestHandlerEntryCounter() const { return dbgRequestHandlerEntryCounter; }
  virtual LONG DbgListenThreadPollCounter() const { return dbgListenThreadPollCounter; }
  virtual LONG CriticalErrorCounter() const { return criticalErrorCounter; }

private:
  WeakMT<IWebServerCallback>  callback;
  struct mg_context *         mgCtx;
  volatile LONG               dbgRequestHandlerEntryCounter, dbgListenThreadPollCounter;
  volatile LONG               criticalErrorCounter;

  void StopImpl();
  static void * __cdecl MgCallback( mg_event event, mg_connection * conn );
  void ProcessRequest( mg_connection * conn, const mg_request_info * request_info );
};

} //namespace webServer

#endif //WEBSERVERMONGOOSE_H_INCLUDED
