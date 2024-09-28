#ifndef WINFILESYSTEMWATCHER_H_6F50ACFD
#define WINFILESYSTEMWATCHER_H_6F50ACFD

#include "FileSystem.h"
#include <System/ThreadHelpers.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WinFileSystemWatcher : public IFileWatcher, public CObjectBase
{	
public:
  WinFileSystemWatcher( const string& basePath, const string path );
  ~WinFileSystemWatcher();

  virtual bool SomethingChanged( IFileWatcher::TChangedFileList* );
  virtual const string& GetPath() const { return path; }
  DWORD Process( volatile bool& isRunning );

private:
  string basePath;
  string path;
  threading::ProcessingThread<WinFileSystemWatcher>* pThread;

  HANDLE directoryHandle;
  volatile DWORD hasDataFlag;
  vector<char> buffer;
  threading::Mutex bufferLock;

  WinFileSystemWatcher() : pThread(0), directoryHandle(0), hasDataFlag(0) {}
  OBJECT_BASIC_METHODS( WinFileSystemWatcher );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //#define WINFILESYSTEMWATCHER_H_6F50ACFD
