namespace DAL.Entities
{
  /// <summary>
  /// Покупаемый итем.
  /// </summary>
  public class Consumable : DictionaryEntity
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
    
    /// <summary>
    /// Стоимость.
    /// </summary>
    public virtual int NaftaCost { get; set; }

    #region Equality code

    public virtual bool Equals(Consumable other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return base.Equals(other) && Equals(other.dbid, dbid) && other.NaftaCost == NaftaCost;
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as Consumable);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int result = base.GetHashCode();
        result = (result*397) ^ (dbid != null ? dbid.GetHashCode() : 0);
        result = (result*397) ^ NaftaCost;
        return result;
      }
    }

    public static bool operator ==(Consumable left, Consumable right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(Consumable left, Consumable right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}