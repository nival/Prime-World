#include "stdafx.h"
#include "FileExtensionStatisticsMonitor.h"
#include "FilePath.h"


FileExtensionStatisticsMonitor::FileExtensionStatisticsMonitor()
{
  NGlobal::RegisterContextCmd( "fs_extensions_dump", this, &FileExtensionStatisticsMonitor::CommandDump );
  NGlobal::RegisterContextCmd( "fs_extensions_reset", this, &FileExtensionStatisticsMonitor::CommandReset );
}



void FileExtensionStatisticsMonitor::OnDestroyContents()
{
  NGlobal::UnregisterCmd( "fs_extensions_dump" );
  NGlobal::UnregisterCmd( "fs_extensions_reset" );
}



void FileExtensionStatisticsMonitor::OnGetDirectories( const string & root, NHPTimer::FTime timeSpent )
{
  //TODO..
}



void FileExtensionStatisticsMonitor::OnGetFiles( const string & root, NHPTimer::FTime timeSpent )
{
  //TODO...
}



void FileExtensionStatisticsMonitor::OnGetFileInfo( const string & fileName, NHPTimer::FTime timeSpent )
{
  string ext = NFile::GetFileExt( fileName );

  threading::MutexLock lock( mutex );

  SExtensionData & data = extData[ext];
  ++data.getInfoCount;
  data.getInfoTime += timeSpent;
}



void FileExtensionStatisticsMonitor::OnOpenFile( const string & fileName, NHPTimer::FTime timeSpent, unsigned size )
{
  string ext = NFile::GetFileExt( fileName );

  threading::MutexLock lock( mutex );

  SExtensionData & data = extData[ext];
  ++data.openCount;
  data.totalReadSize += size;
  data.openTime += timeSpent;
}



void FileExtensionStatisticsMonitor::Reset()
{
  threading::MutexLock lock( mutex );

  extData.clear();
}



void FileExtensionStatisticsMonitor::Dump()
{
  threading::MutexLock lock( mutex );

  DebugTrace( "File operations statistics by extension:" );

  NHPTimer::FTime totalOpenTime = 0, totalGetInfoTime = 0;
  unsigned totalOpenCount = 0, totalGetInfoCount = 0;
  unsigned totalSize = 0;

  for ( TExtensionData::const_iterator it = extData.begin(); it != extData.end(); ++it )
  {
    SExtensionData & data = it->second;
    DebugTrace( "  '%s': %.3f sec open, %.3f sec getInfo, %u open, %u getInfo, %u %s total", it->first.c_str(),
      data.openTime, data.getInfoTime,
      data.openCount, data.getInfoCount,
      ( data.totalReadSize < 1024 ) ? data.totalReadSize : data.totalReadSize / 1024, ( data.totalReadSize < 1024 ) ? "bytes" : "kbytes" );

    totalOpenCount += data.openCount;
    totalGetInfoCount += data.getInfoCount;
    totalOpenTime += data.openTime;
    totalGetInfoTime += data.getInfoTime;
    totalSize += data.totalReadSize;
  }

  DebugTrace( "Total: totalSize %u kbytes read, %u files opened, %u in getFileInfo, %.3f + %.3f seconds spent", 
    totalSize / 1024, totalOpenCount, totalGetInfoCount, totalOpenTime, totalGetInfoTime );
}



bool FileExtensionStatisticsMonitor::CommandDump( const char *name, const vector<wstring> &args )
{
  Dump();
  return true;
}



bool FileExtensionStatisticsMonitor::CommandReset( const char *name, const vector<wstring> &args )
{
  Reset();
  return true;
}
