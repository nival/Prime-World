#include "SocialLobbyMMStatisticsEx.h"
#include "Server/LiveMMaking/LiveMMakingTypes.h"
#include "Db/DBServer.auto.h"
#include "SocialLobbyConfig.h"

const string GetBasketKey(const int i)
{
  switch (i)
  {
  case 0:
    return "Newbie";
  case 1:
    return "Leaver";
  default:
    return "Normal";
  }
}

int getWaitRRKey(const mmaking::SGame & _mmData, const NDb::AdvMapDescription* map)
{
  int key = 0;
  /*
  if (map->matchmakingSettings->useRanking)
  {
    StrongMT<mmaking::RankTable> ranks = new mmaking::RankTable();
    ranks->Init( map->matchmakingSettings );
    const mmaking::RankDescription * r = ranks->FindRank( _mmData.humans[0].members[0].heroRating) ;
    if ( r )
      return key + r->index;
  }
  else
  {*/
    vector< NDb::MMakingRank >::const_iterator cit = map->matchmakingSettings->ranks.begin();
    for ( ; cit !=  map->matchmakingSettings->ranks.end(); ++cit )
    {

      if (cit->lowRating > _mmData.humans[0].members[0].heroRating)
        return key;

      key = cit->lowRating;
    }
  //}
  return -1;
}

const pair<int, int> getWaitTimeModeKey(const mmaking::SGame & _mmData, const NDb::AdvMapDescription* map)
{
  int key =0;
  switch (map->mapType )
  {

  case NDb::MAPTYPE_PVP:
  case NDb::MAPTYPE_CTE:
  case NDb::MAPTYPE_TRAINING:
  case NDb::MAPTYPE_TUTORIAL:
  case NDb::MAPTYPE_SERIES:
  case NDb::MAPTYPE_COOPERATIVE:
    key = getWaitRRKey(_mmData, map);
    return make_pair( key !=-1? map->mapType:-1, key);
  default:
    return make_pair(-1, key);
  }
}


const pair<int, pair<int,int>> getWaitTimeGroupKey( const mmaking::SGame & _mmData, const NDb::AdvMapDescription* map )
{
  pair<int, int> key;
  switch (_mmData.basket)
  {
  case mmaking::EBasket::Newbie:
    key = getWaitTimeModeKey(_mmData,map);

    return make_pair(key.first!=-1? 0 :-1 ,key);

  case mmaking::EBasket::Leaver:
    key = getWaitTimeModeKey(_mmData,map);
    return make_pair(key.first!=-1? 1 :-1 ,key);

  case mmaking::EBasket::Normal:
    key = getWaitTimeModeKey(_mmData,map);
    return make_pair(key.first!=-1? 2 :-1 ,key);
  default:
    return make_pair(-1,key);
  }
}
void GatherMmStatisticsByMode( const NDb::AdvMapDescription* _map,   map< int, map< int, map<int, list<timer::Time>>> >& lastGameWaitTimesByMode,
                              map< int, map< int, map<int, timer::Time>>>& lastGameGatheredByMode, socialLobby::Config* _config, timer::Time now,
                              const mmaking::SGame & _mmData )
  {

    if ( !_map )
    {
      WarningTrace( "Unsupported map in game. map=%s", _mmData.mapId );
      return;
    }

    pair<int, pair<int, int>> waitTimeGroupKey = getWaitTimeGroupKey(_mmData, _map);

    if (waitTimeGroupKey.first < 0)
      return;

    timer::Time totalWait = 0;
    int total = 0;

    for ( int pi = 0; pi < _mmData.humans.size(); ++pi )
    {
      int sz = _mmData.humans[pi].members.size();
      total += sz;
      totalWait += _mmData.humans[pi].waitTime * sz;
    }
    NI_VERIFY( total, "", return );

    timer::Time avgWait = totalWait / total;
    lastGameWaitTimesByMode[waitTimeGroupKey.first][waitTimeGroupKey.second.first][waitTimeGroupKey.second.second].push_back( avgWait );

    while ( lastGameWaitTimesByMode[waitTimeGroupKey.first][waitTimeGroupKey.second.first][waitTimeGroupKey.second.second].size() > _config->mmWaitTimeLineLength )
      lastGameWaitTimesByMode[waitTimeGroupKey.first][waitTimeGroupKey.second.first][waitTimeGroupKey.second.second].pop_front();

    lastGameGatheredByMode[waitTimeGroupKey.first][waitTimeGroupKey.second.first][waitTimeGroupKey.second.second] = now;

  }

void GetServerStatusEx(  map< int, map< int, map<int, list<timer::Time>>> >& lastGameWaitTimesByMode,
                       map< int, map< int, map<int, timer::Time>>>& lastGameGatheredByMode, socialLobby::Config* _config, timer::Time now, TBasketAvgTimes& avgTimesPerMode)
{

  for ( map< int, map< int, map< int, list<timer::Time> > > >::iterator itb = lastGameWaitTimesByMode.begin(); itb != lastGameWaitTimesByMode.end(); ++itb )
  {
    const string basket = GetBasketKey((*itb).first);

    for( map<int, map< int, list<timer::Time> > > ::iterator itm = (*itb).second.begin(); itm != (*itb).second.end(); ++itm )
    {
      int mode = (*itm).first;
      for (map< int, list<timer::Time> >::iterator itr = (*itm).second.begin(); itr != (*itm).second.end(); ++itr )
      {
        avgTimesPerMode[basket][mode][(*itr).first] = 0;
        float totalWaitPerMode = 0;
        for (list<timer::Time>::iterator it = (*itr).second.begin(); it != (*itr).second.end(); ++it)
          totalWaitPerMode += (*it);

        avgTimesPerMode[basket][mode][(*itr).first] = (*itr).second.size() ? (totalWaitPerMode / (timer::Time)(*itr).second.size() ) : 0;
        avgTimesPerMode[basket][mode][(*itr).first] += ( now - lastGameGatheredByMode[(*itb).first][mode][(*itr).first] ) * _config->mmWaitTimeFactor;
        avgTimesPerMode[basket][mode][(*itr).first] = Min( avgTimesPerMode[basket][mode][(*itr).first], _config->mmWaitTimeLimit );

        //DebugTrace("avgTimesPerMode[%s][%d][%d] %f", basket.c_str(), mode, (*itr).first, avgTimesPerMode[basket][mode][(*itr).first]);
      }
    }
  }
}