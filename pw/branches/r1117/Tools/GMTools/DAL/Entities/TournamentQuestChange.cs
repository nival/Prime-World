using System;

namespace DAL.Entities
{

  /// <summary>
  /// Изменение состояния динамического квеста
  /// </summary>
  public class TournamentQuestChange
  {
    public virtual long Id { get; set; }

    public virtual Player Player { get; set; }

    /// <summary>
    /// Идентификатор динамического квеста
    /// </summary>
    public virtual int QuestIndex { get; set; }

    /// <summary>
    /// Название динамического квеста
    /// </summary>
    public virtual string QuestName { get; set; }

    /// <summary>
    /// Тип завершения квеста
    /// </summary>
    public virtual TournamentQuestResult CompleteType { get; set; }

    public virtual DateTime Timestamp { get; set; }

    /// <summary>
    /// Была ли выбрана альтернативная линейка (актуально только для ChangeType = QuestChangeType.Complete)
    /// </summary>
    public virtual bool AlternativeLine { get; set; }

    #region Equality code

    protected bool Equals( TournamentQuestChange other )
    {
      return Id == other.Id && Equals( Player, other.Player ) && QuestIndex == other.QuestIndex && string.Equals( QuestName, other.QuestName ) && CompleteType == other.CompleteType && Timestamp.Equals( other.Timestamp ) && AlternativeLine == other.AlternativeLine;
    }

    public override bool Equals( object obj )
    {
      if ( ReferenceEquals( null, obj ) ) return false;
      if ( ReferenceEquals( this, obj ) ) return true;
      if ( obj.GetType() != this.GetType() ) return false;
      return Equals( (TournamentQuestChange)obj );
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int hashCode = Id.GetHashCode();
        hashCode = ( hashCode * 397 ) ^ ( Player != null ? Player.GetHashCode() : 0 );
        hashCode = ( hashCode * 397 ) ^ QuestIndex;
        hashCode = ( hashCode * 397 ) ^ ( QuestName != null ? QuestName.GetHashCode() : 0 );
        hashCode = ( hashCode * 397 ) ^ (int)CompleteType;
        hashCode = ( hashCode * 397 ) ^ Timestamp.GetHashCode();
        return hashCode;
      }
    }

    #endregion
  }
}