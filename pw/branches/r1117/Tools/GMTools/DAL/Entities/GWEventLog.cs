using System;

namespace DAL.Entities
{
  public class GWEventLog
  {
    public virtual int Id { get; set; }
    public virtual string GWEventmid { get; set; }
    public virtual long GuildId { get; set; }
    public virtual int LastPoints { get; set; }
    public virtual int CurrentPoints { get; set; }
    public virtual DateTime TimeStamp { get; set; }
    public virtual int Auid { get; set; }
  }
}
