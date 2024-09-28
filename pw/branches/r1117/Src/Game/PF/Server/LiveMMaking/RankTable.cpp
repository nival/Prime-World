#include "stdafx.h"
#include "RankTable.h"
#include "Db/DBServer.auto.h"


NI_DEFINE_REFCOUNT( mmaking::RankTable );

namespace mmaking
{

  EBasket::Enum RankTable::getBasket(const int i) const
  {
    return i ? EBasket::Normal : EBasket::Newbie;
  }

bool RankTable::Init( const NDb::MapMMakingSettings * _sett )
{
  mergedIdx2Rank.reserve( _sett->ranks.size() );

  ranks.resize( _sett->ranks.size() );
  int mergedIndex = 0;
  for ( int i = 0; i < _sett->ranks.size(); ++i )
  {
    const NDb::MMakingRank & src = _sett->ranks[i];
    RankDescription & dest = ranks[i];

    dest.from = src.lowRating;
    dest.index = i;
    dest.mergedIndex = mergedIndex;
    dest.mergeRanksCount = src.mergeRanksCount;
    dest.basket = getBasket(i);
    dest.name = src.debugName;
    dest.useForceMM = src.useForceMM;
    dest.usePlayerRatingMM = src.usePlayerRatingMM;

    if ( i > 0 )
      ranks[i - 1].to = src.lowRating;

    if ( !src.mergeWithNextRank )
    {
      mergedIdx2Rank.push_back( i );
      ++mergedIndex;
    }
  }

  NI_VERIFY( !ranks.empty(), "No MM ranks data", return false );

  ranks.back().to = ranks.back().from * 10;

  for ( int i = 0; i < ranks.size(); ++i )
    ranks[i].highRating = ( 0.5 * ( ranks[i].from + ranks[i].to ) ) > _sett->locationPingSettings.ratingThreshold;

  return true;
}




const RankDescription * RankTable::FindRank( float _rating ) const
{
  NI_VERIFY( !ranks.empty(), "", return 0 );

  for ( int i = 0; i + 1 < ranks.size(); ++i )
  {
    if ( _rating < ranks[i + 1].from )
      return &ranks[i];
  }

  return &ranks.back();
}



const RankDescription * RankTable::FindRankByIndex( int _idx  ) const
{
  NI_VERIFY( _idx >= 0 && _idx < ranks.size(), "", return 0 );

  return &ranks[_idx];
}



const RankDescription * RankTable::FindRankByMergedIndex( int _mergedIdx ) const
{
  NI_VERIFY( _mergedIdx  >= 0 && _mergedIdx < mergedIdx2Rank.size(), "", return 0 );
  
  int idx = mergedIdx2Rank[_mergedIdx];

  NI_VERIFY( idx >= 0 && idx < ranks.size(), "", return 0 );
  return &ranks[idx];
}

} //namespace mmaking
