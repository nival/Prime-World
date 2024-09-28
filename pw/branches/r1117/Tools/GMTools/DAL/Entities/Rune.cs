namespace DAL.Entities
{
  /// <summary>
  /// Руна Golden Lamp
  /// </summary>
  public class Rune : DictionaryEntity
  {

    public virtual int Percent { get; set; }

    #region Equality code

    public virtual bool Equals(Rune other)
    {
      return base.Equals(other) && Percent == other.Percent;
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (obj.GetType() != this.GetType()) return false;
      return Equals((Rune) obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        return (base.GetHashCode() * 397) ^ Percent;
      }
    }

    public static bool operator ==(Rune left, Rune right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(Rune left, Rune right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}