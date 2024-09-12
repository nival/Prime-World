#pragma once

#include "TextFileDumper.h"
#include "MultiReaderLock.h"
#include "System/JobThread.h"

#if defined( NV_WIN_PLATFORM )
  #define BAD_FILE_VALUE      INVALID_HANDLE_VALUE
  #define FILE_HANDLE         HANDLE
#elif defined( NV_LINUX_PLATFORM )
  #define BAD_FILE_VALUE      -1
  #define FILE_HANDLE         int
#endif

namespace NLogg
{

class SyncTextFileDumper : public BasicTextFileDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( SyncTextFileDumper, BasicTextFileDumper )

protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

public:
  explicit SyncTextFileDumper( CLogger * pDefaultLogger, const char * suffix, const char* _folder );
  ~SyncTextFileDumper();

  virtual string FileName() const;

private:
  class TestFileRotorThread;
  friend class TestFileRotorThread;

  string      suffix;
  string      folder;
  string      logFileName;
  FILE_HANDLE handle;
  threading::MultiReaderLock multiLock;

  StrongMT<threading::JobThread> thread;

  void OpenLogFile();
  void CloseLogFile();
  void RotateLogParallel();
};

} //namespace NLogg
