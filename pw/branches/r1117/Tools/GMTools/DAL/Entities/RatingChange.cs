using System;

namespace DAL.Entities
{
  /// <summary>
  /// Изменение рейтинга
  /// </summary>
  public class RatingChange
  {
    /// <summary>
    /// Идентификатор
    /// </summary>
    public virtual int Id { get; set; }

    /// <summary>
    /// Тип рейтинга
    /// </summary>
    public virtual RatingType Type { get; set; }

    /// <summary>
    /// Игрок
    /// </summary>
    public virtual Player Player { get; set; }

    /// <summary>
    /// Уникальный id сессии, который формируется на пвх сервере
    /// </summary>
    public virtual long? PersistentId { get; set; }

    /// <summary>
    /// Герой (в том случае, если рейтинг имеет к нему отношение)
    /// </summary>
    public virtual Character Character { get; set; }

    /// <summary>
    /// Изменение рейтинга
    /// </summary>
    public virtual int Change { get; set; }

    /// <summary>
    /// Итоговое значение рейтинга
    /// </summary>
    public virtual int Total { get; set; }

    /// <summary>
    /// Итоговое значение рейтинга
    /// </summary>
    public virtual DateTime Timestamp { get; set; }

    #region Equality code

    public virtual bool Equals(RatingChange other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return Id == other.Id && Type.Equals(other.Type) && Equals(Player, other.Player) && PersistentId == other.PersistentId && Equals(Character, other.Character) && Change == other.Change && Total == other.Total && Timestamp.Equals(other.Timestamp);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (!(obj is RatingChange)) return false;
      return Equals((RatingChange) obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int hashCode = Id;
        hashCode = (hashCode*397) ^ Type.GetHashCode();
        hashCode = (hashCode*397) ^ (Player != null ? Player.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ PersistentId.GetHashCode();
        hashCode = (hashCode*397) ^ (Character != null ? Character.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ Change;
        hashCode = (hashCode*397) ^ Total;
        hashCode = (hashCode*397) ^ Timestamp.GetHashCode();
        return hashCode;
      }
    }

    public static bool operator ==(RatingChange left, RatingChange right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(RatingChange left, RatingChange right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}