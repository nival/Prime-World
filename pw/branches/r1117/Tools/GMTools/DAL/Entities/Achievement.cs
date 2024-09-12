namespace DAL.Entities
{
  /// <summary>
  /// Достижение.
  /// </summary>
  public class Achievement : DictionaryEntity
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

    public virtual bool Equals(Achievement other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return base.Equals(other) && Equals(other.dbid, dbid);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as Achievement);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        {
          return (base.GetHashCode()*397) ^ (dbid != null ? dbid.GetHashCode() : 0);
        }
      }
    }

    public static bool operator ==(Achievement left, Achievement right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(Achievement left, Achievement right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}