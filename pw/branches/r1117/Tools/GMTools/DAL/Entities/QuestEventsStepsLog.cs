using System;

namespace DAL.Entities
{
  public class QuestEventsStepsLog
  {
    public virtual int Id { get; set; }
    public virtual int ToStepChange { get; set; }
    public virtual int Stage { get; set; }
    public virtual int Auid { get; set; }
    public virtual DateTime TimeStamp { get; set; }
  }
}