#include "stdafx.h"

#include "AsyncTextFileDumper.h"
#include "System/TextFileWorker.h"


namespace NLogg
{

AsyncTextFileDumper::AsyncTextFileDumper( CLogger * _logger, const char * _suffix, size_t _bufferSize, const char* _folder ) :
BasicTextFileDumper( _logger, "text" )
{
  job = new TextFileWorkerThread( _suffix, _bufferSize, _folder );
  thread = new threading::JobThread( job, "TextLogWorker", 3000, 65536 );
}



AsyncTextFileDumper::~AsyncTextFileDumper()
{
  thread = 0;

  job = 0;
}



void AsyncTextFileDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  job->PushMessage( headerAndText );
}



string AsyncTextFileDumper::FileName() const
{
  return job->Filename();
}

} //namespace NLogg
