#include "stdafx.h"

//#include "LogHelpers.h"
#include "LogFileName.h"
#include "FileSystem/FileUtils.h"

#include "FileStreamDumper.h"

namespace NLogg
{

CFileStreamDumper::CFileStreamDumper( CLogger * pDefaultLogger ) : CDumper( pDefaultLogger, "stream" )
{
  string crclogFileName = NDebug::GenerateDebugFileName("GLLogFile", "txt");

  stream = new FileWriteStream(crclogFileName, FILEACCESS_WRITE, FILEOPEN_OPEN_ALWAYS);
}



void CFileStreamDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  threading::MutexLock guard( mutex );

  if ( stream->CanWrite() )
    stream->Write( textOnly, strlen( textOnly ) );
}

}
