using System;
using BusinessLogic.Game;
using log4net;


namespace StatisticService.RPC
{
  public class StatisticWriter
  {
    private static ILog _log = LogManager.GetLogger(typeof(StatisticWriter));

    private readonly ISessionEventWriter _sessionEventWriter;
    private readonly GameStatContext.StatisticWriterContext _context;


    public StatisticWriter(IUnmanagedRpcCallbacks unrpc, ISessionEventWriter writer, GameStatContext.StatisticWriterContext context)
    {
      _sessionEventWriter = writer;
      _context = context;

      unrpc.Register(new RemoteCallHandler<ClientCommonSessionEvent>(LogSessionEvent));
      unrpc.Register(new RemoteCallHandler<ClientSessionDamageMessage>(LogSessionDamage));
    }

    //remote
    public void LogSessionEvent(ClientCommonSessionEvent evt, ICallContext callCtx)
    {
      if (!_context.LogSessionEvent.Contains(evt.eventType))
      {
        _log.DebugFormat("ignore event LogSessionEvent(type={0})", evt.eventType);
        return;
      }

      CommonSessionEventInfo common = evt.common;
      float x = evt.x, y = evt.y;
      int eventType = evt.eventType;
      SessionEventInfo info = evt.info;

      if (!Enum.IsDefined(typeof(SessionEventType), eventType))
      {
        _log.WarnFormat("{0} unknown event type id", eventType);
        return;
      }

      _log.DebugFormat("event {0}: sessionId={1}, playerId={2}", (SessionEventType)eventType, common.sessionId, common.playerId);
      try
      {
        switch ((SessionEventType) eventType)
        {
          case SessionEventType.TalentUsed:
            _sessionEventWriter.TalentUsed(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.TalentSwitchedOff:
            _sessionEventWriter.TalentSwitchedOff(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.TalentUnlocked:
            _sessionEventWriter.TalentUnlocked(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2);
            break;

          case SessionEventType.ImpulsiveBuffUsed:
            _sessionEventWriter.ImpulsiveBuffUsed(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.ImpulsiveBuffSuggested:
            _sessionEventWriter.ImpulsiveBuffSuggested(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.CheatUsed:
            _sessionEventWriter.CheatUsed(common.sessionId, common.step, x, y, common.playerId, info.strParam1);
            break;

          case SessionEventType.TimeSlice:
            _sessionEventWriter.TimeSlice(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2, info.intParam3, info.intParam4);
            break;

          case SessionEventType.MG2Started:
            _sessionEventWriter.MG2Started(common.sessionId, common.step, x, y, common.playerId);
            break;

          case SessionEventType.MG2BoostUsage:
            _sessionEventWriter.MG2BoostUsage(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.MG2LevelFailed:
            _sessionEventWriter.MG2LevelFailed(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2);
            break;

          case SessionEventType.MG2BallsChanged:
            _sessionEventWriter.MG2BallsChanged(common.sessionId, common.step, x, y, common.playerId);
            break;

          case SessionEventType.MG2LevelWon:
            _sessionEventWriter.MG2LevelWon(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2);
            break;

          case SessionEventType.MG2LevelStarted:
            _sessionEventWriter.MG2LevelStarted(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2);
            break;

          case SessionEventType.MG2Exit:
            _sessionEventWriter.MG2Exit(common.sessionId, common.step, x, y, common.playerId);
            break;

          case SessionEventType.Kill:
            _sessionEventWriter.Kill(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2);
            break;

          case SessionEventType.Death:
            _sessionEventWriter.Death(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2);
            break;

          case SessionEventType.Assist:
            _sessionEventWriter.Assist(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2, info.intParam3);
            break;

          case SessionEventType.LevelUp:
            _sessionEventWriter.LevelUp(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.ConsumableBought:
            _sessionEventWriter.ConsumableBought(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2);
            break;

          case SessionEventType.ConsumableUsed:
            _sessionEventWriter.ConsumableUsed(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.Achievement:
            _sessionEventWriter.Achievement(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.Ressurection:
            _sessionEventWriter.Ressurection(common.sessionId, common.step, x, y, common.playerId);
            break;

          case SessionEventType.BuildingDestroyed:
            _sessionEventWriter.BuildingDestroyed(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2, info.intParam3);
            break;

          case SessionEventType.FlagRaised:
            _sessionEventWriter.Flag(common.sessionId, common.step, x, y, common.playerId, true, info.intParam1, info.intParam2, info.intParam3, info.intParam4, info.intParam5);
            break;

          case SessionEventType.FlagDropped:
            _sessionEventWriter.Flag(common.sessionId, common.step, x, y, common.playerId, false, info.intParam1, info.intParam2, info.intParam3, info.intParam4, info.intParam5);
            break;

          case SessionEventType.NaftaIncomeFromHero:
            _sessionEventWriter.NaftaIncomeFromHero(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2, info.intParam3);
            break;

          case SessionEventType.NaftaIncomeFromBuilding:
            _sessionEventWriter.NaftaIncomeFromBuilding(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2, info.intParam3);
            break;

          case SessionEventType.NaftaIncomeFromCreature:
            _sessionEventWriter.NaftaIncomeFromCreature(common.sessionId, common.step, x, y, common.playerId, info.intParam1, info.intParam2, info.intParam3);
            break;

          case SessionEventType.NaftaIncomeFromTalent:
            _sessionEventWriter.NaftaIncomeFromTalent(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.NaftaIncomeFromImpulsiveBuff:
            _sessionEventWriter.NaftaIncomeFromImpulsiveBuff(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.NaftaIncomeFromMinigame:
            _sessionEventWriter.NaftaIncomeFromMinigame(common.sessionId, common.step, x, y, common.playerId, info.intParam1);
            break;

          case SessionEventType.ScriptEvent:
            _sessionEventWriter.ScriptEvent(common.sessionId, common.step, common.playerId, info.strParam1, info.strParam2,
                                            info.intParam1, info.intParam2, info.intParam3, info.intParam4, info.intParam5);
            break;

          default:
            _log.WarnFormat("{0} event not implemented: sessionid={1}, playerid={2}, info={3}",
                            (SessionEventType)eventType, common.sessionId, common.playerId, info);
            break;
        }
      }
      catch(Exception ex)
      {
        _log.Error("Failed to log session event.", ex);
      }
    }

    //remote
    public void LogSessionDamage(ClientSessionDamageMessage msg, ICallContext callCtx)
    {
      if (!_context.LogSessionDamage)
      {
        _log.Debug("ignore event LogSessionDamage");
        return;
      }

      CommonSessionEventInfo common = msg.common;
      SessionDamageInfo info = msg.info;

      _log.DebugFormat("damage report: sessionId={0}, playerId={1}", common.sessionId, common.playerId);

      try
      {
        _sessionEventWriter.Damage(common.sessionId, common.step, 0, 0, common.playerId, info.dealt, info.opponentId, info.unitType, info.talentId, info.physicalDamage, info.magicalDamage, info.pureDamage);
      }
      catch (Exception ex)
      {
        _log.Error("Failed to log damage report.", ex);
      }
    }
  }
}
