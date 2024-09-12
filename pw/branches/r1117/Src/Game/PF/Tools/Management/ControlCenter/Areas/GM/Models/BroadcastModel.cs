using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Models
{
  public class BroadcastModel
  {
    public int Id { get; set; }
    [Required]
    public string Title { get; set; }
    [DisplayName("Start time")]
    public DateTime TimeStart { get; set; }
    [DisplayName("Finish time")]
    public DateTime TimeFinish { get; set; }
    public int TimeZone { get; set; }
    public int Interval { get; set; }
    [DisplayName("Enabled")]
    public bool EnabledNow { get; set; }

    public class Message
    {
      public string Locale { get; set; }
      public string Text { get; set; }
    }
    public List<Message> Messages { get; set; }

    public BroadcastModel()
    {
    }

    public BroadcastModel(List<string> locales)
    {
      if (locales == null || locales.Count == 0)
        throw new ArgumentException("Locales list is null or empty", "locales");

      TimeStart = DateTime.UtcNow;
      TimeFinish = DateTime.UtcNow;
      Messages = locales.Select(l => new Message { Locale = l }).ToList();
    }

    public BroadcastModel(List<string> locales, BroadcastInfo info)
    {
      if (locales == null || locales.Count == 0)
        throw new ArgumentException("Locales list is null or empty", "locales");

      Id = info.Id;
      Title = info.Title;
      Messages = locales.Select(l => new Message
                                       {
                                         Locale = l,
                                         Text = info.Messages.Any(m => m.Locale == l)
                                                  ? info.Messages.Single(m => m.Locale == l).Text
                                                  : null
                                       }).ToList();
      TimeStart = info.TimeStart.FromUnixTimestamp();
      TimeFinish = info.TimeFinish.FromUnixTimestamp();
      Interval = info.Interval;
      EnabledNow = info.EnabledNow;
    }
  }

}