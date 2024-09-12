using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;

namespace ControlCenter.Areas.EventTool.Models
{
  public class QuestEventStageStepModel
  {
    #region Data Fields

    [DisplayName("Title")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Title { get; set; }

    [DisplayName("Choices")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("QuestEventStageStepChoiceModel")]
    public List<QuestEventStageStepChoiceModel> Choices { get; set; }

    #endregion

    #region Control Fields

    public int Index { get; set; }
    public string CommandPrefix { get; set; }

    #endregion

    public QuestEventStageStepModel()
    {
      Title = string.Empty;
      Choices = new List<QuestEventStageStepChoiceModel>();
    }

    public QuestEventStageStepModel(QuestEventStageStep questEventStageStep)
    {
      Title = questEventStageStep.Title ?? string.Empty;
      Choices = questEventStageStep.Variants.Select(v => new QuestEventStageStepChoiceModel(v)).ToList();
    }

    public QuestEventStageStep ToQuestEventStageStep()
    {
      QuestEventStageStep questEventStageStep = new QuestEventStageStep()
      {
        Title = Title,
        Variants = Choices.Select(ch => ch.ToQuestEventStageStepVariant()).ToList(),
      };
      return questEventStageStep;
    }

    public QuestEventStageStepModel Clone()
    {
      var model = new QuestEventStageStepModel
      {
        Title = Title,
        Choices = new List<QuestEventStageStepChoiceModel>(Choices.Select(c => c.Clone())),
      };
      return model;
    }

    public void PrepareControlFields(int index, string commandPrefix)
    {
      Index = index;
      CommandPrefix = commandPrefix + Index + ":";
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
        case "choice_add":
          return CommandChoiceAdd();
        case "choice_remove":
          return CommandChoiceRemove(param);
        case "choice_up":
          return CommandChoiceMoveUp(param);
        case "choice_down":
          return CommandChoiceMoveUp(param + 1);
      }
      return false;
    }

    private bool CommandChoiceAdd()
    {
      var model = new QuestEventStageStepChoiceModel();
      Choices.Add(model);
      return true;
    }

    private bool CommandChoiceRemove(int index)
    {
      if (index < 0 || index >= Choices.Count)
        return false;
      Choices.RemoveAt(index);
      return true;
    }

    private bool CommandChoiceMoveUp(int index)
    {
      if (index < 1 || index >= Choices.Count)
        return false;
      var to = Choices[index - 1];
      var from = Choices[index];
      Choices[index - 1] = from;
      Choices[index] = to;
      return true;
    }
  }
}
