using System;
using System.Collections.Generic;
using System.Linq;
using DAL.Entities;

namespace DAL.Repositories
{
  public interface IQuestEventsStagesRepository : IRepository<QuestEventsStagesLog>
  {
    List<QuestEventsStagesLog> GetQuestEventsStepsByAuid(int auid, DateTime startTime, DateTime endTime, int offset, int limit, out int rowsCount);
  }

  public class QuestEventsStagesRepository : Repository<QuestEventsStagesLog>, IQuestEventsStagesRepository
  {
    public List<QuestEventsStagesLog> GetQuestEventsStepsByAuid(int auid, DateTime startTime, DateTime endTime, int offset, int limit,
      out int rowsCount)
    {
      if (startTime >= endTime)
        throw new ArgumentException("DateFrom cannot be greater than DateTo", "datefrom");

      var gwEventLogQuery = Session.QueryOver<QuestEventsStagesLog>()
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