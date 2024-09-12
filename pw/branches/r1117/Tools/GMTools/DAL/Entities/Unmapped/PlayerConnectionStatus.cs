namespace DAL.Entities
{
  /// <summary>
  /// Копия Peered::Status из C++ PeeredTypes.h
  /// </summary>
  public enum PlayerConnectionStatus
  {
    Connecting = 0,
    Ready = 1,
    Active = 2,
    Away = 3,
    DisconnectedByClient = 4,
    DisconnectedByServer = 5,
    ConnectionTimedOut = 6,
    DisconnectedByCheatAttempt = 7,
    DisconnectedByClientIntentionally = 8,
    ConnectionTimedOutOnReconnect = 9,
    DisconnectedByAsync = 10,
  }
}