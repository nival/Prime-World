using System;

namespace DAL.Entities
{

  /// <summary>
  /// Повторный сбор пати после игровой сессии.
  /// </summary>
  public class AfterParty
  {

    public virtual int Id { get; set; }

    public virtual DateTime Timestamp { get; set; }

    /// <summary>
    /// Id сессии из которой пришли участники (либо часть участников).
    /// </summary>
    public virtual long PersistentId { get; set; }

    /// <summary>
    /// Ушла ли пати в матчмейкинг.
    /// </summary>
    public virtual bool MMStarted { get; set; }

  }

}