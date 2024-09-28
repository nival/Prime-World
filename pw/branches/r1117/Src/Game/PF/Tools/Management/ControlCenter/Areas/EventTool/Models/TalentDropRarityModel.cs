using System;
using System.ComponentModel.DataAnnotations;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class TalentDropRarityModel
  {
    public int TimeZone { get; set; }
    public int Id { get; set; }

    [Required]
    public string Description { get; set; }

    [Required]
    public DateTime StartTime { get; set; }

    [Required]
    public DateTime EndTime { get; set; }

    public bool Enabled { get; set; }

    [Required]
    public bool Premium { get; set; }

    [Required]
    public int GoodRarity { get; set; }

    [Required]
    public int ExcellentRarity { get; set; }

    [Required]
    public int MagnificentRarity { get; set; }

    [Required]
    public int ExclusiveRarity { get; set; }


    public TalentDropRarityInfoModel OrdinaryDefault;
    public TalentDropRarityInfoModel PremiumDefault;


    public TalentDropRarityModel()
    {
    }


    public TalentDropRarityModel(TalentDropRarityEvent info)
    {
      Id = info.PersistentId;
      Description = info.Description;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
      Enabled = info.Enabled;
      Premium = info.Premium;
      GoodRarity = info.DropRarity.Good;
      ExcellentRarity = info.DropRarity.Excellent;
      MagnificentRarity = info.DropRarity.Magnificent;
      ExclusiveRarity = info.DropRarity.Exclusive;
    }

  }



  public class TalentDropRarityInfoModel
  {

    public int Class { get; set; }

    public int Ordinary { get; set; }

    public int Good { get; set; }

    public int Excellent { get; set; }

    public int Magnificent { get; set; }

    public int Exclusive { get; set; }


    public TalentDropRarityInfoModel()
    {
    }


    public TalentDropRarityInfoModel(TalentDropRarity info)
    {
      Class = info.ClassRar;
      Ordinary = info.Ordinary;
      Good = info.Good;
      Excellent = info.Excellent;
      Magnificent = info.Magnificent;
      Exclusive = info.Exclusive;
    }

  }

}