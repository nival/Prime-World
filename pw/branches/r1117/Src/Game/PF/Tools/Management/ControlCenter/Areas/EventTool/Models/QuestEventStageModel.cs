using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;

namespace ControlCenter.Areas.EventTool.Models
{
  public class QuestEventStageModel
  {
    #region Data Fields

    [DisplayName("Title")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Title { get; set; }

    [DisplayName("Text")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Text { get; set; }

    [DisplayName( "Image (533x678 (мб порезано до 390x678 на узких мониках))" )]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Image { get; set; }

    [DisplayName("Reward")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("RollEventItemModel")]
    public RollEventItemModel Reward { get; set; }

    [DisplayName( "LoseReward" )]
    [Required( ErrorMessage = "If you see this message, ask programmer!" )]
    [UIHint( "RollEventItemModel" )]
    public RollEventItemModel LoseReward { get; set; }

    [DisplayName("Steps")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("QuestEventStageStepModel")]
    public List<QuestEventStageStepModel> Steps { get; set; }

    #endregion

    #region Helper Fields

    public int Index { get; set; }
    public string CommandPrefix { get; set; }

    #endregion

    public QuestEventStageModel()
    {
      Title = string.Empty;
      Text = string.Empty;
      Image = string.Empty;
      Reward = new RollEventItemModel( RollEventItemTypeEnum.Lootbox, false );
      LoseReward = new RollEventItemModel( RollEventItemTypeEnum.Lootbox, false );
      Steps = new List<QuestEventStageStepModel>();
    }

    public QuestEventStageModel(QuestEventStage questEventStage)
    {
      Title = questEventStage.Title ?? string.Empty;
      Text = questEventStage.Text ?? string.Empty;
      Image = questEventStage.Image ?? string.Empty;
      Reward = new RollEventItemModel( questEventStage.Reward );
      LoseReward = new RollEventItemModel( questEventStage.LoseReward );
      Steps = new List<QuestEventStageStepModel>(questEventStage.Steps.Select(item => new QuestEventStageStepModel(item)));
    }

    public QuestEventStage ToQuestEventStage()
    {
      var questEventStage = new QuestEventStage()
      {
        Title = Title,
        Text = Text,
        Image = Image,
        Reward = Reward.ToRollEventItem(),
        Steps = new List<QuestEventStageStep>(Steps.Select(s => s.ToQuestEventStageStep())),
        LoseReward = LoseReward.ToRollEventItem(),
      };
      return questEventStage;
    }

    public QuestEventStageModel Clone()
    {
      var model = new QuestEventStageModel
      {
        Title = Title,
        Text = Text,
        Image = Image,
        Reward = Reward.Clone(),
        LoseReward = LoseReward.Clone(),
        Steps = new List<QuestEventStageStepModel>(Steps.Select(s => s.Clone()))
      };
      return model;
    }

    public void PrepareControlFields(int index, string commandPrefix)
    {
      Index = index;
      CommandPrefix = commandPrefix + Index + ":";

      string stepCommandPrefix = CommandPrefix + "step_command:";
      for (int i = 0; i < Steps.Count; i++)
      {
        Steps[i].PrepareControlFields(i, stepCommandPrefix);
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
        case "step_add":
          return CommandStepAdd();
        case "step_remove":
          return CommandStepRemove(param);
        case "step_up":
          return CommandStepMoveUp(param);
        case "step_down":
          return CommandStepMoveUp(param + 1);
        case "step_clone":
          return CommandStepClone(param);
        case "step_command":
          return CommandStepCommand(param, cmdArgs, startIdx + 2);
      }
      return false;
    }

    private bool CommandStepAdd()
    {
      var model = new QuestEventStageStepModel();
      Steps.Add(model);
      return true;
    }

    private bool CommandStepRemove(int index)
    {
      if (index < 0 || index >= Steps.Count)
        return false;
      Steps.RemoveAt(index);
      return true;
    }

    private bool CommandStepMoveUp(int index)
    {
      if (index < 1 || index >= Steps.Count)
        return false;
      var to = Steps[index - 1];
      var from = Steps[index];
      Steps[index - 1] = from;
      Steps[index] = to;
      return true;
    }

    private bool CommandStepClone(int index)
    {
      if (index < 0 || index >= Steps.Count)
        return false;
      var model = Steps[index].Clone();
      Steps.Add(model);
      return true;
    }

    private bool CommandStepCommand(int index, string[] cmdArgs, int startIdx)
    {
      if (index < 0 || index >= Steps.Count)
        return false;
      return Steps[index].ProcessCommand(cmdArgs, startIdx);
    }
  }
}
