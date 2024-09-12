namespace DAL.Entities
{
  /// <summary>
  /// Тип абилки.
  /// </summary>
  public class AbilityType : DictionaryEntity
  {
    #region Equality code

    public virtual bool Equals(AbilityType other)
    {
      return base.Equals(other);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as AbilityType);
    }

    public override int GetHashCode()
    {
      return base.GetHashCode();
    }

    public static bool operator ==(AbilityType left, AbilityType right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(AbilityType left, AbilityType right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}