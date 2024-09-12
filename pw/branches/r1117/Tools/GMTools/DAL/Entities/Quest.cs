namespace DAL.Entities
{
  public class Quest : DictionaryEntity
  {
    /// <summary>
    /// Строковый идентификатор (из которого формируется настоящий id)
    /// </summary>
    public virtual string QuestId { get; set; }

    #region Equality code

    public virtual bool Equals(Quest other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return base.Equals(other) && Equals(other.QuestId, QuestId);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as Quest);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        return (base.GetHashCode()*397) ^ (QuestId != null ? QuestId.GetHashCode() : 0);
      }
    }

    public static bool operator ==(Quest left, Quest right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(Quest left, Quest right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}