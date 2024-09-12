#pragma once

#include "TextFileDumper.h"

namespace threading
{
  class JobThread;
}

namespace NLogg
{

class TextFileWorkerThread;

class AsyncTextFileDumper : public BasicTextFileDumper
{
protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

public:
  explicit AsyncTextFileDumper( CLogger * _logger, const char * _suffix, size_t _bufferSize, const char* _folder );
  ~AsyncTextFileDumper();

  virtual string FileName() const;

private:
  StrongMT<threading::JobThread>  thread;
  StrongMT<TextFileWorkerThread>  job;
};

} //namespace NLogg
