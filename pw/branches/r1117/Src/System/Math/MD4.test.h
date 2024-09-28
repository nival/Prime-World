//!Component('System/Math/MD4')
//!Component('System/Commands')

#include <System/stdafx.h>
#include "cxxtest/TestSuite.h"

#include "MD4.h"

class Test_MD4 : public CxxTest::TestSuite
{
public:

    void test_Incremental()
    {
      math::MD4Generator md0;
      md0.Start();
      md0.Update((const byte*)"12", 2);
      md0.Update((const byte*)"34", 2);

      math::MD4Generator md1;
      md1.Start();
      md1.Update((const byte*)"1234", 4);
      TS_ASSERT_EQUALS(md0.Stop(), md1.Stop());
      TS_ASSERT_EQUALS(md0.Get(), md1.Get());
    }

    void test_MD5()
    {
      math::MD5Generator md0;
      md0.Start();
      md0.Update((const byte*)"12", 2);
      md0.Update((const byte*)"34", 2);

      math::MD5Generator md1;
      md1.Start();
      md1.Update((const byte*)"1234", 4);
      TS_ASSERT_EQUALS(md0.Stop(), md1.Stop());
      TS_ASSERT_EQUALS(md0.Get(), md1.Get());
    }

};

