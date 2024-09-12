#include "System/stdafx.h"
#include "System/ThreadPool.h"

#include <System/ServerStdOutDumper.h>
//#include <System/ServerTextFileDumper.h>
#include <System/FileSystem/FileUtils.h>
#include <System/LogFileName.h>
#include <System/BSUtil.h>

class Job : public threading::ITPJob
{
public:
  Job()
  {
  }

public:
  void Execute()
  {
    LOG_M(0).Trace("Do our fucking job 100500 times");
    ::Sleep(10);
  }
};

int main(int argc, char* argv[])
{
  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "GameTestClient", "private", 0, 0, 0, 0);
  ScopedPtr<NLogg::CServerStdOutDumper> stdoutDumper;
  Reset( stdoutDumper, new NLogg::CServerStdOutDumper( &GetSystemLog() ) );
  //ScopedPtr<NLogg::CServerTextFileDumper> textLogDumper;
  //Reset( textLogDumper, new NLogg::CServerTextFileDumper( &GetSystemLog() ) );
  NBSU::InitUnhandledExceptionHandler();
  //textLogDumper->SetFileName("output");

  threading::ThreadPool tp;
  tp.Open(10);

  unsigned int k = 100;
  while(k--)
  {
    Job j;
    for(unsigned int i = 0; i < 100500; ++i)
    {
      tp.pushJob(&j);
    }

    tp.WaitJobs();
  }

  tp.Close();
}
