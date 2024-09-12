namespace DAL.Entities
{
  /// <summary>
  /// Информация о таланте, с которым пошли в сессию
  /// </summary>
  public class TalentJoinSession
  {
    public virtual long Id { get; set; }

    /// <summary>
    /// Игрок
    /// </summary>
    public virtual Player Player { get; set; }

    /// <summary>
    /// Герой
    /// </summary>
    public virtual Character Character { get; set; }

    /// <summary>
    /// Уникальный id сессии, который формируется на пвх сервере
    /// </summary>
    public virtual long PersistentId { get; set; }

    /// <summary>
    /// Талант
    /// </summary>
    public virtual Talent Talent { get; set; }
  }
}