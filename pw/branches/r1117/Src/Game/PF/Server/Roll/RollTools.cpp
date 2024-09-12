
#include "RollTools.h"

#include "RollLog.h"
#include "Db/DBServer.auto.h"
#include "PF_GameLogic/PFResourcesCollection.h"
#include "nalgoritm.h"


int roll::RollTools::RankFromRating( int rating )
{
  int rank = 0;

  NDb::Ptr< NDb::HeroRanks > heroRanks = NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->heroRanks;
  if(!heroRanks || (rank < 0 || rank > heroRanks->ranks.size())) 
  {
    ROLL_LOG_ERR("RatingFromRank failed. Return default value: 0");
  }
  else
  {
    int maxRank = heroRanks->ranks.size() - 1 ;
    for(int i = 0; i < heroRanks->ranks.size(); ++i)
    {
      if(heroRanks->ranks[i].rating > rating)
      {
        rank = i > 0 ? i - 1:i;
        break;
      }

      if(i == maxRank)
      {
        rank = i;
      }
    }
  }
  return rank;
}

int roll::RollTools::RatingFromRank( int rank )
{
  int rating = 0;
  NDb::Ptr< NDb::HeroRanks > heroRanks = NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->heroRanks;
  
  if(!heroRanks || (rank < 0 || rank > heroRanks->ranks.size())) 
  {
    ROLL_LOG_ERR("RatingFromRank failed. Return default value: 0");
  }
  else
  {
    rating = heroRanks->ranks[rank].rating;
  }

  return rating;
}

///////////////////////////////////////////////////////////////////////////////

nstl::vector<roll::SAwardInfo>::iterator roll::RollTools::FindAwardByType(nstl::vector<roll::SAwardInfo>& awards, roll::EAwardType::Enum  type)
{
  struct find_
  {
    find_(roll::EAwardType::Enum  type) : type_(type){}
    bool operator()(const roll::SAwardInfo& award)
    {
      return award.type == type_;
    }
    roll::EAwardType::Enum  type_;
  };

  return nstl::find_if(awards.begin(), awards.end(), find_(type));
}

void roll::RollTools::EnumMapsAsString(const vector< NDb::Ptr< NDb::AdvMapDescription > > maps, string& mapsAsString)
{
  struct MapsEnumerator
  {
    MapsEnumerator(string * outMapsAsString) : out_(outMapsAsString) { }
    void operator()(const NDb::Ptr< NDb::AdvMapDescription > map)
    {
      string mapId = map->GetDBID().GetFormatted();
      if(!mapId.empty())
      {
        (*out_) += mapId;
        (*out_) += ", ";
      }
    }
    string * out_;
  };

  nstl::for_each(maps.begin(), maps.end(), MapsEnumerator(&mapsAsString));
}

void roll::RollTools::VectorToString(const vector<string>& v, string& outString)
{
  struct StringEnumerator
  {
    StringEnumerator(string * outAsString) : out_(outAsString) { }
    void operator()(const string& value)
    {
        (*out_) += value;
        (*out_) += ", ";
    }
    string* out_;
  };

  nstl::for_each(v.begin(), v.end(), StringEnumerator(&outString));
}


