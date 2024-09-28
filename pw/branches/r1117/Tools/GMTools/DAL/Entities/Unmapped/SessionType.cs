namespace DAL.Entities
{
  /// <summary>
  /// Тип передаваемой сессии.
  /// Соответствует namespace EGameType (\Src\Game\PF\Server\Statistic\StatisticsServerTypes.h)
  /// </summary>
  public enum SessionType
  {
    /// <summary>
    /// Дефолтное значение, не должно появляться.
    /// </summary>
    None = 0,

    /// <summary>
    /// Олдскульное создание сессии.
    /// </summary>
    Dev_Custom = 1,

    // Не используются:
    // PvX_Matchmaking = 2,
    // PvX_Training = 3,

    /// <summary>
    /// ОБычный матчмейкинг.
    /// </summary>
    Soc_Matchmaking = 4,

    /// <summary>
    /// Тренировка.
    /// </summary>
    Soc_Training = 5,

    /// <summary>
    /// Туториал.
    /// </summary>
    Soc_Tutorial = 6,

    /// <summary>
    /// PvE сингл.
    /// </summary>
    Soc_Singleplayer = 7,

    /// <summary>
    /// PvE кооп.
    /// </summary>
    Soc_Coop = 8,

    /// <summary>
    /// Договорная игра.
    /// </summary>
    Soc_CustomGame = 9,

    /// <summary>
    /// Договорная игра с ботами
    /// </summary>
    Soc_CustomGameBots = 10
  }
}