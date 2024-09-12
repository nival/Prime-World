using System;
using System.Collections.Generic;

namespace ControlCenter.Areas.GM.Models
{
    public class QuestEventsStepsModel : PagedModel
    {
        public List<QuestEventsStepsHistoryModel> Events { get; set; }
        public DateTime StartTime { get; set; }
        public DateTime EndTime { get; set; }
        public int Auid { get; set; }
        public int Stage { get; set; }
        public QuestEventsStepsModel()
        {
            Events = new List<QuestEventsStepsHistoryModel>();
        } 
    }

    public class QuestEventsStepsHistoryModel
    {
        public int ToStageStepChange { get; set; }
        public int Stage { get; set; }
        public int Auid { get; set; }
        public DateTime TimeStamp { get; set; }
    }

}