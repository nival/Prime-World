using System;

namespace DAL.Entities
{
  public class QuestEventsStagesLog
  {
    public virtual int Id { get; set; }
    public virtual int ToStageChange { get; set; }
    public virtual int Auid { get; set; }
    public virtual DateTime TimeStamp { get; set; } 
  }
}