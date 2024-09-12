using System;
using System.Collections.Generic;
using DAL.Entities;
using NHibernate.Criterion;
using log4net;

namespace DAL.Repositories
{
  public interface ITalentLogRepository : IRepository<TalentLog>
  {
    TalentLog Create(string operation, string data, long playerid, int talentid, long talentinstanceid, int? characterid, long? persistentid, DateTime timestamp);
    IList<TalentLog> GetByParametersPaged(long playerid, DateTime datefrom, DateTime dateto, int offset, int limit, out int rows);
  }

  public class TalentLogRepository: Repository<TalentLog>, ITalentLogRepository
  {
    private static ILog _log = LogManager.GetLogger(typeof(TalentLogRepository));

    public TalentLog Create(string operation, string data, long playerid, int talentid, long talentinstanceid, int? characterid, long? persistentid, DateTime timestamp)
    {
      if (String.IsNullOrEmpty(operation)) throw new ArgumentNullException("operation");

      var talent = Session.Get<Talent>(talentid);
      if (talent == null)
      {
        _log.ErrorFormat("Cannot create new TalentLog object: Talent(id={0}) is not exists", talentid);
        return null;
      }
      var player = Session.Get<Player>(playerid);
      if (player == null)
      {
        _log.ErrorFormat("Cannot create new TalentLog object: Player(id={0}) is not exists", playerid);
        return null;
      }
      Character character = null;
      if (characterid.HasValue)
      {
        character = Session.Get<Character>(characterid.Value);
        if (character == null)
        {
          _log.ErrorFormat("Cannot create new TalentLog object: Character(id={0}) is not exists", characterid.Value);
          return null;
        }
      }

      var talentlog = new TalentLog
                        {
                          Operation = operation,
                          Data = data,
                          Player = player,
                          Talent = talent,
                          TalentInstanceId = talentinstanceid,
                          Character = character,
                          PersistentId = persistentid,
                          Timestamp = timestamp
                        };
      Add(talentlog);

      return talentlog;
    }

    public IList<TalentLog> GetByParametersPaged(long playerid, DateTime datefrom, DateTime dateto, int offset, int limit, out int rows)
    {
      if (datefrom >= dateto)
        throw new ArgumentException("DateFrom cannot be greater than DateTo", "datefrom");

      var query = Session.QueryOver<TalentLog>()
        .Where(r => r.Player.Id == playerid && r.Timestamp >= datefrom && r.Timestamp <= dateto);

      rows = query.RowCount();

      return query.OrderBy(r => r.Timestamp).Desc
        .Skip(offset).Take(limit)
        .List();
    }
  }
}