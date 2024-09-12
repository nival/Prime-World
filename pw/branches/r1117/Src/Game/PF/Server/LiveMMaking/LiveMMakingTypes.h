#ifndef LIVEMMAKINGTYPES_H_INCLUDED
#define LIVEMMAKINGTYPES_H_INCLUDED

#include "Server/LobbyPvx/CommonTypes.h"
// Dirty hack! Fix!
#if defined( NV_LINUX_PLATFORM )
#include "Server/Db/DBServer.auto.h"
#endif


namespace NDb
{
  enum EMapType;
}


namespace mmaking
{

namespace serviceIds
{
  static const Transport::TServiceId Service = "livemmaking";
} //namespace serviceIds



namespace EBasket
{
  enum Enum
  {
    Undefined           = -1,
    Newbie              = 0,
    Normal              = 1,
    Leaver              = 2
  };

  NI_ENUM_DECL_STD;
}


namespace EDebugGameType
{
  enum Enum
  {
    Normal,
    LongWait,
    FullParty
  };

  NI_ENUM_DECL_STD;
};



namespace EServiceGameModes
{
  enum Enum
  {
    Any,
    ProductionOnly,
    DevelopmentOnly
  };

  NI_ENUM_DECL_STD;
};


const static int HeroClassesNumber = 6; //Doubled by db enum MMakingHeroClassEnum (DBMMaking.cs)


typedef int TUserId;
typedef int TRequestUId;
typedef int THeroShortId;


struct SLocationPing : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  string      clusterId;
  int         ping;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clusterId); f.Add(3,&ping); return 0; }

  SLocationPing() : ping( 0 ) {}

  SLocationPing( const char * _clusterId, int _ping ) :
  clusterId( _clusterId ),
  ping( _ping )
  {}

  bool operator == ( const SLocationPing & _other ) const {
    return ( clusterId == _other.clusterId ) && ( ping == _other.ping );
  }
};



struct SGeoInfo : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  string                  locale;
  vector<SLocationPing>   pings;
  string                  location;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&locale); f.Add(3,&pings); f.Add(4,&location); return 0; }

  SGeoInfo() {}

  SGeoInfo( const char * _locale ) :
  locale( _locale )
  {}

  bool operator == ( const SGeoInfo & _other ) const {
    return ( locale == _other.locale ) && ( pings == _other.pings ) && ( location == _other.location );
  }

  string FmtPings() const;
};



struct SRequestMember : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  TUserId               mmId;
  string                heroId;
  lobby::ESex::Enum     sex;
  EBasket::Enum         basket;
  int                   guardRating;
  int                   playerRating;
  int                   heroRating;
  float                 force;
  SGeoInfo              geoInfo;
  int                   loseStreak;
  int                   totalWins;
  int                   fameLevel;
  lobby::ETeam::Enum    original_team;
  int                   totalLeaves;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&mmId); f.Add(3,&heroId); f.Add(4,&sex); f.Add(5,&basket); f.Add(6,&guardRating); f.Add(7,&playerRating); f.Add(8,&heroRating); f.Add(9,&force); f.Add(10,&geoInfo); f.Add(11,&loseStreak); f.Add(12,&totalWins); f.Add(13,&fameLevel); f.Add(14,&original_team); f.Add(15,&totalLeaves); return 0; }

  SRequestMember( TUserId _mmId, const char * _hero, lobby::ESex::Enum _sex, EBasket::Enum _basket, int _guardRating, int _playerRating, int _heroRating, float _force, const SGeoInfo & _geo, int _loseStreak, int _totalWins, int _fameLevel, lobby::ETeam::Enum _original_team, int _totalLeaves ) :
  mmId( _mmId ),
  heroId( _hero ),
  sex( _sex ),
  basket( _basket ),
  guardRating( _guardRating ),
  playerRating( _playerRating ),
  heroRating( _heroRating ),
  force( _force ),
  geoInfo( _geo ),
  loseStreak( _loseStreak ),
  totalWins( _totalWins ),
  fameLevel( _fameLevel ),
  original_team(_original_team),
  totalLeaves(_totalLeaves)
  {}

  SRequestMember() :
  mmId( 0 ),
  sex( lobby::ESex::Undefined ),
  basket( EBasket::Undefined ),
  guardRating( 0 ),
  playerRating( 0 ),
  heroRating( 0 ),
  force( 0 ),
  loseStreak( 0 ),
  totalWins( 0 ),
  fameLevel( 0 ),
  original_team(lobby::ETeam::None),
  totalLeaves(0)
  {}
};



struct SRequestCommonData : public rpc::Data
{
  SERIALIZE_ID();

  //"basket" field should be here, but it is in SRequestMember, because it is MM pesponsibility
  //to determine basket of party dependinig on individual member's baskets

  ZDATA
  ZNOPARENT( rpc::Data )
  lobby::ETeam::Enum    team;
  int                   clientRevision;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&team); f.Add(3,&clientRevision);return 0; }

  SRequestCommonData( lobby::ETeam::Enum _team, int _clientRevision) :
  team( _team ),
  clientRevision( _clientRevision )
  {}

  SRequestCommonData() :
  team( lobby::ETeam::None ),
  clientRevision( 0 )
  {}
};



struct SGameParty : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  SRequestCommonData      common;
  timer::Time             waitTime;
  TRequestUId             requestUId;
  vector<SRequestMember>  members;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&common); f.Add(3,&waitTime); f.Add(4,&requestUId); f.Add(5,&members); return 0; }

  SGameParty( const SRequestCommonData & _cmnData, timer::Time _waitTime, TRequestUId _reqId ) :
  common( _cmnData ), waitTime( _waitTime ), requestUId( _reqId ) {}

  SGameParty() : waitTime( 0 ), requestUId( 0 ) {}
};



struct SBotGameMember : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  lobby::ETeam::Enum    team;
  string                heroId;
  string                heroSkin;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&team); f.Add(3,&heroId); f.Add(4,&heroSkin); return 0; }

  SBotGameMember( lobby::ETeam::Enum _team, const char * _hero, const char * _skin ) :
  team( _team ),
  heroId( _hero ),
  heroSkin( _skin )
  {}
  SBotGameMember() : team( lobby::ETeam::None ) {}
};



struct SGame : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  NDb::EMapType                 mapType;
  string                        mapId;
  lobby::ETeam::Enum            manoeuvresFaction;
  EBasket::Enum                 basket;
  EDebugGameType::Enum          debugGameType;
  vector<SGameParty>            humans;
  vector<SBotGameMember>        bots;
  
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&mapType); f.Add(3,&mapId); f.Add(4,&manoeuvresFaction); f.Add(5,&basket); f.Add(6,&debugGameType); f.Add(7,&humans); f.Add(8,&bots); return 0; }

  SGame() :
  mapType( (NDb::EMapType)0 ),
  manoeuvresFaction( lobby::ETeam::None ),
  basket( EBasket::Undefined ),
  debugGameType( EDebugGameType::Normal )
  {}

  void Swap( SGame & game )
  {
    swap( mapType, game.mapType );
    //mapId.swap( game.mapId ); //nstl::string::swap is BROKEN (NUM_TASK)
    { string tmp = game.mapId;
      game.mapId = mapId;
      mapId = tmp; }

    swap( manoeuvresFaction, game.manoeuvresFaction );
    swap( basket, game.basket );
    swap( debugGameType, game.debugGameType );

    humans.swap( game.humans );
    bots.swap( game.bots );
  }
};



struct SReconnectSlot : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  lobby::TGameId    gameId;
  TRequestUId       userRequestId;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&gameId); f.Add(3,&userRequestId); return 0; }

  SReconnectSlot() : gameId( 0 ), userRequestId( 0 ) {}
  SReconnectSlot( lobby::TGameId _gameId, TRequestUId _userRequestId ) : gameId( _gameId ), userRequestId( _userRequestId ) {}
};


string PrepareGameModeName( const string & mapId );

} //namespace mmaking

#endif //LIVEMMAKINGTYPES_H_INCLUDED
