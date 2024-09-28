#pragma once

#include "RPC/RPC.h"

namespace Monitoring
{

static const char * intfSuffix = ".mon";

struct PerfCounterSample : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  nstl::string  name;
  short rc;
  byte type;
  nstl::wstring val;
  time_t        time;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&name); f.Add(3,&rc); f.Add(4,&type); f.Add(5,&val); f.Add(6,&time); return 0; }

  PerfCounterSample() : rc(-1), type(0), time(0){} 
};


REMOTE class IPerfCounterProvider : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IPerfCounterProvider, IBaseInterfaceMT );

public:
  RPC_ID();

  REMOTE virtual nstl::vector<nstl::string> GetPerfCountersList() = 0;
  REMOTE virtual PerfCounterSample GetPerfCounterSample(char const * name) = 0;
};

}
