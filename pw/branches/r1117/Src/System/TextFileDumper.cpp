#include "stdafx.h"

#include "TextFileDumper.h"
#include "System/AsyncTextFileDumper.h"
#include "System/SyncTextFileDumper.h"


namespace NLogg
{

static bool s_syncMode = false;
static size_t s_asyncBuffer = 1024 * 1024;

BasicTextFileDumper * BasicTextFileDumper::New( CLogger * logger, const char * suffix, const char* folder /*= 0*/)
{
  if ( s_syncMode )
    return new SyncTextFileDumper( logger, suffix, folder );
  else
    return new AsyncTextFileDumper( logger, suffix, s_asyncBuffer, folder );
}



void BasicTextFileDumper::Setup( bool syncMode, unsigned bufferSize )
{
  s_syncMode = syncMode;
  s_asyncBuffer = bufferSize;
}

} //namespace NLogg
