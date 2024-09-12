#pragma once

namespace test
{

namespace EGameFinishClientState
{
  enum Enum
  {
    NotConnected,  // Client was not connected to the game session
    FinishedGame,  // Client was connected and finished game session
    Disconnected,  // Client was disconnected before game finish
  };
}

struct SClientStatistics : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  int      clientId; //FIXME: в принципе, это поле здесь не нужно; Ќадо бы попробовать избавитс€ от него
  EGameFinishClientState::Enum  clientState;
  uint                      totalAfkSeconds; 
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&clientState); f.Add(4,&totalAfkSeconds); return 0; }

  SClientStatistics() : clientId(0), clientState(EGameFinishClientState::NotConnected), totalAfkSeconds(0) {}

  SClientStatistics( int _clientId, EGameFinishClientState::Enum _clientState, uint _totalAfkSeconds ) :
  clientId(_clientId), clientState(_clientState), totalAfkSeconds(_totalAfkSeconds) {}
};

namespace EMode
{
  enum Enum
  {
    None,
    PvP,
    OfficerPvp,
    Train,
    Tutorial
  };
}

namespace EBasket
{
  enum Enum
  {
    Undefined   = -1,
    Newbie      = 0,
    Normal      = 1,
    Guard       = 2
  };
}

namespace ETeam
{
  enum Enum
  {
    None = -1,
    Team1 = 0,
    Team2 = 1,
    COUNT
  };
}

struct TalentInfo
{
  ZDATA
    uint id;
    int refineRate;
    int actionBarIdx;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&id); f.Add(3,&refineRate); f.Add(4,&actionBarIdx); return 0; }

  TalentInfo() : id( 0 ), refineRate( 0 ), actionBarIdx( 0 ) {}
  TalentInfo( uint _id, int rr, int abIdx ) : id( _id ), refineRate( rr ), actionBarIdx( abIdx ) {}
};

struct TalentRollItem
{
  ZDATA
    int probability;
    nstl::string dbid;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&probability); f.Add(3,&dbid); return 0; }

  TalentRollItem() : probability( 0 ) {}
  TalentRollItem( int _probability, nstl::string _dbid ) : probability( _probability ), dbid( _dbid ) {}
};

struct TalentRollItems
{
  ZDATA
    int version;
    vector<TalentRollItem> items;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&version); f.Add(3,&items); return 0; }

  TalentRollItems() : version( 0 ) {} 
};

typedef nstl::hash_map<nstl::string, TalentRollItems> TTalentRollTable;
struct TalentRollData
{
  ZDATA
    int generationIndex;
    TTalentRollTable rollTable;
    bool previousPremiumState;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&generationIndex); f.Add(3,&rollTable); f.Add(4,&previousPremiumState); return 0; }

  TalentRollData() : generationIndex( 0 ), previousPremiumState(false) {}
};

typedef nstl::map<uint, TalentInfo> PlayerTalentSet;
typedef ni_detail::UInt64 TAuid;
typedef ni_detail::UInt64 TGuildAuid;


struct GuildData
{
  ZDATA
  TGuildAuid    id;
  float         rating;
  int           level;
  int           buildingLevel;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&id); f.Add(3,&rating); f.Add(4,&level); f.Add(5,&buildingLevel); return 0; }

  GuildData() :
  id( 0 ),
  rating( 0 ),
  level( 0 )
  {}
};


struct PlayerInfo
{
  ZDATA
    TAuid             auid; //TEMP: ѕока добавить ауид сюда. Ќадеюсь, временно
    PlayerTalentSet   talents;
    nstl::vector<int> inventory;
    nstl::vector<int> friends;
    uint              heroId; 
    uint              heroEnergy;
    uint              avatarLevel;
    uint              heroLevel;
    float             hsHealth;
    float             hsMana;
    float             hsStrength;
    float             hsIntellect;
    float             hsAgility;
    float             hsCunning;
    float             hsFortitude;
    float             hsWill;
    float             hsLifeRegen;
    float             hsManaRegen;
    int               heroExp;
    int               guardRating;
    int               playerRating;
    int               heroRating;
    TalentRollData    talentRollData;
    float             dropRate;
    bool              hasPremium;
    EBasket::Enum     basket;
    string            heroSkin;
    string            locale;
    bool              fwod;
    GuildData         guildData;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&auid); f.Add(3,&talents); f.Add(4,&inventory); f.Add(5,&friends); f.Add(6,&heroId); f.Add(7,&heroEnergy); f.Add(8,&avatarLevel); f.Add(9,&heroLevel); f.Add(10,&hsHealth); f.Add(11,&hsMana); f.Add(12,&hsStrength); f.Add(13,&hsIntellect); f.Add(14,&hsAgility); f.Add(15,&hsCunning); f.Add(16,&hsFortitude); f.Add(17,&hsWill); f.Add(18,&hsLifeRegen); f.Add(19,&hsManaRegen); f.Add(20,&heroExp); f.Add(21,&guardRating); f.Add(22,&playerRating); f.Add(23,&heroRating); f.Add(24,&talentRollData); f.Add(25,&dropRate); f.Add(26,&hasPremium); f.Add(27,&basket); f.Add(28,&heroSkin); f.Add(29,&locale); f.Add(30,&fwod); f.Add(31,&guildData); return 0; }

  PlayerInfo() : 
    auid( 0 ),
    heroId( 0 ), 
    heroEnergy( 0 ), 
    avatarLevel( 0 ),
    heroLevel( 0 ), 
    hsHealth( 0.f ),
    hsMana( 0.f ),
    hsStrength( 0.f ),
    hsIntellect( 0.f ),
    hsAgility( 0.f ),
    hsCunning( 0.f ),
    hsFortitude( 0.f ),
    hsWill( 0.f ),
    hsLifeRegen( 0.f ),
    hsManaRegen( 0.f ),
    heroExp(0),
    guardRating(0),
    playerRating(0),
    heroRating(0),
    dropRate( 1.0f ),
    hasPremium( false ),
    basket( EBasket::Undefined ),
    fwod(false),
    heroSkin("")
    {}
};

struct SPreGamePerUserData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  int  clientId;
  ETeam::Enum    faction;
  PlayerInfo     playerInfo;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&faction); f.Add(4,&playerInfo); return 0; }

  SPreGamePerUserData() : clientId( 0 ), faction( ETeam::None ) {}
};

struct GameGuildData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  TGuildAuid          team1GuildId;
  TGuildAuid          team2GuildId;

  //etc.
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&team1GuildId); f.Add(3,&team2GuildId); return 0; }

  GameGuildData() :
  team1GuildId( 0 ), team2GuildId( 0 )
  {}
};
typedef ni_detail::UInt64 TGameId;
typedef long long TUserId;
typedef TGameId TSocialGameId; //YES, It's here
typedef ni_detail::UInt64 TGuildAuid;


struct SPreGameData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )  
  EMode::Enum                 mode;
  EBasket::Enum      mmBasket;
  nstl::string                mapDesc;      // AdvMapDesc DBID supposed
  int                         gameServerSid;
  TSocialGameId        socialLobbyGameId;
  GameGuildData        guildData;
  vector<SPreGamePerUserData> users;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&mode); f.Add(3,&mmBasket); f.Add(4,&mapDesc); f.Add(5,&gameServerSid); f.Add(6,&socialLobbyGameId); f.Add(7,&guildData); f.Add(8,&users); return 0; }

  SPreGameData() :
  mode( EMode::None ),
  mmBasket( EBasket::Undefined ),
  gameServerSid( 0 ),
  socialLobbyGameId( 0 )
  {}
};

struct SPostGamePerUserData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  int        clientId;
  int                         score;
  SClientStatistics   statistics;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&score); f.Add(4,&statistics); return 0; }

  SPostGamePerUserData() :
  clientId( 0 ),
  score( 0 )
  {}
};

namespace EGameResult
{
  enum Enum
  {
    SyncResults,   // результаты получены с клиентов и все клиенты прислали одинаковые результаты
    NoResults,     // у сессии нет результатов
    NobodyCame,    // не дождались коннекта ни одного пользовател€
    AsyncResults,  // результаты получены с клиентов и есть разногласи€ по содержимому
    Async,         // случилс€ асинк и результатов нет
    Unknown,
  };
}


struct SPostGameData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  EGameResult::Enum      gameResult;
  ETeam::Enum            victoriousFaction;
  uint                          totalSeconds;
  vector<SPostGamePerUserData>  users;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&gameResult); f.Add(3,&victoriousFaction); f.Add(4,&totalSeconds); f.Add(5,&users); return 0; }

  SPostGameData() :
  gameResult( EGameResult::Unknown ),
  victoriousFaction( ETeam::None ),
  totalSeconds(0)
  {}
};

}


     