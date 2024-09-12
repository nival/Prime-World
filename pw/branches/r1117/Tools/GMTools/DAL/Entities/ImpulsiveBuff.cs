namespace DAL.Entities
{
  /// <summary>
  /// Спонтанная покупка.
  /// </summary>
  public class ImpulsiveBuff : DictionaryEntity
  {
    private string dbid;

    /// <summary>
    /// DBID.
    /// </summary>
    public virtual string DBID
    {
      get { return dbid; }
      set { dbid = Truncate(value, 1024); }
    }

    #region Equality code

    public virtual bool Equals(ImpulsiveBuff other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return base.Equals(other) && Equals(other.dbid, dbid);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as ImpulsiveBuff);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        {
          return (base.GetHashCode() * 397) ^ (dbid != null ? dbid.GetHashCode() : 0);
        }
      }
    }

    public static bool operator ==(ImpulsiveBuff left, ImpulsiveBuff right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(ImpulsiveBuff left, ImpulsiveBuff right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}
