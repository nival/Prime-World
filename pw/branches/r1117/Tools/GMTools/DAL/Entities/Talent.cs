namespace DAL.Entities
{
  /// <summary>
  /// Талант.
  /// </summary>
  public class Talent : DictionaryEntity
  {
    private string description;
    private string dbid;
    private string talentId;
    /// <summary>
    /// Описание.
    /// </summary>
    public virtual string Description
    {
      set { description = Truncate(value, 1023); }
      get { return description; }
    }

    /// <summary>
    /// DBID.
    /// </summary>
    public virtual string DBID
    {
      get { return dbid; }
      set { dbid = Truncate(value, 1024); }
    }

    /// <summary>
    /// Строковый идентификатор (из которого формируется настоящий id)
    /// </summary>
    public virtual string TalentId
    {
      get { return talentId; }
      set { talentId = Truncate(value); }
    }

    /// <summary>
    /// Кулдаун.
    /// </summary>
    public virtual float Cooldown { set; get; }

    /// <summary>
    /// Уровень таланта (DBTypes.ETalentLevel + 1)
    /// </summary>
    public virtual int Tour { set; get; }

    /// <summary>
    /// Ценность таланта
    /// </summary>
    public virtual TalentRarity Rarity { set; get; }

    /// <summary>
    /// Стоимость
    /// </summary>
    public virtual float Budget { set; get; }

    /// <summary>
    /// Тип абилки.
    /// </summary>
    public virtual AbilityType AbilityType { set; get; }


    #region Equality code

    public virtual bool Equals(Talent other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return base.Equals(other) && Equals(other.description, description) && Equals(other.dbid, dbid) &&
             Equals(other.talentId, talentId) && other.Cooldown == Cooldown && other.Tour == Tour &&
             other.Rarity == Rarity && other.Budget == Budget && Equals(other.AbilityType, AbilityType);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as Talent);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int result = base.GetHashCode();
        result = (result * 397) ^ (description != null ? description.GetHashCode() : 0);
        result = (result * 397) ^ (dbid != null ? dbid.GetHashCode() : 0);
        result = (result * 397) ^ (talentId != null ? talentId.GetHashCode() : 0);
        result = (result * 397) ^ Cooldown.GetHashCode();
        result = (result * 397) ^ Tour;
        result = (result * 397) ^ Rarity.GetHashCode();
        result = (result * 397) ^ Budget.GetHashCode();
        result = (result * 397) ^ (AbilityType != null ? AbilityType.GetHashCode() : 0);
        return result;
      }
    }

    public static bool operator ==(Talent left, Talent right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(Talent left, Talent right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}
