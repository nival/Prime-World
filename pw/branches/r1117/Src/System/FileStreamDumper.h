#pragma once

#include "Dumper.h"
#include "FileSystem/FileWriteStream.h"

namespace NLogg
{

class CFileStreamDumper : public CDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( CFileStreamDumper, CDumper );

protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

public:
  CFileStreamDumper( CLogger * pDefaultLogger );

private:
  threading::Mutex mutex;
  CObj<FileWriteStream> stream;
};

}
