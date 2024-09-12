#pragma once

namespace NDb
{
  struct HeroRanks;
  struct Rank;
  enum EFaction;
  struct MapMMakingSettings;
  struct MMakingRank;
}

namespace NGameX
{



class HeroRankCalculator: public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( HeroRankCalculator, BaseObjectST );
public:
  HeroRankCalculator(const NDb::HeroRanks * _heroRanks);
  HeroRankCalculator(const NDb::MapMMakingSettings * _sett);

  const NDb::Rank GetRank(int raiting);
  const NDb::MMakingRank GetMMRank(int raiting);
  const char * GetRankIcon(NDb::EFaction faction, const NDb::Rank & rank);
  const wstring & GetRankName(NDb::EFaction faction, const NDb::Rank & rank);

private:
  NDb::Ptr<NDb::HeroRanks> heroRanks;
  NDb::Ptr<NDb::MapMMakingSettings> dbSett;
};

}