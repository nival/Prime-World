#pragma once

#include "Dumper.h"

namespace NLogg
{

class CStringDumper : public CDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( CStringDumper, CDumper );

private:
  char *string;
  int size;

protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

public:
  CStringDumper( CLogger * pDefaultLogger, char * string, int size );

private:
  threading::Mutex mutex;
};

}
