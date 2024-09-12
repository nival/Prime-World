using System;

namespace DAL.Entities
{
  /// <summary>
  /// Общая структура для хранения GM операций
  /// </summary>
  public class GMOperation
  {
    public virtual int Id { get; set; }

    /*
     <property column="DataProviderConst" name="DataProvider"  
   type="EnumStringType`1[[My.Namespace.DataProvider, My.Namespace]]">  
     */
    public virtual GMOperationType Type { get; set; }

    public virtual Player Player { get; set; }

    public virtual string Data { get; set; }

    public virtual string GMLogin { get; set; }

    public virtual DateTime Timestamp { get; set; }
  }
}