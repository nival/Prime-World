using System;

namespace DAL.Entities
{
  /// <summary>
  /// Жалоба игрока
  /// </summary>
  public class Claim
  {
    public virtual int Id { get; set; }

    /// <summary>
    /// Игрок, отправивший жалобу
    /// </summary>
    public virtual Player FromPlayer { get; set; }

    /// <summary>
    /// Игрок, на которого пожаловались
    /// </summary>
    public virtual Player ToPlayer { get; set; }

    /// <summary>
    /// Откуда пришла жалоба (0 - замок, 1 - сессия)
    /// </summary>
    public virtual int Source { get; set; }

    /// <summary>
    /// Тип жалобы
    /// </summary>
    public virtual int Category { get; set; }

    /// <summary>
    /// Локаль
    /// </summary>
    public virtual string Locale { get; set; }

    /// <summary>
    /// Локаль
    /// </summary>
    public virtual string Muid { get; set; }

    /// <summary>
    /// Комментарий жалобы
    /// </summary>
    public virtual string Comment { get; set; }

    /// <summary>
    /// Лог чата
    /// </summary>
    public virtual string ChatLog { get; set; }

    public virtual DateTime Timestamp { get; set; }

    /// <summary>
    /// Id pvx сессии
    /// </summary>
    public virtual long PersistentId { get; set; }

    public virtual int Kills { get; set; }

    public virtual int Deaths { get; set; }

    public virtual int Assists { get; set; }

    public virtual int Points { get; set; }

    public virtual int Prime { get; set; }

    public virtual int Distance { get; set; }

    public virtual int Afks { get; set; }

    public virtual PlayerConnectionStatus ConnStatus { get; set; }

    /// <summary>
    /// GM действие, по которому обработана данная жалоба
    /// </summary>
    public virtual GMUserOperation GMUserOperation { get; set; }
  }
}