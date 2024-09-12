using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class RerollShopSlotsModel
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
    public RerollSlotsModel RerollSlots { get; set; }
    public RerollSlotsModel DefaultRerollSlots { get; set; }

    public RerollShopSlotsModel()
    {
    }


    public RerollShopSlotsModel( RerollShopSlots info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
      Enabled = info.Enabled;
      RerollSlots = new RerollSlotsModel( info );
    }

  }

  public class RerollSlotsModel
  {
    [Required]
    public int UsualSlots { get; set; }

    [Required]
    public int PremiumSlots { get; set; }

    [Required]
    [DisplayName( "Max inactive usual slots after reroll" )]
    public int MaxActiveUsualSlots { get; set; }

    [Required]
    [DisplayName( "Max inactive premium slots after reroll" )]
    public int MaxActivePremiumSlots { get; set; }

    public RerollSlotsModel()
    {
      
    }

    public RerollSlotsModel( RerollShopSlots info )
    {
      UsualSlots = info.UsualSlots;
      PremiumSlots = info.PremiumSlots;
      MaxActiveUsualSlots = info.MaxActiveUsualSlots;
      MaxActivePremiumSlots = info.MaxActivePremiumSlots;
    }
  }

}