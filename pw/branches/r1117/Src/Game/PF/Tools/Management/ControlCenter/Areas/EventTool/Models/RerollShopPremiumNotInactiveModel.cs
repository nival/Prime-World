using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class RerollShopPremiumNotInactiveEventModel
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
    [DisplayName("Enable to force premium slots reroll instantly")]
    public bool IsInactive { get; set; }

    public bool IsInactiveDefault { get; set; }

    public RerollShopPremiumNotInactiveEventModel()
    {
    }


    public RerollShopPremiumNotInactiveEventModel( RerollShopPremiumNotInactiveEvent info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
      Enabled = info.Enabled;
      IsInactive = info.IsInactive;
    }

  }

}