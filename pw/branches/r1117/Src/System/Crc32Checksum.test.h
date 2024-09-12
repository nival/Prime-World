//!Component("System/Crc32Utils")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "Crc32Calculator.h"

class Test_Crc32Checksum : public CxxTest::TestSuite 
{
public:
  void test_Simple()
  {
    Crc32Checksum s;
    s.AddString("Test");
    s.Get();
  }

};
