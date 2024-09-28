using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class FirstBuyPriceModel : INewPricesListModel<FirstBuyPriceInfoModel>
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

    private readonly List<FirstBuyPriceInfoModel> newPrices = new List<FirstBuyPriceInfoModel>();
    public List<FirstBuyPriceInfoModel> NewPrices { get { return newPrices; } }

    public List<FirstBuyPriceInfoModel> DefaultPrices = new List<FirstBuyPriceInfoModel>();


    public FirstBuyPriceModel()
    {
    }


    public FirstBuyPriceModel( FirstBuyGoldPriceEvent info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      NewPrices.AddRange( info.FirstBuys.Select( p => new FirstBuyPriceInfoModel( p ) ) );
    }


    public override string ToString()
    {
      return
        String.Format(
          "FirstBuyPriceInfoModel(NewPrices: [{0}], DefaultPrices: [{1}], Id: {2}, Description: {3}, Enabled: {4}, StartTime: {5}, EndTime: {6})",
          String.Join( ",", NewPrices.Select( p => p.ToString() ).ToArray() ),
          String.Join( ",", DefaultPrices.Select( p => p.ToString() ).ToArray() ),
          Id, Description, Enabled, StartTime, EndTime );
    }

  }



  public class FirstBuyPriceInfoModel
  {

    public string Construction { get; set; }

    public int GoldPrice { get; set; }


    public FirstBuyPriceInfoModel()
    {
    }


    public FirstBuyPriceInfoModel( FirstBuyGoldPrice p )
    {
      Construction = p.PersistentId;
      GoldPrice = p.Price;
    }


    public override string ToString()
    {
      return string.Format( "FirstBuyPriceInfoModel(Construction: {0}, GoldPrice: {1})", Construction, GoldPrice );
    }

  }

}