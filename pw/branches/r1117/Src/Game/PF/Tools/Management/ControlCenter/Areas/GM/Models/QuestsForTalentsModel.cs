using System;
using System.Collections.Generic;

namespace ControlCenter.Areas.GM.Models
{
    public class QuestsForTalentsModel
    {
        public List<QuestForTalentModel> items = new List<QuestForTalentModel>();
        public long Auid { get; set; }
        public string Login { get; set; }
    }

    public class QuestForTalentModel
    {
        public long Auid { get; set; }
        public int QuestId { get; set; }
        public DateTime StartTime { get; set; }
        public DateTime EndTime { get; set; }
        public int TalentAwardPersistentId { get; set; }
        public string TalentAwardName { get; set; }
        public int ShardsSpent { get; set; }
        public string FullDynamicQuestDump { get; set; }
        public int CurrentObjectiveValue { get; set; }
        public string CurrentObjectiveData { get; set; }
        public int ObjectiveId { get; set; }
        public int AwardId { get; set; }
        public int Reason { get; set; }
        public string TotalObjectiveData { get; set; }
    }
}