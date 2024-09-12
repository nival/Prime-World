#include "worker.h"
#include "system/math/md4.h"
#include <stdlib.h>
#include <io.h>
#include <direct.h>



const static char * Salt = "Prime World Launcher";


ThreadContext::ThreadContext( const wchar_t * _userDirectory, unsigned _maxFileSize, unsigned _maxFilesPerSecond ) :
path( _userDirectory ),
maxFileSize( _maxFileSize ),
maxFilesPerSecond( ( _maxFilesPerSecond > 1 ) ? _maxFilesPerSecond : 1 ),
stopFlag( false ), stillRunning( true ),
curl( 0 ),
logFile( 0 )
{
  path += L"\\statdata\\";
  searchpath = path + L"*.sta";

  memset( curlErrorMsg, 0, CURL_ERROR_SIZE );

  InitLogging( _userDirectory );

  Log( "Statistics data daemon started. path=%S, maxFile=%u, maxFilesPerSec=%u, ptr=%p", searchpath.c_str(), _maxFileSize, _maxFilesPerSecond, (void *)this );
}



ThreadContext::~ThreadContext()
{
  Log( "Destructing statistics data daemon. ptr=%p", (void *)this );

  if ( logFile )
    fclose( logFile );

  ShutdownCurl();
}



static size_t Curl_write_callback( void * ptr, size_t size, size_t nmemb, void * userdata )
{
  std::string & buffer = *(std::string *)userdata;
  std::string text( (const char *)ptr, size * nmemb );
  buffer += text;
  return size * nmemb;
}



void ThreadContext::Work()
{
  curl_global_init( CURL_GLOBAL_WIN32 );

  time_t lastScan = 0;
  time( &lastScan );

  const double minCd = 3.0, maxCd = 24.0;
  double cooldown = minCd;


  while( !stopFlag )
  {
    Sleep( 100 );

    time_t t = 0;
    time( &t );

    double diff = difftime( t, lastScan );
    if ( diff >= cooldown )
    {
      lastScan = t;

      if ( ScanFiles( (int)( diff * maxFilesPerSecond ) ) )
        cooldown = minCd;
      else
      {
        cooldown *= 2.0;
        if ( cooldown > maxCd )
          cooldown = maxCd;
      }
    }
  }

  ShutdownCurl();

  curl_global_cleanup();

  stillRunning = false;
}



void ThreadContext::Stop()
{
  if ( !stopFlag )
    Log( "Stopping statistics data daemon. ptr=%p", (void *)this );

  stopFlag = true;
}



void ThreadContext::InitCurl()
{
  curl = curl_easy_init();
  if ( !curl )
    return;

  curl_easy_setopt( curl, CURLOPT_NOPROGRESS, 1L );
  curl_easy_setopt( curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1 );

  curl_easy_setopt( curl, CURLOPT_FORBID_REUSE, 0L );
  curl_easy_setopt( curl, CURLOPT_FRESH_CONNECT, 0L );

  curl_easy_setopt( curl, CURLOPT_CONNECTTIMEOUT, (long)10 );
  curl_easy_setopt( curl, CURLOPT_TIMEOUT, (long)20 );

  curl_easy_setopt( curl, CURLOPT_WRITEHEADER, 0 );
  curl_easy_setopt( curl, CURLOPT_WRITEDATA, 0 );
  curl_easy_setopt( curl, CURLOPT_HEADERFUNCTION, Curl_write_callback );
  curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, Curl_write_callback );
  curl_easy_setopt( curl, CURLOPT_ERRORBUFFER, curlErrorMsg );
}



void ThreadContext::ShutdownCurl()
{
  Log( "Closing CURL" );

  if ( curl )
    curl_easy_cleanup( curl );
  curl = 0;
}



bool ThreadContext::Post( const char * _url, const void * _postBody, size_t _postBodySize )
{
  Log( "Posting data. url=%s, size=%u", _url, _postBodySize );

  if ( !curl )
    return false;

  std::string answerHeader, answerBody;

  memset( curlErrorMsg, 0, CURL_ERROR_SIZE );

  curl_easy_setopt( curl, CURLOPT_POST, 1L );

  curl_easy_setopt( curl, CURLOPT_URL, _url );

  curl_easy_setopt( curl, CURLOPT_POSTFIELDS, (void *)_postBody );
  curl_easy_setopt( curl, CURLOPT_POSTFIELDSIZE, (LONG)_postBodySize );

  curl_easy_setopt( curl, CURLOPT_WRITEHEADER, &answerHeader );
  curl_easy_setopt( curl, CURLOPT_WRITEDATA, &answerBody );

  CURLcode res = curl_easy_perform( curl );

  long responseCode = 0;
  curl_easy_getinfo( curl, CURLINFO_RESPONSE_CODE, &responseCode );

  curl_easy_setopt( curl, CURLOPT_WRITEHEADER, 0 );
  curl_easy_setopt( curl, CURLOPT_WRITEDATA, 0 );

  curl_easy_setopt( curl, CURLOPT_POSTFIELDS, (void *)0 );
  curl_easy_setopt( curl, CURLOPT_POSTFIELDSIZE, (LONG)0 );

  if ( res != CURLE_OK )
  {
    Log( "ERROR: CURL failed. code=%u, msg=%s", (unsigned)res, curlErrorMsg );

    ShutdownCurl();
    return false;
  }

  if ( responseCode != 200 )
  {
    Log( "ERROR: HTTP response is not 200. code=%u, msg=%s", (unsigned)responseCode, curlErrorMsg );

    ShutdownCurl();
    return false;
  }

  return true;
}



bool ThreadContext::ScanFiles( int _limit )
{
  bool errors = false;

  _wfinddata_t findData;
  memset( &findData, 0, sizeof( findData ) );

  intptr_t ffile = _wfindfirst( searchpath.c_str(), &findData );
  int uploadLimit = _limit, scanLimit = 64;
  while( !stopFlag && ( ffile != -1 ) && ( uploadLimit >= 0 ) && ( scanLimit >= 0 ) )
  {
    std::wstring filename = path + findData.name;

    EUploadReaction::Enum reaction = EUploadReaction::KeepFile;

    if ( !UploadFile( reaction, filename.c_str(), findData.size ) == EUploadReaction::DeleteFile )
      errors = true;

    if ( reaction == EUploadReaction::DeleteFile )
    {
      --uploadLimit;

      Log( "Removing file. name=%S", filename.c_str() );

      _wremove( filename.c_str() );
    }
  
    --scanLimit;
    if ( _wfindnext( ffile, &findData ) != 0 )
      break;
  }

  _findclose( ffile );

  if ( curl )
    ShutdownCurl();

  if ( !scanLimit )
    return false;

  return !errors;
}



bool ThreadContext::UploadFile( EUploadReaction::Enum & _reaction, const wchar_t * _filename, size_t _size )
{
  Log( "Uploading file. name=%S, size=%u", _filename, (unsigned)_size );

  std::string url;
  std::vector<byte> data;
  if ( !LoadFile( url, data, _filename, _size ) )
  {
    Log( "ERROR: Failed to load file!" );
    _reaction = EUploadReaction::DeleteFile;
    return false;
  }

  if( data.empty() )
  {
    Log( "ERROR: Empty file!" );
    _reaction = EUploadReaction::DeleteFile;
    return false;
  }

  Log( "Data loaded. size=%u", (unsigned)data.size() );

  AppendTimestamp( url );

  if ( !curl )
  {
    Log( "Initializing CURL" );
    InitCurl();
  }

  if ( Post( url.c_str(), &data[0], data.size() ) )
  {
    Log( "File posted ok" );
    _reaction = EUploadReaction::DeleteFile;
    return true;
  }
  else
  {
    Log( "ERROR: Failed to post file" );
    ShutdownCurl();
  }
  _reaction = EUploadReaction::DeleteFile;
  return false;
}



bool ThreadContext::LoadFile( std::string & _url, std::vector<byte> & _data, const wchar_t * _filename, size_t _size )
{
  const size_t hdrSize = math::MD4::DIGEST_SIZE_IN_BYTES + sizeof( ni_detail::UInt32 );

  if ( _size <= hdrSize )
    return false;

  if ( _size > maxFileSize )
    return false;

  FILE * f = _wfopen( _filename, L"rb" );
  if ( !f )
    return false;

  ni_detail::Byte diskMD5[math::MD4::DIGEST_SIZE_IN_BYTES];
  ni_detail::UInt32 urlLen = 0;
  std::vector<ni_detail::Byte> encodedUrl;

  if ( fread( diskMD5, 1, math::MD4::DIGEST_SIZE_IN_BYTES, f ) == math::MD4::DIGEST_SIZE_IN_BYTES )
    if ( fread( &urlLen, 1, sizeof( urlLen ), f ) == sizeof( urlLen ) )
      if ( urlLen && ( urlLen < _size - hdrSize ) )
      {
        encodedUrl.resize( urlLen );
        if ( fread( &encodedUrl[0], 1, encodedUrl.size(), f ) == urlLen )
        {
          size_t dataSize = _size - hdrSize - urlLen;

          _data.resize( dataSize, 0 );
          if ( fread( &_data[0], 1, _data.size(), f ) == dataSize )
          {
            fclose( f );
            f = 0;

            math::MD5Generator md5;
            md5.Start();
            md5.Update( (const byte *)Salt, strlen( Salt ) );
            md5.AddObject( urlLen );
            md5.Update( &encodedUrl[0], encodedUrl.size() );
            md5.Update( &_data[0], _data.size() );
            md5.Update( (const byte *)Salt, strlen( Salt ) );
            md5.Stop();

            if ( memcmp( diskMD5, md5.Get().code, math::MD4::DIGEST_SIZE_IN_BYTES ) == 0 )
            {
              _url.resize( encodedUrl.size(), 0 );
              for ( size_t i = 0; i < encodedUrl.size(); ++i )
                _url[i] = (byte)encodedUrl[i] ^ (byte)( 0xff & ( ( i + 101 ) * 11 ) );

              return true;
            }
          }
        }
      }

  if ( f )
    fclose( f );
  return false;
}



void ThreadContext::AppendTimestamp( std::string & _url )
{
  time_t t = 0;
  time( &t );

  char buf[128] = "";
  _snprintf( buf, 127, "?timestamp=%u", (unsigned)t );
  buf[127] = 0;
  _url += buf;
}



void ThreadContext::InitLogging( const wchar_t * _userDirectory )
{
  std::wstring logfname = _userDirectory;
  logfname += L"\\statdaemonlogs\\";

  _wmkdir( logfname.c_str() );

  time_t now = 0;
  time( &now );
  const tm * utc = gmtime( &now );

  wchar_t buf[256] = L"";
  _snwprintf( buf, 256, L"StatLog_%04u.%02u.%02u_%02u.%02u.%02u_%08x.txt", 
    (unsigned)( 1900 + utc->tm_year ), (unsigned)( 1 + utc->tm_mon ), (unsigned)utc->tm_mday,
    (unsigned)utc->tm_hour, (unsigned)utc->tm_min, (unsigned)utc->tm_sec,
    (unsigned)GetTickCount() );

  logfname += buf;

  logFile = _wfopen( logfname.c_str(), L"wt" );
  if ( !logFile )
    return;
}



void ThreadContext::Log( const char * _fmt, ... )
{
  if ( !logFile )
    return;

  time_t now = 0;
  time( &now );
  const tm * utc = gmtime( &now );

  fprintf( logFile, "%04u.%02u.%02u %02u:%02u:%02u (%u) ", 
    (unsigned)( 1900 + utc->tm_year ), (unsigned)( 1 + utc->tm_mon ), (unsigned)utc->tm_mday,
    (unsigned)utc->tm_hour, (unsigned)utc->tm_min, (unsigned)utc->tm_sec,
    (unsigned)GetCurrentThreadId() );


  va_list args;
  va_start( args, _fmt );

  vfprintf( logFile, _fmt, args );

  va_end( args );

  fprintf( logFile, "\n" );

  fflush( logFile );
}
