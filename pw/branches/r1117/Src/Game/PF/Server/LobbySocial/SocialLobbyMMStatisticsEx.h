#ifndef SOCIALLOBBYMMSTATISTICSEX_H_INCLUDED
#define SOCIALLOBBYMMSTATISTICSEX_H_INCLUDED

typedef nstl::map<int, float> TAvgRRTimes;
typedef nstl::map<int, TAvgRRTimes> TModeAvgTimes;
typedef nstl::map<string, TModeAvgTimes> TBasketAvgTimes;

namespace NDb
{
  struct AdvMapDescription;
  struct MMakingRank;
}

namespace socialLobby
{
  class Config;
  class IMaps;
}
namespace  mmaking
{ 
  struct SGame;
}

const string GetBasketKey(const int i);
int getWaitRRKey(const mmaking::SGame & _mmData, const NDb::AdvMapDescription* map);
const pair<int, int> getWaitTimeModeKey(const mmaking::SGame & _mmData, const NDb::AdvMapDescription* map);
const pair<int, pair<int,int>> getWaitTimeGroupKey( const mmaking::SGame & _mmData, const NDb::AdvMapDescription* map );
void GatherMmStatisticsByMode( const NDb::AdvMapDescription* _map,   map< int, map< int, map<int, list<timer::Time>>> >& lastGameWaitTimesByMode,
                              map< int, map< int, map<int, timer::Time>>>& lastGameGatheredByMode, socialLobby::Config* _config, timer::Time now,
                              const mmaking::SGame & _mmData );

void GetServerStatusEx(  map< int, map< int, map<int, list<timer::Time>>> >& lastGameWaitTimesByMode,
                       map< int, map< int, map<int, timer::Time>>>& lastGameGatheredByMode, socialLobby::Config* _config, timer::Time now, TBasketAvgTimes& avgTimesPerMode);

#endif //SOCIALLOBBYMMSTATISTICSEX_H_INCLUDED
