namespace DAL.Entities
{
  public class CastleBuilding : DictionaryEntity
  {
    /// <summary>
    /// Описание.
    /// </summary>
    public virtual string Description { get; set; }

    /// <summary>
    /// Максимальный уровень здания.
    /// </summary>
    public virtual int MaxLevel { get; set; }

    #region Equality code

    protected virtual bool Equals(CastleBuilding other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return base.Equals(other) && string.Equals(Description, other.Description) && MaxLevel == other.MaxLevel;
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as CastleBuilding);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int hashCode = base.GetHashCode();
        hashCode = (hashCode*397) ^ (Description != null ? Description.GetHashCode() : 0);
        hashCode = (hashCode*397) ^ MaxLevel;
        return hashCode;
      }
    }

    public static bool operator ==(CastleBuilding left, CastleBuilding right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(CastleBuilding left, CastleBuilding right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}