using System;

namespace DAL.Entities
{
  /// <summary>
  /// Сессия матчмейкинга
  /// </summary>
  public class MMakingSession
  {
    /// <summary>
    /// Идентификатор
    /// </summary>
    public virtual long Id { get; set; }

    /// <summary>
    /// Уникальный id из сервера матчмейкинга
    /// </summary>
    public virtual long PersistentId { get; set; }

    /// <summary>
    /// Статус { None = 0, Launched = 1, Dismissed = 2 }
    /// </summary>
    public virtual int Status { get; set; }

    /// <summary>
    /// Фракция, для которой выполнялся маневр { None = -1, Team1 = 0, Team2 = 1 }
    /// </summary>
    public virtual int ManoeuvresFaction { get; set; }

    /// <summary>
    /// Тип сессии (из какой "корзины" матчмейкинга она собрана)
    /// { Undefined = -1, Newbie = 0, Normal = 1, Guard = 2 }
    /// </summary>
    public virtual int Basket { get; set; }

    /// <summary>
    /// Карта
    /// </summary>
    public virtual string Map { get; set; }

    /// <summary>
    /// Время создания сессии
    /// </summary>
    public virtual DateTime Timestamp { get; set; }

  }
}