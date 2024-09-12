#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#include <string>
#include <vector>
#include <curl/curl.h>
#include <curl/easy.h>
#include "System/NonCopyable.h"


namespace EUploadReaction
{
  enum Enum { KeepFile, DeleteFile };
}


class ThreadContext : public NonCopyable
{
public:
  ThreadContext( const wchar_t * _userDirectory, unsigned _maxFileSize, unsigned _maxFilesPerSecond );
  ~ThreadContext();

  void Work();

  void Stop();
  bool Stopping() const { return stopFlag; }
  bool StillRunning() const { return stillRunning; }

private:
  std::wstring        path;
  const unsigned      maxFileSize;
  const unsigned      maxFilesPerSecond;

  bool volatile       stopFlag;
  bool volatile       stillRunning;

  std::wstring        searchpath;
  CURL *              curl;
  char                curlErrorMsg[CURL_ERROR_SIZE];

  FILE *              logFile;

  void InitCurl();
  void ShutdownCurl();
  bool Post( const char * _url, const void * _postBody, size_t _postBodySize );

  bool ScanFiles( int _limit );
  bool UploadFile( EUploadReaction::Enum & _reaction, const wchar_t * _filename, size_t _size );
  bool LoadFile( std::string & _url, std::vector<byte> & _data, const wchar_t * _filename, size_t _size );
  void AppendTimestamp( std::string & _url );

  void InitLogging( const wchar_t * _userDirectory );
  void Log( const char * _fmt, ... );
};

#endif //WORKER_H_INCLUDED
