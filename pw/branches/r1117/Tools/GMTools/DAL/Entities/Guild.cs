using System;

namespace DAL.Entities
{
  /// <summary>
  /// Гильдия
  /// </summary>
  public class Guild
  {
    public virtual long Id { get; set; }
    /// <summary>
    /// Сокращение
    /// </summary>
    public virtual string ShortName { get; set; }
    /// <summary>
    /// Полное имя
    /// </summary>
    public virtual string FullName { get; set; }

    /// <summary>
    /// Создатель
    /// </summary>
    public virtual Player Creator { get; set; }
    /// <summary>
    /// Дата создания гильдии
    /// </summary>
    public virtual DateTime CreationDate { get; set; }
    /// <summary>
    /// Дата создания гильдии
    /// </summary>
    public virtual DateTime? DisbandingDate { get; set; }
    /// <summary>
    /// Траты за создание
    /// </summary>
    public virtual ResourceLog ResourceLog { get; set; }

    /// <summary>
    /// Количество игроков в клане
    /// </summary>
    public virtual int MembersCount { get; set; }

    public override string ToString()
    {
      return String.Format("Guild(Id={0},ShortName={1},FullName={2})", Id, ShortName, FullName);
    }
  }
}