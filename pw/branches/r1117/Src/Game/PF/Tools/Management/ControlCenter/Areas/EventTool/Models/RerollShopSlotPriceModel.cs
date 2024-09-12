using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class RerollShopSlotPriceModel : INewPricesListModel<RerollSlotPriceInfoModel>
  {
    public int TimeZone { get; set; }
    public int Id { get; set; }

    [Required]
    public string Description { get; set; }

    public bool Enabled { get; set; }

    [Required]
    public DateTime StartTime { get; set; }

    [Required]
    public DateTime EndTime { get; set; }

    private readonly List<RerollSlotPriceInfoModel> newPrices = new List<RerollSlotPriceInfoModel>();
    public List<RerollSlotPriceInfoModel> NewPrices { get { return newPrices; } }
    
    public List<RerollSlotPriceInfoModel> DefaultPrices = new List<RerollSlotPriceInfoModel>();

    public RerollShopSlotPriceModel()
    {
    }

    public RerollShopSlotPriceModel( RerollShopSlotPriceEvent info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      NewPrices.AddRange(info.Slots.Select(p => new RerollSlotPriceInfoModel(p)));
    }

    public override string ToString()
    {
      return
        String.Format(
          "RerollSlotPriceModel(NewPrices: [{0}], DefaultPrices: [{1}], Id: {2}, Description: {3}, Enabled: {4}, StartTime: {5}, EndTime: {6})",
          String.Join(",", NewPrices.Select(p => p.ToString()).ToArray()),
          String.Join(",", DefaultPrices.Select(p => p.ToString()).ToArray()),
          Id, Description, Enabled, StartTime, EndTime);
    }
  }

  public class RerollSlotPriceInfoModel
  {

    public string Slot { get; set; }

    public string Group { get; set; }

    public int MinPrice { get; set; }

    public int MaxPrice { get; set; }


    public RerollSlotPriceInfoModel()
    {
    }


    public RerollSlotPriceInfoModel( RerollShopSlotPrice p )
    {
      Slot = p.PersistentId;
      Group = p.GroupId;
      MinPrice = p.MinPrice;
      MaxPrice = p.MaxPrice;
    }


    public override string ToString()
    {
      return String.Format( "RerollSlotPriceInfoModel(Slot: {0}, Group:{1}, MinPrice: {2}, MaxPrice: {3})", Slot, Group, MinPrice, MaxPrice );
    }

  }
}