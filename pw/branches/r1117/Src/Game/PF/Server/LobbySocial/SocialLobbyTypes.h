#ifndef SOCIALLOBBYTYPES_H_INCLUDED
#define SOCIALLOBBYTYPES_H_INCLUDED

#include "RPC/RPC.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "Server/LiveMMaking/LiveMMakingTypes.h"
#include "Server/Roll/RollTypes.h"


namespace socialLobby
{

namespace serviceIds
{
  const Transport::TServiceId Service   = "social_lobby";
  static const char * SocialInterface   = "to_social";
  static const char * PvxInterface      = "to_pvx";
  static const char * DevEntrance       = "dev";
} //namespace serviceIds



namespace ERequestStatus
{
  enum Enum
  {
    Null                    = 0,
    JustAddedToSocialServer = 1, //Unsed in PvX/C++
    JustAddedToHttpGateway  = 2,
    JustAddedToLobby        = 3,
    WaitingPartyMembers     = 49,
    InLine                  = 50,
    WaitingAccept           = 100,
    Accepted                = 101,
    PreparingPvX            = 108,
    WaitingInPvX            = 102,
    InGame                  = 104,
    GameFinished            = 106,
    ClientDropped           = 107,
    WaitingGameFinish       = 109,
    PreGameLobby            = 110,
    AcceptTimedOut          = 200,
    IncompleteParty         = 201,
    PartyCameApart          = 202
  };

  NI_ENUM_DECL_STD;
}



typedef lobby::TUserId TUId;
typedef int TUserIdPvX;
typedef ni_detail::SInt64 TPartyId;



struct PlayerDetails : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  TUId              uid;
  TUserIdPvX        pvxUserId;
  string            login;
  wstring           nick;
  NCore::PlayerInfo gameData;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&uid); f.Add(3,&pvxUserId); f.Add(4,&login); f.Add(5,&nick); f.Add(6,&gameData); return 0; }

  PlayerDetails() : uid( 0 ), pvxUserId( 0 ) {}
};



namespace EPvxLobbyInstanceMode
{
  enum Enum
  {
    Normal              = 0,
    ForcePartial        = 1,
    ForceFullGames      = 2
  };

  NI_ENUM_DECL_STD;
}



struct PvxClusterSettings : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  unsigned                      capacity;
  EPvxLobbyInstanceMode::Enum   specialMode;
  vector<TUId>                  specialList;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&capacity); f.Add(3,&specialMode); f.Add(4,&specialList); return 0; }

  PvxClusterSettings()
  {}
};


struct PvxGameDetails : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  vector<PlayerDetails>   playerDetails;
  bool                    preGameLobby;
  bool                    customGame;
  lobby::GameGuildData    guildData;
  lobby::ETypeOfSession::Enum     sessiontype;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&playerDetails); f.Add(3,&preGameLobby); f.Add(4,&customGame); f.Add(5,&guildData); f.Add(6,&sessiontype); return 0; }

  PvxGameDetails() :
  preGameLobby( false ),
  customGame( false ),
  sessiontype( lobby::ETypeOfSession::SESSIONTYPE_USUALBATTLE)
  {}

  const PlayerDetails * FindPlayer( TUserIdPvX _pvxUserId );
};



struct SMatchmakingRequestCore : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  TUId                    uid;
  TUserIdPvX              userIdPvx;
  TUId                    targetUid;
  string                  sessionContextId;
  string                  login;
  wstring                 nickname;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&uid); f.Add(3,&userIdPvx); f.Add(4,&targetUid); f.Add(5,&sessionContextId); f.Add(6,&login); f.Add(7,&nickname); return 0; }

  SMatchmakingRequestCore() :
  uid( 0 ),
  userIdPvx( 0 ),
  targetUid( 0 )
  {}
};



struct SMatchmakingRequest : public SMatchmakingRequestCore
{
  SERIALIZE_ID();

  ZDATA_( SMatchmakingRequestCore )
  string                  map;
  lobby::ETeam::Enum      faction;
  string                  heroId;
  lobby::ESex::Enum       zzimaSex;
  mmaking::EBasket::Enum  basket;
  int                     guardRating;
  int                     playerRating;
  int                     heroRating;
  float                   force;
  int                     clientRevision;
  mmaking::SGeoInfo       geoInfo;
  TPartyId                partyId;
  vector<TUId>            partyLineup;
  vector<TUId>            enemyPartyLineup; //for custom-games
  string                  winLoseHistory;
  int                     totalWins;
  int                     fameLevel;
  lobby::ETeam::Enum      original_faction;
  int                     totalLeaves;

  ZEND int operator&( IBinSaver &f ) { f.Add(1,( SMatchmakingRequestCore *)this); f.Add(2,&map); f.Add(3,&faction); f.Add(4,&heroId); f.Add(5,&zzimaSex); f.Add(6,&basket); f.Add(7,&guardRating); f.Add(8,&playerRating); f.Add(9,&heroRating); f.Add(10,&force); f.Add(11,&clientRevision); f.Add(12,&geoInfo); f.Add(13,&partyId); f.Add(14,&partyLineup); f.Add(15,&enemyPartyLineup); f.Add(16,&winLoseHistory); f.Add(17,&totalWins); f.Add(18,&fameLevel); f.Add(19,&original_faction); f.Add(20,&totalLeaves); return 0; }

  SMatchmakingRequest() :
  faction( lobby::ETeam::None ),
  zzimaSex( lobby::ESex::Undefined ),
  basket( mmaking::EBasket::Undefined ),
  guardRating( 0 ),
  playerRating( 0 ),
  heroRating( 0 ),
  force( 0 ),
  clientRevision( 0 ),
  partyId( 0 ),
  totalWins( 0 ),
  fameLevel( 0 ),
  original_faction(lobby::ETeam::None),
  totalLeaves( 0 )
  {}
};




struct SGameResults : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  lobby::ETeam::Enum    winner;
  bool                  playerWin;
  bool                  playerIsLeaver;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&winner); f.Add(3,&playerWin); f.Add(4,&playerIsLeaver); return 0; }

  SGameResults() :
  winner( lobby::ETeam::None ),
  playerWin( false ),
  playerIsLeaver( false )
  {}
};



struct SAllyStatus
{
  ZDATA
  TUId    uid;
  bool    ready;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&uid); f.Add(3,&ready); return 0; }

  SAllyStatus() :
  uid( 0 ),
  ready( 0 )
  {}

  SAllyStatus( TUId _uid, bool _ready ) :
  uid( _uid ),
  ready( _ready )
  {}

  bool operator == ( const SAllyStatus & other ) const { return ( uid == other.uid ) && ( ready == other.ready ); }
};



struct SPreGameLobby
{
  ZDATA
  int                       foesReady;
  vector<SAllyStatus>       allies;
  bool                      preGameLobby;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&foesReady); f.Add(3,&allies); f.Add(4,&preGameLobby); return 0; }

  SPreGameLobby() :
  foesReady( 0 ),
  preGameLobby( false )
  {}
};




struct SMatchmakingStatus : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  ERequestStatus::Enum    progress;
  string                  sessionContextId;
  int                     requestsAccepted;
  int                     totalPlayers; 
  lobby::TSocialGameId    gameId;
  string                  pvxSessionKey;
  SGameResults            gameResults;
  mmaking::EBasket::Enum  gameBasket;
  SPreGameLobby           preGameLobbyInfo;
  string                  debugInfo;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&progress); f.Add(3,&sessionContextId); f.Add(4,&requestsAccepted); f.Add(5,&totalPlayers); f.Add(6,&gameId); f.Add(7,&pvxSessionKey); f.Add(8,&gameResults); f.Add(9,&gameBasket); f.Add(10,&preGameLobbyInfo); f.Add(11,&debugInfo); return 0; }

  SMatchmakingStatus() :
  progress( ERequestStatus::Null ),
  requestsAccepted( 0 ),
  totalPlayers( 0 ),
  gameId( 0 ),
  gameBasket( mmaking::EBasket::Undefined )
  {}
};



struct SPlayerData : public rpc::Data //Just an RPC wrapper around NCore::PlayerInfo
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  NCore::PlayerInfo     data;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&data); return 0; }

  SPlayerData() {}
  explicit SPlayerData( const NCore::PlayerInfo & _data ) : data( _data ) {}
};

typedef nstl::map<int, float> TAvgRRTimes;
typedef nstl::map<int, TAvgRRTimes> TModeAvgTimes;
typedef nstl::map<string, TModeAvgTimes> TBasketAvgTimes;

struct SServerStatus : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  float     acceptTimeout;
  float     averageMmTime;
  float     reconnectTimeout;
  float     guardLobbyTimeout;
  string    pvpMmDebugStatus;
  TBasketAvgTimes avgTimesPerMode;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&acceptTimeout); f.Add(3,&averageMmTime); f.Add(4,&reconnectTimeout); f.Add(5,&guardLobbyTimeout); f.Add(6,&pvpMmDebugStatus); f.Add(7, &avgTimesPerMode); return 0; }

  SServerStatus() :
  acceptTimeout( 0.0f ),
  averageMmTime( 0.0f ),
  reconnectTimeout( 0.0f ),
  guardLobbyTimeout( 0.0f )
  {}
};



struct SDevUidRange
{
  TUId      from, to;

  SDevUidRange() : from( 0 ), to( 0 ) {}
  SDevUidRange( TUId _from, TUId _to ) : from( _from ), to( _to ) {}
};

}; //namespace socialLobby

#endif //SOCIALLOBBYTYPES_H_INCLUDED
