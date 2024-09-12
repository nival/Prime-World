#pragma once

namespace NCore
{

static const int INVALID_STEP = -1;

//UGLY: For historical reasons, this enums MUST be synchronized with similar one in Src\Game\PF\Server\Lobby\CommonTypes.h
namespace EPlayerType
{
  enum Enum
  {
    Invalid,
    Human,
    Computer
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



namespace EBasket
{
  enum Enum
  {
    Undefined   = -1,
    Newbie      = 0,
    Normal      = 1,
    Leaver      = 2
  };
}



namespace ESex
{
  enum Enum { Undefined, Male, Female };
}



typedef vector<ETeam::Enum> TPlayerSpawnInfo;

struct TalentInfo
{
  ZDATA
    uint id;
    int refineRate;
    int actionBarIdx;
    bool isInstaCast;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&id); f.Add(3,&refineRate); f.Add(4,&actionBarIdx); f.Add(5,&isInstaCast); return 0; }

  TalentInfo() : id( 0 ), refineRate( 0 ), actionBarIdx( 0 ), isInstaCast( false ) {}
  TalentInfo( uint _id, int rr, int abIdx, bool isInstaCast ) : id( _id ), refineRate( rr ), actionBarIdx( abIdx ), isInstaCast ( isInstaCast ) {}
};


// Talent roll data HELL
struct TalentRollItem
{
  ZDATA
    int probability;
    int dbid;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&probability); f.Add(3,&dbid); return 0; }

  TalentRollItem() : probability( 0 ), dbid( 0 ) {}
  TalentRollItem( int _probability, int _dbid ) : probability( _probability ), dbid( _dbid ) {}
};

struct TalentRollItems
{
  ZDATA
    int version;
    int dbVersion;
    vector<TalentRollItem> defaultItems;
    vector<TalentRollItem> premiumItems;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&version); f.Add(3,&dbVersion); f.Add(4,&defaultItems); f.Add(5,&premiumItems); return 0; }

  TalentRollItems() : version( 0 ), dbVersion( 0 ) {} 
};

typedef nstl::hash_map<nstl::string, TalentRollItems> TTalentRollTable;


struct TalentRollData
{
  ZDATA
    int generationIndex;
    TTalentRollTable rollTable;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&generationIndex); f.Add(3,&rollTable); return 0; }

  TalentRollData() : generationIndex( 0 ) {}
};
// End of roll data hell

typedef nstl::map<uint, TalentInfo> PlayerTalentSet;
typedef ni_detail::UInt64 TAuid;
typedef ni_detail::UInt64 TGuildAuid;
typedef nstl::map<int, nstl::string> TComplaintInfo;


struct GuildData
{
  ZDATA
  TGuildAuid    id;
  float         rating;
  int           level;
  int           buildingLevel;
  int           icon_number;
  string        icon_url;
  bool          guidWarEventPass; 
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&id); f.Add(3,&rating); f.Add(4,&level); f.Add(5,&buildingLevel); f.Add(6,&icon_number); f.Add(7,&icon_url); f.Add(8,&guidWarEventPass); return 0; }

  GuildData() : id( 0 ), rating( 0 ), level( 0 ), icon_number( 0 ), icon_url( "" ), guidWarEventPass(false) {}
};



struct RatingDelta
{
  ZDATA
  float         onVictory;
  float         onDefeat;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&onVictory); f.Add(3,&onDefeat); return 0; }

  RatingDelta() :
  onVictory( 0 ),
  onDefeat( 0 )
  {}
};

struct PlayerBuffValue
{
  ZDATA
  float add;
  float mul;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&add); f.Add(3,&mul); return 0; }
  PlayerBuffValue(): add(0.0f),mul(1.0f){} 
  explicit PlayerBuffValue(float addVal, float mulVal): add(addVal),mul(mulVal){}
};

typedef nstl::map<int, PlayerBuffValue> TPlayerBuffs;
typedef nstl::vector<nstl::string> TAwardsBuffs;

struct PlayerInfo
{
  ZDATA
    TAuid             auid; //TEMP: Пока добавить ауид сюда. Надеюсь, временно
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
    float             guardRating;
    float             playerRating;
    float             heroRating;
    TalentRollData    talentRollData;
    float             dropRate;
    bool              hasPremium;
    EBasket::Enum     basket;
    string            heroSkin;
    string            locale;
    bool              fwod;
    GuildData         guildData;
    string            goldLampRollContainer;
    bool              customGame;
    uint              partyId;
    bool              partyLeader;
    RatingDelta       ratingDeltaPrediction;
    int               complaintsToday;
    int               complaintsMax;
    TComplaintInfo    complaintsInfo;
    bool              chatMuted;
    string            flagId;
    string            flagCustomPicture;
    wstring           flagCustomTooltip;
    bool              hasFullLibrary;
    TPlayerBuffs      hBuffs;
    TAwardsBuffs      aBuffs;
    bool              isAnimatedAvatar;
    int               leagueIndex;
    int               ownLeaguePlace;
    nstl::vector<int> leaguePlaces;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&auid); f.Add(3,&talents); f.Add(4,&inventory); f.Add(5,&friends); f.Add(6,&heroId); f.Add(7,&heroEnergy); f.Add(8,&avatarLevel); f.Add(9,&heroLevel); f.Add(10,&hsHealth); f.Add(11,&hsMana); f.Add(12,&hsStrength); f.Add(13,&hsIntellect); f.Add(14,&hsAgility); f.Add(15,&hsCunning); f.Add(16,&hsFortitude); f.Add(17,&hsWill); f.Add(18,&hsLifeRegen); f.Add(19,&hsManaRegen); f.Add(20,&heroExp); f.Add(21,&guardRating); f.Add(22,&playerRating); f.Add(23,&heroRating); f.Add(24,&talentRollData); f.Add(25,&dropRate); f.Add(26,&hasPremium); f.Add(27,&basket); f.Add(28,&heroSkin); f.Add(29,&locale); f.Add(30,&fwod); f.Add(31,&guildData); f.Add(32,&goldLampRollContainer); f.Add(33,&customGame); f.Add(34,&partyId); f.Add(35,&partyLeader); f.Add(36,&ratingDeltaPrediction); f.Add(37,&complaintsToday); f.Add(38,&complaintsMax); f.Add(39,&complaintsInfo); f.Add(40,&chatMuted); f.Add(41,&flagId); f.Add(42,&flagCustomPicture); f.Add(43,&flagCustomTooltip); f.Add(44,&hasFullLibrary); f.Add(45,&hBuffs); f.Add(46,&aBuffs); f.Add(47,&isAnimatedAvatar); f.Add(48,&leagueIndex); f.Add(49,&ownLeaguePlace); f.Add(50,&leaguePlaces); return 0; }

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
    heroSkin(""),
    customGame( false ),
    partyId( 0 ),
    partyLeader( false ),
    complaintsToday( 0 ),
    complaintsMax(0 ),
    chatMuted(false),
    isAnimatedAvatar(true),
    leagueIndex(0),
    ownLeaguePlace(0)
    {}
};



struct PlayerStartInfo
{
  ZDATA
  int                 playerID;
  ETeam::Enum         teamID;
  ETeam::Enum         originalTeamID;
  EPlayerType::Enum   playerType;
  int                 userID;
  ESex::Enum          zzimaSex;
  wstring             nickname;
  PlayerInfo          playerInfo; 
  bool                usePlayerInfoTalentSet;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&playerID); f.Add(3,&teamID); f.Add(4,&originalTeamID); f.Add(5,&playerType); f.Add(6,&userID); f.Add(7,&zzimaSex); f.Add(8,&nickname); f.Add(9,&playerInfo); f.Add(10,&usePlayerInfoTalentSet); return 0; }

  PlayerStartInfo() :
  playerID( 0 ), teamID( ETeam::None ), originalTeamID( ETeam::None ), playerType( EPlayerType::Invalid ), userID( -1 ), zzimaSex( ESex::Undefined ), usePlayerInfoTalentSet(false) {}

  PlayerStartInfo( int playerID, ETeam::Enum teamID, ETeam::Enum _originalTeamID, EPlayerType::Enum playerType = EPlayerType::Invalid, int userID = -1, ESex::Enum _sex = ESex::Undefined ) :
  playerID( playerID ), teamID( teamID ), originalTeamID( _originalTeamID ), playerType( playerType ), userID( userID ), zzimaSex( _sex ), usePlayerInfoTalentSet(false) {} 
};

typedef vector<NCore::PlayerStartInfo> TPlayersStartInfo;

struct MapStartInfo
{
  ZDATA
  string                  mapDescName;
  string                  replayName;
  int                     randomSeed;
  vector<PlayerStartInfo> playersInfo;
  bool                    isCustomGame;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&mapDescName); f.Add(3,&replayName); f.Add(4,&randomSeed); f.Add(5,&playersInfo); f.Add(6,&isCustomGame); return 0; }

  MapStartInfo() : randomSeed( 0 ) {}
};

struct ClientSettings
{
  ZDATA
  bool minigameEnabled;
  float logicParam1;
  bool showHeroLevel;
  bool showHeroRating;
  bool showHeroForce;
  bool showDeltaRaiting;
  bool showLocale;
  bool showGuildEmblem;
  string shareUrl;
  bool aiForLeaversEnabled;
  int aiForLeaversThreshold;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&minigameEnabled); f.Add(3,&logicParam1); f.Add(4,&showHeroLevel); f.Add(5,&showHeroRating); f.Add(6,&showHeroForce); f.Add(7,&showDeltaRaiting); f.Add(8,&showLocale); f.Add(9,&showGuildEmblem); f.Add(10,&shareUrl); f.Add(11,&aiForLeaversEnabled); f.Add(12,&aiForLeaversThreshold); return 0; }

  ClientSettings() :
  minigameEnabled(false),
  logicParam1(0.0f),
  showHeroLevel(false),
  showHeroRating(false),
  showHeroForce(false),
  showDeltaRaiting(false),
  showLocale( false ),
  showGuildEmblem(false),
  shareUrl(""),
  aiForLeaversEnabled(false),
  aiForLeaversThreshold(0)
  {}

  ClientSettings(
    bool _minigameEnabled, 
    float _logicParam1, 
    bool _showHeroLevel, 
    bool _showHeroRating, 
    bool _showHeroForce, 
    bool _showDeltaRaiting, 
    bool _showLocale,
    bool _showGuildEmblem,
    string _shareUrl,
    bool _aiForLeaversEnabled,
    bool _aiForLeaversThreshold) :
  minigameEnabled(_minigameEnabled),
  logicParam1(_logicParam1),
  showHeroLevel(_showHeroLevel),
  showHeroRating(_showHeroRating),
  showHeroForce(_showHeroForce),
  showDeltaRaiting(_showDeltaRaiting),
  showLocale(_showLocale),
  showGuildEmblem(_showGuildEmblem),
  shareUrl(_shareUrl),
  aiForLeaversEnabled(_aiForLeaversEnabled),
  aiForLeaversThreshold(_aiForLeaversThreshold)
  {}
};

} //namespace NCore
