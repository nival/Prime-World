using System;

namespace DAL.Entities
{
  /// <summary>
  /// Смена фракции (или первичный выбор)
  /// </summary>
  public class FactionChange
  {
    /// <summary>
    /// Идентификатор
    /// </summary>
    public virtual int Id { get; set; }

    /// <summary>
    /// Игрок
    /// </summary>
    public virtual Player Player { get; set; }

    /// <summary>
    /// Фракция до смены
    /// </summary>
    public virtual Faction OldFaction { get; set; }

    /// <summary>
    /// Фракция после смены
    /// </summary>
    public virtual Faction NewFaction { get; set; }

    /// <summary>
    /// Потраченные ресурсы
    /// </summary>
    public virtual ResourceLog ResourceLog { get; set; }

    /// <summary>
    /// Дата смены
    /// </summary>
    public virtual DateTime Timestamp { get; set; }

    #region Equality code

    public virtual bool Equals(FactionChange other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return other.Id == Id && Equals(other.Player, Player) && Equals(other.OldFaction, OldFaction) && Equals(other.NewFaction, NewFaction) && Equals(other.ResourceLog, ResourceLog) && other.Timestamp.Equals(Timestamp);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (obj.GetType() != typeof (FactionChange)) return false;
      return Equals((FactionChange) obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int result = Id;
        result = (result*397) ^ (Player != null ? Player.GetHashCode() : 0);
        result = (result*397) ^ OldFaction.GetHashCode();
        result = (result*397) ^ NewFaction.GetHashCode();
        result = (result*397) ^ (ResourceLog != null ? ResourceLog.GetHashCode() : 0);
        result = (result*397) ^ Timestamp.GetHashCode();
        return result;
      }
    }

    #endregion
  }
}