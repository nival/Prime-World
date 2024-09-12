#pragma once

#include "Server/RPC/base.h"

namespace StatisticService
{

namespace RPC
{

struct SessionEventInfo
{
  ZDATA
  int intParam1;
  int intParam2;
  int intParam3;
  int intParam4;
  int intParam5;
  nstl::wstring strParam1;
  nstl::wstring strParam2;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&intParam1); f.Add(3,&intParam2); f.Add(4,&intParam3); f.Add(5,&intParam4); f.Add(6,&intParam5); f.Add(7,&strParam1); f.Add(8,&strParam2); return 0; }

  SessionEventInfo() :
  intParam1(0),
  intParam2(0),
  intParam3(0),
  intParam4(0),
  intParam5(0)
  {}
};



struct SessionDamageInfo
{
  ZDATA
  bool dealt;
  int opponentId;
  int unitType;
  int talentId;
  float physicalDamage;
  float magicalDamage;
  float pureDamage;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&dealt); f.Add(3,&opponentId); f.Add(4,&unitType); f.Add(5,&talentId); f.Add(6,&physicalDamage); f.Add(7,&magicalDamage); f.Add(8,&pureDamage); return 0; }
};

} //namespace RPC

} //namespace StatisticService
