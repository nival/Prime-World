using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Runtime.Remoting.Activation;
using System.Web.Mvc;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  #region Submodels

  public enum RollEventRuleTypeEnum
  {
    Simple = 0,
    Reforge = 1,
  }

  public class RollEventRuleModel
  {
    [Required(ErrorMessage = "Roll Rule type required!")]
    [DisplayName("Roll Rule Type")]
    public RollEventRuleTypeEnum RuleType { get; set; }

    [DisplayName("Description")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Description { get; set; }

    [Required(ErrorMessage = "Roll Event Title must be defined")]
    [DisplayName("Title")]
    public string Title { get; set; }

    [DisplayName("Text")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Text { get; set; }

    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("ResourceTableSmallModel")]
    public ResourcesTableSmallModel Price { get; set; }

    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [DisplayName("Rewards List")]
    [UIHint("RollEventItemModel")]
    public List<RollEventItemModel> Rewards { get; set; }

    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [DisplayName("Reforge Sources List")]
    [UIHint("RollEventItemModel")]
    public List<RollEventItemModel> ReforgeSource { get; set; }

    public RollEventRuleModel()
    {
      RuleType = RollEventRuleTypeEnum.Simple;
      Description = string.Empty;
      Title = string.Empty;
      Text = string.Empty;
      Price = new ResourcesTableSmallModel();
      Rewards = new List<RollEventItemModel>();
      ReforgeSource = new List<RollEventItemModel>();
    }

    public RollEventRuleModel(RollEventRule rollEventRule)
    {
      RuleType = (RollEventRuleTypeEnum) rollEventRule.RuleType;
      Description = rollEventRule.Description;
      Title = rollEventRule.TitleLocalized;
      Text = rollEventRule.TextLocalized;
      Price = new ResourcesTableSmallModel(rollEventRule.Price);
      Rewards = new List<RollEventItemModel>(rollEventRule.Rewards.Select(item => new RollEventItemModel(item)));
      ReforgeSource = new List<RollEventItemModel>(rollEventRule.ReforgeSource.Select(item => new RollEventItemModel(item)));
    }

    public RollEventRule ToRollEventRule()
    {
      RollEventRule rollEventRule = new RollEventRule()
      {
        RuleType = (RollEventRuleType) RuleType,
        Description = Description,
        TitleLocalized = Title,
        TextLocalized = Text,
        Price = Price.ToResourceTableSmall(),
        Rewards = new List<RollEventItem>(Rewards.Select(model => model.ToRollEventItem())),
        ReforgeSource = new List<RollEventItem>(ReforgeSource.Select(model => model.ToRollEventItem())),
      };
      return rollEventRule;
    }
  }

  #endregion

  public class RollEventModel
  {
    [DisplayName("Event ID")]
    public int EventId { get; set; }

    [Required]
    [DisplayName("Event title")]
    public string Title { get; set; }

    [DisplayName("Event description text")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Text { get; set; }

    [Required]
    [DisplayName("Internal description")]
    public string Description { get; set; }

    [Required]
    [DisplayName("Event locale")]
    public string Locale { get; set; }

    [DisplayName( "Event image (1588x424 (мб порезано до 1180x424 на узких мониках))" )]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Image { get; set; }

    [Required]
    [DisplayName("Starting time")]
    public DateTime StartTime { get; set; }

    [Required]
    [DisplayName("Endind time")]
    public DateTime EndTime { get; set; }

    [Required]
    [DisplayName("Enabled?")]
    public bool Enabled { get; set; }

    [DisplayName("Completion Talent PersistentID")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string CompletionTalentId { get; set; }

    [DisplayName("Completion talent convert ratio")]
    [Range(1, 1000000, ErrorMessage = "Must be in range from 1 to 1000000")]
    public int CompletionTalentRatio { get; set; }

    [DisplayName("Promoted currencies")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string CurrencyIds { get; set; }

    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [DisplayName("Roll Rules")]
    public List<RollEventRuleModel> Rolls { get; set; }

    [Required]
    public int GUID { get; set; }

    #region Support data

    public SelectList AvailableLocales { get; set; }
    public bool New { get; set; }

    #endregion

    public RollEventModel()
    {
      Text = string.Empty;
      Image = string.Empty;
      CompletionTalentId = string.Empty;
      CompletionTalentRatio = 1;
      CurrencyIds = string.Empty;
      Rolls = new List<RollEventRuleModel>();
      StartTime = DateTime.UtcNow.AddDays(1);
      EndTime = DateTime.UtcNow.AddDays(2);
      GUID = -1;

      New = true;
    }

    public RollEventModel(RollEvent rollEvent)
    {
      Locale = rollEvent.Locale;
      Image = rollEvent.Image;
      Text = rollEvent.Text;
      Title = rollEvent.Title;
      EventId = rollEvent.PersistentId;
      Description = rollEvent.Description;
      StartTime = rollEvent.StartTime.FromUnixTimestamp();
      EndTime = rollEvent.EndTime.FromUnixTimestamp();
      Enabled = rollEvent.Enabled;
      CompletionTalentId = rollEvent.CompletionTalentId;
      CompletionTalentRatio = rollEvent.CompletionTalentRatio;
      GUID = rollEvent.Guid;

      CurrencyIds = rollEvent.CurrencyIds.Count > 0 ? rollEvent.CurrencyIds.Aggregate((f, s) => f + ", " + s) : string.Empty;
      Rolls = new List<RollEventRuleModel>(rollEvent.Rolls.Select(item => new RollEventRuleModel(item)));

      New = false;
    }

    public RollEvent ToRollEvent()
    {
      RollEvent rollEvent = new RollEvent()
      {
        Locale = Locale,
        Image = Image,
        Text = Text,
        Title = Title,
        PersistentId = EventId,
        Description = Description,
        StartTime = StartTime.ToUnixTimestamp(),
        EndTime = EndTime.ToUnixTimestamp(),
        Enabled = Enabled,
        CompletionTalentId = CompletionTalentId,
        CompletionTalentRatio = CompletionTalentRatio,
        Guid = GUID,
        CurrencyIds = new List<string>(CurrencyIds.Split(',').Select(s => s.Trim()).Where(s => !string.IsNullOrEmpty(s))),
        Rolls = new List<RollEventRule>(Rolls.Select(model => model.ToRollEventRule())),
      };
      return rollEvent;
    }
  }
}