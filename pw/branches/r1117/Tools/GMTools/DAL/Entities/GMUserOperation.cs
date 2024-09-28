using System;

namespace DAL.Entities
{
  /// <summary>
  /// GM операции с пользователями (баны/мьюты)
  /// </summary>
  public class GMUserOperation
  {
    public virtual int Id { get; set; }

    public virtual GMUserOperationType Type { get; set; }

    public virtual Player Player { get; set; }

    public virtual int Minutes { get; set; }
    
    public virtual int? Points { get; set; }

    public virtual string Reason { get; set; }

    public virtual string GMLogin { get; set; }

    public virtual DateTime Timestamp { get; set; }
  }
}