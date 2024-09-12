namespace DAL.Entities
{
  /// <summary>
  /// Существо.
  /// </summary>
  public class Creature : DictionaryEntity
  {
    #region Equality code

    public virtual bool Equals(Creature other)
    {
      return base.Equals(other);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as Creature);
    }

    public override int GetHashCode()
    {
      return base.GetHashCode();
    }

    public static bool operator ==(Creature left, Creature right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(Creature left, Creature right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}