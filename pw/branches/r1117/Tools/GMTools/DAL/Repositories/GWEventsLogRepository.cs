using System;
using System.Collections.Generic;
using System.Linq;
using DAL.Entities;
using NHibernate;

namespace DAL.Repositories
{
  public interface IGWEventsLogRepository : IRepository<GWEventLog>
  {
    List<GWEventLog> GetGWEventLogByEventIdx(int eventIdx, DateTime startTime, DateTime endTime, int offset, int limit, out int rowsCount);
    List<GWEventLog> GetGWEventLogByGuild(long guildIdx, DateTime startTime, DateTime endTime, int offset, int limit, out int rowsCount);
    List<GWEventLog> GetGWEventLogByAuid(int auid, DateTime startTime, DateTime endTime, int offset, int limit, out int rowsCount);
  }

  public class GWEventsLogRepository : Repository<GWEventLog>, IGWEventsLogRepository
  {
    public List<GWEventLog> GetGWEventLogByEventIdx(int eventIdx, DateTime startTime, DateTime endTime, int offset, int limit, out int rowsCount)
    {
      if (startTime >= endTime)
        throw new ArgumentException("DateFrom cannot be greater than DateTo", "datefrom");

      var eventIdxS = eventIdx.ToString();
      var gwEventLogQuery = Session.QueryOver<GWEventLog>()
        .Where(e => e.GWEventmid == eventIdxS && e.TimeStamp >= startTime && e.TimeStamp <= endTime);

      rowsCount = gwEventLogQuery.RowCount();
      
      var gwEventLog = gwEventLogQuery
        .OrderBy(e => e.TimeStamp).Desc
        .Skip(offset).Take(limit)
        .List();

      return gwEventLog.ToList();
    }
    

    public List<GWEventLog> GetGWEventLogByGuild(long guildIdx, DateTime startTime, DateTime endTime, int offset, int limit, out int rowsCount)
    {
      if (startTime >= endTime)
        throw new ArgumentException("DateFrom cannot be greater than DateTo", "datefrom");

      var gwEventLogQuery = Session.QueryOver<GWEventLog>()
        .Where(e => e.GuildId == guildIdx && e.TimeStamp >= startTime && e.TimeStamp <= endTime);

      rowsCount = gwEventLogQuery.RowCount();

      var gwEventLog = gwEventLogQuery
        .OrderBy(e => e.TimeStamp).Desc
        .Skip(offset).Take(limit)
        .List();

      return gwEventLog.ToList();
    }

    public List<GWEventLog> GetGWEventLogByAuid(int auid, DateTime startTime, DateTime endTime, int offset, int limit, out int rowsCount)
    {
      if (startTime >= endTime)
        throw new ArgumentException("DateFrom cannot be greater than DateTo", "datefrom");

      var gwEventLogQuery = Session.QueryOver<GWEventLog>()
        .Where(e => e.Auid == auid && e.TimeStamp >= startTime && e.TimeStamp <= endTime);

      rowsCount = gwEventLogQuery.RowCount();

      var gwEventLog = gwEventLogQuery
        .OrderBy(e => e.TimeStamp).Desc
        .Skip(offset).Take(limit)
        .List();

      return gwEventLog.ToList();
    }
  }
}
