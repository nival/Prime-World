#pragma once

#include "Dumper.h"

namespace NLogg
{

class CStdOutDumper : public CDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( CStdOutDumper, CDumper );

protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

public:
  CStdOutDumper( CLogger *pDefaultLogger, FILE *pFile = stdout, bool isMessageOnly = true ) : 
      CDumper( pDefaultLogger, "stdout" ), pFile(pFile), isMessageOnly(isMessageOnly)  {}

private:
  bool isMessageOnly;
  FILE *pFile;  
};

}
