#include "StdAfx.h"
#include "HeroRankCalculator.h"
#include "DBHeroRanks.h"
#include "DBServer.h"

namespace NGameX
{



HeroRankCalculator::HeroRankCalculator( const NDb::HeroRanks * _heroRanks )
: heroRanks(_heroRanks)
{}

HeroRankCalculator::HeroRankCalculator( const NDb::MapMMakingSettings * _sett )
: dbSett(_sett)
{}

const NDb::MMakingRank HeroRankCalculator::GetMMRank(int raiting)
{
  if (dbSett->ranks.empty())
     return NDb::MMakingRank();
  
  int rank = 0;
  for ( const int totalRanks = dbSett->ranks.size() - 1; rank < totalRanks && raiting >= dbSett->ranks[rank+1].lowRating; rank++ ) {}

  return dbSett->ranks[rank];

}

const NDb::Rank HeroRankCalculator::GetRank( int raiting )
{
  if (!heroRanks)
    return NDb::Rank();

  // find a rank corresponding to the specified hero rating
  int rank = 0;
  for ( const int totalRanks = heroRanks->ranks.size() - 1; rank < totalRanks && raiting >= heroRanks->ranks[rank+1].rating; rank++ ) {}

  return heroRanks->ranks[rank];
}

const char * HeroRankCalculator::GetRankIcon( NDb::EFaction faction, const NDb::Rank & rank )
{
  const NDb::Texture * texture = faction == NDb::FACTION_FREEZE? rank.iconA: rank.iconB;
  if (texture)
    return texture->textureFileName.c_str();

  return "";
}

const wstring & HeroRankCalculator::GetRankName( NDb::EFaction faction, const NDb::Rank & rank )
{
  return faction == NDb::FACTION_FREEZE? rank.rankNameA.GetText(): rank.rankNameB.GetText();
}
}


NI_DEFINE_REFCOUNT( NGameX::HeroRankCalculator )

