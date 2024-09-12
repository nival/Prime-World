
using System;

namespace DAL.Entities
{

  /// <summary>
  /// Информация об участнике осады клана
  /// </summary>
  public class GuildSiegeParticipant
  {

    public virtual long Id { get; set; }

    /// <summary>
    /// Осада
    /// </summary>
    public virtual GuildSiege GuildSiege { get; set; }

    /// <summary>
    /// Клан
    /// </summary>
    public virtual Guild Guild { get; set; }

    /// <summary>
    /// Рейтинг
    /// </summary>
    public virtual int Rating { get; set; }

    /// <summary>
    /// Очки осады
    /// </summary>
    public virtual int SiegePoints { get; set; }

    /// <summary>
    /// Цена вступления в осаду
    /// </summary>
    public virtual GuildPointsLog GuildPointsLog { get; set; }

    /// <summary>
    /// Время вступления в осаду
    /// </summary>
    public virtual DateTime StartTime { get; set; }

    /// <summary>
    /// Время выхода из осады
    /// </summary>
    public virtual DateTime EndTime { get; set; }

  }

}