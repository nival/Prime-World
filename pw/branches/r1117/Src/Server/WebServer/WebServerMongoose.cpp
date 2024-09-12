#include "stdafx.h"
#include "WebServerMongoose.h"
#include "System/InlineProfiler.h"


#include "mongoose.h"

namespace webServer
{


static float s_postReceiveTimeout = 30.0f;
REGISTER_VAR( "http_gateway_post_receive_timeout", s_postReceiveTimeout, STORAGE_NONE );


class MongooseRequest : public IWebServerRequest
{
public:
  MongooseRequest( mg_context * _ctx, mg_connection * _conn, const mg_request_info * _req ) :
  mgctx( _ctx ), mgconn( _conn ), mgrequest( _req ) {}

  virtual const char * GetHeader( const char * name ) const
  {
    return mg_get_header( mgconn, name );
  }

  virtual const char * GetUri() const
  {
    return mgrequest->uri;
  }

  virtual const char * GetQueryString() const
  {
    return mgrequest->query_string ? mgrequest->query_string : "";
  }

  virtual string GetQueryVar( const char * name, int bufferSize ) const
  {
    NI_PROFILE_FUNCTION;

    if ( mgrequest->query_string && bufferSize > 0 )
    {
      string buf;
      buf.resize( bufferSize, 0 );
      int result = mg_get_var( mgrequest->query_string, strlen( mgrequest->query_string ), name, &buf[0], bufferSize );
      if ( result >= 0 ) {
        buf.resize( result );
        return buf;
      }
    }

    return string();
  }

  virtual void WriteString( const char * text )
  {
    NI_PROFILE_FUNCTION;

    mg_write( mgconn, text, strlen( text ) );
  }

  virtual int ReadData( void * buffer, unsigned bufferSize )
  {
    NI_PROFILE_FUNCTION;

    return mg_read( mgconn, buffer, bufferSize );
  }

private:
  mg_context *            mgctx;
  mg_connection *         mgconn;
  const mg_request_info * mgrequest;
};



MongooseServer::MongooseServer( IWebServerCallback * _callback, int _port, int _threadsNumber, bool _keepAlive, int _maxReqSize, const char * _ipFilter ) :
callback( _callback ),
mgCtx( 0 ),
dbgRequestHandlerEntryCounter( 0 ), dbgListenThreadPollCounter( 0 ),
criticalErrorCounter( 0 )
{
  MessageTrace( "Starting Mongoose web server version %s", mg_version() );
  //FIXME:
  //Keep in mind: Mongoose does not exit when mg_stop is called if keep alive is active (http://code.google.com/p/mongoose/issues/detail?id=268)

  string strPort = NI_STRFMT( "%d", _port );
  string strMaxReq = NI_STRFMT( "%d", _maxReqSize );
  string strNumThreads = NI_STRFMT( "%d", _threadsNumber );

  vector<const char *> options;

  options.push_back( "document_root" );
  options.push_back( "." );

  options.push_back( "listening_ports" );
  options.push_back( strPort.c_str() );

  options.push_back( "num_threads" );
  options.push_back( strNumThreads.c_str() );

  if ( _ipFilter ) {
    options.push_back( "access_control_list" );
    options.push_back( _ipFilter );
  }

  options.push_back( "enable_keep_alive" );
  options.push_back( _keepAlive ? "yes" : "no" );

  options.push_back( (const char *)NULL );

  mgCtx = mg_start( &MongooseServer::MgCallback, this, &options[0] );
  NI_ASSERT( mgCtx, "Could not start mongoose web server" );
}



MongooseServer::~MongooseServer()
{
  StopImpl();
}



void MongooseServer::StopImpl()
{
  if ( mgCtx )
    mg_stop( mgCtx );
  mgCtx = 0;
}



void * __cdecl MongooseServer::MgCallback( mg_event event, mg_connection * conn )
{
  switch ( event )
  {
    case MG_EVENT_LOG:
      MessageTrace( "WebServer log: %s", mg_get_log_message( conn ) );
      return (void *)1;

    case MG_HTTP_ERROR:
      ErrorTrace( "HTTP Error" );
      break;

    case MG_NEW_REQUEST:
    {
      NI_PROFILE_BLOCK( "New Mongoose Req" );
      MongooseServer * This = (MongooseServer *)mg_get_user_data( conn );
      InterlockedIncrement( &This->dbgRequestHandlerEntryCounter );
      This->ProcessRequest( conn, mg_get_request_info( conn ) );
      InterlockedDecrement( &This->dbgRequestHandlerEntryCounter );
      return (void *)1;
    }

    case MG_NI_MASTER_THREAD_START:
      NI_PROFILE_THREAD_EX_START( "Mongoose Master" );
      break;

    case MG_NI_MASTER_THREAD_STOP:
      NI_PROFILE_THREAD_EX_STOP;
      break;

    case MG_NI_WORKER_THREAD_START:
      NI_PROFILE_THREAD_EX_START( "Mongoose Worker" );
      break;

    case MG_NI_WORKER_THREAD_STOP:
      NI_PROFILE_THREAD_EX_STOP;
      break;

    case MG_NI_MASTER_THREAD_POLL:
      MongooseServer * This = (MongooseServer *)mg_get_user_data( conn );
      InterlockedIncrement( &This->dbgListenThreadPollCounter );
      break;
  }

  return (void *)0;
}



void MongooseServer::ProcessRequest( mg_connection * conn, const mg_request_info * request_info )
{
  NI_PROFILE_FUNCTION;

  timer::Time started = timer::Now();

  if ( request_info->request_method && !strcmp( request_info->request_method, "POST" ) )
  {
    NI_PROFILE_BLOCK( "Reading POST body" );

    string postBody;

    const char * contLen = mg_get_header( conn, "Content-Length" );
    int contentLen = 0;
    if ( contLen && ( sscanf( contLen, "%d", &contentLen ) == 1 ) )
    {
      timer::Time timeout = started + s_postReceiveTimeout;

      for ( int bytesDone = 0; bytesDone < contentLen; )
      {
        if ( timer::Now() > timeout ) {
          ErrorTrace( "POST body receive time out. timeout=%.1f, bytes=%d, total=%d", s_postReceiveTimeout, bytesDone, contentLen );
          InterlockedIncrement( &criticalErrorCounter );
          return;
        }

        const size_t bufSz = 16384;
        char buf[bufSz] = "";

        int read = 0;
        {
          NI_PROFILE_HEAVY_BLOCK( "mg_read" );
          read = mg_read( conn, buf, bufSz );
        }

        if ( read > 0 ) {
          postBody.append( buf, buf + read );
          bytesDone += read;
        }
        else if ( read < 0 ) {
          ErrorTrace( "POST body receive failed, web server returned error. bytes=%d, total=%d", bytesDone, contentLen );
          InterlockedIncrement( &criticalErrorCounter );
          return;
        }
        else {
          NI_PROFILE_HEAVY_BLOCK( "Sleep" );
          Sleep( 1 );
        }
      }
    }

    const timer::Time elapsed = timer::Now() - started;

    if ( StrongMT<IWebServerCallback> locked = callback.Lock() ) {
      MongooseRequest req( mgCtx, conn, request_info );
      locked->ProcessRequest( &req, postBody, elapsed );
    }

  }
}

} //namespace webServer
