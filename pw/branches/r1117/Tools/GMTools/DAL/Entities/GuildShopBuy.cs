using System;

namespace DAL.Entities
{

  /// <summary>
  /// Покупка в магазине клана
  /// </summary>
  public class GuildShopBuy
  {

    public virtual long Id { get; set; }

    public virtual Player Player { get; set; }

    public virtual Guild Guild { get; set; }

    /// <summary>
    /// Купленный итем
    /// </summary>
    public virtual GuildShopItem GuildShopItem { get; set; }

    /// <summary>
    /// Куплено ли в магазине сюзерена (false - в своем)
    /// </summary>
    public virtual bool HasSuzerain { get; set; }

    /// <summary>
    /// Уровень магазина
    /// </summary>
    public virtual int ShopLevel { get; set; }

    /// <summary>
    /// Цена
    /// </summary>
    public virtual GuildPointsLog GuildPointsLog { get; set; }

    public virtual DateTime Timestamp { get; set; }

  }

}