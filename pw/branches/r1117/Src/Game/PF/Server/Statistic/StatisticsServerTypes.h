#pragma once
#include "Server/RPC/Base.h"
#include "StatisticsCommonTypes.h"

//
// ATTENTION!
// AHTUNG!
// У этих структур есть двойники в коде статистики, C#
// Перед любыми изменениями посоветоваться с програмистами сервиса статистики
//

namespace StatisticService
{

namespace ELobbyReaction
{
  enum Enum { None, Accept, Cancel, Slowpoke, PreGameLobbyReady, PreGameLobbyNotReady };
}


typedef ni_detail::UInt64 TMMakingGameId;


namespace ELobbyGameStatus
{
  enum Enum { None, Launched, Dismissed };
}


namespace EGameType
{
  enum Enum
  {
    None,
    Dev_Custom,
    PvX_Matchmaking, //Unused
    PvX_Training, //Unused
    Soc_Matchmaking,
    Soc_Training,
    Soc_Tutorial,
    Soc_Singleplayer,
    Soc_Coop,
    Soc_CustomGame,
    Soc_CustomGameBots
  };
}


namespace RPC
{

struct SessionStartPlayer : rpc::Data
{
  SERIALIZE_ID();
  ZDATA
  int userid;
  int faction;
  int sex;
  int heroid;
  wstring nickname;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&userid); f.Add(3,&faction); f.Add(4,&sex); f.Add(5,&heroid); f.Add(6,&nickname); return 0; }

  SessionStartPlayer() : userid( 0 ), faction( 0 ), sex( 0 ), heroid( 0 ) {}
};



struct SessionStartEvent : rpc::Data
{
  SERIALIZE_ID();
  ZDATA
  __int64 sessionid;
  TMMakingGameId persistentId;
  nstl::wstring map;
  nstl::wstring server;
  nstl::wstring cluster;
  nstl::wstring serverAddr;
  int sessionType;
  vector<SessionStartPlayer> players;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionid); f.Add(3,&persistentId); f.Add(4,&map); f.Add(5,&server); f.Add(6,&cluster); f.Add(7,&serverAddr); f.Add(8,&sessionType); f.Add(9,&players); return 0; }

  SessionStartEvent() : sessionid( 0 ), persistentId( 0 ), sessionType( 0 ) {}
};



struct SessionServerResultsPlayer : rpc::Data
{
  SERIALIZE_ID();
  ZDATA
  int userid;
  int finishStatus; //Peered::EGameFinishClientState::Enum
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&userid); f.Add(3,&finishStatus); return 0; }

  explicit SessionServerResultsPlayer() :
  userid( 0 ), finishStatus( 0 )
  {}
};



struct SessionResultEvent : rpc::Data
{
  SERIALIZE_ID();
  ZDATA

  int result;
  __int64 sessionid;
  SessionClientResults clientData;
  vector<SessionServerResultsPlayer> serverPlayersInfo;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&result); f.Add(3,&sessionid); f.Add(4,&clientData); f.Add(5,&serverPlayersInfo); return 0; }

  SessionResultEvent() : result( 0 ), sessionid( 0 ) {}
};



struct MMakingMember : rpc::Data
{
  SERIALIZE_ID();
  ZDATA

  int     userid;
  int     faction;
  int     sex;
  int     heroid;
  int     heroRating;
  int     playerRating;
  int     guardRating;
  float   force;
  int     partyId;
  float   waitTime;
  int     loseStreak;
  int     fameLevel;
  int     basket; //mmaking::EBasket
  int     lobbyReaction; //ELobbyReaction
  float   lobbyReactionTime;
  int     original_faction;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&userid); f.Add(3,&faction); f.Add(4,&sex); f.Add(5,&heroid); f.Add(6,&heroRating); f.Add(7,&playerRating); f.Add(8,&guardRating); f.Add(9,&force); f.Add(10,&partyId); f.Add(11,&waitTime); f.Add(12,&loseStreak); f.Add(13,&fameLevel); f.Add(14,&basket); f.Add(15,&lobbyReaction); f.Add(16,&lobbyReactionTime); f.Add(17,&original_faction); return 0; }

  MMakingMember() :
  userid( 0 ),
  faction( 0 ),
  sex( 0 ),
  heroid( 0 ),
  heroRating( 0 ),
  playerRating( 0 ),
  guardRating( 0 ),
  force( 0 ),
  partyId( 0 ),
  waitTime( 0 ),
  loseStreak( 0 ),
  fameLevel( 0 ),
  basket( 0 ),
  lobbyReaction( ELobbyReaction::None ),
  lobbyReactionTime( 0 ),
  original_faction( 0 )
  {}
};



struct MMakingGame : rpc::Data
{
  SERIALIZE_ID();
  ZDATA

  TMMakingGameId          persistentId;
  int                     status; //ELobbyGameStatus
  int                     basket; //mmaking::EBasket
  vector<MMakingMember>   members;
  wstring                 map;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&persistentId); f.Add(3,&status); f.Add(4,&basket); f.Add(5,&members); f.Add(6,&map); return 0; }

  MMakingGame() :
  persistentId( 0 ),
  status( ELobbyGameStatus::None ),
  basket( 0 )
  {}
};



struct MMakingCanceled : rpc::Data
{
  SERIALIZE_ID();
  ZDATA

  wstring           map;
  MMakingMember     member;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&map); f.Add(3,&member); return 0; }

  MMakingCanceled()
  {}
};



struct ExceedingStepTimeInfoServer : rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  __int64 sessionId;
  int currentStep;
  __int64 startTime;
  __int64 finishTime;
  int stepCount;
  int stepTimeMin;
  int stepTimeMax;
  int stepTimeAvg;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionId); f.Add(3,&currentStep); f.Add(4,&startTime); f.Add(5,&finishTime); f.Add(6,&stepCount); f.Add(7,&stepTimeMin); f.Add(8,&stepTimeMax); f.Add(9,&stepTimeAvg); return 0; }

  ExceedingStepTimeInfoServer()
  : sessionId(0)
  , currentStep(0)
  , startTime(0)
  , finishTime(0)
  , stepCount(0)
  , stepTimeMin(0)
  , stepTimeMax(0)
  , stepTimeAvg(0)
  {}
};



struct ReconnectAttemptInfo : rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  __int64 sessionId;
  int userId;
  int currentStep;
  int reconnectType;
  int resultCode;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionId); f.Add(3,&userId); f.Add(4,&currentStep); f.Add(5,&reconnectType); f.Add(6,&resultCode); return 0; }

  ReconnectAttemptInfo()
  : sessionId(0)
  , userId(0)
  , currentStep(0)
  , reconnectType(0)
  , resultCode(0)
  {}
};



struct SessionTrafficInfo : rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  __int64 sessionId;
  int totalIn;
  int totalOut;
  float avgOutPerStep;
  int maxOutPerStep;
  int totalInReconnect;
  int totalOutReconnect;
  float avgOutReconnect;
  int maxOutReconnect;
  float avgCmdPerSecond;
  int maxCmdPerSecond;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionId); f.Add(3,&totalIn); f.Add(4,&totalOut); f.Add(5,&avgOutPerStep); f.Add(6,&maxOutPerStep); f.Add(7,&totalInReconnect); f.Add(8,&totalOutReconnect); f.Add(9,&avgOutReconnect); f.Add(10,&maxOutReconnect); f.Add(11,&avgCmdPerSecond); f.Add(12,&maxCmdPerSecond); return 0; }

  SessionTrafficInfo()
  : sessionId(0)
  , totalIn(0)
  , totalOut(0)
  , avgOutPerStep(0.0f)
  , maxOutPerStep(0)
  , totalInReconnect(0)
  , totalOutReconnect(0)
  , avgOutReconnect(0.0f)
  , maxOutReconnect(0)
  , avgCmdPerSecond(0.0f)
  , maxCmdPerSecond(0)
  {}
};



struct SessionUserContext : rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  __int64 sessionid;
  int userid;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionid); f.Add(3,&userid); return 0; }

  SessionUserContext() :
  sessionid( 0 ),
  userid( 0 )
  {}

  SessionUserContext( __int64 _sessionid, int _userid ) :
  sessionid( _sessionid ),
  userid( _userid )
  {}
};



struct UserCheatEvent : rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  SessionUserContext    ctx;
  int                   cheatType;
  wstring               clientIp;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&ctx); f.Add(3,&cheatType); f.Add(4,&clientIp); return 0; }

  UserCheatEvent() :
  cheatType( 0 )
  {}
};



struct UserDisconnectEvent : rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  SessionUserContext    ctx;
  int                   reason;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&ctx); f.Add(3,&reason); return 0; }

  UserDisconnectEvent() :
  reason( 0 )
  {}
};



struct UserStatusEvent : rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  SessionUserContext    ctx;
  int                   status;
  int                   step;
  int                   reason;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&ctx); f.Add(3,&status); f.Add(4,&step); f.Add(5,&reason); return 0; }

  UserStatusEvent() :
  status( 0 ),
  step( 0 ),
  reason( 0 )
  {}
};

} //namespace RPC

} //namespace StatisticService
