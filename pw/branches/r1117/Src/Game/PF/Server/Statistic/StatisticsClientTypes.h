#pragma once
#include <Server/RPC/all.h>
#include "PF_GameLogic/GameLogicStatisticsTypes.h"

namespace StatisticService
{

namespace RPC
{

struct CommonSessionEventInfo : rpc::Data
{
  SERIALIZE_ID();
  ZDATA
  __int64 sessionId;
  int playerId;
  int step;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionId); f.Add(3,&playerId); f.Add(4,&step); return 0; }

  CommonSessionEventInfo() :
  sessionId( 0 ),
  playerId( 0 ),
  step( 0 )
  {}

  CommonSessionEventInfo( __int64 _sessionId, int _playerId, int _step ) :
  sessionId( _sessionId ),
  playerId( _playerId ),
  step( _step )
  {}
};



struct ClientCommonSessionEvent : rpc::Data
{
  SERIALIZE_ID();
  ZDATA
  CommonSessionEventInfo  common;
  float                   x;
  float                   y;
  int                     eventType;
  SessionEventInfo        info;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&common); f.Add(3,&x); f.Add(4,&y); f.Add(5,&eventType); f.Add(6,&info); return 0; }

  ClientCommonSessionEvent() :
  x( 0 ),
  y( 0 ),
  eventType( 0 )
  {}
};



struct ClientSessionDamageMessage : rpc::Data
{
  SERIALIZE_ID();
  ZDATA
  CommonSessionEventInfo  common;
  SessionDamageInfo       info;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&common); f.Add(3,&info); return 0; }

  ClientSessionDamageMessage()
  {}
};

}

}
