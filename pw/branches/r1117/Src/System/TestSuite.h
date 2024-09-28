#ifndef TESTSUITE_H_C778C003_9F82_4EBF
#define TESTSUITE_H_C778C003_9F82_4EBF

#include "TestAssertDumper.h"

namespace test
{

struct AssertDisabler
{
  AssertDisabler()
  {
    NLogg::FailTestOnAnyError( false );
    DisableDebugAsserts();
  }
  ~AssertDisabler()
  {
    EnableDebugAsserts();
    NLogg::FailTestOnAnyError( true );
  }
};

} // test

#endif