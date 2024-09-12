#pragma once

#include "Dumper.h"

namespace NLogg
{

class CEventDumper : public CDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( CEventDumper, CDumper );

protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

public:
  CEventDumper( CLogger *pDefaultLogger ) :
  CDumper( pDefaultLogger, "event" )
  {}

private:
  threading::Mutex mutex;
};

}
