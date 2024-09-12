using System;

namespace BusinessLogic.Game
{
  public interface ISessionEventWriter : IDisposable
  {
    bool IsRunning { get; }

    void TalentUsed(long sessionId, int step, float x, float y, long playerid, int talentId);
    void TalentSwitchedOff(long sessionId, int step, float x, float y, long playerid, int talentId);
    void TalentUnlocked(long sessionId, int step, float x, float y, long playerid, int talentId, int nafta);
    void ImpulsiveBuffUsed(long sessionId, int step, float x, float y, long playerid, int impulsiveBuffId);
    void ImpulsiveBuffSuggested(long sessionId, int step, float x, float y, long playerid, int impulsiveBuffId);
    void CheatUsed(long sessionId, int step, float x, float y, long playerid, string command);
    void TimeSlice(long sessionId, int step, float x, float y, long playerid, int slice, int level, int totalNafta, int salaryNafta);
    void Kill(long sessionId, int step, float x, float y, long playerid, long victimId, int victimCreatureId);
    void Death(long sessionId, int step, float x, float y, long playerid, long killerId, int killerCreatureId);
    void Assist(long sessionId, int step, float x, float y, long playerid, long victimId, long killerId, int killerCreatureId);
    void LevelUp(long sessionId, int step, float x, float y, long playerid, int level);
    void ConsumableBought(long sessionId, int step, float x, float y, long playerid, int consumableId, int nafta);
    void ConsumableUsed(long sessionId, int step, float x, float y, long playerid, int consumableId);
    void Achievement(long sessionId, int step, float x, float y, long playerid, int achievementId);
    void Ressurection(long sessionId, int step, float x, float y, long playerid);
    void BuildingDestroyed(long sessionId, int step, float x, float y, long playerid, int buildingId, long destroyerId, int destroyerCreatureId);
    void Flag(long sessionId, int step, float x, float y, long playerid, bool raised, int faction, int road, int segment, long activatorId, int activatorCreatureId);
    void NaftaIncomeFromHero(long sessionId, int step, float x, float y, long playerid, int naftaForKill, int naftaSpecForKill, int teamNaftaForKill);
    void NaftaIncomeFromCreature(long sessionId, int step, float x, float y, long playerid, int naftaForKill, int naftaSpecForKill, int teamNaftaForKill);
    void NaftaIncomeFromBuilding(long sessionId, int step, float x, float y, long playerid, int naftaForKill, int naftaSpecForKill, int teamNaftaForKill);
    void NaftaIncomeFromTalent(long sessionId, int step, float x, float y, long playerid, int nafta);
    void NaftaIncomeFromImpulsiveBuff(long sessionId, int step, float x, float y, long playerid, int nafta);
    void NaftaIncomeFromMinigame(long sessionId, int step, float x, float y, long playerid, int nafta);
    void MG2Started(long sessionId, int step, float x, float y, long playerid);
    void MG2Exit(long sessionId, int step, float x, float y, long playerid);
    void MG2LevelStarted(long sessionId, int step, float x, float y, long playerid, int level, int paint);
    void MG2LevelWon(long sessionId, int step, float x, float y, long playerid, int level, int paint);
    void MG2LevelFailed(long sessionId, int step, float x, float y, long playerid, int level, int paint);
    void MG2BallsChanged(long sessionId, int step, float x, float y, long playerid);
    void MG2BoostUsage(long sessionId, int step, float x, float y, long playerid, int boostId);
    void Damage(long sessionId, int step, float x, float y, long playerid, bool dealt, int opponentId, int unitType, int talentId, float physicalDamage, float magicalDamage, float pureDamage);
    void DebugVar(long sessionId, int step, float x, float y, long playerid, string name, string value, DateTime timestamp);
    void ScriptEvent(long sessionId, int step, long playerId, string strParam1, string strParam2,
                     int intParam1, int intParam2, int intParam3, int intParam4, int intParam5);

    void Disconnect(long sessionId, long playerid, int reason, DateTime timestamp);
    void Reconnect(long sessionId, long playerid, int step, string type, string result, DateTime timestamp);
    void Cheat(long sessionId, long playerid, int cheattype, string clientIp, DateTime timestamp);
    void ExceedingServerStepTime(long sessionId, int step, DateTime startTime, DateTime finishTime, int stepCount, int stepTimeMin, int stepTimeMax, int stepTimeAvg);
    void GSTraffic(long sessionId, int totalin, int totalout, float avgoutperstep, int maxoutperstep, int totalinreconnect,
                   int totaloutreconnect, float avgoutreconnect, int maxoutreconnect, float avgcmdpersecond, int maxcmdpersecond);

    // debug events
    void ExceedingStepTime(long sessionId, long playerId, int typeId, int startStep, int finishStep, DateTime startTime, DateTime finishTime,
                           int stepCount, int stepTimeMin, int stepTimeMax, int stepTimeAvg, int worldRequestStep, int rpcPing, int transportPing);
    void ExceedingPingTime(long sessionId, long playerId, int typeId, DateTime startTime, DateTime finishTime,
                           int pingLCount, int pingLTimeMin, int pingLTimeMax, int pingLTimeAvg,
                           int pingHCount, int pingHTimeMin, int pingHTimeMax, int pingHTimeAvg);
    void LogOfflineEvent(long playerId, long persistentId, int code, long auxData, DateTime timestamp);
  }
}