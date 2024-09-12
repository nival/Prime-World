#ifndef FILEACTIVITYSIMPLEMONITOR_H_INCLUDED
#define FILEACTIVITYSIMPLEMONITOR_H_INCLUDED

#include <System/config.h>
#include <System/SyncPrimitives.h>
#include "FileSystemDebugMonitor.h"

#if defined( NV_LINUX_PLATFORM )

	#include <fstream>

#endif

class FileActivitySimpleMonitor : public IFileSystemDebugMonitor, public CObjectBase
{
  OBJECT_BASIC_METHODS( FileActivitySimpleMonitor );

public:
  FileActivitySimpleMonitor();
  FileActivitySimpleMonitor( const char * logSuffix );

  ~FileActivitySimpleMonitor();

  virtual void OnGetDirectories( const string & root, NHPTimer::FTime timeSpent );
  virtual void OnGetFiles( const string & root, NHPTimer::FTime timeSpent );
  virtual void OnGetFileInfo( const string & fileName, NHPTimer::FTime timeSpent );
  virtual void OnOpenFile( const string & fileName, NHPTimer::FTime timeSpent, unsigned size );

protected:

  void OpenOutputFile();
  void WriteEntry( const char * operation, NHPTimer::FTime timeSpent, unsigned size, const string & fileName );

private:

  threading::Mutex    mutex;
  string              outputFilename;

#if defined( NV_WIN_PLATFORM )

  HANDLE              output;

#elif defined( NV_LINUX_PLATFORM )

  std::ofstream       m_output;

#endif

};

#endif //FILEACTIVITYSIMPLEMONITOR_H_INCLUDED

