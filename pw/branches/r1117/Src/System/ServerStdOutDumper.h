#pragma once

#include "Dumper.h"
#include "JobThread.h"

#include "System/InlineProfiler3/InlineProfiler3.h"

#ifdef NI_PLATF_LINUX

  typedef int HANDLE;

#endif

namespace NLogg
{

class CServerStdOutDumper : public CDumper
{
protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

public:
  class Job;

  CServerStdOutDumper( CLogger * pDefaultLogger ) :
  CDumper( pDefaultLogger, "stdout" )
  {
    Launch();
  }

  CServerStdOutDumper( CLogger * pDefaultLogger, NLogg::ELevel minLevel ) :
  CDumper( pDefaultLogger, "stdout" )
  {
    AddMinLevel( minLevel );
    Launch();
  }

  ~CServerStdOutDumper();

private:
  StrongMT<threading::JobThread> thread;
  StrongMT<Job> job;

  void Launch();
};

} //namespace NLogg
