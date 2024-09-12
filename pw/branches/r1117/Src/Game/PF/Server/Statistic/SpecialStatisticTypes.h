#pragma once
#include "Server/RPC/base.h"

namespace StatisticService
{

namespace RPC
{

struct PermittedStatisticsMethods : rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  vector<int> methods;
  vector<int> sessionEvents;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&methods); f.Add(3,&sessionEvents); return 0; }

  PermittedStatisticsMethods()
  {}
};

} //namespace RPC

} //namespace StatisticService
