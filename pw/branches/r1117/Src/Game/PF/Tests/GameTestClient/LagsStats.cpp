#include "stdafx.h"
#include "LagsStats.h"
#include "GTCLog.h"
#include <Server/AppFramework/Interfaces.h>


namespace ELagType
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char * ToString(Enum type)
{
  switch (type)
  {
  case Step: return "Step";
  case Queue: return "Queue";
  }
  return "<Unknown>";
}

} // namespace ELagType


namespace gtc
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LagsStats::Reset()
{
  clients.clear();
  avgTimeSum = 0;
  minTime = INT_MAX;
  maxTime = 0;
  count = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LagsStats::AddLag(const AppFramework::InstanceStatistics & stats, 
                        int _minTime, int avgTime, int _maxTime, int step, Transport::TClientId cid)
{
  clients.insert(cid);
  avgTimeSum += avgTime;
  if (_minTime < minTime) 
    minTime = _minTime;
  if (_maxTime > maxTime)
    maxTime = _maxTime;
  ++count;

  time_t startTimeStamp = stats.GetFirstStartTimeStamp();
  time_t endTimeStamp = stats.GetFinishTimeStamp();

  struct tm startTime;
  struct tm endTime;
  localtime_s(&startTime, &startTimeStamp);
  localtime_s(&endTime, &endTimeStamp);

  DebugTrace("%s lags detected: min:%d average:%d max:%d count:%d (cid=%d)", 
      ELagType::ToString(lagType), _minTime, avgTime, _maxTime, stats.GetLongTimeCount(), cid);
  DebugTrace("%s lags detected: start:%02d:%02d:%02d end:%02d:%02d:%02d step:%d (cid=%d)", 
      ELagType::ToString(lagType), startTime.tm_hour, startTime.tm_min, startTime.tm_sec, 
      endTime.tm_hour, endTime.tm_min, endTime.tm_sec, step, cid);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LagsStats::DumpLags()
{
  if (count > 0)
  {
    int avgTime = avgTimeSum / count;
    LOG_M( GameTestClient::StatusChannel ).Trace("%s lags: clients %d, min %d, avg %d, max %d, count %d", 
      ELagType::ToString(lagType), clients.size(), minTime, avgTime, maxTime, count);
    Reset();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LagsStats::SetType(ELagType::Enum type)
{
  NI_VERIFY( type >= 0 && type < ELagType::_Count, "Wrong lag type", return; );
  lagType = type;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LagsStatsContainer::Init()
{
  for (int i = 0; i < ELagType::_Count; ++i)
    lagsStats[i].SetType((ELagType::Enum)i);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LagsStatsContainer::AddLag(ELagType::Enum type, const AppFramework::InstanceStatistics & stats, 
             int minTime, int avgTime, int maxTime, int step, Transport::TClientId cid)
{
  TLagsStatsCont::iterator it = lagsStats.find(type);
  NI_VERIFY(it != lagsStats.end(), "Lags type not found", return; );
  it->second.AddLag(stats, minTime, avgTime, maxTime, step, cid);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LagsStatsContainer::DumpLags()
{
  for (TLagsStatsCont::iterator it = lagsStats.begin(); it != lagsStats.end(); ++it)
    it->second.DumpLags();
}

} // namespace gtc

//NI_DEFINE_REFCOUNT( gtc::Client_GS );
