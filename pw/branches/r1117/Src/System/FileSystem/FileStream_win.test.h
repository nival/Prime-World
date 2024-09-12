//!Component("System/Streams")
//!Component("System/Stream")
//!Component("System/Pointers/Pointers")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "../Stream.h"
#include "FileStream.h"
#include "FileStream_stdlib.h"
#include "MemoryLib/newdelete.h"

#include <iostream>
#include <stdlib.h>

class TestFileStream : public CxxTest::TestSuite
{
public:
  CObj<FileStream> fileStream;
  //CObj<StdLibFileStream> fileStream;

  virtual void setUp()
  {
    string fileName = "FileStream.dump";
    fileStream = new FileStream( "FileStream.dump", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
    //fileStream = new StdLibFileStream( "FileStream.dump", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
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

    std::cout << char(10) << "Running " << timesToWrite 
              << " dumps of " << writesPerItteration*sizeof(int) << " bytes";

    for (int i = 0; i < timesToWrite; ++i)
    {
      timer::Time t1 = timer::Now();

      for (int j = 0; j < writesPerItteration; ++j)
      {
        fileStream->Write(&j, sizeof(int));
      }

      fileStream->Flush();

      timer::Time t2 = timer::Now();

      double deltaTime = t2 - t1;
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

      std::cout << char(10) << deltaTime << " sec";
    }

    std::cout << char(10) << "Minimum: " << minTime << " sec";
    std::cout << char(10) << "Maximum: " << maxTime << " sec";
    std::cout << char(10) << "Average: " << totalTime/(double)timesToWrite << " sec" << char(10);

    //system("pause");

    //TS_ASSERT_LESS_THAN(2.0, t1 - t2);
  }

};
