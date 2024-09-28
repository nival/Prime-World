using System;
using System.ComponentModel.DataAnnotations;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class TechsModel
  {
    public int TimeZone { get; set; }
    public int Id { get; set; }

    [Required]
    public string Description { get; set; }

    [Required]
    public DateTime StartTime { get; set; }

    [Required]
    public DateTime EndTime { get; set; }

    [Required]
    public string Type { get; set; }

    [Required]
    public int Time { get; set; }


    public TechsModel()
    {
    }


    public TechsModel(TechsInfo info)
    {
      Id = info.PersistentId;
      Description = info.Description;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
      Type = info.Type;
      Time = info.Time;
    }

  }

}