
#ifndef __ROLLTOOLS_H__
#define __ROLLTOOLS_H__

#include "RollTypes.h"
#include "Db/DBServer.auto.h"

namespace roll
{
  namespace RollTools
  {
    int RankFromRating(int rating);
    int RatingFromRank(int rating);

    ///////////////////////////////////////////////////////////////////////////

    nstl::vector<roll::SAwardInfo>::iterator FindAwardByType(nstl::vector<roll::SAwardInfo>& awards, roll::EAwardType::Enum  type);

    void EnumMapsAsString(const vector< NDb::Ptr< NDb::AdvMapDescription > > maps, string& mapsAsString);
    void VectorToString(const vector<string>& v, string& mapsAsString);
  };
};

#endif//__ROLLTOOLS_H__