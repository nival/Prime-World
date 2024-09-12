using System;

namespace DAL.Entities
{

  /// <summary>
  /// Ежесуточный пересчет информации о клане
  /// </summary>
  public class GuildDailyStats
  {

    public virtual long Id { get; set; }

    /// <summary>
    /// Клан
    /// </summary>
    public virtual Guild Guild { get; set; }

    /// <summary>
    /// Рейтинг
    /// </summary>
    public virtual int Rating { get; set; }

    /// <summary>
    /// Общее количество клановой валюты
    /// </summary>
    public virtual int GuildPoints { get; set; }

    /// <summary>
    /// Заработано клановой валюты за день
    /// </summary>
    public virtual int GuildPointsToday { get; set; }

    /// <summary>
    /// Место в мире
    /// </summary>
    public virtual int Rank { get; set; }

    /// <summary>
    /// Количество вассалов
    /// </summary>
    public virtual int VassalsCount { get; set; }

    /// <summary>
    /// Приход очков с вассалов за сутки
    /// </summary>
    public virtual int VassalsPoints { get; set; }


    public virtual DateTime Timestamp { get; set; }

  }

}