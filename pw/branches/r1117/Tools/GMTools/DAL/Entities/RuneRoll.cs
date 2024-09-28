using System;

namespace DAL.Entities
{
  /// <summary>
  /// Ролл руны из сессии
  /// </summary>
  public class RuneRoll
  {
    public virtual int Id { get; set; }

    /// <summary>
    /// Игрок
    /// </summary>
    public virtual Player Player { get; set; }

    /// <summary>
    /// Уникальный id сессии, который формируется на пвх сервере
    /// </summary>
    public virtual long PersistentId { get; set; }

    /// <summary>
    /// Полученная руна
    /// </summary>
    public virtual Rune Rune { get; set; }

    /// <summary>
    /// Дата события
    /// </summary>
    public virtual DateTime Timestamp { get; set; }

    /// <summary>
    /// Рун было
    /// </summary>
    public virtual int Runescountold { get; set; }

    /// <summary>
    /// Рун стало
    /// </summary>
    public virtual int Runescountnew { get; set; }
  }
}