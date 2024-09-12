using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class RerollShopGroupPriceModel : INewPricesListModel<RerollShopGroupPriceInfoModel>
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

    private readonly List<RerollShopGroupPriceInfoModel> newPrices = new List<RerollShopGroupPriceInfoModel>();
    public List<RerollShopGroupPriceInfoModel> NewPrices { get { return newPrices; } }

    public List<RerollShopGroupPriceInfoModel> DefaultPrices = new List<RerollShopGroupPriceInfoModel>();

    public RerollShopGroupPriceModel()
    {
    }

    public RerollShopGroupPriceModel( RerollShopGroupPriceEvent info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      NewPrices.AddRange( info.Groups.Select( p => new RerollShopGroupPriceInfoModel( p ) ) );
    }

    public override string ToString()
    {
      return
        String.Format(
          "RerollSlotPriceModel(NewPrices: [{0}], DefaultPrices: [{1}], Id: {2}, Description: {3}, Enabled: {4}, StartTime: {5}, EndTime: {6})",
          String.Join( ",", NewPrices.Select( p => p.ToString() ).ToArray() ),
          String.Join( ",", DefaultPrices.Select( p => p.ToString() ).ToArray() ),
          Id, Description, Enabled, StartTime, EndTime );
    }
  }

  public class RerollShopGroupPriceInfoModel
  {

    public string Group { get; set; }

    public int MinPrice { get; set; }

    public int MaxPrice { get; set; }


    public RerollShopGroupPriceInfoModel()
    {
    }


    public RerollShopGroupPriceInfoModel( RerollShopGroupPrice p )
    {
      Group = p.PersistentId;
      MinPrice = p.MinPrice;
      MaxPrice = p.MaxPrice;
    }


    public override string ToString()
    {
      return String.Format( "RerollShopGroupPriceInfoModel(Group: {0}, MinPrice: {1}, MaxPrice: {2})", Group, MinPrice, MaxPrice );
    }

  }
}