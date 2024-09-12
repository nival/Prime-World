using System;

namespace DAL.Entities
{
  /// <summary>
  /// Результаты сессии по конкретному игроку.
  /// </summary>
  public class SessionToPlayer
  {
    /// <summary>
    /// Идентификатор.
    /// </summary>
    public virtual int Id { get; set; }

    /// <summary>
    /// Персонаж игрока.
    /// </summary>
    public virtual PlayerCharacter PlayerCharacter { get; set; }

    /// <summary>
    /// Игровая сессия.
    /// </summary>
    public virtual GameSession GameSession { get; set; }

    /// <summary>
    /// Клан игрока
    /// </summary>
    public virtual Guild Guild { get; set; }

    /// <summary>
    /// Достигнутый уровень.
    /// </summary>
    public virtual int FinalLevel { get; set; }

    /// <summary>
    /// Игрок не доиграл сессию
    /// </summary>
    public virtual bool Leaver { get; set; }

    /// <summary>
    /// За сколько минут достигнут максимальный уровень.
    /// </summary>
    public virtual int MaxLevelReached { get; set; }

    /// <summary>
    /// Фракция
    /// </summary>
    public virtual Faction Faction { get; set; }

    /// <summary>
    /// Набрано очков.
    /// </summary>
    public virtual int Score { get; set; }

    /// <summary>
    /// Убийства персонажей.
    /// </summary>
    public virtual int Kills { get; set; }

    /// <summary>
    /// Смерти.
    /// </summary>
    public virtual int Deaths { get; set; }

    /// <summary>
    /// Ассисты.
    /// </summary>
    public virtual int Assists { get; set; }

    /// <summary>
    /// Убито вражеских крипов.
    /// </summary>
    public virtual int EnemyCreepsKilled { get; set; }

    /// <summary>
    /// Убито нейтральных крипов.
    /// </summary>
    public virtual int NeutralCreepsKilled { get; set; }

    /// <summary>
    /// Адрес релея на который попал игрок
    /// </summary>
    public virtual string RelayAddress { get; set; }

    /// <summary>
    /// Время начала сессии (для партиционирования)
    /// </summary>
    public virtual DateTime? StartTime { get; set; }
  }
}
