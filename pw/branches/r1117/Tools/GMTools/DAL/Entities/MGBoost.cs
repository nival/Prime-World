namespace DAL.Entities
{
  /// <summary>
  /// Буст миниигры.
  /// </summary>
  public class MGBoost : DictionaryEntity
  {
    #region Equality code

    public virtual bool Equals(MGBoost other)
    {
      return base.Equals(other);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as MGBoost);
    }

    public override int GetHashCode()
    {
      return base.GetHashCode();
    }

    public static bool operator ==(MGBoost left, MGBoost right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(MGBoost left, MGBoost right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}