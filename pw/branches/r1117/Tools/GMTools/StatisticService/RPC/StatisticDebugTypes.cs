using System;

namespace StatisticService.RPC
{
  public class DebugVarMessage : ISerializable
  {
    public long sessionId;
    public int playerId;
    public int step;
    public string debugVarName;
    public string debugVarValue;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sessionId);
      s.Add(ref playerId);
      s.Add(ref step);
      s.Add(ref debugVarName);
      s.Add(ref debugVarValue);
    }
  }



  public class ExceedingStepTimeInfo : ISerializable
  {
    public int typeId;
    public long sessionId;
    public int playerId;
    public int startStep;
    public int finishStep;
    public long startTime;
    public long finishTime;
    public int stepCount;
    public int stepTimeMin;
    public int stepTimeMax;
    public int stepTimeAvg;
    public int lastWorldRequestStep;
    public int rpcPing;
    public int transportPing;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref typeId);
      s.Add(ref sessionId);
      s.Add(ref playerId);
      s.Add(ref startStep);
      s.Add(ref finishStep);
      s.Add(ref startTime);
      s.Add(ref finishTime);
      s.Add(ref stepCount);
      s.Add(ref stepTimeMin);
      s.Add(ref stepTimeMax);
      s.Add(ref stepTimeAvg);
      s.Add(ref lastWorldRequestStep);
      s.Add(ref rpcPing);
      s.Add(ref transportPing);
    }

    public override string ToString()
    {
      return String.Format("ExceedingStepTimeInfo(TypeID={0},SessionID={1},PlayerID={2},StartStep={3},FinishStep={4},StartTime={5},FinishTime={6},StepCount={7},StepTimeMin={8},StepTimeMax={9},StepTimeAvg={10},LastWorldRequestStep={11},RpcPing={12},TransportPing={13})",
                           typeId, sessionId, playerId, startStep, finishStep, startTime, finishTime, stepCount, stepTimeMin, stepTimeMax, stepTimeAvg, lastWorldRequestStep, rpcPing, transportPing);
    }
  }

  public class ExceedingPingTimeInfo : ISerializable
  {
    public int typeId;
    public long sessionId;
    public int playerId;
    public long startTime;
    public long finishTime;
    public int pingLCount;
    public int pingLTimeMin;
    public int pingLTimeMax;
    public int pingLTimeAvg;
    public int pingHCount;
    public int pingHTimeMin;
    public int pingHTimeMax;
    public int pingHTimeAvg;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref typeId);
      s.Add(ref sessionId);
      s.Add(ref playerId);
      s.Add(ref startTime);
      s.Add(ref finishTime);
      s.Add(ref pingLCount);
      s.Add(ref pingLTimeMin);
      s.Add(ref pingLTimeMax);
      s.Add(ref pingLTimeAvg);
      s.Add(ref pingHCount);
      s.Add(ref pingHTimeMin);
      s.Add(ref pingHTimeMax);
      s.Add(ref pingHTimeAvg);
    }

    public override string ToString()
    {
      return string.Format("ExceedingPingTimeInfo(TypeID={0},SessionID={1},PlayerID={2},StartTime={3},FinishTime={4},PingLCount={5},PingLTimeMin={6},PingLTimeMax={7},PingLTimeAvg={8},PingHCount={9},PingHTimeMin={10},PingHTimeMax={11},PingHTimeAvg={12})",
                           typeId, sessionId, playerId, startTime, finishTime, pingLCount, pingLTimeMin, pingLTimeMax, pingLTimeAvg, pingHCount, pingHTimeMin, pingHTimeMax, pingHTimeAvg);
    }
  }


  public class OfflineClientEvent : ISerializable
  {
    public int playerId;
    public long persistentId;
    public int code;
    public long auxData;
    public int eventTimestamp;
    public int clientTimestampForSync;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref playerId);
      s.Add(ref persistentId);
      s.Add(ref code);
      s.Add(ref auxData);
      s.Add(ref eventTimestamp);
      s.Add(ref clientTimestampForSync);
    }

    public override string ToString()
    {
      return string.Format("OfflineClientEvent(PlayerId={0}, PersistentId={1}, Code={2}, AuxData={3}, ClientTimestamp={4}, ClientTimestampForSync={5})",
                           playerId, persistentId, code, auxData, eventTimestamp, clientTimestampForSync);
    }
  }


  public class PvxLoginInfo : ISerializable
  {
    public long sessionId;
    public int playerId;
    public string relayAddress;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sessionId);
      s.Add(ref playerId);
      s.Add(ref relayAddress);
    }

    public override string ToString()
    {
      return string.Format("PvxLoginInfo(SessionId={0}, PlayerId={1}, RelayAddress={2})",
                           sessionId, playerId, relayAddress);
    }
  }


  public class PvxScreenResolutionInfo : ISerializable
  {
    public long sessionId;
    public int playerId;
    public int width;
    public int height;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sessionId);
      s.Add(ref playerId);
      s.Add(ref width);
      s.Add(ref height);
    }

    public override string ToString()
    {
      return string.Format("PvxScreenResolutionInfo(SessionId={0}, PlayerId={1}, width={2}, height={3})", sessionId, playerId, width, height);
    }
  }
}
