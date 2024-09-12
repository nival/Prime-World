using System;

namespace DAL.Entities
{
  public class LeaverPointsLog
  {
    public virtual long Id { get; set; }

    public virtual Player Player { get; set; }
    public virtual long? PersistentId { get; set; }
    public virtual string Type { get; set; }

    public virtual int LeaverPointsChange { get; set; }
    public virtual int LeaverPointsTotal { get; set; }
    public virtual bool IsLeaverChanged { get; set; }
    public virtual bool IsLeaver { get; set; }
    public virtual bool IsBadBehaviour { get; set; }

    public virtual DateTime Timestamp { get; set; } 
  }
}