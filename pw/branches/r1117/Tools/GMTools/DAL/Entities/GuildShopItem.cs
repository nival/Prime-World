namespace DAL.Entities
{

  /// <summary>
  /// Итем из кланового магазина
  /// </summary>
  public class GuildShopItem : DictionaryEntity
  {
    public virtual string DBID { get; set; }

    public virtual string Description { get; set; }

    #region Equality code

    protected virtual bool Equals(GuildShopItem other)
    {
      return base.Equals(other) && string.Equals(DBID, other.DBID) && string.Equals(Description, other.Description);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (obj.GetType() != this.GetType()) return false;
      return Equals((GuildShopItem) obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int hashCode = base.GetHashCode();
        hashCode = (hashCode * 397) ^ (DBID != null ? DBID.GetHashCode() : 0);
        hashCode = (hashCode * 397) ^ (Description != null ? Description.GetHashCode() : 0);
        return hashCode;
      }
    }

    public static bool operator ==(GuildShopItem left, GuildShopItem right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(GuildShopItem left, GuildShopItem right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}