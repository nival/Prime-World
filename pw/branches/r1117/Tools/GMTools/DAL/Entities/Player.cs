using System;

namespace DAL.Entities
{
  /// <summary>
  /// Игрокъ.
  /// </summary>
  public class Player
  {
    /// <summary>
    /// Идѣнтификаторъ
    /// </summary>
    public virtual long Id { get; set; }

    /// <summary>
    /// Никнейм игрока
    /// </summary>
    public virtual string Nickname { get; set; }

    /// <summary>
    /// Пол игрока. { Undefined = 0, Male = 1, Female = 2 }
    /// </summary>
    public virtual int Sex { get; set; }

    /// <summary>
    /// Фракция игрока
    /// </summary>
    public virtual Faction Faction { get; set; }

    /// <summary>
    /// Гильдия игрока
    /// </summary>
    public virtual Guild Guild { get; set; }

    /// <summary>
    /// Надежность
    /// </summary>
    public virtual int Reliability { get; set; }

    /// <summary>
    /// Признак того, что игрок является сотрудником Nival.
    /// </summary>
    public virtual bool Nival { get; set; }

    /// <summary>
    /// Локаль игрока (указывает на принадлежность к стране)
    /// </summary>
    public virtual string Locale { get; set; }

    /// <summary>
    /// Становился ливером.
    /// </summary>
    public virtual int? LeaverCount { get; set; }

    /// <summary>
    /// Становился ливером по наказанию ГМом.
    /// </summary>
    public virtual int? LeaverGMCount { get; set; }

    /// <summary>
    /// Количество очков ливера.
    /// </summary>
    public virtual int LeaverPoints { get; set; }

    /// <summary>
    /// Является ли "дезертиром" в данный момент.
    /// </summary>
    public virtual bool IsLeaver { get; set; }


    public override string ToString()
    {
      return String.Format("Player(Id={0},Nickname={1})", Id, Nickname);
    }

    #region Equality code

    public virtual bool Equals(Player other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return Id == other.Id && string.Equals(Nickname, other.Nickname) && Sex == other.Sex &&
             Faction.Equals(other.Faction) && Equals(Guild, other.Guild) && Nival.Equals(other.Nival) &&
             Reliability == other.Reliability && string.Equals(Locale, other.Locale) &&
             LeaverCount == other.LeaverCount && LeaverGMCount == other.LeaverGMCount &&
             LeaverPoints == other.LeaverPoints && IsLeaver == other.IsLeaver;
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (!(obj is Player)) return false;
      return Equals((Player) obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int hashCode = Id.GetHashCode();
        hashCode = (hashCode*397) ^ (Nickname != null ? Nickname.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ Sex;
        hashCode = (hashCode*397) ^ Faction.GetHashCode();
        hashCode = (hashCode*397) ^ (Guild != null ? Guild.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ Nival.GetHashCode();
        hashCode = (hashCode*397) ^ Reliability;
        hashCode = (hashCode*397) ^ (Locale != null ? Locale.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ LeaverCount ?? 0;
        hashCode = (hashCode*397) ^ LeaverGMCount ?? 0;
        hashCode = (hashCode*397) ^ LeaverPoints;
        hashCode = (hashCode*397) ^ IsLeaver.GetHashCode();
        return hashCode;
      }
    }

    public static bool operator ==(Player left, Player right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(Player left, Player right)
    {
      return !Equals(left, right);
    }

    #endregion

    public const string DefaultLocale = "RU";
  }
}
