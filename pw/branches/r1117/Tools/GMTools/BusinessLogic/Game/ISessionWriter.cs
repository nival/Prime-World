using System;
using System.Collections.Generic;

namespace BusinessLogic.Game
{
  /// <summary>
  /// Запись информации о начале и результатах сессии.
  /// </summary>
  public interface ISessionWriter : IDisposable
  {
    bool IsRunning { get; }

    /// <summary>
    /// Матчмейкинг отменен
    /// </summary>
    void MMakingCancelled(MMakingPlayerInfo mmplayer, DateTime timestamp);

    /// <summary>
    /// Матчмейкинг собрал сессию
    /// </summary>
    void MMakingSession(ulong persistentId, int status, int manoeuvresFaction, int basket, string map, DateTime timestamp, IEnumerable<MMakingPlayerInfo> mmplayers);

    /// <summary>
    /// Начало сессии
    /// </summary>
    void SessionStart(long persistentId, string map, string server, string serveraddress, string cluster, int sessionType, DateTime timestamp, IEnumerable<SessionStartPlayerInfo> players);

    /// <summary>
    /// Результаты сессии
    /// </summary>
    void SessionResult(long persistentId, int result, int sideWon, int surrendervote, DateTime timestamp, IEnumerable<SessionResultPlayerInfo> players);

    /// <summary>
    /// Клиентская информация о relay
    /// </summary>
    void SessionRelayInfo(long persistentId, long playerid, string relayAddress);
  }
}