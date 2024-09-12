using System;
namespace DAL.Entities
{
    public class ReRollShopLog
    {
        /// <summary>
        /// Идентификатор
        /// </summary>
    public virtual int Id { get; set; }
    public virtual Player Player { get; set; }
    public virtual long? Auid { get; set; }
    public virtual int ItemId { get; set; }

    public virtual int ItemGroup { get; set; }
    public virtual long ItemPrice { get; set; }
    public virtual string ItemPriceType { get; set; }

    public virtual int RerollCount { get; set; }
    public virtual string SlotType { get; set; }
    public virtual DateTime Timestamp { get; set; }
    }
}