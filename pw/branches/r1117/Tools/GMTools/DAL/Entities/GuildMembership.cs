using System;

namespace DAL.Entities
{
  /// <summary>
  /// Информация о вступлении/исключении игрока из гильдии
  /// </summary>
  public class GuildMembership
  {
    public virtual int Id { get; set; }
    /// <summary>
    /// Игрок
    /// </summary>
    public virtual Player Player { get; set; }
    /// <summary>
    /// Гильдия в которую вступает игрок
    /// </summary>
    public virtual Guild Guild { get; set; }
    /// <summary>
    /// Дата вступлений
    /// </summary>
    public virtual DateTime JoinDate { get; set; }
    /// <summary>
    /// Дата выхода
    /// </summary>
    public virtual DateTime? LeaveDate { get; set; }
    /// <summary>
    /// Признак того, что игрок был оттуда кикнут
    /// </summary>
    public virtual bool? Kicked { get; set; }

    public override string ToString()
    {
      return String.Format("GuildMembership(Id={0},Player={1},Guild={2})", Id, Player, Guild);
    }
  }
}