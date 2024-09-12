#ifndef FILESYSTEMDEBUGMONITOR_H_INCLUDED
#define FILESYSTEMDEBUGMONITOR_H_INCLUDED

#include "FileSystemDebugMonitor.h"
#include "System/SyncPrimitives.h"

class FileExtensionStatisticsMonitor : public IFileSystemDebugMonitor, public CObjectBase
{
  OBJECT_BASIC_METHODS( FileExtensionStatisticsMonitor );

public:
  FileExtensionStatisticsMonitor();
  void OnDestroyContents();

  virtual void OnGetDirectories( const string & root, NHPTimer::FTime timeSpent );
  virtual void OnGetFiles( const string & root, NHPTimer::FTime timeSpent );
  virtual void OnGetFileInfo( const string & fileName, NHPTimer::FTime timeSpent );
  virtual void OnOpenFile( const string & fileName, NHPTimer::FTime timeSpent, unsigned size );

  void Reset();

  void Dump();

private:
  struct SExtensionData
  {
    unsigned          openCount, getInfoCount;
    unsigned          totalReadSize;
    NHPTimer::FTime   openTime, getInfoTime;

    SExtensionData() : openCount(), getInfoCount(), totalReadSize(), openTime(), getInfoTime() {}
  };

  typedef map<string, SExtensionData> TExtensionData;

  threading::Mutex    mutex;
  TExtensionData      extData;

  bool CommandDump( const char *name, const vector<wstring> &args );
  bool CommandReset( const char *name, const vector<wstring> &args );
};

#endif //FILESYSTEMDEBUGMONITOR_H_INCLUDED
