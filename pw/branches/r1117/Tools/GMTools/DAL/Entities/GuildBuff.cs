namespace DAL.Entities
{

  /// <summary>
  /// Клановый баф
  /// </summary>
  public class GuildBuff : DictionaryEntity
  {
    public virtual string DBID { get; set; }

    #region Equality code

    protected bool Equals(GuildBuff other)
    {
      return base.Equals(other) && string.Equals(DBID, other.DBID);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (obj.GetType() != this.GetType()) return false;
      return Equals((GuildBuff) obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        return (base.GetHashCode() * 397) ^ (DBID != null ? DBID.GetHashCode() : 0);
      }
    }

    public static bool operator ==(GuildBuff left, GuildBuff right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(GuildBuff left, GuildBuff right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}