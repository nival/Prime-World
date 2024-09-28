using System;

namespace DAL.Entities
{
  /// <summary>
  /// Информация по персонажу каждого игрока.
  /// </summary>
  public class PlayerCharacter
  {
    /// <summary>
    /// Идентификатор.
    /// </summary>
    public virtual int Id { get; set; }

    /// <summary>
    /// Персонаж.
    /// </summary>
    public virtual Character Character { get; set; }

    /// <summary>
    /// Игрок.
    /// </summary>
    public virtual Player Player { get; set; }

    /// <summary>
    /// Заблокирован
    /// </summary>
    public virtual bool Locked { set; get; }

    /// <summary>
    /// Дата приобретения
    /// </summary>
    public virtual DateTime UnlockDate { set; get; }

    public override string ToString()
    {
      return string.Format("PlayerCharacter(Id={0},{1},{2})", Id, Player, Character);
    }

    #region Equality code

    public virtual bool Equals(PlayerCharacter other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return other.Id == Id && Equals(other.Character, Character) && Equals(other.Player, Player) && other.Locked.Equals(Locked) && other.UnlockDate.Equals(UnlockDate);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (!(obj is PlayerCharacter)) return false;
      return Equals((PlayerCharacter) obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int result = Id;
        result = (result*397) ^ (Character != null ? Character.GetHashCode() : 0);
        result = (result*397) ^ (Player != null ? Player.GetHashCode() : 0);
        result = (result*397) ^ Locked.GetHashCode();
        result = (result*397) ^ UnlockDate.GetHashCode();
        return result;
      }
    }

    public static bool operator ==(PlayerCharacter left, PlayerCharacter right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(PlayerCharacter left, PlayerCharacter right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}
