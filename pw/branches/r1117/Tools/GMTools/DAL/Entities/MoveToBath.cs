using System;

namespace DAL.Entities
{
  /// <summary>
  /// Перемещение героя в баню
  /// </summary>
  public class MoveToBath
  {
    /// <summary>
    /// Идентификатор
    /// </summary>
    public virtual int Id { get; set; }

    /// <summary>
    /// Герой конкретного игрока
    /// </summary>
    public virtual PlayerCharacter PlayerCharacter { get; set; }

    /// <summary>
    /// Потраченные ресурсы
    /// </summary>
    public virtual ResourceLog ResourceLog { get; set; }

    /// <summary>
    /// Количество минут
    /// </summary>
    public virtual int Minutes { get; set; }

    /// <summary>
    /// Дата анлока
    /// </summary>
    public virtual DateTime Timestamp { get; set; }

    #region Equality code

    public virtual bool Equals(MoveToBath other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return Id == other.Id && Equals(PlayerCharacter, other.PlayerCharacter) && Equals(ResourceLog, other.ResourceLog) && Minutes == other.Minutes && Timestamp.Equals(other.Timestamp);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (!(obj is MoveToBath)) return false;
      return Equals((MoveToBath)obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int hashCode = Id;
        hashCode = (hashCode*397) ^ (PlayerCharacter != null ? PlayerCharacter.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ (ResourceLog != null ? ResourceLog.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ Minutes;
        hashCode = (hashCode*397) ^ Timestamp.GetHashCode();
        return hashCode;
      }
    }

    public static bool operator ==(MoveToBath left, MoveToBath right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(MoveToBath left, MoveToBath right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}