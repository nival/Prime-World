using System;

namespace DAL.Entities
{
  /// <summary>
  /// Операции с талантами
  /// </summary>
  public class TalentLog
  {
    public virtual long Id { get; set; }

    /// <summary>
    /// Тип операции
    /// </summary>
    public virtual string Operation { get; set; }
    
    /// <summary>
    /// Дополнительные данные по операции
    /// </summary>
    public virtual string Data { get; set; }

    /// <summary>
    /// Игрок
    /// </summary>
    public virtual Player Player { get; set; }

    /// <summary>
    /// Талант
    /// </summary>
    public virtual Talent Talent { get; set; }

    /// <summary>
    /// Инстанс таланта
    /// </summary>
    public virtual long TalentInstanceId { get; set; }

    /// <summary>
    /// Герой, к которому привязан талант
    /// </summary>
    public virtual Character Character { get; set; }
    
    /// <summary>
    /// Persistent id сессии, если это получение таланта из сессии
    /// </summary>
    public virtual long? PersistentId { get; set; }

    /// <summary>
    /// Таймстамп
    /// </summary>
    public virtual DateTime Timestamp { get; set; }
  }
}