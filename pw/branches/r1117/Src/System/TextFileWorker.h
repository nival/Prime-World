#ifndef TEXTFILEWORKER_H_INCLUDED
#define TEXTFILEWORKER_H_INCLUDED

#include "System/JobThread.h"
#include "MemoryBlockPool.h"

#if defined( NV_WIN_PLATFORM )
  #define BAD_FILE_VALUE      INVALID_HANDLE_VALUE
  #define FILE_HANDLE         HANDLE
#elif defined( NV_LINUX_PLATFORM )
  #define BAD_FILE_VALUE      -1
  #define FILE_HANDLE         int
#endif

namespace NLogg
{

class TextFileWorkerThread : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TextFileWorkerThread, threading::IThreadJob, BaseObjectMT );

public:
  TextFileWorkerThread( const char * _suffix, size_t _bufferLimit, const char* _folder );
  ~TextFileWorkerThread();

  void PushMessage( const char * text );
  string Filename();

private:
  typedef vector<memory::MemoryBlock> MemoryBlocks;

  const size_t                  bufferLimit;
  string                        suffix;
  bool                          justStarted;
  bool                          reopenFile;
  threading::Mutex              mutex;
  threading::Event              evtNewMessage;
  string                        fileName;
  vector<ni_detail::Byte>       inputBuffer, workingBuffer;
  int                           threadsafeSkippedMessages, skippedMessages;
  int                           lastRotationHour, lastRotationDay;
  FILE_HANDLE                   handle;
  string                        folder;

  virtual void Work( volatile bool & isRunning );

  void Write();
  void Swap();
  void CloseLogFile();
  void OpenLogFile();
  void UpdateFile();
  void WriteText( const char * text );
  void WriteData( const void * data, size_t size );
};

} //namespace NLogg

#endif //TEXTFILEWORKER_H_INCLUDED
