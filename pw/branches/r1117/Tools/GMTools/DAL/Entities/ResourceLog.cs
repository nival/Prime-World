using System;
using System.Collections.Generic;
using System.Linq;

namespace DAL.Entities
{
  /// <summary>
  /// Информация по тратам ресурсов
  /// </summary>
  public class ResourceLog
  {
    public virtual long Id { get; set; }
    /// <summary>
    /// Источник ресурсов
    /// </summary>
    public virtual string Source { get; set; }
    /// <summary>
    /// Название здания-источника ресурсов
    /// </summary>
    public virtual string BuildingName { get; set; }
    /// <summary>
    /// Persistent id сессии, если источник ресурсов - session
    /// </summary>
    public virtual long? PersistentId { get; set; }
    /// <summary>
    /// Доход (true) или расход (false)
    /// </summary>
    public virtual bool Gain { get; set; }
    /// <summary>
    /// Игрок
    /// </summary>
    public virtual Player Player { get; set; }

    /// <summary>
    /// Золото
    /// </summary>
    public virtual int GoldChange { get; set; }
    /// <summary>
    /// Серебро
    /// </summary>
    public virtual int SilverChange { get; set; }
    /// <summary>
    /// Кристаллы прайма
    /// </summary>
    public virtual int PerlChange { get; set; }
    /// <summary>
    /// Красные кристаллы прайма
    /// </summary>
    public virtual int? RedPerlChange { get; set; }
    /// <summary>
    /// Население
    /// </summary>
    public virtual int PopulationChange { get; set; }
    /// <summary>
    /// Дерево/Шелк
    /// </summary>
    public virtual int Resource1Change { get; set; }
    /// <summary>
    /// Руда/Каучук
    /// </summary>
    public virtual int Resource2Change { get; set; }
    /// <summary>
    /// Еда
    /// </summary>
    public virtual int Resource3Change { get; set; }
    /// <summary>
    /// Shard
    /// </summary>
    public virtual int? ShardChange { get; set; }
    /// <summary>
    /// CurrencyChange
    /// </summary>
    
    public virtual string CurrencyChange { get; set; } //it is currencydata(old impl) and currency name(new impl)

    public virtual string CurrencyName
    {
        get { return CurrencyChange; }
        set { CurrencyChange = value; }
    }

    public virtual int? CurrencyChangeValue { get; set; }


    /// <summary>
    /// Всего золота
    /// </summary>
    public virtual int GoldTotal { get; set; }
    /// <summary>
    /// Всего серебра
    /// </summary>
    public virtual int SilverTotal { get; set; }
    /// <summary>
    /// Всего кристаллов прайма
    /// </summary>
    public virtual int PerlTotal { get; set; }
    /// <summary>
    /// Всего красных кристаллов прайма
    /// </summary>
    public virtual int? RedPerlTotal { get; set; }
    /// <summary>
    /// Всего населения
    /// </summary>
    public virtual int PopulationTotal { get; set; }
    /// <summary>
    /// Всего дерева/шелка
    /// </summary>
    public virtual int Resource1Total { get; set; }
    /// <summary>
    /// Всего руды/каучука
    /// </summary>
    public virtual int Resource2Total { get; set; }
    /// <summary>
    /// Всего еды
    /// </summary>
    public virtual int Resource3Total { get; set; }
    /// <summary>
    /// Shard total
    /// </summary>
    public virtual int? ShardTotal { get; set; }
    /// <summary>
    /// CurrencyTotal
    /// </summary>
    public virtual string CurrencyTotal { get; set; } //it is currencydata(old impl) and null(new impl)
    public virtual int? CurrencyTotalValue { get; set; }

    /// <summary>
    /// Время события
    /// </summary>
    public virtual DateTime Timestamp { get; set; }

    public override string ToString()
    {
      return string.Format("ResourceLog(Id={0},Source={1},BuildingName={2},Gain={3},{4},GoldChange={5},SilverChange={6},PerlChange={7},RedPerlChange={8},PopulationChange={9},Resource1Change={10},Resource2Change={11},Resource3Change={12},ShardChange={22},CurrencyChange={24},GoldTotal={13},SilverTotal={14},PerlTotal={15},RedPerlTotal={16},PopulationTotal={17},Resource1Total={18},Resource2Total={19},Resource3Total={20},ShardTotal={23},CurrencyTotal={26}:{25},Timestamp={21})",
                           Id, Source, BuildingName, Gain, Player, GoldChange, SilverChange, PerlChange, RedPerlChange, PopulationChange, Resource1Change, Resource2Change, Resource3Change, GoldTotal, SilverTotal, PerlTotal, RedPerlTotal, PopulationTotal, Resource1Total, Resource2Total, Resource3Total, Timestamp, ShardChange, ShardTotal, CurrencyChangeValue, CurrencyTotalValue, CurrencyName);
    }

    public static string ConvertCurrency(Dictionary<string, int> currency)
    {
      return ConvertCurrency(currency, true);
    }

    public static string ConvertCurrency(Dictionary<string, int> currency, bool gain)
    {
      if (currency == null)
        return null;
      return string.Join(",", currency.Select(c => string.Format("[{0}: {1}]", c.Key, gain ? c.Value : -c.Value)).ToArray());
    }

    #region Equality code

    public virtual bool Equals(ResourceLog other)
    {
      if (ReferenceEquals(null, other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return other.Id == Id && Equals(other.Source, Source) && Equals(other.BuildingName, BuildingName) && other.PersistentId == PersistentId && other.Gain.Equals(Gain) && Equals(other.Player, Player) &&
             other.GoldChange == GoldChange && other.SilverChange == SilverChange && other.PerlChange == PerlChange && other.RedPerlChange == RedPerlChange &&
             other.PopulationChange == PopulationChange && other.Resource1Change == Resource1Change &&
             other.Resource2Change == Resource2Change && other.Resource3Change == Resource3Change &&
             other.GoldTotal == GoldTotal && other.SilverTotal == SilverTotal && other.PerlTotal == PerlTotal && other.RedPerlTotal == RedPerlTotal && CurrencyChange.Equals(other.CurrencyChange) && CurrencyTotal.Equals(other.CurrencyTotal) && CurrencyChangeValue == other.CurrencyChangeValue && 
             other.PopulationTotal == PopulationTotal && other.Resource1Total == Resource1Total &&
             other.Resource2Total == Resource2Total && other.Resource3Total == Resource3Total &&
             other.ShardChange == ShardChange &&
             other.ShardTotal == ShardTotal &&
             other.CurrencyTotalValue == CurrencyTotalValue &&
             other.Timestamp.Equals(Timestamp);
    }

    public override bool Equals(object obj)
    {
      if (ReferenceEquals(null, obj)) return false;
      if (ReferenceEquals(this, obj)) return true;
      if (obj.GetType() != typeof (ResourceLog)) return false;
      return Equals((ResourceLog) obj);
    }

    public override int GetHashCode()
    {
      unchecked
      {
        int result = Id.GetHashCode();
        result = (result*397) ^ (Source != null ? Source.GetHashCode() : 0);
        result = (result*397) ^ (BuildingName != null ? BuildingName.GetHashCode() : 0);
        result = (result*397) ^ PersistentId.GetHashCode();
        result = (result*397) ^ Gain.GetHashCode();
        result = (result*397) ^ (Player != null ? Player.GetHashCode() : 0);
        result = (result*397) ^ GoldChange;
        result = (result*397) ^ SilverChange;
        result = (result*397) ^ PerlChange;
        result = (result*397) ^ RedPerlChange ?? 0;
        result = (result*397) ^ PopulationChange;
        result = (result*397) ^ Resource1Change;
        result = (result*397) ^ Resource2Change;
        result = (result*397) ^ Resource3Change;
        result = (result*397) ^ ShardChange ?? 0;
        result = (result*397) ^ (CurrencyChange != null ? CurrencyChange.GetHashCode() : 0);
        result = (result*397) ^ CurrencyChangeValue ?? 0;
        result = (result*397) ^ GoldTotal;
        result = (result*397) ^ SilverTotal;
        result = (result*397) ^ PerlTotal;
        result = (result*397) ^ RedPerlTotal ?? 0;
        result = (result*397) ^ PopulationTotal;
        result = (result*397) ^ Resource1Total;
        result = (result*397) ^ Resource2Total;
        result = (result*397) ^ Resource3Total;
        result = (result*397) ^ ShardTotal ?? 0;
        result = (result*397) ^ (CurrencyTotal != null ? CurrencyTotal.GetHashCode() : 0);
        result = (result*397) ^ CurrencyTotalValue ?? 0;
        result = (result*397) ^ Timestamp.GetHashCode();
        return result;
      }
    }

    public static bool operator ==(ResourceLog left, ResourceLog right)
    {
      return Equals(left, right);
    }

    public static bool operator !=(ResourceLog left, ResourceLog right)
    {
      return !Equals(left, right);
    }

    #endregion
  }
}