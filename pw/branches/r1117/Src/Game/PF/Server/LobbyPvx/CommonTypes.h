#ifndef LOBBYCOMMONTYPES_H_INCLUDED
#define LOBBYCOMMONTYPES_H_INCLUDED

#include "RPC/RPC.h"
#include "Network/TransportAddress.h"
#include "System/EnumToString.h"
#include <ClusterTypes/ClusterTypes.h>
//#include "Server/Statistic/StatisticTypes.h"


namespace lobby
{

namespace serviceIds
{
  const Transport::TServiceId Service = "lobby";
  static const char * Entrance    = "lobby:entrance";
  static const char * Accounting  = "lobby:accounting";
} //namespace serviceIds


namespace EOperationResult
{
  enum Enum { Ok, InProgress, InternalError, NoFreeSlot, GameNotFound, GameStarted, AlreadyInGame, RevisionDiffers, RestrictedAccess };

  NI_ENUM_DECL_STD;
}



//UGLY: Due to link/dependencies problems, next enums MUST be synchronized with similar ones in GameTypes.h
namespace ETeam
{
  enum Enum
  {
    None = -1,
    Team1 = 0,
    Team2 = 1
  };

  inline Enum Invert( Enum e ) { return ( e == Team1 ) ? Team2 : ( ( e == Team2 ) ? Team1 : None ); }
  inline int Index( Enum e ) { NI_ASSERT( ( e == Team1 ) || ( e == Team2 ), "" ); return ( e == Team1 ) ? 0 : 1; }
  inline Enum Index( int idx ) { NI_VERIFY( idx >= 0 && idx < 2, "", return None ); return idx == 0 ? Team1 : Team2; }

  NI_ENUM_DECL_STD;
}

namespace ESex
{
  enum Enum { Undefined, Male, Female };

  NI_ENUM_DECL_STD;
}




namespace EPlayerType
{
  enum Enum
  {
    Invalid,
    Human,
    Computer
  };

  NI_ENUM_DECL_STD;
}



namespace EGameType
{
  enum Enum { None, Custom, SocialMMaking };

  NI_ENUM_DECL_STD;
}


namespace ETypeOfSession 
{
    enum Enum { 
        SESSIONTYPE_USUALBATTLE = 1,
        SESSIONTYPE_GUILDBATTLE = 2
    };

    NI_ENUM_DECL_STD;
}

namespace EGameMemberReadiness
{
  enum Enum { NotReady, Ready, ReadyForAnything };
}


typedef Cluster::TGameId TGameId;
typedef long long TUserId;
typedef TGameId TSocialGameId; //YES, It's here
typedef ni_detail::UInt64 TGuildAuid;

const char * FmtGameId( TGameId _id );
inline const char * FmtSocGameId( TSocialGameId _id ) { return FmtGameId( _id ); }


struct SUserInfo : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  int                 userId;
  ESex::Enum          zzimaSex;
  wstring             nickname;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&userId); f.Add(3,&zzimaSex); f.Add(4,&nickname); return 0; }

  SUserInfo() : userId(-1), zzimaSex( ESex::Undefined ) {} 
  SUserInfo( int _uid, ESex::Enum _sex, const wchar_t * _nick ) : userId( _uid ), zzimaSex( _sex ), nickname( _nick ) {}
};



struct GameGuildData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  map<ETeam::Enum, vector<TGuildAuid>>  guilds;

  //etc.
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&guilds); return 0; }

  GameGuildData() {}
};



struct SGameParameters : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  EGameType::Enum     gameType;
  wstring             name;
  string              mapId;
  int                 slotsCount;
  int                 maxPlayersPerTeam; // must be computed from map on server
  int                 randomSeed;
  ETeam::Enum         manoeuvresFaction;
  bool                hadPreGameLobby;
  bool                customGame;
  GameGuildData       guildData;
  ETypeOfSession::Enum        sessiontype;

  //etc.
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&gameType); f.Add(3,&name); f.Add(4,&mapId); f.Add(5,&slotsCount); f.Add(6,&maxPlayersPerTeam); f.Add(7,&randomSeed); f.Add(8,&manoeuvresFaction); f.Add(9,&hadPreGameLobby); f.Add(10,&customGame); f.Add(11,&guildData); f.Add(12,&sessiontype); return 0; }

  SGameParameters() :
  gameType( EGameType::None ),
  slotsCount( 0 ),
  maxPlayersPerTeam( 5 ),
  randomSeed( 0 ),
  manoeuvresFaction( ETeam::None ),
  hadPreGameLobby( false ),
  customGame( false ),
  sessiontype(ETypeOfSession::SESSIONTYPE_USUALBATTLE)
  {}
};



struct SPlayerGameContext : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  EPlayerType::Enum   playerType;
  ETeam::Enum         team;
  string              hero;
  string              botSkin; //For bots only; Empty for live players
  ETeam::Enum         original_team;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&playerType); f.Add(3,&team); f.Add(4,&hero); f.Add(5,&botSkin); f.Add(6,&original_team); return 0; }
  SPlayerGameContext() :
  playerType( EPlayerType::Invalid ), team( ETeam::None ), original_team( ETeam::None ) {} 

  SPlayerGameContext( EPlayerType::Enum _playerType, ETeam::Enum _team, ETeam::Enum _orig_team, const char * _hero ) :
  playerType( _playerType ), team( _team ), original_team(_orig_team), hero( _hero ) {}
};



struct SGameMember : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  SUserInfo               user;
  SPlayerGameContext      context;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&user); f.Add(3,&context); return 0; }
  SGameMember() {}
  SGameMember( const SUserInfo & _user, const SPlayerGameContext & _ctx ) : user( _user ), context( _ctx ) {} 
};



typedef vector<SGameMember>  TGameLineUp;




struct SDevGameInfo : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  TGameId     gameId;
  wstring     name;
  string      mapId;
  int         playersCount;
  int         maxPlayers;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&gameId); f.Add(3,&name); f.Add(4,&mapId); f.Add(5,&playersCount); f.Add(6,&maxPlayers); return 0; }

  SDevGameInfo() : gameId( 0 ), playersCount( 0 ), maxPlayers( 0 ) {}
  SDevGameInfo( int id, const wchar_t * _name, const char * _mapId, int players, int maxPlayers ) :
    gameId( id ), name( _name ), mapId( _mapId ), playersCount( players ), maxPlayers( maxPlayers ) {}
};



typedef list<SDevGameInfo>  TDevGamesList;


namespace EGameResult
{
  enum Enum
  {
    SyncResults,   // результаты получены с клиентов и все клиенты прислали одинаковые результаты
    NoResults,     // у сессии нет результатов
    NobodyCame,    // не дождались коннекта ни одного пользователя
    AsyncResults,  // результаты получены с клиентов и есть разногласия по содержимому
    Async,         // случился асинк и результатов нет
    Unknown,
  };

  NI_ENUM_DECL_STD;
}

}; //namespace lobby

#endif //LOBBYCOMMONTYPES_H_INCLUDED
