using System;
using System.ComponentModel.DataAnnotations;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class CustomEventModel
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
    public string Type { get; set; }


    public CustomEventModel()
    {
    }


    public CustomEventModel(CustomEvent info)
    {
      Id = info.PersistentId;
      Description = info.Description;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
      Enabled = info.Enabled;
      Type = info.Type;
    }

  }

}