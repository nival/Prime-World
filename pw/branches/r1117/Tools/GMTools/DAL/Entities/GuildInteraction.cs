using System;

namespace DAL.Entities
{

  /// <summary>
  /// Взаимодействие между кланами
  /// </summary>
  public class GuildInteraction
  {

    public virtual long Id { get; set; }

    /// <summary>
    /// Клан, инициирующий взаимодействие
    /// </summary>
    public virtual Guild Guild { get; set; }

    /// <summary>
    /// Объект воздействия
    /// </summary>
    public virtual Guild TargetGuild { get; set; }

    /// <summary>
    /// Тип взаимодействия
    /// </summary>
    public virtual GuildInteractionType Type { get; set; }

    /// <summary>
    /// Было ли взаимодействие результатом осады
    /// </summary>
    public virtual GuildSiege GuildSiege { get; set; }

    /// <summary>
    /// Время ожидания
    /// </summary>
    public virtual int WaitingTime { get; set; }


    public virtual DateTime Timestamp { get; set; } 

  }
}