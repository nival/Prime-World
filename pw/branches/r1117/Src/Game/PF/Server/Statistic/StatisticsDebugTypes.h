#pragma once
#include <Server/RPC/all.h>

namespace StatisticService
{
namespace RPC
{

  struct DebugVarMessage : rpc::Data
  {
    SERIALIZE_ID();
    ZDATA
    __int64 sessionId;
    int playerId;
    int step;
    wstring debugVarName;
    wstring debugVarValue;

    ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionId); f.Add(3,&playerId); f.Add(4,&step); f.Add(5,&debugVarName); f.Add(6,&debugVarValue); return 0; }

    DebugVarMessage() :
    sessionId( 0 ),
    playerId( 0 ),
    step( 0 )
    {}
  };


  enum ExceedingStepTimeType
  {
    LogicStepTime   = 0x00000001,
    ServerStepTime  = 0x00000002,
    NoDataTime      = 0x00000004,
    AltTabFlag      = 0x00000008,
    DragFlag        = 0x00000010,
    InactiveFlag    = 0x00000020,
    RpcQueueTime    = 0x00000040,
    OpenedFileFlag  = 0x00000080,
    ScreenshotFlag  = 0x00000100,
  };


  struct ExceedingStepTimeInfo : rpc::Data
  {
    SERIALIZE_ID();
    ZDATA
    int typeId;
    __int64 sessionId;
    int playerId;
    int startStep;
    int finishStep;
    __int64 startTime;
    __int64 finishTime;
    int stepCount;
    int stepTimeMin;
    int stepTimeMax;
    int stepTimeAvg;
    int lastWorldRequestStep;
    int rpcPing;
    int transportPing;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&typeId); f.Add(3,&sessionId); f.Add(4,&playerId); f.Add(5,&startStep); f.Add(6,&finishStep); f.Add(7,&startTime); f.Add(8,&finishTime); f.Add(9,&stepCount); f.Add(10,&stepTimeMin); f.Add(11,&stepTimeMax); f.Add(12,&stepTimeAvg); f.Add(13,&lastWorldRequestStep); f.Add(14,&rpcPing); f.Add(15,&transportPing); return 0; }
  };

  enum ExceedingPingTimeType
  {
    GameServerRPCPingTime,
    GameServerTransportPingTime,
    LobbyServerTransportPingTime,
  };

  struct ExceedingPingTimeInfo : rpc::Data
  {
    SERIALIZE_ID();
    ZDATA
    int typeId;
    __int64 sessionId;
    int playerId;
    __int64 startTime;
    __int64 finishTime;
    int pingLCount;
    int pingLTimeMin;
    int pingLTimeMax;
    int pingLTimeAvg;
    int pingHCount;
    int pingHTimeMin;
    int pingHTimeMax;
    int pingHTimeAvg;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&typeId); f.Add(3,&sessionId); f.Add(4,&playerId); f.Add(5,&startTime); f.Add(6,&finishTime); f.Add(7,&pingLCount); f.Add(8,&pingLTimeMin); f.Add(9,&pingLTimeMax); f.Add(10,&pingLTimeAvg); f.Add(11,&pingHCount); f.Add(12,&pingHTimeMin); f.Add(13,&pingHTimeMax); f.Add(14,&pingHTimeAvg); return 0; }
  };


  struct OfflineClientEvent : rpc::Data
  {
    SERIALIZE_ID();
    ZDATA
    int playerId;
    __int64 persistentId;
    int code;
    __int64 auxData;
    int eventTimestamp;
    int clientTimestampForSync;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&playerId); f.Add(3,&persistentId); f.Add(4,&code); f.Add(5,&auxData); f.Add(6,&eventTimestamp); f.Add(7,&clientTimestampForSync); return 0; }

    OfflineClientEvent() :
    playerId( 0 ), persistentId( 0 ), code( 0 ), auxData( 0 ), eventTimestamp( 0 ), clientTimestampForSync( 0 ) {}
  };



  struct PvxLoginInfo : rpc::Data
  {
    SERIALIZE_ID();
    ZDATA
    __int64 sessionId;
    int playerId;
    wstring relayAddress;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionId); f.Add(3,&playerId); f.Add(4,&relayAddress); return 0; }

    PvxLoginInfo() : sessionId(0), playerId(0) {}
    PvxLoginInfo(__int64 _sessionId, int _playerId, const wstring & _relayAddress) 
      : sessionId(_sessionId), playerId(_playerId), relayAddress(_relayAddress) {}
  };


  struct PvxScreenResolutionInfo : rpc::Data
  {
    SERIALIZE_ID();
    ZDATA
    __int64 sessionId;
    int playerId;
    int width;
    int height;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionId); f.Add(3,&playerId); f.Add(4,&width); f.Add(5,&height); return 0; }

    PvxScreenResolutionInfo() : playerId( 0 ), width( 0 ), height( 0 ) {}
    PvxScreenResolutionInfo( __int64 _sessionId, int _playerId, int _w, int _h ) :
    sessionId( _sessionId ),
    playerId( _playerId ),
    width( _w ),
    height( _h )
    {}
  };

}  // namespace RPC

}  // namespace StatisticService
