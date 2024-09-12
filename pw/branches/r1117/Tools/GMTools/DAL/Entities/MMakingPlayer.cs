using System;

namespace DAL.Entities
{
  /// <summary>
  /// Информация об матчмейкинге игрока
  /// </summary>
  public class MMakingPlayer
  {
    /// <summary>
    /// Идентификатор
    /// </summary>
    public virtual long Id { get; set; }

    /// <summary>
    /// Сессия матчмейкинга
    /// </summary>
    public virtual MMakingSession MMakingSession { get; set; }

    /// <summary>
    /// Герой игрока
    /// </summary>
    public virtual PlayerCharacter PlayerCharacter { get; set; }

    /// <summary>
    /// Пол игрока { Undefined = 0, Male = 1, Female = 2 }
    /// </summary>
    public virtual int Sex { get; set; }

    /// <summary>
    /// Фракция игрока { None = -1, Team1 = 0, Team2 = 1 }
    /// </summary>
    public virtual int Faction { get; set; }

    /// <summary>
    /// Рейтинг
    /// </summary>
    public virtual int Rating { get; set; }

    /// <summary>
    /// Рейтинг игрока
    /// </summary>
    public virtual int PlayerRating { get; set; }

    /// <summary>
    /// Форс
    /// </summary>
    public virtual float Force { get; set; }

    /// <summary>
    /// Номер группы
    /// </summary>
    public virtual int Party { get; set; }

    /// <summary>
    /// Время ожидания
    /// </summary>
    public virtual float WaitInterval { get; set; }

    /// <summary>
    /// Серия поражений
    /// </summary>
    public virtual int LoseStreak { get; set; }

    /// <summary>
    /// Уровень фейма игрока
    /// </summary>
    public virtual int FameLevel { get; set; }

    /// <summary>
    /// Тип игрока (в какую "корзину" матчмейкинга он попадает) { Undefined = -1, Newbie = 0, Normal = 1, Guard = 2 }
    /// </summary>
    public virtual int Basket { get; set; }

    /// <summary>
    /// Реакция { None = 0, Accept = 1, Cancel = 2, Slowpoke = 3, PreGameLobbyReady=4, PreGameLobbyNotReady=5 }
    /// </summary>
    public virtual int LobbyReaction { get; set; }

    /// <summary>
    /// Время реакции, пишется только для тамбура, во всех остальных случаях = 0
    /// </summary>
    public virtual float? LobbyReactionTime { get; set; }

    /// <summary>
    /// Время окончания матчмейкинга (успешного или нет)
    /// </summary>
    public virtual DateTime Timestamp { get; set; }
  }
}