using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  /// <summary>
  /// Этот интерфейс нужен чтобы описать универсальный биндер NewPricesModelBinder для заполнения списка новых цен.
  /// </summary>
  public interface INewPricesListModel<TList>
  {
    List<TList> NewPrices { get; }
  }


  public class HeroPriceModel : INewPricesListModel<HeroPriceInfoModel>
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

    private readonly List<HeroPriceInfoModel> newPrices = new List<HeroPriceInfoModel>();
    public List<HeroPriceInfoModel> NewPrices { get { return newPrices; } }
    
    public List<HeroPriceInfoModel> DefaultPrices = new List<HeroPriceInfoModel>();

    public HeroPriceModel()
    {
    }

    public HeroPriceModel(HeroPriceEvent info)
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      NewPrices.AddRange(info.Heroes.Select(p => new HeroPriceInfoModel(p)));
    }

    public override string ToString()
    {
      return
        String.Format(
          "HeroPriceModel(NewPrices: [{0}], DefaultPrices: [{1}], Id: {2}, Description: {3}, Enabled: {4}, StartTime: {5}, EndTime: {6})",
          String.Join(",", NewPrices.Select(p => p.ToString()).ToArray()),
          String.Join(",", DefaultPrices.Select(p => p.ToString()).ToArray()),
          Id, Description, Enabled, StartTime, EndTime);
    }
  }



  public class HeroPriceInfoModel
  {

    public string Hero { get; set; }

    public int SilverPrice { get; set; }

    public int GoldPrice { get; set; }


    public HeroPriceInfoModel()
    {
    }


    public HeroPriceInfoModel(HeroPrice p)
    {
      Hero = p.PersistentId;
      SilverPrice = p.SilverPrice;
      GoldPrice = p.GoldPrice;
    }


    public override string ToString()
    {
      return String.Format("HeroPriceInfoModel(Hero: {0}, SilverPrice: {1}, GoldPrice: {2})", Hero, SilverPrice, GoldPrice);
    }

  }

}