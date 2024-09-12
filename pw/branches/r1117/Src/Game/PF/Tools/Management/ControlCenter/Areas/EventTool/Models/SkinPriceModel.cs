using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class SkinPriceModel : INewPricesListModel<SkinPriceInfoModel>
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

    private readonly List<SkinPriceInfoModel> newPrices = new List<SkinPriceInfoModel>();
    public List<SkinPriceInfoModel> NewPrices { get { return newPrices; } }

    public List<SkinPriceInfoModel> DefaultPrices = new List<SkinPriceInfoModel>();


    public SkinPriceModel()
    {
    }


    public SkinPriceModel(SkinGoldPriceEvent info)
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      NewPrices.AddRange(info.Skins.Select(p => new SkinPriceInfoModel(p)));
    }


    public override string ToString()
    {
      return
        String.Format(
          "SkinPriceModel(NewPrices: [{0}], DefaultPrices: [{1}], Id: {2}, Description: {3}, Enabled: {4}, StartTime: {5}, EndTime: {6})",
          String.Join(",", NewPrices.Select(p => p.ToString()).ToArray()),
          String.Join(",", DefaultPrices.Select(p => p.ToString()).ToArray()),
          Id, Description, Enabled, StartTime, EndTime);
    }

  }



  public class SkinPriceInfoModel
  {

    public string Skin { get; set; }

    public int Hero { get; set; }

    public int Price { get; set; }


    public SkinPriceInfoModel()
    {
    }


    public SkinPriceInfoModel(SkinGoldPrice p)
    {
      Hero = p.HeroClassId;
      Skin = p.PersistentId;
      Price = p.Price;
    }


    public override string ToString()
    {
      return string.Format("SkinPriceInfoModel(Skin: {0}, Hero: {1}, Price: {2})", Skin, Hero, Price);
    }

  }

}