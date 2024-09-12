using System;

namespace DAL.Entities
{
  /// <summary>
  /// Социальная сессия.
  /// </summary>
  public class SocialSession
  {
    /// <summary>
    /// Идентификатор.
    /// </summary>
    public virtual long Id { get; set; }

    /// <summary>
    /// Игрок.
    /// </summary>
    public virtual Player Player { get; set; }

    /// <summary>
    /// IP адрес игрока
    /// </summary>
    public virtual string PlayerIp { get; set; }

    /// <summary>
    /// Сервер.
    /// </summary>
    public virtual string Server { get; set; }

    /// <summary>
    /// Кластер.
    /// </summary>
    public virtual string Cluster { get; set; }

    /// <summary>
    /// Время начала сессии.
    /// </summary>
    public virtual DateTime StartTime { get; set; }

    /// <summary>
    /// Время окончания сессии.
    /// </summary>
    public virtual DateTime EndTime { get; set; }

  }
}