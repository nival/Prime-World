//!Component("System/Streams")
//!Component("System/Stream")
//!Component("System/Pointers/Pointers")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "../Stream.h"
#include "FileWriteBufferedStream.h"
#include "MemoryLib/newdelete.h"

#include <iostream>
#include <stdlib.h>

class TestFileWrite2 : public CxxTest::TestSuite
{
public:
  CObj<FileWriteBufferedStream> fileWriteBufferedStream;

  virtual void setUp()
  {
    //string fileName = "FileWriteBufferedStream.dump";
    //fileWriteBufferedStream = new FileWriteBufferedStream(fileName, 1<<16, 1<<20);
  }

  virtual void tearDown()
  {
  }

  void TestMassiveSmallWrites()
  {
    const int timesToWrite = 20;
    const int writesPerItteration = 4096;
    double totalTime = 0;
    double minTime = 0;
    double maxTime = 0;
    
    string fileName = "FileWriteBufferedStream.dump";
    fileWriteBufferedStream = new FileWriteBufferedStream(fileName, 1<<16, 1<<20);

    std::cout << char(10) << "Running " << timesToWrite 
              << " dumps of " << writesPerItteration*sizeof(int) << " bytes";

    for (int i = 0; i < timesToWrite; ++i)
    {
      timer::Time t1 = timer::Now();

      for (int j = 0; j < writesPerItteration; ++j)
      {
        fileWriteBufferedStream->Write(&j, sizeof(int));
      }

      timer::Time t2 = timer::Now();

      fileWriteBufferedStream->Flush();

      timer::Time t3 = timer::Now();

      double deltaTime = t3 - t1;
      totalTime += deltaTime;

      if (i == 0)
      {
        minTime = deltaTime;
        maxTime = deltaTime;
      }
      else
      {
        if (minTime > deltaTime)
          minTime = deltaTime;
        if (maxTime < deltaTime)
          maxTime = deltaTime;
      }

      std::cout << char(10) << deltaTime << " sec." << " buffering: " << t2-t1 << " flush: " << t3-t2;
    }

    std::cout << char(10) << "Minimum: " << minTime << " sec";
    std::cout << char(10) << "Maximum: " << maxTime << " sec";
    std::cout << char(10) << "Average: " << totalTime/(double)timesToWrite << " sec" << char(10);

    /*system("pause");*/

    //TS_ASSERT_LESS_THAN(2.0, t1 - t2);
  }

};
