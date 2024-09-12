#include <System/stdafx.h>
#include <cxxtest/TestSuite.h>
#include "PeeredImpl.h"
#include <System/TestSuite.h>

struct Test_BlockHistory : public CxxTest::TestSuite
{
  void test_EraseX()
  {
    Peered::BlockHistory h;
    nstl::vector<rpc::MemoryBlock> data;

    h.Append("Hi0", 3);
    h.Append("Hi1", 3);

    h.FinishStep(); //0
    h.FinishStep(); //1
    h.FinishStep(); //2

    h.CopyStep(0, data);
    TS_ASSERT_EQUALS(2, data.size());
    TS_ASSERT_SAME_DATA("Hi0", data[0].memory, data[0].size);
    TS_ASSERT_SAME_DATA("Hi1", data[1].memory, data[1].size);
    h.CopyStep(1, data);
    TS_ASSERT_EQUALS(0, data.size());

    h.EraseSteps(2);

    h.FinishStep(); //3
    h.FinishStep(); //4

    h.CopyStep(2, data);
    TS_ASSERT_EQUALS(0, data.size());
    h.CopyStep(3, data);
    TS_ASSERT_EQUALS(0, data.size());
  }

  void test_Simple()
  {
    Peered::BlockHistory h;

    TS_ASSERT_EQUALS(0, h.GetAccumulatedItemsCount());

    h.Append("data0", 5);
    TS_ASSERT_EQUALS(1, h.GetAccumulatedItemsCount());

    h.Append("data1", 5);
    TS_ASSERT_EQUALS(2, h.GetAccumulatedItemsCount());

    h.FinishStep();
    TS_ASSERT_EQUALS(0, h.GetAccumulatedItemsCount());

    nstl::vector<rpc::MemoryBlock> data;
    h.CopyStep(0, data);
    TS_ASSERT_EQUALS(2, data.size());
    TS_ASSERT_SAME_DATA("data0", data[0].memory, data[0].size);
    TS_ASSERT_SAME_DATA("data1", data[1].memory, data[1].size);

    test::AssertDisabler ad;

    h.CopyStep(1, data);
    TS_ASSERT_EQUALS(0, data.size());

    h.CopyStep(-1, data);
    TS_ASSERT_EQUALS(0, data.size());
  }

  void test_TwoSteps()
  {
    Peered::BlockHistory h;

    h.Append("Test0", 5);
    h.Append("Test1", 5);
    h.FinishStep();

    h.Append("Test2", 5);
    h.FinishStep();

    nstl::vector<rpc::MemoryBlock> data;
    h.CopyStep(0, data);
    TS_ASSERT_EQUALS(2, data.size());
    TS_ASSERT_SAME_DATA("Test0", data[0].memory, data[0].size);
    TS_ASSERT_SAME_DATA("Test1", data[1].memory, data[1].size);

    h.CopyStep(1, data);
    TS_ASSERT_EQUALS(1, data.size());
    TS_ASSERT_SAME_DATA("Test2", data[0].memory, data[0].size);
  }

  void test_EraseSteps()
  {
    Peered::BlockHistory h;

    h.Append("Test0", 5);
    h.Append("Test1", 5);
    h.FinishStep();

    h.Append("Test2", 5);
    h.FinishStep();

    h.Append("Test3", 5);

    h.EraseSteps(1);

    nstl::vector<rpc::MemoryBlock> data;

    {
      test::AssertDisabler ad;

      h.CopyStep(0, data);
      TS_ASSERT_EQUALS(0, data.size());
    }

    h.CopyStep(1, data);
    TS_ASSERT_EQUALS(1, data.size());
    TS_ASSERT_SAME_DATA("Test2", data[0].memory, data[0].size);

    h.FinishStep();
    h.CopyStep(2, data);
    TS_ASSERT_EQUALS(1, data.size());
    TS_ASSERT_SAME_DATA("Test3", data[0].memory, data[0].size);
  }

  void test_EraseMultiSteps()
  {
    Peered::BlockHistory h;

    h.Append("Hi0", 3);
    h.Append("Hi1", 3);
    h.FinishStep();

    h.Append("Hi2", 3);
    h.Append("Hi3", 3);
    h.Append("Hi4", 3);
    h.FinishStep();

    h.Append("Hi5", 3);
    h.Append("Hi6", 3);
    h.FinishStep();

    h.Append("Hi7", 3);

    h.EraseSteps(2);
    h.FinishStep();

    nstl::vector<rpc::MemoryBlock> data;

    {
      test::AssertDisabler ad;

      for (int i=0;i<3;++i)
      {
        h.CopyStep(0, data);
        TS_ASSERT_EQUALS(0, data.size());
      }
    }

    h.CopyStep(3, data);
    TS_ASSERT_EQUALS(1, data.size());
    TS_ASSERT_SAME_DATA("Hi7", data[0].memory, data[0].size);
  }

  void test_EraseAllStepsWithNoPendingCommands()
  {
    Peered::BlockHistory h;

    h.Append("Test0", 5);
    h.Append("Test1", 5);
    h.FinishStep();

    h.Append("Test2", 5);
    h.FinishStep();

    h.EraseSteps(2);

    test::AssertDisabler ad;

    nstl::vector<rpc::MemoryBlock> data;
    h.CopyStep(0, data);
    TS_ASSERT_EQUALS(0, data.size());
    h.CopyStep(1, data);
    TS_ASSERT_EQUALS(0, data.size());
    h.CopyStep(2, data);
    TS_ASSERT_EQUALS(0, data.size());

    h.Append("Test3", 5);
    h.FinishStep();

    h.CopyStep(2, data);
    TS_ASSERT_EQUALS(1, data.size());
    TS_ASSERT_SAME_DATA("Test3", data[0].memory, data[0].size);
  }

  void test_EraseEmptySteps()
  {
    Peered::BlockHistory h;

    h.FinishStep();
    h.FinishStep();

    h.EraseSteps(2);
  }

  void test_SecondErase()
  {  
    Peered::BlockHistory h;

    for (int i=0;i<20;++i)    
    {
      h.Append("Test", 4);
      h.FinishStep();
    }
    h.EraseSteps(20);
    for (int i=0;i<10;++i)    
    {
      h.Append("Test", 4);
      h.FinishStep();
    }
    h.EraseSteps(30);
  }

  void test_EraseAllSteps()
  {
    Peered::BlockHistory h;
    for (int i=0;i<20;++i)
    {
      h.Append("Test", 4);
      h.FinishStep();
    }
    TS_ASSERT_EQUALS(20, h.EraseSteps(20));
    for (int i=0;i<10;++i)
    {
      h.Append("Test", 4);
      h.FinishStep();
    }
    TS_ASSERT_EQUALS(10, h.EraseSteps(30));
    for (int i=0;i<10;++i)
    {
      h.Append("Test", 4);
      h.FinishStep();
    }
    TS_ASSERT_EQUALS(10, h.EraseSteps(40));
    TS_ASSERT_EQUALS(0, h.EraseSteps(41));
  }


  void test_Stress()
  {
    Peered::BlockHistory h;
    int startStep = 0;
    int logsSteps = 5;

    const char* datas[5] = {
      "Dataaaa0-5",
      "Dataaaa1-0",
      "Dataaaa1-5",
      "Dataaaa2-0",
      "Dataaaa2-5",
    };

    for (int x=0;x<5;++x)
    {
      for (int k=0;k<10;++k)
      {
        char buffer[16] = "DataaaaX-K";
        buffer[7] = 48+x;
        buffer[9] = 48+k;
        h.Append(buffer, 10);
        h.FinishStep();
      }
      startStep += logsSteps;
      h.EraseSteps(startStep);

      nstl::vector<rpc::MemoryBlock> data;
      h.CopyStep(startStep, data);
      TS_ASSERT_SAME_DATA(datas[x], data[0].memory, data[0].size);
    }
  }
};

