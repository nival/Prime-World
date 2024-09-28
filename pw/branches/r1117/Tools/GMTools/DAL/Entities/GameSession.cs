using System;

namespace DAL.Entities
{
  /// <summary>
  /// Результаты игровой сессии.
  /// </summary>
  public class GameSession
  {
    /// <summary>
    /// Идентификатор.
    /// </summary>
    public virtual int Id { get; set; }

    /// <summary>
    /// Уникальный id, который формируется на пвх сервере
    /// </summary>
    public virtual long PersistentId { get; set; }

    /// <summary>
    /// Результат сессии
    /// </summary>
    public virtual SessionResult SessionResult { get; set; }

    /// <summary>
    /// Сервер.
    /// </summary>
    public virtual string Server { get; set; }

    /// <summary>
    /// IP адрес сервера.
    /// </summary>
    public virtual string ServerAddress { get; set; }

    /// <summary>
    /// Кластер.
    /// </summary>
    public virtual string Cluster { get; set; }

    /// <summary>
    /// Карта.
    /// </summary>
    public virtual string Map { get; set; }

    /// <summary>
    /// Тип запущенной сессии.
    /// </summary>
    public virtual SessionType SessionType { get; set; }

    /// <summary>
    /// Время начала сессии.
    /// </summary>
    public virtual DateTime StartTime { get; set; }

    /// <summary>
    /// Время окончания сессии.
    /// </summary>
    public virtual DateTime EndTime { get; set; }

    /// <summary>
    /// Победившая сторона. { None = -1, Team1 = 0, Team2 = 1 }
    /// </summary>
    public virtual int SideWon { get; set; }

    /// <summary>
    /// Количество проголосовавших за сдачу (0 - игра не закончилась сдачей)
    /// </summary>
    public virtual int SurrenderVote { get; set; }

    #region Equality code

    public virtual bool Equals(GameSession other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return Id == other.Id && PersistentId == other.PersistentId && SessionResult.Equals(other.SessionResult) &&
             String.Equals(Map, other.Map) && String.Equals(Server, other.Server) && String.Equals(ServerAddress, other.ServerAddress) && String.Equals(Cluster, other.Cluster) &&
             SessionType.Equals(other.SessionType) && StartTime.Equals(other.StartTime) && SideWon == other.SideWon &&
             EndTime.Equals(other.EndTime) && SurrenderVote == other.SurrenderVote;
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (!(obj is GameSession)) return false;
      return Equals((GameSession)obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int hashCode = Id;
        hashCode = (hashCode*397) ^ PersistentId.GetHashCode();
        hashCode = (hashCode*397) ^ SessionResult.GetHashCode();
        hashCode = (hashCode*397) ^ (Map != null ? Map.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ (Server != null ? Server.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ (ServerAddress != null ? ServerAddress.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ (Cluster != null ? Cluster.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ SessionType.GetHashCode();
        hashCode = (hashCode*397) ^ StartTime.GetHashCode();
        hashCode = (hashCode*397) ^ SideWon;
        hashCode = (hashCode*397) ^ EndTime.GetHashCode();
        hashCode = (hashCode*397) ^ SurrenderVote;
        return hashCode;
      }
    }

    public static bool operator ==(GameSession left, GameSession right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(GameSession left, GameSession right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}
