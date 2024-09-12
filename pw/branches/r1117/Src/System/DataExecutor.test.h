//!Component('NSTL')
//!Component('DataExecutor')
//!Component('Streams')
//!Component('Base64')

#include "stdafx.h"

#if defined( NV_WIN_PLATFORM )
#pragma warning(disable: 4731)
#include "DataExecutor.h"
#endif // defined( NV_WIN_PLATFORM )
#include "cxxtest/TestSuite.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class DataExecutortest : public CxxTest::TestSuite
{
public:

  void testPushingAndPopping()
  {
#if defined( NV_WIN_PLATFORM )
    unsigned char const  getFloatZero[] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x8B ,0xEC ,0xD9 ,0xEE ,0x5D ,0xC3};
    DataExecutor execFloatZero(2, getFloatZero, sizeof(getFloatZero));
    unsigned char const  getFloatOne [] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x8B ,0xEC ,0xD9 ,0xE8 ,0x5D ,0xC3};
    DataExecutor execFloatOne(2, getFloatOne, sizeof(getFloatOne));
    unsigned char const  getInt32Zero[] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x8B ,0xEC ,0x33 ,0xC0 ,0x5D ,0xC3};    
    DataExecutor execInt32Zero(2, getInt32Zero, sizeof(getInt32Zero));
    unsigned char const  getInt32One [] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x8B ,0xEC ,0xB8 ,0x01 ,0x00 ,0x00 ,0x00 ,0x5D ,0xC3};    
    DataExecutor execInt32One(2, getInt32One, sizeof(getInt32One));
    unsigned char const  getBoolFalse[] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x8B ,0xEC ,0x32 ,0xC0 ,0x5D ,0xC3};    
    DataExecutor execBoolFalse(2, getBoolFalse, sizeof(getBoolFalse));
    unsigned char const  getBoolTrue [] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x8B ,0xEC ,0xB0 ,0x01 ,0x5D ,0xC3};    
    DataExecutor execBoolTrue(2, getBoolTrue, sizeof(getBoolTrue));

    TS_ASSERT_EQUALS(execFloatZero.ExecuteFree<float>(NULL, NULL, NULL), 0);
    TS_ASSERT_EQUALS(execFloatZero.ExecuteFree<float>(), 0);
    TS_ASSERT_EQUALS(execFloatZero.ExecuteFree<float>("Supremacy"), 0);

    TS_ASSERT_EQUALS(execFloatOne.ExecuteFree<float>(NULL, NULL, NULL), 1.0f);
    TS_ASSERT_EQUALS(execFloatOne.ExecuteFree<float>(), 1.0f);
    TS_ASSERT_EQUALS(execFloatOne.ExecuteFree<float>("Supremacy"), 1.0f);

    TS_ASSERT_EQUALS(execInt32Zero.ExecuteFree<int>(NULL, NULL, NULL), 0);
    TS_ASSERT_EQUALS(execInt32Zero.ExecuteFree<int>(), 0);
    TS_ASSERT_EQUALS(execInt32Zero.ExecuteFree<int>("Supremacy"), 0);

    TS_ASSERT_EQUALS(execInt32One.ExecuteFree<int>(NULL, NULL, NULL), 1);
    TS_ASSERT_EQUALS(execInt32One.ExecuteFree<int>(), 1);
    TS_ASSERT_EQUALS(execInt32One.ExecuteFree<int>("Supremacy"), 1);

    TS_ASSERT_EQUALS(execBoolFalse.ExecuteFree<bool>(NULL, NULL, NULL), false);
    TS_ASSERT_EQUALS(execBoolFalse.ExecuteFree<bool>(), false);
    TS_ASSERT_EQUALS(execBoolFalse.ExecuteFree<bool>("Supremacy"), false);

    TS_ASSERT_EQUALS(execBoolTrue.ExecuteFree<bool>(NULL, NULL, NULL), true);
    TS_ASSERT_EQUALS(execBoolTrue.ExecuteFree<bool>(), true);
    TS_ASSERT_EQUALS(execBoolTrue.ExecuteFree<bool>("Supremacy"), true);

    TS_ASSERT_EQUALS(execFloatZero.Execute<float>((const void *)0, NULL, NULL), 0);
    TS_ASSERT_EQUALS(execFloatOne.Execute <float>((const void *)0, NULL, NULL), 1.0f);
    TS_ASSERT_EQUALS(execInt32Zero.Execute<int>  ((const void *)0, NULL, NULL), 0);
    TS_ASSERT_EQUALS(execInt32One.Execute <int>  ((const void *)0, NULL, NULL), 1);
    TS_ASSERT_EQUALS(execBoolFalse.Execute <bool>((const void *)0, NULL, NULL), false);
    TS_ASSERT_EQUALS(execBoolTrue.Execute <bool> ((const void *)0, NULL, NULL), true);
#endif // defined( NV_WIN_PLATFORM ) 
  }
};

