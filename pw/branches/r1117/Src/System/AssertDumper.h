#ifndef _ASSERT_DUMPER_H_
#define _ASSERT_DUMPER_H_

#include "Dumper.h"

namespace NLogg
{

class CAssertDumper : public CDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( CAssertDumper, CDumper );

public:
  CAssertDumper( CLogger *pDefaultLogger );

  static void EnableAssertMessageBox(bool enable = true);

protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

private:
  CAssertDumper();

  threading::Mutex mutex;
};

}

#endif
