using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;

namespace ControlCenter.Areas.EventTool.Models
{
  public class QuestEventStageStepChoiceModel
  {
    #region Data Fields

    [DisplayName("Choice Title")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Title { get; set; }

    [DisplayName("Win Message")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string WinMessage { get; set; }

    [DisplayName("Lose Message")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string LoseMessage { get; set; }

    [DisplayName( "Win Ratio for average player" )]
    [Required( ErrorMessage = "Win ratio must be defined as floating point value in range from 0.0 to 1.0" )]
    [Range( 0.0d, 1.0d, ErrorMessage = "Out of supported range" )]
    public double WinRatioBase { get; set; }

    [DisplayName( "Win Ratio for player with 'Golden Age'" )]
    [Required( ErrorMessage = "Win ratio must be defined as floating point value in range from 0.0 to 1.0" )]
    [Range( 0.0d, 1.0d, ErrorMessage = "Out of supported range" )]
    public double WinRatioGold { get; set; }

    [DisplayName( "Choice price" )]
    [Required( ErrorMessage = "If you see this message, ask programmer!" )]
    [UIHint( "ResourceTableSmallModel" )]
    public ResourcesTableSmallModel Price { get; set; }

    #endregion

    public QuestEventStageStepChoiceModel()
    {
      Title = string.Empty;
      WinMessage = string.Empty;
      LoseMessage = string.Empty;
      WinRatioBase = 0.9d;
      WinRatioGold = 0.95d;
      Price = new ResourcesTableSmallModel();
    }

    public QuestEventStageStepChoiceModel( QuestEventStageStepVariant questEventStageStepVariant )
    {
      Title = questEventStageStepVariant.Message ?? string.Empty;
      WinMessage = questEventStageStepVariant.WinMessage ?? string.Empty;
      LoseMessage = questEventStageStepVariant.LoseMessage ?? string.Empty;
      WinRatioBase = questEventStageStepVariant.WinRatioBase;
      WinRatioGold = questEventStageStepVariant.WinRatioGold;
      Price = new ResourcesTableSmallModel( questEventStageStepVariant.Price );
    }

    public QuestEventStageStepVariant ToQuestEventStageStepVariant()
    {
      var questEventStageStepVariant = new QuestEventStageStepVariant()
      {
        Message = Title,
        WinMessage = WinMessage,
        LoseMessage = LoseMessage,
        WinRatioBase = WinRatioBase,
        WinRatioGold = WinRatioGold,
        Price = Price.ToResourceTableSmall(),
      };
      return questEventStageStepVariant;
    }

    public QuestEventStageStepChoiceModel Clone()
    {
      var model = new QuestEventStageStepChoiceModel
      {
        Title = Title,
        WinMessage = WinMessage,
        LoseMessage = LoseMessage,
        WinRatioBase = WinRatioBase,
        WinRatioGold = WinRatioGold,
        Price = Price.Clone(),
      };
      return model;
    }
  }
}