using System;
using System.Linq;
using BusinessLogic.Game;
using KontagentLib;
using StatisticService.ThriftImpls;
using log4net;


namespace StatisticService.RPC
{
  public class StatisticClusterWriter
  {
    private static ILog _log = LogManager.GetLogger(typeof(StatisticClusterWriter));

    private ISessionWriter writer;
    private ISessionEventWriter eventwriter;
    private IKontagentManager kontagentManager;


    public StatisticClusterWriter(IUnmanagedRpcCallbacks unrpc, ISessionWriter writer, ISessionEventWriter eventwriter, IKontagentManager km)
    {
      this.writer = writer;
      this.eventwriter = eventwriter;
      this.kontagentManager = km;

      unrpc.Register(new RemoteCallHandler<SessionStartEvent>(LogSessionStart));
      unrpc.Register(new RemoteCallHandler<SessionResultEvent>(LogSessionResults));
      unrpc.Register(new RemoteCallHandler<MMakingCanceled>(LogMMakingCancelled));
      unrpc.Register(new RemoteCallHandler<MMakingGame>(LogMMakingGame));
      unrpc.Register(new RemoteCallHandler<UserDisconnectEvent>(LogUserDisconnected));
      unrpc.Register(new RemoteCallHandler<UserStatusEvent>(LogUserStatus));
      unrpc.Register(new RemoteCallHandler<UserCheatEvent>(LogUserCheated));
      unrpc.Register(new RemoteCallHandler<ExceedingStepTimeInfoServer>(LogGSLag));
      unrpc.Register(new RemoteCallHandler<ReconnectAttemptInfo>(LogReconnect));
      unrpc.Register(new RemoteCallHandler<SessionTrafficInfo>(LogTraffic));
    }

    //remote
    public void LogSessionStart(SessionStartEvent info, ICallContext callCtx)
    {
      try
      {
        _log.DebugFormat("Session start "  + info);
        writer.SessionStart(info.sessionid, info.map, info.server, info.serverAddr, info.cluster, info.sessionType, callCtx.ToDate(),
                            info.players.Select(p => (SessionStartPlayerInfo)p));

        if (kontagentManager != null)
          foreach(var player in info.players)
            kontagentManager.SessionStart(player.userid, player.faction, info.sessionType, player.heroid);
      }
      catch (Exception ex)
      {
        _log.Error("Failed to write session start " + info, ex);
      }
    }

    //remote
    public void LogSessionResults(SessionResultEvent info, ICallContext callCtx)
    {
      try
      {
        _log.DebugFormat("Session results " + info);
        writer.SessionResult(info.sessionid, info.result, info.clientData.sideWon, info.clientData.surrenderVote, callCtx.ToDate(),
          info.clientData.players.Select(p =>
          new SessionResultPlayerInfo
          {
            UserId = p.userid,
            FinalLevel = p.scoring.finalLevel,
            Leaver = info.serverPlayersInfo.Single(i => i.userid == p.userid).finishStatus != (int)EGameFinishClientState.FinishedGame,
            Score = p.scoring.score,
            Kills = p.scoring.kills,
            Deaths = p.scoring.deaths,
            Assists = p.scoring.assists,
            EnemyCreepsKilled = p.scoring.enemyCreepsKilled,
            NeutralCreepsKilled = p.scoring.neutralCreepsKilled
          }
          ));
      }
      catch (Exception ex)
      {
        _log.Error("Failed to write session results " + info, ex);
      }
    }

    //remote
    public void LogMMakingCancelled(MMakingCanceled info, ICallContext callCtx)
    {
      try
      {
        _log.Debug("Matchmaking cancelled " + info.member + ", map " + info.map);
        writer.MMakingCancelled((MMakingPlayerInfo)info.member, callCtx.ToDate());
      }
      catch (Exception ex)
      {
        _log.Error("EXCEPTIONARE:", ex );
      }
    }

    //remote
    public void LogMMakingGame(MMakingGame game, ICallContext callCtx)
    {
      try
      {
        _log.Debug("Matchmaking session has created " + game);
        writer.MMakingSession(game.persistentId, game.status, -1, game.basket, game.map, callCtx.ToDate(), game.members.Select(m => (MMakingPlayerInfo)m));
      }
      catch (Exception ex)
      {
        _log.Error("EXCEPTIONARE:", ex);
      }
    }

    //'reason' is Peered::Status from C++ PeeredTypes.h
    //remote
    public void LogUserDisconnected(UserDisconnectEvent evt, ICallContext callCtx)
    {
      try
      {
        _log.DebugFormat("User dropped: {0}, {1}", evt.ctx, evt.reason);
        eventwriter.Disconnect(evt.ctx.sessionid, evt.ctx.userid, evt.reason, callCtx.ToDate());
      }
      catch (Exception ex)
      {
        _log.Error("EXCEPTIONARE:", ex);
      }
    }

    //'status' is Peered::Status from C++ PeeredTypes.h
    //'reason' is Peered::EDisconnectReason::Enum from C++ Peered.h
    //remote
    public void LogUserStatus(UserStatusEvent evt, ICallContext callCtx)
    {
      try
      {
        _log.DebugFormat("User status: {0}, {1}, {2}, {3}", evt.ctx, evt.status, evt.step, evt.reason);
        //TODO...
      }
      catch (Exception ex)
      {
        _log.Error("EXCEPTIONARE:", ex);
      }
    }

    // 'cheatType' is lobby::ECheatType from C++ ISessionHybridLink.h
    //remote
    public void LogUserCheated(UserCheatEvent evt, ICallContext callCtx)
    {
      try
      {
        _log.DebugFormat("User cheated: {0}, {1}, {2}", evt.ctx, evt.cheatType, evt.clientIp);
        eventwriter.Cheat(evt.ctx.sessionid, evt.ctx.userid, evt.cheatType, evt.clientIp, callCtx.ToDate());
      }
      catch (Exception ex)
      {
        _log.Error("EXCEPTIONARE:", ex);
      }
    }

    //remote
    public void LogGSLag(ExceedingStepTimeInfoServer info, ICallContext callCtx)
    {
      try
      {
        _log.Debug("GS lag: " + info);
        eventwriter.ExceedingServerStepTime(info.sessionId, info.currentStep,
                                            EntitiesConvertor.FromUnixTimestamp(info.startTime, callCtx.transmissionTimestamp),
                                            EntitiesConvertor.FromUnixTimestamp(info.finishTime, callCtx.transmissionTimestamp),
                                            info.stepCount, info.stepTimeMin, info.stepTimeMax, info.stepTimeAvg);
      }
      catch (Exception ex)
      {
        _log.Error("EXCEPTIONARE:", ex);
      }
    }

    //remote
    public void LogReconnect(ReconnectAttemptInfo info, ICallContext callCtx)
    {
      try
      {
        _log.Debug("Reconnect: " + info);
        eventwriter.Reconnect(info.sessionId, info.userId, info.currentStep,
                              ((ReconnectType) info.reconnectType).ToString().ToLower(),
                              ((ReconnectResult) info.resultCode).ToString().ToLower(),
                              callCtx.ToDate());
      }
      catch (Exception ex)
      {
        _log.Error("EXCEPTIONARE:", ex);
      }
    }

    //remote
    public void LogTraffic(SessionTrafficInfo info, ICallContext callCtx)
    {
      try
      {
        _log.Debug("Traffic: " + info);
        eventwriter.GSTraffic(info.sessionId, info.totalIn, info.totalOut, info.avgOutPerStep, info.maxOutPerStep, info.totalInReconnect,
                              info.totalOutReconnect, info.avgOutReconnect, info.maxOutReconnect, info.avgCmdPerSecond, info.maxCmdPerSecond);
      }
      catch ( Exception ex )
      {
        _log.Error( "EXCEPTIONARE:", ex );
      }
    }
  }
}
