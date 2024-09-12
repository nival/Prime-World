using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class CustomMapModel
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
    public string Day { get; set; }

    [Required]
    public string StartHour { get; set; }

    [Required]
    public string EndHour { get; set; }

    [Required]
    public string MapDbid { get; set; }

    [Required]
    public string MapType { get; set; }

    public bool MapEnabled { get; set; }


    public CustomMapModel()
    {
    }


    public CustomMapModel(CustomMap info)
    {
      Id = info.PersistentId;
      Description = info.Description;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
      Enabled = info.Enabled;
      Day = info.Day;
      StartHour = info.StartHour;
      EndHour = info.EndHour;
      MapDbid = info.MapDbid;
      MapType = info.MapType;
      MapEnabled = info.MapEnabled;
    }

  }

}