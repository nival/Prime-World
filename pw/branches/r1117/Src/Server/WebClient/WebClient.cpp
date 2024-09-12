#include "stdafx.h"
#include "WebClient.h"
#include <curl/curl.h>
#include <curl/easy.h>


static bool s_debugCurl = false;
REGISTER_VAR( "curl_debug", s_debugCurl, STORAGE_NONE );

static int s_connectTimeout = 5;
REGISTER_VAR( "curl_conn_to", s_connectTimeout, STORAGE_NONE );

static int s_totalTimeout = 15;
REGISTER_VAR( "curl_total_to", s_totalTimeout, STORAGE_NONE );

namespace webClient
{

class CurlClient : public BaseObjectMT, public IHttpClient
{
  NI_DECLARE_REFCOUNT_CLASS_2( CurlClient, BaseObjectMT, IHttpClient );

public:
  CurlClient() :
  _curl( NULL ),
  _responseCode( 0 )
  {
    memset( _curlErrorMsg, CURL_ERROR_SIZE, 0 );
  }

  ~CurlClient() {
    CloseCurl();
  }

protected:
  //IHttpClient
  virtual void SetRequestProperies( const TRequestProperties & reqProperties ) { _reqProperties = reqProperties; }
  virtual bool PerformPOST( const char * url, const void * _postBody, size_t _postBodySize, string & answerHeader, string & answerBody );
  virtual bool PerformGET( const char * url, string & answerHeader, string & answerBody );
  virtual long GetResponseCode() const { return _responseCode; }

private:
  CURL * _curl;
  char _curlErrorMsg[CURL_ERROR_SIZE];
  TRequestProperties _reqProperties;
  long _responseCode;

  void InitCurl();
  void CloseCurl();
  curl_slist * CreateHeaders( const TRequestProperties & reqProperties );
};




IHttpClient * NewHttpClient()
{
  return new CurlClient;
}



struct CurlGlobalInitializator
{
  CurlGlobalInitializator() {
    curl_global_init( CURL_GLOBAL_WIN32 );
  }

  ~CurlGlobalInitializator() {
    curl_global_cleanup();
  }
};

static CurlGlobalInitializator curlGlobalInitializator;


static size_t CurlCb_write_callback( void * ptr, size_t size, size_t nmemb, void * userdata )
{
  string & buffer = *(string *)userdata;
  string text( (const char *)ptr, size * nmemb );
  buffer += text;
  return size * nmemb;
}


static int CurlCb_debug_callback( CURL * curl, curl_infotype type, char * ptr, size_t sz, void * aux )
{
  if ( ptr && sz )
    DebugTrace( "CURL debug: type=%d, size=%d, text=%.*s", (int)type, sz, sz, ptr );
  else
    DebugTrace( "CURL debug: type=%d", (int)type );

  switch ( type )
  {
    case CURLINFO_TEXT:
    case CURLINFO_HEADER_IN:
    case CURLINFO_HEADER_OUT:
    case CURLINFO_DATA_IN:
    case CURLINFO_DATA_OUT:
    case CURLINFO_SSL_DATA_IN:
    case CURLINFO_SSL_DATA_OUT:
      break;
  }

  return 0;
}



void CurlClient::InitCurl()
{
  MessageTrace( "Initializing CURLlib..." );

  NI_VERIFY( !_curl, "", return );

  _curl = curl_easy_init();
  NI_VERIFY( _curl, "Curl initialization failed", return );

  if ( s_debugCurl ) {
    curl_easy_setopt( _curl, CURLOPT_VERBOSE, (LONG)1 );
    curl_easy_setopt( _curl, CURLOPT_DEBUGFUNCTION, (LONG)CurlCb_debug_callback );
  }

  curl_easy_setopt( _curl, CURLOPT_NOPROGRESS, 1L );
  curl_easy_setopt(_curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1); // HTTP 1.1

  curl_easy_setopt(_curl, CURLOPT_FORBID_REUSE, 0L );
  curl_easy_setopt(_curl, CURLOPT_FRESH_CONNECT, 0L );

  curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, (long)s_connectTimeout );
  curl_easy_setopt(_curl, CURLOPT_TIMEOUT, (long)s_totalTimeout );

  curl_easy_setopt( _curl, CURLOPT_WRITEHEADER, 0 );
  curl_easy_setopt( _curl, CURLOPT_WRITEDATA, 0 );
  curl_easy_setopt( _curl, CURLOPT_HEADERFUNCTION, CurlCb_write_callback );
  curl_easy_setopt( _curl, CURLOPT_WRITEFUNCTION, CurlCb_write_callback );
  curl_easy_setopt( _curl, CURLOPT_ERRORBUFFER, _curlErrorMsg );
}



void CurlClient::CloseCurl()
{
  MessageTrace( "Shutting CURLlib down..." );

  if ( _curl )
    curl_easy_cleanup( _curl );
  _curl = 0;
}



curl_slist * CurlClient::CreateHeaders( const TRequestProperties & reqProperties )
{
  struct curl_slist * headers = NULL;
  headers = curl_slist_append( headers, "Accept-Encoding: text" );

  for ( TRequestProperties::const_iterator it = reqProperties.begin(); it != reqProperties.end(); ++it )
    headers = curl_slist_append( headers, it->c_str() );

  return headers;
}



bool CurlClient::PerformPOST( const char * url, const void * _postBody, size_t _postBodySize, string & answerHeader, string & answerBody )
{
  if ( !_curl )
    InitCurl();

  if ( !_curl )
    return false;

  strcpy( _curlErrorMsg, "" );

  MessageTrace( "Performing HTTP POST: url_len=%d, body_len=%d, url='%s'", strlen( url ), _postBodySize, url );

  curl_easy_setopt( _curl, CURLOPT_POST, 1L );

  curl_easy_setopt( _curl, CURLOPT_URL, url );

  curl_easy_setopt( _curl, CURLOPT_POSTFIELDS, (void *)_postBody );
  curl_easy_setopt( _curl, CURLOPT_POSTFIELDSIZE, (LONG)_postBodySize );

  curl_easy_setopt( _curl, CURLOPT_WRITEHEADER, &answerHeader );
  curl_easy_setopt( _curl, CURLOPT_WRITEDATA, &answerBody );

  curl_slist * headers = CreateHeaders( _reqProperties );
  curl_easy_setopt( _curl, CURLOPT_HTTPHEADER, headers );
  
#if defined( NV_LINUX_PLATFORM )
  // Prevent "longjmp causes uninitialized stack frame" CURL bug in Linux
  curl_easy_setopt( _curl, CURLOPT_NOSIGNAL, 1 );
#endif
  
  CURLcode res = curl_easy_perform( _curl );

  _responseCode = 0;
  curl_easy_getinfo( _curl, CURLINFO_RESPONSE_CODE, &_responseCode );

  curl_easy_setopt( _curl, CURLOPT_HTTPHEADER, 0 );
  curl_slist_free_all( headers );

  curl_easy_setopt( _curl, CURLOPT_WRITEHEADER, 0 );
  curl_easy_setopt( _curl, CURLOPT_WRITEDATA, 0 );

  curl_easy_setopt( _curl, CURLOPT_POSTFIELDS, (void *)0 );
  curl_easy_setopt( _curl, CURLOPT_POSTFIELDSIZE, (LONG)0 );

  if ( res != CURLE_OK ) {
    ErrorTrace( "Libcurl failed: %s", _curlErrorMsg );
    CloseCurl(); //We will try to re-initialize with next request
    return false;
  }
  else
    DebugTrace( "HTTP POST performed" );

  return true;
}



bool CurlClient::PerformGET( const char * url, string & answerHeader, string & answerBody )
{
  if ( !_curl )
    InitCurl();

  if ( !_curl )
    return false;

  strcpy( _curlErrorMsg, "" );

  MessageTrace( "Performing HTTP GET: url_len=%d, url='%s'", strlen( url ), url );

  curl_easy_setopt( _curl, CURLOPT_HTTPGET, 1L );

  curl_easy_setopt( _curl, CURLOPT_URL, url );

  curl_easy_setopt( _curl, CURLOPT_WRITEHEADER, &answerHeader );
  curl_easy_setopt( _curl, CURLOPT_WRITEDATA, &answerBody );

  curl_slist * headers = CreateHeaders( _reqProperties );
  curl_easy_setopt( _curl, CURLOPT_HTTPHEADER, headers );
  
  CURLcode res = curl_easy_perform( _curl );

  _responseCode = 0;
  curl_easy_getinfo( _curl, CURLINFO_RESPONSE_CODE, &_responseCode );

  curl_easy_setopt( _curl, CURLOPT_HTTPHEADER, 0 );
  curl_slist_free_all( headers );

  curl_easy_setopt( _curl, CURLOPT_WRITEHEADER, 0 );
  curl_easy_setopt( _curl, CURLOPT_WRITEDATA, 0 );

  if ( res != CURLE_OK ) {
    ErrorTrace( "Libcurl failed: %s", _curlErrorMsg );
    CloseCurl(); //We will try to re-initialize with next request
    return false;
  }
  else
    DebugTrace( "HTTP GET performed" );

  return true;
}

} //namespace webClient

NI_DEFINE_REFCOUNT( webClient::CurlClient );
