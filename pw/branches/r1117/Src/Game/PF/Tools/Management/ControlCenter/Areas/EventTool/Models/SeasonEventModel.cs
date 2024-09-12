using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Web.Mvc;
using System.Web.UI.MobileControls.Adapters;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class SeasonEventModel
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
    public int SeasonEventGUID { get; set; }

    [DisplayName("Completion Talent PersistentID")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string CompletionTalentId { get; set; }

    [DisplayName("Completion talent convert ratio")]
    [Required]
    [Range(1, 1000000, ErrorMessage = "Must be in range from 1 to 1000000")]
    public int CompletionTalentRatio { get; set; }

    [DisplayName("ShopCurrencyId")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string ShopCurrencyId { get; set; }

    [DisplayName("RewardsCurrencyId")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string RewardsCurrencyId { get; set; }

    [DisplayName( "BannerUrl (1107x597 (мб порезано до 698x597 на узких мониках))" )]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string BannerUrl { get; set; }

    [DisplayName("Title")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Title { get; set; }

    [DisplayName("Text")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Text { get; set; }

    [DisplayName("RewardsBlockTitle")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string RewardsBlockTitle { get; set; }

    [DisplayName("Groups")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("SeasonEventShopGroupModel")]
    public List<SeasonEventShopGroupModel> ShopGroups { get; set; }

    [DisplayName("SeasonProgressRewardRelations")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    public List<SeasonProgressRewardRelation> SeasonProgressRewardRelations { get; set; }

    [DisplayName("WorldRatingRewardRelations")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    public List<WorldRatingRewardRelation> WorldRatingRewardRelations { get; set; }

    #endregion

    #region HelperFields

    public SelectList AvailableLocales { get; set; }
    public bool New { get; set; }

    #endregion

    #region CommandsDefines

    public const string WorldRatingNameCommand = "worldrating_reward";
    public const string ProgressNameCommand = "progress_reward";
    public const string GroupNameCommand = "group";
    public const string MemberNameCommand = "item";

    #endregion

    public SeasonEventModel()
    {
      EventId = 0;
      Description = string.Empty;
      Locale = string.Empty;
      RewardsBlockTitle = string.Empty;
      ShopCurrencyId = string.Empty;
      RewardsCurrencyId = string.Empty;
      StartTime = DateTime.UtcNow.AddDays(1);
      EndTime = DateTime.UtcNow.AddDays(2);
      Enabled = false;
      SeasonEventGUID = -1;

      ShopGroups = new List<SeasonEventShopGroupModel>();
      SeasonProgressRewardRelations = new List<SeasonProgressRewardRelation>();
      WorldRatingRewardRelations = new List<WorldRatingRewardRelation>();
 
      New = true;
    }

    public SeasonEventModel(AccountLib.SeasonEvent model)
    {
      EventId = model.PersistentId;
      Description = model.Description;
      Locale = model.Locale;
      StartTime = model.StartTime.FromUnixTimestamp();
      EndTime = model.EndTime.FromUnixTimestamp();
      Enabled = model.Enabled;

      SeasonEventGUID = model.Guid;
      BannerUrl = model.BannerUrl;
      Title = model.Title;
      Text = model.Text;
      ShopCurrencyId = model.ShopCurrencyId;
      RewardsCurrencyId = model.RewardsCurrencyId;
      CompletionTalentId = model.CompletionTalentId;
      CompletionTalentRatio = model.CompletionTalentRatio;
      RewardsBlockTitle = model.RewardsBlockTitle;

      ShopGroups = model.ShopGroups.Select(q => new SeasonEventShopGroupModel(q)).ToList();
      SeasonProgressRewardRelations = model.ProgressRewardRelations.Select(q => new SeasonProgressRewardRelation(q)).ToList();
      WorldRatingRewardRelations = model.WorldRatingRewardRelations.Select(q => new WorldRatingRewardRelation(q)).ToList();
    }

    public AccountLib.SeasonEvent ToTType()
    {
      return new AccountLib.SeasonEvent
      {
        PersistentId = EventId,
        Description = Description,
        Locale = Locale,
        StartTime = StartTime.ToUnixTimestamp(),
        EndTime = EndTime.ToUnixTimestamp(),
        Enabled = Enabled,
        RewardsBlockTitle = RewardsBlockTitle,

        Guid = SeasonEventGUID,
        Title = Title,
        Text = Text,
        BannerUrl = BannerUrl,
        CompletionTalentId = CompletionTalentId,
        CompletionTalentRatio = CompletionTalentRatio,
        ShopCurrencyId = ShopCurrencyId,
        RewardsCurrencyId = RewardsCurrencyId,
        ShopGroups = ShopGroups.Select(q => q.ToTType()).ToList(),
        ProgressRewardRelations = SeasonProgressRewardRelations.Select(q => q.ToTType()).ToList(),
        WorldRatingRewardRelations = WorldRatingRewardRelations.Select(q => q.ToTType()).ToList(),
      };
    }

    public void PrepareControlFields()
    {
      New = EventId == 0;
      string stageCommandPrefix = GroupNameCommand + "_command:";
      for (int i = 0; i < ShopGroups.Count; i++)
      {
        ShopGroups[i].PrepareControlFields(i, stageCommandPrefix);
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
        case GroupNameCommand + "_add":
          ShopGroups.Add(new SeasonEventShopGroupModel());
          break;
        case GroupNameCommand + "_remove":
          ShopGroups.RemoveAt(param);
          break;
        case GroupNameCommand + "_up":
          Utils.CommandElementMove(param, ShopGroups);
          break;
        case GroupNameCommand + "_down":
          Utils.CommandElementMove(param + 1, ShopGroups);
          break;
        case GroupNameCommand + "_clone":
          ShopGroups.Add(ShopGroups[param].Clone());
          break;
        case GroupNameCommand + "_command":
          return CommandGroupCommand(param, cmdArgs, startIdx + 2);
        default:
          if (cmd.Contains(ProgressNameCommand))
            return CommandExperienceReward(cmd, param);
          else if (cmd.Contains(WorldRatingNameCommand))
            return CommandWorldRatingReward(cmd, param);
          
          return false;
      }

      return true;
    }

    private bool CommandGroupCommand(int index, string[] cmdArgs, int startIndex)
    {
      if (index < 0 || index >= ShopGroups.Count)
        return false;
      return ShopGroups[index].ProcessCommand(cmdArgs, startIndex);
    }

    private bool CommandExperienceReward(string cmd, int param)
    {
      switch (cmd)
      {
        case ProgressNameCommand + "_add":
          SeasonProgressRewardRelations.Add(new SeasonProgressRewardRelation());
          break;
        case ProgressNameCommand + "_remove":
          SeasonProgressRewardRelations.RemoveAt(param);
          break;
        case ProgressNameCommand + "_up":
          Utils.CommandElementMove(param, SeasonProgressRewardRelations);
          break;
        case ProgressNameCommand + "_down":
          Utils.CommandElementMove(param + 1, SeasonProgressRewardRelations);
          break;
        case ProgressNameCommand + "_clone":
          SeasonProgressRewardRelations.Add(SeasonProgressRewardRelations[param].Clone());
          break;
        default:
          return false;
      }
      return true;
    }

    private bool CommandWorldRatingReward(string cmd, int param)
    {
      switch (cmd)
      {
        case WorldRatingNameCommand + "_add":
          WorldRatingRewardRelations.Add(new WorldRatingRewardRelation());
          break;
        case WorldRatingNameCommand + "_remove":
          WorldRatingRewardRelations.RemoveAt(param);
          break;
        case WorldRatingNameCommand + "_up":
          Utils.CommandElementMove(param, WorldRatingRewardRelations);
          break;
        case WorldRatingNameCommand + "_down":
          Utils.CommandElementMove(param + 1, WorldRatingRewardRelations);
          break;
        case WorldRatingNameCommand + "_clone":
          WorldRatingRewardRelations.Add(WorldRatingRewardRelations[param].Clone());
          break;
        default:
          return false;
      }
      return true;
    }
  }

  public class SeasonProgressRewardRelation
  {
    [DisplayName("Reward")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("RollEventItemModel")]
    public RollEventItemModel Reward { get; set; }

    [Required]
    public int RewardCount { get; set; }
    [Required]
    public int RequiredProgress { get; set; }

    public SeasonProgressRewardRelation()
    {
      Reward = new RollEventItemModel(RollEventItemTypeEnum.Lootbox, false);
      RewardCount = 1;
    }

    public SeasonProgressRewardRelation(AccountLib.SeasonProgressRewardRelation model)
    {
      Reward = new RollEventItemModel(model.Reward, false);
      RewardCount = model.RewardCount;
      RequiredProgress = model.RequiredProgress;
    }

    public AccountLib.SeasonProgressRewardRelation ToTType()
    {
      return new AccountLib.SeasonProgressRewardRelation
      {
        Reward = Reward.ToRollEventItem(),
        RewardCount = RewardCount,
        RequiredProgress = RequiredProgress,
      };
    }

    public SeasonProgressRewardRelation Clone()
    {
      return new SeasonProgressRewardRelation
      {
        Reward = Reward.Clone(),
        RewardCount = RewardCount,
        RequiredProgress = RequiredProgress
      };
    }
  } 
}