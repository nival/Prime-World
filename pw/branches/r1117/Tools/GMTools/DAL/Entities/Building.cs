namespace DAL.Entities
{
  /// <summary>
  /// Здание.
  /// </summary>
  public class Building : DictionaryEntity
  {
    private string description;

    /// <summary>
    /// Описание.
    /// </summary>
    public virtual string Description
    {
      set { description = Truncate(value, 1023); }
      get { return description; }
    }

    #region Equality code

    public virtual bool Equals(Building other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return base.Equals(other) && Equals(other.description, description);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as Building);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        {
          return (base.GetHashCode()*397) ^ (description != null ? description.GetHashCode() : 0);
        }
      }
    }

    public static bool operator ==(Building left, Building right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(Building left, Building right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}