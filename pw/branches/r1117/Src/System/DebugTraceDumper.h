#pragma once

#include "Dumper.h"

namespace NLogg
{

class CDebugTraceDumper : public CDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( CDebugTraceDumper, CDumper );

public:
  CDebugTraceDumper( CLogger *pDefaultLogger, bool isMessageOnly = false ) :
  CDumper( pDefaultLogger, "trace" ),
  isMessageOnly(isMessageOnly)
  {}

protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

private:
  bool isMessageOnly;
};

}
