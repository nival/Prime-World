
using System;
using System.Collections.Generic;
using System.Linq;
using DAL.Entities;

namespace DAL.Repositories
{
  public interface IQuestEventsStepsRepository : IRepository<QuestEventsStepsLog>
  {
    List<QuestEventsStepsLog> GetQuestEventsStepsByAuidAndStage(int auid, int stage, DateTime startTime, DateTime endTime, int offset, int limit, out int rowsCount);
  }

  public class QuestEventsStepsRepository : Repository<QuestEventsStepsLog>, IQuestEventsStepsRepository
  {
    public List<QuestEventsStepsLog> GetQuestEventsStepsByAuidAndStage(int auid, int stage, DateTime startTime, DateTime endTime, int offset, int limit,
      out int rowsCount)
    {
      if (startTime >= endTime)
        throw new ArgumentException("DateFrom cannot be greater than DateTo", "datefrom");

      var gwEventLogQuery = Session.QueryOver<QuestEventsStepsLog>()
        .Where(e => e.Auid == auid && e.Stage == stage && e.TimeStamp >= startTime && e.TimeStamp <= endTime);

      rowsCount = gwEventLogQuery.RowCount();

      var gwEventLog = gwEventLogQuery
        .OrderBy(e => e.TimeStamp).Desc
        .Skip(offset).Take(limit)
        .List();

      return gwEventLog.ToList();
    }
  }
}