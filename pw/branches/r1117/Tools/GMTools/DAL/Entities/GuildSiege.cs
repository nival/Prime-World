using System;

namespace DAL.Entities
{

  /// <summary>
  /// Информация о совершенной осаде клана
  /// </summary>
  public class GuildSiege
  {

    public virtual long Id { get; set; }

    /// <summary>
    /// Напавший клан
    /// </summary>
    public virtual Guild Guild { get; set; }

    /// <summary>
    /// Рейтинг напавшего клана на момент осады
    /// </summary>
    public virtual int Rating { get; set; }

    /// <summary>
    /// Осаждаемый клан
    /// </summary>
    public virtual Guild TargetGuild { get; set; }

    /// <summary>
    /// Рейтинг осаждаемого клана на момент осады
    /// </summary>
    public virtual int TargetRating { get; set; }

    /// <summary>
    /// Сюзерен осаждаемого клана
    /// </summary>
    public virtual Guild TargetSuzerainGuild { get; set; }

    /// <summary>
    /// Рейтинг сюзерена осаждаемого клана на момент осады
    /// </summary>
    public virtual int? TargetSuzerainRating { get; set; }

    /// <summary>
    /// Время начала
    /// </summary>
    public virtual DateTime StartTime { get; set; }
    
    /// <summary>
    /// Время окончания
    /// </summary>
    public virtual DateTime EndTime { get; set; }

    /// <summary>
    /// Победитель
    /// </summary>
    public virtual Guild Winner { get; set; }

    /// <summary>
    /// Стоимость операции
    /// </summary>
    public virtual GuildPointsLog GuildPointsLog { get; set; }

  }

}