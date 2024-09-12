namespace DAL.Entities
{
  /// <summary>
  /// Персонаж.
  /// </summary>
  public class Character : DictionaryEntity
  {
    private string dbid;
    private string description;

    /// <summary>
    /// DBID.
    /// </summary>
    public virtual string DBID
    {
      get { return dbid; }
      set { dbid = Truncate(value, 1024); }
    }

    /// <summary>
    /// Описание.
    /// </summary>
    public virtual string Description
    {
      get { return description; }
      set { description = Truncate(value); }
    }

    /// <summary>
    /// Пол героя. Соответствует enum EGender { Male = 0, Female = 1 }
    /// </summary>
    public virtual int Gender { get; set; }

    public override string ToString()
    {
      return string.Format("Character(Id={0},Name={1})", Id, Name);
    }

    #region Equality code

    public virtual bool Equals(Character other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return base.Equals(other) && Equals(other.DBID, DBID) && Equals(other.Description, Description) && other.Gender == Gender;
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      return Equals(obj as Character);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int result = base.GetHashCode();
        result = (result*397) ^ (DBID != null ? DBID.GetHashCode() : 0);
        result = (result*397) ^ (Description != null ? Description.GetHashCode() : 0);
        result = (result*397) ^ Gender;
        return result;
      }
    }

    public static bool operator ==(Character left, Character right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(Character left, Character right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}
