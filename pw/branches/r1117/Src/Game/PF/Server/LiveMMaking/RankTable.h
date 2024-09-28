#ifndef MM_RANKTABLE_H_INCLUDED
#define MM_RANKTABLE_H_INCLUDED

#include "IMMakingLogic.h"

namespace NDb
{
  struct MapMMakingSettings;
}


namespace mmaking
{

class RankTable : public IRankTable, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RankTable, IRankTable, BaseObjectMT );

public:
  RankTable() {}

  bool Init( const NDb::MapMMakingSettings * _sett );

  EBasket::Enum getBasket(const int i) const;
  virtual const RankDescription * FindRank( float _rating ) const;
  virtual const RankDescription * FindRankByIndex( int _idx  ) const;
  virtual const RankDescription * FindRankByMergedIndex( int _mergedIdx ) const;
  virtual int RanksNumber() const { return ranks.size(); }
  virtual int MergedRanksNumber() const { return mergedIdx2Rank.size(); }


private:
  vector<RankDescription>   ranks;
  vector<int>               mergedIdx2Rank;
};


} //namespace mmaking

#endif //MM_RANKTABLE_H_INCLUDED
