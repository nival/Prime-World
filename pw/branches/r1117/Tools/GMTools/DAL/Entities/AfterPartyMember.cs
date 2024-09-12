using System;

namespace DAL.Entities
{

  /// <summary>
  /// Участник повторно собранной пати.
  /// </summary>
  public class AfterPartyMember
  {

    public virtual int Id { get; set; }

    public virtual Player Player { get; set; }

    public virtual AfterParty AfterParty { get; set; }

    /// <summary>
    /// Id сессии из которой пришел игрок (если не был добавлен в пати в замке).
    /// </summary>
    public virtual long? PersistentId { get; set; }

    /// <summary>
    /// Игрок был кикнут из пати.
    /// </summary>
    public virtual bool Kicked { get; set; } 

    /// <summary>
    /// Игрок ливнул из пати.
    /// </summary>
    public virtual bool Leaved { get; set; }

    public virtual DateTime Timestamp { get; set; }

  }

}