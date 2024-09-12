namespace DAL.Entities
{
  /// <summary>
  /// Тип передаваемой сессии.
  /// Соответствует namespace EGameType (\Src\PF_GameLogic\GameStatisticTypes.h)
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

    /// <summary>
    /// Матчмейкинг.
    /// </summary>
    PvX_Matchmaking = 2,

    /// <summary>
    /// Тренировка.
    /// </summary>
    PvX_Training = 3,

    /// <summary>
    /// Матчмейкинг через социальный сервер.
    /// </summary>
    Soc_Matchmaking,

    /// <summary>
    /// Тренировка через социальный сервер.
    /// </summary>
    Soc_Training
  }
}