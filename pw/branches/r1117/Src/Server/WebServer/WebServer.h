#ifndef WEBSERVER_H_INCLUDED
#define WEBSERVER_H_INCLUDED

namespace webServer
{

_interface IWebServerRequest
{
  virtual const char *  GetHeader( const char * name ) const = 0;
  virtual const char *  GetUri() const = 0;
  virtual const char *  GetQueryString() const = 0;
  virtual string        GetQueryVar( const char * name, int bufferSize ) const = 0;
  virtual void          WriteString( const char * text ) = 0;
  virtual int           ReadData( void * buffer, unsigned bufferSize ) = 0;
};



_interface IWebServerCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IWebServerCallback, IBaseInterfaceMT );

  virtual void ProcessRequest( IWebServerRequest * request, const string & rawPostBody, timer::Time dbgElapsed ) = 0;
};



_interface IWebServerInstance : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IWebServerInstance, IBaseInterfaceMT );

  virtual bool IsStarted() const = 0;
  virtual LONG DbgRequestHandlerEntryCounter() const = 0;
  virtual LONG DbgListenThreadPollCounter() const = 0;
  virtual LONG CriticalErrorCounter() const = 0;
};



IWebServerInstance * CreateInstance( IWebServerCallback * _callback, int _port, int _threadsNumber, bool _keepAlive, int _maxReqSize, const char * _ipFilter );

} //namespace webServer

#endif //WEBSERVER_H_INCLUDED
