using System;
using DAL.Entities;
using log4net;

namespace DAL.Repositories
{
  public interface IRuneRollRepository : IRepository<RuneRoll>
  {
    //RuneRoll Create(long playerid, int runeid, long persistentid, DateTime timestamp);
  }

  public class RuneRollRepository : Repository<RuneRoll>, IRuneRollRepository
  {
//    private static ILog _log = LogManager.GetLogger(typeof(RuneRollRepository));
//
//    public RuneRoll Create(long playerid, int runeid, long persistentid, DateTime timestamp)
//    {
//      var rune = Session.Get<Rune>(runeid);
//      if (rune == null)
//      {
//        _log.ErrorFormat("Cannot create new RuneRoll object: Rune(id={0}) is not exists", runeid);
//        return null;
//      }
//      var player = Session.Get<Player>(playerid);
//      if (player == null)
//      {
//        _log.ErrorFormat("Cannot create new RuneRoll object: Player(id={0}) is not exists", playerid);
//        return null;
//      }
//
//      var runeroll = new RuneRoll { Player = player, Rune = rune, PersistentId = persistentid, Timestamp = timestamp};
//      Add(runeroll);
//
//      return runeroll;
//    }
  }
}