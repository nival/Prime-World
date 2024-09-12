#pragma once

#include "GameTestClientBase.h"


namespace AppFramework
{
  struct InstanceStatistics;
}


namespace ELagType
{
  enum Enum
  {
    Step,
    Queue,
    _Count
  };

  const char * ToString(Enum type);
}


namespace gtc
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LagsStats
{
public:
  LagsStats() : lagType(ELagType::Step) { Reset(); }

  void Reset();
  void AddLag(const AppFramework::InstanceStatistics & stats, 
               int _minTime, int avgTime, int _maxTime, int step, Transport::TClientId cid);
  void DumpLags();
  void SetType(ELagType::Enum type);

private:
  ELagType::Enum lagType;
  nstl::set<Transport::TClientId> clients;
  int avgTimeSum;
  int minTime;
  int maxTime;
  int count;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LagsStatsContainer
{
public:
  void Init();
  void AddLag(ELagType::Enum type, const AppFramework::InstanceStatistics & stats, 
               int minTime, int avgTime, int maxTime, int step, Transport::TClientId cid);
  void DumpLags();

private:
  typedef nstl::map<int, LagsStats> TLagsStatsCont;
  TLagsStatsCont lagsStats;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IClientsContainer : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(IClientsContainer, IBaseInterfaceMT);

public:
  virtual LagsStatsContainer & GetLagsStatsContainer() = 0;
};

} // namespace gtc
