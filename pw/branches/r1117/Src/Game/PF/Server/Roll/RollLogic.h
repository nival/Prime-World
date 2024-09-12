#pragma once

#include "RPC/RPC.h"
#include "RollTypes.h"
#include "RollConfig.h"
#include "System/RandomGenerator.h"
#include "Server/Db/DBServer.auto.h"
#include "TalentRollDataCache.h"
#include "RollTools.h"
#include "RollBuff.h"

namespace NWorld
{
  class PFResourcesCollection;
}

namespace roll
{

//class TalentRollDataCache;

#ifdef PW_UNIT_TEST
  namespace dbg{
   class DropNRollTests;
  }
#endif// PW_UNIT_TEST

  class ClanWarsAwardsSettingsHolder
  {
  public:
    ClanWarsAwardsSettingsHolder(const NDb::ClanWarsSettings* cwSettings, int teamSize, const NDb::ModeRollSettings* rollSettings)
      :teamSize_(teamSize), cwSettings_(cwSettings), rollSettings_(rollSettings) {}

    const NDb::ClanWarsSettings* GetSettings() const{ return cwSettings_;}
    const NDb::ModeRollSettings* GetRollSettings() const{ return rollSettings_;}
    const int GetTeamSize() const{ return teamSize_;}

  private:

    int teamSize_;
    const NDb::ClanWarsSettings* cwSettings_ ;
    const NDb::ModeRollSettings* rollSettings_;

  };

  class GuildWarEventrPointsCalculator;

class DropNRoll : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( DropNRoll, BaseObjectST );

public:
  static NDb::Ptr<NDb::RollSettings> DbRoot();

  DropNRoll( IConfigProvider * _cfg, const NDb::RollSettings * _rollSettings, const NDb::Ptr<NDb::MapList>& mapList, NWorld::PFResourcesCollection* _talentsCollection );

  void Poll( timer::Time now );

  void RollAwards( vector<SUserAward> & _rollResult, map<NCore::TGuildAuid, SGuildAward> & _guildAwards, const SPreGameData & _preGame, const SPostGameData & _postGame );
  void RollForge( SUserAward & _award, const SForgeRollData & _data );

private:
  struct RollContext;
  struct RollGuildData;
  struct RollInputData;

  typedef nstl::vector<NDb::Ptr<NDb::RollContainer>> TContainers;

  StrongMT<IConfigProvider> config;
  NDb::Ptr<NDb::RollSettings> rollSettings;
  NDb::Ptr<NDb::HeroRanks> heroRanks;
  CObj<NWorld::PFResourcesCollection> talentsCollection;
  NRandom::RandomGenerator random;

  typedef map<int,vector<NDb::Ptr<NDb::Talent>>> TalentGroupCollection;
  vector<TalentGroupCollection> talentRollTable;
  vector<Transport::TClientId> dropAllClientIds;

  Strong<TalentRollDataCache> rollDataCache;
  Strong<roll::buff::RollBonusDataCache> rollBonusDataCache;

  inline bool IsResource(EAwardType::Enum value);
  void ResetRollData( RollContext & ctx, const NDb::RollContainer * container, const int version = -1 );
  void ValidateRollData( RollContext & ctx, const NDb::RollContainer * container, const int version, const ni_detail::UInt64 userId );
  void _RollPlayersAwardsFromContainer( vector<SAwardInfo> & _awards, RollContext & ctx, const NDb::RollContainer* container, const RollInputData & userPreGame );

  void _RollItemToContainer( vector<SAwardInfo> &_awards, RollContext & ctx, const NDb::RollItem* rollItem, const NDb::RollContainer* container, const RollInputData & userPreGame );
  void GenerateRollTables( const NDb::Ptr<NDb::MapList>& mapList );
  void FillRollTableFromContainer( const NDb::RollContainer* rollContainer, const int allowedRollGroups  );

  void RollPlayersAwardsFromContainer(vector<SAwardInfo>& _awards, RollContext & ctx, const NDb::RollContainer* container, const RollInputData & userPreGame );

  float GetEnduranceCoeff(EAwardType::Enum awardType, const NDb::ModeRollSettings* settings, bool isHeroTired, NCore::EBasket::Enum basket);

  void RollRating( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const NDb::AdvMapDescription * _map );
  void RollSingleRating( vector<SUserAward> & _rollResult, EAwardType::Enum type, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, float NCore::PlayerInfo::*ratingField, const NDb::AdvMapDescription * _map );

  void AwardHeroEnergy( vector<SUserAward> & _award, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame );
  void AwardHeroExperienceAndFame( vector<SUserAward> & _award, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg );
  
  void RollContainers( vector<SUserAward> & _award, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg );
  bool RollEventContainers( SUserAward & userAward, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData, const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, const bool isPlayerVictorious, const RollConfig* _cfg );
  void RollUsualContainers( SUserAward & userAward, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData, const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, const bool isPlayerVictorious, const RollConfig* _cfg );
  void RollContainerForScore(SUserAward & userAward, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData, 
    const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, const bool isPlayerVictorious, const RollConfig* _cfg,
    RollInputData & userRollInput, RollContext & ctx, const NDb::RollContainer* container);
  void RollContainerForAdditionalScore(SUserAward & userAward, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData, 
    const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, const bool isPlayerVictorious, const RollConfig* _cfg,
    RollInputData & userRollInput, RollContext & ctx, const NDb::RollContainer* container);
  void RollDefaultContainer(SUserAward & userAward, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData, 
    const SPostGamePerUserData & userPostData, const SPreGameData & _preGame, const bool isPlayerVictorious, const RollConfig* _cfg,
    RollInputData & userRollInput, RollContext & ctx);
  
  void RollReliabilityAndDodge( vector<SUserAward> & _award, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame );
  void RollEndurance( vector<SUserAward> & _award, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame );
  void RollFWOD( vector<SUserAward> & _award, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg );
  void ApplyPremium( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg );
  void RollMarketingEvents( vector<SUserAward> & _rollResult, const SPreGameData & _preGame, const SPostGameData & _postGame );

  void FillRollGuildData( const SPreGameData & _preGame, const SPostGameData & _postGame, map<NCore::TGuildAuid,RollGuildData>& _rollGuildsData );
  void RollGuildAwards( map<NCore::TGuildAuid, SGuildAward>& _guildAwards, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const NDb::AdvMapDescription * _map );
  void RollGuildMembersAwards( vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame );

  void RollClanWarUsersAwards( vector<SUserAward> & _rollResult, GuildWarEventrPointsCalculator& calculator);
  void PrepareClanWarGuildsAwards( vector<SUserAward> & _rollResult, map<NCore::TGuildAuid, SGuildAward>& _guildAwards, GuildWarEventrPointsCalculator& calculator );
  void ApplyBuffs(vector<SUserAward> & _rollResult, const NDb::ModeRollSettings * settings, const SPreGameData & _preGame, const SPostGameData & _postGame, const RollConfig* _cfg );

  void RollTalentsBuff(SUserAward& userAward, buff::RollBonusContext* rollBonusContext, const NDb::ModeRollSettings * settings, const SPreGamePerUserData & userPreData);

  void ParseDropAllClientIds();
  void DropAllAwards( vector<SAwardInfo> & _awards );

  void UpdateRollDataCache( vector<SUserAward> & _rollResult );
  void UpdateRollBuffStatistics(vector<SUserAward> & _rollResult);

  void ApplyBuffsOnUserAwards(const SPreGamePerUserData & userPreData, vector<SUserAward>& userAwards, const NDb::ModeRollSettings * settings);

#ifdef PW_UNIT_TEST
public:
  IConfigProvider * GetConfig() const{return config.GetSafe();}
  const NDb::Ptr<NDb::HeroRanks>& GetHeroRanks(){return heroRanks;}
  friend class roll::dbg::DropNRollTests;
#endif//PW_UNIT_TEST
};

///////////////////////////////////////////////////////////////////////////////

class ClanDataAgregator
{
public:
  struct ClanMemberData
  {
    ClanMemberData(lobby::TGuildAuid cid, Transport::TClientId pid, bool isWinner, lobby::ETeam::Enum team, float score, bool hasPremium)
      :pid_(pid), isWinner_(isWinner), cid_(cid), team_(team), sessionScore(score), hasPremium_(hasPremium) {}

    Transport::TClientId pid_;
    bool isWinner_;
    lobby::TGuildAuid cid_;
    lobby::ETeam::Enum team_;
    float sessionScore;
    bool hasPremium_;
  };

  typedef nstl::map<lobby::TGuildAuid, nstl::vector<ClanMemberData>> TClanMembers;
  typedef nstl::vector<ClanMemberData> TMembers;
  typedef nstl::vector<lobby::TGuildAuid> TWinClans;
  typedef nstl::vector<lobby::TGuildAuid> TClansInBothTeam;

public:
  void AddMember(lobby::TGuildAuid cId, Transport::TClientId pId, bool isWinner, lobby::ETeam::Enum team, float score, bool hasPremium);
  const ClanMemberData* FindMember(Transport::TClientId pId);
  bool IsClanInWinnersTeam(lobby::TGuildAuid cid);
  bool IsClanInBothTeam( lobby::TGuildAuid cid );
  size_t MembersCount(lobby::TGuildAuid cId);
  size_t ClansCount();

private:
  TClanMembers clansMembers_;
  TWinClans clansInWinnerTeam_;
};


class GuildWarEventrPointsCalculator
{
  struct PartyUser
  {
    PartyUser(uint pid, Transport::TClientId uid, float u_rating)
      : pid_(pid), uid_(uid), u_rating_(u_rating)
    {
      rank_ = RollTools::RankFromRating(u_rating_);
    }

    uint pid_;
    Transport::TClientId uid_;
    float u_rating_;
    int rank_;
  };

  typedef nstl::vector<roll::SAwardInfo> TSAwardInfoVec;
  typedef nstl::vector<roll::SPreGamePerUserData> TSPreGamePerUserDataUsers;
  typedef nstl::map<lobby::ETeam::Enum, int> TPlayersInParties;

public:
  GuildWarEventrPointsCalculator(const ClanWarsAwardsSettingsHolder& cwSettings, const SPreGameData& preGame, const SPostGameData& postGame);

  void CalculatePoints(nstl::vector<roll::SUserAward> & playersAwards);
  void FinalizeClanWarAwards(vector<roll::SUserAward> & playersAwards, map<NCore::TGuildAuid, SGuildAward>& guildAwards);
  bool IsValidSettings() const;
  
private:

  bool CollectClanMembersData();
  int GetMaxHeroRankInTeam(lobby::ETeam::Enum team);
  bool IsTeamFullParty(lobby::ETeam::Enum team);

  void AddClanPoints(map<NCore::TGuildAuid, SGuildAward>& guildAwards, NCore::TGuildAuid clanId, float count, roll::EAwardType::Enum pointsType);

  GuildWarEventrPointsCalculator& operator=(const GuildWarEventrPointsCalculator&);
  float GetPartyClanMembersModifierBonus(lobby::TGuildAuid clanId);
  float GetFoeCountsModifierBonus(int foeCount);
  float GetDefeatedFoeRankModifierBonus(float rank);

  int GetFoeInPartiesCount(lobby::ETeam::Enum team);

private:
   const ClanWarsAwardsSettingsHolder& cwSettings_;
   const roll::SPreGameData& preGame_;
   const roll::SPostGameData& postGame_;

   ClanDataAgregator clansData_;
   TPlayersInParties playersInParties_;

};

///////////////////////////////////////////////////////////////////////////////

bool IsPvPGameMode( const roll::SPreGameData & _preGame );

} //namespace roll
