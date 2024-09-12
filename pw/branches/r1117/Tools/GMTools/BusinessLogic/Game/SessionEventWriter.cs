using System;
using System.Collections.Generic;
using BusinessLogic.DBLogs;
using BusinessLogic.DBLogs.Mapping;
using BusinessLogic.Queuing;
using DataLogging;

namespace BusinessLogic.Game
{
  public class SessionEventWriter : ISessionEventWriter
  {
    private readonly IDBLogsStorage storage;

    public enum Tables
    {
      Logs,
      Management
    }

    public SessionEventWriter(string connectionString, Tables tables)
    {
      var dlcontext = new DataLoggingContext(connectionString);
      var dbwriter = new DatabaseWriter(dlcontext);
      
      IEnumerable<TableFormat> tableformats = null;
      switch (tables)
      {
        case Tables.Logs:
          tableformats = TablesMapping.GetLogsTables(); 
          break;
        case Tables.Management:
          tableformats = TablesMapping.GetManagementTables();
          break;
      }

      this.storage = new DBLogsStorage(new TaskExecutor { Name = "SessionEventWriter" }, dbwriter, tableformats);
    }

    public SessionEventWriter(IDBLogsStorage storage)
    {
      this.storage = storage;
    }

    public bool IsRunning
    {
      get { return storage.IsRunning; }
    }

    public void TalentUsed(long sessionId, int step, float x, float y, long playerid, int talentId)
    {
      storage.WriteIn("talentused", sessionId, step, x, y, playerid, talentId);
    }

    public void TalentSwitchedOff(long sessionId, int step, float x, float y, long playerid, int talentId)
    {
      storage.WriteIn("talentswitchedoff", sessionId, step, x, y, playerid, talentId);
    }

    public void TalentUnlocked(long sessionId, int step, float x, float y, long playerid, int talentId, int nafta)
    {
      storage.WriteIn("talentunlocked", sessionId, step, x, y, playerid, talentId, nafta);
    }

    public void ImpulsiveBuffUsed(long sessionId, int step, float x, float y, long playerid, int impulsiveBuffId)
    {
      storage.WriteIn("impulsivebuffused", sessionId, step, x, y, playerid, impulsiveBuffId);
    }

    public void ImpulsiveBuffSuggested(long sessionId, int step, float x, float y, long playerid, int impulsiveBuffId)
    {
      storage.WriteIn("impulsivebuffsuggested", sessionId, step, x, y, playerid, impulsiveBuffId);
    }

    public void CheatUsed(long sessionId, int step, float x, float y, long playerid, string command)
    {
      storage.WriteIn("cheatused", sessionId, step, x, y, playerid, command);
    }

    public void TimeSlice(long sessionId, int step, float x, float y, long playerid, int slice, int level, int totalNafta, int salaryNafta)
    {
      storage.WriteIn("timeslice", sessionId, step, x, y, playerid, slice, level, totalNafta, salaryNafta);
    }

    public void Kill(long sessionId, int step, float x, float y, long playerid, long victimPlayerId, int victimCreatureId)
    {
      storage.WriteIn("kill", sessionId, step, x, y, playerid, victimPlayerId, victimCreatureId);
    }

    public void Death(long sessionId, int step, float x, float y, long playerid, long killerPlayerId, int killerCreatureId)
    {
      storage.WriteIn("death", sessionId, step, x, y, playerid, killerPlayerId, killerCreatureId);
    }

    public void Assist(long sessionId, int step, float x, float y, long playerid, long victimPlayerId, long killerPlayerId, int killerCreatureId)
    {
      storage.WriteIn("assist", sessionId, step, x, y, playerid, victimPlayerId, killerPlayerId, killerCreatureId);
    }

    public void LevelUp(long sessionId, int step, float x, float y, long playerid, int level)
    {
      storage.WriteIn("levelup", sessionId, step, x, y, playerid, level);
    }

    public void ConsumableBought(long sessionId, int step, float x, float y, long playerid, int consumableId, int nafta)
    {
      storage.WriteIn("consumablebought", sessionId, step, x, y, playerid, consumableId, nafta);
    }

    public void ConsumableUsed(long sessionId, int step, float x, float y, long playerid, int consumableId)
    {
      storage.WriteIn("consumableused", sessionId, step, x, y, playerid, consumableId);
    }

    public void Achievement(long sessionId, int step, float x, float y, long playerid, int achievementId)
    {
      storage.WriteIn("achievement", sessionId, step, x, y, playerid, achievementId);
    }

    public void Ressurection(long sessionId, int step, float x, float y, long playerid)
    {
      storage.WriteIn("ressurection", sessionId, step, x, y, playerid);
    }

    #region World events

    public void BuildingDestroyed(long sessionId, int step, float x, float y, long playerid, int buildingId,
                                  long destroyerPlayerId, int destroyerCreatureId)
    {
      storage.WriteIn("buildingdestroyed", sessionId, step, x, y, playerid, buildingId,
                      destroyerPlayerId, destroyerCreatureId);
    }

    public void Flag(long sessionId, int step, float x, float y, long playerid, bool raised, int faction,
                     int road, int segment, long activatorPlayerId, int activatorCreatureId)
    {
      storage.WriteIn("flag", sessionId, step, x, y, playerid, raised, faction,
                      road, segment, activatorPlayerId, activatorCreatureId);
    }

    #endregion

    #region NaftaIncome events

    public void NaftaIncomeFromHero(long sessionId, int step, float x, float y, long playerid, 
                                    int naftaForKill, int naftaSpecForKill, int teamNaftaForKill)
    {
      storage.WriteIn("naftaincome", sessionId, step, x, y, playerid, (int)NaftaIncomeFrom.Hero,
                      naftaForKill, naftaSpecForKill, teamNaftaForKill, 0);
    }

    public void NaftaIncomeFromCreature(long sessionId, int step, float x, float y, long playerid,
                                        int naftaForKill, int naftaSpecForKill, int teamNaftaForKill)
    {
      storage.WriteIn("naftaincome", sessionId, step, x, y, playerid, (int)NaftaIncomeFrom.Creature,
                      naftaForKill, naftaSpecForKill, teamNaftaForKill, 0);
    }

    public void NaftaIncomeFromBuilding(long sessionId, int step, float x, float y, long playerid,
                                        int naftaForKill, int naftaSpecForKill, int teamNaftaForKill)
    {
      storage.WriteIn("naftaincome", sessionId, step, x, y, playerid, (int)NaftaIncomeFrom.Building,
                      naftaForKill, naftaSpecForKill, teamNaftaForKill, 0);
    }

    public void NaftaIncomeFromTalent(long sessionId, int step, float x, float y, long playerid, int nafta)
    {
      storage.WriteIn("naftaincome", sessionId, step, x, y, playerid, (int)NaftaIncomeFrom.Talent, 0, 0, 0, nafta);
    }

    public void NaftaIncomeFromImpulsiveBuff(long sessionId, int step, float x, float y, long playerid, int nafta)
    {
      storage.WriteIn("naftaincome", sessionId, step, x, y, playerid, (int)NaftaIncomeFrom.ImpulsiveBuff, 0, 0, 0, nafta);
    }

    public void NaftaIncomeFromMinigame(long sessionId, int step, float x, float y, long playerid, int nafta)
    {
      storage.WriteIn("naftaincome", sessionId, step, x, y, playerid, (int)NaftaIncomeFrom.Minigame, 0, 0, 0, nafta);
    }

    #endregion

    #region MG2 events

    public void MG2Started(long sessionId, int step, float x, float y, long playerid)
    {
      storage.WriteIn("mg2started", sessionId, step, x, y, playerid);
    }

    public void MG2Exit(long sessionId, int step, float x, float y, long playerid)
    {
      storage.WriteIn("mg2exit", sessionId, step, x, y, playerid);
    }

    public void MG2LevelStarted(long sessionId, int step, float x, float y, long playerid, int level, int paint)
    {
      storage.WriteIn("mg2levelstarted", sessionId, step, x, y, playerid, level, paint);
    }

    public void MG2LevelWon(long sessionId, int step, float x, float y, long playerid, int level, int paint)
    {
      storage.WriteIn("mg2levelwon", sessionId, step, x, y, playerid, level, paint);
    }

    public void MG2LevelFailed(long sessionId, int step, float x, float y, long playerid, int level, int paint)
    {
      storage.WriteIn("mg2levelfailed", sessionId, step, x, y, playerid, level, paint);
    }

    public void MG2BallsChanged(long sessionId, int step, float x, float y, long playerid)
    {
      storage.WriteIn("mg2ballschanged", sessionId, step, x, y, playerid);
    }

    public void MG2BoostUsage(long sessionId, int step, float x, float y, long playerid, int boostId)
    {
      storage.WriteIn("mg2boostused", sessionId, step, x, y, playerid, boostId);
    }

    #endregion

    public void Damage(long sessionId, int step, float x, float y, long playerid, bool dealt, int opponentId,
                       int unitType, int talentId, float physicalDamage, float magicalDamage, float pureDamage)
    {
      storage.WriteIn("damage", sessionId, step, playerid, dealt,
                      opponentId, unitType, talentId, physicalDamage, magicalDamage, pureDamage);
    }

    public void DebugVar(long sessionId, int step, float x, float y, long playerid, string name, string value, DateTime timestamp)
    {
      storage.WriteIn("debugvar", sessionId, step, timestamp, playerid, name, value);
    }

    public void ScriptEvent(long sessionId, int step, long playerId, string strParam1, string strParam2,
                            int intParam1, int intParam2, int intParam3, int intParam4, int intParam5)
    {
      storage.WriteIn("scriptevent", sessionId, step, playerId, strParam1, strParam2, intParam1, intParam2, intParam3, intParam4, intParam5);
    }

    public void Disconnect(long sessionId, long playerid, int reason, DateTime timestamp)
    {
      storage.WriteIn("disconnect", sessionId, playerid, reason, timestamp);
    }

    public void Reconnect(long sessionId, long playerid, int step, string type, string result, DateTime timestamp)
    {
      storage.WriteIn("reconnect", sessionId, playerid, step, type, result, timestamp);
    }

    public void Cheat(long sessionId, long playerid, int cheattype, string clientIp, DateTime timestamp)
    {
      storage.WriteIn("cheat", sessionId, playerid, cheattype, clientIp, timestamp);
    }

    public void ExceedingServerStepTime(long sessionId, int step, DateTime startTime, DateTime finishTime, int stepCount, int stepTimeMin, int stepTimeMax, int stepTimeAvg)
    {
      storage.WriteIn("exceedingserversteptime", sessionId, step, startTime, finishTime, stepCount, stepTimeMin, stepTimeMax, stepTimeAvg);
    }

    public void GSTraffic(long sessionId, int totalin, int totalout, float avgoutperstep, int maxoutperstep, int totalinreconnect, int totaloutreconnect, float avgoutreconnect, int maxoutreconnect, float avgcmdpersecond, int maxcmdpersecond)
    {
      storage.WriteIn("gstraffic", sessionId, totalin, totalout, avgoutperstep, maxoutperstep, totalinreconnect, totaloutreconnect, avgoutreconnect, maxoutreconnect, avgcmdpersecond, maxcmdpersecond);
    }

    #region Debug events

    public void ExceedingStepTime(long sessionId, long playerId, int typeId, int startStep, int finishStep, DateTime startTime, DateTime finishTime,
                              int stepCount, int stepTimeMin, int stepTimeMax, int stepTimeAvg, int worldRequestStep, int rpcPing, int transportPing)
    {
      storage.WriteIn("exceedingsteptime", sessionId, playerId, typeId, startStep, finishStep, startTime, finishTime, stepCount,
                      stepTimeMin, stepTimeMax, stepTimeAvg, worldRequestStep, rpcPing, transportPing);
    }

    public void ExceedingPingTime(long sessionId, long playerId, int typeId, DateTime startTime, DateTime finishTime,
                                  int pingLCount, int pingLTimeMin, int pingLTimeMax, int pingLTimeAvg, int pingHCount, int pingHTimeMin, int pingHTimeMax, int pingHTimeAvg)
    {
      storage.WriteIn("exceedingpingtime", sessionId, playerId, typeId, startTime, finishTime, pingLCount,
                      pingLTimeMin, pingLTimeMax, pingLTimeAvg, pingHCount, pingHTimeMin, pingHTimeMax, pingHTimeAvg);
    }

    public void LogOfflineEvent(long playerId, long persistentId, int code, long auxData, DateTime timestamp)
    {
      storage.WriteIn("offlineevent", playerId, persistentId, code, auxData, timestamp);
    }

    #endregion

    #region IDisposable members

    private bool disposed;

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }

    ~SessionEventWriter()
    {
      Dispose(false);
    }

    private void Dispose(bool disposing)
    {
      if (!disposed)
      {
        if (disposing)
        {
          storage.Dispose();
        }
        disposed = true;
      }
    }

    #endregion
  }
}
