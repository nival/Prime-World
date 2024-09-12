using System;
using System.ComponentModel.DataAnnotations;
using System.Runtime.Serialization;
using System.Web.Mvc;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class RerollShopTooltipModel
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
    public string Tooltip { get; set; }

    [Required]
    public string Locale { get; set; }

    public SelectList SvcLocales { get; set; }


    public RerollShopTooltipModel()
    {
    }


    public RerollShopTooltipModel( RerollShopTooltip info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
      Enabled = info.Enabled;
      Tooltip = info.Tooltip;
      Locale = info.Locale;
    }

  }

}