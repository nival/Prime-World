using System;
using BusinessLogic.Game;
using log4net;
using StatisticService.ThriftImpls;

namespace StatisticService.RPC
{
  public class StatisticDebugWriter
  {
    private static ILog _log = LogManager.GetLogger(typeof (StatisticDebugWriter));

    private ISessionEventWriter writer;
    private ISessionWriter sessionwriter;
    private readonly GameStatContext.StatisticDebugWriterContext context;


    public StatisticDebugWriter(IUnmanagedRpcCallbacks unrpc, ISessionEventWriter writer, ISessionWriter sessionwriter, GameStatContext.StatisticDebugWriterContext context)
    {
      this.writer = writer;
      this.sessionwriter = sessionwriter;
      this.context = context;

      unrpc.Register(new RemoteCallHandler<ExceedingStepTimeInfo>(LogExceedingStepTime));
      unrpc.Register(new RemoteCallHandler<ExceedingPingTimeInfo>(LogExceedingPingTime));
      unrpc.Register(new RemoteCallHandler<OfflineClientEvent>(LogOfflineEvent));
      unrpc.Register(new RemoteCallHandler<DebugVarMessage>(LogDebugVar));
      unrpc.Register(new RemoteCallHandler<PvxLoginInfo>(LogPvxLogin));
      unrpc.Register(new RemoteCallHandler<PvxScreenResolutionInfo>(LogPvxScreenResolution));
    }

    //remote
    public void LogExceedingStepTime(ExceedingStepTimeInfo info, ICallContext callCtx)
    {
      if (!context.LogExceedingStepTime)
      {
        _log.Debug("ignore event LogExceedingStepTime");
        return;
      }

      _log.DebugFormat("exceeding step time info: sessionId={0}, playerId={1}", info.sessionId, info.playerId);
      try
      {
        writer.ExceedingStepTime(info.sessionId, info.playerId, info.typeId, info.startStep, info.finishStep,
                                 EntitiesConvertor.FromUnixTimestamp(info.startTime, callCtx.transmissionTimestamp),
                                 EntitiesConvertor.FromUnixTimestamp(info.finishTime, callCtx.transmissionTimestamp),
                                 info.stepCount, info.stepTimeMin, info.stepTimeMax, info.stepTimeAvg,
                                 info.lastWorldRequestStep, info.rpcPing, info.transportPing);
      }
      catch (Exception ex)
      {
        _log.Error("Failed to log debug info about exceeding step time, info = " + info, ex);
      }
    }

    //remote
    public void LogExceedingPingTime(ExceedingPingTimeInfo info, ICallContext callCtx)
    {
      if (!context.LogExceedingPingTime)
      {
        _log.Debug("ignore event LogExceedingPingTime");
        return;
      }

      _log.DebugFormat("exceeding ping time info: sessionId={0}, playerId={1}", info.sessionId, info.playerId);
      try
      {
        writer.ExceedingPingTime(info.sessionId, info.playerId, info.typeId,
                                 EntitiesConvertor.FromUnixTimestamp(info.startTime, callCtx.transmissionTimestamp),
                                 EntitiesConvertor.FromUnixTimestamp(info.finishTime, callCtx.transmissionTimestamp),
                                 info.pingLCount, info.pingLTimeMin, info.pingLTimeMax, info.pingLTimeAvg,
                                 info.pingHCount, info.pingHTimeMin, info.pingHTimeMax, info.pingHTimeAvg);
      }
      catch (Exception ex)
      {
        _log.Error("Failed to log debug info about exceeding step time, info = " + info, ex);
      }
    }

    //remote
    public void LogOfflineEvent(OfflineClientEvent evt, ICallContext callCtx)
    {
      if (!context.LogOfflineEvent)
      {
        _log.Debug("ignore event LogOfflineEvent");
        return;
      }

      _log.DebugFormat("offline client event: sessionId={0}", evt );
      try
      {
        writer.LogOfflineEvent(evt.playerId, evt.persistentId, evt.code, evt.auxData, callCtx.ToDate());
      }
      catch (Exception ex)
      {
        _log.Error("Failed to log offline client event, info = " + evt, ex);
      }
    }

    //remote
    public void LogDebugVar(DebugVarMessage msg, ICallContext callCtx)
    {
      if (!context.LogDebugVar)
      {
        _log.Debug("ignore event LogDebugVar");
        return;
      }

      try
      {
        _log.DebugFormat("debug var: sessionId={0}, playerId={1}, {2} = \"{3}\"", msg.sessionId, msg.playerId, msg.debugVarName, msg.debugVarValue);
        writer.DebugVar(msg.sessionId, msg.step, 0, 0, msg.playerId, msg.debugVarName, msg.debugVarValue, callCtx.ToDate());
      }
      catch (Exception ex)
      {
        _log.Error("Failed to log debug var.", ex);
      }
    }

    //remote
    public void LogPvxLogin(PvxLoginInfo info, ICallContext callCtx)
    {
      if (!context.LogPvxLogin)
      {
        _log.Debug("ignore event LogPvxLogin");
        return;
      }

      try
      {
        _log.DebugFormat("pvx login: sessionId={0}, playerId={1}, relayAddress={2}", info.sessionId, info.playerId, info.relayAddress);
        sessionwriter.SessionRelayInfo(info.sessionId, info.playerId, info.relayAddress);
      }
      catch ( Exception ex )
      {
        _log.Error("Failed to log pvx login.", ex);
      }
    }


    //remote
    public void LogPvxScreenResolution(PvxScreenResolutionInfo info, ICallContext callCtx)
    {
      if (!context.LogPvxScreenResolution)
      {
        _log.Debug("ignore event LogPvxScreenResolution");
        return;
      }
      
      try
      {
        _log.DebugFormat("pvx screen resolution: info={0}", info);
        // Пока информация пишется в таблицу дебагваров (как это было раньше)
        // захардкодил имя дебагвара
        writer.DebugVar(info.sessionId, 0, 0, 0, info.playerId, "ScreenResolution", String.Format("{0}x{1}", info.width, info.height), callCtx.ToDate());
      }
      catch (Exception ex)
      {
        _log.Error("Failed to log pvx login.", ex);
      }
    }
  }
}