using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class QuestEventModel
  {
    #region Common Data Fields

    [DisplayName("Event Id")]
    public int EventId { get; set; }

    [DisplayName("Internal description")]
    [Required]
    public string Description { get; set; }

    [DisplayName("Event locale")]
    [Required]
    public string Locale { get; set; }

    [DisplayName("Starting time")]
    [Required]
    public DateTime StartTime { get; set; }

    [DisplayName("Ending time")]
    [Required]
    public DateTime EndTime { get; set; }

    [DisplayName("Enabled?")]
    [Required]
    public bool Enabled { get; set; }

    #endregion

    #region Specific Data Fields

    [Required]
    public int GUID { get; set; }

    [DisplayName("Event title")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Title { get; set; }

    [DisplayName("Event text")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Text { get; set; }

    [DisplayName("Promoted currencies")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string CurrencyIds { get; set; }

    [DisplayName("Stages")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("QuestEventStageModel")]
    public List<QuestEventStageModel> Stages { get; set; }

    [DisplayName("Completion Talent PersistentID")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string CompletionTalentId { get; set; }

    [DisplayName("Completion talent convert ratio")]
    [Range(1, 1000000, ErrorMessage = "Must be in range from 1 to 1000000")]
    public int CompletionTalentRatio { get; set; }

    #endregion

    #region HelperFields

    public SelectList AvailableLocales { get; set; }
    public bool New { get; set; }

    #endregion

    public QuestEventModel()
    {
      EventId = 0;
      Description = string.Empty;
      Locale = string.Empty;
      StartTime = DateTime.UtcNow.AddDays(1);
      EndTime = DateTime.UtcNow.AddDays(2);
      Enabled = false;

      Title = string.Empty;
      Text = string.Empty;
      CurrencyIds = string.Empty;
      Stages = new List<QuestEventStageModel>();
      CompletionTalentId = string.Empty;
      CompletionTalentRatio = 1;
      GUID = -1;

      New = true;
    }

    public QuestEventModel(QuestEvent questEvent)
    {
      EventId = questEvent.PersistentId;
      Description = questEvent.Description;
      Locale = questEvent.Locale;
      StartTime = questEvent.StartTime.FromUnixTimestamp();
      EndTime = questEvent.EndTime.FromUnixTimestamp();
      Enabled = questEvent.Enabled;

      Title = questEvent.Title;
      Text = questEvent.Text;
      CurrencyIds = questEvent.CurrencyIds.Count > 0 ? questEvent.CurrencyIds.Aggregate((f, s) => f + ", " + s) : string.Empty;
      Stages = new List<QuestEventStageModel>(questEvent.Stages.Select(item => new QuestEventStageModel(item)));
      CompletionTalentId = questEvent.CompletionTalentId;
      CompletionTalentRatio = questEvent.CompletionTalentRatio;
      GUID = questEvent.Guid;

      New = false;
    }

    public QuestEvent ToQuestEvent()
    {
      QuestEvent questEvent = new QuestEvent()
      {
        PersistentId = EventId,
        Description = Description,
        Locale = Locale,
        StartTime = StartTime.ToUnixTimestamp(),
        EndTime = EndTime.ToUnixTimestamp(),
        Enabled = Enabled,

        Title = Title,
        Text = Text,
        CurrencyIds = new List<string>(CurrencyIds.Split(',').Select(s => s.Trim()).Where(s => !string.IsNullOrEmpty(s))),
        Stages = new List<QuestEventStage>(Stages.Select(item => item.ToQuestEventStage())),
        CompletionTalentId = CompletionTalentId,
        CompletionTalentRatio = CompletionTalentRatio,
        Guid = GUID,
      };
      return questEvent;
    }

    public void PrepareControlFields()
    {
      New = EventId == 0;
      string stageCommandPrefix = "stage_command:";
      for (int i = 0; i < Stages.Count; i++)
      {
        Stages[i].PrepareControlFields(i, stageCommandPrefix);
      }
    }

    public bool ProcessCommand(string[] cmdArgs, int startIdx)
    {
      if (cmdArgs.Length < startIdx + 2)
        return false;

      string cmd = cmdArgs[startIdx];
      int param;
      if (!int.TryParse(cmdArgs[startIdx + 1], out param))
        return false;

      switch (cmd)
      {
        case "stage_add":
          return CommandStageAdd();
        case "stage_remove":
          return CommandStageRemove(param);
        case "stage_up":
          return CommandStageMoveUp(param);
        case "stage_down":
          return CommandStageMoveUp(param + 1);
        case "stage_clone":
          return CommandStageClone(param);
        case "stage_command":
          return CommandStageCommand(param, cmdArgs, startIdx + 2);
      }
      return false;
    }

    private bool CommandStageAdd()
    {
      var model = new QuestEventStageModel();
      Stages.Add(model);
      return true;
    }

    private bool CommandStageRemove(int index)
    {
      if (index < 0 || index >= Stages.Count)
        return false;
      Stages.RemoveAt(index);
      return true;
    }

    private bool CommandStageMoveUp(int index)
    {
      if (index < 1 || index >= Stages.Count)
        return false;
      var to = Stages[index - 1];
      var from = Stages[index];
      Stages[index - 1] = from;
      Stages[index] = to;
      return true;
    }

    private bool CommandStageClone(int index)
    {
      if (index < 0 || index >= Stages.Count)
        return false;
      var model = Stages[index].Clone();
      Stages.Add(model);
      return true;
    }

    private bool CommandStageCommand(int index, string[] cmdArgs, int startIndex)
    {
      if (index < 0 || index >= Stages.Count)
        return false;
      return Stages[index].ProcessCommand(cmdArgs, startIndex);
    }
  }
}