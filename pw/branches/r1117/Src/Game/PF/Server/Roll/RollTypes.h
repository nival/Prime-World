#ifndef ROLLTYPES_H_INCLUDED
#define ROLLTYPES_H_INCLUDED

#include "RPC/RPC.h"
#include "Network/TransportAddress.h"
#include "System/EnumToString.h"
#include "Core/GameTypes.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "HybridServer/PeeredTypes.h"
#include "Server/LiveMMaking/LiveMMakingTypes.h"
#include "Server/Statistic/SessionPlayerScoring.h"
#include "Server/Statistic/SessionPlayerExtra.h"

namespace NDb
{
  struct Talent;
}

namespace roll
{

namespace serviceIds
{
  const Transport::TServiceId BalancerService = "rollbalancer";
  static const char * BalancerInterface = "irollbalancer";

  const Transport::TServiceId InstanceService = "roll";
} //namespace serviceIds



namespace EMode
{
  enum Enum
  {
    None,
    PvP,
    LobbyPvp,
    Train,
    Tutorial,
    CustomGame,
    Singleplayer,
    Coop
  };

  NI_ENUM_DECL_STD;
}



typedef Transport::TClientId UserId;
typedef lobby::TSocialGameId TRollId;


struct SPreGamePerUserData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  Transport::TClientId  clientId;
  lobby::ETeam::Enum    faction;
  NCore::PlayerInfo     playerInfo;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&faction); f.Add(4,&playerInfo); return 0; }

  SPreGamePerUserData() : clientId( 0 ), faction( lobby::ETeam::None ) {}
};



struct SPreGameData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )  
  EMode::Enum                 mode;
  mmaking::EBasket::Enum      mmBasket;
  nstl::string                mapDesc;      // AdvMapDesc DBID supposed
  lobby::TSocialGameId        socialLobbyGameId;
  lobby::GameGuildData        guildData;
  vector<SPreGamePerUserData> users;
  lobby::ETypeOfSession::Enum sessionType;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&mode); f.Add(3,&mmBasket); f.Add(4,&mapDesc); f.Add(5,&socialLobbyGameId); f.Add(6,&guildData); f.Add(6,&users); f.Add(7,&sessionType); return 0; }

  SPreGameData() :
  mode( EMode::None ),
  mmBasket( mmaking::EBasket::Undefined ),
  socialLobbyGameId( 0 )
  {}
};



struct SPostGamePerUserData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  Transport::TClientId        clientId;
  StatisticService::SessionPlayerScoring scoring;
  StatisticService::SessionPlayerExtra extra;
  Peered::SClientStatistics   statistics;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&scoring); f.Add(4,&statistics);  f.Add(5,&extra); return 0; }

  SPostGamePerUserData() :
  clientId( 0 )
  {}
};



struct SPostGameData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  lobby::EGameResult::Enum      gameResult;
  lobby::ETeam::Enum            victoriousFaction;
  uint                          totalSeconds;
  vector<SPostGamePerUserData>  users;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&gameResult); f.Add(3,&victoriousFaction); f.Add(4,&totalSeconds); f.Add(5,&users); return 0; }

  SPostGameData() :
  gameResult( lobby::EGameResult::Unknown ),
  victoriousFaction( lobby::ETeam::None ),
  totalSeconds(0)
  {}
};



struct SForgeRollData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  lobby::TUserId        uid;
  TRollId               rollId;
  int                   count;
  NCore::TalentRollData talentRollData;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&uid); f.Add(3,&rollId); f.Add(4,&count); f.Add(5,&talentRollData); return 0; }

  SForgeRollData() :
  uid( 0 ),
  rollId( 0 ),
  count( 0 ) {}
};



namespace EAwardType
{
  enum Enum
  {
    None,
    Talent,
    Silver,
    Hero,
    HeroRating,
    Reliability,
    Experience,
    Resource1,
    Resource2,
    HeroEnergy,
    Fame,
    Resource3,
    Pearl,
    NewSeed,
    PlayerRating,
    DodgePoints,
    GuardRating,
    GuildWarEventPoints,
    GuildResource,
    MarketingEvent,
    ClanWarsPlayerRating,
    ClanWarsClanRating,
    RedPearl,
    Shard,
    CustomCurrency,

    NumOfAwardTypes
  };

  NI_ENUM_DECL_STD;
}

struct SAwardBonusInfo
{
  ZDATA

  float count;
  nstl::string id;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&count); f.Add(3,&id); return 0; }

  SAwardBonusInfo()
    : count(0) {}

  SAwardBonusInfo(float _count, const nstl::string& _id)
    : count(_count), id(_id) {}
};


struct SAwardInfo : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  EAwardType::Enum  type;
  int               id;  // crc32 from persistentId in xdb data, GetWorld()->GetResourcesCollection()
  float             count;
  uint              vendorCost;
  bool              isOwnedByPlayer;
  bool              isPremium;
  bool              isTasty;
  UserId            giverUser;
  bool              isGuildBonus;
  SAwardBonusInfo   bonus;
  nstl::string      customCurrencyId;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&type); f.Add(3,&id); f.Add(4,&count); f.Add(5,&vendorCost); f.Add(6,&isOwnedByPlayer); f.Add(7,&isPremium); f.Add(8,&isTasty); f.Add(9,&giverUser); f.Add(10,&isGuildBonus); f.Add(11,&bonus); f.Add(12,&customCurrencyId); return 0; }

  SAwardInfo() :
  type( EAwardType::None ),
  id( 0 ),
  count( 0 ),
  vendorCost(0),
  isOwnedByPlayer(false),
  isPremium(false),
  isTasty(false),
  giverUser(0),
  isGuildBonus(false) {}

  SAwardInfo( EAwardType::Enum _type, int _id, int _count, uint _vendorCost, bool _isOwnedByPlayer, bool _isPremium = false, bool _isTasty = false, UserId _giverUser = 0, bool _isGuildBonus = false) :
  type( _type ),
  id( _id ),
  count( _count ),
  vendorCost(_vendorCost),
  isOwnedByPlayer(_isOwnedByPlayer),
  isPremium(_isPremium),
  isTasty(_isTasty),
  giverUser(_giverUser),
  isGuildBonus(_isGuildBonus)
  {}
};



struct SUserAward : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  UserId                userId;
  vector<SAwardInfo>    awards;
  NCore::TalentRollData talentRollData;
  bool                  playerWin;
  bool                  playerLeaver;
  bool                  hadPreGameLobby;
  set<string>           appliedRollBuffs;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&userId); f.Add(3,&awards); f.Add(4,&talentRollData); f.Add(5,&playerWin); f.Add(6,&playerLeaver); f.Add(7,&hadPreGameLobby); f.Add(8,&appliedRollBuffs); return 0; }

  SUserAward() :
  userId( 0 ),
  playerWin( false ),
  playerLeaver( false ),
  hadPreGameLobby( false )
  {}
};



struct SGuildAward : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  NCore::TGuildAuid     guildId;
  vector<SAwardInfo>    awards;
  NCore::TalentRollData talentRollData;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&guildId); f.Add(3,&awards); f.Add(4,&talentRollData); return 0; }

  SGuildAward() :
  guildId( 0 )
  {}

  SGuildAward(NCore::TGuildAuid _guildId) :
  guildId( _guildId )
  {}
};


string DbgDumpAwards( const vector<SAwardInfo> & awards );

}; //namespace roll

#endif //ROLLTYPES_H_INCLUDED
