namespace DAL.Entities
{
  /// <summary>
  /// Тип существа.
  /// </summary>
  public class UnitType : DictionaryEntity
  {
    #region Equality code

    public virtual bool Equals(UnitType other)
    {
      return base.Equals(other);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as UnitType);
    }

    public override int GetHashCode()
    {
      return base.GetHashCode();
    }

    public static bool operator ==(UnitType left, UnitType right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(UnitType left, UnitType right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}