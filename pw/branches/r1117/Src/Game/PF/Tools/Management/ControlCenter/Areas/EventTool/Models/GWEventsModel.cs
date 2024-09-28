using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GWEvents.Models
{

    public class GWEventHistory : PagedModel
    {
      public List<GWEventHistoryModel> GwEvents { get; set; }
      public DateTime StartTime { get; set; }
      public DateTime EndTime { get; set; }
      public int EventIdx { get; set; }
      public long GuildAuid { get; set; }
      public int Auid { get; set; }
      public GWEventHistory()
      {
        GwEvents = new List<GWEventHistoryModel>();
      }
    }
    public class GWEventHistoryModel
    {
      public int EventIndex { get; set; }
      public long GuildId { get; set; }
      public int LastPoints { get; set; }
      public int CurrentPoints { get; set; }
      public DateTime TimeStamp { get; set; }
      public int Auid { get; set; }
    }

    public class GWEventsModel
    {
        public List<GWEventModel> GwEvents { get; set; }

        public GWEventsModel()
        {
            GwEvents = new List<GWEventModel>();
        }

        public GWEventsModel(IEnumerable<AccountLib.GWEventModel> tGwEvents)
        {
            GwEvents = new List<GWEventModel>();
            GwEvents.AddRange(tGwEvents.Select(tGwEvent => new GWEventModel(tGwEvent)));
        }
    }

    #region Submodels
    public class GWEventModel
    {
        #region Support data
        public int TimeZone { get; set; }
        [DisplayName("MongoDB ID")]
        public string Id { get; set; }
        [DisplayName("Event index")]
        public int EventIndex { get; set; }
        public bool Enabled { get; set; }
        public long CurrentPoints { get; set; }
        public int PointsToAddLimit { get; set; }
        #endregion

        [Required]
        public DateTime EndTime { get; set; }

        [Required]
        public long PointsToAdd { get; set; }

        [Required]
        public long Limit { get; set; }

        public GWEventModel()
        {
            EndTime = DateTime.Now;
            Id = string.Empty;
        }

        public GWEventModel(AccountLib.GWEventModel tGwEventModel)
        {
            Id = tGwEventModel.PersistentId;
            Enabled = tGwEventModel.Enabled;
            PointsToAddLimit = tGwEventModel.PointsToAddLimit;
            CurrentPoints = tGwEventModel.Points;
            EndTime = tGwEventModel.EndTime.FromUnixTimestamp();
            Limit = tGwEventModel.Limit;
            EventIndex = tGwEventModel.Event_index;
        }

        public AccountLib.GWEventModel toTGWEventModel()
        {
            var tGwEventModel = new AccountLib.GWEventModel
            {
                PersistentId = Id,
                Enabled = Enabled,
                PointsToAddLimit = PointsToAddLimit,
                Points = PointsToAdd,
                EndTime = EndTime.ToUnixTimestamp(),
                Limit = Limit,
                Event_index = EventIndex
            };
            return tGwEventModel;
        }

    }
    #endregion
}
