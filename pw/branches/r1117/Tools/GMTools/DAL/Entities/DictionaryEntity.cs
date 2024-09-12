namespace DAL.Entities
{
  /// <summary>
  /// Базовая сущность для справочников.
  /// </summary>
  public class DictionaryEntity
  {
    /// <summary>
    /// Идентификатор.
    /// </summary>
    public virtual int Id { get; set; }

    private string name;

    /// <summary>
    /// Название.
    /// </summary>
    public virtual string Name
    {
      get { return name; }
      set { name = Truncate(value); }
    }

    /// <summary>
    /// Признак того, что объект удален.
    /// </summary>
    public virtual bool Deleted { get; set; }

    /// <summary>
    /// Укорачивает строки до 255 символов (длина по умолчанию в NHibernate)
    /// </summary>
    /// <param name="value">Строка.</param>
    protected string Truncate(string value)
    {
      return Truncate(value, 255);
    }

    /// <summary>
    /// Укорачивает строки, длиннее заданной величины.
    /// </summary>
    /// <param name="value">Строка.</param>
    /// <param name="size">Длина.</param>
    protected string Truncate(string value, int size)
    {
      if (System.String.IsNullOrEmpty(value))
        return value;
      return value.Length <= size ? value : value.Remove(size);
    }

    #region Equality code

    public override bool Equals(object obj)
    {
      return base.Equals(obj);
    }

    public virtual bool Equals(DictionaryEntity other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return Equals(other.Name, Name) && other.Id == Id && other.Deleted.Equals(Deleted);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int result = (Name != null ? Name.GetHashCode() : 0);
        result = (result*397) ^ Id;
        result = (result*397) ^ Deleted.GetHashCode();
        return result;
      }
    }

    public static bool operator ==(DictionaryEntity left, DictionaryEntity right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(DictionaryEntity left, DictionaryEntity right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}