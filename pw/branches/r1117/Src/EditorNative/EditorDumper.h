#pragma once
#include "../System/Dumper.h"

namespace EditorNative
{

class EditorDumper : public NLogg::CDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( EditorDumper, NLogg::CDumper );

public:
  EditorDumper( NLogg::CLogger *pDefaultLogger ) : CDumper( pDefaultLogger ) {}

protected:
  virtual void OnDump( const NLogg::SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

  threading::Mutex mutex;
};

} // namespace EditorNative
