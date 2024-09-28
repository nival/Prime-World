using System;

namespace DAL.Entities
{
  /// <summary>
  /// Изменение состояния квеста
  /// </summary>
  public class QuestChange
  {
    /// <summary>
    /// Идентификатор
    /// </summary>
    public virtual long Id { get; set; }

    /// <summary>
    /// Игрок
    /// </summary>
    public virtual Player Player { get; set; }

    /// <summary>
    /// Потраченные ресурсы
    /// </summary>
    public virtual Quest Quest { get; set; }

    /// <summary>
    /// Потраченные ресурсы
    /// </summary>
    public virtual QuestChangeType ChangeType { get; set; }

    /// <summary>
    /// Дата события
    /// </summary>
    public virtual DateTime Timestamp { get; set; }

    #region Equality code

    public virtual bool Equals(QuestChange other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return other.Id == Id && Equals(other.Player, Player) && Equals(other.Quest, Quest) && Equals(other.ChangeType, ChangeType) && other.Timestamp.Equals(Timestamp);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (obj.GetType() != typeof (QuestChange)) return false;
      return Equals((QuestChange) obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int result = Id.GetHashCode();
        result = (result*397) ^ (Player != null ? Player.GetHashCode() : 0);
        result = (result*397) ^ (Quest != null ? Quest.GetHashCode() : 0);
        result = (result*397) ^ ChangeType.GetHashCode();
        result = (result*397) ^ Timestamp.GetHashCode();
        return result;
      }
    }

    #endregion
  }
}