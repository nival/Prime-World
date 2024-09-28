using System;

namespace DAL.Entities
{

  public class GuildPointsLog
  {

    public virtual long Id { get; set; }

    /// <summary>
    /// Тип операции с клановыми ресурсами
    /// </summary>
    public virtual GuildPointsLogType Type { get; set; }

    public virtual Guild Guild { get; set; }

    public virtual Player Player { get; set; }

    // Изменение
    public virtual int GuildPointsChange { get; set; }
    public virtual int PlayerPointsChange { get; set; }

    // Всего
    public virtual int GuildPointsTotal { get; set; }
    public virtual int PlayerPointsTotal { get; set; }

    /// <summary>
    /// Persistent id сессии, если type = session
    /// </summary>
    public virtual long? PersistentId { get; set; }

    public virtual DateTime Timestamp { get; set; }
  }

}