#ifndef _ASSERT_DUMPER_H_
#define _ASSERT_DUMPER_H_

#include "Dumper.h"

namespace NLogg
{

class TestAssertDumper : public CDumper
{
public:
    TestAssertDumper( CLogger *pDefaultLogger, const char *szName );
  virtual ~TestAssertDumper() { }
protected:
    virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );
private:
    TestAssertDumper();
};

void FailTestOnAnyError( bool fail );
void FailTestOnLogLevel( ELevel level, bool fail ); //Actually, only WARNING, ERROR, ASSERT & CRITICAL works

}

#endif
